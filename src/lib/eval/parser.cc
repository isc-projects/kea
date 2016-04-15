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


// First part of user declarations.

#line 37 "parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.h"

// User implementation prologue.

#line 51 "parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 32 "parser.yy" // lalr1.cc:413

# include "eval_context.h"

#line 57 "parser.cc" // lalr1.cc:413


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
#if YYDEBUG

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

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.yy" // lalr1.cc:479
namespace isc { namespace eval {
#line 143 "parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  EvalParser::yytnamerr_ (const char *yystr)
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
  EvalParser::EvalParser (EvalContext& ctx_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  EvalParser::~EvalParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  EvalParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  EvalParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  EvalParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  EvalParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  EvalParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  EvalParser::symbol_number_type
  EvalParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  EvalParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  EvalParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 37: // option_repr_type
        value.move< TokenOption::RepresentationType > (that.value);
        break;

      case 42: // pkt6_field
        value.move< TokenPkt6::FieldType > (that.value);
        break;

      case 40: // relay6_field
        value.move< TokenRelay6Field::FieldType > (that.value);
        break;

      case 27: // "constant string"
      case 28: // "integer"
      case 29: // "constant hexstring"
      case 30: // "option name"
      case 31: // "ip address"
        value.move< std::string > (that.value);
        break;

      case 36: // option_code
        value.move< uint16_t > (that.value);
        break;

      case 41: // nest_level
        value.move< uint8_t > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  EvalParser::stack_symbol_type&
  EvalParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 37: // option_repr_type
        value.copy< TokenOption::RepresentationType > (that.value);
        break;

      case 42: // pkt6_field
        value.copy< TokenPkt6::FieldType > (that.value);
        break;

      case 40: // relay6_field
        value.copy< TokenRelay6Field::FieldType > (that.value);
        break;

      case 27: // "constant string"
      case 28: // "integer"
      case 29: // "constant hexstring"
      case 30: // "option name"
      case 31: // "ip address"
        value.copy< std::string > (that.value);
        break;

      case 36: // option_code
        value.copy< uint16_t > (that.value);
        break;

      case 41: // nest_level
        value.copy< uint8_t > (that.value);
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
  EvalParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  EvalParser::yy_print_ (std::ostream& yyo,
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
            case 27: // "constant string"

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "parser.cc" // lalr1.cc:636
        break;

      case 28: // "integer"

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 373 "parser.cc" // lalr1.cc:636
        break;

      case 29: // "constant hexstring"

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 380 "parser.cc" // lalr1.cc:636
        break;

      case 30: // "option name"

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 387 "parser.cc" // lalr1.cc:636
        break;

      case 31: // "ip address"

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 394 "parser.cc" // lalr1.cc:636
        break;

      case 36: // option_code

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint16_t > (); }
#line 401 "parser.cc" // lalr1.cc:636
        break;

      case 37: // option_repr_type

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenOption::RepresentationType > (); }
#line 408 "parser.cc" // lalr1.cc:636
        break;

      case 40: // relay6_field

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenRelay6Field::FieldType > (); }
#line 415 "parser.cc" // lalr1.cc:636
        break;

      case 41: // nest_level

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint8_t > (); }
#line 422 "parser.cc" // lalr1.cc:636
        break;

      case 42: // pkt6_field

#line 82 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenPkt6::FieldType > (); }
#line 429 "parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  EvalParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  EvalParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  EvalParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  EvalParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  EvalParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  EvalParser::debug_level_type
  EvalParser::debug_level () const
  {
    return yydebug_;
  }

  void
  EvalParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline EvalParser::state_type
  EvalParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  EvalParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  EvalParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  EvalParser::parse ()
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
      case 37: // option_repr_type
        yylhs.value.build< TokenOption::RepresentationType > ();
        break;

      case 42: // pkt6_field
        yylhs.value.build< TokenPkt6::FieldType > ();
        break;

      case 40: // relay6_field
        yylhs.value.build< TokenRelay6Field::FieldType > ();
        break;

      case 27: // "constant string"
      case 28: // "integer"
      case 29: // "constant hexstring"
      case 30: // "option name"
      case 31: // "ip address"
        yylhs.value.build< std::string > ();
        break;

      case 36: // option_code
        yylhs.value.build< uint16_t > ();
        break;

      case 41: // nest_level
        yylhs.value.build< uint8_t > ();
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
  case 4:
#line 96 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 680 "parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 101 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 689 "parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 106 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 698 "parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 111 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 707 "parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 116 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as< uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 716 "parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 121 "parser.yy" // lalr1.cc:859
    {
                   switch (ctx.getUniverse()) {
                   case Option::V4:
                   {
                       TokenPtr opt(new TokenRelay4Option(yystack_[3].value.as< uint16_t > (), TokenOption::EXISTS));
                       ctx.expression.push_back(opt);
                       break;
                   }
                   case Option::V6:
                       // We will have relay6[123] for the DHCPv6.
                       // In a very distant future we'll possibly be able
                       // to mix both if we have DHCPv4-over-DHCPv6, so it
                       // has some sense to make it explicit whether we
                       // talk about DHCPv4 relay or DHCPv6 relay. However,
                       // for the time being relay4 can be used in DHCPv4
                       // only.
                       error(yystack_[5].location, "relay4 can only be used in DHCPv4.");
                   }
                }
