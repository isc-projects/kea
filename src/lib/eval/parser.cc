// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
#line 33 "parser.yy"

# include "eval_context.h"

#line 51 "parser.cc"


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

#line 14 "parser.yy"
namespace isc { namespace eval {
#line 143 "parser.cc"


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
#if EVALDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
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
      return yystos_[+state];
  }

  EvalParser::stack_symbol_type::stack_symbol_type ()
  {}

  EvalParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 64: // option_repr_type
        value.YY_MOVE_OR_COPY< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case 68: // pkt4_field
        value.YY_MOVE_OR_COPY< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case 69: // pkt6_field
        value.YY_MOVE_OR_COPY< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case 66: // pkt_metadata
        value.YY_MOVE_OR_COPY< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case 70: // relay6_field
        value.YY_MOVE_OR_COPY< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case 65: // nest_level
        value.YY_MOVE_OR_COPY< int8_t > (YY_MOVE (that.value));
        break;

      case 51: // "constant string"
      case 52: // "integer"
      case 53: // "constant hexstring"
      case 54: // "option name"
      case 55: // "ip address"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 62: // option_code
      case 63: // sub_option_code
        value.YY_MOVE_OR_COPY< uint16_t > (YY_MOVE (that.value));
        break;

      case 61: // integer_expr
      case 67: // enterprise_id
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
      case 64: // option_repr_type
        value.move< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case 68: // pkt4_field
        value.move< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case 69: // pkt6_field
        value.move< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case 66: // pkt_metadata
        value.move< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case 70: // relay6_field
        value.move< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case 65: // nest_level
        value.move< int8_t > (YY_MOVE (that.value));
        break;

      case 51: // "constant string"
      case 52: // "integer"
      case 53: // "constant hexstring"
      case 54: // "option name"
      case 55: // "ip address"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 62: // option_code
      case 63: // sub_option_code
        value.move< uint16_t > (YY_MOVE (that.value));
        break;

      case 61: // integer_expr
      case 67: // enterprise_id
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
  EvalParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 64: // option_repr_type
        value.copy< TokenOption::RepresentationType > (that.value);
        break;

      case 68: // pkt4_field
        value.copy< TokenPkt4::FieldType > (that.value);
        break;

      case 69: // pkt6_field
        value.copy< TokenPkt6::FieldType > (that.value);
        break;

      case 66: // pkt_metadata
        value.copy< TokenPkt::MetadataType > (that.value);
        break;

      case 70: // relay6_field
        value.copy< TokenRelay6Field::FieldType > (that.value);
        break;

      case 65: // nest_level
        value.copy< int8_t > (that.value);
        break;

      case 51: // "constant string"
      case 52: // "integer"
      case 53: // "constant hexstring"
      case 54: // "option name"
      case 55: // "ip address"
        value.copy< std::string > (that.value);
        break;

      case 62: // option_code
      case 63: // sub_option_code
        value.copy< uint16_t > (that.value);
        break;

      case 61: // integer_expr
      case 67: // enterprise_id
        value.copy< uint32_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  EvalParser::stack_symbol_type&
  EvalParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 64: // option_repr_type
        value.move< TokenOption::RepresentationType > (that.value);
        break;

      case 68: // pkt4_field
        value.move< TokenPkt4::FieldType > (that.value);
        break;

      case 69: // pkt6_field
        value.move< TokenPkt6::FieldType > (that.value);
        break;

      case 66: // pkt_metadata
        value.move< TokenPkt::MetadataType > (that.value);
        break;

      case 70: // relay6_field
        value.move< TokenRelay6Field::FieldType > (that.value);
        break;

      case 65: // nest_level
        value.move< int8_t > (that.value);
        break;

      case 51: // "constant string"
      case 52: // "integer"
      case 53: // "constant hexstring"
      case 54: // "option name"
      case 55: // "ip address"
        value.move< std::string > (that.value);
        break;

