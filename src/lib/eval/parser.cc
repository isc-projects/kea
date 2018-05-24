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
#define yylex   evallex

// First part of user declarations.

#line 39 "parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.h"

// User implementation prologue.

#line 53 "parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 33 "parser.yy" // lalr1.cc:413

# include "eval_context.h"

#line 59 "parser.cc" // lalr1.cc:413


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
#if EVALDEBUG

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

#else // !EVALDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !EVALDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "parser.yy" // lalr1.cc:479
namespace isc { namespace eval {
#line 145 "parser.cc" // lalr1.cc:479

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
#if EVALDEBUG
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
      case 61: // option_repr_type
        value.move< TokenOption::RepresentationType > (that.value);
        break;

      case 65: // pkt4_field
        value.move< TokenPkt4::FieldType > (that.value);
        break;

      case 66: // pkt6_field
        value.move< TokenPkt6::FieldType > (that.value);
        break;

      case 63: // pkt_metadata
        value.move< TokenPkt::MetadataType > (that.value);
        break;

      case 67: // relay6_field
        value.move< TokenRelay6Field::FieldType > (that.value);
        break;

      case 62: // nest_level
        value.move< int8_t > (that.value);
        break;

      case 49: // "constant string"
      case 50: // "integer"
      case 51: // "constant hexstring"
      case 52: // "option name"
      case 53: // "ip address"
        value.move< std::string > (that.value);
        break;

      case 60: // option_code
        value.move< uint16_t > (that.value);
        break;

      case 59: // integer_expr
      case 64: // enterprise_id
        value.move< uint32_t > (that.value);
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
      case 61: // option_repr_type
        value.copy< TokenOption::RepresentationType > (that.value);
        break;

      case 65: // pkt4_field
        value.copy< TokenPkt4::FieldType > (that.value);
        break;

      case 66: // pkt6_field
        value.copy< TokenPkt6::FieldType > (that.value);
        break;

      case 63: // pkt_metadata
        value.copy< TokenPkt::MetadataType > (that.value);
        break;

      case 67: // relay6_field
        value.copy< TokenRelay6Field::FieldType > (that.value);
        break;

      case 62: // nest_level
        value.copy< int8_t > (that.value);
        break;

      case 49: // "constant string"
      case 50: // "integer"
      case 51: // "constant hexstring"
      case 52: // "option name"
      case 53: // "ip address"
        value.copy< std::string > (that.value);
        break;

      case 60: // option_code
        value.copy< uint16_t > (that.value);
        break;

      case 59: // integer_expr
      case 64: // enterprise_id
        value.copy< uint32_t > (that.value);
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

#if EVALDEBUG
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
            case 49: // "constant string"

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 394 "parser.cc" // lalr1.cc:636
        break;

      case 50: // "integer"

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 401 "parser.cc" // lalr1.cc:636
        break;

      case 51: // "constant hexstring"

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 408 "parser.cc" // lalr1.cc:636
        break;

      case 52: // "option name"

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 415 "parser.cc" // lalr1.cc:636
        break;

      case 53: // "ip address"

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 422 "parser.cc" // lalr1.cc:636
        break;

      case 59: // integer_expr

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint32_t > (); }
#line 429 "parser.cc" // lalr1.cc:636
        break;

      case 60: // option_code

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint16_t > (); }
#line 436 "parser.cc" // lalr1.cc:636
        break;

      case 61: // option_repr_type

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenOption::RepresentationType > (); }
#line 443 "parser.cc" // lalr1.cc:636
        break;

      case 62: // nest_level

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int8_t > (); }
#line 450 "parser.cc" // lalr1.cc:636
        break;

      case 63: // pkt_metadata

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenPkt::MetadataType > (); }
#line 457 "parser.cc" // lalr1.cc:636
        break;

      case 64: // enterprise_id

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint32_t > (); }
#line 464 "parser.cc" // lalr1.cc:636
        break;

      case 65: // pkt4_field

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenPkt4::FieldType > (); }
#line 471 "parser.cc" // lalr1.cc:636
        break;

      case 66: // pkt6_field

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenPkt6::FieldType > (); }
#line 478 "parser.cc" // lalr1.cc:636
        break;

      case 67: // relay6_field

#line 110 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenRelay6Field::FieldType > (); }
#line 485 "parser.cc" // lalr1.cc:636
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

