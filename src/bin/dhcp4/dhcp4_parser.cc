// A Bison parser, made by GNU Bison 3.2.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:438

#include <dhcp4/parser_context.h>

#line 51 "dhcp4_parser.cc" // lalr1.cc:438


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:513
namespace isc { namespace dhcp {
#line 146 "dhcp4_parser.cc" // lalr1.cc:513

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
    :
#if PARSER4_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 194: // value
      case 198: // map_value
      case 244: // socket_type
      case 247: // outbound_interface_value
      case 269: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 355: // hr_mode
      case 504: // ncr_protocol_value
      case 511: // replace_client_name_value
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 177: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 176: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 175: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 174: // "constant string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if defined __cplusplus && 201103L <= __cplusplus
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 194: // value
      case 198: // map_value
      case 244: // socket_type
      case 247: // outbound_interface_value
      case 269: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 355: // hr_mode
      case 504: // ncr_protocol_value
      case 511: // replace_client_name_value
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 177: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 176: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 175: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 174: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if !defined __cplusplus || __cplusplus < 201103L
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 194: // value
      case 198: // map_value
      case 244: // socket_type
      case 247: // outbound_interface_value
      case 269: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 355: // hr_mode
      case 504: // ncr_protocol_value
      case 511: // replace_client_name_value
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
        value.move< ElementPtr > (that.value);
        break;

      case 177: // "boolean"
        value.move< bool > (that.value);
        break;

      case 176: // "floating point"
        value.move< double > (that.value);
        break;

      case 175: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 174: // "constant string"
        value.move< std::string > (that.value);
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo,
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
<<<<<<< HEAD
<<<<<<< HEAD
      case 174: // "constant string"
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case 175: // "integer"
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case 176: // "floating point"
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case 177: // "boolean"
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case 194: // value
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case 198: // map_value
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case 244: // socket_type
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case 247: // outbound_interface_value
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case 269: // db_type
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case 355: // hr_mode
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case 504: // ncr_protocol_value
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case 511: // replace_client_name_value
#line 256 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
=======
            case 174: // "constant string"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 175: // "integer"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 176: // "floating point"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 177: // "boolean"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 194: // value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 198: // map_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 244: // socket_type

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 247: // outbound_interface_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 450 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 269: // db_type

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 457 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 356: // hr_mode

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 464 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 505: // ncr_protocol_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 471 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 512: // replace_client_name_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 478 "dhcp4_parser.cc" // lalr1.cc:672
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
        break;

=======
            case 174: // "constant string"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 175: // "integer"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 176: // "floating point"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 177: // "boolean"

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 194: // value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 198: // map_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 244: // socket_type

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 247: // outbound_interface_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 450 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 269: // db_type

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 457 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 356: // hr_mode

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 464 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 505: // ncr_protocol_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 471 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 512: // replace_client_name_value

#line 256 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 478 "dhcp4_parser.cc" // lalr1.cc:672
        break;

>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if defined __cplusplus && 201103L <= __cplusplus
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp4Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp4Parser::parse ()
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

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

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
  | yyreduce -- Do a reduction.  |
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
      case 194: // value
      case 198: // map_value
      case 244: // socket_type
      case 247: // outbound_interface_value
      case 269: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 355: // hr_mode
      case 504: // ncr_protocol_value
      case 511: // replace_client_name_value
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
      case 356: // hr_mode
      case 505: // ncr_protocol_value
      case 512: // replace_client_name_value
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 177: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 176: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 175: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 174: // "constant string"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
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
  case 2:
<<<<<<< HEAD
<<<<<<< HEAD
#line 265 "dhcp4_parser.yy"
=======
#line 265 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 265 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 4:
<<<<<<< HEAD
<<<<<<< HEAD
#line 266 "dhcp4_parser.yy"
=======
#line 266 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 266 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.CONFIG; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 6:
<<<<<<< HEAD
<<<<<<< HEAD
#line 267 "dhcp4_parser.yy"
=======
#line 267 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 267 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.DHCP4; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 8:
<<<<<<< HEAD
<<<<<<< HEAD
#line 268 "dhcp4_parser.yy"
=======
#line 268 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 268 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 10:
<<<<<<< HEAD
<<<<<<< HEAD
#line 269 "dhcp4_parser.yy"
=======
#line 269 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 269 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.SUBNET4; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 12:
<<<<<<< HEAD
<<<<<<< HEAD
#line 270 "dhcp4_parser.yy"
=======
#line 270 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 270 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.POOLS; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 14:
<<<<<<< HEAD
<<<<<<< HEAD
#line 271 "dhcp4_parser.yy"
=======
#line 271 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 271 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 774 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 16:
<<<<<<< HEAD
<<<<<<< HEAD
#line 272 "dhcp4_parser.yy"
=======
#line 272 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 272 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.DHCP4; }
#line 780 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 18:
<<<<<<< HEAD
<<<<<<< HEAD
#line 273 "dhcp4_parser.yy"
=======
#line 273 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 273 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 786 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 20:
<<<<<<< HEAD
<<<<<<< HEAD
#line 274 "dhcp4_parser.yy"
=======
#line 274 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 274 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 792 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 22:
<<<<<<< HEAD
<<<<<<< HEAD
#line 275 "dhcp4_parser.yy"
=======
#line 275 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 275 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 798 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 24:
<<<<<<< HEAD
<<<<<<< HEAD
#line 276 "dhcp4_parser.yy"
=======
#line 276 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 276 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 804 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 26:
<<<<<<< HEAD
<<<<<<< HEAD
#line 277 "dhcp4_parser.yy"
=======
#line 277 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 277 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.LOGGING; }
#line 810 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 28:
<<<<<<< HEAD
<<<<<<< HEAD
#line 278 "dhcp4_parser.yy"
=======
#line 278 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 278 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 816 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 30:
<<<<<<< HEAD
<<<<<<< HEAD
#line 286 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 825 "dhcp4_parser.cc"
    break;

  case 31:
#line 287 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 831 "dhcp4_parser.cc"
    break;

  case 32:
#line 288 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 837 "dhcp4_parser.cc"
    break;

  case 33:
#line 289 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 843 "dhcp4_parser.cc"
    break;

  case 34:
#line 290 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 849 "dhcp4_parser.cc"
    break;

  case 35:
#line 291 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 855 "dhcp4_parser.cc"
    break;

  case 36:
#line 292 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 861 "dhcp4_parser.cc"
    break;

  case 37:
#line 295 "dhcp4_parser.yy"
=======
#line 286 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 822 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 31:
#line 287 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 288 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 289 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 290 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 291 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 852 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 292 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 295 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 286 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 822 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 31:
#line 287 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 288 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 289 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 290 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 291 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 852 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 292 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 295 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 867 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 38:
<<<<<<< HEAD
<<<<<<< HEAD
#line 300 "dhcp4_parser.yy"
=======
#line 300 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 300 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 39:
<<<<<<< HEAD
<<<<<<< HEAD
#line 305 "dhcp4_parser.yy"
=======
#line 305 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 305 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 40:
<<<<<<< HEAD
<<<<<<< HEAD
#line 311 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp4_parser.cc"
    break;

  case 43:
#line 318 "dhcp4_parser.yy"
=======
#line 311 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 894 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 43:
#line 318 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 311 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 894 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 43:
#line 318 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 903 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 44:
<<<<<<< HEAD
<<<<<<< HEAD
#line 322 "dhcp4_parser.yy"
=======
#line 322 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 322 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 913 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 45:
<<<<<<< HEAD
<<<<<<< HEAD
#line 329 "dhcp4_parser.yy"
=======
#line 329 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 329 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 922 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 46:
<<<<<<< HEAD
<<<<<<< HEAD
#line 332 "dhcp4_parser.yy"
=======
#line 332 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 332 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // list parsing complete. Put any sanity checking here
}
#line 930 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 49:
<<<<<<< HEAD
<<<<<<< HEAD
#line 340 "dhcp4_parser.yy"
=======
#line 340 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 340 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 939 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 50:
<<<<<<< HEAD
<<<<<<< HEAD
#line 344 "dhcp4_parser.yy"
=======
#line 344 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 344 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 51:
<<<<<<< HEAD
<<<<<<< HEAD
#line 351 "dhcp4_parser.yy"
=======
#line 351 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 351 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // List parsing about to start
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 52:
<<<<<<< HEAD
<<<<<<< HEAD
#line 353 "dhcp4_parser.yy"
=======
#line 353 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 353 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 965 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 55:
<<<<<<< HEAD
<<<<<<< HEAD
#line 362 "dhcp4_parser.yy"
=======
#line 362 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 362 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 974 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 56:
<<<<<<< HEAD
<<<<<<< HEAD
#line 366 "dhcp4_parser.yy"
=======
#line 366 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 366 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 983 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 57:
<<<<<<< HEAD
<<<<<<< HEAD
#line 377 "dhcp4_parser.yy"
=======
#line 377 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 377 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 58:
<<<<<<< HEAD
<<<<<<< HEAD
#line 387 "dhcp4_parser.yy"
=======
#line 387 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 387 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 59:
<<<<<<< HEAD
<<<<<<< HEAD
#line 392 "dhcp4_parser.yy"
=======
#line 392 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 392 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 68:
<<<<<<< HEAD
<<<<<<< HEAD
#line 416 "dhcp4_parser.yy"
=======
#line 416 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 416 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1031 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 69:
<<<<<<< HEAD
<<<<<<< HEAD
#line 423 "dhcp4_parser.yy"
=======
#line 423 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 423 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 70:
<<<<<<< HEAD
<<<<<<< HEAD
#line 431 "dhcp4_parser.yy"
=======
#line 431 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 431 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 71:
<<<<<<< HEAD
<<<<<<< HEAD
#line 435 "dhcp4_parser.yy"
=======
#line 435 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 435 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // No global parameter is required
    // parsing completed
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 116:
<<<<<<< HEAD
<<<<<<< HEAD
#line 490 "dhcp4_parser.yy"
=======
#line 490 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 490 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1069 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 117:
<<<<<<< HEAD
<<<<<<< HEAD
#line 495 "dhcp4_parser.yy"
=======
#line 495 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 495 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1078 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 118:
<<<<<<< HEAD
<<<<<<< HEAD
#line 500 "dhcp4_parser.yy"
=======
#line 500 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 500 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1087 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 119:
<<<<<<< HEAD
<<<<<<< HEAD
#line 505 "dhcp4_parser.yy"
=======
#line 505 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 505 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1096 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 120:
<<<<<<< HEAD
<<<<<<< HEAD
#line 510 "dhcp4_parser.yy"
=======
#line 510 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 510 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 121:
<<<<<<< HEAD
<<<<<<< HEAD
#line 515 "dhcp4_parser.yy"
=======
#line 515 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 515 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 122:
<<<<<<< HEAD
<<<<<<< HEAD
#line 520 "dhcp4_parser.yy"
=======
#line 520 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 520 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1123 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 123:
<<<<<<< HEAD
<<<<<<< HEAD
#line 525 "dhcp4_parser.yy"
=======
#line 525 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 525 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 124:
<<<<<<< HEAD
<<<<<<< HEAD
#line 530 "dhcp4_parser.yy"
=======
#line 530 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 530 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1141 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 125:
<<<<<<< HEAD
<<<<<<< HEAD
#line 535 "dhcp4_parser.yy"
=======
#line 535 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 535 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1149 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 126:
<<<<<<< HEAD
<<<<<<< HEAD
#line 537 "dhcp4_parser.yy"
=======
#line 537 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 537 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1159 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 127:
<<<<<<< HEAD
<<<<<<< HEAD
#line 543 "dhcp4_parser.yy"
=======
#line 543 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 543 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1168 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 128:
<<<<<<< HEAD
<<<<<<< HEAD
#line 548 "dhcp4_parser.yy"
=======
#line 548 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 548 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1177 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 129:
<<<<<<< HEAD
<<<<<<< HEAD
#line 553 "dhcp4_parser.yy"
=======
#line 553 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 553 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1186 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 130:
<<<<<<< HEAD
<<<<<<< HEAD
#line 559 "dhcp4_parser.yy"
=======
#line 559 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 559 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1197 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 131:
<<<<<<< HEAD
<<<<<<< HEAD
#line 564 "dhcp4_parser.yy"
=======
#line 564 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 564 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 141:
<<<<<<< HEAD
<<<<<<< HEAD
#line 583 "dhcp4_parser.yy"
=======
#line 583 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 583 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 142:
<<<<<<< HEAD
<<<<<<< HEAD
#line 587 "dhcp4_parser.yy"
=======
#line 587 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 587 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 143:
<<<<<<< HEAD
<<<<<<< HEAD
#line 592 "dhcp4_parser.yy"
=======
#line 592 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 592 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 144:
<<<<<<< HEAD
<<<<<<< HEAD
#line 597 "dhcp4_parser.yy"
=======
#line 597 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 597 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 145:
<<<<<<< HEAD
<<<<<<< HEAD
#line 602 "dhcp4_parser.yy"
=======
#line 602 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 602 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1254 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 146:
<<<<<<< HEAD
<<<<<<< HEAD
#line 604 "dhcp4_parser.yy"
=======
#line 604 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 604 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1263 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 147:
<<<<<<< HEAD
<<<<<<< HEAD
#line 609 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1272 "dhcp4_parser.cc"
    break;

  case 148:
#line 610 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1278 "dhcp4_parser.cc"
    break;

  case 149:
#line 613 "dhcp4_parser.yy"
=======
#line 609 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1269 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 610 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1275 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 613 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 609 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1269 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 610 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1275 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 613 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 150:
<<<<<<< HEAD
<<<<<<< HEAD
#line 615 "dhcp4_parser.yy"
=======
#line 615 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 615 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 151:
<<<<<<< HEAD
<<<<<<< HEAD
#line 620 "dhcp4_parser.yy"
=======
#line 620 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 620 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1300 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 152:
<<<<<<< HEAD
<<<<<<< HEAD
#line 622 "dhcp4_parser.yy"
=======
#line 622 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 622 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1308 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 153:
<<<<<<< HEAD
<<<<<<< HEAD
#line 626 "dhcp4_parser.yy"
=======
#line 626 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 626 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 154:
<<<<<<< HEAD
<<<<<<< HEAD
#line 632 "dhcp4_parser.yy"
=======
#line 632 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 632 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1328 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 155:
<<<<<<< HEAD
<<<<<<< HEAD
#line 637 "dhcp4_parser.yy"
=======
#line 637 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 637 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1339 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 156:
<<<<<<< HEAD
<<<<<<< HEAD
#line 644 "dhcp4_parser.yy"
=======
#line 644 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 644 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1350 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 157:
<<<<<<< HEAD
<<<<<<< HEAD
#line 649 "dhcp4_parser.yy"
=======
#line 649 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 649 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1359 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 161:
<<<<<<< HEAD
<<<<<<< HEAD
#line 659 "dhcp4_parser.yy"
=======
#line 659 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 659 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1367 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 162:
<<<<<<< HEAD
<<<<<<< HEAD
#line 661 "dhcp4_parser.yy"
=======
#line 661 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 661 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
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
#line 1387 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 163:
<<<<<<< HEAD
<<<<<<< HEAD
#line 677 "dhcp4_parser.yy"
=======
#line 677 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 677 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1398 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 164:
<<<<<<< HEAD
<<<<<<< HEAD
#line 682 "dhcp4_parser.yy"
=======
#line 682 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 682 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1409 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 165:
<<<<<<< HEAD
<<<<<<< HEAD
#line 689 "dhcp4_parser.yy"
=======
#line 689 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 689 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1420 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 166:
<<<<<<< HEAD
<<<<<<< HEAD
#line 694 "dhcp4_parser.yy"
=======
#line 694 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 694 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1429 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 171:
<<<<<<< HEAD
<<<<<<< HEAD
#line 707 "dhcp4_parser.yy"
=======
#line 707 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 707 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1439 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 172:
<<<<<<< HEAD
<<<<<<< HEAD
#line 711 "dhcp4_parser.yy"
=======
#line 711 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 711 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1449 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 195:
#line 743 "dhcp4_parser.yy"
=======
  case 196:
#line 744 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 196:
#line 744 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1457 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 196:
#line 745 "dhcp4_parser.yy"
=======
  case 197:
#line 746 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 197:
#line 746 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1469 "dhcp4_parser.cc"
    break;

  case 197:
#line 750 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1475 "dhcp4_parser.cc"
    break;

  case 198:
#line 751 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1481 "dhcp4_parser.cc"
    break;

  case 199:
#line 752 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1487 "dhcp4_parser.cc"
    break;

  case 200:
#line 753 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1493 "dhcp4_parser.cc"
    break;

