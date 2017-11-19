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
      case 172: // value
      case 176: // map_value
      case 220: // db_type
      case 296: // hr_mode
      case 367: // known_clients_value
      case 431: // duid_type
      case 464: // ncr_protocol_value
      case 472: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 156: // "boolean"
        value.move< bool > (that.value);
        break;

      case 155: // "floating point"
        value.move< double > (that.value);
        break;

      case 154: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 153: // "constant string"
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
      case 172: // value
      case 176: // map_value
      case 220: // db_type
      case 296: // hr_mode
      case 367: // known_clients_value
      case 431: // duid_type
      case 464: // ncr_protocol_value
      case 472: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 156: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 155: // "floating point"
        value.copy< double > (that.value);
        break;

      case 154: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 153: // "constant string"
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
            case 153: // "constant string"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 154: // "integer"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 155: // "floating point"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 156: // "boolean"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 172: // value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 176: // map_value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 220: // db_type

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 296: // hr_mode

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 367: // known_clients_value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 431: // duid_type

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 464: // ncr_protocol_value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 472: // replace_client_name_value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 172: // value
      case 176: // map_value
      case 220: // db_type
      case 296: // hr_mode
      case 367: // known_clients_value
      case 431: // duid_type
      case 464: // ncr_protocol_value
      case 472: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 156: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 155: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 154: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 153: // "constant string"
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
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 291 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 313 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 317 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 335 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 339 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 365 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 388 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1416 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1425 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1434 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1454 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1624 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 958 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1181 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1228 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2119 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1314 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.KNOWN_CLIENTS);
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("known-clients", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("only", ctx.loc2pos(yystack_[0].location))); }
#line 2245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location))); }
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1339 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2369 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2520 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2538 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2703 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2721 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2757 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2927 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1821 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3019 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3028 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1868 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 2022 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3332 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3336 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -710;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     218,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,    55,    29,    61,    73,    75,    79,
     100,   108,   121,   129,   145,   157,   159,   164,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,    29,    -3,    10,    26,   333,   156,
     154,   103,    12,   160,    71,   204,    40,   163,  -710,   193,
     198,   203,   207,   238,  -710,  -710,  -710,  -710,  -710,   230,
    -710,    39,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,   247,   281,   302,   308,   316,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,   318,  -710,  -710,
    -710,    48,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,   325,    97,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,   328,   344,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   134,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   136,  -710,
    -710,  -710,  -710,  -710,   367,  -710,   368,   369,  -710,  -710,
    -710,  -710,  -710,   143,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   245,
     284,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   258,
    -710,  -710,   370,  -710,  -710,  -710,   371,  -710,  -710,   291,
     373,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,   374,   375,  -710,  -710,  -710,  -710,   372,   378,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
     178,  -710,  -710,  -710,   379,  -710,  -710,   380,  -710,   381,
     382,  -710,  -710,   383,   384,   385,  -710,  -710,  -710,   188,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,    29,    29,  -710,   224,
     386,   387,   388,   389,   390,  -710,    10,  -710,   391,   392,
     393,   228,   244,   248,   251,   252,   395,   396,   397,   399,
     400,   403,   404,   405,   406,   407,   408,   259,   410,   411,
      26,  -710,   412,   264,   333,  -710,   413,   414,   415,   417,
     418,   419,   270,   269,   422,   423,   424,   425,   156,  -710,
     426,   430,   154,  -710,   431,   282,   433,   287,   288,   103,
    -710,   434,   435,   436,   439,   442,   443,   444,  -710,    12,
    -710,   445,   446,   299,   450,   451,   452,   301,  -710,    71,
     454,   303,   304,  -710,   204,   457,   458,   263,  -710,   310,
     460,   463,   314,   465,   319,   320,   466,   467,   321,   322,
     323,   468,   471,   163,  -710,  -710,  -710,   472,   473,   474,
      29,    29,    29,  -710,   475,   476,   477,  -710,  -710,  -710,
    -710,  -710,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,  -710,   491,   492,  -710,   495,  -710,  -710,
     496,   497,   498,   341,   342,   350,  -710,  -710,   -23,   353,
     502,   501,  -710,   356,   293,  -710,   357,  -710,   358,  -710,
    -710,  -710,   495,   495,   495,   359,   360,   361,   362,  -710,
     363,   364,  -710,   365,   366,   376,  -710,  -710,   377,  -710,
    -710,  -710,   394,    29,  -710,  -710,   398,   401,  -710,   402,
    -710,  -710,   231,   409,  -710,  -710,  -710,   111,   416,  -710,
      29,    26,   420,  -710,  -710,  -710,   333,    49,    49,   513,
     515,   516,   517,   -33,    29,   -13,   518,   519,   168,    23,
     250,   163,  -710,  -710,   520,   521,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,   524,   448,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,   197,  -710,   205,  -710,  -710,   206,
    -710,  -710,  -710,  -710,   530,   531,   532,   533,   534,  -710,
    -710,  -710,   219,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,   222,  -710,   535,   536,
    -710,  -710,   537,   539,  -710,  -710,   538,   542,  -710,  -710,
     540,   545,  -710,  -710,  -710,   137,  -710,  -710,  -710,   544,
    -710,  -710,  -710,   174,  -710,  -710,  -710,  -710,   249,  -710,
    -710,   546,   550,  -710,   552,   553,   554,   555,   556,   557,
     225,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
     558,   559,   560,  -710,  -710,   232,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,   246,  -710,  -710,  -710,   260,   421,
    -710,   561,   562,  -710,  -710,   564,   563,  -710,  -710,   565,
     569,  -710,  -710,   567,  -710,   572,   420,  -710,  -710,   573,
     574,   575,   576,   427,   428,   429,   432,   437,   578,   581,
      49,  -710,  -710,   156,  -710,   513,    71,  -710,   515,   204,
    -710,   516,    70,  -710,   517,   -33,  -710,  -710,   -13,  -710,
      45,   518,  -710,    40,  -710,   519,   438,   440,   441,   447,
     449,   453,   168,  -710,   582,   583,   455,   456,   459,    23,
    -710,   585,   586,   250,  -710,  -710,  -710,   587,   570,   154,
    -710,   520,   103,  -710,   521,    12,  -710,   524,   592,  -710,
     593,  -710,   317,   461,   462,   464,  -710,  -710,  -710,  -710,
    -710,   469,   470,  -710,   261,  -710,   589,  -710,   591,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,   262,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,   594,   597,  -710,  -710,  -710,  -710,   283,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   243,   478,
    -710,  -710,  -710,  -710,   479,   493,  -710,  -710,   499,   285,
    -710,   286,  -710,   596,  -710,   500,   598,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
      70,  -710,   602,  -710,    45,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   295,
    -710,  -710,   505,  -710,    42,   598,  -710,  -710,  -710,   604,
    -710,  -710,  -710,   292,  -710,  -710,  -710,  -710,  -710,   607,
     494,   608,    42,  -710,   611,  -710,   508,  -710,   612,  -710,
    -710,   324,  -710,   -82,   612,  -710,  -710,   614,   616,   617,
     294,  -710,  -710,  -710,  -710,  -710,  -710,   620,   506,   511,
     526,   -82,  -710,   528,  -710,  -710,  -710,  -710,  -710
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   102,     9,   215,    11,   349,    13,
     375,    15,   404,    17,   278,    19,   286,    21,   321,    23,
     180,    25,   488,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   406,     0,   288,   323,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   541,   535,   537,   539,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   100,   111,
     113,     0,     0,     0,     0,     0,   207,   276,   313,   252,
     153,   170,   161,   437,   172,   191,   454,     0,   476,   486,
      94,     0,    70,    72,    73,    74,    75,    76,    79,    80,
      81,    82,    84,    83,    88,    89,    77,    78,    86,    87,
      85,    90,    91,    92,    93,   108,     0,     0,   104,   106,
     107,   341,   367,   361,   237,   239,   241,     0,     0,   245,
     243,   396,   433,   236,   219,   220,   221,   222,     0,   217,
     226,   227,   228,   231,   233,   229,   230,   223,   224,   235,
     225,   232,   234,   359,   363,   358,   355,   354,     0,   351,
     353,   356,   357,   389,     0,   392,     0,     0,   388,   383,
     382,   386,   387,     0,   377,   379,   380,   384,   385,   381,
     431,   419,   421,   423,   425,   427,   429,   418,   417,     0,
     407,   408,   412,   413,   410,   414,   415,   416,   411,     0,
     303,   143,     0,   307,   305,   310,     0,   299,   300,     0,
     289,   290,   292,   302,   293,   294,   295,   309,   296,   297,
     298,   335,     0,     0,   333,   334,   337,   338,     0,   324,
     325,   327,   328,   329,   330,   331,   332,   187,   189,   184,
       0,   182,   185,   186,     0,   508,   510,     0,   513,     0,
       0,   517,   521,     0,     0,     0,   526,   533,   506,     0,
     490,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,    44,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    55,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   216,
       0,     0,     0,   350,     0,     0,     0,     0,     0,     0,
     376,     0,     0,     0,     0,     0,     0,     0,   405,     0,
     279,     0,     0,     0,     0,     0,     0,     0,   287,     0,
       0,     0,     0,   322,     0,     0,     0,     0,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   489,    48,    41,     0,     0,     0,
       0,     0,     0,    59,     0,     0,     0,    95,    96,    97,
      98,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   475,     0,     0,    71,     0,   110,   105,
       0,     0,     0,     0,     0,     0,   250,   251,     0,     0,
       0,     0,   218,     0,     0,   352,     0,   391,     0,   394,
     395,   378,     0,     0,     0,     0,     0,     0,     0,   409,
       0,     0,   301,     0,     0,     0,   312,   291,     0,   339,
     340,   326,     0,     0,   183,   507,     0,     0,   512,     0,
     515,   516,     0,     0,   523,   524,   525,     0,     0,   491,
       0,     0,     0,   536,   538,   540,     0,     0,     0,   209,
     280,   315,   254,     0,    45,     0,     0,   174,     0,     0,
       0,     0,    49,   109,   343,   369,    38,   362,   238,   240,
     242,   247,   248,   249,   246,   244,   398,     0,   360,   365,
     366,   364,   390,   393,   432,   420,   422,   424,   426,   428,
     430,   304,   144,   308,   306,   311,   336,   188,   190,   509,
     511,   514,   519,   520,   518,   522,   529,   528,   530,   531,
     532,   527,   534,    42,     0,   546,     0,   543,   545,     0,
     130,   136,   138,   140,     0,     0,     0,     0,     0,   149,
     151,   129,     0,   115,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,   213,     0,   210,
     211,   284,     0,   281,   282,   319,     0,   316,   317,   258,
       0,   255,   256,   159,   160,     0,   155,   157,   158,     0,
     168,   169,   165,     0,   163,   166,   167,   441,     0,   439,
     178,     0,   175,   176,     0,     0,     0,     0,     0,     0,
       0,   193,   195,   196,   197,   198,   199,   200,   465,   471,
       0,     0,     0,   464,   463,     0,   456,   458,   461,   459,
     460,   462,   482,   484,     0,   478,   480,   481,     0,    51,
     347,     0,   344,   345,   373,     0,   370,   371,   402,     0,
     399,   400,   435,     0,    67,     0,     0,   542,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   114,     0,   208,     0,   288,   277,     0,   323,
     314,     0,     0,   253,     0,     0,   154,   171,     0,   162,
     443,     0,   438,     0,   173,     0,     0,     0,     0,     0,
       0,     0,     0,   192,     0,     0,     0,     0,     0,     0,
     455,     0,     0,     0,   477,   487,    53,     0,    52,     0,
     342,     0,     0,   368,     0,   406,   397,     0,     0,   434,
       0,   544,     0,     0,     0,     0,   142,   145,   146,   147,
     148,     0,     0,   116,     0,   212,     0,   283,     0,   318,
     275,   272,   274,   266,   267,   262,   263,   264,   265,   271,
     270,   273,     0,   260,   268,   269,   257,   156,   164,   452,
     450,   451,   449,     0,   444,   445,   447,   448,   440,     0,
     177,   201,   202,   203,   204,   205,   206,   194,     0,     0,
     470,   473,   474,   457,     0,     0,   479,    50,     0,     0,
     346,     0,   372,     0,   401,     0,     0,   132,   133,   134,
     135,   131,   137,   139,   141,   150,   152,   214,   285,   320,
       0,   259,     0,   442,     0,   179,   467,   468,   469,   466,
     472,   483,   485,    54,   348,   374,   403,   436,   550,     0,
     548,   261,     0,   446,     0,     0,   547,   453,   562,     0,
     560,   558,   554,     0,   552,   556,   557,   555,   549,     0,
       0,     0,     0,   551,     0,   559,     0,   553,     0,   561,
     566,     0,   564,     0,     0,   563,   574,     0,     0,     0,
       0,   568,   570,   571,   572,   573,   565,     0,     0,     0,
       0,     0,   567,     0,   576,   577,   578,   569,   575
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,    11,  -710,    88,  -710,  -710,
    -710,  -710,  -710,  -710,    44,  -710,  -130,  -710,  -710,  -710,
     -66,  -710,  -710,  -710,   309,  -710,  -710,  -710,  -710,   115,
     289,   -68,   -48,   -47,   -44,  -710,  -710,  -710,  -710,  -710,
     112,   290,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   109,
     -90,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,   -73,  -710,  -517,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -102,  -512,  -710,  -710,  -710,  -710,
    -103,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -109,
    -710,  -710,  -710,  -106,   241,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -113,  -710,  -710,  -710,  -710,  -710,  -710,  -709,
    -710,  -710,  -710,   -85,  -710,  -710,  -710,   -81,   312,  -710,
    -710,  -708,  -710,  -703,  -710,   -43,  -710,  -702,  -710,  -710,
    -710,  -701,  -710,  -710,  -710,  -710,   -93,  -710,  -710,  -227,
     571,  -710,  -710,  -710,  -710,  -710,   -83,  -710,  -710,  -710,
     -77,  -710,   298,  -710,   -61,  -710,  -710,  -710,  -710,  -710,
     -56,  -710,  -710,  -710,  -710,  -710,   -54,  -710,  -710,  -710,
     -80,  -710,  -710,  -710,   -79,  -710,   277,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,   -99,  -710,
    -710,  -710,   -87,   329,  -710,  -710,   -38,  -710,   -64,  -710,
    -710,  -710,  -710,  -710,  -710,   -91,  -710,  -710,  -710,   -78,
     326,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,   -76,  -710,  -710,  -710,   -75,  -710,   311,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -697,  -710,  -710,  -710,  -710,  -710,  -710,
     -49,  -710,  -710,  -710,  -178,  -710,  -710,  -710,  -710,  -710,
    -710,   -62,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,   -65,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,   171,   297,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,    -7,  -710,  -710,
    -710,  -191,  -710,  -710,  -207,  -710,  -710,  -710,  -710,  -710,
    -710,  -217,  -710,  -710,  -230,  -710,  -710,  -710,  -710,  -710
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   537,
      82,    83,    39,    64,    79,    80,   533,   689,   767,   768,
     120,    41,    66,    91,    92,    93,   310,    43,    67,   121,
     122,   123,   124,   125,   126,   127,   128,   318,    45,    68,
     147,   148,   149,   342,   150,   129,   319,   130,   320,   602,
     603,   604,   709,   861,   605,   710,   606,   711,   607,   712,
     608,   238,   382,   610,   611,   612,   613,   614,   718,   615,
     719,   131,   330,   635,   636,   637,   638,   132,   332,   643,
     644,   645,   646,   133,   331,   134,   334,   651,   652,   653,
     743,    61,    76,   270,   271,   272,   395,   273,   396,   135,
     335,   660,   661,   662,   663,   664,   665,   666,   667,   136,
     326,   618,   619,   620,   723,    47,    69,   168,   169,   170,
     349,   171,   350,   172,   351,   173,   355,   174,   354,   544,
     175,   176,   137,   329,   630,   631,   632,   732,   812,   813,
     138,   327,    55,    73,   622,   623,   624,   726,    57,    74,
     239,   240,   241,   242,   243,   244,   245,   381,   246,   385,
     247,   384,   248,   249,   386,   250,   139,   328,   626,   627,
     628,   729,    59,    75,   258,   259,   260,   261,   262,   390,
     263,   264,   265,   266,   178,   346,   691,   692,   693,   769,
      49,    70,   188,   189,   190,   360,   179,   348,   192,   361,
     551,   180,   347,   695,   696,   697,   772,    51,    71,   203,
     204,   205,   364,   206,   207,   366,   208,   209,   181,   356,
     699,   700,   701,   775,    53,    72,   219,   220,   221,   222,
     372,   223,   373,   224,   374,   225,   375,   226,   376,   227,
     377,   228,   371,   182,   357,   703,   778,   140,   333,   648,
     649,   740,   823,   824,   825,   826,   827,   872,   141,   336,
     675,   676,   677,   754,   879,   678,   679,   755,   680,   681,
     142,   143,   338,   684,   685,   686,   761,   687,   762,   144,
     339,    63,    77,   289,   290,   291,   292,   400,   293,   401,
     294,   295,   403,   296,   297,   298,   406,   574,   299,   407,
     300,   301,   302,   303,   411,   581,   304,   412,    94,   312,
      95,   313,    96,   314,    97,   311,   586,   587,   588,   705,
     889,   890,   894,   903,   904,   905,   906,   911,   907,   909,
     921,   922,   923,   930,   931,   932,   937,   933,   934,   935
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   164,   255,   163,   185,   198,   217,   202,   237,   254,
     269,   288,   674,   642,   256,   177,   187,   200,   218,   257,
      84,   165,   166,   806,   807,   167,    36,   186,   199,   808,
     810,   811,   191,   201,    29,   815,    30,    98,    31,   668,
      99,   100,   316,   541,   542,   543,   633,   317,   595,   926,
     108,   340,   927,   928,   929,    28,   341,   101,   102,   103,
     104,   105,   106,   107,   108,   590,   633,   640,    40,   641,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
      42,   231,    44,   108,   231,   210,    46,   230,   231,   211,
     212,   213,   214,   215,   216,   109,   110,   111,   112,   113,
     344,   101,   102,   103,   104,   345,   106,    48,   108,   231,
     231,   114,   232,   233,   115,    50,   234,   235,   236,   819,
     634,   116,   669,   670,   671,   672,   267,   268,    52,   117,
     118,   155,   156,   119,   158,   159,    54,   358,    85,   362,
     735,   108,   359,   736,   363,   160,   369,    86,    87,    88,
      81,   370,    56,   162,   193,   194,   195,   196,   197,   153,
     184,   806,   807,    89,    58,    89,    60,   808,   810,   811,
     576,    62,   898,   815,   899,   900,    89,   738,   160,    89,
     739,   397,    32,    33,    34,    35,   398,   101,   102,   103,
     104,   413,   108,    89,   108,    89,   414,   107,    89,   305,
     340,   306,    89,   183,   151,   704,   152,   307,   706,   344,
     153,   184,   153,   707,   708,   308,   154,   155,   156,   157,
     158,   159,   720,    89,    89,   720,   642,   721,   752,   160,
     722,   160,   161,   753,   315,   759,   577,   578,   579,   162,
     760,   309,   674,   231,   251,   232,   233,   252,   253,   763,
      90,   321,   741,   378,   764,   742,    89,   654,   655,   656,
     657,   658,   659,   413,   358,   870,   380,   580,   765,   867,
     871,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   322,   397,   379,   362,   369,
     164,   875,   163,   884,   885,   912,   185,   941,   895,   388,
     913,   896,   942,   198,   177,   202,   323,    89,   187,    89,
     165,   166,   324,   217,   167,   200,    89,   415,   416,   186,
     325,   255,   337,   237,   191,   218,   199,   924,   254,   343,
     925,   201,   352,   256,   857,   858,   859,   860,   257,   876,
     877,   878,   554,   555,   556,   145,   146,   288,   353,   267,
     268,   549,   550,   572,   573,   682,   683,    89,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   365,   367,   368,   383,   387,   389,   417,   391,   392,
     393,   394,   427,   399,   402,   404,   405,   408,   409,   410,
     418,   419,   420,   421,   422,   424,   425,   426,   428,   432,
     433,   434,   429,   435,   436,   430,   431,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   447,   450,   451,   452,
     448,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     463,   513,   514,   515,   464,   466,   467,   468,   472,   473,
     474,   469,   470,   475,   609,   609,   476,   477,   478,   480,
     481,   601,   601,   482,   483,   484,   485,   486,   488,   489,
     490,   492,   493,   673,   496,   288,   495,   497,   498,   499,
     502,   503,   507,   500,   501,   508,   510,   504,   505,   506,
     511,   512,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   538,   539,   528,   529,   530,   531,
     532,   534,   535,   540,   568,    30,   545,   546,   547,   548,
     552,   553,   557,   558,   559,   560,   561,   562,   563,   564,
     617,   583,   621,   625,   629,   647,   650,   690,   694,   565,
     566,   698,   702,   575,   713,   714,   715,   716,   717,   725,
     536,   724,   728,   727,   730,   731,   733,   567,   734,   585,
     737,   569,   744,   745,   570,   571,   746,   747,   748,   749,
     750,   751,   756,   757,   758,   771,   774,   770,   639,   582,
     773,   776,   777,   848,   766,   779,   780,   782,   783,   784,
     785,   786,   791,   788,   787,   792,   838,   839,   789,   844,
     845,   790,   831,   847,   832,   833,   855,   868,   856,   869,
     874,   834,   873,   835,   886,   888,   892,   836,   910,   840,
     841,   914,   916,   842,   862,   863,   918,   864,   938,   920,
     939,   940,   865,   866,   943,   423,   584,   616,   589,   446,
     793,   880,   881,   817,   449,   818,   830,   829,   494,   837,
     795,   816,   794,   891,   229,   797,   882,   609,   915,   796,
     798,   799,   883,   887,   601,   164,   255,   163,   897,   805,
     237,   919,   944,   254,   801,   945,   800,   821,   256,   177,
     462,   491,   850,   257,   820,   165,   166,   269,   814,   167,
     946,   948,   849,   852,   802,   803,   822,   487,   804,   809,
     479,   465,   828,   673,   851,   471,   893,   843,   846,   781,
     853,   854,   688,   185,   908,   917,   198,   936,   202,   217,
     509,   947,     0,     0,     0,   187,     0,     0,   200,     0,
       0,   218,     0,     0,     0,     0,   186,     0,     0,   199,
       0,   191,     0,     0,   201,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   805,     0,     0,
       0,   821,   801,     0,   800,     0,     0,     0,   820,     0,
       0,     0,     0,     0,     0,     0,   814,     0,     0,     0,
     822,   902,   802,   803,     0,     0,   804,   809,   901,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   902,
       0,     0,     0,     0,     0,     0,   901
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,    69,    75,    69,    70,    71,    72,    71,    74,    75,
      76,    77,   529,   525,    75,    69,    70,    71,    72,    75,
      10,    69,    69,   732,   732,    69,    15,    70,    71,   732,
     732,   732,    70,    71,     5,   732,     7,    11,     9,    16,
      14,    15,     3,    66,    67,    68,    79,     8,    25,   131,
      38,     3,   134,   135,   136,     0,     8,    31,    32,    33,
      34,    35,    36,    37,    38,    16,    79,    80,     7,    82,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       7,    39,     7,    38,    39,    73,     7,    16,    39,    77,
      78,    79,    80,    81,    82,    69,    70,    71,    72,    73,
       3,    31,    32,    33,    34,     8,    36,     7,    38,    39,
      39,    85,    41,    42,    88,     7,    45,    46,    47,    74,
     153,    95,    99,   100,   101,   102,    86,    87,     7,   103,
     104,    61,    62,   107,    64,    65,     7,     3,   128,     3,
       3,    38,     8,     6,     8,    75,     3,   137,   138,   139,
     153,     8,     7,    83,    51,    52,    53,    54,    55,    56,
      57,   870,   870,   153,     7,   153,     7,   870,   870,   870,
      59,     7,   130,   870,   132,   133,   153,     3,    75,   153,
       6,     3,   153,   154,   155,   156,     8,    31,    32,    33,
      34,     3,    38,   153,    38,   153,     8,    37,   153,     6,
       3,     3,   153,    49,    48,     8,    50,     4,     3,     3,
      56,    57,    56,     8,     8,     8,    60,    61,    62,    63,
      64,    65,     3,   153,   153,     3,   738,     8,     3,    75,
       8,    75,    76,     8,     4,     3,   125,   126,   127,    83,
       8,     3,   759,    39,    40,    41,    42,    43,    44,     3,
     316,     4,     3,     8,     8,     6,   153,    89,    90,    91,
      92,    93,    94,     3,     3,     3,     8,   156,     8,     8,
       8,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     4,     3,     3,     3,     3,
     358,     8,   358,     8,     8,     3,   362,     3,     3,     8,
       8,     6,     8,   369,   358,   369,     4,   153,   362,   153,
     358,   358,     4,   379,   358,   369,   153,   306,   307,   362,
       4,   394,     4,   389,   362,   379,   369,     3,   394,     4,
       6,   369,     4,   394,    17,    18,    19,    20,   394,    96,
      97,    98,   472,   473,   474,    12,    13,   413,     4,    86,
      87,    58,    59,   122,   123,   105,   106,   153,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     4,     4,     4,     4,     4,     3,   153,     4,     4,
       8,     3,   154,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   154,     4,
       4,     4,   154,     4,     4,   154,   154,     4,     4,     4,
       4,     4,     4,   154,     4,     4,     4,     4,     4,     4,
     156,     4,     4,     4,   154,   156,     4,     4,     4,     4,
       4,   420,   421,   422,     4,     4,   154,     4,     4,     4,
       4,   154,   154,     4,   517,   518,     4,     4,     4,     4,
       4,   517,   518,   154,     4,     4,     4,   156,     4,   156,
     156,     4,     4,   529,     4,   531,   156,     4,   154,     4,
       4,     4,     4,   154,   154,     4,     4,   156,   156,   156,
       7,     7,     7,     7,     7,     5,     5,     5,     5,     5,
       5,     5,     5,     5,   153,   153,     7,     7,     7,     7,
       5,     5,     5,   153,   493,     7,   153,     5,     7,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
       7,   510,     7,     7,     7,     7,     7,     7,     7,   153,
     153,     7,    84,   124,     4,     4,     4,     4,     4,     3,
     452,     6,     3,     6,     6,     3,     6,   153,     3,   129,
       6,   153,     6,     3,   153,   153,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     3,     6,   524,   153,
       6,     6,     3,     3,   153,     8,     4,     4,     4,     4,
       4,   154,     4,   154,   156,     4,     4,     4,   156,     4,
       4,   154,   154,     6,   154,   154,     4,     8,     5,     8,
       3,   154,     8,   154,     8,     7,     4,   154,     4,   154,
     154,     4,     4,   154,   153,   153,     5,   153,     4,     7,
       4,     4,   153,   153,     4,   316,   511,   518,   516,   340,
     720,   153,   153,   735,   344,   738,   745,   743,   397,   752,
     725,   734,   723,   870,    73,   728,   153,   720,   154,   726,
     729,   731,   153,   153,   720,   723,   729,   723,   153,   732,
     726,   153,   156,   729,   732,   154,   732,   740,   729,   723,
     358,   394,   771,   729,   740,   723,   723,   743,   732,   723,
     154,   153,   769,   774,   732,   732,   740,   389,   732,   732,
     379,   362,   741,   759,   772,   369,   874,   759,   763,   706,
     775,   777,   531,   769,   895,   912,   772,   924,   772,   775,
     413,   941,    -1,    -1,    -1,   769,    -1,    -1,   772,    -1,
      -1,   775,    -1,    -1,    -1,    -1,   769,    -1,    -1,   772,
      -1,   769,    -1,    -1,   772,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   870,    -1,    -1,
      -1,   874,   870,    -1,   870,    -1,    -1,    -1,   874,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   870,    -1,    -1,    -1,
     874,   894,   870,   870,    -1,    -1,   870,   870,   894,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   912,
      -1,    -1,    -1,    -1,    -1,    -1,   912
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,     0,     5,
       7,     9,   153,   154,   155,   156,   172,   173,   174,   179,
       7,   188,     7,   194,     7,   205,     7,   282,     7,   357,
       7,   374,     7,   391,     7,   309,     7,   315,     7,   339,
       7,   258,     7,   448,   180,   175,   189,   195,   206,   283,
     358,   375,   392,   310,   316,   340,   259,   449,   172,   181,
     182,   153,   177,   178,    10,   128,   137,   138,   139,   153,
     187,   190,   191,   192,   475,   477,   479,   481,    11,    14,
      15,    31,    32,    33,    34,    35,    36,    37,    38,    69,
      70,    71,    72,    73,    85,    88,    95,   103,   104,   107,
     187,   196,   197,   198,   199,   200,   201,   202,   203,   212,
     214,   238,   244,   250,   252,   266,   276,   299,   307,   333,
     414,   425,   437,   438,   446,    12,    13,   207,   208,   209,
     211,    48,    50,    56,    60,    61,    62,    63,    64,    65,
      75,    76,    83,   187,   198,   199,   200,   201,   284,   285,
     286,   288,   290,   292,   294,   297,   298,   333,   351,   363,
     368,   385,   410,    49,    57,   187,   292,   333,   359,   360,
     361,   363,   365,    51,    52,    53,    54,    55,   187,   292,
     333,   363,   365,   376,   377,   378,   380,   381,   383,   384,
      73,    77,    78,    79,    80,    81,    82,   187,   333,   393,
     394,   395,   396,   398,   400,   402,   404,   406,   408,   307,
      16,    39,    41,    42,    45,    46,    47,   187,   228,   317,
     318,   319,   320,   321,   322,   323,   325,   327,   329,   330,
     332,    40,    43,    44,   187,   228,   321,   327,   341,   342,
     343,   344,   345,   347,   348,   349,   350,    86,    87,   187,
     260,   261,   262,   264,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   187,   450,
     451,   452,   453,   455,   457,   458,   460,   461,   462,   465,
     467,   468,   469,   470,   473,     6,     3,     4,     8,     3,
     193,   482,   476,   478,   480,     4,     3,     8,   204,   213,
     215,     4,     4,     4,     4,     4,   277,   308,   334,   300,
     239,   251,   245,   415,   253,   267,   426,     4,   439,   447,
       3,     8,   210,     4,     3,     8,   352,   369,   364,   287,
     289,   291,     4,     4,   295,   293,   386,   411,     3,     8,
     362,   366,     3,     8,   379,     4,   382,     4,     4,     3,
       8,   409,   397,   399,   401,   403,   405,   407,     8,     3,
       8,   324,   229,     4,   328,   326,   331,     4,     8,     3,
     346,     4,     4,     8,     3,   263,   265,     3,     8,     4,
     454,   456,     4,   459,     4,     4,   463,   466,     4,     4,
       4,   471,   474,     3,     8,   172,   172,   153,     4,     4,
       4,     4,     4,   191,     4,     4,     4,   154,   154,   154,
     154,   154,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   154,     4,     4,   197,     4,   156,   208,
       4,     4,     4,     4,     4,     4,   154,   156,     4,     4,
       4,     4,   285,     4,     4,   360,     4,   154,     4,   154,
     154,   377,     4,     4,     4,     4,     4,     4,     4,   395,
       4,     4,   154,     4,     4,     4,   156,   319,     4,   156,
     156,   343,     4,     4,   261,   156,     4,     4,   154,     4,
     154,   154,     4,     4,   156,   156,   156,     4,     4,   451,
       4,     7,     7,   172,   172,   172,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     7,     5,   183,     5,     5,   174,   176,   153,   153,
     153,    66,    67,    68,   296,   153,     5,     7,   153,    58,
      59,   367,   153,   153,   183,   183,   183,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   172,   153,
     153,   153,   122,   123,   464,   124,    59,   125,   126,   127,
     156,   472,   153,   172,   196,   129,   483,   484,   485,   207,
      16,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,   187,   216,   217,   218,   221,   223,   225,   227,   228,
     230,   231,   232,   233,   234,   236,   216,     7,   278,   279,
     280,     7,   311,   312,   313,     7,   335,   336,   337,     7,
     301,   302,   303,    79,   153,   240,   241,   242,   243,   181,
      80,    82,   242,   246,   247,   248,   249,     7,   416,   417,
       7,   254,   255,   256,    89,    90,    91,    92,    93,    94,
     268,   269,   270,   271,   272,   273,   274,   275,    16,    99,
     100,   101,   102,   187,   230,   427,   428,   429,   432,   433,
     435,   436,   105,   106,   440,   441,   442,   444,   450,   184,
       7,   353,   354,   355,     7,   370,   371,   372,     7,   387,
     388,   389,    84,   412,     8,   486,     3,     8,     8,   219,
     222,   224,   226,     4,     4,     4,     4,     4,   235,   237,
       3,     8,     8,   281,     6,     3,   314,     6,     3,   338,
       6,     3,   304,     6,     3,     3,     6,     6,     3,     6,
     418,     3,     6,   257,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   430,   434,     4,     4,     4,     3,
       8,   443,   445,     3,     8,     8,   153,   185,   186,   356,
       6,     3,   373,     6,     3,   390,     6,     3,   413,     8,
       4,   484,     4,     4,     4,     4,   154,   156,   154,   156,
     154,     4,     4,   217,   284,   280,   317,   313,   341,   337,
     187,   198,   199,   200,   201,   228,   276,   288,   290,   292,
     294,   298,   305,   306,   333,   410,   303,   241,   247,    74,
     187,   228,   333,   419,   420,   421,   422,   423,   417,   260,
     256,   154,   154,   154,   154,   154,   154,   269,     4,     4,
     154,   154,   154,   428,     4,     4,   441,     6,     3,   359,
     355,   376,   372,   393,   389,     4,     5,    17,    18,    19,
      20,   220,   153,   153,   153,   153,   153,     8,     8,     8,
       3,     8,   424,     8,     3,     8,    96,    97,    98,   431,
     153,   153,   153,   153,     8,     8,     8,   153,     7,   487,
     488,   306,     4,   421,   489,     3,     6,   153,   130,   132,
     133,   187,   228,   490,   491,   492,   493,   495,   488,   496,
       4,   494,     3,     8,     4,   154,     4,   491,     5,   153,
       7,   497,   498,   499,     3,     6,   131,   134,   135,   136,
     500,   501,   502,   504,   505,   506,   498,   503,     4,     4,
       4,     3,     8,     4,   156,   154,   154,   501,   153
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   157,   159,   158,   160,   158,   161,   158,   162,   158,
     163,   158,   164,   158,   165,   158,   166,   158,   167,   158,
     168,   158,   169,   158,   170,   158,   171,   158,   172,   172,
     172,   172,   172,   172,   172,   173,   175,   174,   176,   177,
     177,   178,   178,   180,   179,   181,   181,   182,   182,   184,
     183,   185,   185,   186,   186,   187,   189,   188,   190,   190,
     191,   191,   191,   191,   191,   191,   193,   192,   195,   194,
     196,   196,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   198,   199,   200,   201,   202,
     204,   203,   206,   205,   207,   207,   208,   208,   210,   209,
     211,   213,   212,   215,   214,   216,   216,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     219,   218,   220,   220,   220,   220,   222,   221,   224,   223,
     226,   225,   227,   229,   228,   230,   231,   232,   233,   235,
     234,   237,   236,   239,   238,   240,   240,   241,   241,   242,
     243,   245,   244,   246,   246,   247,   247,   247,   248,   249,
     251,   250,   253,   252,   254,   254,   255,   255,   257,   256,
     259,   258,   260,   260,   260,   261,   261,   263,   262,   265,
     264,   267,   266,   268,   268,   269,   269,   269,   269,   269,
     269,   270,   271,   272,   273,   274,   275,   277,   276,   278,
     278,   279,   279,   281,   280,   283,   282,   284,   284,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   287,   286,   289,
     288,   291,   290,   293,   292,   295,   294,   296,   296,   296,
     297,   298,   300,   299,   301,   301,   302,   302,   304,   303,
     305,   305,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   308,   307,   310,   309,
     311,   311,   312,   312,   314,   313,   316,   315,   317,   317,
     318,   318,   319,   319,   319,   319,   319,   319,   319,   319,
     320,   321,   322,   324,   323,   326,   325,   328,   327,   329,
     331,   330,   332,   334,   333,   335,   335,   336,   336,   338,
     337,   340,   339,   341,   341,   342,   342,   343,   343,   343,
     343,   343,   343,   343,   344,   346,   345,   347,   348,   349,
     350,   352,   351,   353,   353,   354,   354,   356,   355,   358,
     357,   359,   359,   360,   360,   360,   360,   360,   360,   362,
     361,   364,   363,   366,   365,   367,   367,   369,   368,   370,
     370,   371,   371,   373,   372,   375,   374,   376,   376,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   377,   379,
     378,   380,   382,   381,   383,   384,   386,   385,   387,   387,
     388,   388,   390,   389,   392,   391,   393,   393,   394,   394,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   397,
     396,   399,   398,   401,   400,   403,   402,   405,   404,   407,
     406,   409,   408,   411,   410,   413,   412,   415,   414,   416,
     416,   418,   417,   419,   419,   420,   420,   421,   421,   421,
     421,   422,   424,   423,   426,   425,   427,   427,   428,   428,
     428,   428,   428,   428,   428,   430,   429,   431,   431,   431,
     432,   434,   433,   435,   436,   437,   439,   438,   440,   440,
     441,   441,   443,   442,   445,   444,   447,   446,   449,   448,
     450,   450,   451,   451,   451,   451,   451,   451,   451,   451,
     451,   451,   451,   451,   451,   451,   451,   452,   454,   453,
     456,   455,   457,   459,   458,   460,   461,   463,   462,   464,
     464,   466,   465,   467,   468,   469,   471,   470,   472,   472,
     472,   472,   472,   474,   473,   476,   475,   478,   477,   480,
     479,   482,   481,   483,   483,   484,   486,   485,   487,   487,
     489,   488,   490,   490,   491,   491,   491,   491,   491,   492,
     494,   493,   496,   495,   497,   497,   499,   498,   500,   500,
     501,   501,   501,   501,   503,   502,   504,   505,   506
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
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
  "$@47", "reservation_mode", "$@48", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@49", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@50",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@51", "sub_option_def_list", "$@52", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@53",
  "sub_option_def", "$@54", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@55",
  "option_def_record_types", "$@56", "space", "$@57", "option_def_space",
  "option_def_encapsulate", "$@58", "option_def_array", "option_data_list",
  "$@59", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@60", "sub_option_data", "$@61",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@62",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@63", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@64", "sub_pool6", "$@65",
  "pool_params", "pool_param", "pool_entry", "$@66", "user_context",
  "$@67", "known_clients", "$@68", "known_clients_value", "pd_pools_list",
  "$@69", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@70", "sub_pd_pool", "$@71", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@72", "pd_prefix_len", "excluded_prefix",
  "$@73", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@74", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@75", "sub_reservation", "$@76", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@77", "prefixes", "$@78", "duid", "$@79", "hw_address", "$@80",
  "hostname", "$@81", "flex_id_value", "$@82",
  "reservation_client_classes", "$@83", "relay", "$@84", "relay_map",
  "$@85", "client_classes", "$@86", "client_classes_list",
  "client_class_entry", "$@87", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@88", "server_id", "$@89",
  "server_id_params", "server_id_param", "server_id_type", "$@90",
  "duid_type", "htype", "identifier", "$@91", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@92", "control_socket_params",
  "control_socket_param", "socket_type", "$@93", "socket_name", "$@94",
  "dhcp_ddns", "$@95", "sub_dhcp_ddns", "$@96", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@97",
  "server_ip", "$@98", "server_port", "sender_ip", "$@99", "sender_port",
  "max_queue_size", "ncr_protocol", "$@100", "ncr_protocol_value",
  "ncr_format", "$@101", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@102",
  "replace_client_name_value", "generated_prefix", "$@103",
  "dhcp4_json_object", "$@104", "dhcpddns_json_object", "$@105",
  "control_agent_json_object", "$@106", "logging_object", "$@107",
  "logging_params", "logging_param", "loggers", "$@108", "loggers_entries",
  "logger_entry", "$@109", "logger_params", "logger_param", "debuglevel",
  "severity", "$@110", "output_options_list", "$@111",
  "output_options_list_content", "output_entry", "$@112",
  "output_params_list", "output_params", "output", "$@113", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   239,   239,   239,   240,   240,   241,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   246,   246,   247,   247,
     248,   248,   249,   249,   250,   250,   251,   251,   259,   260,
     261,   262,   263,   264,   265,   268,   273,   273,   284,   287,
     288,   291,   295,   302,   302,   309,   310,   313,   317,   324,
     324,   331,   332,   335,   339,   350,   360,   360,   375,   376,
     380,   381,   382,   383,   384,   385,   388,   388,   403,   403,
     412,   413,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   443,   448,   453,   458,   463,
     468,   468,   479,   479,   488,   489,   492,   493,   496,   496,
     506,   512,   512,   524,   524,   536,   537,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     555,   555,   562,   563,   564,   565,   568,   568,   576,   576,
     584,   584,   592,   597,   597,   605,   610,   615,   620,   625,
     625,   633,   633,   642,   642,   652,   653,   656,   657,   660,
     665,   670,   670,   680,   681,   684,   685,   686,   689,   694,
     701,   701,   711,   711,   721,   722,   725,   726,   729,   729,
     739,   739,   749,   750,   751,   754,   755,   758,   758,   766,
     766,   774,   774,   785,   786,   789,   790,   791,   792,   793,
     794,   797,   802,   807,   812,   817,   822,   830,   830,   843,
     844,   847,   848,   855,   855,   881,   881,   892,   893,   897,
     898,   899,   900,   901,   902,   903,   904,   905,   906,   907,
     908,   909,   910,   911,   912,   913,   914,   917,   917,   925,
     925,   933,   933,   941,   941,   949,   949,   956,   957,   958,
     961,   966,   974,   974,   985,   986,   990,   991,   994,   994,
    1002,  1003,  1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,
    1014,  1015,  1016,  1017,  1018,  1019,  1026,  1026,  1039,  1039,
    1048,  1049,  1052,  1053,  1058,  1058,  1073,  1073,  1087,  1088,
    1091,  1092,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1105,  1107,  1112,  1114,  1114,  1122,  1122,  1130,  1130,  1138,
    1140,  1140,  1148,  1157,  1157,  1169,  1170,  1175,  1176,  1181,
    1181,  1193,  1193,  1205,  1206,  1211,  1212,  1217,  1218,  1219,
    1220,  1221,  1222,  1223,  1226,  1228,  1228,  1236,  1238,  1240,
    1245,  1253,  1253,  1265,  1266,  1269,  1270,  1273,  1273,  1283,
    1283,  1292,  1293,  1296,  1297,  1298,  1299,  1300,  1301,  1304,
    1304,  1312,  1312,  1319,  1319,  1327,  1328,  1334,  1334,  1346,
    1347,  1350,  1351,  1354,  1354,  1366,  1366,  1378,  1379,  1382,
    1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1391,  1394,
    1394,  1402,  1407,  1407,  1415,  1420,  1428,  1428,  1438,  1439,
    1442,  1443,  1446,  1446,  1455,  1455,  1464,  1465,  1468,  1469,
    1473,  1474,  1475,  1476,  1477,  1478,  1479,  1480,  1481,  1484,
    1484,  1494,  1494,  1504,  1504,  1512,  1512,  1520,  1520,  1528,
    1528,  1536,  1536,  1549,  1549,  1559,  1559,  1570,  1570,  1580,
    1581,  1584,  1584,  1594,  1595,  1598,  1599,  1602,  1603,  1604,
    1605,  1608,  1610,  1610,  1621,  1621,  1633,  1634,  1637,  1638,
    1639,  1640,  1641,  1642,  1643,  1646,  1646,  1653,  1654,  1655,
    1658,  1663,  1663,  1671,  1676,  1683,  1690,  1690,  1700,  1701,
    1704,  1705,  1708,  1708,  1716,  1716,  1726,  1726,  1738,  1738,
    1748,  1749,  1752,  1753,  1754,  1755,  1756,  1757,  1758,  1759,
    1760,  1761,  1762,  1763,  1764,  1765,  1766,  1769,  1774,  1774,
    1782,  1782,  1790,  1795,  1795,  1803,  1808,  1813,  1813,  1821,
    1822,  1825,  1825,  1833,  1838,  1843,  1848,  1848,  1856,  1859,
    1862,  1865,  1868,  1874,  1874,  1884,  1884,  1891,  1891,  1898,
    1898,  1911,  1911,  1924,  1925,  1929,  1933,  1933,  1945,  1946,
    1950,  1950,  1958,  1959,  1962,  1963,  1964,  1965,  1966,  1969,
    1974,  1974,  1982,  1982,  1992,  1993,  1996,  1996,  2004,  2005,
    2008,  2009,  2010,  2011,  2014,  2014,  2022,  2027,  2032
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
#line 4514 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2037 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