#if EVALDEBUG
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
#endif // EVALDEBUG

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
      case 61: // option_repr_type
        yylhs.value.build< TokenOption::RepresentationType > ();
        break;

      case 65: // pkt4_field
        yylhs.value.build< TokenPkt4::FieldType > ();
        break;

      case 66: // pkt6_field
        yylhs.value.build< TokenPkt6::FieldType > ();
        break;

      case 63: // pkt_metadata
        yylhs.value.build< TokenPkt::MetadataType > ();
        break;

      case 67: // relay6_field
        yylhs.value.build< TokenRelay6Field::FieldType > ();
        break;

      case 62: // nest_level
        yylhs.value.build< int8_t > ();
        break;

      case 49: // "constant string"
      case 50: // "integer"
      case 51: // "constant hexstring"
      case 52: // "option name"
      case 53: // "ip address"
        yylhs.value.build< std::string > ();
        break;

      case 60: // option_code
        yylhs.value.build< uint16_t > ();
        break;

      case 59: // integer_expr
      case 64: // enterprise_id
        yylhs.value.build< uint32_t > ();
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
  case 6:
#line 130 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 749 "parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 135 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 758 "parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 140 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 767 "parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 145 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 776 "parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 150 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as< uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 785 "parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 155 "parser.yy" // lalr1.cc:859
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
#line 809 "parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 175 "parser.yy" // lalr1.cc:859
    {
                    switch (ctx.getUniverse()) {
                    case Option::V6:
                    {
                        TokenPtr opt(new TokenRelay6Option(yystack_[8].value.as< int8_t > (), yystack_[3].value.as< uint16_t > (), TokenOption::EXISTS));
                        ctx.expression.push_back(opt);
                        break;
                    }
                    case Option::V4:
                        // For now we only use relay6 in DHCPv6.
                        error(yystack_[10].location, "relay6 can only be used in DHCPv6.");
                    }
                }
#line 827 "parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 189 "parser.yy" // lalr1.cc:859
    {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as< uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 840 "parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 198 "parser.yy" // lalr1.cc:859
    {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as< uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 853 "parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 207 "parser.yy" // lalr1.cc:859
    {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as< uint32_t > (), TokenOption::EXISTS, yystack_[3].value.as< uint16_t > ()));
                  ctx.expression.push_back(exist);
               }
#line 867 "parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 217 "parser.yy" // lalr1.cc:859
    {
                  // Expression member('foo')
                  //
                  // This token will check if the packet is a member of
                  // the specified client class.
                  // To avoid loops at evaluation only already defined and
                  // built-in classes are allowed.
                  std::string cc = yystack_[1].value.as< std::string > ();
                  if (!ctx.isClientClassDefined(cc)) {
                      error(yystack_[1].location, "Not defined client class '" + cc + "'");
                  }
                  TokenPtr member(new TokenMember(cc));
                  ctx.expression.push_back(member);
              }
#line 886 "parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 234 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 895 "parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 239 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 904 "parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 244 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 913 "parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 249 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as< uint16_t > (), yystack_[0].value.as< TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 922 "parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 254 "parser.yy" // lalr1.cc:859
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
#line 946 "parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 275 "parser.yy" // lalr1.cc:859
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr opt(new TokenRelay6Option(yystack_[8].value.as< int8_t > (), yystack_[3].value.as< uint16_t > (), yystack_[0].value.as< TokenOption::RepresentationType > ()));
                         ctx.expression.push_back(opt);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[10].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 964 "parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 290 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr pkt_metadata(new TokenPkt(yystack_[0].value.as< TokenPkt::MetadataType > ()));
                      ctx.expression.push_back(pkt_metadata);
                  }
#line 973 "parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 295 "parser.yy" // lalr1.cc:859
    {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr pkt4_field(new TokenPkt4(yystack_[0].value.as< TokenPkt4::FieldType > ()));
                         ctx.expression.push_back(pkt4_field);
                         break;
                     }
                     case Option::V6:
                         // For now we only use pkt4 in DHCPv4.
                         error(yystack_[2].location, "pkt4 can only be used in DHCPv4.");
                     }
                  }
#line 991 "parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 309 "parser.yy" // lalr1.cc:859
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr pkt6_field(new TokenPkt6(yystack_[0].value.as< TokenPkt6::FieldType > ()));
                         ctx.expression.push_back(pkt6_field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use pkt6 in DHCPv6.
                         error(yystack_[2].location, "pkt6 can only be used in DHCPv6.");
                     }
                  }
#line 1009 "parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 323 "parser.yy" // lalr1.cc:859
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr relay6field(new TokenRelay6Field(yystack_[3].value.as< int8_t > (), yystack_[0].value.as< TokenRelay6Field::FieldType > ()));
                         ctx.expression.push_back(relay6field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[5].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 1027 "parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 338 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 1036 "parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 343 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1045 "parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 348 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression.push_back(cond);
                  }
