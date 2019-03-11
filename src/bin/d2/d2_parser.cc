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
#define yylex   d2_parser_lex



#include "d2_parser.h"


// Unqualified %code blocks.
#line 34 "d2_parser.yy" // lalr1.cc:435

#include <d2/parser_context.h>

#line 51 "d2_parser.cc" // lalr1.cc:435


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
#if D2_PARSER_DEBUG

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

#else // !D2_PARSER_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !D2_PARSER_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "d2_parser.yy" // lalr1.cc:510
namespace isc { namespace d2 {
#line 146 "d2_parser.cc" // lalr1.cc:510

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  D2Parser::yytnamerr_ (const char *yystr)
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
  D2Parser::D2Parser (isc::d2::D2ParserContext& ctx_yyarg)
    :
#if D2_PARSER_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  D2Parser::~D2Parser ()
  {}

  D2Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  D2Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  D2Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  D2Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  D2Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  D2Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  D2Parser::symbol_number_type
  D2Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  D2Parser::stack_symbol_type::stack_symbol_type ()
  {}

  D2Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 71: // value
      case 75: // map_value
      case 99: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 59: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 58: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 57: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 56: // "constant string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  D2Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 71: // value
      case 75: // map_value
      case 99: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 59: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 58: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 57: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 56: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  D2Parser::stack_symbol_type&
  D2Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 71: // value
      case 75: // map_value
      case 99: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 59: // "boolean"
        value.move< bool > (that.value);
        break;

      case 58: // "floating point"
        value.move< double > (that.value);
        break;

