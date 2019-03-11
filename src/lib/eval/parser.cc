// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.


// Take the name prefix into account.
#define yylex   evallex



#include "parser.h"


// Unqualified %code blocks.
#line 33 "parser.yy" // lalr1.cc:435

# include "eval_context.h"

#line 51 "parser.cc" // lalr1.cc:435


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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !EVALDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "parser.yy" // lalr1.cc:510
namespace isc { namespace eval {
#line 146 "parser.cc" // lalr1.cc:510

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
        std::string yyr;
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
              else
                goto append;

            append:
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

  EvalParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  EvalParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  EvalParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  EvalParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  EvalParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  EvalParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  EvalParser::symbol_number_type
  EvalParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  EvalParser::stack_symbol_type::stack_symbol_type ()
  {}

  EvalParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 62: // option_repr_type
        value.YY_MOVE_OR_COPY< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case 66: // pkt4_field
        value.YY_MOVE_OR_COPY< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case 67: // pkt6_field
        value.YY_MOVE_OR_COPY< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case 64: // pkt_metadata
        value.YY_MOVE_OR_COPY< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case 68: // relay6_field
        value.YY_MOVE_OR_COPY< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case 63: // nest_level
        value.YY_MOVE_OR_COPY< int8_t > (YY_MOVE (that.value));
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 61: // option_code
        value.YY_MOVE_OR_COPY< uint16_t > (YY_MOVE (that.value));
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.YY_MOVE_OR_COPY< uint32_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  EvalParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 62: // option_repr_type
        value.move< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case 66: // pkt4_field
        value.move< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case 67: // pkt6_field
        value.move< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case 64: // pkt_metadata
        value.move< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case 68: // relay6_field
        value.move< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case 63: // nest_level
        value.move< int8_t > (YY_MOVE (that.value));
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 61: // option_code
        value.move< uint16_t > (YY_MOVE (that.value));
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.move< uint32_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  EvalParser::stack_symbol_type&
  EvalParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 62: // option_repr_type
        value.move< TokenOption::RepresentationType > (that.value);
        break;

      case 66: // pkt4_field
        value.move< TokenPkt4::FieldType > (that.value);
        break;

      case 67: // pkt6_field
        value.move< TokenPkt6::FieldType > (that.value);
        break;

      case 64: // pkt_metadata
        value.move< TokenPkt::MetadataType > (that.value);
        break;

      case 68: // relay6_field
        value.move< TokenRelay6Field::FieldType > (that.value);
        break;

      case 63: // nest_level
        value.move< int8_t > (that.value);
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        value.move< std::string > (that.value);
        break;

      case 61: // option_code
        value.move< uint16_t > (that.value);
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        value.move< uint32_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
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
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 50: // "constant string"
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 449 "parser.cc" // lalr1.cc:676
        break;

      case 51: // "integer"
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 455 "parser.cc" // lalr1.cc:676
        break;

      case 52: // "constant hexstring"
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 461 "parser.cc" // lalr1.cc:676
        break;

      case 53: // "option name"
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 467 "parser.cc" // lalr1.cc:676
        break;

      case 54: // "ip address"
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 473 "parser.cc" // lalr1.cc:676
        break;

      case 60: // integer_expr
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < uint32_t > (); }
#line 479 "parser.cc" // lalr1.cc:676
        break;

      case 61: // option_code
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < uint16_t > (); }
#line 485 "parser.cc" // lalr1.cc:676
        break;

      case 62: // option_repr_type
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < TokenOption::RepresentationType > (); }
#line 491 "parser.cc" // lalr1.cc:676
        break;

      case 63: // nest_level
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int8_t > (); }
#line 497 "parser.cc" // lalr1.cc:676
        break;

      case 64: // pkt_metadata
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < TokenPkt::MetadataType > (); }
#line 503 "parser.cc" // lalr1.cc:676
        break;

      case 65: // enterprise_id
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < uint32_t > (); }
#line 509 "parser.cc" // lalr1.cc:676
        break;

      case 66: // pkt4_field
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < TokenPkt4::FieldType > (); }
#line 515 "parser.cc" // lalr1.cc:676
        break;

      case 67: // pkt6_field
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < TokenPkt6::FieldType > (); }
#line 521 "parser.cc" // lalr1.cc:676
        break;

      case 68: // relay6_field
