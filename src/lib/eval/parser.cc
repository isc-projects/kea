// A Bison parser, made by GNU Bison 3.7.6.

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

#line 52 "parser.cc"


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
#line 145 "parser.cc"

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
  | symbol kinds.  |
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
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 464 "parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 470 "parser.cc"
        break;

      case symbol_kind::S_HEXSTRING: // "constant hexstring"
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 476 "parser.cc"
        break;

      case symbol_kind::S_OPTION_NAME: // "option name"
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 482 "parser.cc"
        break;

      case symbol_kind::S_IP_ADDRESS: // "ip address"
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 488 "parser.cc"
        break;

      case symbol_kind::S_integer_expr: // integer_expr
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 494 "parser.cc"
        break;

      case symbol_kind::S_option_code: // option_code
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 500 "parser.cc"
        break;

      case symbol_kind::S_sub_option_code: // sub_option_code
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 506 "parser.cc"
        break;

      case symbol_kind::S_option_repr_type: // option_repr_type
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenOption::RepresentationType > (); }
#line 512 "parser.cc"
        break;

      case symbol_kind::S_nest_level: // nest_level
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < int8_t > (); }
#line 518 "parser.cc"
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt::MetadataType > (); }
#line 524 "parser.cc"
        break;

      case symbol_kind::S_enterprise_id: // enterprise_id
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 530 "parser.cc"
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt4::FieldType > (); }
#line 536 "parser.cc"
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt6::FieldType > (); }
#line 542 "parser.cc"
        break;

      case symbol_kind::S_relay6_field: // relay6_field
