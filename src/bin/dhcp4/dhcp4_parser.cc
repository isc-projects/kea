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
      case 173: // value
      case 177: // map_value
      case 215: // socket_type
      case 218: // outbound_interface_value
      case 234: // db_type
      case 316: // hr_mode
      case 462: // ncr_protocol_value
      case 470: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 157: // "boolean"
        value.move< bool > (that.value);
        break;

      case 156: // "floating point"
        value.move< double > (that.value);
        break;

      case 155: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 154: // "constant string"
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
      case 173: // value
      case 177: // map_value
      case 215: // socket_type
      case 218: // outbound_interface_value
      case 234: // db_type
      case 316: // hr_mode
      case 462: // ncr_protocol_value
      case 470: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 157: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 156: // "floating point"
        value.copy< double > (that.value);
        break;

      case 155: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 154: // "constant string"
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
            case 154: // "constant string"

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 155: // "integer"

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 156: // "floating point"

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 157: // "boolean"

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 173: // value

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 177: // map_value

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 215: // socket_type

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 218: // outbound_interface_value

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 234: // db_type

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 316: // hr_mode

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 462: // ncr_protocol_value

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 470: // replace_client_name_value

#line 232 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 173: // value
      case 177: // map_value
      case 215: // socket_type
      case 218: // outbound_interface_value
      case 234: // db_type
      case 316: // hr_mode
      case 462: // ncr_protocol_value
      case 470: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 157: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 156: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 155: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 154: // "constant string"
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
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 297 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 315 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 341 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 367 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 391 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 638 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1062 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1185 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2158 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2289 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2457 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2515 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2587 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2595 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2605 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2623 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2641 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2715 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1879 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1898 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3183 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3192 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3277 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3368 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3395 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3399 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -752;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     369,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,    38,    19,    40,    42,    57,    63,
      73,    79,   133,   154,   161,   173,   179,   181,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,    19,    43,    31,    33,    75,   160,
       8,   168,   147,    41,    58,    52,   308,   121,  -752,   214,
     257,   266,   264,   313,  -752,  -752,  -752,  -752,  -752,   315,
    -752,    68,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   317,
     324,  -752,  -752,  -752,  -752,  -752,  -752,   325,   326,   327,
     329,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,   332,  -752,  -752,  -752,    90,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   334,  -752,   105,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   335,   337,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,   169,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   186,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   304,   339,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
     342,  -752,  -752,   341,  -752,  -752,  -752,   347,  -752,  -752,
     349,   340,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   354,   355,  -752,  -752,  -752,
    -752,   356,   359,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   197,  -752,  -752,  -752,   363,
    -752,  -752,   366,  -752,   367,   368,  -752,  -752,   370,   371,
     373,  -752,  -752,  -752,  -752,  -752,   208,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   215,  -752,  -752,  -752,    19,    19,  -752,
     219,   378,   380,   381,   383,   387,  -752,    31,  -752,   388,
     241,   242,   391,   392,   397,   398,   401,   402,   255,   260,
     261,   276,   428,   429,   430,   431,   432,   433,   437,   439,
     440,   441,   291,   445,   446,    33,  -752,   447,   448,   449,
     297,    75,  -752,   451,   452,   453,   454,   455,   460,   461,
     311,   312,   464,   466,   467,   469,   160,  -752,   471,     8,
    -752,   472,   474,   475,   476,   479,   480,   481,   482,  -752,
     168,  -752,   483,   484,   336,   486,   488,   489,   344,  -752,
      41,   490,   345,   346,  -752,    58,   493,   494,   229,  -752,
     348,   495,   500,   351,   519,   374,   375,   520,   521,   376,
     377,   379,   522,   527,   308,  -752,   528,   121,  -752,  -752,
    -752,   531,   530,   532,    19,    19,    19,  -752,   533,  -752,
    -752,   384,   389,   393,   534,   535,   540,  -752,  -752,  -752,
    -752,   541,   543,   544,   545,   546,   400,   547,   550,   551,
     552,  -752,   553,   554,  -752,   557,    15,   309,  -752,  -752,
     403,   404,   409,   559,   411,   412,   413,  -752,  -752,    46,
     414,   564,   563,  -752,   417,  -752,   557,   418,   419,   420,
     421,   422,   423,   424,  -752,   425,   426,  -752,   427,   434,
     435,  -752,  -752,   436,  -752,  -752,  -752,   438,    19,  -752,
    -752,   442,   443,  -752,   444,  -752,  -752,    30,   458,  -752,
    -752,  -752,     6,   450,  -752,   578,  -752,    19,    33,   121,
    -752,  -752,  -752,    75,  -752,  -752,  -752,   240,   240,   577,
     579,   580,   584,   586,  -752,  -752,  -752,   176,   587,   588,
      56,    95,   308,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,   592,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   593,   492,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   594,  -752,   218,   238,
     239,  -752,  -752,  -752,  -752,   598,   599,   601,   602,   603,
    -752,  -752,   604,   605,   606,   607,   608,  -752,   245,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,   285,  -752,   609,
     548,  -752,  -752,   610,   611,  -752,  -752,   612,   614,  -752,
    -752,   613,   617,  -752,  -752,   615,   619,  -752,  -752,  -752,
    -752,  -752,  -752,   201,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,   221,  -752,  -752,   618,   620,  -752,   621,   622,   623,
     624,   625,   626,   286,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   289,  -752,  -752,  -752,
     292,   459,  -752,   627,   628,  -752,  -752,   629,   631,  -752,
    -752,   630,  -752,   237,  -752,  -752,  -752,  -752,   632,   633,
     635,   636,   477,   485,   491,   487,   496,   637,   639,   497,
     498,   499,   501,   502,   240,  -752,  -752,   240,  -752,   577,
     160,  -752,   579,    41,  -752,   580,    58,  -752,   584,   390,
    -752,   586,   176,  -752,    39,   587,  -752,    52,  -752,   588,
     503,   505,   506,   507,   508,   509,    56,  -752,   641,   643,
      95,  -752,  -752,  -752,   642,   646,     8,  -752,   592,   168,
    -752,   593,   651,  -752,    65,   594,  -752,   120,   511,   512,
     513,  -752,  -752,  -752,  -752,  -752,   514,   515,  -752,  -752,
    -752,  -752,  -752,  -752,   293,  -752,   299,  -752,   649,  -752,
     662,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,   300,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,   663,   647,  -752,  -752,  -752,  -752,   301,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,   518,   523,
    -752,  -752,   524,   303,  -752,   665,  -752,   525,  -752,   670,
    -752,  -752,  -752,  -752,  -752,   307,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   390,  -752,   671,  -752,    39,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,   672,   526,   676,
      65,  -752,  -752,   529,  -752,   677,  -752,   536,  -752,  -752,
     678,  -752,  -752,   263,  -752,     7,   678,  -752,  -752,   680,
     682,   683,   310,  -752,  -752,  -752,  -752,  -752,  -752,   684,
     538,   537,   555,     7,  -752,   539,  -752,  -752,  -752,  -752,
    -752
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   116,     9,   246,    11,   399,    13,
     423,    15,   324,    17,   332,    19,   369,    21,   211,    23,
     509,    25,   566,    27,    45,    39,     0,     0,     0,     0,
       0,   425,     0,   334,   371,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   564,   558,   560,   562,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   105,     0,
       0,   444,   446,   448,   129,   131,   133,     0,     0,     0,
       0,   238,   322,   361,   295,   411,   413,   189,   470,   203,
     222,     0,   494,   507,    98,     0,    70,    72,    73,    74,
      75,    91,    92,    78,    79,    80,    81,    82,    86,    87,
      76,    77,    84,    85,    96,    97,    93,    94,    95,    83,
      88,    89,    90,   118,   120,   124,     0,   115,     0,   107,
     109,   110,   111,   112,   113,   114,   276,   278,   280,   391,
     274,   282,   284,     0,     0,   288,   286,   415,   466,   273,
     250,   251,   252,   264,     0,   248,   255,   268,   269,   270,
     256,   257,   260,   262,   258,   259,   253,   254,   271,   272,
     261,   265,   266,   267,   263,   409,   408,   405,   404,     0,
     401,   403,   406,   407,   464,   452,   454,   458,   456,   462,
     460,   450,   443,   437,   441,   442,     0,   426,   427,   438,
     439,   440,   434,   429,   435,   431,   432,   433,   436,   430,
       0,   351,   174,     0,   355,   353,   358,     0,   347,   348,
       0,   335,   336,   338,   350,   339,   340,   341,   357,   342,
     343,   344,   345,   346,   385,     0,     0,   383,   384,   387,
     388,     0,   372,   373,   375,   376,   377,   378,   379,   380,
     381,   382,   218,   220,   215,     0,   213,   216,   217,     0,
     531,   533,     0,   536,     0,     0,   540,   544,     0,     0,
       0,   549,   556,   529,   527,   528,     0,   511,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   571,     0,   568,   570,    44,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    55,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   247,     0,     0,
     400,     0,     0,     0,     0,     0,     0,     0,     0,   424,
       0,   325,     0,     0,     0,     0,     0,     0,     0,   333,
       0,     0,     0,     0,   370,     0,     0,     0,     0,   212,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   510,     0,     0,   567,    48,
      41,     0,     0,     0,     0,     0,     0,    59,     0,   103,
     104,     0,     0,     0,     0,     0,     0,    99,   100,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   493,     0,     0,    71,     0,     0,     0,   128,   108,
       0,     0,     0,     0,     0,     0,     0,   293,   294,     0,
       0,     0,     0,   249,     0,   402,     0,     0,     0,     0,
       0,     0,     0,     0,   428,     0,     0,   349,     0,     0,
       0,   360,   337,     0,   389,   390,   374,     0,     0,   214,
     530,     0,     0,   535,     0,   538,   539,     0,     0,   546,
     547,   548,     0,     0,   512,     0,   569,     0,     0,     0,
     559,   561,   563,     0,   445,   447,   449,     0,     0,   135,
     240,   326,   363,   297,    38,   412,   414,     0,     0,   205,
       0,     0,     0,    49,   119,   122,   123,   121,   126,   127,
     125,   277,   279,   281,   393,   275,   283,   285,   290,   291,
     292,   289,   287,   417,     0,   410,   465,   453,   455,   459,
     457,   463,   461,   451,   352,   175,   356,   354,   359,   386,
     219,   221,   532,   534,   537,   542,   543,   541,   545,   551,
     552,   553,   554,   555,   550,   557,     0,    42,     0,     0,
       0,   161,   167,   169,   171,     0,     0,     0,     0,     0,
     183,   185,     0,     0,     0,     0,     0,   160,     0,   141,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     156,   157,   158,   153,   159,   154,   155,     0,   139,     0,
     136,   137,   244,     0,   241,   242,   330,     0,   327,   328,
     367,     0,   364,   365,   301,     0,   298,   299,   198,   199,
     200,   201,   202,     0,   191,   193,   194,   195,   196,   197,
     474,     0,   472,   209,     0,   206,   207,     0,     0,     0,
       0,     0,     0,     0,   224,   226,   227,   228,   229,   230,
     231,   503,   505,   502,   500,   501,     0,   496,   498,   499,
       0,    51,   397,     0,   394,   395,   421,     0,   418,   419,
     468,     0,   575,     0,   573,    67,   565,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   130,   132,     0,   134,     0,
       0,   239,     0,   334,   323,     0,   371,   362,     0,     0,
     296,     0,     0,   190,   476,     0,   471,     0,   204,     0,
       0,     0,     0,     0,     0,     0,     0,   223,     0,     0,
       0,   495,   508,    53,     0,    52,     0,   392,     0,   425,
     416,     0,     0,   467,     0,     0,   572,     0,     0,     0,
       0,   173,   176,   177,   178,   179,     0,     0,   187,   188,
     180,   181,   182,   142,     0,   138,     0,   243,     0,   329,
       0,   366,   321,   318,   308,   309,   311,   305,   306,   307,
     317,   316,     0,   303,   310,   319,   320,   312,   313,   314,
     315,   300,   192,   491,   489,   490,   482,   483,   487,   488,
     484,   485,   486,     0,   477,   478,   480,   481,   473,     0,
     208,   232,   233,   234,   235,   236,   237,   225,     0,     0,
     497,    50,     0,     0,   396,     0,   420,     0,   589,     0,
     587,   585,   579,   583,   584,     0,   577,   581,   582,   580,
     574,   163,   164,   165,   166,   162,   168,   170,   172,   184,
     186,   140,   245,   331,   368,     0,   302,     0,   475,     0,
     210,   504,   506,    54,   398,   422,   469,     0,     0,     0,
       0,   576,   304,     0,   479,     0,   586,     0,   578,   492,
       0,   588,   593,     0,   591,     0,     0,   590,   601,     0,
       0,     0,     0,   595,   597,   598,   599,   600,   592,     0,
       0,     0,     0,     0,   594,     0,   603,   604,   605,   596,
     602
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   -37,  -752,   224,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,   195,  -752,  -752,  -752,
     -66,  -752,  -752,  -752,   362,  -752,  -752,  -752,  -752,   158,
     352,   -38,   -26,   -23,  -752,  -752,   -21,  -752,  -752,   159,
     330,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
     -52,  -752,  -535,   -49,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,   -22,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,   -56,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,   -60,  -752,  -752,  -752,   -59,   333,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   -65,  -752,  -752,  -752,  -752,
    -752,  -752,  -751,  -752,  -752,  -752,   -35,  -752,  -752,  -752,
      -6,   372,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -748,  -752,  -752,  -752,   -20,  -752,  -737,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   -16,  -752,  -752,  -190,   -61,
    -752,  -752,  -752,  -752,  -752,    -5,  -752,  -752,  -752,    -4,
    -752,   357,  -752,   -68,  -752,  -752,  -752,  -752,  -752,   -62,
    -752,  -752,  -752,  -752,  -752,    -3,  -752,  -752,  -752,    -7,
    -752,  -752,  -752,     2,  -752,   360,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,   -29,  -752,  -752,
    -752,   -17,   385,  -752,  -752,   -54,  -752,   -34,  -752,  -752,
    -752,  -752,  -752,   -18,  -752,  -752,  -752,   -19,  -752,   386,
     -46,  -752,     3,  -752,     4,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -736,  -752,  -752,  -752,  -752,  -752,  -752,     9,
    -752,  -752,  -752,  -138,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,    -2,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
     223,   353,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,  -752,
    -752,  -752,  -752,  -752,  -752,   250,   358,  -752,  -752,  -752,
     -15,  -752,  -752,  -139,  -752,  -752,  -752,  -752,  -752,  -752,
    -154,  -752,  -752,  -169,  -752,  -752,  -752,  -752,  -752
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   555,
      82,    83,    39,    64,    79,    80,   564,   721,   794,   795,
     637,    41,    66,    91,    92,    93,   331,    43,    67,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   339,   158,
     159,    45,    68,   160,   367,   161,   368,   567,   162,   369,
     570,   163,   134,   345,   135,   346,   136,   347,   659,   660,
     661,   757,   638,   639,   640,   738,   905,   641,   739,   642,
     740,   643,   741,   644,   645,   403,   646,   647,   648,   649,
     650,   651,   652,   653,   747,   654,   748,   655,   656,   137,
     358,   683,   684,   685,   686,   687,   688,   689,   138,   360,
     694,   695,   696,   777,    59,    75,   285,   286,   287,   416,
     288,   417,   139,   361,   703,   704,   705,   706,   707,   708,
     709,   710,   140,   352,   663,   664,   665,   760,    47,    69,
     184,   185,   186,   377,   187,   373,   188,   374,   189,   375,
     190,   378,   191,   379,   192,   383,   193,   382,   581,   194,
     195,   141,   355,   675,   676,   677,   769,   842,   843,   142,
     353,    53,    72,   667,   668,   669,   763,    55,    73,   250,
     251,   252,   253,   254,   255,   256,   402,   257,   406,   258,
     405,   259,   260,   407,   261,   143,   354,   671,   672,   673,
     766,    57,    74,   271,   272,   273,   274,   275,   411,   276,
     277,   278,   279,   197,   376,   723,   724,   725,   796,    49,
      70,   209,   210,   211,   388,   144,   356,   145,   357,   200,
     384,   727,   728,   729,   799,    51,    71,   226,   227,   228,
     146,   342,   147,   343,   148,   344,   232,   398,   233,   392,
     234,   393,   235,   395,   236,   394,   237,   397,   238,   396,
     239,   391,   204,   385,   731,   802,   149,   359,   691,   692,
     774,   863,   864,   865,   866,   867,   917,   150,   151,   363,
     716,   717,   718,   788,   719,   789,   152,   364,    61,    76,
     306,   307,   308,   309,   421,   310,   422,   311,   312,   424,
     313,   314,   315,   427,   607,   316,   428,   317,   318,   319,
     320,   432,   614,   321,   433,    94,   333,    95,   334,    96,
     335,    97,   332,    63,    77,   323,   324,   325,   436,   733,
     734,   804,   895,   896,   897,   898,   929,   899,   927,   943,
     944,   945,   952,   953,   954,   959,   955,   956,   957
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   124,   157,   179,   206,   222,   269,   248,   267,   284,
     303,   240,   270,   657,   164,   198,   212,   224,   838,   262,
     280,   839,   304,   201,    29,   229,    30,    78,    31,   565,
     566,   180,   841,   850,   165,   199,   213,   225,    28,   263,
     281,    84,   305,   181,    98,   605,   182,    40,   183,    42,
     207,   249,   268,    99,   100,   101,   102,   103,   104,   105,
     106,   101,   102,   103,    44,   113,   196,   208,   223,   241,
      46,   337,   202,   203,   230,   231,   338,   205,   115,   116,
      48,   107,   108,   109,   110,   111,    50,   153,   154,   112,
     113,   155,   176,   365,   156,   112,   113,   242,   366,   242,
     114,   243,   244,   115,   116,   245,   246,   247,   371,   115,
     116,   115,   116,   372,   117,   118,   242,   264,   243,   244,
     265,   266,   853,   242,   578,   579,   580,   119,   115,   116,
     120,   609,   610,   611,   612,   115,   116,   121,   122,   948,
      52,   123,   949,   950,   951,   115,   116,   282,   283,   901,
     902,   903,   904,   606,   697,   698,   699,   700,   701,   702,
      85,    54,    89,   613,   838,   115,   116,   839,    56,    86,
      87,    88,   386,    32,    33,    34,    35,   387,   841,   850,
      58,   100,   101,   102,   103,    89,    60,    89,    62,   389,
     101,   102,   103,    89,   390,    89,   888,    81,   889,   890,
     418,   711,   712,   112,   772,   419,    89,   773,   107,   108,
     109,   434,    89,   166,   167,   168,   435,   113,   437,    89,
     326,   365,   824,   438,   775,   113,   735,   776,   169,    89,
     115,   116,   170,   171,   172,   173,   174,   175,   115,   116,
     805,   437,   371,   806,   176,   177,   736,   737,   754,    89,
     214,   322,   178,   755,   215,   216,   217,   218,   219,   220,
     327,   221,   678,   679,   680,   681,   946,   682,   621,   947,
     328,    90,   329,   622,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   632,   633,   634,   635,   636,   754,   786,
     439,   440,   790,   756,   787,   434,   754,   791,   242,   124,
     792,   911,   386,   915,   418,   157,   389,   912,   916,   920,
     930,   924,   399,   963,    89,   931,   330,   164,   964,   336,
     179,   340,    89,   206,   282,   283,   568,   569,   341,   348,
     349,   350,   198,   351,   222,   212,   362,   165,   370,   380,
     201,   381,   400,   410,   248,   404,   224,   269,   180,   267,
     401,   408,   199,   270,   229,   213,   262,   409,   412,   413,
     181,   280,   415,   182,   414,   183,   225,   420,   303,   207,
     423,   425,   426,   441,   429,   430,   263,   431,   115,   116,
     304,   281,   442,   196,   443,   444,   208,   445,   249,   202,
     203,   446,   448,   268,    89,   451,   452,   223,   449,   450,
     305,   453,   454,   230,   231,   455,   456,   540,   541,   542,
     457,   100,   101,   102,   103,   458,   459,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   460,   461,   462,   463,   464,   465,   466,   107,   108,
     109,   467,   111,   468,   469,   470,   471,   113,   242,   472,
     473,   475,   476,   477,   478,   480,   481,   482,   483,   484,
     115,   116,    89,   171,   485,   486,   487,   175,   489,   488,
     490,   491,   124,   492,   176,   494,   496,   157,   497,   498,
     499,   601,   178,   500,   501,   502,   503,   505,   506,   164,
     508,   507,   509,   510,   513,   713,   303,   517,   518,   521,
     617,   511,   514,   515,   522,   520,   523,   714,   304,   165,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   524,   527,   528,   532,   715,   305,   525,
     526,   533,   535,   529,   530,   537,   531,   538,   544,   539,
     543,   547,   548,   545,    89,   549,   550,   546,   551,   552,
     553,   759,   557,    30,   556,   558,   559,   571,   572,   560,
     561,   562,   563,   573,   574,   575,   576,   577,   582,   583,
     584,   585,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   608,   616,   658,   730,   662,   666,   597,   598,
     599,   670,   600,   674,   690,   693,   602,   603,   604,   722,
     726,   732,   742,   743,   615,   744,   745,   746,   749,   750,
     751,   752,   753,   793,   762,   758,   761,   765,   764,   767,
     768,   770,   771,   779,   778,   780,   781,   782,   783,   784,
     785,   798,   811,   797,   801,   800,   807,   808,   803,   809,
     810,   816,   812,   817,   814,   878,   813,   879,   881,   882,
     919,   815,   818,   819,   820,   887,   821,   913,   871,   822,
     872,   873,   874,   875,   876,   906,   907,   908,   909,   910,
     914,   918,   921,   925,   928,   933,   935,   922,   923,   926,
     937,   936,   940,   939,   960,   942,   961,   962,   965,   554,
     941,   586,   967,   970,   179,   966,   618,   248,   269,   447,
     267,   479,   620,   832,   270,   823,   198,   825,   854,   262,
     968,   284,   280,   856,   201,   845,   852,   474,   869,   870,
     858,   877,   180,   847,   713,   932,   199,   827,   860,   263,
     206,   833,   281,   222,   181,   846,   714,   182,   891,   183,
     859,   249,   212,   834,   268,   224,   835,   837,   836,   840,
     893,   519,   855,   229,   826,   851,   715,   196,   493,   828,
     829,   831,   213,   202,   203,   225,   844,   512,   830,   884,
     894,   857,   848,   849,   495,   516,   207,   861,   862,   883,
     885,   934,   892,   886,   868,   720,   504,   534,   880,   619,
     900,   938,   958,   208,   969,   536,   223,     0,     0,     0,
       0,     0,   230,   231,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   832,
       0,     0,     0,   854,     0,     0,     0,     0,   856,     0,
       0,   845,     0,     0,   891,   858,     0,     0,     0,   847,
       0,     0,     0,   860,     0,     0,   893,   833,     0,     0,
       0,   846,     0,     0,     0,   859,     0,     0,     0,   834,
       0,     0,   835,   837,   836,   840,   894,   855,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   892,     0,
       0,     0,   844,     0,     0,     0,   857,     0,   848,   849,
       0,     0,   861,   862
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    74,    73,    74,    75,
      76,    72,    74,   548,    68,    69,    70,    71,   769,    73,
      74,   769,    76,    69,     5,    71,     7,    64,     9,    14,
      15,    69,   769,   769,    68,    69,    70,    71,     0,    73,
      74,    10,    76,    69,    11,    15,    69,     7,    69,     7,
      70,    73,    74,    20,    21,    22,    23,    24,    25,    26,
      27,    22,    23,    24,     7,    57,    69,    70,    71,    28,
       7,     3,    69,    69,    71,    71,     8,    69,    70,    71,
       7,    48,    49,    50,    51,    52,     7,    12,    13,    56,
      57,    16,    84,     3,    19,    56,    57,    58,     8,    58,
      67,    60,    61,    70,    71,    64,    65,    66,     3,    70,
      71,    70,    71,     8,    81,    82,    58,    59,    60,    61,
      62,    63,    83,    58,    78,    79,    80,    94,    70,    71,
      97,   125,   126,   127,   128,    70,    71,   104,   105,   132,
       7,   108,   135,   136,   137,    70,    71,    95,    96,    29,
      30,    31,    32,   123,    98,    99,   100,   101,   102,   103,
     129,     7,   154,   157,   915,    70,    71,   915,     7,   138,
     139,   140,     3,   154,   155,   156,   157,     8,   915,   915,
       7,    21,    22,    23,    24,   154,     7,   154,     7,     3,
      22,    23,    24,   154,     8,   154,   131,   154,   133,   134,
       3,   106,   107,    56,     3,     8,   154,     6,    48,    49,
      50,     3,   154,    53,    54,    55,     8,    57,     3,   154,
       6,     3,   757,     8,     3,    57,     8,     6,    68,   154,
      70,    71,    72,    73,    74,    75,    76,    77,    70,    71,
       3,     3,     3,     6,    84,    85,     8,     8,     3,   154,
      82,   130,    92,     8,    86,    87,    88,    89,    90,    91,
       3,    93,    86,    87,    88,    89,     3,    91,    28,     6,
       4,   337,     8,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     3,     3,
     327,   328,     3,     8,     8,     3,     3,     8,    58,   365,
       8,     8,     3,     3,     3,   371,     3,     8,     8,     8,
       3,     8,     8,     3,   154,     8,     3,   371,     8,     4,
     386,     4,   154,   389,    95,    96,    17,    18,     4,     4,
       4,     4,   386,     4,   400,   389,     4,   371,     4,     4,
     386,     4,     3,     3,   410,     4,   400,   415,   386,   415,
       8,     4,   386,   415,   400,   389,   410,     8,     4,     4,
     386,   415,     3,   386,     8,   386,   400,     4,   434,   389,
       4,     4,     4,   154,     4,     4,   410,     4,    70,    71,
     434,   415,     4,   386,     4,     4,   389,     4,   410,   386,
     386,     4,     4,   415,   154,     4,     4,   400,   157,   157,
     434,     4,     4,   400,   400,     4,     4,   444,   445,   446,
     155,    21,    22,    23,    24,   155,   155,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   155,     4,     4,     4,     4,     4,     4,    48,    49,
      50,     4,    52,     4,     4,     4,   155,    57,    58,     4,
       4,     4,     4,     4,   157,     4,     4,     4,     4,     4,
      70,    71,   154,    73,     4,     4,   155,    77,     4,   157,
       4,     4,   538,     4,    84,     4,     4,   543,     4,     4,
       4,   518,    92,     4,     4,     4,     4,     4,     4,   543,
       4,   155,     4,     4,     4,   561,   562,     4,     4,     4,
     537,   157,   157,   157,     4,   157,   155,   561,   562,   543,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,     4,     4,     4,     4,   561,   562,   155,
     155,     4,     4,   157,   157,     4,   157,     7,   154,     7,
       7,     7,     7,   154,   154,     5,     5,   154,     5,     5,
       5,     3,     5,     7,   154,     5,     5,   154,   154,     7,
       7,     7,     5,   154,     5,   154,   154,   154,   154,     5,
       7,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   124,     5,     7,    93,     7,     7,   154,   154,
     154,     7,   154,     7,     7,     7,   154,   154,   154,     7,
       7,     7,     4,     4,   154,     4,     4,     4,     4,     4,
       4,     4,     4,   154,     3,     6,     6,     3,     6,     6,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,     3,   155,     6,     3,     6,     4,     4,     8,     4,
       4,     4,   157,     4,   157,     4,   155,     4,     6,     3,
       3,   155,   155,   155,   155,     4,   155,     8,   155,   157,
     155,   155,   155,   155,   155,   154,   154,   154,   154,   154,
       8,     8,   154,     8,     4,     4,     4,   154,   154,   154,
       4,   155,     5,   154,     4,     7,     4,     4,     4,   465,
     154,   496,   155,   154,   760,   157,   538,   763,   766,   337,
     766,   371,   543,   769,   766,   754,   760,   759,   774,   763,
     155,   777,   766,   774,   760,   769,   772,   365,   777,   779,
     774,   786,   760,   769,   790,   915,   760,   762,   774,   763,
     796,   769,   766,   799,   760,   769,   790,   760,   804,   760,
     774,   763,   796,   769,   766,   799,   769,   769,   769,   769,
     804,   418,   774,   799,   760,   771,   790,   760,   386,   763,
     765,   768,   796,   760,   760,   799,   769,   410,   766,   798,
     804,   774,   769,   769,   389,   415,   796,   774,   774,   796,
     799,   919,   804,   801,   775,   562,   400,   434,   790,   539,
     805,   930,   946,   796,   963,   437,   799,    -1,    -1,    -1,
      -1,    -1,   799,   799,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   915,
      -1,    -1,    -1,   919,    -1,    -1,    -1,    -1,   919,    -1,
      -1,   915,    -1,    -1,   930,   919,    -1,    -1,    -1,   915,
      -1,    -1,    -1,   919,    -1,    -1,   930,   915,    -1,    -1,
      -1,   915,    -1,    -1,    -1,   919,    -1,    -1,    -1,   915,
      -1,    -1,   915,   915,   915,   915,   930,   919,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   930,    -1,
      -1,    -1,   915,    -1,    -1,    -1,   919,    -1,   915,   915,
      -1,    -1,   919,   919
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     5,
       7,     9,   154,   155,   156,   157,   173,   174,   175,   180,
       7,   189,     7,   195,     7,   209,     7,   296,     7,   377,
       7,   393,     7,   329,     7,   335,     7,   359,     7,   272,
       7,   446,     7,   481,   181,   176,   190,   196,   210,   297,
     378,   394,   330,   336,   360,   273,   447,   482,   173,   182,
     183,   154,   178,   179,    10,   129,   138,   139,   140,   154,
     188,   191,   192,   193,   473,   475,   477,   479,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    48,    49,    50,
      51,    52,    56,    57,    67,    70,    71,    81,    82,    94,
      97,   104,   105,   108,   188,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   220,   222,   224,   257,   266,   280,
     290,   319,   327,   353,   383,   385,   398,   400,   402,   424,
     435,   436,   444,    12,    13,    16,    19,   188,   207,   208,
     211,   213,   216,   219,   383,   385,    53,    54,    55,    68,
      72,    73,    74,    75,    76,    77,    84,    85,    92,   188,
     199,   200,   201,   204,   298,   299,   300,   302,   304,   306,
     308,   310,   312,   314,   317,   318,   353,   371,   383,   385,
     387,   398,   400,   402,   420,    69,   188,   312,   353,   379,
     380,   381,   383,   385,    82,    86,    87,    88,    89,    90,
      91,    93,   188,   353,   383,   385,   395,   396,   397,   398,
     400,   402,   404,   406,   408,   410,   412,   414,   416,   418,
     327,    28,    58,    60,    61,    64,    65,    66,   188,   242,
     337,   338,   339,   340,   341,   342,   343,   345,   347,   349,
     350,   352,   383,   385,    59,    62,    63,   188,   242,   341,
     347,   361,   362,   363,   364,   365,   367,   368,   369,   370,
     383,   385,    95,    96,   188,   274,   275,   276,   278,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   188,   383,   385,   448,   449,   450,   451,
     453,   455,   456,   458,   459,   460,   463,   465,   466,   467,
     468,   471,   130,   483,   484,   485,     6,     3,     4,     8,
       3,   194,   480,   474,   476,   478,     4,     3,     8,   206,
       4,     4,   399,   401,   403,   221,   223,   225,     4,     4,
       4,     4,   291,   328,   354,   320,   384,   386,   258,   425,
     267,   281,     4,   437,   445,     3,     8,   212,   214,   217,
       4,     3,     8,   303,   305,   307,   372,   301,   309,   311,
       4,     4,   315,   313,   388,   421,     3,     8,   382,     3,
       8,   419,   407,   409,   413,   411,   417,   415,   405,     8,
       3,     8,   344,   243,     4,   348,   346,   351,     4,     8,
       3,   366,     4,     4,     8,     3,   277,   279,     3,     8,
       4,   452,   454,     4,   457,     4,     4,   461,   464,     4,
       4,     4,   469,   472,     3,     8,   486,     3,     8,   173,
     173,   154,     4,     4,     4,     4,     4,   192,     4,   157,
     157,     4,     4,     4,     4,     4,     4,   155,   155,   155,
     155,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   155,     4,     4,   198,     4,     4,     4,   157,   208,
       4,     4,     4,     4,     4,     4,     4,   155,   157,     4,
       4,     4,     4,   299,     4,   380,     4,     4,     4,     4,
       4,     4,     4,     4,   397,     4,     4,   155,     4,     4,
       4,   157,   339,     4,   157,   157,   363,     4,     4,   275,
     157,     4,     4,   155,     4,   155,   155,     4,     4,   157,
     157,   157,     4,     4,   449,     4,   484,     4,     7,     7,
     173,   173,   173,     7,   154,   154,   154,     7,     7,     5,
       5,     5,     5,     5,   175,   177,   154,     5,     5,     5,
       7,     7,     7,     5,   184,    14,    15,   215,    17,    18,
     218,   154,   154,   154,     5,   154,   154,   154,    78,    79,
      80,   316,   154,     5,     7,   154,   184,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   173,   154,   154,   154,    15,   123,   462,   124,   125,
     126,   127,   128,   157,   470,   154,     5,   173,   197,   483,
     207,    28,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,   188,   230,   231,
     232,   235,   237,   239,   241,   242,   244,   245,   246,   247,
     248,   249,   250,   251,   253,   255,   256,   230,     7,   226,
     227,   228,     7,   292,   293,   294,     7,   331,   332,   333,
       7,   355,   356,   357,     7,   321,   322,   323,    86,    87,
      88,    89,    91,   259,   260,   261,   262,   263,   264,   265,
       7,   426,   427,     7,   268,   269,   270,    98,    99,   100,
     101,   102,   103,   282,   283,   284,   285,   286,   287,   288,
     289,   106,   107,   188,   383,   385,   438,   439,   440,   442,
     448,   185,     7,   373,   374,   375,     7,   389,   390,   391,
      93,   422,     7,   487,   488,     8,     8,     8,   233,   236,
     238,   240,     4,     4,     4,     4,     4,   252,   254,     4,
       4,     4,     4,     4,     3,     8,     8,   229,     6,     3,
     295,     6,     3,   334,     6,     3,   358,     6,     3,   324,
       6,     3,     3,     6,   428,     3,     6,   271,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   441,   443,
       3,     8,     8,   154,   186,   187,   376,     6,     3,   392,
       6,     3,   423,     8,   489,     3,     6,     4,     4,     4,
       4,   155,   157,   155,   157,   155,     4,     4,   155,   155,
     155,   155,   157,   231,   230,   228,   298,   294,   337,   333,
     361,   357,   188,   199,   200,   201,   204,   242,   290,   308,
     312,   314,   325,   326,   353,   383,   385,   398,   400,   402,
     420,   323,   260,    83,   188,   242,   327,   353,   383,   385,
     398,   400,   402,   429,   430,   431,   432,   433,   427,   274,
     270,   155,   155,   155,   155,   155,   155,   283,     4,     4,
     439,     6,     3,   379,   375,   395,   391,     4,   131,   133,
     134,   188,   242,   383,   385,   490,   491,   492,   493,   495,
     488,    29,    30,    31,    32,   234,   154,   154,   154,   154,
     154,     8,     8,     8,     8,     3,     8,   434,     8,     3,
       8,   154,   154,   154,     8,     8,   154,   496,     4,   494,
       3,     8,   326,     4,   431,     4,   155,     4,   491,   154,
       5,   154,     7,   497,   498,   499,     3,     6,   132,   135,
     136,   137,   500,   501,   502,   504,   505,   506,   498,   503,
       4,     4,     4,     3,     8,     4,   157,   155,   155,   501,
     154
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   158,   160,   159,   161,   159,   162,   159,   163,   159,
     164,   159,   165,   159,   166,   159,   167,   159,   168,   159,
     169,   159,   170,   159,   171,   159,   172,   159,   173,   173,
     173,   173,   173,   173,   173,   174,   176,   175,   177,   178,
     178,   179,   179,   181,   180,   182,   182,   183,   183,   185,
     184,   186,   186,   187,   187,   188,   190,   189,   191,   191,
     192,   192,   192,   192,   192,   192,   194,   193,   196,   195,
     197,   197,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   199,
     200,   201,   202,   203,   204,   206,   205,   207,   207,   208,
     208,   208,   208,   208,   208,   208,   210,   209,   212,   211,
     214,   213,   215,   215,   217,   216,   218,   218,   219,   221,
     220,   223,   222,   225,   224,   226,   226,   227,   227,   229,
     228,   230,   230,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   233,   232,   234,   234,   234,   234,   236,   235,   238,
     237,   240,   239,   241,   243,   242,   244,   245,   246,   247,
     248,   249,   250,   252,   251,   254,   253,   255,   256,   258,
     257,   259,   259,   260,   260,   260,   260,   260,   261,   262,
     263,   264,   265,   267,   266,   268,   268,   269,   269,   271,
     270,   273,   272,   274,   274,   274,   275,   275,   277,   276,
     279,   278,   281,   280,   282,   282,   283,   283,   283,   283,
     283,   283,   284,   285,   286,   287,   288,   289,   291,   290,
     292,   292,   293,   293,   295,   294,   297,   296,   298,   298,
     299,   299,   299,   299,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   301,   300,   303,   302,   305,   304,
     307,   306,   309,   308,   311,   310,   313,   312,   315,   314,
     316,   316,   316,   317,   318,   320,   319,   321,   321,   322,
     322,   324,   323,   325,   325,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   328,   327,   330,   329,   331,   331,   332,   332,
     334,   333,   336,   335,   337,   337,   338,   338,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   340,   341,
     342,   344,   343,   346,   345,   348,   347,   349,   351,   350,
     352,   354,   353,   355,   355,   356,   356,   358,   357,   360,
     359,   361,   361,   362,   362,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   364,   366,   365,   367,   368,   369,
     370,   372,   371,   373,   373,   374,   374,   376,   375,   378,
     377,   379,   379,   380,   380,   380,   380,   380,   380,   382,
     381,   384,   383,   386,   385,   388,   387,   389,   389,   390,
     390,   392,   391,   394,   393,   395,   395,   396,   396,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   399,   398,   401,   400,   403,   402,
     405,   404,   407,   406,   409,   408,   411,   410,   413,   412,
     415,   414,   417,   416,   419,   418,   421,   420,   423,   422,
     425,   424,   426,   426,   428,   427,   429,   429,   430,   430,
     431,   431,   431,   431,   431,   431,   431,   431,   431,   431,
     432,   434,   433,   435,   437,   436,   438,   438,   439,   439,
     439,   439,   439,   441,   440,   443,   442,   445,   444,   447,
     446,   448,   448,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     450,   452,   451,   454,   453,   455,   457,   456,   458,   459,
     461,   460,   462,   462,   464,   463,   465,   466,   467,   469,
     468,   470,   470,   470,   470,   470,   472,   471,   474,   473,
     476,   475,   478,   477,   480,   479,   482,   481,   483,   483,
     484,   486,   485,   487,   487,   489,   488,   490,   490,   491,
     491,   491,   491,   491,   491,   491,   492,   494,   493,   496,
     495,   497,   497,   499,   498,   500,   500,   501,   501,   501,
     501,   503,   502,   504,   505,   506
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
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
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
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
  "$@51", "client_class", "$@52", "reservation_mode", "$@53", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@54",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@55", "shared_network_params", "shared_network_param",
  "option_def_list", "$@56", "sub_option_def_list", "$@57",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@58", "sub_option_def", "$@59",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@60",
  "option_def_record_types", "$@61", "space", "$@62", "option_def_space",
  "option_def_encapsulate", "$@63", "option_def_array", "option_data_list",
  "$@64", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@65", "sub_option_data", "$@66",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@67",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@68", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@69", "sub_pool4", "$@70",
  "pool_params", "pool_param", "pool_entry", "$@71", "user_context",
  "$@72", "comment", "$@73", "reservations", "$@74", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@75", "sub_reservation",
  "$@76", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@77", "server_hostname", "$@78",
  "boot_file_name", "$@79", "ip_address", "$@80", "duid", "$@81",
  "hw_address", "$@82", "client_id_value", "$@83", "circuit_id_value",
  "$@84", "flex_id_value", "$@85", "hostname", "$@86",
  "reservation_client_classes", "$@87", "relay", "$@88", "relay_map",
  "$@89", "client_classes", "$@90", "client_classes_list",
  "client_class_entry", "$@91", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@92", "dhcp4o6_port",
  "control_socket", "$@93", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@94",
  "control_socket_name", "$@95", "dhcp_ddns", "$@96", "sub_dhcp_ddns",
  "$@97", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@98", "server_ip", "$@99", "server_port",
  "sender_ip", "$@100", "sender_port", "max_queue_size", "ncr_protocol",
  "$@101", "ncr_protocol_value", "ncr_format", "$@102",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@103", "replace_client_name_value",
  "generated_prefix", "$@104", "dhcp6_json_object", "$@105",
  "dhcpddns_json_object", "$@106", "control_agent_json_object", "$@107",
  "logging_object", "$@108", "sub_logging", "$@109", "logging_params",
  "logging_param", "loggers", "$@110", "loggers_entries", "logger_entry",
  "$@111", "logger_params", "logger_param", "debuglevel", "severity",
  "$@112", "output_options_list", "$@113", "output_options_list_content",
  "output_entry", "$@114", "output_params_list", "output_params", "output",
  "$@115", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   241,   241,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   247,   248,   248,   249,   249,
     250,   250,   251,   251,   252,   252,   253,   253,   261,   262,
     263,   264,   265,   266,   267,   270,   275,   275,   286,   289,
     290,   293,   297,   304,   304,   311,   312,   315,   319,   326,
     326,   333,   334,   337,   341,   352,   362,   362,   378,   379,
     383,   384,   385,   386,   387,   388,   391,   391,   406,   406,
     415,   416,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   450,
     455,   460,   465,   470,   475,   481,   481,   492,   493,   496,
     497,   498,   499,   500,   501,   502,   505,   505,   514,   514,
     524,   524,   531,   532,   535,   535,   542,   544,   548,   554,
     554,   566,   566,   578,   578,   588,   589,   592,   593,   596,
     596,   606,   607,   610,   611,   612,   613,   614,   615,   616,
     617,   618,   619,   620,   621,   622,   623,   624,   625,   626,
     627,   630,   630,   637,   638,   639,   640,   643,   643,   651,
     651,   659,   659,   667,   672,   672,   680,   685,   690,   695,
     700,   705,   710,   715,   715,   723,   723,   731,   736,   741,
     741,   751,   752,   755,   756,   757,   758,   759,   762,   767,
     772,   777,   782,   787,   787,   797,   798,   801,   802,   805,
     805,   815,   815,   825,   826,   827,   830,   831,   834,   834,
     842,   842,   850,   850,   861,   862,   865,   866,   867,   868,
     869,   870,   873,   878,   883,   888,   893,   898,   906,   906,
     919,   920,   923,   924,   931,   931,   957,   957,   968,   969,
     973,   974,   975,   976,   977,   978,   979,   980,   981,   982,
     983,   984,   985,   986,   987,   988,   989,   990,   991,   992,
     993,   994,   995,   996,   999,   999,  1007,  1007,  1015,  1015,
    1023,  1023,  1031,  1031,  1039,  1039,  1047,  1047,  1055,  1055,
    1062,  1063,  1064,  1067,  1072,  1079,  1079,  1090,  1091,  1095,
    1096,  1099,  1099,  1107,  1108,  1111,  1112,  1113,  1114,  1115,
    1116,  1117,  1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,
    1126,  1127,  1134,  1134,  1147,  1147,  1156,  1157,  1160,  1161,
    1166,  1166,  1181,  1181,  1195,  1196,  1199,  1200,  1203,  1204,
    1205,  1206,  1207,  1208,  1209,  1210,  1211,  1212,  1215,  1217,
    1222,  1224,  1224,  1232,  1232,  1240,  1240,  1248,  1250,  1250,
    1258,  1267,  1267,  1279,  1280,  1285,  1286,  1291,  1291,  1303,
    1303,  1315,  1316,  1321,  1322,  1327,  1328,  1329,  1330,  1331,
    1332,  1333,  1334,  1335,  1338,  1340,  1340,  1348,  1350,  1352,
    1357,  1365,  1365,  1377,  1378,  1381,  1382,  1385,  1385,  1395,
    1395,  1405,  1406,  1409,  1410,  1411,  1412,  1413,  1414,  1417,
    1417,  1425,  1425,  1450,  1450,  1480,  1480,  1490,  1491,  1494,
    1495,  1498,  1498,  1507,  1507,  1516,  1517,  1520,  1521,  1525,
    1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,
    1536,  1537,  1538,  1539,  1542,  1542,  1550,  1550,  1558,  1558,
    1566,  1566,  1574,  1574,  1582,  1582,  1590,  1590,  1598,  1598,
    1606,  1606,  1614,  1614,  1622,  1622,  1635,  1635,  1645,  1645,
    1656,  1656,  1666,  1667,  1670,  1670,  1680,  1681,  1684,  1685,
    1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,
    1700,  1702,  1702,  1714,  1721,  1721,  1731,  1732,  1735,  1736,
    1737,  1738,  1739,  1742,  1742,  1750,  1750,  1760,  1760,  1772,
    1772,  1782,  1783,  1786,  1787,  1788,  1789,  1790,  1791,  1792,
    1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,
    1805,  1810,  1810,  1818,  1818,  1826,  1831,  1831,  1839,  1844,
    1849,  1849,  1857,  1858,  1861,  1861,  1869,  1874,  1879,  1884,
    1884,  1892,  1895,  1898,  1901,  1904,  1910,  1910,  1920,  1920,
    1927,  1927,  1934,  1934,  1946,  1946,  1956,  1956,  1967,  1968,
    1972,  1976,  1976,  1988,  1989,  1993,  1993,  2001,  2002,  2005,
    2006,  2007,  2008,  2009,  2010,  2011,  2014,  2019,  2019,  2027,
    2027,  2037,  2038,  2041,  2041,  2049,  2050,  2053,  2054,  2055,
    2056,  2059,  2059,  2067,  2072,  2077
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
#line 4612 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2082 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
