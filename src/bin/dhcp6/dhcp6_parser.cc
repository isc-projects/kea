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

  case 101:
#line 460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 736 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 187:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 816 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1623 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 907 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 249:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1071 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1078 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1187 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1234 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1382 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 409:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 411:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2573 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2677 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1834 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3119 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2009 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2043 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2052 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2063 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2071 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3341 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2103 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2187 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2189 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 644:
#line 2227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2245 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -796;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     315,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,    42,    36,    58,    79,   106,
     120,   121,   142,   160,   166,   178,   192,   219,   221,   223,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,    36,  -115,
      27,    33,    68,   175,   234,   243,   332,    17,    70,   133,
       3,   319,    84,  -796,   226,   194,   230,   228,   248,  -796,
    -796,  -796,  -796,  -796,   253,  -796,    43,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,   271,   278,   314,
     324,   325,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   330,  -796,  -796,  -796,
      54,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   342,
    -796,    82,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,   350,   351,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,    91,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   134,  -796,  -796,  -796,
    -796,  -796,   354,  -796,   360,   364,  -796,  -796,  -796,  -796,
    -796,  -796,   213,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
     285,   258,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
     300,  -796,  -796,   370,  -796,  -796,  -796,   374,  -796,  -796,
     363,   329,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,   381,   384,  -796,  -796,  -796,
    -796,   394,   389,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,   217,  -796,  -796,  -796,   412,
    -796,  -796,   426,  -796,   430,   445,  -796,  -796,   450,   451,
     454,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   246,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,   257,  -796,  -796,
    -796,    36,    36,  -796,   294,   456,   457,   458,   476,   477,
    -796,    27,  -796,   478,   479,   481,   482,   321,   322,   323,
     327,   333,   486,   488,   490,   491,   494,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   344,   505,   507,    33,
    -796,   508,   349,    68,  -796,   509,   515,   516,   517,   518,
     357,   356,   521,   522,   523,   524,   525,   175,  -796,   526,
     234,  -796,   527,   366,   529,   368,   369,   243,  -796,   536,
     537,   538,   539,   540,   541,   543,  -796,   332,  -796,   544,
     545,   385,   546,   548,   549,   386,  -796,    70,   551,   388,
     390,  -796,   133,   553,   555,   123,  -796,   393,   558,   559,
     402,   563,   403,   404,   567,   568,   405,   406,   407,   572,
     573,   574,   575,   319,  -796,   576,    84,  -796,  -796,  -796,
     577,   578,   579,    36,    36,    36,  -796,   580,   581,   582,
     585,  -796,  -796,  -796,  -796,  -796,   586,   587,   588,   589,
     417,   590,   592,   593,   594,   595,   596,   598,   597,   599,
    -796,   600,   601,  -796,   604,  -796,  -796,   605,   606,   418,
     419,   429,  -796,  -796,   343,   604,   435,   607,   608,  -796,
     440,  -796,   448,  -796,   449,  -796,  -796,  -796,   604,   604,
     604,   452,   453,   455,   459,  -796,   460,   461,  -796,   462,
     463,   464,  -796,  -796,   465,  -796,  -796,  -796,   466,    36,
    -796,  -796,   467,   468,  -796,   469,  -796,  -796,   191,   484,
    -796,  -796,  -796,    55,   470,   471,   472,  -796,   614,  -796,
      36,    33,    84,  -796,  -796,  -796,    68,   129,   129,   615,
     616,   631,   632,  -796,  -796,  -796,   633,   -49,    36,    53,
     564,   634,   636,   326,    62,    21,   319,  -796,  -796,   637,
     638,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
     639,    -3,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   640,  -796,   260,   261,
     264,  -796,  -796,  -796,  -796,   617,   644,   645,   646,   647,
    -796,   648,   649,  -796,   650,   651,   652,  -796,   276,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,   282,  -796,   653,
     654,  -796,  -796,   655,   657,  -796,  -796,   656,   660,  -796,
    -796,   658,   662,  -796,  -796,   661,   663,  -796,  -796,  -796,
     108,  -796,  -796,  -796,   664,  -796,  -796,  -796,   144,  -796,
    -796,  -796,  -796,   304,  -796,  -796,  -796,   181,  -796,  -796,
     665,   666,  -796,   668,   669,   670,   671,   672,   673,   307,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   674,
     675,   676,  -796,  -796,  -796,  -796,   308,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   316,  -796,
    -796,  -796,   317,   493,  -796,   677,   678,  -796,  -796,   679,
     681,  -796,  -796,   680,   684,  -796,  -796,  -796,   682,  -796,
    -796,   280,  -796,  -796,  -796,  -796,   685,   687,   688,   689,
     528,   514,   530,   520,   531,   691,   532,   533,   696,   535,
     542,   534,   129,  -796,  -796,   129,  -796,   615,   175,  -796,
     616,    70,  -796,   631,   133,  -796,   632,   208,  -796,   633,
     -49,  -796,  -796,    53,  -796,   699,   564,  -796,    57,   634,
    -796,     3,  -796,   636,   547,   550,   552,   554,   556,   557,
     326,  -796,   700,   701,   560,   561,   562,    62,  -796,   702,
     703,    21,  -796,  -796,  -796,   704,   706,   234,  -796,   637,
     243,  -796,   638,   332,  -796,   639,   707,  -796,   288,   640,
    -796,   190,   565,   566,   569,  -796,  -796,  -796,  -796,  -796,
     570,  -796,  -796,   571,  -796,  -796,  -796,  -796,   328,  -796,
     335,  -796,   709,  -796,   711,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   345,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   603,  -796,
    -796,   708,  -796,  -796,  -796,  -796,  -796,   713,   712,  -796,
    -796,  -796,  -796,  -796,   367,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   346,   609,  -796,  -796,  -796,  -796,   610,
     613,  -796,  -796,   618,   383,  -796,   395,  -796,   716,  -796,
     619,  -796,   710,  -796,  -796,  -796,  -796,  -796,   398,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   208,  -796,
    -796,   721,   584,  -796,    57,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   725,   591,
     728,   288,  -796,  -796,   620,  -796,  -796,   732,  -796,   621,
    -796,  -796,   726,  -796,  -796,   289,  -796,   -42,   726,  -796,
    -796,   735,   736,   739,   401,  -796,  -796,  -796,  -796,  -796,
    -796,   742,   602,   623,   626,   -42,  -796,   630,  -796,  -796,
    -796,  -796,  -796
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   108,     9,   249,    11,
     394,    13,   419,    15,   449,    17,   319,    19,   327,    21,
     364,    23,   214,    25,   546,    27,   609,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   451,     0,   329,   366,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     607,   601,   603,   605,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   106,   120,   122,   124,     0,     0,     0,
       0,     0,   241,   317,   356,   407,   409,   290,   187,   204,
     195,   180,   486,   206,   225,   507,     0,   531,   544,   100,
       0,    72,    74,    75,    76,    77,    78,    81,    82,    83,
      84,    99,    85,    87,    86,    91,    92,    79,    80,    89,
      90,    97,    98,    88,    93,    94,    95,    96,   117,     0,
     116,     0,   110,   112,   113,   114,   115,   386,   411,   273,
     275,   277,     0,     0,   283,   281,   279,   441,   480,   272,
     253,   254,   255,   256,     0,   251,   260,   261,   262,   265,
     266,   268,   263,   264,   257,   258,   270,   271,   259,   267,
     269,   405,   404,   400,   401,   399,     0,   396,   398,   402,
     403,   434,     0,   437,     0,     0,   433,   427,   428,   426,
     431,   432,     0,   421,   423,   424,   429,   430,   425,   478,
     466,   468,   470,   472,   474,   476,   465,   462,   463,   464,
       0,   452,   453,   457,   458,   455,   459,   460,   461,   456,
       0,   346,   165,     0,   350,   348,   353,     0,   342,   343,
       0,   330,   331,   333,   345,   334,   335,   336,   352,   337,
     338,   339,   340,   341,   380,     0,     0,   378,   379,   382,
     383,     0,   367,   368,   370,   371,   372,   373,   374,   375,
     376,   377,   221,   223,   218,     0,   216,   219,   220,     0,
     570,   572,     0,   575,     0,     0,   579,   583,     0,     0,
       0,   588,   595,   597,   599,   568,   566,   567,     0,   548,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   614,     0,   611,   613,
      46,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      57,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,     0,     0,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   250,     0,
       0,   395,     0,     0,     0,     0,     0,     0,   420,     0,
       0,     0,     0,     0,     0,     0,   450,     0,   320,     0,
       0,     0,     0,     0,     0,     0,   328,     0,     0,     0,
       0,   365,     0,     0,     0,     0,   215,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   547,     0,     0,   610,    50,    43,
       0,     0,     0,     0,     0,     0,    61,     0,     0,     0,
       0,   101,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     530,     0,     0,    73,     0,   119,   111,     0,     0,     0,
       0,     0,   288,   289,     0,     0,     0,     0,     0,   252,
       0,   397,     0,   436,     0,   439,   440,   422,     0,     0,
       0,     0,     0,     0,     0,   454,     0,     0,   344,     0,
       0,     0,   355,   332,     0,   384,   385,   369,     0,     0,
     217,   569,     0,     0,   574,     0,   577,   578,     0,     0,
     585,   586,   587,     0,     0,     0,     0,   549,     0,   612,
       0,     0,     0,   602,   604,   606,     0,     0,     0,   126,
     243,   321,   358,    40,   408,   410,   292,     0,    47,     0,
       0,     0,   208,     0,     0,     0,     0,    51,   118,   388,
     413,   274,   276,   278,   285,   286,   287,   284,   282,   280,
     443,     0,   406,   435,   438,   479,   467,   469,   471,   473,
     475,   477,   347,   166,   351,   349,   354,   381,   222,   224,
     571,   573,   576,   581,   582,   580,   584,   590,   591,   592,
     593,   594,   589,   596,   598,   600,     0,    44,     0,     0,
       0,   152,   158,   160,   162,     0,     0,     0,     0,     0,
     175,     0,     0,   178,     0,     0,     0,   151,     0,   132,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     146,   147,   148,   149,   144,   145,   150,     0,   130,     0,
     127,   128,   247,     0,   244,   245,   325,     0,   322,   323,
     362,     0,   359,   360,   296,     0,   293,   294,   193,   194,
       0,   189,   191,   192,     0,   202,   203,   199,     0,   197,
     200,   201,   185,     0,   182,   184,   490,     0,   488,   212,
       0,   209,   210,     0,     0,     0,     0,     0,     0,     0,
     227,   229,   230,   231,   232,   233,   234,   520,   526,     0,
       0,     0,   519,   516,   517,   518,     0,   509,   511,   514,
     512,   513,   515,   540,   542,   539,   537,   538,     0,   533,
     535,   536,     0,    53,   392,     0,   389,   390,   417,     0,
     414,   415,   447,     0,   444,   445,   484,   483,     0,   482,
     618,     0,   616,    69,   608,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,   123,     0,   125,     0,     0,   242,
       0,   329,   318,     0,   366,   357,     0,     0,   291,     0,
       0,   188,   205,     0,   196,     0,     0,   181,   492,     0,
     487,     0,   207,     0,     0,     0,     0,     0,     0,     0,
       0,   226,     0,     0,     0,     0,     0,     0,   508,     0,
       0,     0,   532,   545,    55,     0,    54,     0,   387,     0,
       0,   412,     0,   451,   442,     0,     0,   481,     0,     0,
     615,     0,     0,     0,     0,   164,   167,   168,   169,   170,
       0,   177,   171,     0,   172,   173,   174,   133,     0,   129,
       0,   246,     0,   324,     0,   361,   316,   311,   313,   304,
     305,   300,   301,   302,   303,   309,   310,   308,   312,     0,
     298,   306,   314,   315,   307,   295,   190,   198,     0,   183,
     504,     0,   502,   503,   499,   500,   501,     0,   493,   494,
     496,   497,   498,   489,     0,   211,   235,   236,   237,   238,
     239,   240,   228,     0,     0,   525,   528,   529,   510,     0,
       0,   534,    52,     0,     0,   391,     0,   416,     0,   446,
       0,   632,     0,   630,   628,   622,   626,   627,     0,   620,
     624,   625,   623,   617,   154,   155,   156,   157,   153,   159,
     161,   163,   176,   179,   131,   248,   326,   363,     0,   297,
     186,     0,     0,   491,     0,   213,   522,   523,   524,   521,
     527,   541,   543,    56,   393,   418,   448,   485,     0,     0,
       0,     0,   619,   299,     0,   506,   495,     0,   629,     0,
     621,   505,     0,   631,   636,     0,   634,     0,     0,   633,
     644,     0,     0,     0,     0,   638,   640,   641,   642,   643,
     635,     0,     0,     0,     0,     0,   637,     0,   646,   647,
     648,   639,   645
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,     0,  -796,   189,  -796,
    -796,  -796,  -796,  -796,  -796,   176,  -796,  -427,  -796,  -796,
    -796,   -70,  -796,  -796,  -796,   420,  -796,  -796,  -796,  -796,
     211,   400,   -58,   -53,   -52,   -41,  -796,  -796,  -796,  -796,
    -796,   187,   413,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,   -34,  -796,  -549,    -2,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   -66,  -796,
    -567,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   -22,  -796,  -796,  -796,
    -796,  -796,   -15,  -561,  -796,  -796,  -796,  -796,   -16,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,   -19,  -796,  -796,
    -796,   -18,   376,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
     -24,  -796,  -796,  -796,  -796,  -796,  -796,  -795,  -796,  -796,
    -796,     7,  -796,  -796,  -796,    10,   422,  -796,  -796,  -794,
    -796,  -788,  -796,   -35,  -796,   -11,  -796,  -783,  -796,  -796,
    -796,  -782,  -796,  -796,  -796,  -796,     4,  -796,  -796,  -164,
     749,  -796,  -796,  -796,  -796,  -796,    15,  -796,  -796,  -796,
      18,  -796,   408,  -796,   -72,  -796,  -796,  -796,  -796,  -796,
     -65,  -796,  -796,  -796,  -796,  -796,    -7,  -796,  -796,  -796,
      14,  -796,  -796,  -796,    19,  -796,   409,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   -27,  -796,
    -796,  -796,   -23,   436,  -796,  -796,   -48,  -796,   -20,  -796,
    -796,  -796,  -796,  -796,   -17,  -796,  -796,  -796,   -21,   431,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,   -14,  -796,  -796,  -796,    -9,  -796,   425,   251,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -781,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
      26,  -796,  -796,  -796,  -150,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,    11,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,    -4,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,   273,   410,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   295,   411,  -796,  -796,  -796,    -8,  -796,
    -796,  -151,  -796,  -796,  -796,  -796,  -796,  -796,  -166,  -796,
    -796,  -181,  -796,  -796,  -796,  -796,  -796
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     574,    87,    88,    41,    68,    84,    85,   588,   763,   855,
     856,   657,    43,    70,    96,    97,    98,   345,    45,    71,
     130,   131,   132,   133,   134,   135,   136,   137,   353,    47,
      72,   161,   162,   163,   381,   164,   138,   354,   139,   355,
     140,   356,   679,   680,   681,   805,   658,   659,   660,   786,
     978,   661,   787,   662,   788,   663,   789,   664,   665,   420,
     666,   667,   668,   669,   670,   671,   672,   673,   674,   795,
     675,   676,   798,   141,   371,   713,   714,   715,   825,   142,
     368,   700,   701,   702,   703,   143,   370,   708,   709,   710,
     711,   144,   369,   145,   373,   720,   721,   722,   831,    63,
      80,   295,   296,   297,   433,   298,   434,   146,   374,   729,
     730,   731,   732,   733,   734,   735,   736,   147,   362,   683,
     684,   685,   808,    49,    73,   184,   185,   186,   387,   187,
     388,   188,   389,   189,   394,   190,   393,   191,   392,   597,
     192,   193,   148,   367,   695,   696,   697,   817,   909,   910,
     149,   363,    57,    77,   687,   688,   689,   811,    59,    78,
     260,   261,   262,   263,   264,   265,   266,   419,   267,   423,
     268,   422,   269,   270,   424,   271,   150,   364,   691,   692,
     693,   814,    61,    79,   281,   282,   283,   284,   285,   428,
     286,   287,   288,   289,   195,   385,   765,   766,   767,   857,
      51,    74,   206,   207,   208,   399,   151,   365,   152,   366,
     198,   386,   769,   770,   771,   860,    53,    75,   222,   223,
     224,   402,   225,   226,   404,   227,   228,   199,   395,   773,
     774,   775,   863,    55,    76,   240,   241,   242,   243,   410,
     244,   411,   245,   412,   246,   413,   247,   414,   248,   415,
     249,   409,   200,   396,   778,   779,   866,   153,   372,   717,
     718,   828,   927,   928,   929,   930,   931,   991,   932,   154,
     375,   746,   747,   748,   842,   999,   749,   750,   843,   751,
     752,   155,   156,   377,   758,   759,   760,   849,   761,   850,
     157,   378,    65,    81,   318,   319,   320,   321,   438,   322,
     439,   323,   324,   441,   325,   326,   327,   444,   625,   328,
     445,   329,   330,   331,   332,   449,   632,   333,   450,   334,
     451,   335,   452,    99,   347,   100,   348,   101,   349,   102,
     346,    67,    82,   337,   338,   339,   455,   781,   782,   868,
     968,   969,   970,   971,  1010,   972,  1008,  1025,  1026,  1027,
    1034,  1035,  1036,  1041,  1037,  1038,  1039
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   129,   160,   179,   202,   216,   236,   279,   258,   277,
     294,   315,   259,   278,   280,   180,    38,   743,   707,   677,
     181,   182,   902,   903,   165,   196,   209,   220,   238,   904,
     272,   290,   183,   316,   907,   908,   914,    89,   698,   203,
     217,    31,    30,    32,   103,    33,   351,   104,   105,   106,
      86,   352,   166,   197,   210,   221,   239,   379,   273,   291,
     113,   317,   380,   204,   218,    42,   194,   205,   219,   237,
     107,   108,   109,   110,   111,   112,   113,   114,   598,   737,
     158,   159,   230,   115,   116,   383,    44,   251,   646,   776,
     384,   605,   606,   607,   397,   115,   116,   292,   293,   398,
    1030,   114,   252,  1031,  1032,  1033,   117,   118,   119,   120,
     121,   820,   122,    46,   821,   252,   699,   253,   254,   115,
     116,   255,   256,   257,   115,   116,   123,    48,    50,   124,
     115,   116,   115,   116,   753,   754,   125,   400,   920,   921,
     698,   705,   401,   706,   126,   127,   641,   823,   128,    52,
     824,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,    90,    54,    94,   738,
     739,   740,   741,    56,   252,    91,    92,    93,   252,   274,
     253,   254,   275,   276,   829,    58,    94,   830,   627,   628,
     629,   630,    94,   902,   903,   115,   116,   341,    94,    60,
     904,    34,    35,    36,    37,   907,   908,   914,   974,   975,
     976,   977,   107,   108,   109,   110,   407,   292,   293,   114,
     435,   408,    94,   631,   336,   436,    62,    94,    64,   167,
      66,   168,   340,    94,   342,    94,   343,   115,   116,   169,
     170,   171,   172,   173,   174,   107,   108,   109,   110,   453,
     112,   344,   114,   252,   454,   175,   888,   350,   176,   177,
     456,   417,   707,   379,   456,   457,   178,   383,   783,   784,
     115,   116,   785,   170,   171,   357,   173,   174,   114,   802,
     743,    95,   358,   869,   803,   802,   870,   114,   175,   201,
     804,   176,  1028,   416,    94,  1029,   115,   116,    94,   178,
     211,   212,   213,   214,   215,   115,   116,   826,   418,   129,
     840,   847,   827,   160,   175,   841,   848,   176,   359,   851,
     453,   623,   624,   175,   852,   853,   176,   179,   360,   361,
     202,   802,   427,   252,   376,   165,   984,   216,   397,   180,
      94,   458,   459,   985,   181,   182,   382,   236,   988,   196,
     115,   116,   209,   989,   390,   391,   183,   258,   403,   220,
     279,   259,   277,   166,   405,   203,   278,   280,   406,   238,
     435,   426,   217,    94,   421,   995,   114,   197,   425,   272,
     210,   115,   116,   315,   290,   429,   400,   221,   430,   204,
     194,  1004,   432,   205,   115,   116,   218,   239,   407,    94,
     219,  1011,   431,  1005,  1045,   316,  1012,   273,    94,  1046,
     237,   229,   291,   594,   595,   596,   437,   230,   231,   232,
     233,   234,   235,   723,   724,   725,   726,   727,   728,   961,
     440,   962,   963,   317,   442,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   443,
     996,   997,   998,    94,   446,   447,   313,   314,   448,   460,
     461,   462,   463,   563,   564,   565,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     464,   465,   467,   468,    94,   469,   470,   471,   472,   473,
     476,   129,   477,   474,   478,   479,   160,    94,   480,   475,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   491,
     490,   492,   494,   497,   742,   755,   315,   495,   165,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     510,   512,   513,   514,   515,   516,   744,   756,   316,   619,
     518,   519,   520,   521,   522,   523,   166,   524,   526,   527,
     529,   528,   530,   531,   532,   534,   535,   538,   536,   539,
     637,   541,   542,   543,   745,   757,   317,   545,   544,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     558,   560,   575,   591,   592,   561,   562,   566,   567,   568,
     569,   570,   571,   572,   593,   576,    32,   577,   578,   579,
     599,   581,   580,   582,   583,   602,   584,   585,   586,   587,
     589,   590,   600,   603,   604,   601,   626,   608,   609,   636,
     610,   790,   678,   682,   611,   612,   613,   614,   615,   616,
     617,   618,   620,   621,   622,   633,   634,   635,   686,   690,
     694,   716,   712,   719,   764,   768,   772,   780,   791,   792,
     793,   794,   796,   797,   799,   800,   801,   807,   854,   806,
     810,   809,   812,   813,   815,   816,   819,   818,   573,   833,
     822,   832,   834,   835,   836,   837,   838,   839,   844,   845,
     846,   859,   876,   858,   862,   861,   864,   865,   878,   871,
     867,   872,   873,   874,   875,   880,   877,   879,   881,   882,
     883,   884,   886,   918,   943,   944,   949,   950,   885,   953,
     952,   960,   992,   936,  1009,   994,   937,   986,   938,   987,
     939,   993,   940,   941,  1006,  1014,   945,   946,   947,  1017,
     979,   980,  1019,  1024,   981,   982,   983,  1022,   179,  1042,
    1043,   258,   279,  1044,   277,   259,  1047,   896,   278,   280,
     180,   901,  1015,   640,   704,   181,   182,  1018,   922,   897,
     196,   294,   923,   272,   898,   899,   290,   183,   990,   912,
    1048,   466,   638,   889,  1000,  1001,   900,   742,  1002,   493,
     925,   755,   905,  1003,  1007,  1021,  1023,   202,   197,  1049,
     216,   273,  1050,   236,   291,  1052,   496,   913,   964,   744,
     887,   194,   965,   756,   919,   916,   906,   917,   926,   209,
     911,   540,   220,   934,   935,   238,   942,   891,   890,   509,
     966,   924,   203,   915,  1013,   217,   250,   745,   893,   892,
     895,   757,   955,   894,   954,   533,   511,   210,   517,   956,
     221,   537,   525,   239,  1016,   957,   204,   951,   967,   218,
     205,   959,   777,   219,   958,   933,   237,   639,   948,   762,
    1020,   973,  1040,   557,  1051,     0,     0,   559,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   896,     0,
       0,     0,   901,     0,   922,     0,     0,     0,   923,     0,
     897,     0,     0,     0,     0,   898,   899,     0,     0,     0,
     912,   964,     0,     0,     0,   965,   925,   900,     0,     0,
       0,     0,     0,   905,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   966,     0,     0,     0,     0,   913,     0,
       0,     0,     0,     0,   926,     0,     0,   906,     0,     0,
       0,   911,     0,     0,     0,     0,     0,   924,     0,     0,
       0,   967
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    79,    78,    79,
      80,    81,    78,    79,    79,    73,    16,   584,   579,   568,
      73,    73,   817,   817,    72,    73,    74,    75,    76,   817,
      78,    79,    73,    81,   817,   817,   817,    10,    87,    74,
      75,     5,     0,     7,    11,     9,     3,    14,    15,    16,
     165,     8,    72,    73,    74,    75,    76,     3,    78,    79,
      43,    81,     8,    74,    75,     7,    73,    74,    75,    76,
      37,    38,    39,    40,    41,    42,    43,    44,   505,    17,
      12,    13,    85,    62,    63,     3,     7,    17,    26,    92,
       8,   518,   519,   520,     3,    62,    63,    94,    95,     8,
     142,    44,    45,   145,   146,   147,    73,    74,    75,    76,
      77,     3,    79,     7,     6,    45,   165,    47,    48,    62,
      63,    51,    52,    53,    62,    63,    93,     7,     7,    96,
      62,    63,    62,    63,   113,   114,   103,     3,    81,    82,
      87,    88,     8,    90,   111,   112,    17,     3,   115,     7,
       6,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,   139,     7,   165,   107,
     108,   109,   110,     7,    45,   148,   149,   150,    45,    46,
      47,    48,    49,    50,     3,     7,   165,     6,   133,   134,
     135,   136,   165,   988,   988,    62,    63,     3,   165,     7,
     988,   165,   166,   167,   168,   988,   988,   988,    18,    19,
      20,    21,    37,    38,    39,    40,     3,    94,    95,    44,
       3,     8,   165,   168,   140,     8,     7,   165,     7,    54,
       7,    56,     6,   165,     4,   165,     8,    62,    63,    64,
      65,    66,    67,    68,    69,    37,    38,    39,    40,     3,
      42,     3,    44,    45,     8,    80,   805,     4,    83,    84,
       3,     3,   823,     3,     3,     8,    91,     3,     8,     8,
      62,    63,     8,    65,    66,     4,    68,    69,    44,     3,
     847,   351,     4,     3,     8,     3,     6,    44,    80,    55,
       8,    83,     3,     8,   165,     6,    62,    63,   165,    91,
      57,    58,    59,    60,    61,    62,    63,     3,     8,   379,
       3,     3,     8,   383,    80,     8,     8,    83,     4,     3,
       3,   130,   131,    80,     8,     8,    83,   397,     4,     4,
     400,     3,     3,    45,     4,   383,     8,   407,     3,   397,
     165,   341,   342,     8,   397,   397,     4,   417,     3,   397,
      62,    63,   400,     8,     4,     4,   397,   427,     4,   407,
     432,   427,   432,   383,     4,   400,   432,   432,     4,   417,
       3,     8,   407,   165,     4,     8,    44,   397,     4,   427,
     400,    62,    63,   453,   432,     4,     3,   407,     4,   400,
     397,     8,     3,   400,    62,    63,   407,   417,     3,   165,
     407,     3,     8,     8,     3,   453,     8,   427,   165,     8,
     417,    79,   432,    70,    71,    72,     4,    85,    86,    87,
      88,    89,    90,    97,    98,    99,   100,   101,   102,   141,
       4,   143,   144,   453,     4,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     4,
     104,   105,   106,   165,     4,     4,   137,   138,     4,   165,
       4,     4,     4,   463,   464,   465,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
       4,     4,     4,     4,   165,     4,     4,   166,   166,   166,
       4,   561,     4,   166,     4,     4,   566,   165,     4,   166,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     166,     4,     4,     4,   584,   585,   586,   168,   566,     4,
       4,     4,     4,   166,   168,     4,     4,     4,     4,     4,
       4,     4,   166,     4,   166,   166,   584,   585,   586,   539,
       4,     4,     4,     4,     4,     4,   566,     4,     4,     4,
       4,   166,     4,     4,   168,     4,   168,     4,   168,     4,
     560,   168,     4,     4,   584,   585,   586,     4,   166,   166,
     166,     4,     4,   168,   168,   168,     4,     4,     4,     4,
       4,     4,   165,   165,   165,     7,     7,     7,     7,     7,
       5,     5,     5,     5,   165,     5,     7,     5,     5,     5,
     165,     5,     7,     5,     7,   165,     7,     7,     7,     5,
       5,     5,     5,   165,   165,     7,   132,   165,   165,     5,
     165,     4,     7,     7,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,     7,     7,
       7,     7,    78,     7,     7,     7,     7,     7,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   165,     6,
       3,     6,     6,     3,     6,     3,     3,     6,   479,     3,
       6,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   168,     6,     3,     6,     6,     3,   168,     4,
       8,     4,     4,     4,   166,     4,   166,   166,   166,   166,
       4,   166,   168,     4,     4,     4,     4,     4,   166,     3,
       6,     4,     4,   166,     4,     3,   166,     8,   166,     8,
     166,     8,   166,   166,     8,     4,   166,   166,   166,     4,
     165,   165,     4,     7,   165,   165,   165,     5,   808,     4,
       4,   811,   814,     4,   814,   811,     4,   817,   814,   814,
     808,   817,   168,   566,   578,   808,   808,   166,   828,   817,
     808,   831,   828,   811,   817,   817,   814,   808,   165,   817,
     168,   351,   561,   807,   165,   165,   817,   847,   165,   379,
     828,   851,   817,   165,   165,   165,   165,   857,   808,   166,
     860,   811,   166,   863,   814,   165,   383,   817,   868,   847,
     802,   808,   868,   851,   826,   820,   817,   823,   828,   857,
     817,   435,   860,   831,   833,   863,   840,   810,   808,   397,
     868,   828,   857,   819,   988,   860,    77,   847,   813,   811,
     816,   851,   859,   814,   857,   427,   400,   857,   407,   860,
     860,   432,   417,   863,   994,   862,   857,   851,   868,   860,
     857,   865,   601,   860,   863,   829,   863,   562,   847,   586,
    1011,   869,  1028,   453,  1045,    -1,    -1,   456,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   988,    -1,
      -1,    -1,   988,    -1,   994,    -1,    -1,    -1,   994,    -1,
     988,    -1,    -1,    -1,    -1,   988,   988,    -1,    -1,    -1,
     988,  1011,    -1,    -1,    -1,  1011,   994,   988,    -1,    -1,
      -1,    -1,    -1,   988,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1011,    -1,    -1,    -1,    -1,   988,    -1,
      -1,    -1,    -1,    -1,   994,    -1,    -1,   988,    -1,    -1,
      -1,   988,    -1,    -1,    -1,    -1,    -1,   994,    -1,    -1,
      -1,  1011
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
      76,    77,    79,    93,    96,   103,   111,   112,   115,   200,
     209,   210,   211,   212,   213,   214,   215,   216,   225,   227,
     229,   262,   268,   274,   280,   282,   296,   306,   331,   339,
     365,   395,   397,   446,   458,   470,   471,   479,    12,    13,
     200,   220,   221,   222,   224,   395,   397,    54,    56,    64,
      65,    66,    67,    68,    69,    80,    83,    84,    91,   200,
     211,   212,   213,   214,   314,   315,   316,   318,   320,   322,
     324,   326,   329,   330,   365,   383,   395,   397,   399,   416,
     441,    55,   200,   322,   324,   365,   391,   392,   393,   395,
     397,    57,    58,    59,    60,    61,   200,   322,   324,   365,
     395,   397,   407,   408,   409,   411,   412,   414,   415,    79,
      85,    86,    87,    88,    89,    90,   200,   365,   395,   397,
     424,   425,   426,   427,   429,   431,   433,   435,   437,   439,
     339,    17,    45,    47,    48,    51,    52,    53,   200,   247,
     349,   350,   351,   352,   353,   354,   355,   357,   359,   361,
     362,   364,   395,   397,    46,    49,    50,   200,   247,   353,
     359,   373,   374,   375,   376,   377,   379,   380,   381,   382,
     395,   397,    94,    95,   200,   290,   291,   292,   294,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   137,   138,   200,   395,   397,   483,   484,
     485,   486,   488,   490,   491,   493,   494,   495,   498,   500,
     501,   502,   503,   506,   508,   510,   140,   522,   523,   524,
       6,     3,     4,     8,     3,   206,   519,   513,   515,   517,
       4,     3,     8,   217,   226,   228,   230,     4,     4,     4,
       4,     4,   307,   340,   366,   396,   398,   332,   269,   281,
     275,   263,   447,   283,   297,   459,     4,   472,   480,     3,
       8,   223,     4,     3,     8,   384,   400,   317,   319,   321,
       4,     4,   327,   325,   323,   417,   442,     3,     8,   394,
       3,     8,   410,     4,   413,     4,     4,     3,     8,   440,
     428,   430,   432,   434,   436,   438,     8,     3,     8,   356,
     248,     4,   360,   358,   363,     4,     8,     3,   378,     4,
       4,     8,     3,   293,   295,     3,     8,     4,   487,   489,
       4,   492,     4,     4,   496,   499,     4,     4,     4,   504,
     507,   509,   511,     3,     8,   525,     3,     8,   185,   185,
     165,     4,     4,     4,     4,     4,   204,     4,     4,     4,
       4,   166,   166,   166,   166,   166,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     166,     4,     4,   210,     4,   168,   221,     4,     4,     4,
       4,     4,   166,   168,     4,     4,     4,     4,     4,   315,
       4,   392,     4,   166,     4,   166,   166,   408,     4,     4,
       4,     4,     4,     4,     4,   426,     4,     4,   166,     4,
       4,     4,   168,   351,     4,   168,   168,   375,     4,     4,
     291,   168,     4,     4,   166,     4,   166,   166,     4,     4,
     168,   168,   168,     4,     4,     4,     4,   484,     4,   523,
       4,     7,     7,   185,   185,   185,     7,     7,     7,     5,
       5,     5,     5,   187,   189,   165,     5,     5,     5,     5,
       7,     5,     5,     7,     7,     7,     7,     5,   196,     5,
       5,   165,   165,   165,    70,    71,    72,   328,   196,   165,
       5,     7,   165,   165,   165,   196,   196,   196,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   185,
     165,   165,   165,   130,   131,   497,   132,   133,   134,   135,
     136,   168,   505,   165,   165,   165,     5,   185,   209,   522,
     220,    17,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   200,   235,   236,
     237,   240,   242,   244,   246,   247,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   259,   260,   235,     7,   231,
     232,   233,     7,   308,   309,   310,     7,   343,   344,   345,
       7,   367,   368,   369,     7,   333,   334,   335,    87,   165,
     270,   271,   272,   273,   194,    88,    90,   272,   276,   277,
     278,   279,    78,   264,   265,   266,     7,   448,   449,     7,
     284,   285,   286,    97,    98,    99,   100,   101,   102,   298,
     299,   300,   301,   302,   303,   304,   305,    17,   107,   108,
     109,   110,   200,   249,   395,   397,   460,   461,   462,   465,
     466,   468,   469,   113,   114,   200,   395,   397,   473,   474,
     475,   477,   483,   197,     7,   385,   386,   387,     7,   401,
     402,   403,     7,   418,   419,   420,    92,   427,   443,   444,
       7,   526,   527,     8,     8,     8,   238,   241,   243,   245,
       4,     4,     4,     4,     4,   258,     4,     4,   261,     4,
       4,     4,     3,     8,     8,   234,     6,     3,   311,     6,
       3,   346,     6,     3,   370,     6,     3,   336,     6,     3,
       3,     6,     6,     3,     6,   267,     3,     8,   450,     3,
       6,   287,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   463,   467,     4,     4,     4,     3,     8,   476,
     478,     3,     8,     8,   165,   198,   199,   388,     6,     3,
     404,     6,     3,   421,     6,     3,   445,     8,   528,     3,
       6,     4,     4,     4,     4,   166,   168,   166,   168,   166,
       4,   166,   166,     4,   166,   166,   168,   236,   235,   233,
     314,   310,   349,   345,   373,   369,   200,   211,   212,   213,
     214,   247,   306,   318,   320,   322,   324,   326,   330,   337,
     338,   365,   395,   397,   441,   335,   271,   277,     4,   265,
      81,    82,   200,   247,   365,   395,   397,   451,   452,   453,
     454,   455,   457,   449,   290,   286,   166,   166,   166,   166,
     166,   166,   299,     4,     4,   166,   166,   166,   461,     4,
       4,   474,     6,     3,   391,   387,   407,   403,   424,   420,
       4,   141,   143,   144,   200,   247,   395,   397,   529,   530,
     531,   532,   534,   527,    18,    19,    20,    21,   239,   165,
     165,   165,   165,   165,     8,     8,     8,     8,     3,     8,
     165,   456,     4,     8,     3,     8,   104,   105,   106,   464,
     165,   165,   165,   165,     8,     8,     8,   165,   535,     4,
     533,     3,     8,   338,     4,   168,   453,     4,   166,     4,
     530,   165,     5,   165,     7,   536,   537,   538,     3,     6,
     142,   145,   146,   147,   539,   540,   541,   543,   544,   545,
     537,   542,     4,     4,     4,     3,     8,     4,   168,   166,
     166,   540,   165
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
     210,   211,   212,   213,   214,   215,   217,   216,   219,   218,
     220,   220,   221,   221,   221,   221,   221,   223,   222,   224,
     226,   225,   228,   227,   230,   229,   231,   231,   232,   232,
     234,   233,   235,   235,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   238,   237,   239,   239,   239,   239,   241,   240,
     243,   242,   245,   244,   246,   248,   247,   249,   250,   251,
     252,   253,   254,   255,   256,   258,   257,   259,   261,   260,
     263,   262,   264,   264,   265,   267,   266,   269,   268,   270,
     270,   271,   271,   272,   273,   275,   274,   276,   276,   277,
     277,   277,   278,   279,   281,   280,   283,   282,   284,   284,
     285,   285,   287,   286,   289,   288,   290,   290,   290,   291,
     291,   293,   292,   295,   294,   297,   296,   298,   298,   299,
     299,   299,   299,   299,   299,   300,   301,   302,   303,   304,
     305,   307,   306,   308,   308,   309,   309,   311,   310,   313,
     312,   314,   314,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   317,   316,   319,   318,   321,   320,   323,
     322,   325,   324,   327,   326,   328,   328,   328,   329,   330,
     332,   331,   333,   333,   334,   334,   336,   335,   337,   337,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   340,   339,   342,
     341,   343,   343,   344,   344,   346,   345,   348,   347,   349,
     349,   350,   350,   351,   351,   351,   351,   351,   351,   351,
     351,   351,   351,   352,   353,   354,   356,   355,   358,   357,
     360,   359,   361,   363,   362,   364,   366,   365,   367,   367,
     368,   368,   370,   369,   372,   371,   373,   373,   374,   374,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   376,
     378,   377,   379,   380,   381,   382,   384,   383,   385,   385,
     386,   386,   388,   387,   390,   389,   391,   391,   392,   392,
     392,   392,   392,   392,   392,   394,   393,   396,   395,   398,
     397,   400,   399,   401,   401,   402,   402,   404,   403,   406,
     405,   407,   407,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   410,   409,   411,   413,   412,   414,
     415,   417,   416,   418,   418,   419,   419,   421,   420,   423,
     422,   424,   424,   425,   425,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   428,   427,   430,   429,
     432,   431,   434,   433,   436,   435,   438,   437,   440,   439,
     442,   441,   443,   443,   445,   444,   447,   446,   448,   448,
     450,   449,   451,   451,   452,   452,   453,   453,   453,   453,
     453,   453,   453,   454,   456,   455,   457,   459,   458,   460,
     460,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     463,   462,   464,   464,   464,   465,   467,   466,   468,   469,
     470,   472,   471,   473,   473,   474,   474,   474,   474,   474,
     476,   475,   478,   477,   480,   479,   482,   481,   483,   483,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   485,
     487,   486,   489,   488,   490,   492,   491,   493,   494,   496,
     495,   497,   497,   499,   498,   500,   501,   502,   504,   503,
     505,   505,   505,   505,   505,   507,   506,   509,   508,   511,
     510,   513,   512,   515,   514,   517,   516,   519,   518,   521,
     520,   522,   522,   523,   525,   524,   526,   526,   528,   527,
     529,   529,   530,   530,   530,   530,   530,   530,   530,   531,
     533,   532,   535,   534,   536,   536,   538,   537,   539,   539,
     540,   540,   540,   540,   542,   541,   543,   544,   545
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
       1,     3,     3,     3,     3,     3,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     6,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
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
     457,   460,   465,   470,   475,   480,   485,   485,   496,   496,
     505,   506,   509,   510,   511,   512,   513,   516,   516,   526,
     532,   532,   544,   544,   556,   556,   566,   567,   570,   571,
     574,   574,   584,   585,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   608,   608,   615,   616,   617,   618,   621,   621,
     629,   629,   637,   637,   645,   650,   650,   658,   663,   668,
     673,   678,   683,   688,   693,   698,   698,   706,   711,   711,
     719,   719,   729,   730,   732,   734,   734,   752,   752,   762,
     763,   766,   767,   770,   775,   780,   780,   790,   791,   794,
     795,   796,   799,   804,   811,   811,   821,   821,   831,   832,
     835,   836,   839,   839,   849,   849,   859,   860,   861,   864,
     865,   868,   868,   876,   876,   884,   884,   895,   896,   899,
     900,   901,   902,   903,   904,   907,   912,   917,   922,   927,
     932,   940,   940,   953,   954,   957,   958,   965,   965,   991,
     991,  1002,  1003,  1007,  1008,  1009,  1010,  1011,  1012,  1013,
    1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,
    1024,  1025,  1026,  1029,  1029,  1037,  1037,  1045,  1045,  1053,
    1053,  1061,  1061,  1071,  1071,  1078,  1079,  1080,  1083,  1088,
    1096,  1096,  1107,  1108,  1112,  1113,  1116,  1116,  1124,  1125,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1151,  1151,  1164,
    1164,  1173,  1174,  1177,  1178,  1183,  1183,  1198,  1198,  1212,
    1213,  1216,  1217,  1220,  1221,  1222,  1223,  1224,  1225,  1226,
    1227,  1228,  1229,  1232,  1234,  1239,  1241,  1241,  1249,  1249,
    1257,  1257,  1265,  1267,  1267,  1275,  1284,  1284,  1296,  1297,
    1302,  1303,  1308,  1308,  1320,  1320,  1332,  1333,  1338,  1339,
    1344,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1355,
    1357,  1357,  1365,  1367,  1369,  1374,  1382,  1382,  1394,  1395,
    1398,  1399,  1402,  1402,  1412,  1412,  1421,  1422,  1425,  1426,
    1427,  1428,  1429,  1430,  1431,  1434,  1434,  1442,  1442,  1467,
    1467,  1497,  1497,  1509,  1510,  1513,  1514,  1517,  1517,  1529,
    1529,  1541,  1542,  1545,  1546,  1547,  1548,  1549,  1550,  1551,
    1552,  1553,  1554,  1555,  1558,  1558,  1566,  1571,  1571,  1579,
    1584,  1592,  1592,  1602,  1603,  1606,  1607,  1610,  1610,  1619,
    1619,  1628,  1629,  1632,  1633,  1637,  1638,  1639,  1640,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1650,  1650,  1660,  1660,
    1670,  1670,  1678,  1678,  1686,  1686,  1694,  1694,  1702,  1702,
    1715,  1715,  1725,  1726,  1729,  1729,  1740,  1740,  1750,  1751,
    1754,  1754,  1764,  1765,  1768,  1769,  1772,  1773,  1774,  1775,
    1776,  1777,  1778,  1781,  1783,  1783,  1791,  1799,  1799,  1811,
    1812,  1815,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,
    1826,  1826,  1833,  1834,  1835,  1838,  1843,  1843,  1851,  1856,
    1863,  1870,  1870,  1880,  1881,  1884,  1885,  1886,  1887,  1888,
    1891,  1891,  1899,  1899,  1909,  1909,  1921,  1921,  1931,  1932,
    1935,  1936,  1937,  1938,  1939,  1940,  1941,  1942,  1943,  1944,
    1945,  1946,  1947,  1948,  1949,  1950,  1951,  1952,  1953,  1956,
    1961,  1961,  1969,  1969,  1977,  1982,  1982,  1990,  1995,  2000,
    2000,  2008,  2009,  2012,  2012,  2020,  2025,  2030,  2035,  2035,
    2043,  2046,  2049,  2052,  2055,  2061,  2061,  2069,  2069,  2077,
    2077,  2087,  2087,  2094,  2094,  2101,  2101,  2114,  2114,  2124,
    2124,  2135,  2136,  2140,  2144,  2144,  2156,  2157,  2161,  2161,
    2169,  2170,  2173,  2174,  2175,  2176,  2177,  2178,  2179,  2182,
    2187,  2187,  2195,  2195,  2205,  2206,  2209,  2209,  2217,  2218,
    2221,  2222,  2223,  2224,  2227,  2227,  2235,  2240,  2245
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
#line 4852 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2250 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
