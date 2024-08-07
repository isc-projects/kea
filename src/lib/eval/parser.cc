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
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 469 "parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 475 "parser.cc"
        break;

      case symbol_kind::S_HEXSTRING: // "constant hexstring"
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 481 "parser.cc"
        break;

      case symbol_kind::S_OPTION_NAME: // "option name"
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 487 "parser.cc"
        break;

      case symbol_kind::S_IP_ADDRESS: // "ip address"
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 493 "parser.cc"
        break;

      case symbol_kind::S_integer_expr: // integer_expr
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 499 "parser.cc"
        break;

      case symbol_kind::S_option_code: // option_code
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 505 "parser.cc"
        break;

      case symbol_kind::S_sub_option_code: // sub_option_code
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 511 "parser.cc"
        break;

      case symbol_kind::S_option_repr_type: // option_repr_type
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenOption::RepresentationType > (); }
#line 517 "parser.cc"
        break;

      case symbol_kind::S_nest_level: // nest_level
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < int8_t > (); }
#line 523 "parser.cc"
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt::MetadataType > (); }
#line 529 "parser.cc"
        break;

      case symbol_kind::S_enterprise_id: // enterprise_id
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 535 "parser.cc"
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt4::FieldType > (); }
#line 541 "parser.cc"
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
#line 135 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt6::FieldType > (); }
#line 547 "parser.cc"
        break;

      case symbol_kind::S_relay6_field: // relay6_field