#line 111 "parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < TokenRelay6Field::FieldType > (); }
#line 527 "parser.cc" // lalr1.cc:676
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  EvalParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  EvalParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  EvalParser::yypop_ (int n)
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

  EvalParser::state_type
  EvalParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  EvalParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  EvalParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  EvalParser::operator() ()
  {
    return parse ();
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 62: // option_repr_type
        yylhs.value.emplace< TokenOption::RepresentationType > ();
        break;

      case 66: // pkt4_field
        yylhs.value.emplace< TokenPkt4::FieldType > ();
        break;

      case 67: // pkt6_field
        yylhs.value.emplace< TokenPkt6::FieldType > ();
        break;

      case 64: // pkt_metadata
        yylhs.value.emplace< TokenPkt::MetadataType > ();
        break;

      case 68: // relay6_field
        yylhs.value.emplace< TokenRelay6Field::FieldType > ();
        break;

      case 63: // nest_level
        yylhs.value.emplace< int8_t > ();
        break;

      case 50: // "constant string"
      case 51: // "integer"
      case 52: // "constant hexstring"
      case 53: // "option name"
      case 54: // "ip address"
        yylhs.value.emplace< std::string > ();
        break;

      case 61: // option_code
        yylhs.value.emplace< uint16_t > ();
        break;

      case 60: // integer_expr
      case 65: // enterprise_id
        yylhs.value.emplace< uint32_t > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 6:
#line 131 "parser.yy" // lalr1.cc:919
    {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 811 "parser.cc" // lalr1.cc:919
    break;

  case 7:
#line 136 "parser.yy" // lalr1.cc:919
    {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 820 "parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 141 "parser.yy" // lalr1.cc:919
    {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 829 "parser.cc" // lalr1.cc:919
    break;

  case 9:
#line 146 "parser.yy" // lalr1.cc:919
    {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 838 "parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 151 "parser.yy" // lalr1.cc:919
    {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 847 "parser.cc" // lalr1.cc:919
    break;

  case 11:
#line 156 "parser.yy" // lalr1.cc:919
    {
                   switch (ctx.getUniverse()) {
                   case Option::V4:
                   {
                       TokenPtr opt(new TokenRelay4Option(yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
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
#line 871 "parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 176 "parser.yy" // lalr1.cc:919
    {
                    switch (ctx.getUniverse()) {
                    case Option::V6:
                    {
                        TokenPtr opt(new TokenRelay6Option(yystack_[8].value.as < int8_t > (), yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                        ctx.expression.push_back(opt);
                        break;
                    }
                    case Option::V4:
                        // For now we only use relay6 in DHCPv6.
                        error(yystack_[10].location, "relay6 can only be used in DHCPv6.");
                    }
                }
#line 889 "parser.cc" // lalr1.cc:919
    break;

  case 13:
#line 190 "parser.yy" // lalr1.cc:919
    {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 902 "parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 199 "parser.yy" // lalr1.cc:919
    {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 915 "parser.cc" // lalr1.cc:919
    break;

  case 15:
#line 208 "parser.yy" // lalr1.cc:919
    {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), TokenOption::EXISTS, yystack_[3].value.as < uint16_t > ()));
                  ctx.expression.push_back(exist);
               }
#line 929 "parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 218 "parser.yy" // lalr1.cc:919
    {
                  // Expression member('foo')
                  //
                  // This token will check if the packet is a member of
                  // the specified client class.
                  // To avoid loops at evaluation only already defined and
                  // built-in classes are allowed.
                  std::string cc = yystack_[1].value.as < std::string > ();
                  if (!ctx.isClientClassDefined(cc)) {
                      error(yystack_[1].location, "Not defined client class '" + cc + "'");
                  }
                  TokenPtr member(new TokenMember(cc));
                  ctx.expression.push_back(member);
              }
#line 948 "parser.cc" // lalr1.cc:919
    break;

  case 17:
#line 235 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 957 "parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 240 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 966 "parser.cc" // lalr1.cc:919
    break;

  case 19:
#line 245 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 975 "parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 250 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 984 "parser.cc" // lalr1.cc:919
    break;

  case 21:
#line 255 "parser.yy" // lalr1.cc:919
    {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr opt(new TokenRelay4Option(yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
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
#line 1008 "parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 276 "parser.yy" // lalr1.cc:919
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr opt(new TokenRelay6Option(yystack_[8].value.as < int8_t > (), yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                         ctx.expression.push_back(opt);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[10].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 1026 "parser.cc" // lalr1.cc:919
    break;

  case 23:
#line 291 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr pkt_metadata(new TokenPkt(yystack_[0].value.as < TokenPkt::MetadataType > ()));
                      ctx.expression.push_back(pkt_metadata);
                  }
#line 1035 "parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 296 "parser.yy" // lalr1.cc:919
    {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr pkt4_field(new TokenPkt4(yystack_[0].value.as < TokenPkt4::FieldType > ()));
                         ctx.expression.push_back(pkt4_field);
                         break;
                     }
                     case Option::V6:
                         // For now we only use pkt4 in DHCPv4.
                         error(yystack_[2].location, "pkt4 can only be used in DHCPv4.");
                     }
                  }
#line 1053 "parser.cc" // lalr1.cc:919
    break;

  case 25:
#line 310 "parser.yy" // lalr1.cc:919
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr pkt6_field(new TokenPkt6(yystack_[0].value.as < TokenPkt6::FieldType > ()));
                         ctx.expression.push_back(pkt6_field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use pkt6 in DHCPv6.
                         error(yystack_[2].location, "pkt6 can only be used in DHCPv6.");
                     }
                  }
#line 1071 "parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 324 "parser.yy" // lalr1.cc:919
    {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr relay6field(new TokenRelay6Field(yystack_[3].value.as < int8_t > (), yystack_[0].value.as < TokenRelay6Field::FieldType > ()));
                         ctx.expression.push_back(relay6field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[5].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 1089 "parser.cc" // lalr1.cc:919
    break;

  case 27:
#line 339 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 1098 "parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 344 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1107 "parser.cc" // lalr1.cc:919
    break;

  case 29:
#line 349 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression.push_back(cond);
                  }
#line 1116 "parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 354 "parser.yy" // lalr1.cc:919
    {
                      TokenPtr tohex(new TokenToHexString());
                      ctx.expression.push_back(tohex);
                  }
#line 1125 "parser.cc" // lalr1.cc:919
    break;

  case 31:
#line 359 "parser.yy" // lalr1.cc:919
    {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1138 "parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 368 "parser.yy" // lalr1.cc:919
    {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1152 "parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 378 "parser.yy" // lalr1.cc:919
    {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), yystack_[0].value.as < TokenOption::RepresentationType > (), yystack_[3].value.as < uint16_t > ()));
                    ctx.expression.push_back(opt);
                }
#line 1165 "parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 387 "parser.yy" // lalr1.cc:919
    {
                    // expression: vendor-class[1234].data
                    //
                    // Vendor class option does not have suboptions,
                    // but chunks of data (typically 1, but the option
                    // structure allows multiple of them). If chunk
                    // offset is not specified, we assume the first (0th)
                    // is requested.
                    TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (),
                                                               TokenVendor::DATA, 0));
                    ctx.expression.push_back(vendor_class);
                }
#line 1182 "parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 400 "parser.yy" // lalr1.cc:919
    {
                    // expression: vendor-class[1234].data[5]
                    //
                    // Vendor class option does not have suboptions,
                    // but chunks of data (typically 1, but the option
                    // structure allows multiple of them). This syntax
                    // specifies which data chunk (tuple) we want.
                    uint8_t index = ctx.convertUint8(yystack_[1].value.as < std::string > (), yystack_[1].location);
                    TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), yystack_[6].value.as < uint32_t > (),
                                                               TokenVendor::DATA, index));
                    ctx.expression.push_back(vendor_class);
                }
#line 1199 "parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 413 "parser.yy" // lalr1.cc:919
    {
                    TokenPtr integer(new TokenInteger(yystack_[0].value.as < uint32_t > ()));
                    ctx.expression.push_back(integer);
                }
#line 1208 "parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 420 "parser.yy" // lalr1.cc:919
    {
                     yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1216 "parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 426 "parser.yy" // lalr1.cc:919
    {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1224 "parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 430 "parser.yy" // lalr1.cc:919
    {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionName(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1232 "parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 436 "parser.yy" // lalr1.cc:919
    {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1240 "parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 440 "parser.yy" // lalr1.cc:919
    {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1248 "parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 446 "parser.yy" // lalr1.cc:919
    {
                     yylhs.value.as < int8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1256 "parser.cc" // lalr1.cc:919
    break;

  case 43:
#line 455 "parser.yy" // lalr1.cc:919
    {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::IFACE;
                  }
#line 1264 "parser.cc" // lalr1.cc:919
    break;

  case 44:
#line 459 "parser.yy" // lalr1.cc:919
    {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::SRC;
                  }
#line 1272 "parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 463 "parser.yy" // lalr1.cc:919
    {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::DST;
                  }
#line 1280 "parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 467 "parser.yy" // lalr1.cc:919
    {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::LEN;
                  }
#line 1288 "parser.cc" // lalr1.cc:919
    break;

  case 47:
#line 473 "parser.yy" // lalr1.cc:919
    {
                       yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                   }
#line 1296 "parser.cc" // lalr1.cc:919
    break;

  case 48:
#line 477 "parser.yy" // lalr1.cc:919
    {
                       yylhs.value.as < uint32_t > () = 0;
                   }
#line 1304 "parser.cc" // lalr1.cc:919
    break;

  case 49:
#line 483 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1312 "parser.cc" // lalr1.cc:919
    break;

  case 50:
#line 487 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1320 "parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 491 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1328 "parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 495 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1336 "parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 499 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1344 "parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 503 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1352 "parser.cc" // lalr1.cc:919
    break;

  case 55:
#line 507 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1360 "parser.cc" // lalr1.cc:919
    break;

  case 56:
#line 511 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::MSGTYPE;
                 }
#line 1368 "parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 515 "parser.yy" // lalr1.cc:919
    {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::TRANSID;
                 }
#line 1376 "parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 521 "parser.yy" // lalr1.cc:919
    {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE;
                 }
#line 1384 "parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 525 "parser.yy" // lalr1.cc:919
    {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::TRANSID;
                 }
#line 1392 "parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 531 "parser.yy" // lalr1.cc:919
    {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR;
                   }
#line 1400 "parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 535 "parser.yy" // lalr1.cc:919
    {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR;
                   }
#line 1408 "parser.cc" // lalr1.cc:919
    break;

  case 62:
#line 541 "parser.yy" // lalr1.cc:919
    {
                    TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                    ctx.expression.push_back(str);
                }
#line 1417 "parser.cc" // lalr1.cc:919
    break;

  case 63:
#line 548 "parser.yy" // lalr1.cc:919
    {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1426 "parser.cc" // lalr1.cc:919
    break;

  case 64:
#line 553 "parser.yy" // lalr1.cc:919
    {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 1435 "parser.cc" // lalr1.cc:919
    break;


#line 1439 "parser.cc" // lalr1.cc:919
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  EvalParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const signed char EvalParser::yypact_ninf_ = -118;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short
  EvalParser::yypact_[] =
  {
     -14,    27,    76,    17,    27,    27,    37,    41,    53,    39,
      52,    59,    77,    85,    93,    98,    88,    29,    94,  -118,
    -118,  -118,  -118,  -118,    56,   104,  -118,   114,   124,   129,
     119,   120,  -118,  -118,     7,  -118,    87,    87,    67,    95,
      50,    62,    76,    76,    27,    76,   100,   -35,    99,   -35,
     101,    27,    27,    76,    87,    87,    67,   -35,   -35,  -118,
    -118,  -118,   131,   133,  -118,   134,   147,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,   116,   117,    -3,   118,  -118,  -118,  -118,  -118,
    -118,   139,  -118,   140,  -118,  -118,   151,  -118,   142,   143,
     144,   145,   146,   148,   149,   150,  -118,   112,    76,    76,
      76,   152,   153,   154,   155,   156,   157,   158,     9,    64,
      12,  -118,   128,   164,   141,   172,   -15,     0,   103,   103,
      36,   132,   170,  -118,  -118,  -118,  -118,  -118,  -118,   165,
    -118,  -118,  -118,   -29,  -118,    76,  -118,  -118,   166,   167,
    -118,   168,   169,    87,  -118,  -118,   181,   182,   136,    87,
      87,    87,   173,  -118,  -118,   174,   175,   176,   177,   171,
    -118,   178,   179,   180,    80,   113,   103,   103,  -118,  -118,
    -118,  -118
  };

  const unsigned char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      37,    18,    19,     2,     4,     0,    36,     0,     0,     0,
       0,     0,     3,     1,     0,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
      38,    39,     0,     0,    42,     0,     0,    43,    44,    45,
      46,    23,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    24,     0,     0,     0,     0,    58,    59,    25,    48,
      47,     0,    32,     0,    31,     7,     8,     9,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    41,    10,    20,    11,    21,     0,
      60,    61,    26,     0,    28,     0,    30,    13,    34,     0,
      14,     0,     0,     0,    64,    63,     0,     0,     0,     0,
       0,     0,     0,    27,    29,     0,     0,     0,     0,     0,
      35,     0,     0,     0,     0,     0,     0,     0,    12,    22,
      15,    33
  };

  const short
  EvalParser::yypgoto_[] =
  {
    -118,  -118,  -118,     3,    -2,  -118,   -36,  -117,   138,  -118,
     -34,  -118,  -118,  -118,  -118,  -118
  };

  const short
  EvalParser::yydefgoto_[] =
  {
      -1,     3,    23,    24,    25,    26,    62,   136,    65,    71,
      91,    81,    88,   142,   122,   156
  };

  const unsigned char
  EvalParser::yytable_[] =
  {
      32,    63,   138,    51,    52,   147,   154,    34,    35,   149,
      89,    59,   138,    51,    52,    93,    90,    33,    98,    99,
     150,   139,   155,   101,   102,   140,   141,   133,   134,   135,
       4,   148,     5,   109,     1,     2,     6,     7,     8,     9,
      82,    83,    39,    85,    47,   151,    48,    84,    10,   140,
     141,    97,    36,    11,    95,    96,    37,   179,   181,   179,
     181,    12,    51,    52,    13,    14,    15,    16,    38,    40,
      17,    18,    67,    68,    69,    70,    41,    19,    20,    21,
      42,    22,   133,   134,   137,    27,    28,    29,    43,    72,
      73,    74,    75,    76,    77,    78,    44,    10,   133,   134,
     178,    45,    11,    79,    80,    46,   123,   124,   125,    49,
      12,    50,    53,    13,    14,    15,    16,   162,    64,    30,
      31,   133,   134,   166,   167,   168,    19,    20,    21,    54,
      22,   133,   134,   180,    57,    58,    48,    50,    60,    55,
      61,    86,    87,   157,    56,    66,    92,   103,    94,   104,
     105,   106,   107,   108,   110,   111,   112,    51,   113,   114,
     115,   116,   117,   121,   143,   118,   119,   120,   144,   126,
     127,   128,   129,   130,   131,   132,   146,   145,   148,   152,
     153,   158,   159,   160,   161,   163,   164,   165,   174,   169,
     170,   171,   172,   173,   100,   175,   176,   177
  };

  const unsigned char
  EvalParser::yycheck_[] =
  {
       2,    37,   119,     6,     7,    20,    35,     4,     5,     9,
      45,     4,   129,     6,     7,    49,    51,     0,    54,    55,
      20,     9,    51,    57,    58,    13,    14,    18,    19,    20,
       3,    46,     5,    36,    48,    49,     9,    10,    11,    12,
      42,    43,     3,    45,    15,     9,    17,    44,    21,    13,
      14,    53,    15,    26,    51,    52,    15,   174,   175,   176,
     177,    34,     6,     7,    37,    38,    39,    40,    15,    17,
      43,    44,    22,    23,    24,    25,    17,    50,    51,    52,
       3,    54,    18,    19,    20,     9,    10,    11,     3,    27,
      28,    29,    30,    31,    32,    33,     3,    21,    18,    19,
      20,     3,    26,    41,    42,    17,   108,   109,   110,    15,
      34,    17,     8,    37,    38,    39,    40,   153,    51,    43,
      44,    18,    19,   159,   160,   161,    50,    51,    52,    15,
      54,    18,    19,    20,    15,    15,    17,    17,    51,    15,
      53,    41,    42,   145,    15,    50,    47,    16,    47,    16,
      16,     4,    36,    36,    36,    16,    16,     6,    16,    16,
      16,    16,    16,    51,    36,    17,    17,    17,     4,    17,
      17,    17,    17,    17,    17,    17,     4,    36,    46,     9,
      15,    15,    15,    15,    15,     4,     4,    51,    17,    16,
      16,    16,    16,    16,    56,    17,    17,    17
  };

  const unsigned char
  EvalParser::yystos_[] =
  {
       0,    48,    49,    56,     3,     5,     9,    10,    11,    12,
      21,    26,    34,    37,    38,    39,    40,    43,    44,    50,
      51,    52,    54,    57,    58,    59,    60,     9,    10,    11,
      43,    44,    59,     0,    58,    58,    15,    15,    15,     3,
      17,    17,     3,     3,     3,     3,    17,    15,    17,    15,
      17,     6,     7,     8,    15,    15,    15,    15,    15,     4,
      51,    53,    61,    61,    51,    63,    50,    22,    23,    24,
      25,    64,    27,    28,    29,    30,    31,    32,    33,    41,
      42,    66,    59,    59,    58,    59,    41,    42,    67,    45,
      51,    65,    47,    65,    47,    58,    58,    59,    61,    61,
      63,    65,    65,    16,    16,    16,     4,    36,    36,    36,
      36,    16,    16,    16,    16,    16,    16,    16,    17,    17,
      17,    51,    69,    59,    59,    59,    17,    17,    17,    17,
      17,    17,    17,    18,    19,    20,    62,    20,    62,     9,
      13,    14,    68,    36,     4,    36,     4,    20,    46,     9,
      20,     9,     9,    15,    35,    51,    70,    59,    15,    15,
      15,    15,    61,     4,     4,    51,    61,    61,    61,    16,
      16,    16,    16,    16,    17,    17,    17,    17,    20,    62,
      20,    62
  };

  const unsigned char
  EvalParser::yyr1_[] =
  {
       0,    55,    56,    56,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    60,    61,    61,
      62,    62,    63,    64,    64,    64,    64,    65,    65,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      68,    68,    69,    70,    70
  };

  const unsigned char
  EvalParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     3,     2,     3,     3,     3,
       6,     6,    11,     6,     6,    11,     4,     1,     1,     1,
       6,     6,    11,     3,     3,     3,     6,     8,     6,     8,
       6,     3,     3,    11,     6,     9,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
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
  "\"all\"", "\",\"", "\"concat\"", "\"ifelse\"", "\"hexstring\"",
  "\"pkt6\"", "\"msgtype\"", "\"transid\"", "\"vendor-class\"",
  "\"vendor\"", "\"*\"", "\"data\"", "\"enterprise\"",
  "\"top-level bool\"", "\"top-level string\"", "\"constant string\"",
  "\"integer\"", "\"constant hexstring\"", "\"option name\"",
  "\"ip address\"", "$accept", "start", "expression", "bool_expr",
  "string_expr", "integer_expr", "option_code", "option_repr_type",
  "nest_level", "pkt_metadata", "enterprise_id", "pkt4_field",
  "pkt6_field", "relay6_field", "start_expr", "length_expr", YY_NULLPTR
  };

#if EVALDEBUG
  const unsigned short
  EvalParser::yyrline_[] =
  {
       0,   120,   120,   121,   126,   129,   130,   135,   140,   145,
     150,   155,   175,   189,   198,   207,   217,   234,   239,   244,
     249,   254,   275,   290,   295,   309,   323,   338,   343,   348,
     353,   358,   367,   377,   386,   399,   412,   419,   425,   429,
     435,   439,   445,   454,   458,   462,   466,   472,   476,   482,
     486,   490,   494,   498,   502,   506,   510,   514,   520,   524,
     530,   534,   540,   547,   552
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
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  EvalParser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // EVALDEBUG


#line 14 "parser.yy" // lalr1.cc:1242
} } // isc::eval
#line 1942 "parser.cc" // lalr1.cc:1242
#line 559 "parser.yy" // lalr1.cc:1243

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
