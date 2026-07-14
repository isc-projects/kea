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

      case symbol_kind::S_relay6_option_chain: // relay6_option_chain
        value.YY_MOVE_OR_COPY< std::pair<int8_t, std::vector<uint16_t>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vendor_option_chain: // vendor_option_chain
        value.YY_MOVE_OR_COPY< std::pair<uint32_t, std::vector<uint16_t>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_option_chain: // option_chain
      case symbol_kind::S_relay4_option_chain: // relay4_option_chain
        value.YY_MOVE_OR_COPY< std::vector<uint16_t> > (YY_MOVE (that.value));
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

      case symbol_kind::S_relay6_option_chain: // relay6_option_chain
        value.move< std::pair<int8_t, std::vector<uint16_t>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vendor_option_chain: // vendor_option_chain
        value.move< std::pair<uint32_t, std::vector<uint16_t>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_option_chain: // option_chain
      case symbol_kind::S_relay4_option_chain: // relay4_option_chain
        value.move< std::vector<uint16_t> > (YY_MOVE (that.value));
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

      case symbol_kind::S_relay6_option_chain: // relay6_option_chain
        value.copy< std::pair<int8_t, std::vector<uint16_t>> > (that.value);
        break;

      case symbol_kind::S_vendor_option_chain: // vendor_option_chain
        value.copy< std::pair<uint32_t, std::vector<uint16_t>> > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_option_chain: // option_chain
      case symbol_kind::S_relay4_option_chain: // relay4_option_chain
        value.copy< std::vector<uint16_t> > (that.value);
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

      case symbol_kind::S_relay6_option_chain: // relay6_option_chain
        value.move< std::pair<int8_t, std::vector<uint16_t>> > (that.value);
        break;

      case symbol_kind::S_vendor_option_chain: // vendor_option_chain
        value.move< std::pair<uint32_t, std::vector<uint16_t>> > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_option_chain: // option_chain
      case symbol_kind::S_relay4_option_chain: // relay4_option_chain
        value.move< std::vector<uint16_t> > (that.value);
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
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 521 "parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 527 "parser.cc"
        break;

      case symbol_kind::S_HEXSTRING: // "constant hexstring"
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 533 "parser.cc"
        break;

      case symbol_kind::S_OPTION_NAME: // "option name"
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 539 "parser.cc"
        break;

      case symbol_kind::S_IP_ADDRESS: // "ip address"
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 545 "parser.cc"
        break;

      case symbol_kind::S_option_chain: // option_chain
#line 141 "parser.yy"
                 {
    for (size_t i = 0; i < yysym.value.template as < std::vector<uint16_t> > ().size(); ++i) {
        yyoutput << (i > 0 ? ", " : "") << yysym.value.template as < std::vector<uint16_t> > ()[i];
    }
}
#line 555 "parser.cc"
        break;

      case symbol_kind::S_relay4_option_chain: // relay4_option_chain
#line 141 "parser.yy"
                 {
    for (size_t i = 0; i < yysym.value.template as < std::vector<uint16_t> > ().size(); ++i) {
        yyoutput << (i > 0 ? ", " : "") << yysym.value.template as < std::vector<uint16_t> > ()[i];
    }
}
#line 565 "parser.cc"
        break;

      case symbol_kind::S_relay6_option_chain: // relay6_option_chain
#line 147 "parser.yy"
                 {
    yyoutput << yysym.value.template as < std::pair<int8_t, std::vector<uint16_t>> > ().first << std::endl;
    for (size_t i = 0; i < yysym.value.template as < std::pair<int8_t, std::vector<uint16_t>> > ().second.size(); ++i) {
        yyoutput << (i > 0 ? ", " : "") << yysym.value.template as < std::pair<int8_t, std::vector<uint16_t>> > ().second[i];
    }
}
#line 576 "parser.cc"
        break;

      case symbol_kind::S_vendor_option_chain: // vendor_option_chain
#line 154 "parser.yy"
                 {
    yyoutput << yysym.value.template as < std::pair<uint32_t, std::vector<uint16_t>> > ().first << std::endl;
    for (size_t i = 0; i < yysym.value.template as < std::pair<uint32_t, std::vector<uint16_t>> > ().second.size(); ++i) {
        yyoutput << (i > 0 ? ", " : "") << yysym.value.template as < std::pair<uint32_t, std::vector<uint16_t>> > ().second[i];
    }
}
#line 587 "parser.cc"
        break;

      case symbol_kind::S_integer_expr: // integer_expr
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 593 "parser.cc"
        break;

      case symbol_kind::S_option_code: // option_code
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 599 "parser.cc"
        break;

      case symbol_kind::S_sub_option_code: // sub_option_code
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < uint16_t > (); }
#line 605 "parser.cc"
        break;

      case symbol_kind::S_option_repr_type: // option_repr_type
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenOption::RepresentationType > (); }
#line 611 "parser.cc"
        break;

      case symbol_kind::S_nest_level: // nest_level
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < int8_t > (); }
#line 617 "parser.cc"
        break;

      case symbol_kind::S_pkt_metadata: // pkt_metadata
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt::MetadataType > (); }
#line 623 "parser.cc"
        break;

      case symbol_kind::S_enterprise_id: // enterprise_id
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < uint32_t > (); }
#line 629 "parser.cc"
        break;

      case symbol_kind::S_pkt4_field: // pkt4_field
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt4::FieldType > (); }
#line 635 "parser.cc"
        break;

      case symbol_kind::S_pkt6_field: // pkt6_field
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenPkt6::FieldType > (); }
#line 641 "parser.cc"
        break;

      case symbol_kind::S_relay6_field: // relay6_field