      case 62: // option_code
      case 63: // sub_option_code
        value.move< uint16_t > (that.value);
        break;

      case 61: // integer_expr
      case 67: // enterprise_id
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
      case 51: // "constant string"
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 507 "parser.cc"
        break;

      case 52: // "integer"
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 513 "parser.cc"
        break;

      case 53: // "constant hexstring"
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 519 "parser.cc"
        break;

      case 54: // "option name"
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 525 "parser.cc"
        break;

      case 55: // "ip address"
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 531 "parser.cc"
        break;

      case 61: // integer_expr
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 537 "parser.cc"
        break;

      case 62: // option_code
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 543 "parser.cc"
        break;

      case 63: // sub_option_code
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 549 "parser.cc"
        break;

      case 64: // option_repr_type
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenOption::RepresentationType > (); }
#line 555 "parser.cc"
        break;

      case 65: // nest_level
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < int8_t > (); }
#line 561 "parser.cc"
        break;

      case 66: // pkt_metadata
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt::MetadataType > (); }
#line 567 "parser.cc"
        break;

      case 67: // enterprise_id
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 573 "parser.cc"
        break;

      case 68: // pkt4_field
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt4::FieldType > (); }
#line 579 "parser.cc"
        break;

      case 69: // pkt6_field
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt6::FieldType > (); }
#line 585 "parser.cc"
        break;

      case 70: // relay6_field
