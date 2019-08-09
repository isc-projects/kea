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
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:438

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc" // lalr1.cc:438


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:513
namespace isc { namespace dhcp {
#line 146 "dhcp6_parser.cc" // lalr1.cc:513

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 185: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 184: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 183: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 182: // "constant string"
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

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 185: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 184: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 183: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 182: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if !defined __cplusplus || __cplusplus < 201103L
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
        value.move< ElementPtr > (that.value);
        break;

      case 185: // "boolean"
        value.move< bool > (that.value);
        break;

      case 184: // "floating point"
        value.move< double > (that.value);
        break;

      case 183: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 182: // "constant string"
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
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
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
      case 182: // "constant string"
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 405 "dhcp6_parser.cc"
        break;

      case 183: // "integer"
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 411 "dhcp6_parser.cc"
        break;

      case 184: // "floating point"
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case 185: // "boolean"
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case 203: // value
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case 207: // map_value
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case 268: // db_type
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case 361: // hr_mode
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case 497: // duid_type
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case 532: // ncr_protocol_value
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case 539: // replace_client_name_value
#line 261 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
=======
            case 182: // "constant string"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 183: // "integer"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 184: // "floating point"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 185: // "boolean"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 203: // value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 207: // map_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 268: // db_type

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 362: // hr_mode

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 498: // duid_type

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 533: // ncr_protocol_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 540: // replace_client_name_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 468 "dhcp6_parser.cc" // lalr1.cc:672
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
        break;

=======
            case 182: // "constant string"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 183: // "integer"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 184: // "floating point"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 185: // "boolean"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 203: // value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 207: // map_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 268: // db_type

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 362: // hr_mode

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 498: // duid_type

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 533: // ncr_protocol_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 540: // replace_client_name_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 468 "dhcp6_parser.cc" // lalr1.cc:672
        break;

>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Dhcp6Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if defined __cplusplus && 201103L <= __cplusplus
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp6Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp6Parser::parse ()
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
      case 203: // value
      case 207: // map_value
      case 268: // db_type
<<<<<<< HEAD
<<<<<<< HEAD
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 185: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 184: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 183: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 182: // "constant string"
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
#line 270 "dhcp6_parser.yy"
=======
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
<<<<<<< HEAD
<<<<<<< HEAD
#line 271 "dhcp6_parser.yy"
=======
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
<<<<<<< HEAD
<<<<<<< HEAD
#line 272 "dhcp6_parser.yy"
=======
#line 272 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 272 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
<<<<<<< HEAD
<<<<<<< HEAD
#line 273 "dhcp6_parser.yy"
=======
#line 273 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 273 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
<<<<<<< HEAD
<<<<<<< HEAD
#line 274 "dhcp6_parser.yy"
=======
#line 274 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 274 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
<<<<<<< HEAD
<<<<<<< HEAD
#line 275 "dhcp6_parser.yy"
=======
#line 275 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 275 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
<<<<<<< HEAD
<<<<<<< HEAD
#line 276 "dhcp6_parser.yy"
=======
#line 276 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 276 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
<<<<<<< HEAD
<<<<<<< HEAD
#line 277 "dhcp6_parser.yy"
=======
#line 277 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 277 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
<<<<<<< HEAD
<<<<<<< HEAD
#line 278 "dhcp6_parser.yy"
=======
#line 278 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 278 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
<<<<<<< HEAD
<<<<<<< HEAD
#line 279 "dhcp6_parser.yy"
=======
#line 279 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 279 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
<<<<<<< HEAD
<<<<<<< HEAD
#line 280 "dhcp6_parser.yy"
=======
#line 280 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 280 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
<<<<<<< HEAD
<<<<<<< HEAD
#line 281 "dhcp6_parser.yy"
=======
#line 281 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 281 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
<<<<<<< HEAD
<<<<<<< HEAD
#line 282 "dhcp6_parser.yy"
=======
#line 282 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 282 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
<<<<<<< HEAD
<<<<<<< HEAD
#line 283 "dhcp6_parser.yy"
=======
#line 283 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 283 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
<<<<<<< HEAD
<<<<<<< HEAD
#line 284 "dhcp6_parser.yy"
=======
#line 284 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 284 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
<<<<<<< HEAD
<<<<<<< HEAD
#line 292 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 821 "dhcp6_parser.cc"
    break;

  case 33:
#line 293 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 827 "dhcp6_parser.cc"
    break;

  case 34:
#line 294 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 833 "dhcp6_parser.cc"
    break;

  case 35:
#line 295 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp6_parser.cc"
    break;

  case 36:
#line 296 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp6_parser.cc"
    break;

  case 37:
#line 297 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 851 "dhcp6_parser.cc"
    break;

  case 38:
#line 298 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 857 "dhcp6_parser.cc"
    break;

  case 39:
#line 301 "dhcp6_parser.yy"
=======
#line 292 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 293 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 294 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 295 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 296 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 297 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 298 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 301 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 292 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 293 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 294 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 295 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 296 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 297 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 298 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 301 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
<<<<<<< HEAD
<<<<<<< HEAD
#line 306 "dhcp6_parser.yy"
=======
#line 306 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 306 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 41:
<<<<<<< HEAD
<<<<<<< HEAD
#line 311 "dhcp6_parser.yy"
=======
#line 311 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 311 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 42:
<<<<<<< HEAD
<<<<<<< HEAD
#line 317 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 893 "dhcp6_parser.cc"
    break;

  case 45:
#line 324 "dhcp6_parser.yy"
=======
#line 317 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 324 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 317 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 324 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
<<<<<<< HEAD
<<<<<<< HEAD
#line 328 "dhcp6_parser.yy"
=======
#line 328 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 328 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 47:
<<<<<<< HEAD
<<<<<<< HEAD
#line 335 "dhcp6_parser.yy"
=======
#line 335 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 335 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 48:
<<<<<<< HEAD
<<<<<<< HEAD
#line 338 "dhcp6_parser.yy"
=======
#line 338 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 338 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // list parsing complete. Put any sanity checking here
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
<<<<<<< HEAD
<<<<<<< HEAD
#line 346 "dhcp6_parser.yy"
=======
#line 346 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 346 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
<<<<<<< HEAD
<<<<<<< HEAD
#line 350 "dhcp6_parser.yy"
=======
#line 350 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 350 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 53:
<<<<<<< HEAD
<<<<<<< HEAD
#line 357 "dhcp6_parser.yy"
=======
#line 357 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 357 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // List parsing about to start
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 54:
<<<<<<< HEAD
<<<<<<< HEAD
#line 359 "dhcp6_parser.yy"
=======
#line 359 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 359 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
<<<<<<< HEAD
<<<<<<< HEAD
#line 368 "dhcp6_parser.yy"
=======
#line 368 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 368 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
<<<<<<< HEAD
<<<<<<< HEAD
#line 372 "dhcp6_parser.yy"
=======
#line 372 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 372 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
<<<<<<< HEAD
<<<<<<< HEAD
#line 383 "dhcp6_parser.yy"
=======
#line 383 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 383 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 60:
<<<<<<< HEAD
<<<<<<< HEAD
#line 393 "dhcp6_parser.yy"
=======
#line 393 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 393 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 61:
<<<<<<< HEAD
<<<<<<< HEAD
#line 398 "dhcp6_parser.yy"
=======
#line 398 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 398 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1013 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 70:
<<<<<<< HEAD
<<<<<<< HEAD
#line 421 "dhcp6_parser.yy"
=======
#line 421 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 421 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 71:
<<<<<<< HEAD
<<<<<<< HEAD
#line 428 "dhcp6_parser.yy"
=======
#line 428 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 428 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 72:
<<<<<<< HEAD
<<<<<<< HEAD
#line 436 "dhcp6_parser.yy"
=======
#line 436 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 436 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 73:
<<<<<<< HEAD
<<<<<<< HEAD
#line 440 "dhcp6_parser.yy"
=======
#line 440 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 440 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // No global parameter is required
    // parsing completed
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 119:
<<<<<<< HEAD
<<<<<<< HEAD
#line 496 "dhcp6_parser.yy"
=======
#line 496 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 496 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 120:
<<<<<<< HEAD
<<<<<<< HEAD
#line 498 "dhcp6_parser.yy"
=======
#line 498 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 498 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 121:
<<<<<<< HEAD
<<<<<<< HEAD
#line 504 "dhcp6_parser.yy"
=======
#line 504 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 504 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 122:
<<<<<<< HEAD
<<<<<<< HEAD
#line 509 "dhcp6_parser.yy"
=======
#line 509 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 509 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 123:
<<<<<<< HEAD
<<<<<<< HEAD
#line 514 "dhcp6_parser.yy"
=======
#line 514 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 514 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 124:
<<<<<<< HEAD
<<<<<<< HEAD
#line 519 "dhcp6_parser.yy"
=======
#line 519 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 519 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 125:
<<<<<<< HEAD
<<<<<<< HEAD
#line 524 "dhcp6_parser.yy"
=======
#line 524 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 524 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 126:
<<<<<<< HEAD
<<<<<<< HEAD
#line 529 "dhcp6_parser.yy"
=======
#line 529 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 529 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 127:
<<<<<<< HEAD
<<<<<<< HEAD
#line 534 "dhcp6_parser.yy"
=======
#line 534 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 534 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 128:
<<<<<<< HEAD
<<<<<<< HEAD
#line 539 "dhcp6_parser.yy"
=======
#line 539 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 539 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1145 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
<<<<<<< HEAD
<<<<<<< HEAD
#line 544 "dhcp6_parser.yy"
=======
#line 544 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 544 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
<<<<<<< HEAD
<<<<<<< HEAD
#line 549 "dhcp6_parser.yy"
=======
#line 549 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 549 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 131:
<<<<<<< HEAD
<<<<<<< HEAD
#line 554 "dhcp6_parser.yy"
=======
#line 554 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 554 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1172 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 132:
<<<<<<< HEAD
<<<<<<< HEAD
#line 559 "dhcp6_parser.yy"
=======
#line 559 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 559 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 133:
<<<<<<< HEAD
<<<<<<< HEAD
#line 564 "dhcp6_parser.yy"
=======
#line 564 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 564 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 134:
<<<<<<< HEAD
<<<<<<< HEAD
#line 566 "dhcp6_parser.yy"
=======
#line 566 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 566 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 135:
<<<<<<< HEAD
<<<<<<< HEAD
#line 572 "dhcp6_parser.yy"
=======
#line 572 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 572 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1210 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 136:
<<<<<<< HEAD
<<<<<<< HEAD
#line 577 "dhcp6_parser.yy"
=======
#line 577 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 577 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1220 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 137:
<<<<<<< HEAD
<<<<<<< HEAD
#line 583 "dhcp6_parser.yy"
=======
#line 583 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 583 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1230 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 138:
<<<<<<< HEAD
<<<<<<< HEAD
#line 587 "dhcp6_parser.yy"
=======
#line 587 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 587 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 146:
<<<<<<< HEAD
<<<<<<< HEAD
#line 603 "dhcp6_parser.yy"
=======
#line 603 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 603 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1250 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 147:
<<<<<<< HEAD
<<<<<<< HEAD
#line 608 "dhcp6_parser.yy"
=======
#line 608 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 608 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 148:
<<<<<<< HEAD
<<<<<<< HEAD
#line 613 "dhcp6_parser.yy"
=======
#line 613 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 613 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1268 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 149:
<<<<<<< HEAD
<<<<<<< HEAD
#line 619 "dhcp6_parser.yy"
=======
#line 619 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 619 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 150:
<<<<<<< HEAD
<<<<<<< HEAD
#line 624 "dhcp6_parser.yy"
=======
#line 624 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 624 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1290 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 151:
<<<<<<< HEAD
<<<<<<< HEAD
#line 631 "dhcp6_parser.yy"
=======
#line 631 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 631 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 152:
<<<<<<< HEAD
<<<<<<< HEAD
#line 636 "dhcp6_parser.yy"
=======
#line 636 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 636 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 153:
<<<<<<< HEAD
<<<<<<< HEAD
#line 643 "dhcp6_parser.yy"
=======
#line 643 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 643 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1323 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 154:
<<<<<<< HEAD
<<<<<<< HEAD
#line 648 "dhcp6_parser.yy"
=======
#line 648 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 648 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1332 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 159:
<<<<<<< HEAD
<<<<<<< HEAD
#line 661 "dhcp6_parser.yy"
=======
#line 661 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 661 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1342 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 160:
<<<<<<< HEAD
<<<<<<< HEAD
#line 665 "dhcp6_parser.yy"
=======
#line 665 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 665 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1352 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 183:
#line 697 "dhcp6_parser.yy"
=======
  case 184:
#line 698 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 184:
#line 698 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1360 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 184:
#line 699 "dhcp6_parser.yy"
=======
  case 185:
#line 700 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 185:
#line 700 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1373 "dhcp6_parser.cc"
    break;

  case 185:
#line 704 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1379 "dhcp6_parser.cc"
    break;

  case 186:
#line 705 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1385 "dhcp6_parser.cc"
    break;

  case 187:
#line 706 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1391 "dhcp6_parser.cc"
    break;

  case 188:
#line 707 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1397 "dhcp6_parser.cc"
    break;