#line 139 "parser.yy"
                 { yyoutput << yysym.value.template as < TokenRelay6Field::FieldType > (); }
#line 647 "parser.cc"
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

      case symbol_kind::S_relay6_option_chain: // relay6_option_chain
        yylhs.value.emplace< std::pair<int8_t, std::vector<uint16_t>> > ();
        break;

      case symbol_kind::S_vendor_option_chain: // vendor_option_chain
        yylhs.value.emplace< std::pair<uint32_t, std::vector<uint16_t>> > ();
        break;

      case symbol_kind::S_STRING: // "constant string"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_HEXSTRING: // "constant hexstring"
      case symbol_kind::S_OPTION_NAME: // "option name"
      case symbol_kind::S_IP_ADDRESS: // "ip address"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_option_chain: // option_chain
      case symbol_kind::S_relay4_option_chain: // relay4_option_chain
        yylhs.value.emplace< std::vector<uint16_t> > ();
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
  case 5: // option_chain: "option" "[" option_code "]"
#line 178 "parser.yy"
                {
                    yylhs.value.as < std::vector<uint16_t> > ().push_back(yystack_[1].value.as < uint16_t > ());
                }
#line 957 "parser.cc"
    break;

  case 6: // option_chain: option_chain "." "option" "[" sub_option_code "]"
#line 182 "parser.yy"
                {
                    yylhs.value.as < std::vector<uint16_t> > () = std::move(yystack_[5].value.as < std::vector<uint16_t> > ());
                    yylhs.value.as < std::vector<uint16_t> > ().push_back(yystack_[1].value.as < uint16_t > ());
                }
#line 966 "parser.cc"
    break;

  case 7: // relay4_option_chain: "relay4" "[" sub_option_code "]"
#line 189 "parser.yy"
                        {
                            // Ensure we are parsing a DHCPv4 context
                            if (ctx.getUniverse() != Option::V4) {
                                error(yystack_[3].location, "relay4 can only be used in DHCPv4.");
                            }
                            yylhs.value.as < std::vector<uint16_t> > ().push_back(yystack_[1].value.as < uint16_t > ());
                        }
#line 978 "parser.cc"
    break;

  case 8: // relay4_option_chain: relay4_option_chain "." "option" "[" option_code "]"
#line 197 "parser.yy"
                        {
                            yylhs.value.as < std::vector<uint16_t> > () = std::move(yystack_[5].value.as < std::vector<uint16_t> > ());
                            yylhs.value.as < std::vector<uint16_t> > ().push_back(yystack_[1].value.as < uint16_t > ());
                        }
#line 987 "parser.cc"
    break;

  case 9: // relay6_option_chain: "relay6" "[" nest_level "]" "." "option" "[" sub_option_code "]"
#line 204 "parser.yy"
                        {
                            // Ensure we are parsing a DHCPv6 context
                            if (ctx.getUniverse() != Option::V6) {
                                error(yystack_[8].location, "relay6 can only be used in DHCPv6.");
                            }
                            yylhs.value.as < std::pair<int8_t, std::vector<uint16_t>> > ().first = yystack_[6].value.as < int8_t > ();
                            yylhs.value.as < std::pair<int8_t, std::vector<uint16_t>> > ().second.push_back(yystack_[1].value.as < uint16_t > ());
                        }
#line 1000 "parser.cc"
    break;

  case 10: // relay6_option_chain: relay6_option_chain "." "option" "[" option_code "]"
#line 213 "parser.yy"
                        {
                            yylhs.value.as < std::pair<int8_t, std::vector<uint16_t>> > () = std::move(yystack_[5].value.as < std::pair<int8_t, std::vector<uint16_t>> > ());
                            yylhs.value.as < std::pair<int8_t, std::vector<uint16_t>> > ().second.push_back(yystack_[1].value.as < uint16_t > ());
                        }
#line 1009 "parser.cc"
    break;

  case 11: // vendor_option_chain: "vendor" "[" enterprise_id "]" "." "option" "[" sub_option_code "]"
#line 220 "parser.yy"
                        {
                            yylhs.value.as < std::pair<uint32_t, std::vector<uint16_t>> > ().first = yystack_[6].value.as < uint32_t > ();
                            yylhs.value.as < std::pair<uint32_t, std::vector<uint16_t>> > ().second.push_back(yystack_[1].value.as < uint16_t > ());
                        }
#line 1018 "parser.cc"
    break;

  case 12: // vendor_option_chain: vendor_option_chain "." "option" "[" option_code "]"
#line 225 "parser.yy"
                        {
                            yylhs.value.as < std::pair<uint32_t, std::vector<uint16_t>> > () = std::move(yystack_[5].value.as < std::pair<uint32_t, std::vector<uint16_t>> > ());
                            yylhs.value.as < std::pair<uint32_t, std::vector<uint16_t>> > ().second.push_back(yystack_[1].value.as < uint16_t > ());
                        }
#line 1027 "parser.cc"
    break;

  case 14: // bool_expr: "not" bool_expr
#line 233 "parser.yy"
                {
                    TokenPtr neg(new TokenNot());
                    ctx.expression_.push_back(neg);
                }
#line 1036 "parser.cc"
    break;

  case 15: // $@1: %empty
#line 238 "parser.yy"
                {
                    unsigned target = ++ctx.label_;
                    ctx.labels_.push_back(target);
                    TokenPtr pobf(new TokenPopOrBranchFalse(target));
                    ctx.expression_.push_back(pobf);
                }