#line 135 "parser.yy"
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
#line 155 "parser.yy"
                {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 851 "parser.cc"
    break;

  case 7: // $@1: %empty
#line 160 "parser.yy"
                {
                    unsigned target = ++ctx.label;
                    ctx.labels.push_back(target);
                    TokenPtr pobf(new TokenPopOrBranchFalse(target));
                    ctx.expression.push_back(pobf);
                }
#line 862 "parser.cc"
    break;

  case 8: // bool_expr: bool_expr "and" $@1 bool_expr
#line 165 "parser.yy"
                            {
                    unsigned target = ctx.labels.back();
                    ctx.labels.pop_back();
                    TokenPtr lab(new TokenLabel(target));
                    ctx.expression.push_back(lab);
                }
#line 873 "parser.cc"
    break;

  case 9: // bool_expr: bool_expr "sand" bool_expr
#line 172 "parser.yy"
                {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 882 "parser.cc"
    break;

  case 10: // $@2: %empty
#line 177 "parser.yy"
                {
                    unsigned target = ++ctx.label;
                    ctx.labels.push_back(target);
                    TokenPtr pobt(new TokenPopOrBranchTrue(target));
                    ctx.expression.push_back(pobt);
                }
#line 893 "parser.cc"
    break;

  case 11: // bool_expr: bool_expr "or" $@2 bool_expr
#line 182 "parser.yy"
                            {
                    unsigned target = ctx.labels.back();
                    ctx.labels.pop_back();
                    TokenPtr lab(new TokenLabel(target));
                    ctx.expression.push_back(lab);
                }
#line 904 "parser.cc"
    break;

  case 12: // bool_expr: bool_expr "sor" bool_expr
#line 189 "parser.yy"
                {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 913 "parser.cc"
    break;

  case 13: // bool_expr: string_expr "==" string_expr
#line 194 "parser.yy"
                {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 922 "parser.cc"
    break;

  case 14: // bool_expr: "option" "[" option_code "]" "." "exists"
#line 199 "parser.yy"
                {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 931 "parser.cc"
    break;

  case 15: // bool_expr: "option" "[" option_code "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 204 "parser.yy"
                {
                    TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 940 "parser.cc"
    break;

  case 16: // bool_expr: "relay4" "[" sub_option_code "]" "." "exists"
#line 209 "parser.yy"
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
#line 964 "parser.cc"
    break;

  case 17: // bool_expr: "relay6" "[" nest_level "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 229 "parser.yy"
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
#line 982 "parser.cc"
    break;

  case 18: // bool_expr: "vendor-class" "[" enterprise_id "]" "." "exists"
#line 243 "parser.yy"
              {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 995 "parser.cc"
    break;

  case 19: // bool_expr: "vendor" "[" enterprise_id "]" "." "exists"
#line 252 "parser.yy"
              {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 1008 "parser.cc"
    break;

  case 20: // bool_expr: "vendor" "[" enterprise_id "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 261 "parser.yy"
              {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), TokenOption::EXISTS, yystack_[3].value.as < uint16_t > ()));
                  ctx.expression.push_back(exist);
               }
#line 1022 "parser.cc"
    break;

  case 21: // bool_expr: "member" "(" "constant string" ")"
#line 271 "parser.yy"
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
#line 1041 "parser.cc"
    break;

  case 22: // bool_expr: "match" "(" "constant string" "," string_expr ")"
#line 286 "parser.yy"
              {
                  // Expression match('<regex>', <string_expr>)
                  //
                  // This token will check if the regular expression matches
                  // the string expression.
                  TokenPtr match(new TokenMatch(yystack_[3].value.as < std::string > ()));
                  ctx.expression.push_back(match);
              }
#line 1054 "parser.cc"
    break;

  case 23: // string_expr: "constant string"
#line 297 "parser.yy"
                  {
                      TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 1063 "parser.cc"
    break;

  case 24: // string_expr: "constant hexstring"
#line 302 "parser.yy"
                  {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 1072 "parser.cc"
    break;

  case 25: // string_expr: "ip address"
#line 307 "parser.yy"
                  {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 1081 "parser.cc"
    break;

  case 26: // string_expr: "option" "[" option_code "]" "." option_repr_type
#line 312 "parser.yy"
                  {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1090 "parser.cc"
    break;

  case 27: // string_expr: "option" "[" option_code "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 317 "parser.yy"
                  {
                      TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1099 "parser.cc"
    break;

  case 28: // string_expr: "relay4" "[" sub_option_code "]" "." option_repr_type
#line 322 "parser.yy"
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
#line 1123 "parser.cc"
    break;

  case 29: // string_expr: "relay6" "[" nest_level "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 343 "parser.yy"
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
#line 1141 "parser.cc"
    break;

  case 30: // string_expr: "pkt" "." pkt_metadata
#line 358 "parser.yy"
                  {
                      TokenPtr pkt_metadata(new TokenPkt(yystack_[0].value.as < TokenPkt::MetadataType > ()));
                      ctx.expression.push_back(pkt_metadata);
                  }
#line 1150 "parser.cc"
    break;

  case 31: // string_expr: "pkt4" "." pkt4_field
#line 363 "parser.yy"
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
#line 1168 "parser.cc"
    break;

  case 32: // string_expr: "pkt6" "." pkt6_field
#line 377 "parser.yy"
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
#line 1186 "parser.cc"
    break;

  case 33: // string_expr: "relay6" "[" nest_level "]" "." relay6_field
#line 391 "parser.yy"
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
#line 1204 "parser.cc"
    break;

  case 34: // string_expr: "substring" "(" string_expr "," start_expr "," length_expr ")"
#line 406 "parser.yy"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 1213 "parser.cc"
    break;

  case 35: // string_expr: "split" "(" string_expr "," string_expr "," int_expr ")"
#line 411 "parser.yy"
                  {
                      TokenPtr split(new TokenSplit());
                      ctx.expression.push_back(split);
                  }
#line 1222 "parser.cc"
    break;

  case 36: // string_expr: "concat" "(" string_expr "," string_expr ")"
#line 416 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1231 "parser.cc"
    break;

  case 37: // string_expr: string_expr "+" string_expr
#line 421 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1240 "parser.cc"
    break;

  case 38: // string_expr: "lcase" "(" string_expr ")"
#line 426 "parser.yy"
                  {
                      TokenPtr lcase(new TokenLowerCase());
                      ctx.expression.push_back(lcase);
                  }
#line 1249 "parser.cc"
    break;

  case 39: // string_expr: "ucase" "(" string_expr ")"
#line 431 "parser.yy"
                  {
                      TokenPtr ucase(new TokenUpperCase());
                      ctx.expression.push_back(ucase);
                  }
#line 1258 "parser.cc"
    break;

  case 40: // $@3: %empty
#line 436 "parser.yy"
                  {
                      unsigned target = ++ctx.label;
                      ctx.labels.push_back(target);
                      TokenPtr pabf(new TokenPopAndBranchFalse(target));
                      ctx.expression.push_back(pabf);
                  }
#line 1269 "parser.cc"
    break;

  case 41: // $@4: %empty
#line 441 "parser.yy"
                                    {
                      unsigned target = ctx.labels.back();
                      ctx.labels.pop_back();
                      unsigned target2 = ++ctx.label;
                      ctx.labels.push_back(target2);
                      TokenPtr branch(new TokenBranch(target2));
                      ctx.expression.push_back(branch);
                      TokenPtr lab(new TokenLabel(target));
                      ctx.expression.push_back(lab);
                  }
#line 1284 "parser.cc"
    break;

  case 42: // string_expr: "ifelse" "(" bool_expr "," $@3 string_expr "," $@4 string_expr ")"
#line 450 "parser.yy"
                                    {
                      unsigned target = ctx.labels.back();
                      ctx.labels.pop_back();
                      TokenPtr lab(new TokenLabel(target));
                      ctx.expression.push_back(lab);
                  }
#line 1295 "parser.cc"
    break;

  case 43: // string_expr: "sifelse" "(" bool_expr "," string_expr "," string_expr ")"
#line 457 "parser.yy"
                  {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression.push_back(cond);
                  }
#line 1304 "parser.cc"
    break;

  case 44: // string_expr: "hexstring" "(" string_expr "," string_expr ")"
#line 462 "parser.yy"
                  {
                      TokenPtr tohex(new TokenToHexString());
                      ctx.expression.push_back(tohex);
                  }
#line 1313 "parser.cc"
    break;

  case 45: // string_expr: "addrtotext" "(" string_expr ")"
#line 467 "parser.yy"
                  {
                      TokenPtr addrtotext(new TokenIpAddressToText());
                      ctx.expression.push_back(addrtotext);
                  }
#line 1322 "parser.cc"
    break;

  case 46: // string_expr: "int8totext" "(" string_expr ")"
#line 472 "parser.yy"
                  {
                      TokenPtr int8totext(new TokenInt8ToText());
                      ctx.expression.push_back(int8totext);
                  }
#line 1331 "parser.cc"
    break;

  case 47: // string_expr: "int16totext" "(" string_expr ")"
#line 477 "parser.yy"
                  {
                      TokenPtr int16totext(new TokenInt16ToText());
                      ctx.expression.push_back(int16totext);
                  }
#line 1340 "parser.cc"
    break;

  case 48: // string_expr: "int32totext" "(" string_expr ")"
#line 482 "parser.yy"
                  {
                      TokenPtr int32totext(new TokenInt32ToText());
                      ctx.expression.push_back(int32totext);
                  }
#line 1349 "parser.cc"
    break;

  case 49: // string_expr: "uint8totext" "(" string_expr ")"
#line 487 "parser.yy"
                  {
                      TokenPtr uint8totext(new TokenUInt8ToText());
                      ctx.expression.push_back(uint8totext);
                  }
#line 1358 "parser.cc"
    break;

  case 50: // string_expr: "uint16totext" "(" string_expr ")"
#line 492 "parser.yy"
                  {
                      TokenPtr uint16totext(new TokenUInt16ToText());
                      ctx.expression.push_back(uint16totext);
                  }
#line 1367 "parser.cc"
    break;

  case 51: // string_expr: "uint32totext" "(" string_expr ")"
#line 497 "parser.yy"
                  {
                      TokenPtr uint32totext(new TokenUInt32ToText());
                      ctx.expression.push_back(uint32totext);
                  }
#line 1376 "parser.cc"
    break;

  case 52: // string_expr: "vendor" "." "enterprise"
#line 502 "parser.yy"
                {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1389 "parser.cc"
    break;

  case 53: // string_expr: "vendor-class" "." "enterprise"
#line 511 "parser.yy"
                {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1403 "parser.cc"
    break;

  case 54: // string_expr: "vendor" "[" enterprise_id "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 521 "parser.yy"
                {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), yystack_[0].value.as < TokenOption::RepresentationType > (), yystack_[3].value.as < uint16_t > ()));
                    ctx.expression.push_back(opt);
                }
#line 1416 "parser.cc"
    break;

  case 55: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data"
#line 530 "parser.yy"
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
#line 1433 "parser.cc"
    break;

  case 56: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data" "[" "integer" "]"
#line 543 "parser.yy"
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
#line 1450 "parser.cc"
    break;

  case 57: // string_expr: integer_expr
#line 556 "parser.yy"
                {
                    TokenPtr integer(new TokenInteger(yystack_[0].value.as < uint32_t > ()));
                    ctx.expression.push_back(integer);
                }
#line 1459 "parser.cc"
    break;

  case 59: // integer_expr: "integer"
#line 564 "parser.yy"
                 {
                     yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1467 "parser.cc"
    break;

  case 60: // option_code: "integer"
#line 570 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1475 "parser.cc"
    break;

  case 61: // option_code: "option name"
#line 574 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionName(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1483 "parser.cc"
    break;

  case 62: // sub_option_code: "integer"
#line 580 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1491 "parser.cc"
    break;

  case 63: // option_repr_type: "text"
#line 586 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1499 "parser.cc"
    break;

  case 64: // option_repr_type: "hex"
#line 590 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1507 "parser.cc"
    break;

  case 65: // nest_level: "integer"
#line 596 "parser.yy"
                 {
                     yylhs.value.as < int8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1515 "parser.cc"
    break;

  case 66: // pkt_metadata: "iface"
#line 605 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::IFACE;
                  }
#line 1523 "parser.cc"
    break;

  case 67: // pkt_metadata: "src"
#line 609 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::SRC;
                  }
#line 1531 "parser.cc"
    break;

  case 68: // pkt_metadata: "dst"
#line 613 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::DST;
                  }
#line 1539 "parser.cc"
    break;

  case 69: // pkt_metadata: "len"
#line 617 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::LEN;
                  }
#line 1547 "parser.cc"
    break;

  case 70: // enterprise_id: "integer"
#line 623 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                   }
#line 1555 "parser.cc"
    break;

  case 71: // enterprise_id: "*"
#line 627 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = 0;
                   }
#line 1563 "parser.cc"
    break;

  case 72: // pkt4_field: "mac"
#line 633 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1571 "parser.cc"
    break;

  case 73: // pkt4_field: "hlen"
#line 637 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1579 "parser.cc"
    break;

  case 74: // pkt4_field: "htype"
#line 641 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1587 "parser.cc"
    break;

  case 75: // pkt4_field: "ciaddr"
#line 645 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1595 "parser.cc"
    break;

  case 76: // pkt4_field: "giaddr"
#line 649 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1603 "parser.cc"
    break;

  case 77: // pkt4_field: "yiaddr"
#line 653 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1611 "parser.cc"
    break;

  case 78: // pkt4_field: "siaddr"
#line 657 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1619 "parser.cc"
    break;

  case 79: // pkt4_field: "msgtype"
#line 661 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::MSGTYPE;
                 }
#line 1627 "parser.cc"
    break;

  case 80: // pkt4_field: "transid"
#line 665 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::TRANSID;
                 }
#line 1635 "parser.cc"
    break;

  case 81: // pkt6_field: "msgtype"
#line 671 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE;
                 }
#line 1643 "parser.cc"
    break;

  case 82: // pkt6_field: "transid"
#line 675 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::TRANSID;
                 }
#line 1651 "parser.cc"
    break;

  case 83: // relay6_field: "peeraddr"
#line 681 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR;
                   }
#line 1659 "parser.cc"
    break;

  case 84: // relay6_field: "linkaddr"
#line 685 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR;
                   }