      case 57: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 56: // "constant string"
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
  D2Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if D2_PARSER_DEBUG
  template <typename Base>
  void
  D2Parser::yy_print_ (std::ostream& yyo,
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
      case 56: // "constant string"
#line 115 "d2_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 392 "d2_parser.cc" // lalr1.cc:676
        break;

      case 57: // "integer"
#line 115 "d2_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 398 "d2_parser.cc" // lalr1.cc:676
        break;

      case 58: // "floating point"
#line 115 "d2_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 404 "d2_parser.cc" // lalr1.cc:676
        break;

      case 59: // "boolean"
#line 115 "d2_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 410 "d2_parser.cc" // lalr1.cc:676
        break;

      case 71: // value
#line 115 "d2_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 416 "d2_parser.cc" // lalr1.cc:676
        break;

      case 75: // map_value
#line 115 "d2_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 422 "d2_parser.cc" // lalr1.cc:676
        break;

      case 99: // ncr_protocol_value
#line 115 "d2_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "d2_parser.cc" // lalr1.cc:676
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  D2Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  D2Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  D2Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if D2_PARSER_DEBUG
  std::ostream&
  D2Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  D2Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  D2Parser::debug_level_type
  D2Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  D2Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // D2_PARSER_DEBUG

  D2Parser::state_type
  D2Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  D2Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  D2Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  D2Parser::operator() ()
  {
    return parse ();
  }

  int
  D2Parser::parse ()
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
      case 71: // value
      case 75: // map_value
      case 99: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 59: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 58: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 57: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 56: // "constant string"
        yylhs.value.emplace< std::string > ();
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
  case 2:
#line 124 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "d2_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 125 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "d2_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 126 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 702 "d2_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 127 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 708 "d2_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 128 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 714 "d2_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 129 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 720 "d2_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 130 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 726 "d2_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 131 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 732 "d2_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 132 "d2_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 738 "d2_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 140 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 744 "d2_parser.cc" // lalr1.cc:919
    break;

  case 21:
#line 141 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 750 "d2_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 142 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 756 "d2_parser.cc" // lalr1.cc:919
    break;

  case 23:
#line 143 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 762 "d2_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 144 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 768 "d2_parser.cc" // lalr1.cc:919
    break;

  case 25:
#line 145 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 774 "d2_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 146 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 780 "d2_parser.cc" // lalr1.cc:919
    break;

  case 27:
#line 149 "d2_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 789 "d2_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 154 "d2_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 800 "d2_parser.cc" // lalr1.cc:919
    break;

  case 29:
#line 159 "d2_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 810 "d2_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 165 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 816 "d2_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 172 "d2_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 825 "d2_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 176 "d2_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 835 "d2_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 183 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 844 "d2_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 186 "d2_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 852 "d2_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 194 "d2_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 861 "d2_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 198 "d2_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 870 "d2_parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 209 "d2_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 881 "d2_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 219 "d2_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 892 "d2_parser.cc" // lalr1.cc:919
    break;

  case 43:
#line 224 "d2_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 902 "d2_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 246 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 913 "d2_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 251 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 922 "d2_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 256 "d2_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 932 "d2_parser.cc" // lalr1.cc:919
    break;

  case 55:
#line 260 "d2_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 940 "d2_parser.cc" // lalr1.cc:919
    break;

  case 70:
#line 283 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 948 "d2_parser.cc" // lalr1.cc:919
    break;

  case 71:
#line 285 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 958 "d2_parser.cc" // lalr1.cc:919
    break;

  case 72:
#line 291 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 970 "d2_parser.cc" // lalr1.cc:919
    break;

  case 73:
#line 299 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 983 "d2_parser.cc" // lalr1.cc:919
    break;

  case 74:
#line 308 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 991 "d2_parser.cc" // lalr1.cc:919
    break;

  case 75:
#line 310 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1000 "d2_parser.cc" // lalr1.cc:919
    break;

  case 76:
#line 316 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1006 "d2_parser.cc" // lalr1.cc:919
    break;

  case 77:
#line 317 "d2_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1012 "d2_parser.cc" // lalr1.cc:919
    break;

  case 78:
#line 320 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1020 "d2_parser.cc" // lalr1.cc:919
    break;

  case 79:
#line 322 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1030 "d2_parser.cc" // lalr1.cc:919
    break;

  case 80:
#line 328 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1038 "d2_parser.cc" // lalr1.cc:919
    break;

  case 81:
#line 330 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as < ElementPtr > ();
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
#line 1065 "d2_parser.cc" // lalr1.cc:919
    break;

  case 82:
#line 353 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1073 "d2_parser.cc" // lalr1.cc:919
    break;

  case 83:
#line 355 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
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
#line 1102 "d2_parser.cc" // lalr1.cc:919
    break;

  case 84:
#line 380 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1113 "d2_parser.cc" // lalr1.cc:919
    break;

  case 85:
#line 385 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1122 "d2_parser.cc" // lalr1.cc:919
    break;

  case 86:
#line 390 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1133 "d2_parser.cc" // lalr1.cc:919
    break;

  case 87:
#line 395 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "d2_parser.cc" // lalr1.cc:919
    break;

  case 94:
#line 414 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1153 "d2_parser.cc" // lalr1.cc:919
    break;

  case 95:
#line 419 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "d2_parser.cc" // lalr1.cc:919
    break;

  case 96:
#line 424 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1171 "d2_parser.cc" // lalr1.cc:919
    break;

  case 97:
#line 427 "d2_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 1179 "d2_parser.cc" // lalr1.cc:919
    break;

  case 102:
#line 439 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1189 "d2_parser.cc" // lalr1.cc:919
    break;

  case 103:
#line 443 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1197 "d2_parser.cc" // lalr1.cc:919
    break;

  case 104:
#line 447 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1206 "d2_parser.cc" // lalr1.cc:919
    break;

  case 105:
#line 450 "d2_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 1214 "d2_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 467 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1222 "d2_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 469 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1236 "d2_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 479 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1244 "d2_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 481 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1255 "d2_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 491 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1266 "d2_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 496 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1275 "d2_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 501 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1284 "d2_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 504 "d2_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 1292 "d2_parser.cc" // lalr1.cc:919
    break;

  case 124:
#line 512 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1302 "d2_parser.cc" // lalr1.cc:919
    break;

  case 125:
#line 516 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1310 "d2_parser.cc" // lalr1.cc:919
    break;

  case 126:
#line 520 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1319 "d2_parser.cc" // lalr1.cc:919
    break;

  case 127:
#line 523 "d2_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 1327 "d2_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 539 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "d2_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 541 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1349 "d2_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 551 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1357 "d2_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 553 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1367 "d2_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 559 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1379 "d2_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 573 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1390 "d2_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 578 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1399 "d2_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 583 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1408 "d2_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 586 "d2_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 1416 "d2_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 598 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1426 "d2_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 602 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1434 "d2_parser.cc" // lalr1.cc:919
    break;

  case 151:
#line 606 "d2_parser.yy" // lalr1.cc:919
    {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1444 "d2_parser.cc" // lalr1.cc:919
    break;

  case 152:
#line 610 "d2_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 1452 "d2_parser.cc" // lalr1.cc:919
    break;

  case 162:
#line 628 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1460 "d2_parser.cc" // lalr1.cc:919
    break;

  case 163:
#line 630 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1474 "d2_parser.cc" // lalr1.cc:919
    break;

  case 164:
#line 640 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "d2_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 642 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1495 "d2_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 651 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1507 "d2_parser.cc" // lalr1.cc:919
    break;

  case 167:
#line 659 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1515 "d2_parser.cc" // lalr1.cc:919
    break;

  case 168:
#line 661 "d2_parser.yy" // lalr1.cc:919
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1528 "d2_parser.cc" // lalr1.cc:919
    break;

  case 169:
#line 675 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1539 "d2_parser.cc" // lalr1.cc:919
    break;

  case 170:
#line 680 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1548 "d2_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 696 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1556 "d2_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 698 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1566 "d2_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 704 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "d2_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 706 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1584 "d2_parser.cc" // lalr1.cc:919
    break;

  case 182:
#line 714 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1592 "d2_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 716 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1601 "d2_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 721 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1609 "d2_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 723 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1618 "d2_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 728 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1626 "d2_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 730 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1635 "d2_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 740 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1646 "d2_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 745 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1655 "d2_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 762 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1666 "d2_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 767 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1675 "d2_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 779 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1685 "d2_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 783 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1693 "d2_parser.cc" // lalr1.cc:919
    break;

  case 208:
#line 800 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1701 "d2_parser.cc" // lalr1.cc:919
    break;

  case 209:
#line 802 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1711 "d2_parser.cc" // lalr1.cc:919
    break;

  case 210:
#line 808 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1720 "d2_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 812 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "d2_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 814 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1738 "d2_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 820 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1749 "d2_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 825 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1758 "d2_parser.cc" // lalr1.cc:919
    break;

  case 217:
#line 834 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1768 "d2_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 838 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 1776 "d2_parser.cc" // lalr1.cc:919
    break;

  case 225:
#line 852 "d2_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1784 "d2_parser.cc" // lalr1.cc:919
    break;

  case 226:
#line 854 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1794 "d2_parser.cc" // lalr1.cc:919
    break;

  case 227:
#line 860 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1803 "d2_parser.cc" // lalr1.cc:919
    break;

  case 228:
#line 865 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1812 "d2_parser.cc" // lalr1.cc:919
    break;

  case 229:
#line 870 "d2_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1821 "d2_parser.cc" // lalr1.cc:919
    break;


#line 1825 "d2_parser.cc" // lalr1.cc:919
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
  D2Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  D2Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char D2Parser::yypact_ninf_ = -92;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
      50,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
      12,     2,     1,    23,    42,    11,    44,    17,    59,    65,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,     2,    18,
       8,     9,    15,    87,    40,    99,    13,   100,   -92,   102,
     122,   129,   118,   131,   -92,   -92,   -92,   -92,   -92,   137,
     -92,    49,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   139,
     147,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
      78,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   157,   -92,   -92,   -92,   -92,   -92,
      79,   -92,   -92,   -92,   -92,   -92,   -92,   164,   132,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,    85,   -92,   -92,   -92,
     -92,   -92,   167,   150,   -92,   -92,   158,   -92,   -92,   -92,
     -92,   106,   -92,   -92,   -92,   -92,   -92,    47,   -92,   -92,
       2,     2,   -92,   107,   170,   171,   172,   173,   174,   -92,
       8,   -92,   175,   123,   125,   177,   179,   180,   181,   182,
     183,   184,   185,     9,   -92,   186,   134,   188,   189,    15,
     -92,    15,   -92,    87,   190,   191,   192,    40,   -92,    40,
     -92,    99,   193,   141,   195,    13,   -92,    13,   100,   -92,
     -92,   -92,   196,     2,     2,     2,   194,   201,   -92,   153,
     -92,   -92,    22,   198,   203,   155,   205,   206,   209,   208,
     -92,   160,   -92,   161,   168,   -92,   112,   -92,   169,   215,
     176,   -92,   113,   -92,   178,   -92,   187,   -92,   114,   -92,
       2,   -92,   -92,   -92,     9,   197,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -12,   -12,    87,    55,   -92,   -92,
     -92,   -92,   -92,   100,   -92,   -92,   -92,   -92,   -92,   -92,
     115,   -92,   116,   -92,   -92,   -92,   -92,   124,   -92,   -92,
     -92,   146,   216,   -92,   -92,   -92,   -92,   -92,   149,   -92,
     -92,   -92,    89,   -92,   199,   197,   -92,   217,   -12,   -92,
     -92,   -92,   219,   222,    55,   -92,   -92,   223,   -92,   224,
     -92,   200,   202,   -92,   220,    99,   -92,   -92,   -92,   165,
     -92,   225,    33,   220,   -92,   -92,   -92,   -92,   226,   -92,
     -92,   -92,   -92,   152,   -92,   -92,   -92,   -92,   -92,   -92,
     229,   232,   204,   233,    33,   -92,   207,   234,   -92,   210,
     -92,   -92,   231,   -92,   -92,   166,   -92,    39,   231,   -92,
     -92,   236,   237,   238,   156,   -92,   -92,   -92,   -92,   -92,
     -92,   240,   211,   212,   218,    39,   -92,   221,   -92,   -92,
     -92,   -92,   -92
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    35,    28,    24,    23,    20,    21,    22,    27,     3,
      25,    26,    42,     5,    54,     7,   151,     9,   143,    11,
     104,    13,    96,    15,   126,    17,   120,    19,    37,    31,
       0,     0,     0,   145,     0,    98,     0,     0,    39,     0,
      38,     0,     0,    32,   182,   184,   186,    52,   188,     0,
      51,     0,    44,    49,    46,    48,    50,    47,    70,     0,
       0,    74,    78,    80,    82,    84,    86,   141,   169,    69,
       0,    56,    58,    59,    60,    61,    62,    67,    68,    63,
      64,    65,    66,   164,     0,   167,   162,   161,   159,   160,
       0,   153,   155,   156,   157,   158,   149,     0,   146,   147,
     116,   118,   114,   113,   111,   112,     0,   106,   108,   109,
     110,   102,     0,    99,   100,   138,     0,   136,   135,   133,
     134,     0,   128,   130,   131,   132,   124,     0,   122,    36,
       0,     0,    29,     0,     0,     0,     0,     0,     0,    41,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,     0,     0,     0,     0,     0,
     152,     0,   144,     0,     0,     0,     0,     0,   105,     0,
      97,     0,     0,     0,     0,     0,   127,     0,     0,   121,
      40,    33,     0,     0,     0,     0,     0,     0,    45,     0,
      72,    73,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,   166,     0,     0,   154,     0,   148,     0,     0,
       0,   107,     0,   101,     0,   140,     0,   129,     0,   123,
       0,   183,   185,   187,     0,     0,    71,    76,    77,    75,
      79,    30,    81,    83,    88,    88,   145,     0,   165,   168,
     163,   150,   117,     0,   115,   103,   139,   137,   125,    34,
       0,   193,     0,   190,   192,    94,    93,     0,    89,    90,
      92,     0,     0,   178,   180,   177,   175,   176,     0,   171,
     173,   174,     0,    53,     0,     0,   189,     0,     0,    85,
      87,   142,     0,     0,     0,   170,   119,     0,   191,     0,
      91,     0,     0,   172,     0,    98,   179,   181,   197,     0,
     195,     0,     0,     0,   194,    95,   208,   213,     0,   211,
     207,   205,   206,     0,   199,   201,   203,   204,   202,   196,
       0,     0,     0,     0,     0,   198,     0,     0,   210,     0,
     200,   209,     0,   212,   217,     0,   215,     0,     0,   214,
     225,     0,     0,     0,     0,   219,   221,   222,   223,   224,
     216,     0,     0,     0,     0,     0,   218,     0,   227,   228,
     229,   220,   226
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -38,   -92,    31,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -50,   -92,   -92,   -92,    86,   -92,   -92,   -92,
     -92,     3,    76,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -51,   -92,   -39,   -92,   -92,   -92,   -92,   -92,
      -5,   -92,   -47,   -92,   -92,   -92,   -92,   -63,   -92,    64,
     -92,   -92,   -92,    68,    72,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,    -3,    66,   -92,   -92,   -92,    70,    67,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,    20,
     -92,    90,   -92,   -92,   -92,    93,   101,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -36,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -17,   -92,   -92,   -92,   -44,   -92,   -92,   -62,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -77,   -92,   -92,
     -91,   -92,   -92,   -92,   -92,   -92
  };

  const short
  D2Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    49,   252,    62,    63,    31,    48,
      59,    60,    89,    33,    50,    71,    72,    73,   157,    35,
      51,    90,    91,    92,   162,    93,    94,    95,   165,   249,
      96,   166,    97,   167,    98,   168,    99,   169,   100,   170,
     277,   278,   279,   280,   297,    43,    55,   132,   133,   134,
     189,    41,    54,   126,   127,   128,   186,   129,   184,   130,
     185,    47,    57,   147,   148,   197,    45,    56,   141,   142,
     143,   194,   144,   192,   145,   101,   171,    39,    53,   117,
     118,   119,   181,    37,    52,   110,   111,   112,   178,   113,
     175,   114,   115,   177,   102,   172,   288,   289,   290,   302,
     291,   303,    74,   154,    75,   155,    76,   156,    77,   158,
     272,   273,   274,   294,   319,   320,   322,   333,   334,   335,
     340,   336,   337,   343,   338,   341,   355,   356,   357,   364,
     365,   366,   371,   367,   368,   369
  };