#line 113 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenRelay6Field::FieldType > (); }
#line 591 "parser.cc"
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
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
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
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
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
      case 64: // option_repr_type
        yylhs.value.emplace< TokenOption::RepresentationType > ();
        break;

      case 68: // pkt4_field
        yylhs.value.emplace< TokenPkt4::FieldType > ();
        break;

      case 69: // pkt6_field
        yylhs.value.emplace< TokenPkt6::FieldType > ();
        break;

      case 66: // pkt_metadata
        yylhs.value.emplace< TokenPkt::MetadataType > ();
        break;

      case 70: // relay6_field
        yylhs.value.emplace< TokenRelay6Field::FieldType > ();
        break;

      case 65: // nest_level
        yylhs.value.emplace< int8_t > ();
        break;

      case 51: // "constant string"
      case 52: // "integer"
      case 53: // "constant hexstring"
      case 54: // "option name"
      case 55: // "ip address"
        yylhs.value.emplace< std::string > ();
        break;

      case 62: // option_code
      case 63: // sub_option_code
        yylhs.value.emplace< uint16_t > ();
        break;

      case 61: // integer_expr
      case 67: // enterprise_id
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
#line 133 "parser.yy"
                {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 877 "parser.cc"
    break;

  case 7:
#line 138 "parser.yy"
                {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 886 "parser.cc"
    break;

  case 8:
#line 143 "parser.yy"
                {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 895 "parser.cc"
    break;

  case 9:
#line 148 "parser.yy"
                {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 904 "parser.cc"
    break;

  case 10:
#line 153 "parser.yy"
                {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 913 "parser.cc"
    break;

  case 11:
#line 158 "parser.yy"
                {
                    TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 922 "parser.cc"
    break;

  case 12:
#line 163 "parser.yy"
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
#line 946 "parser.cc"
    break;

  case 13:
#line 183 "parser.yy"
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
#line 964 "parser.cc"
    break;

  case 14:
#line 197 "parser.yy"
              {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 977 "parser.cc"
    break;

  case 15:
#line 206 "parser.yy"
              {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 990 "parser.cc"
    break;

  case 16:
#line 215 "parser.yy"
              {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), TokenOption::EXISTS, yystack_[3].value.as < uint16_t > ()));
                  ctx.expression.push_back(exist);
               }
#line 1004 "parser.cc"
    break;

  case 17:
#line 225 "parser.yy"
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
#line 1023 "parser.cc"
    break;

  case 18:
#line 242 "parser.yy"
                  {
                      TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 1032 "parser.cc"
    break;

  case 19:
#line 247 "parser.yy"
                  {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 1041 "parser.cc"
    break;

  case 20:
#line 252 "parser.yy"
                  {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 1050 "parser.cc"
    break;

  case 21:
#line 257 "parser.yy"
                  {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1059 "parser.cc"
    break;

  case 22:
#line 262 "parser.yy"
                  {
                      TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1068 "parser.cc"
    break;

  case 23:
#line 267 "parser.yy"
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
#line 1092 "parser.cc"
    break;

  case 24:
#line 288 "parser.yy"
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
#line 1110 "parser.cc"
    break;

  case 25:
#line 303 "parser.yy"
                  {
                      TokenPtr pkt_metadata(new TokenPkt(yystack_[0].value.as < TokenPkt::MetadataType > ()));
                      ctx.expression.push_back(pkt_metadata);
                  }
#line 1119 "parser.cc"
    break;

  case 26:
#line 308 "parser.yy"
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
#line 1137 "parser.cc"
    break;

  case 27:
#line 322 "parser.yy"
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
#line 1155 "parser.cc"
    break;

  case 28:
#line 336 "parser.yy"
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
#line 1173 "parser.cc"
    break;

  case 29:
#line 351 "parser.yy"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 1182 "parser.cc"
    break;

  case 30:
#line 356 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1191 "parser.cc"
    break;

  case 31:
#line 361 "parser.yy"
                  {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression.push_back(cond);
                  }
#line 1200 "parser.cc"
    break;

  case 32:
#line 366 "parser.yy"
                  {
                      TokenPtr tohex(new TokenToHexString());
                      ctx.expression.push_back(tohex);
                  }
#line 1209 "parser.cc"
    break;

  case 33:
#line 371 "parser.yy"
                  {
                      TokenPtr addrtotext(new TokenIpAddressToText());
                      ctx.expression.push_back(addrtotext);
                  }
#line 1218 "parser.cc"
    break;

  case 34:
#line 376 "parser.yy"
                {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1231 "parser.cc"
    break;

  case 35:
#line 385 "parser.yy"
                {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1245 "parser.cc"
    break;

  case 36:
#line 395 "parser.yy"
                {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), yystack_[0].value.as < TokenOption::RepresentationType > (), yystack_[3].value.as < uint16_t > ()));
                    ctx.expression.push_back(opt);
                }
#line 1258 "parser.cc"
    break;

  case 37:
#line 404 "parser.yy"
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
#line 1275 "parser.cc"
    break;

  case 38:
#line 417 "parser.yy"
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
#line 1292 "parser.cc"
    break;

  case 39:
#line 430 "parser.yy"
                {
                    TokenPtr integer(new TokenInteger(yystack_[0].value.as < uint32_t > ()));
                    ctx.expression.push_back(integer);
                }
#line 1301 "parser.cc"
    break;

  case 40:
#line 437 "parser.yy"
                 {
                     yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1309 "parser.cc"
    break;

  case 41:
#line 443 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1317 "parser.cc"
    break;

  case 42:
#line 447 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionName(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1325 "parser.cc"
    break;

  case 43:
#line 453 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1333 "parser.cc"
    break;

  case 44:
#line 459 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1341 "parser.cc"
    break;

  case 45:
#line 463 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1349 "parser.cc"
    break;

  case 46:
#line 469 "parser.yy"
                 {
                     yylhs.value.as < int8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1357 "parser.cc"
    break;

  case 47:
#line 478 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::IFACE;
                  }
#line 1365 "parser.cc"
    break;

  case 48:
#line 482 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::SRC;
                  }
#line 1373 "parser.cc"
    break;

  case 49:
#line 486 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::DST;
                  }
#line 1381 "parser.cc"
    break;

  case 50:
#line 490 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::LEN;
                  }
#line 1389 "parser.cc"
    break;

  case 51:
#line 496 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                   }
#line 1397 "parser.cc"
    break;

  case 52:
#line 500 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = 0;
                   }
#line 1405 "parser.cc"
    break;

  case 53:
#line 506 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1413 "parser.cc"
    break;

  case 54:
#line 510 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1421 "parser.cc"
    break;

  case 55:
#line 514 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1429 "parser.cc"
    break;

  case 56:
#line 518 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1437 "parser.cc"
    break;

  case 57:
#line 522 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1445 "parser.cc"
    break;

  case 58:
#line 526 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1453 "parser.cc"
    break;

  case 59:
#line 530 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1461 "parser.cc"
    break;

  case 60:
#line 534 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::MSGTYPE;
                 }
#line 1469 "parser.cc"
    break;

  case 61:
#line 538 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::TRANSID;
                 }
#line 1477 "parser.cc"
    break;

  case 62:
#line 544 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE;
                 }
#line 1485 "parser.cc"
    break;

  case 63:
#line 548 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::TRANSID;
                 }
#line 1493 "parser.cc"
    break;

  case 64:
#line 554 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR;
                   }
#line 1501 "parser.cc"
    break;

  case 65:
#line 558 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR;
                   }