#line 1047 "parser.cc"
    break;

  case 16: // bool_expr: bool_expr "and" $@1 bool_expr
#line 243 "parser.yy"
                            {
                    unsigned target = ctx.labels_.back();
                    ctx.labels_.pop_back();
                    TokenPtr lab(new TokenLabel(target));
                    ctx.expression_.push_back(lab);
                }
#line 1058 "parser.cc"
    break;

  case 17: // bool_expr: bool_expr "sand" bool_expr
#line 250 "parser.yy"
                {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression_.push_back(neg);
                }
#line 1067 "parser.cc"
    break;

  case 18: // $@2: %empty
#line 255 "parser.yy"
                {
                    unsigned target = ++ctx.label_;
                    ctx.labels_.push_back(target);
                    TokenPtr pobt(new TokenPopOrBranchTrue(target));
                    ctx.expression_.push_back(pobt);
                }
#line 1078 "parser.cc"
    break;

  case 19: // bool_expr: bool_expr "or" $@2 bool_expr
#line 260 "parser.yy"
                            {
                    unsigned target = ctx.labels_.back();
                    ctx.labels_.pop_back();
                    TokenPtr lab(new TokenLabel(target));
                    ctx.expression_.push_back(lab);
                }
#line 1089 "parser.cc"
    break;

  case 20: // bool_expr: bool_expr "sor" bool_expr
#line 267 "parser.yy"
                {
                    TokenPtr neg(new TokenOr());
                    ctx.expression_.push_back(neg);
                }
#line 1098 "parser.cc"
    break;

  case 21: // bool_expr: string_expr "==" string_expr
#line 272 "parser.yy"
                {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression_.push_back(eq);
                }
#line 1107 "parser.cc"
    break;

  case 22: // bool_expr: option_chain "." "exists"
#line 277 "parser.yy"
                {
                    TokenPtr opt(new TokenOption(yystack_[2].value.as < std::vector<uint16_t> > (), TokenOption::EXISTS));
                    ctx.expression_.push_back(opt);
                }
#line 1116 "parser.cc"
    break;

  case 23: // bool_expr: relay4_option_chain "." "exists"
#line 282 "parser.yy"
                {
                   switch (ctx.getUniverse()) {
                   case Option::V4:
                   {
                       TokenPtr opt(new TokenRelay4Option(yystack_[2].value.as < std::vector<uint16_t> > (), TokenOption::EXISTS));
                       ctx.expression_.push_back(opt);
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
                       error(yystack_[2].location, "relay4 can only be used in DHCPv4.");
                   }
                }
#line 1140 "parser.cc"
    break;

  case 24: // bool_expr: relay6_option_chain "." "exists"
#line 302 "parser.yy"
                {
                    switch (ctx.getUniverse()) {
                    case Option::V6:
                    {
                        TokenPtr opt(new TokenRelay6Option(yystack_[2].value.as < std::pair<int8_t, std::vector<uint16_t>> > ().first, yystack_[2].value.as < std::pair<int8_t, std::vector<uint16_t>> > ().second, TokenOption::EXISTS));
                        ctx.expression_.push_back(opt);
                        break;
                    }
                    case Option::V4:
                        // For now we only use relay6 in DHCPv6.
                        error(yystack_[2].location, "relay6 can only be used in DHCPv6.");
                    }
                }
#line 1158 "parser.cc"
    break;

  case 25: // bool_expr: "vendor-class" "[" enterprise_id "]" "." "exists"
#line 316 "parser.yy"
              {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression_.push_back(exist);
              }
#line 1171 "parser.cc"
    break;

  case 26: // bool_expr: "vendor" "[" enterprise_id "]" "." "exists"
#line 325 "parser.yy"
              {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[3].value.as < uint32_t > (), TokenOption::EXISTS));
                  ctx.expression_.push_back(exist);
              }
#line 1184 "parser.cc"
    break;

  case 27: // bool_expr: vendor_option_chain "." "exists"
#line 334 "parser.yy"
              {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), yystack_[2].value.as < std::pair<uint32_t, std::vector<uint16_t>> > ().first, TokenOption::EXISTS, yystack_[2].value.as < std::pair<uint32_t, std::vector<uint16_t>> > ().second));
                  ctx.expression_.push_back(exist);
               }
#line 1198 "parser.cc"
    break;

  case 28: // bool_expr: "member" "(" "constant string" ")"
#line 344 "parser.yy"
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
                  ctx.expression_.push_back(member);
              }
#line 1217 "parser.cc"
    break;

  case 29: // bool_expr: "match" "(" "constant string" "," string_expr ")"
#line 359 "parser.yy"
              {
                  // Expression match('<regex>', <string_expr>)
                  //
                  // This token will check if the regular expression matches
                  // the string expression.
                  TokenPtr match(new TokenMatch(yystack_[3].value.as < std::string > ()));
                  ctx.expression_.push_back(match);
              }
#line 1230 "parser.cc"
    break;

  case 30: // string_expr: "constant string"
#line 370 "parser.yy"
                  {
                      TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                      ctx.expression_.push_back(str);
                  }
#line 1239 "parser.cc"
    break;

  case 31: // string_expr: "constant hexstring"
#line 375 "parser.yy"
                  {
                      TokenPtr hex(new TokenHexString(yystack_[0].value.as < std::string > ()));
                      ctx.expression_.push_back(hex);
                  }
#line 1248 "parser.cc"
    break;

  case 32: // string_expr: "ip address"
#line 380 "parser.yy"
                  {
                      TokenPtr ip(new TokenIpAddress(yystack_[0].value.as < std::string > ()));
                      ctx.expression_.push_back(ip);
                  }