  case 201:
#line 756 "dhcp4_parser.yy"
=======
#line 1466 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 751 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1472 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 752 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1478 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 753 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1484 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 201:
=======
#line 1466 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 751 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1472 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 752 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1478 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 753 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1484 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 201:
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
#line 754 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1490 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 757 "dhcp4_parser.yy" // lalr1.cc:907
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 202:
#line 758 "dhcp4_parser.yy"
=======
  case 203:
#line 759 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 203:
#line 759 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 203:
#line 764 "dhcp4_parser.yy"
=======
  case 204:
#line 765 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 204:
#line 765 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 204:
#line 766 "dhcp4_parser.yy"
=======
  case 205:
#line 767 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 205:
#line 767 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 205:
#line 772 "dhcp4_parser.yy"
=======
  case 206:
#line 773 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 206:
#line 773 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 206:
#line 774 "dhcp4_parser.yy"
=======
  case 207:
#line 775 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 207:
#line 775 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 207:
#line 780 "dhcp4_parser.yy"
=======
  case 208:
#line 781 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 208:
#line 781 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 208:
#line 785 "dhcp4_parser.yy"
=======
  case 209:
#line 786 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 209:
#line 786 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 209:
#line 787 "dhcp4_parser.yy"
=======
  case 210:
#line 788 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 210:
#line 788 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1571 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 210:
#line 793 "dhcp4_parser.yy"
=======
  case 211:
#line 794 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 211:
#line 794 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 211:
#line 798 "dhcp4_parser.yy"
=======
  case 212:
#line 799 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 212:
#line 799 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1589 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 212:
#line 803 "dhcp4_parser.yy"
=======
  case 213:
#line 804 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 213:
#line 804 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 213:
#line 808 "dhcp4_parser.yy"
=======
  case 214:
#line 809 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 214:
#line 809 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 214:
#line 813 "dhcp4_parser.yy"
=======
  case 215:
#line 814 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 215:
#line 814 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 215:
#line 818 "dhcp4_parser.yy"
=======
  case 216:
#line 819 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 216:
#line 819 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 216:
#line 823 "dhcp4_parser.yy"
=======
  case 217:
#line 824 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 217:
#line 824 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 217:
#line 828 "dhcp4_parser.yy"
=======
  case 218:
#line 829 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 218:
#line 829 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 218:
#line 830 "dhcp4_parser.yy"
=======
  case 219:
#line 831 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 219:
#line 831 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 219:
#line 836 "dhcp4_parser.yy"
=======
  case 220:
#line 837 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 220:
#line 837 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1660 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 220:
#line 838 "dhcp4_parser.yy"
=======
  case 221:
#line 839 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 221:
#line 839 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1670 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 221:
#line 844 "dhcp4_parser.yy"
=======
  case 222:
#line 845 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 222:
#line 845 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 222:
#line 846 "dhcp4_parser.yy"
=======
  case 223:
#line 847 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 223:
#line 847 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 223:
#line 852 "dhcp4_parser.yy"
=======
  case 224:
#line 853 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 224:
#line 853 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1696 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 224:
#line 854 "dhcp4_parser.yy"
=======
  case 225:
#line 855 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 225:
#line 855 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1706 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 225:
#line 860 "dhcp4_parser.yy"
=======
  case 226:
#line 861 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 226:
#line 861 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1715 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 226:
#line 865 "dhcp4_parser.yy"
=======
  case 227:
#line 866 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 227:
#line 866 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 227:
#line 870 "dhcp4_parser.yy"
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  case 228:
#line 871 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1733 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 877 "dhcp4_parser.yy" // lalr1.cc:907
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1744 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 228:
#line 875 "dhcp4_parser.yy"
=======
  case 230:
#line 882 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 230:
#line 882 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 236:
#line 891 "dhcp4_parser.yy"
=======
  case 238:
#line 898 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 238:
#line 898 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1762 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 237:
#line 896 "dhcp4_parser.yy"
=======
  case 239:
#line 903 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 239:
#line 903 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 238:
#line 901 "dhcp4_parser.yy"
=======
  case 240:
#line 908 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 240:
#line 908 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 239:
#line 906 "dhcp4_parser.yy"
=======
  case 241:
#line 913 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 241:
#line 913 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 240:
#line 911 "dhcp4_parser.yy"
=======
  case 242:
#line 918 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 242:
#line 918 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 241:
#line 916 "dhcp4_parser.yy"
=======
  case 243:
#line 923 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 243:
#line 923 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1809 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 242:
#line 921 "dhcp4_parser.yy"
=======
  case 244:
#line 928 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 244:
#line 928 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1818 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 247:
#line 934 "dhcp4_parser.yy"
=======
  case 249:
#line 941 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 249:
#line 941 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1828 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 248:
#line 938 "dhcp4_parser.yy"
=======
  case 250:
#line 945 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 250:
#line 945 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1838 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 249:
#line 944 "dhcp4_parser.yy"
=======
  case 251:
#line 951 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 251:
#line 951 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 250:
#line 948 "dhcp4_parser.yy"
=======
  case 252:
#line 955 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 252:
#line 955 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1858 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 256:
#line 963 "dhcp4_parser.yy"
=======
  case 258:
#line 970 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 258:
#line 970 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 257:
#line 965 "dhcp4_parser.yy"
=======
  case 259:
#line 972 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 259:
#line 972 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 258:
#line 971 "dhcp4_parser.yy"
=======
  case 260:
#line 978 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 260:
#line 978 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 259:
#line 973 "dhcp4_parser.yy"
=======
  case 261:
#line 980 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 261:
#line 980 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 260:
#line 979 "dhcp4_parser.yy"
=======
  case 262:
#line 986 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 262:
#line 986 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1904 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 261:
#line 984 "dhcp4_parser.yy"
=======
  case 263:
#line 991 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 263:
#line 991 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1914 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 270:
#line 1002 "dhcp4_parser.yy"
=======
  case 272:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 272:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 271:
#line 1007 "dhcp4_parser.yy"
=======
  case 273:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 273:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1932 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 272:
#line 1012 "dhcp4_parser.yy"
=======
  case 274:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 274:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 273:
#line 1017 "dhcp4_parser.yy"
=======
  case 275:
#line 1024 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 275:
#line 1024 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1950 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 274:
#line 1022 "dhcp4_parser.yy"
=======
  case 276:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 276:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 275:
#line 1027 "dhcp4_parser.yy"
=======
  case 277:
#line 1034 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 277:
#line 1034 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1968 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 276:
#line 1035 "dhcp4_parser.yy"
=======
  case 278:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 278:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1979 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 277:
#line 1040 "dhcp4_parser.yy"
=======
  case 279:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 279:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 282:
#line 1060 "dhcp4_parser.yy"
=======
  case 284:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 284:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 283:
#line 1064 "dhcp4_parser.yy"
=======
  case 285:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 285:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 284:
#line 1086 "dhcp4_parser.yy"
=======
  case 286:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 286:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 285:
#line 1090 "dhcp4_parser.yy"
=======
  case 287:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 287:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 317:
#line 1133 "dhcp4_parser.yy"
=======
  case 319:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 319:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 318:
#line 1135 "dhcp4_parser.yy"
=======
  case 320:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 320:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 319:
#line 1141 "dhcp4_parser.yy"
=======
  case 321:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 321:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2070 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 320:
#line 1143 "dhcp4_parser.yy"
=======
  case 322:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 322:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2080 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 321:
#line 1149 "dhcp4_parser.yy"
=======
  case 323:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 323:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2088 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 322:
#line 1151 "dhcp4_parser.yy"
=======
  case 324:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 324:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2098 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 323:
#line 1157 "dhcp4_parser.yy"
=======
  case 325:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 325:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2106 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 324:
#line 1159 "dhcp4_parser.yy"
=======
  case 326:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 326:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2116 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 325:
#line 1165 "dhcp4_parser.yy"
=======
  case 327:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 327:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 326:
#line 1167 "dhcp4_parser.yy"
=======
  case 328:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 328:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2134 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 327:
#line 1173 "dhcp4_parser.yy"
=======
  case 329:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 329:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 328:
#line 1175 "dhcp4_parser.yy"
=======
  case 330:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 330:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 329:
#line 1181 "dhcp4_parser.yy"
=======
  case 331:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 331:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2163 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 330:
#line 1186 "dhcp4_parser.yy"
=======
  case 332:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 332:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 331:
#line 1191 "dhcp4_parser.yy"
=======
  case 333:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 333:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2180 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 332:
#line 1193 "dhcp4_parser.yy"
=======
  case 334:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 334:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2189 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 333:
#line 1198 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2189 "dhcp4_parser.cc"
    break;

  case 334:
#line 1199 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2195 "dhcp4_parser.cc"
    break;

  case 335:
#line 1200 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2201 "dhcp4_parser.cc"
    break;

  case 336:
#line 1201 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2207 "dhcp4_parser.cc"
    break;

  case 337:
#line 1204 "dhcp4_parser.yy"
=======
  case 335:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2195 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 336:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2201 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 337:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2207 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 338:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2213 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 339:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 335:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2195 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 336:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2201 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 337:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2207 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 338:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2213 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 339:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 338:
#line 1211 "dhcp4_parser.yy"
=======
  case 340:
#line 1218 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 340:
#line 1218 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 339:
#line 1216 "dhcp4_parser.yy"
=======
  case 341:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 341:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 344:
#line 1231 "dhcp4_parser.yy"
=======
  case 346:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 346:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 345:
#line 1235 "dhcp4_parser.yy"
=======
  case 347:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 347:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 372:
#line 1273 "dhcp4_parser.yy"
=======
  case 374:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 374:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2271 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 373:
#line 1278 "dhcp4_parser.yy"
=======
  case 375:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 375:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2280 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 374:
#line 1286 "dhcp4_parser.yy"
=======
  case 376:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 376:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2289 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 375:
#line 1289 "dhcp4_parser.yy"
=======
  case 377:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 377:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // parsing completed
}
#line 2297 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 380:
#line 1305 "dhcp4_parser.yy"
=======
  case 382:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 382:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 381:
#line 1309 "dhcp4_parser.yy"
=======
  case 383:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 383:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2319 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 382:
#line 1320 "dhcp4_parser.yy"
=======
  case 384:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 384:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 383:
#line 1324 "dhcp4_parser.yy"
=======
  case 385:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 385:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 399:
#line 1356 "dhcp4_parser.yy"
=======
  case 401:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 401:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 401:
#line 1363 "dhcp4_parser.yy"
=======
  case 403:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 403:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2358 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 402:
#line 1365 "dhcp4_parser.yy"
=======
  case 404:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 404:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2368 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 403:
#line 1371 "dhcp4_parser.yy"
=======
  case 405:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 405:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2376 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 404:
#line 1373 "dhcp4_parser.yy"
=======
  case 406:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 406:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2386 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 405:
#line 1379 "dhcp4_parser.yy"
=======
  case 407:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 407:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2394 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 406:
#line 1381 "dhcp4_parser.yy"
=======
  case 408:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 408:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2404 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 408:
#line 1389 "dhcp4_parser.yy"
=======
  case 410:
#line 1396 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 410:
#line 1396 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2412 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 409:
#line 1391 "dhcp4_parser.yy"
=======
  case 411:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 411:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2422 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 410:
#line 1397 "dhcp4_parser.yy"
=======
  case 412:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 412:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2431 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 411:
#line 1406 "dhcp4_parser.yy"
=======
  case 413:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 413:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 412:
#line 1411 "dhcp4_parser.yy"
=======
  case 414:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 414:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2451 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 417:
#line 1430 "dhcp4_parser.yy"
=======
  case 419:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 419:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2461 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 418:
#line 1434 "dhcp4_parser.yy"
=======
  case 420:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 420:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 419:
#line 1442 "dhcp4_parser.yy"
=======
  case 421:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 421:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 420:
#line 1446 "dhcp4_parser.yy"
=======
  case 422:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 422:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 435:
#line 1479 "dhcp4_parser.yy"
=======
  case 437:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 437:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2497 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 436:
#line 1481 "dhcp4_parser.yy"
=======
  case 438:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 438:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2507 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 439:
#line 1491 "dhcp4_parser.yy"
=======
  case 441:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 441:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 440:
#line 1496 "dhcp4_parser.yy"
=======
  case 442:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 442:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2525 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 441:
#line 1504 "dhcp4_parser.yy"
=======
  case 443:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 443:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 442:
#line 1509 "dhcp4_parser.yy"
=======
  case 444:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 444:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 447:
#line 1524 "dhcp4_parser.yy"
=======
  case 449:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 449:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 448:
#line 1528 "dhcp4_parser.yy"
=======
  case 450:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 450:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 449:
#line 1534 "dhcp4_parser.yy"
=======
  case 451:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 451:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 450:
#line 1538 "dhcp4_parser.yy"
=======
  case 452:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 452:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2585 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 460:
#line 1557 "dhcp4_parser.yy"
=======
  case 462:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 462:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2593 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 461:
#line 1559 "dhcp4_parser.yy"
=======
  case 463:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 463:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2603 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 462:
#line 1565 "dhcp4_parser.yy"
=======
  case 464:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 464:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2611 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 463:
#line 1567 "dhcp4_parser.yy"
=======
  case 465:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 465:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
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
#line 2638 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 464:
#line 1590 "dhcp4_parser.yy"
=======
  case 466:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 466:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 465:
#line 1592 "dhcp4_parser.yy"
=======
  case 467:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 467:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
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
#line 2675 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 466:
#line 1620 "dhcp4_parser.yy"
=======
  case 468:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 468:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 467:
#line 1625 "dhcp4_parser.yy"
=======
  case 469:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 469:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2695 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 472:
#line 1638 "dhcp4_parser.yy"
=======
  case 474:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 474:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 473:
#line 1642 "dhcp4_parser.yy"
=======
  case 475:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 475:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 474:
#line 1647 "dhcp4_parser.yy"
=======
  case 476:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 476:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2724 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 475:
#line 1651 "dhcp4_parser.yy"
=======
  case 477:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 477:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2733 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 495:
#line 1682 "dhcp4_parser.yy"
=======
  case 497:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 497:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 496:
#line 1684 "dhcp4_parser.yy"
=======
  case 498:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 498:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2751 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 497:
#line 1690 "dhcp4_parser.yy"
=======
  case 499:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 499:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 498:
#line 1692 "dhcp4_parser.yy"
=======
  case 500:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 500:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 499:
#line 1698 "dhcp4_parser.yy"
=======
  case 501:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 501:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 500:
#line 1700 "dhcp4_parser.yy"
=======
  case 502:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 502:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2787 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 501:
#line 1706 "dhcp4_parser.yy"
=======
  case 503:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 503:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 502:
#line 1708 "dhcp4_parser.yy"
=======
  case 504:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 504:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 503:
#line 1714 "dhcp4_parser.yy"
=======
  case 505:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 505:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2816 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 504:
#line 1719 "dhcp4_parser.yy"
=======
  case 506:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 506:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2825 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 505:
#line 1724 "dhcp4_parser.yy"
=======
  case 507:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 507:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 506:
#line 1726 "dhcp4_parser.yy"
=======
  case 508:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 508:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2843 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 507:
#line 1732 "dhcp4_parser.yy"
=======
  case 509:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 509:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2851 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 508:
#line 1734 "dhcp4_parser.yy"
=======
  case 510:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 510:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2861 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 509:
#line 1740 "dhcp4_parser.yy"
=======
  case 511:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 511:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2869 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 510:
#line 1742 "dhcp4_parser.yy"
=======
  case 512:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 512:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 511:
#line 1748 "dhcp4_parser.yy"
=======
  case 513:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 513:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 512:
#line 1750 "dhcp4_parser.yy"
=======
  case 514:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 514:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2897 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 513:
#line 1756 "dhcp4_parser.yy"
=======
  case 515:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 515:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2905 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 514:
#line 1758 "dhcp4_parser.yy"
=======
  case 516:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 516:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2915 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 515:
#line 1764 "dhcp4_parser.yy"
=======
  case 517:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 517:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 516:
#line 1766 "dhcp4_parser.yy"
=======
  case 518:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 518:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2933 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 517:
#line 1772 "dhcp4_parser.yy"
=======
  case 519:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 519:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 518:
#line 1777 "dhcp4_parser.yy"
=======
  case 520:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 520:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 519:
#line 1785 "dhcp4_parser.yy"
=======
  case 521:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 521:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2964 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 520:
#line 1790 "dhcp4_parser.yy"
=======
  case 522:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 522:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2973 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 523:
#line 1802 "dhcp4_parser.yy"
=======
  case 525:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 525:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2984 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 524:
#line 1807 "dhcp4_parser.yy"
=======
  case 526:
#line 1814 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 526:
#line 1814 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 527:
#line 1816 "dhcp4_parser.yy"
=======
  case 529:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 529:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3003 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 528:
#line 1820 "dhcp4_parser.yy"
=======
  case 530:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 530:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3013 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 545:
#line 1849 "dhcp4_parser.yy"
=======
  case 547:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 547:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3021 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 546:
#line 1851 "dhcp4_parser.yy"
=======
  case 548:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 548:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3031 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 547:
#line 1857 "dhcp4_parser.yy"
=======
  case 549:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 549:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3040 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 548:
#line 1866 "dhcp4_parser.yy"
=======
  case 550:
#line 1873 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 550:
#line 1873 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3049 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 549:
#line 1873 "dhcp4_parser.yy"
=======
  case 551:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 551:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3060 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 550:
#line 1878 "dhcp4_parser.yy"
=======
  case 552:
#line 1885 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 552:
#line 1885 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3069 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 558:
#line 1894 "dhcp4_parser.yy"
=======
  case 560:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 560:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3077 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 559:
#line 1896 "dhcp4_parser.yy"
=======
  case 561:
#line 1903 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 561:
#line 1903 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 560:
#line 1902 "dhcp4_parser.yy"
=======
  case 562:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 562:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 561:
#line 1904 "dhcp4_parser.yy"
=======
  case 563:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 563:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 562:
#line 1913 "dhcp4_parser.yy"
=======
  case 564:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 564:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 563:
#line 1915 "dhcp4_parser.yy"
=======
  case 565:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 565:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr qc = yystack_[0].value.as< ElementPtr > ();
    ctx.stack_.back()->set("dhcp-queue-control", qc);

    // Doing this manually, because dhcp-queue-control
    // content is otherwise arbitrary
    if (!qc->contains("enable-queue")) {
        std::stringstream msg;
        msg << "'enable-queue' is required: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    if (qc->contains("queue-type")) {
        ConstElementPtr queue_type = qc->get("queue-type");
        if (queue_type->getType() != Element::string) {
            std::stringstream msg;
            msg << "'queue-type' must be a string: ";
            msg  << "(" << qc->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
    }

    ctx.leave();
}
#line 3151 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 564:
#line 1951 "dhcp4_parser.yy"
=======
  case 566:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 566:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3162 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 565:
#line 1956 "dhcp4_parser.yy"
=======
  case 567:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 567:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 566:
#line 1963 "dhcp4_parser.yy"
=======
  case 568:
#line 1970 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 568:
#line 1970 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3183 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 567:
#line 1967 "dhcp4_parser.yy"
=======
  case 569:
#line 1974 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 569:
#line 1974 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3193 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 588:
#line 1997 "dhcp4_parser.yy"
=======
  case 590:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 590:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3202 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 589:
#line 2002 "dhcp4_parser.yy"
=======
  case 591:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 591:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3210 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 590:
#line 2004 "dhcp4_parser.yy"
=======
  case 592:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 592:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3220 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 591:
#line 2010 "dhcp4_parser.yy"
=======
  case 593:
#line 2017 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 593:
#line 2017 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3228 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 592:
#line 2012 "dhcp4_parser.yy"
=======
  case 594:
#line 2019 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 594:
#line 2019 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3238 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 593:
#line 2018 "dhcp4_parser.yy"
=======
  case 595:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 595:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3247 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 594:
#line 2023 "dhcp4_parser.yy"
=======
  case 596:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 596:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3255 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 595:
#line 2025 "dhcp4_parser.yy"
=======
  case 597:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 597:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3265 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 596:
#line 2031 "dhcp4_parser.yy"
=======
  case 598:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 598:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3274 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 597:
#line 2036 "dhcp4_parser.yy"
=======
  case 599:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 599:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3283 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 598:
#line 2041 "dhcp4_parser.yy"
=======
  case 600:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 600:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3291 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 599:
#line 2043 "dhcp4_parser.yy"
=======
  case 601:
#line 2050 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 601:
#line 2050 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3300 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 600:
#line 2049 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3300 "dhcp4_parser.cc"
    break;

  case 601:
#line 2050 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3306 "dhcp4_parser.cc"
    break;

  case 602:
#line 2053 "dhcp4_parser.yy"
=======
  case 602:
#line 2056 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3306 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2057 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3312 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 602:
#line 2056 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3306 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2057 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3312 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3320 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 603:
#line 2055 "dhcp4_parser.yy"
=======
  case 605:
#line 2062 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 605:
#line 2062 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3330 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 604:
#line 2061 "dhcp4_parser.yy"
=======
  case 606:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 606:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3339 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 605:
#line 2066 "dhcp4_parser.yy"
=======
  case 607:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 607:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3348 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 606:
#line 2071 "dhcp4_parser.yy"
=======
  case 608:
#line 2078 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 608:
#line 2078 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3356 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 607:
#line 2073 "dhcp4_parser.yy"
=======
  case 609:
#line 2080 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 609:
#line 2080 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3365 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 608:
#line 2079 "dhcp4_parser.yy"
=======
  case 610:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 610:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3373 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 609:
#line 2082 "dhcp4_parser.yy"
=======
  case 611:
#line 2089 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 611:
#line 2089 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3381 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 610:
#line 2085 "dhcp4_parser.yy"
=======
  case 612:
#line 2092 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 612:
#line 2092 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3389 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 611:
#line 2088 "dhcp4_parser.yy"
=======
  case 613:
#line 2095 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 613:
#line 2095 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3397 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 612:
#line 2091 "dhcp4_parser.yy"
=======
  case 614:
#line 2098 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 614:
#line 2098 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3406 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 613:
#line 2097 "dhcp4_parser.yy"
=======
  case 615:
#line 2104 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 615:
#line 2104 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3414 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 614:
#line 2099 "dhcp4_parser.yy"
=======
  case 616:
#line 2106 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 616:
#line 2106 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3424 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 615:
#line 2105 "dhcp4_parser.yy"
=======
  case 617:
#line 2112 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 617:
#line 2112 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3432 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 616:
#line 2107 "dhcp4_parser.yy"
=======
  case 618:
#line 2114 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 618:
#line 2114 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3442 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 617:
#line 2113 "dhcp4_parser.yy"
=======
  case 619:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 619:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3450 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 618:
#line 2115 "dhcp4_parser.yy"
=======
  case 620:
#line 2122 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 620:
#line 2122 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 619:
#line 2124 "dhcp4_parser.yy"
=======
  case 621:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 621:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3468 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 620:
#line 2126 "dhcp4_parser.yy"
=======
  case 622:
#line 2133 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 622:
#line 2133 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3477 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 621:
#line 2131 "dhcp4_parser.yy"
=======
  case 623:
#line 2138 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 623:
#line 2138 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 622:
#line 2133 "dhcp4_parser.yy"
=======
  case 624:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 624:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3494 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 623:
#line 2138 "dhcp4_parser.yy"
=======
  case 625:
#line 2145 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 625:
#line 2145 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3502 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 624:
#line 2140 "dhcp4_parser.yy"
=======
  case 626:
#line 2147 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 626:
#line 2147 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3511 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 625:
#line 2145 "dhcp4_parser.yy"
=======
  case 627:
#line 2152 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 627:
#line 2152 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3522 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 626:
#line 2150 "dhcp4_parser.yy"
=======
  case 628:
#line 2157 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 628:
#line 2157 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3532 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 627:
#line 2156 "dhcp4_parser.yy"
=======
  case 629:
#line 2163 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 629:
#line 2163 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3542 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 628:
#line 2160 "dhcp4_parser.yy"
=======
  case 630:
#line 2167 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 630:
#line 2167 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // No config_control params are required
    // parsing completed
}
#line 3551 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 633:
#line 2175 "dhcp4_parser.yy"
=======
  case 635:
#line 2182 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 635:
#line 2182 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3562 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 634:
#line 2180 "dhcp4_parser.yy"
=======
  case 636:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 636:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3571 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 635:
#line 2185 "dhcp4_parser.yy"
=======
  case 637:
#line 2192 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 637:
#line 2192 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3580 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 636:
#line 2195 "dhcp4_parser.yy"
=======
  case 638:
#line 2202 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 638:
#line 2202 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3591 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 637:
#line 2200 "dhcp4_parser.yy"
=======
  case 639:
#line 2207 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 639:
#line 2207 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3600 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 638:
#line 2205 "dhcp4_parser.yy"
=======
  case 640:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 640:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3610 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 639:
#line 2209 "dhcp4_parser.yy"
=======
  case 641:
#line 2216 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 641:
#line 2216 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    // parsing completed
}
#line 3618 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 643:
#line 2225 "dhcp4_parser.yy"
=======
  case 645:
#line 2232 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 645:
#line 2232 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3629 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 644:
#line 2230 "dhcp4_parser.yy"
=======
  case 646:
#line 2237 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 646:
#line 2237 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3638 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 647:
#line 2242 "dhcp4_parser.yy"
=======
  case 649:
#line 2249 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 649:
#line 2249 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3648 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 648:
#line 2246 "dhcp4_parser.yy"
=======
  case 650:
#line 2253 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 650:
#line 2253 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
}
#line 3656 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 658:
#line 2263 "dhcp4_parser.yy"
=======
  case 660:
#line 2270 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 660:
#line 2270 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3665 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 659:
#line 2268 "dhcp4_parser.yy"
=======
  case 661:
#line 2275 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 661:
#line 2275 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3673 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 660:
#line 2270 "dhcp4_parser.yy"
=======
  case 662:
#line 2277 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 662:
#line 2277 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3683 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 661:
#line 2276 "dhcp4_parser.yy"
=======
  case 663:
#line 2283 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 663:
#line 2283 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3694 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 662:
#line 2281 "dhcp4_parser.yy"
=======
  case 664:
#line 2288 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 664:
#line 2288 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3703 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 665:
#line 2290 "dhcp4_parser.yy"
=======
  case 667:
#line 2297 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 667:
#line 2297 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3713 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 666:
#line 2294 "dhcp4_parser.yy"
=======
  case 668:
#line 2301 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 668:
#line 2301 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.stack_.pop_back();
}
#line 3721 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 674:
#line 2309 "dhcp4_parser.yy"
=======
  case 675:
#line 2315 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 675:
#line 2315 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3729 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 675:
#line 2311 "dhcp4_parser.yy"
=======
  case 676:
#line 2317 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 676:
#line 2317 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3739 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 676:
#line 2317 "dhcp4_parser.yy"
=======
  case 677:
#line 2323 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 677:
#line 2323 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3748 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 677:
#line 2322 "dhcp4_parser.yy"
=======
  case 678:
#line 2328 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 678:
#line 2328 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3757 "dhcp4_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 678:
#line 2327 "dhcp4_parser.yy"
=======
  case 679:
#line 2333 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
  case 679:
#line 2333 "dhcp4_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3766 "dhcp4_parser.cc" // lalr1.cc:907
<<<<<<< HEAD
    break;

  case 679:
#line 2332 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3768 "dhcp4_parser.cc"
    break;

  case 680:
#line 2334 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3778 "dhcp4_parser.cc"
    break;


<<<<<<< HEAD
#line 3782 "dhcp4_parser.cc"

=======
#line 3770 "dhcp4_parser.cc" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
    break;


