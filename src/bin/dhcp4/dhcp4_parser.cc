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
      case 176: // value
      case 180: // map_value
      case 218: // socket_type
      case 221: // outbound_interface_value
      case 237: // db_type
      case 321: // hr_mode
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 160: // "boolean"
        value.move< bool > (that.value);
        break;

      case 159: // "floating point"
        value.move< double > (that.value);
        break;

      case 158: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 157: // "constant string"
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
      case 176: // value
      case 180: // map_value
      case 218: // socket_type
      case 221: // outbound_interface_value
      case 237: // db_type
      case 321: // hr_mode
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 160: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 159: // "floating point"
        value.copy< double > (that.value);
        break;

      case 158: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 157: // "constant string"
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
            case 157: // "constant string"

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 158: // "integer"

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 159: // "floating point"

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 160: // "boolean"

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 176: // value

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 180: // map_value

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 218: // socket_type

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 221: // outbound_interface_value

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 237: // db_type

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 321: // hr_mode

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 469: // ncr_protocol_value

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 477: // replace_client_name_value

#line 235 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 176: // value
      case 180: // map_value
      case 218: // socket_type
      case 221: // outbound_interface_value
      case 237: // db_type
      case 321: // hr_mode
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 160: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 159: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 158: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 157: // "constant string"
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
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 370 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 394 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 853 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1979 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1185 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1435 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2571 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2635 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1885 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1974 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3289 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3354 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3426 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3430 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -765;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     310,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,    30,    22,    66,    72,   108,   111,
     125,   154,   195,   216,   233,   242,   249,   257,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,    22,     1,    34,    60,    43,   171,
       6,   115,   157,   368,   382,   -51,   428,    82,  -765,   271,
     273,   279,   281,   289,  -765,  -765,  -765,  -765,  -765,   291,
    -765,    46,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   292,
     294,  -765,  -765,  -765,  -765,  -765,  -765,   297,   299,   300,
     302,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,   303,  -765,  -765,  -765,   126,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,   314,  -765,   137,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   315,   317,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   141,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,   143,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   285,
     319,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   318,  -765,  -765,   321,  -765,  -765,  -765,
     325,  -765,  -765,   322,   320,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   327,   328,
    -765,  -765,  -765,  -765,   326,   330,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   144,  -765,
    -765,  -765,   331,  -765,  -765,   333,  -765,   337,   338,  -765,
    -765,   339,   341,   342,  -765,  -765,  -765,  -765,  -765,   145,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,   147,  -765,  -765,  -765,
      22,    22,  -765,   190,   345,   348,   350,   351,   357,  -765,
      34,  -765,   358,   209,   213,   362,   367,   370,   371,   372,
     373,   224,   225,   231,   236,   387,   391,   394,   396,   398,
     399,   401,   423,   427,   431,   288,   433,   443,    60,  -765,
     444,   445,   446,   307,    43,  -765,   447,   464,   465,   466,
     467,   468,   469,   316,   324,   471,   472,   474,   475,   476,
     171,  -765,   477,     6,  -765,   481,   482,   483,   484,   485,
     486,   487,   488,  -765,   115,  -765,   489,   491,   346,   492,
     493,   499,   347,  -765,   368,   501,   349,   355,  -765,   382,
     502,   504,   100,  -765,   356,   506,   507,   359,   514,   361,
     363,   516,   518,   364,   366,   369,   519,   523,   428,  -765,
     524,    82,  -765,  -765,  -765,   526,   527,   529,    22,    22,
      22,  -765,   530,  -765,  -765,   374,   381,   397,   548,   549,
     552,  -765,  -765,  -765,  -765,   553,   554,   555,   556,   557,
     405,   558,   560,   561,   562,  -765,   563,   564,  -765,   567,
     215,   220,  -765,  -765,   410,   411,   416,   569,   418,   419,
     420,  -765,  -765,   237,   567,   421,   574,   573,  -765,   424,
    -765,   567,   425,   426,   429,   430,   432,   434,   435,  -765,
     436,   437,  -765,   438,   439,   440,  -765,  -765,   441,  -765,
    -765,  -765,   442,    22,  -765,  -765,   448,   449,  -765,   450,
    -765,  -765,    17,   457,  -765,  -765,  -765,   -32,   451,  -765,
     583,  -765,    22,    60,    82,  -765,  -765,  -765,    43,  -765,
    -765,  -765,   378,   378,   593,   594,   595,   596,   597,  -765,
    -765,  -765,    12,   602,   603,    18,    55,   428,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   604,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   605,
     184,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,   606,  -765,   151,   166,   170,  -765,  -765,  -765,
    -765,   586,   610,   611,   612,   613,  -765,  -765,   614,   615,
     616,   617,   618,  -765,   180,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   181,  -765,   619,   620,  -765,  -765,   621,
     623,  -765,  -765,   622,   626,  -765,  -765,   624,   628,  -765,
    -765,   627,   629,  -765,  -765,  -765,  -765,  -765,  -765,    47,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,    58,  -765,  -765,
     630,   631,  -765,   633,   634,   635,   636,   637,   638,   193,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,   206,  -765,  -765,  -765,   208,   478,  -765,   639,
     640,  -765,  -765,   641,   643,  -765,  -765,  -765,  -765,   642,
    -765,    85,  -765,  -765,  -765,  -765,   644,   645,   647,   648,
     495,   494,   497,   496,   500,   653,   655,   503,   505,   508,
     509,   510,   378,  -765,  -765,   378,  -765,   593,   171,  -765,
     594,   368,  -765,   595,   382,  -765,   596,   211,  -765,   597,
      12,  -765,   229,   602,  -765,   -51,  -765,   603,   511,   513,
     515,   517,   520,   521,    18,  -765,   656,   658,    55,  -765,
    -765,  -765,   659,   661,     6,  -765,   604,   115,  -765,   605,
     664,  -765,    -1,   606,  -765,   280,   525,   528,   531,  -765,
    -765,  -765,  -765,  -765,   532,   533,  -765,  -765,  -765,  -765,
    -765,  -765,   219,  -765,   228,  -765,   666,  -765,   668,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,   247,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   673,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   672,   669,  -765,  -765,  -765,  -765,  -765,
     259,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   534,
     535,  -765,  -765,   536,   263,  -765,   675,  -765,   567,  -765,
     677,  -765,  -765,  -765,  -765,  -765,   267,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,   211,  -765,   680,   537,
    -765,   229,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   682,
     538,   683,    -1,  -765,  -765,   541,  -765,  -765,   689,  -765,
     542,  -765,  -765,   688,  -765,  -765,   101,  -765,   -45,   688,
    -765,  -765,   696,   697,   699,   270,  -765,  -765,  -765,  -765,
    -765,  -765,   700,   546,   551,   566,   -45,  -765,   550,  -765,
    -765,  -765,  -765,  -765
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
     518,    25,   575,    27,    45,    39,     0,     0,     0,     0,
       0,   430,     0,   338,   375,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   573,   567,   569,   571,     0,
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
     216,   217,     0,   540,   542,     0,   545,     0,     0,   549,
     553,     0,     0,     0,   558,   565,   538,   536,   537,     0,
     520,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   580,     0,   577,   579,    44,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    55,
       0,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   247,     0,     0,   404,     0,     0,     0,     0,     0,
       0,     0,     0,   429,     0,   329,     0,     0,     0,     0,
       0,     0,     0,   337,     0,     0,     0,     0,   374,     0,
       0,     0,     0,   212,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   519,
       0,     0,   576,    48,    41,     0,     0,     0,     0,     0,
       0,    59,     0,   103,   104,     0,     0,     0,     0,     0,
       0,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   502,     0,     0,    71,     0,
       0,     0,   128,   108,     0,     0,     0,     0,     0,     0,
       0,   296,   297,     0,     0,     0,     0,     0,   249,     0,
     406,     0,     0,     0,     0,     0,     0,     0,     0,   433,
       0,     0,   353,     0,     0,     0,   364,   341,     0,   393,
     394,   378,     0,     0,   214,   539,     0,     0,   544,     0,
     547,   548,     0,     0,   555,   556,   557,     0,     0,   521,
       0,   578,     0,     0,     0,   568,   570,   572,     0,   450,
     452,   454,     0,     0,   135,   240,   330,   367,   300,    38,
     417,   419,     0,     0,   205,     0,     0,     0,    49,   119,
     122,   123,   121,   126,   127,   125,   278,   280,   282,   397,
     276,   284,   286,   293,   294,   295,   292,   290,   288,   422,
       0,   415,   472,   460,   462,   466,   464,   470,   468,   456,
     356,   175,   360,   358,   363,   390,   219,   221,   541,   543,
     546,   551,   552,   550,   554,   560,   561,   562,   563,   564,
     559,   566,     0,    42,     0,     0,     0,   161,   167,   169,
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
     584,     0,   582,    67,   574,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   132,     0,   134,     0,     0,   239,
       0,   338,   327,     0,   375,   366,     0,     0,   299,     0,
       0,   190,   483,     0,   478,     0,   204,     0,     0,     0,
       0,     0,     0,     0,     0,   223,     0,     0,     0,   504,
     517,    53,     0,    52,     0,   396,     0,   430,   421,     0,
       0,   474,     0,     0,   581,     0,     0,     0,     0,   173,
     176,   177,   178,   179,     0,     0,   187,   188,   180,   181,
     182,   142,     0,   138,     0,   243,     0,   333,     0,   370,
     325,   322,   311,   312,   314,   308,   309,   310,   320,   321,
     319,     0,   306,   313,   323,   324,   315,   316,   317,   318,
     303,   192,   499,     0,   497,   498,   490,   491,   495,   496,
     492,   493,   494,     0,   484,   485,   487,   488,   489,   480,
       0,   208,   232,   233,   234,   235,   236,   237,   225,     0,
       0,   506,    50,     0,     0,   400,     0,   425,     0,   598,
       0,   596,   594,   588,   592,   593,     0,   586,   590,   591,
     589,   583,   163,   164,   165,   166,   162,   168,   170,   172,
     184,   186,   140,   245,   335,   372,     0,   305,     0,     0,
     482,     0,   210,   513,   515,    54,   402,   427,   458,     0,
       0,     0,     0,   585,   307,     0,   501,   486,     0,   595,
       0,   587,   500,     0,   597,   602,     0,   600,     0,     0,
     599,   610,     0,     0,     0,     0,   604,   606,   607,   608,
     609,   601,     0,     0,     0,     0,     0,   603,     0,   612,
     613,   614,   605,   611
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   -40,  -765,   155,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -468,  -765,  -765,  -765,
     -66,  -765,  -765,  -765,   304,  -765,  -765,  -765,  -765,   167,
     365,   -23,   -11,    -9,  -765,  -765,     9,  -765,  -765,   165,
     352,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
     -52,  -765,  -547,   -37,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,   -22,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,   -53,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,   -58,  -765,  -765,  -765,   -55,   353,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   -47,  -765,  -765,  -765,  -765,
    -765,  -765,  -764,  -765,  -765,  -765,   -31,  -765,  -765,  -765,
       8,   377,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -756,  -765,  -765,  -765,   -42,  -765,    -5,  -765,  -739,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,   -16,  -765,  -765,
    -157,   -61,  -765,  -765,  -765,  -765,  -765,    10,  -765,  -765,
    -765,    11,  -765,   375,  -765,   -62,  -765,  -765,  -765,  -765,
    -765,   -56,  -765,  -765,  -765,  -765,  -765,    -3,  -765,  -765,
    -765,    15,  -765,  -765,  -765,    13,  -765,   376,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   -18,
    -765,  -765,  -765,   -20,   400,  -765,  -765,   -54,  -765,   -34,
    -765,  -765,  -765,  -765,  -765,   -17,  -765,  -765,  -765,   -13,
    -765,   392,   -46,  -765,   -26,  -765,     3,  -765,   207,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -736,  -765,  -765,  -765,
    -765,  -765,    19,  -765,  -765,  -765,  -133,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,     2,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,   238,   379,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   262,
     380,  -765,  -765,  -765,   -10,  -765,  -765,  -135,  -765,  -765,
    -765,  -765,  -765,  -765,  -151,  -765,  -765,  -167,  -765,  -765,
    -765,  -765,  -765
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   560,
      82,    83,    39,    64,    79,    80,   569,   727,   802,   803,
     643,    41,    66,    91,    92,    93,   334,    43,    67,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   342,   158,
     159,    45,    68,   160,   370,   161,   371,   572,   162,   372,
     575,   163,   134,   348,   135,   349,   136,   350,   665,   666,
     667,   765,   644,   645,   646,   746,   916,   647,   747,   648,
     748,   649,   749,   650,   651,   407,   652,   653,   654,   655,
     656,   657,   658,   659,   755,   660,   756,   661,   662,   137,
     361,   689,   690,   691,   692,   693,   694,   695,   138,   363,
     700,   701,   702,   785,    59,    75,   288,   289,   290,   420,
     291,   421,   139,   364,   709,   710,   711,   712,   713,   714,
     715,   716,   140,   355,   669,   670,   671,   768,    47,    69,
     185,   186,   187,   380,   188,   376,   189,   377,   190,   378,
     191,   381,   192,   382,   193,   387,   194,   386,   195,   385,
     586,   196,   197,   141,   358,   681,   682,   683,   777,   851,
     852,   142,   356,    53,    72,   673,   674,   675,   771,    55,
      73,   253,   254,   255,   256,   257,   258,   259,   406,   260,
     410,   261,   409,   262,   263,   411,   264,   143,   357,   677,
     678,   679,   774,    57,    74,   274,   275,   276,   277,   278,
     415,   279,   280,   281,   282,   199,   379,   729,   730,   731,
     804,    49,    70,   212,   213,   214,   392,   144,   359,   145,
     360,   202,   388,   733,   734,   735,   807,    51,    71,   229,
     230,   231,   146,   345,   147,   346,   148,   347,   235,   402,
     738,   810,   236,   396,   237,   397,   238,   399,   239,   398,
     240,   401,   241,   400,   242,   395,   206,   389,   739,   149,
     362,   697,   698,   782,   873,   874,   875,   876,   877,   928,
     878,   150,   151,   366,   722,   723,   724,   796,   725,   797,
     152,   367,    61,    76,   309,   310,   311,   312,   425,   313,
     426,   314,   315,   428,   316,   317,   318,   431,   613,   319,
     432,   320,   321,   322,   323,   436,   620,   324,   437,    94,
     336,    95,   337,    96,   338,    97,   335,    63,    77,   326,
     327,   328,   440,   741,   742,   812,   906,   907,   908,   909,
     941,   910,   939,   956,   957,   958,   965,   966,   967,   972,
     968,   969,   970
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   124,   157,   180,   208,   225,   663,   251,   270,   287,
     306,   243,   272,   846,   164,   200,   215,   227,   273,   265,
     283,   847,   307,   203,    78,   232,   587,    29,   209,    30,
      28,    31,   611,   592,   165,   201,   216,   228,   850,   266,
     284,   859,   308,   204,    84,   233,   181,   285,   286,   340,
     780,   252,   271,   781,   341,   153,   154,   245,   182,   155,
     183,   783,   156,   113,   784,   210,   198,   211,   226,   115,
     116,    98,   205,    40,   234,   207,   115,   116,   184,    42,
      99,   100,   101,   102,   103,   104,   105,   106,   813,   176,
     961,   814,   177,   962,   963,   964,   615,   616,   617,   618,
     684,   685,   686,   687,   959,   688,    89,   960,   107,   108,
     109,   110,   111,   115,   116,    44,   112,   113,    46,   703,
     704,   705,   706,   707,   708,   115,   116,   114,   619,   368,
     115,   116,    48,   899,   369,   900,   901,   101,   102,   103,
     374,   117,   118,   612,   390,   375,   393,   422,   438,   391,
     441,   394,   423,   439,   368,   442,    89,   119,    81,   743,
     120,    50,   846,    89,   717,   718,    85,   121,   122,   441,
     847,   123,   113,   374,   744,    86,    87,    88,   745,    32,
      33,    34,    35,   762,   762,   115,   116,   850,   763,   764,
     859,    89,   100,   101,   102,   103,   794,   217,   285,   286,
      89,   795,    52,   218,   219,   220,   221,   222,   223,   798,
     224,   438,    89,   112,   799,   325,   800,    89,   832,   107,
     108,   109,   762,    54,   166,   167,   168,   922,   113,   570,
     571,   390,   100,   101,   102,   103,   923,   573,   574,   169,
      56,   115,   116,   170,   171,   172,   173,   174,   175,    58,
     926,   101,   102,   103,   176,   927,    60,   177,   178,   107,
     108,   109,   422,   111,    62,   179,   393,   932,   113,   245,
     942,   936,    89,   976,    90,   943,   330,   329,   977,   224,
     736,   115,   116,   331,   171,   112,   113,   245,   175,   332,
     443,   444,   333,   403,   176,   339,   343,   177,   344,   115,
     116,   351,   124,   352,   353,   179,   354,   365,   157,   912,
     913,   914,   915,   862,   863,   583,   584,   585,   373,   383,
     164,   384,   404,   414,   180,   408,   405,   208,    89,   412,
     413,   416,   417,   419,   418,   424,   200,   427,   225,   215,
     165,   429,   430,   433,   203,   434,   435,   445,   251,   446,
     227,   209,   447,   270,   448,   449,   201,   272,   232,   216,
     265,   450,   452,   273,   204,   283,   455,   181,    89,   453,
     228,   456,   306,   454,   457,   458,   459,   460,   233,   182,
     266,   183,   461,   462,   307,   284,    89,   198,   210,   463,
     211,   465,   252,   205,   464,   466,   244,   271,   467,   184,
     468,   226,   469,   470,   308,   471,   627,   234,   545,   546,
     547,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,   639,   640,   641,   642,   245,   472,   246,   247,
     938,   473,   248,   249,   250,   474,   245,   476,   115,   116,
     245,   267,   246,   247,   268,   269,   475,   477,   479,   480,
     481,   484,   115,   116,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   482,   485,   486,
     487,   488,   489,   490,   491,   493,   494,   124,   495,   496,
     497,   499,   157,   607,   492,   501,   502,   503,   504,   505,
     506,   507,   508,   510,   164,   511,   513,   514,   115,   116,
     719,   306,   623,   515,   512,   518,   522,   516,   523,   519,
     526,   527,   720,   307,   165,   520,   525,   528,   529,   530,
     532,   531,   533,   537,   534,    89,   535,   538,   540,   536,
     542,   549,   721,   308,   543,    89,   544,   548,   550,    89,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   551,   552,   553,   554,   555,   556,
     557,   558,   561,   562,    30,   563,   564,   576,   577,   565,
     566,   567,   568,   578,   579,   580,   581,   582,   588,   589,
     590,   591,   593,   594,   614,    89,   595,   596,   622,   597,
     750,   598,   599,   600,   601,   602,   603,   604,   605,   606,
     664,   668,   672,   676,   680,   608,   609,   610,   621,   696,
     699,   728,   732,   740,   751,   752,   753,   754,   757,   758,
     759,   760,   761,   767,   559,   766,   770,   769,   772,   773,
     775,   776,   779,   778,   787,   801,   786,   788,   789,   790,
     791,   792,   793,   806,   451,   805,   809,   808,   815,   816,
     811,   817,   818,   819,   820,   821,   822,   824,   823,   825,
     889,   826,   890,   827,   893,   892,   828,   829,   898,   882,
     830,   883,   931,   884,   924,   885,   925,   929,   886,   887,
     930,   940,   917,   937,   945,   918,   948,   950,   919,   920,
     921,   933,   934,   935,   953,   955,   949,   946,   952,   954,
     973,   974,   180,   975,   978,   251,   979,   983,   270,   980,
     624,   840,   272,   626,   200,   833,   864,   265,   273,   287,
     283,   866,   203,   854,   981,   831,   483,   861,   868,   881,
     880,   856,   719,   478,   201,   848,   870,   266,   208,   835,
     284,   225,   204,   855,   720,   181,   902,   888,   869,   252,
     215,   857,   271,   227,   841,   845,   871,   182,   904,   183,
     865,   232,   209,   860,   721,   198,   842,   498,   843,   944,
     216,   205,   849,   228,   853,   524,   834,   184,   905,   867,
     858,   233,   836,   837,   894,   872,   844,   838,   895,   517,
     903,   839,   897,   500,   896,   521,   509,   737,   947,   210,
     891,   211,   879,   911,   226,   726,   625,   951,   971,   982,
     234,     0,     0,     0,     0,     0,     0,   539,     0,     0,
       0,   541,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     840,     0,     0,     0,     0,   864,     0,     0,     0,     0,
     866,     0,   854,     0,     0,     0,   902,   868,     0,     0,
     856,     0,     0,     0,   848,   870,     0,     0,   904,     0,
       0,     0,   855,     0,     0,     0,     0,   869,     0,     0,
     857,     0,     0,   841,   845,   871,     0,     0,   905,   865,
       0,     0,     0,     0,     0,   842,     0,   843,     0,     0,
     903,   849,     0,   853,     0,     0,     0,     0,   867,   858,
       0,     0,     0,     0,   872,   844
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,   553,    73,    74,    75,
      76,    72,    74,   777,    68,    69,    70,    71,    74,    73,
      74,   777,    76,    69,    64,    71,   494,     5,    70,     7,
       0,     9,    15,   501,    68,    69,    70,    71,   777,    73,
      74,   777,    76,    69,    10,    71,    69,    98,    99,     3,
       3,    73,    74,     6,     8,    12,    13,    58,    69,    16,
      69,     3,    19,    57,     6,    70,    69,    70,    71,    70,
      71,    11,    69,     7,    71,    69,    70,    71,    69,     7,
      20,    21,    22,    23,    24,    25,    26,    27,     3,    83,
     135,     6,    86,   138,   139,   140,   128,   129,   130,   131,
      88,    89,    90,    91,     3,    93,   157,     6,    48,    49,
      50,    51,    52,    70,    71,     7,    56,    57,     7,   101,
     102,   103,   104,   105,   106,    70,    71,    67,   160,     3,
      70,    71,     7,   134,     8,   136,   137,    22,    23,    24,
       3,    81,    82,   126,     3,     8,     3,     3,     3,     8,
       3,     8,     8,     8,     3,     8,   157,    97,   157,     8,
     100,     7,   926,   157,   109,   110,   132,   107,   108,     3,
     926,   111,    57,     3,     8,   141,   142,   143,     8,   157,
     158,   159,   160,     3,     3,    70,    71,   926,     8,     8,
     926,   157,    21,    22,    23,    24,     3,    82,    98,    99,
     157,     8,     7,    88,    89,    90,    91,    92,    93,     3,
      95,     3,   157,    56,     8,   133,     8,   157,   765,    48,
      49,    50,     3,     7,    53,    54,    55,     8,    57,    14,
      15,     3,    21,    22,    23,    24,     8,    17,    18,    68,
       7,    70,    71,    72,    73,    74,    75,    76,    77,     7,
       3,    22,    23,    24,    83,     8,     7,    86,    87,    48,
      49,    50,     3,    52,     7,    94,     3,     8,    57,    58,
       3,     8,   157,     3,   340,     8,     3,     6,     8,    95,
      96,    70,    71,     4,    73,    56,    57,    58,    77,     8,
     330,   331,     3,     8,    83,     4,     4,    86,     4,    70,
      71,     4,   368,     4,     4,    94,     4,     4,   374,    29,
      30,    31,    32,    84,    85,    78,    79,    80,     4,     4,
     374,     4,     3,     3,   390,     4,     8,   393,   157,     4,
       8,     4,     4,     3,     8,     4,   390,     4,   404,   393,
     374,     4,     4,     4,   390,     4,     4,   157,   414,     4,
     404,   393,     4,   419,     4,     4,   390,   419,   404,   393,
     414,     4,     4,   419,   390,   419,     4,   390,   157,   160,
     404,     4,   438,   160,     4,     4,     4,     4,   404,   390,
     414,   390,   158,   158,   438,   419,   157,   390,   393,   158,
     393,     4,   414,   390,   158,     4,    28,   419,     4,   390,
       4,   404,     4,     4,   438,     4,    28,   404,   448,   449,
     450,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    58,     4,    60,    61,
     898,     4,    64,    65,    66,     4,    58,     4,    70,    71,
      58,    59,    60,    61,    62,    63,   158,     4,     4,     4,
       4,     4,    70,    71,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   160,     4,     4,
       4,     4,     4,     4,   158,     4,     4,   543,     4,     4,
       4,     4,   548,   523,   160,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   548,     4,     4,     4,    70,    71,
     566,   567,   542,     4,   158,     4,     4,   160,     4,   160,
       4,     4,   566,   567,   548,   160,   160,   158,     4,   158,
       4,   158,     4,     4,   160,   157,   160,     4,     4,   160,
       4,   157,   566,   567,     7,   157,     7,     7,   157,   157,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   157,     7,     7,     5,     5,     5,
       5,     5,   157,     5,     7,     5,     5,   157,   157,     7,
       7,     7,     5,   157,     5,   157,   157,   157,   157,     5,
       7,   157,   157,   157,   127,   157,   157,   157,     5,   157,
       4,   157,   157,   157,   157,   157,   157,   157,   157,   157,
       7,     7,     7,     7,     7,   157,   157,   157,   157,     7,
       7,     7,     7,     7,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   469,     6,     3,     6,     6,     3,
       6,     3,     3,     6,     3,   157,     6,     4,     4,     4,
       4,     4,     4,     3,   340,     6,     3,     6,     4,     4,
       8,     4,     4,   158,   160,   158,   160,     4,   158,     4,
       4,   158,     4,   158,     3,     6,   158,   158,     4,   158,
     160,   158,     3,   158,     8,   158,     8,     4,   158,   158,
       8,     4,   157,     8,     4,   157,     4,     4,   157,   157,
     157,   157,   157,   157,     5,     7,   158,   160,   157,   157,
       4,     4,   768,     4,     4,   771,   160,   157,   774,   158,
     543,   777,   774,   548,   768,   767,   782,   771,   774,   785,
     774,   782,   768,   777,   158,   762,   374,   780,   782,   787,
     785,   777,   798,   368,   768,   777,   782,   771,   804,   770,
     774,   807,   768,   777,   798,   768,   812,   794,   782,   771,
     804,   777,   774,   807,   777,   777,   782,   768,   812,   768,
     782,   807,   804,   779,   798,   768,   777,   390,   777,   926,
     804,   768,   777,   807,   777,   422,   768,   768,   812,   782,
     777,   807,   771,   773,   804,   782,   777,   774,   806,   414,
     812,   776,   809,   393,   807,   419,   404,   590,   931,   804,
     798,   804,   783,   813,   807,   567,   544,   942,   959,   976,
     807,    -1,    -1,    -1,    -1,    -1,    -1,   438,    -1,    -1,
      -1,   441,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     926,    -1,    -1,    -1,    -1,   931,    -1,    -1,    -1,    -1,
     931,    -1,   926,    -1,    -1,    -1,   942,   931,    -1,    -1,
     926,    -1,    -1,    -1,   926,   931,    -1,    -1,   942,    -1,
      -1,    -1,   926,    -1,    -1,    -1,    -1,   931,    -1,    -1,
     926,    -1,    -1,   926,   926,   931,    -1,    -1,   942,   931,
      -1,    -1,    -1,    -1,    -1,   926,    -1,   926,    -1,    -1,
     942,   926,    -1,   926,    -1,    -1,    -1,    -1,   931,   926,
      -1,    -1,    -1,    -1,   931,   926
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     5,
       7,     9,   157,   158,   159,   160,   176,   177,   178,   183,
       7,   192,     7,   198,     7,   212,     7,   299,     7,   382,
       7,   398,     7,   334,     7,   340,     7,   364,     7,   275,
       7,   453,     7,   488,   184,   179,   193,   199,   213,   300,
     383,   399,   335,   341,   365,   276,   454,   489,   176,   185,
     186,   157,   181,   182,    10,   132,   141,   142,   143,   157,
     191,   194,   195,   196,   480,   482,   484,   486,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    48,    49,    50,
      51,    52,    56,    57,    67,    70,    71,    81,    82,    97,
     100,   107,   108,   111,   191,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   223,   225,   227,   260,   269,   283,
     293,   324,   332,   358,   388,   390,   403,   405,   407,   430,
     442,   443,   451,    12,    13,    16,    19,   191,   210,   211,
     214,   216,   219,   222,   388,   390,    53,    54,    55,    68,
      72,    73,    74,    75,    76,    77,    83,    86,    87,    94,
     191,   202,   203,   204,   207,   301,   302,   303,   305,   307,
     309,   311,   313,   315,   317,   319,   322,   323,   358,   376,
     388,   390,   392,   403,   405,   407,   427,    69,   191,   315,
     317,   358,   384,   385,   386,   388,   390,    82,    88,    89,
      90,    91,    92,    93,    95,   191,   358,   388,   390,   400,
     401,   402,   403,   405,   407,   409,   413,   415,   417,   419,
     421,   423,   425,   332,    28,    58,    60,    61,    64,    65,
      66,   191,   245,   342,   343,   344,   345,   346,   347,   348,
     350,   352,   354,   355,   357,   388,   390,    59,    62,    63,
     191,   245,   346,   352,   366,   367,   368,   369,   370,   372,
     373,   374,   375,   388,   390,    98,    99,   191,   277,   278,
     279,   281,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   191,   388,   390,   455,
     456,   457,   458,   460,   462,   463,   465,   466,   467,   470,
     472,   473,   474,   475,   478,   133,   490,   491,   492,     6,
       3,     4,     8,     3,   197,   487,   481,   483,   485,     4,
       3,     8,   209,     4,     4,   404,   406,   408,   224,   226,
     228,     4,     4,     4,     4,   294,   333,   359,   325,   389,
     391,   261,   431,   270,   284,     4,   444,   452,     3,     8,
     215,   217,   220,     4,     3,     8,   306,   308,   310,   377,
     304,   312,   314,     4,     4,   320,   318,   316,   393,   428,
       3,     8,   387,     3,     8,   426,   414,   416,   420,   418,
     424,   422,   410,     8,     3,     8,   349,   246,     4,   353,
     351,   356,     4,     8,     3,   371,     4,     4,     8,     3,
     280,   282,     3,     8,     4,   459,   461,     4,   464,     4,
       4,   468,   471,     4,     4,     4,   476,   479,     3,     8,
     493,     3,     8,   176,   176,   157,     4,     4,     4,     4,
       4,   195,     4,   160,   160,     4,     4,     4,     4,     4,
       4,   158,   158,   158,   158,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   158,     4,     4,   201,     4,
       4,     4,   160,   211,     4,     4,     4,     4,     4,     4,
       4,   158,   160,     4,     4,     4,     4,     4,   302,     4,
     385,     4,     4,     4,     4,     4,     4,     4,     4,   402,
       4,     4,   158,     4,     4,     4,   160,   344,     4,   160,
     160,   368,     4,     4,   278,   160,     4,     4,   158,     4,
     158,   158,     4,     4,   160,   160,   160,     4,     4,   456,
       4,   491,     4,     7,     7,   176,   176,   176,     7,   157,
     157,   157,     7,     7,     5,     5,     5,     5,     5,   178,
     180,   157,     5,     5,     5,     7,     7,     7,     5,   187,
      14,    15,   218,    17,    18,   221,   157,   157,   157,     5,
     157,   157,   157,    78,    79,    80,   321,   187,   157,     5,
       7,   157,   187,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   176,   157,   157,
     157,    15,   126,   469,   127,   128,   129,   130,   131,   160,
     477,   157,     5,   176,   200,   490,   210,    28,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   191,   233,   234,   235,   238,   240,   242,
     244,   245,   247,   248,   249,   250,   251,   252,   253,   254,
     256,   258,   259,   233,     7,   229,   230,   231,     7,   295,
     296,   297,     7,   336,   337,   338,     7,   360,   361,   362,
       7,   326,   327,   328,    88,    89,    90,    91,    93,   262,
     263,   264,   265,   266,   267,   268,     7,   432,   433,     7,
     271,   272,   273,   101,   102,   103,   104,   105,   106,   285,
     286,   287,   288,   289,   290,   291,   292,   109,   110,   191,
     388,   390,   445,   446,   447,   449,   455,   188,     7,   378,
     379,   380,     7,   394,   395,   396,    96,   409,   411,   429,
       7,   494,   495,     8,     8,     8,   236,   239,   241,   243,
       4,     4,     4,     4,     4,   255,   257,     4,     4,     4,
       4,     4,     3,     8,     8,   232,     6,     3,   298,     6,
       3,   339,     6,     3,   363,     6,     3,   329,     6,     3,
       3,     6,   434,     3,     6,   274,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   448,   450,     3,     8,
       8,   157,   189,   190,   381,     6,     3,   397,     6,     3,
     412,     8,   496,     3,     6,     4,     4,     4,     4,   158,
     160,   158,   160,   158,     4,     4,   158,   158,   158,   158,
     160,   234,   233,   231,   301,   297,   342,   338,   366,   362,
     191,   202,   203,   204,   207,   245,   293,   311,   315,   317,
     319,   330,   331,   358,   388,   390,   403,   405,   407,   427,
     328,   263,    84,    85,   191,   245,   332,   358,   388,   390,
     403,   405,   407,   435,   436,   437,   438,   439,   441,   433,
     277,   273,   158,   158,   158,   158,   158,   158,   286,     4,
       4,   446,     6,     3,   384,   380,   400,   396,     4,   134,
     136,   137,   191,   245,   388,   390,   497,   498,   499,   500,
     502,   495,    29,    30,    31,    32,   237,   157,   157,   157,
     157,   157,     8,     8,     8,     8,     3,     8,   440,     4,
       8,     3,     8,   157,   157,   157,     8,     8,   187,   503,
       4,   501,     3,     8,   331,     4,   160,   437,     4,   158,
       4,   498,   157,     5,   157,     7,   504,   505,   506,     3,
       6,   135,   138,   139,   140,   507,   508,   509,   511,   512,
     513,   505,   510,     4,     4,     4,     3,     8,     4,   160,
     158,   158,   508,   157
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   161,   163,   162,   164,   162,   165,   162,   166,   162,
     167,   162,   168,   162,   169,   162,   170,   162,   171,   162,
     172,   162,   173,   162,   174,   162,   175,   162,   176,   176,
     176,   176,   176,   176,   176,   177,   179,   178,   180,   181,
     181,   182,   182,   184,   183,   185,   185,   186,   186,   188,
     187,   189,   189,   190,   190,   191,   193,   192,   194,   194,
     195,   195,   195,   195,   195,   195,   197,   196,   199,   198,
     200,   200,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   202,
     203,   204,   205,   206,   207,   209,   208,   210,   210,   211,
     211,   211,   211,   211,   211,   211,   213,   212,   215,   214,
     217,   216,   218,   218,   220,   219,   221,   221,   222,   224,
     223,   226,   225,   228,   227,   229,   229,   230,   230,   232,
     231,   233,   233,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   236,   235,   237,   237,   237,   237,   239,   238,   241,
     240,   243,   242,   244,   246,   245,   247,   248,   249,   250,
     251,   252,   253,   255,   254,   257,   256,   258,   259,   261,
     260,   262,   262,   263,   263,   263,   263,   263,   264,   265,
     266,   267,   268,   270,   269,   271,   271,   272,   272,   274,
     273,   276,   275,   277,   277,   277,   278,   278,   280,   279,
     282,   281,   284,   283,   285,   285,   286,   286,   286,   286,
     286,   286,   287,   288,   289,   290,   291,   292,   294,   293,
     295,   295,   296,   296,   298,   297,   300,   299,   301,   301,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   304,   303,   306,   305,   308,
     307,   310,   309,   312,   311,   314,   313,   316,   315,   318,
     317,   320,   319,   321,   321,   321,   322,   323,   325,   324,
     326,   326,   327,   327,   329,   328,   330,   330,   331,   331,
     331,   331,   331,   331,   331,   331,   331,   331,   331,   331,
     331,   331,   331,   331,   331,   331,   333,   332,   335,   334,
     336,   336,   337,   337,   339,   338,   341,   340,   342,   342,
     343,   343,   344,   344,   344,   344,   344,   344,   344,   344,
     344,   344,   345,   346,   347,   349,   348,   351,   350,   353,
     352,   354,   356,   355,   357,   359,   358,   360,   360,   361,
     361,   363,   362,   365,   364,   366,   366,   367,   367,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   369,   371,
     370,   372,   373,   374,   375,   377,   376,   378,   378,   379,
     379,   381,   380,   383,   382,   384,   384,   385,   385,   385,
     385,   385,   385,   385,   387,   386,   389,   388,   391,   390,
     393,   392,   394,   394,   395,   395,   397,   396,   399,   398,
     400,   400,   401,   401,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   404,
     403,   406,   405,   408,   407,   410,   409,   412,   411,   414,
     413,   416,   415,   418,   417,   420,   419,   422,   421,   424,
     423,   426,   425,   428,   427,   429,   429,   431,   430,   432,
     432,   434,   433,   435,   435,   436,   436,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   438,   440,
     439,   441,   442,   444,   443,   445,   445,   446,   446,   446,
     446,   446,   448,   447,   450,   449,   452,   451,   454,   453,
     455,   455,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   457,
     459,   458,   461,   460,   462,   464,   463,   465,   466,   468,
     467,   469,   469,   471,   470,   472,   473,   474,   476,   475,
     477,   477,   477,   477,   477,   479,   478,   481,   480,   483,
     482,   485,   484,   487,   486,   489,   488,   490,   490,   491,
     493,   492,   494,   494,   496,   495,   497,   497,   498,   498,
     498,   498,   498,   498,   498,   499,   501,   500,   503,   502,
     504,   504,   506,   505,   507,   507,   508,   508,   508,   508,
     510,   509,   511,   512,   513
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     3
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
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_LOGGING", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp4_object", "$@18", "sub_dhcp4",
  "$@19", "global_params", "global_param", "valid_lifetime", "renew_timer",
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
  "generated_prefix", "$@105", "dhcp6_json_object", "$@106",
  "dhcpddns_json_object", "$@107", "control_agent_json_object", "$@108",
  "logging_object", "$@109", "sub_logging", "$@110", "logging_params",
  "logging_param", "loggers", "$@111", "loggers_entries", "logger_entry",
  "$@112", "logger_params", "logger_param", "debuglevel", "severity",
  "$@113", "output_options_list", "$@114", "output_options_list_content",
  "output_entry", "$@115", "output_params_list", "output_params", "output",
  "$@116", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   244,   244,   244,   245,   245,   246,   246,   247,   247,
     248,   248,   249,   249,   250,   250,   251,   251,   252,   252,
     253,   253,   254,   254,   255,   255,   256,   256,   264,   265,
     266,   267,   268,   269,   270,   273,   278,   278,   289,   292,
     293,   296,   300,   307,   307,   314,   315,   318,   322,   329,
     329,   336,   337,   340,   344,   355,   365,   365,   381,   382,
     386,   387,   388,   389,   390,   391,   394,   394,   409,   409,
     418,   419,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   453,
     458,   463,   468,   473,   478,   484,   484,   495,   496,   499,
     500,   501,   502,   503,   504,   505,   508,   508,   517,   517,
     527,   527,   534,   535,   538,   538,   545,   547,   551,   557,
     557,   569,   569,   581,   581,   591,   592,   595,   596,   599,
     599,   609,   610,   613,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   624,   625,   626,   627,   628,   629,
     630,   633,   633,   640,   641,   642,   643,   646,   646,   654,
     654,   662,   662,   670,   675,   675,   683,   688,   693,   698,
     703,   708,   713,   718,   718,   726,   726,   734,   739,   744,
     744,   754,   755,   758,   759,   760,   761,   762,   765,   770,
     775,   780,   785,   790,   790,   800,   801,   804,   805,   808,
     808,   818,   818,   828,   829,   830,   833,   834,   837,   837,
     845,   845,   853,   853,   864,   865,   868,   869,   870,   871,
     872,   873,   876,   881,   886,   891,   896,   901,   909,   909,
     922,   923,   926,   927,   934,   934,   960,   960,   971,   972,
     976,   977,   978,   979,   980,   981,   982,   983,   984,   985,
     986,   987,   988,   989,   990,   991,   992,   993,   994,   995,
     996,   997,   998,   999,  1000,  1003,  1003,  1011,  1011,  1019,
    1019,  1027,  1027,  1035,  1035,  1043,  1043,  1051,  1051,  1059,
    1059,  1069,  1069,  1076,  1077,  1078,  1081,  1086,  1093,  1093,
    1104,  1105,  1109,  1110,  1113,  1113,  1121,  1122,  1125,  1126,
    1127,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,
    1137,  1138,  1139,  1140,  1141,  1142,  1149,  1149,  1162,  1162,
    1171,  1172,  1175,  1176,  1181,  1181,  1196,  1196,  1210,  1211,
    1214,  1215,  1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,
    1226,  1227,  1230,  1232,  1237,  1239,  1239,  1247,  1247,  1255,
    1255,  1263,  1265,  1265,  1273,  1282,  1282,  1294,  1295,  1300,
    1301,  1306,  1306,  1318,  1318,  1330,  1331,  1336,  1337,  1342,
    1343,  1344,  1345,  1346,  1347,  1348,  1349,  1350,  1353,  1355,
    1355,  1363,  1365,  1367,  1372,  1380,  1380,  1392,  1393,  1396,
    1397,  1400,  1400,  1410,  1410,  1420,  1421,  1424,  1425,  1426,
    1427,  1428,  1429,  1430,  1433,  1433,  1441,  1441,  1466,  1466,
    1496,  1496,  1506,  1507,  1510,  1511,  1514,  1514,  1523,  1523,
    1532,  1533,  1536,  1537,  1541,  1542,  1543,  1544,  1545,  1546,
    1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,  1558,
    1558,  1566,  1566,  1574,  1574,  1582,  1582,  1590,  1590,  1600,
    1600,  1608,  1608,  1616,  1616,  1624,  1624,  1632,  1632,  1640,
    1640,  1648,  1648,  1661,  1661,  1671,  1672,  1678,  1678,  1688,
    1689,  1692,  1692,  1702,  1703,  1706,  1707,  1710,  1711,  1712,
    1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,  1723,  1725,
    1725,  1733,  1742,  1749,  1749,  1759,  1760,  1763,  1764,  1765,
    1766,  1767,  1770,  1770,  1778,  1778,  1788,  1788,  1800,  1800,
    1810,  1811,  1814,  1815,  1816,  1817,  1818,  1819,  1820,  1821,
    1822,  1823,  1824,  1825,  1826,  1827,  1828,  1829,  1830,  1833,
    1838,  1838,  1846,  1846,  1854,  1859,  1859,  1867,  1872,  1877,
    1877,  1885,  1886,  1889,  1889,  1897,  1902,  1907,  1912,  1912,
    1920,  1923,  1926,  1929,  1932,  1938,  1938,  1948,  1948,  1955,
    1955,  1962,  1962,  1974,  1974,  1984,  1984,  1995,  1996,  2000,
    2004,  2004,  2016,  2017,  2021,  2021,  2029,  2030,  2033,  2034,
    2035,  2036,  2037,  2038,  2039,  2042,  2047,  2047,  2055,  2055,
    2065,  2066,  2069,  2069,  2077,  2078,  2081,  2082,  2083,  2084,
    2087,  2087,  2095,  2100,  2105
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
#line 4654 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2110 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