#line 1509 "parser.cc"
    break;

  case 66:
#line 564 "parser.yy"
                {
                    TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                    ctx.expression.push_back(str);
                }
#line 1518 "parser.cc"
    break;

  case 67:
#line 571 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1527 "parser.cc"
    break;

  case 68:
#line 576 "parser.yy"
                 {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 1536 "parser.cc"
    break;


#line 1540 "parser.cc"

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
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
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
      error_token.state = state_type (yyn);
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
    std::ptrdiff_t yycount = 0;
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
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
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
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
    std::ptrdiff_t yyi = 0;
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


  const signed char EvalParser::yypact_ninf_ = -124;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short
  EvalParser::yypact_[] =
  {
      42,    49,   113,     5,    49,    49,    15,    28,    70,    54,
      91,    92,   117,   125,   133,   134,   135,   104,    88,   114,
    -124,  -124,  -124,  -124,  -124,    17,   132,  -124,   126,   127,
     128,   115,   118,  -124,  -124,    67,  -124,    30,    93,    94,
      97,    56,   -15,   113,   113,    49,   113,   113,    20,   -26,
      96,   -26,   108,    49,    49,   113,    30,    93,    94,   -26,
     -26,  -124,  -124,  -124,   139,  -124,   143,  -124,   144,   157,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,   131,   136,     3,   137,   158,
    -124,  -124,  -124,  -124,  -124,   147,  -124,   153,  -124,  -124,
     164,  -124,   155,   159,   160,   161,   162,   163,   165,   166,
    -124,   122,   113,   113,   113,  -124,   167,   168,   169,   170,
     171,   172,   173,    13,    18,    37,  -124,   145,   175,   156,
     187,   -18,    -1,    16,    80,    63,   146,   185,   180,  -124,
    -124,  -124,  -124,  -124,  -124,   181,  -124,  -124,  -124,   -31,
    -124,   113,  -124,  -124,   182,   183,  -124,   184,   186,   188,
      93,    93,  -124,  -124,   196,   198,   152,    93,    93,    93,
      93,   189,   190,  -124,  -124,   191,   192,   193,   194,   195,
     197,   199,  -124,   200,   201,   202,   203,    77,    99,   107,
      80,    80,    80,  -124,  -124,  -124,  -124,  -124,  -124
  };

  const signed char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    40,    19,    20,     2,     4,     0,    39,     0,     0,
       0,     0,     0,     3,     1,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,    41,    42,     0,    43,     0,    46,     0,     0,
      47,    48,    49,    50,    25,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    26,     0,     0,     0,     0,     0,
      62,    63,    27,    52,    51,     0,    35,     0,    34,     7,
       8,     9,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    10,    21,    12,    23,     0,    64,    65,    28,     0,
      30,     0,    32,    14,    37,     0,    15,     0,     0,     0,
       0,     0,    68,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    31,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    22,    13,    24,    16,    36
  };

  const short
  EvalParser::yypgoto_[] =
  {
    -124,  -124,  -124,     2,    -2,  -124,   174,   -54,  -123,   154,
    -124,   -11,  -124,  -124,  -124,  -124,  -124
  };

  const short
  EvalParser::yydefgoto_[] =
  {
      -1,     3,    24,    25,    26,    27,    64,    66,   142,    68,
      74,    95,    84,    92,   148,   127,   164
  };

  const unsigned char
  EvalParser::yytable_[] =
  {
      33,   144,   153,   103,   162,    34,    35,    36,   155,    53,
      54,   144,    75,    76,    77,    78,    79,    80,    81,   156,
      93,   163,   138,    53,    54,   157,    94,    82,    83,   154,
      37,   139,   140,   141,   139,   140,   139,   140,   143,   113,
      97,    85,    86,    38,    88,    89,   145,    87,   105,   106,
     146,   147,     4,   101,     5,    99,   100,    40,     6,     7,
       8,     9,    90,    91,   194,   196,   198,   194,   196,   198,
      10,    61,   158,    53,    54,    11,   146,   147,    70,    71,
      72,    73,    62,    12,    63,    39,    13,    14,    15,    16,
      17,     1,     2,    18,    19,   139,   140,   193,   139,   140,
      20,    21,    22,    49,    23,    50,   171,   172,    41,    42,
     128,   129,   130,   176,   177,   178,   179,   139,   140,   195,
      43,    48,    28,    29,    30,   139,   140,   197,    44,    51,
      59,    52,    50,    60,    10,    52,    45,    46,    47,    11,
      55,    56,    57,    58,    96,    65,    67,    12,    69,   165,
      13,    14,    15,    16,    17,   107,    98,    31,    32,   108,
     109,   110,   115,   116,    20,    21,    22,   111,    23,   117,
      53,   118,   112,   114,   126,   119,   120,   121,   122,   150,
     123,   149,   124,   125,   131,   132,   133,   134,   135,   136,
     137,   152,   151,   154,   159,   160,   161,   166,   167,   168,
     173,   169,   174,   170,   175,   180,   181,   182,   183,   184,
     185,   186,   104,     0,   187,     0,   188,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     102
  };

  const short
  EvalParser::yycheck_[] =
  {
       2,   124,    20,    57,    35,     0,     4,     5,     9,     6,
       7,   134,    27,    28,    29,    30,    31,    32,    33,    20,
      46,    52,     9,     6,     7,     9,    52,    42,    43,    47,
      15,    18,    19,    20,    18,    19,    18,    19,    20,    36,
      51,    43,    44,    15,    46,    47,     9,    45,    59,    60,
      13,    14,     3,    55,     5,    53,    54,     3,     9,    10,
      11,    12,    42,    43,   187,   188,   189,   190,   191,   192,
      21,     4,     9,     6,     7,    26,    13,    14,    22,    23,
      24,    25,    52,    34,    54,    15,    37,    38,    39,    40,
      41,    49,    50,    44,    45,    18,    19,    20,    18,    19,
      51,    52,    53,    15,    55,    17,   160,   161,    17,    17,
     112,   113,   114,   167,   168,   169,   170,    18,    19,    20,
       3,    17,     9,    10,    11,    18,    19,    20,     3,    15,
      15,    17,    17,    15,    21,    17,     3,     3,     3,    26,
       8,    15,    15,    15,    48,    52,    52,    34,    51,   151,
      37,    38,    39,    40,    41,    16,    48,    44,    45,    16,
      16,     4,     4,    16,    51,    52,    53,    36,    55,    16,
       6,    16,    36,    36,    52,    16,    16,    16,    16,     4,
      17,    36,    17,    17,    17,    17,    17,    17,    17,    17,
      17,     4,    36,    47,     9,    15,    15,    15,    15,    15,
       4,    15,     4,    15,    52,    16,    16,    16,    16,    16,
      16,    16,    58,    -1,    17,    -1,    17,    17,    17,    17,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56
  };

  const signed char
  EvalParser::yystos_[] =
  {
       0,    49,    50,    57,     3,     5,     9,    10,    11,    12,
      21,    26,    34,    37,    38,    39,    40,    41,    44,    45,
      51,    52,    53,    55,    58,    59,    60,    61,     9,    10,
      11,    44,    45,    60,     0,    59,    59,    15,    15,    15,
       3,    17,    17,     3,     3,     3,     3,     3,    17,    15,
      17,    15,    17,     6,     7,     8,    15,    15,    15,    15,
      15,     4,    52,    54,    62,    52,    63,    52,    65,    51,
      22,    23,    24,    25,    66,    27,    28,    29,    30,    31,
      32,    33,    42,    43,    68,    60,    60,    59,    60,    60,
      42,    43,    69,    46,    52,    67,    48,    67,    48,    59,
      59,    60,    62,    63,    65,    67,    67,    16,    16,    16,
       4,    36,    36,    36,    36,     4,    16,    16,    16,    16,
      16,    16,    16,    17,    17,    17,    52,    71,    60,    60,
      60,    17,    17,    17,    17,    17,    17,    17,     9,    18,
      19,    20,    64,    20,    64,     9,    13,    14,    70,    36,
       4,    36,     4,    20,    47,     9,    20,     9,     9,     9,
      15,    15,    35,    52,    72,    60,    15,    15,    15,    15,
      15,    63,    63,     4,     4,    52,    63,    63,    63,    63,
      16,    16,    16,    16,    16,    16,    16,    17,    17,    17,
      17,    17,    17,    20,    64,    20,    64,    20,    64
  };

  const signed char
  EvalParser::yyr1_[] =
  {
       0,    56,    57,    57,    58,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    62,    62,    63,    64,    64,    65,    66,    66,    66,
      66,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    72,    72
  };

  const signed char
  EvalParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     3,     2,     3,     3,     3,
       6,    11,     6,    11,     6,     6,    11,     4,     1,     1,
       1,     6,    11,     6,    11,     3,     3,     3,     6,     8,
       6,     8,     6,     4,     3,     3,    11,     6,     9,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
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
  "\"addrtotext\"", "\"pkt6\"", "\"msgtype\"", "\"transid\"",
  "\"vendor-class\"", "\"vendor\"", "\"*\"", "\"data\"", "\"enterprise\"",
  "\"top-level bool\"", "\"top-level string\"", "\"constant string\"",
  "\"integer\"", "\"constant hexstring\"", "\"option name\"",
  "\"ip address\"", "$accept", "start", "expression", "bool_expr",
  "string_expr", "integer_expr", "option_code", "sub_option_code",
  "option_repr_type", "nest_level", "pkt_metadata", "enterprise_id",
  "pkt4_field", "pkt6_field", "relay6_field", "start_expr", "length_expr", YY_NULLPTR
  };

#if EVALDEBUG
  const short
  EvalParser::yyrline_[] =
  {
       0,   122,   122,   123,   128,   131,   132,   137,   142,   147,
     152,   157,   162,   182,   196,   205,   214,   224,   241,   246,
     251,   256,   261,   266,   287,   302,   307,   321,   335,   350,
     355,   360,   365,   370,   375,   384,   394,   403,   416,   429,
     436,   442,   446,   452,   458,   462,   468,   477,   481,   485,
     489,   495,   499,   505,   509,   513,   517,   521,   525,   529,
     533,   537,   543,   547,   553,   557,   563,   570,   575
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
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  EvalParser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
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


#line 14 "parser.yy"
} } // isc::eval
#line 2055 "parser.cc"

#line 582 "parser.yy"

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