#line 740 "parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 141 "parser.yy" // lalr1.cc:859
    {
                    switch (ctx.getUniverse()) {
                    case Option::V6:
                    {
                        TokenPtr opt(new TokenRelay6Option(yystack_[8].value.as< uint8_t > (), yystack_[3].value.as< uint16_t > (), TokenOption::EXISTS));
                        ctx.expression.push_back(opt);
                        break;
                    }
                    case Option::V4:
                        // For now we only use relay6 in DHCPv6.
                        error(yystack_[10].location, "relay6 can only be used in DHCPv6.");
                    }
                }
#line 758 "parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 157 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 767 "parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 162 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 776 "parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 167 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 785 "parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 172 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as< uint16_t > (), yystack_[0].value.as< TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 794 "parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 177 "parser.yy" // lalr1.cc:859
    {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr opt(new TokenRelay4Option(yystack_[3].value.as< uint16_t > (), yystack_[0].value.as< TokenOption::RepresentationType > ()));
                         ctx.expression.push_back(opt);
                         break;
                     }
                     case Option::V6:
                         // We will have relay6[123] for the DHCPv6.
                         // In a very distant future we'll possibly be able
                         // to mix both if we have DHCPv4-over-DHCPv6, so it
                         // has some sense to make it explicit whether we
                         // talk about DHCPv4 relay or DHCPv6 relay. However,
                         // for the time being relay4 can be used in DHCPv4
                         // only.
                         error(yystack_[5].location, "relay4 can only be used in DHCPv4.");
                     }
                  }
#line 818 "parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 198 "parser.yy" // lalr1.cc:859
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr opt(new TokenRelay6Option(yystack_[8].value.as< uint8_t > (), yystack_[3].value.as< uint16_t > (), yystack_[0].value.as< TokenOption::RepresentationType > ()));
                         ctx.expression.push_back(opt);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[10].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 836 "parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 213 "parser.yy" // lalr1.cc:859
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr relay6field(new TokenRelay6Field(yystack_[3].value.as< uint8_t > (), yystack_[0].value.as< TokenRelay6Field::FieldType > ()));
                         ctx.expression.push_back(relay6field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[5].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 854 "parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 229 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 863 "parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 234 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 872 "parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 239 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr pkt6_field(new TokenPkt6(yystack_[0].value.as< TokenPkt6::FieldType > ()));
                      ctx.expression.push_back(pkt6_field);
                  }
