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
      case 50: // option_repr_type
        value.move< TokenOption::RepresentationType > (that.value);
        break;

      case 52: // pkt4_field
        value.move< TokenPkt4::FieldType > (that.value);
        break;

      case 57: // pkt6_field
        value.move< TokenPkt6::FieldType > (that.value);
        break;

      case 55: // relay6_field
        value.move< TokenRelay6Field::FieldType > (that.value);
        break;

      case 40: // "constant string"
      case 41: // "integer"
      case 42: // "constant hexstring"
      case 43: // "option name"
      case 44: // "ip address"
        value.move< std::string > (that.value);
        break;

      case 49: // option_code
        value.move< uint16_t > (that.value);
        break;

      case 51: // enterprise_id
        value.move< uint32_t > (that.value);
        break;

      case 56: // nest_level
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
      case 50: // option_repr_type
        value.copy< TokenOption::RepresentationType > (that.value);
        break;

      case 52: // pkt4_field
        value.copy< TokenPkt4::FieldType > (that.value);
        break;

      case 57: // pkt6_field
        value.copy< TokenPkt6::FieldType > (that.value);
        break;

      case 55: // relay6_field
        value.copy< TokenRelay6Field::FieldType > (that.value);
        break;

      case 40: // "constant string"
      case 41: // "integer"
      case 42: // "constant hexstring"
      case 43: // "option name"
      case 44: // "ip address"
        value.copy< std::string > (that.value);
        break;

      case 49: // option_code
        value.copy< uint16_t > (that.value);
        break;

      case 51: // enterprise_id
        value.copy< uint32_t > (that.value);
        break;

      case 56: // nest_level
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
            case 40: // "constant string"

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 382 "parser.cc" // lalr1.cc:636
        break;

      case 41: // "integer"

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 389 "parser.cc" // lalr1.cc:636
        break;

      case 42: // "constant hexstring"

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 396 "parser.cc" // lalr1.cc:636
        break;

      case 43: // "option name"

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 403 "parser.cc" // lalr1.cc:636
        break;

      case 44: // "ip address"

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 410 "parser.cc" // lalr1.cc:636
        break;

      case 49: // option_code

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint16_t > (); }
#line 417 "parser.cc" // lalr1.cc:636
        break;

      case 50: // option_repr_type

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenOption::RepresentationType > (); }
#line 424 "parser.cc" // lalr1.cc:636
        break;

      case 51: // enterprise_id

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint32_t > (); }
#line 431 "parser.cc" // lalr1.cc:636
        break;

      case 52: // pkt4_field

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenPkt4::FieldType > (); }
#line 438 "parser.cc" // lalr1.cc:636
        break;

      case 55: // relay6_field

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenRelay6Field::FieldType > (); }
#line 445 "parser.cc" // lalr1.cc:636
        break;

      case 56: // nest_level

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< uint8_t > (); }
#line 452 "parser.cc" // lalr1.cc:636
        break;

      case 57: // pkt6_field

#line 97 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TokenPkt6::FieldType > (); }
#line 459 "parser.cc" // lalr1.cc:636
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
      case 50: // option_repr_type
        yylhs.value.build< TokenOption::RepresentationType > ();
        break;

      case 52: // pkt4_field
        yylhs.value.build< TokenPkt4::FieldType > ();
        break;

      case 57: // pkt6_field
        yylhs.value.build< TokenPkt6::FieldType > ();
        break;

      case 55: // relay6_field
        yylhs.value.build< TokenRelay6Field::FieldType > ();
        break;

      case 40: // "constant string"
      case 41: // "integer"
      case 42: // "constant hexstring"
      case 43: // "option name"
      case 44: // "ip address"
        yylhs.value.build< std::string > ();
        break;

      case 49: // option_code
        yylhs.value.build< uint16_t > ();
        break;

      case 51: // enterprise_id
        yylhs.value.build< uint32_t > ();
        break;

      case 56: // nest_level
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
#line 111 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 718 "parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 116 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 727 "parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 121 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 736 "parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 126 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 745 "parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 131 "parser.yy" // lalr1.cc:859
    {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as< uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 754 "parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 136 "parser.yy" // lalr1.cc:859
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
#line 778 "parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 156 "parser.yy" // lalr1.cc:859
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
#line 796 "parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 170 "parser.yy" // lalr1.cc:859
    {
              // Expression: vendor-class[1234].exists
              //
              // This token will find option 124 (DHCPv4) or 16 (DHCPv6), and will check
              // if enterprise-id equals specified value.
              TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as< uint32_t > (), TokenOption::EXISTS));
              ctx.expression.push_back(exist);
          }