  case 189:
#line 710 "dhcp6_parser.yy"
=======
#line 1369 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 705 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 706 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1381 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 707 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1387 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
=======
#line 1369 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 705 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 706 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1381 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 707 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1387 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
#line 708 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 711 "dhcp6_parser.yy" // lalr1.cc:907
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 190:
#line 712 "dhcp6_parser.yy"
=======
  case 191:
#line 713 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 191:
#line 713 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 191:
#line 718 "dhcp6_parser.yy"
=======
  case 192:
#line 719 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 192:
#line 719 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1419 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 192:
#line 720 "dhcp6_parser.yy"
=======
  case 193:
#line 721 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 193:
#line 721 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 193:
#line 726 "dhcp6_parser.yy"
=======
  case 194:
#line 727 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 194:
#line 727 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1437 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 194:
#line 728 "dhcp6_parser.yy"
=======
  case 195:
#line 729 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 195:
#line 729 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 195:
#line 734 "dhcp6_parser.yy"
=======
  case 196:
#line 735 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 196:
#line 735 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 196:
#line 739 "dhcp6_parser.yy"
=======
  case 197:
#line 740 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 197:
#line 740 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 197:
#line 741 "dhcp6_parser.yy"
=======
  case 198:
#line 742 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 198:
#line 742 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 198:
#line 747 "dhcp6_parser.yy"
=======
  case 199:
#line 748 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 199:
#line 748 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 199:
#line 752 "dhcp6_parser.yy"
=======
  case 200:
#line 753 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 200:
#line 753 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 200:
#line 757 "dhcp6_parser.yy"
=======
  case 201:
#line 758 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 201:
#line 758 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1501 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 201:
#line 762 "dhcp6_parser.yy"
=======
  case 202:
#line 763 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 202:
#line 763 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 202:
#line 767 "dhcp6_parser.yy"
=======
  case 203:
#line 768 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 203:
#line 768 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1519 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 203:
#line 772 "dhcp6_parser.yy"
=======
  case 204:
#line 773 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1528 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 778 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
=======
  case 204:
#line 773 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1528 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 778 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1537 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 204:
#line 777 "dhcp6_parser.yy"
=======
  case 206:
#line 783 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 206:
#line 783 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 205:
#line 782 "dhcp6_parser.yy"
=======
  case 207:
#line 788 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 207:
#line 788 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 206:
#line 787 "dhcp6_parser.yy"
=======
  case 208:
#line 793 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 208:
#line 793 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 207:
#line 789 "dhcp6_parser.yy"
=======
  case 209:
#line 795 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 209:
#line 795 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1573 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 208:
#line 795 "dhcp6_parser.yy"
=======
  case 210:
#line 801 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 210:
#line 801 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1582 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 209:
#line 800 "dhcp6_parser.yy"
=======
  case 211:
#line 806 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 211:
#line 806 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1590 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 210:
#line 802 "dhcp6_parser.yy"
=======
  case 212:
#line 808 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 212:
#line 808 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1600 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 211:
#line 808 "dhcp6_parser.yy"
=======
  case 213:
#line 814 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 213:
#line 814 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1608 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 212:
#line 810 "dhcp6_parser.yy"
=======
  case 214:
#line 816 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 214:
#line 816 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 213:
#line 816 "dhcp6_parser.yy"
=======
  case 215:
#line 822 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 215:
#line 822 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1626 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 214:
#line 818 "dhcp6_parser.yy"
=======
  case 216:
#line 824 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 216:
#line 824 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1636 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 215:
#line 824 "dhcp6_parser.yy"
=======
  case 217:
#line 830 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 217:
#line 830 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 216:
#line 829 "dhcp6_parser.yy"
=======
  case 218:
#line 835 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 218:
#line 835 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 220:
#line 839 "dhcp6_parser.yy"
=======
  case 222:
#line 845 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 222:
#line 845 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 221:
#line 841 "dhcp6_parser.yy"
=======
  case 223:
#line 847 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 223:
#line 847 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
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
#line 1684 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 222:
#line 857 "dhcp6_parser.yy"
=======
  case 224:
#line 863 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 224:
#line 863 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1695 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 223:
#line 862 "dhcp6_parser.yy"
=======
  case 225:
#line 868 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 225:
#line 868 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1704 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 228:
#line 875 "dhcp6_parser.yy"
=======
  case 230:
#line 881 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 230:
#line 881 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1713 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 229:
#line 880 "dhcp6_parser.yy"
=======
  case 231:
#line 886 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 231:
#line 886 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 230:
#line 885 "dhcp6_parser.yy"
=======
  case 232:
#line 891 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 232:
#line 891 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 231:
#line 890 "dhcp6_parser.yy"
=======
  case 233:
#line 896 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 233:
#line 896 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1742 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 237:
#line 904 "dhcp6_parser.yy"
=======
  case 239:
#line 910 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 239:
#line 910 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 238:
#line 909 "dhcp6_parser.yy"
=======
  case 240:
#line 915 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 240:
#line 915 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1760 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 239:
#line 916 "dhcp6_parser.yy"
=======
  case 241:
#line 922 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 241:
#line 922 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 240:
#line 921 "dhcp6_parser.yy"
=======
  case 242:
#line 927 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 242:
#line 927 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1780 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 241:
#line 926 "dhcp6_parser.yy"
=======
  case 243:
#line 932 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 243:
#line 932 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 242:
#line 931 "dhcp6_parser.yy"
=======
  case 244:
#line 937 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 244:
#line 937 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 247:
#line 944 "dhcp6_parser.yy"
=======
  case 249:
#line 950 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 249:
#line 950 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1810 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 248:
#line 948 "dhcp6_parser.yy"
=======
  case 250:
#line 954 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 250:
#line 954 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1820 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 249:
#line 954 "dhcp6_parser.yy"
=======
  case 251:
#line 960 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 251:
#line 960 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1830 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 250:
#line 958 "dhcp6_parser.yy"
=======
  case 252:
#line 964 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 252:
#line 964 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1840 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 256:
#line 973 "dhcp6_parser.yy"
=======
  case 258:
#line 979 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 258:
#line 979 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1848 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 257:
#line 975 "dhcp6_parser.yy"
=======
  case 259:
#line 981 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 259:
#line 981 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1858 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 258:
#line 981 "dhcp6_parser.yy"
=======
  case 260:
#line 987 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 260:
#line 987 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1866 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 259:
#line 983 "dhcp6_parser.yy"
=======
  case 261:
#line 989 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 261:
#line 989 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1875 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 260:
#line 989 "dhcp6_parser.yy"
=======
  case 262:
#line 995 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 262:
#line 995 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1886 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 261:
#line 994 "dhcp6_parser.yy"
=======
  case 263:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 263:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 270:
#line 1012 "dhcp6_parser.yy"
=======
  case 272:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 272:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 271:
#line 1017 "dhcp6_parser.yy"
=======
  case 273:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 273:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1914 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 272:
#line 1022 "dhcp6_parser.yy"
=======
  case 274:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 274:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1923 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 273:
#line 1027 "dhcp6_parser.yy"
=======
  case 275:
#line 1033 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 275:
#line 1033 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1932 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 274:
#line 1032 "dhcp6_parser.yy"
=======
  case 276:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 276:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 275:
#line 1037 "dhcp6_parser.yy"
=======
  case 277:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 277:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1950 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 276:
#line 1045 "dhcp6_parser.yy"
=======
  case 278:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 278:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 277:
#line 1050 "dhcp6_parser.yy"
=======
  case 279:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 279:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1970 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 282:
#line 1070 "dhcp6_parser.yy"
=======
  case 284:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 284:
#line 1076 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1980 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 283:
#line 1074 "dhcp6_parser.yy"
=======
  case 285:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 285:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2006 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 284:
#line 1096 "dhcp6_parser.yy"
=======
  case 286:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 286:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2016 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 285:
#line 1100 "dhcp6_parser.yy"
=======
  case 287:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 287:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2026 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 315:
#line 1141 "dhcp6_parser.yy"
=======
  case 317:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 317:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2034 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 316:
#line 1143 "dhcp6_parser.yy"
=======
  case 318:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 318:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 317:
#line 1149 "dhcp6_parser.yy"
=======
  case 319:
#line 1155 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 319:
#line 1155 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 318:
#line 1151 "dhcp6_parser.yy"
=======
  case 320:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 320:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 319:
#line 1157 "dhcp6_parser.yy"
=======
  case 321:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 321:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2070 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 320:
#line 1159 "dhcp6_parser.yy"
=======
  case 322:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 322:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 321:
#line 1165 "dhcp6_parser.yy"
=======
  case 323:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 323:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 322:
#line 1167 "dhcp6_parser.yy"
=======
  case 324:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 324:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 323:
#line 1173 "dhcp6_parser.yy"
=======
  case 325:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 325:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 324:
#line 1178 "dhcp6_parser.yy"
=======
  case 326:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 326:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 325:
#line 1183 "dhcp6_parser.yy"
=======
  case 327:
#line 1189 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 327:
#line 1189 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 326:
#line 1185 "dhcp6_parser.yy"
=======
  case 328:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 328:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 327:
#line 1190 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2136 "dhcp6_parser.cc"
    break;

  case 328:
#line 1191 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2142 "dhcp6_parser.cc"
    break;

  case 329:
#line 1192 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2148 "dhcp6_parser.cc"
    break;

  case 330:
#line 1193 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2154 "dhcp6_parser.cc"
    break;

  case 331:
#line 1196 "dhcp6_parser.yy"
=======
  case 329:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2141 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 330:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2147 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 331:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2153 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 332:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2159 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 333:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 329:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2141 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 330:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2147 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 331:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2153 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 332:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2159 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 333:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 332:
#line 1201 "dhcp6_parser.yy"
=======
  case 334:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 334:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2177 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 333:
#line 1209 "dhcp6_parser.yy"
=======
  case 335:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 335:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 334:
#line 1214 "dhcp6_parser.yy"
=======
  case 336:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 336:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 339:
#line 1229 "dhcp6_parser.yy"
=======
  case 341:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 341:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2207 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 340:
#line 1233 "dhcp6_parser.yy"
=======
  case 342:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 342:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 367:
#line 1271 "dhcp6_parser.yy"
=======
  case 369:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 369:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 368:
#line 1276 "dhcp6_parser.yy"
=======
  case 370:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 370:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2235 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 369:
#line 1284 "dhcp6_parser.yy"
=======
  case 371:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 371:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2244 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 370:
#line 1287 "dhcp6_parser.yy"
=======
  case 372:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 372:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // parsing completed
}
#line 2252 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 375:
#line 1303 "dhcp6_parser.yy"
=======
  case 377:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 377:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 376:
#line 1307 "dhcp6_parser.yy"
=======
  case 378:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 378:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2274 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 377:
#line 1318 "dhcp6_parser.yy"
=======
  case 379:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 379:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2284 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 378:
#line 1322 "dhcp6_parser.yy"
=======
  case 380:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 380:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 394:
#line 1354 "dhcp6_parser.yy"
=======
  case 396:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 396:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2305 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 396:
#line 1361 "dhcp6_parser.yy"
=======
  case 398:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 398:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 397:
#line 1363 "dhcp6_parser.yy"
=======
  case 399:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 399:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2323 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 398:
#line 1369 "dhcp6_parser.yy"
=======
  case 400:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 400:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 399:
#line 1371 "dhcp6_parser.yy"
=======
  case 401:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 401:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2341 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 400:
#line 1377 "dhcp6_parser.yy"
=======
  case 402:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 402:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 401:
#line 1379 "dhcp6_parser.yy"
=======
  case 403:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 403:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 403:
#line 1387 "dhcp6_parser.yy"
=======
  case 405:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 405:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2367 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 404:
#line 1389 "dhcp6_parser.yy"
=======
  case 406:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 406:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 405:
#line 1395 "dhcp6_parser.yy"
=======
  case 407:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 407:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2386 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 406:
#line 1404 "dhcp6_parser.yy"
=======
  case 408:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 408:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 407:
#line 1409 "dhcp6_parser.yy"
=======
  case 409:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 409:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2406 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 412:
#line 1428 "dhcp6_parser.yy"
=======
  case 414:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 414:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 413:
#line 1432 "dhcp6_parser.yy"
=======
  case 415:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 415:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2425 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 414:
#line 1440 "dhcp6_parser.yy"
=======
  case 416:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 416:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 415:
#line 1444 "dhcp6_parser.yy"
=======
  case 417:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 417:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2444 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 430:
#line 1477 "dhcp6_parser.yy"
=======
  case 432:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 432:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 431:
#line 1479 "dhcp6_parser.yy"
=======
  case 433:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 433:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2462 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 434:
#line 1489 "dhcp6_parser.yy"
=======
  case 436:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 436:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 435:
#line 1494 "dhcp6_parser.yy"
=======
  case 437:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 437:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 436:
#line 1502 "dhcp6_parser.yy"
=======
  case 438:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 438:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 437:
#line 1507 "dhcp6_parser.yy"
=======
  case 439:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 439:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2500 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 442:
#line 1522 "dhcp6_parser.yy"
=======
  case 444:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 444:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 443:
#line 1526 "dhcp6_parser.yy"
=======
  case 445:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 445:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2520 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 444:
#line 1532 "dhcp6_parser.yy"
=======
  case 446:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 446:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 445:
#line 1536 "dhcp6_parser.yy"
=======
  case 447:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 447:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2539 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 455:
#line 1554 "dhcp6_parser.yy"
=======
  case 457:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 457:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2547 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 456:
#line 1556 "dhcp6_parser.yy"
=======
  case 458:
#line 1562 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 458:
#line 1562 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2557 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 457:
#line 1562 "dhcp6_parser.yy"
=======
  case 459:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 459:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2565 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 458:
#line 1564 "dhcp6_parser.yy"
=======
  case 460:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 460:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
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
#line 2592 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 459:
#line 1587 "dhcp6_parser.yy"
=======
  case 461:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 461:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 460:
#line 1589 "dhcp6_parser.yy"
=======
  case 462:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 462:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
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
#line 2629 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 461:
#line 1617 "dhcp6_parser.yy"
=======
  case 463:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 463:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2640 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 462:
#line 1622 "dhcp6_parser.yy"
=======
  case 464:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 464:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2649 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 467:
#line 1637 "dhcp6_parser.yy"
=======
  case 469:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 469:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 468:
#line 1641 "dhcp6_parser.yy"
=======
  case 470:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 470:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2671 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 469:
#line 1649 "dhcp6_parser.yy"
=======
  case 471:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 471:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2681 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 470:
#line 1653 "dhcp6_parser.yy"
=======
  case 472:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 472:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 484:
#line 1678 "dhcp6_parser.yy"
=======
  case 486:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 486:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 485:
#line 1680 "dhcp6_parser.yy"
=======
  case 487:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 487:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 486:
#line 1686 "dhcp6_parser.yy"
=======
  case 488:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 488:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2720 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 487:
#line 1691 "dhcp6_parser.yy"
=======
  case 489:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 489:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 488:
#line 1693 "dhcp6_parser.yy"
=======
  case 490:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 490:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2738 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 489:
#line 1699 "dhcp6_parser.yy"
=======
  case 491:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 491:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 490:
#line 1704 "dhcp6_parser.yy"
=======
  case 492:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 492:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2756 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 491:
#line 1712 "dhcp6_parser.yy"
=======
  case 493:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 493:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2767 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 492:
#line 1717 "dhcp6_parser.yy"
=======
  case 494:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 494:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 497:
#line 1730 "dhcp6_parser.yy"
=======
  case 499:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 499:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 498:
#line 1734 "dhcp6_parser.yy"
=======
  case 500:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 500:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2795 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 499:
#line 1739 "dhcp6_parser.yy"
=======
  case 501:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 501:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 500:
#line 1743 "dhcp6_parser.yy"
=======
  case 502:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 502:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2814 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 516:
#line 1770 "dhcp6_parser.yy"
=======
  case 518:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 518:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 517:
#line 1775 "dhcp6_parser.yy"
=======
  case 519:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 519:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 518:
#line 1780 "dhcp6_parser.yy"
=======
  case 520:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 520:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 519:
#line 1785 "dhcp6_parser.yy"
=======
  case 521:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 521:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2854 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 520:
#line 1790 "dhcp6_parser.yy"
=======
  case 522:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 522:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 521:
#line 1792 "dhcp6_parser.yy"
=======
  case 523:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 523:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2872 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 522:
#line 1798 "dhcp6_parser.yy"
=======
  case 524:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 524:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 523:
#line 1800 "dhcp6_parser.yy"
=======
  case 525:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 525:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 524:
#line 1806 "dhcp6_parser.yy"
=======
  case 526:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 526:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 525:
#line 1808 "dhcp6_parser.yy"
=======
  case 527:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 527:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 526:
#line 1814 "dhcp6_parser.yy"
=======
  case 528:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 528:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2916 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 527:
#line 1816 "dhcp6_parser.yy"
=======
  case 529:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 529:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2926 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 528:
#line 1822 "dhcp6_parser.yy"
=======
  case 530:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 530:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2937 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 529:
#line 1827 "dhcp6_parser.yy"
=======
  case 531:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 531:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 530:
#line 1835 "dhcp6_parser.yy"
=======
  case 532:
#line 1841 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 532:
#line 1841 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 531:
#line 1840 "dhcp6_parser.yy"
=======
  case 533:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 533:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2966 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 534:
#line 1849 "dhcp6_parser.yy"
=======
  case 536:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 536:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2974 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 535:
#line 1851 "dhcp6_parser.yy"
=======
  case 537:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 537:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2984 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 536:
#line 1860 "dhcp6_parser.yy"
=======
  case 538:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 538:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2995 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 537:
#line 1865 "dhcp6_parser.yy"
=======
  case 539:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 539:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3004 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 540:
#line 1874 "dhcp6_parser.yy"
=======
  case 542:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 542:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3014 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 541:
#line 1878 "dhcp6_parser.yy"
=======
  case 543:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 543:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3024 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 554:
#line 1903 "dhcp6_parser.yy"
=======
  case 556:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 556:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3032 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 555:
#line 1905 "dhcp6_parser.yy"
=======
  case 557:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 557:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3042 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 556:
#line 1911 "dhcp6_parser.yy"
=======
  case 558:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 558:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3051 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 557:
#line 1919 "dhcp6_parser.yy"
=======
  case 559:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 559:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3062 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 558:
#line 1924 "dhcp6_parser.yy"
=======
  case 560:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 560:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 570:
#line 1946 "dhcp6_parser.yy"
=======
  case 572:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 572:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 571:
#line 1948 "dhcp6_parser.yy"
=======
  case 573:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 573:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 572:
#line 1953 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3091 "dhcp6_parser.cc"
    break;

  case 573:
#line 1954 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3097 "dhcp6_parser.cc"
    break;

  case 574:
#line 1955 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3103 "dhcp6_parser.cc"
    break;

  case 575:
#line 1958 "dhcp6_parser.yy"
=======
  case 574:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3096 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3102 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 574:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3096 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3102 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3117 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 576:
#line 1963 "dhcp6_parser.yy"
=======
  case 578:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 578:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 577:
#line 1965 "dhcp6_parser.yy"
=======
  case 579:
#line 1971 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 579:
#line 1971 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 578:
#line 1971 "dhcp6_parser.yy"
=======
  case 580:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 580:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 579:
#line 1976 "dhcp6_parser.yy"
=======
  case 581:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 581:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3153 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 580:
#line 1983 "dhcp6_parser.yy"
=======
  case 582:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 582:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3162 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 581:
#line 1990 "dhcp6_parser.yy"
=======
  case 583:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 583:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3173 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 582:
#line 1995 "dhcp6_parser.yy"
=======
  case 584:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 584:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3182 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 590:
#line 2011 "dhcp6_parser.yy"
=======
  case 592:
#line 2017 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 592:
#line 2017 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3190 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 591:
#line 2013 "dhcp6_parser.yy"
=======
  case 593:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 593:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3200 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 592:
#line 2019 "dhcp6_parser.yy"
=======
  case 594:
#line 2025 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 594:
#line 2025 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3208 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 593:
#line 2021 "dhcp6_parser.yy"
=======
  case 595:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 595:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 594:
#line 2029 "dhcp6_parser.yy"
=======
  case 596:
#line 2035 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 596:
#line 2035 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3226 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 595:
#line 2031 "dhcp6_parser.yy"
=======
  case 597:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 597:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
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

    // queue-enable is mandatory
    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
     }

    // if queue-type is supplied make sure it's a string
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
#line 3266 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 596:
#line 2069 "dhcp6_parser.yy"
=======
  case 598:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 598:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3277 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 597:
#line 2074 "dhcp6_parser.yy"
=======
  case 599:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 599:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3288 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 598:
#line 2081 "dhcp6_parser.yy"
=======
  case 600:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 600:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3298 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 599:
#line 2085 "dhcp6_parser.yy"
=======
  case 601:
#line 2091 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 601:
#line 2091 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3308 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 620:
#line 2115 "dhcp6_parser.yy"
=======
  case 622:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 622:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3317 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 621:
#line 2120 "dhcp6_parser.yy"
=======
  case 623:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 623:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3325 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 622:
#line 2122 "dhcp6_parser.yy"
=======
  case 624:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 624:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3335 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 623:
#line 2128 "dhcp6_parser.yy"
=======
  case 625:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 625:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3343 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 624:
#line 2130 "dhcp6_parser.yy"
=======
  case 626:
#line 2136 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 626:
#line 2136 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3353 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 625:
#line 2136 "dhcp6_parser.yy"
=======
  case 627:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 627:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3362 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 626:
#line 2141 "dhcp6_parser.yy"
=======
  case 628:
#line 2147 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 628:
#line 2147 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3370 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 627:
#line 2143 "dhcp6_parser.yy"
=======
  case 629:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 629:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3380 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 628:
#line 2149 "dhcp6_parser.yy"
=======
  case 630:
#line 2155 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 630:
#line 2155 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3389 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 629:
#line 2154 "dhcp6_parser.yy"
=======
  case 631:
#line 2160 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 631:
#line 2160 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3398 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 630:
#line 2159 "dhcp6_parser.yy"
=======
  case 632:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 632:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3406 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 631:
#line 2161 "dhcp6_parser.yy"
=======
  case 633:
#line 2167 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 633:
#line 2167 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3415 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 632:
#line 2167 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3416 "dhcp6_parser.cc"
    break;

  case 633:
#line 2168 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3422 "dhcp6_parser.cc"
    break;

  case 634:
#line 2171 "dhcp6_parser.yy"
=======
  case 634:
#line 2173 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3421 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2174 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3427 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 634:
#line 2173 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3421 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2174 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3427 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3435 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 635:
#line 2173 "dhcp6_parser.yy"
=======
  case 637:
#line 2179 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 637:
#line 2179 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 636:
#line 2179 "dhcp6_parser.yy"
=======
  case 638:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 638:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3454 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 637:
#line 2184 "dhcp6_parser.yy"
=======
  case 639:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 639:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3463 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 638:
#line 2189 "dhcp6_parser.yy"
=======
  case 640:
#line 2195 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 640:
#line 2195 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3471 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 639:
#line 2191 "dhcp6_parser.yy"
=======
  case 641:
#line 2197 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 641:
#line 2197 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3480 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 640:
#line 2197 "dhcp6_parser.yy"
=======
  case 642:
#line 2203 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 642:
#line 2203 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3488 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 641:
#line 2200 "dhcp6_parser.yy"
=======
  case 643:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 643:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3496 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 642:
#line 2203 "dhcp6_parser.yy"
=======
  case 644:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 644:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3504 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 643:
#line 2206 "dhcp6_parser.yy"
=======
  case 645:
#line 2212 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 645:
#line 2212 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3512 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 644:
#line 2209 "dhcp6_parser.yy"
=======
  case 646:
#line 2215 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 646:
#line 2215 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3521 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 645:
#line 2215 "dhcp6_parser.yy"
=======
  case 647:
#line 2221 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 647:
#line 2221 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3529 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 646:
#line 2217 "dhcp6_parser.yy"
=======
  case 648:
#line 2223 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 648:
#line 2223 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3539 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 647:
#line 2223 "dhcp6_parser.yy"
=======
  case 649:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 649:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3547 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 648:
#line 2225 "dhcp6_parser.yy"
=======
  case 650:
#line 2231 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 650:
#line 2231 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3557 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 649:
#line 2231 "dhcp6_parser.yy"
=======
  case 651:
#line 2237 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 651:
#line 2237 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3565 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 650:
#line 2233 "dhcp6_parser.yy"
=======
  case 652:
#line 2239 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 652:
#line 2239 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3575 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 651:
#line 2241 "dhcp6_parser.yy"
=======
  case 653:
#line 2247 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 653:
#line 2247 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3583 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 652:
#line 2243 "dhcp6_parser.yy"
=======
  case 654:
#line 2249 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 654:
#line 2249 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3592 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 653:
#line 2248 "dhcp6_parser.yy"
=======
  case 655:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 655:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3600 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 654:
#line 2250 "dhcp6_parser.yy"
=======
  case 656:
#line 2256 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 656:
#line 2256 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3609 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 655:
#line 2255 "dhcp6_parser.yy"
=======
  case 657:
#line 2261 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 657:
#line 2261 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3617 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 656:
#line 2257 "dhcp6_parser.yy"
=======
  case 658:
#line 2263 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 658:
#line 2263 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3626 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 657:
#line 2264 "dhcp6_parser.yy"
=======
  case 659:
#line 2270 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 659:
#line 2270 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3637 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 658:
#line 2269 "dhcp6_parser.yy"
=======
  case 660:
#line 2275 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 660:
#line 2275 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3647 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 659:
#line 2275 "dhcp6_parser.yy"
=======
  case 661:
#line 2281 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 661:
#line 2281 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3657 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 660:
#line 2279 "dhcp6_parser.yy"
=======
  case 662:
#line 2285 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 662:
#line 2285 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // No config_control params are required
    // parsing completed
}
#line 3666 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 665:
#line 2294 "dhcp6_parser.yy"
=======
  case 667:
#line 2300 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 667:
#line 2300 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3677 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 666:
#line 2299 "dhcp6_parser.yy"
=======
  case 668:
#line 2305 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 668:
#line 2305 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3686 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 667:
#line 2304 "dhcp6_parser.yy"
=======
  case 669:
#line 2310 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 669:
#line 2310 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3695 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 668:
#line 2314 "dhcp6_parser.yy"
=======
  case 670:
#line 2320 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 670:
#line 2320 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3706 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 669:
#line 2319 "dhcp6_parser.yy"
=======
  case 671:
#line 2325 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 671:
#line 2325 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3715 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 670:
#line 2324 "dhcp6_parser.yy"
=======
  case 672:
#line 2330 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 672:
#line 2330 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3725 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 671:
#line 2328 "dhcp6_parser.yy"
=======
  case 673:
#line 2334 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 673:
#line 2334 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    // parsing completed
}
#line 3733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 675:
#line 2344 "dhcp6_parser.yy"
=======
  case 677:
#line 2350 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 677:
#line 2350 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3744 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 676:
#line 2349 "dhcp6_parser.yy"
=======
  case 678:
#line 2355 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 678:
#line 2355 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3753 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 679:
#line 2361 "dhcp6_parser.yy"
=======
  case 681:
#line 2367 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 681:
#line 2367 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 680:
#line 2365 "dhcp6_parser.yy"
=======
  case 682:
#line 2371 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 682:
#line 2371 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
}
#line 3771 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 690:
#line 2382 "dhcp6_parser.yy"
=======
  case 692:
#line 2388 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 692:
#line 2388 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3780 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 691:
#line 2387 "dhcp6_parser.yy"
=======
  case 693:
#line 2393 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 693:
#line 2393 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3788 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 692:
#line 2389 "dhcp6_parser.yy"
=======
  case 694:
#line 2395 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 694:
#line 2395 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3798 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 693:
#line 2395 "dhcp6_parser.yy"
=======
  case 695:
#line 2401 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 695:
#line 2401 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3809 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 694:
#line 2400 "dhcp6_parser.yy"
=======
  case 696:
#line 2406 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 696:
#line 2406 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3818 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 697:
#line 2409 "dhcp6_parser.yy"
=======
  case 699:
#line 2415 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 699:
#line 2415 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3828 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 698:
#line 2413 "dhcp6_parser.yy"
=======
  case 700:
#line 2419 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 700:
#line 2419 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.stack_.pop_back();
}
#line 3836 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 706:
#line 2428 "dhcp6_parser.yy"
=======
  case 707:
#line 2433 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 707:
#line 2433 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3844 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 707:
#line 2430 "dhcp6_parser.yy"
=======
  case 708:
#line 2435 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 708:
#line 2435 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3854 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 708:
#line 2436 "dhcp6_parser.yy"
=======
  case 709:
#line 2441 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 709:
#line 2441 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3863 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 709:
#line 2441 "dhcp6_parser.yy"
=======
  case 710:
#line 2446 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 710:
#line 2446 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3872 "dhcp6_parser.cc" // lalr1.cc:907
    break;

<<<<<<< HEAD
<<<<<<< HEAD
  case 710:
#line 2446 "dhcp6_parser.yy"
=======
  case 711:
#line 2451 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
  case 711:
#line 2451 "dhcp6_parser.yy" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3881 "dhcp6_parser.cc" // lalr1.cc:907
<<<<<<< HEAD
    break;

  case 711:
#line 2451 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3884 "dhcp6_parser.cc"
    break;

  case 712:
#line 2453 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3894 "dhcp6_parser.cc"
    break;


<<<<<<< HEAD
#line 3898 "dhcp6_parser.cc"

=======
#line 3885 "dhcp6_parser.cc" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
    break;


#line 3885 "dhcp6_parser.cc" // lalr1.cc:907
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short Dhcp6Parser::yypact_ninf_ = -878;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
<<<<<<< HEAD
<<<<<<< HEAD
     480,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    45,    70,    59,    69,
      78,   131,   133,   135,   144,   146,   173,   184,   197,   206,
     207,   219,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,    70,  -139,    30,    79,    41,   280,    81,   164,
     172,    39,    43,   444,   -28,   464,  -103,    93,  -875,   236,
     224,   239,   242,   255,  -875,  -875,  -875,  -875,  -875,   274,
    -875,    75,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   299,   301,   308,   317,   318,   339,
     341,   345,   347,   349,   351,   361,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   362,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,    85,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   381,  -875,   113,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   383,
     391,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   138,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   141,  -875,
    -875,  -875,  -875,  -875,   401,  -875,   405,   415,  -875,  -875,
    -875,  -875,  -875,  -875,   169,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   359,   421,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   418,  -875,  -875,   423,  -875,  -875,  -875,   425,
    -875,  -875,   422,   438,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,   439,   440,  -875,
    -875,  -875,  -875,   443,   455,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,   185,  -875,  -875,
    -875,   462,  -875,  -875,   463,  -875,   466,   467,  -875,  -875,
     473,   486,  -875,  -875,  -875,  -875,  -875,   199,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   200,  -875,  -875,  -875,   487,   212,
    -875,  -875,  -875,  -875,    70,    70,  -875,   311,   492,   493,
     494,   495,   496,  -875,    30,  -875,   497,   498,   505,   506,
     507,   510,   340,   342,   343,   346,   350,   352,   353,   354,
     337,   348,   355,   360,   513,   520,   523,   524,   526,   534,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   372,   552,   554,   555,   556,   557,   558,    79,  -875,
     559,   380,    41,  -875,   562,   563,   564,   565,   566,   389,
     386,   569,   573,   574,   280,  -875,   575,    81,  -875,   576,
     398,   578,   400,   403,   164,  -875,   580,   583,   587,   590,
     591,   608,   610,  -875,   172,  -875,   615,   616,   441,   617,
     618,   619,   442,  -875,    43,   621,   445,   446,  -875,   444,
     624,   625,    65,  -875,   447,   629,   632,   456,   634,   457,
     458,   638,   639,   459,   460,   658,   659,   464,  -875,  -103,
    -875,   661,   483,    93,  -875,  -875,  -875,   663,   662,   664,
      70,    70,    70,  -875,   488,   665,   666,   667,   668,   671,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   499,   672,   673,   674,   675,   501,   363,   680,
     681,   682,   683,   684,   685,   687,   688,   689,   690,  -875,
     691,   675,   692,   512,   518,   696,  -875,   697,  -875,  -875,
     698,   699,   525,   527,   528,  -875,  -875,   697,   529,   701,
    -875,   530,  -875,   531,  -875,   532,  -875,  -875,  -875,   697,
     697,   697,   533,   535,   536,   537,  -875,   538,   539,  -875,
     551,   553,   560,  -875,  -875,   561,  -875,  -875,  -875,   567,
      70,  -875,  -875,   568,   570,  -875,   571,  -875,  -875,    36,
     521,  -875,  -875,   159,   572,  -875,  -875,   700,  -875,  -875,
      70,    79,  -103,  -875,  -875,  -875,  -875,    93,    41,   260,
     260,   709,  -875,   715,   716,   717,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   718,   -37,    70,   -33,   596,   719,
     720,   721,   257,   122,    35,  -875,   464,  -875,  -875,   722,
    -875,  -875,   723,   724,  -875,  -875,  -875,  -875,  -875,   -61,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   709,  -875,   221,   225,   248,   261,  -875,  -875,
    -875,  -875,   676,   702,   728,   730,   732,  -875,   733,   734,
    -875,  -875,  -875,   735,   736,   737,  -875,   262,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   276,  -875,
     738,   742,  -875,  -875,   740,   744,  -875,  -875,   745,   752,
    -875,  -875,   750,   754,  -875,  -875,   753,   755,  -875,  -875,
    -875,    83,  -875,  -875,  -875,   756,  -875,  -875,  -875,    97,
    -875,  -875,  -875,  -875,   310,  -875,  -875,  -875,   186,  -875,
    -875,   757,   758,  -875,  -875,   759,   761,  -875,   762,   763,
     764,   765,   766,   767,   331,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   768,   769,   770,  -875,  -875,  -875,
    -875,   332,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   333,  -875,  -875,  -875,   334,  -875,   254,
    -875,   593,  -875,   771,   773,  -875,  -875,   772,   776,  -875,
    -875,  -875,   774,  -875,   775,  -875,  -875,  -875,  -875,   779,
     780,   781,   782,   577,   595,   604,   603,   606,   786,   609,
     611,   787,   789,   791,   613,   614,   620,   260,  -875,  -875,
     260,  -875,   709,   280,  -875,   715,    43,  -875,   716,   444,
    -875,   717,   436,  -875,   718,   -37,  -875,  -875,   -33,  -875,
     794,   596,  -875,    89,   719,  -875,   172,  -875,   720,   -28,
    -875,   721,   623,   626,   627,   628,   630,   631,   257,  -875,
     795,   796,   633,   635,   637,   122,  -875,   797,   798,    35,
    -875,  -875,   124,   722,  -875,  -875,   801,   800,    81,  -875,
     723,   164,  -875,   724,   804,  -875,  -875,   451,   622,   642,
     644,  -875,  -875,  -875,  -875,  -875,   645,  -875,  -875,   647,
     652,   654,  -875,  -875,  -875,  -875,   344,  -875,   373,  -875,
     807,  -875,   809,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   374,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   655,  -875,  -875,   808,  -875,  -875,  -875,
    -875,  -875,   813,   835,  -875,  -875,  -875,  -875,  -875,   833,
    -875,   385,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
      40,   669,  -875,  -875,  -875,  -875,   670,   677,  -875,  -875,
     844,  -875,  -875,  -875,  -875,  -875,   394,  -875,  -875,  -875,
    -875,  -875,  -875,   712,   395,  -875,   404,  -875,   725,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,   436,  -875,  -875,   846,   714,
    -875,    89,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,   850,   686,   868,   124,  -875,  -875,  -875,  -875,  -875,
    -875,   741,  -875,  -875,   743,  -875,   746,  -875,  -875,   876,
    -875,  -875,   388,  -875,   154,   876,  -875,  -875,   897,   898,
     900,  -875,   414,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     910,   731,   747,   748,   911,   154,  -875,   751,  -875,  -875,
    -875,   760,  -875,  -875,  -875
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
     427,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,    40,    70,    59,    63,
      65,    69,    79,    87,   101,   133,   144,   182,   185,   189,
     200,   219,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,    70,   -19,    29,    78,    41,   435,    80,   168,
     171,    58,    43,   460,   -65,   485,    91,   161,  -878,   244,
     254,   285,   307,   354,  -878,  -878,  -878,  -878,  -878,   355,
    -878,    99,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   363,   367,   377,   382,   383,   384,
     389,   391,   393,   394,   399,   401,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,   403,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   156,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,   405,  -878,   169,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   408,
     413,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,   180,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   183,  -878,
    -878,  -878,  -878,  -878,   415,  -878,   418,   420,  -878,  -878,
    -878,  -878,  -878,  -878,   195,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   350,   423,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   421,  -878,  -878,   426,  -878,  -878,  -878,   444,
    -878,  -878,   441,   424,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   446,   447,  -878,
    -878,  -878,  -878,   450,   459,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   205,  -878,  -878,
    -878,   462,  -878,  -878,   463,  -878,   466,   467,  -878,  -878,
     469,   470,  -878,  -878,  -878,  -878,  -878,   213,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   221,  -878,  -878,  -878,   471,   225,
    -878,  -878,  -878,  -878,    70,    70,  -878,   294,   486,   487,
     488,   489,   491,  -878,    29,  -878,   492,   493,   494,   495,
     496,   497,   319,   320,   322,   328,   343,   344,   345,   346,
     347,   349,   352,   356,   503,   504,   505,   506,   526,   536,
     537,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   370,   550,   551,   552,   554,   555,   556,    78,  -878,
     557,   380,    41,  -878,   562,   563,   564,   565,   566,   388,
     387,   569,   573,   574,   435,  -878,   575,    80,  -878,   576,
     398,   578,   400,   404,   168,  -878,   580,   582,   587,   608,
     610,   612,   627,  -878,   171,  -878,   628,   629,   453,   636,
     637,   639,   461,  -878,    43,   640,   464,   465,  -878,   460,
     641,   643,   104,  -878,   468,   644,   647,   472,   648,   473,
     474,   650,   654,   475,   476,   655,   658,   485,  -878,    91,
    -878,   659,   482,   161,  -878,  -878,  -878,   662,   661,   663,
      70,    70,    70,  -878,   490,   664,   666,   667,   668,   671,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   498,   672,   673,   674,   675,   499,   151,   678,
     680,   681,   682,   683,   684,   686,   687,   688,   689,  -878,
     690,   675,   691,   511,   512,   694,  -878,   695,  -878,  -878,
     696,   697,   521,   522,   523,  -878,  -878,   695,   524,   700,
    -878,   527,  -878,   528,  -878,   529,  -878,  -878,  -878,   695,
     695,   695,   530,   531,   532,   533,  -878,   534,   535,  -878,
     538,   549,   553,  -878,  -878,   558,  -878,  -878,  -878,   559,
      70,  -878,  -878,   560,   561,  -878,   567,  -878,  -878,   122,
     570,  -878,  -878,    50,   568,  -878,  -878,   703,  -878,  -878,
      70,    78,    91,  -878,  -878,  -878,  -878,   161,    41,   265,
     265,   712,  -878,   714,   715,   716,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   717,   -38,    70,   155,   594,   718,
     719,   720,   196,    22,    36,  -878,   485,  -878,  -878,   721,
    -878,  -878,   722,   723,  -878,  -878,  -878,  -878,  -878,   -23,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   712,  -878,   248,   275,   276,   279,  -878,  -878,
    -878,  -878,   665,   728,   729,   730,   732,  -878,   733,   734,
    -878,  -878,  -878,   735,   740,   741,   742,  -878,   282,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     313,  -878,   745,   744,  -878,  -878,   746,   750,  -878,  -878,
     748,   752,  -878,  -878,   751,   753,  -878,  -878,   754,   755,
    -878,  -878,  -878,    85,  -878,  -878,  -878,   756,  -878,  -878,
    -878,    98,  -878,  -878,  -878,  -878,   314,  -878,  -878,  -878,
     109,  -878,  -878,   757,   758,  -878,  -878,   759,   761,  -878,
     762,   763,   764,   765,   766,   767,   315,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,   768,   769,   770,  -878,
    -878,  -878,  -878,   316,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   323,  -878,  -878,  -878,   324,
    -878,   135,  -878,   577,  -878,   771,   772,  -878,  -878,   773,
     775,  -878,  -878,  -878,   774,  -878,   777,  -878,  -878,  -878,
    -878,   776,   780,   781,   782,   593,   596,   604,   603,   606,
     786,   609,   611,   787,   789,   791,   613,   614,   615,   616,
     265,  -878,  -878,   265,  -878,   712,   435,  -878,   714,    43,
    -878,   715,   460,  -878,   716,   295,  -878,   717,   -38,  -878,
    -878,   155,  -878,   794,   594,  -878,    83,   718,  -878,   171,
    -878,   719,   -65,  -878,   720,   618,   619,   620,   621,   622,
     623,   196,  -878,   803,   804,   626,   630,   631,    22,  -878,
     806,   807,    36,  -878,  -878,   203,   721,  -878,  -878,   809,
     813,    80,  -878,   722,   168,  -878,   723,   808,  -878,  -878,
     419,   635,   638,   642,  -878,  -878,  -878,  -878,  -878,   645,
    -878,  -878,   657,   669,   693,  -878,  -878,  -878,  -878,  -878,
     325,  -878,   326,  -878,   810,  -878,   811,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   327,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   704,  -878,  -878,
     817,  -878,  -878,  -878,  -878,  -878,   815,   826,  -878,  -878,
    -878,  -878,  -878,   822,  -878,   348,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   216,   725,  -878,  -878,  -878,  -878,
     736,   737,  -878,  -878,   828,  -878,  -878,  -878,  -878,  -878,
     358,  -878,  -878,  -878,  -878,  -878,  -878,   739,   362,  -878,
     366,  -878,   747,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   295,
    -878,  -878,   833,   656,  -878,    83,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   836,   670,   840,   203,  -878,
    -878,  -878,  -878,  -878,  -878,   749,  -878,  -878,   743,  -878,
     760,  -878,  -878,   847,  -878,  -878,   179,  -878,    -9,   847,
    -878,  -878,   851,   853,   858,   374,  -878,  -878,  -878,  -878,
    -878,  -878,   868,   778,   727,   779,    -9,  -878,   783,  -878,
    -878,  -878,  -878,  -878
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   137,     9,
     286,    11,   446,    13,   471,    15,   501,    17,   371,    19,
     379,    21,   416,    23,   251,    25,   600,    27,   672,    29,
     661,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     503,     0,   381,   418,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   670,   653,   655,   657,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   119,   659,
     135,   149,   151,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   278,   369,   408,
     459,   461,   327,   335,   224,   241,   232,   217,   538,   493,
     243,   262,   559,     0,   583,   596,   598,   649,   651,   677,
     118,     0,    74,    76,    77,    78,    79,    80,    81,    82,
      83,    84,   112,   113,   114,    85,   110,    88,    89,    90,
      91,   107,    92,    94,    93,    98,    99,    86,   111,    87,
      96,    97,   105,   106,   108,    95,   100,   101,   102,   103,
     104,   116,   117,   109,   115,   146,     0,   145,     0,   139,
     141,   142,   143,   144,   438,   463,   317,   319,   321,     0,
       0,   325,   323,   532,   316,   290,   291,   292,   293,   294,
     295,   296,   297,   313,   314,   315,     0,   288,   301,   302,
     303,   306,   307,   309,   304,   305,   298,   299,   311,   312,
     300,   308,   310,   457,   456,   452,   453,   451,     0,   448,
     450,   454,   455,   486,     0,   489,     0,     0,   485,   479,
     480,   478,   483,   484,     0,   473,   475,   476,   481,   482,
     477,   530,   518,   520,   522,   524,   526,   528,   517,   514,
     515,   516,     0,   504,   505,   509,   510,   507,   511,   512,
     513,   508,     0,   398,   197,     0,   402,   400,   405,     0,
     394,   395,     0,   382,   383,   385,   397,   386,   387,   388,
     404,   389,   390,   391,   392,   393,   432,     0,     0,   430,
     431,   434,   435,     0,   419,   420,   422,   423,   424,   425,
     426,   427,   428,   429,   258,   260,   255,     0,   253,   256,
     257,     0,   623,   625,     0,   628,     0,     0,   632,   636,
       0,     0,   640,   647,   621,   619,   620,     0,   602,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,     0,   674,   676,   667,     0,     0,
     663,   665,   666,    48,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    59,     0,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,   138,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   287,     0,     0,   447,     0,
       0,     0,     0,     0,     0,   472,     0,     0,     0,     0,
       0,     0,     0,   502,     0,   372,     0,     0,     0,     0,
       0,     0,     0,   380,     0,     0,     0,     0,   417,     0,
       0,     0,     0,   252,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   601,     0,
     673,     0,     0,     0,   662,    52,    45,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   582,
       0,     0,     0,     0,     0,     0,    75,     0,   148,   140,
       0,     0,     0,     0,     0,   333,   334,     0,     0,     0,
     289,     0,   449,     0,   488,     0,   491,   492,   474,     0,
       0,     0,     0,     0,     0,     0,   506,     0,     0,   396,
       0,     0,     0,   407,   384,     0,   436,   437,   421,     0,
       0,   254,   622,     0,     0,   627,     0,   630,   631,     0,
       0,   638,   639,     0,     0,   603,   675,     0,   669,   664,
       0,     0,     0,   654,   656,   658,   120,     0,     0,     0,
       0,   155,   134,   280,   373,   410,    42,   460,   462,   329,
     330,   331,   332,   328,   337,     0,    49,     0,     0,     0,
     495,   245,     0,     0,     0,   597,     0,   650,   652,     0,
      53,   147,   440,   465,   318,   320,   322,   326,   324,     0,
     458,   487,   490,   531,   519,   521,   523,   525,   527,   529,
     399,   198,   403,   401,   406,   433,   259,   261,   624,   626,
     629,   634,   635,   633,   637,   642,   643,   644,   645,   646,
     641,   648,   155,    46,     0,     0,     0,     0,   184,   190,
     192,   194,     0,     0,     0,     0,     0,   208,     0,     0,
     211,   213,   215,     0,     0,     0,     0,   183,     0,   161,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     175,   182,   176,   177,   178,   173,   174,   179,   180,   181,
       0,   159,     0,   156,   157,   284,     0,   281,   282,   377,
       0,   374,   375,   414,     0,   411,   412,   341,     0,   338,
     339,   230,   231,     0,   226,   228,   229,     0,   239,   240,
     236,     0,   234,   237,   238,   222,     0,   219,   221,   542,
       0,   540,   499,     0,   496,   497,   249,     0,   246,   247,
       0,     0,     0,     0,     0,     0,     0,   264,   266,   267,
     268,   269,   270,   271,   572,   578,     0,     0,     0,   571,
     568,   569,   570,     0,   561,   563,   566,   564,   565,   567,
     592,   594,   591,   589,   590,     0,   585,   587,   588,     0,
     681,     0,   679,    55,   444,     0,   441,   442,   469,     0,
     466,   467,   536,   535,     0,   534,     0,    71,   671,   660,
     136,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
