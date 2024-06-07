// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   evallex



#include "parser.h"


// Unqualified %code blocks.
#line 33 "parser.yy"

# include "eval_context.h"

// Avoid warnings with the error counter.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#line 57 "parser.cc"


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
      yy_stack_print_ ();                \
  } while (false)

#else // !EVALDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
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
#line 150 "parser.cc"

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

  /*---------.
  | symbol.  |
  `---------*/



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

  EvalParser::symbol_kind_type
  EvalParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  EvalParser::stack_symbol_type::stack_symbol_type ()
  {}

  EvalParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.YY_MOVE_OR_COPY< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.YY_MOVE_OR_COPY< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.YY_MOVE_OR_COPY< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.YY_MOVE_OR_COPY< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.YY_MOVE_OR_COPY< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.YY_MOVE_OR_COPY< int8_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.YY_MOVE_OR_COPY< uint16_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
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
    switch (that.kind ())
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.move< TokenOption::RepresentationType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.move< TokenPkt4::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.move< TokenPkt6::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.move< TokenPkt::MetadataType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.move< TokenRelay6Field::FieldType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.move< int8_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.move< uint16_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
        value.move< uint32_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  EvalParser::stack_symbol_type&
  EvalParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.copy< TokenOption::RepresentationType > (that.value);
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.copy< TokenPkt4::FieldType > (that.value);
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.copy< TokenPkt6::FieldType > (that.value);
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.copy< TokenPkt::MetadataType > (that.value);
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.copy< TokenRelay6Field::FieldType > (that.value);
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.copy< int8_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.copy< uint16_t > (that.value);
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
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
    switch (that.kind ())
    {
      case symbol_kind::S_option_repr_type: // option_repr_type
        value.move< TokenOption::RepresentationType > (that.value);
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        value.move< TokenPkt4::FieldType > (that.value);
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        value.move< TokenPkt6::FieldType > (that.value);
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        value.move< TokenPkt::MetadataType > (that.value);
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        value.move< TokenRelay6Field::FieldType > (that.value);
        break;

      case symbol_kind::S_nest_level: // nest_level
        value.move< int8_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        value.move< uint16_t > (that.value);
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
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
  EvalParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_STRING: // "constant string"
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 469 "parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 475 "parser.cc"
        break;

      case symbol_kind::S_HEXSTRING: // "constant hexstring"
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 481 "parser.cc"
        break;

      case symbol_kind::S_OPTION_NAME: // "option name"
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 487 "parser.cc"
        break;

      case symbol_kind::S_IP_ADDRESS: // "ip address"
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 493 "parser.cc"
        break;

      case symbol_kind::S_integer_expr: // integer_expr
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 499 "parser.cc"
        break;

      case symbol_kind::S_option_code: // option_code
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 505 "parser.cc"
        break;

      case symbol_kind::S_sub_option_code: // sub_option_code
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 511 "parser.cc"
        break;

      case symbol_kind::S_option_repr_type: // option_repr_type
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenOption::RepresentationType > (); }
#line 517 "parser.cc"
        break;

      case symbol_kind::S_nest_level: // nest_level
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < int8_t > (); }
#line 523 "parser.cc"
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt::MetadataType > (); }
#line 529 "parser.cc"
        break;

      case symbol_kind::S_enterprise_id: // enterprise_id
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 535 "parser.cc"
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt4::FieldType > (); }
#line 541 "parser.cc"
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt6::FieldType > (); }
#line 547 "parser.cc"
        break;

      case symbol_kind::S_relay6_field: // relay6_field
#line 130 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenRelay6Field::FieldType > (); }
#line 553 "parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
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
  EvalParser::yypop_ (int n) YY_NOEXCEPT
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
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  EvalParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  EvalParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
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
    YY_STACK_PRINT ();

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
        YYCDEBUG << "Reading a token\n";
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

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
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
      case symbol_kind::S_option_repr_type: // option_repr_type
        yylhs.value.emplace< TokenOption::RepresentationType > ();
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
        yylhs.value.emplace< TokenPkt4::FieldType > ();
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
        yylhs.value.emplace< TokenPkt6::FieldType > ();
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
        yylhs.value.emplace< TokenPkt::MetadataType > ();
        break;

      case symbol_kind::S_relay6_field: // relay6_field
        yylhs.value.emplace< TokenRelay6Field::FieldType > ();
        break;

      case symbol_kind::S_nest_level: // nest_level
        yylhs.value.emplace< int8_t > ();
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_option_code: // option_code
      case symbol_kind::S_sub_option_code: // sub_option_code
        yylhs.value.emplace< uint16_t > ();
        break;

      case symbol_kind::S_integer_expr: // integer_expr
      case symbol_kind::S_enterprise_id: // enterprise_id
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
  case 6: // bool_expr: "not" bool_expr