#line 3770 "dhcp4_parser.cc" // lalr1.cc:907
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Dhcp4Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short Dhcp4Parser::yypact_ninf_ = -840;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
<<<<<<< HEAD
<<<<<<< HEAD
     317,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    32,    21,    71,    80,    98,
     114,   132,   136,   155,   183,   192,   209,   252,   260,   263,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,    21,    27,
      17,   123,    75,   227,    39,   234,   164,    28,   154,   -41,
     515,   134,   117,  -837,   274,   278,   287,   284,   290,  -837,
    -837,  -837,  -837,  -837,   302,  -837,    44,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   303,   316,   337,  -837,
    -837,  -837,  -837,  -837,  -837,   346,   347,   354,   356,   357,
     358,   359,   360,   361,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   362,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    57,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,   363,  -837,    78,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   365,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,    90,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,    93,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   313,   345,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   364,  -837,
    -837,   366,  -837,  -837,  -837,   369,  -837,  -837,   367,   373,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   374,   375,  -837,  -837,  -837,  -837,   372,
     378,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,    96,  -837,  -837,  -837,   380,  -837,  -837,
     384,  -837,   387,   388,  -837,  -837,   389,   390,  -837,  -837,
    -837,  -837,  -837,   106,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     108,  -837,  -837,  -837,   392,   112,  -837,  -837,  -837,  -837,
      21,    21,  -837,   225,   402,   403,   405,   407,   408,  -837,
      17,  -837,   409,   411,   415,   200,   243,   244,   419,   425,
     434,   437,   439,   440,   267,   270,   283,   286,   295,   282,
     296,   297,   299,   458,   467,   471,   487,   488,   489,   498,
     499,   501,   502,   503,   504,   507,   338,   508,   510,   511,
     512,   513,   514,   123,  -837,   516,   517,   520,   342,    75,
    -837,   522,   524,   525,   526,   527,   528,   368,   529,   531,
     532,   227,  -837,   535,    39,  -837,   536,   538,   542,   543,
     544,   545,   546,   547,  -837,   234,  -837,   549,   550,   381,
     551,   553,   554,   382,  -837,    28,   556,   385,   386,  -837,
     154,   560,   561,    46,  -837,   391,   562,   563,   394,   567,
     398,   399,   572,   573,   404,   406,   575,   576,   515,  -837,
     134,  -837,   580,   410,   117,  -837,  -837,  -837,   582,   581,
     583,    21,    21,    21,  -837,   584,   586,   587,  -837,  -837,
    -837,   413,   418,   422,   590,   591,   597,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   430,   600,   601,   602,
     603,   604,   435,   240,   605,   608,   609,   610,   611,  -837,
     613,   604,   615,   442,   443,   649,  -837,   650,   153,   221,
    -837,  -837,   482,   484,   485,   657,   490,   491,  -837,   650,
     492,   656,  -837,   493,  -837,   650,   494,   495,   496,   497,
     500,   505,   506,  -837,   509,   518,  -837,   519,   521,   523,
    -837,  -837,   530,  -837,  -837,  -837,   533,    21,  -837,  -837,
     534,   537,  -837,   539,  -837,  -837,    26,   449,  -837,  -837,
     -16,   540,  -837,  -837,   667,  -837,  -837,    21,   123,   134,
    -837,  -837,  -837,   117,    75,   651,  -837,  -837,  -837,   585,
     585,   666,  -837,   669,   670,   671,   674,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   198,   675,   677,   678,   158,
     -34,  -837,   515,  -837,  -837,   679,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   680,  -837,  -837,
    -837,  -837,   143,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   666,  -837,   133,   139,   169,   170,
    -837,   202,  -837,  -837,  -837,  -837,  -837,  -837,   684,   686,
     687,   690,   692,  -837,  -837,  -837,  -837,   694,   695,   696,
     697,   698,  -837,   203,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   206,  -837,   699,   700,  -837,  -837,
     703,   707,  -837,  -837,   706,   712,  -837,  -837,   710,   714,
    -837,  -837,   713,   715,  -837,  -837,  -837,  -837,  -837,  -837,
      42,  -837,  -837,  -837,  -837,  -837,  -837,  -837,    77,  -837,
    -837,   716,   717,  -837,  -837,   718,   720,  -837,   702,   721,
     722,   723,   724,   725,   212,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   216,  -837,  -837,
    -837,   229,  -837,   219,  -837,   557,  -837,   726,   727,  -837,
    -837,  -837,  -837,   728,   729,  -837,  -837,  -837,  -837,   730,
     651,  -837,   733,   734,   735,   736,   558,   564,   568,   565,
     569,   741,   742,   743,   744,   574,   577,   578,   579,   588,
     585,  -837,  -837,   585,  -837,   666,   227,  -837,   669,    28,
    -837,   670,   154,  -837,   671,   438,  -837,   674,   198,  -837,
      47,   675,  -837,   234,  -837,   677,   -41,  -837,   678,   589,
     592,   593,   594,   595,   596,   158,  -837,   746,   747,   -34,
    -837,  -837,   194,   679,  -837,  -837,   749,   753,    39,  -837,
     680,   754,  -837,  -837,   598,  -837,   319,   599,   606,   607,
    -837,  -837,  -837,  -837,  -837,   614,   617,   619,   620,  -837,
    -837,  -837,  -837,  -837,  -837,   232,  -837,   242,  -837,   752,
    -837,   755,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     257,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   757,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   758,   759,  -837,  -837,  -837,  -837,  -837,   766,
    -837,   300,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     625,   634,  -837,  -837,   771,  -837,  -837,  -837,  -837,  -837,
     314,  -837,  -837,  -837,  -837,  -837,  -837,   635,   341,  -837,
     650,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   438,  -837,
     772,   637,  -837,    47,  -837,  -837,  -837,  -837,   773,   612,
     774,   194,  -837,  -837,  -837,  -837,  -837,   642,  -837,  -837,
     777,  -837,   659,  -837,  -837,   750,  -837,  -837,   255,  -837,
      13,   750,  -837,  -837,   775,   779,   780,  -837,   344,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   781,   648,   661,   664,
     838,    13,  -837,   708,  -837,  -837,  -837,   709,  -837,  -837,
    -837
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
     494,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,    47,    21,    56,    76,   105,
     118,   135,   137,   149,   170,   172,   183,   193,   225,   257,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,    21,   -93,
      17,   155,    29,    60,    55,   413,   154,    18,   270,   -37,
     479,    97,   211,  -840,    94,   254,   267,   280,   272,  -840,
    -840,  -840,  -840,  -840,   322,  -840,    70,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,   327,   328,   334,  -840,
    -840,  -840,  -840,  -840,  -840,   335,   336,   338,   345,   346,
     347,   348,   350,   353,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,   354,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,    93,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,   360,  -840,   108,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,   361,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,   123,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,   150,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,   291,   363,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,   359,  -840,
    -840,   364,  -840,  -840,  -840,   365,  -840,  -840,   362,   369,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,   371,   372,  -840,  -840,  -840,  -840,   370,
     374,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,   159,  -840,  -840,  -840,   375,  -840,  -840,
     376,  -840,   377,   380,  -840,  -840,   384,   387,  -840,  -840,
    -840,  -840,  -840,   186,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
     230,  -840,  -840,  -840,   388,   236,  -840,  -840,  -840,  -840,
      21,    21,  -840,   199,   389,   390,   392,   395,   397,  -840,
      17,  -840,   402,   404,   405,   234,   235,   238,   409,   415,
     416,   417,   419,   425,   263,   283,   284,   286,   287,   268,
     288,   289,   292,   462,   464,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   477,   309,   478,   482,   483,
     487,   488,   489,   155,  -840,   490,   491,   492,   320,    29,
    -840,   496,   497,   498,   499,   500,   501,   331,   503,   504,
     506,    60,  -840,   507,    55,  -840,   508,   509,   510,   517,
     519,   520,   521,   522,  -840,   413,  -840,   523,   524,   355,
     525,   530,   531,   366,  -840,    18,   532,   373,   378,  -840,
     270,   533,   535,   142,  -840,   379,   536,   538,   382,   543,
     385,   391,   544,   545,   386,   394,   547,   549,   479,  -840,
      97,  -840,   550,   393,   211,  -840,  -840,  -840,   558,   476,
     560,    21,    21,    21,  -840,   562,   566,   567,  -840,  -840,
    -840,   403,   406,   407,   569,   572,   578,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,   410,   580,   581,   583,
     584,   585,   420,   243,   586,   588,   591,   592,   593,  -840,
     595,   585,   597,   424,   431,   594,  -840,   614,   218,   307,
    -840,  -840,   446,   448,   450,   622,   454,   455,  -840,   614,
     457,   625,  -840,   459,  -840,   614,   502,   505,   511,   512,
     513,   514,   515,  -840,   516,   518,  -840,   526,   527,   528,
    -840,  -840,   529,  -840,  -840,  -840,   534,    21,  -840,  -840,
     537,   539,  -840,   540,  -840,  -840,    14,   449,  -840,  -840,
      28,   541,  -840,  -840,   663,  -840,  -840,    21,   155,    97,
    -840,  -840,  -840,   211,    29,   646,  -840,  -840,  -840,   596,
     596,   664,  -840,   665,   666,   667,   668,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,    31,   670,   671,   673,    91,
     -15,  -840,   479,  -840,  -840,   674,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,   675,  -840,  -840,
    -840,  -840,   176,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,   664,  -840,   239,   240,   250,   262,
    -840,   264,  -840,  -840,  -840,  -840,  -840,  -840,   679,   680,
     687,   689,   690,  -840,  -840,  -840,  -840,   691,   692,   693,
     694,   695,   700,  -840,   265,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,   271,  -840,   699,   703,
    -840,  -840,   701,   706,  -840,  -840,   704,   709,  -840,  -840,
     710,   714,  -840,  -840,   712,   716,  -840,  -840,  -840,  -840,
    -840,  -840,    59,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
      74,  -840,  -840,   715,   717,  -840,  -840,   718,   719,  -840,
     721,   722,   723,   724,   725,   726,   275,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,   279,
    -840,  -840,  -840,   281,  -840,   107,  -840,   557,  -840,   727,
     720,  -840,  -840,  -840,  -840,   728,   729,  -840,  -840,  -840,
    -840,   730,   646,  -840,   733,   734,   735,   736,   568,   555,
     570,   564,   571,   738,   740,   743,   744,   574,   575,   576,
     577,   579,   582,   596,  -840,  -840,   596,  -840,   664,    60,
    -840,   665,    18,  -840,   666,   270,  -840,   667,   233,  -840,
     668,    31,  -840,   460,   670,  -840,   413,  -840,   671,   -37,
    -840,   673,   587,   589,   590,   598,   599,   600,    91,  -840,
     749,   750,   -15,  -840,  -840,    78,   674,  -840,  -840,   752,
     756,    55,  -840,   675,   751,  -840,  -840,   602,  -840,   325,
     603,   604,   605,  -840,  -840,  -840,  -840,  -840,   606,   607,
     608,   609,  -840,  -840,  -840,  -840,  -840,  -840,  -840,   295,
    -840,   304,  -840,   753,  -840,   755,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,   305,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,   762,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,   759,   757,  -840,  -840,
    -840,  -840,  -840,   760,  -840,   306,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,   610,   611,  -840,  -840,   765,  -840,
    -840,  -840,  -840,  -840,   308,  -840,  -840,  -840,  -840,  -840,
    -840,   612,   312,  -840,   614,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,   233,  -840,   767,   613,  -840,   460,  -840,  -840,
    -840,  -840,   768,   616,   783,    78,  -840,  -840,  -840,  -840,
    -840,   620,  -840,  -840,   791,  -840,   623,  -840,  -840,   781,
    -840,  -840,   196,  -840,   -49,   781,  -840,  -840,   798,   807,
     808,   314,  -840,  -840,  -840,  -840,  -840,  -840,   813,   642,
     653,   661,   -49,  -840,   681,  -840,  -840,  -840,  -840,  -840
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   141,     9,   286,    11,
     451,    13,   476,    15,   376,    17,   384,    19,   421,    21,
     251,    23,   568,    25,   640,    27,   629,    29,    47,    41,
       0,     0,     0,     0,     0,   478,     0,   386,   423,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     638,   621,   623,   625,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   627,   130,   156,     0,     0,     0,   497,
     499,   501,   154,   163,   165,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   278,   374,   413,   340,   464,
     466,   333,   229,   525,   468,   243,   262,     0,   551,   564,
     566,   617,   619,   645,   115,     0,    72,    74,    75,    76,
      77,    78,   109,   110,   111,    79,   107,    96,    97,    98,
      82,    83,   104,    84,    85,    86,    90,    91,    80,   108,
      81,    88,    89,   102,   103,   105,    99,   100,   101,    87,
      92,    93,    94,    95,   113,   114,   106,   112,   143,   145,
     149,     0,   140,     0,   132,   134,   135,   136,   137,   138,
     139,   321,   323,   325,   443,   319,   327,     0,   331,   329,
     521,   318,   290,   291,   292,   293,   294,   315,   316,   317,
     305,   306,     0,   288,   297,   310,   311,   312,   298,   300,
     301,   303,   299,   295,   296,   313,   314,   302,   307,   308,
     309,   304,   462,   461,   457,   458,   456,     0,   453,   455,
     459,   460,   519,   507,   509,   513,   511,   517,   515,   503,
     496,   490,   494,   495,     0,   479,   480,   491,   492,   493,
     487,   482,   488,   484,   485,   486,   489,   483,     0,   403,
     209,     0,   407,   405,   410,     0,   399,   400,     0,   387,
     388,   390,   402,   391,   392,   393,   409,   394,   395,   396,
     397,   398,   437,     0,     0,   435,   436,   439,   440,     0,
     424,   425,   427,   428,   429,   430,   431,   432,   433,   434,
     258,   260,   255,     0,   253,   256,   257,     0,   591,   593,
       0,   596,     0,     0,   600,   604,     0,     0,   608,   615,
     589,   587,   588,     0,   570,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
       0,   642,   644,   635,     0,     0,   631,   633,   634,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,     0,     0,   452,     0,     0,     0,     0,
       0,     0,     0,     0,   477,     0,   377,     0,     0,     0,
       0,     0,     0,     0,   385,     0,     0,     0,     0,   422,
       0,     0,     0,     0,   252,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   569,
       0,   641,     0,     0,     0,   630,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   550,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     0,
     153,   133,     0,     0,     0,     0,     0,     0,   339,     0,
       0,     0,   289,     0,   454,     0,     0,     0,     0,     0,
       0,     0,     0,   481,     0,     0,   401,     0,     0,     0,
     412,   389,     0,   441,   442,   426,     0,     0,   254,   590,
       0,     0,   595,     0,   598,   599,     0,     0,   606,   607,
       0,     0,   571,   643,     0,   637,   632,     0,     0,     0,
     622,   624,   626,     0,     0,     0,   498,   500,   502,     0,
       0,   167,   126,   280,   378,   415,   342,    40,   465,   467,
     335,   336,   337,   338,   334,     0,     0,   470,   245,     0,
       0,   565,     0,   618,   620,     0,    51,   144,   147,   148,
     146,   151,   152,   150,   322,   324,   326,   445,   320,   328,
     332,   330,     0,   463,   520,   508,   510,   514,   512,   518,
     516,   504,   404,   210,   408,   406,   411,   438,   259,   261,
     592,   594,   597,   602,   603,   601,   605,   610,   611,   612,
     613,   614,   609,   616,   167,    44,     0,     0,     0,     0,
     161,     0,   158,   160,   196,   202,   204,   206,     0,     0,
       0,     0,     0,   218,   220,   222,   224,     0,     0,     0,
       0,     0,     0,   195,     0,   173,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   188,   189,   190,   185,
     191,   192,   193,   186,   187,   194,     0,   171,     0,   168,
     169,   284,     0,   281,   282,   382,     0,   379,   380,   419,
       0,   416,   417,   346,     0,   343,   344,   238,   239,   240,
     241,   242,     0,   231,   233,   234,   235,   236,   237,   529,
       0,   527,   474,     0,   471,   472,   249,     0,   246,   247,
       0,     0,     0,     0,     0,     0,     0,   264,   266,   267,
     268,   269,   270,   271,   560,   562,   559,   557,   558,     0,
     553,   555,   556,     0,   649,     0,   647,    53,   449,     0,
     446,   447,   505,   523,   524,     0,     0,    69,   639,   628,
     131,     0,     0,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
<<<<<<< HEAD
<<<<<<< HEAD
       0,   155,   164,     0,   166,     0,     0,   277,     0,   384,
     373,     0,   421,   412,     0,     0,   339,     0,     0,   228,
     529,     0,   524,   476,   467,     0,     0,   242,     0,     0,
       0,     0,     0,     0,     0,     0,   261,     0,     0,     0,
     550,   565,     0,     0,   644,    55,     0,    54,     0,   442,
       0,     0,   520,   634,     0,   159,     0,     0,     0,     0,
     207,   210,   211,   212,   213,     0,     0,     0,     0,   225,
     226,   214,   215,   216,   174,     0,   170,     0,   281,     0,
     379,     0,   416,   371,   363,   364,   365,   351,   352,   368,
     369,   370,   354,   355,   348,   349,   350,   361,   362,   360,
       0,   346,   353,   366,   367,   356,   357,   358,   359,   343,
     230,   545,     0,   543,   544,   536,   537,   541,   542,   538,
     539,   540,     0,   530,   531,   533,   534,   535,   526,     0,
     471,     0,   246,   270,   271,   272,   273,   274,   275,   263,
       0,     0,   552,   661,     0,   659,   657,   651,   655,   656,
       0,   649,   653,   654,   652,   646,    52,     0,     0,   446,
       0,   162,   197,   198,   199,   200,   196,   202,   204,   206,
     218,   220,   222,   224,   172,   283,   381,   418,     0,   345,
       0,     0,   528,     0,   473,   248,   559,   561,     0,     0,
       0,     0,   648,    56,   448,   504,   347,     0,   547,   532,
       0,   658,     0,   650,   546,     0,   660,   665,     0,   663,
       0,     0,   662,   674,     0,     0,     0,   679,     0,   667,
     669,   670,   671,   672,   673,   664,     0,     0,     0,     0,
       0,     0,   666,     0,   676,   677,   678,     0,   668,   675,
     680
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
       0,     0,     0,     0,   155,   164,     0,   166,     0,     0,
     279,     0,   386,   375,     0,   423,   414,     0,     0,   341,
       0,     0,   230,   531,     0,   526,   478,   469,     0,     0,
     244,     0,     0,     0,     0,     0,     0,     0,     0,   263,
       0,     0,     0,   552,   567,     0,     0,   646,    55,     0,
      54,     0,   444,     0,     0,   522,   636,     0,   159,     0,
       0,     0,     0,   208,   211,   212,   213,   214,     0,     0,
       0,     0,   226,   227,   215,   216,   217,   228,   174,     0,
     170,     0,   283,     0,   381,     0,   418,   373,   365,   366,
     367,   353,   354,   370,   371,   372,   356,   357,   350,   351,
     352,   363,   364,   362,     0,   348,   355,   368,   369,   358,
     359,   360,   361,   345,   232,   547,     0,   545,   546,   538,
     539,   543,   544,   540,   541,   542,     0,   532,   533,   535,
     536,   537,   528,     0,   473,     0,   248,   272,   273,   274,
     275,   276,   277,   265,     0,     0,   554,   663,     0,   661,
     659,   653,   657,   658,     0,   651,   655,   656,   654,   648,
      52,     0,     0,   448,     0,   162,   198,   199,   200,   201,
     197,   203,   205,   207,   219,   221,   223,   225,   172,   285,
     383,   420,     0,   347,     0,     0,   530,     0,   475,   250,
     561,   563,     0,     0,     0,     0,   650,    56,   450,   506,
     349,     0,   549,   534,     0,   660,     0,   652,   548,     0,
     662,   667,     0,   665,     0,     0,   664,   675,     0,     0,
       0,     0,   669,   671,   672,   673,   674,   666,     0,     0,
       0,     0,     0,   668,     0,   677,   678,   679,   670,   676
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
<<<<<<< HEAD
<<<<<<< HEAD
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -46,  -837,  -468,  -837,
     180,  -837,  -837,  -837,  -837,  -837,  -837,  -534,  -837,  -837,
    -837,   -70,  -837,  -837,  -837,   464,  -837,  -837,  -837,  -837,
     237,   429,   -55,   -54,   -27,   -24,    -9,     6,     9,    11,
    -837,  -837,  -837,  -837,    12,    19,  -837,  -837,   247,   451,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,    55,  -837,  -837,  -837,
    -837,  -837,  -837,   195,  -837,    31,  -837,  -607,    38,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   -35,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    24,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    16,  -837,  -837,  -837,    14,   423,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,    10,  -837,  -837,  -837,  -837,  -837,
    -837,  -836,  -837,  -837,  -837,    40,  -837,  -837,  -837,    41,
     459,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -828,
    -837,   -17,  -837,    -5,  -837,    22,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,    34,  -837,  -837,  -129,   -65,  -837,  -837,
    -837,  -837,  -837,    43,  -837,  -837,  -837,    48,  -837,   441,
    -837,   -72,  -837,  -837,  -837,  -837,  -837,   -66,  -837,  -837,
    -837,  -837,  -837,    -7,  -837,  -837,  -837,    45,  -837,  -837,
    -837,    49,  -837,   432,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,     3,  -837,  -837,  -837,     7,
     466,  -837,  -837,   -39,  -837,   -19,  -837,   -59,  -837,  -837,
    -837,    33,  -837,  -837,  -837,    50,  -837,   457,   -58,  -837,
     -52,  -837,    -1,  -837,   251,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -825,  -837,  -837,  -837,  -837,  -837,    51,  -837,
    -837,  -837,  -119,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    29,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   273,   428,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -64,  -837,   -60,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     304,   426,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   310,
     431,   -57,  -837,  -837,    35,  -837,  -837,  -117,  -837,  -837,
    -837,  -837,  -837,  -837,  -136,  -837,  -837,  -155,  -837,  -837,
    -837,  -837,  -837,  -837,  -837
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,   -46,  -840,  -481,  -840,
     298,  -840,  -840,  -840,  -840,  -840,  -840,  -534,  -840,  -840,
    -840,   -70,  -840,  -840,  -840,   465,  -840,  -840,  -840,  -840,
     256,   463,   -55,   -54,   -27,   -24,    -9,     6,     9,    11,
    -840,  -840,  -840,  -840,    12,    19,  -840,  -840,   228,   418,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,    16,  -840,  -840,  -840,
    -840,  -840,  -840,   189,  -840,    27,  -840,  -607,    35,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,   -35,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,    20,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,     8,  -840,  -840,  -840,    13,   422,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,     5,  -840,  -840,  -840,  -840,
    -840,  -840,  -839,  -840,  -840,  -840,    36,  -840,  -840,  -840,
      39,   458,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -831,  -840,   -17,  -840,    -5,  -840,    22,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,    30,  -840,  -840,  -131,   -65,  -840,
    -840,  -840,  -840,  -840,    38,  -840,  -840,  -840,    41,  -840,
     439,  -840,   -72,  -840,  -840,  -840,  -840,  -840,   -66,  -840,
    -840,  -840,  -840,  -840,    -7,  -840,  -840,  -840,    40,  -840,
    -840,  -840,    43,  -840,   435,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,     3,  -840,  -840,  -840,
      10,   480,  -840,  -840,   -39,  -840,   -19,  -840,   -59,  -840,
    -840,  -840,    32,  -840,  -840,  -840,    33,  -840,   461,   -58,
    -840,   -52,  -840,    -1,  -840,   251,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -828,  -840,  -840,  -840,  -840,  -840,    44,
    -840,  -840,  -840,  -125,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,    23,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,   277,   426,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,   -64,  -840,   -60,
    -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
    -840,   310,   423,  -840,  -840,  -840,  -840,  -840,  -840,  -840,
     311,   432,   -57,  -840,  -840,    25,  -840,  -840,  -120,  -840,
    -840,  -840,  -840,  -840,  -840,  -139,  -840,  -840,  -155,  -840,
    -840,  -840,  -840,  -840
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     628,    87,    88,    41,    68,    84,    85,   647,   817,   899,
     900,   723,    43,    70,    96,    97,    98,   374,    45,    71,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   403,   157,   158,   159,   160,   383,   193,   194,
      47,    72,   195,   425,   196,   426,   650,   197,   427,   653,