#line 809 "parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 179 "parser.yy" // lalr1.cc:859
    {
              // Expression: vendor[1234].exists
              //
              // This token will find option 125 (DHCPv4) or 17 (DHCPv6), and will check
              // if enterprise-id equals specified value.
              TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as< uint32_t > (), TokenOption::EXISTS));
              ctx.expression.push_back(exist);

          }
#line 823 "parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 189 "parser.yy" // lalr1.cc:859
    {
              // Expression vendor[1234].option[123].exists
              //
              // This token will check if specified vendor option exists, has specified
              // enterprise-id and if has specified suboption.
              TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as< uint32_t > (), TokenOption::EXISTS, yystack_[3].value.as< uint16_t > ()));
              ctx.expression.push_back(exist);
          }
#line 836 "parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 200 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 845 "parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 205 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 854 "parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 210 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 863 "parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 215 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as< uint16_t > (), yystack_[0].value.as< TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 872 "parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 220 "parser.yy" // lalr1.cc:859
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
#line 896 "parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 241 "parser.yy" // lalr1.cc:859
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
#line 914 "parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 256 "parser.yy" // lalr1.cc:859
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
#line 932 "parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 271 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr pkt4_field(new TokenPkt4(yystack_[0].value.as< TokenPkt4::FieldType > ()));
                      ctx.expression.push_back(pkt4_field);
                  }
#line 941 "parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 276 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr pkt6_field(new TokenPkt6(yystack_[0].value.as< TokenPkt6::FieldType > ()));
                      ctx.expression.push_back(pkt6_field);
                  }
#line 950 "parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 281 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 959 "parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 286 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 968 "parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 291 "parser.yy" // lalr1.cc:859
    {
              // expression: vendor.enterprise
              //
              // This token will return enterprise-id number of received vendor option.
              TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
              ctx.expression.push_back(vendor);
          }
#line 980 "parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 299 "parser.yy" // lalr1.cc:859
    {
              // expression: vendor-class.enterprise
              //
              // This token will return enterprise-id number of received vendor class option.
              TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                   TokenVendor::ENTERPRISE_ID));
              ctx.expression.push_back(vendor);
          }
#line 993 "parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 308 "parser.yy" // lalr1.cc:859
    {
              // expression: vendor[1234].option[56].exists
              // expression: vendor[1234].option[56].hex
              //
              // This token will search for vendor option with specified enterprise-id.
              // If found, will search for specified suboption and finally will return
              // if it exists ('exists') or its content ('hex')
              TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as< uint32_t > (), yystack_[0].value.as< TokenOption::RepresentationType > (), yystack_[3].value.as< uint16_t > ()));
              ctx.expression.push_back(opt);
          }
#line 1008 "parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 319 "parser.yy" // lalr1.cc:859
    {
              // expression: vendor-class[1234].data
              //
              // Vendor class option does not have suboptions, but chunks of data (typically 1,
              // but the option structure allows multiple of them). If chunk offset is not
              // specified, we assume the first (0th) is requested.
              TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as< uint32_t > (),
                                                         TokenVendor::DATA, 0));
              ctx.expression.push_back(vendor_class);
          }
#line 1023 "parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 330 "parser.yy" // lalr1.cc:859
    {
              // expression: vendor-class[1234].data[5]
              //
              // Vendor class option does not have suboptions, but chunks of data (typically 1,
              // but the option structure allows multiple of them). This syntax specifies
              // which data chunk (tuple) we want.
              uint8_t index = ctx.convertUint8(yystack_[1].value.as< std::string > (), yystack_[1].location);
              TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), yystack_[6].value.as< uint32_t > (),
                                                         TokenVendor::DATA, index));
              ctx.expression.push_back(vendor_class);
          }
