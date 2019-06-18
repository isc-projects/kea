// A Bison parser, made by GNU Bison 3.4.1.

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
#line 34 "d2_parser.yy"

#include <d2/parser_context.h>

#line 51 "d2_parser.cc"


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

#line 14 "d2_parser.yy"
namespace isc { namespace d2 {
#line 146 "d2_parser.cc"


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
#line 115 "d2_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 393 "d2_parser.cc"
        break;

      case 57: // "integer"
#line 115 "d2_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 399 "d2_parser.cc"
        break;

      case 58: // "floating point"
#line 115 "d2_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 405 "d2_parser.cc"
        break;

      case 59: // "boolean"
#line 115 "d2_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 411 "d2_parser.cc"
        break;

      case 71: // value
#line 115 "d2_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 417 "d2_parser.cc"
        break;

      case 75: // map_value
#line 115 "d2_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 423 "d2_parser.cc"
        break;

      case 99: // ncr_protocol_value
#line 115 "d2_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "d2_parser.cc"
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
#line 124 "d2_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 691 "d2_parser.cc"
    break;

  case 4:
#line 125 "d2_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 697 "d2_parser.cc"
    break;

  case 6:
#line 126 "d2_parser.yy"
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 703 "d2_parser.cc"
    break;

  case 8:
#line 127 "d2_parser.yy"
    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 709 "d2_parser.cc"
    break;