<<<<<<< HEAD
<<<<<<< HEAD
     198,   161,   391,   162,   384,   701,   702,   703,   829,   163,
     392,   164,   393,   746,   747,   748,   853,   723,   724,   725,
     832,  1016,   726,   833,   727,   834,   728,   835,   729,   730,
     458,   731,   732,   733,   734,   735,   736,   737,   738,   841,
     739,   842,   740,   843,   741,   844,   742,   743,   165,   411,
     770,   771,   772,   773,   774,   775,   776,   166,   414,   785,
     786,   787,   876,    61,    79,   323,   324,   325,   471,   326,
     472,   167,   415,   794,   795,   796,   797,   798,   799,   800,
     801,   168,   404,   750,   751,   752,   856,    49,    73,   222,
     223,   224,   435,   225,   431,   226,   432,   227,   433,   228,
     436,   229,   439,   230,   438,   169,   410,   634,   232,   170,
     407,   762,   763,   764,   865,   950,   951,   171,   405,    55,
      76,   754,   755,   756,   859,    57,    77,   288,   289,   290,
     291,   292,   293,   294,   457,   295,   461,   296,   460,   297,
     298,   462,   299,   172,   406,   758,   759,   760,   862,    59,
      78,   309,   310,   311,   312,   313,   466,   314,   315,   316,
     317,   234,   434,   817,   818,   819,   898,    51,    74,   247,
     248,   249,   443,   173,   408,   174,   409,   175,   413,   781,
     782,   783,   873,    53,    75,   264,   265,   266,   176,   388,
     177,   389,   178,   390,   270,   453,   822,   901,   271,   447,
     272,   448,   273,   450,   274,   449,   275,   452,   276,   451,
     277,   446,   241,   440,   823,   179,   412,   778,   779,   870,
     972,   973,   974,   975,   976,  1030,   977,   180,   181,   417,
     807,   808,   809,   887,   810,   888,   182,   418,   183,   419,
      63,    80,   343,   344,   345,   346,   476,   347,   477,   348,
     349,   479,   350,   351,   352,   482,   685,   353,   483,   354,
     355,   356,   486,   692,   357,   487,   184,   420,   185,   421,
      99,   376,   100,   377,   101,   378,   186,   382,    67,    82,
     365,   366,   367,   492,   368,   102,   375,    65,    81,   360,
     361,   187,   422,   813,   814,   892,  1000,  1001,  1002,  1003,
    1040,  1004,  1038,  1058,  1059,  1060,  1068,  1069,  1070,  1076,
    1071,  1072,  1073,  1074,  1080
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
     198,   161,   391,   162,   384,   701,   702,   703,   831,   163,
     392,   164,   393,   748,   749,   750,   856,   724,   725,   726,
     834,  1020,   727,   835,   728,   836,   729,   837,   730,   731,
     458,   732,   733,   734,   735,   736,   737,   738,   739,   843,
     740,   844,   741,   845,   742,   846,   743,   744,   745,   165,
     411,   772,   773,   774,   775,   776,   777,   778,   166,   414,
     787,   788,   789,   879,    61,    79,   323,   324,   325,   471,
     326,   472,   167,   415,   796,   797,   798,   799,   800,   801,
     802,   803,   168,   404,   752,   753,   754,   859,    49,    73,
     222,   223,   224,   435,   225,   431,   226,   432,   227,   433,
     228,   436,   229,   439,   230,   438,   169,   410,   634,   232,
     170,   407,   764,   765,   766,   868,   954,   955,   171,   405,
      55,    76,   756,   757,   758,   862,    57,    77,   288,   289,
     290,   291,   292,   293,   294,   457,   295,   461,   296,   460,
     297,   298,   462,   299,   172,   406,   760,   761,   762,   865,
      59,    78,   309,   310,   311,   312,   313,   466,   314,   315,
     316,   317,   234,   434,   819,   820,   821,   901,    51,    74,
     247,   248,   249,   443,   173,   408,   174,   409,   175,   413,
     783,   784,   785,   876,    53,    75,   264,   265,   266,   176,
     388,   177,   389,   178,   390,   270,   453,   824,   904,   271,
     447,   272,   448,   273,   450,   274,   449,   275,   452,   276,
     451,   277,   446,   241,   440,   825,   179,   412,   780,   781,
     873,   976,   977,   978,   979,   980,  1034,   981,   180,   181,
     417,   809,   810,   811,   890,   812,   891,   182,   418,   183,
     419,    63,    80,   343,   344,   345,   346,   476,   347,   477,
     348,   349,   479,   350,   351,   352,   482,   685,   353,   483,
     354,   355,   356,   486,   692,   357,   487,   184,   420,   185,
     421,    99,   376,   100,   377,   101,   378,   186,   382,    67,
      82,   365,   366,   367,   492,   368,   102,   375,    65,    81,
     360,   361,   187,   422,   815,   816,   895,  1004,  1005,  1006,
    1007,  1044,  1008,  1042,  1062,  1063,  1064,  1071,  1072,  1073,
    1078,  1074,  1075,  1076
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   144,   192,   211,   243,   260,   307,   286,   305,   322,
<<<<<<< HEAD
<<<<<<< HEAD
     340,   278,   308,   744,   237,   238,   358,   267,   212,   213,
     359,   239,    83,   268,   362,   660,    31,    89,    32,   945,
      33,   664,    30,   199,   235,   250,   262,   946,   300,   318,
     958,   341,   287,   306,   683,   868,   214,   380,   869,   215,
     129,   130,   381,   200,   236,   251,   263,   244,   301,   319,
     423,   342,   279,   627,   216,   424,   233,   246,   261,   245,
     320,   321,   240,   627,   269,   109,   110,   111,    42,   217,
     871,   429,   218,   872,   219,   220,   430,    44,   802,   803,
     188,   189,   221,   441,   190,   231,   444,   191,   442,   473,
     280,   445,   281,   282,   474,    46,   283,   284,   285,   488,
     127,   490,   129,   130,   489,   494,   491,   126,   127,   280,
     495,    48,   242,   129,   130,   687,   688,   689,   690,   363,
     364,   129,   130,    94,   103,   208,   423,   104,   209,    50,
      94,   825,   490,    52,   961,   962,   105,   826,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   320,   321,   129,
     130,   691,    54,  1063,    90,   684,  1064,  1065,  1066,  1067,
     648,   649,   494,   429,    91,    92,    93,   827,   828,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      56,    94,   945,   126,   127,    34,    35,    36,    37,    58,
     946,    86,    94,   958,   128,   830,   850,   129,   130,   850,
     831,   851,   131,    94,   852,   885,    60,   132,   133,   889,
     886,    94,   893,   134,   890,   894,   280,   302,   281,   282,
     303,   304,   488,   135,   126,   850,   136,   891,   129,   130,
    1024,   651,   652,   137,   138,   441,   925,   139,   140,    94,
    1025,   259,   820,   107,   108,   109,   110,   111,  1061,    62,
    1028,  1062,   109,   110,   111,  1029,   280,    64,   141,   142,
      66,   143,   788,   789,   790,   791,   792,   793,   129,   130,
     369,   370,   143,   115,   116,   117,   118,   119,   120,   121,
     122,   371,   372,   373,   201,   202,   203,    94,   127,   765,
     766,   767,   768,   473,   769,   127,   379,   385,  1035,   204,
      95,   129,   130,   205,   206,   207,   131,  1041,   129,   130,
     386,   454,  1042,   208,   496,   497,   209,   134,    94,   252,
     630,   631,   632,   633,   210,   253,   254,   255,   256,   257,
     258,   387,   259,   993,   444,   994,   995,  1081,   455,  1044,
     394,   395,  1082,   144,  1012,  1013,  1014,  1015,   396,   192,
     397,   398,   399,   400,   401,   402,   416,   428,    94,   437,
     459,   211,   456,   463,   243,   464,   465,   508,   467,   468,
     469,   470,   237,   238,   475,   260,   212,   213,   478,   239,
     199,   480,   481,   484,   485,   286,   493,   267,   307,   498,
     305,    94,   235,   268,   308,   250,   499,   500,    94,   501,
     200,   502,   503,   505,   214,   506,   262,   215,   340,   507,
     509,   510,   236,   511,   358,   251,   300,   244,   359,   512,
     287,   318,   216,   362,   233,   306,   263,   246,   513,   245,
     240,   514,   517,   515,   516,   518,   301,   217,   261,   341,
     218,   319,   219,   220,   269,   610,   611,   612,   519,   522,
     221,   520,   526,   231,   107,   108,   109,   110,   111,   342,
     521,   527,   523,   524,   525,   528,  1045,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   529,   530,   531,   115,   116,   117,   118,   119,   120,
     121,   122,   532,   533,   125,   534,   535,   536,   537,   127,
     280,   538,   540,   539,   541,   542,   543,   544,   545,   550,
     547,   548,   129,   130,   549,   206,   552,   131,   553,   554,
     555,   556,   557,   559,   208,   560,   561,   209,   144,   563,
     565,   679,   566,   558,   192,   210,   567,   568,   569,   570,
     571,   572,   362,   574,   575,   577,   576,   578,   579,   580,
     582,   695,   583,   584,   586,   587,   590,   591,   589,   592,
     804,   593,   340,   594,   595,   199,   596,   597,   358,   600,
     601,   598,   359,   599,   604,   605,   607,   616,   608,   686,
     609,   613,   617,   614,   615,   200,   618,   619,   620,   129,
     130,   805,   621,   341,   622,   623,   624,   625,   626,   629,
     635,    32,    94,   636,   637,   638,   643,   644,   639,   704,
     640,   806,   642,   342,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   714,   715,   716,   717,   718,   719,   720,
     721,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   645,   646,   654,   280,   655,   656,
     141,   142,   657,   662,   658,   659,   661,   663,   665,   666,
     667,   668,   694,   745,   669,   700,   749,   753,   757,   670,
     671,   761,   777,   672,   780,   784,   812,   816,   836,    94,
     837,   838,   673,   674,   839,   675,   840,   676,   845,   846,
     847,   848,   849,   855,   677,   854,   879,   678,   680,   857,
     858,   681,   860,   682,   693,   861,   863,   864,   867,   866,
     875,   641,   874,   878,   877,   880,   881,   882,   883,   884,
     900,   895,   899,   910,   904,   903,   902,   906,   907,   908,
     909,   911,   913,   912,   914,   915,   916,   917,   918,   919,
     990,   991,   920,   921,   922,  1006,  1007,  1057,  1010,    94,
    1026,  1031,  1033,  1027,   983,   923,  1032,   984,   985,   986,
     987,   988,  1011,  1017,  1034,  1039,  1047,  1050,  1052,  1077,
    1018,  1019,  1055,  1078,  1079,  1083,   211,  1051,  1020,   286,
     307,  1021,   305,  1022,  1023,   933,   308,   237,   238,  1036,
     963,   212,   213,   260,   239,   965,   322,   955,  1037,  1043,
     934,   935,   969,   956,  1048,   267,  1054,   235,   970,   804,
     300,   268,   996,   318,   287,  1084,   953,   306,   243,   214,
     944,   967,   215,  1056,   262,   964,  1085,   236,   936,  1086,
     301,   937,  1087,   319,   504,   696,   954,   216,   947,   233,
     805,   968,   546,   998,   263,   240,   938,   997,   952,   250,
     948,   699,   217,   966,   957,   218,   261,   219,   220,   971,
     806,   939,   269,   999,   940,   221,   941,   942,   231,   251,
     551,   244,  1089,  1090,   943,   905,   926,   949,   924,   824,
     981,   246,   960,   245,   982,   989,   588,   927,   928,  1046,
     562,   959,   585,  1009,   930,  1008,   581,   929,   980,   932,
     564,   931,   573,   821,  1049,   811,   602,   698,   992,   697,
     606,   603,   978,   979,  1053,  1075,  1088,     0,  1005,     0,
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
     340,   278,   308,   746,   237,   238,   358,   267,   212,   213,
     359,   239,    83,   268,   362,   660,    31,    89,    32,   949,
      33,   664,   683,   199,   235,   250,   262,   950,   300,   318,
     962,   341,   287,   306,   188,   189,   214,    30,   190,   215,
     627,   191,   279,   200,   236,   251,   263,   244,   301,   319,
     627,   342,   871,    42,   216,   872,   233,   246,   261,   245,
     129,   130,   240,   380,   269,   320,   321,   874,   381,   217,
     875,    86,   218,    44,   219,   220,   107,   108,   109,   110,
     111,   280,   221,   281,   282,   231,   423,   283,   284,   285,
     369,   424,  1067,   129,   130,  1068,  1069,  1070,   804,   805,
     896,   429,    46,   897,   129,   130,   430,   115,   116,   117,
     118,   119,   120,   121,   122,    48,   441,   127,   201,   202,
     203,   442,   127,   767,   768,   769,   770,    94,   771,   242,
     129,   130,    50,   204,    52,   129,   130,   205,   206,   207,
     131,   280,   208,   444,   684,   209,    54,   208,   445,    94,
     209,   134,   473,   129,   130,    90,   103,   474,   210,   104,
     687,   688,   689,   690,    91,    92,    93,    56,   105,    58,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   488,
      60,    94,    94,   949,   489,    34,    35,    36,    37,  1065,
      62,   950,  1066,    94,   962,   691,   790,   791,   792,   793,
     794,   795,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   363,   364,   126,   126,   127,   997,    94,
     998,   999,    64,   490,    94,   648,   649,   128,   491,   494,
     129,   130,   423,   490,   495,   131,   143,   827,   828,   929,
     132,   133,    94,   494,   320,   321,   134,   370,   829,   107,
     108,   109,   110,   111,    66,   429,   135,   832,   853,   136,
     830,   371,   833,   854,   853,   373,   137,   138,   888,   855,
     139,   140,   892,   889,   488,   259,   822,   893,   372,   894,
     115,   116,   117,   118,   119,   120,   121,   122,   853,   454,
     125,   141,   142,  1028,   143,   127,   280,   441,  1032,   473,
      95,  1045,  1029,  1033,  1039,   444,  1046,  1082,   129,   130,
    1048,   206,  1083,   131,   496,   497,   379,   651,   652,    94,
     208,   385,   386,   209,   630,   631,   632,   633,   387,   394,
     395,   210,   396,   280,   302,   281,   282,   303,   304,   397,
     398,   399,   400,   144,   401,   129,   130,   402,   416,   192,
    1016,  1017,  1018,  1019,   428,   437,   455,   456,   459,   463,
     464,   211,   465,   498,   243,   467,   468,   470,   469,   475,
     478,   480,   237,   238,   481,   260,   212,   213,   484,   239,
     199,   485,   493,   499,   500,   286,   501,   267,   307,   502,
     305,   503,   235,   268,   308,   250,   505,    94,   506,   507,
     200,   508,   509,   511,   214,   510,   262,   215,   340,   512,
     513,   514,   236,   515,   358,   251,   300,   244,   359,   516,
     287,   318,   216,   362,   233,   306,   263,   246,   517,   245,
     240,   109,   110,   111,    94,   522,   301,   217,   261,   341,
     218,   319,   219,   220,   269,   610,   611,   612,   518,   519,
     221,   520,   521,   231,   523,   524,   526,   525,   527,   342,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
    1049,   538,   540,   608,   539,   127,   541,   542,   109,   110,
     111,   543,   544,   545,   547,   548,   549,   550,   129,   130,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   252,
     561,   563,   565,   566,   567,   253,   254,   255,   256,   257,
     258,   568,   259,   569,   570,   571,   572,   574,   575,   577,
     576,   126,   127,   280,   578,   579,   582,   586,   144,   587,
     590,   679,   591,   580,   192,   129,   130,   593,   596,   597,
     583,   600,   362,   601,   604,   584,   589,   592,   965,   966,
     594,   695,   607,   598,   129,   130,   595,   609,   605,   613,
     806,   599,   340,   614,   615,   199,   619,   616,   358,   620,
     617,   618,   359,   621,   622,   623,   624,    94,   625,   626,
     686,   635,    32,   636,   629,   200,   637,   638,   643,   645,
     639,   807,   640,   341,   642,   644,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   646,
     654,   808,   655,   342,   656,   141,   142,   657,   658,   659,
     704,   661,   662,   663,    94,   705,   706,   707,   708,   709,
     710,   711,   712,   713,   714,   715,   716,   717,   718,   719,
     720,   721,   722,    94,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   694,   280,
     700,   747,   751,   755,   759,   763,   665,   779,   782,   666,
     786,   814,   818,   838,   839,   667,   668,   669,   670,   671,
     672,   840,   673,   841,   842,   847,   848,   849,   850,   851,
     674,   675,   676,   677,   852,   857,   858,   860,   678,   861,
     863,   680,   864,   681,   682,   693,   866,   867,   869,   870,
     878,   877,   881,   903,   880,   882,   883,   884,   885,   886,
     887,   898,   914,   902,   907,   906,   905,   909,   910,   911,
     912,   916,   918,   913,   919,   915,   917,   920,   921,   922,
     923,   924,   925,   994,   995,  1014,   926,   927,  1010,  1011,
    1037,  1030,   987,  1031,   988,   989,  1035,  1036,  1038,  1043,
      94,  1051,  1054,   990,   991,   992,  1015,  1021,  1022,  1023,
    1024,  1025,  1026,  1027,  1040,  1041,  1047,  1056,  1061,   211,
    1052,  1055,   286,   307,  1058,   305,  1059,  1060,   937,   308,
     237,   238,  1079,   967,   212,   213,   260,   239,   969,   322,
     959,  1080,  1081,   938,   939,   973,   960,  1084,   267,  1085,
     235,   974,   806,   300,   268,  1000,   318,   287,  1086,   957,
     306,   243,   214,   948,   971,   215,  1087,   262,   968,   641,
     236,   940,   699,   301,   941,   504,   319,   551,   908,   958,
     216,   951,   233,   807,   972,  1089,  1002,   263,   240,   942,
    1001,   956,   250,   952,   696,   217,   970,   961,   218,   261,
     219,   220,   975,   808,   943,   269,  1003,   944,   221,   945,
     946,   231,   251,   826,   244,   930,   546,   947,   928,   986,
     953,   964,   985,   993,   246,   588,   245,   932,   931,   562,
     963,  1050,   934,   933,   581,   585,  1013,   936,   935,   983,
     984,  1012,  1053,   823,   602,   996,   573,   606,   982,   813,
     697,  1009,   603,   698,   564,  1057,  1077,  1088,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   937,     0,     0,     0,     0,   967,     0,     0,
       0,     0,   969,     0,   959,  1000,     0,   938,   939,   973,
     960,     0,     0,     0,     0,   974,     0,     0,     0,     0,
       0,     0,     0,   957,     0,     0,     0,   948,   971,     0,
       0,     0,   968,     0,     0,   940,  1002,     0,   941,     0,
    1001,     0,     0,   958,     0,   951,     0,     0,   972,     0,
       0,     0,     0,   942,     0,   956,  1003,   952,     0,     0,
     970,   961,     0,     0,     0,     0,   975,     0,   943,     0,
       0,   944,     0,   945,   946,     0,     0,     0,     0,     0,
       0,   947,     0,     0,   953
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,   620,    73,    73,    80,    75,    73,    73,
<<<<<<< HEAD
<<<<<<< HEAD
      80,    73,    68,    75,    81,   559,     5,    10,     7,   865,
       9,   565,     0,    72,    73,    74,    75,   865,    77,    78,
     865,    80,    77,    78,    18,     3,    73,     3,     6,    73,
      84,    85,     8,    72,    73,    74,    75,    74,    77,    78,
       3,    80,    34,   531,    73,     8,    73,    74,    75,    74,
     111,   112,    73,   541,    75,    28,    29,    30,     7,    73,
       3,     3,    73,     6,    73,    73,     8,     7,   122,   123,
      15,    16,    73,     3,    19,    73,     3,    22,     8,     3,
      72,     8,    74,    75,     8,     7,    78,    79,    80,     3,
      71,     3,    84,    85,     8,     3,     8,    70,    71,    72,
       8,     7,    83,    84,    85,   141,   142,   143,   144,    12,
      13,    84,    85,   174,    11,    96,     3,    14,    99,     7,
     174,     8,     3,     7,    97,    98,    23,     8,    25,    26,
      27,    28,    29,    30,    31,    32,    33,   111,   112,    84,
      85,   177,     7,   150,   147,   139,   153,   154,   155,   156,
      17,    18,     3,     3,   157,   158,   159,     8,     8,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
       7,   174,  1028,    70,    71,   174,   175,   176,   177,     7,
    1028,   174,   174,  1028,    81,     3,     3,    84,    85,     3,
       8,     8,    89,   174,     8,     3,     7,    94,    95,     3,
       8,   174,     3,   100,     8,     6,    72,    73,    74,    75,
      76,    77,     3,   110,    70,     3,   113,     8,    84,    85,
       8,    20,    21,   120,   121,     3,   853,   124,   125,   174,
       8,   108,   109,    26,    27,    28,    29,    30,     3,     7,
       3,     6,    28,    29,    30,     8,    72,     7,   145,   146,
       7,   148,   114,   115,   116,   117,   118,   119,    84,    85,
       6,     3,   148,    56,    57,    58,    59,    60,    61,    62,
      63,     4,     8,     3,    67,    68,    69,   174,    71,   101,
     102,   103,   104,     3,   106,    71,     4,     4,     8,    82,
     380,    84,    85,    86,    87,    88,    89,     3,    84,    85,
       4,     8,     8,    96,   370,   371,    99,   100,   174,    95,
      90,    91,    92,    93,   107,   101,   102,   103,   104,   105,
     106,     4,   108,   149,     3,   151,   152,     3,     3,     8,
       4,     4,     8,   423,    35,    36,    37,    38,     4,   429,
       4,     4,     4,     4,     4,     4,     4,     4,   174,     4,
       4,   441,     8,     4,   444,     8,     3,   177,     4,     4,
       8,     3,   441,   441,     4,   455,   441,   441,     4,   441,
     429,     4,     4,     4,     4,   465,     4,   455,   470,   174,
     470,   174,   441,   455,   470,   444,     4,     4,   174,     4,
     429,     4,     4,     4,   441,     4,   455,   441,   488,     4,
     177,   177,   441,     4,   488,   444,   465,   444,   488,     4,
     465,   470,   441,   490,   441,   470,   455,   444,     4,   444,
     441,     4,   175,     4,     4,   175,   465,   441,   455,   488,
     441,   470,   441,   441,   455,   501,   502,   503,   175,   177,
     441,   175,     4,   441,    26,    27,    28,    29,    30,   488,
     175,     4,   176,   176,   175,     4,  1010,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     4,     4,     4,    56,    57,    58,    59,    60,    61,
      62,    63,     4,     4,    66,     4,     4,     4,     4,    71,
      72,     4,     4,   175,     4,     4,     4,     4,     4,   177,
       4,     4,    84,    85,     4,    87,     4,    89,     4,     4,
       4,     4,     4,     4,    96,     4,     4,    99,   608,     4,
       4,   587,     4,   175,   614,   107,     4,     4,     4,     4,
       4,     4,   609,     4,     4,     4,   175,     4,     4,   177,
       4,   607,   177,   177,     4,     4,     4,     4,   177,   175,
     640,     4,   642,   175,   175,   614,     4,     4,   642,     4,
       4,   177,   642,   177,     4,   175,     4,   174,     7,   140,
       7,     7,   174,     7,     7,   614,   174,     7,     7,    84,
      85,   640,     5,   642,   174,     5,     5,     5,     5,   174,
       5,     7,   174,     5,     5,     5,   174,   174,     7,    34,
       7,   640,     7,   642,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,     5,     5,   174,    72,   174,   174,
     145,   146,     5,     7,   174,   174,   174,   174,   174,   174,
     174,   174,     5,     7,   174,    24,     7,     7,     7,   174,
     174,     7,     7,   174,     7,     7,     7,     7,     4,   174,
       4,     4,   174,   174,     4,   174,     4,   174,     4,     4,
       4,     4,     4,     3,   174,     6,     4,   174,   174,     6,
       3,   174,     6,   174,   174,     3,     6,     3,     3,     6,
       3,   541,     6,     3,     6,     4,     4,     4,     4,     4,
       3,   174,     6,   175,     4,     6,     8,     4,     4,     4,
       4,   177,   177,   175,   175,     4,     4,     4,     4,   175,
       4,     4,   175,   175,   175,     6,     3,     7,     4,   174,
       8,     4,     3,     8,   175,   177,     8,   175,   175,   175,
     175,   175,   174,   174,     8,     4,     4,     4,     4,     4,
     174,   174,     5,     4,     4,     4,   856,   175,   174,   859,
     862,   174,   862,   174,   174,   865,   862,   856,   856,   174,
     870,   856,   856,   873,   856,   870,   876,   865,   174,   174,
     865,   865,   870,   865,   177,   873,   174,   856,   870,   889,
     859,   873,   892,   862,   859,   177,   865,   862,   898,   856,
     865,   870,   856,   174,   873,   870,   175,   856,   865,   175,
     859,   865,     4,   862,   380,   608,   865,   856,   865,   856,
     889,   870,   423,   892,   873,   856,   865,   892,   865,   898,
     865,   614,   856,   870,   865,   856,   873,   856,   856,   870,
     889,   865,   873,   892,   865,   856,   865,   865,   856,   898,
     429,   898,   174,   174,   865,   830,   855,   865,   850,   694,
     876,   898,   868,   898,   878,   885,   473,   856,   858,  1028,
     441,   867,   470,   900,   861,   898,   465,   859,   875,   864,
     444,   862,   455,   662,  1033,   642,   488,   613,   889,   609,
     494,   490,   871,   873,  1041,  1061,  1081,    -1,   893,    -1,
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
      80,    73,    68,    75,    81,   559,     5,    10,     7,   868,
       9,   565,    18,    72,    73,    74,    75,   868,    77,    78,
     868,    80,    77,    78,    15,    16,    73,     0,    19,    73,
     531,    22,    34,    72,    73,    74,    75,    74,    77,    78,
     541,    80,     3,     7,    73,     6,    73,    74,    75,    74,
      85,    86,    73,     3,    75,   112,   113,     3,     8,    73,
       6,   174,    73,     7,    73,    73,    26,    27,    28,    29,
      30,    73,    73,    75,    76,    73,     3,    79,    80,    81,
       6,     8,   151,    85,    86,   154,   155,   156,   123,   124,
       3,     3,     7,     6,    85,    86,     8,    57,    58,    59,
      60,    61,    62,    63,    64,     7,     3,    72,    68,    69,
      70,     8,    72,   102,   103,   104,   105,   174,   107,    84,
      85,    86,     7,    83,     7,    85,    86,    87,    88,    89,
      90,    73,    97,     3,   140,   100,     7,    97,     8,   174,
     100,   101,     3,    85,    86,   148,    11,     8,   108,    14,
     142,   143,   144,   145,   157,   158,   159,     7,    23,     7,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     3,
       7,   174,   174,  1032,     8,   174,   175,   176,   177,     3,
       7,  1032,     6,   174,  1032,   177,   115,   116,   117,   118,
     119,   120,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    12,    13,    71,    71,    72,   150,   174,
     152,   153,     7,     3,   174,    17,    18,    82,     8,     3,
      85,    86,     3,     3,     8,    90,   149,     8,     8,   856,
      95,    96,   174,     3,   112,   113,   101,     3,     8,    26,
      27,    28,    29,    30,     7,     3,   111,     3,     3,   114,
       8,     4,     8,     8,     3,     3,   121,   122,     3,     8,
     125,   126,     3,     8,     3,   109,   110,     8,     8,     8,
      57,    58,    59,    60,    61,    62,    63,    64,     3,     8,
      67,   146,   147,     8,   149,    72,    73,     3,     3,     3,
     380,     3,     8,     8,     8,     3,     8,     3,    85,    86,
       8,    88,     8,    90,   370,   371,     4,    20,    21,   174,
      97,     4,     4,   100,    91,    92,    93,    94,     4,     4,
       4,   108,     4,    73,    74,    75,    76,    77,    78,     4,
       4,     4,     4,   423,     4,    85,    86,     4,     4,   429,
      35,    36,    37,    38,     4,     4,     3,     8,     4,     4,
       8,   441,     3,   174,   444,     4,     4,     3,     8,     4,
       4,     4,   441,   441,     4,   455,   441,   441,     4,   441,
     429,     4,     4,     4,     4,   465,     4,   455,   470,     4,
     470,     4,   441,   455,   470,   444,     4,   174,     4,     4,
     429,   177,   177,     4,   441,   177,   455,   441,   488,     4,
       4,     4,   441,     4,   488,   444,   465,   444,   488,     4,
     465,   470,   441,   490,   441,   470,   455,   444,   175,   444,
     441,    28,    29,    30,   174,   177,   465,   441,   455,   488,
     441,   470,   441,   441,   455,   501,   502,   503,   175,   175,
     441,   175,   175,   441,   176,   176,     4,   175,     4,   488,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
    1014,     4,     4,     7,   175,    72,     4,     4,    28,    29,
      30,     4,     4,     4,     4,     4,     4,   177,    85,    86,
       4,     4,     4,     4,     4,     4,   175,     4,     4,    96,
       4,     4,     4,     4,     4,   102,   103,   104,   105,   106,
     107,     4,   109,     4,     4,     4,     4,     4,     4,     4,
     175,    71,    72,    73,     4,     4,     4,     4,   608,     4,
       4,   587,     4,   177,   614,    85,    86,     4,     4,     4,
     177,     4,   609,     4,     4,   177,   177,   175,    98,    99,
     175,   607,     4,   177,    85,    86,   175,     7,   175,     7,
     640,   177,   642,     7,     7,   614,     7,   174,   642,     7,
     174,   174,   642,     5,   174,     5,     5,   174,     5,     5,
     141,     5,     7,     5,   174,   614,     5,     5,   174,     5,
       7,   640,     7,   642,     7,   174,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,     5,
     174,   640,   174,   642,   174,   146,   147,     5,   174,   174,
      34,   174,     7,   174,   174,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,   174,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     5,    73,
      24,     7,     7,     7,     7,     7,   174,     7,     7,   174,
       7,     7,     7,     4,     4,   174,   174,   174,   174,   174,
     174,     4,   174,     4,     4,     4,     4,     4,     4,     4,
     174,   174,   174,   174,     4,     6,     3,     6,   174,     3,
       6,   174,     3,   174,   174,   174,     6,     3,     6,     3,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,   174,   177,     6,     4,     6,     8,     4,     4,     4,
       4,   177,     4,   175,     4,   175,   175,     4,     4,   175,
     175,   175,   175,     4,     4,     4,   177,   175,     6,     3,
       3,     8,   175,     8,   175,   175,     4,     8,     8,     4,
     174,     4,     4,   175,   175,   175,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,     4,     7,   859,
     177,   175,   862,   865,   174,   865,     5,   174,   868,   865,
     859,   859,     4,   873,   859,   859,   876,   859,   873,   879,
     868,     4,     4,   868,   868,   873,   868,     4,   876,   177,
     859,   873,   892,   862,   876,   895,   865,   862,   175,   868,
     865,   901,   859,   868,   873,   859,   175,   876,   873,   541,
     859,   868,   614,   862,   868,   380,   865,   429,   832,   868,
     859,   868,   859,   892,   873,   174,   895,   876,   859,   868,
     895,   868,   901,   868,   608,   859,   873,   868,   859,   876,
     859,   859,   873,   892,   868,   876,   895,   868,   859,   868,
     868,   859,   901,   694,   901,   858,   423,   868,   853,   881,
     868,   871,   879,   888,   901,   473,   901,   861,   859,   441,
     870,  1032,   864,   862,   465,   470,   903,   867,   865,   876,
     878,   901,  1037,   662,   488,   892,   455,   494,   874,   642,
     609,   896,   490,   613,   444,  1045,  1065,  1082,    -1,    -1,