#line 1039 "parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 344 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 1047 "parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 348 "parser.yy" // lalr1.cc:859
    {
                     yylhs.value.as< uint16_t > () = ctx.convertOptionName(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 1055 "parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 354 "parser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1063 "parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 358 "parser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1071 "parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 364 "parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< uint32_t > () = ctx.convertUint32(yystack_[0].value.as< std::string > (), yystack_[0].location);
}
#line 1079 "parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 368 "parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< uint32_t > () = 0;
}
#line 1087 "parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 373 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1095 "parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 377 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1103 "parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 381 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1111 "parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 385 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1119 "parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 389 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1127 "parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 393 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1135 "parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 397 "parser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1143 "parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 403 "parser.yy" // lalr1.cc:859
    {
                     TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1152 "parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 410 "parser.yy" // lalr1.cc:859
    {
                      TokenPtr str(new TokenString(yystack_[0].value.as< std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 1161 "parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 415 "parser.yy" // lalr1.cc:859
    {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 1170 "parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 421 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR; }
#line 1176 "parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 422 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR; }
#line 1182 "parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 426 "parser.yy" // lalr1.cc:859
    {
                 yylhs.value.as< uint8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as< std::string > (), yystack_[0].location);
                 }
#line 1190 "parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 434 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE; }
#line 1196 "parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 435 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< TokenPkt6::FieldType > () = TokenPkt6::TRANSID; }
#line 1202 "parser.cc" // lalr1.cc:859
    break;


#line 1206 "parser.cc" // lalr1.cc:859
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


  const signed char EvalParser::yypact_ninf_ = -82;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short int
  EvalParser::yypact_[] =
  {
      65,    65,    65,    -4,    -1,     7,    29,    47,    66,    41,
       2,    24,   -82,   -82,   -82,    84,    92,    83,    40,   -82,
      45,    45,    67,    56,    -3,    -3,    69,   -11,    75,   -11,
      77,   -82,    65,    65,    -3,   -82,   -82,   -82,    80,    91,
     -82,   100,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     103,   104,   105,    73,    76,    90,    94,   -82,   -82,   -82,
     -82,   -82,   106,   -82,   107,   -82,   -82,   117,   -82,   109,
     110,   111,    45,    45,    67,   -11,   -11,    87,    -3,   113,
     114,    36,    43,    11,   116,   118,   119,   120,   121,   -82,
     102,   133,   -16,     0,   -82,   -82,   -82,   -82,   -82,   -82,
     124,   -82,   -82,   -82,   123,   125,   126,   127,   128,   -14,
     -82,   -82,   131,   132,   -82,    45,    93,    93,    22,   112,
     138,   -82,   -82,   136,   108,    45,   137,   134,   139,   -82,
     140,   141,   135,    45,    45,   -82,   142,    46,   144,   145,
      54,   -82,   -82,   146,   147,   -82,   -82,    93,    93
  };

  const unsigned char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,    15,    16,     0,     2,     0,     0,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     3,    30,    31,     0,     0,
      48,     0,    36,    37,    38,    39,    40,    41,    42,    21,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    22,
      35,    34,     0,    26,     0,    25,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,     0,    32,    33,     8,    17,     9,    18,
       0,    46,    47,    20,     0,     0,     0,     0,     0,     0,
      24,    11,    28,     0,    12,     0,     0,     0,     0,     0,
       0,    45,    44,     0,     0,     0,     0,     0,     0,    23,
       0,     0,     0,     0,     0,    29,     0,     0,     0,     0,
       0,    10,    19,     0,     0,    13,    27,     0,     0
  };

  const signed char
  EvalParser::yypgoto_[] =
  {
     -82,   -82,    10,   -20,   -21,   -81,   -27,   -82,   -82,   -82,
     -82,    95,   -82
  };

  const signed char
  EvalParser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    38,    97,    62,    49,    90,   123,
     103,    41,    59
  };

  const unsigned char
  EvalParser::yytable_[] =
  {
      39,    99,    64,   111,    55,    56,    50,    51,    52,   113,
      20,    18,    19,    21,    68,   121,    27,     6,    28,   114,
     100,    22,   112,   101,   102,     7,    60,   122,     8,     9,
      61,   127,    53,    54,   101,   102,    99,    12,    29,    13,
      30,    14,    66,    67,    35,    23,    32,    33,    87,    88,
      24,    84,    85,    94,    95,    96,   142,    26,    91,   146,
      94,    95,    98,    94,    95,   141,   142,   146,     1,    25,
       2,    94,    95,   145,     3,     4,     5,    42,    43,    44,
      45,    46,    47,    48,    31,     6,    36,    75,    37,    28,
      76,    34,    30,     7,   126,    69,     8,     9,    32,    33,
      10,    11,    57,    58,   131,    12,    70,    13,    40,    14,
      94,    95,   138,   139,    63,    71,    65,    72,    73,    74,
      77,    79,    80,    32,    78,    81,    82,    83,    89,    92,
      93,   104,   109,   105,   106,   107,   108,   110,   115,   116,
     129,   117,   118,   119,   120,   124,   125,   128,   133,   130,
     112,   137,   132,   134,     0,   135,   136,     0,   140,   143,
     144,     0,   147,   148,     0,     0,     0,     0,     0,    86
  };

  const short int
  EvalParser::yycheck_[] =
  {
      21,    82,    29,    19,    24,    25,     9,    10,    11,     9,
      14,     1,     2,    14,    34,    29,    14,    20,    16,    19,
       9,    14,    38,    12,    13,    28,    37,    41,    31,    32,
      41,     9,    35,    36,    12,    13,   117,    40,    14,    42,
      16,    44,    32,    33,     4,    16,     6,     7,    75,    76,
       3,    72,    73,    17,    18,    19,   137,    16,    78,   140,
      17,    18,    19,    17,    18,    19,   147,   148,     3,     3,
       5,    17,    18,    19,     9,    10,    11,    21,    22,    23,
      24,    25,    26,    27,     0,    20,    41,    14,    43,    16,
      14,     8,    16,    28,   115,    15,    31,    32,     6,     7,
      35,    36,    33,    34,   125,    40,    15,    42,    41,    44,
      17,    18,   133,   134,    39,    15,    39,    14,    14,    14,
      30,    15,    15,     6,    30,    16,    16,    16,    41,    16,
      16,    15,    30,    15,    15,    15,    15,     4,    14,    16,
       4,    16,    16,    16,    16,    14,    14,     9,    14,    41,
      38,    16,    15,    14,    -1,    15,    15,    -1,    16,    15,
      15,    -1,    16,    16,    -1,    -1,    -1,    -1,    -1,    74
  };

  const unsigned char
  EvalParser::yystos_[] =
  {
       0,     3,     5,     9,    10,    11,    20,    28,    31,    32,
      35,    36,    40,    42,    44,    46,    47,    48,    47,    47,
      14,    14,    14,    16,     3,     3,    16,    14,    16,    14,
      16,     0,     6,     7,     8,     4,    41,    43,    49,    49,
      41,    56,    21,    22,    23,    24,    25,    26,    27,    52,
       9,    10,    11,    35,    36,    48,    48,    33,    34,    57,
      37,    41,    51,    39,    51,    39,    47,    47,    48,    15,
      15,    15,    14,    14,    14,    14,    14,    30,    30,    15,
      15,    16,    16,    16,    49,    49,    56,    51,    51,    41,
      53,    48,    16,    16,    17,    18,    19,    50,    19,    50,
       9,    12,    13,    55,    15,    15,    15,    15,    15,    30,
       4,    19,    38,     9,    19,    14,    16,    16,    16,    16,
      16,    29,    41,    54,    14,    14,    49,     9,     9,     4,
      41,    49,    15,    14,    14,    15,    15,    16,    49,    49,
      16,    19,    50,    15,    15,    19,    50,    16,    16
  };

  const unsigned char
  EvalParser::yyr1_[] =
  {
       0,    45,    46,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    53,    54,    54,    55,    55,    56,    57,
      57
  };

  const unsigned char
  EvalParser::yyr2_[] =
  {
       0,     2,     1,     3,     2,     3,     3,     3,     6,     6,
      11,     6,     6,    11,     1,     1,     1,     6,     6,    11,
       6,     3,     3,     8,     6,     3,     3,    11,     6,     9,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const EvalParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"(\"", "\")\"", "\"not\"",
  "\"and\"", "\"or\"", "\"==\"", "\"option\"", "\"relay4\"", "\"relay6\"",
  "\"peeraddr\"", "\"linkaddr\"", "\"[\"", "\"]\"", "\".\"", "\"text\"",
  "\"hex\"", "\"exists\"", "\"pkt4\"", "\"mac\"", "\"hlen\"", "\"htype\"",
  "\"ciaddr\"", "\"giaddr\"", "\"yiaddr\"", "\"siaddr\"", "\"substring\"",
  "\"all\"", "\",\"", "\"concat\"", "\"pkt6\"", "\"msgtype\"",
  "\"transid\"", "\"vendor-class\"", "\"vendor\"", "\"*\"", "\"data\"",
  "\"enterprise\"", "\"constant string\"", "\"integer\"",
  "\"constant hexstring\"", "\"option name\"", "\"ip address\"", "$accept",
  "expression", "bool_expr", "string_expr", "option_code",
  "option_repr_type", "enterprise_id", "pkt4_field", "start_expr",
  "length_expr", "relay6_field", "nest_level", "pkt6_field", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  EvalParser::yyrline_[] =
  {
       0,   106,   106,   109,   110,   115,   120,   125,   130,   135,
     155,   169,   178,   188,   199,   204,   209,   214,   219,   240,
     255,   270,   275,   280,   285,   290,   298,   307,   318,   329,
     343,   347,   353,   357,   363,   367,   372,   376,   380,   384,
     388,   392,   396,   402,   409,   414,   421,   422,   425,   434,
     435
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
#line 1670 "parser.cc" // lalr1.cc:1167
#line 438 "parser.yy" // lalr1.cc:1168

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