<<<<<<< HEAD
<<<<<<< HEAD
       0,     0,     0,     0,     0,     0,     0,     0,   150,   152,
       0,   154,     0,     0,   277,     0,   379,   368,     0,   416,
     407,     0,     0,   334,     0,     0,   223,   240,     0,   231,
       0,     0,   216,   542,     0,   537,   501,   492,     0,     0,
     242,     0,     0,     0,     0,     0,     0,     0,     0,   261,
       0,     0,     0,     0,     0,     0,   558,     0,     0,     0,
     582,   597,     0,     0,   676,    57,     0,    56,     0,   437,
       0,     0,   462,     0,     0,   531,   666,     0,     0,     0,
       0,   195,   198,   199,   200,   201,     0,   208,   202,     0,
       0,     0,   203,   204,   205,   162,     0,   158,     0,   281,
       0,   374,     0,   411,   366,   354,   355,   356,   358,   359,
     360,   347,   348,   363,   364,   365,   343,   344,   345,   346,
     352,   353,   351,   357,     0,   341,   349,   361,   362,   350,
     338,   225,   233,     0,   218,   554,     0,   552,   553,   549,
     550,   551,     0,   543,   544,   546,   547,   548,   539,     0,
     496,     0,   246,   270,   271,   272,   273,   274,   275,   263,
       0,     0,   575,   578,   579,   560,     0,     0,   584,   693,
       0,   691,   689,   683,   687,   688,     0,   681,   685,   686,
     684,   678,    54,     0,     0,   441,     0,   466,     0,   185,
     186,   187,   188,   184,   190,   192,   194,   207,   210,   212,
     214,   160,   283,   376,   413,     0,   340,   221,     0,     0,
     541,     0,   498,   248,   572,   573,   574,   571,   577,   591,
     593,     0,     0,     0,     0,   680,    58,   443,   468,   535,
     342,     0,   556,   545,     0,   690,     0,   682,   555,     0,
     692,   697,     0,   695,     0,     0,   694,   706,     0,     0,
       0,   711,     0,   699,   701,   702,   703,   704,   705,   696,
       0,     0,     0,     0,     0,     0,   698,     0,   708,   709,
     710,     0,   700,   707,   712
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
       0,   150,   152,     0,   154,     0,     0,   279,     0,   381,
     370,     0,   418,   409,     0,     0,   336,     0,     0,   225,
     242,     0,   233,     0,     0,   218,   544,     0,   539,   503,
     494,     0,     0,   244,     0,     0,     0,     0,     0,     0,
       0,     0,   263,     0,     0,     0,     0,     0,     0,   560,
       0,     0,     0,   584,   599,     0,     0,   678,    57,     0,
      56,     0,   439,     0,     0,   464,     0,     0,   533,   668,
       0,     0,     0,     0,   196,   199,   200,   201,   202,     0,
     210,   203,     0,     0,     0,   205,   206,   207,   204,   162,
       0,   158,     0,   283,     0,   376,     0,   413,   368,   356,
     357,   358,   360,   361,   362,   349,   350,   365,   366,   367,
     345,   346,   347,   348,   354,   355,   353,   359,     0,   343,
     351,   363,   364,   352,   340,   227,   235,     0,   220,   556,
       0,   554,   555,   551,   552,   553,     0,   545,   546,   548,
     549,   550,   541,     0,   498,     0,   248,   272,   273,   274,
     275,   276,   277,   265,     0,     0,   577,   580,   581,   562,
       0,     0,   586,   695,     0,   693,   691,   685,   689,   690,
       0,   683,   687,   688,   686,   680,    54,     0,     0,   443,
       0,   468,     0,   186,   187,   188,   189,   185,   191,   193,
     195,   209,   212,   214,   216,   160,   285,   378,   415,     0,
     342,   223,     0,     0,   543,     0,   500,   250,   574,   575,
     576,   573,   579,   593,   595,     0,     0,     0,     0,   682,
      58,   445,   470,   537,   344,     0,   558,   547,     0,   692,
       0,   684,   557,     0,   694,   699,     0,   697,     0,     0,
     696,   707,     0,     0,     0,     0,   701,   703,   704,   705,
     706,   698,     0,     0,     0,     0,     0,   700,     0,   709,
     710,   711,   702,   708
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
<<<<<<< HEAD
<<<<<<< HEAD
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,    54,  -875,  -502,
    -875,   134,  -875,  -875,  -875,  -875,   268,  -875,  -476,  -875,
    -875,  -875,   -74,  -875,  -875,  -875,   579,  -875,  -875,  -875,
    -875,   287,   489,  -875,  -875,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,     3,     7,    10,    15,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   288,   490,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   213,  -875,    37,  -875,  -622,    47,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     -21,  -875,  -650,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,    24,  -875,  -875,  -875,  -875,  -875,    31,  -641,
    -875,  -875,  -875,  -875,    33,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,    17,  -875,  -875,  -875,    20,   452,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    19,  -875,  -875,  -875,
    -875,  -875,  -875,  -874,  -875,  -875,  -875,    50,  -875,  -875,
    -875,    55,   500,  -875,  -875,  -869,  -875,  -867,  -875,   -11,
    -875,    -5,  -875,    18,  -875,  -875,  -875,  -866,  -875,  -875,
    -875,  -875,    46,  -875,  -875,  -136,   870,  -875,  -875,  -875,
    -875,  -875,    57,  -875,  -875,  -875,    56,  -875,   469,  -875,
     -69,  -875,  -875,  -875,  -875,  -875,   -66,  -875,  -875,  -875,
    -875,  -875,   -58,  -875,  -875,  -875,    58,  -875,  -875,  -875,
      61,  -875,   468,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,     6,  -875,  -875,  -875,    13,   508,
    -875,  -875,   -53,  -875,   -29,  -875,  -875,  -875,  -875,  -875,
       5,  -875,  -875,  -875,    11,   502,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   -62,  -875,  -875,  -875,    49,  -875,  -875,
    -875,    48,  -875,   503,   284,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -864,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    60,  -875,  -875,  -875,
    -123,  -875,  -875,  -875,  -875,  -875,  -875,  -875,    34,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,    32,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   304,   465,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   -73,  -875,   -51,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     338,   470,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   356,
     471,   -44,  -875,  -875,    38,  -875,  -875,  -128,  -875,  -875,
    -875,  -875,  -875,  -875,  -147,  -875,  -875,  -166,  -875,  -875,
    -875,  -875,  -875,  -875,  -875
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,    54,  -878,  -502,
    -878,   336,  -878,  -878,  -878,  -878,   246,  -878,  -508,  -878,
    -878,  -878,   -74,  -878,  -878,  -878,   510,  -878,  -878,  -878,
    -878,   274,   479,  -878,  -878,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,     3,     7,    10,    15,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,   288,   502,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   215,  -878,    33,  -878,  -622,    42,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     -21,  -878,  -650,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,    16,  -878,  -878,  -878,  -878,  -878,    25,
    -641,  -878,  -878,  -878,  -878,    23,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,    11,  -878,  -878,  -878,    14,   445,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,     8,  -878,  -878,
    -878,  -878,  -878,  -878,  -877,  -878,  -878,  -878,    47,  -878,
    -878,  -878,    45,   484,  -878,  -878,  -872,  -878,  -870,  -878,
     -11,  -878,    -5,  -878,    18,  -878,  -878,  -878,  -869,  -878,
    -878,  -878,  -878,    44,  -878,  -878,  -142,   867,  -878,  -878,
    -878,  -878,  -878,    49,  -878,  -878,  -878,    53,  -878,   477,
    -878,   -69,  -878,  -878,  -878,  -878,  -878,   -66,  -878,  -878,
    -878,  -878,  -878,   -58,  -878,  -878,  -878,    51,  -878,  -878,
    -878,    52,  -878,   478,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,     0,  -878,  -878,  -878,     5,
     500,  -878,  -878,   -53,  -878,   -29,  -878,  -878,  -878,  -878,
    -878,     2,  -878,  -878,  -878,     6,   507,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   -62,  -878,  -878,  -878,    38,  -878,
    -878,  -878,    55,  -878,   501,   287,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -867,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,    56,  -878,  -878,
    -878,  -131,  -878,  -878,  -878,  -878,  -878,  -878,  -878,    30,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,    27,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,   304,   480,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   -73,  -878,   -51,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   335,   481,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     351,   483,   -44,  -878,  -878,    31,  -878,  -878,  -132,  -878,
    -878,  -878,  -878,  -878,  -878,  -151,  -878,  -878,  -167,  -878,
    -878,  -878,  -878,  -878
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   647,    92,    93,    43,    72,    89,    90,   671,   853,
     949,   950,   737,    45,    74,   101,   102,   103,   388,    47,
      75,   151,   152,   153,   396,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   414,   167,
     398,    49,    76,   198,   199,   200,   440,   201,   168,   399,