  const unsigned short
  D2Parser::yytable_[] =
  {
      70,   108,   107,   124,   123,   139,   138,    21,    32,    22,
      58,    23,    20,   109,   275,   125,    38,   140,    64,    65,
      66,    67,    42,    78,    79,    80,    81,   135,   136,    82,
      34,    83,    84,    85,    86,    83,    84,    83,    84,    87,
     247,   248,   137,    88,    69,    68,   103,   104,   105,    36,
     198,    40,   160,   199,   106,    83,    84,   161,    24,    25,
      26,    27,    83,    84,    69,    69,    44,   120,   121,    69,
      46,    69,   326,   327,    61,   328,   329,    83,    84,   122,
     360,   173,   179,   361,   362,   363,   174,   180,   187,    69,
     283,   284,   198,   188,   116,   306,    69,     1,     2,     3,
       4,     5,     6,     7,     8,     9,   131,   146,   149,   195,
      70,    69,   200,   201,   196,   179,   187,   195,   173,   295,
     261,   265,   268,   293,   296,   150,   152,   298,   108,   107,
     108,   107,   299,   151,   153,   183,   124,   123,   124,   123,
     109,   159,   109,   163,   139,   138,   139,   138,   125,   298,
     125,   164,   304,   191,   300,   344,   140,   305,   140,   375,
     345,   176,   193,   202,   376,   241,   242,   243,   323,   358,
     182,   324,   359,   190,   203,   204,   205,   206,   207,   209,
     210,   212,   211,   213,   214,   215,   216,   217,   218,   219,
     221,   222,   223,   224,   228,   229,   230,   234,   235,   236,
     240,   244,   269,   307,   276,   276,   286,   285,   245,   246,
      22,   253,   254,   255,   256,   257,   258,   259,   287,   250,
     263,   309,   301,   311,   260,   262,   312,   318,   314,   315,
     342,   325,   264,   346,   266,   271,   347,   349,   354,   352,
     372,   373,   374,   267,   377,   251,   208,   270,   276,   220,
     281,   310,   321,   286,   285,   233,   316,   232,   317,   231,
     292,   348,   237,   351,   239,   287,   353,   238,   313,   379,
     378,   331,   330,   227,   226,   380,   282,   382,   308,   339,
     225,   370,   350,   332,   381,     0,     0,     0,     0,     0,
       0,     0,     0,   331,   330,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   332
  };