#line 1054 "parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 353 "parser.yy" // lalr1.cc:859
    {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1067 "parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 362 "parser.yy" // lalr1.cc:859
    {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1081 "parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 372 "parser.yy" // lalr1.cc:859
    {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as< uint32_t > (), yystack_[0].value.as< TokenOption::RepresentationType > (), yystack_[3].value.as< uint16_t > ()));
                    ctx.expression.push_back(opt);
                }
#line 1094 "parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 381 "parser.yy" // lalr1.cc:859
    {
                    // expression: vendor-class[1234].data
                    //
                    // Vendor class option does not have suboptions,
                    // but chunks of data (typically 1, but the option
                    // structure allows multiple of them). If chunk
                    // offset is not specified, we assume the first (0th)
                    // is requested.
                    TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as< uint32_t > (),
                                                               TokenVendor::DATA, 0));
                    ctx.expression.push_back(vendor_class);
                }
#line 1111 "parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 394 "parser.yy" // lalr1.cc:859
    {
                    // expression: vendor-class[1234].data[5]
                    //
                    // Vendor class option does not have suboptions,
                    // but chunks of data (typically 1, but the option
                    // structure allows multiple of them). This syntax
                    // specifies which data chunk (tuple) we want.
                    uint8_t index = ctx.convertUint8(yystack_[1].value.as< std::string > (), yystack_[1].location);
                    TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), yystack_[6].value.as< uint32_t > (),
                                                               TokenVendor::DATA, index));
                    ctx.expression.push_back(vendor_class);
                }
#line 1128 "parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 407 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr integer(new TokenInteger(yystack_[0].value.as< uint32_t > ()));
                    ctx.expression.push_back(integer);
                }
#line 1137 "parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 414 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< uint32_t > () = ctx.convertUint32(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 1145 "parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 420 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 1153 "parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 424 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< uint16_t > () = ctx.convertOptionName(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 1161 "parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 430 "parser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1169 "parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 434 "parser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1177 "parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 440 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< int8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 1185 "parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 449 "parser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< TokenPkt::MetadataType > () = TokenPkt::IFACE;
                  }
#line 1193 "parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 453 "parser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< TokenPkt::MetadataType > () = TokenPkt::SRC;
                  }
#line 1201 "parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 457 "parser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< TokenPkt::MetadataType > () = TokenPkt::DST;
                  }
#line 1209 "parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 461 "parser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< TokenPkt::MetadataType > () = TokenPkt::LEN;
                  }
#line 1217 "parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 467 "parser.yy" // lalr1.cc:859
    {
                       yylhs.value.as< uint32_t > () = ctx.convertUint32(yystack_[0].value.as< std::string > (), yystack_[0].location);
                   }
#line 1225 "parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 471 "parser.yy" // lalr1.cc:859
    {
                       yylhs.value.as< uint32_t > () = 0;
                   }
#line 1233 "parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 477 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1241 "parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 481 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1249 "parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 485 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1257 "parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 489 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1265 "parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 493 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1273 "parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 497 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1281 "parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 501 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1289 "parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 505 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::MSGTYPE;
                 }
#line 1297 "parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 509 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::TRANSID;
                 }
#line 1305 "parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 515 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE;
                 }
#line 1313 "parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 519 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< TokenPkt6::FieldType > () = TokenPkt6::TRANSID;
                 }
#line 1321 "parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 525 "parser.yy" // lalr1.cc:859
    {
                       yylhs.value.as< TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR;
                   }
#line 1329 "parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 529 "parser.yy" // lalr1.cc:859
    {
                       yylhs.value.as< TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR;
                   }
#line 1337 "parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 535 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                    ctx.expression.push_back(str);
                }