<<<<<<< HEAD
=======
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
<<<<<<< HEAD
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
      -1,    -1,  1032,    -1,    -1,    -1,    -1,  1037,    -1,    -1,
      -1,    -1,  1037,    -1,  1032,  1045,    -1,  1032,  1032,  1037,
    1032,    -1,    -1,    -1,    -1,  1037,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1032,    -1,    -1,    -1,  1032,  1037,    -1,
      -1,    -1,  1037,    -1,    -1,  1032,  1045,    -1,  1032,    -1,
    1045,    -1,    -1,  1032,    -1,  1032,    -1,    -1,  1037,    -1,
      -1,    -1,    -1,  1032,    -1,  1032,  1045,  1032,    -1,    -1,
    1037,  1032,    -1,    -1,    -1,    -1,  1037,    -1,  1032,    -1,
      -1,  1032,    -1,  1032,  1032,    -1,    -1,    -1,    -1,    -1,
      -1,  1032,    -1,    -1,  1032
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
       0,     5,     7,     9,   174,   175,   176,   177,   194,   195,
<<<<<<< HEAD
<<<<<<< HEAD
     196,   201,     7,   210,     7,   216,     7,   238,     7,   335,
       7,   415,     7,   431,     7,   367,     7,   373,     7,   397,
       7,   311,     7,   488,     7,   535,     7,   526,   202,   197,
     211,   217,   239,   336,   416,   432,   368,   374,   398,   312,
     489,   536,   527,   194,   203,   204,   174,   199,   200,    10,
     147,   157,   158,   159,   174,   209,   212,   213,   214,   518,
     520,   522,   533,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    70,    71,    81,    84,
      85,    89,    94,    95,   100,   110,   113,   120,   121,   124,
     125,   145,   146,   148,   209,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   231,   232,   233,
     234,   249,   251,   257,   259,   296,   305,   319,   329,   353,
     357,   365,   391,   421,   423,   425,   436,   438,   440,   463,
     475,   476,   484,   486,   514,   516,   524,   539,    15,    16,
      19,    22,   209,   236,   237,   240,   242,   245,   248,   421,
     423,    67,    68,    69,    82,    86,    87,    88,    96,    99,
     107,   209,   220,   221,   222,   223,   224,   225,   226,   227,
     232,   233,   337,   338,   339,   341,   343,   345,   347,   349,
     351,   353,   356,   391,   409,   421,   423,   425,   436,   438,
     440,   460,    83,   209,   349,   351,   391,   417,   418,   419,
     421,   423,    95,   101,   102,   103,   104,   105,   106,   108,
     209,   391,   421,   423,   433,   434,   435,   436,   438,   440,
     442,   446,   448,   450,   452,   454,   456,   458,   365,    34,
      72,    74,    75,    78,    79,    80,   209,   277,   375,   376,
     377,   378,   379,   380,   381,   383,   385,   387,   388,   390,
     421,   423,    73,    76,    77,   209,   277,   379,   385,   399,
     400,   401,   402,   403,   405,   406,   407,   408,   421,   423,
     111,   112,   209,   313,   314,   315,   317,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     209,   421,   423,   490,   491,   492,   493,   495,   497,   498,
     500,   501,   502,   505,   507,   508,   509,   512,   514,   516,
     537,   538,   539,    12,    13,   528,   529,   530,   532,     6,
       3,     4,     8,     3,   215,   534,   519,   521,   523,     4,
       3,     8,   525,   235,   252,     4,     4,     4,   437,   439,
     441,   250,   258,   260,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   230,   330,   366,   392,   358,   422,   424,
     354,   297,   464,   426,   306,   320,     4,   477,   485,   487,
     515,   517,   540,     3,     8,   241,   243,   246,     4,     3,
       8,   342,   344,   346,   410,   340,   348,     4,   352,   350,
     461,     3,     8,   420,     3,     8,   459,   447,   449,   453,
     451,   457,   455,   443,     8,     3,     8,   382,   278,     4,
     386,   384,   389,     4,     8,     3,   404,     4,     4,     8,
       3,   316,   318,     3,     8,     4,   494,   496,     4,   499,
       4,     4,   503,   506,     4,     4,   510,   513,     3,     8,
       3,     8,   531,     4,     3,     8,   194,   194,   174,     4,
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
     196,   201,     7,   210,     7,   216,     7,   238,     7,   336,
       7,   416,     7,   432,     7,   368,     7,   374,     7,   398,
       7,   312,     7,   489,     7,   536,     7,   527,   202,   197,
     211,   217,   239,   337,   417,   433,   369,   375,   399,   313,
     490,   537,   528,   194,   203,   204,   174,   199,   200,    10,
     148,   157,   158,   159,   174,   209,   212,   213,   214,   519,
     521,   523,   534,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    71,    72,    82,    85,
      86,    90,    95,    96,   101,   111,   114,   121,   122,   125,
     126,   146,   147,   149,   209,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   231,   232,   233,
     234,   249,   251,   257,   259,   297,   306,   320,   330,   354,
     358,   366,   392,   422,   424,   426,   437,   439,   441,   464,
     476,   477,   485,   487,   515,   517,   525,   540,    15,    16,
      19,    22,   209,   236,   237,   240,   242,   245,   248,   422,
     424,    68,    69,    70,    83,    87,    88,    89,    97,   100,
     108,   209,   220,   221,   222,   223,   224,   225,   226,   227,
     232,   233,   338,   339,   340,   342,   344,   346,   348,   350,
     352,   354,   357,   392,   410,   422,   424,   426,   437,   439,
     441,   461,    84,   209,   350,   352,   392,   418,   419,   420,
     422,   424,    96,   102,   103,   104,   105,   106,   107,   109,
     209,   392,   422,   424,   434,   435,   436,   437,   439,   441,
     443,   447,   449,   451,   453,   455,   457,   459,   366,    34,
      73,    75,    76,    79,    80,    81,   209,   277,   376,   377,
     378,   379,   380,   381,   382,   384,   386,   388,   389,   391,
     422,   424,    74,    77,    78,   209,   277,   380,   386,   400,
     401,   402,   403,   404,   406,   407,   408,   409,   422,   424,
     112,   113,   209,   314,   315,   316,   318,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     209,   422,   424,   491,   492,   493,   494,   496,   498,   499,
     501,   502,   503,   506,   508,   509,   510,   513,   515,   517,
     538,   539,   540,    12,    13,   529,   530,   531,   533,     6,
       3,     4,     8,     3,   215,   535,   520,   522,   524,     4,
       3,     8,   526,   235,   252,     4,     4,     4,   438,   440,
     442,   250,   258,   260,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   230,   331,   367,   393,   359,   423,   425,
     355,   298,   465,   427,   307,   321,     4,   478,   486,   488,
     516,   518,   541,     3,     8,   241,   243,   246,     4,     3,
       8,   343,   345,   347,   411,   341,   349,     4,   353,   351,
     462,     3,     8,   421,     3,     8,   460,   448,   450,   454,
     452,   458,   456,   444,     8,     3,     8,   383,   278,     4,
     387,   385,   390,     4,     8,     3,   405,     4,     4,     8,
       3,   317,   319,     3,     8,     4,   495,   497,     4,   500,
       4,     4,   504,   507,     4,     4,   511,   514,     3,     8,
       3,     8,   532,     4,     3,     8,   194,   194,   174,     4,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
       4,     4,     4,     4,   213,     4,     4,     4,   177,   177,
     177,     4,     4,     4,     4,     4,     4,   175,   175,   175,
     175,   175,   177,   176,   176,   175,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   175,
       4,     4,     4,     4,     4,     4,   219,     4,     4,     4,
     177,   237,     4,     4,     4,     4,     4,     4,   175,     4,
