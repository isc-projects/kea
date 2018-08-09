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
      case 185: // value
      case 189: // map_value
      case 239: // db_type
      case 328: // hr_mode
      case 464: // duid_type
      case 497: // ncr_protocol_value
      case 505: // replace_client_name_value
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
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 185: // value
      case 189: // map_value
      case 239: // db_type
      case 328: // hr_mode
      case 464: // duid_type
      case 497: // ncr_protocol_value
      case 505: // replace_client_name_value
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
            case 165: // "constant string"

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 166: // "integer"

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 167: // "floating point"

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 168: // "boolean"

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 185: // value

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 189: // map_value

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 239: // db_type

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 328: // hr_mode

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 464: // duid_type

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 497: // ncr_protocol_value

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 505: // replace_client_name_value

#line 242 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 185: // value
      case 189: // map_value
      case 239: // db_type
      case 328: // hr_mode
      case 464: // duid_type
      case 497: // ncr_protocol_value
      case 505: // replace_client_name_value
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
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 304 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 308 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 326 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 330 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 339 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1623 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1040 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1168 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1470 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2426 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2573 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2677 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1834 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1926 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3119 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2003 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2009 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2010 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2047 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2050 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2056 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3341 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2166 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2214 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2228 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2236 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3570 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3574 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -794;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     308,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,    51,    47,    46,    64,    68,
      72,    86,   108,   152,   161,   211,   217,   233,   234,   249,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,    47,  -110,
      39,    58,    45,   229,    94,    26,   355,   104,    77,    14,
     -13,   357,   132,  -794,   274,   285,   302,   300,   307,  -794,
    -794,  -794,  -794,  -794,   329,  -794,   115,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   342,   345,   347,
     349,   350,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   352,  -794,  -794,
    -794,   133,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   353,  -794,   140,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   361,   362,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,   147,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   157,  -794,  -794,
    -794,  -794,  -794,   365,  -794,   370,   375,  -794,  -794,  -794,
    -794,  -794,  -794,   164,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   351,   334,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   373,  -794,  -794,   379,  -794,  -794,  -794,   381,  -794,
    -794,   380,   358,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   385,   388,  -794,  -794,
    -794,  -794,   390,   418,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   168,  -794,  -794,  -794,
     419,  -794,  -794,   420,  -794,   421,   422,  -794,  -794,   423,
     424,   427,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   172,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   178,  -794,
    -794,  -794,    47,    47,  -794,   272,   434,   435,   442,   444,
     445,  -794,    39,  -794,   447,   448,   449,   450,   256,   289,
     290,   291,   321,   484,   485,   486,   487,   489,   492,   497,
     498,   499,   500,   501,   502,   503,   504,   506,   346,   507,
     509,    58,  -794,   510,   356,    45,  -794,   511,   515,   519,
     521,   522,   368,   359,   527,   529,   531,   532,   229,  -794,
     533,    94,  -794,   534,   377,   535,   378,   382,    26,  -794,
     541,   542,   543,   545,   546,   547,   548,  -794,   355,  -794,
     549,   550,   389,   552,   553,   554,   391,  -794,    77,   556,
     393,   394,  -794,    14,   559,   560,    10,  -794,   397,   562,
     563,   402,   565,   404,   405,   568,   569,   407,   408,   409,
     574,   575,   576,   577,   357,  -794,   578,   132,  -794,  -794,
    -794,   579,   580,   581,    47,    47,    47,  -794,   582,   583,
     584,   587,  -794,  -794,  -794,  -794,  -794,   588,   589,   591,
     590,   433,   594,   595,   596,   597,   598,   599,   601,   602,
     603,   604,  -794,   605,   606,  -794,   609,  -794,  -794,   610,
     611,   438,   443,   452,  -794,  -794,   331,   609,   453,   612,
    -794,   455,  -794,   456,  -794,   457,  -794,  -794,  -794,   609,
     609,   609,   458,   459,   460,   461,  -794,   462,   463,  -794,
     464,   465,   466,  -794,  -794,   467,  -794,  -794,  -794,   468,
      47,  -794,  -794,   469,   470,  -794,   471,  -794,  -794,    76,
     454,  -794,  -794,  -794,   -22,   472,   473,   474,  -794,   635,
    -794,    47,    58,   132,  -794,  -794,  -794,    45,   203,   203,
     634,   636,   637,   638,  -794,  -794,  -794,   639,    -7,    47,
      29,   564,   640,   641,   642,   224,   136,   138,   357,  -794,
    -794,   643,   644,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,    18,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   645,  -794,   189,
     200,   213,  -794,  -794,  -794,  -794,   649,   650,   651,   652,
     653,  -794,   654,   655,  -794,   656,   657,   658,  -794,   214,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   246,  -794,
     659,   660,  -794,  -794,   661,   663,  -794,  -794,   662,   666,
    -794,  -794,   664,   668,  -794,  -794,   667,   669,  -794,  -794,
    -794,   179,  -794,  -794,  -794,   670,  -794,  -794,  -794,   257,
    -794,  -794,  -794,  -794,   247,  -794,  -794,  -794,   275,  -794,
    -794,   671,   672,  -794,  -794,   673,   675,  -794,   676,   677,
     678,   679,   680,   681,   250,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   682,   683,   684,  -794,  -794,  -794,
    -794,   267,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   268,  -794,  -794,  -794,   271,   524,  -794,
     685,   687,  -794,  -794,   686,   690,  -794,  -794,  -794,   688,
    -794,  -794,   284,  -794,  -794,  -794,  -794,   691,   693,   694,
     695,   508,   416,   528,   417,   536,   696,   537,   538,   697,
     539,   540,   441,   203,  -794,  -794,   203,  -794,   634,   229,
    -794,   636,    77,  -794,   637,    14,  -794,   638,   367,  -794,
     639,    -7,  -794,  -794,    29,  -794,   703,   564,  -794,    82,
     640,  -794,   355,  -794,   641,   -13,  -794,   642,   544,   551,
     555,   557,   558,   561,   224,  -794,   704,   705,   566,   567,
     570,   136,  -794,   707,   708,   138,  -794,  -794,  -794,   709,
     710,    94,  -794,   643,    26,  -794,   644,   712,  -794,   121,
     645,  -794,   395,   572,   573,   585,  -794,  -794,  -794,  -794,
    -794,   615,  -794,  -794,   617,  -794,  -794,  -794,  -794,   281,
    -794,   296,  -794,   706,  -794,   711,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     297,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   624,
    -794,  -794,   714,  -794,  -794,  -794,  -794,  -794,   717,   719,
    -794,  -794,  -794,  -794,  -794,   718,  -794,   299,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   212,   627,  -794,  -794,
    -794,  -794,   630,   631,  -794,  -794,   633,   311,  -794,   326,
    -794,   647,  -794,   716,  -794,  -794,  -794,  -794,  -794,   327,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   367,
    -794,  -794,   724,   496,  -794,    82,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   725,
     648,   726,   121,  -794,  -794,   665,  -794,  -794,   729,  -794,
     674,  -794,  -794,   728,  -794,  -794,   339,  -794,    48,   728,
    -794,  -794,   727,   736,   737,   333,  -794,  -794,  -794,  -794,
    -794,  -794,   740,   593,   689,   692,    48,  -794,   698,  -794,
    -794,  -794,  -794,  -794
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   109,     9,   250,    11,
     395,    13,   420,    15,   450,    17,   320,    19,   328,    21,
     365,    23,   215,    25,   547,    27,   610,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   452,     0,   330,   367,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     608,   602,   604,   606,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   107,   121,   123,   125,     0,     0,     0,
       0,     0,   242,   318,   357,   408,   410,   291,   188,   205,
     196,   181,   487,   442,   207,   226,   508,     0,   532,   545,
     101,     0,    72,    74,    75,    76,    77,    78,    81,    82,
      83,    84,    99,    85,    87,    86,    91,    92,    79,    80,
      89,    90,    97,    98,   100,    88,    93,    94,    95,    96,
     118,     0,   117,     0,   111,   113,   114,   115,   116,   387,
     412,   274,   276,   278,     0,     0,   284,   282,   280,   481,
     273,   254,   255,   256,   257,     0,   252,   261,   262,   263,
     266,   267,   269,   264,   265,   258,   259,   271,   272,   260,
     268,   270,   406,   405,   401,   402,   400,     0,   397,   399,
     403,   404,   435,     0,   438,     0,     0,   434,   428,   429,
     427,   432,   433,     0,   422,   424,   425,   430,   431,   426,
     479,   467,   469,   471,   473,   475,   477,   466,   463,   464,
     465,     0,   453,   454,   458,   459,   456,   460,   461,   462,
     457,     0,   347,   166,     0,   351,   349,   354,     0,   343,
     344,     0,   331,   332,   334,   346,   335,   336,   337,   353,
     338,   339,   340,   341,   342,   381,     0,     0,   379,   380,
     383,   384,     0,   368,   369,   371,   372,   373,   374,   375,
     376,   377,   378,   222,   224,   219,     0,   217,   220,   221,
       0,   571,   573,     0,   576,     0,     0,   580,   584,     0,
       0,     0,   589,   596,   598,   600,   569,   567,   568,     0,
     549,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   566,   615,     0,   612,
     614,    46,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    57,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   251,
       0,     0,   396,     0,     0,     0,     0,     0,     0,   421,
       0,     0,     0,     0,     0,     0,     0,   451,     0,   321,
       0,     0,     0,     0,     0,     0,     0,   329,     0,     0,
       0,     0,   366,     0,     0,     0,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   548,     0,     0,   611,    50,
      43,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,   102,   103,   104,   105,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   531,     0,     0,    73,     0,   120,   112,     0,
       0,     0,     0,     0,   289,   290,     0,     0,     0,     0,
     253,     0,   398,     0,   437,     0,   440,   441,   423,     0,
       0,     0,     0,     0,     0,     0,   455,     0,     0,   345,
       0,     0,     0,   356,   333,     0,   385,   386,   370,     0,
       0,   218,   570,     0,     0,   575,     0,   578,   579,     0,
       0,   586,   587,   588,     0,     0,     0,     0,   550,     0,
     613,     0,     0,     0,   603,   605,   607,     0,     0,     0,
     127,   244,   322,   359,    40,   409,   411,   293,     0,    47,
       0,     0,     0,   444,   209,     0,     0,     0,     0,    51,
     119,   389,   414,   275,   277,   279,   286,   287,   288,   285,
     283,   281,     0,   407,   436,   439,   480,   468,   470,   472,
     474,   476,   478,   348,   167,   352,   350,   355,   382,   223,
     225,   572,   574,   577,   582,   583,   581,   585,   591,   592,
     593,   594,   595,   590,   597,   599,   601,     0,    44,     0,
       0,     0,   153,   159,   161,   163,     0,     0,     0,     0,
       0,   176,     0,     0,   179,     0,     0,     0,   152,     0,
     133,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   147,   148,   149,   150,   145,   146,   151,     0,   131,
       0,   128,   129,   248,     0,   245,   246,   326,     0,   323,
     324,   363,     0,   360,   361,   297,     0,   294,   295,   194,
     195,     0,   190,   192,   193,     0,   203,   204,   200,     0,
     198,   201,   202,   186,     0,   183,   185,   491,     0,   489,
     448,     0,   445,   446,   213,     0,   210,   211,     0,     0,
       0,     0,     0,     0,     0,   228,   230,   231,   232,   233,
     234,   235,   521,   527,     0,     0,     0,   520,   517,   518,
     519,     0,   510,   512,   515,   513,   514,   516,   541,   543,
     540,   538,   539,     0,   534,   536,   537,     0,    53,   393,
       0,   390,   391,   418,     0,   415,   416,   485,   484,     0,
     483,   619,     0,   617,    69,   609,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   122,   124,     0,   126,     0,     0,
     243,     0,   330,   319,     0,   367,   358,     0,     0,   292,
       0,     0,   189,   206,     0,   197,     0,     0,   182,   493,
       0,   488,   452,   443,     0,     0,   208,     0,     0,     0,
       0,     0,     0,     0,     0,   227,     0,     0,     0,     0,
       0,     0,   509,     0,     0,     0,   533,   546,    55,     0,
      54,     0,   388,     0,     0,   413,     0,     0,   482,     0,
       0,   616,     0,     0,     0,     0,   165,   168,   169,   170,
     171,     0,   178,   172,     0,   173,   174,   175,   134,     0,
     130,     0,   247,     0,   325,     0,   362,   317,   312,   314,
     305,   306,   301,   302,   303,   304,   310,   311,   309,   313,
       0,   299,   307,   315,   316,   308,   296,   191,   199,     0,
     184,   505,     0,   503,   504,   500,   501,   502,     0,   494,
     495,   497,   498,   499,   490,     0,   447,     0,   212,   236,
     237,   238,   239,   240,   241,   229,     0,     0,   526,   529,
     530,   511,     0,     0,   535,    52,     0,     0,   392,     0,
     417,     0,   633,     0,   631,   629,   623,   627,   628,     0,
     621,   625,   626,   624,   618,   155,   156,   157,   158,   154,
     160,   162,   164,   177,   180,   132,   249,   327,   364,     0,
     298,   187,     0,     0,   492,     0,   449,   214,   523,   524,
     525,   522,   528,   542,   544,    56,   394,   419,   486,     0,
       0,     0,     0,   620,   300,     0,   507,   496,     0,   630,
       0,   622,   506,     0,   632,   637,     0,   635,     0,     0,
     634,   645,     0,     0,     0,     0,   639,   641,   642,   643,
     644,   636,     0,     0,     0,     0,     0,   638,     0,   647,
     648,   649,   640,   646
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,    34,  -794,   266,  -794,
    -794,  -794,  -794,  -794,  -794,   170,  -794,  -429,  -794,  -794,
    -794,   -70,  -794,  -794,  -794,   401,  -794,  -794,  -794,  -794,
     185,   387,   -66,   -54,   -51,   -34,  -794,  -794,  -794,  -794,
    -794,   235,   371,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,    -4,  -794,  -545,    -3,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   -42,  -794,
    -574,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   -20,  -794,  -794,  -794,
    -794,  -794,    -5,  -567,  -794,  -794,  -794,  -794,   -16,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   -24,  -794,  -794,
    -794,   -18,   383,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     -19,  -794,  -794,  -794,  -794,  -794,  -794,  -793,  -794,  -794,
    -794,     9,  -794,  -794,  -794,    13,   428,  -794,  -794,  -787,
    -794,  -784,  -794,   -30,  -794,   -28,  -794,  -780,  -794,  -794,
    -794,  -778,  -794,  -794,  -794,  -794,     8,  -794,  -794,  -160,
     755,  -794,  -794,  -794,  -794,  -794,    21,  -794,  -794,  -794,
      25,  -794,   410,  -794,   -38,  -794,  -794,  -794,  -794,  -794,
     -36,  -794,  -794,  -794,  -794,  -794,    -8,  -794,  -794,  -794,
      23,  -794,  -794,  -794,    27,  -794,   411,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   -17,  -794,
    -794,  -794,   -14,   440,  -794,  -794,   -58,  -794,   -46,  -794,
    -794,  -794,  -794,  -794,   -23,  -794,  -794,  -794,   -15,   437,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   -31,  -794,  -794,
    -794,    16,  -794,  -794,  -794,    19,  -794,   430,   252,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -770,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
      22,  -794,  -794,  -794,  -138,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,    11,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,     4,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   273,   406,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   301,   412,  -794,  -794,  -794,    -2,  -794,
    -794,  -147,  -794,  -794,  -794,  -794,  -794,  -794,  -163,  -794,
    -794,  -179,  -794,  -794,  -794,  -794,  -794
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     575,    87,    88,    41,    68,    84,    85,   590,   768,   859,
     860,   658,    43,    70,    96,    97,    98,   346,    45,    71,
     131,   132,   133,   134,   135,   136,   137,   138,   354,    47,
      72,   163,   164,   165,   383,   166,   139,   355,   140,   356,
     141,   357,   680,   681,   682,   806,   659,   660,   661,   787,
     979,   662,   788,   663,   789,   664,   790,   665,   666,   421,
     667,   668,   669,   670,   671,   672,   673,   674,   675,   796,
     676,   677,   799,   142,   372,   714,   715,   716,   826,   143,
     369,   701,   702,   703,   704,   144,   371,   709,   710,   711,
     712,   145,   370,   146,   375,   725,   726,   727,   835,    63,
      80,   296,   297,   298,   434,   299,   435,   147,   376,   734,
     735,   736,   737,   738,   739,   740,   741,   148,   363,   684,
     685,   686,   809,    49,    73,   185,   186,   187,   389,   188,
     390,   189,   391,   190,   396,   191,   395,   192,   394,   599,
     193,   194,   149,   368,   696,   697,   698,   818,   910,   911,
     150,   364,    57,    77,   688,   689,   690,   812,    59,    78,
     261,   262,   263,   264,   265,   266,   267,   420,   268,   424,
     269,   423,   270,   271,   425,   272,   151,   365,   692,   693,
     694,   815,    61,    79,   282,   283,   284,   285,   286,   429,
     287,   288,   289,   290,   196,   387,   770,   771,   772,   861,
      51,    74,   207,   208,   209,   400,   152,   366,   153,   367,
     199,   388,   774,   775,   776,   864,    53,    75,   223,   224,
     225,   403,   226,   227,   405,   228,   229,   154,   374,   721,
     722,   723,   832,    55,    76,   241,   242,   243,   244,   411,
     245,   412,   246,   413,   247,   414,   248,   415,   249,   416,
     250,   410,   201,   397,   779,   780,   867,   155,   373,   718,
     719,   829,   928,   929,   930,   931,   932,   992,   933,   156,
     377,   751,   752,   753,   846,  1001,   754,   755,   847,   756,
     757,   157,   158,   379,   763,   764,   765,   853,   766,   854,
     159,   380,    65,    81,   319,   320,   321,   322,   439,   323,
     440,   324,   325,   442,   326,   327,   328,   445,   626,   329,
     446,   330,   331,   332,   333,   450,   633,   334,   451,   335,
     452,   336,   453,    99,   348,   100,   349,   101,   350,   102,
     347,    67,    82,   338,   339,   340,   456,   782,   783,   869,
     969,   970,   971,   972,  1011,   973,  1009,  1026,  1027,  1028,
    1035,  1036,  1037,  1042,  1038,  1039,  1040
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   130,   162,   180,   203,   217,   237,   181,   259,   278,
     295,   316,   748,   708,   167,   197,   210,   221,   239,   182,
     273,   291,   183,   317,   678,   903,   168,   198,   211,   222,
     240,   904,   274,   292,   905,   318,   260,   279,   908,   184,
     909,   280,   200,   281,   204,   218,   205,   219,   915,    89,
      38,    30,    31,    42,    32,    86,    33,   160,   161,   253,
     275,   254,   255,   276,   277,   195,   206,   220,   238,   103,
     114,    44,   104,   105,   106,    46,   115,   116,   600,    48,
     699,   293,   294,   212,   213,   214,   215,   216,   115,   116,
     606,   607,   608,    50,   252,   107,   108,   109,   110,   111,
     112,   113,   114,   231,   293,   294,   177,   115,   116,   178,
     777,   628,   629,   630,   631,    52,   699,   706,   352,   707,
     115,   116,   253,   353,   254,   255,   114,   253,   256,   257,
     258,   117,   118,   119,   120,   121,   381,   122,   114,   115,
     116,   382,   123,   385,   115,   116,   632,   113,   386,   202,
     398,   124,    94,   742,   125,   399,   115,   116,   700,    54,
     401,   126,   647,   921,   922,   402,   253,   408,    56,   127,
     128,   436,   409,   129,   177,   454,   437,   178,    90,    94,
     455,   457,   821,   115,   116,   822,   458,    91,    92,    93,
    1031,    94,   381,  1032,  1033,  1034,   903,   784,   115,   116,
     115,   116,   904,   457,    94,   905,   624,   625,   785,   908,
      94,   909,    34,    35,    36,    37,   385,   803,    58,   915,
     642,   786,   804,    94,    60,   643,   644,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
      62,    64,    94,   743,   744,   745,   746,    94,   253,   803,
     827,   758,   759,   844,   805,   828,    66,   708,   845,    94,
     824,   889,   962,   825,   963,   964,   107,   108,   109,   110,
     851,   855,   337,   114,   454,   852,   856,   748,   830,   857,
     341,   831,    95,   169,   803,   170,    94,   870,   342,   985,
     871,   115,   116,   171,   172,   173,   174,   175,   176,   398,
     989,    94,   436,    94,   986,   990,   343,   997,   344,   177,
     345,   130,   178,   123,   401,   162,   998,   999,  1000,  1006,
     179,   728,   729,   730,   731,   732,   733,   167,   180,   408,
    1012,   203,   181,   351,  1007,  1013,  1046,   418,   217,   168,
     197,  1047,  1029,   210,   182,  1030,   358,   183,   237,   359,
     221,   360,   198,   361,   362,   211,   378,   384,   259,   417,
     239,   428,   222,   278,   184,   392,   393,   200,    94,   404,
     273,   204,   240,   205,   406,   291,   459,   460,   218,   407,
     219,   419,   274,   422,   316,   426,   260,   292,   427,   430,
     195,   279,   431,   206,    94,   280,   317,   281,   432,   114,
     220,   596,   597,   598,   107,   108,   109,   110,   318,   112,
     238,   114,   253,   975,   976,   977,   978,   115,   116,   115,
     116,   433,   472,   438,   441,   443,   444,   447,   448,   115,
     116,   449,   172,   173,   230,   175,   176,   461,   462,   463,
     231,   232,   233,   234,   235,   236,   464,   177,   465,   466,
     178,   468,   469,   470,   471,   473,   474,   475,   179,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   476,   477,   478,
     479,   480,   130,   481,   314,   315,   482,   162,   564,   565,
     566,   483,   484,   485,   486,   487,   488,   489,   490,   167,
     491,   493,   492,   494,   496,   499,   747,   760,   316,   500,
      94,   168,    94,   501,   497,   502,   503,   505,   749,   761,
     317,   506,    94,   507,   504,   508,   509,   511,   513,   515,
     750,   762,   318,   514,   516,   519,   520,   521,   517,   522,
     523,   524,   525,   527,   528,   529,   530,   531,   532,   533,
     535,   536,   537,   539,   540,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   620,   551,   552,   553,   554,   555,
     556,   557,   559,   561,   877,   879,   627,   562,   563,   567,
     568,   569,   570,   571,   572,   638,   573,    32,   576,   577,
     578,   579,   580,   593,   582,   581,   583,   584,   594,   887,
     585,   586,   587,   588,   589,   591,   592,   595,   601,   602,
     603,   604,   605,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   621,   622,   623,   634,   635,   636,
     637,   679,   713,   683,   687,   691,   695,   717,   720,   724,
     769,   773,   781,   791,   792,   793,   794,   795,   797,   798,
     800,   801,   802,   808,  1016,   807,   811,   810,   813,   814,
     816,   817,   820,   819,   876,   834,   823,   833,   837,   836,
     838,   839,   840,   841,   842,   843,   848,   849,   850,   858,
     863,   862,   865,   866,   878,   872,   868,   873,   874,   875,
     881,   884,   880,   882,   883,   885,   886,   919,   946,   947,
     939,   952,   953,   956,   987,   955,   961,   940,   993,   988,
    1010,   941,   995,   942,   943,   994,   996,   944,  1015,  1018,
    1020,  1043,   948,   949,  1023,  1025,   950,   980,   981,   180,
    1044,  1045,   259,   181,  1048,   278,   574,   639,   897,   705,
     982,   197,   898,   467,   273,   182,   498,   291,   183,   923,
     913,  1049,   237,   198,   899,   295,   274,   900,   495,   292,
     260,   926,   914,   279,   239,   184,   902,   280,   200,   281,
     983,   747,   984,   927,   901,   760,   240,   924,   906,   991,
     907,   203,  1002,   749,   217,  1003,  1004,   761,  1005,   965,
     888,   195,   641,   210,   890,   750,   221,   920,   918,   762,
     912,   967,  1008,   938,  1019,   211,   917,   937,   222,   541,
     892,   925,   891,   968,   238,   945,   510,   966,   916,  1014,
    1022,   204,   251,   205,   218,   894,   219,   893,   534,  1024,
     896,   512,   895,   960,   538,   518,   958,   957,   526,   959,
     936,   935,   934,   206,   778,  1050,   220,  1017,  1051,   954,
     558,   767,   951,  1053,   640,  1021,  1041,  1052,   974,   560,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   897,
       0,     0,     0,   898,     0,   923,     0,     0,     0,     0,
       0,   913,     0,     0,     0,   899,     0,   926,   900,     0,
       0,     0,   965,   914,     0,     0,     0,   902,     0,   927,
       0,     0,     0,   924,   967,   901,     0,     0,     0,   906,
       0,   907,     0,     0,     0,     0,   968,     0,     0,     0,
     966,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   912,     0,     0,     0,     0,     0,   925
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    73,    78,    79,
      80,    81,   586,   580,    72,    73,    74,    75,    76,    73,
      78,    79,    73,    81,   569,   818,    72,    73,    74,    75,
      76,   818,    78,    79,   818,    81,    78,    79,   818,    73,
     818,    79,    73,    79,    74,    75,    74,    75,   818,    10,
      16,     0,     5,     7,     7,   165,     9,    12,    13,    45,
      46,    47,    48,    49,    50,    73,    74,    75,    76,    11,
      44,     7,    14,    15,    16,     7,    62,    63,   507,     7,
      87,    94,    95,    57,    58,    59,    60,    61,    62,    63,
     519,   520,   521,     7,    17,    37,    38,    39,    40,    41,
      42,    43,    44,    85,    94,    95,    80,    62,    63,    83,
      92,   133,   134,   135,   136,     7,    87,    88,     3,    90,
      62,    63,    45,     8,    47,    48,    44,    45,    51,    52,
      53,    73,    74,    75,    76,    77,     3,    79,    44,    62,
      63,     8,    84,     3,    62,    63,   168,    43,     8,    55,
       3,    93,   165,    17,    96,     8,    62,    63,   165,     7,
       3,   103,    26,    81,    82,     8,    45,     3,     7,   111,
     112,     3,     8,   115,    80,     3,     8,    83,   139,   165,
       8,     3,     3,    62,    63,     6,     8,   148,   149,   150,
     142,   165,     3,   145,   146,   147,   989,     8,    62,    63,
      62,    63,   989,     3,   165,   989,   130,   131,     8,   989,
     165,   989,   165,   166,   167,   168,     3,     3,     7,   989,
      17,     8,     8,   165,     7,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
       7,     7,   165,   107,   108,   109,   110,   165,    45,     3,
       3,   113,   114,     3,     8,     8,     7,   824,     8,   165,
       3,   806,   141,     6,   143,   144,    37,    38,    39,    40,
       3,     3,   140,    44,     3,     8,     8,   851,     3,     8,
       6,     6,   352,    54,     3,    56,   165,     3,     3,     8,
       6,    62,    63,    64,    65,    66,    67,    68,    69,     3,
       3,   165,     3,   165,     8,     8,     4,     8,     8,    80,
       3,   381,    83,    84,     3,   385,   104,   105,   106,     8,
      91,    97,    98,    99,   100,   101,   102,   385,   398,     3,
       3,   401,   398,     4,     8,     8,     3,     3,   408,   385,
     398,     8,     3,   401,   398,     6,     4,   398,   418,     4,
     408,     4,   398,     4,     4,   401,     4,     4,   428,     8,
     418,     3,   408,   433,   398,     4,     4,   398,   165,     4,
     428,   401,   418,   401,     4,   433,   342,   343,   408,     4,
     408,     8,   428,     4,   454,     4,   428,   433,     8,     4,
     398,   433,     4,   401,   165,   433,   454,   433,     8,    44,
     408,    70,    71,    72,    37,    38,    39,    40,   454,    42,
     418,    44,    45,    18,    19,    20,    21,    62,    63,    62,
      63,     3,   166,     4,     4,     4,     4,     4,     4,    62,
      63,     4,    65,    66,    79,    68,    69,   165,     4,     4,
      85,    86,    87,    88,    89,    90,     4,    80,     4,     4,
      83,     4,     4,     4,     4,   166,   166,   166,    91,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   166,     4,     4,
       4,     4,   562,     4,   137,   138,     4,   567,   464,   465,
     466,     4,     4,     4,     4,     4,     4,     4,     4,   567,
       4,     4,   166,     4,     4,     4,   586,   587,   588,     4,
     165,   567,   165,     4,   168,     4,     4,   168,   586,   587,
     588,     4,   165,     4,   166,     4,     4,     4,     4,     4,
     586,   587,   588,   166,   166,     4,     4,     4,   166,     4,
       4,     4,     4,     4,     4,   166,     4,     4,     4,   168,
       4,   168,   168,     4,     4,   168,     4,     4,   166,     4,
     166,   166,     4,     4,   540,   168,   168,   168,     4,     4,
       4,     4,     4,     4,   168,   168,   132,     7,     7,     7,
       7,     7,     5,     5,     5,   561,     5,     7,   165,     5,
       5,     5,     5,   165,     5,     7,     5,     5,   165,   168,
       7,     7,     7,     7,     5,     5,     5,   165,   165,     7,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
       5,     7,    78,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   168,     6,     3,     6,     6,     3,
       6,     3,     3,     6,   166,     3,     6,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   165,
       3,     6,     6,     3,   166,     4,     8,     4,     4,     4,
       4,     4,   166,   166,   166,   166,   166,     4,     4,     4,
     166,     4,     4,     3,     8,     6,     4,   166,     4,     8,
       4,   166,     3,   166,   166,     8,     8,   166,     4,     4,
       4,     4,   166,   166,     5,     7,   166,   165,   165,   809,
       4,     4,   812,   809,     4,   815,   480,   562,   818,   579,
     165,   809,   818,   352,   812,   809,   385,   815,   809,   829,
     818,   168,   832,   809,   818,   835,   812,   818,   381,   815,
     812,   829,   818,   815,   832,   809,   818,   815,   809,   815,
     165,   851,   165,   829,   818,   855,   832,   829,   818,   165,
     818,   861,   165,   851,   864,   165,   165,   855,   165,   869,
     803,   809,   567,   861,   808,   851,   864,   827,   824,   855,
     818,   869,   165,   837,   166,   861,   821,   835,   864,   436,
     811,   829,   809,   869,   832,   844,   398,   869,   820,   989,
     165,   861,    77,   861,   864,   814,   864,   812,   428,   165,
     817,   401,   815,   866,   433,   408,   863,   861,   418,   864,
     834,   832,   830,   861,   602,   166,   864,   995,   166,   855,
     454,   588,   851,   165,   563,  1012,  1029,  1046,   870,   457,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   989,
      -1,    -1,    -1,   989,    -1,   995,    -1,    -1,    -1,    -1,
      -1,   989,    -1,    -1,    -1,   989,    -1,   995,   989,    -1,
      -1,    -1,  1012,   989,    -1,    -1,    -1,   989,    -1,   995,
      -1,    -1,    -1,   995,  1012,   989,    -1,    -1,    -1,   989,
      -1,   989,    -1,    -1,    -1,    -1,  1012,    -1,    -1,    -1,
    1012,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   989,    -1,    -1,    -1,    -1,    -1,   995
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
       0,     5,     7,     9,   165,   166,   167,   168,   185,   186,
     187,   192,     7,   201,     7,   207,     7,   218,     7,   312,
       7,   389,     7,   405,     7,   422,     7,   341,     7,   347,
       7,   371,     7,   288,     7,   481,     7,   520,   193,   188,
     202,   208,   219,   313,   390,   406,   423,   342,   348,   372,
     289,   482,   521,   185,   194,   195,   165,   190,   191,    10,
     139,   148,   149,   150,   165,   200,   203,   204,   205,   512,
     514,   516,   518,    11,    14,    15,    16,    37,    38,    39,
      40,    41,    42,    43,    44,    62,    63,    73,    74,    75,
      76,    77,    79,    84,    93,    96,   103,   111,   112,   115,
     200,   209,   210,   211,   212,   213,   214,   215,   216,   225,
     227,   229,   262,   268,   274,   280,   282,   296,   306,   331,
     339,   365,   395,   397,   416,   446,   458,   470,   471,   479,
      12,    13,   200,   220,   221,   222,   224,   395,   397,    54,
      56,    64,    65,    66,    67,    68,    69,    80,    83,    91,
     200,   211,   212,   213,   214,   314,   315,   316,   318,   320,
     322,   324,   326,   329,   330,   365,   383,   395,   397,   399,
     416,   441,    55,   200,   322,   324,   365,   391,   392,   393,
     395,   397,    57,    58,    59,    60,    61,   200,   322,   324,
     365,   395,   397,   407,   408,   409,   411,   412,   414,   415,
      79,    85,    86,    87,    88,    89,    90,   200,   365,   395,
     397,   424,   425,   426,   427,   429,   431,   433,   435,   437,
     439,   339,    17,    45,    47,    48,    51,    52,    53,   200,
     247,   349,   350,   351,   352,   353,   354,   355,   357,   359,
     361,   362,   364,   395,   397,    46,    49,    50,   200,   247,
     353,   359,   373,   374,   375,   376,   377,   379,   380,   381,
     382,   395,   397,    94,    95,   200,   290,   291,   292,   294,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   137,   138,   200,   395,   397,   483,
     484,   485,   486,   488,   490,   491,   493,   494,   495,   498,
     500,   501,   502,   503,   506,   508,   510,   140,   522,   523,
     524,     6,     3,     4,     8,     3,   206,   519,   513,   515,
     517,     4,     3,     8,   217,   226,   228,   230,     4,     4,
       4,     4,     4,   307,   340,   366,   396,   398,   332,   269,
     281,   275,   263,   447,   417,   283,   297,   459,     4,   472,
     480,     3,     8,   223,     4,     3,     8,   384,   400,   317,
     319,   321,     4,     4,   327,   325,   323,   442,     3,     8,
     394,     3,     8,   410,     4,   413,     4,     4,     3,     8,
     440,   428,   430,   432,   434,   436,   438,     8,     3,     8,
     356,   248,     4,   360,   358,   363,     4,     8,     3,   378,
       4,     4,     8,     3,   293,   295,     3,     8,     4,   487,
     489,     4,   492,     4,     4,   496,   499,     4,     4,     4,
     504,   507,   509,   511,     3,     8,   525,     3,     8,   185,
     185,   165,     4,     4,     4,     4,     4,   204,     4,     4,
       4,     4,   166,   166,   166,   166,   166,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   166,     4,     4,   210,     4,   168,   221,     4,
       4,     4,     4,     4,   166,   168,     4,     4,     4,     4,
     315,     4,   392,     4,   166,     4,   166,   166,   408,     4,
       4,     4,     4,     4,     4,     4,   426,     4,     4,   166,
       4,     4,     4,   168,   351,     4,   168,   168,   375,     4,
       4,   291,   168,     4,     4,   166,     4,   166,   166,     4,
       4,   168,   168,   168,     4,     4,     4,     4,   484,     4,
     523,     4,     7,     7,   185,   185,   185,     7,     7,     7,
       5,     5,     5,     5,   187,   189,   165,     5,     5,     5,
       5,     7,     5,     5,     5,     7,     7,     7,     7,     5,
     196,     5,     5,   165,   165,   165,    70,    71,    72,   328,
     196,   165,     7,   165,   165,   165,   196,   196,   196,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     185,   165,   165,   165,   130,   131,   497,   132,   133,   134,
     135,   136,   168,   505,   165,   165,   165,     5,   185,   209,
     522,   220,    17,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,   200,   235,
     236,   237,   240,   242,   244,   246,   247,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   259,   260,   235,     7,
     231,   232,   233,     7,   308,   309,   310,     7,   343,   344,
     345,     7,   367,   368,   369,     7,   333,   334,   335,    87,
     165,   270,   271,   272,   273,   194,    88,    90,   272,   276,
     277,   278,   279,    78,   264,   265,   266,     7,   448,   449,
       7,   418,   419,   420,     7,   284,   285,   286,    97,    98,
      99,   100,   101,   102,   298,   299,   300,   301,   302,   303,
     304,   305,    17,   107,   108,   109,   110,   200,   249,   395,
     397,   460,   461,   462,   465,   466,   468,   469,   113,   114,
     200,   395,   397,   473,   474,   475,   477,   483,   197,     7,
     385,   386,   387,     7,   401,   402,   403,    92,   427,   443,
     444,     7,   526,   527,     8,     8,     8,   238,   241,   243,
     245,     4,     4,     4,     4,     4,   258,     4,     4,   261,
       4,     4,     4,     3,     8,     8,   234,     6,     3,   311,
       6,     3,   346,     6,     3,   370,     6,     3,   336,     6,
       3,     3,     6,     6,     3,     6,   267,     3,     8,   450,
       3,     6,   421,     6,     3,   287,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   463,   467,     4,     4,
       4,     3,     8,   476,   478,     3,     8,     8,   165,   198,
     199,   388,     6,     3,   404,     6,     3,   445,     8,   528,
       3,     6,     4,     4,     4,     4,   166,   168,   166,   168,
     166,     4,   166,   166,     4,   166,   166,   168,   236,   235,
     233,   314,   310,   349,   345,   373,   369,   200,   211,   212,
     213,   214,   247,   306,   318,   320,   322,   324,   326,   330,
     337,   338,   365,   395,   397,   441,   335,   271,   277,     4,
     265,    81,    82,   200,   247,   365,   395,   397,   451,   452,
     453,   454,   455,   457,   449,   424,   420,   290,   286,   166,
     166,   166,   166,   166,   166,   299,     4,     4,   166,   166,
     166,   461,     4,     4,   474,     6,     3,   391,   387,   407,
     403,     4,   141,   143,   144,   200,   247,   395,   397,   529,
     530,   531,   532,   534,   527,    18,    19,    20,    21,   239,
     165,   165,   165,   165,   165,     8,     8,     8,     8,     3,
       8,   165,   456,     4,     8,     3,     8,     8,   104,   105,
     106,   464,   165,   165,   165,   165,     8,     8,   165,   535,
       4,   533,     3,     8,   338,     4,   168,   453,     4,   166,
       4,   530,   165,     5,   165,     7,   536,   537,   538,     3,
       6,   142,   145,   146,   147,   539,   540,   541,   543,   544,
     545,   537,   542,     4,     4,     4,     3,     8,     4,   168,
     166,   166,   540,   165
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
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
     210,   210,   211,   212,   213,   214,   215,   217,   216,   219,
     218,   220,   220,   221,   221,   221,   221,   221,   223,   222,
     224,   226,   225,   228,   227,   230,   229,   231,   231,   232,
     232,   234,   233,   235,   235,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   238,   237,   239,   239,   239,   239,   241,
     240,   243,   242,   245,   244,   246,   248,   247,   249,   250,
     251,   252,   253,   254,   255,   256,   258,   257,   259,   261,
     260,   263,   262,   264,   264,   265,   267,   266,   269,   268,
     270,   270,   271,   271,   272,   273,   275,   274,   276,   276,
     277,   277,   277,   278,   279,   281,   280,   283,   282,   284,
     284,   285,   285,   287,   286,   289,   288,   290,   290,   290,
     291,   291,   293,   292,   295,   294,   297,   296,   298,   298,
     299,   299,   299,   299,   299,   299,   300,   301,   302,   303,
     304,   305,   307,   306,   308,   308,   309,   309,   311,   310,
     313,   312,   314,   314,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   317,   316,   319,   318,   321,   320,
     323,   322,   325,   324,   327,   326,   328,   328,   328,   329,
     330,   332,   331,   333,   333,   334,   334,   336,   335,   337,
     337,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   340,   339,
     342,   341,   343,   343,   344,   344,   346,   345,   348,   347,
     349,   349,   350,   350,   351,   351,   351,   351,   351,   351,
     351,   351,   351,   351,   352,   353,   354,   356,   355,   358,
     357,   360,   359,   361,   363,   362,   364,   366,   365,   367,
     367,   368,   368,   370,   369,   372,   371,   373,   373,   374,
     374,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     376,   378,   377,   379,   380,   381,   382,   384,   383,   385,
     385,   386,   386,   388,   387,   390,   389,   391,   391,   392,
     392,   392,   392,   392,   392,   392,   394,   393,   396,   395,
     398,   397,   400,   399,   401,   401,   402,   402,   404,   403,
     406,   405,   407,   407,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   410,   409,   411,   413,   412,
     414,   415,   417,   416,   418,   418,   419,   419,   421,   420,
     423,   422,   424,   424,   425,   425,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   428,   427,   430,
     429,   432,   431,   434,   433,   436,   435,   438,   437,   440,
     439,   442,   441,   443,   443,   445,   444,   447,   446,   448,
     448,   450,   449,   451,   451,   452,   452,   453,   453,   453,
     453,   453,   453,   453,   454,   456,   455,   457,   459,   458,
     460,   460,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   463,   462,   464,   464,   464,   465,   467,   466,   468,
     469,   470,   472,   471,   473,   473,   474,   474,   474,   474,
     474,   476,   475,   478,   477,   480,   479,   482,   481,   483,
     483,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     485,   487,   486,   489,   488,   490,   492,   491,   493,   494,
     496,   495,   497,   497,   499,   498,   500,   501,   502,   504,
     503,   505,   505,   505,   505,   505,   507,   506,   509,   508,
     511,   510,   513,   512,   515,   514,   517,   516,   519,   518,
     521,   520,   522,   522,   523,   525,   524,   526,   526,   528,
     527,   529,   529,   530,   530,   530,   530,   530,   530,   530,
     531,   533,   532,   535,   534,   536,   536,   538,   537,   539,
     539,   540,   540,   540,   540,   542,   541,   543,   544,   545
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
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
       1,     1,     3,     3,     3,     3,     3,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
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
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"preferred-lifetime\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp6_object", "$@19", "sub_dhcp6",
  "$@20", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@21",
  "sub_interfaces6", "$@22", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@23", "re_detect",
  "lease_database", "$@24", "hosts_database", "$@25", "hosts_databases",
  "$@26", "database_list", "not_empty_database_list", "database", "$@27",
  "database_map_params", "database_map_param", "database_type", "$@28",
  "db_type", "user", "$@29", "password", "$@30", "host", "$@31", "port",
  "name", "$@32", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@33", "max_reconnect_tries", "keyspace", "$@34",
  "sanity_checks", "$@35", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@36", "mac_sources", "$@37", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@38",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@39",
  "hooks_libraries", "$@40", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@41",
  "sub_hooks_library", "$@42", "hooks_params", "hooks_param", "library",
  "$@43", "parameters", "$@44", "expired_leases_processing", "$@45",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@46",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@47",
  "sub_subnet6", "$@48", "subnet6_params", "subnet6_param", "subnet",
  "$@49", "interface", "$@50", "interface_id", "$@51", "client_class",
  "$@52", "require_client_classes", "$@53", "reservation_mode", "$@54",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@55",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@56", "shared_network_params", "shared_network_param",
  "option_def_list", "$@57", "sub_option_def_list", "$@58",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@59", "sub_option_def", "$@60",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@61",
  "option_def_record_types", "$@62", "space", "$@63", "option_def_space",
  "option_def_encapsulate", "$@64", "option_def_array", "option_data_list",
  "$@65", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@66", "sub_option_data", "$@67",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@68",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@69", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@70", "sub_pool6", "$@71",
  "pool_params", "pool_param", "pool_entry", "$@72", "user_context",
  "$@73", "comment", "$@74", "pd_pools_list", "$@75",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@76", "sub_pd_pool", "$@77", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@78", "pd_prefix_len", "excluded_prefix", "$@79",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@80",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@81", "sub_reservation", "$@82", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@83", "prefixes", "$@84", "duid", "$@85", "hw_address", "$@86",
  "hostname", "$@87", "flex_id_value", "$@88",
  "reservation_client_classes", "$@89", "relay", "$@90", "relay_map",
  "ip_address", "$@91", "client_classes", "$@92", "client_classes_list",
  "client_class_entry", "$@93", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@94", "only_if_required",
  "server_id", "$@95", "server_id_params", "server_id_param",
  "server_id_type", "$@96", "duid_type", "htype", "identifier", "$@97",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@98",
  "control_socket_params", "control_socket_param", "socket_type", "$@99",
  "socket_name", "$@100", "dhcp_ddns", "$@101", "sub_dhcp_ddns", "$@102",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@103", "server_ip", "$@104", "server_port",
  "sender_ip", "$@105", "sender_port", "max_queue_size", "ncr_protocol",
  "$@106", "ncr_protocol_value", "ncr_format", "$@107",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@108", "replace_client_name_value",
  "generated_prefix", "$@109", "hostname_char_set", "$@110",
  "hostname_char_replacement", "$@111", "dhcp4_json_object", "$@112",
  "dhcpddns_json_object", "$@113", "control_agent_json_object", "$@114",
  "logging_object", "$@115", "sub_logging", "$@116", "logging_params",
  "logging_param", "loggers", "$@117", "loggers_entries", "logger_entry",
  "$@118", "logger_params", "logger_param", "debuglevel", "severity",
  "$@119", "output_options_list", "$@120", "output_options_list_content",
  "output_entry", "$@121", "output_params_list", "output_params", "output",
  "$@122", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   251,   251,   251,   252,   252,   253,   253,   254,   254,
     255,   255,   256,   256,   257,   257,   258,   258,   259,   259,
     260,   260,   261,   261,   262,   262,   263,   263,   264,   264,
     272,   273,   274,   275,   276,   277,   278,   281,   286,   286,
     297,   300,   301,   304,   308,   315,   315,   322,   323,   326,
     330,   337,   337,   344,   345,   348,   352,   363,   373,   373,
     388,   389,   393,   394,   395,   396,   397,   398,   401,   401,
     416,   416,   425,   426,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   461,   466,   471,   476,   481,   486,   486,   497,
     497,   506,   507,   510,   511,   512,   513,   514,   517,   517,
     527,   533,   533,   545,   545,   557,   557,   567,   568,   571,
     572,   575,   575,   585,   586,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   609,   609,   616,   617,   618,   619,   622,
     622,   630,   630,   638,   638,   646,   651,   651,   659,   664,
     669,   674,   679,   684,   689,   694,   699,   699,   707,   712,
     712,   720,   720,   730,   731,   733,   735,   735,   753,   753,
     763,   764,   767,   768,   771,   776,   781,   781,   791,   792,
     795,   796,   797,   800,   805,   812,   812,   822,   822,   832,
     833,   836,   837,   840,   840,   850,   850,   860,   861,   862,
     865,   866,   869,   869,   877,   877,   885,   885,   896,   897,
     900,   901,   902,   903,   904,   905,   908,   913,   918,   923,
     928,   933,   941,   941,   954,   955,   958,   959,   966,   966,
     992,   992,  1003,  1004,  1008,  1009,  1010,  1011,  1012,  1013,
    1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,
    1024,  1025,  1026,  1027,  1030,  1030,  1038,  1038,  1046,  1046,
    1054,  1054,  1062,  1062,  1072,  1072,  1079,  1080,  1081,  1084,
    1089,  1097,  1097,  1108,  1109,  1113,  1114,  1117,  1117,  1125,
    1126,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1152,  1152,
    1165,  1165,  1174,  1175,  1178,  1179,  1184,  1184,  1199,  1199,
    1213,  1214,  1217,  1218,  1221,  1222,  1223,  1224,  1225,  1226,
    1227,  1228,  1229,  1230,  1233,  1235,  1240,  1242,  1242,  1250,
    1250,  1258,  1258,  1266,  1268,  1268,  1276,  1285,  1285,  1297,
    1298,  1303,  1304,  1309,  1309,  1321,  1321,  1333,  1334,  1339,
    1340,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,
    1356,  1358,  1358,  1366,  1368,  1370,  1375,  1383,  1383,  1395,
    1396,  1399,  1400,  1403,  1403,  1413,  1413,  1422,  1423,  1426,
    1427,  1428,  1429,  1430,  1431,  1432,  1435,  1435,  1443,  1443,
    1468,  1468,  1498,  1498,  1510,  1511,  1514,  1515,  1518,  1518,
    1530,  1530,  1542,  1543,  1546,  1547,  1548,  1549,  1550,  1551,
    1552,  1553,  1554,  1555,  1556,  1559,  1559,  1567,  1572,  1572,
    1580,  1585,  1593,  1593,  1603,  1604,  1607,  1608,  1611,  1611,
    1620,  1620,  1629,  1630,  1633,  1634,  1638,  1639,  1640,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1648,  1651,  1651,  1661,
    1661,  1671,  1671,  1679,  1679,  1687,  1687,  1695,  1695,  1703,
    1703,  1716,  1716,  1726,  1727,  1730,  1730,  1741,  1741,  1751,
    1752,  1755,  1755,  1765,  1766,  1769,  1770,  1773,  1774,  1775,
    1776,  1777,  1778,  1779,  1782,  1784,  1784,  1792,  1800,  1800,
    1812,  1813,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,
    1824,  1827,  1827,  1834,  1835,  1836,  1839,  1844,  1844,  1852,
    1857,  1864,  1871,  1871,  1881,  1882,  1885,  1886,  1887,  1888,
    1889,  1892,  1892,  1900,  1900,  1910,  1910,  1922,  1922,  1932,
    1933,  1936,  1937,  1938,  1939,  1940,  1941,  1942,  1943,  1944,
    1945,  1946,  1947,  1948,  1949,  1950,  1951,  1952,  1953,  1954,
    1957,  1962,  1962,  1970,  1970,  1978,  1983,  1983,  1991,  1996,
    2001,  2001,  2009,  2010,  2013,  2013,  2021,  2026,  2031,  2036,
    2036,  2044,  2047,  2050,  2053,  2056,  2062,  2062,  2070,  2070,
    2078,  2078,  2088,  2088,  2095,  2095,  2102,  2102,  2115,  2115,
    2125,  2125,  2136,  2137,  2141,  2145,  2145,  2157,  2158,  2162,
    2162,  2170,  2171,  2174,  2175,  2176,  2177,  2178,  2179,  2180,
    2183,  2188,  2188,  2196,  2196,  2206,  2207,  2210,  2210,  2218,
    2219,  2222,  2223,  2224,  2225,  2228,  2228,  2236,  2241,  2246
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
#line 4850 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2251 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