#line 1257 "parser.cc"
    break;

  case 33: // string_expr: option_chain "." option_repr_type
#line 385 "parser.yy"
              {
                  TokenPtr opt(new TokenOption(yystack_[2].value.as < std::vector<uint16_t> > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                  ctx.expression_.push_back(opt);
              }
#line 1266 "parser.cc"
    break;

  case 34: // string_expr: relay4_option_chain "." option_repr_type
#line 390 "parser.yy"
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr opt(new TokenRelay4Option(yystack_[2].value.as < std::vector<uint16_t> > (), yystack_[0].value.as < TokenOption::RepresentationType > ()));
                         ctx.expression_.push_back(opt);
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
                         error(yystack_[2].location, "relay4 can only be used in DHCPv4.");
                     }
                  }
#line 1290 "parser.cc"
    break;

  case 35: // string_expr: relay6_option_chain "." option_repr_type
#line 411 "parser.yy"
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr opt(new TokenRelay6Option(yystack_[2].value.as < std::pair<int8_t, std::vector<uint16_t>> > ().first, yystack_[2].value.as < std::pair<int8_t, std::vector<uint16_t>> > ().second, yystack_[0].value.as < TokenOption::RepresentationType > ()));
                         ctx.expression_.push_back(opt);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[2].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 1308 "parser.cc"
    break;

  case 36: // string_expr: "pkt" "." pkt_metadata
#line 426 "parser.yy"
                  {
                      TokenPtr pkt_metadata(new TokenPkt(yystack_[0].value.as < TokenPkt::MetadataType > ()));
                      ctx.expression_.push_back(pkt_metadata);
                  }
#line 1317 "parser.cc"
    break;

  case 37: // string_expr: "pkt4" "." pkt4_field
#line 431 "parser.yy"
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr pkt4_field(new TokenPkt4(yystack_[0].value.as < TokenPkt4::FieldType > ()));
                         ctx.expression_.push_back(pkt4_field);
                         break;
                     }
                     case Option::V6:
                         // For now we only use pkt4 in DHCPv4.
                         error(yystack_[2].location, "pkt4 can only be used in DHCPv4.");
                     }
                  }
#line 1335 "parser.cc"
    break;

  case 38: // string_expr: "pkt6" "." pkt6_field
#line 445 "parser.yy"
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr pkt6_field(new TokenPkt6(yystack_[0].value.as < TokenPkt6::FieldType > ()));
                         ctx.expression_.push_back(pkt6_field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use pkt6 in DHCPv6.
                         error(yystack_[2].location, "pkt6 can only be used in DHCPv6.");
                     }
                  }
#line 1353 "parser.cc"
    break;

  case 39: // string_expr: "relay6" "[" nest_level "]" "." relay6_field
#line 459 "parser.yy"
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr relay6field(new TokenRelay6Field(yystack_[3].value.as < int8_t > (), yystack_[0].value.as < TokenRelay6Field::FieldType > ()));
                         ctx.expression_.push_back(relay6field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(yystack_[5].location, "relay6 can only be used in DHCPv6.");
                     }
                  }
#line 1371 "parser.cc"
    break;

  case 40: // string_expr: "substring" "(" string_expr "," start_expr "," length_expr ")"
#line 474 "parser.yy"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression_.push_back(sub);
                  }
#line 1380 "parser.cc"
    break;

  case 41: // string_expr: "split" "(" string_expr "," string_expr "," int_expr ")"
#line 479 "parser.yy"
                  {
                      TokenPtr split(new TokenSplit());
                      ctx.expression_.push_back(split);
                  }
#line 1389 "parser.cc"
    break;

  case 42: // string_expr: "concat" "(" string_expr "," string_expr ")"
#line 484 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression_.push_back(conc);
                  }
#line 1398 "parser.cc"
    break;

  case 43: // string_expr: string_expr "+" string_expr
#line 489 "parser.yy"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression_.push_back(conc);
                  }
#line 1407 "parser.cc"
    break;

  case 44: // string_expr: "lcase" "(" string_expr ")"
#line 494 "parser.yy"
                  {
                      TokenPtr lcase(new TokenLowerCase());
                      ctx.expression_.push_back(lcase);
                  }
#line 1416 "parser.cc"
    break;

  case 45: // string_expr: "ucase" "(" string_expr ")"
#line 499 "parser.yy"
                  {
                      TokenPtr ucase(new TokenUpperCase());
                      ctx.expression_.push_back(ucase);
                  }
#line 1425 "parser.cc"
    break;

  case 46: // $@3: %empty
#line 504 "parser.yy"
                  {
                      unsigned target = ++ctx.label_;
                      ctx.labels_.push_back(target);
                      TokenPtr pabf(new TokenPopAndBranchFalse(target));
                      ctx.expression_.push_back(pabf);
                  }
#line 1436 "parser.cc"
    break;

  case 47: // $@4: %empty
#line 509 "parser.yy"
                                    {
                      unsigned target = ctx.labels_.back();
                      ctx.labels_.pop_back();
                      unsigned target2 = ++ctx.label_;
                      ctx.labels_.push_back(target2);
                      TokenPtr branch(new TokenBranch(target2));
                      ctx.expression_.push_back(branch);
                      TokenPtr lab(new TokenLabel(target));
                      ctx.expression_.push_back(lab);
                  }
#line 1451 "parser.cc"
    break;

  case 48: // string_expr: "ifelse" "(" bool_expr "," $@3 string_expr "," $@4 string_expr ")"