#line 1667 "parser.cc"
    break;

  case 85: // start_expr: "integer"
#line 691 "parser.yy"
                {
                    TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                    ctx.expression.push_back(str);
                }
#line 1676 "parser.cc"
    break;

  case 86: // length_expr: "integer"
#line 698 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1685 "parser.cc"
    break;

  case 87: // length_expr: "all"
#line 703 "parser.yy"
                 {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 1694 "parser.cc"
    break;

  case 88: // int_expr: "integer"
#line 710 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1703 "parser.cc"
    break;


#line 1707 "parser.cc"

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


  const short EvalParser::yypact_ninf_ = -173;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short
  EvalParser::yypact_[] =
  {
     -45,   175,   236,     4,   175,   175,    61,   101,   107,    25,
      26,    82,   102,   149,   159,   179,   182,   192,   198,   205,
     206,   210,   211,   213,   227,   228,   232,   136,   156,   157,
     240,  -173,  -173,  -173,  -173,  -173,   134,     7,  -173,   236,
     151,   229,   233,   160,   164,   126,  -173,   113,     1,  -173,
     124,   185,   186,   180,   120,    79,   236,   236,   236,   175,
     175,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   -33,   -35,   193,   -35,   194,   188,  -173,   175,  -173,
     175,   236,   236,     2,   124,   185,   186,   -35,   -35,  -173,
    -173,  -173,  -173,   238,  -173,   239,  -173,   242,   254,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,   152,   155,   158,    68,    84,   161,
       3,     5,     6,     8,     9,    10,    11,    12,    16,  -173,
    -173,  -173,  -173,  -173,   243,  -173,   244,  -173,   224,   175,
     259,   175,   125,   126,  -173,   248,   249,   250,   251,   252,
     255,   256,   258,  -173,   225,   236,   236,  -173,   236,   236,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,   273,
     276,   236,  -173,    91,   277,   278,   279,   280,   281,    74,
     106,    88,  -173,   265,   165,    28,   236,   166,    29,   -19,
      18,    30,    95,   116,   114,   246,   260,   290,  -173,  -173,
    -173,  -173,  -173,  -173,   291,  -173,  -173,  -173,    -8,   245,
    -173,   195,   236,  -173,  -173,   292,   293,  -173,  -173,   295,
     296,   297,   185,   185,  -173,  -173,   311,  -173,   312,  -173,
      31,   253,   185,   185,   185,   185,   299,   300,  -173,  -173,
     236,  -173,   302,   303,   304,   305,   306,   307,   308,    32,
    -173,   309,   310,   313,   314,   138,   144,  -173,   150,   116,
     116,   116,  -173,  -173,  -173,  -173,  -173,  -173
  };

  const signed char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    59,    24,    25,     2,     4,     0,    57,     0,
       0,     0,     0,     0,     0,     3,     1,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     0,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
      58,    60,    61,     0,    62,     0,    65,     0,     0,    66,
      67,    68,    69,    30,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
      82,    32,    71,    70,     0,    53,     0,    52,     0,     0,
       9,     0,    12,    13,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,    40,     0,     0,
      45,    46,    47,    48,    49,    50,    51,    38,    39,     0,
       0,     0,     8,    11,     0,     0,     0,     0,     0,     0,
       0,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,    64,
      14,    26,    16,    28,     0,    83,    84,    33,     0,     0,
      36,     0,     0,    44,    18,    55,     0,    19,    22,     0,
       0,     0,     0,     0,    87,    86,     0,    88,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
      56,     0,     0,     0,     0,     0,     0,    42,     0,     0,
       0,     0,    15,    27,    17,    29,    20,    54
  };

  const short
  EvalParser::yypgoto_[] =
  {
    -173,  -173,  -173,    22,  -173,  -173,    -2,  -173,  -173,  -173,
     241,   -84,  -172,   257,  -173,   -49,  -173,  -173,  -173,  -173,
    -173,  -173
  };

  const unsigned char
  EvalParser::yydefgoto_[] =
  {
       0,     3,    35,    36,   139,   141,    37,   186,   240,    38,
      93,    95,   201,    97,   103,   134,   113,   131,   207,   183,
     226,   228
  };

  const short
  EvalParser::yytable_[] =
  {
      45,   146,    48,   214,    46,    90,    90,   160,   203,   161,
     162,    81,   163,   164,   165,   166,   167,    81,     1,     2,
     168,   203,   129,   130,   132,   136,    47,    49,    53,   216,
     224,   133,   210,   213,   218,   241,   257,    83,   148,   149,
     217,   215,    82,    82,    82,    54,    82,    82,    82,    82,
      82,    82,    82,    82,   114,   115,   116,    82,   225,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,    82,
      82,    82,    82,    82,    77,    78,    79,    80,    50,   143,
     144,   117,   118,   263,   265,   197,   267,   263,   265,   267,
      77,    78,    79,    80,   198,   199,   200,    77,    78,   204,
     140,    55,   142,   205,   206,    56,   219,   157,   104,   105,
     106,   107,   108,   109,   110,   198,   199,    89,    51,    77,
      78,    79,    80,   158,    52,   220,   198,   199,   202,   205,
     206,    77,    78,    79,   111,   112,   198,   199,   236,   237,
      77,    78,    79,    80,    99,   100,   101,   102,   243,   244,
     245,   246,    57,   184,   185,    71,   187,   188,   198,   199,
     262,   172,    58,   173,   198,   199,   264,    82,    84,   191,
     198,   199,   266,    72,    74,    73,    75,    87,     4,    73,
       5,    88,    59,    75,   211,    60,     6,     7,     8,     9,
      91,   154,    92,    82,   155,    61,    82,   156,    10,    82,
     159,    62,    82,    11,   209,   212,    82,    82,    63,    64,
     230,    12,    13,    65,    66,    14,    67,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      68,    69,    28,    29,   229,    70,    82,    30,   249,    39,
      31,    32,    33,    76,    34,    98,    85,    40,    41,    42,
      86,    94,    96,   138,   135,   137,   150,   151,   153,    10,
     152,   169,   170,   171,    11,    77,   174,   175,   176,   177,
     178,   221,    12,    13,   179,   180,    14,   181,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,   182,   189,    43,    44,   190,   192,   193,   194,   195,
     196,    31,    32,    33,   208,    34,   215,   222,   223,   231,
     232,   227,   233,   234,   235,   238,   239,   247,   248,   242,
     250,   251,   252,   253,   254,   145,   255,   256,   258,   259,
       0,     0,   260,   261,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147
  };

  const short
  EvalParser::yycheck_[] =
  {
       2,    85,     4,    22,     0,     4,     4,     4,   180,     4,
       4,    10,     4,     4,     4,     4,     4,    10,    63,    64,
       4,   193,    55,    56,    59,    74,     4,     5,     3,    11,
      38,    66,     4,     4,     4,     4,     4,    39,    87,    88,
      22,    60,    41,    41,    41,    19,    41,    41,    41,    41,
      41,    41,    41,    41,    56,    57,    58,    41,    66,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    41,
      41,    41,    41,    41,     6,     7,     8,     9,    17,    81,
      82,    59,    60,   255,   256,    11,   258,   259,   260,   261,
       6,     7,     8,     9,    20,    21,    22,     6,     7,    11,
      78,    19,    80,    15,    16,     3,    11,    39,    29,    30,
      31,    32,    33,    34,    35,    20,    21,     4,    17,     6,
       7,     8,     9,    39,    17,    11,    20,    21,    22,    15,
      16,     6,     7,     8,    55,    56,    20,    21,   222,   223,
       6,     7,     8,     9,    24,    25,    26,    27,   232,   233,
     234,   235,     3,   155,   156,    19,   158,   159,    20,    21,
      22,   139,     3,   141,    20,    21,    22,    41,    17,   171,
      20,    21,    22,    17,    17,    19,    19,    17,     3,    19,
       5,    17,     3,    19,   186,     3,    11,    12,    13,    14,
      66,    39,    68,    41,    39,     3,    41,    39,    23,    41,
      39,     3,    41,    28,    39,    39,    41,    41,     3,     3,
     212,    36,    37,     3,     3,    40,     3,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
       3,     3,    57,    58,    39,     3,    41,    62,   240,     3,
      65,    66,    67,     3,    69,    65,    17,    11,    12,    13,
      17,    66,    66,    65,    61,    61,    18,    18,     4,    23,
      18,    18,    18,    39,    28,     6,    18,    18,    18,    18,
      18,    11,    36,    37,    19,    19,    40,    19,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    66,    19,    57,    58,    19,    19,    19,    19,    19,
      19,    65,    66,    67,    39,    69,    60,    17,    17,    17,
      17,    66,    17,    17,    17,     4,     4,    18,    18,    66,
      18,    18,    18,    18,    18,    84,    19,    19,    19,    19,
      -1,    -1,    19,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86
  };

  const signed char
  EvalParser::yystos_[] =
  {
       0,    63,    64,    71,     3,     5,    11,    12,    13,    14,
      23,    28,    36,    37,    40,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    57,    58,
      62,    65,    66,    67,    69,    72,    73,    76,    79,     3,
      11,    12,    13,    57,    58,    76,     0,    73,    76,    73,
      17,    17,    17,     3,    19,    19,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,    19,    17,    19,    17,    19,     3,     6,     7,     8,
       9,    10,    41,    76,    17,    17,    17,    17,    17,     4,
       4,    66,    68,    80,    66,    81,    66,    83,    65,    24,
      25,    26,    27,    84,    29,    30,    31,    32,    33,    34,
      35,    55,    56,    86,    76,    76,    76,    73,    73,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    55,
      56,    87,    59,    66,    85,    61,    85,    61,    65,    74,
      73,    75,    73,    76,    76,    80,    81,    83,    85,    85,
      18,    18,    18,     4,    39,    39,    39,    39,    39,    39,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    18,
      18,    39,    73,    73,    18,    18,    18,    18,    18,    19,
      19,    19,    66,    89,    76,    76,    77,    76,    76,    19,
      19,    76,    19,    19,    19,    19,    19,    11,    20,    21,
      22,    82,    22,    82,    11,    15,    16,    88,    39,    39,
       4,    76,    39,     4,    22,    60,    11,    22,     4,    11,
      11,    11,    17,    17,    38,    66,    90,    66,    91,    39,
      76,    17,    17,    17,    17,    17,    81,    81,     4,     4,
      78,     4,    66,    81,    81,    81,    81,    18,    18,    76,
      18,    18,    18,    18,    18,    19,    19,     4,    19,    19,
      19,    19,    22,    82,    22,    82,    22,    82
  };

  const signed char
  EvalParser::yyr1_[] =
  {
       0,    70,    71,    71,    72,    73,    73,    74,    73,    73,
      75,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      77,    78,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    79,
      80,    80,    81,    82,    82,    83,    84,    84,    84,    84,
      85,    85,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    87,    87,    88,    88,    89,    90,    90,    91
  };

  const signed char
  EvalParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     3,     2,     0,     4,     3,
       0,     4,     3,     3,     6,    11,     6,    11,     6,     6,
      11,     4,     6,     1,     1,     1,     6,    11,     6,    11,
       3,     3,     3,     6,     8,     8,     6,     3,     4,     4,
       0,     0,    10,     8,     6,     4,     4,     4,     4,     4,
       4,     4,     3,     3,    11,     6,     9,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
  };