#line 114 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenRelay6Field::FieldType > (); }
#line 548 "parser.cc"
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
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
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
#line 134 "parser.yy"
                {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
#line 846 "parser.cc"
    break;

  case 7: // bool_expr: bool_expr "and" bool_expr
#line 139 "parser.yy"
                {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
#line 855 "parser.cc"
    break;

  case 8: // bool_expr: bool_expr "or" bool_expr
#line 144 "parser.yy"
                {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
#line 864 "parser.cc"
    break;

  case 9: // bool_expr: string_expr "==" string_expr
#line 149 "parser.yy"
                {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
#line 873 "parser.cc"
    break;

  case 10: // bool_expr: "option" "[" option_code "]" "." "exists"
#line 154 "parser.yy"
                {
                    TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 882 "parser.cc"
    break;

  case 11: // bool_expr: "option" "[" option_code "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 159 "parser.yy"
                {
                    TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
#line 891 "parser.cc"
    break;

  case 12: // bool_expr: "relay4" "[" sub_option_code "]" "." "exists"
#line 164 "parser.yy"
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
#line 915 "parser.cc"
    break;

  case 13: // bool_expr: "relay6" "[" nest_level "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 184 "parser.yy"
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
#line 933 "parser.cc"
    break;

  case 14: // bool_expr: "vendor-class" "[" enterprise_id "]" "." "exists"
#line 198 "parser.yy"
              {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 946 "parser.cc"
    break;

  case 15: // bool_expr: "vendor" "[" enterprise_id "]" "." "exists"
#line 207 "parser.yy"
              {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
#line 959 "parser.cc"
    break;

  case 16: // bool_expr: "vendor" "[" enterprise_id "]" "." "option" "[" sub_option_code "]" "." "exists"
#line 216 "parser.yy"
              {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), TokenOption::EXISTS, yystack_[3].value.as < uint16_t > ()));
                  ctx.expression.push_back(exist);
               }
#line 973 "parser.cc"
    break;

  case 17: // bool_expr: "member" "(" "constant string" ")"
#line 226 "parser.yy"
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
#line 992 "parser.cc"
    break;

  case 18: // string_expr: "constant string"
#line 243 "parser.yy"
                  {
                      TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(str);
                  }
#line 1001 "parser.cc"
    break;

  case 19: // string_expr: "constant hexstring"
#line 248 "parser.yy"
                  {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(hex);
                  }
#line 1010 "parser.cc"
    break;

  case 20: // string_expr: "ip address"
#line 253 "parser.yy"
                  {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as < std::string > ()));
                      ctx.expression.push_back(ip);
                  }
#line 1019 "parser.cc"
    break;

  case 21: // string_expr: "option" "[" option_code "]" "." option_repr_type
#line 258 "parser.yy"
                  {
                      TokenPtr opt(new TokenOption(yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1028 "parser.cc"
    break;

  case 22: // string_expr: "option" "[" option_code "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 263 "parser.yy"
                  {
                      TokenPtr opt(new TokenSubOption(yystack_[8].value.as < uint16_t > (), yystack_[3].value.as < uint16_t > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                      ctx.expression.push_back(opt);
                  }
#line 1037 "parser.cc"
    break;

  case 23: // string_expr: "relay4" "[" sub_option_code "]" "." option_repr_type
#line 268 "parser.yy"
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
#line 1061 "parser.cc"
    break;

  case 24: // string_expr: "relay6" "[" nest_level "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 289 "parser.yy"
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
#line 1079 "parser.cc"
    break;

  case 25: // string_expr: "pkt" "." pkt_metadata
#line 304 "parser.yy"
                  {
                      TokenPtr pkt_metadata(new TokenPkt(yystack_[0].value.as < TokenPkt::MetadataType > ()));
                      ctx.expression.push_back(pkt_metadata);
                  }
#line 1088 "parser.cc"
    break;

  case 26: // string_expr: "pkt4" "." pkt4_field
#line 309 "parser.yy"
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
#line 1106 "parser.cc"
    break;

  case 27: // string_expr: "pkt6" "." pkt6_field
#line 323 "parser.yy"
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
#line 1124 "parser.cc"
    break;

  case 28: // string_expr: "relay6" "[" nest_level "]" "." relay6_field
#line 337 "parser.yy"
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
#line 1142 "parser.cc"
    break;

  case 29: // string_expr: "substring" "(" string_expr "," start_expr "," length_expr ")"
#line 352 "parser.yy"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
#line 1151 "parser.cc"
    break;

  case 30: // string_expr: "concat" "(" string_expr "," string_expr ")"
#line 357 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1160 "parser.cc"
    break;

  case 31: // string_expr: string_expr "+" string_expr
#line 362 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
#line 1169 "parser.cc"
    break;

  case 32: // string_expr: "ifelse" "(" bool_expr "," string_expr "," string_expr ")"
#line 367 "parser.yy"
                  {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression.push_back(cond);
                  }
#line 1178 "parser.cc"
    break;

  case 33: // string_expr: "hexstring" "(" string_expr "," string_expr ")"
#line 372 "parser.yy"
                  {
                      TokenPtr tohex(new TokenToHexString());
                      ctx.expression.push_back(tohex);
                  }
#line 1187 "parser.cc"
    break;

  case 34: // string_expr: "vendor" "." "enterprise"
#line 377 "parser.yy"
                {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1200 "parser.cc"
    break;

  case 35: // string_expr: "vendor-class" "." "enterprise"
#line 386 "parser.yy"
                {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
#line 1214 "parser.cc"
    break;

  case 36: // string_expr: "vendor" "[" enterprise_id "]" "." "option" "[" sub_option_code "]" "." option_repr_type
#line 396 "parser.yy"
                {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[8].value.as < uint32_t > (), yystack_[0].value.as < TokenOption::RepresentationType > (), yystack_[3].value.as < uint16_t > ()));
                    ctx.expression.push_back(opt);
                }
#line 1227 "parser.cc"
    break;

  case 37: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data"
#line 405 "parser.yy"
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
#line 1244 "parser.cc"
    break;

  case 38: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data" "[" "integer" "]"
#line 418 "parser.yy"
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
#line 1261 "parser.cc"
    break;

  case 39: // string_expr: integer_expr
#line 431 "parser.yy"
                {
                    TokenPtr integer(new TokenInteger(yystack_[0].value.as < uint32_t > ()));
                    ctx.expression.push_back(integer);
                }
#line 1270 "parser.cc"
    break;

  case 41: // integer_expr: "integer"
#line 439 "parser.yy"
                 {
                     yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1278 "parser.cc"
    break;

  case 42: // option_code: "integer"
#line 445 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1286 "parser.cc"
    break;

  case 43: // option_code: "option name"
#line 449 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionName(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1294 "parser.cc"
    break;

  case 44: // sub_option_code: "integer"
#line 455 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1302 "parser.cc"
    break;

  case 45: // option_repr_type: "text"
#line 461 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1310 "parser.cc"
    break;

  case 46: // option_repr_type: "hex"
#line 465 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1318 "parser.cc"
    break;

  case 47: // nest_level: "integer"
#line 471 "parser.yy"
                 {
                     yylhs.value.as < int8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1326 "parser.cc"
    break;

  case 48: // pkt_metadata: "iface"
#line 480 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::IFACE;
                  }
#line 1334 "parser.cc"
    break;

  case 49: // pkt_metadata: "src"
#line 484 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::SRC;
                  }
#line 1342 "parser.cc"
    break;

  case 50: // pkt_metadata: "dst"
#line 488 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::DST;
                  }
#line 1350 "parser.cc"
    break;

  case 51: // pkt_metadata: "len"
#line 492 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::LEN;
                  }
#line 1358 "parser.cc"
    break;

  case 52: // enterprise_id: "integer"
#line 498 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                   }
#line 1366 "parser.cc"
    break;

  case 53: // enterprise_id: "*"
#line 502 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = 0;
                   }
#line 1374 "parser.cc"
    break;

  case 54: // pkt4_field: "mac"
#line 508 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1382 "parser.cc"
    break;

  case 55: // pkt4_field: "hlen"
#line 512 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1390 "parser.cc"
    break;

  case 56: // pkt4_field: "htype"
#line 516 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1398 "parser.cc"
    break;

  case 57: // pkt4_field: "ciaddr"
#line 520 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1406 "parser.cc"
    break;

  case 58: // pkt4_field: "giaddr"
#line 524 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1414 "parser.cc"
    break;

  case 59: // pkt4_field: "yiaddr"
#line 528 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1422 "parser.cc"
    break;

  case 60: // pkt4_field: "siaddr"
#line 532 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1430 "parser.cc"
    break;

  case 61: // pkt4_field: "msgtype"
#line 536 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::MSGTYPE;
                 }
#line 1438 "parser.cc"
    break;

  case 62: // pkt4_field: "transid"
#line 540 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::TRANSID;
                 }
#line 1446 "parser.cc"
    break;

  case 63: // pkt6_field: "msgtype"
#line 546 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE;
                 }
#line 1454 "parser.cc"
    break;

  case 64: // pkt6_field: "transid"
#line 550 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::TRANSID;
                 }
#line 1462 "parser.cc"
    break;

  case 65: // relay6_field: "peeraddr"
#line 556 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR;
                   }