  const short
  D2Parser::yycheck_[] =
  {
      50,    52,    52,    54,    54,    56,    56,     5,     7,     7,
      48,     9,     0,    52,    26,    54,     5,    56,    10,    11,
      12,    13,     5,    14,    15,    16,    17,    14,    15,    20,
       7,    22,    23,    24,    25,    22,    23,    22,    23,    30,
      18,    19,    29,    34,    56,    37,    31,    32,    33,     7,
       3,     7,     3,     6,    39,    22,    23,     8,    56,    57,
      58,    59,    22,    23,    56,    56,     7,    27,    28,    56,
       5,    56,    39,    40,    56,    42,    43,    22,    23,    39,
      41,     3,     3,    44,    45,    46,     8,     8,     3,    56,
      35,    36,     3,     8,     7,     6,    56,    47,    48,    49,
      50,    51,    52,    53,    54,    55,     7,     7,     6,     3,
     160,    56,   150,   151,     8,     3,     3,     3,     3,     3,
       8,     8,     8,     8,     8,     3,     8,     3,   179,   179,
     181,   181,     8,     4,     3,     3,   187,   187,   189,   189,
     179,     4,   181,     4,   195,   195,   197,   197,   187,     3,
     189,     4,     3,     3,     8,     3,   195,     8,   197,     3,
       8,     4,     4,    56,     8,   203,   204,   205,     3,     3,
       6,     6,     6,     6,     4,     4,     4,     4,     4,     4,
      57,     4,    57,     4,     4,     4,     4,     4,     4,     4,
       4,    57,     4,     4,     4,     4,     4,     4,    57,     4,
       4,     7,   240,     4,   254,   255,   257,   257,     7,    56,
       7,    56,     7,     7,     5,     7,    56,    56,   257,    21,
       5,     4,     6,     4,    56,    56,     4,     7,     5,     5,
       4,     6,    56,     4,    56,    38,     4,     4,     7,     5,
       4,     4,     4,    56,     4,   214,   160,   244,   298,   173,
     255,   298,   315,   304,   304,   191,    56,   189,    56,   187,
     263,    57,   195,    56,   198,   304,    56,   197,   304,    57,
      59,   322,   322,   183,   181,    57,   256,    56,   295,   323,
     179,   358,   344,   322,   375,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   344,   344,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   344
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
       0,     5,     7,     9,    56,    57,    58,    59,    71,    72,
      73,    78,     7,    83,     7,    89,     7,   153,     5,   147,
       7,   121,     5,   115,     7,   136,     5,   131,    79,    74,
      84,    90,   154,   148,   122,   116,   137,   132,    71,    80,
      81,    56,    76,    77,    10,    11,    12,    13,    37,    56,
      82,    85,    86,    87,   172,   174,   176,   178,    14,    15,
      16,    17,    20,    22,    23,    24,    25,    30,    34,    82,
      91,    92,    93,    95,    96,    97,   100,   102,   104,   106,
     108,   145,   164,    31,    32,    33,    39,    82,   102,   104,
     155,   156,   157,   159,   161,   162,     7,   149,   150,   151,
      27,    28,    39,    82,   102,   104,   123,   124,   125,   127,
     129,     7,   117,   118,   119,    14,    15,    29,    82,   102,
     104,   138,   139,   140,   142,   144,     7,   133,   134,     6,
       3,     4,     8,     3,   173,   175,   177,    88,   179,     4,
       3,     8,    94,     4,     4,    98,   101,   103,   105,   107,
     109,   146,   165,     3,     8,   160,     4,   163,   158,     3,
       8,   152,     6,     3,   128,   130,   126,     3,     8,   120,
       6,     3,   143,     4,   141,     3,     8,   135,     3,     6,
      71,    71,    56,     4,     4,     4,     4,     4,    86,     4,
      57,    57,     4,     4,     4,     4,     4,     4,     4,     4,
      92,     4,    57,     4,     4,   156,   155,   151,     4,     4,
       4,   124,   123,   119,     4,    57,     4,   139,   138,   134,
       4,    71,    71,    71,     7,     7,    56,    18,    19,    99,
      21,    73,    75,    56,     7,     7,     5,     7,    56,    56,
      56,     8,    56,     5,    56,     8,    56,    56,     8,    71,
      91,    38,   180,   181,   182,    26,    82,   110,   111,   112,
     113,   110,   149,    35,    36,    82,   102,   104,   166,   167,
     168,   170,   133,     8,   183,     3,     8,   114,     3,     8,
       8,     6,   169,   171,     3,     8,     6,     4,   181,     4,
     112,     4,     4,   167,     5,     5,    56,    56,     7,   184,
     185,   117,   186,     3,     6,     6,    39,    40,    42,    43,
      82,   102,   104,   187,   188,   189,   191,   192,   194,   185,
     190,   195,     4,   193,     3,     8,     4,     4,    57,     4,
     188,    56,     5,    56,     7,   196,   197,   198,     3,     6,
      41,    44,    45,    46,   199,   200,   201,   203,   204,   205,
     197,   202,     4,     4,     4,     3,     8,     4,    59,    57,
      57,   200,    56
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    60,    62,    61,    63,    61,    64,    61,    65,    61,
      66,    61,    67,    61,    68,    61,    69,    61,    70,    61,
      71,    71,    71,    71,    71,    71,    71,    72,    74,    73,
      75,    76,    76,    77,    77,    79,    78,    80,    80,    81,
      81,    82,    84,    83,    85,    85,    86,    86,    86,    86,
      86,    86,    88,    87,    90,    89,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      94,    93,    95,    96,    98,    97,    99,    99,   101,   100,
     103,   102,   105,   104,   107,   106,   109,   108,   110,   110,
     111,   111,   112,   112,   114,   113,   116,   115,   117,   117,
     118,   118,   120,   119,   122,   121,   123,   123,   124,   124,
     124,   124,   124,   124,   126,   125,   128,   127,   130,   129,
     132,   131,   133,   133,   135,   134,   137,   136,   138,   138,
     139,   139,   139,   139,   139,   139,   141,   140,   143,   142,
     144,   146,   145,   148,   147,   149,   149,   150,   150,   152,
     151,   154,   153,   155,   155,   156,   156,   156,   156,   156,
     156,   156,   158,   157,   160,   159,   161,   163,   162,   165,
     164,   166,   166,   167,   167,   167,   167,   167,   169,   168,
     171,   170,   173,   172,   175,   174,   177,   176,   179,   178,
     180,   180,   181,   183,   182,   184,   184,   186,   185,   187,
     187,   188,   188,   188,   188,   188,   188,   188,   190,   189,
     191,   193,   192,   195,   194,   196,   196,   198,   197,   199,
     199,   200,   200,   200,   200,   202,   201,   203,   204,   205
  };

