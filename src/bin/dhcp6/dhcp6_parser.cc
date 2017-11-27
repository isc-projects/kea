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
#define yylex   parser6_lex

// First part of user declarations.

#line 39 "dhcp6_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp6_parser.h"

// User implementation prologue.

#line 53 "dhcp6_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:413

#include <dhcp6/parser_context.h>

#line 59 "dhcp6_parser.cc" // lalr1.cc:413


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp6_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 174: // value
      case 178: // map_value
      case 222: // db_type
      case 300: // hr_mode
      case 371: // known_clients_value
      case 436: // duid_type
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 158: // "boolean"
        value.move< bool > (that.value);
        break;

      case 157: // "floating point"
        value.move< double > (that.value);
        break;

      case 156: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 155: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 174: // value
      case 178: // map_value
      case 222: // db_type
      case 300: // hr_mode
      case 371: // known_clients_value
      case 436: // duid_type
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 158: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 157: // "floating point"
        value.copy< double > (that.value);
        break;

      case 156: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 155: // "constant string"
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
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
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
            case 155: // "constant string"

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 156: // "integer"

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 157: // "floating point"

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 158: // "boolean"

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 174: // value

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 178: // map_value

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 222: // db_type

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 300: // hr_mode

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 371: // known_clients_value

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 436: // duid_type

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 469: // ncr_protocol_value

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 477: // replace_client_name_value