#if EVALDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const EvalParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"(\"", "\")\"",
  "\"not\"", "\"and\"", "\"sand\"", "\"or\"", "\"sor\"", "\"==\"",
  "\"option\"", "\"relay4\"", "\"relay6\"", "\"member\"", "\"peeraddr\"",
  "\"linkaddr\"", "\"[\"", "\"]\"", "\".\"", "\"text\"", "\"hex\"",
  "\"exists\"", "\"pkt\"", "\"iface\"", "\"src\"", "\"dst\"", "\"len\"",
  "\"pkt4\"", "\"mac\"", "\"hlen\"", "\"htype\"", "\"ciaddr\"",
  "\"giaddr\"", "\"yiaddr\"", "\"siaddr\"", "\"substring\"", "\"split\"",
  "\"all\"", "\",\"", "\"concat\"", "\"+\"", "\"ifelse\"", "\"sifelse\"",
  "\"hexstring\"", "\"addrtotext\"", "\"int8totext\"", "\"int16totext\"",
  "\"int32totext\"", "\"uint8totext\"", "\"uint16totext\"",
  "\"uint32totext\"", "\"lcase\"", "\"ucase\"", "\"pkt6\"", "\"msgtype\"",
  "\"transid\"", "\"vendor-class\"", "\"vendor\"", "\"*\"", "\"data\"",
  "\"enterprise\"", "\"match\"", "\"top-level bool\"",
  "\"top-level string\"", "\"constant string\"", "\"integer\"",
  "\"constant hexstring\"", "\"option name\"", "\"ip address\"", "$accept",
  "start", "expression", "bool_expr", "$@1", "$@2", "string_expr", "$@3",
  "$@4", "integer_expr", "option_code", "sub_option_code",
  "option_repr_type", "nest_level", "pkt_metadata", "enterprise_id",
  "pkt4_field", "pkt6_field", "relay6_field", "start_expr", "length_expr",
  "int_expr", YY_NULLPTR
  };
#endif


#if EVALDEBUG
  const short
  EvalParser::yyrline_[] =
  {
       0,   144,   144,   145,   150,   153,   154,   160,   159,   171,
     177,   176,   188,   193,   198,   203,   208,   228,   242,   251,
     260,   270,   285,   296,   301,   306,   311,   316,   321,   342,
     357,   362,   376,   390,   405,   410,   415,   420,   425,   430,
     436,   441,   435,   456,   461,   466,   471,   476,   481,   486,
     491,   496,   501,   510,   520,   529,   542,   555,   560,   563,
     569,   573,   579,   585,   589,   595,   604,   608,   612,   616,
     622,   626,   632,   636,   640,   644,   648,   652,   656,   660,
     664,   670,   674,   680,   684,   690,   697,   702,   709
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
#line 2359 "parser.cc"

#line 716 "parser.yy"

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