#line 150 "parser.yy"
                {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 851 "parser.cc"
    break;

  case 7: // bool_expr: bool_expr "and" bool_expr
#line 155 "parser.yy"
                {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 860 "parser.cc"
    break;

  case 8: // bool_expr: bool_expr "or" bool_expr
#line 160 "parser.yy"
                {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 869 "parser.cc"
    break;

  case 9: // bool_expr: string_expr "==" string_expr
#line 165 "parser.yy"
                {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 878 "parser.cc"
    break;

  case 10: // bool_expr: "option" "[" option_code "]" "." "exists"
#line 170 "parser.yy"
                {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 887 "parser.cc"
    break;

  case 11: // bool_expr: "option" "[" option_code "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 175 "parser.yy"
                {
                    TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 896 "parser.cc"
    break;

  case 12: // bool_expr: "relay4" "[" sub_option_code "]" "." "exists"
#line 180 "parser.yy"
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
#line 920 "parser.cc"
    break;

  case 13: // bool_expr: "relay6" "[" nest_level "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 200 "parser.yy"
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
#line 938 "parser.cc"
    break;

  case 14: // bool_expr: "vendor-class" "[" enterprise_id "]" "." "exists"
#line 214 "parser.yy"
              {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 951 "parser.cc"
    break;

  case 15: // bool_expr: "vendor" "[" enterprise_id "]" "." "exists"
#line 223 "parser.yy"
              {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 964 "parser.cc"
    break;

  case 16: // bool_expr: "vendor" "[" enterprise_id "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 232 "parser.yy"
              {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), TokenOption::EXISTS, yystack_[3].value.as < uint16_t > ()));
                  ctx.expression.push_back(exist);
               }
#line 978 "parser.cc"
    break;

  case 17: // bool_expr: "member" "(" "constant string" ")"
#line 242 "parser.yy"
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
#line 997 "parser.cc"
    break;

  case 18: // bool_expr: "match" "(" "constant string" "," string_expr ")"
#line 257 "parser.yy"
              {
                  // Expression match('<regex>', <string_expr>)
                  //
                  // This token will check if the regular expression matches
                  // the string expression.
                  TokenPtr match(new TokenMatch(yystack_[3].value.as < std::string > ()));
                  ctx.expression.push_back(match);
              }
#line 1010 "parser.cc"
    break;

  case 19: // string_expr: "constant string"
#line 268 "parser.yy"
                  {
                      TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 1019 "parser.cc"
    break;

  case 20: // string_expr: "constant hexstring"
#line 273 "parser.yy"
                  {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 1028 "parser.cc"
    break;

  case 21: // string_expr: "ip address"
#line 278 "parser.yy"
                  {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 1037 "parser.cc"
    break;

  case 22: // string_expr: "option" "[" option_code "]" "." option_repr_type
#line 283 "parser.yy"
                  {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1046 "parser.cc"
    break;

  case 23: // string_expr: "option" "[" option_code "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 288 "parser.yy"
                  {
                      TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1055 "parser.cc"
    break;

  case 24: // string_expr: "relay4" "[" sub_option_code "]" "." option_repr_type
#line 293 "parser.yy"
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
#line 1079 "parser.cc"
    break;

  case 25: // string_expr: "relay6" "[" nest_level "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 314 "parser.yy"
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
#line 1097 "parser.cc"
    break;

  case 26: // string_expr: "pkt" "." pkt_metadata
#line 329 "parser.yy"
                  {
                      TokenPtr pkt_metadata(new TokenPkt(yystack_[0].value.as < TokenPkt::MetadataType > ()));
                      ctx.expression.push_back(pkt_metadata);
                  }
#line 1106 "parser.cc"
    break;

  case 27: // string_expr: "pkt4" "." pkt4_field
#line 334 "parser.yy"
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
#line 1124 "parser.cc"
    break;

  case 28: // string_expr: "pkt6" "." pkt6_field
#line 348 "parser.yy"
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
#line 1142 "parser.cc"
    break;

  case 29: // string_expr: "relay6" "[" nest_level "]" "." relay6_field
#line 362 "parser.yy"
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
#line 1160 "parser.cc"
    break;

  case 30: // string_expr: "substring" "(" string_expr "," start_expr "," length_expr ")"
#line 377 "parser.yy"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 1169 "parser.cc"
    break;

  case 31: // string_expr: "split" "(" string_expr "," string_expr "," int_expr ")"
#line 382 "parser.yy"
                  {
                      TokenPtr split(new TokenSplit());
                      ctx.expression.push_back(split);
                  }
#line 1178 "parser.cc"
    break;

  case 32: // string_expr: "concat" "(" string_expr "," string_expr ")"
#line 387 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1187 "parser.cc"
    break;

  case 33: // string_expr: string_expr "+" string_expr
#line 392 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1196 "parser.cc"
    break;

  case 34: // string_expr: "lcase" "(" string_expr ")"
#line 397 "parser.yy"
                  {
                      TokenPtr lcase(new TokenLowerCase());
                      ctx.expression.push_back(lcase);
                  }
#line 1205 "parser.cc"
    break;

  case 35: // string_expr: "ucase" "(" string_expr ")"
#line 402 "parser.yy"
                  {
                      TokenPtr ucase(new TokenUpperCase());
                      ctx.expression.push_back(ucase);
                  }
#line 1214 "parser.cc"
    break;

  case 36: // string_expr: "ifelse" "(" bool_expr "," string_expr "," string_expr ")"
#line 407 "parser.yy"
                  {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression.push_back(cond);
                  }
#line 1223 "parser.cc"
    break;

  case 37: // string_expr: "hexstring" "(" string_expr "," string_expr ")"
#line 412 "parser.yy"
                  {
                      TokenPtr tohex(new TokenToHexString());
                      ctx.expression.push_back(tohex);
                  }
#line 1232 "parser.cc"
    break;

  case 38: // string_expr: "addrtotext" "(" string_expr ")"
#line 417 "parser.yy"
                  {
                      TokenPtr addrtotext(new TokenIpAddressToText());
                      ctx.expression.push_back(addrtotext);
                  }
#line 1241 "parser.cc"
    break;

  case 39: // string_expr: "int8totext" "(" string_expr ")"
#line 422 "parser.yy"
                  {
                      TokenPtr int8totext(new TokenInt8ToText());
                      ctx.expression.push_back(int8totext);
                  }
#line 1250 "parser.cc"
    break;

  case 40: // string_expr: "int16totext" "(" string_expr ")"
#line 427 "parser.yy"
                  {
                      TokenPtr int16totext(new TokenInt16ToText());
                      ctx.expression.push_back(int16totext);
                  }
#line 1259 "parser.cc"
    break;

  case 41: // string_expr: "int32totext" "(" string_expr ")"
#line 432 "parser.yy"
                  {
                      TokenPtr int32totext(new TokenInt32ToText());
                      ctx.expression.push_back(int32totext);
                  }
#line 1268 "parser.cc"
    break;

  case 42: // string_expr: "uint8totext" "(" string_expr ")"
#line 437 "parser.yy"
                  {
                      TokenPtr uint8totext(new TokenUInt8ToText());
                      ctx.expression.push_back(uint8totext);
                  }
#line 1277 "parser.cc"
    break;

  case 43: // string_expr: "uint16totext" "(" string_expr ")"
#line 442 "parser.yy"
                  {
                      TokenPtr uint16totext(new TokenUInt16ToText());
                      ctx.expression.push_back(uint16totext);
                  }
#line 1286 "parser.cc"
    break;

  case 44: // string_expr: "uint32totext" "(" string_expr ")"
#line 447 "parser.yy"
                  {
                      TokenPtr uint32totext(new TokenUInt32ToText());
                      ctx.expression.push_back(uint32totext);
                  }
#line 1295 "parser.cc"
    break;

  case 45: // string_expr: "vendor" "." "enterprise"
#line 452 "parser.yy"
                {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1308 "parser.cc"
    break;

  case 46: // string_expr: "vendor-class" "." "enterprise"
#line 461 "parser.yy"
                {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1322 "parser.cc"
    break;

  case 47: // string_expr: "vendor" "[" enterprise_id "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 471 "parser.yy"
                {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), yystack_[0].value.as < TokenOption::RepresentationType > (), yystack_[3].value.as < uint16_t > ()));
                    ctx.expression.push_back(opt);
                }
#line 1335 "parser.cc"
    break;

  case 48: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data"
#line 480 "parser.yy"
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
#line 1352 "parser.cc"
    break;

  case 49: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data" "[" "integer" "]"
#line 493 "parser.yy"
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
#line 1369 "parser.cc"
    break;

  case 50: // string_expr: integer_expr
#line 506 "parser.yy"
                {
                    TokenPtr integer(new TokenInteger(yystack_[0].value.as < uint32_t > ()));
                    ctx.expression.push_back(integer);
                }
#line 1378 "parser.cc"
    break;

  case 52: // integer_expr: "integer"
#line 514 "parser.yy"
                 {
                     yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1386 "parser.cc"
    break;

  case 53: // option_code: "integer"
#line 520 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1394 "parser.cc"
    break;

  case 54: // option_code: "option name"
#line 524 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionName(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1402 "parser.cc"
    break;

  case 55: // sub_option_code: "integer"
#line 530 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1410 "parser.cc"
    break;

  case 56: // option_repr_type: "text"
#line 536 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1418 "parser.cc"
    break;

  case 57: // option_repr_type: "hex"
#line 540 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1426 "parser.cc"
    break;

  case 58: // nest_level: "integer"
#line 546 "parser.yy"
                 {
                     yylhs.value.as < int8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1434 "parser.cc"
    break;

  case 59: // pkt_metadata: "iface"
#line 555 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::IFACE;
                  }
#line 1442 "parser.cc"
    break;

  case 60: // pkt_metadata: "src"
#line 559 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::SRC;
                  }
#line 1450 "parser.cc"
    break;

  case 61: // pkt_metadata: "dst"
#line 563 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::DST;
                  }
#line 1458 "parser.cc"
    break;

  case 62: // pkt_metadata: "len"
#line 567 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::LEN;
                  }
#line 1466 "parser.cc"
    break;

  case 63: // enterprise_id: "integer"
#line 573 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                   }
#line 1474 "parser.cc"
    break;

  case 64: // enterprise_id: "*"
#line 577 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = 0;
                   }
#line 1482 "parser.cc"
    break;

  case 65: // pkt4_field: "mac"
#line 583 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1490 "parser.cc"
    break;

  case 66: // pkt4_field: "hlen"
#line 587 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1498 "parser.cc"
    break;

  case 67: // pkt4_field: "htype"
#line 591 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1506 "parser.cc"
    break;

  case 68: // pkt4_field: "ciaddr"
#line 595 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1514 "parser.cc"
    break;

  case 69: // pkt4_field: "giaddr"
#line 599 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1522 "parser.cc"
    break;

  case 70: // pkt4_field: "yiaddr"
#line 603 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1530 "parser.cc"
    break;

  case 71: // pkt4_field: "siaddr"
#line 607 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1538 "parser.cc"
    break;

  case 72: // pkt4_field: "msgtype"
#line 611 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::MSGTYPE;
                 }
#line 1546 "parser.cc"
    break;

  case 73: // pkt4_field: "transid"
#line 615 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::TRANSID;
                 }
#line 1554 "parser.cc"
    break;

  case 74: // pkt6_field: "msgtype"
#line 621 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE;
                 }
#line 1562 "parser.cc"
    break;

  case 75: // pkt6_field: "transid"
#line 625 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::TRANSID;
                 }
#line 1570 "parser.cc"
    break;

  case 76: // relay6_field: "peeraddr"
#line 631 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR;
                   }
#line 1578 "parser.cc"
    break;

  case 77: // relay6_field: "linkaddr"
#line 635 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR;
                   }