#line 518 "parser.yy"
                                    {
                      unsigned target = ctx.labels_.back();
                      ctx.labels_.pop_back();
                      TokenPtr lab(new TokenLabel(target));
                      ctx.expression_.push_back(lab);
                  }
#line 1462 "parser.cc"
    break;

  case 49: // string_expr: "sifelse" "(" bool_expr "," string_expr "," string_expr ")"
#line 525 "parser.yy"
                  {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression_.push_back(cond);
                  }
#line 1471 "parser.cc"
    break;

  case 50: // string_expr: "hexstring" "(" string_expr "," string_expr ")"
#line 530 "parser.yy"
                  {
                      TokenPtr tohex(new TokenToHexString());
                      ctx.expression_.push_back(tohex);
                  }
#line 1480 "parser.cc"
    break;

  case 51: // string_expr: "addrtotext" "(" string_expr ")"
#line 535 "parser.yy"
                  {
                      TokenPtr addrtotext(new TokenIpAddressToText());
                      ctx.expression_.push_back(addrtotext);
                  }
#line 1489 "parser.cc"
    break;

  case 52: // string_expr: "int8totext" "(" string_expr ")"
#line 540 "parser.yy"
                  {
                      TokenPtr int8totext(new TokenInt8ToText());
                      ctx.expression_.push_back(int8totext);
                  }
#line 1498 "parser.cc"
    break;

  case 53: // string_expr: "int16totext" "(" string_expr ")"
#line 545 "parser.yy"
                  {
                      TokenPtr int16totext(new TokenInt16ToText());
                      ctx.expression_.push_back(int16totext);
                  }
#line 1507 "parser.cc"
    break;

  case 54: // string_expr: "int32totext" "(" string_expr ")"
#line 550 "parser.yy"
                  {
                      TokenPtr int32totext(new TokenInt32ToText());
                      ctx.expression_.push_back(int32totext);
                  }
#line 1516 "parser.cc"
    break;

  case 55: // string_expr: "uint8totext" "(" string_expr ")"
#line 555 "parser.yy"
                  {
                      TokenPtr uint8totext(new TokenUInt8ToText());
                      ctx.expression_.push_back(uint8totext);
                  }
#line 1525 "parser.cc"
    break;

  case 56: // string_expr: "uint16totext" "(" string_expr ")"
#line 560 "parser.yy"
                  {
                      TokenPtr uint16totext(new TokenUInt16ToText());
                      ctx.expression_.push_back(uint16totext);
                  }
#line 1534 "parser.cc"
    break;

  case 57: // string_expr: "uint32totext" "(" string_expr ")"
#line 565 "parser.yy"
                  {
                      TokenPtr uint32totext(new TokenUInt32ToText());
                      ctx.expression_.push_back(uint32totext);
                  }
#line 1543 "parser.cc"
    break;

  case 58: // string_expr: "vendor" "." "enterprise"
#line 570 "parser.yy"
                {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression_.push_back(vendor);
                }
#line 1556 "parser.cc"
    break;

  case 59: // string_expr: "vendor-class" "." "enterprise"
#line 579 "parser.yy"
                {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression_.push_back(vendor);
                }
#line 1570 "parser.cc"
    break;

  case 60: // string_expr: vendor_option_chain "." option_repr_type
#line 589 "parser.yy"
                {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), yystack_[2].value.as < std::pair<uint32_t, std::vector<uint16_t>> > ().first, yystack_[0].value.as < TokenOption::RepresentationType > (), yystack_[2].value.as < std::pair<uint32_t, std::vector<uint16_t>> > ().second));
                    ctx.expression_.push_back(opt);
                }
#line 1583 "parser.cc"
    break;

  case 61: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data"
#line 598 "parser.yy"
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
                    ctx.expression_.push_back(vendor_class);
                }
#line 1600 "parser.cc"
    break;

  case 62: // string_expr: "vendor-class" "[" enterprise_id "]" "." "data" "[" "integer" "]"
#line 611 "parser.yy"
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
                    ctx.expression_.push_back(vendor_class);
                }
#line 1617 "parser.cc"
    break;

  case 63: // string_expr: integer_expr
#line 624 "parser.yy"
                {
                    TokenPtr integer(new TokenInteger(yystack_[0].value.as < uint32_t > ()));
                    ctx.expression_.push_back(integer);
                }
#line 1626 "parser.cc"
    break;

  case 65: // integer_expr: "integer"
#line 632 "parser.yy"
                 {
                     yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1634 "parser.cc"
    break;

  case 66: // option_code: "integer"
#line 638 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1642 "parser.cc"
    break;

  case 67: // option_code: "option name"
#line 642 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionName(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1650 "parser.cc"
    break;

  case 68: // sub_option_code: "integer"
#line 648 "parser.yy"
                 {
                     yylhs.value.as < uint16_t > () = ctx.convertOptionCode(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1658 "parser.cc"
    break;

  case 69: // option_repr_type: "text"
#line 654 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::TEXTUAL;
                      }
#line 1666 "parser.cc"
    break;

  case 70: // option_repr_type: "hex"
#line 658 "parser.yy"
                      {
                          yylhs.value.as < TokenOption::RepresentationType > () = TokenOption::HEXADECIMAL;
                      }
#line 1674 "parser.cc"
    break;

  case 71: // nest_level: "integer"
#line 664 "parser.yy"
                 {
                     yylhs.value.as < int8_t > () = ctx.convertNestLevelNumber(yystack_[0].value.as < std::string > (), yystack_[0].location);
                 }
#line 1682 "parser.cc"
    break;

  case 72: // pkt_metadata: "iface"
#line 673 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::IFACE;
                  }
#line 1690 "parser.cc"
    break;

  case 73: // pkt_metadata: "src"
#line 677 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::SRC;
                  }