<<<<<<< HEAD
<<<<<<< HEAD
     169,   400,   170,   401,   760,   761,   762,   890,   737,   738,
     739,   869,  1073,   740,   870,   741,   871,   742,   872,   743,
     744,   477,   745,   746,   747,   748,   749,   750,   751,   752,
     753,   878,   754,   755,   881,   756,   882,   757,   883,   171,
     425,   794,   795,   796,   910,   172,   422,   781,   782,   783,
     784,   173,   424,   789,   790,   791,   792,   174,   423,   175,
     428,   805,   806,   807,   919,    65,    84,   337,   338,   339,
     490,   340,   491,   176,   429,   814,   815,   816,   817,   818,
     819,   820,   821,   177,   415,   764,   765,   766,   893,    51,
      77,   226,   227,   228,   446,   229,   447,   230,   448,   231,
     452,   232,   451,   178,   420,   653,   234,   235,   179,   421,
     776,   777,   778,   902,  1004,  1005,   180,   416,    59,    81,
     768,   769,   770,   896,    61,    82,   302,   303,   304,   305,
     306,   307,   308,   476,   309,   480,   310,   479,   311,   312,
     481,   313,   181,   417,   772,   773,   774,   899,    63,    83,
     323,   324,   325,   326,   327,   485,   328,   329,   330,   331,
     237,   444,   853,   854,   855,   948,    53,    78,   248,   249,
     250,   456,   182,   418,   183,   419,   240,   445,   857,   858,
     859,   951,    55,    79,   264,   265,   266,   459,   267,   268,
     461,   269,   270,   184,   427,   801,   802,   803,   916,    57,
      80,   282,   283,   284,   285,   467,   286,   468,   287,   469,
     288,   470,   289,   471,   290,   472,   291,   466,   242,   453,
     862,   863,   954,   185,   426,   798,   799,   913,  1022,  1023,
    1024,  1025,  1026,  1088,  1027,   186,   430,   831,   832,   833,
     930,  1097,   834,   835,   931,   836,   837,   187,   188,   432,
     843,   844,   845,   937,   846,   938,   189,   433,   190,   434,
      67,    85,   357,   358,   359,   360,   495,   361,   496,   362,
     363,   498,   364,   365,   366,   501,   703,   367,   502,   368,
     369,   370,   505,   710,   371,   506,   191,   435,   192,   436,
     104,   390,   105,   391,   106,   392,   193,   397,    71,    87,
     379,   380,   381,   511,   382,   107,   389,    69,    86,   374,
     375,   194,   437,   849,   850,   942,  1056,  1057,  1058,  1059,
    1103,  1060,  1101,  1122,  1123,  1124,  1132,  1133,  1134,  1140,
    1135,  1136,  1137,  1138,  1144
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
     169,   400,   170,   401,   762,   763,   764,   893,   738,   739,
     740,   871,  1077,   741,   872,   742,   873,   743,   874,   744,
     745,   477,   746,   747,   748,   749,   750,   751,   752,   753,
     754,   755,   880,   756,   757,   883,   758,   884,   759,   885,
     171,   425,   796,   797,   798,   913,   172,   422,   783,   784,
     785,   786,   173,   424,   791,   792,   793,   794,   174,   423,
     175,   428,   807,   808,   809,   922,    65,    84,   337,   338,
     339,   490,   340,   491,   176,   429,   816,   817,   818,   819,
     820,   821,   822,   823,   177,   415,   766,   767,   768,   896,
      51,    77,   226,   227,   228,   446,   229,   447,   230,   448,
     231,   452,   232,   451,   178,   420,   653,   234,   235,   179,
     421,   778,   779,   780,   905,  1008,  1009,   180,   416,    59,
      81,   770,   771,   772,   899,    61,    82,   302,   303,   304,
     305,   306,   307,   308,   476,   309,   480,   310,   479,   311,
     312,   481,   313,   181,   417,   774,   775,   776,   902,    63,
      83,   323,   324,   325,   326,   327,   485,   328,   329,   330,
     331,   237,   444,   855,   856,   857,   951,    53,    78,   248,
     249,   250,   456,   182,   418,   183,   419,   240,   445,   859,
     860,   861,   954,    55,    79,   264,   265,   266,   459,   267,
     268,   461,   269,   270,   184,   427,   803,   804,   805,   919,
      57,    80,   282,   283,   284,   285,   467,   286,   468,   287,
     469,   288,   470,   289,   471,   290,   472,   291,   466,   242,
     453,   864,   865,   957,   185,   426,   800,   801,   916,  1026,
    1027,  1028,  1029,  1030,  1092,  1031,   186,   430,   833,   834,
     835,   933,  1101,   836,   837,   934,   838,   839,   187,   188,
     432,   845,   846,   847,   940,   848,   941,   189,   433,   190,
     434,    67,    85,   357,   358,   359,   360,   495,   361,   496,
     362,   363,   498,   364,   365,   366,   501,   703,   367,   502,
     368,   369,   370,   505,   710,   371,   506,   191,   435,   192,
     436,   104,   390,   105,   391,   106,   392,   193,   397,    71,
      87,   379,   380,   381,   511,   382,   107,   389,    69,    86,
     374,   375,   194,   437,   851,   852,   945,  1060,  1061,  1062,
    1063,  1107,  1064,  1105,  1126,  1127,  1128,  1135,  1136,  1137,
    1142,  1138,  1139,  1140
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   150,   197,   214,   244,   258,   278,   215,   300,   319,
<<<<<<< HEAD
<<<<<<< HEAD
     336,   354,   372,   828,   321,   241,   788,   322,   758,   236,
     247,   261,   279,   202,   238,   251,   262,   280,   997,   314,
     332,   216,   355,   998,   373,   999,  1003,   217,  1009,   272,
      94,   218,   376,    91,   646,    32,   860,   203,   239,   252,
     263,   281,   149,   315,   333,   219,   356,   195,   196,   646,
     220,   301,   320,   221,   293,   779,    44,   245,   259,   779,
     786,    40,   787,   246,   260,    33,    46,    34,   394,    35,
     222,   334,   335,   395,   223,    48,   905,   224,   438,   906,
     108,   109,   225,   439,   110,   233,   128,   111,   112,   113,
     908,   677,   294,   909,   295,   296,   377,   378,   297,   298,
     299,   130,   131,   683,   684,   685,   442,   130,   131,   130,
     131,   443,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,    50,   129,
      52,   454,    54,   822,   457,   780,   455,   129,   294,   458,
     243,    56,   723,    58,    99,   130,   131,   130,   131,  1094,
    1095,  1096,   132,   838,   839,   130,   131,   133,   134,   135,
     136,   137,   464,   138,   334,   335,   211,   465,   139,   212,
      60,   701,   702,   294,    95,  1015,  1016,   140,   492,   914,
     141,    62,   915,   493,    96,    97,    98,   142,   130,   131,
     130,   131,   507,   509,    64,   143,   144,   508,   510,   145,
     146,   997,    99,    66,    68,   513,   998,    99,   999,  1003,
     514,  1009,   129,    99,   438,    99,    70,   384,   509,   865,
     129,   147,   148,   866,   149,   253,   254,   255,   256,   257,
     130,   131,   383,   385,   823,   824,   825,   826,   130,   131,
     386,   513,    36,    37,    38,    39,   867,   943,   387,   211,
     944,    99,   212,    99,   442,   887,   271,   788,   976,   868,
     888,    99,   272,   273,   274,   275,   276,   277,   393,   887,
    1049,   718,  1050,  1051,   889,   828,   719,   720,   721,   722,
     723,   724,   725,   726,   727,   728,   729,   730,   731,   732,
     733,   734,   735,   402,    99,   403,    99,   705,   706,   707,
     708,  1127,   404,   911,  1128,  1129,  1130,  1131,   912,   294,
     100,   405,   406,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   928,   935,   939,   507,   129,   929,
     936,   940,   941,   407,   709,   408,    99,   887,   204,   409,
     205,   410,  1081,   411,    99,   412,   130,   131,   206,   207,
     208,   209,   210,   132,   150,   413,   431,   473,   197,   808,
     809,   810,   811,   812,   813,   211,   454,  1085,   212,   139,
     214,  1082,  1086,   244,   215,   441,   213,   449,   492,   202,
     258,  1125,   241,  1093,  1126,   450,   236,  1104,   457,   247,
     278,   238,  1105,  1107,   251,   460,   261,   464,   216,   462,
     300,   262,  1108,   203,   217,   319,   279,  1145,   218,   463,
     321,   280,  1146,   322,   474,   239,   475,   478,   252,   482,
     483,   314,   219,   354,   372,   263,   332,   220,   515,   516,
     221,   484,    99,   486,   487,   281,   245,   649,   650,   651,
     652,   488,   246,   259,   355,   315,   373,   222,   489,   260,
     333,   223,    99,   301,   224,   376,   494,   497,   320,   225,
     499,   500,   233,  1069,  1070,  1071,  1072,   503,   356,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     504,   512,   127,   517,   129,   294,   518,   519,   520,   521,
     522,   524,   525,   294,   316,   295,   296,   317,   318,   526,
     527,   528,   130,   131,   529,   207,   208,   542,   210,   132,
     130,   131,   538,   530,   543,   531,   532,   544,   545,   533,
     546,   211,   539,   534,   212,   535,   536,   537,   547,   540,
     130,   131,   213,   541,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   150,   561,   562,
     563,   564,   565,   567,   197,   568,   570,   571,   572,   573,
     574,   576,   575,   577,   633,   634,   635,   578,   579,   581,
     583,   584,   585,   586,   589,   202,   587,   590,   376,   827,
     840,   591,   354,   372,   592,   593,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   203,
     829,   841,   594,   355,   595,   373,   147,   148,    99,   597,
     598,   600,   601,   602,   599,   605,    99,   603,   609,   610,
     606,   607,   612,   613,   830,   842,   614,   356,   616,   615,
     617,   618,   619,   620,   621,   622,    99,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   623,   624,   697,   627,   628,   630,   704,   631,
     636,   632,   637,   638,   639,   640,   641,   643,   644,   645,
     873,   642,    34,   648,   713,   654,   655,   656,   657,   793,
     659,   658,   660,   661,   667,   665,   662,   663,   664,   666,
     668,   669,   670,   672,   673,   712,   874,   674,   679,   675,
     676,   678,   680,   681,   682,   686,   759,   687,   688,   689,
     690,   691,   763,   767,   771,   775,   797,   800,   804,   848,
     852,   856,   875,   692,   876,   693,   877,   879,   880,   884,
     885,   886,   694,   695,   891,   892,   894,   895,  1119,   696,
     698,   897,   699,   700,   711,   898,   900,   901,   904,   903,
     961,   918,   907,   917,   921,   920,   922,   923,   924,   925,
     926,   927,   932,   933,   934,   945,   950,   949,   952,   953,
     962,   956,   955,   957,   958,   959,   960,   963,   964,   965,
     966,   969,   967,   970,   968,   971,   972,   973,  1013,  1040,
    1041,  1046,  1047,  1063,  1074,   974,  1033,  1062,  1068,  1034,
    1035,  1036,  1089,  1037,  1038,  1083,  1042,  1084,  1043,   214,
    1044,  1090,   300,   215,  1075,   319,  1076,  1077,   984,  1078,
     321,   241,   985,   322,  1079,   236,  1080,  1087,  1091,  1017,
     238,  1092,   278,   314,  1006,   336,   332,   216,  1102,  1007,
    1111,  1098,  1099,   217,  1114,  1019,   986,   218,   279,  1100,
    1020,   827,   987,   280,   239,   840,   988,   315,  1052,  1115,
     333,   219,  1116,  1008,   244,   301,   220,   258,   320,   221,
     989,   996,   829,  1121,  1021,   990,   841,   281,   991,  1054,
     247,  1000,  1018,   261,  1106,   251,   222,  1001,   262,  1112,
     223,  1141,  1142,   224,  1143,   992,   830,  1109,   225,   993,
     842,   233,   994,  1055,  1147,  1151,  1148,   995,   714,   252,
    1002,  1053,   263,  1118,   785,   864,   717,   566,  1120,   977,
    1149,  1150,   569,  1153,   975,  1014,  1011,   245,  1032,  1031,
     259,  1012,  1154,   246,   611,   979,   260,  1039,   978,  1110,
    1010,   292,   980,   604,   580,   981,  1065,   608,  1067,   983,
     982,  1064,  1066,   861,  1029,   582,   588,  1030,  1113,  1045,
     847,  1048,   625,   523,  1028,   716,  1117,   596,  1139,  1152,
     626,  1061,     0,   629,     0,     0,     0,     0,   715,     0,
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
     336,   354,   372,   830,   321,   241,   790,   322,   760,   236,
     247,   261,   279,   202,   238,   251,   262,   280,  1001,   314,
     332,   216,   355,  1002,   373,  1003,  1007,   217,  1013,    94,
      32,   218,   376,   824,   646,   334,   335,   203,   239,   252,
     263,   281,   723,   315,   333,   219,   356,   195,   196,   646,
     220,   301,   320,   221,   293,   781,    44,   245,   259,   677,
      46,    40,    48,   246,   260,    33,    50,    34,   272,    35,
     222,   683,   684,   685,   223,   862,    52,   224,   908,   108,
     109,   909,   225,   110,    54,   233,   111,   112,   113,   130,
     131,   911,   394,   294,   912,   295,   296,   395,    56,   297,
     298,   299,   917,   130,   131,   918,   128,    99,   130,   131,
     130,   131,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   946,   129,
      58,   947,   129,   294,   782,   825,   826,   827,   828,  1131,
     243,    60,  1132,  1133,  1134,   130,   131,   130,   131,   438,
     130,   131,   132,    91,   439,   840,   841,   133,   134,   135,
     136,   137,   442,   138,   377,   378,   211,   443,   139,   212,
    1019,  1020,  1129,   454,    95,  1130,   457,   140,   455,    62,
     141,   458,    64,    96,    97,    98,    66,   142,   464,   705,
     706,   707,   708,   465,    99,   143,   144,    68,   492,   145,
     146,    99,  1001,   493,   334,   335,   507,  1002,    99,  1003,
    1007,   508,  1013,    99,   509,    99,    70,   129,   513,   510,
     129,   147,   148,   514,   149,   709,   649,   650,   651,   652,
     253,   254,   255,   256,   257,   130,   131,   149,   130,   131,
     383,   438,    36,    37,    38,    39,   867,   384,   781,   788,
      99,   789,    99,   294,   211,    99,   271,   212,   701,   702,
     790,   980,   272,   273,   274,   275,   276,   277,   509,   513,
     130,   131,   442,   868,   869,   890,   718,   870,   830,   385,
     891,   719,   720,   721,   722,   723,   724,   725,   726,   727,
     728,   729,   730,   731,   732,   733,   734,   735,   736,   810,
     811,   812,   813,   814,   815,   386,   890,   914,   931,   938,
     100,   892,   915,   932,   939,   294,   942,   507,   890,   454,
    1089,   943,   944,  1085,  1086,  1090,  1098,  1099,  1100,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
      99,   492,   127,    99,   129,   294,  1097,   387,   473,   393,
    1053,  1108,  1054,  1055,   150,   457,  1109,   402,   197,   464,
    1111,   403,   130,   131,  1112,   207,   208,  1146,   210,   132,
     214,   404,  1147,   244,   215,    99,   405,   406,   407,   202,
     258,   211,   241,   408,   212,   409,   236,   410,   411,   247,
     278,   238,   213,   412,   251,   413,   261,   431,   216,   441,
     300,   262,   449,   203,   217,   319,   279,   450,   218,   460,
     321,   280,   462,   322,   463,   239,   474,   484,   252,   475,
     478,   314,   219,   354,   372,   263,   332,   220,   515,   516,
     221,  1073,  1074,  1075,  1076,   281,   245,    99,   482,   483,
     486,   487,   246,   259,   355,   315,   373,   222,   488,   260,
     333,   223,   489,   301,   224,   376,   494,   497,   320,   225,
     499,   500,   233,   503,   504,   512,   517,    99,   356,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     518,   519,   520,   521,   129,   522,   524,   525,   526,   527,
     528,   529,   530,   531,   204,   532,   205,   542,   543,   544,
     545,   533,   130,   131,   206,   207,   208,   209,   210,   132,
     294,   316,   295,   296,   317,   318,   534,   535,   536,   537,
     546,   211,   538,   539,   212,   139,   540,   130,   131,   541,
     547,   548,   213,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   150,   563,   564,
     565,   567,   130,   131,   197,   568,   570,   571,   572,   573,
     574,   575,   576,   577,   633,   634,   635,   578,   579,   581,
     583,   584,   585,   586,   589,   202,   590,   587,   376,   829,
     842,   591,   354,   372,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,   203,
     831,   843,   592,   355,   593,   373,   594,    99,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   595,   597,   598,   832,   844,   599,   356,   147,   148,
     600,   601,    99,   602,   605,   609,   603,   610,   613,   606,
     607,   614,   616,   612,   619,   615,   617,   618,   620,   623,
     621,   622,   624,   627,   697,   628,   630,    99,   631,   875,
     632,   637,   636,   638,   639,   640,   641,   643,   644,   645,
     642,   648,    34,   654,   713,   655,   656,   657,   795,   659,
     658,   660,   661,   667,   668,   662,   663,   664,   666,   669,
     670,   672,   673,   674,   675,   676,   678,   679,   712,   680,
     681,   682,   686,   687,   688,   689,   690,   691,   704,   761,
     692,   765,   769,   773,   777,   799,   802,   806,   850,   854,
     858,   693,   876,   877,   878,   694,   879,   881,   882,   886,
     695,   696,   698,   699,   887,   888,   889,   895,  1123,   700,
     711,   894,   897,   898,   900,   901,   904,   903,   907,   948,
     906,   921,   910,   920,   924,   923,   925,   926,   927,   928,
     929,   930,   935,   936,   937,   953,   964,   952,   956,   955,
     960,   965,   958,   959,   961,   962,   963,   966,   967,   968,
     969,   972,   970,   973,   971,   974,   975,   976,  1017,   978,
     977,  1037,  1038,  1039,  1040,  1041,  1042,  1044,  1045,  1046,
    1050,  1051,  1072,  1047,  1048,  1066,  1067,  1078,  1087,  1088,
    1079,  1093,   214,  1094,  1080,   300,   215,  1081,   319,  1095,
    1096,   988,  1106,   321,   241,   989,   322,  1115,   236,  1082,
    1118,  1116,  1021,   238,  1120,   278,   314,  1010,   336,   332,
     216,  1083,  1011,  1119,  1125,  1143,   217,  1144,  1023,   990,
     218,   279,  1145,  1024,   829,   991,   280,   239,   842,   992,
     315,  1056,  1148,   333,   219,  1084,  1012,   244,   301,   220,
     258,   320,   221,   993,  1000,   831,  1091,  1025,   994,   843,
     281,   995,  1058,   247,  1004,  1022,   261,   665,   251,   222,
    1005,   262,   787,   223,   523,   714,   224,  1102,   996,   832,
    1150,   225,   997,   844,   233,   998,  1059,   566,  1103,  1104,
     999,  1110,   252,  1006,  1057,   263,   717,   866,   981,  1113,
    1018,  1122,   979,  1015,  1016,  1036,  1035,   611,   580,  1043,
     245,   982,  1124,   259,   569,   983,   246,  1114,   292,   260,
     985,  1014,   984,  1069,   986,   987,  1068,   582,  1071,  1034,
    1070,   604,  1151,  1149,  1117,  1153,   863,   608,  1049,  1052,
     849,   588,   716,  1032,  1033,   596,  1121,  1065,  1141,  1152,
       0,     0,     0,   715,     0,     0,     0,   625,     0,     0,
       0,     0,   626,     0,   629,     0,     0,     0,     0,     0,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   988,     0,     0,     0,   989,
       0,  1021,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1010,     0,     0,  1056,     0,  1011,  1023,     0,     0,
       0,     0,  1024,   990,     0,     0,     0,     0,     0,   991,
       0,     0,     0,   992,     0,  1058,     0,     0,     0,     0,
    1012,     0,     0,     0,     0,     0,  1025,   993,  1000,     0,
       0,     0,   994,     0,  1022,   995,     0,     0,  1004,  1059,
       0,     0,     0,     0,  1005,     0,     0,  1057,     0,     0,
       0,     0,   996,     0,     0,     0,   997,     0,     0,   998,
       0,     0,     0,     0,   999,     0,     0,  1006
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    85,   663,    83,    77,   657,    83,   640,    77,
<<<<<<< HEAD
<<<<<<< HEAD
      78,    79,    80,    76,    77,    78,    79,    80,   902,    82,
      83,    77,    85,   902,    85,   902,   902,    77,   902,   100,
      10,    77,    86,   182,   546,     0,   107,    76,    77,    78,
      79,    80,   155,    82,    83,    77,    85,    16,    17,   561,
      77,    82,    83,    77,    21,   102,     7,    78,    79,   102,
     103,    17,   105,    78,    79,     5,     7,     7,     3,     9,
      77,   109,   110,     8,    77,     7,     3,    77,     3,     6,
      11,    12,    77,     8,    15,    77,    57,    18,    19,    20,
       3,   577,    59,     6,    61,    62,    13,    14,    65,    66,
      67,    76,    77,   589,   590,   591,     3,    76,    77,    76,
      77,     8,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     7,    58,
       7,     3,     7,    21,     3,   182,     8,    58,    59,     8,
      69,     7,    30,     7,   182,    76,    77,    76,    77,   119,
     120,   121,    83,   128,   129,    76,    77,    88,    89,    90,
      91,    92,     3,    94,   109,   110,    95,     8,    99,    98,
       7,   145,   146,    59,   154,    96,    97,   108,     3,     3,
     111,     7,     6,     8,   164,   165,   166,   118,    76,    77,
      76,    77,     3,     3,     7,   126,   127,     8,     8,   130,
     131,  1085,   182,     7,     7,     3,  1085,   182,  1085,  1085,
       8,  1085,    58,   182,     3,   182,     7,     3,     3,     8,
      58,   152,   153,     8,   155,    71,    72,    73,    74,    75,
      76,    77,     6,     4,   122,   123,   124,   125,    76,    77,
       8,     3,   182,   183,   184,   185,     8,     3,     3,    95,
       6,   182,    98,   182,     3,     3,    94,   908,   890,     8,
       8,   182,   100,   101,   102,   103,   104,   105,     4,     3,
     156,    21,   158,   159,     8,   935,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     4,   182,     4,   182,   148,   149,   150,
     151,   157,     4,     3,   160,   161,   162,   163,     8,    59,
     394,     4,     4,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     3,     3,     3,     3,    58,     8,
       8,     8,     8,     4,   185,     4,   182,     3,    68,     4,
      70,     4,     8,     4,   182,     4,    76,    77,    78,    79,
      80,    81,    82,    83,   438,     4,     4,     8,   442,   112,
     113,   114,   115,   116,   117,    95,     3,     3,    98,    99,
     454,     8,     8,   457,   454,     4,   106,     4,     3,   442,
     464,     3,   454,     8,     6,     4,   454,     3,     3,   457,
     474,   454,     8,     8,   457,     4,   464,     3,   454,     4,
     484,   464,     8,   442,   454,   489,   474,     3,   454,     4,
     489,   474,     8,   489,     3,   454,     8,     4,   457,     4,
       8,   484,   454,   507,   507,   464,   489,   454,   384,   385,
     454,     3,   182,     4,     4,   474,   457,    84,    85,    86,
      87,     8,   457,   464,   507,   484,   507,   454,     3,   464,
     489,   454,   182,   484,   454,   509,     4,     4,   489,   454,
       4,     4,   454,    22,    23,    24,    25,     4,   507,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       4,     4,    56,   182,    58,    59,     4,     4,     4,     4,
       4,     4,     4,    59,    60,    61,    62,    63,    64,     4,
       4,     4,    76,    77,     4,    79,    80,     4,    82,    83,
      76,    77,   185,   183,     4,   183,   183,     4,     4,   183,
       4,    95,   184,   183,    98,   183,   183,   183,     4,   184,
      76,    77,   106,   183,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   183,     4,   631,     4,     4,
       4,     4,     4,     4,   638,   185,     4,     4,     4,     4,
       4,   185,   183,     4,   520,   521,   522,     4,     4,     4,
       4,   183,     4,   183,     4,   638,   183,     4,   632,   663,
     664,     4,   666,   666,     4,     4,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   638,
     663,   664,     4,   666,     4,   666,   152,   153,   182,     4,
       4,     4,     4,     4,   183,     4,   182,   185,     4,     4,
     185,   185,   185,     4,   663,   664,     4,   666,     4,   183,
     183,   183,     4,     4,   185,   185,   182,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,     4,     4,   610,     4,   183,     4,   147,     7,
     182,     7,     7,     7,     7,     7,     5,     5,     5,     5,
       4,   182,     7,   182,   630,     5,     5,     5,     5,    93,
       5,     7,     5,     5,   182,   561,     7,     7,     7,     7,
     182,     5,     5,     5,     5,     5,     4,   182,     7,   182,
     182,   182,   182,   182,   182,   182,     7,   182,   182,   182,
     182,   182,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     4,   182,     4,   182,     4,     4,     4,     4,
       4,     4,   182,   182,     6,     3,     6,     3,     5,   182,
     182,     6,   182,   182,   182,     3,     6,     3,     3,     6,
     183,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   182,     3,     6,     6,     3,
     185,     6,     8,     4,     4,     4,     4,   183,   185,   183,
       4,     4,   183,     4,   183,     4,   183,   183,     4,     4,
       4,     4,     4,     3,   182,   185,   183,     6,     4,   183,
     183,   183,     4,   183,   183,     8,   183,     8,   183,   893,
     183,     8,   896,   893,   182,   899,   182,   182,   902,   182,
     899,   893,   902,   899,   182,   893,   182,   182,     3,   913,
     893,     8,   916,   896,   902,   919,   899,   893,     4,   902,
       4,   182,   182,   893,     4,   913,   902,   893,   916,   182,
     913,   935,   902,   916,   893,   939,   902,   896,   942,   183,
     899,   893,     4,   902,   948,   896,   893,   951,   899,   893,
     902,   902,   935,     7,   913,   902,   939,   916,   902,   942,
     948,   902,   913,   951,   182,   948,   893,   902,   951,   185,
     893,     4,     4,   893,     4,   902,   935,   182,   893,   902,
     939,   893,   902,   942,     4,     4,   185,   902,   631,   948,
     902,   942,   951,   182,   656,   712,   638,   438,   182,   892,
     183,   183,   442,   182,   887,   911,   905,   948,   921,   919,
     951,   908,   182,   948,   492,   895,   951,   928,   893,  1085,
     904,    81,   896,   484,   454,   898,   950,   489,   953,   901,
     899,   948,   951,   679,   916,   457,   464,   918,  1091,   935,
     666,   939,   507,   394,   914,   637,  1104,   474,  1125,  1145,
     509,   943,    -1,   513,    -1,    -1,    -1,    -1,   632,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
      78,    79,    80,    76,    77,    78,    79,    80,   905,    82,
      83,    77,    85,   905,    85,   905,   905,    77,   905,    10,
       0,    77,    86,    21,   546,   110,   111,    76,    77,    78,
      79,    80,    30,    82,    83,    77,    85,    16,    17,   561,
      77,    82,    83,    77,    21,   103,     7,    78,    79,   577,
       7,    17,     7,    78,    79,     5,     7,     7,   101,     9,
      77,   589,   590,   591,    77,   108,     7,    77,     3,    11,
      12,     6,    77,    15,     7,    77,    18,    19,    20,    77,
      78,     3,     3,    60,     6,    62,    63,     8,     7,    66,
      67,    68,     3,    77,    78,     6,    58,   182,    77,    78,
      77,    78,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     3,    59,
       7,     6,    59,    60,   182,   123,   124,   125,   126,   158,
      70,     7,   161,   162,   163,    77,    78,    77,    78,     3,
      77,    78,    84,   182,     8,   129,   130,    89,    90,    91,
      92,    93,     3,    95,    13,    14,    96,     8,   100,    99,
      97,    98,     3,     3,   155,     6,     3,   109,     8,     7,
     112,     8,     7,   164,   165,   166,     7,   119,     3,   149,
     150,   151,   152,     8,   182,   127,   128,     7,     3,   131,
     132,   182,  1089,     8,   110,   111,     3,  1089,   182,  1089,
    1089,     8,  1089,   182,     3,   182,     7,    59,     3,     8,
      59,   153,   154,     8,   156,   185,    85,    86,    87,    88,
      72,    73,    74,    75,    76,    77,    78,   156,    77,    78,
       6,     3,   182,   183,   184,   185,     8,     3,   103,   104,
     182,   106,   182,    60,    96,   182,    95,    99,   146,   147,
     911,   893,   101,   102,   103,   104,   105,   106,     3,     3,
      77,    78,     3,     8,     8,     3,    21,     8,   938,     4,
       8,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,   113,
     114,   115,   116,   117,   118,     8,     3,     3,     3,     3,
     394,     8,     8,     8,     8,    60,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,   120,   121,   122,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     182,     3,    57,   182,    59,    60,     8,     3,     8,     4,
     157,     3,   159,   160,   438,     3,     8,     4,   442,     3,
       8,     4,    77,    78,     8,    80,    81,     3,    83,    84,
     454,     4,     8,   457,   454,   182,     4,     4,     4,   442,
     464,    96,   454,     4,    99,     4,   454,     4,     4,   457,
     474,   454,   107,     4,   457,     4,   464,     4,   454,     4,
     484,   464,     4,   442,   454,   489,   474,     4,   454,     4,
     489,   474,     4,   489,     4,   454,     3,     3,   457,     8,
       4,   484,   454,   507,   507,   464,   489,   454,   384,   385,
     454,    22,    23,    24,    25,   474,   457,   182,     4,     8,
       4,     4,   457,   464,   507,   484,   507,   454,     8,   464,
     489,   454,     3,   484,   454,   509,     4,     4,   489,   454,
       4,     4,   454,     4,     4,     4,   182,   182,   507,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
       4,     4,     4,     4,    59,     4,     4,     4,     4,     4,
       4,     4,   183,   183,    69,   183,    71,     4,     4,     4,
       4,   183,    77,    78,    79,    80,    81,    82,    83,    84,
      60,    61,    62,    63,    64,    65,   183,   183,   183,   183,
       4,    96,   185,   184,    99,   100,   184,    77,    78,   183,
       4,     4,   107,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   183,     4,     4,     4,   631,     4,     4,
       4,     4,    77,    78,   638,   185,     4,     4,     4,     4,
       4,   183,   185,     4,   520,   521,   522,     4,     4,     4,
       4,   183,     4,   183,     4,   638,     4,   183,   632,   663,
     664,     4,   666,   666,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   638,
     663,   664,     4,   666,     4,   666,     4,   182,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,     4,     4,     4,   663,   664,   183,   666,   153,   154,
       4,     4,   182,     4,     4,     4,   185,     4,     4,   185,
     185,     4,     4,   185,     4,   183,   183,   183,     4,     4,
     185,   185,     4,     4,   610,   183,     4,   182,     7,     4,
       7,     7,   182,     7,     7,     7,     5,     5,     5,     5,
     182,   182,     7,     5,   630,     5,     5,     5,    94,     5,
       7,     5,     5,   182,   182,     7,     7,     7,     7,     5,
       5,     5,     5,   182,   182,   182,   182,     7,     5,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   148,     7,
     182,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,   182,     4,     4,     4,   182,     4,     4,     4,     4,
     182,   182,   182,   182,     4,     4,     4,     3,     5,   182,
     182,     6,     6,     3,     6,     3,     3,     6,     3,   182,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   183,     6,     3,     6,
       4,   185,     8,     6,     4,     4,     4,   183,   185,   183,
       4,     4,   183,     4,   183,     4,   183,   183,     4,   183,
     185,   183,   183,   183,   183,   183,   183,     4,     4,   183,
       4,     4,     4,   183,   183,     6,     3,   182,     8,     8,
     182,     4,   896,     8,   182,   899,   896,   182,   902,     3,
       8,   905,     4,   902,   896,   905,   902,     4,   896,   182,
       4,   185,   916,   896,     4,   919,   899,   905,   922,   902,
     896,   182,   905,   183,     7,     4,   896,     4,   916,   905,
     896,   919,     4,   916,   938,   905,   919,   896,   942,   905,
     899,   945,     4,   902,   896,   182,   905,   951,   899,   896,
     954,   902,   896,   905,   905,   938,   182,   916,   905,   942,
     919,   905,   945,   951,   905,   916,   954,   561,   951,   896,
     905,   954,   656,   896,   394,   631,   896,   182,   905,   938,
     183,   896,   905,   942,   896,   905,   945,   438,   182,   182,
     905,   182,   951,   905,   945,   954,   638,   712,   895,   182,
     914,   182,   890,   908,   911,   924,   922,   492,   454,   931,
     951,   896,   182,   954,   442,   898,   951,  1089,    81,   954,
     901,   907,   899,   953,   902,   904,   951,   457,   956,   921,
     954,   484,   183,   185,  1095,   182,   679,   489,   938,   942,
     666,   464,   637,   917,   919,   474,  1108,   946,  1129,  1146,
      -1,    -1,    -1,   632,    -1,    -1,    -1,   507,    -1,    -1,
      -1,    -1,   509,    -1,   513,    -1,    -1,    -1,    -1,    -1,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1089,    -1,    -1,    -1,  1089,
      -1,  1095,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1089,    -1,    -1,  1108,    -1,  1089,  1095,    -1,    -1,
      -1,    -1,  1095,  1089,    -1,    -1,    -1,    -1,    -1,  1089,
      -1,    -1,    -1,  1089,    -1,  1108,    -1,    -1,    -1,    -1,
    1089,    -1,    -1,    -1,    -1,    -1,  1095,  1089,  1089,    -1,
      -1,    -1,  1089,    -1,  1095,  1089,    -1,    -1,  1089,  1108,
      -1,    -1,    -1,    -1,  1089,    -1,    -1,  1108,    -1,    -1,
      -1,    -1,  1089,    -1,    -1,    -1,  1089,    -1,    -1,  1089,
      -1,    -1,    -1,    -1,  1089,    -1,    -1,  1089
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,     0,     5,     7,     9,   182,   183,   184,   185,
     203,   204,   205,   210,     7,   219,     7,   225,     7,   247,
