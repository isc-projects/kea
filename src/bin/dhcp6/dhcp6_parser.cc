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
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy"

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc"


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

#line 14 "dhcp6_parser.yy"
namespace isc { namespace dhcp {
#line 143 "dhcp6_parser.cc"


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

  Dhcp6Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp6Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp6Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp6Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp6Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const YY_NOEXCEPT
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
      case 213: // value
      case 217: // map_value
      case 258: // ddns_replace_client_name_value
      case 292: // db_type
      case 386: // hr_mode
      case 522: // duid_type
      case 565: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 195: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 194: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 193: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 192: // "constant string"
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

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 213: // value
      case 217: // map_value
      case 258: // ddns_replace_client_name_value
      case 292: // db_type
      case 386: // hr_mode
      case 522: // duid_type
      case 565: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 195: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 194: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 193: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 192: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 213: // value
      case 217: // map_value
      case 258: // ddns_replace_client_name_value
      case 292: // db_type
      case 386: // hr_mode
      case 522: // duid_type
      case 565: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 195: // "boolean"
        value.move< bool > (that.value);
        break;

      case 194: // "floating point"
        value.move< double > (that.value);
        break;

      case 193: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 192: // "constant string"
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
      case 192: // "constant string"
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 402 "dhcp6_parser.cc"
        break;

      case 193: // "integer"
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 408 "dhcp6_parser.cc"
        break;

      case 194: // "floating point"
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 414 "dhcp6_parser.cc"
        break;

      case 195: // "boolean"
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 420 "dhcp6_parser.cc"
        break;

      case 213: // value
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 426 "dhcp6_parser.cc"
        break;

      case 217: // map_value
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp6_parser.cc"
        break;

      case 258: // ddns_replace_client_name_value
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp6_parser.cc"
        break;

      case 292: // db_type
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp6_parser.cc"
        break;

      case 386: // hr_mode
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp6_parser.cc"
        break;

      case 522: // duid_type
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp6_parser.cc"
        break;

      case 565: // ncr_protocol_value
#line 271 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp6_parser.cc"
        break;

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
#if 201103L <= YY_CPLUSPLUS
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
      case 213: // value
      case 217: // map_value
      case 258: // ddns_replace_client_name_value
      case 292: // db_type
      case 386: // hr_mode
      case 522: // duid_type
      case 565: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 195: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 194: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 193: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 192: // "constant string"
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
#line 280 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 728 "dhcp6_parser.cc"
    break;

  case 4:
#line 281 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 734 "dhcp6_parser.cc"
    break;

  case 6:
#line 282 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 740 "dhcp6_parser.cc"
    break;

  case 8:
#line 283 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 746 "dhcp6_parser.cc"
    break;

  case 10:
#line 284 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.SUBNET6; }
#line 752 "dhcp6_parser.cc"
    break;

  case 12:
#line 285 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 758 "dhcp6_parser.cc"
    break;

  case 14:
#line 286 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 764 "dhcp6_parser.cc"
    break;

  case 16:
#line 287 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 770 "dhcp6_parser.cc"
    break;

  case 18:
#line 288 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 776 "dhcp6_parser.cc"
    break;

  case 20:
#line 289 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 782 "dhcp6_parser.cc"
    break;

  case 22:
#line 290 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 788 "dhcp6_parser.cc"
    break;

  case 24:
#line 291 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 794 "dhcp6_parser.cc"
    break;

  case 26:
#line 292 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 800 "dhcp6_parser.cc"
    break;

  case 28:
#line 293 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 806 "dhcp6_parser.cc"
    break;

  case 30:
#line 294 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 812 "dhcp6_parser.cc"
    break;

  case 32:
#line 302 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 818 "dhcp6_parser.cc"
    break;

  case 33:
#line 303 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 824 "dhcp6_parser.cc"
    break;

  case 34:
#line 304 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 830 "dhcp6_parser.cc"
    break;

  case 35:
#line 305 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 836 "dhcp6_parser.cc"
    break;

  case 36:
#line 306 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 842 "dhcp6_parser.cc"
    break;

  case 37:
#line 307 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 848 "dhcp6_parser.cc"
    break;

  case 38:
#line 308 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 854 "dhcp6_parser.cc"
    break;

  case 39:
#line 311 "dhcp6_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 863 "dhcp6_parser.cc"
    break;

  case 40:
#line 316 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 874 "dhcp6_parser.cc"
    break;

  case 41:
#line 321 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 884 "dhcp6_parser.cc"
    break;

  case 42:
#line 327 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 890 "dhcp6_parser.cc"
    break;

  case 45:
#line 334 "dhcp6_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 899 "dhcp6_parser.cc"
    break;

  case 46:
#line 338 "dhcp6_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 909 "dhcp6_parser.cc"
    break;

  case 47:
#line 345 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 918 "dhcp6_parser.cc"
    break;

  case 48:
#line 348 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 926 "dhcp6_parser.cc"
    break;

  case 51:
#line 356 "dhcp6_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 935 "dhcp6_parser.cc"
    break;

  case 52:
#line 360 "dhcp6_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 944 "dhcp6_parser.cc"
    break;

  case 53:
#line 367 "dhcp6_parser.yy"
    {
    // List parsing about to start
}
#line 952 "dhcp6_parser.cc"
    break;

  case 54:
#line 369 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 961 "dhcp6_parser.cc"
    break;

  case 57:
#line 378 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 970 "dhcp6_parser.cc"
    break;

  case 58:
#line 382 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 979 "dhcp6_parser.cc"
    break;

  case 59:
#line 393 "dhcp6_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 990 "dhcp6_parser.cc"
    break;

  case 60:
#line 403 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1001 "dhcp6_parser.cc"
    break;

  case 61:
#line 408 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1014 "dhcp6_parser.cc"
    break;

  case 70:
#line 431 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1027 "dhcp6_parser.cc"
    break;

  case 71:
#line 438 "dhcp6_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1037 "dhcp6_parser.cc"
    break;

  case 72:
#line 446 "dhcp6_parser.yy"
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1047 "dhcp6_parser.cc"
    break;

  case 73:
#line 450 "dhcp6_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 125:
#line 512 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1064 "dhcp6_parser.cc"
    break;

  case 126:
#line 514 "dhcp6_parser.yy"
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1074 "dhcp6_parser.cc"
    break;

  case 127:
#line 520 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1083 "dhcp6_parser.cc"
    break;

  case 128:
#line 525 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1092 "dhcp6_parser.cc"
    break;

  case 129:
#line 530 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1101 "dhcp6_parser.cc"
    break;

  case 130:
#line 535 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1110 "dhcp6_parser.cc"
    break;

  case 131:
#line 540 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1119 "dhcp6_parser.cc"
    break;

  case 132:
#line 545 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1128 "dhcp6_parser.cc"
    break;

  case 133:
#line 550 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1137 "dhcp6_parser.cc"
    break;

  case 134:
#line 555 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1146 "dhcp6_parser.cc"
    break;

  case 135:
#line 560 "dhcp6_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 136:
#line 565 "dhcp6_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1164 "dhcp6_parser.cc"
    break;

  case 137:
#line 570 "dhcp6_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1173 "dhcp6_parser.cc"
    break;

  case 138:
#line 575 "dhcp6_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1182 "dhcp6_parser.cc"
    break;

  case 139:
#line 580 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 140:
#line 585 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1200 "dhcp6_parser.cc"
    break;

  case 141:
#line 590 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1209 "dhcp6_parser.cc"
    break;

  case 142:
#line 595 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1217 "dhcp6_parser.cc"
    break;

  case 143:
#line 597 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1226 "dhcp6_parser.cc"
    break;

  case 144:
#line 603 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1234 "dhcp6_parser.cc"
    break;

  case 145:
#line 606 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1242 "dhcp6_parser.cc"
    break;

  case 146:
#line 609 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1250 "dhcp6_parser.cc"
    break;

  case 147:
#line 612 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1258 "dhcp6_parser.cc"
    break;

  case 148:
#line 615 "dhcp6_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1267 "dhcp6_parser.cc"
    break;

  case 149:
#line 621 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 150:
#line 623 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 151:
#line 629 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1293 "dhcp6_parser.cc"
    break;

  case 152:
#line 631 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 153:
#line 637 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 154:
#line 639 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 155:
#line 645 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1329 "dhcp6_parser.cc"
    break;

  case 156:
#line 647 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 157:
#line 653 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1347 "dhcp6_parser.cc"
    break;

  case 158:
#line 655 "dhcp6_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1357 "dhcp6_parser.cc"
    break;

  case 159:
#line 661 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1368 "dhcp6_parser.cc"
    break;

  case 160:
#line 666 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1378 "dhcp6_parser.cc"
    break;

  case 161:
#line 672 "dhcp6_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1388 "dhcp6_parser.cc"
    break;

  case 162:
#line 676 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1397 "dhcp6_parser.cc"
    break;

  case 170:
#line 692 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 171:
#line 697 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1417 "dhcp6_parser.cc"
    break;

  case 172:
#line 702 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1426 "dhcp6_parser.cc"
    break;

  case 173:
#line 708 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1437 "dhcp6_parser.cc"
    break;

  case 174:
#line 713 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1448 "dhcp6_parser.cc"
    break;

  case 175:
#line 720 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1459 "dhcp6_parser.cc"
    break;

  case 176:
#line 725 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 177:
#line 732 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1481 "dhcp6_parser.cc"
    break;

  case 178:
#line 737 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 183:
#line 750 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1500 "dhcp6_parser.cc"
    break;

  case 184:
#line 754 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1510 "dhcp6_parser.cc"
    break;

  case 208:
#line 787 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1518 "dhcp6_parser.cc"
    break;

  case 209:
#line 789 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1527 "dhcp6_parser.cc"
    break;

  case 210:
#line 794 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1533 "dhcp6_parser.cc"
    break;

  case 211:
#line 795 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1539 "dhcp6_parser.cc"
    break;

  case 212:
#line 796 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1545 "dhcp6_parser.cc"
    break;

  case 213:
#line 797 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1551 "dhcp6_parser.cc"
    break;

  case 214:
#line 800 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1559 "dhcp6_parser.cc"
    break;

  case 215:
#line 802 "dhcp6_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1569 "dhcp6_parser.cc"
    break;

  case 216:
#line 808 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 217:
#line 810 "dhcp6_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 218:
#line 816 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1595 "dhcp6_parser.cc"
    break;

  case 219:
#line 818 "dhcp6_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1605 "dhcp6_parser.cc"
    break;

  case 220:
#line 824 "dhcp6_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1614 "dhcp6_parser.cc"
    break;

  case 221:
#line 829 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1622 "dhcp6_parser.cc"
    break;

  case 222:
#line 831 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1632 "dhcp6_parser.cc"
    break;

  case 223:
#line 837 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 224:
#line 842 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1650 "dhcp6_parser.cc"
    break;

  case 225:
#line 847 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1659 "dhcp6_parser.cc"
    break;

  case 226:
#line 852 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 227:
#line 857 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 228:
#line 862 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1686 "dhcp6_parser.cc"
    break;

  case 229:
#line 867 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1695 "dhcp6_parser.cc"
    break;