#line 1698 "parser.cc"
    break;

  case 74: // pkt_metadata: "dst"
#line 681 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::DST;
                  }
#line 1706 "parser.cc"
    break;

  case 75: // pkt_metadata: "len"
#line 685 "parser.yy"
                  {
                      yylhs.value.as < TokenPkt::MetadataType > () = TokenPkt::LEN;
                  }
#line 1714 "parser.cc"
    break;

  case 76: // enterprise_id: "integer"
#line 691 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = ctx.convertUint32(yystack_[0].value.as < std::string > (), yystack_[0].location);
                   }
#line 1722 "parser.cc"
    break;

  case 77: // enterprise_id: "*"
#line 695 "parser.yy"
                   {
                       yylhs.value.as < uint32_t > () = 0;
                   }
#line 1730 "parser.cc"
    break;

  case 78: // pkt4_field: "mac"
#line 701 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CHADDR;
                }
#line 1738 "parser.cc"
    break;

  case 79: // pkt4_field: "hlen"
#line 705 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HLEN;
                }
#line 1746 "parser.cc"
    break;

  case 80: // pkt4_field: "htype"
#line 709 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::HTYPE;
                }
#line 1754 "parser.cc"
    break;

  case 81: // pkt4_field: "ciaddr"
#line 713 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::CIADDR;
                }
#line 1762 "parser.cc"
    break;

  case 82: // pkt4_field: "giaddr"
#line 717 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::GIADDR;
                }
#line 1770 "parser.cc"
    break;

  case 83: // pkt4_field: "yiaddr"
#line 721 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::YIADDR;
                }
#line 1778 "parser.cc"
    break;

  case 84: // pkt4_field: "siaddr"
#line 725 "parser.yy"
                {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::SIADDR;
                }
#line 1786 "parser.cc"
    break;

  case 85: // pkt4_field: "msgtype"
#line 729 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::MSGTYPE;
                 }
#line 1794 "parser.cc"
    break;

  case 86: // pkt4_field: "transid"
#line 733 "parser.yy"
                 {
                    yylhs.value.as < TokenPkt4::FieldType > () = TokenPkt4::TRANSID;
                 }
#line 1802 "parser.cc"
    break;

  case 87: // pkt6_field: "msgtype"
#line 739 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::MSGTYPE;
                 }
#line 1810 "parser.cc"
    break;

  case 88: // pkt6_field: "transid"
#line 743 "parser.yy"
                 {
                     yylhs.value.as < TokenPkt6::FieldType > () = TokenPkt6::TRANSID;
                 }
#line 1818 "parser.cc"
    break;

  case 89: // relay6_field: "peeraddr"
#line 749 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::PEERADDR;
                   }
#line 1826 "parser.cc"
    break;

  case 90: // relay6_field: "linkaddr"
#line 753 "parser.yy"
                   {
                       yylhs.value.as < TokenRelay6Field::FieldType > () = TokenRelay6Field::LINKADDR;
                   }
#line 1834 "parser.cc"
    break;

  case 91: // start_expr: "integer"
#line 759 "parser.yy"
                {
                    TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                    ctx.expression_.push_back(str);
                }
#line 1843 "parser.cc"
    break;

  case 92: // length_expr: "integer"
#line 766 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression_.push_back(str);
                 }
#line 1852 "parser.cc"
    break;

  case 93: // length_expr: "all"
#line 771 "parser.yy"
                 {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression_.push_back(str);
                 }
#line 1861 "parser.cc"
    break;

  case 94: // int_expr: "integer"
#line 778 "parser.yy"
                 {
                     TokenPtr str(new TokenString(yystack_[0].value.as < std::string > ()));
                     ctx.expression_.push_back(str);
                 }
#line 1870 "parser.cc"
    break;