<<<<<<< HEAD
<<<<<<< HEAD
       7,   345,     7,   422,     7,   438,     7,   455,     7,   374,
       7,   380,     7,   404,     7,   321,     7,   516,     7,   563,
       7,   554,   211,   206,   220,   226,   248,   346,   423,   439,
     456,   375,   381,   405,   322,   517,   564,   555,   203,   212,
     213,   182,   208,   209,    10,   154,   164,   165,   166,   182,
     218,   221,   222,   223,   546,   548,   550,   561,    11,    12,
      15,    18,    19,    20,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      76,    77,    83,    88,    89,    90,    91,    92,    94,    99,
     108,   111,   118,   126,   127,   130,   131,   152,   153,   155,
     218,   227,   228,   229,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   245,   254,   256,
     258,   295,   301,   307,   313,   315,   329,   339,   359,   364,
     372,   398,   428,   430,   449,   479,   491,   503,   504,   512,
     514,   542,   544,   552,   567,    16,    17,   218,   249,   250,
     251,   253,   428,   430,    68,    70,    78,    79,    80,    81,
      82,    95,    98,   106,   218,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   347,   348,   349,   351,
     353,   355,   357,   359,   362,   363,   398,   416,   428,   430,
     432,   449,   474,    69,   218,   355,   357,   398,   424,   425,
     426,   428,   430,    71,    72,    73,    74,    75,   218,   355,
     357,   398,   428,   430,   440,   441,   442,   444,   445,   447,
     448,    94,   100,   101,   102,   103,   104,   105,   218,   398,
     428,   430,   457,   458,   459,   460,   462,   464,   466,   468,
     470,   472,   372,    21,    59,    61,    62,    65,    66,    67,
     218,   276,   382,   383,   384,   385,   386,   387,   388,   390,
     392,   394,   395,   397,   428,   430,    60,    63,    64,   218,
     276,   386,   392,   406,   407,   408,   409,   410,   412,   413,
     414,   415,   428,   430,   109,   110,   218,   323,   324,   325,
     327,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   218,   428,   430,   518,   519,   520,
     521,   523,   525,   526,   528,   529,   530,   533,   535,   536,
     537,   540,   542,   544,   565,   566,   567,    13,    14,   556,
     557,   558,   560,     6,     3,     4,     8,     3,   224,   562,
     547,   549,   551,     4,     3,     8,   230,   553,   246,   255,
     257,   259,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   244,   340,   373,   399,   429,   431,
     360,   365,   302,   314,   308,   296,   480,   450,   316,   330,
     492,     4,   505,   513,   515,   543,   545,   568,     3,     8,
     252,     4,     3,     8,   417,   433,   350,   352,   354,     4,
       4,   358,   356,   475,     3,     8,   427,     3,     8,   443,
       4,   446,     4,     4,     3,     8,   473,   461,   463,   465,
     467,   469,   471,     8,     3,     8,   389,   277,     4,   393,
     391,   396,     4,     8,     3,   411,     4,     4,     8,     3,
     326,   328,     3,     8,     4,   522,   524,     4,   527,     4,
       4,   531,   534,     4,     4,   538,   541,     3,     8,     3,
       8,   559,     4,     3,     8,   203,   203,   182,     4,     4,
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
       7,   346,     7,   423,     7,   439,     7,   456,     7,   375,
       7,   381,     7,   405,     7,   322,     7,   517,     7,   564,
       7,   555,   211,   206,   220,   226,   248,   347,   424,   440,
     457,   376,   382,   406,   323,   518,   565,   556,   203,   212,
     213,   182,   208,   209,    10,   155,   164,   165,   166,   182,
     218,   221,   222,   223,   547,   549,   551,   562,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      77,    78,    84,    89,    90,    91,    92,    93,    95,   100,
     109,   112,   119,   127,   128,   131,   132,   153,   154,   156,
     218,   227,   228,   229,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   245,   254,   256,
     258,   296,   302,   308,   314,   316,   330,   340,   360,   365,
     373,   399,   429,   431,   450,   480,   492,   504,   505,   513,
     515,   543,   545,   553,   568,    16,    17,   218,   249,   250,
     251,   253,   429,   431,    69,    71,    79,    80,    81,    82,
      83,    96,    99,   107,   218,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   348,   349,   350,   352,
     354,   356,   358,   360,   363,   364,   399,   417,   429,   431,
     433,   450,   475,    70,   218,   356,   358,   399,   425,   426,
     427,   429,   431,    72,    73,    74,    75,    76,   218,   356,
     358,   399,   429,   431,   441,   442,   443,   445,   446,   448,
     449,    95,   101,   102,   103,   104,   105,   106,   218,   399,
     429,   431,   458,   459,   460,   461,   463,   465,   467,   469,
     471,   473,   373,    21,    60,    62,    63,    66,    67,    68,
     218,   276,   383,   384,   385,   386,   387,   388,   389,   391,
     393,   395,   396,   398,   429,   431,    61,    64,    65,   218,
     276,   387,   393,   407,   408,   409,   410,   411,   413,   414,
     415,   416,   429,   431,   110,   111,   218,   324,   325,   326,
     328,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   218,   429,   431,   519,   520,   521,
     522,   524,   526,   527,   529,   530,   531,   534,   536,   537,
     538,   541,   543,   545,   566,   567,   568,    13,    14,   557,
     558,   559,   561,     6,     3,     4,     8,     3,   224,   563,
     548,   550,   552,     4,     3,     8,   230,   554,   246,   255,
     257,   259,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   244,   341,   374,   400,   430,   432,
     361,   366,   303,   315,   309,   297,   481,   451,   317,   331,
     493,     4,   506,   514,   516,   544,   546,   569,     3,     8,
     252,     4,     3,     8,   418,   434,   351,   353,   355,     4,
       4,   359,   357,   476,     3,     8,   428,     3,     8,   444,
       4,   447,     4,     4,     3,     8,   474,   462,   464,   466,
     468,   470,   472,     8,     3,     8,   390,   277,     4,   394,
     392,   397,     4,     8,     3,   412,     4,     4,     8,     3,
     327,   329,     3,     8,     4,   523,   525,     4,   528,     4,
       4,   532,   535,     4,     4,   539,   542,     3,     8,     3,
       8,   560,     4,     3,     8,   203,   203,   182,     4,     4,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
       4,     4,     4,   222,     4,     4,     4,     4,     4,     4,
     183,   183,   183,   183,   183,   183,   183,   183,   185,   184,
     184,   183,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   183,
       4,     4,     4,     4,     4,     4,   228,     4,   185,   250,
       4,     4,     4,     4,     4,   183,   185,     4,     4,     4,