  case 230:
#line 872 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1704 "dhcp6_parser.cc"
    break;

  case 231:
#line 877 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1713 "dhcp6_parser.cc"
    break;

  case 232:
#line 882 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1721 "dhcp6_parser.cc"
    break;

  case 233:
#line 884 "dhcp6_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1731 "dhcp6_parser.cc"
    break;

  case 234:
#line 890 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1740 "dhcp6_parser.cc"
    break;

  case 235:
#line 895 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1748 "dhcp6_parser.cc"
    break;

  case 236:
#line 897 "dhcp6_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1758 "dhcp6_parser.cc"
    break;

  case 237:
#line 903 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp6_parser.cc"
    break;

  case 238:
#line 905 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1776 "dhcp6_parser.cc"
    break;

  case 239:
#line 911 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1784 "dhcp6_parser.cc"
    break;

  case 240:
#line 913 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1794 "dhcp6_parser.cc"
    break;

  case 241:
#line 919 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 242:
#line 924 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1814 "dhcp6_parser.cc"
    break;

  case 246:
#line 934 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1822 "dhcp6_parser.cc"
    break;

  case 247:
#line 936 "dhcp6_parser.yy"
    {

    if ( (string(yystack_[0].value.as < std::string > ()) == "none") ||
         (string(yystack_[0].value.as < std::string > ()) == "warn") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as < std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as < std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1842 "dhcp6_parser.cc"
    break;

  case 248:
#line 952 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 249:
#line 957 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 254:
#line 970 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1871 "dhcp6_parser.cc"
    break;

  case 255:
#line 975 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1880 "dhcp6_parser.cc"
    break;

  case 256:
#line 980 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1891 "dhcp6_parser.cc"
    break;

  case 257:
#line 985 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 263:
#line 999 "dhcp6_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 264:
#line 1004 "dhcp6_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 265:
#line 1011 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp6_parser.cc"
    break;

  case 266:
#line 1016 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1938 "dhcp6_parser.cc"
    break;

  case 267:
#line 1021 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1949 "dhcp6_parser.cc"
    break;

  case 268:
#line 1026 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1958 "dhcp6_parser.cc"
    break;

  case 273:
#line 1039 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1968 "dhcp6_parser.cc"
    break;

  case 274:
#line 1043 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1978 "dhcp6_parser.cc"
    break;

  case 275:
#line 1049 "dhcp6_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1988 "dhcp6_parser.cc"
    break;

  case 276:
#line 1053 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 282:
#line 1068 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2006 "dhcp6_parser.cc"
    break;

  case 283:
#line 1070 "dhcp6_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2016 "dhcp6_parser.cc"
    break;

  case 284:
#line 1076 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2024 "dhcp6_parser.cc"
    break;

  case 285:
#line 1078 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2033 "dhcp6_parser.cc"
    break;

  case 286:
#line 1084 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2044 "dhcp6_parser.cc"
    break;

  case 287:
#line 1089 "dhcp6_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2054 "dhcp6_parser.cc"
    break;

  case 296:
#line 1107 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2063 "dhcp6_parser.cc"
    break;

  case 297:
#line 1112 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2072 "dhcp6_parser.cc"
    break;

  case 298:
#line 1117 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2081 "dhcp6_parser.cc"
    break;

  case 299:
#line 1122 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2090 "dhcp6_parser.cc"
    break;

  case 300:
#line 1127 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2099 "dhcp6_parser.cc"
    break;

  case 301:
#line 1132 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2108 "dhcp6_parser.cc"
    break;

  case 302:
#line 1140 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2119 "dhcp6_parser.cc"
    break;

  case 303:
#line 1145 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2128 "dhcp6_parser.cc"
    break;

  case 308:
#line 1165 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2138 "dhcp6_parser.cc"
    break;

  case 309:
#line 1169 "dhcp6_parser.yy"
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
#line 2164 "dhcp6_parser.cc"
    break;

  case 310:
#line 1191 "dhcp6_parser.yy"
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 311:
#line 1195 "dhcp6_parser.yy"
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2184 "dhcp6_parser.cc"
    break;

  case 349:
#line 1244 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 350:
#line 1246 "dhcp6_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 351:
#line 1252 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2210 "dhcp6_parser.cc"
    break;

  case 352:
#line 1254 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2220 "dhcp6_parser.cc"
    break;

  case 353:
#line 1260 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 354:
#line 1262 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2238 "dhcp6_parser.cc"
    break;

  case 355:
#line 1268 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2246 "dhcp6_parser.cc"
    break;

  case 356:
#line 1270 "dhcp6_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2256 "dhcp6_parser.cc"
    break;

  case 357:
#line 1276 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 358:
#line 1281 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2276 "dhcp6_parser.cc"
    break;

  case 359:
#line 1286 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2284 "dhcp6_parser.cc"
    break;

  case 360:
#line 1288 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 361:
#line 1293 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2299 "dhcp6_parser.cc"
    break;

  case 362:
#line 1294 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2305 "dhcp6_parser.cc"
    break;

  case 363:
#line 1295 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2311 "dhcp6_parser.cc"
    break;

  case 364:
#line 1296 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2317 "dhcp6_parser.cc"
    break;

  case 365:
#line 1299 "dhcp6_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2326 "dhcp6_parser.cc"
    break;

  case 366:
#line 1304 "dhcp6_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 367:
#line 1312 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2346 "dhcp6_parser.cc"
    break;

  case 368:
#line 1317 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2355 "dhcp6_parser.cc"
    break;

  case 373:
#line 1332 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2365 "dhcp6_parser.cc"
    break;

  case 374:
#line 1336 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2373 "dhcp6_parser.cc"
    break;

  case 409:
#line 1382 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 410:
#line 1387 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2393 "dhcp6_parser.cc"
    break;

  case 411:
#line 1395 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2402 "dhcp6_parser.cc"
    break;

  case 412:
#line 1398 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 2410 "dhcp6_parser.cc"
    break;

  case 417:
#line 1414 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2420 "dhcp6_parser.cc"
    break;

  case 418:
#line 1418 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2432 "dhcp6_parser.cc"
    break;

  case 419:
#line 1429 "dhcp6_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2442 "dhcp6_parser.cc"
    break;

  case 420:
#line 1433 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2454 "dhcp6_parser.cc"
    break;

  case 436:
#line 1465 "dhcp6_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2463 "dhcp6_parser.cc"
    break;

  case 438:
#line 1472 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2471 "dhcp6_parser.cc"
    break;

  case 439:
#line 1474 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc"
    break;

  case 440:
#line 1480 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2489 "dhcp6_parser.cc"
    break;

  case 441:
#line 1482 "dhcp6_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2499 "dhcp6_parser.cc"
    break;

  case 442:
#line 1488 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 443:
#line 1490 "dhcp6_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2517 "dhcp6_parser.cc"
    break;

  case 445:
#line 1498 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 446:
#line 1500 "dhcp6_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 447:
#line 1506 "dhcp6_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2544 "dhcp6_parser.cc"
    break;

  case 448:
#line 1515 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 449:
#line 1520 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2564 "dhcp6_parser.cc"
    break;

  case 454:
#line 1539 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2574 "dhcp6_parser.cc"
    break;

  case 455:
#line 1543 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2583 "dhcp6_parser.cc"
    break;

  case 456:
#line 1551 "dhcp6_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2593 "dhcp6_parser.cc"
    break;

  case 457:
#line 1555 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2602 "dhcp6_parser.cc"
    break;

  case 472:
#line 1588 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 473:
#line 1590 "dhcp6_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 476:
#line 1600 "dhcp6_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2629 "dhcp6_parser.cc"
    break;

  case 477:
#line 1605 "dhcp6_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 478:
#line 1613 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2649 "dhcp6_parser.cc"
    break;

  case 479:
#line 1618 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2658 "dhcp6_parser.cc"
    break;

  case 484:
#line 1633 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2668 "dhcp6_parser.cc"
    break;

  case 485:
#line 1637 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2678 "dhcp6_parser.cc"
    break;

  case 486:
#line 1643 "dhcp6_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 487:
#line 1647 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2697 "dhcp6_parser.cc"
    break;

  case 497:
#line 1665 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp6_parser.cc"
    break;

  case 498:
#line 1667 "dhcp6_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 499:
#line 1673 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 500:
#line 1675 "dhcp6_parser.yy"
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
#line 2750 "dhcp6_parser.cc"
    break;

  case 501:
#line 1698 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp6_parser.cc"
    break;

  case 502:
#line 1700 "dhcp6_parser.yy"
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
#line 2787 "dhcp6_parser.cc"
    break;

  case 503:
#line 1728 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2798 "dhcp6_parser.cc"
    break;

  case 504:
#line 1733 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2807 "dhcp6_parser.cc"
    break;

  case 509:
#line 1748 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2817 "dhcp6_parser.cc"
    break;

  case 510:
#line 1752 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 511:
#line 1760 "dhcp6_parser.yy"
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2839 "dhcp6_parser.cc"
    break;

  case 512:
#line 1764 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2851 "dhcp6_parser.cc"
    break;

  case 526:
#line 1789 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2859 "dhcp6_parser.cc"
    break;

  case 527:
#line 1791 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2869 "dhcp6_parser.cc"
    break;

  case 528:
#line 1797 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2878 "dhcp6_parser.cc"
    break;

  case 529:
#line 1802 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2886 "dhcp6_parser.cc"
    break;

  case 530:
#line 1804 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2896 "dhcp6_parser.cc"
    break;

  case 531:
#line 1810 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 532:
#line 1815 "dhcp6_parser.yy"
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 533:
#line 1823 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 534:
#line 1828 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2934 "dhcp6_parser.cc"
    break;

  case 539:
#line 1841 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2944 "dhcp6_parser.cc"
    break;

  case 540:
#line 1845 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 541:
#line 1850 "dhcp6_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2963 "dhcp6_parser.cc"
    break;

  case 542:
#line 1854 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 558:
#line 1881 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2983 "dhcp6_parser.cc"
    break;

  case 559:
#line 1886 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2992 "dhcp6_parser.cc"
    break;

  case 560:
#line 1891 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3003 "dhcp6_parser.cc"
    break;

  case 561:
#line 1896 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3012 "dhcp6_parser.cc"
    break;

  case 562:
#line 1901 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp6_parser.cc"
    break;

  case 563:
#line 1903 "dhcp6_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3030 "dhcp6_parser.cc"
    break;

  case 564:
#line 1909 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3038 "dhcp6_parser.cc"
    break;

  case 565:
#line 1911 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3048 "dhcp6_parser.cc"
    break;

  case 566:
#line 1917 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp6_parser.cc"
    break;

  case 567:
#line 1919 "dhcp6_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3066 "dhcp6_parser.cc"
    break;

  case 568:
#line 1925 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3074 "dhcp6_parser.cc"
    break;

  case 569:
#line 1927 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3084 "dhcp6_parser.cc"
    break;

  case 570:
#line 1933 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3095 "dhcp6_parser.cc"
    break;

  case 571:
#line 1938 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 572:
#line 1946 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3115 "dhcp6_parser.cc"
    break;

  case 573:
#line 1951 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3124 "dhcp6_parser.cc"
    break;

  case 576:
#line 1960 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 577:
#line 1962 "dhcp6_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3142 "dhcp6_parser.cc"
    break;

  case 578:
#line 1971 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3153 "dhcp6_parser.cc"
    break;

  case 579:
#line 1976 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3162 "dhcp6_parser.cc"
    break;

  case 582:
#line 1985 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3172 "dhcp6_parser.cc"
    break;

  case 583:
#line 1989 "dhcp6_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3182 "dhcp6_parser.cc"
    break;

  case 596:
#line 2014 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3190 "dhcp6_parser.cc"
    break;

  case 597:
#line 2016 "dhcp6_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 598:
#line 2022 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3209 "dhcp6_parser.cc"
    break;

  case 599:
#line 2030 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3220 "dhcp6_parser.cc"
    break;

  case 600:
#line 2035 "dhcp6_parser.yy"
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 612:
#line 2057 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 613:
#line 2059 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3248 "dhcp6_parser.cc"
    break;

  case 614:
#line 2064 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3254 "dhcp6_parser.cc"
    break;

  case 615:
#line 2065 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3260 "dhcp6_parser.cc"
    break;

  case 616:
#line 2066 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3266 "dhcp6_parser.cc"
    break;

  case 617:
#line 2069 "dhcp6_parser.yy"
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3275 "dhcp6_parser.cc"
    break;

  case 618:
#line 2074 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3283 "dhcp6_parser.cc"
    break;

  case 619:
#line 2076 "dhcp6_parser.yy"
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 620:
#line 2082 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3302 "dhcp6_parser.cc"
    break;

  case 621:
#line 2087 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3311 "dhcp6_parser.cc"
    break;

  case 622:
#line 2094 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3320 "dhcp6_parser.cc"
    break;

  case 623:
#line 2101 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3331 "dhcp6_parser.cc"
    break;

  case 624:
#line 2106 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3340 "dhcp6_parser.cc"
    break;

  case 632:
#line 2122 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 633:
#line 2124 "dhcp6_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3358 "dhcp6_parser.cc"
    break;

  case 634:
#line 2130 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 635:
#line 2132 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3376 "dhcp6_parser.cc"
    break;

  case 636:
#line 2140 "dhcp6_parser.yy"
    {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3387 "dhcp6_parser.cc"
    break;

  case 637:
#line 2145 "dhcp6_parser.yy"
    {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 646:
#line 2164 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3407 "dhcp6_parser.cc"
    break;

  case 647:
#line 2169 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3415 "dhcp6_parser.cc"
    break;

  case 648:
#line 2171 "dhcp6_parser.yy"
    {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3425 "dhcp6_parser.cc"
    break;

  case 649:
#line 2177 "dhcp6_parser.yy"
    {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3434 "dhcp6_parser.cc"
    break;

  case 650:
#line 2182 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3442 "dhcp6_parser.cc"
    break;

  case 651:
#line 2184 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3451 "dhcp6_parser.cc"
    break;

  case 652:
#line 2191 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3462 "dhcp6_parser.cc"
    break;

  case 653:
#line 2196 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3473 "dhcp6_parser.cc"
    break;

  case 654:
#line 2203 "dhcp6_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3483 "dhcp6_parser.cc"
    break;

  case 655:
#line 2207 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3493 "dhcp6_parser.cc"
    break;

  case 676:
#line 2237 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3502 "dhcp6_parser.cc"
    break;

  case 677:
#line 2242 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3510 "dhcp6_parser.cc"
    break;

  case 678:
#line 2244 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3520 "dhcp6_parser.cc"
    break;

  case 679:
#line 2250 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 680:
#line 2252 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3538 "dhcp6_parser.cc"
    break;

  case 681:
#line 2258 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3547 "dhcp6_parser.cc"
    break;

  case 682:
#line 2263 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 683:
#line 2265 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 684:
#line 2271 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3574 "dhcp6_parser.cc"
    break;

  case 685:
#line 2276 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3583 "dhcp6_parser.cc"
    break;

  case 686:
#line 2281 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3591 "dhcp6_parser.cc"
    break;

  case 687:
#line 2283 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3600 "dhcp6_parser.cc"
    break;

  case 688:
#line 2289 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3606 "dhcp6_parser.cc"
    break;

  case 689:
#line 2290 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3612 "dhcp6_parser.cc"
    break;

  case 690:
#line 2293 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3620 "dhcp6_parser.cc"
    break;

  case 691:
#line 2295 "dhcp6_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 692:
#line 2302 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 693:
#line 2308 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3648 "dhcp6_parser.cc"
    break;

  case 694:
#line 2314 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 695:
#line 2316 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3665 "dhcp6_parser.cc"
    break;

  case 696:
#line 2322 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3673 "dhcp6_parser.cc"
    break;

  case 697:
#line 2324 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3683 "dhcp6_parser.cc"
    break;

  case 698:
#line 2331 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3691 "dhcp6_parser.cc"
    break;

  case 699:
#line 2333 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 700:
#line 2340 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3709 "dhcp6_parser.cc"
    break;

  case 701:
#line 2342 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3719 "dhcp6_parser.cc"
    break;

  case 702:
#line 2350 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 703:
#line 2352 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3736 "dhcp6_parser.cc"
    break;

  case 704:
#line 2357 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3744 "dhcp6_parser.cc"
    break;

  case 705:
#line 2359 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3753 "dhcp6_parser.cc"
    break;

  case 706:
#line 2364 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3761 "dhcp6_parser.cc"
    break;

  case 707:
#line 2366 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3770 "dhcp6_parser.cc"
    break;

  case 708:
#line 2373 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3781 "dhcp6_parser.cc"
    break;

  case 709:
#line 2378 "dhcp6_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3791 "dhcp6_parser.cc"
    break;

  case 710:
#line 2384 "dhcp6_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3801 "dhcp6_parser.cc"
    break;

  case 711:
#line 2388 "dhcp6_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3810 "dhcp6_parser.cc"
    break;

  case 716:
#line 2403 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3821 "dhcp6_parser.cc"
    break;

  case 717:
#line 2408 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3830 "dhcp6_parser.cc"
    break;

  case 718:
#line 2413 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3839 "dhcp6_parser.cc"
    break;

  case 719:
#line 2423 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3850 "dhcp6_parser.cc"
    break;

  case 720:
#line 2428 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3859 "dhcp6_parser.cc"
    break;

  case 721:
#line 2433 "dhcp6_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3869 "dhcp6_parser.cc"
    break;

  case 722:
#line 2437 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 3877 "dhcp6_parser.cc"
    break;

  case 726:
#line 2453 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3888 "dhcp6_parser.cc"
    break;

  case 727:
#line 2458 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3897 "dhcp6_parser.cc"
    break;

  case 730:
#line 2470 "dhcp6_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3907 "dhcp6_parser.cc"
    break;

  case 731:
#line 2474 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3915 "dhcp6_parser.cc"
    break;

  case 741:
#line 2491 "dhcp6_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3924 "dhcp6_parser.cc"
    break;

  case 742:
#line 2496 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 743:
#line 2498 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3942 "dhcp6_parser.cc"
    break;

  case 744:
#line 2504 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 745:
#line 2509 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 748:
#line 2518 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3972 "dhcp6_parser.cc"
    break;

  case 749:
#line 2522 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 757:
#line 2537 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3988 "dhcp6_parser.cc"
    break;

  case 758:
#line 2539 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3998 "dhcp6_parser.cc"
    break;

  case 759:
#line 2545 "dhcp6_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4007 "dhcp6_parser.cc"
    break;

  case 760:
#line 2550 "dhcp6_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4016 "dhcp6_parser.cc"
    break;

  case 761:
#line 2555 "dhcp6_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4025 "dhcp6_parser.cc"
    break;

  case 762:
#line 2560 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4033 "dhcp6_parser.cc"
    break;

  case 763:
#line 2562 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4043 "dhcp6_parser.cc"
    break;


#line 4047 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -932;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     166,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,    52,    31,    76,    82,
      97,   105,   113,   142,   152,   173,   175,   201,   224,   244,
     245,   252,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,    31,  -101,    29,   524,    41,   196,   229,    95,
      80,    42,    78,   257,   -38,   528,   103,   158,  -932,   254,
     274,   306,   281,   301,  -932,  -932,  -932,  -932,  -932,   325,
    -932,    38,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,   328,   329,   332,   335,   356,   371,
     372,   383,   401,   409,   412,   413,  -932,   425,   426,   435,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   453,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,    56,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   468,  -932,
      59,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,   469,   476,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,    87,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,    99,  -932,
    -932,  -932,  -932,  -932,   481,  -932,   484,   491,  -932,  -932,
    -932,  -932,  -932,  -932,   115,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,   386,   388,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,   407,  -932,  -932,   492,  -932,  -932,  -932,   493,
    -932,  -932,   490,   496,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,   497,   498,  -932,
    -932,  -932,  -932,   499,   507,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,   162,  -932,  -932,
    -932,   509,  -932,  -932,   510,  -932,   512,   515,  -932,  -932,
     516,   517,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   191,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,   193,  -932,  -932,  -932,
     519,   199,  -932,  -932,  -932,  -932,    31,    31,  -932,   308,
     521,   522,   523,   526,   527,  -932,    29,  -932,   529,   530,
     533,   534,   536,   537,   318,   339,   355,   357,   358,   359,
     360,   361,   333,   362,   363,   365,   545,   364,   366,   367,
     551,   556,   559,   560,   561,   562,   563,   586,   587,   588,
     589,   590,   592,   593,   595,   596,   597,   599,   600,   416,
     601,   602,   606,   609,   611,   612,   524,  -932,   613,   431,
      41,  -932,   620,   623,   624,   625,   627,   439,   438,   630,
     633,   636,   196,  -932,   639,   229,  -932,   640,   452,   642,
     454,   455,    95,  -932,   646,   651,   652,   655,   656,   658,
     660,  -932,    80,  -932,   662,   663,   495,   665,   679,   680,
     500,  -932,    78,   681,   501,   502,  -932,   257,   688,   689,
     102,  -932,   503,   690,   695,   513,   696,   514,   518,   701,
     704,   520,   531,   705,   706,   708,   709,   528,  -932,   103,
    -932,   710,   525,   158,  -932,  -932,  -932,   713,   712,   714,
      31,    31,    31,  -932,   532,   715,   716,   718,   720,   723,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,   538,  -932,  -932,  -932,    25,   539,   540,   724,
     728,   729,   730,   543,    64,   731,   733,   734,   735,   736,
     737,   739,   740,   741,   742,  -932,   743,   744,   745,   549,
     554,   748,  -932,   749,  -932,  -932,   750,   751,   555,   565,
     566,  -932,  -932,   749,   567,   753,  -932,   569,  -932,   570,
    -932,   571,  -932,  -932,  -932,   749,   749,   749,   572,   573,
     574,   575,  -932,   576,   577,  -932,   578,   579,   580,  -932,
    -932,   581,  -932,  -932,  -932,   582,    31,  -932,  -932,   583,
     584,  -932,   585,  -932,  -932,    83,   621,  -932,  -932,    25,
     591,   594,   598,  -932,  -932,   774,  -932,  -932,    31,   524,
     103,  -932,  -932,  -932,  -932,   158,    41,   100,   100,   773,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   775,
     777,   778,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
     780,   -44,    31,   210,   691,   781,   782,   785,   143,    84,
     -39,   -23,   528,  -932,  -932,   786,  -932,  -932,   787,   788,
    -932,  -932,  -932,  -932,  -932,   -65,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,   773,  -932,   214,   266,   285,
     287,  -932,  -932,  -932,  -932,   792,   793,   794,   795,   796,
    -932,   797,   798,  -932,  -932,  -932,   799,   800,   801,   802,
    -932,   300,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,   303,  -932,   803,   804,  -932,  -932,   805,
     807,  -932,  -932,   806,   810,  -932,  -932,   808,   812,  -932,
    -932,   811,   813,  -932,  -932,  -932,    60,  -932,  -932,  -932,
     814,  -932,  -932,  -932,    70,  -932,  -932,  -932,  -932,   313,
    -932,  -932,  -932,   116,  -932,  -932,   815,   816,  -932,  -932,
     817,   819,  -932,   820,   821,   822,   823,   824,   825,   327,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   826,
     827,   828,  -932,  -932,  -932,  -932,   381,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   387,  -932,
    -932,  -932,   829,  -932,   830,  -932,  -932,  -932,   390,  -932,
    -932,  -932,  -932,  -932,   411,  -932,   192,  -932,   616,  -932,
     831,   832,  -932,  -932,   833,   835,  -932,  -932,  -932,   834,
    -932,   837,  -932,  -932,  -932,  -932,   836,   840,   841,   842,
     643,   653,   648,   654,   657,   843,   659,   661,   847,   849,
     851,   664,   666,   667,   668,   100,  -932,  -932,   100,  -932,
     773,   196,  -932,   775,    78,  -932,   777,   257,  -932,   778,
     320,  -932,   780,   -44,  -932,  -932,   210,  -932,   852,   691,
    -932,   234,   781,  -932,    80,  -932,   782,   -38,  -932,   785,
     670,   671,   672,   673,   674,   675,   143,  -932,   854,   856,
     676,   677,   678,    84,  -932,   868,   869,   -39,  -932,   683,
     870,   682,   872,   -23,  -932,  -932,   231,   786,  -932,  -932,
     873,   879,   229,  -932,   787,    95,  -932,   788,   880,  -932,
    -932,   205,   626,   693,   698,  -932,  -932,  -932,  -932,  -932,
     700,  -932,  -932,   703,   722,   752,  -932,  -932,  -932,  -932,
    -932,   428,  -932,   429,  -932,   893,  -932,   898,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,   442,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,   759,  -932,  -932,   903,
    -932,  -932,  -932,  -932,  -932,   900,   907,  -932,  -932,  -932,
    -932,  -932,   904,  -932,   457,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,   235,   761,  -932,  -932,  -932,  -932,   784,
     790,  -932,  -932,   809,  -932,    31,  -932,  -932,   911,  -932,
    -932,  -932,  -932,  -932,   461,  -932,  -932,  -932,  -932,  -932,
    -932,   818,   463,  -932,   467,  -932,   838,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,   320,  -932,  -932,   924,   747,  -932,   234,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,   925,   839,   933,   231,  -932,  -932,  -932,  -932,  -932,
    -932,   844,  -932,  -932,   776,  -932,   845,  -932,  -932,   966,
    -932,  -932,   272,  -932,    39,   966,  -932,  -932,   974,   975,
     976,  -932,   473,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
     989,   846,   850,   853,   990,    39,  -932,   848,  -932,  -932,
    -932,   857,  -932,  -932,  -932
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   161,     9,
     310,    11,   486,    13,   511,    15,   541,    17,   411,    19,
     419,    21,   456,    23,   275,    25,   654,    27,   721,    29,
     710,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     543,     0,   421,   458,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   719,   702,   704,   706,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   125,   708,
     159,   173,   175,   177,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,     0,     0,     0,
     142,   149,   151,   302,   409,   448,   499,   501,   359,   367,
     248,   265,   256,   241,   578,   533,   267,   286,   599,     0,
     623,   636,   652,   153,   155,   726,   124,     0,    74,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   112,   113,
     114,    85,   118,   119,   120,   121,   122,   123,   116,   117,
     110,    88,    89,    90,    91,   107,    92,    94,    93,    98,
      99,    86,   111,    87,    96,    97,   105,   106,   108,    95,
     100,   101,   102,   103,   104,   109,   115,   170,     0,   169,
       0,   163,   165,   166,   167,   168,   478,   503,   349,   351,
     353,     0,     0,   357,   355,   572,   348,   314,   315,   316,
     317,   318,   319,   320,   321,   337,   338,   339,   342,   343,
     344,   345,   346,   347,   340,   341,     0,   312,   325,   326,
     327,   330,   331,   333,   328,   329,   322,   323,   335,   336,
     324,   332,   334,   497,   496,   492,   493,   491,     0,   488,
     490,   494,   495,   526,     0,   529,     0,     0,   525,   519,
     520,   518,   523,   524,     0,   513,   515,   516,   521,   522,
     517,   570,   558,   560,   562,   564,   566,   568,   557,   554,
     555,   556,     0,   544,   545,   549,   550,   547,   551,   552,
     553,   548,     0,   438,   221,     0,   442,   440,   445,     0,
     434,   435,     0,   422,   423,   425,   437,   426,   427,   428,
     444,   429,   430,   431,   432,   433,   472,     0,     0,   470,
     471,   474,   475,     0,   459,   460,   462,   463,   464,   465,
     466,   467,   468,   469,   282,   284,   279,     0,   277,   280,
     281,     0,   677,   679,     0,   682,     0,     0,   686,   690,
       0,     0,   694,   696,   698,   700,   675,   673,   674,     0,
     656,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   670,   671,   672,     0,   723,   725,   716,
       0,     0,   712,   714,   715,    48,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    59,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   162,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   311,     0,     0,   487,     0,     0,     0,
       0,     0,     0,   512,     0,     0,     0,     0,     0,     0,
       0,   542,     0,   412,     0,     0,     0,     0,     0,     0,
       0,   420,     0,     0,     0,     0,   457,     0,     0,     0,
       0,   276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   655,     0,
     722,     0,     0,     0,   711,    52,    45,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,     0,   139,   140,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   622,     0,     0,     0,     0,
       0,     0,    75,     0,   172,   164,     0,     0,     0,     0,
       0,   365,   366,     0,     0,     0,   313,     0,   489,     0,
     528,     0,   531,   532,   514,     0,     0,     0,     0,     0,
       0,     0,   546,     0,     0,   436,     0,     0,     0,   447,
     424,     0,   476,   477,   461,     0,     0,   278,   676,     0,
       0,   681,     0,   684,   685,     0,     0,   692,   693,     0,
       0,     0,     0,   657,   724,     0,   718,   713,     0,     0,
       0,   703,   705,   707,   126,     0,     0,     0,     0,   179,
     158,   144,   145,   146,   147,   148,   143,   150,   152,   304,
     413,   450,    42,   500,   502,   361,   362,   363,   364,   360,
     369,     0,    49,     0,     0,     0,   535,   269,     0,     0,
       0,     0,     0,   154,   156,     0,    53,   171,   480,   505,
     350,   352,   354,   358,   356,     0,   498,   527,   530,   571,
     559,   561,   563,   565,   567,   569,   439,   222,   443,   441,
     446,   473,   283,   285,   678,   680,   683,   688,   689,   687,
     691,   695,   697,   699,   701,   179,    46,     0,     0,     0,
       0,   208,   214,   216,   218,     0,     0,     0,     0,     0,
     232,     0,     0,   235,   237,   239,     0,     0,     0,     0,
     207,     0,   185,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   199,   206,   200,   201,   202,   197,   198,
     203,   204,   205,     0,   183,     0,   180,   181,   308,     0,
     305,   306,   417,     0,   414,   415,   454,     0,   451,   452,
     373,     0,   370,   371,   254,   255,     0,   250,   252,   253,
       0,   263,   264,   260,     0,   258,   261,   262,   246,     0,
     243,   245,   582,     0,   580,   539,     0,   536,   537,   273,
       0,   270,   271,     0,     0,     0,     0,     0,     0,     0,
     288,   290,   291,   292,   293,   294,   295,   612,   618,     0,
       0,     0,   611,   608,   609,   610,     0,   601,   603,   606,
     604,   605,   607,   632,   634,   631,   629,   630,     0,   625,
     627,   628,     0,   647,     0,   650,   643,   644,     0,   638,
     640,   641,   642,   645,     0,   730,     0,   728,    55,   484,
       0,   481,   482,   509,     0,   506,   507,   576,   575,     0,
     574,     0,    71,   720,   709,   160,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   174,   176,     0,   178,
       0,     0,   303,     0,   421,   410,     0,   458,   449,     0,
       0,   368,     0,     0,   249,   266,     0,   257,     0,     0,
     242,   584,     0,   579,   543,   534,     0,     0,   268,     0,
       0,     0,     0,     0,     0,     0,     0,   287,     0,     0,
       0,     0,     0,     0,   600,     0,     0,     0,   624,     0,
       0,     0,     0,     0,   637,   653,     0,     0,   727,    57,
       0,    56,     0,   479,     0,     0,   504,     0,     0,   573,
     717,     0,     0,     0,     0,   220,   223,   224,   225,   226,
       0,   234,   227,     0,     0,     0,   229,   230,   231,   228,
     186,     0,   182,     0,   307,     0,   416,     0,   453,   408,
     388,   389,   390,   392,   393,   394,   381,   382,   397,   398,
     399,   402,   403,   404,   405,   406,   407,   400,   401,   377,
     378,   379,   380,   386,   387,   385,   391,     0,   375,   383,
     395,   396,   384,   372,   251,   259,     0,   244,   596,     0,
     594,   595,   591,   592,   593,     0,   585,   586,   588,   589,
     590,   581,     0,   538,     0,   272,   296,   297,   298,   299,
     300,   301,   289,     0,     0,   617,   620,   621,   602,     0,
       0,   626,   646,     0,   649,     0,   639,   744,     0,   742,
     740,   734,   738,   739,     0,   732,   736,   737,   735,   729,
      54,     0,     0,   483,     0,   508,     0,   210,   211,   212,
     213,   209,   215,   217,   219,   233,   236,   238,   240,   184,
     309,   418,   455,     0,   374,   247,     0,     0,   583,     0,
     540,   274,   614,   615,   616,   613,   619,   633,   635,   648,
     651,     0,     0,     0,     0,   731,    58,   485,   510,   577,
     376,     0,   598,   587,     0,   741,     0,   733,   597,     0,
     743,   748,     0,   746,     0,     0,   745,   757,     0,     0,
       0,   762,     0,   750,   752,   753,   754,   755,   756,   747,
       0,     0,     0,     0,     0,     0,   749,     0,   759,   760,
     761,     0,   751,   758,   763
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,    -5,  -932,   415,
    -932,  -932,  -932,  -932,  -932,  -932,   297,  -932,  -533,  -932,
    -932,  -932,   -74,  -932,  -932,  -932,   603,  -932,  -932,  -932,
    -932,   331,   542,  -932,  -932,   -62,   -42,   -40,   -34,   -30,
     -29,   -27,   -26,     4,     5,     7,  -932,     8,     9,    10,
      11,  -932,   343,    21,  -932,    23,  -932,    24,  -932,    26,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,   330,   535,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   248,  -932,
      61,  -932,  -652,    67,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,   -66,  -932,  -686,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,    40,  -932,  -932,
    -932,  -932,  -932,    50,  -675,  -932,  -932,  -932,  -932,    48,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,    37,  -932,
    -932,  -932,    43,   504,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,    35,  -932,  -932,  -932,  -932,  -932,  -932,  -931,  -932,
    -932,  -932,    62,  -932,  -932,  -932,    66,   541,  -932,  -932,
    -929,  -932,  -928,  -932,    30,  -932,    32,  -932,    36,  -932,
    -932,  -932,  -927,  -932,  -932,  -932,  -932,    63,  -932,  -932,
    -145,   941,  -932,  -932,  -932,  -932,  -932,    71,  -932,  -932,
    -932,    72,  -932,   544,  -932,   -76,  -932,  -932,  -932,  -932,
    -932,   -70,  -932,  -932,  -932,  -932,  -932,   -24,  -932,  -932,
    -932,    69,  -932,  -932,  -932,    74,  -932,   546,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,    15,
    -932,  -932,  -932,    22,   548,  -932,  -932,   -58,  -932,    -8,
    -932,  -932,  -932,  -932,  -932,    18,  -932,  -932,  -932,    33,
     547,  -932,  -932,  -932,  -932,  -932,  -932,  -932,   -47,  -932,
    -932,  -932,    75,  -932,  -932,  -932,    79,  -932,   550,   334,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -926,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,    85,  -932,  -932,  -932,  -131,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,    57,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,    58,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,    51,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,   346,   553,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,  -932,   385,   557,  -932,  -932,  -932,  -932,  -932,  -932,
    -932,   391,   552,   -72,  -932,  -932,    55,  -932,  -932,  -120,
    -932,  -932,  -932,  -932,  -932,  -932,  -140,  -932,  -932,  -159,
    -932,  -932,  -932,  -932,  -932,  -932,  -932
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   693,    92,    93,    43,    72,    89,    90,   717,   908,
    1010,  1011,   780,    45,    74,   101,   102,   103,   410,    47,
      75,   157,   158,   159,   418,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   440,   686,   176,   441,   177,   442,   178,   463,   179,
     464,   180,   436,   181,   420,    49,    76,   210,   211,   212,
     468,   213,   182,   421,   183,   422,   184,   423,   805,   806,
     807,   948,   781,   782,   783,   926,  1151,   784,   927,   785,
     928,   786,   929,   787,   788,   505,   789,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   935,   799,   800,   938,
     801,   939,   802,   940,   185,   453,   839,   840,   841,   968,
     186,   450,   826,   827,   828,   829,   187,   452,   834,   835,
     836,   837,   188,   451,   189,   456,   850,   851,   852,   977,
      65,    84,   357,   358,   359,   518,   360,   519,   190,   457,
     859,   860,   861,   862,   863,   864,   865,   866,   191,   443,
     809,   810,   811,   951,    51,    77,   246,   247,   248,   474,
     249,   475,   250,   476,   251,   480,   252,   479,   192,   448,
     699,   254,   255,   193,   449,   821,   822,   823,   960,  1077,
    1078,   194,   444,    59,    81,   813,   814,   815,   954,    61,
      82,   322,   323,   324,   325,   326,   327,   328,   504,   329,
     508,   330,   507,   331,   332,   509,   333,   195,   445,   817,
     818,   819,   957,    63,    83,   343,   344,   345,   346,   347,
     513,   348,   349,   350,   351,   257,   472,   910,   911,   912,
    1012,    53,    78,   268,   269,   270,   484,   196,   446,   197,
     447,   260,   473,   914,   915,   916,  1015,    55,    79,   284,
     285,   286,   487,   287,   288,   489,   289,   290,   198,   455,
     846,   847,   848,   974,    57,    80,   302,   303,   304,   305,
     495,   306,   496,   307,   497,   308,   498,   309,   499,   310,
     500,   311,   494,   262,   481,   919,   920,  1018,   199,   454,
     843,   844,   971,  1095,  1096,  1097,  1098,  1099,  1166,  1100,
     200,   458,   876,   877,   878,   988,  1175,   879,   880,   989,
     881,   882,   201,   202,   460,   888,   889,   890,   995,   891,
     996,   203,   461,   898,   899,   900,   901,  1000,   902,   903,
    1002,   204,   462,    67,    85,   379,   380,   381,   382,   523,
     383,   524,   384,   385,   526,   386,   387,   388,   529,   749,
     389,   530,   390,   391,   392,   533,   393,   534,   394,   535,
     395,   536,   104,   412,   105,   413,   106,   414,   205,   419,
      71,    87,   401,   402,   403,   541,   404,   107,   411,    69,
      86,   396,   397,   206,   465,   906,   907,  1006,  1134,  1135,
    1136,  1137,  1183,  1138,  1181,  1202,  1203,  1204,  1212,  1213,
    1214,  1220,  1215,  1216,  1217,  1218,  1224
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   156,   209,   226,   264,   278,   298,   341,   320,   339,
     356,   376,    40,   342,   398,   227,   321,   340,   214,   258,
     271,   282,   300,   873,   334,   352,   803,   377,   833,  1070,
     261,  1071,  1072,  1076,  1082,   228,    33,   229,    34,    94,
      35,   416,   292,   230,   136,   137,   417,   231,   232,   917,
     233,   234,    32,   256,   267,   281,   299,   207,   208,   466,
     136,   137,   470,   963,   467,   824,   964,   471,   215,   259,
     272,   283,   301,   966,   335,   353,   967,   378,   354,   355,
     723,   235,   236,    44,   237,   238,   239,   240,   241,    46,
     482,    91,   729,   730,   731,   483,   883,   884,   242,   313,
     243,   244,   485,   245,    48,   867,   134,   486,   265,   279,
     266,   280,    50,   253,   766,   892,   893,   894,   492,   972,
      52,   761,   973,   493,   136,   137,   762,   763,   764,   765,
     766,   767,   768,   769,   770,   771,   772,   773,   774,   775,
     776,   777,   778,   779,   314,   135,   315,   316,   825,    54,
     317,   318,   319,    99,    99,   695,   696,   697,   698,    56,
     135,   136,   137,   136,   137,   520,   314,   136,   137,   895,
     521,   399,   400,   273,   274,   275,   276,   277,   136,   137,
      58,   291,    60,   681,   682,   683,   684,   292,   293,   294,
     295,   296,   297,    95,   537,  1007,   539,   223,  1008,   538,
     224,   540,   543,    96,    97,    98,  1207,   544,    62,  1208,
    1209,  1210,  1211,   868,   869,   870,   871,   466,   354,   355,
     685,    99,   922,    36,    37,    38,    39,  1147,  1148,  1149,
    1150,    64,  1070,    99,  1071,  1072,  1076,  1082,   747,   748,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    66,    68,   127,   128,   129,   130,   131,   132,    70,
     405,   135,   853,   854,   855,   856,   857,   858,   155,   539,
      99,   216,    99,   217,   923,  1205,    99,   406,  1206,   136,
     137,   218,   219,   220,   221,   222,   138,    99,   543,   408,
     470,   833,    99,   924,   135,   925,  1041,   314,   223,   135,
     314,   224,   145,   945,   409,   263,   945,   873,   946,   225,
     407,   947,   136,   137,   136,   137,   969,   136,   137,   824,
     831,   970,   832,   314,   336,   315,   316,   337,   338,   415,
     986,   223,   424,   425,   224,   987,   426,  1088,  1089,   427,
     136,   137,   100,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   153,   154,
     428,  1172,  1173,  1174,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   429,   430,   127,   128,   129,
     130,   131,   132,   133,   993,   135,   314,   431,    99,   994,
     997,   502,   156,  1003,   501,   998,   209,  1127,  1004,  1128,
    1129,   545,   546,   136,   137,   432,   219,   220,   226,   222,
     138,   264,   214,   433,   537,   503,   434,   435,   278,  1005,
     227,    99,   223,    99,   258,   224,    99,   271,   298,   437,
     438,   945,   482,   225,   282,   261,  1159,  1160,   320,   439,
     228,   341,   229,   339,   300,  1163,   321,   342,   230,    99,
    1164,   340,   231,   232,   334,   233,   234,   459,   256,   352,
     520,   267,   215,   376,  1184,  1171,   485,   398,   281,  1185,
     492,  1187,   469,   477,   259,  1188,  1225,   272,   299,   377,
     478,  1226,   153,   154,   283,   488,   235,   236,   490,   237,
     238,   239,   240,   241,   301,   491,   506,   510,   511,   512,
     547,   514,   515,   242,   335,   243,   244,   516,   245,   353,
     517,   560,    99,   522,   525,   265,   527,   266,   253,   528,
     531,   532,   279,   542,   280,   548,   549,   550,   568,   378,
     551,   552,   561,   554,   555,   108,   109,   556,   557,   110,
     558,   559,   111,   112,   113,   671,   672,   673,   562,   572,
     563,   564,   565,   566,   567,   576,   569,   570,   571,   573,
     577,   574,   575,   578,   579,   580,   581,   582,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     583,   584,   585,   586,   587,   156,   588,   589,   398,   590,
     591,   592,   209,   593,   594,   596,   597,   136,   137,   595,
     598,   136,   137,   599,   138,   600,   601,   603,   214,   139,
     140,   141,   142,   143,   606,   144,   604,   607,   608,   609,
     145,   610,   611,   612,   613,   872,   885,   614,   376,   146,
     615,   743,   147,   617,   619,   620,   621,   622,   623,   148,
     625,   874,   886,   896,   377,   626,   627,   149,   150,   628,
     629,   151,   630,   756,   631,   152,   633,   634,   215,   636,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   637,   638,   641,   153,   154,   635,   155,
     374,   375,   645,   646,   649,   639,   642,   643,   648,   650,
     652,   875,   887,   897,   378,   655,   651,   653,   656,   659,
     660,   654,   661,   662,   665,   657,    99,   668,   666,   669,
      99,   670,   675,   676,   674,   677,   658,   678,   679,   689,
     680,   687,   688,   690,   691,   694,   700,    34,   701,   702,
     703,   713,   705,   704,   706,   707,   714,   720,   708,   709,
     710,   711,   712,   715,   716,   718,   719,   721,   722,   724,
     725,   726,   727,   728,   732,   733,   734,   735,   736,   737,
     738,   739,   740,   741,   742,   744,   745,   746,   750,   755,
     804,  1199,   808,   752,   812,   816,   753,   820,   842,   845,
     754,   838,   849,   905,   909,   913,   930,   931,   932,   933,
     934,   936,   937,   941,   942,   943,   944,   950,  1009,   949,
     953,   952,   955,   956,   958,   959,   962,   961,  1152,   976,
     965,   975,   979,   978,   980,   981,   982,   983,   984,   985,
     990,   991,   992,   999,  1001,  1014,  1025,  1013,  1017,  1016,
    1021,  1027,  1019,  1020,  1022,  1023,  1024,  1030,  1026,  1028,
    1029,  1033,  1031,  1034,  1032,  1035,  1086,  1036,  1113,  1037,
    1114,  1039,  1038,  1106,  1107,  1108,  1109,  1110,  1111,  1115,
    1116,  1117,  1119,  1120,  1123,  1124,  1125,   226,  1122,  1140,
     320,   341,  1141,   339,  1146,  1153,  1049,   342,   321,   227,
    1154,   340,  1155,   258,  1069,  1156,   334,  1090,  1050,   352,
     298,  1161,  1080,   356,   261,  1091,  1162,  1167,  1168,   228,
    1169,   229,  1170,  1093,  1157,  1182,   300,   230,  1051,   872,
    1052,   231,   232,   885,   233,   234,  1053,   256,  1191,  1194,
    1054,  1055,  1130,  1056,  1057,   874,  1079,  1196,   264,   886,
    1131,   278,  1192,   259,  1158,   896,   335,  1092,  1132,   353,
     299,  1165,  1081,  1176,   271,   235,   236,   282,   237,   238,
     239,   240,   241,  1094,  1058,  1059,   301,  1060,  1061,  1062,
    1063,  1064,   242,  1201,   243,   244,  1177,   245,  1221,  1222,
    1223,  1065,  1178,  1066,  1067,   875,  1068,   253,   267,   887,
    1073,   281,  1074,  1227,  1231,   897,  1075,   692,  1133,   830,
     757,  1179,   751,   921,   272,   605,   760,   283,   602,  1087,
    1186,  1042,  1040,  1084,  1085,  1044,  1105,  1043,  1190,   553,
    1104,  1112,   312,   616,   647,  1083,  1045,  1046,  1048,  1143,
    1189,  1047,  1195,   618,  1142,  1145,  1198,  1200,  1193,   624,
    1233,  1228,   265,  1229,   266,   279,  1230,   280,  1144,  1234,
    1118,  1103,   632,  1102,  1126,  1121,   640,  1101,   904,   918,
     759,   758,  1139,   644,  1197,  1219,  1232,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1049,
     663,   664,     0,     0,     0,  1090,     0,  1069,     0,     0,
     667,  1050,     0,  1091,     0,  1080,     0,     0,     0,     0,
    1130,  1093,     0,     0,     0,     0,     0,     0,  1131,     0,
    1180,  1051,     0,  1052,     0,     0,  1132,     0,     0,  1053,
       0,     0,     0,  1054,  1055,     0,  1056,  1057,     0,  1079,
       0,     0,     0,     0,     0,  1092,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1081,     0,     0,     0,     0,
       0,  1094,     0,     0,     0,     0,     0,  1058,  1059,     0,
    1060,  1061,  1062,  1063,  1064,     0,  1133,     0,     0,     0,
       0,     0,     0,     0,  1065,     0,  1066,  1067,     0,  1068,
       0,     0,     0,  1073,     0,  1074,     0,     0,     0,  1075
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    17,    83,    86,    77,    82,    83,    76,    77,
      78,    79,    80,   709,    82,    83,   678,    85,   703,   960,
      77,   960,   960,   960,   960,    77,     5,    77,     7,    10,
       9,     3,   107,    77,    83,    84,     8,    77,    77,   114,
      77,    77,     0,    77,    78,    79,    80,    16,    17,     3,
      83,    84,     3,     3,     8,   109,     6,     8,    76,    77,
      78,    79,    80,     3,    82,    83,     6,    85,   116,   117,
     613,    77,    77,     7,    77,    77,    77,    77,    77,     7,
       3,   192,   625,   626,   627,     8,   135,   136,    77,    21,
      77,    77,     3,    77,     7,    21,    64,     8,    78,    79,
      78,    79,     7,    77,    30,   138,   139,   140,     3,     3,
       7,    21,     6,     8,    83,    84,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    66,    65,    68,    69,   192,     7,
      72,    73,    74,   192,   192,    91,    92,    93,    94,     7,
      65,    83,    84,    83,    84,     3,    66,    83,    84,   192,
       8,    13,    14,    78,    79,    80,    81,    82,    83,    84,
       7,   101,     7,   158,   159,   160,   161,   107,   108,   109,
     110,   111,   112,   164,     3,     3,     3,   102,     6,     8,
     105,     8,     3,   174,   175,   176,   167,     8,     7,   170,
     171,   172,   173,   129,   130,   131,   132,     3,   116,   117,
     195,   192,     8,   192,   193,   194,   195,    22,    23,    24,
      25,     7,  1163,   192,  1163,  1163,  1163,  1163,   155,   156,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,     7,     7,    57,    58,    59,    60,    61,    62,     7,
       6,    65,   119,   120,   121,   122,   123,   124,   165,     3,
     192,    75,   192,    77,     8,     3,   192,     3,     6,    83,
      84,    85,    86,    87,    88,    89,    90,   192,     3,     8,
       3,   966,   192,     8,    65,     8,   948,    66,   102,    65,
      66,   105,   106,     3,     3,    76,     3,   993,     8,   113,
       4,     8,    83,    84,    83,    84,     3,    83,    84,   109,
     110,     8,   112,    66,    67,    68,    69,    70,    71,     4,
       3,   102,     4,     4,   105,     8,     4,   103,   104,     4,
      83,    84,   416,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   162,   163,
       4,   126,   127,   128,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,     4,     4,    57,    58,    59,
      60,    61,    62,    63,     3,    65,    66,     4,   192,     8,
       3,     3,   466,     3,     8,     8,   470,   166,     8,   168,
     169,   406,   407,    83,    84,     4,    86,    87,   482,    89,
      90,   485,   470,     4,     3,     8,     4,     4,   492,     8,
     482,   192,   102,   192,   482,   105,   192,   485,   502,     4,
       4,     3,     3,   113,   492,   482,     8,     8,   512,     4,
     482,   517,   482,   517,   502,     3,   512,   517,   482,   192,
       8,   517,   482,   482,   512,   482,   482,     4,   482,   517,
       3,   485,   470,   537,     3,     8,     3,   539,   492,     8,
       3,     8,     4,     4,   482,     8,     3,   485,   502,   537,
       4,     8,   162,   163,   492,     4,   482,   482,     4,   482,
     482,   482,   482,   482,   502,     4,     4,     4,     8,     3,
     192,     4,     4,   482,   512,   482,   482,     8,   482,   517,
       3,   193,   192,     4,     4,   485,     4,   485,   482,     4,
       4,     4,   492,     4,   492,     4,     4,     4,   195,   537,
       4,     4,   193,     4,     4,    11,    12,     4,     4,    15,
       4,     4,    18,    19,    20,   550,   551,   552,   193,     4,
     193,   193,   193,   193,   193,     4,   194,   194,   193,   195,
       4,   195,   195,     4,     4,     4,     4,     4,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       4,     4,     4,     4,     4,   669,     4,     4,   670,     4,
       4,     4,   676,     4,     4,     4,     4,    83,    84,   193,
       4,    83,    84,     4,    90,     4,     4,     4,   676,    95,
      96,    97,    98,    99,     4,   101,   195,     4,     4,     4,
     106,     4,   193,   195,     4,   709,   710,     4,   712,   115,
       4,   646,   118,     4,     4,   193,     4,   193,   193,   125,
       4,   709,   710,   711,   712,     4,     4,   133,   134,     4,
       4,   137,     4,   668,     4,   141,     4,     4,   676,     4,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,     4,     4,     4,   162,   163,   193,   165,
     162,   163,     4,     4,     4,   195,   195,   195,   195,     4,
       4,   709,   710,   711,   712,     4,   193,   193,     4,     4,
       4,   193,     4,     4,     4,   195,   192,     4,   193,     7,
     192,     7,     7,     7,   192,     7,   195,     7,     5,     5,
     192,   192,   192,     5,     5,   192,     5,     7,     5,     5,
       5,   192,     5,     7,     5,     5,   192,   192,     7,     7,
       7,     7,     7,     5,     5,     5,     5,   192,   192,   192,
       7,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   157,     5,
       7,     5,     7,   192,     7,     7,   192,     7,     7,     7,
     192,   100,     7,     7,     7,     7,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   192,     6,
       3,     6,     6,     3,     6,     3,     3,     6,   192,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   193,     6,     3,     6,
       4,   193,     8,     6,     4,     4,     4,     4,   195,   195,
     193,     4,   193,     4,   193,     4,     4,   193,     4,   193,
       4,   193,   195,   193,   193,   193,   193,   193,   193,   193,
     193,   193,     4,     4,     4,   193,     4,   951,   195,     6,
     954,   957,     3,   957,     4,   192,   960,   957,   954,   951,
     192,   957,   192,   951,   960,   192,   954,   971,   960,   957,
     974,     8,   960,   977,   951,   971,     8,     4,     8,   951,
       3,   951,     8,   971,   192,     4,   974,   951,   960,   993,
     960,   951,   951,   997,   951,   951,   960,   951,     4,     4,
     960,   960,  1006,   960,   960,   993,   960,     4,  1012,   997,
    1006,  1015,   195,   951,   192,  1003,   954,   971,  1006,   957,
     974,   192,   960,   192,  1012,   951,   951,  1015,   951,   951,
     951,   951,   951,   971,   960,   960,   974,   960,   960,   960,
     960,   960,   951,     7,   951,   951,   192,   951,     4,     4,
       4,   960,   192,   960,   960,   993,   960,   951,  1012,   997,
     960,  1015,   960,     4,     4,  1003,   960,   582,  1006,   702,
     669,   192,   659,   755,  1012,   470,   676,  1015,   466,   969,
     192,   950,   945,   963,   966,   953,   979,   951,  1163,   416,
     977,   986,    81,   482,   520,   962,   954,   956,   959,  1014,
     192,   957,   193,   485,  1012,  1017,   192,   192,  1169,   492,
     192,   195,  1012,   193,  1012,  1015,   193,  1015,  1015,   192,
     993,   976,   502,   974,  1003,   997,   512,   972,   712,   725,
     675,   670,  1007,   517,  1184,  1205,  1225,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1163,
     537,   539,    -1,    -1,    -1,  1169,    -1,  1163,    -1,    -1,
     543,  1163,    -1,  1169,    -1,  1163,    -1,    -1,    -1,    -1,
    1184,  1169,    -1,    -1,    -1,    -1,    -1,    -1,  1184,    -1,
    1125,  1163,    -1,  1163,    -1,    -1,  1184,    -1,    -1,  1163,
      -1,    -1,    -1,  1163,  1163,    -1,  1163,  1163,    -1,  1163,
      -1,    -1,    -1,    -1,    -1,  1169,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1163,    -1,    -1,    -1,    -1,
      -1,  1169,    -1,    -1,    -1,    -1,    -1,  1163,  1163,    -1,
    1163,  1163,  1163,  1163,  1163,    -1,  1184,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1163,    -1,  1163,  1163,    -1,  1163,
      -1,    -1,    -1,  1163,    -1,  1163,    -1,    -1,    -1,  1163
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,     5,     7,     9,   192,   193,   194,   195,
     213,   214,   215,   220,     7,   229,     7,   235,     7,   271,
       7,   370,     7,   447,     7,   463,     7,   480,     7,   399,
       7,   405,     7,   429,     7,   346,     7,   549,     7,   595,
       7,   586,   221,   216,   230,   236,   272,   371,   448,   464,
     481,   400,   406,   430,   347,   550,   596,   587,   213,   222,
     223,   192,   218,   219,    10,   164,   174,   175,   176,   192,
     228,   231,   232,   233,   578,   580,   582,   593,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    83,    84,    90,    95,
      96,    97,    98,    99,   101,   106,   115,   118,   125,   133,
     134,   137,   141,   162,   163,   165,   228,   237,   238,   239,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   259,   261,   263,   265,
     267,   269,   278,   280,   282,   320,   326,   332,   338,   340,
     354,   364,   384,   389,   397,   423,   453,   455,   474,   504,
     516,   528,   529,   537,   547,   584,   599,    16,    17,   228,
     273,   274,   275,   277,   453,   455,    75,    77,    85,    86,
      87,    88,    89,   102,   105,   113,   228,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   253,   254,
     255,   256,   259,   261,   263,   265,   372,   373,   374,   376,
     378,   380,   382,   384,   387,   388,   423,   441,   453,   455,
     457,   474,   499,    76,   228,   380,   382,   423,   449,   450,
     451,   453,   455,    78,    79,    80,    81,    82,   228,   380,
     382,   423,   453,   455,   465,   466,   467,   469,   470,   472,
     473,   101,   107,   108,   109,   110,   111,   112,   228,   423,
     453,   455,   482,   483,   484,   485,   487,   489,   491,   493,
     495,   497,   397,    21,    66,    68,    69,    72,    73,    74,
     228,   300,   407,   408,   409,   410,   411,   412,   413,   415,
     417,   419,   420,   422,   453,   455,    67,    70,    71,   228,
     300,   411,   417,   431,   432,   433,   434,   435,   437,   438,
     439,   440,   453,   455,   116,   117,   228,   348,   349,   350,
     352,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   162,   163,   228,   453,   455,   551,
     552,   553,   554,   556,   558,   559,   561,   562,   563,   566,
     568,   569,   570,   572,   574,   576,   597,   598,   599,    13,
      14,   588,   589,   590,   592,     6,     3,     4,     8,     3,
     234,   594,   579,   581,   583,     4,     3,     8,   240,   585,
     270,   279,   281,   283,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   268,     4,     4,     4,
     257,   260,   262,   365,   398,   424,   454,   456,   385,   390,
     327,   339,   333,   321,   505,   475,   341,   355,   517,     4,
     530,   538,   548,   264,   266,   600,     3,     8,   276,     4,
       3,     8,   442,   458,   375,   377,   379,     4,     4,   383,
     381,   500,     3,     8,   452,     3,     8,   468,     4,   471,
       4,     4,     3,     8,   498,   486,   488,   490,   492,   494,
     496,     8,     3,     8,   414,   301,     4,   418,   416,   421,
       4,     8,     3,   436,     4,     4,     8,     3,   351,   353,
       3,     8,     4,   555,   557,     4,   560,     4,     4,   564,
     567,     4,     4,   571,   573,   575,   577,     3,     8,     3,
       8,   591,     4,     3,     8,   213,   213,   192,     4,     4,
       4,     4,     4,   232,     4,     4,     4,     4,     4,     4,
     193,   193,   193,   193,   193,   193,   193,   193,   195,   194,
     194,   193,     4,   195,   195,   195,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   193,     4,     4,     4,     4,
       4,     4,   238,     4,   195,   274,     4,     4,     4,     4,
       4,   193,   195,     4,     4,     4,   373,     4,   450,     4,
     193,     4,   193,   193,   466,     4,     4,     4,     4,     4,
       4,     4,   484,     4,     4,   193,     4,     4,     4,   195,
     409,     4,   195,   195,   433,     4,     4,   349,   195,     4,
       4,   193,     4,   193,   193,     4,     4,   195,   195,     4,
       4,     4,     4,   552,   598,     4,   193,   589,     4,     7,
       7,   213,   213,   213,   192,     7,     7,     7,     7,     5,
     192,   158,   159,   160,   161,   195,   258,   192,   192,     5,
       5,     5,   215,   217,   192,    91,    92,    93,    94,   386,
       5,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,   192,   192,     5,     5,   224,     5,     5,
     192,   192,   192,   224,   192,     7,   192,   192,   192,   224,
     224,   224,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   213,   192,   192,   192,   155,   156,   565,
     157,   258,   192,   192,   192,     5,   213,   237,   597,   588,
     273,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
     228,   288,   289,   290,   293,   295,   297,   299,   300,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   313,
     314,   316,   318,   288,     7,   284,   285,   286,     7,   366,
     367,   368,     7,   401,   402,   403,     7,   425,   426,   427,
       7,   391,   392,   393,   109,   192,   328,   329,   330,   331,
     222,   110,   112,   330,   334,   335,   336,   337,   100,   322,
     323,   324,     7,   506,   507,     7,   476,   477,   478,     7,
     342,   343,   344,   119,   120,   121,   122,   123,   124,   356,
     357,   358,   359,   360,   361,   362,   363,    21,   129,   130,
     131,   132,   228,   302,   453,   455,   518,   519,   520,   523,
     524,   526,   527,   135,   136,   228,   453,   455,   531,   532,
     533,   535,   138,   139,   140,   192,   453,   455,   539,   540,
     541,   542,   544,   545,   551,     7,   601,   602,   225,     7,
     443,   444,   445,     7,   459,   460,   461,   114,   485,   501,
     502,   284,     8,     8,     8,     8,   291,   294,   296,   298,
       4,     4,     4,     4,     4,   312,     4,     4,   315,   317,
     319,     4,     4,     4,     4,     3,     8,     8,   287,     6,
       3,   369,     6,     3,   404,     6,     3,   428,     6,     3,
     394,     6,     3,     3,     6,     6,     3,     6,   325,     3,
       8,   508,     3,     6,   479,     6,     3,   345,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   521,   525,
       4,     4,     4,     3,     8,   534,   536,     3,     8,     4,
     543,     4,   546,     3,     8,     8,   603,     3,     6,   192,
     226,   227,   446,     6,     3,   462,     6,     3,   503,     8,
       6,     4,     4,     4,     4,   193,   195,   193,   195,   193,
       4,   193,   193,     4,     4,     4,   193,   193,   195,   193,
     289,   288,   286,   372,   368,   407,   403,   431,   427,   228,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   253,   254,   255,   256,   259,   261,   263,   265,   300,
     364,   376,   378,   380,   382,   384,   388,   395,   396,   423,
     453,   455,   499,   393,   329,   335,     4,   323,   103,   104,
     228,   300,   423,   453,   455,   509,   510,   511,   512,   513,
     515,   507,   482,   478,   348,   344,   193,   193,   193,   193,
     193,   193,   357,     4,     4,   193,   193,   193,   519,     4,
       4,   532,   195,     4,   193,     4,   540,   166,   168,   169,
     228,   300,   453,   455,   604,   605,   606,   607,   609,   602,
       6,     3,   449,   445,   465,   461,     4,    22,    23,    24,
      25,   292,   192,   192,   192,   192,   192,   192,   192,     8,
       8,     8,     8,     3,     8,   192,   514,     4,     8,     3,
       8,     8,   126,   127,   128,   522,   192,   192,   192,   192,
     213,   610,     4,   608,     3,     8,   192,     8,     8,   192,
     396,     4,   195,   511,     4,   193,     4,   605,   192,     5,
     192,     7,   611,   612,   613,     3,     6,   167,   170,   171,
     172,   173,   614,   615,   616,   618,   619,   620,   621,   612,
     617,     4,     4,     4,   622,     3,     8,     4,   195,   193,
     193,     4,   615,   192,   192
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   196,   198,   197,   199,   197,   200,   197,   201,   197,
     202,   197,   203,   197,   204,   197,   205,   197,   206,   197,
     207,   197,   208,   197,   209,   197,   210,   197,   211,   197,
     212,   197,   213,   213,   213,   213,   213,   213,   213,   214,
     216,   215,   217,   218,   218,   219,   219,   221,   220,   222,
     222,   223,   223,   225,   224,   226,   226,   227,   227,   228,
     230,   229,   231,   231,   232,   232,   232,   232,   232,   232,
     234,   233,   236,   235,   237,   237,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   240,   239,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   257,   256,   258,   258,   258,   258,   258,   260,
     259,   262,   261,   264,   263,   266,   265,   268,   267,   270,
     269,   272,   271,   273,   273,   274,   274,   274,   274,   274,
     276,   275,   277,   279,   278,   281,   280,   283,   282,   284,
     284,   285,   285,   287,   286,   288,   288,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   291,   290,
     292,   292,   292,   292,   294,   293,   296,   295,   298,   297,
     299,   301,   300,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   312,   311,   313,   315,   314,   317,   316,   319,
     318,   321,   320,   322,   322,   323,   325,   324,   327,   326,
     328,   328,   329,   329,   330,   331,   333,   332,   334,   334,
     335,   335,   335,   336,   337,   339,   338,   341,   340,   342,
     342,   343,   343,   345,   344,   347,   346,   348,   348,   348,
     349,   349,   351,   350,   353,   352,   355,   354,   356,   356,
     357,   357,   357,   357,   357,   357,   358,   359,   360,   361,
     362,   363,   365,   364,   366,   366,   367,   367,   369,   368,
     371,   370,   372,   372,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   375,
     374,   377,   376,   379,   378,   381,   380,   383,   382,   385,
     384,   386,   386,   386,   386,   387,   388,   390,   389,   391,
     391,   392,   392,   394,   393,   395,   395,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   398,
     397,   400,   399,   401,   401,   402,   402,   404,   403,   406,
     405,   407,   407,   408,   408,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   410,   411,   412,   414,   413,
     416,   415,   418,   417,   419,   421,   420,   422,   424,   423,
     425,   425,   426,   426,   428,   427,   430,   429,   431,   431,
     432,   432,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   434,   436,   435,   437,   438,   439,   440,   442,   441,
     443,   443,   444,   444,   446,   445,   448,   447,   449,   449,
     450,   450,   450,   450,   450,   450,   450,   452,   451,   454,
     453,   456,   455,   458,   457,   459,   459,   460,   460,   462,
     461,   464,   463,   465,   465,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   468,   467,   469,   471,
     470,   472,   473,   475,   474,   476,   476,   477,   477,   479,
     478,   481,   480,   482,   482,   483,   483,   484,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   486,   485,
     488,   487,   490,   489,   492,   491,   494,   493,   496,   495,
     498,   497,   500,   499,   501,   501,   503,   502,   505,   504,
     506,   506,   508,   507,   509,   509,   510,   510,   511,   511,
     511,   511,   511,   511,   511,   512,   514,   513,   515,   517,
     516,   518,   518,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   521,   520,   522,   522,   522,   523,   525,   524,
     526,   527,   528,   530,   529,   531,   531,   532,   532,   532,
     532,   532,   534,   533,   536,   535,   538,   537,   539,   539,
     540,   540,   540,   540,   540,   540,   541,   543,   542,   544,
     546,   545,   548,   547,   550,   549,   551,   551,   552,   552,
     552,   552,   552,   552,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   553,   555,   554,   557,
     556,   558,   560,   559,   561,   562,   564,   563,   565,   565,
     567,   566,   568,   569,   571,   570,   573,   572,   575,   574,
     577,   576,   579,   578,   581,   580,   583,   582,   585,   584,
     587,   586,   588,   588,   589,   589,   591,   590,   592,   594,
     593,   596,   595,   597,   597,   598,   600,   599,   601,   601,
     603,   602,   604,   604,   605,   605,   605,   605,   605,   605,
     605,   606,   608,   607,   610,   609,   611,   611,   613,   612,
     614,   614,   615,   615,   615,   615,   615,   617,   616,   618,
     619,   620,   622,   621
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     3,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4
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
  "\"server-tag\"", "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"shared-networks\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp4\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_LOGGING", "SUB_CONFIG_CONTROL",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "value", "sub_json", "map2", "$@16", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@17", "list_content",
  "not_empty_list", "list_strings", "$@18", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@19",
  "global_objects", "global_object", "dhcp6_object", "$@20", "sub_dhcp6",
  "$@21", "global_params", "global_param", "data_directory", "$@22",
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@23", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@24", "ddns_qualifying_suffix", "$@25",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "server_tag", "$@28", "interfaces_config", "$@29", "sub_interfaces6",
  "$@30", "interfaces_config_params", "interfaces_config_param",
  "interfaces_list", "$@31", "re_detect", "lease_database", "$@32",
  "hosts_database", "$@33", "hosts_databases", "$@34", "database_list",
  "not_empty_database_list", "database", "$@35", "database_map_params",
  "database_map_param", "database_type", "$@36", "db_type", "user", "$@37",
  "password", "$@38", "host", "$@39", "port", "name", "$@40", "persist",
  "lfc_interval", "readonly", "connect_timeout", "reconnect_wait_time",
  "max_row_errors", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@41", "max_reconnect_tries", "keyspace", "$@42",
  "consistency", "$@43", "serial_consistency", "$@44", "sanity_checks",
  "$@45", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@46", "mac_sources", "$@47", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@48",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@49",
  "hooks_libraries", "$@50", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@51",
  "sub_hooks_library", "$@52", "hooks_params", "hooks_param", "library",
  "$@53", "parameters", "$@54", "expired_leases_processing", "$@55",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@56",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@57",
  "sub_subnet6", "$@58", "subnet6_params", "subnet6_param", "subnet",
  "$@59", "interface", "$@60", "interface_id", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@66", "shared_network_params", "shared_network_param",
  "option_def_list", "$@67", "sub_option_def_list", "$@68",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@69", "sub_option_def", "$@70",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool6", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "pd_pools_list", "$@85",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@86", "sub_pd_pool", "$@87", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@88", "pd_prefix_len", "excluded_prefix", "$@89",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@90",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@93", "prefixes", "$@94", "duid", "$@95", "hw_address", "$@96",
  "hostname", "$@97", "flex_id_value", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "ip_address", "$@101", "client_classes", "$@102", "client_classes_list",
  "client_class_entry", "$@103", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@104", "only_if_required",
  "server_id", "$@105", "server_id_params", "server_id_param",
  "server_id_type", "$@106", "duid_type", "htype", "identifier", "$@107",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@108",
  "control_socket_params", "control_socket_param", "socket_type", "$@109",
  "socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@116",
  "server_ip", "$@117", "server_port", "sender_ip", "$@118", "sender_port",
  "max_queue_size", "ncr_protocol", "$@119", "ncr_protocol_value",
  "ncr_format", "$@120", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@121",
  "dep_generated_prefix", "$@122", "dep_hostname_char_set", "$@123",
  "dep_hostname_char_replacement", "$@124", "dhcp4_json_object", "$@125",
  "dhcpddns_json_object", "$@126", "control_agent_json_object", "$@127",
  "config_control", "$@128", "sub_config_control", "$@129",
  "config_control_params", "config_control_param", "config_databases",
  "$@130", "config_fetch_wait_time", "logging_object", "$@131",
  "sub_logging", "$@132", "logging_params", "logging_param", "loggers",
  "$@133", "loggers_entries", "logger_entry", "$@134", "logger_params",
  "logger_param", "debuglevel", "severity", "$@135", "output_options_list",
  "$@136", "output_options_list_content", "output_entry", "$@137",
  "output_params_list", "output_params", "output", "$@138", "flush",
  "maxsize", "maxver", "pattern", "$@139", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   280,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   289,   290,   290,   291,   291,   292,   292,   293,   293,
     294,   294,   302,   303,   304,   305,   306,   307,   308,   311,
     316,   316,   327,   330,   331,   334,   338,   345,   345,   352,
     353,   356,   360,   367,   367,   374,   375,   378,   382,   393,
     403,   403,   418,   419,   423,   424,   425,   426,   427,   428,
     431,   431,   446,   446,   455,   456,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   512,   512,   520,   525,   530,
     535,   540,   545,   550,   555,   560,   565,   570,   575,   580,
     585,   590,   595,   595,   603,   606,   609,   612,   615,   621,
     621,   629,   629,   637,   637,   645,   645,   653,   653,   661,
     661,   672,   672,   681,   682,   685,   686,   687,   688,   689,
     692,   692,   702,   708,   708,   720,   720,   732,   732,   742,
     743,   746,   747,   750,   750,   760,   761,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,   774,   775,   776,
     777,   778,   779,   780,   781,   782,   783,   784,   787,   787,
     794,   795,   796,   797,   800,   800,   808,   808,   816,   816,
     824,   829,   829,   837,   842,   847,   852,   857,   862,   867,
     872,   877,   882,   882,   890,   895,   895,   903,   903,   911,
     911,   919,   919,   929,   930,   932,   934,   934,   952,   952,
     962,   963,   966,   967,   970,   975,   980,   980,   990,   991,
     994,   995,   996,   999,  1004,  1011,  1011,  1021,  1021,  1031,
    1032,  1035,  1036,  1039,  1039,  1049,  1049,  1059,  1060,  1061,
    1064,  1065,  1068,  1068,  1076,  1076,  1084,  1084,  1095,  1096,
    1099,  1100,  1101,  1102,  1103,  1104,  1107,  1112,  1117,  1122,
    1127,  1132,  1140,  1140,  1153,  1154,  1157,  1158,  1165,  1165,
    1191,  1191,  1202,  1203,  1207,  1208,  1209,  1210,  1211,  1212,
    1213,  1214,  1215,  1216,  1217,  1218,  1219,  1220,  1221,  1222,
    1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1244,
    1244,  1252,  1252,  1260,  1260,  1268,  1268,  1276,  1276,  1286,
    1286,  1293,  1294,  1295,  1296,  1299,  1304,  1312,  1312,  1323,
    1324,  1328,  1329,  1332,  1332,  1340,  1341,  1344,  1345,  1346,
    1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,  1365,  1366,
    1367,  1368,  1369,  1370,  1371,  1372,  1373,  1374,  1375,  1382,
    1382,  1395,  1395,  1404,  1405,  1408,  1409,  1414,  1414,  1429,
    1429,  1443,  1444,  1447,  1448,  1451,  1452,  1453,  1454,  1455,
    1456,  1457,  1458,  1459,  1460,  1463,  1465,  1470,  1472,  1472,
    1480,  1480,  1488,  1488,  1496,  1498,  1498,  1506,  1515,  1515,
    1527,  1528,  1533,  1534,  1539,  1539,  1551,  1551,  1563,  1564,
    1569,  1570,  1575,  1576,  1577,  1578,  1579,  1580,  1581,  1582,
    1583,  1586,  1588,  1588,  1596,  1598,  1600,  1605,  1613,  1613,
    1625,  1626,  1629,  1630,  1633,  1633,  1643,  1643,  1652,  1653,
    1656,  1657,  1658,  1659,  1660,  1661,  1662,  1665,  1665,  1673,
    1673,  1698,  1698,  1728,  1728,  1740,  1741,  1744,  1745,  1748,
    1748,  1760,  1760,  1772,  1773,  1776,  1777,  1778,  1779,  1780,
    1781,  1782,  1783,  1784,  1785,  1786,  1789,  1789,  1797,  1802,
    1802,  1810,  1815,  1823,  1823,  1833,  1834,  1837,  1838,  1841,
    1841,  1850,  1850,  1859,  1860,  1863,  1864,  1868,  1869,  1870,
    1871,  1872,  1873,  1874,  1875,  1876,  1877,  1878,  1881,  1881,
    1891,  1891,  1901,  1901,  1909,  1909,  1917,  1917,  1925,  1925,
    1933,  1933,  1946,  1946,  1956,  1957,  1960,  1960,  1971,  1971,
    1981,  1982,  1985,  1985,  1995,  1996,  1999,  2000,  2003,  2004,
    2005,  2006,  2007,  2008,  2009,  2012,  2014,  2014,  2022,  2030,
    2030,  2042,  2043,  2046,  2047,  2048,  2049,  2050,  2051,  2052,
    2053,  2054,  2057,  2057,  2064,  2065,  2066,  2069,  2074,  2074,
    2082,  2087,  2094,  2101,  2101,  2111,  2112,  2115,  2116,  2117,
    2118,  2119,  2122,  2122,  2130,  2130,  2140,  2140,  2152,  2153,
    2156,  2157,  2158,  2159,  2160,  2161,  2164,  2169,  2169,  2177,
    2182,  2182,  2191,  2191,  2203,  2203,  2213,  2214,  2217,  2218,
    2219,  2220,  2221,  2222,  2223,  2224,  2225,  2226,  2227,  2228,
    2229,  2230,  2231,  2232,  2233,  2234,  2237,  2242,  2242,  2250,
    2250,  2258,  2263,  2263,  2271,  2276,  2281,  2281,  2289,  2290,
    2293,  2293,  2302,  2308,  2314,  2314,  2322,  2322,  2331,  2331,
    2340,  2340,  2350,  2350,  2357,  2357,  2364,  2364,  2373,  2373,
    2384,  2384,  2394,  2395,  2399,  2400,  2403,  2403,  2413,  2423,
    2423,  2433,  2433,  2444,  2445,  2449,  2453,  2453,  2465,  2466,
    2470,  2470,  2478,  2479,  2482,  2483,  2484,  2485,  2486,  2487,
    2488,  2491,  2496,  2496,  2504,  2504,  2514,  2515,  2518,  2518,
    2526,  2527,  2530,  2531,  2532,  2533,  2534,  2537,  2537,  2545,
    2550,  2555,  2560,  2560
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


#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 5502 "dhcp6_parser.cc"

#line 2568 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