  const unsigned char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     6,     0,     1,
       1,     3,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const D2Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"Dhcp4\"",
  "\"Control-agent\"", "\"DhcpDdns\"", "\"ip-address\"", "\"port\"",
  "\"dns-server-timeout\"", "\"ncr-protocol\"", "\"UDP\"", "\"TCP\"",
  "\"ncr-format\"", "\"JSON\"", "\"user-context\"", "\"comment\"",
  "\"forward-ddns\"", "\"reverse-ddns\"", "\"ddns-domains\"",
  "\"key-name\"", "\"dns-servers\"", "\"hostname\"", "\"tsig-keys\"",
  "\"algorithm\"", "\"digest-bits\"", "\"secret\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"Logging\"", "\"loggers\"",
  "\"name\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS", "SUB_TSIG_KEY",
  "SUB_TSIG_KEYS", "SUB_DDNS_DOMAIN", "SUB_DDNS_DOMAINS", "SUB_DNS_SERVER",
  "SUB_DNS_SERVERS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "value", "sub_json",
  "map2", "$@10", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@11", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@12", "global_objects",
  "global_object", "dhcpddns_object", "$@13", "sub_dhcpddns", "$@14",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@15", "port",
  "dns_server_timeout", "ncr_protocol", "$@16", "ncr_protocol_value",
  "ncr_format", "$@17", "user_context", "$@18", "comment", "$@19",
  "forward_ddns", "$@20", "reverse_ddns", "$@21", "ddns_mgr_params",
  "not_empty_ddns_mgr_params", "ddns_mgr_param", "ddns_domains", "$@22",
  "sub_ddns_domains", "$@23", "ddns_domain_list",
  "not_empty_ddns_domain_list", "ddns_domain", "$@24", "sub_ddns_domain",
  "$@25", "ddns_domain_params", "ddns_domain_param", "ddns_domain_name",
  "$@26", "ddns_domain_key_name", "$@27", "dns_servers", "$@28",
  "sub_dns_servers", "$@29", "dns_server_list", "dns_server", "$@30",
  "sub_dns_server", "$@31", "dns_server_params", "dns_server_param",
  "dns_server_hostname", "$@32", "dns_server_ip_address", "$@33",
  "dns_server_port", "tsig_keys", "$@34", "sub_tsig_keys", "$@35",
  "tsig_keys_list", "not_empty_tsig_keys_list", "tsig_key", "$@36",
  "sub_tsig_key", "$@37", "tsig_key_params", "tsig_key_param",
  "tsig_key_name", "$@38", "tsig_key_algorithm", "$@39",
  "tsig_key_digest_bits", "tsig_key_secret", "$@40", "control_socket",
  "$@41", "control_socket_params", "control_socket_param",
  "control_socket_type", "$@42", "control_socket_name", "$@43",
  "dhcp6_json_object", "$@44", "dhcp4_json_object", "$@45",
  "control_agent_json_object", "$@46", "logging_object", "$@47",
  "logging_params", "logging_param", "loggers", "$@48", "loggers_entries",
  "logger_entry", "$@49", "logger_params", "logger_param", "name", "$@50",
  "debuglevel", "severity", "$@51", "output_options_list", "$@52",
  "output_options_list_content", "output_entry", "$@53",
  "output_params_list", "output_params", "output", "$@54", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short
  D2Parser::yyrline_[] =
  {
       0,   124,   124,   124,   125,   125,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   132,   132,
     140,   141,   142,   143,   144,   145,   146,   149,   154,   154,
     165,   168,   169,   172,   176,   183,   183,   190,   191,   194,
     198,   209,   219,   219,   231,   232,   236,   237,   238,   239,
     240,   241,   246,   246,   256,   256,   264,   265,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     283,   283,   291,   299,   308,   308,   316,   317,   320,   320,
     328,   328,   353,   353,   380,   380,   390,   390,   400,   401,
     404,   405,   408,   409,   414,   414,   424,   424,   431,   432,
     435,   436,   439,   439,   447,   447,   454,   455,   458,   459,
     460,   461,   462,   463,   467,   467,   479,   479,   491,   491,
     501,   501,   508,   509,   512,   512,   520,   520,   527,   528,
     531,   532,   533,   534,   535,   536,   539,   539,   551,   551,
     559,   573,   573,   583,   583,   590,   591,   594,   595,   598,
     598,   606,   606,   615,   616,   619,   620,   621,   622,   623,
     624,   625,   628,   628,   640,   640,   651,   659,   659,   675,
     675,   685,   686,   689,   690,   691,   692,   693,   696,   696,
     704,   704,   714,   714,   721,   721,   728,   728,   740,   740,
     753,   754,   758,   762,   762,   774,   775,   779,   779,   787,
     788,   791,   792,   793,   794,   795,   796,   797,   800,   800,
     808,   812,   812,   820,   820,   830,   831,   834,   834,   842,
     843,   846,   847,   848,   849,   852,   852,   860,   865,   870
  };

  // Print the state stack on the debug stream.
  void
  D2Parser::yystack_print_ ()
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
  D2Parser::yy_reduce_print_ (int yyrule)
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
#endif // D2_PARSER_DEBUG


#line 14 "d2_parser.yy" // lalr1.cc:1242
} } // isc::d2
#line 2516 "d2_parser.cc" // lalr1.cc:1242
#line 875 "d2_parser.yy" // lalr1.cc:1243


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