<<<<<<< HEAD
<<<<<<< HEAD
     348,     4,   425,     4,   183,     4,   183,   183,   441,     4,
       4,     4,     4,     4,     4,     4,   459,     4,     4,   183,
       4,     4,     4,   185,   384,     4,   185,   185,   408,     4,
       4,   324,   185,     4,     4,   183,     4,   183,   183,     4,
       4,   185,   185,     4,     4,   519,   566,     4,   183,   557,
       4,     7,     7,   203,   203,   203,   182,     7,     7,     7,
       7,     5,   182,     5,     5,     5,   205,   207,   182,    84,
      85,    86,    87,   361,     5,     5,     5,     5,     7,     5,
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
     349,     4,   426,     4,   183,     4,   183,   183,   442,     4,
       4,     4,     4,     4,     4,     4,   460,     4,     4,   183,
       4,     4,     4,   185,   385,     4,   185,   185,   409,     4,
       4,   325,   185,     4,     4,   183,     4,   183,   183,     4,
       4,   185,   185,     4,     4,   520,   567,     4,   183,   558,
       4,     7,     7,   203,   203,   203,   182,     7,     7,     7,
       7,     5,   182,     5,     5,     5,   205,   207,   182,    85,
      86,    87,    88,   362,     5,     5,     5,     5,     7,     5,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
       5,     5,     7,     7,     7,   207,     7,   182,   182,     5,
       5,   214,     5,     5,   182,   182,   182,   214,   182,     7,
     182,   182,   182,   214,   214,   214,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   203,   182,   182,
<<<<<<< HEAD
<<<<<<< HEAD
     182,   145,   146,   532,   147,   148,   149,   150,   151,   185,
     539,   182,     5,   203,   227,   565,   556,   249,    21,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,   218,   264,   265,   266,
     269,   271,   273,   275,   276,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   288,   289,   291,   293,   264,     7,
     260,   261,   262,     7,   341,   342,   343,     7,   376,   377,
     378,     7,   400,   401,   402,     7,   366,   367,   368,   102,
     182,   303,   304,   305,   306,   212,   103,   105,   305,   309,
     310,   311,   312,    93,   297,   298,   299,     7,   481,   482,
       7,   451,   452,   453,     7,   317,   318,   319,   112,   113,
     114,   115,   116,   117,   331,   332,   333,   334,   335,   336,
     337,   338,    21,   122,   123,   124,   125,   218,   278,   428,
     430,   493,   494,   495,   498,   499,   501,   502,   128,   129,
     218,   428,   430,   506,   507,   508,   510,   518,     7,   569,
     570,   215,     7,   418,   419,   420,     7,   434,   435,   436,
     107,   460,   476,   477,   260,     8,     8,     8,     8,   267,
     270,   272,   274,     4,     4,     4,     4,     4,   287,     4,
       4,   290,   292,   294,     4,     4,     4,     3,     8,     8,
     263,     6,     3,   344,     6,     3,   379,     6,     3,   403,
       6,     3,   369,     6,     3,     3,     6,     6,     3,     6,
     300,     3,     8,   483,     3,     6,   454,     6,     3,   320,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     496,   500,     4,     4,     4,     3,     8,   509,   511,     3,
       8,     8,   571,     3,     6,   182,   216,   217,   421,     6,
       3,   437,     6,     3,   478,     8,     6,     4,     4,     4,
       4,   183,   185,   183,   185,   183,     4,   183,   183,     4,
       4,     4,   183,   183,   185,   265,   264,   262,   347,   343,
     382,   378,   406,   402,   218,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   276,   339,   351,   353,
     355,   357,   359,   363,   370,   371,   398,   428,   430,   474,
     368,   304,   310,     4,   298,    96,    97,   218,   276,   398,
     428,   430,   484,   485,   486,   487,   488,   490,   482,   457,
     453,   323,   319,   183,   183,   183,   183,   183,   183,   332,
       4,     4,   183,   183,   183,   494,     4,     4,   507,   156,
     158,   159,   218,   276,   428,   430,   572,   573,   574,   575,
     577,   570,     6,     3,   424,   420,   440,   436,     4,    22,
      23,    24,    25,   268,   182,   182,   182,   182,   182,   182,
     182,     8,     8,     8,     8,     3,     8,   182,   489,     4,
       8,     3,     8,     8,   119,   120,   121,   497,   182,   182,
     182,   578,     4,   576,     3,     8,   182,     8,     8,   182,
     371,     4,   185,   486,     4,   183,     4,   573,   182,     5,
     182,     7,   579,   580,   581,     3,     6,   157,   160,   161,
     162,   163,   582,   583,   584,   586,   587,   588,   589,   580,
     585,     4,     4,     4,   590,     3,     8,     4,   185,   183,
     183,     4,   583,   182,   182
=======
     182,   146,   147,   533,   148,   149,   150,   151,   152,   185,
     540,   182,     5,   203,   227,   566,   557,   249,    21,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
=======
     182,   146,   147,   533,   148,   149,   150,   151,   152,   185,
     540,   182,     5,   203,   227,   566,   557,   249,    21,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
      37,    38,    39,    40,    41,    42,    43,   218,   264,   265,
     266,   269,   271,   273,   275,   276,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   289,   290,   292,   294,
     264,     7,   260,   261,   262,     7,   342,   343,   344,     7,
     377,   378,   379,     7,   401,   402,   403,     7,   367,   368,
     369,   103,   182,   304,   305,   306,   307,   212,   104,   106,
     306,   310,   311,   312,   313,    94,   298,   299,   300,     7,
     482,   483,     7,   452,   453,   454,     7,   318,   319,   320,
     113,   114,   115,   116,   117,   118,   332,   333,   334,   335,
     336,   337,   338,   339,    21,   123,   124,   125,   126,   218,
     278,   429,   431,   494,   495,   496,   499,   500,   502,   503,
     129,   130,   218,   429,   431,   507,   508,   509,   511,   519,
       7,   570,   571,   215,     7,   419,   420,   421,     7,   435,
     436,   437,   108,   461,   477,   478,   260,     8,     8,     8,
       8,   267,   270,   272,   274,     4,     4,     4,     4,     4,
     288,     4,     4,   291,   293,   295,     4,     4,     4,     4,
       3,     8,     8,   263,     6,     3,   345,     6,     3,   380,
       6,     3,   404,     6,     3,   370,     6,     3,     3,     6,
       6,     3,     6,   301,     3,     8,   484,     3,     6,   455,
       6,     3,   321,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   497,   501,     4,     4,     4,     3,     8,
     510,   512,     3,     8,     8,   572,     3,     6,   182,   216,
     217,   422,     6,     3,   438,     6,     3,   479,     8,     6,
       4,     4,     4,     4,   183,   185,   183,   185,   183,     4,
     183,   183,     4,     4,     4,   183,   183,   185,   183,   265,
     264,   262,   348,   344,   383,   379,   407,   403,   218,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     276,   340,   352,   354,   356,   358,   360,   364,   371,   372,
     399,   429,   431,   475,   369,   305,   311,     4,   299,    97,
      98,   218,   276,   399,   429,   431,   485,   486,   487,   488,
     489,   491,   483,   458,   454,   324,   320,   183,   183,   183,
     183,   183,   183,   333,     4,     4,   183,   183,   183,   495,
       4,     4,   508,   157,   159,   160,   218,   276,   429,   431,
     573,   574,   575,   576,   578,   571,     6,     3,   425,   421,
     441,   437,     4,    22,    23,    24,    25,   268,   182,   182,
     182,   182,   182,   182,   182,     8,     8,     8,     8,     3,
       8,   182,   490,     4,     8,     3,     8,     8,   120,   121,
     122,   498,   182,   182,   182,   579,     4,   577,     3,     8,
     182,     8,     8,   182,   372,     4,   185,   487,     4,   183,
       4,   574,   182,     5,   182,     7,   580,   581,   582,     3,
       6,   158,   161,   162,   163,   583,   584,   585,   587,   588,
     589,   581,   586,     4,     4,     4,     3,     8,     4,   185,
     183,   183,   584,   182
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   186,   188,   187,   189,   187,   190,   187,   191,   187,
     192,   187,   193,   187,   194,   187,   195,   187,   196,   187,
     197,   187,   198,   187,   199,   187,   200,   187,   201,   187,
     202,   187,   203,   203,   203,   203,   203,   203,   203,   204,
     206,   205,   207,   208,   208,   209,   209,   211,   210,   212,
     212,   213,   213,   215,   214,   216,   216,   217,   217,   218,
     220,   219,   221,   221,   222,   222,   222,   222,   222,   222,
     224,   223,   226,   225,   227,   227,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   230,
     229,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   244,   243,   246,   245,   248,   247,   249,
     249,   250,   250,   250,   250,   250,   252,   251,   253,   255,
     254,   257,   256,   259,   258,   260,   260,   261,   261,   263,
     262,   264,   264,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