#line 232 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp6_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp6Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  inline Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::parse ()
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
      case 174: // value
      case 178: // map_value
      case 222: // db_type
      case 300: // hr_mode
      case 371: // known_clients_value
      case 436: // duid_type
      case 469: // ncr_protocol_value
      case 477: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 158: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 157: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 156: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 155: // "constant string"
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
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 337 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1416 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1434 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 824 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1624 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("eval-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1827 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1040 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1176 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.KNOWN_CLIENTS);
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("known-clients", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("only", ctx.loc2pos(yystack_[0].location))); }
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location))); }
#line 2271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1418 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2599 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("eval-on-demand", b);
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2804 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2832 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1887 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1890 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3142 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3278 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 2004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 2009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2022 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3352 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3361 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3365 "dhcp6_parser.cc" // lalr1.cc:859
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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp6Parser::yypact_ninf_ = -720;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     234,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,    39,    31,    84,   118,   126,   131,
     149,   155,   191,   198,   200,   210,   227,   241,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,    31,   -43,     4,    30,    35,   168,
     206,   184,   130,    52,    68,    14,   -29,   252,  -720,   185,
     172,   190,   211,   222,  -720,  -720,  -720,  -720,  -720,   271,
    -720,    43,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,   292,   306,   310,   328,   331,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,   333,  -720,  -720,
    -720,   116,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,   336,   129,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,   337,   338,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,   169,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,   171,  -720,  -720,  -720,  -720,  -720,   340,  -720,   341,
     347,  -720,  -720,  -720,  -720,  -720,  -720,   187,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,   261,   275,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,   345,  -720,  -720,   350,  -720,  -720,  -720,
     351,  -720,  -720,   348,   354,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,   355,   356,  -720,  -720,
    -720,  -720,   381,   387,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,   189,  -720,  -720,  -720,   388,  -720,
    -720,   389,  -720,   390,   391,  -720,  -720,   392,   393,   394,
    -720,  -720,  -720,   212,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
      31,    31,  -720,   203,   395,   396,   397,   398,   399,  -720,
       4,  -720,   400,   401,   402,   235,   254,   255,   258,   259,
     404,   405,   408,   409,   412,   416,   417,   418,   419,   420,
     421,   270,   423,   424,    30,  -720,   425,   272,    35,  -720,
     427,   428,   429,   430,   431,   432,   281,   280,   435,   436,
     437,   438,   439,   168,  -720,   440,   441,   206,  -720,   442,
     291,   444,   293,   296,   184,  -720,   449,   450,   451,   452,
     455,   456,   457,  -720,   130,  -720,   458,   459,   308,   461,
     462,   463,   312,  -720,    68,   464,   314,   315,  -720,    14,
     470,   471,    59,  -720,   318,   473,   474,   323,   476,   325,
     326,   479,   480,   327,   329,   332,   482,   484,   252,  -720,
    -720,  -720,   485,   486,   487,    31,    31,    31,  -720,   488,
     489,   490,  -720,  -720,  -720,  -720,  -720,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,  -720,   504,
     505,  -720,   508,  -720,  -720,   509,   510,   511,   352,   361,
     362,  -720,  -720,   232,   508,   364,   515,   514,  -720,   367,
     253,  -720,   368,  -720,   369,  -720,  -720,  -720,   508,   508,
     508,   370,   371,   372,   373,  -720,   374,   375,  -720,   376,
     377,   378,  -720,  -720,   379,  -720,  -720,  -720,   380,    31,
    -720,  -720,   382,   383,  -720,   384,  -720,  -720,   192,   366,
    -720,  -720,  -720,    13,   385,  -720,    31,    30,   410,  -720,
    -720,  -720,    35,    53,    53,   529,   535,   536,   537,   -39,
      31,   -11,   538,   539,     2,    27,   217,   252,  -720,  -720,
     540,   541,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,   542,   465,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,   218,  -720,   248,  -720,  -720,   249,  -720,  -720,  -720,
    -720,   546,   548,   549,   550,   551,  -720,  -720,  -720,   256,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,   257,  -720,   552,   553,  -720,  -720,   554,
     556,  -720,  -720,   555,   559,  -720,  -720,   557,   561,  -720,
    -720,  -720,    82,  -720,  -720,  -720,   560,  -720,  -720,  -720,
     105,  -720,  -720,  -720,  -720,   143,  -720,  -720,   562,   564,
    -720,   565,   566,   567,   568,   569,   570,   263,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,   571,   572,   573,
    -720,  -720,   264,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,   265,  -720,  -720,  -720,   273,   426,  -720,   574,   575,
    -720,  -720,   576,   580,  -720,  -720,   578,   582,  -720,  -720,
     579,  -720,   584,   410,  -720,  -720,   585,   586,   587,   588,
     443,   407,   445,   446,   447,   589,   590,    53,  -720,  -720,
     168,  -720,   529,    68,  -720,   535,    14,  -720,   536,   119,
    -720,   537,   -39,  -720,  -720,   -11,  -720,    11,   538,  -720,
     -29,  -720,   539,   453,   454,   460,   466,   467,   468,     2,
    -720,   591,   592,   469,   472,   475,    27,  -720,   593,   594,
     217,  -720,  -720,  -720,   596,   583,   206,  -720,   540,   184,
    -720,   541,   130,  -720,   542,   601,  -720,   595,  -720,   330,
     477,   478,   481,  -720,  -720,  -720,  -720,  -720,   483,   491,
    -720,   274,  -720,   598,  -720,   599,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
     276,  -720,  -720,  -720,  -720,  -720,  -720,  -720,   604,  -720,
    -720,  -720,   603,   609,  -720,  -720,  -720,  -720,  -720,   283,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,   207,   492,
    -720,  -720,  -720,  -720,   507,   513,  -720,  -720,   516,   284,
    -720,   285,  -720,   605,  -720,   517,   607,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
     119,  -720,   611,   519,  -720,    11,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
     157,  -720,  -720,   520,  -720,  -720,   115,   607,  -720,  -720,
    -720,   613,  -720,  -720,  -720,   286,  -720,  -720,  -720,  -720,
    -720,   614,   522,   615,   115,  -720,   616,  -720,   524,  -720,
     619,  -720,  -720,   170,  -720,   -15,   619,  -720,  -720,   623,
     625,   626,   287,  -720,  -720,  -720,  -720,  -720,  -720,   630,
     532,   531,   543,   -15,  -720,   547,  -720,  -720,  -720,  -720,
    -720
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   102,     9,   215,    11,   353,    13,
     380,    15,   410,    17,   282,    19,   290,    21,   325,    23,
     180,    25,   496,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   412,     0,   292,   327,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   549,   543,   545,   547,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   100,   111,
     113,     0,     0,     0,     0,     0,   207,   280,   317,   255,
     153,   170,   161,   443,   172,   191,   462,     0,   484,   494,
      94,     0,    70,    72,    73,    74,    75,    76,    79,    80,
      81,    82,    84,    83,    88,    89,    77,    78,    86,    87,
      85,    90,    91,    92,    93,   108,     0,     0,   104,   106,
     107,   345,   372,   366,   238,   240,   242,     0,     0,   248,
     246,   244,   402,   439,   237,   219,   220,   221,   222,     0,
     217,   226,   227,   228,   231,   232,   234,   229,   230,   223,
     224,   236,   225,   233,   235,   364,   368,   363,   359,   360,
     358,     0,   355,   357,   361,   362,   395,     0,   398,     0,
       0,   394,   388,   389,   387,   392,   393,     0,   382,   384,
     385,   390,   391,   386,   437,   425,   427,   429,   431,   433,
     435,   424,   423,     0,   413,   414,   418,   419,   416,   420,
     421,   422,   417,     0,   307,   143,     0,   311,   309,   314,
       0,   303,   304,     0,   293,   294,   296,   306,   297,   298,
     299,   313,   300,   301,   302,   339,     0,     0,   337,   338,
     341,   342,     0,   328,   329,   331,   332,   333,   334,   335,
     336,   187,   189,   184,     0,   182,   185,   186,     0,   516,
     518,     0,   521,     0,     0,   525,   529,     0,     0,     0,
     534,   541,   514,     0,   498,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,    44,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    55,
       0,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,     0,     0,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   216,     0,     0,     0,   354,     0,
       0,     0,     0,     0,     0,   381,     0,     0,     0,     0,
       0,     0,     0,   411,     0,   283,     0,     0,     0,     0,
       0,     0,     0,   291,     0,     0,     0,     0,   326,     0,
       0,     0,     0,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   497,
      48,    41,     0,     0,     0,     0,     0,     0,    59,     0,
       0,     0,    95,    96,    97,    98,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   483,     0,
       0,    71,     0,   110,   105,     0,     0,     0,     0,     0,
       0,   253,   254,     0,     0,     0,     0,     0,   218,     0,
       0,   356,     0,   397,     0,   400,   401,   383,     0,     0,
       0,     0,     0,     0,     0,   415,     0,     0,   305,     0,
       0,     0,   316,   295,     0,   343,   344,   330,     0,     0,
     183,   515,     0,     0,   520,     0,   523,   524,     0,     0,
     531,   532,   533,     0,     0,   499,     0,     0,     0,   544,
     546,   548,     0,     0,     0,   209,   284,   319,   257,     0,
      45,     0,     0,   174,     0,     0,     0,     0,    49,   109,
     347,   374,    38,   367,   239,   241,   243,   250,   251,   252,
     249,   247,   245,   404,     0,   365,   370,   371,   369,   396,
     399,   438,   426,   428,   430,   432,   434,   436,   308,   144,
     312,   310,   315,   340,   188,   190,   517,   519,   522,   527,
     528,   526,   530,   537,   536,   538,   539,   540,   535,   542,
      42,     0,   554,     0,   551,   553,     0,   130,   136,   138,
     140,     0,     0,     0,     0,     0,   149,   151,   129,     0,
     115,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,   213,     0,   210,   211,   288,     0,
     285,   286,   323,     0,   320,   321,   261,     0,   258,   259,
     159,   160,     0,   155,   157,   158,     0,   168,   169,   165,
       0,   163,   166,   167,   447,     0,   445,   178,     0,   175,
     176,     0,     0,     0,     0,     0,     0,     0,   193,   195,
     196,   197,   198,   199,   200,   473,   479,     0,     0,     0,
     472,   471,     0,   464,   466,   469,   467,   468,   470,   490,
     492,     0,   486,   488,   489,     0,    51,   351,     0,   348,
     349,   378,     0,   375,   376,   408,     0,   405,   406,   441,
       0,    67,     0,     0,   550,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   114,
       0,   208,     0,   292,   281,     0,   327,   318,     0,     0,
     256,     0,     0,   154,   171,     0,   162,   449,     0,   444,
       0,   173,     0,     0,     0,     0,     0,     0,     0,     0,
     192,     0,     0,     0,     0,     0,     0,   463,     0,     0,
       0,   485,   495,    53,     0,    52,     0,   346,     0,     0,
     373,     0,   412,   403,     0,     0,   440,     0,   552,     0,
       0,     0,     0,   142,   145,   146,   147,   148,     0,     0,
     116,     0,   212,     0,   287,     0,   322,   279,   276,   278,
     269,   270,   265,   266,   267,   268,   274,   275,   273,   277,
       0,   263,   271,   272,   260,   156,   164,   459,     0,   457,
     458,   456,     0,   450,   451,   453,   454,   455,   446,     0,
     177,   201,   202,   203,   204,   205,   206,   194,     0,     0,
     478,   481,   482,   465,     0,     0,   487,    50,     0,     0,
     350,     0,   377,     0,   407,     0,     0,   132,   133,   134,
     135,   131,   137,   139,   141,   150,   152,   214,   289,   324,
       0,   262,     0,     0,   448,     0,   179,   475,   476,   477,
     474,   480,   491,   493,    54,   352,   379,   409,   442,   558,
       0,   556,   264,     0,   461,   452,     0,     0,   555,   460,
     570,     0,   568,   566,   562,     0,   560,   564,   565,   563,
     557,     0,     0,     0,     0,   559,     0,   567,     0,   561,
       0,   569,   574,     0,   572,     0,     0,   571,   582,     0,
       0,     0,     0,   576,   578,   579,   580,   581,   573,     0,
       0,     0,     0,     0,   575,     0,   584,   585,   586,   577,
     583
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,    -8,  -720,   100,  -720,  -720,
    -720,  -720,  -720,  -720,    49,  -720,  -374,  -720,  -720,  -720,
     -66,  -720,  -720,  -720,   300,  -720,  -720,  -720,  -720,   120,
     295,   -48,   -44,   -42,   -41,  -720,  -720,  -720,  -720,  -720,
     113,   294,  -720,  -720,  -720,  -720,  -720,  -720,  -720,   117,
     -87,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,   -73,  -720,  -523,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,   -99,  -518,  -720,  -720,  -720,  -720,
    -101,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -107,
    -720,  -720,  -720,  -102,   247,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -109,  -720,  -720,  -720,  -720,  -720,  -720,  -719,
    -720,  -720,  -720,   -81,  -720,  -720,  -720,   -78,   290,  -720,
    -720,  -716,  -720,  -715,  -720,   -38,  -720,   -36,  -720,  -713,
    -720,  -720,  -720,  -710,  -720,  -720,  -720,  -720,   -86,  -720,
    -720,  -224,   621,  -720,  -720,  -720,  -720,  -720,   -77,  -720,
    -720,  -720,   -76,  -720,   266,  -720,   -56,  -720,  -720,  -720,
    -720,  -720,   -53,  -720,  -720,  -720,  -720,  -720,   -54,  -720,
    -720,  -720,   -79,  -720,  -720,  -720,   -71,  -720,   297,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
     -74,  -720,  -720,  -720,   -84,   302,  -720,  -720,   -40,  -720,
     -70,  -720,  -720,  -720,  -720,  -720,  -720,   -75,  -720,  -720,
    -720,   -72,   334,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,   -69,  -720,  -720,  -720,   -68,  -720,
     321,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -702,  -720,  -720,  -720,  -720,
    -720,  -720,   -37,  -720,  -720,  -720,  -173,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,   -49,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,   -52,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,   182,   303,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
    -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,  -720,
       7,  -720,  -720,  -720,  -184,  -720,  -720,  -200,  -720,  -720,
    -720,  -720,  -720,  -720,  -210,  -720,  -720,  -226,  -720,  -720,
    -720,  -720,  -720
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   543,
      82,    83,    39,    64,    79,    80,   539,   696,   774,   775,
     120,    41,    66,    91,    92,    93,   314,    43,    67,   121,
     122,   123,   124,   125,   126,   127,   128,   322,    45,    68,
     147,   148,   149,   346,   150,   129,   323,   130,   324,   609,
     610,   611,   716,   871,   612,   717,   613,   718,   614,   719,
     615,   242,   387,   617,   618,   619,   620,   621,   725,   622,
     726,   131,   334,   642,   643,   644,   645,   132,   336,   650,
     651,   652,   653,   133,   335,   134,   338,   658,   659,   660,
     750,    61,    76,   274,   275,   276,   400,   277,   401,   135,
     339,   667,   668,   669,   670,   671,   672,   673,   674,   136,
     330,   625,   626,   627,   730,    47,    69,   169,   170,   171,
     353,   172,   354,   173,   355,   174,   360,   175,   359,   176,
     358,   550,   177,   178,   137,   333,   637,   638,   639,   739,
     820,   821,   138,   331,    55,    73,   629,   630,   631,   733,
      57,    74,   243,   244,   245,   246,   247,   248,   249,   386,
     250,   390,   251,   389,   252,   253,   391,   254,   139,   332,
     633,   634,   635,   736,    59,    75,   262,   263,   264,   265,
     266,   395,   267,   268,   269,   270,   180,   350,   698,   699,
     700,   776,    49,    70,   191,   192,   193,   365,   181,   352,
     195,   366,   558,   182,   351,   702,   703,   704,   779,    51,
      71,   207,   208,   209,   369,   210,   211,   371,   212,   213,
     183,   361,   706,   707,   708,   782,    53,    72,   223,   224,
     225,   226,   377,   227,   378,   228,   379,   229,   380,   230,
     381,   231,   382,   232,   376,   184,   362,   710,   785,   140,
     337,   655,   656,   747,   832,   833,   834,   835,   836,   882,
     837,   141,   340,   682,   683,   684,   761,   890,   685,   686,
     762,   687,   688,   142,   143,   342,   691,   692,   693,   768,
     694,   769,   144,   343,    63,    77,   293,   294,   295,   296,
     405,   297,   406,   298,   299,   408,   300,   301,   302,   411,
     581,   303,   412,   304,   305,   306,   307,   416,   588,   308,
     417,    94,   316,    95,   317,    96,   318,    97,   315,   593,
     594,   595,   712,   900,   901,   906,   915,   916,   917,   918,
     923,   919,   921,   933,   934,   935,   942,   943,   944,   949,
     945,   946,   947
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   206,   259,   164,   187,   201,   221,    36,   241,   258,
     273,   292,   681,   649,    84,   179,   190,   204,   222,   260,
     813,   165,   261,   814,   815,   166,   818,   167,   168,   819,
     194,   205,   188,   202,   189,   203,    29,   823,    30,    28,
      31,    98,   640,   675,    99,   100,   320,   145,   146,   108,
     235,   321,   602,   235,   255,   236,   237,   256,   257,   271,
     272,   101,   102,   103,   104,   105,   106,   107,   108,   597,
     640,   647,   583,   648,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   234,   742,   827,   828,   743,   107,
     551,    40,   235,   661,   662,   663,   664,   665,   666,   109,
     110,   111,   112,   113,   561,   562,   563,   235,   745,   236,
     237,   746,    81,   238,   239,   240,   641,   114,   938,   344,
     115,   939,   940,   941,   345,    42,    89,   116,   676,   677,
     678,   679,   348,    44,    85,   117,   118,   349,    46,   119,
     584,   585,   586,    86,    87,    88,   748,   271,   272,   749,
     101,   102,   103,   104,   235,   106,    48,   108,   235,    89,
     907,   813,    50,   908,   814,   815,    89,   818,   108,    89,
     819,   587,   363,   936,   367,   310,   937,   364,   823,   368,
     155,   156,    89,   158,   159,    89,    32,    33,    34,    35,
     374,   309,   402,   160,   311,   375,   161,   403,    52,   101,
     102,   103,   104,   214,   163,    54,   108,    56,    89,   215,
     216,   217,   218,   219,   220,   418,   151,    58,   152,   312,
     419,   344,   108,    89,   153,   313,   711,   649,   154,   155,
     156,   157,   158,   159,    60,   196,   197,   198,   199,   200,
     153,   186,   160,   681,   108,   161,   162,   910,    62,   911,
     912,   713,   348,   163,    90,   185,   714,   715,   160,   727,
     727,   161,   153,   186,   728,   729,   759,   766,   770,   383,
      89,   760,   767,   771,    89,   319,   418,   363,   384,   880,
     160,   772,   877,   161,   881,    89,   402,   367,   374,   924,
     953,   886,   895,   896,   925,   954,   325,   164,   547,   548,
     549,   187,   420,   421,   206,   887,   888,   889,   201,   179,
     326,   556,   557,   190,   327,   165,   579,   580,   221,   166,
     204,   167,   168,    89,   689,   690,   259,   194,   241,   188,
     222,   189,   328,   258,   205,   329,   202,   341,   203,    89,
     347,   356,   357,   260,   370,   372,   261,   867,   868,   869,
     870,   373,   292,   385,   388,   392,   393,   394,   422,   396,
     397,    89,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   398,
     399,   432,   404,   407,   409,   410,   413,   414,   415,   423,
     424,   425,   426,   427,   429,   430,   431,    89,   437,   438,
     433,   434,   439,   440,   435,   436,   441,   519,   520,   521,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   452,
     453,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   469,   470,   472,   473,   474,   475,
     616,   616,   476,   478,   479,   480,   481,   608,   608,   482,
     483,   484,   486,   487,   488,   489,   490,   491,   494,   680,
     492,   292,   495,   496,   498,   499,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   513,   511,   514,   516,
     512,   575,   582,   517,   518,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   544,   590,   534,
     535,   536,   537,   538,   540,   541,   545,   546,    30,   552,
     553,   554,   555,   559,   560,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   624,   576,   577,   578,
     589,   592,   628,   632,   636,   654,   657,   697,   701,   705,
     720,   709,   721,   722,   723,   724,   732,   542,   731,   735,
     734,   737,   738,   740,   741,   794,   744,   752,   751,   753,
     754,   755,   756,   757,   758,   763,   764,   765,   778,   646,
     777,   773,   780,   781,   783,   784,   858,   786,   787,   789,
     790,   791,   792,   798,   799,   848,   849,   854,   855,   793,
     866,   795,   857,   797,   796,   865,   878,   879,   883,   841,
     842,   884,   885,   897,   899,   903,   843,   922,   926,   928,
     428,   930,   844,   845,   846,   850,   932,   950,   851,   951,
     952,   852,   872,   873,   955,   596,   874,   591,   875,   451,
     800,   623,   454,   825,   826,   840,   876,   891,   839,   500,
     847,   802,   801,   468,   616,   824,   902,   803,   804,   806,
     493,   608,   892,   259,   164,   805,   812,   241,   893,   471,
     258,   894,   898,   807,   830,   909,   179,   904,   927,   931,
     260,   829,   165,   261,   273,   822,   166,   957,   167,   168,
     956,   808,   859,   831,   233,   809,   497,   810,   811,   958,
     680,   816,   960,   817,   860,   485,   862,   861,   477,   206,
     187,   838,   905,   201,   863,   864,   221,   853,   856,   695,
     788,   515,   190,   920,   929,   204,   948,   959,   222,     0,
       0,     0,     0,     0,     0,     0,   194,     0,   188,   205,
     189,   202,     0,   203,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   812,     0,     0,
       0,     0,   830,     0,   807,     0,     0,     0,     0,   829,
       0,     0,     0,     0,     0,     0,   822,     0,     0,     0,
       0,   831,   808,   914,     0,     0,   809,     0,   810,   811,
     913,     0,   816,     0,   817,     0,     0,     0,     0,     0,
       0,   914,     0,     0,     0,     0,     0,     0,   913
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    71,    75,    69,    70,    71,    72,    15,    74,    75,
      76,    77,   535,   531,    10,    69,    70,    71,    72,    75,
     739,    69,    75,   739,   739,    69,   739,    69,    69,   739,
      70,    71,    70,    71,    70,    71,     5,   739,     7,     0,
       9,    11,    81,    16,    14,    15,     3,    12,    13,    38,
      39,     8,    25,    39,    40,    41,    42,    43,    44,    88,
      89,    31,    32,    33,    34,    35,    36,    37,    38,    16,
      81,    82,    59,    84,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    16,     3,    75,    76,     6,    37,
     464,     7,    39,    91,    92,    93,    94,    95,    96,    69,
      70,    71,    72,    73,   478,   479,   480,    39,     3,    41,
      42,     6,   155,    45,    46,    47,   155,    87,   133,     3,
      90,   136,   137,   138,     8,     7,   155,    97,   101,   102,
     103,   104,     3,     7,   130,   105,   106,     8,     7,   109,
     127,   128,   129,   139,   140,   141,     3,    88,    89,     6,
      31,    32,    33,    34,    39,    36,     7,    38,    39,   155,
       3,   880,     7,     6,   880,   880,   155,   880,    38,   155,
     880,   158,     3,     3,     3,     3,     6,     8,   880,     8,
      61,    62,   155,    64,    65,   155,   155,   156,   157,   158,
       3,     6,     3,    74,     4,     8,    77,     8,     7,    31,
      32,    33,    34,    73,    85,     7,    38,     7,   155,    79,
      80,    81,    82,    83,    84,     3,    48,     7,    50,     8,
       8,     3,    38,   155,    56,     3,     8,   745,    60,    61,
      62,    63,    64,    65,     7,    51,    52,    53,    54,    55,
      56,    57,    74,   766,    38,    77,    78,   132,     7,   134,
     135,     3,     3,    85,   320,    49,     8,     8,    74,     3,
       3,    77,    56,    57,     8,     8,     3,     3,     3,     8,
     155,     8,     8,     8,   155,     4,     3,     3,     3,     3,
      74,     8,     8,    77,     8,   155,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,     4,   363,    66,    67,
      68,   367,   310,   311,   374,    98,    99,   100,   374,   363,
       4,    58,    59,   367,     4,   363,   124,   125,   384,   363,
     374,   363,   363,   155,   107,   108,   399,   367,   394,   367,
     384,   367,     4,   399,   374,     4,   374,     4,   374,   155,
       4,     4,     4,   399,     4,     4,   399,    17,    18,    19,
      20,     4,   418,     8,     4,     4,     8,     3,   155,     4,
       4,   155,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,     8,
       3,   156,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   155,     4,     4,
     156,   156,     4,     4,   156,   156,     4,   425,   426,   427,
       4,     4,     4,     4,     4,     4,   156,     4,     4,     4,
     158,     4,     4,     4,     4,     4,     4,   156,   158,     4,
       4,     4,     4,     4,     4,     4,     4,   156,     4,   156,
     523,   524,   156,     4,     4,     4,     4,   523,   524,     4,
       4,     4,     4,     4,   156,     4,     4,     4,     4,   535,
     158,   537,   158,   158,     4,     4,   158,     4,     4,   156,
       4,   156,   156,     4,     4,   158,     4,   158,     4,     4,
     158,   499,   126,     7,     7,     7,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     5,     5,   155,   516,     7,
       7,     7,     7,     5,     5,     5,   155,   155,     7,   155,
       5,     7,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,     7,   155,   155,   155,
     155,   131,     7,     7,     7,     7,     7,     7,     7,     7,
       4,    86,     4,     4,     4,     4,     3,   457,     6,     3,
       6,     6,     3,     6,     3,   158,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   530,
       6,   155,     6,     3,     6,     3,     3,     8,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   156,
       5,   156,     6,   156,   158,     4,     8,     8,     4,   156,
     156,     8,     3,     8,     7,     4,   156,     4,     4,     4,
     320,     5,   156,   156,   156,   156,     7,     4,   156,     4,
       4,   156,   155,   155,     4,   522,   155,   517,   155,   344,
     727,   524,   348,   742,   745,   752,   155,   155,   750,   402,
     759,   732,   730,   363,   727,   741,   880,   733,   735,   738,
     394,   727,   155,   736,   730,   736,   739,   733,   155,   367,
     736,   155,   155,   739,   747,   155,   730,   158,   156,   155,
     736,   747,   730,   736,   750,   739,   730,   156,   730,   730,
     158,   739,   776,   747,    73,   739,   399,   739,   739,   156,
     766,   739,   155,   739,   778,   384,   781,   779,   374,   779,
     776,   748,   885,   779,   782,   784,   782,   766,   770,   537,
     713,   418,   776,   907,   924,   779,   936,   953,   782,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   776,    -1,   776,   779,
     776,   779,    -1,   779,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   880,    -1,    -1,
      -1,    -1,   885,    -1,   880,    -1,    -1,    -1,    -1,   885,
      -1,    -1,    -1,    -1,    -1,    -1,   880,    -1,    -1,    -1,
      -1,   885,   880,   906,    -1,    -1,   880,    -1,   880,   880,
     906,    -1,   880,    -1,   880,    -1,    -1,    -1,    -1,    -1,
      -1,   924,    -1,    -1,    -1,    -1,    -1,    -1,   924
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     5,
       7,     9,   155,   156,   157,   158,   174,   175,   176,   181,
       7,   190,     7,   196,     7,   207,     7,   284,     7,   361,
       7,   378,     7,   395,     7,   313,     7,   319,     7,   343,
       7,   260,     7,   453,   182,   177,   191,   197,   208,   285,
     362,   379,   396,   314,   320,   344,   261,   454,   174,   183,
     184,   155,   179,   180,    10,   130,   139,   140,   141,   155,
     189,   192,   193,   194,   480,   482,   484,   486,    11,    14,
      15,    31,    32,    33,    34,    35,    36,    37,    38,    69,
      70,    71,    72,    73,    87,    90,    97,   105,   106,   109,
     189,   198,   199,   200,   201,   202,   203,   204,   205,   214,
     216,   240,   246,   252,   254,   268,   278,   303,   311,   337,
     418,   430,   442,   443,   451,    12,    13,   209,   210,   211,
     213,    48,    50,    56,    60,    61,    62,    63,    64,    65,
      74,    77,    78,    85,   189,   200,   201,   202,   203,   286,
     287,   288,   290,   292,   294,   296,   298,   301,   302,   337,
     355,   367,   372,   389,   414,    49,    57,   189,   294,   296,
     337,   363,   364,   365,   367,   369,    51,    52,    53,    54,
      55,   189,   294,   296,   337,   367,   369,   380,   381,   382,
     384,   385,   387,   388,    73,    79,    80,    81,    82,    83,
      84,   189,   337,   397,   398,   399,   400,   402,   404,   406,
     408,   410,   412,   311,    16,    39,    41,    42,    45,    46,
      47,   189,   230,   321,   322,   323,   324,   325,   326,   327,
     329,   331,   333,   334,   336,    40,    43,    44,   189,   230,
     325,   331,   345,   346,   347,   348,   349,   351,   352,   353,
     354,    88,    89,   189,   262,   263,   264,   266,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   189,   455,   456,   457,   458,   460,   462,   463,
     465,   466,   467,   470,   472,   473,   474,   475,   478,     6,
       3,     4,     8,     3,   195,   487,   481,   483,   485,     4,
       3,     8,   206,   215,   217,     4,     4,     4,     4,     4,
     279,   312,   338,   304,   241,   253,   247,   419,   255,   269,
     431,     4,   444,   452,     3,     8,   212,     4,     3,     8,
     356,   373,   368,   289,   291,   293,     4,     4,   299,   297,
     295,   390,   415,     3,     8,   366,   370,     3,     8,   383,
       4,   386,     4,     4,     3,     8,   413,   401,   403,   405,
     407,   409,   411,     8,     3,     8,   328,   231,     4,   332,
     330,   335,     4,     8,     3,   350,     4,     4,     8,     3,
     265,   267,     3,     8,     4,   459,   461,     4,   464,     4,
       4,   468,   471,     4,     4,     4,   476,   479,     3,     8,
     174,   174,   155,     4,     4,     4,     4,     4,   193,     4,
       4,     4,   156,   156,   156,   156,   156,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   156,     4,
       4,   199,     4,   158,   210,     4,     4,     4,     4,     4,
       4,   156,   158,     4,     4,     4,     4,     4,   287,     4,
       4,   364,     4,   156,     4,   156,   156,   381,     4,     4,
       4,     4,     4,     4,     4,   399,     4,     4,   156,     4,
       4,     4,   158,   323,     4,   158,   158,   347,     4,     4,
     263,   158,     4,     4,   156,     4,   156,   156,     4,     4,
     158,   158,   158,     4,     4,   456,     4,     7,     7,   174,
     174,   174,     7,     7,     7,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     7,     7,     7,     7,     5,   185,
       5,     5,   176,   178,   155,   155,   155,    66,    67,    68,
     300,   185,   155,     5,     7,   155,    58,    59,   371,   155,
     155,   185,   185,   185,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   174,   155,   155,   155,   124,
     125,   469,   126,    59,   127,   128,   129,   158,   477,   155,
     174,   198,   131,   488,   489,   490,   209,    16,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,   189,   218,
     219,   220,   223,   225,   227,   229,   230,   232,   233,   234,
     235,   236,   238,   218,     7,   280,   281,   282,     7,   315,
     316,   317,     7,   339,   340,   341,     7,   305,   306,   307,
      81,   155,   242,   243,   244,   245,   183,    82,    84,   244,
     248,   249,   250,   251,     7,   420,   421,     7,   256,   257,
     258,    91,    92,    93,    94,    95,    96,   270,   271,   272,
     273,   274,   275,   276,   277,    16,   101,   102,   103,   104,
     189,   232,   432,   433,   434,   437,   438,   440,   441,   107,
     108,   445,   446,   447,   449,   455,   186,     7,   357,   358,
     359,     7,   374,   375,   376,     7,   391,   392,   393,    86,
     416,     8,   491,     3,     8,     8,   221,   224,   226,   228,
       4,     4,     4,     4,     4,   237,   239,     3,     8,     8,
     283,     6,     3,   318,     6,     3,   342,     6,     3,   308,
       6,     3,     3,     6,     6,     3,     6,   422,     3,     6,
     259,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   435,   439,     4,     4,     4,     3,     8,   448,   450,
       3,     8,     8,   155,   187,   188,   360,     6,     3,   377,
       6,     3,   394,     6,     3,   417,     8,     4,   489,     4,
       4,     4,     4,   156,   158,   156,   158,   156,     4,     4,
     219,   286,   282,   321,   317,   345,   341,   189,   200,   201,
     202,   203,   230,   278,   290,   292,   294,   296,   298,   302,
     309,   310,   337,   414,   307,   243,   249,    75,    76,   189,
     230,   337,   423,   424,   425,   426,   427,   429,   421,   262,
     258,   156,   156,   156,   156,   156,   156,   271,     4,     4,
     156,   156,   156,   433,     4,     4,   446,     6,     3,   363,
     359,   380,   376,   397,   393,     4,     5,    17,    18,    19,
      20,   222,   155,   155,   155,   155,   155,     8,     8,     8,
       3,     8,   428,     4,     8,     3,     8,    98,    99,   100,
     436,   155,   155,   155,   155,     8,     8,     8,   155,     7,
     492,   493,   310,     4,   158,   425,   494,     3,     6,   155,
     132,   134,   135,   189,   230,   495,   496,   497,   498,   500,
     493,   501,     4,   499,     3,     8,     4,   156,     4,   496,
       5,   155,     7,   502,   503,   504,     3,     6,   133,   136,
     137,   138,   505,   506,   507,   509,   510,   511,   503,   508,
       4,     4,     4,     3,     8,     4,   158,   156,   156,   506,
     155
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   159,   161,   160,   162,   160,   163,   160,   164,   160,
     165,   160,   166,   160,   167,   160,   168,   160,   169,   160,
     170,   160,   171,   160,   172,   160,   173,   160,   174,   174,
     174,   174,   174,   174,   174,   175,   177,   176,   178,   179,
     179,   180,   180,   182,   181,   183,   183,   184,   184,   186,
     185,   187,   187,   188,   188,   189,   191,   190,   192,   192,
     193,   193,   193,   193,   193,   193,   195,   194,   197,   196,
     198,   198,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   200,   201,   202,   203,   204,
     206,   205,   208,   207,   209,   209,   210,   210,   212,   211,
     213,   215,   214,   217,   216,   218,   218,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     221,   220,   222,   222,   222,   222,   224,   223,   226,   225,
     228,   227,   229,   231,   230,   232,   233,   234,   235,   237,
     236,   239,   238,   241,   240,   242,   242,   243,   243,   244,
     245,   247,   246,   248,   248,   249,   249,   249,   250,   251,
     253,   252,   255,   254,   256,   256,   257,   257,   259,   258,
     261,   260,   262,   262,   262,   263,   263,   265,   264,   267,
     266,   269,   268,   270,   270,   271,   271,   271,   271,   271,
     271,   272,   273,   274,   275,   276,   277,   279,   278,   280,
     280,   281,   281,   283,   282,   285,   284,   286,   286,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   289,   288,
     291,   290,   293,   292,   295,   294,   297,   296,   299,   298,
     300,   300,   300,   301,   302,   304,   303,   305,   305,   306,
     306,   308,   307,   309,   309,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     312,   311,   314,   313,   315,   315,   316,   316,   318,   317,
     320,   319,   321,   321,   322,   322,   323,   323,   323,   323,
     323,   323,   323,   323,   324,   325,   326,   328,   327,   330,
     329,   332,   331,   333,   335,   334,   336,   338,   337,   339,
     339,   340,   340,   342,   341,   344,   343,   345,   345,   346,
     346,   347,   347,   347,   347,   347,   347,   347,   348,   350,
     349,   351,   352,   353,   354,   356,   355,   357,   357,   358,
     358,   360,   359,   362,   361,   363,   363,   364,   364,   364,
     364,   364,   364,   364,   366,   365,   368,   367,   370,   369,
     371,   371,   373,   372,   374,   374,   375,   375,   377,   376,
     379,   378,   380,   380,   381,   381,   381,   381,   381,   381,
     381,   381,   381,   381,   381,   383,   382,   384,   386,   385,
     387,   388,   390,   389,   391,   391,   392,   392,   394,   393,
     396,   395,   397,   397,   398,   398,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   401,   400,   403,   402,   405,
     404,   407,   406,   409,   408,   411,   410,   413,   412,   415,
     414,   417,   416,   419,   418,   420,   420,   422,   421,   423,
     423,   424,   424,   425,   425,   425,   425,   425,   426,   428,
     427,   429,   431,   430,   432,   432,   433,   433,   433,   433,
     433,   433,   433,   435,   434,   436,   436,   436,   437,   439,
     438,   440,   441,   442,   444,   443,   445,   445,   446,   446,
     448,   447,   450,   449,   452,   451,   454,   453,   455,   455,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   457,   459,   458,   461,   460,
     462,   464,   463,   465,   466,   468,   467,   469,   469,   471,
     470,   472,   473,   474,   476,   475,   477,   477,   477,   477,
     477,   479,   478,   481,   480,   483,   482,   485,   484,   487,
     486,   488,   488,   489,   491,   490,   492,   492,   494,   493,
     495,   495,   496,   496,   496,   496,   496,   497,   499,   498,
     501,   500,   502,   502,   504,   503,   505,   505,   506,   506,
     506,   506,   508,   507,   509,   510,   511
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"known-clients\"", "\"only\"", "\"never\"",
  "\"subnet\"", "\"interface\"", "\"interface-id\"", "\"id\"",
  "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"eval-client-classes\"", "\"test\"",
  "\"eval-on-demand\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEFS", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "value", "sub_json", "map2", "$@14", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp6_object", "$@18", "sub_dhcp6",
  "$@19", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@20",
  "sub_interfaces6", "$@21", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@22", "re_detect",
  "lease_database", "$@23", "hosts_database", "$@24",
  "database_map_params", "database_map_param", "database_type", "$@25",
  "db_type", "user", "$@26", "password", "$@27", "host", "$@28", "port",
  "name", "$@29", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@30", "keyspace", "$@31", "mac_sources", "$@32",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@33",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@34",
  "hooks_libraries", "$@35", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@36",
  "sub_hooks_library", "$@37", "hooks_params", "hooks_param", "library",
  "$@38", "parameters", "$@39", "expired_leases_processing", "$@40",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@41",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@42",
  "sub_subnet6", "$@43", "subnet6_params", "subnet6_param", "subnet",
  "$@44", "interface", "$@45", "interface_id", "$@46", "client_class",
  "$@47", "eval_client_classes", "$@48", "reservation_mode", "$@49",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@50",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@51", "shared_network_params", "shared_network_param",
  "option_def_list", "$@52", "sub_option_def_list", "$@53",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@54", "sub_option_def", "$@55",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@56",
  "option_def_record_types", "$@57", "space", "$@58", "option_def_space",
  "option_def_encapsulate", "$@59", "option_def_array", "option_data_list",
  "$@60", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@61", "sub_option_data", "$@62",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@63",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@64", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@65", "sub_pool6", "$@66",
  "pool_params", "pool_param", "pool_entry", "$@67", "user_context",
  "$@68", "known_clients", "$@69", "known_clients_value", "pd_pools_list",
  "$@70", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@71", "sub_pd_pool", "$@72", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@73", "pd_prefix_len", "excluded_prefix",
  "$@74", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@75", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@76", "sub_reservation", "$@77", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@78", "prefixes", "$@79", "duid", "$@80", "hw_address", "$@81",
  "hostname", "$@82", "flex_id_value", "$@83",
  "reservation_client_classes", "$@84", "relay", "$@85", "relay_map",
  "$@86", "client_classes", "$@87", "client_classes_list",
  "client_class_entry", "$@88", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@89", "eval_on_demand",
  "server_id", "$@90", "server_id_params", "server_id_param",
  "server_id_type", "$@91", "duid_type", "htype", "identifier", "$@92",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@93",
  "control_socket_params", "control_socket_param", "socket_type", "$@94",
  "socket_name", "$@95", "dhcp_ddns", "$@96", "sub_dhcp_ddns", "$@97",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@98", "server_ip", "$@99", "server_port",
  "sender_ip", "$@100", "sender_port", "max_queue_size", "ncr_protocol",
  "$@101", "ncr_protocol_value", "ncr_format", "$@102",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@103", "replace_client_name_value",
  "generated_prefix", "$@104", "dhcp4_json_object", "$@105",
  "dhcpddns_json_object", "$@106", "control_agent_json_object", "$@107",
  "logging_object", "$@108", "logging_params", "logging_param", "loggers",
  "$@109", "loggers_entries", "logger_entry", "$@110", "logger_params",
  "logger_param", "debuglevel", "severity", "$@111", "output_options_list",
  "$@112", "output_options_list_content", "output_entry", "$@113",
  "output_params_list", "output_params", "output", "$@114", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   241,   241,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   247,   248,   248,   249,   249,
     250,   250,   251,   251,   252,   252,   253,   253,   261,   262,
     263,   264,   265,   266,   267,   270,   275,   275,   286,   289,
     290,   293,   297,   304,   304,   311,   312,   315,   319,   326,
     326,   333,   334,   337,   341,   352,   362,   362,   377,   378,
     382,   383,   384,   385,   386,   387,   390,   390,   405,   405,
     414,   415,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   445,   450,   455,   460,   465,
     470,   470,   481,   481,   490,   491,   494,   495,   498,   498,
     508,   514,   514,   526,   526,   538,   539,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     557,   557,   564,   565,   566,   567,   570,   570,   578,   578,
     586,   586,   594,   599,   599,   607,   612,   617,   622,   627,
     627,   635,   635,   644,   644,   654,   655,   658,   659,   662,
     667,   672,   672,   682,   683,   686,   687,   688,   691,   696,
     703,   703,   713,   713,   723,   724,   727,   728,   731,   731,
     741,   741,   751,   752,   753,   756,   757,   760,   760,   768,
     768,   776,   776,   787,   788,   791,   792,   793,   794,   795,
     796,   799,   804,   809,   814,   819,   824,   832,   832,   845,
     846,   849,   850,   857,   857,   883,   883,   894,   895,   899,
     900,   901,   902,   903,   904,   905,   906,   907,   908,   909,
     910,   911,   912,   913,   914,   915,   916,   917,   920,   920,
     928,   928,   936,   936,   944,   944,   952,   952,   962,   962,
     969,   970,   971,   974,   979,   987,   987,   998,   999,  1003,
    1004,  1007,  1007,  1015,  1016,  1019,  1020,  1021,  1022,  1023,
    1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,
    1040,  1040,  1053,  1053,  1062,  1063,  1066,  1067,  1072,  1072,
    1087,  1087,  1101,  1102,  1105,  1106,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,  1119,  1121,  1126,  1128,  1128,  1136,
    1136,  1144,  1144,  1152,  1154,  1154,  1162,  1171,  1171,  1183,
    1184,  1189,  1190,  1195,  1195,  1207,  1207,  1219,  1220,  1225,
    1226,  1231,  1232,  1233,  1234,  1235,  1236,  1237,  1240,  1242,
    1242,  1250,  1252,  1254,  1259,  1267,  1267,  1279,  1280,  1283,
    1284,  1287,  1287,  1297,  1297,  1306,  1307,  1310,  1311,  1312,
    1313,  1314,  1315,  1316,  1319,  1319,  1327,  1327,  1334,  1334,
    1342,  1343,  1349,  1349,  1361,  1362,  1365,  1366,  1369,  1369,
    1381,  1381,  1393,  1394,  1397,  1398,  1399,  1400,  1401,  1402,
    1403,  1404,  1405,  1406,  1407,  1410,  1410,  1418,  1423,  1423,
    1431,  1436,  1444,  1444,  1454,  1455,  1458,  1459,  1462,  1462,
    1471,  1471,  1480,  1481,  1484,  1485,  1489,  1490,  1491,  1492,
    1493,  1494,  1495,  1496,  1497,  1500,  1500,  1510,  1510,  1520,
    1520,  1528,  1528,  1536,  1536,  1544,  1544,  1552,  1552,  1565,
    1565,  1575,  1575,  1586,  1586,  1596,  1597,  1600,  1600,  1610,
    1611,  1614,  1615,  1618,  1619,  1620,  1621,  1622,  1625,  1627,
    1627,  1635,  1643,  1643,  1655,  1656,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1668,  1668,  1675,  1676,  1677,  1680,  1685,
    1685,  1693,  1698,  1705,  1712,  1712,  1722,  1723,  1726,  1727,
    1730,  1730,  1738,  1738,  1748,  1748,  1760,  1760,  1770,  1771,
    1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,
    1784,  1785,  1786,  1787,  1788,  1791,  1796,  1796,  1804,  1804,
    1812,  1817,  1817,  1825,  1830,  1835,  1835,  1843,  1844,  1847,
    1847,  1855,  1860,  1865,  1870,  1870,  1878,  1881,  1884,  1887,
    1890,  1896,  1896,  1906,  1906,  1913,  1913,  1920,  1920,  1933,
    1933,  1946,  1947,  1951,  1955,  1955,  1967,  1968,  1972,  1972,
    1980,  1981,  1984,  1985,  1986,  1987,  1988,  1991,  1996,  1996,
    2004,  2004,  2014,  2015,  2018,  2018,  2026,  2027,  2030,  2031,
    2032,  2033,  2036,  2036,  2044,  2049,  2054
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4557 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2059 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