<<<<<<< HEAD
<<<<<<< HEAD
       4,     4,   338,     4,   418,     4,     4,     4,     4,     4,
       4,     4,     4,   435,     4,     4,   175,     4,     4,     4,
     177,   377,     4,   177,   177,   401,     4,     4,   314,   177,
       4,     4,   175,     4,   175,   175,     4,     4,   177,   177,
       4,     4,   491,   538,     4,   175,   529,     4,     7,     7,
     194,   194,   194,     7,     7,     7,   174,   174,   174,     7,
       7,     5,   174,     5,     5,     5,     5,   196,   198,   174,
      90,    91,    92,    93,   355,     5,     5,     5,     5,     7,
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
       4,     4,   339,     4,   419,     4,     4,     4,     4,     4,
       4,     4,     4,   436,     4,     4,   175,     4,     4,     4,
     177,   378,     4,   177,   177,   402,     4,     4,   315,   177,
       4,     4,   175,     4,   175,   175,     4,     4,   177,   177,
       4,     4,   492,   539,     4,   175,   530,     4,     7,     7,
     194,   194,   194,     7,     7,     7,   174,   174,   174,     7,
       7,     5,   174,     5,     5,     5,     5,   196,   198,   174,
      91,    92,    93,    94,   356,     5,     5,     5,     5,     7,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
       7,   198,     7,   174,   174,     5,     5,   205,    17,    18,
     244,    20,    21,   247,   174,   174,   174,     5,   174,   174,
     205,   174,     7,   174,   205,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   194,
<<<<<<< HEAD
<<<<<<< HEAD
     174,   174,   174,    18,   139,   504,   140,   141,   142,   143,
     144,   177,   511,   174,     5,   194,   218,   537,   528,   236,
      24,   253,   254,   255,    34,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,   209,   265,   266,   267,   270,   272,   274,   276,
     277,   279,   280,   281,   282,   283,   284,   285,   286,   288,
     290,   292,   294,   295,   265,     7,   261,   262,   263,     7,
     331,   332,   333,     7,   369,   370,   371,     7,   393,   394,
     395,     7,   359,   360,   361,   101,   102,   103,   104,   106,
     298,   299,   300,   301,   302,   303,   304,     7,   465,   466,
       7,   427,   428,   429,     7,   307,   308,   309,   114,   115,
     116,   117,   118,   119,   321,   322,   323,   324,   325,   326,
     327,   328,   122,   123,   209,   421,   423,   478,   479,   480,
     482,   490,     7,   541,   542,   206,     7,   411,   412,   413,
     109,   442,   444,   462,   261,     8,     8,     8,     8,   256,
       3,     8,   268,   271,   273,   275,     4,     4,     4,     4,
       4,   287,   289,   291,   293,     4,     4,     4,     4,     4,
       3,     8,     8,   264,     6,     3,   334,     6,     3,   372,
       6,     3,   396,     6,     3,   362,     6,     3,     3,     6,
     467,     3,     6,   430,     6,     3,   310,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   481,   483,     3,
       8,     8,   543,     3,     6,   174,   207,   208,   414,     6,
       3,   445,     8,     6,     4,   254,     4,     4,     4,     4,
     175,   177,   175,   177,   175,     4,     4,     4,     4,   175,
     175,   175,   175,   177,   266,   265,   263,   337,   333,   375,
     371,   399,   395,   209,   220,   221,   222,   223,   224,   225,
     226,   227,   232,   233,   277,   329,   347,   349,   351,   353,
     363,   364,   391,   421,   423,   436,   438,   440,   460,   361,
     299,    97,    98,   209,   277,   365,   391,   421,   423,   436,
     438,   440,   468,   469,   470,   471,   472,   474,   466,   433,
     429,   313,   309,   175,   175,   175,   175,   175,   175,   322,
       4,     4,   479,   149,   151,   152,   209,   277,   421,   423,
     544,   545,   546,   547,   549,   542,     6,     3,   417,   413,
       4,   174,    35,    36,    37,    38,   269,   174,   174,   174,
     174,   174,   174,   174,     8,     8,     8,     8,     3,     8,
     473,     4,     8,     3,     8,     8,   174,   174,   550,     4,
     548,     3,     8,   174,     8,   205,   364,     4,   177,   470,
       4,   175,     4,   545,   174,     5,   174,     7,   551,   552,
     553,     3,     6,   150,   153,   154,   155,   156,   554,   555,
     556,   558,   559,   560,   561,   552,   557,     4,     4,     4,
     562,     3,     8,     4,   177,   175,   175,     4,   555,   174,
     174
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
     174,   174,   174,    18,   140,   505,   141,   142,   143,   144,
     145,   177,   512,   174,     5,   194,   218,   538,   529,   236,
      24,   253,   254,   255,    34,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,   209,   265,   266,   267,   270,   272,   274,
     276,   277,   279,   280,   281,   282,   283,   284,   285,   286,
     288,   290,   292,   294,   295,   296,   265,     7,   261,   262,
     263,     7,   332,   333,   334,     7,   370,   371,   372,     7,
     394,   395,   396,     7,   360,   361,   362,   102,   103,   104,
     105,   107,   299,   300,   301,   302,   303,   304,   305,     7,
     466,   467,     7,   428,   429,   430,     7,   308,   309,   310,
     115,   116,   117,   118,   119,   120,   322,   323,   324,   325,
     326,   327,   328,   329,   123,   124,   209,   422,   424,   479,
     480,   481,   483,   491,     7,   542,   543,   206,     7,   412,
     413,   414,   110,   443,   445,   463,   261,     8,     8,     8,
       8,   256,     3,     8,   268,   271,   273,   275,     4,     4,
       4,     4,     4,   287,   289,   291,   293,     4,     4,     4,
       4,     4,     4,     3,     8,     8,   264,     6,     3,   335,
       6,     3,   373,     6,     3,   397,     6,     3,   363,     6,
       3,     3,     6,   468,     3,     6,   431,     6,     3,   311,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     482,   484,     3,     8,     8,   544,     3,     6,   174,   207,
     208,   415,     6,     3,   446,     8,     6,     4,   254,     4,
       4,     4,     4,   175,   177,   175,   177,   175,     4,     4,
       4,     4,   175,   175,   175,   175,   177,   175,   266,   265,
     263,   338,   334,   376,   372,   400,   396,   209,   220,   221,
     222,   223,   224,   225,   226,   227,   232,   233,   277,   330,
     348,   350,   352,   354,   364,   365,   392,   422,   424,   437,
     439,   441,   461,   362,   300,    98,    99,   209,   277,   366,
     392,   422,   424,   437,   439,   441,   469,   470,   471,   472,
     473,   475,   467,   434,   430,   314,   310,   175,   175,   175,
     175,   175,   175,   323,     4,     4,   480,   150,   152,   153,
     209,   277,   422,   424,   545,   546,   547,   548,   550,   543,
       6,     3,   418,   414,     4,   174,    35,    36,    37,    38,
     269,   174,   174,   174,   174,   174,   174,   174,     8,     8,
       8,     8,     3,     8,   474,     4,     8,     3,     8,     8,
     174,   174,   551,     4,   549,     3,     8,   174,     8,   205,
     365,     4,   177,   471,     4,   175,     4,   546,   174,     5,
     174,     7,   552,   553,   554,     3,     6,   151,   154,   155,
     156,   555,   556,   557,   559,   560,   561,   553,   558,     4,
       4,     4,     3,     8,     4,   177,   175,   175,   556,   174
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   178,   180,   179,   181,   179,   182,   179,   183,   179,
     184,   179,   185,   179,   186,   179,   187,   179,   188,   179,
     189,   179,   190,   179,   191,   179,   192,   179,   193,   179,
     194,   194,   194,   194,   194,   194,   194,   195,   197,   196,
     198,   199,   199,   200,   200,   202,   201,   203,   203,   204,
     204,   206,   205,   207,   207,   208,   208,   209,   211,   210,
     212,   212,   213,   213,   213,   213,   213,   213,   215,   214,
     217,   216,   218,   218,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   230,   229,   231,   232,   233,
     235,   234,   236,   236,   237,   237,   237,   237,   237,   237,
     237,   239,   238,   241,   240,   243,   242,   244,   244,   246,
     245,   247,   247,   248,   250,   249,   252,   251,   253,   253,
     254,   256,   255,   258,   257,   260,   259,   261,   261,   262,
     262,   264,   263,   265,   265,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