#line 881 "parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 246 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 889 "parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 250 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< uint16_t > () = ctx.convertOptionName(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 897 "parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 256 "parser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 905 "parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 260 "parser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 913 "parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 266 "parser.yy" // lalr1.cc:859
    {
                     TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 922 "parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 273 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 931 "parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 278 "parser.yy" // lalr1.cc:859
    {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 940 "parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 284 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR; }
#line 946 "parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 285 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR; }
#line 952 "parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 289 "parser.yy" // lalr1.cc:859
    {
		 yylhs.value.as< uint8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 960 "parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 297 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE; }
#line 966 "parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 298 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenPkt6::FieldType > () = TokenPkt6::TRANSID; }
#line 972 "parser.cc" // lalr1.cc:859
    break;


#line 976 "parser.cc" // lalr1.cc:859
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
  EvalParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  EvalParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char EvalParser::yypact_ninf_ = -54;

  const signed char EvalParser::yytable_ninf_ = -1;

  const signed char
  EvalParser::yypact_[] =
  {
      29,    29,    29,   -12,    -4,     7,    21,    30,    32,   -54,
     -54,   -54,    13,    10,    46,    16,   -54,    -3,    -3,     9,
      52,    52,    42,   -54,    29,    29,    52,   -54,   -54,   -54,
      40,    54,   -54,    56,    43,    59,    60,    55,    58,   -54,
     -54,   -54,   -54,    72,   -54,    66,    68,    69,    -3,    -3,
       9,    61,    52,    25,    28,    -1,    71,    73,    75,   -54,
      65,    87,   -54,   -54,   -54,   -54,   -54,   -54,    78,   -54,
     -54,   -54,    77,    79,    80,   -14,   -54,    -3,    33,    33,
       6,   -54,   -54,    90,    82,    84,   -54,    83,    -3,    47,
      85,   -54,   -54,    86,    33
  };

  const unsigned char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
      12,    13,     0,     2,     0,     0,     4,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     0,     3,    21,    22,
       0,     0,    30,     0,     0,     0,     0,     0,     0,    31,
      32,    20,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
       0,     0,    23,    24,     8,    14,     9,    15,     0,    28,
      29,    17,     0,     0,     0,     0,    19,     0,     0,     0,
       0,    27,    26,     0,     0,     0,    18,     0,     0,     0,
       0,    10,    16,     0,     0
  };

  const signed char
  EvalParser::yypgoto_[] =
  {
     -54,   -54,     4,   -17,   -18,   -53,   -54,   -54,   -54,    51,
     -54
  };

  const signed char
  EvalParser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    30,    65,    60,    83,    71,    33,
      41
  };

  const unsigned char
  EvalParser::yytable_[] =
  {
      31,    67,    17,    37,    38,    15,    16,    81,    68,    44,
      18,    69,    70,    23,    82,    85,    24,    25,    69,    70,
      27,    19,    24,    25,    20,    28,    67,    29,    42,    43,
      56,    57,     1,    21,     2,    61,    92,    32,     3,     4,
       5,    92,    62,    63,    64,    62,    63,    66,    22,     6,
      62,    63,     7,     8,    26,    45,     9,    48,    10,    84,
      11,    34,    35,    36,    62,    63,    91,    39,    40,    46,
      90,    47,     6,    49,    50,     7,     8,    51,    24,     9,
      52,    10,    53,    11,    54,    55,    72,    75,    73,    59,
      74,    76,    77,    78,    86,    79,    80,    87,    88,    89,
      93,    58,    94
  };

  const unsigned char
  EvalParser::yycheck_[] =
  {
      18,    54,    14,    20,    21,     1,     2,    21,     9,    26,
      14,    12,    13,     0,    28,     9,     6,     7,    12,    13,
       4,    14,     6,     7,     3,    28,    79,    30,    24,    25,
      48,    49,     3,     3,     5,    52,    89,    28,     9,    10,
      11,    94,    17,    18,    19,    17,    18,    19,    16,    20,
      17,    18,    23,    24,     8,    15,    27,    14,    29,    77,
      31,     9,    10,    11,    17,    18,    19,    25,    26,    15,
      88,    15,    20,    14,    14,    23,    24,    22,     6,    27,
      22,    29,    16,    31,    16,    16,    15,    22,    15,    28,
      15,     4,    14,    16,     4,    16,    16,    15,    14,    16,
      15,    50,    16
  };

  const unsigned char
  EvalParser::yystos_[] =
  {
       0,     3,     5,     9,    10,    11,    20,    23,    24,    27,
      29,    31,    33,    34,    35,    34,    34,    14,    14,    14,
       3,     3,    16,     0,     6,     7,     8,     4,    28,    30,
      36,    36,    28,    41,     9,    10,    11,    35,    35,    25,
      26,    42,    34,    34,    35,    15,    15,    15,    14,    14,
      14,    22,    22,    16,    16,    16,    36,    36,    41,    28,
      38,    35,    17,    18,    19,    37,    19,    37,     9,    12,
      13,    40,    15,    15,    15,    22,     4,    14,    16,    16,
      16,    21,    28,    39,    36,     9,     4,    15,    14,    16,
      36,    19,    37,    15,    16
  };

  const unsigned char
  EvalParser::yyr1_[] =
  {
       0,    32,    33,    34,    34,    34,    34,    34,    34,    34,
      34,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    36,    36,    37,    37,    38,    39,    39,    40,    40,
      41,    42,    42
  };

  const unsigned char
  EvalParser::yyr2_[] =
  {
       0,     2,     1,     3,     2,     3,     3,     3,     6,     6,
      11,     1,     1,     1,     6,     6,    11,     6,     8,     6,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const EvalParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"(\"", "\")\"", "\"not\"",
  "\"and\"", "\"or\"", "\"==\"", "\"option\"", "\"relay4\"", "\"relay6\"",
  "\"peeraddr\"", "\"linkaddr\"", "\"[\"", "\"]\"", "\".\"", "\"text\"",
  "\"hex\"", "\"exists\"", "\"substring\"", "\"all\"", "\",\"",
  "\"concat\"", "\"pkt6\"", "\"msgtype\"", "\"transid\"",
  "\"constant string\"", "\"integer\"", "\"constant hexstring\"",
  "\"option name\"", "\"ip address\"", "$accept", "expression",
  "bool_expr", "string_expr", "option_code", "option_repr_type",
  "start_expr", "length_expr", "relay6_field", "nest_level", "pkt6_field", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  EvalParser::yyrline_[] =
  {
       0,    91,    91,    94,    95,   100,   105,   110,   115,   120,
     140,   156,   161,   166,   171,   176,   197,   212,   228,   233,
     238,   245,   249,   255,   259,   265,   272,   277,   284,   285,
     288,   297,   298
  };

  // Print the state stack on the debug stream.
  void
  EvalParser::yystack_print_ ()
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
  EvalParser::yy_reduce_print_ (int yyrule)
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
#endif // YYDEBUG


#line 13 "parser.yy" // lalr1.cc:1167
} } // isc::eval
#line 1404 "parser.cc" // lalr1.cc:1167
#line 301 "parser.yy" // lalr1.cc:1168

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