#line 1470 "parser.cc"
    break;

  case 66: // relay6_field: "linkaddr"
#line 560 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR;
                   }
#line 1478 "parser.cc"
    break;

  case 67: // start_expr: "integer"
#line 566 "parser.yy"
                {
                    TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                    ctx.expression.push_back(str);
                }
#line 1487 "parser.cc"
    break;

  case 68: // length_expr: "integer"
#line 573 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression.push_back(str);
                 }
#line 1496 "parser.cc"
    break;

  case 69: // length_expr: "all"
#line 578 "parser.yy"
                 {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
#line 1505 "parser.cc"
    break;


#line 1509 "parser.cc"

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

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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


  const signed char EvalParser::yypact_ninf_ = -126;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short
  EvalParser::yypact_[] =
  {
      36,     7,    86,    22,     7,     7,    21,    48,    84,   101,
      62,    91,   118,   133,   137,   160,    94,    15,   107,  -126,
    -126,  -126,  -126,  -126,   122,    12,  -126,    86,   154,   161,
     162,   140,   141,   142,  -126,    76,     1,  -126,   108,   126,
     135,   138,   110,    45,    86,    86,     7,    86,   131,   -23,
     136,   -23,   143,     7,     7,    86,    86,    -1,   108,   126,
     135,   -23,   -23,  -126,  -126,  -126,  -126,   159,  -126,   163,
    -126,   165,   178,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,   123,   128,
      64,   129,  -126,  -126,  -126,  -126,  -126,   167,  -126,   169,
    -126,  -126,   180,   142,  -126,   172,   174,   176,   177,   179,
     181,   182,   183,  -126,   144,    86,    86,    86,   184,   185,
     186,   187,   188,   189,   190,    72,   124,    89,  -126,   158,
       0,   132,    17,    -7,     6,    75,   153,    92,   150,   199,
     194,  -126,  -126,  -126,  -126,  -126,  -126,   195,  -126,  -126,
    -126,   -21,  -126,    86,  -126,  -126,   196,   197,  -126,   198,
     200,   201,   126,   126,  -126,  -126,   210,    23,   166,   126,
     126,   126,   126,   203,   204,  -126,  -126,   205,   206,   207,
     208,   209,   211,   212,  -126,   213,   214,   215,   216,   127,
     130,   134,   153,   153,   153,  -126,  -126,  -126,  -126,  -126,
    -126
  };

  const signed char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
      41,    19,    20,     2,     4,     0,    39,     0,     0,     0,
       0,     0,     0,     3,     1,     0,     0,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,    40,    42,    43,     0,    44,     0,
      47,     0,     0,    48,    49,    50,    51,    25,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    26,     0,     0,
       0,     0,    63,    64,    27,    53,    52,     0,    35,     0,
      34,     7,     8,     9,    31,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,    46,    10,    21,    12,    23,     0,    65,    66,
      28,     0,    30,     0,    33,    14,    37,     0,    15,     0,
       0,     0,     0,     0,    69,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    32,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,    22,    13,    24,    16,
      36
  };

  const short
  EvalParser::yypgoto_[] =
  {
    -126,  -126,  -126,     3,    -2,  -126,   168,   -53,  -125,   157,
    -126,   -27,  -126,  -126,  -126,  -126,  -126
  };

  const unsigned char
  EvalParser::yydefgoto_[] =
  {
       0,     3,    23,    24,    25,    26,    67,    69,   144,    71,
      77,    97,    87,    94,   150,   129,   166
  };

  const unsigned char
  EvalParser::yytable_[] =
  {
      33,   146,    36,    64,   152,    64,   106,    35,    37,    55,
       4,   146,     5,   155,   164,   157,     6,     7,     8,     9,
      55,   154,    34,    95,    99,    57,   158,   176,    10,    96,
      49,   165,    50,    11,   108,   109,    38,    56,    56,    56,
     156,    12,    88,    89,    13,    91,    14,    15,    16,    90,
      56,    17,    18,   103,   104,    56,   101,   102,    19,    20,
      21,    56,    22,    39,   196,   198,   200,   196,   198,   200,
      53,    54,    78,    79,    80,    81,    82,    83,    84,    42,
      63,   140,    53,    54,   159,     1,     2,    85,    86,    27,
     141,   142,   143,   141,   142,    28,    29,    30,   147,    40,
     116,   160,   148,   149,    41,   148,   149,    10,    43,   173,
     174,    48,    11,   130,   131,   132,   178,   179,   180,   181,
      12,    44,    51,    13,    52,    14,    15,    16,    53,    54,
      31,    32,    73,    74,    75,    76,    45,    19,    20,    21,
      46,    22,   141,   142,   145,   141,   142,   195,   141,   142,
     197,   167,   141,   142,   199,    61,    62,    50,    52,   114,
      65,    56,    66,    47,   115,   117,    56,    56,   153,    58,
      56,   141,   142,    92,    93,   110,    59,    60,    68,   111,
      56,   112,   113,   118,    98,   119,    53,    70,   120,    72,
     121,   100,   122,   123,   151,   124,   128,   156,   125,   126,
     127,   133,   134,   135,   136,   137,   138,   139,   161,   162,
     163,   168,   169,   170,   175,   171,   172,   107,   177,   182,
     183,   184,   185,   186,   187,   188,   105,     0,   189,   190,
     191,   192,   193,   194
  };

  const short
  EvalParser::yycheck_[] =
  {
       2,   126,     4,     4,     4,     4,    59,     4,     5,     8,
       3,   136,     5,    20,    35,     9,     9,    10,    11,    12,
       8,     4,     0,    46,    51,    27,    20,     4,    21,    52,
      15,    52,    17,    26,    61,    62,    15,    38,    38,    38,
      47,    34,    44,    45,    37,    47,    39,    40,    41,    46,
      38,    44,    45,    55,    56,    38,    53,    54,    51,    52,
      53,    38,    55,    15,   189,   190,   191,   192,   193,   194,
       6,     7,    27,    28,    29,    30,    31,    32,    33,    17,
       4,     9,     6,     7,     9,    49,    50,    42,    43,     3,
      18,    19,    20,    18,    19,     9,    10,    11,     9,    15,
      36,     9,    13,    14,     3,    13,    14,    21,    17,   162,
     163,    17,    26,   115,   116,   117,   169,   170,   171,   172,
      34,     3,    15,    37,    17,    39,    40,    41,     6,     7,
      44,    45,    22,    23,    24,    25,     3,    51,    52,    53,
       3,    55,    18,    19,    20,    18,    19,    20,    18,    19,
      20,   153,    18,    19,    20,    15,    15,    17,    17,    36,
      52,    38,    54,     3,    36,    36,    38,    38,    36,    15,
      38,    18,    19,    42,    43,    16,    15,    15,    52,    16,
      38,    16,     4,    16,    48,    16,     6,    52,    16,    51,
      16,    48,    16,    16,    36,    16,    52,    47,    17,    17,
      17,    17,    17,    17,    17,    17,    17,    17,     9,    15,
      15,    15,    15,    15,     4,    15,    15,    60,    52,    16,
      16,    16,    16,    16,    16,    16,    58,    -1,    17,    17,
      17,    17,    17,    17
  };

  const signed char
  EvalParser::yystos_[] =
  {
       0,    49,    50,    57,     3,     5,     9,    10,    11,    12,
      21,    26,    34,    37,    39,    40,    41,    44,    45,    51,
      52,    53,    55,    58,    59,    60,    61,     3,     9,    10,
      11,    44,    45,    60,     0,    59,    60,    59,    15,    15,
      15,     3,    17,    17,     3,     3,     3,     3,    17,    15,
      17,    15,    17,     6,     7,     8,    38,    60,    15,    15,
      15,    15,    15,     4,     4,    52,    54,    62,    52,    63,
      52,    65,    51,    22,    23,    24,    25,    66,    27,    28,
      29,    30,    31,    32,    33,    42,    43,    68,    60,    60,
      59,    60,    42,    43,    69,    46,    52,    67,    48,    67,
      48,    59,    59,    60,    60,    62,    63,    65,    67,    67,
      16,    16,    16,     4,    36,    36,    36,    36,    16,    16,
      16,    16,    16,    16,    16,    17,    17,    17,    52,    71,
      60,    60,    60,    17,    17,    17,    17,    17,    17,    17,
       9,    18,    19,    20,    64,    20,    64,     9,    13,    14,
      70,    36,     4,    36,     4,    20,    47,     9,    20,     9,
       9,     9,    15,    15,    35,    52,    72,    60,    15,    15,
      15,    15,    15,    63,    63,     4,     4,    52,    63,    63,
      63,    63,    16,    16,    16,    16,    16,    16,    16,    17,
      17,    17,    17,    17,    17,    20,    64,    20,    64,    20,
      64
  };

  const signed char
  EvalParser::yyr1_[] =
  {
       0,    56,    57,    57,    58,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    62,    62,    63,    64,    64,    65,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    70,    71,    72,    72
  };

  const signed char
  EvalParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     3,     2,     3,     3,     3,
       6,    11,     6,    11,     6,     6,    11,     4,     1,     1,
       1,     6,    11,     6,    11,     3,     3,     3,     6,     8,
       6,     3,     8,     6,     3,     3,    11,     6,     9,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
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
  "\"siaddr\"", "\"substring\"", "\"all\"", "\",\"", "\"concat\"", "\"+\"",
  "\"ifelse\"", "\"hexstring\"", "\"pkt6\"", "\"msgtype\"", "\"transid\"",
  "\"vendor-class\"", "\"vendor\"", "\"*\"", "\"data\"", "\"enterprise\"",
  "\"top-level bool\"", "\"top-level string\"", "\"constant string\"",
  "\"integer\"", "\"constant hexstring\"", "\"option name\"",
  "\"ip address\"", "$accept", "start", "expression", "bool_expr",
  "string_expr", "integer_expr", "option_code", "sub_option_code",
  "option_repr_type", "nest_level", "pkt_metadata", "enterprise_id",
  "pkt4_field", "pkt6_field", "relay6_field", "start_expr", "length_expr", YY_NULLPTR
  };
#endif


#if EVALDEBUG
  const short
  EvalParser::yyrline_[] =
  {
       0,   123,   123,   124,   129,   132,   133,   138,   143,   148,
     153,   158,   163,   183,   197,   206,   215,   225,   242,   247,
     252,   257,   262,   267,   288,   303,   308,   322,   336,   351,
     356,   361,   366,   371,   376,   385,   395,   404,   417,   430,
     435,   438,   444,   448,   454,   460,   464,   470,   479,   483,
     487,   491,   497,   501,   507,   511,   515,   519,   523,   527,
     531,   535,   539,   545,   549,   555,   559,   565,   572,   577
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
#line 2105 "parser.cc"

#line 584 "parser.yy"

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
