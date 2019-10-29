// A Bison parser, made by GNU Bison 3.4.2.

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
#line 143 "d2_parser.cc"


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
      case 72: // value
      case 76: // map_value
      case 100: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 60: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 59: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 58: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 57: // "constant string"
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
      case 72: // value
      case 76: // map_value
      case 100: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 60: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 59: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 58: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 57: // "constant string"
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
      case 72: // value
      case 76: // map_value
      case 100: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 60: // "boolean"
        value.move< bool > (that.value);
        break;

      case 59: // "floating point"
        value.move< double > (that.value);
        break;

      case 58: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 57: // "constant string"
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
      case 57: // "constant string"
#line 116 "d2_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 390 "d2_parser.cc"
        break;

      case 58: // "integer"
#line 116 "d2_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 396 "d2_parser.cc"
        break;

      case 59: // "floating point"
#line 116 "d2_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 402 "d2_parser.cc"
        break;

      case 60: // "boolean"
#line 116 "d2_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 408 "d2_parser.cc"
        break;

      case 72: // value
#line 116 "d2_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "d2_parser.cc"
        break;

      case 76: // map_value
#line 116 "d2_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 420 "d2_parser.cc"
        break;

      case 100: // ncr_protocol_value
#line 116 "d2_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 426 "d2_parser.cc"
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
      case 72: // value
      case 76: // map_value
      case 100: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 60: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 59: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 58: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 57: // "constant string"
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
#line 125 "d2_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 688 "d2_parser.cc"
    break;

  case 4:
#line 126 "d2_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 694 "d2_parser.cc"
    break;

  case 6:
#line 127 "d2_parser.yy"
    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 700 "d2_parser.cc"
    break;

  case 8:
#line 128 "d2_parser.yy"
    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 706 "d2_parser.cc"
    break;

  case 10:
#line 129 "d2_parser.yy"
    { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 712 "d2_parser.cc"
    break;

  case 12:
#line 130 "d2_parser.yy"
    { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 718 "d2_parser.cc"
    break;

  case 14:
#line 131 "d2_parser.yy"
    { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 724 "d2_parser.cc"
    break;

  case 16:
#line 132 "d2_parser.yy"
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 730 "d2_parser.cc"
    break;

  case 18:
#line 133 "d2_parser.yy"
    { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 736 "d2_parser.cc"
    break;

  case 20:
#line 141 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "d2_parser.cc"
    break;

  case 21:
#line 142 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "d2_parser.cc"
    break;

  case 22:
#line 143 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "d2_parser.cc"
    break;

  case 23:
#line 144 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "d2_parser.cc"
    break;

  case 24:
#line 145 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 766 "d2_parser.cc"
    break;

  case 25:
#line 146 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "d2_parser.cc"
    break;

  case 26:
#line 147 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "d2_parser.cc"
    break;

  case 27:
#line 150 "d2_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 787 "d2_parser.cc"
    break;

  case 28:
#line 155 "d2_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "d2_parser.cc"
    break;

  case 29:
#line 160 "d2_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "d2_parser.cc"
    break;

  case 30:
#line 166 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "d2_parser.cc"
    break;

  case 33:
#line 173 "d2_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 823 "d2_parser.cc"
    break;

  case 34:
#line 177 "d2_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 833 "d2_parser.cc"
    break;

  case 35:
#line 184 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "d2_parser.cc"
    break;

  case 36:
#line 187 "d2_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 850 "d2_parser.cc"
    break;

  case 39:
#line 195 "d2_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 859 "d2_parser.cc"
    break;

  case 40:
#line 199 "d2_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 868 "d2_parser.cc"
    break;

  case 41:
#line 210 "d2_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 879 "d2_parser.cc"
    break;

  case 42:
#line 220 "d2_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "d2_parser.cc"
    break;

  case 43:
#line 225 "d2_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "d2_parser.cc"
    break;

  case 52:
#line 247 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 911 "d2_parser.cc"
    break;

  case 53:
#line 252 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 920 "d2_parser.cc"
    break;

  case 54:
#line 257 "d2_parser.yy"
    {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 930 "d2_parser.cc"
    break;

  case 55:
#line 261 "d2_parser.yy"
    {
    // parsing completed
}
#line 938 "d2_parser.cc"
    break;

  case 71:
#line 285 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 946 "d2_parser.cc"
    break;

  case 72:
#line 287 "d2_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 956 "d2_parser.cc"
    break;

  case 73:
#line 293 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 968 "d2_parser.cc"
    break;

  case 74:
#line 301 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 981 "d2_parser.cc"
    break;

  case 75:
#line 310 "d2_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 989 "d2_parser.cc"
    break;

  case 76:
#line 312 "d2_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 998 "d2_parser.cc"
    break;

  case 77:
#line 318 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1004 "d2_parser.cc"
    break;

  case 78:
#line 319 "d2_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1010 "d2_parser.cc"
    break;

  case 79:
#line 322 "d2_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1018 "d2_parser.cc"
    break;

  case 80:
#line 324 "d2_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1028 "d2_parser.cc"
    break;

  case 81:
#line 330 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1036 "d2_parser.cc"
    break;

  case 82:
#line 332 "d2_parser.yy"
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
#line 1063 "d2_parser.cc"
    break;

  case 83:
#line 355 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1071 "d2_parser.cc"
    break;

  case 84:
#line 357 "d2_parser.yy"
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
#line 1100 "d2_parser.cc"
    break;

  case 85:
#line 382 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1111 "d2_parser.cc"
    break;

  case 86:
#line 387 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "d2_parser.cc"
    break;

  case 87:
#line 392 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1131 "d2_parser.cc"
    break;

  case 88:
#line 397 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "d2_parser.cc"
    break;

  case 95:
#line 416 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1151 "d2_parser.cc"
    break;

  case 96:
#line 421 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "d2_parser.cc"
    break;

  case 97:
#line 426 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1169 "d2_parser.cc"
    break;

  case 98:
#line 429 "d2_parser.yy"
    {
    // parsing completed
}
#line 1177 "d2_parser.cc"
    break;

  case 103:
#line 441 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1187 "d2_parser.cc"
    break;

  case 104:
#line 445 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1195 "d2_parser.cc"
    break;

  case 105:
#line 449 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1204 "d2_parser.cc"
    break;

  case 106:
#line 452 "d2_parser.yy"
    {
    // parsing completed
}
#line 1212 "d2_parser.cc"
    break;

  case 115:
#line 469 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1220 "d2_parser.cc"
    break;

  case 116:
#line 471 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1234 "d2_parser.cc"
    break;

  case 117:
#line 481 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1242 "d2_parser.cc"
    break;

  case 118:
#line 483 "d2_parser.yy"
    {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1253 "d2_parser.cc"
    break;

  case 119:
#line 493 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1264 "d2_parser.cc"
    break;

  case 120:
#line 498 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1273 "d2_parser.cc"
    break;

  case 121:
#line 503 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1282 "d2_parser.cc"
    break;

  case 122:
#line 506 "d2_parser.yy"
    {
    // parsing completed
}
#line 1290 "d2_parser.cc"
    break;

  case 125:
#line 514 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1300 "d2_parser.cc"
    break;

  case 126:
#line 518 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1308 "d2_parser.cc"
    break;

  case 127:
#line 522 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1317 "d2_parser.cc"
    break;

  case 128:
#line 525 "d2_parser.yy"
    {
    // parsing completed
}
#line 1325 "d2_parser.cc"
    break;

  case 137:
#line 541 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1333 "d2_parser.cc"
    break;

  case 138:
#line 543 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1347 "d2_parser.cc"
    break;

  case 139:
#line 553 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1355 "d2_parser.cc"
    break;

  case 140:
#line 555 "d2_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1365 "d2_parser.cc"
    break;

  case 141:
#line 561 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1377 "d2_parser.cc"
    break;

  case 142:
#line 575 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1388 "d2_parser.cc"
    break;

  case 143:
#line 580 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1397 "d2_parser.cc"
    break;

  case 144:
#line 585 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1406 "d2_parser.cc"
    break;

  case 145:
#line 588 "d2_parser.yy"
    {
    // parsing completed
}
#line 1414 "d2_parser.cc"
    break;

  case 150:
#line 600 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1424 "d2_parser.cc"
    break;

  case 151:
#line 604 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1432 "d2_parser.cc"
    break;

  case 152:
#line 608 "d2_parser.yy"
    {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1442 "d2_parser.cc"
    break;

  case 153:
#line 612 "d2_parser.yy"
    {
    // parsing completed
}
#line 1450 "d2_parser.cc"
    break;

  case 163:
#line 630 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1458 "d2_parser.cc"
    break;

  case 164:
#line 632 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1472 "d2_parser.cc"
    break;

  case 165:
#line 642 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1480 "d2_parser.cc"
    break;

  case 166:
#line 644 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1493 "d2_parser.cc"
    break;

  case 167:
#line 653 "d2_parser.yy"
    {
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1505 "d2_parser.cc"
    break;

  case 168:
#line 661 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "d2_parser.cc"
    break;

  case 169:
#line 663 "d2_parser.yy"
    {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1526 "d2_parser.cc"
    break;

  case 170:
#line 677 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1537 "d2_parser.cc"
    break;

  case 171:
#line 682 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1546 "d2_parser.cc"
    break;

  case 179:
#line 698 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1554 "d2_parser.cc"
    break;

  case 180:
#line 700 "d2_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1564 "d2_parser.cc"
    break;

  case 181:
#line 706 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1572 "d2_parser.cc"
    break;

  case 182:
#line 708 "d2_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1582 "d2_parser.cc"
    break;

  case 183:
#line 716 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1590 "d2_parser.cc"
    break;

  case 184:
#line 718 "d2_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1599 "d2_parser.cc"
    break;

  case 185:
#line 723 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1607 "d2_parser.cc"
    break;

  case 186:
#line 725 "d2_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1616 "d2_parser.cc"
    break;

  case 187:
#line 730 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1624 "d2_parser.cc"
    break;

  case 188:
#line 732 "d2_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1633 "d2_parser.cc"
    break;

  case 189:
#line 742 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 1644 "d2_parser.cc"
    break;

  case 190:
#line 747 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1653 "d2_parser.cc"
    break;

  case 194:
#line 764 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1664 "d2_parser.cc"
    break;

  case 195:
#line 769 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1673 "d2_parser.cc"
    break;

  case 198:
#line 781 "d2_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1683 "d2_parser.cc"
    break;

  case 199:
#line 785 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1691 "d2_parser.cc"
    break;

  case 209:
#line 802 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "d2_parser.cc"
    break;

  case 210:
#line 804 "d2_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1709 "d2_parser.cc"
    break;

  case 211:
#line 810 "d2_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1718 "d2_parser.cc"
    break;

  case 212:
#line 814 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1726 "d2_parser.cc"
    break;

  case 213:
#line 816 "d2_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1736 "d2_parser.cc"
    break;

  case 214:
#line 822 "d2_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1747 "d2_parser.cc"
    break;

  case 215:
#line 827 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1756 "d2_parser.cc"
    break;

  case 218:
#line 836 "d2_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1766 "d2_parser.cc"
    break;

  case 219:
#line 840 "d2_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 1774 "d2_parser.cc"
    break;

  case 227:
#line 855 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "d2_parser.cc"
    break;

  case 228:
#line 857 "d2_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1792 "d2_parser.cc"
    break;

  case 229:
#line 863 "d2_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1801 "d2_parser.cc"
    break;

  case 230:
#line 868 "d2_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1810 "d2_parser.cc"
    break;

  case 231:
#line 873 "d2_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1819 "d2_parser.cc"
    break;

  case 232:
#line 878 "d2_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1827 "d2_parser.cc"
    break;

  case 233:
#line 880 "d2_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1837 "d2_parser.cc"
    break;


#line 1841 "d2_parser.cc"

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
      14,     2,     1,    23,    37,    11,    39,    43,    47,    51,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,     2,    22,
       8,     9,    18,    85,    50,   104,    13,   120,  -238,    84,
     125,   132,   129,   135,  -238,  -238,  -238,  -238,  -238,   140,
    -238,    55,  -238,  -238,  -238,  -238,  -238,  -238,  -238,   142,
     150,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,    66,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,   160,  -238,  -238,  -238,
    -238,  -238,    68,  -238,  -238,  -238,  -238,  -238,  -238,   167,
     153,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    83,  -238,
    -238,  -238,  -238,  -238,   168,   162,  -238,  -238,   171,  -238,
    -238,  -238,  -238,    97,  -238,  -238,  -238,  -238,  -238,    49,
    -238,  -238,     2,     2,  -238,   119,   174,   175,   176,   177,
     178,  -238,     8,  -238,   179,   126,   128,   181,   183,   184,
     185,   186,   187,   188,   189,   190,     9,  -238,   191,   138,
     193,   194,    18,  -238,    18,  -238,    85,   195,   196,   197,
      50,  -238,    50,  -238,   104,   198,   145,   200,    13,  -238,
      13,   120,  -238,  -238,  -238,   201,     2,     2,     2,   205,
     206,  -238,   157,  -238,  -238,    19,   199,   208,   161,   209,
     210,   202,   212,   216,  -238,   166,  -238,   170,   172,  -238,
      98,  -238,   173,   219,   180,  -238,   100,  -238,   182,  -238,
     192,  -238,   101,  -238,     2,  -238,  -238,  -238,     9,   203,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    -4,    -4,
      85,    59,   218,  -238,  -238,  -238,  -238,  -238,   120,  -238,
    -238,  -238,  -238,  -238,  -238,   127,   149,  -238,  -238,  -238,
    -238,   152,  -238,  -238,  -238,   155,   220,  -238,  -238,  -238,
    -238,  -238,   159,  -238,  -238,  -238,  -238,    77,  -238,   107,
    -238,   203,  -238,   224,    -4,  -238,  -238,  -238,   227,   228,
      59,  -238,    45,   218,  -238,  -238,  -238,   229,  -238,   207,
     211,  -238,  -238,  -238,   231,  -238,  -238,  -238,  -238,   163,
    -238,  -238,  -238,  -238,  -238,  -238,   104,  -238,  -238,   232,
     234,   214,   236,    45,  -238,   237,   213,   239,  -238,   217,
    -238,  -238,  -238,   226,  -238,  -238,   123,  -238,    52,   226,
    -238,  -238,   238,   241,   242,  -238,   169,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,   243,   215,   221,   222,   244,    52,
    -238,   225,  -238,  -238,  -238,   230,  -238,  -238,  -238
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
     215,   227,     0,     0,     0,   232,     0,   220,   222,   223,
     224,   225,   226,   217,     0,     0,     0,     0,     0,     0,
     219,     0,   229,   230,   231,     0,   221,   228,   233
  };

  const short
  D2Parser::yypgoto_[] =
  {
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,   -38,  -238,    33,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,   -50,  -238,  -238,  -238,    89,  -238,  -238,  -238,
    -238,     4,    79,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,   -51,  -238,   -39,  -238,  -238,  -238,  -238,  -238,
      -6,  -238,   -48,  -238,  -238,  -238,  -238,   -79,  -238,    64,
    -238,  -238,  -238,    71,    75,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,    -2,    76,  -238,  -238,  -238,    67,    78,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    21,
    -238,    92,  -238,  -238,  -238,    99,    87,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,   -26,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,   -16,  -237,  -238,  -238,   -27,  -238,  -238,   -55,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,   -70,  -238,  -238,
     -89,  -238,  -238,  -238,  -238,  -238,  -238,  -238
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
     339,   332,   333,   342,   334,   340,   356,   357,   358,   366,
     367,   368,   374,   369,   370,   371,   372,   378
  };

  const unsigned short
  D2Parser::yytable_[] =
  {
      70,   110,   109,   126,   125,   141,   140,    21,    32,    22,
      58,    23,   278,   111,    20,   127,    38,   142,    64,    65,
      66,    67,   279,    78,    79,    80,    81,   137,   138,    82,
      34,    83,    84,    85,    86,    83,    84,   251,   252,    87,
      83,    84,   139,    88,    36,    68,    40,    89,    42,   105,
     106,   107,   201,    69,    44,   202,    46,   108,   162,    24,
      25,    26,    27,   163,   278,    69,    69,    83,    84,   176,
      69,   182,    83,    84,   177,    69,   183,   122,   123,    61,
     313,    83,    84,   314,   322,   323,   190,   324,   325,   124,
     151,   191,   118,   361,   287,   288,   362,   363,   364,   365,
     198,   182,    69,   190,   198,   199,   266,    69,   270,   273,
     201,   133,    70,   315,   203,   204,    69,     1,     2,     3,
       4,     5,     6,     7,     8,     9,   359,   148,   152,   360,
     176,   110,   109,   110,   109,   300,   153,   154,   155,   126,
     125,   126,   125,   111,   161,   111,   165,   141,   140,   141,
     140,   127,   301,   127,   166,   304,   186,   302,   304,   142,
     305,   142,   310,   306,   179,   194,   343,   311,   245,   246,
     247,   344,   379,   185,   193,   196,   205,   380,   206,   207,
     208,   209,   210,   212,   213,   215,   214,   216,   217,   218,
     219,   220,   221,   222,   223,   225,   226,   227,   228,   232,
     233,   234,   238,   239,   240,   244,   274,   260,   280,   280,
     290,   289,   248,   249,   250,    22,   258,   259,   257,   261,
     254,   262,   291,   263,   268,   296,   307,   264,   317,   265,
     267,   319,   320,   355,   336,   341,   346,   269,   347,   271,
     349,    89,   375,   351,   353,   376,   377,   381,   385,   272,
     255,   211,   275,   285,   280,   224,   318,   345,   237,   290,
     289,   327,   326,   236,   337,   235,   299,   242,   338,   229,
     352,   291,   348,   328,   354,   382,   241,   243,   231,   383,
     384,   286,   387,   230,   321,   316,   335,   388,   350,   373,
     386,     0,   327,   326,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   328
  };

  const short
  D2Parser::yycheck_[] =
  {
      50,    52,    52,    54,    54,    56,    56,     5,     7,     7,
      48,     9,   249,    52,     0,    54,     5,    56,    10,    11,
      12,    13,    26,    14,    15,    16,    17,    14,    15,    20,
       7,    22,    23,    24,    25,    22,    23,    18,    19,    30,
      22,    23,    29,    34,     7,    37,     7,    38,     5,    31,
      32,    33,     3,    57,     7,     6,     5,    39,     3,    57,
      58,    59,    60,     8,   301,    57,    57,    22,    23,     3,
      57,     3,    22,    23,     8,    57,     8,    27,    28,    57,
       3,    22,    23,     6,    39,    40,     3,    42,    43,    39,
       6,     8,     7,    41,    35,    36,    44,    45,    46,    47,
       3,     3,    57,     3,     3,     8,     8,    57,     8,     8,
       3,     7,   162,     6,   152,   153,    57,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     3,     7,     3,     6,
       3,   182,   182,   184,   184,     8,     4,     8,     3,   190,
     190,   192,   192,   182,     4,   184,     4,   198,   198,   200,
     200,   190,     3,   192,     4,     3,     3,     8,     3,   198,
       8,   200,     3,     8,     4,     3,     3,     8,   206,   207,
     208,     8,     3,     6,     6,     4,    57,     8,     4,     4,
       4,     4,     4,     4,    58,     4,    58,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    58,     4,     4,     4,
       4,     4,     4,    58,     4,     4,   244,     5,   258,   259,
     261,   261,     7,     7,    57,     7,     7,     7,    57,     7,
      21,     5,   261,    57,     5,     7,     6,    57,     4,    57,
      57,     4,     4,     7,     5,     4,     4,    57,     4,    57,
       4,    38,     4,     6,     5,     4,     4,     4,     4,    57,
     217,   162,   248,   259,   304,   176,   304,   336,   194,   310,
     310,   312,   312,   192,    57,   190,   268,   200,    57,   182,
      57,   310,    58,   312,    57,    60,   198,   201,   186,    58,
      58,   260,    57,   184,   310,   301,   313,    57,   343,   359,
     379,    -1,   343,   343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   343
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
       0,     5,     7,     9,    57,    58,    59,    60,    72,    73,
      74,    79,     7,    84,     7,    90,     7,   154,     5,   148,
       7,   122,     5,   116,     7,   137,     5,   132,    80,    75,
      85,    91,   155,   149,   123,   117,   138,   133,    72,    81,
      82,    57,    77,    78,    10,    11,    12,    13,    37,    57,
      83,    86,    87,    88,   173,   175,   177,   179,    14,    15,
      16,    17,    20,    22,    23,    24,    25,    30,    34,    38,
      83,    92,    93,    94,    96,    97,    98,   101,   103,   105,
     107,   109,   146,   165,   183,    31,    32,    33,    39,    83,
     103,   105,   156,   157,   158,   160,   162,   163,     7,   150,
     151,   152,    27,    28,    39,    83,   103,   105,   124,   125,
     126,   128,   130,     7,   118,   119,   120,    14,    15,    29,
      83,   103,   105,   139,   140,   141,   143,   145,     7,   134,
     135,     6,     3,     4,     8,     3,   174,   176,   178,    89,
     180,     4,     3,     8,    95,     4,     4,    99,   102,   104,
     106,   108,   110,   147,   166,   184,     3,     8,   161,     4,
     164,   159,     3,     8,   153,     6,     3,   129,   131,   127,
       3,     8,   121,     6,     3,   144,     4,   142,     3,     8,
     136,     3,     6,    72,    72,    57,     4,     4,     4,     4,
       4,    87,     4,    58,    58,     4,     4,     4,     4,     4,
       4,     4,     4,     4,    93,     4,    58,     4,     4,   157,
     156,   152,     4,     4,     4,   125,   124,   120,     4,    58,
       4,   140,   139,   135,     4,    72,    72,    72,     7,     7,
      57,    18,    19,   100,    21,    74,    76,    57,     7,     7,
       5,     7,     5,    57,    57,    57,     8,    57,     5,    57,
       8,    57,    57,     8,    72,    92,   181,   182,   183,    26,
      83,   111,   112,   113,   114,   111,   150,    35,    36,    83,
     103,   105,   167,   168,   169,   171,     7,   185,   186,   134,
       8,     3,     8,   115,     3,     8,     8,     6,   170,   172,
       3,     8,   187,     3,     6,     6,   182,     4,   113,     4,
       4,   168,    39,    40,    42,    43,    83,   103,   105,   188,
     189,   190,   192,   193,   195,   186,     5,    57,    57,   191,
     196,     4,   194,     3,     8,   118,     4,     4,    58,     4,
     189,     6,    57,     5,    57,     7,   197,   198,   199,     3,
       6,    41,    44,    45,    46,    47,   200,   201,   202,   204,
     205,   206,   207,   198,   203,     4,     4,     4,   208,     3,
       8,     4,    60,    58,    58,     4,   201,    57,    57
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    61,    63,    62,    64,    62,    65,    62,    66,    62,
      67,    62,    68,    62,    69,    62,    70,    62,    71,    62,
      72,    72,    72,    72,    72,    72,    72,    73,    75,    74,
      76,    77,    77,    78,    78,    80,    79,    81,    81,    82,
      82,    83,    85,    84,    86,    86,    87,    87,    87,    87,
      87,    87,    89,    88,    91,    90,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    95,    94,    96,    97,    99,    98,   100,   100,   102,
     101,   104,   103,   106,   105,   108,   107,   110,   109,   111,
     111,   112,   112,   113,   113,   115,   114,   117,   116,   118,
     118,   119,   119,   121,   120,   123,   122,   124,   124,   125,
     125,   125,   125,   125,   125,   127,   126,   129,   128,   131,
     130,   133,   132,   134,   134,   136,   135,   138,   137,   139,
     139,   140,   140,   140,   140,   140,   140,   142,   141,   144,
     143,   145,   147,   146,   149,   148,   150,   150,   151,   151,
     153,   152,   155,   154,   156,   156,   157,   157,   157,   157,
     157,   157,   157,   159,   158,   161,   160,   162,   164,   163,
     166,   165,   167,   167,   168,   168,   168,   168,   168,   170,
     169,   172,   171,   174,   173,   176,   175,   178,   177,   180,
     179,   181,   181,   182,   184,   183,   185,   185,   187,   186,
     188,   188,   189,   189,   189,   189,   189,   189,   189,   191,
     190,   192,   194,   193,   196,   195,   197,   197,   199,   198,
     200,   200,   201,   201,   201,   201,   201,   203,   202,   204,
     205,   206,   208,   207
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
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4
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
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
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
  "maxsize", "maxver", "pattern", "$@55", YY_NULLPTR
  };

#if D2_PARSER_DEBUG
  const unsigned short
  D2Parser::yyrline_[] =
  {
       0,   125,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   131,   131,   132,   132,   133,   133,
     141,   142,   143,   144,   145,   146,   147,   150,   155,   155,
     166,   169,   170,   173,   177,   184,   184,   191,   192,   195,
     199,   210,   220,   220,   232,   233,   237,   238,   239,   240,
     241,   242,   247,   247,   257,   257,   265,   266,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   285,   285,   293,   301,   310,   310,   318,   319,   322,
     322,   330,   330,   355,   355,   382,   382,   392,   392,   402,
     403,   406,   407,   410,   411,   416,   416,   426,   426,   433,
     434,   437,   438,   441,   441,   449,   449,   456,   457,   460,
     461,   462,   463,   464,   465,   469,   469,   481,   481,   493,
     493,   503,   503,   510,   511,   514,   514,   522,   522,   529,
     530,   533,   534,   535,   536,   537,   538,   541,   541,   553,
     553,   561,   575,   575,   585,   585,   592,   593,   596,   597,
     600,   600,   608,   608,   617,   618,   621,   622,   623,   624,
     625,   626,   627,   630,   630,   642,   642,   653,   661,   661,
     677,   677,   687,   688,   691,   692,   693,   694,   695,   698,
     698,   706,   706,   716,   716,   723,   723,   730,   730,   742,
     742,   755,   756,   760,   764,   764,   776,   777,   781,   781,
     789,   790,   793,   794,   795,   796,   797,   798,   799,   802,
     802,   810,   814,   814,   822,   822,   832,   833,   836,   836,
     844,   845,   848,   849,   850,   851,   852,   855,   855,   863,
     868,   873,   878,   878
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
#line 2536 "d2_parser.cc"

#line 886 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