#line 1874 "parser.cc"

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


  const short EvalParser::yypact_ninf_ = -193;

  const signed char EvalParser::yytable_ninf_ = -1;

  const short
  EvalParser::yypact_[] =
  {
      64,   207,    89,    58,   207,   207,    -9,    17,    46,    20,
      56,    90,   113,   116,   145,   150,   173,   177,   184,   185,
     203,   208,   214,   220,   226,   231,   272,   243,   105,   166,
     282,  -193,  -193,  -193,  -193,  -193,   244,   251,   252,   283,
     233,    52,  -193,    89,   176,   186,   286,   292,   294,   295,
     274,  -193,   280,    -1,  -193,   228,   250,   253,   255,   266,
     248,    89,    89,    89,   207,   207,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    23,    45,   257,    45,
     261,   258,   146,   187,   205,   211,  -193,   207,  -193,   207,
      89,    89,     2,    45,    45,    86,   152,   217,   225,  -193,
    -193,  -193,  -193,   299,  -193,   303,  -193,   306,   321,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,    43,   256,   259,   143,   153,   260,
       3,     6,     7,     8,     9,    10,    11,    12,    14,  -193,
    -193,  -193,  -193,  -193,   308,  -193,   309,  -193,   289,   312,
    -193,  -193,  -193,  -193,   313,  -193,  -193,   314,  -193,  -193,
     315,  -193,  -193,   207,   327,   207,   163,   274,  -193,   316,
     317,  -193,  -193,   318,  -193,   270,    89,    89,  -193,    89,
      89,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
     319,   320,    89,   250,   228,   228,   228,  -193,   158,   322,
     323,    13,  -193,   301,   267,    15,    89,   268,    33,   -18,
      65,    42,   325,   326,   328,   329,   285,   337,   332,  -193,
    -193,  -193,   -33,   284,  -193,   271,    89,  -193,  -193,   334,
     335,  -193,  -193,  -193,  -193,  -193,  -193,   250,  -193,  -193,
     349,  -193,   350,  -193,    53,   290,   250,   339,  -193,  -193,
      89,  -193,   340,   341,  -193,    73,  -193,  -193,  -193
  };

  const signed char
  EvalParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    65,    31,    32,     2,     0,     0,     0,     0,
       4,     0,    63,     0,     0,     0,     0,     0,     0,     0,
       3,     1,     0,     0,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      64,    66,    67,     0,    68,     0,    71,     0,     0,    72,
      73,    74,    75,    36,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
      88,    38,    77,    76,     0,    59,     0,    58,     0,     0,
      69,    70,    22,    33,     0,    23,    34,     0,    24,    35,
       0,    27,    60,     0,    17,     0,    20,    21,    43,     0,
       0,     5,     7,     0,    28,     0,     0,     0,    46,     0,
       0,    51,    52,    53,    54,    55,    56,    57,    44,    45,
       0,     0,     0,     0,     0,     0,     0,    16,    19,     0,
       0,     0,    91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,    39,     0,     0,    42,     0,     0,    50,    25,    61,
       0,    26,    29,     6,     8,    10,    12,     0,    93,    92,
       0,    94,     0,    47,     0,     0,     0,     0,    40,    41,
       0,    49,     0,     0,     9,     0,    62,    11,    48
  };

  const short
  EvalParser::yypgoto_[] =
  {
    -193,  -193,  -193,    16,    21,    26,    31,    34,  -193,  -193,
      -2,  -193,  -193,  -193,    72,  -192,   117,  -193,  -193,    51,
    -193,  -193,  -193,  -193,  -193,  -193
  };

  const unsigned char
  EvalParser::yydefgoto_[] =
  {
       0,     3,    35,    46,    47,    48,    49,    40,   163,   165,
      41,   206,   250,    42,   103,   105,   153,   107,   113,   144,
     123,   141,   221,   203,   240,   242
  };

  const short
  EvalParser::yytable_[] =
  {
      50,   212,    53,   100,   228,   238,   100,   181,    55,    90,
     182,   183,   184,   185,   186,   187,   188,    36,   189,   224,
      36,    36,    37,    58,   218,    37,    37,    38,   219,   220,
      38,    38,    39,   239,    56,    39,    39,   227,    52,    54,
      91,    92,   229,    91,    91,   247,   232,    91,    91,    91,
      91,    91,    91,    91,   253,    91,    91,   251,    51,   124,
     125,   126,    90,    57,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,    91,    59,   230,   258,   139,   140,
      36,    36,   175,    91,    91,    37,    37,   231,   167,   168,
      38,    38,    43,    91,    91,    39,    39,   149,   127,   128,
       6,     7,     8,    36,   142,    36,   150,   151,    37,    60,
      37,   143,    10,    38,    91,    38,    61,    11,    39,    62,
      39,   164,    77,   166,    78,    12,    13,     1,     2,    14,
     146,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,   169,   170,    44,    45,    63,    86,
      87,    88,    89,    64,    31,    32,    33,   149,    34,    86,
      87,    88,    89,   154,    86,    87,   150,   151,   152,    86,
      87,    88,   150,   151,   204,   205,    65,   207,   208,    36,
      66,    36,   178,    79,    37,    80,    37,    67,    68,    38,
     211,    38,   179,    93,    39,    78,    39,   197,   154,   198,
     156,   159,   162,    94,   225,    80,    69,   150,   151,   155,
       4,    70,     5,   156,   159,   162,   157,    71,     6,     7,
       8,     9,   160,    72,   244,   150,   151,   158,   157,    73,
      10,   150,   151,   161,    74,    11,   160,   150,   151,    86,
      87,    88,    89,    12,    13,   150,   151,    14,   255,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    76,    82,    28,    29,   213,   214,   215,    30,
      83,    84,    31,    32,    33,    75,    34,   114,   115,   116,
     117,   118,   119,   120,    99,    81,    86,    87,    88,    89,
     109,   110,   111,   112,   101,   176,   102,    91,   177,   180,
      91,    91,    85,   121,   122,    95,   223,   226,    91,    91,
     243,    96,    91,    97,    98,    91,   104,   171,   145,   106,
     108,   172,   147,   148,   173,   174,   190,   191,   192,   193,
     194,   195,   196,    86,   199,   200,   202,   201,   209,   210,
     222,   216,   217,   233,   234,   229,   235,   236,   230,   237,
     241,   245,   246,   248,   249,     0,   252,   254,   256,   257
  };

  const short
  EvalParser::yycheck_[] =
  {
       2,   193,     4,     4,    22,    38,     4,     4,    17,    10,
       4,     4,     4,     4,     4,     4,     4,     1,     4,     4,
       4,     5,     1,     3,    11,     4,     5,     1,    15,    16,
       4,     5,     1,    66,    17,     4,     5,     4,     4,     5,
      41,    43,    60,    41,    41,   237,     4,    41,    41,    41,
      41,    41,    41,    41,   246,    41,    41,     4,     0,    61,
      62,    63,    10,    17,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    41,    19,    11,     4,    55,    56,
      64,    65,    39,    41,    41,    64,    65,    22,    90,    91,
      64,    65,     3,    41,    41,    64,    65,    11,    64,    65,
      11,    12,    13,    87,    59,    89,    20,    21,    87,    19,
      89,    66,    23,    87,    41,    89,     3,    28,    87,     3,
      89,    87,    17,    89,    19,    36,    37,    63,    64,    40,
      79,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    93,    94,    57,    58,     3,     6,
       7,     8,     9,     3,    65,    66,    67,    11,    69,     6,
       7,     8,     9,    11,     6,     7,    20,    21,    22,     6,
       7,     8,    20,    21,   176,   177,     3,   179,   180,   163,
       3,   165,    39,    17,   163,    19,   165,     3,     3,   163,
     192,   165,    39,    17,   163,    19,   165,   163,    11,   165,
      83,    84,    85,    17,   206,    19,     3,    20,    21,    22,
       3,     3,     5,    96,    97,    98,    11,     3,    11,    12,
      13,    14,    11,     3,   226,    20,    21,    22,    11,     3,
      23,    20,    21,    22,     3,    28,    11,    20,    21,     6,
       7,     8,     9,    36,    37,    20,    21,    40,   250,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    19,    19,    57,    58,   194,   195,   196,    62,
      19,    19,    65,    66,    67,     3,    69,    29,    30,    31,
      32,    33,    34,    35,     4,     3,     6,     7,     8,     9,
      24,    25,    26,    27,    66,    39,    68,    41,    39,    39,
      41,    41,    19,    55,    56,    19,    39,    39,    41,    41,
      39,    19,    41,    19,    19,    41,    66,    18,    61,    66,
      65,    18,    61,    65,    18,     4,    18,    18,    39,    17,
      17,    17,    17,     6,    18,    18,    66,    19,    19,    19,
      39,    19,    19,    18,    18,    60,    18,    18,    11,    17,
      66,    17,    17,     4,     4,    -1,    66,    18,    18,    18
  };

  const signed char
  EvalParser::yystos_[] =
  {
       0,    63,    64,    71,     3,     5,    11,    12,    13,    14,
      23,    28,    36,    37,    40,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    57,    58,
      62,    65,    66,    67,    69,    72,    73,    74,    75,    76,
      77,    80,    83,     3,    57,    58,    73,    74,    75,    76,
      80,     0,    77,    80,    77,    17,    17,    17,     3,    19,
      19,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,    19,    17,    19,    17,
      19,     3,    19,    19,    19,    19,     6,     7,     8,     9,
      10,    41,    80,    17,    17,    19,    19,    19,    19,     4,
       4,    66,    68,    84,    66,    85,    66,    87,    65,    24,
      25,    26,    27,    88,    29,    30,    31,    32,    33,    34,
      35,    55,    56,    90,    80,    80,    80,    77,    77,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    55,
      56,    91,    59,    66,    89,    61,    89,    61,    65,    11,
      20,    21,    22,    86,    11,    22,    86,    11,    22,    86,
      11,    22,    86,    78,    77,    79,    77,    80,    80,    89,
      89,    18,    18,    18,     4,    39,    39,    39,    39,    39,
      39,     4,     4,     4,     4,     4,     4,     4,     4,     4,
      18,    18,    39,    17,    17,    17,    17,    77,    77,    18,
      18,    19,    66,    93,    80,    80,    81,    80,    80,    19,
      19,    80,    85,    84,    84,    84,    19,    19,    11,    15,
      16,    92,    39,    39,     4,    80,    39,     4,    22,    60,
      11,    22,     4,    18,    18,    18,    18,    17,    38,    66,
      94,    66,    95,    39,    80,    17,    17,    85,     4,     4,
      82,     4,    66,    85,    18,    80,    18,    18,     4
  };

  const signed char
  EvalParser::yyr1_[] =
  {
       0,    70,    71,    71,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    77,    77,    79,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    81,    82,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    83,    84,    84,    85,    86,
      86,    87,    88,    88,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    91,    91,    92,
      92,    93,    94,    94,    95
  };

  const signed char
  EvalParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     4,     6,     4,     6,     9,
       6,     9,     6,     3,     2,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     6,     6,     3,     4,     6,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     6,
       8,     8,     6,     3,     4,     4,     0,     0,    10,     8,
       6,     4,     4,     4,     4,     4,     4,     4,     3,     3,
       3,     6,     9,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
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
  "start", "expression", "option_chain", "relay4_option_chain",
  "relay6_option_chain", "vendor_option_chain", "bool_expr", "$@1", "$@2",
  "string_expr", "$@3", "$@4", "integer_expr", "option_code",
  "sub_option_code", "option_repr_type", "nest_level", "pkt_metadata",
  "enterprise_id", "pkt4_field", "pkt6_field", "relay6_field",
  "start_expr", "length_expr", "int_expr", YY_NULLPTR
  };
#endif


#if EVALDEBUG
  const short
  EvalParser::yyrline_[] =
  {
       0,   168,   168,   169,   174,   177,   181,   188,   196,   203,
     212,   219,   224,   231,   232,   238,   237,   249,   255,   254,
     266,   271,   276,   281,   301,   315,   324,   333,   343,   358,
     369,   374,   379,   384,   389,   410,   425,   430,   444,   458,
     473,   478,   483,   488,   493,   498,   504,   509,   503,   524,
     529,   534,   539,   544,   549,   554,   559,   564,   569,   578,
     588,   597,   610,   623,   628,   631,   637,   641,   647,   653,
     657,   663,   672,   676,   680,   684,   690,   694,   700,   704,
     708,   712,   716,   720,   724,   728,   732,   738,   742,   748,
     752,   758,   765,   770,   777
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
#line 2529 "parser.cc"

#line 784 "parser.yy"

void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