<<<<<<< HEAD
<<<<<<< HEAD
     265,   265,   265,   267,   266,   268,   268,   268,   268,   270,
     269,   272,   271,   274,   273,   275,   277,   276,   278,   279,
     280,   281,   282,   283,   284,   285,   287,   286,   288,   290,
     289,   292,   291,   294,   293,   296,   295,   297,   297,   298,
     300,   299,   302,   301,   303,   303,   304,   304,   305,   306,
     308,   307,   309,   309,   310,   310,   310,   311,   312,   314,
     313,   316,   315,   317,   317,   318,   318,   320,   319,   322,
     321,   323,   323,   323,   324,   324,   326,   325,   328,   327,
     330,   329,   331,   331,   332,   332,   332,   332,   332,   332,
     333,   334,   335,   336,   337,   338,   340,   339,   341,   341,
     342,   342,   344,   343,   346,   345,   347,   347,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   350,   349,   352,   351,   354,
     353,   356,   355,   358,   357,   360,   359,   361,   361,   361,
     361,   362,   363,   365,   364,   366,   366,   367,   367,   369,
     368,   370,   370,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   373,   372,   375,
     374,   376,   376,   377,   377,   379,   378,   381,   380,   382,
     382,   383,   383,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   385,   386,   387,   389,   388,   391,   390,
     393,   392,   394,   396,   395,   397,   399,   398,   400,   400,
     401,   401,   403,   402,   405,   404,   406,   406,   407,   407,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   409,
     411,   410,   412,   413,   414,   415,   417,   416,   418,   418,
     419,   419,   421,   420,   423,   422,   424,   424,   425,   425,
     425,   425,   425,   425,   425,   427,   426,   429,   428,   431,
     430,   433,   432,   434,   434,   435,   435,   437,   436,   439,
     438,   440,   440,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   441,   443,   442,   444,   446,   445,   447,
     448,   450,   449,   451,   451,   452,   452,   454,   453,   456,
     455,   457,   457,   458,   458,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   461,   460,   463,   462,
     465,   464,   467,   466,   469,   468,   471,   470,   473,   472,
     475,   474,   476,   476,   478,   477,   480,   479,   481,   481,
     483,   482,   484,   484,   485,   485,   486,   486,   486,   486,
     486,   486,   486,   487,   489,   488,   490,   492,   491,   493,
     493,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     496,   495,   497,   497,   497,   498,   500,   499,   501,   502,
     503,   505,   504,   506,   506,   507,   507,   507,   507,   507,
     509,   508,   511,   510,   513,   512,   515,   514,   517,   516,
     518,   518,   519,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   519,   519,
     520,   522,   521,   524,   523,   525,   527,   526,   528,   529,
     531,   530,   532,   532,   534,   533,   535,   536,   538,   537,
     539,   539,   539,   539,   539,   541,   540,   543,   542,   545,
     544,   547,   546,   549,   548,   551,   550,   553,   552,   555,
     554,   556,   556,   557,   557,   559,   558,   560,   562,   561,
     564,   563,   565,   565,   566,   568,   567,   569,   569,   571,
     570,   572,   572,   573,   573,   573,   573,   573,   573,   573,
     574,   576,   575,   578,   577,   579,   579,   581,   580,   582,
     582,   583,   583,   583,   583,   583,   585,   584,   586,   587,
     588,   590,   589
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
     265,   265,   265,   265,   267,   266,   268,   268,   268,   268,
     270,   269,   272,   271,   274,   273,   275,   277,   276,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   288,   287,
     289,   291,   290,   293,   292,   295,   294,   297,   296,   298,
     298,   299,   301,   300,   303,   302,   304,   304,   305,   305,
     306,   307,   309,   308,   310,   310,   311,   311,   311,   312,
     313,   315,   314,   317,   316,   318,   318,   319,   319,   321,
     320,   323,   322,   324,   324,   324,   325,   325,   327,   326,
     329,   328,   331,   330,   332,   332,   333,   333,   333,   333,
     333,   333,   334,   335,   336,   337,   338,   339,   341,   340,
     342,   342,   343,   343,   345,   344,   347,   346,   348,   348,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   351,   350,   353,
     352,   355,   354,   357,   356,   359,   358,   361,   360,   362,
     362,   362,   362,   363,   364,   366,   365,   367,   367,   368,
     368,   370,   369,   371,   371,   372,   372,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   372,   372,   374,
     373,   376,   375,   377,   377,   378,   378,   380,   379,   382,
     381,   383,   383,   384,   384,   385,   385,   385,   385,   385,
     385,   385,   385,   385,   385,   386,   387,   388,   390,   389,
     392,   391,   394,   393,   395,   397,   396,   398,   400,   399,
     401,   401,   402,   402,   404,   403,   406,   405,   407,   407,
     408,   408,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   410,   412,   411,   413,   414,   415,   416,   418,   417,
     419,   419,   420,   420,   422,   421,   424,   423,   425,   425,
     426,   426,   426,   426,   426,   426,   426,   428,   427,   430,
     429,   432,   431,   434,   433,   435,   435,   436,   436,   438,
     437,   440,   439,   441,   441,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   444,   443,   445,   447,
     446,   448,   449,   451,   450,   452,   452,   453,   453,   455,
     454,   457,   456,   458,   458,   459,   459,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   462,   461,
     464,   463,   466,   465,   468,   467,   470,   469,   472,   471,
     474,   473,   476,   475,   477,   477,   479,   478,   481,   480,
     482,   482,   484,   483,   485,   485,   486,   486,   487,   487,
     487,   487,   487,   487,   487,   488,   490,   489,   491,   493,
     492,   494,   494,   495,   495,   495,   495,   495,   495,   495,
     495,   495,   497,   496,   498,   498,   498,   499,   501,   500,
     502,   503,   504,   506,   505,   507,   507,   508,   508,   508,
     508,   508,   510,   509,   512,   511,   514,   513,   516,   515,
     518,   517,   519,   519,   520,   520,   520,   520,   520,   520,
     520,   520,   520,   520,   520,   520,   520,   520,   520,   520,
     520,   520,   521,   523,   522,   525,   524,   526,   528,   527,
     529,   530,   532,   531,   533,   533,   535,   534,   536,   537,
     539,   538,   540,   540,   540,   540,   540,   542,   541,   544,
     543,   546,   545,   548,   547,   550,   549,   552,   551,   554,
     553,   556,   555,   557,   557,   558,   558,   560,   559,   561,
     563,   562,   565,   564,   566,   566,   567,   569,   568,   570,
     570,   572,   571,   573,   573,   574,   574,   574,   574,   574,
     574,   574,   575,   577,   576,   579,   578,   580,   580,   582,
     581,   583,   583,   584,   584,   584,   584,   586,   585,   587,
     588,   589
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
<<<<<<< HEAD
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
=======
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
<<<<<<< HEAD
<<<<<<< HEAD
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     3,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     0,     6,     3,
       0,     6,     0,     4,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"data-directory\"",
  "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"consistency\"",
  "\"serial-consistency\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"subnet6\"", "\"option-def\"", "\"option-data\"",
  "\"name\"", "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"always-send\"", "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"pools\"", "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"shared-networks\"", "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"client-classes\"", "\"require-client-classes\"",
  "\"test\"", "\"only-if-required\"", "\"client-class\"",
  "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"", "\"duid\"",
  "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "$@15", "value", "sub_json", "map2", "$@16", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@17", "list_content",
  "not_empty_list", "list_strings", "$@18", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@19",
  "global_objects", "global_object", "dhcp6_object", "$@20", "sub_dhcp6",
  "$@21", "global_params", "global_param", "data_directory", "$@22",
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "decline_probation_period", "server_tag", "$@23",
  "interfaces_config", "$@24", "sub_interfaces6", "$@25",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@26", "re_detect", "lease_database", "$@27", "hosts_database", "$@28",
  "hosts_databases", "$@29", "database_list", "not_empty_database_list",
  "database", "$@30", "database_map_params", "database_map_param",
  "database_type", "$@31", "db_type", "user", "$@32", "password", "$@33",
  "host", "$@34", "port", "name", "$@35", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "max_row_errors",
  "request_timeout", "tcp_keepalive", "tcp_nodelay", "contact_points",
  "$@36", "max_reconnect_tries", "keyspace", "$@37", "consistency", "$@38",
  "serial_consistency", "$@39", "sanity_checks", "$@40",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@41",
  "mac_sources", "$@42", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@43",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@44",
  "hooks_libraries", "$@45", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@46",
  "sub_hooks_library", "$@47", "hooks_params", "hooks_param", "library",
  "$@48", "parameters", "$@49", "expired_leases_processing", "$@50",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@51",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@52",
  "sub_subnet6", "$@53", "subnet6_params", "subnet6_param", "subnet",
  "$@54", "interface", "$@55", "interface_id", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@60",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@61", "shared_network_params", "shared_network_param",
  "option_def_list", "$@62", "sub_option_def_list", "$@63",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@64", "sub_option_def", "$@65",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool6", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "pd_pools_list", "$@80",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@81", "sub_pd_pool", "$@82", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@83", "pd_prefix_len", "excluded_prefix", "$@84",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@85",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@86", "sub_reservation", "$@87", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@88", "prefixes", "$@89", "duid", "$@90", "hw_address", "$@91",
  "hostname", "$@92", "flex_id_value", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "ip_address", "$@96", "client_classes", "$@97", "client_classes_list",
  "client_class_entry", "$@98", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@99", "only_if_required",
  "server_id", "$@100", "server_id_params", "server_id_param",
  "server_id_type", "$@101", "duid_type", "htype", "identifier", "$@102",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@103",
  "control_socket_params", "control_socket_param", "socket_type", "$@104",
  "socket_name", "$@105", "dhcp_queue_control", "$@106", "dhcp_ddns",
  "$@107", "sub_dhcp_ddns", "$@108", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@109", "server_ip", "$@110",
  "server_port", "sender_ip", "$@111", "sender_port", "max_queue_size",
  "ncr_protocol", "$@112", "ncr_protocol_value", "ncr_format", "$@113",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@114", "replace_client_name_value", "generated_prefix", "$@115",
  "hostname_char_set", "$@116", "hostname_char_replacement", "$@117",
  "dhcp4_json_object", "$@118", "dhcpddns_json_object", "$@119",
  "control_agent_json_object", "$@120", "config_control", "$@121",
  "sub_config_control", "$@122", "config_control_params",
  "config_control_param", "config_databases", "$@123",
  "config_fetch_wait_time", "logging_object", "$@124", "sub_logging",
  "$@125", "logging_params", "logging_param", "loggers", "$@126",
  "loggers_entries", "logger_entry", "$@127", "logger_params",
  "logger_param", "debuglevel", "severity", "$@128", "output_options_list",
  "$@129", "output_options_list_content", "output_entry", "$@130",
  "output_params_list", "output_params", "output", "$@131", "flush",
  "maxsize", "maxver", "pattern", "$@132", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   270,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     279,   279,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   292,   293,   294,   295,   296,   297,   298,   301,
     306,   306,   317,   320,   321,   324,   328,   335,   335,   342,
     343,   346,   350,   357,   357,   364,   365,   368,   372,   383,
     393,   393,   408,   409,   413,   414,   415,   416,   417,   418,
     421,   421,   436,   436,   445,   446,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   496,
     496,   504,   509,   514,   519,   524,   529,   534,   539,   544,
     549,   554,   559,   564,   564,   572,   572,   583,   583,   592,
     593,   596,   597,   598,   599,   600,   603,   603,   613,   619,
     619,   631,   631,   643,   643,   653,   654,   657,   658,   661,
     661,   671,   672,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
<<<<<<< HEAD
<<<<<<< HEAD
     692,   693,   694,   697,   697,   704,   705,   706,   707,   710,
     710,   718,   718,   726,   726,   734,   739,   739,   747,   752,
     757,   762,   767,   772,   777,   782,   787,   787,   795,   800,
     800,   808,   808,   816,   816,   824,   824,   834,   835,   837,
     839,   839,   857,   857,   867,   868,   871,   872,   875,   880,
     885,   885,   895,   896,   899,   900,   901,   904,   909,   916,
     916,   926,   926,   936,   937,   940,   941,   944,   944,   954,
     954,   964,   965,   966,   969,   970,   973,   973,   981,   981,
     989,   989,  1000,  1001,  1004,  1005,  1006,  1007,  1008,  1009,
    1012,  1017,  1022,  1027,  1032,  1037,  1045,  1045,  1058,  1059,
    1062,  1063,  1070,  1070,  1096,  1096,  1107,  1108,  1112,  1113,
    1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,  1123,
    1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,
    1134,  1135,  1136,  1137,  1138,  1141,  1141,  1149,  1149,  1157,
    1157,  1165,  1165,  1173,  1173,  1183,  1183,  1190,  1191,  1192,
    1193,  1196,  1201,  1209,  1209,  1220,  1221,  1225,  1226,  1229,
    1229,  1237,  1238,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,  1257,
    1258,  1259,  1260,  1261,  1262,  1263,  1264,  1271,  1271,  1284,
    1284,  1293,  1294,  1297,  1298,  1303,  1303,  1318,  1318,  1332,
    1333,  1336,  1337,  1340,  1341,  1342,  1343,  1344,  1345,  1346,
    1347,  1348,  1349,  1352,  1354,  1359,  1361,  1361,  1369,  1369,
    1377,  1377,  1385,  1387,  1387,  1395,  1404,  1404,  1416,  1417,
    1422,  1423,  1428,  1428,  1440,  1440,  1452,  1453,  1458,  1459,
    1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,  1472,  1475,
    1477,  1477,  1485,  1487,  1489,  1494,  1502,  1502,  1514,  1515,
    1518,  1519,  1522,  1522,  1532,  1532,  1541,  1542,  1545,  1546,
    1547,  1548,  1549,  1550,  1551,  1554,  1554,  1562,  1562,  1587,
    1587,  1617,  1617,  1629,  1630,  1633,  1634,  1637,  1637,  1649,
    1649,  1661,  1662,  1665,  1666,  1667,  1668,  1669,  1670,  1671,
    1672,  1673,  1674,  1675,  1678,  1678,  1686,  1691,  1691,  1699,
    1704,  1712,  1712,  1722,  1723,  1726,  1727,  1730,  1730,  1739,
    1739,  1748,  1749,  1752,  1753,  1757,  1758,  1759,  1760,  1761,
    1762,  1763,  1764,  1765,  1766,  1767,  1770,  1770,  1780,  1780,
    1790,  1790,  1798,  1798,  1806,  1806,  1814,  1814,  1822,  1822,
    1835,  1835,  1845,  1846,  1849,  1849,  1860,  1860,  1870,  1871,
    1874,  1874,  1884,  1885,  1888,  1889,  1892,  1893,  1894,  1895,
    1896,  1897,  1898,  1901,  1903,  1903,  1911,  1919,  1919,  1931,
    1932,  1935,  1936,  1937,  1938,  1939,  1940,  1941,  1942,  1943,
    1946,  1946,  1953,  1954,  1955,  1958,  1963,  1963,  1971,  1976,
    1983,  1990,  1990,  2000,  2001,  2004,  2005,  2006,  2007,  2008,
    2011,  2011,  2019,  2019,  2029,  2029,  2069,  2069,  2081,  2081,
    2091,  2092,  2095,  2096,  2097,  2098,  2099,  2100,  2101,  2102,
    2103,  2104,  2105,  2106,  2107,  2108,  2109,  2110,  2111,  2112,
    2115,  2120,  2120,  2128,  2128,  2136,  2141,  2141,  2149,  2154,
    2159,  2159,  2167,  2168,  2171,  2171,  2179,  2184,  2189,  2189,
    2197,  2200,  2203,  2206,  2209,  2215,  2215,  2223,  2223,  2231,
    2231,  2241,  2241,  2248,  2248,  2255,  2255,  2264,  2264,  2275,
    2275,  2285,  2286,  2290,  2291,  2294,  2294,  2304,  2314,  2314,
    2324,  2324,  2335,  2336,  2340,  2344,  2344,  2356,  2357,  2361,
    2361,  2369,  2370,  2373,  2374,  2375,  2376,  2377,  2378,  2379,
    2382,  2387,  2387,  2395,  2395,  2405,  2406,  2409,  2409,  2417,
    2418,  2421,  2422,  2423,  2424,  2425,  2428,  2428,  2436,  2441,
    2446,  2451,  2451
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
     692,   693,   694,   695,   698,   698,   705,   706,   707,   708,
     711,   711,   719,   719,   727,   727,   735,   740,   740,   748,
     753,   758,   763,   768,   773,   778,   783,   788,   793,   793,
     801,   806,   806,   814,   814,   822,   822,   830,   830,   840,
     841,   843,   845,   845,   863,   863,   873,   874,   877,   878,
     881,   886,   891,   891,   901,   902,   905,   906,   907,   910,
     915,   922,   922,   932,   932,   942,   943,   946,   947,   950,
     950,   960,   960,   970,   971,   972,   975,   976,   979,   979,
     987,   987,   995,   995,  1006,  1007,  1010,  1011,  1012,  1013,
    1014,  1015,  1018,  1023,  1028,  1033,  1038,  1043,  1051,  1051,
    1064,  1065,  1068,  1069,  1076,  1076,  1102,  1102,  1113,  1114,
    1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1147,  1147,  1155,
    1155,  1163,  1163,  1171,  1171,  1179,  1179,  1189,  1189,  1196,
    1197,  1198,  1199,  1202,  1207,  1215,  1215,  1226,  1227,  1231,
    1232,  1235,  1235,  1243,  1244,  1247,  1248,  1249,  1250,  1251,
    1252,  1253,  1254,  1255,  1256,  1257,  1258,  1259,  1260,  1261,
    1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1277,
    1277,  1290,  1290,  1299,  1300,  1303,  1304,  1309,  1309,  1324,
    1324,  1338,  1339,  1342,  1343,  1346,  1347,  1348,  1349,  1350,
    1351,  1352,  1353,  1354,  1355,  1358,  1360,  1365,  1367,  1367,
    1375,  1375,  1383,  1383,  1391,  1393,  1393,  1401,  1410,  1410,
    1422,  1423,  1428,  1429,  1434,  1434,  1446,  1446,  1458,  1459,
    1464,  1465,  1470,  1471,  1472,  1473,  1474,  1475,  1476,  1477,
    1478,  1481,  1483,  1483,  1491,  1493,  1495,  1500,  1508,  1508,
    1520,  1521,  1524,  1525,  1528,  1528,  1538,  1538,  1547,  1548,
    1551,  1552,  1553,  1554,  1555,  1556,  1557,  1560,  1560,  1568,
    1568,  1593,  1593,  1623,  1623,  1635,  1636,  1639,  1640,  1643,
    1643,  1655,  1655,  1667,  1668,  1671,  1672,  1673,  1674,  1675,
    1676,  1677,  1678,  1679,  1680,  1681,  1684,  1684,  1692,  1697,
    1697,  1705,  1710,  1718,  1718,  1728,  1729,  1732,  1733,  1736,
    1736,  1745,  1745,  1754,  1755,  1758,  1759,  1763,  1764,  1765,
    1766,  1767,  1768,  1769,  1770,  1771,  1772,  1773,  1776,  1776,
    1786,  1786,  1796,  1796,  1804,  1804,  1812,  1812,  1820,  1820,
    1828,  1828,  1841,  1841,  1851,  1852,  1855,  1855,  1866,  1866,
    1876,  1877,  1880,  1880,  1890,  1891,  1894,  1895,  1898,  1899,
    1900,  1901,  1902,  1903,  1904,  1907,  1909,  1909,  1917,  1925,
    1925,  1937,  1938,  1941,  1942,  1943,  1944,  1945,  1946,  1947,
    1948,  1949,  1952,  1952,  1959,  1960,  1961,  1964,  1969,  1969,
    1977,  1982,  1989,  1996,  1996,  2006,  2007,  2010,  2011,  2012,
    2013,  2014,  2017,  2017,  2025,  2025,  2035,  2035,  2075,  2075,
    2087,  2087,  2097,  2098,  2101,  2102,  2103,  2104,  2105,  2106,
    2107,  2108,  2109,  2110,  2111,  2112,  2113,  2114,  2115,  2116,
    2117,  2118,  2121,  2126,  2126,  2134,  2134,  2142,  2147,  2147,
    2155,  2160,  2165,  2165,  2173,  2174,  2177,  2177,  2185,  2190,
    2195,  2195,  2203,  2206,  2209,  2212,  2215,  2221,  2221,  2229,
    2229,  2237,  2237,  2247,  2247,  2254,  2254,  2261,  2261,  2270,
    2270,  2281,  2281,  2291,  2292,  2296,  2297,  2300,  2300,  2310,
    2320,  2320,  2330,  2330,  2341,  2342,  2346,  2350,  2350,  2362,
    2363,  2367,  2367,  2375,  2376,  2379,  2380,  2381,  2382,  2383,
    2384,  2385,  2388,  2393,  2393,  2401,  2401,  2411,  2412,  2415,
    2415,  2423,  2424,  2427,  2428,  2429,  2430,  2433,  2433,  2441,
    2446,  2451
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1218
} } // isc::dhcp
<<<<<<< HEAD
<<<<<<< HEAD
#line 5282 "dhcp6_parser.cc"

#line 2459 "dhcp6_parser.yy"
=======
#line 5256 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2456 "dhcp6_parser.yy" // lalr1.cc:1219
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
#line 5256 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2456 "dhcp6_parser.yy" // lalr1.cc:1219
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