<<<<<<< HEAD
<<<<<<< HEAD
     266,   266,   266,   266,   266,   268,   267,   269,   269,   269,
     269,   271,   270,   273,   272,   275,   274,   276,   278,   277,
     279,   280,   281,   282,   283,   284,   285,   287,   286,   289,
     288,   291,   290,   293,   292,   294,   295,   297,   296,   298,
     298,   299,   299,   299,   299,   299,   300,   301,   302,   303,
     304,   306,   305,   307,   307,   308,   308,   310,   309,   312,
     311,   313,   313,   313,   314,   314,   316,   315,   318,   317,
     320,   319,   321,   321,   322,   322,   322,   322,   322,   322,
     323,   324,   325,   326,   327,   328,   330,   329,   331,   331,
     332,   332,   334,   333,   336,   335,   337,   337,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   340,   339,   342,
     341,   344,   343,   346,   345,   348,   347,   350,   349,   352,
     351,   354,   353,   355,   355,   355,   355,   356,   358,   357,
     359,   359,   360,   360,   362,   361,   363,   363,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   366,   365,   368,   367,   369,   369,   370,   370,
     372,   371,   374,   373,   375,   375,   376,   376,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   378,   379,
     380,   382,   381,   384,   383,   386,   385,   387,   389,   388,
     390,   392,   391,   393,   393,   394,   394,   396,   395,   398,
     397,   399,   399,   400,   400,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   402,   404,   403,   405,   406,   407,
     408,   410,   409,   411,   411,   412,   412,   414,   413,   416,
     415,   417,   417,   418,   418,   418,   418,   418,   418,   418,
     420,   419,   422,   421,   424,   423,   426,   425,   427,   427,
     428,   428,   430,   429,   432,   431,   433,   433,   434,   434,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   437,   436,   439,   438,   441,
     440,   443,   442,   445,   444,   447,   446,   449,   448,   451,
     450,   453,   452,   455,   454,   457,   456,   459,   458,   461,
     460,   462,   462,   464,   463,   465,   465,   467,   466,   468,
     468,   469,   469,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   471,   473,   472,   474,   475,   477,
     476,   478,   478,   479,   479,   479,   479,   479,   481,   480,
     483,   482,   485,   484,   487,   486,   489,   488,   490,   490,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   492,   494,
     493,   496,   495,   497,   499,   498,   500,   501,   503,   502,
     504,   504,   506,   505,   507,   508,   510,   509,   511,   511,
     511,   511,   511,   513,   512,   515,   514,   517,   516,   519,
     518,   521,   520,   523,   522,   525,   524,   527,   526,   528,
     528,   529,   529,   531,   530,   532,   534,   533,   536,   535,
     537,   537,   538,   540,   539,   541,   541,   543,   542,   544,
     544,   545,   545,   545,   545,   545,   545,   545,   546,   548,
     547,   550,   549,   551,   551,   553,   552,   554,   554,   555,
     555,   555,   555,   555,   557,   556,   558,   559,   560,   562,
     561
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
     266,   266,   266,   266,   266,   266,   268,   267,   269,   269,
     269,   269,   271,   270,   273,   272,   275,   274,   276,   278,
     277,   279,   280,   281,   282,   283,   284,   285,   287,   286,
     289,   288,   291,   290,   293,   292,   294,   295,   296,   298,
     297,   299,   299,   300,   300,   300,   300,   300,   301,   302,
     303,   304,   305,   307,   306,   308,   308,   309,   309,   311,
     310,   313,   312,   314,   314,   314,   315,   315,   317,   316,
     319,   318,   321,   320,   322,   322,   323,   323,   323,   323,
     323,   323,   324,   325,   326,   327,   328,   329,   331,   330,
     332,   332,   333,   333,   335,   334,   337,   336,   338,   338,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   341,
     340,   343,   342,   345,   344,   347,   346,   349,   348,   351,
     350,   353,   352,   355,   354,   356,   356,   356,   356,   357,
     359,   358,   360,   360,   361,   361,   363,   362,   364,   364,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   367,   366,   369,   368,   370,   370,
     371,   371,   373,   372,   375,   374,   376,   376,   377,   377,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     379,   380,   381,   383,   382,   385,   384,   387,   386,   388,
     390,   389,   391,   393,   392,   394,   394,   395,   395,   397,
     396,   399,   398,   400,   400,   401,   401,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   403,   405,   404,   406,
     407,   408,   409,   411,   410,   412,   412,   413,   413,   415,
     414,   417,   416,   418,   418,   419,   419,   419,   419,   419,
     419,   419,   421,   420,   423,   422,   425,   424,   427,   426,
     428,   428,   429,   429,   431,   430,   433,   432,   434,   434,
     435,   435,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   438,   437,   440,
     439,   442,   441,   444,   443,   446,   445,   448,   447,   450,
     449,   452,   451,   454,   453,   456,   455,   458,   457,   460,
     459,   462,   461,   463,   463,   465,   464,   466,   466,   468,
     467,   469,   469,   470,   470,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   472,   474,   473,   475,
     476,   478,   477,   479,   479,   480,   480,   480,   480,   480,
     482,   481,   484,   483,   486,   485,   488,   487,   490,   489,
     491,   491,   492,   492,   492,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   492,   492,   492,   492,   492,   492,
     493,   495,   494,   497,   496,   498,   500,   499,   501,   502,
     504,   503,   505,   505,   507,   506,   508,   509,   511,   510,
     512,   512,   512,   512,   512,   514,   513,   516,   515,   518,
     517,   520,   519,   522,   521,   524,   523,   526,   525,   528,
     527,   529,   529,   530,   530,   532,   531,   533,   535,   534,
     537,   536,   538,   538,   539,   541,   540,   542,   542,   544,
     543,   545,   545,   546,   546,   546,   546,   546,   546,   546,
     547,   549,   548,   551,   550,   552,   552,   554,   553,   555,
     555,   556,   556,   556,   556,   558,   557,   559,   560,   561
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     1,     1,     0,
       4,     1,     1,     3,     0,     6,     0,     6,     1,     3,
       1,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
<<<<<<< HEAD
<<<<<<< HEAD
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     3,     0,     6,     0,     4,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     3,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"config-fetch-wait-time\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"authoritative\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"consistency\"", "\"serial-consistency\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"id\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"global\"",
  "\"all\"", "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "interfaces_config", "$@22",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@23", "interfaces_list", "$@24", "dhcp_socket_type", "$@25",
  "socket_type", "outbound_interface", "$@26", "outbound_interface_value",
  "re_detect", "lease_database", "$@27", "sanity_checks", "$@28",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@29",
  "hosts_database", "$@30", "hosts_databases", "$@31", "database_list",
  "not_empty_database_list", "database", "$@32", "database_map_params",
  "database_map_param", "database_type", "$@33", "db_type", "user", "$@34",
  "password", "$@35", "host", "$@36", "port", "name", "$@37", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@38", "keyspace",
  "$@39", "consistency", "$@40", "serial_consistency", "$@41",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
  "host_reservation_identifiers", "$@42",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@43", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@44",
  "sub_hooks_library", "$@45", "hooks_params", "hooks_param", "library",
  "$@46", "parameters", "$@47", "expired_leases_processing", "$@48",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@49",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@50",
  "sub_subnet4", "$@51", "subnet4_params", "subnet4_param", "subnet",
  "$@52", "subnet_4o6_interface", "$@53", "subnet_4o6_interface_id",
  "$@54", "subnet_4o6_subnet", "$@55", "interface", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "shared_networks", "$@60", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@61",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@62", "sub_option_def_list", "$@63", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@64",
  "sub_option_def", "$@65", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool4", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "reservations", "$@80", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@81", "sub_reservation",
  "$@82", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@83", "server_hostname", "$@84",
  "boot_file_name", "$@85", "ip_address", "$@86", "ip_addresses", "$@87",
  "duid", "$@88", "hw_address", "$@89", "client_id_value", "$@90",
  "circuit_id_value", "$@91", "flex_id_value", "$@92", "hostname", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "client_classes", "$@96", "client_classes_list", "client_class_entry",
  "$@97", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@98",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@99",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@100", "control_socket_name", "$@101", "dhcp_queue_control", "$@102",
  "dhcp_ddns", "$@103", "sub_dhcp_ddns", "$@104", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@105",
  "server_ip", "$@106", "server_port", "sender_ip", "$@107", "sender_port",
  "max_queue_size", "ncr_protocol", "$@108", "ncr_protocol_value",
  "ncr_format", "$@109", "override_no_update", "override_client_update",
  "replace_client_name", "$@110", "replace_client_name_value",
  "generated_prefix", "$@111", "hostname_char_set", "$@112",
  "hostname_char_replacement", "$@113", "dhcp6_json_object", "$@114",
  "dhcpddns_json_object", "$@115", "control_agent_json_object", "$@116",
  "config_control", "$@117", "sub_config_control", "$@118",
  "config_control_params", "config_control_param", "config_databases",
  "$@119", "config_fetch_wait_time", "logging_object", "$@120",
  "sub_logging", "$@121", "logging_params", "logging_param", "loggers",
  "$@122", "loggers_entries", "logger_entry", "$@123", "logger_params",
  "logger_param", "debuglevel", "severity", "$@124", "output_options_list",
  "$@125", "output_options_list_content", "output_entry", "$@126",
  "output_params_list", "output_params", "output", "$@127", "flush",
  "maxsize", "maxver", "pattern", "$@128", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   265,   265,   265,   266,   266,   267,   267,   268,   268,
     269,   269,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     286,   287,   288,   289,   290,   291,   292,   295,   300,   300,
     311,   314,   315,   318,   322,   329,   329,   336,   337,   340,
     344,   351,   351,   358,   359,   362,   366,   377,   387,   387,
     403,   404,   408,   409,   410,   411,   412,   413,   416,   416,
     431,   431,   440,   441,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   490,   495,   500,   505,
     510,   515,   520,   525,   530,   535,   535,   543,   548,   553,
     559,   559,   570,   571,   574,   575,   576,   577,   578,   579,
     580,   583,   583,   592,   592,   602,   602,   609,   610,   613,
     613,   620,   622,   626,   632,   632,   644,   644,   654,   655,
     657,   659,   659,   677,   677,   689,   689,   699,   700,   703,
     704,   707,   707,   717,   718,   721,   722,   723,   724,   725,
     726,   727,   728,   729,   730,   731,   732,   733,   734,   735,
<<<<<<< HEAD
<<<<<<< HEAD
     736,   737,   738,   739,   740,   743,   743,   750,   751,   752,
     753,   756,   756,   764,   764,   772,   772,   780,   785,   785,
     793,   798,   803,   808,   813,   818,   823,   828,   828,   836,
     836,   844,   844,   852,   852,   860,   865,   870,   870,   880,
     881,   884,   885,   886,   887,   888,   891,   896,   901,   906,
     911,   916,   916,   926,   927,   930,   931,   934,   934,   944,
     944,   954,   955,   956,   959,   960,   963,   963,   971,   971,
     979,   979,   990,   991,   994,   995,   996,   997,   998,   999,
    1002,  1007,  1012,  1017,  1022,  1027,  1035,  1035,  1048,  1049,
    1052,  1053,  1060,  1060,  1086,  1086,  1097,  1098,  1102,  1103,
    1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,  1112,  1113,
    1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,  1123,
    1124,  1125,  1126,  1127,  1128,  1129,  1130,  1133,  1133,  1141,
    1141,  1149,  1149,  1157,  1157,  1165,  1165,  1173,  1173,  1181,
    1181,  1191,  1191,  1198,  1199,  1200,  1201,  1204,  1211,  1211,
    1222,  1223,  1227,  1228,  1231,  1231,  1239,  1240,  1243,  1244,
    1245,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,
    1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265,  1266,  1273,  1273,  1286,  1286,  1295,  1296,  1299,  1300,
    1305,  1305,  1320,  1320,  1334,  1335,  1338,  1339,  1342,  1343,
    1344,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1354,  1356,
    1361,  1363,  1363,  1371,  1371,  1379,  1379,  1387,  1389,  1389,
    1397,  1406,  1406,  1418,  1419,  1424,  1425,  1430,  1430,  1442,
    1442,  1454,  1455,  1460,  1461,  1466,  1467,  1468,  1469,  1470,
    1471,  1472,  1473,  1474,  1477,  1479,  1479,  1487,  1489,  1491,
    1496,  1504,  1504,  1516,  1517,  1520,  1521,  1524,  1524,  1534,
    1534,  1544,  1545,  1548,  1549,  1550,  1551,  1552,  1553,  1554,
    1557,  1557,  1565,  1565,  1590,  1590,  1620,  1620,  1630,  1631,
    1634,  1635,  1638,  1638,  1647,  1647,  1656,  1657,  1660,  1661,
    1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,  1674,
    1675,  1676,  1677,  1678,  1679,  1682,  1682,  1690,  1690,  1698,
    1698,  1706,  1706,  1714,  1714,  1724,  1724,  1732,  1732,  1740,
    1740,  1748,  1748,  1756,  1756,  1764,  1764,  1772,  1772,  1785,
    1785,  1795,  1796,  1802,  1802,  1812,  1813,  1816,  1816,  1826,
    1827,  1830,  1831,  1834,  1835,  1836,  1837,  1838,  1839,  1840,
    1841,  1842,  1843,  1844,  1847,  1849,  1849,  1857,  1866,  1873,
    1873,  1883,  1884,  1887,  1888,  1889,  1890,  1891,  1894,  1894,
    1902,  1902,  1913,  1913,  1951,  1951,  1963,  1963,  1973,  1974,
    1977,  1978,  1979,  1980,  1981,  1982,  1983,  1984,  1985,  1986,
    1987,  1988,  1989,  1990,  1991,  1992,  1993,  1994,  1997,  2002,
    2002,  2010,  2010,  2018,  2023,  2023,  2031,  2036,  2041,  2041,
    2049,  2050,  2053,  2053,  2061,  2066,  2071,  2071,  2079,  2082,
    2085,  2088,  2091,  2097,  2097,  2105,  2105,  2113,  2113,  2124,
    2124,  2131,  2131,  2138,  2138,  2145,  2145,  2156,  2156,  2166,
    2167,  2171,  2172,  2175,  2175,  2185,  2195,  2195,  2205,  2205,
    2216,  2217,  2221,  2225,  2225,  2237,  2238,  2242,  2242,  2250,
    2251,  2254,  2255,  2256,  2257,  2258,  2259,  2260,  2263,  2268,
    2268,  2276,  2276,  2286,  2287,  2290,  2290,  2298,  2299,  2302,
    2303,  2304,  2305,  2306,  2309,  2309,  2317,  2322,  2327,  2332,
    2332
=======
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
     736,   737,   738,   739,   740,   741,   744,   744,   751,   752,
     753,   754,   757,   757,   765,   765,   773,   773,   781,   786,
     786,   794,   799,   804,   809,   814,   819,   824,   829,   829,
     837,   837,   845,   845,   853,   853,   861,   866,   871,   877,
     877,   887,   888,   891,   892,   893,   894,   895,   898,   903,
     908,   913,   918,   923,   923,   933,   934,   937,   938,   941,
     941,   951,   951,   961,   962,   963,   966,   967,   970,   970,
     978,   978,   986,   986,   997,   998,  1001,  1002,  1003,  1004,
    1005,  1006,  1009,  1014,  1019,  1024,  1029,  1034,  1042,  1042,
    1055,  1056,  1059,  1060,  1067,  1067,  1093,  1093,  1104,  1105,
    1109,  1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,  1118,
    1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,  1128,
    1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,  1140,
    1140,  1148,  1148,  1156,  1156,  1164,  1164,  1172,  1172,  1180,
    1180,  1188,  1188,  1198,  1198,  1205,  1206,  1207,  1208,  1211,
    1218,  1218,  1229,  1230,  1234,  1235,  1238,  1238,  1246,  1247,
    1250,  1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,  1259,
    1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,
    1270,  1271,  1272,  1273,  1280,  1280,  1293,  1293,  1302,  1303,
    1306,  1307,  1312,  1312,  1327,  1327,  1341,  1342,  1345,  1346,
    1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,  1357,  1358,
    1361,  1363,  1368,  1370,  1370,  1378,  1378,  1386,  1386,  1394,
    1396,  1396,  1404,  1413,  1413,  1425,  1426,  1431,  1432,  1437,
    1437,  1449,  1449,  1461,  1462,  1467,  1468,  1473,  1474,  1475,
    1476,  1477,  1478,  1479,  1480,  1481,  1484,  1486,  1486,  1494,
    1496,  1498,  1503,  1511,  1511,  1523,  1524,  1527,  1528,  1531,
    1531,  1541,  1541,  1551,  1552,  1555,  1556,  1557,  1558,  1559,
    1560,  1561,  1564,  1564,  1572,  1572,  1597,  1597,  1627,  1627,
    1637,  1638,  1641,  1642,  1645,  1645,  1654,  1654,  1663,  1664,
    1667,  1668,  1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,
    1680,  1681,  1682,  1683,  1684,  1685,  1686,  1689,  1689,  1697,
    1697,  1705,  1705,  1713,  1713,  1721,  1721,  1731,  1731,  1739,
    1739,  1747,  1747,  1755,  1755,  1763,  1763,  1771,  1771,  1779,
    1779,  1792,  1792,  1802,  1803,  1809,  1809,  1819,  1820,  1823,
    1823,  1833,  1834,  1837,  1838,  1841,  1842,  1843,  1844,  1845,
    1846,  1847,  1848,  1849,  1850,  1851,  1854,  1856,  1856,  1864,
    1873,  1880,  1880,  1890,  1891,  1894,  1895,  1896,  1897,  1898,
    1901,  1901,  1909,  1909,  1920,  1920,  1958,  1958,  1970,  1970,
    1980,  1981,  1984,  1985,  1986,  1987,  1988,  1989,  1990,  1991,
    1992,  1993,  1994,  1995,  1996,  1997,  1998,  1999,  2000,  2001,
    2004,  2009,  2009,  2017,  2017,  2025,  2030,  2030,  2038,  2043,
    2048,  2048,  2056,  2057,  2060,  2060,  2068,  2073,  2078,  2078,
    2086,  2089,  2092,  2095,  2098,  2104,  2104,  2112,  2112,  2120,
    2120,  2131,  2131,  2138,  2138,  2145,  2145,  2152,  2152,  2163,
    2163,  2173,  2174,  2178,  2179,  2182,  2182,  2192,  2202,  2202,
    2212,  2212,  2223,  2224,  2228,  2232,  2232,  2244,  2245,  2249,
    2249,  2257,  2258,  2261,  2262,  2263,  2264,  2265,  2266,  2267,
    2270,  2275,  2275,  2283,  2283,  2293,  2294,  2297,  2297,  2305,
    2306,  2309,  2310,  2311,  2312,  2315,  2315,  2323,  2328,  2333
<<<<<<< HEAD
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
  };

  // Print the state stack on the debug stream.
  void
  Dhcp4Parser::yystack_print_ ()
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1218
} } // isc::dhcp
<<<<<<< HEAD
<<<<<<< HEAD
#line 5118 "dhcp4_parser.cc"

#line 2341 "dhcp4_parser.yy"
=======
#line 5087 "dhcp4_parser.cc" // lalr1.cc:1218
#line 2338 "dhcp4_parser.yy" // lalr1.cc:1219
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter
=======
#line 5087 "dhcp4_parser.cc" // lalr1.cc:1218
#line 2338 "dhcp4_parser.yy" // lalr1.cc:1219
>>>>>>> [#805,!5-p] Memfile and kea-dhcp4 now suppor max-row-errors parameter


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