#line 1586 "parser.cc"
    break;

  case 78: // start_expr: "integer"
#line 641 "parser.yy"
                {
                    TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                    ctx.expression.push_back(str);
                }
#line 1595 "parser.cc"
    break;

  case 79: // length_expr: "integer"
#line 648 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1604 "parser.cc"
    break;

  case 80: // length_expr: "all"
#line 653 "parser.yy"
                 {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 1613 "parser.cc"
    break;

  case 81: // int_expr: "integer"
#line 659 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1622 "parser.cc"
    break;


#line 1626 "parser.cc"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
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
    {
      stack_symbol_type error_token;

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
    YY_STACK_PRINT ();
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

  std::string
  EvalParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // EvalParser::context.
  EvalParser::context::context (const EvalParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  EvalParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  EvalParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
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

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  EvalParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

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
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short EvalParser::yypact_ninf_ = -164;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short
  EvalParser::yypact_[] =
  {
      55,   124,   182,    22,   124,   124,    56,    59,    68,    27,
     108,   115,    45,   100,   154,   157,   160,   178,   181,   186,
     210,   211,   212,   215,   216,   218,   217,    83,   111,   232,
    -164,  -164,  -164,  -164,  -164,   131,    10,  -164,   182,   223,
     224,   225,   165,   179,   202,  -164,    19,     0,  -164,   132,
     180,   184,   187,    96,    61,   182,   182,   182,   124,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,    91,
     -36,   192,   -36,   193,   190,   124,   124,   182,   182,     2,
     132,   180,   184,   -36,   -36,  -164,  -164,  -164,  -164,   226,
    -164,   237,  -164,   238,   251,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
     162,   163,   167,    80,   168,     5,     6,     7,     8,    11,
      12,    13,    17,    29,  -164,  -164,  -164,  -164,  -164,   240,
    -164,   241,  -164,   221,  -164,   253,   202,  -164,   244,   245,
     246,   247,   248,   249,   250,   252,  -164,   205,   182,   182,
     182,   182,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,   254,   255,   182,   256,   257,   258,   259,   260,    86,
      92,    15,  -164,   228,   172,    30,   173,    31,   -17,    87,
      33,    90,   158,    88,   213,   269,   264,  -164,  -164,  -164,
    -164,  -164,  -164,   265,  -164,  -164,  -164,   -31,   219,  -164,
     182,  -164,  -164,   266,   268,  -164,  -164,   270,   271,   272,
     180,   180,  -164,  -164,   280,  -164,   284,    34,   227,   180,
     180,   180,   180,   273,   275,  -164,  -164,  -164,   276,   277,
     278,   279,   281,   282,   283,  -164,   285,   286,   287,   288,
     104,   133,   136,   158,   158,   158,  -164,  -164,  -164,  -164,
    -164,  -164
  };

  const signed char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,    52,    20,    21,     2,     4,     0,    50,     0,     0,
       0,     0,     0,     0,     3,     1,     0,     0,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,    51,    53,    54,     0,
      55,     0,    58,     0,     0,    59,    60,    61,    62,    26,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    74,    75,    28,    64,    63,     0,
      46,     0,    45,     0,     7,     8,     9,    33,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,     0,
       0,     0,    38,    39,    40,    41,    42,    43,    44,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,    10,
      22,    12,    24,     0,    76,    77,    29,     0,     0,    32,
       0,    37,    14,    48,     0,    15,    18,     0,     0,     0,
       0,     0,    80,    79,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    31,    36,     0,     0,
       0,     0,     0,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    23,    13,    25,
      16,    47
  };

  const short
  EvalParser::yypgoto_[] =
  {
    -164,  -164,  -164,     9,    -2,  -164,   229,   -80,  -163,   214,
    -164,   -41,  -164,  -164,  -164,  -164,  -164,  -164
  };

  const unsigned char
  EvalParser::yydefgoto_[] =
  {
       0,     3,    34,    35,    36,    37,    89,    91,   190,    93,
      99,   129,   109,   126,   196,   173,   214,   216
  };

  const unsigned char
  EvalParser::yytable_[] =
  {
      44,   139,    47,   202,    86,   212,    86,   192,    77,   152,
     153,   154,   155,    46,    48,   156,   157,   158,    77,   192,
     127,   159,    45,    85,   193,    75,    76,   128,   194,   195,
      52,   131,   213,   160,   199,   201,    79,   206,   227,    78,
     203,    78,   141,   142,    78,    78,    78,    78,    55,    78,
      78,    78,    78,   110,   111,   112,    78,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   113,    78,    78,
      78,    49,    78,    78,    50,   136,   137,   247,   249,   251,
     247,   249,   251,    51,   134,   135,    75,    76,   100,   101,
     102,   103,   104,   105,   106,   186,   204,   208,    70,   207,
      71,   194,   195,    56,   187,   188,   189,   205,   187,   188,
     187,   188,   191,   107,   108,     1,     2,   150,    95,    96,
      97,    98,   187,   188,   246,    53,    72,     4,    73,     5,
     223,   224,    54,     6,     7,     8,     9,    75,    76,   229,
     230,   231,   232,   124,   125,    10,   174,   175,   176,   177,
      11,   187,   188,   248,   187,   188,   250,    57,    12,    13,
      58,   180,    14,    59,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,   187,   188,    27,    28,
      83,    60,    71,    29,    61,    38,    30,    31,    32,    62,
      33,    39,    40,    41,    84,    87,    73,    88,   217,   147,
     148,    78,    78,    10,   149,   151,    78,    78,    11,   198,
     200,    78,    78,    63,    64,    65,    12,    13,    66,    67,
      14,    68,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    69,    74,    42,    43,    80,    81,
      82,    78,   143,    90,    30,    31,    32,    92,    33,    94,
     130,   132,   133,   144,   145,   146,   161,   162,   163,    75,
     164,   165,   166,   167,   168,   197,   169,   170,   172,   171,
     203,   178,   179,   181,   182,   183,   184,   185,   209,   210,
     211,   218,   215,   219,   225,   220,   221,   222,   226,   233,
     228,   234,   235,   236,   237,   238,   140,   239,     0,   240,
     241,     0,   242,   243,   244,   245,     0,     0,     0,   138
  };

  const short
  EvalParser::yycheck_[] =
  {
       2,    81,     4,    20,     4,    36,     4,   170,     8,     4,
       4,     4,     4,     4,     5,     4,     4,     4,     8,   182,
      56,     4,     0,     4,     9,     6,     7,    63,    13,    14,
       3,    72,    63,     4,     4,     4,    38,     4,     4,    39,
      57,    39,    83,    84,    39,    39,    39,    39,     3,    39,
      39,    39,    39,    55,    56,    57,    39,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    58,    39,    39,
      39,    15,    39,    39,    15,    77,    78,   240,   241,   242,
     243,   244,   245,    15,    75,    76,     6,     7,    27,    28,
      29,    30,    31,    32,    33,     9,     9,     9,    15,     9,
      17,    13,    14,     3,    18,    19,    20,    20,    18,    19,
      18,    19,    20,    52,    53,    60,    61,    37,    22,    23,
      24,    25,    18,    19,    20,    17,    15,     3,    17,     5,
     210,   211,    17,     9,    10,    11,    12,     6,     7,   219,
     220,   221,   222,    52,    53,    21,   148,   149,   150,   151,
      26,    18,    19,    20,    18,    19,    20,     3,    34,    35,
       3,   163,    38,     3,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    18,    19,    54,    55,
      15,     3,    17,    59,     3,     3,    62,    63,    64,     3,
      66,     9,    10,    11,    15,    63,    17,    65,   200,    37,
      37,    39,    39,    21,    37,    37,    39,    39,    26,    37,
      37,    39,    39,     3,     3,     3,    34,    35,     3,     3,
      38,     3,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    17,     3,    54,    55,    15,    15,
      15,    39,    16,    63,    62,    63,    64,    63,    66,    62,
      58,    58,    62,    16,    16,     4,    16,    16,    37,     6,
      16,    16,    16,    16,    16,    37,    17,    17,    63,    17,
      57,    17,    17,    17,    17,    17,    17,    17,     9,    15,
      15,    15,    63,    15,     4,    15,    15,    15,     4,    16,
      63,    16,    16,    16,    16,    16,    82,    16,    -1,    17,
      17,    -1,    17,    17,    17,    17,    -1,    -1,    -1,    80
  };

  const signed char
  EvalParser::yystos_[] =
  {
       0,    60,    61,    68,     3,     5,     9,    10,    11,    12,
      21,    26,    34,    35,    38,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    54,    55,    59,
      62,    63,    64,    66,    69,    70,    71,    72,     3,     9,
      10,    11,    54,    55,    71,     0,    70,    71,    70,    15,
      15,    15,     3,    17,    17,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,    17,
      15,    17,    15,    17,     3,     6,     7,     8,    39,    71,
      15,    15,    15,    15,    15,     4,     4,    63,    65,    73,
      63,    74,    63,    76,    62,    22,    23,    24,    25,    77,
      27,    28,    29,    30,    31,    32,    33,    52,    53,    79,
      71,    71,    71,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    52,    53,    80,    56,    63,    78,
      58,    78,    58,    62,    70,    70,    71,    71,    73,    74,
      76,    78,    78,    16,    16,    16,     4,    37,    37,    37,
      37,    37,     4,     4,     4,     4,     4,     4,     4,     4,
       4,    16,    16,    37,    16,    16,    16,    16,    16,    17,
      17,    17,    63,    82,    71,    71,    71,    71,    17,    17,
      71,    17,    17,    17,    17,    17,     9,    18,    19,    20,
      75,    20,    75,     9,    13,    14,    81,    37,    37,     4,
      37,     4,    20,    57,     9,    20,     4,     9,     9,     9,
      15,    15,    36,    63,    83,    63,    84,    71,    15,    15,
      15,    15,    15,    74,    74,     4,     4,     4,    63,    74,
      74,    74,    74,    16,    16,    16,    16,    16,    16,    16,
      17,    17,    17,    17,    17,    17,    20,    75,    20,    75,
      20,    75
  };

  const signed char
  EvalParser::yyr1_[] =
  {
       0,    67,    68,    68,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    73,    73,    74,    75,    75,    76,    77,
      77,    77,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    80,    80,    81,    81,    82,    83,
      83,    84
  };

  const signed char
  EvalParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     3,     2,     3,     3,     3,
       6,    11,     6,    11,     6,     6,    11,     4,     6,     1,
       1,     1,     6,    11,     6,    11,     3,     3,     3,     6,
       8,     8,     6,     3,     4,     4,     8,     6,     4,     4,
       4,     4,     4,     4,     4,     3,     3,    11,     6,     9,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
  };


#if EVALDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const EvalParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"(\"", "\")\"",
  "\"not\"", "\"and\"", "\"or\"", "\"==\"", "\"option\"", "\"relay4\"",
  "\"relay6\"", "\"member\"", "\"peeraddr\"", "\"linkaddr\"", "\"[\"",
  "\"]\"", "\".\"", "\"text\"", "\"hex\"", "\"exists\"", "\"pkt\"",
  "\"iface\"", "\"src\"", "\"dst\"", "\"len\"", "\"pkt4\"", "\"mac\"",
  "\"hlen\"", "\"htype\"", "\"ciaddr\"", "\"giaddr\"", "\"yiaddr\"",
  "\"siaddr\"", "\"substring\"", "\"split\"", "\"all\"", "\",\"",
  "\"concat\"", "\"+\"", "\"ifelse\"", "\"hexstring\"", "\"addrtotext\"",
  "\"int8totext\"", "\"int16totext\"", "\"int32totext\"",
  "\"uint8totext\"", "\"uint16totext\"", "\"uint32totext\"", "\"lcase\"",
  "\"ucase\"", "\"pkt6\"", "\"msgtype\"", "\"transid\"",
  "\"vendor-class\"", "\"vendor\"", "\"*\"", "\"data\"", "\"enterprise\"",
  "\"match\"", "\"top-level bool\"", "\"top-level string\"",
  "\"constant string\"", "\"integer\"", "\"constant hexstring\"",
  "\"option name\"", "\"ip address\"", "$accept", "start", "expression",
  "bool_expr", "string_expr", "integer_expr", "option_code",
  "sub_option_code", "option_repr_type", "nest_level", "pkt_metadata",
  "enterprise_id", "pkt4_field", "pkt6_field", "relay6_field",
  "start_expr", "length_expr", "int_expr", YY_NULLPTR
  };
#endif


#if EVALDEBUG
  const short
  EvalParser::yyrline_[] =
  {
       0,   139,   139,   140,   145,   148,   149,   154,   159,   164,
     169,   174,   179,   199,   213,   222,   231,   241,   256,   267,
     272,   277,   282,   287,   292,   313,   328,   333,   347,   361,
     376,   381,   386,   391,   396,   401,   406,   411,   416,   421,
     426,   431,   436,   441,   446,   451,   460,   470,   479,   492,
     505,   510,   513,   519,   523,   529,   535,   539,   545,   554,
     558,   562,   566,   572,   576,   582,   586,   590,   594,   598,
     602,   606,   610,   614,   620,   624,   630,   634,   640,   647,
     652,   658
  };

  void
  EvalParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  EvalParser::yy_reduce_print_ (int yyrule) const
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
#line 2264 "parser.cc"

#line 665 "parser.yy"

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