#line 1346 "parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 542 "parser.yy" // lalr1.cc:859
    {
                     TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1355 "parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 547 "parser.yy" // lalr1.cc:859
    {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 1364 "parser.cc" // lalr1.cc:859
    break;


#line 1368 "parser.cc" // lalr1.cc:859
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


  const signed char EvalParser::yypact_ninf_ = -114;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short int
  EvalParser::yypact_[] =
  {
      18,    25,    72,    32,    25,    25,    14,    26,    37,    70,
      80,    84,    99,   105,   110,   100,    33,    90,  -114,  -114,
    -114,  -114,  -114,    38,   116,  -114,   101,   121,   122,   117,
     118,  -114,  -114,    73,  -114,   -38,   -38,    89,    91,    47,
      59,    72,    72,    25,    20,   -31,    95,   -31,    96,    25,
      25,    72,   -38,   -38,    89,   -31,   -31,  -114,  -114,  -114,
     127,   128,  -114,   129,   142,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
     112,   113,    -3,  -114,  -114,  -114,  -114,  -114,   131,  -114,
     134,  -114,  -114,   145,  -114,   136,   137,   138,   139,   140,
     141,   143,   144,  -114,   107,    72,    72,   146,   147,   148,
     149,   150,   151,   152,     5,    76,    13,  -114,   123,   158,
     135,   -14,     1,    66,    66,    29,   125,   163,  -114,  -114,
    -114,  -114,  -114,  -114,   159,  -114,  -114,  -114,   -30,  -114,
      72,  -114,   160,   161,  -114,   162,   164,   -38,  -114,  -114,
     169,   174,   130,   -38,   -38,   -38,   165,  -114,  -114,   166,
     167,   168,   170,   171,  -114,   172,   173,   175,   108,   111,
      66,    66,  -114,  -114,  -114,  -114
  };

  const unsigned char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    36,
      18,    19,     2,     4,     0,    35,     0,     0,     0,     0,
       0,     3,     1,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,    37,    38,
       0,     0,    41,     0,     0,    42,    43,    44,    45,    23,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    24,
       0,     0,     0,    57,    58,    25,    47,    46,     0,    31,
       0,    30,     7,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      10,    20,    11,    21,     0,    59,    60,    26,     0,    28,
       0,    13,    33,     0,    14,     0,     0,     0,    63,    62,
       0,     0,     0,     0,     0,     0,     0,    27,    29,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     0,    12,    22,    15,    32
  };

  const short int
  EvalParser::yypgoto_[] =
  {
    -114,  -114,  -114,     4,    -2,  -114,   -35,  -113,   133,  -114,
     -40,  -114,  -114,  -114,  -114,  -114
  };

  const short int
  EvalParser::yydefgoto_[] =
  {
      -1,     3,    22,    23,    24,    25,    60,   131,    63,    69,
      88,    79,    85,   137,   118,   150
  };

  const unsigned char
  EvalParser::yytable_[] =
  {
      31,    61,   133,    49,    50,   148,   141,    90,    33,    34,
     143,   133,    58,    86,    59,    98,    99,    95,    96,    87,
     149,   144,   134,   128,   129,   130,   135,   136,     4,    35,
       5,   142,    32,   106,     6,     7,     8,     9,   145,    80,
      81,    36,   135,   136,    49,    50,    10,    82,    45,    94,
      46,    11,    37,    92,    93,   173,   175,   173,   175,    12,
      83,    84,    13,    14,    15,     1,     2,    16,    17,    65,
      66,    67,    68,    38,    18,    19,    20,    57,    21,    49,
      50,    26,    27,    28,   128,   129,    70,    71,    72,    73,
      74,    75,    76,    10,   128,   129,   132,    39,    11,    77,
      78,    40,    41,   119,   120,    47,    12,    48,    42,    13,
      14,    15,   156,    43,    29,    30,    52,    44,   160,   161,
     162,    18,    19,    20,    51,    21,   128,   129,   172,   128,
     129,   174,    55,    56,    46,    48,    53,    54,   151,    62,
      64,    89,    91,   100,   101,   102,   103,   107,   104,   105,
     108,    49,   109,   110,   111,   112,   113,   117,   114,   138,
     115,   116,   139,   121,   122,   123,   124,   125,   126,   127,
     142,   140,   146,   157,   147,   152,   153,   154,   158,   155,
     159,   163,   164,   165,   166,     0,   167,    97,   168,   169,
     170,     0,   171
  };

  const short int
  EvalParser::yycheck_[] =
  {
       2,    36,   115,     6,     7,    35,    20,    47,     4,     5,
       9,   124,    50,    44,    52,    55,    56,    52,    53,    50,
      50,    20,     9,    18,    19,    20,    13,    14,     3,    15,
       5,    45,     0,    36,     9,    10,    11,    12,     9,    41,
      42,    15,    13,    14,     6,     7,    21,    43,    15,    51,
      17,    26,    15,    49,    50,   168,   169,   170,   171,    34,
      40,    41,    37,    38,    39,    47,    48,    42,    43,    22,
      23,    24,    25,     3,    49,    50,    51,     4,    53,     6,
       7,     9,    10,    11,    18,    19,    27,    28,    29,    30,
      31,    32,    33,    21,    18,    19,    20,    17,    26,    40,
      41,    17,     3,   105,   106,    15,    34,    17,     3,    37,
      38,    39,   147,     3,    42,    43,    15,    17,   153,   154,
     155,    49,    50,    51,     8,    53,    18,    19,    20,    18,
      19,    20,    15,    15,    17,    17,    15,    15,   140,    50,
      49,    46,    46,    16,    16,    16,     4,    16,    36,    36,
      16,     6,    16,    16,    16,    16,    16,    50,    17,    36,
      17,    17,     4,    17,    17,    17,    17,    17,    17,    17,
      45,    36,     9,     4,    15,    15,    15,    15,     4,    15,
      50,    16,    16,    16,    16,    -1,    16,    54,    17,    17,
      17,    -1,    17
  };

  const unsigned char
  EvalParser::yystos_[] =
  {
       0,    47,    48,    55,     3,     5,     9,    10,    11,    12,
      21,    26,    34,    37,    38,    39,    42,    43,    49,    50,
      51,    53,    56,    57,    58,    59,     9,    10,    11,    42,
      43,    58,     0,    57,    57,    15,    15,    15,     3,    17,
      17,     3,     3,     3,    17,    15,    17,    15,    17,     6,
       7,     8,    15,    15,    15,    15,    15,     4,    50,    52,
      60,    60,    50,    62,    49,    22,    23,    24,    25,    63,
      27,    28,    29,    30,    31,    32,    33,    40,    41,    65,
      58,    58,    57,    40,    41,    66,    44,    50,    64,    46,
      64,    46,    57,    57,    58,    60,    60,    62,    64,    64,
      16,    16,    16,     4,    36,    36,    36,    16,    16,    16,
      16,    16,    16,    16,    17,    17,    17,    50,    68,    58,
      58,    17,    17,    17,    17,    17,    17,    17,    18,    19,
      20,    61,    20,    61,     9,    13,    14,    67,    36,     4,
      36,    20,    45,     9,    20,     9,     9,    15,    35,    50,
      69,    58,    15,    15,    15,    15,    60,     4,     4,    50,
      60,    60,    60,    16,    16,    16,    16,    16,    17,    17,
      17,    17,    20,    61,    20,    61
  };

  const unsigned char
  EvalParser::yyr1_[] =
  {
       0,    54,    55,    55,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    60,    60,    61,
      61,    62,    63,    63,    63,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    67,
      67,    68,    69,    69
  };

  const unsigned char
  EvalParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     3,     2,     3,     3,     3,
       6,     6,    11,     6,     6,    11,     4,     1,     1,     1,
       6,     6,    11,     3,     3,     3,     6,     8,     6,     8,
       3,     3,    11,     6,     9,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const EvalParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"(\"", "\")\"", "\"not\"",
  "\"and\"", "\"or\"", "\"==\"", "\"option\"", "\"relay4\"", "\"relay6\"",
  "\"member\"", "\"peeraddr\"", "\"linkaddr\"", "\"[\"", "\"]\"", "\".\"",
  "\"text\"", "\"hex\"", "\"exists\"", "\"pkt\"", "\"iface\"", "\"src\"",
  "\"dst\"", "\"len\"", "\"pkt4\"", "\"mac\"", "\"hlen\"", "\"htype\"",
  "\"ciaddr\"", "\"giaddr\"", "\"yiaddr\"", "\"siaddr\"", "\"substring\"",
  "\"all\"", "\",\"", "\"concat\"", "\"ifelse\"", "\"pkt6\"",
  "\"msgtype\"", "\"transid\"", "\"vendor-class\"", "\"vendor\"", "\"*\"",
  "\"data\"", "\"enterprise\"", "\"top-level bool\"",
  "\"top-level string\"", "\"constant string\"", "\"integer\"",
  "\"constant hexstring\"", "\"option name\"", "\"ip address\"", "$accept",
  "start", "expression", "bool_expr", "string_expr", "integer_expr",
  "option_code", "option_repr_type", "nest_level", "pkt_metadata",
  "enterprise_id", "pkt4_field", "pkt6_field", "relay6_field",
  "start_expr", "length_expr", YY_NULLPTR
  };

#if EVALDEBUG
  const unsigned short int
  EvalParser::yyrline_[] =
  {
       0,   119,   119,   120,   125,   128,   129,   134,   139,   144,
     149,   154,   174,   188,   197,   206,   216,   233,   238,   243,
     248,   253,   274,   289,   294,   308,   322,   337,   342,   347,
     352,   361,   371,   380,   393,   406,   413,   419,   423,   429,
     433,   439,   448,   452,   456,   460,   466,   470,   476,   480,
     484,   488,   492,   496,   500,   504,   508,   514,   518,   524,
     528,   534,   541,   546
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
#endif // EVALDEBUG


#line 14 "parser.yy" // lalr1.cc:1167
} } // isc::eval
#line 1853 "parser.cc" // lalr1.cc:1167
#line 553 "parser.yy" // lalr1.cc:1168

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