  case 10:
#line 128 "d2_parser.yy"
    { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 715 "d2_parser.cc"
    break;

  case 12:
#line 129 "d2_parser.yy"
    { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 721 "d2_parser.cc"
    break;

  case 14:
#line 130 "d2_parser.yy"
    { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 727 "d2_parser.cc"
    break;

  case 16:
#line 131 "d2_parser.yy"
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 733 "d2_parser.cc"
    break;

  case 18:
#line 132 "d2_parser.yy"
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 739 "d2_parser.cc"
    break;

  case 20:
#line 140 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 745 "d2_parser.cc"
    break;

  case 21:
#line 141 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 751 "d2_parser.cc"
    break;

  case 22:
#line 142 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 757 "d2_parser.cc"
    break;

  case 23:
#line 143 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 763 "d2_parser.cc"
    break;

  case 24:
#line 144 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 769 "d2_parser.cc"
    break;

  case 25:
#line 145 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 775 "d2_parser.cc"
    break;

  case 26:
#line 146 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 781 "d2_parser.cc"
    break;

  case 27:
#line 149 "d2_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 790 "d2_parser.cc"
    break;

  case 28:
#line 154 "d2_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 801 "d2_parser.cc"
    break;

  case 29:
#line 159 "d2_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 811 "d2_parser.cc"
    break;

  case 30:
#line 165 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 817 "d2_parser.cc"
    break;

  case 33:
#line 172 "d2_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 826 "d2_parser.cc"
    break;

  case 34:
#line 176 "d2_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 836 "d2_parser.cc"
    break;

  case 35:
#line 183 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 845 "d2_parser.cc"
    break;

  case 36:
#line 186 "d2_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 853 "d2_parser.cc"
    break;

  case 39:
#line 194 "d2_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 862 "d2_parser.cc"
    break;

  case 40:
#line 198 "d2_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 871 "d2_parser.cc"
    break;

  case 41:
#line 209 "d2_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 882 "d2_parser.cc"
    break;

  case 42:
#line 219 "d2_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 893 "d2_parser.cc"
    break;

  case 43:
#line 224 "d2_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 903 "d2_parser.cc"
    break;

  case 52:
#line 246 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 914 "d2_parser.cc"
    break;

  case 53:
#line 251 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 923 "d2_parser.cc"
    break;

  case 54:
#line 256 "d2_parser.yy"
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 933 "d2_parser.cc"
    break;

  case 55:
#line 260 "d2_parser.yy"
    {
    // parsing completed
}
#line 941 "d2_parser.cc"
    break;

  case 71:
#line 284 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 949 "d2_parser.cc"
    break;

  case 72:
#line 286 "d2_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 959 "d2_parser.cc"
    break;

  case 73:
#line 292 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 971 "d2_parser.cc"
    break;

  case 74:
#line 300 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 984 "d2_parser.cc"
    break;

  case 75:
#line 309 "d2_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 992 "d2_parser.cc"
    break;

  case 76:
#line 311 "d2_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1001 "d2_parser.cc"
    break;

  case 77:
#line 317 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1007 "d2_parser.cc"
    break;

  case 78:
#line 318 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1013 "d2_parser.cc"
    break;

  case 79:
#line 321 "d2_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1021 "d2_parser.cc"
    break;

  case 80:
#line 323 "d2_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1031 "d2_parser.cc"
    break;

  case 81:
#line 329 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1039 "d2_parser.cc"
    break;

  case 82:
#line 331 "d2_parser.yy"
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
#line 1066 "d2_parser.cc"
    break;

  case 83:
#line 354 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1074 "d2_parser.cc"
    break;

  case 84:
#line 356 "d2_parser.yy"
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
#line 1103 "d2_parser.cc"
    break;

  case 85:
#line 381 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1114 "d2_parser.cc"
    break;

  case 86:
#line 386 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1123 "d2_parser.cc"
    break;

  case 87:
#line 391 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1134 "d2_parser.cc"
    break;

  case 88:
#line 396 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1143 "d2_parser.cc"
    break;

  case 95:
#line 415 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1154 "d2_parser.cc"
    break;

  case 96:
#line 420 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1163 "d2_parser.cc"
    break;

  case 97:
#line 425 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1172 "d2_parser.cc"
    break;

  case 98:
#line 428 "d2_parser.yy"
    {
    // parsing completed
}
#line 1180 "d2_parser.cc"
    break;

  case 103:
#line 440 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "d2_parser.cc"
    break;

  case 104:
#line 444 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1198 "d2_parser.cc"
    break;

  case 105:
#line 448 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1207 "d2_parser.cc"
    break;

  case 106:
#line 451 "d2_parser.yy"
    {
    // parsing completed
}
#line 1215 "d2_parser.cc"
    break;

  case 115:
#line 468 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1223 "d2_parser.cc"
    break;

  case 116:
#line 470 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1237 "d2_parser.cc"
    break;

  case 117:
#line 480 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1245 "d2_parser.cc"
    break;

  case 118:
#line 482 "d2_parser.yy"
    {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1256 "d2_parser.cc"
    break;

  case 119:
#line 492 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1267 "d2_parser.cc"
    break;

  case 120:
#line 497 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1276 "d2_parser.cc"
    break;

  case 121:
#line 502 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1285 "d2_parser.cc"
    break;

  case 122:
#line 505 "d2_parser.yy"
    {
    // parsing completed
}
#line 1293 "d2_parser.cc"
    break;

  case 125:
#line 513 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1303 "d2_parser.cc"
    break;

  case 126:
#line 517 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1311 "d2_parser.cc"
    break;

  case 127:
#line 521 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1320 "d2_parser.cc"
    break;

  case 128:
#line 524 "d2_parser.yy"
    {
    // parsing completed
}
#line 1328 "d2_parser.cc"
    break;

  case 137:
#line 540 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "d2_parser.cc"
    break;

  case 138:
#line 542 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1350 "d2_parser.cc"
    break;

  case 139:
#line 552 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1358 "d2_parser.cc"
    break;

  case 140:
#line 554 "d2_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1368 "d2_parser.cc"
    break;

  case 141:
#line 560 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1380 "d2_parser.cc"
    break;

  case 142:
#line 574 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1391 "d2_parser.cc"
    break;

  case 143:
#line 579 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1400 "d2_parser.cc"
    break;

  case 144:
#line 584 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1409 "d2_parser.cc"
    break;

  case 145:
#line 587 "d2_parser.yy"
    {
    // parsing completed
}
#line 1417 "d2_parser.cc"
    break;

  case 150:
#line 599 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1427 "d2_parser.cc"
    break;

  case 151:
#line 603 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1435 "d2_parser.cc"
    break;

  case 152:
#line 607 "d2_parser.yy"
    {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1445 "d2_parser.cc"
    break;

  case 153:
#line 611 "d2_parser.yy"
    {
    // parsing completed
}
#line 1453 "d2_parser.cc"
    break;

  case 163:
#line 629 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1461 "d2_parser.cc"
    break;

  case 164:
#line 631 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1475 "d2_parser.cc"
    break;

  case 165:
#line 641 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1483 "d2_parser.cc"
    break;

  case 166:
#line 643 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1496 "d2_parser.cc"
    break;

  case 167:
#line 652 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1508 "d2_parser.cc"
    break;

  case 168:
#line 660 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "d2_parser.cc"
    break;

  case 169:
#line 662 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1529 "d2_parser.cc"
    break;

  case 170:
#line 676 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1540 "d2_parser.cc"
    break;

  case 171:
#line 681 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1549 "d2_parser.cc"
    break;

  case 179:
#line 697 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1557 "d2_parser.cc"
    break;

  case 180:
#line 699 "d2_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1567 "d2_parser.cc"
    break;

  case 181:
#line 705 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1575 "d2_parser.cc"
    break;

  case 182:
#line 707 "d2_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1585 "d2_parser.cc"
    break;

  case 183:
#line 715 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1593 "d2_parser.cc"
    break;

  case 184:
#line 717 "d2_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1602 "d2_parser.cc"
    break;

  case 185:
#line 722 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1610 "d2_parser.cc"
    break;

  case 186:
#line 724 "d2_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1619 "d2_parser.cc"
    break;

  case 187:
#line 729 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "d2_parser.cc"
    break;

  case 188:
#line 731 "d2_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1636 "d2_parser.cc"
    break;

  case 189:
#line 741 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1647 "d2_parser.cc"
    break;

  case 190:
#line 746 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1656 "d2_parser.cc"
    break;

  case 194:
#line 763 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1667 "d2_parser.cc"
    break;

  case 195:
#line 768 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "d2_parser.cc"
    break;

  case 198:
#line 780 "d2_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1686 "d2_parser.cc"
    break;

  case 199:
#line 784 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1694 "d2_parser.cc"
    break;

  case 209:
#line 801 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1702 "d2_parser.cc"
    break;

  case 210:
#line 803 "d2_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1712 "d2_parser.cc"
    break;

  case 211:
#line 809 "d2_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1721 "d2_parser.cc"
    break;

  case 212:
#line 813 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1729 "d2_parser.cc"
    break;

  case 213:
#line 815 "d2_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1739 "d2_parser.cc"
    break;

  case 214:
#line 821 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1750 "d2_parser.cc"
    break;

  case 215:
#line 826 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1759 "d2_parser.cc"
    break;

  case 218:
#line 835 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1769 "d2_parser.cc"
    break;

  case 219:
#line 839 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1777 "d2_parser.cc"
    break;

  case 226:
#line 853 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1785 "d2_parser.cc"
    break;

  case 227:
#line 855 "d2_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1795 "d2_parser.cc"
    break;

  case 228:
#line 861 "d2_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1804 "d2_parser.cc"
    break;

  case 229:
#line 866 "d2_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1813 "d2_parser.cc"
    break;

  case 230:
#line 871 "d2_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1822 "d2_parser.cc"
    break;


#line 1826 "d2_parser.cc"

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


  const short D2Parser::yypact_ninf_ = -238;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
      69,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
      16,     2,     7,    24,    34,    52,    38,    77,    48,   108,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,     2,    71,
       9,    10,    40,   121,    53,   128,    14,   129,  -238,   131,
     135,   140,   138,   151,  -238,  -238,  -238,  -238,  -238,   160,
    -238,    15,  -238,  -238,  -238,  -238,  -238,  -238,  -238,   161,
     162,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,    46,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,   167,  -238,  -238,  -238,
    -238,  -238,    66,  -238,  -238,  -238,  -238,  -238,  -238,   150,
     169,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    86,  -238,
    -238,  -238,  -238,  -238,   168,   170,  -238,  -238,   171,  -238,
    -238,  -238,  -238,    90,  -238,  -238,  -238,  -238,  -238,    36,
    -238,  -238,     2,     2,  -238,   120,   173,   174,   175,   176,
     177,  -238,     9,  -238,   178,   126,   127,   181,   182,   183,
     184,   185,   186,   187,   188,   189,    10,  -238,   190,   139,
     191,   193,    40,  -238,    40,  -238,   121,   194,   195,   196,
      53,  -238,    53,  -238,   128,   197,   145,   199,    14,  -238,
      14,   129,  -238,  -238,  -238,   200,     2,     2,     2,   198,
     205,  -238,   157,  -238,  -238,    88,   202,   207,   163,   208,
     209,   212,   211,   215,  -238,   165,  -238,   172,   179,  -238,
      92,  -238,   180,   219,   192,  -238,    94,  -238,   201,  -238,
     210,  -238,    96,  -238,     2,  -238,  -238,  -238,    10,   203,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,   -18,   -18,
     121,    55,   218,  -238,  -238,  -238,  -238,  -238,   129,  -238,
    -238,  -238,  -238,  -238,  -238,   100,   102,  -238,  -238,  -238,
    -238,   122,  -238,  -238,  -238,   149,   220,  -238,  -238,  -238,
    -238,  -238,   152,  -238,  -238,  -238,  -238,    50,  -238,    80,
    -238,   203,  -238,   223,   -18,  -238,  -238,  -238,   225,   226,
      55,  -238,    45,   218,  -238,  -238,  -238,   227,  -238,   213,
     214,  -238,  -238,  -238,   229,  -238,  -238,  -238,  -238,   155,
    -238,  -238,  -238,  -238,  -238,  -238,   128,  -238,  -238,   230,
     233,   206,   234,    45,  -238,   236,   216,   235,  -238,   221,
    -238,  -238,  -238,   224,  -238,  -238,   123,  -238,     6,   224,
    -238,  -238,   239,   240,   241,   159,  -238,  -238,  -238,  -238,
    -238,  -238,   242,   148,   217,   222,     6,  -238,   228,  -238,
    -238,  -238,  -238,  -238
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    35,    28,    24,    23,    20,    21,    22,    27,     3,
      25,    26,    42,     5,    54,     7,   152,     9,   144,    11,
     105,    13,    97,    15,   127,    17,   121,    19,    37,    31,
       0,     0,     0,   146,     0,    99,     0,     0,    39,     0,
      38,     0,     0,    32,   183,   185,   187,    52,   189,     0,
      51,     0,    44,    49,    46,    48,    50,    47,    71,     0,
       0,    75,    79,    81,    83,    85,    87,   142,   170,   194,
      70,     0,    56,    58,    59,    60,    61,    62,    68,    69,
      63,    64,    65,    66,    67,   165,     0,   168,   163,   162,
     160,   161,     0,   154,   156,   157,   158,   159,   150,     0,
     147,   148,   117,   119,   115,   114,   112,   113,     0,   107,
     109,   110,   111,   103,     0,   100,   101,   139,     0,   137,
     136,   134,   135,     0,   129,   131,   132,   133,   125,     0,
     123,    36,     0,     0,    29,     0,     0,     0,     0,     0,
       0,    41,     0,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    55,     0,     0,
       0,     0,     0,   153,     0,   145,     0,     0,     0,     0,
       0,   106,     0,    98,     0,     0,     0,     0,     0,   128,
       0,     0,   122,    40,    33,     0,     0,     0,     0,     0,
       0,    45,     0,    73,    74,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,     0,   167,     0,     0,   155,
       0,   149,     0,     0,     0,   108,     0,   102,     0,   141,
       0,   130,     0,   124,     0,   184,   186,   188,     0,     0,
      72,    77,    78,    76,    80,    30,    82,    84,    89,    89,
     146,     0,     0,   166,   169,   164,   151,   118,     0,   116,
     104,   140,   138,   126,    34,     0,     0,   191,   193,    95,
      94,     0,    90,    91,    93,     0,     0,   179,   181,   178,
     176,   177,     0,   172,   174,   175,   198,     0,   196,     0,
      53,     0,   190,     0,     0,    86,    88,   143,     0,     0,
       0,   171,     0,     0,   195,   120,   192,     0,    92,     0,
       0,   173,   209,   214,     0,   212,   208,   206,   207,     0,
     200,   202,   204,   205,   203,   197,    99,   180,   182,     0,
       0,     0,     0,     0,   199,     0,     0,     0,   211,     0,
     201,    96,   210,     0,   213,   218,     0,   216,     0,     0,
     215,   226,     0,     0,     0,     0,   220,   222,   223,   224,
     225,   217,     0,     0,     0,     0,     0,   219,     0,   228,
     229,   230,   221,   227
  };

  const short
  D2Parser::yypgoto_[] =
  {
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,   -38,  -238,    22,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,   -50,  -238,  -238,  -238,    85,  -238,  -238,  -238,
    -238,     1,    74,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,   -51,  -238,   -39,  -238,  -238,  -238,  -238,  -238,
      -8,  -238,   -52,  -238,  -238,  -238,  -238,   -83,  -238,    61,
    -238,  -238,  -238,    64,    68,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,    -4,    67,  -238,  -238,  -238,    65,    78,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    18,
    -238,    81,  -238,  -238,  -238,    91,    98,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,   -29,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,   -19,  -237,  -238,  -238,   -30,  -238,  -238,   -58,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,   -73,  -238,  -238,
     -89,  -238,  -238,  -238,  -238,  -238
  };

  const short
  D2Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    49,   256,    62,    63,    31,    48,
      59,    60,    90,    33,    50,    71,    72,    73,   159,    35,
      51,    91,    92,    93,   164,    94,    95,    96,   167,   253,
      97,   168,    98,   169,    99,   170,   100,   171,   101,   172,
     281,   282,   283,   284,   303,    43,    55,   134,   135,   136,
     192,    41,    54,   128,   129,   130,   189,   131,   187,   132,
     188,    47,    57,   149,   150,   200,    45,    56,   143,   144,
     145,   197,   146,   195,   147,   102,   173,    39,    53,   119,
     120,   121,   184,    37,    52,   112,   113,   114,   181,   115,
     178,   116,   117,   180,   103,   174,   292,   293,   294,   308,
     295,   309,    74,   156,    75,   157,    76,   158,    77,   160,
     276,   277,   104,   175,   297,   298,   312,   329,   330,   331,
     339,   332,   333,   342,   334,   340,   356,   357,   358,   365,
     366,   367,   372,   368,   369,   370
  };

  const unsigned short
  D2Parser::yytable_[] =
  {
      70,   110,   109,   126,   125,   141,   140,    21,   279,    22,
      58,    23,   278,   111,    32,   127,    20,   142,   162,    64,
      65,    66,    67,   163,    78,    79,    80,    81,   137,   138,
      82,    34,    83,    84,    85,    86,    83,    84,    69,   201,
      87,    36,   202,   139,    88,    40,    68,   361,    89,   176,
     362,   363,   364,   313,   177,    44,   314,    38,    24,    25,
      26,    27,    83,    84,   278,    69,    69,    83,    84,   182,
      69,   105,   106,   107,   183,    83,    84,    83,    84,   108,
     122,   123,    42,   201,   322,   323,   315,   324,   325,   190,
     287,   288,   124,   198,   191,   182,    69,   190,   199,   198,
     266,    69,   270,   176,   273,   301,   251,   252,   300,    69,
     302,    69,    70,    46,   203,   204,     1,     2,     3,     4,
       5,     6,     7,     8,     9,   304,   359,    61,   118,   360,
     305,   110,   109,   110,   109,   133,   148,   151,   152,   126,
     125,   126,   125,   111,   153,   111,   154,   141,   140,   141,
     140,   127,   304,   127,   155,   310,   185,   306,   343,   142,
     311,   142,   376,   344,   161,   165,   166,   377,   245,   246,
     247,   179,   186,   194,   193,   196,   205,   206,   207,   208,
     209,   210,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   225,   227,   226,   228,   232,   233,
     234,   238,   239,   240,   244,   248,   274,   379,   280,   280,
     290,   289,   249,   250,    22,   258,   259,   260,   261,   257,
     262,   263,   291,   254,   268,   296,   307,   317,   264,   319,
     320,   355,   336,   341,   346,   265,   267,   347,   349,   255,
     353,    89,   351,   373,   374,   375,   378,   211,   269,   275,
     224,   285,   318,   345,   280,   237,   236,   271,   235,   290,
     289,   327,   326,   348,   299,   242,   272,   231,   243,   337,
     338,   291,   352,   328,   380,   230,   241,   354,   286,   381,
     229,   321,   316,   335,   383,   350,   371,   382,     0,     0,
       0,     0,   327,   326,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   328
  };

  const short
  D2Parser::yycheck_[] =
  {
      50,    52,    52,    54,    54,    56,    56,     5,    26,     7,
      48,     9,   249,    52,     7,    54,     0,    56,     3,    10,
      11,    12,    13,     8,    14,    15,    16,    17,    14,    15,
      20,     7,    22,    23,    24,    25,    22,    23,    56,     3,
      30,     7,     6,    29,    34,     7,    37,    41,    38,     3,
      44,    45,    46,     3,     8,     7,     6,     5,    56,    57,
      58,    59,    22,    23,   301,    56,    56,    22,    23,     3,
      56,    31,    32,    33,     8,    22,    23,    22,    23,    39,
      27,    28,     5,     3,    39,    40,     6,    42,    43,     3,
      35,    36,    39,     3,     8,     3,    56,     3,     8,     3,
       8,    56,     8,     3,     8,     3,    18,    19,     8,    56,
       8,    56,   162,     5,   152,   153,    47,    48,    49,    50,
      51,    52,    53,    54,    55,     3,     3,    56,     7,     6,
       8,   182,   182,   184,   184,     7,     7,     6,     3,   190,
     190,   192,   192,   182,     4,   184,     8,   198,   198,   200,
     200,   190,     3,   192,     3,     3,     6,     8,     3,   198,
       8,   200,     3,     8,     4,     4,     4,     8,   206,   207,
     208,     4,     3,     3,     6,     4,    56,     4,     4,     4,
       4,     4,     4,    57,    57,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    57,     4,     4,     4,
       4,     4,    57,     4,     4,     7,   244,    59,   258,   259,
     261,   261,     7,    56,     7,     7,     7,     5,     7,    56,
       5,    56,   261,    21,     5,     7,     6,     4,    56,     4,
       4,     7,     5,     4,     4,    56,    56,     4,     4,   217,
       5,    38,     6,     4,     4,     4,     4,   162,    56,   248,
     176,   259,   304,   336,   304,   194,   192,    56,   190,   310,
     310,   312,   312,    57,   268,   200,    56,   186,   201,    56,
      56,   310,    56,   312,    57,   184,   198,    56,   260,    57,
     182,   310,   301,   313,    56,   343,   359,   376,    -1,    -1,
      -1,    -1,   343,   343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   343
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
      16,    17,    20,    22,    23,    24,    25,    30,    34,    38,
      82,    91,    92,    93,    95,    96,    97,   100,   102,   104,
     106,   108,   145,   164,   182,    31,    32,    33,    39,    82,
     102,   104,   155,   156,   157,   159,   161,   162,     7,   149,
     150,   151,    27,    28,    39,    82,   102,   104,   123,   124,
     125,   127,   129,     7,   117,   118,   119,    14,    15,    29,
      82,   102,   104,   138,   139,   140,   142,   144,     7,   133,
     134,     6,     3,     4,     8,     3,   173,   175,   177,    88,
     179,     4,     3,     8,    94,     4,     4,    98,   101,   103,
     105,   107,   109,   146,   165,   183,     3,     8,   160,     4,
     163,   158,     3,     8,   152,     6,     3,   128,   130,   126,
       3,     8,   120,     6,     3,   143,     4,   141,     3,     8,
     135,     3,     6,    71,    71,    56,     4,     4,     4,     4,
       4,    86,     4,    57,    57,     4,     4,     4,     4,     4,
       4,     4,     4,     4,    92,     4,    57,     4,     4,   156,
     155,   151,     4,     4,     4,   124,   123,   119,     4,    57,
       4,   139,   138,   134,     4,    71,    71,    71,     7,     7,
      56,    18,    19,    99,    21,    73,    75,    56,     7,     7,
       5,     7,     5,    56,    56,    56,     8,    56,     5,    56,
       8,    56,    56,     8,    71,    91,   180,   181,   182,    26,
      82,   110,   111,   112,   113,   110,   149,    35,    36,    82,
     102,   104,   166,   167,   168,   170,     7,   184,   185,   133,
       8,     3,     8,   114,     3,     8,     8,     6,   169,   171,
       3,     8,   186,     3,     6,     6,   181,     4,   112,     4,
       4,   167,    39,    40,    42,    43,    82,   102,   104,   187,
     188,   189,   191,   192,   194,   185,     5,    56,    56,   190,
     195,     4,   193,     3,     8,   117,     4,     4,    57,     4,
     188,     6,    56,     5,    56,     7,   196,   197,   198,     3,
       6,    41,    44,    45,    46,   199,   200,   201,   203,   204,
     205,   197,   202,     4,     4,     4,     3,     8,     4,    59,
      57,    57,   200,    56
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
      92,    94,    93,    95,    96,    98,    97,    99,    99,   101,
     100,   103,   102,   105,   104,   107,   106,   109,   108,   110,
     110,   111,   111,   112,   112,   114,   113,   116,   115,   117,
     117,   118,   118,   120,   119,   122,   121,   123,   123,   124,
     124,   124,   124,   124,   124,   126,   125,   128,   127,   130,
     129,   132,   131,   133,   133,   135,   134,   137,   136,   138,
     138,   139,   139,   139,   139,   139,   139,   141,   140,   143,
     142,   144,   146,   145,   148,   147,   149,   149,   150,   150,
     152,   151,   154,   153,   155,   155,   156,   156,   156,   156,
     156,   156,   156,   158,   157,   160,   159,   161,   163,   162,
     165,   164,   166,   166,   167,   167,   167,   167,   167,   169,
     168,   171,   170,   173,   172,   175,   174,   177,   176,   179,
     178,   180,   180,   181,   183,   182,   184,   184,   186,   185,
     187,   187,   188,   188,   188,   188,   188,   188,   188,   190,
     189,   191,   193,   192,   195,   194,   196,   196,   198,   197,
     199,   199,   200,   200,   200,   200,   202,   201,   203,   204,
     205
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
       1,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     6,     0,
       1,     1,     3,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
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
     281,   284,   284,   292,   300,   309,   309,   317,   318,   321,
     321,   329,   329,   354,   354,   381,   381,   391,   391,   401,
     402,   405,   406,   409,   410,   415,   415,   425,   425,   432,
     433,   436,   437,   440,   440,   448,   448,   455,   456,   459,
     460,   461,   462,   463,   464,   468,   468,   480,   480,   492,
     492,   502,   502,   509,   510,   513,   513,   521,   521,   528,
     529,   532,   533,   534,   535,   536,   537,   540,   540,   552,
     552,   560,   574,   574,   584,   584,   591,   592,   595,   596,
     599,   599,   607,   607,   616,   617,   620,   621,   622,   623,
     624,   625,   626,   629,   629,   641,   641,   652,   660,   660,
     676,   676,   686,   687,   690,   691,   692,   693,   694,   697,
     697,   705,   705,   715,   715,   722,   722,   729,   729,   741,
     741,   754,   755,   759,   763,   763,   775,   776,   780,   780,
     788,   789,   792,   793,   794,   795,   796,   797,   798,   801,
     801,   809,   813,   813,   821,   821,   831,   832,   835,   835,
     843,   844,   847,   848,   849,   850,   853,   853,   861,   866,
     871
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


#line 14 "d2_parser.yy"
} } // isc::d2
#line 2521 "d2_parser.cc"

#line 876 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
