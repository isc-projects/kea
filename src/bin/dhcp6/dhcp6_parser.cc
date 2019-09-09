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

#line 14 "dhcp6_parser.yy"
namespace isc { namespace dhcp {
#line 146 "dhcp6_parser.cc"


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
      case 205: // value
      case 209: // map_value
      case 271: // db_type
      case 365: // hr_mode
      case 501: // duid_type
      case 536: // ncr_protocol_value
      case 543: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 187: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 186: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 185: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 184: // "constant string"
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
      case 205: // value
      case 209: // map_value
      case 271: // db_type
      case 365: // hr_mode
      case 501: // duid_type
      case 536: // ncr_protocol_value
      case 543: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 187: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 186: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 185: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 184: // "constant string"
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
      case 205: // value
      case 209: // map_value
      case 271: // db_type
      case 365: // hr_mode
      case 501: // duid_type
      case 536: // ncr_protocol_value
      case 543: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 187: // "boolean"
        value.move< bool > (that.value);
        break;

      case 186: // "floating point"
        value.move< double > (that.value);
        break;

      case 185: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 184: // "constant string"
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
      case 184: // "constant string"
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 405 "dhcp6_parser.cc"
        break;

      case 185: // "integer"
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 411 "dhcp6_parser.cc"
        break;

      case 186: // "floating point"
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case 187: // "boolean"
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case 205: // value
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case 209: // map_value
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case 271: // db_type
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case 365: // hr_mode
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case 501: // duid_type
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case 536: // ncr_protocol_value
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case 543: // replace_client_name_value
#line 263 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
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
      case 205: // value
      case 209: // map_value
      case 271: // db_type
      case 365: // hr_mode
      case 501: // duid_type
      case 536: // ncr_protocol_value
      case 543: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 187: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 186: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 185: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 184: // "constant string"
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
#line 272 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 731 "dhcp6_parser.cc"
    break;

  case 4:
#line 273 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 737 "dhcp6_parser.cc"
    break;

  case 6:
#line 274 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 743 "dhcp6_parser.cc"
    break;

  case 8:
#line 275 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 749 "dhcp6_parser.cc"
    break;

  case 10:
#line 276 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.SUBNET6; }
#line 755 "dhcp6_parser.cc"
    break;

  case 12:
#line 277 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 761 "dhcp6_parser.cc"
    break;

  case 14:
#line 278 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 767 "dhcp6_parser.cc"
    break;

  case 16:
#line 279 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 773 "dhcp6_parser.cc"
    break;

  case 18:
#line 280 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 779 "dhcp6_parser.cc"
    break;

  case 20:
#line 281 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 785 "dhcp6_parser.cc"
    break;

  case 22:
#line 282 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 791 "dhcp6_parser.cc"
    break;

  case 24:
#line 283 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 797 "dhcp6_parser.cc"
    break;

  case 26:
#line 284 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 803 "dhcp6_parser.cc"
    break;

  case 28:
#line 285 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 809 "dhcp6_parser.cc"
    break;

  case 30:
#line 286 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 815 "dhcp6_parser.cc"
    break;

  case 32:
#line 294 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 821 "dhcp6_parser.cc"
    break;

  case 33:
#line 295 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 827 "dhcp6_parser.cc"
    break;

  case 34:
#line 296 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 833 "dhcp6_parser.cc"
    break;

  case 35:
#line 297 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp6_parser.cc"
    break;

  case 36:
#line 298 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp6_parser.cc"
    break;

  case 37:
#line 299 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 851 "dhcp6_parser.cc"
    break;

  case 38:
#line 300 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 857 "dhcp6_parser.cc"
    break;

  case 39:
#line 303 "dhcp6_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 866 "dhcp6_parser.cc"
    break;

  case 40:
#line 308 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 877 "dhcp6_parser.cc"
    break;

  case 41:
#line 313 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 887 "dhcp6_parser.cc"
    break;

  case 42:
#line 319 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 893 "dhcp6_parser.cc"
    break;

  case 45:
#line 326 "dhcp6_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 902 "dhcp6_parser.cc"
    break;

  case 46:
#line 330 "dhcp6_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 912 "dhcp6_parser.cc"
    break;

  case 47:
#line 337 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 921 "dhcp6_parser.cc"
    break;

  case 48:
#line 340 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 929 "dhcp6_parser.cc"
    break;

  case 51:
#line 348 "dhcp6_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 938 "dhcp6_parser.cc"
    break;

  case 52:
#line 352 "dhcp6_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp6_parser.cc"
    break;

  case 53:
#line 359 "dhcp6_parser.yy"
    {
    // List parsing about to start
}
#line 955 "dhcp6_parser.cc"
    break;

  case 54:
#line 361 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 964 "dhcp6_parser.cc"
    break;

  case 57:
#line 370 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 973 "dhcp6_parser.cc"
    break;

  case 58:
#line 374 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp6_parser.cc"
    break;

  case 59:
#line 385 "dhcp6_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 993 "dhcp6_parser.cc"
    break;

  case 60:
#line 395 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1004 "dhcp6_parser.cc"
    break;

  case 61:
#line 400 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1017 "dhcp6_parser.cc"
    break;

  case 70:
#line 423 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1030 "dhcp6_parser.cc"
    break;

  case 71:
#line 430 "dhcp6_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1040 "dhcp6_parser.cc"
    break;

  case 72:
#line 438 "dhcp6_parser.yy"
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1050 "dhcp6_parser.cc"
    break;

  case 73:
#line 442 "dhcp6_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 120:
#line 499 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 121:
#line 501 "dhcp6_parser.yy"
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc"
    break;

  case 122:
#line 507 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1086 "dhcp6_parser.cc"
    break;

  case 123:
#line 512 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1095 "dhcp6_parser.cc"
    break;

  case 124:
#line 517 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 125:
#line 522 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1113 "dhcp6_parser.cc"
    break;

  case 126:
#line 527 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1122 "dhcp6_parser.cc"
    break;

  case 127:
#line 532 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1131 "dhcp6_parser.cc"
    break;

  case 128:
#line 537 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1140 "dhcp6_parser.cc"
    break;

  case 129:
#line 542 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1149 "dhcp6_parser.cc"
    break;

  case 130:
#line 547 "dhcp6_parser.yy"
    {
    ElementPtr asl(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-static-leases", asl);
}
#line 1158 "dhcp6_parser.cc"
    break;

  case 131:
#line 552 "dhcp6_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1167 "dhcp6_parser.cc"
    break;

  case 132:
#line 557 "dhcp6_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1176 "dhcp6_parser.cc"
    break;

  case 133:
#line 562 "dhcp6_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 134:
#line 567 "dhcp6_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1194 "dhcp6_parser.cc"
    break;

  case 135:
#line 572 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1202 "dhcp6_parser.cc"
    break;

  case 136:
#line 574 "dhcp6_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1212 "dhcp6_parser.cc"
    break;

  case 137:
#line 580 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1223 "dhcp6_parser.cc"
    break;

  case 138:
#line 585 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 139:
#line 591 "dhcp6_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 140:
#line 595 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1252 "dhcp6_parser.cc"
    break;

  case 148:
#line 611 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 149:
#line 616 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 150:
#line 621 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 151:
#line 627 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 152:
#line 632 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 153:
#line 639 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 154:
#line 644 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1325 "dhcp6_parser.cc"
    break;

  case 155:
#line 651 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1336 "dhcp6_parser.cc"
    break;

  case 156:
#line 656 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1345 "dhcp6_parser.cc"
    break;

  case 161:
#line 669 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1355 "dhcp6_parser.cc"
    break;

  case 162:
#line 673 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1365 "dhcp6_parser.cc"
    break;

  case 186:
#line 706 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 187:
#line 708 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc"
    break;

  case 188:
#line 713 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1388 "dhcp6_parser.cc"
    break;

  case 189:
#line 714 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1394 "dhcp6_parser.cc"
    break;

  case 190:
#line 715 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1400 "dhcp6_parser.cc"
    break;

  case 191:
#line 716 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1406 "dhcp6_parser.cc"
    break;

  case 192:
#line 719 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp6_parser.cc"
    break;

  case 193:
#line 721 "dhcp6_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1424 "dhcp6_parser.cc"
    break;

  case 194:
#line 727 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp6_parser.cc"
    break;

  case 195:
#line 729 "dhcp6_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1442 "dhcp6_parser.cc"
    break;

  case 196:
#line 735 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 197:
#line 737 "dhcp6_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 198:
#line 743 "dhcp6_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1469 "dhcp6_parser.cc"
    break;

  case 199:
#line 748 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1477 "dhcp6_parser.cc"
    break;

  case 200:
#line 750 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1487 "dhcp6_parser.cc"
    break;

  case 201:
#line 756 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1496 "dhcp6_parser.cc"
    break;

  case 202:
#line 761 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1505 "dhcp6_parser.cc"
    break;

  case 203:
#line 766 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1514 "dhcp6_parser.cc"
    break;

  case 204:
#line 771 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1523 "dhcp6_parser.cc"
    break;

  case 205:
#line 776 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 206:
#line 781 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 207:
#line 786 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 208:
#line 791 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1559 "dhcp6_parser.cc"
    break;

  case 209:
#line 796 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1568 "dhcp6_parser.cc"
    break;

  case 210:
#line 801 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1576 "dhcp6_parser.cc"
    break;

  case 211:
#line 803 "dhcp6_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1586 "dhcp6_parser.cc"
    break;

  case 212:
#line 809 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1595 "dhcp6_parser.cc"
    break;

  case 213:
#line 814 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc"
    break;

  case 214:
#line 816 "dhcp6_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc"
    break;

  case 215:
#line 822 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 216:
#line 824 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 217:
#line 830 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 218:
#line 832 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1649 "dhcp6_parser.cc"
    break;

  case 219:
#line 838 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 220:
#line 843 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1669 "dhcp6_parser.cc"
    break;

  case 224:
#line 853 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 225:
#line 855 "dhcp6_parser.yy"
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
#line 1697 "dhcp6_parser.cc"
    break;

  case 226:
#line 871 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 227:
#line 876 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1717 "dhcp6_parser.cc"
    break;

  case 232:
#line 889 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 233:
#line 894 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1735 "dhcp6_parser.cc"
    break;

  case 234:
#line 899 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 235:
#line 904 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 241:
#line 918 "dhcp6_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 242:
#line 923 "dhcp6_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1773 "dhcp6_parser.cc"
    break;

  case 243:
#line 930 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1784 "dhcp6_parser.cc"
    break;

  case 244:
#line 935 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1793 "dhcp6_parser.cc"
    break;

  case 245:
#line 940 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1804 "dhcp6_parser.cc"
    break;

  case 246:
#line 945 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1813 "dhcp6_parser.cc"
    break;

  case 251:
#line 958 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 252:
#line 962 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1833 "dhcp6_parser.cc"
    break;

  case 253:
#line 968 "dhcp6_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1843 "dhcp6_parser.cc"
    break;

  case 254:
#line 972 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 260:
#line 987 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc"
    break;

  case 261:
#line 989 "dhcp6_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1871 "dhcp6_parser.cc"
    break;

  case 262:
#line 995 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp6_parser.cc"
    break;

  case 263:
#line 997 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1888 "dhcp6_parser.cc"
    break;

  case 264:
#line 1003 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1899 "dhcp6_parser.cc"
    break;

  case 265:
#line 1008 "dhcp6_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 274:
#line 1026 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 275:
#line 1031 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1927 "dhcp6_parser.cc"
    break;

  case 276:
#line 1036 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 277:
#line 1041 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1945 "dhcp6_parser.cc"
    break;

  case 278:
#line 1046 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 279:
#line 1051 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 280:
#line 1059 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1974 "dhcp6_parser.cc"
    break;

  case 281:
#line 1064 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 286:
#line 1084 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1993 "dhcp6_parser.cc"
    break;

  case 287:
#line 1088 "dhcp6_parser.yy"
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
#line 2019 "dhcp6_parser.cc"
    break;

  case 288:
#line 1110 "dhcp6_parser.yy"
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 289:
#line 1114 "dhcp6_parser.yy"
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2039 "dhcp6_parser.cc"
    break;

  case 320:
#line 1156 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 321:
#line 1158 "dhcp6_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 322:
#line 1164 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 323:
#line 1166 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 324:
#line 1172 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 325:
#line 1174 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 326:
#line 1180 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2101 "dhcp6_parser.cc"
    break;

  case 327:
#line 1182 "dhcp6_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2111 "dhcp6_parser.cc"
    break;

  case 328:
#line 1188 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2122 "dhcp6_parser.cc"
    break;

  case 329:
#line 1193 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 330:
#line 1198 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2139 "dhcp6_parser.cc"
    break;

  case 331:
#line 1200 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2148 "dhcp6_parser.cc"
    break;

  case 332:
#line 1205 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2154 "dhcp6_parser.cc"
    break;

  case 333:
#line 1206 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2160 "dhcp6_parser.cc"
    break;

  case 334:
#line 1207 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2166 "dhcp6_parser.cc"
    break;

  case 335:
#line 1208 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2172 "dhcp6_parser.cc"
    break;

  case 336:
#line 1211 "dhcp6_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2181 "dhcp6_parser.cc"
    break;

  case 337:
#line 1216 "dhcp6_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2190 "dhcp6_parser.cc"
    break;

  case 338:
#line 1224 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 339:
#line 1229 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2210 "dhcp6_parser.cc"
    break;

  case 344:
#line 1244 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2220 "dhcp6_parser.cc"
    break;

  case 345:
#line 1248 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 373:
#line 1287 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 374:
#line 1292 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2248 "dhcp6_parser.cc"
    break;

  case 375:
#line 1300 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 376:
#line 1303 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 2265 "dhcp6_parser.cc"
    break;

  case 381:
#line 1319 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2275 "dhcp6_parser.cc"
    break;

  case 382:
#line 1323 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2287 "dhcp6_parser.cc"
    break;

  case 383:
#line 1334 "dhcp6_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2297 "dhcp6_parser.cc"
    break;

  case 384:
#line 1338 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2309 "dhcp6_parser.cc"
    break;

  case 400:
#line 1370 "dhcp6_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 402:
#line 1377 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc"
    break;

  case 403:
#line 1379 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 404:
#line 1385 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 405:
#line 1387 "dhcp6_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2354 "dhcp6_parser.cc"
    break;

  case 406:
#line 1393 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 407:
#line 1395 "dhcp6_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 409:
#line 1403 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2380 "dhcp6_parser.cc"
    break;

  case 410:
#line 1405 "dhcp6_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2390 "dhcp6_parser.cc"
    break;

  case 411:
#line 1411 "dhcp6_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2399 "dhcp6_parser.cc"
    break;

  case 412:
#line 1420 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2410 "dhcp6_parser.cc"
    break;

  case 413:
#line 1425 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2419 "dhcp6_parser.cc"
    break;

  case 418:
#line 1444 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2429 "dhcp6_parser.cc"
    break;

  case 419:
#line 1448 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2438 "dhcp6_parser.cc"
    break;

  case 420:
#line 1456 "dhcp6_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 421:
#line 1460 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2457 "dhcp6_parser.cc"
    break;

  case 436:
#line 1493 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 437:
#line 1495 "dhcp6_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 440:
#line 1505 "dhcp6_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2484 "dhcp6_parser.cc"
    break;

  case 441:
#line 1510 "dhcp6_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2493 "dhcp6_parser.cc"
    break;

  case 442:
#line 1518 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2504 "dhcp6_parser.cc"
    break;

  case 443:
#line 1523 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc"
    break;

  case 448:
#line 1538 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2523 "dhcp6_parser.cc"
    break;

  case 449:
#line 1542 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2533 "dhcp6_parser.cc"
    break;

  case 450:
#line 1548 "dhcp6_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2543 "dhcp6_parser.cc"
    break;

  case 451:
#line 1552 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2552 "dhcp6_parser.cc"
    break;

  case 461:
#line 1570 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 462:
#line 1572 "dhcp6_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 463:
#line 1578 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2578 "dhcp6_parser.cc"
    break;

  case 464:
#line 1580 "dhcp6_parser.yy"
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
#line 2605 "dhcp6_parser.cc"
    break;

  case 465:
#line 1603 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2613 "dhcp6_parser.cc"
    break;

  case 466:
#line 1605 "dhcp6_parser.yy"
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
#line 2642 "dhcp6_parser.cc"
    break;

  case 467:
#line 1633 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 468:
#line 1638 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2662 "dhcp6_parser.cc"
    break;

  case 473:
#line 1653 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2672 "dhcp6_parser.cc"
    break;

  case 474:
#line 1657 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2684 "dhcp6_parser.cc"
    break;

  case 475:
#line 1665 "dhcp6_parser.yy"
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 476:
#line 1669 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2706 "dhcp6_parser.cc"
    break;

  case 490:
#line 1694 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp6_parser.cc"
    break;

  case 491:
#line 1696 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc"
    break;

  case 492:
#line 1702 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2733 "dhcp6_parser.cc"
    break;

  case 493:
#line 1707 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 494:
#line 1709 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 495:
#line 1715 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2760 "dhcp6_parser.cc"
    break;

  case 496:
#line 1720 "dhcp6_parser.yy"
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2769 "dhcp6_parser.cc"
    break;

  case 497:
#line 1728 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2780 "dhcp6_parser.cc"
    break;

  case 498:
#line 1733 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc"
    break;

  case 503:
#line 1746 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2799 "dhcp6_parser.cc"
    break;

  case 504:
#line 1750 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2808 "dhcp6_parser.cc"
    break;

  case 505:
#line 1755 "dhcp6_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2818 "dhcp6_parser.cc"
    break;

  case 506:
#line 1759 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2827 "dhcp6_parser.cc"
    break;

  case 522:
#line 1786 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 523:
#line 1791 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2847 "dhcp6_parser.cc"
    break;

  case 524:
#line 1796 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 525:
#line 1801 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 526:
#line 1806 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 527:
#line 1808 "dhcp6_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 528:
#line 1814 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 529:
#line 1816 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 530:
#line 1822 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 531:
#line 1824 "dhcp6_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 532:
#line 1830 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2929 "dhcp6_parser.cc"
    break;

  case 533:
#line 1832 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2939 "dhcp6_parser.cc"
    break;

  case 534:
#line 1838 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2950 "dhcp6_parser.cc"
    break;

  case 535:
#line 1843 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2959 "dhcp6_parser.cc"
    break;

  case 536:
#line 1851 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2970 "dhcp6_parser.cc"
    break;

  case 537:
#line 1856 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2979 "dhcp6_parser.cc"
    break;

  case 540:
#line 1865 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp6_parser.cc"
    break;

  case 541:
#line 1867 "dhcp6_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2997 "dhcp6_parser.cc"
    break;

  case 542:
#line 1876 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3008 "dhcp6_parser.cc"
    break;

  case 543:
#line 1881 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 546:
#line 1890 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 547:
#line 1894 "dhcp6_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 560:
#line 1919 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 561:
#line 1921 "dhcp6_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 562:
#line 1927 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 563:
#line 1935 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3075 "dhcp6_parser.cc"
    break;

  case 564:
#line 1940 "dhcp6_parser.yy"
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp6_parser.cc"
    break;

  case 576:
#line 1962 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3094 "dhcp6_parser.cc"
    break;

  case 577:
#line 1964 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3103 "dhcp6_parser.cc"
    break;

  case 578:
#line 1969 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3109 "dhcp6_parser.cc"
    break;

  case 579:
#line 1970 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3115 "dhcp6_parser.cc"
    break;

  case 580:
#line 1971 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3121 "dhcp6_parser.cc"
    break;

  case 581:
#line 1974 "dhcp6_parser.yy"
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 582:
#line 1979 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp6_parser.cc"
    break;

  case 583:
#line 1981 "dhcp6_parser.yy"
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3148 "dhcp6_parser.cc"
    break;

  case 584:
#line 1987 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 585:
#line 1992 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3166 "dhcp6_parser.cc"
    break;

  case 586:
#line 1999 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3175 "dhcp6_parser.cc"
    break;

  case 587:
#line 2006 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3186 "dhcp6_parser.cc"
    break;

  case 588:
#line 2011 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 596:
#line 2027 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp6_parser.cc"
    break;

  case 597:
#line 2029 "dhcp6_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3213 "dhcp6_parser.cc"
    break;

  case 598:
#line 2035 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 599:
#line 2037 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 600:
#line 2045 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 601:
#line 2047 "dhcp6_parser.yy"
    {
    ElementPtr qc = yystack_[0].value.as < ElementPtr > ();
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
#line 3279 "dhcp6_parser.cc"
    break;

  case 602:
#line 2085 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3290 "dhcp6_parser.cc"
    break;

  case 603:
#line 2090 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3301 "dhcp6_parser.cc"
    break;

  case 604:
#line 2097 "dhcp6_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3311 "dhcp6_parser.cc"
    break;

  case 605:
#line 2101 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3321 "dhcp6_parser.cc"
    break;

  case 626:
#line 2131 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3330 "dhcp6_parser.cc"
    break;

  case 627:
#line 2136 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 628:
#line 2138 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 629:
#line 2144 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3356 "dhcp6_parser.cc"
    break;

  case 630:
#line 2146 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 631:
#line 2152 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3375 "dhcp6_parser.cc"
    break;

  case 632:
#line 2157 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3383 "dhcp6_parser.cc"
    break;

  case 633:
#line 2159 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 634:
#line 2165 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3402 "dhcp6_parser.cc"
    break;

  case 635:
#line 2170 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3411 "dhcp6_parser.cc"
    break;

  case 636:
#line 2175 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3419 "dhcp6_parser.cc"
    break;

  case 637:
#line 2177 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 638:
#line 2183 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3434 "dhcp6_parser.cc"
    break;

  case 639:
#line 2184 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3440 "dhcp6_parser.cc"
    break;

  case 640:
#line 2187 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 641:
#line 2189 "dhcp6_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 642:
#line 2195 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 643:
#line 2200 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 644:
#line 2205 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 645:
#line 2207 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3493 "dhcp6_parser.cc"
    break;

  case 646:
#line 2213 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3501 "dhcp6_parser.cc"
    break;

  case 647:
#line 2216 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3509 "dhcp6_parser.cc"
    break;

  case 648:
#line 2219 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3517 "dhcp6_parser.cc"
    break;

  case 649:
#line 2222 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3525 "dhcp6_parser.cc"
    break;

  case 650:
#line 2225 "dhcp6_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3534 "dhcp6_parser.cc"
    break;

  case 651:
#line 2231 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 652:
#line 2233 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 653:
#line 2239 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 654:
#line 2241 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 655:
#line 2247 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 656:
#line 2249 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3588 "dhcp6_parser.cc"
    break;

  case 657:
#line 2257 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 658:
#line 2259 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3605 "dhcp6_parser.cc"
    break;

  case 659:
#line 2264 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 660:
#line 2266 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3622 "dhcp6_parser.cc"
    break;

  case 661:
#line 2271 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 662:
#line 2273 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 663:
#line 2280 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3650 "dhcp6_parser.cc"
    break;

  case 664:
#line 2285 "dhcp6_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3660 "dhcp6_parser.cc"
    break;

  case 665:
#line 2291 "dhcp6_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3670 "dhcp6_parser.cc"
    break;

  case 666:
#line 2295 "dhcp6_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3679 "dhcp6_parser.cc"
    break;

  case 671:
#line 2310 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 672:
#line 2315 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 673:
#line 2320 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 674:
#line 2330 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3719 "dhcp6_parser.cc"
    break;

  case 675:
#line 2335 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 676:
#line 2340 "dhcp6_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3738 "dhcp6_parser.cc"
    break;

  case 677:
#line 2344 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 681:
#line 2360 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 682:
#line 2365 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 685:
#line 2377 "dhcp6_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 686:
#line 2381 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 696:
#line 2398 "dhcp6_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 697:
#line 2403 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3801 "dhcp6_parser.cc"
    break;

  case 698:
#line 2405 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3811 "dhcp6_parser.cc"
    break;

  case 699:
#line 2411 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3822 "dhcp6_parser.cc"
    break;

  case 700:
#line 2416 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 703:
#line 2425 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3841 "dhcp6_parser.cc"
    break;

  case 704:
#line 2429 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3849 "dhcp6_parser.cc"
    break;

  case 712:
#line 2444 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3857 "dhcp6_parser.cc"
    break;

  case 713:
#line 2446 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 714:
#line 2452 "dhcp6_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 715:
#line 2457 "dhcp6_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3885 "dhcp6_parser.cc"
    break;

  case 716:
#line 2462 "dhcp6_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3894 "dhcp6_parser.cc"
    break;

  case 717:
#line 2467 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 718:
#line 2469 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3912 "dhcp6_parser.cc"
    break;


#line 3916 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -878;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     500,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,    58,    70,    89,    97,
     112,   116,   127,   169,   184,   199,   233,   245,   254,   273,
     276,   277,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,    70,     5,    30,   109,    27,   441,   270,   172,
     258,   272,    69,   213,   -12,   513,   133,    32,  -878,   326,
     341,   351,   358,   356,  -878,  -878,  -878,  -878,  -878,   365,
    -878,    73,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   367,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   381,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   382,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,    75,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   385,  -878,
      83,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   386,   387,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,    85,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   132,  -878,  -878,  -878,  -878,  -878,   388,  -878,   391,
     397,  -878,  -878,  -878,  -878,  -878,  -878,   182,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   394,   403,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   399,  -878,  -878,   405,  -878,
    -878,  -878,   407,  -878,  -878,   408,   410,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     417,   419,  -878,  -878,  -878,  -878,   418,   425,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     201,  -878,  -878,  -878,   426,  -878,  -878,   427,  -878,   429,
     430,  -878,  -878,   439,   442,  -878,  -878,  -878,  -878,  -878,
     204,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   205,  -878,  -878,
    -878,   443,   227,  -878,  -878,  -878,  -878,    70,    70,  -878,
     261,   444,   447,   449,   451,   458,  -878,    30,  -878,   462,
     466,   467,   470,   471,   473,   293,   295,   296,   298,   299,
     312,   313,   314,   315,   320,   322,   323,   321,   496,   499,
     501,   506,   508,   510,   511,   512,   514,   523,   524,   525,
     526,   528,   529,   530,   535,   346,   536,   539,   540,   541,
     542,   543,   109,  -878,   544,   330,    27,  -878,   546,   547,
     548,   549,   550,   380,   368,   552,   553,   554,   441,  -878,
     555,   270,  -878,   556,   383,   557,   398,   401,   172,  -878,
     559,   560,   562,   563,   566,   580,   585,  -878,   258,  -878,
     592,   595,   415,   597,   598,   599,   420,  -878,    69,   600,
     423,   432,  -878,   213,   609,   613,   147,  -878,   434,   618,
     619,   445,   624,   446,   448,   625,   628,   450,   454,   630,
     632,   513,  -878,   133,  -878,   634,   459,    32,  -878,  -878,
    -878,   639,   497,   638,    70,    70,    70,  -878,   476,   654,
     655,   656,   657,   660,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   482,   679,   680,
     681,   682,   503,    23,   683,   685,   686,   687,   688,   689,
     691,   693,   692,   694,  -878,   695,   682,   696,   509,   516,
     699,  -878,   700,  -878,  -878,   701,   702,   531,   532,   533,
    -878,  -878,   700,   534,   703,  -878,   537,  -878,   538,  -878,
     545,  -878,  -878,  -878,   700,   700,   700,   551,   558,   561,
     564,  -878,   565,   567,  -878,   568,   569,   570,  -878,  -878,
     571,  -878,  -878,  -878,   572,    70,  -878,  -878,   573,   574,
    -878,   575,  -878,  -878,    96,   576,  -878,  -878,   -37,   577,
    -878,  -878,   704,  -878,  -878,    70,   109,   133,  -878,  -878,
    -878,  -878,    32,    27,   268,   268,   705,  -878,   706,   707,
     712,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   713,
     -45,    70,    88,   629,   716,   719,   720,   198,   101,   -13,
    -878,   513,  -878,  -878,   721,  -878,  -878,   723,   724,  -878,
    -878,  -878,  -878,  -878,   -38,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   705,  -878,   231,
     257,   259,   265,  -878,  -878,  -878,  -878,   728,   729,   730,
     732,   733,  -878,   734,   735,  -878,  -878,  -878,   736,   737,
     739,   740,  -878,   278,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   279,  -878,   741,   743,  -878,
    -878,   744,   757,  -878,  -878,   756,   760,  -878,  -878,   758,
     762,  -878,  -878,   761,   763,  -878,  -878,  -878,    79,  -878,
    -878,  -878,   764,  -878,  -878,  -878,    91,  -878,  -878,  -878,
    -878,   316,  -878,  -878,  -878,   167,  -878,  -878,   765,   766,
    -878,  -878,   767,   769,  -878,   770,   771,   772,   773,   774,
     775,   317,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   776,   777,   778,  -878,  -878,  -878,  -878,   318,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     319,  -878,  -878,  -878,   325,  -878,   171,  -878,   584,  -878,
     779,   780,  -878,  -878,   781,   783,  -878,  -878,  -878,   782,
    -878,   785,  -878,  -878,  -878,  -878,   784,   788,   789,   790,
     604,   521,   610,   611,   612,   792,   614,   615,   797,   798,
     799,   620,   621,   617,   622,   268,  -878,  -878,   268,  -878,
     705,   441,  -878,   706,    69,  -878,   707,   213,  -878,   712,
     527,  -878,   713,   -45,  -878,  -878,    88,  -878,   804,   629,
    -878,    47,   716,  -878,   258,  -878,   719,   -12,  -878,   720,
     626,   627,   631,   633,   635,   636,   198,  -878,   805,   806,
     637,   640,   641,   101,  -878,   809,   810,   -13,  -878,  -878,
      -9,   721,  -878,  -878,   811,   812,   270,  -878,   723,   172,
    -878,   724,   815,  -878,  -878,   119,   644,   645,   648,  -878,
    -878,  -878,  -878,  -878,   650,  -878,  -878,   651,   653,   658,
    -878,  -878,  -878,  -878,  -878,   331,  -878,   332,  -878,   816,
    -878,   836,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   335,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,   661,  -878,  -878,   819,  -878,  -878,  -878,
    -878,  -878,   838,   846,  -878,  -878,  -878,  -878,  -878,   848,
    -878,   339,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
      94,   674,  -878,  -878,  -878,  -878,   675,   676,  -878,  -878,
     858,  -878,  -878,  -878,  -878,  -878,   342,  -878,  -878,  -878,
    -878,  -878,  -878,   718,   343,  -878,   349,  -878,   725,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   527,  -878,  -878,   863,   690,
    -878,    47,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   876,   722,   887,    -9,  -878,  -878,  -878,  -878,  -878,
    -878,   726,  -878,  -878,   907,  -878,   731,  -878,  -878,   916,
    -878,  -878,   230,  -878,    19,   916,  -878,  -878,   920,   922,
     928,  -878,   350,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     929,   747,   750,   751,   933,    19,  -878,   754,  -878,  -878,
    -878,   755,  -878,  -878,  -878
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   139,     9,
     288,    11,   450,    13,   475,    15,   505,    17,   375,    19,
     383,    21,   420,    23,   253,    25,   604,    27,   676,    29,
     665,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     507,     0,   385,   422,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   674,   657,   659,   661,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   120,   663,
     137,   151,   153,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   280,   373,
     412,   463,   465,   330,   338,   226,   243,   234,   219,   542,
     497,   245,   264,   563,     0,   587,   600,   602,   653,   655,
     681,   119,     0,    74,    76,    77,    78,    79,    80,    81,
      82,    83,    84,   118,   112,   113,   114,    85,   110,    88,
      89,    90,    91,   107,    92,    94,    93,    98,    99,    86,
     111,    87,    96,    97,   105,   106,   108,    95,   100,   101,
     102,   103,   104,   116,   117,   109,   115,   148,     0,   147,
       0,   141,   143,   144,   145,   146,   442,   467,   320,   322,
     324,     0,     0,   328,   326,   536,   319,   292,   293,   294,
     295,   296,   297,   298,   299,   318,   315,   316,   317,     0,
     290,   303,   304,   305,   308,   309,   311,   306,   307,   300,
     301,   313,   314,   302,   310,   312,   461,   460,   456,   457,
     455,     0,   452,   454,   458,   459,   490,     0,   493,     0,
       0,   489,   483,   484,   482,   487,   488,     0,   477,   479,
     480,   485,   486,   481,   534,   522,   524,   526,   528,   530,
     532,   521,   518,   519,   520,     0,   508,   509,   513,   514,
     511,   515,   516,   517,   512,     0,   402,   199,     0,   406,
     404,   409,     0,   398,   399,     0,   386,   387,   389,   401,
     390,   391,   392,   408,   393,   394,   395,   396,   397,   436,
       0,     0,   434,   435,   438,   439,     0,   423,   424,   426,
     427,   428,   429,   430,   431,   432,   433,   260,   262,   257,
       0,   255,   258,   259,     0,   627,   629,     0,   632,     0,
       0,   636,   640,     0,     0,   644,   651,   625,   623,   624,
       0,   606,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   620,   621,   622,     0,   678,   680,
     671,     0,     0,   667,   669,   670,    48,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    59,     0,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,     0,   451,     0,     0,     0,     0,     0,     0,   476,
       0,     0,     0,     0,     0,     0,     0,   506,     0,   376,
       0,     0,     0,     0,     0,     0,     0,   384,     0,     0,
       0,     0,   421,     0,     0,     0,     0,   254,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   605,     0,   677,     0,     0,     0,   666,    52,
      45,     0,     0,     0,     0,     0,     0,    63,     0,     0,
       0,     0,     0,     0,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   586,     0,     0,     0,     0,     0,
       0,    75,     0,   150,   142,     0,     0,     0,     0,     0,
     336,   337,     0,     0,     0,   291,     0,   453,     0,   492,
       0,   495,   496,   478,     0,     0,     0,     0,     0,     0,
       0,   510,     0,     0,   400,     0,     0,     0,   411,   388,
       0,   440,   441,   425,     0,     0,   256,   626,     0,     0,
     631,     0,   634,   635,     0,     0,   642,   643,     0,     0,
     607,   679,     0,   673,   668,     0,     0,     0,   658,   660,
     662,   121,     0,     0,     0,     0,   157,   136,   282,   377,
     414,    42,   464,   466,   332,   333,   334,   335,   331,   340,
       0,    49,     0,     0,     0,   499,   247,     0,     0,     0,
     601,     0,   654,   656,     0,    53,   149,   444,   469,   321,
     323,   325,   329,   327,     0,   462,   491,   494,   535,   523,
     525,   527,   529,   531,   533,   403,   200,   407,   405,   410,
     437,   261,   263,   628,   630,   633,   638,   639,   637,   641,
     646,   647,   648,   649,   650,   645,   652,   157,    46,     0,
       0,     0,     0,   186,   192,   194,   196,     0,     0,     0,
       0,     0,   210,     0,     0,   213,   215,   217,     0,     0,
       0,     0,   185,     0,   163,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   177,   184,   178,   179,   180,
     175,   176,   181,   182,   183,     0,   161,     0,   158,   159,
     286,     0,   283,   284,   381,     0,   378,   379,   418,     0,
     415,   416,   344,     0,   341,   342,   232,   233,     0,   228,
     230,   231,     0,   241,   242,   238,     0,   236,   239,   240,
     224,     0,   221,   223,   546,     0,   544,   503,     0,   500,
     501,   251,     0,   248,   249,     0,     0,     0,     0,     0,
       0,     0,   266,   268,   269,   270,   271,   272,   273,   576,
     582,     0,     0,     0,   575,   572,   573,   574,     0,   565,
     567,   570,   568,   569,   571,   596,   598,   595,   593,   594,
       0,   589,   591,   592,     0,   685,     0,   683,    55,   448,
       0,   445,   446,   473,     0,   470,   471,   540,   539,     0,
     538,     0,    71,   675,   664,   138,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   152,   154,     0,   156,
       0,     0,   281,     0,   385,   374,     0,   422,   413,     0,
       0,   339,     0,     0,   227,   244,     0,   235,     0,     0,
     220,   548,     0,   543,   507,   498,     0,     0,   246,     0,
       0,     0,     0,     0,     0,     0,     0,   265,     0,     0,
       0,     0,     0,     0,   564,     0,     0,     0,   588,   603,
       0,     0,   682,    57,     0,    56,     0,   443,     0,     0,
     468,     0,     0,   537,   672,     0,     0,     0,     0,   198,
     201,   202,   203,   204,     0,   212,   205,     0,     0,     0,
     207,   208,   209,   206,   164,     0,   160,     0,   285,     0,
     380,     0,   417,   372,   359,   360,   361,   363,   364,   365,
     352,   353,   371,   368,   369,   370,   348,   349,   350,   351,
     357,   358,   356,   362,     0,   346,   354,   366,   367,   355,
     343,   229,   237,     0,   222,   560,     0,   558,   559,   555,
     556,   557,     0,   549,   550,   552,   553,   554,   545,     0,
     502,     0,   250,   274,   275,   276,   277,   278,   279,   267,
       0,     0,   581,   584,   585,   566,     0,     0,   590,   699,
       0,   697,   695,   689,   693,   694,     0,   687,   691,   692,
     690,   684,    54,     0,     0,   447,     0,   472,     0,   188,
     189,   190,   191,   187,   193,   195,   197,   211,   214,   216,
     218,   162,   287,   382,   419,     0,   345,   225,     0,     0,
     547,     0,   504,   252,   578,   579,   580,   577,   583,   597,
     599,     0,     0,     0,     0,   686,    58,   449,   474,   541,
     347,     0,   562,   551,     0,   696,     0,   688,   561,     0,
     698,   703,     0,   701,     0,     0,   700,   712,     0,     0,
       0,   717,     0,   705,   707,   708,   709,   710,   711,   702,
       0,     0,     0,     0,     0,     0,   704,     0,   714,   715,
     716,     0,   706,   713,   718
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,    11,  -878,  -494,
    -878,   218,  -878,  -878,  -878,  -878,   280,  -878,  -493,  -878,
    -878,  -878,   -74,  -878,  -878,  -878,   578,  -878,  -878,  -878,
    -878,   304,   502,  -878,  -878,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,     3,     7,    10,    15,    18,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   300,   504,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   225,  -878,    46,  -878,  -627,
      52,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   -21,  -878,  -655,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,    33,  -878,  -878,  -878,  -878,  -878,
      36,  -646,  -878,  -878,  -878,  -878,    37,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,    26,  -878,  -878,  -878,    29,
     461,  -878,  -878,  -878,  -878,  -878,  -878,  -878,    22,  -878,
    -878,  -878,  -878,  -878,  -878,  -877,  -878,  -878,  -878,    56,
    -878,  -878,  -878,    59,   505,  -878,  -878,  -875,  -878,  -874,
    -878,   -11,  -878,    -5,  -878,    21,  -878,  -878,  -878,  -872,
    -878,  -878,  -878,  -878,    49,  -878,  -878,  -133,   883,  -878,
    -878,  -878,  -878,  -878,    60,  -878,  -878,  -878,    61,  -878,
     479,  -878,   -69,  -878,  -878,  -878,  -878,  -878,   -66,  -878,
    -878,  -878,  -878,  -878,   -58,  -878,  -878,  -878,    62,  -878,
    -878,  -878,    63,  -878,   475,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,    14,  -878,  -878,  -878,
      13,   515,  -878,  -878,   -53,  -878,   -29,  -878,  -878,  -878,
    -878,  -878,    12,  -878,  -878,  -878,    20,   517,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   -62,  -878,  -878,  -878,    48,
    -878,  -878,  -878,    53,  -878,   518,   294,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -871,  -878,  -878,  -878,  -878,  -878,  -878,  -878,    64,  -878,
    -878,  -878,  -121,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
      38,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,    35,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   324,   472,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   -73,  -878,
     -51,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   345,   474,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   347,   477,   -44,  -878,  -878,    41,  -878,  -878,  -126,
    -878,  -878,  -878,  -878,  -878,  -878,  -146,  -878,  -878,  -162,
    -878,  -878,  -878,  -878,  -878,  -878,  -878
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   652,    92,    93,    43,    72,    89,    90,   676,   858,
     954,   955,   742,    45,    74,   101,   102,   103,   391,    47,
      75,   152,   153,   154,   399,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   418,
     169,   401,    49,    76,   200,   201,   202,   444,   203,   170,
     402,   171,   403,   172,   404,   767,   768,   769,   898,   743,
     744,   745,   876,  1083,   746,   877,   747,   878,   748,   879,
     749,   750,   481,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,   885,   761,   762,   888,   763,   889,   764,
     890,   173,   429,   801,   802,   803,   918,   174,   426,   788,
     789,   790,   791,   175,   428,   796,   797,   798,   799,   176,
     427,   177,   432,   812,   813,   814,   927,    65,    84,   340,
     341,   342,   494,   343,   495,   178,   433,   821,   822,   823,
     824,   825,   826,   827,   828,   179,   419,   771,   772,   773,
     901,    51,    77,   229,   230,   231,   450,   232,   451,   233,
     452,   234,   456,   235,   455,   180,   424,   658,   237,   238,
     181,   425,   783,   784,   785,   910,  1014,  1015,   182,   420,
      59,    81,   775,   776,   777,   904,    61,    82,   305,   306,
     307,   308,   309,   310,   311,   480,   312,   484,   313,   483,
     314,   315,   485,   316,   183,   421,   779,   780,   781,   907,
      63,    83,   326,   327,   328,   329,   330,   489,   331,   332,
     333,   334,   240,   448,   860,   861,   862,   956,    53,    78,
     251,   252,   253,   460,   184,   422,   185,   423,   243,   449,
     864,   865,   866,   959,    55,    79,   267,   268,   269,   463,
     270,   271,   465,   272,   273,   186,   431,   808,   809,   810,
     924,    57,    80,   285,   286,   287,   288,   471,   289,   472,
     290,   473,   291,   474,   292,   475,   293,   476,   294,   470,
     245,   457,   869,   870,   962,   187,   430,   805,   806,   921,
    1032,  1033,  1034,  1035,  1036,  1098,  1037,   188,   434,   838,
     839,   840,   938,  1107,   841,   842,   939,   843,   844,   189,
     190,   436,   850,   851,   852,   945,   853,   946,   191,   437,
     192,   438,    67,    85,   360,   361,   362,   363,   499,   364,
     500,   365,   366,   502,   367,   368,   369,   505,   708,   370,
     506,   371,   372,   373,   509,   715,   374,   510,   193,   439,
     194,   440,   104,   393,   105,   394,   106,   395,   195,   400,
      71,    87,   382,   383,   384,   515,   385,   107,   392,    69,
      86,   377,   378,   196,   441,   856,   857,   950,  1066,  1067,
    1068,  1069,  1113,  1070,  1111,  1132,  1133,  1134,  1142,  1143,
    1144,  1150,  1145,  1146,  1147,  1148,  1154
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   151,   199,   216,   247,   261,   281,   217,   303,   322,
     339,   357,   375,   835,   324,   244,   795,   325,   765,   239,
     250,   264,   282,   204,   241,   254,   265,   283,    40,   317,
     335,   218,   358,  1007,   376,  1008,  1009,   219,  1013,  1019,
      94,   220,   379,   197,   198,   380,   381,   205,   242,   255,
     266,   284,   297,   318,   336,   221,   359,   651,    32,   786,
     222,   304,   323,   223,   275,   131,   132,   248,   262,   131,
     132,   867,   651,   249,   263,    33,   397,    34,   442,    35,
     224,   398,   913,   443,   225,   914,   446,   226,   458,   682,
     296,   447,   227,   459,   916,   228,    44,   917,   236,   337,
     338,   688,   689,   690,    46,   131,   132,   130,   297,   654,
     655,   656,   657,   710,   711,   712,   713,   845,   846,    48,
     108,   109,   829,    50,   110,   131,   132,   111,   112,   113,
     297,   728,   298,   299,    52,   461,   300,   301,   302,   787,
     462,  1079,  1080,  1081,  1082,  1025,  1026,   131,   132,  1059,
     714,  1060,  1061,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     922,    99,    99,   923,   951,    99,    54,   952,  1137,   131,
     132,  1138,  1139,  1140,  1141,   468,    95,   131,   132,    91,
     469,    56,   786,   793,   133,   794,    96,    97,    98,   134,
     135,   136,   137,   138,   496,   139,    58,   511,   513,   497,
     140,    99,   512,   514,    99,  1104,  1105,  1106,  1007,   141,
    1008,  1009,   142,  1013,  1019,   830,   831,   832,   833,   143,
     517,    99,   130,  1135,   442,   518,  1136,   144,   145,   872,
      60,   146,   147,   706,   707,   256,   257,   258,   259,   260,
     131,   132,    62,    99,    36,    37,    38,    39,   337,   338,
     513,    64,   517,   148,   149,   873,   150,   874,   446,   213,
     795,   985,   214,   875,   297,   319,   298,   299,   320,   321,
      66,   895,   895,    68,    70,    99,   896,   897,   835,   723,
     150,   131,   132,    99,   724,   725,   726,   727,   728,   729,
     730,   731,   732,   733,   734,   735,   736,   737,   738,   739,
     740,   741,   815,   816,   817,   818,   819,   820,   130,   919,
     936,   943,   947,   100,   920,   937,   944,   948,   511,   297,
     130,   129,   386,   949,   895,   458,   131,   132,  1095,  1091,
    1092,   246,   496,  1096,   387,  1114,   461,  1103,   131,   132,
    1115,  1117,   468,  1155,   274,   388,    99,  1118,  1156,   390,
     275,   276,   277,   278,   279,   280,   389,   213,   151,   396,
     214,   405,   199,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   216,   417,   435,   247,   217,   445,
     453,   454,   464,   204,   261,   466,   244,    99,   519,   520,
     239,   467,   477,   250,   281,   241,   478,   479,   254,   482,
     264,   486,   218,   488,   303,   265,   487,   205,   219,   322,
     282,   490,   220,   491,   324,   283,   492,   325,   493,   242,
     498,   501,   255,   503,   504,   317,   221,   357,   375,   266,
     335,   222,    99,   507,   223,   521,   508,   516,   522,   284,
     248,   523,    99,   524,    99,   525,   249,   262,   358,   318,
     376,   224,   526,   263,   336,   225,   528,   304,   226,   379,
     529,   530,   323,   227,   531,   532,   228,   533,   534,   236,
     535,   536,   359,   537,   538,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   539,   540,   541,
     547,   130,   542,   548,   636,   549,   546,   543,   544,   545,
     550,   206,   551,   207,   552,   553,   554,   573,   555,   131,
     132,   208,   209,   210,   211,   212,   133,   556,   557,   558,
     559,   564,   560,   561,   562,   638,   639,   640,   213,   563,
     565,   214,   140,   566,   567,   568,   569,   570,   572,   215,
     575,   576,   577,   578,   579,   581,   582,   583,   584,   586,
     588,   590,   151,   594,   595,   580,   596,   597,   589,   199,
     598,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   591,   599,   128,   592,   130,   297,   600,
     204,   131,   132,   379,   834,   847,   602,   357,   375,   603,
     604,   605,   606,   607,   610,   131,   132,   608,   209,   210,
     611,   212,   133,   614,   205,   836,   848,   615,   358,   612,
     376,   617,   618,   619,   213,    99,   702,   214,   621,   624,
     620,   622,   625,   623,   628,   215,   629,   626,   632,   837,
     849,   627,   359,   635,   633,   637,   718,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     641,   642,   643,   644,   645,   646,   647,   148,   149,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   648,   649,   650,   653,   659,    34,
     660,   661,   662,   672,   664,   663,   665,    99,   666,   667,
     673,   668,   669,   671,   674,   675,   677,   678,   970,   717,
     684,    99,   766,   770,   774,   679,   680,   681,   683,   778,
     782,   685,   686,   804,   800,   709,   807,   811,   855,   687,
     859,   863,   880,   881,   882,   691,   883,   884,   886,   887,
     891,   892,   692,   893,   894,   693,   900,   899,   694,   695,
     902,   696,   697,   698,   699,   700,   701,   703,   704,   705,
     903,   716,   905,   906,   908,   909,   912,   911,   953,   926,
     915,   925,   929,   928,   930,   931,   932,   933,   934,   935,
     940,   941,   942,   958,   670,   957,   961,   960,   965,   969,
     963,   964,   966,   967,   968,   971,   974,   973,   972,   975,
     976,   977,   978,   979,   982,   980,   981,   983,  1023,  1050,
    1051,  1043,  1044,  1056,  1057,  1073,  1045,  1072,  1046,  1078,
    1047,  1048,  1052,  1099,  1093,  1053,  1054,   216,  1084,  1085,
     303,   217,  1086,   322,  1087,  1088,   993,  1089,   324,   244,
     994,   325,  1090,   239,  1094,  1097,  1100,  1027,   241,  1101,
     281,   317,  1016,   339,   335,   218,  1102,  1017,  1108,  1109,
    1110,   219,  1112,  1029,   995,   220,   282,  1121,  1030,   834,
     996,   283,   242,   847,   997,   318,  1062,  1122,   336,   221,
    1124,  1018,   247,   304,   222,   261,   323,   223,   998,  1006,
     836,  1126,  1031,   999,   848,   284,  1000,  1064,   250,  1010,
    1028,   264,  1116,   254,   224,  1011,   265,  1125,   225,  1119,
    1128,   226,  1129,  1001,   837,  1130,   227,  1002,   849,   228,
    1003,  1065,   236,  1131,  1151,  1004,  1152,   255,  1005,  1063,
     266,  1012,  1153,  1157,  1158,  1159,  1160,  1161,  1163,  1164,
     719,   792,   871,   722,   571,   248,   986,   984,   262,  1021,
     574,   249,  1024,  1022,   263,  1042,  1041,   616,  1049,   988,
     987,  1020,  1120,   585,   295,   989,   990,   609,   613,  1074,
     991,   992,  1075,  1077,  1040,   527,   587,  1039,   868,  1076,
    1123,  1055,  1058,   630,   720,   593,  1038,   721,  1127,  1149,
     631,   634,  1071,  1162,     0,   854,   601,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   993,     0,     0,     0,   994,     0,  1027,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1016,     0,     0,
    1062,     0,  1017,  1029,     0,     0,     0,     0,  1030,   995,
       0,     0,     0,     0,     0,   996,     0,     0,     0,   997,
       0,  1064,     0,     0,     0,     0,  1018,     0,     0,     0,
       0,     0,  1031,   998,  1006,     0,     0,     0,   999,     0,
    1028,  1000,     0,     0,  1010,  1065,     0,     0,     0,     0,
    1011,     0,     0,  1063,     0,     0,     0,     0,  1001,     0,
       0,     0,  1002,     0,     0,  1003,     0,     0,     0,     0,
    1004,     0,     0,  1005,     0,     0,  1012
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    85,   668,    83,    77,   662,    83,   645,    77,
      78,    79,    80,    76,    77,    78,    79,    80,    17,    82,
      83,    77,    85,   910,    85,   910,   910,    77,   910,   910,
      10,    77,    86,    16,    17,    13,    14,    76,    77,    78,
      79,    80,    61,    82,    83,    77,    85,   551,     0,   104,
      77,    82,    83,    77,   102,    78,    79,    78,    79,    78,
      79,   109,   566,    78,    79,     5,     3,     7,     3,     9,
      77,     8,     3,     8,    77,     6,     3,    77,     3,   582,
      21,     8,    77,     8,     3,    77,     7,     6,    77,   111,
     112,   594,   595,   596,     7,    78,    79,    60,    61,    86,
      87,    88,    89,   150,   151,   152,   153,   130,   131,     7,
      11,    12,    21,     7,    15,    78,    79,    18,    19,    20,
      61,    30,    63,    64,     7,     3,    67,    68,    69,   184,
       8,    22,    23,    24,    25,    98,    99,    78,    79,   158,
     187,   160,   161,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       3,   184,   184,     6,     3,   184,     7,     6,   159,    78,
      79,   162,   163,   164,   165,     3,   156,    78,    79,   184,
       8,     7,   104,   105,    85,   107,   166,   167,   168,    90,
      91,    92,    93,    94,     3,    96,     7,     3,     3,     8,
     101,   184,     8,     8,   184,   121,   122,   123,  1095,   110,
    1095,  1095,   113,  1095,  1095,   124,   125,   126,   127,   120,
       3,   184,    60,     3,     3,     8,     6,   128,   129,     8,
       7,   132,   133,   147,   148,    73,    74,    75,    76,    77,
      78,    79,     7,   184,   184,   185,   186,   187,   111,   112,
       3,     7,     3,   154,   155,     8,   157,     8,     3,    97,
     916,   898,   100,     8,    61,    62,    63,    64,    65,    66,
       7,     3,     3,     7,     7,   184,     8,     8,   943,    21,
     157,    78,    79,   184,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,   114,   115,   116,   117,   118,   119,    60,     3,
       3,     3,     3,   397,     8,     8,     8,     8,     3,    61,
      60,    59,     6,     8,     3,     3,    78,    79,     3,     8,
       8,    71,     3,     8,     3,     3,     3,     8,    78,    79,
       8,     8,     3,     3,    96,     4,   184,     8,     8,     3,
     102,   103,   104,   105,   106,   107,     8,    97,   442,     4,
     100,     4,   446,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   458,     4,     4,   461,   458,     4,
       4,     4,     4,   446,   468,     4,   458,   184,   387,   388,
     458,     4,     8,   461,   478,   458,     3,     8,   461,     4,
     468,     4,   458,     3,   488,   468,     8,   446,   458,   493,
     478,     4,   458,     4,   493,   478,     8,   493,     3,   458,
       4,     4,   461,     4,     4,   488,   458,   511,   511,   468,
     493,   458,   184,     4,   458,   184,     4,     4,     4,   478,
     461,     4,   184,     4,   184,     4,   461,   468,   511,   488,
     511,   458,     4,   468,   493,   458,     4,   488,   458,   513,
       4,     4,   493,   458,     4,     4,   458,     4,   185,   458,
     185,   185,   511,   185,   185,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,   185,   185,   185,
       4,    60,   187,     4,     7,     4,   185,   187,   186,   186,
       4,    70,     4,    72,     4,     4,     4,   187,     4,    78,
      79,    80,    81,    82,    83,    84,    85,     4,     4,     4,
       4,   185,     4,     4,     4,   524,   525,   526,    97,     4,
       4,   100,   101,     4,     4,     4,     4,     4,     4,   108,
       4,     4,     4,     4,     4,   187,     4,     4,     4,     4,
       4,     4,   636,     4,     4,   185,     4,     4,   185,   643,
       4,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,   185,     4,    58,   185,    60,    61,     4,
     643,    78,    79,   637,   668,   669,     4,   671,   671,     4,
     185,     4,     4,     4,     4,    78,    79,   187,    81,    82,
     187,    84,    85,     4,   643,   668,   669,     4,   671,   187,
     671,   187,     4,     4,    97,   184,   615,   100,     4,     4,
     185,   185,     4,   185,     4,   108,     4,   187,     4,   668,
     669,   187,   671,     4,   185,     7,   635,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     184,     7,     7,     7,     7,     5,   184,   154,   155,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,     5,     5,     5,   184,     5,     7,
       5,     5,     5,   184,     5,     7,     5,   184,     5,     7,
     184,     7,     7,     7,     5,     5,     5,     5,   187,     5,
       7,   184,     7,     7,     7,   184,   184,   184,   184,     7,
       7,   184,   184,     7,    95,   149,     7,     7,     7,   184,
       7,     7,     4,     4,     4,   184,     4,     4,     4,     4,
       4,     4,   184,     4,     4,   184,     3,     6,   184,   184,
       6,   184,   184,   184,   184,   184,   184,   184,   184,   184,
       3,   184,     6,     3,     6,     3,     3,     6,   184,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   566,     6,     3,     6,     4,   185,
       8,     6,     4,     4,     4,   185,     4,   185,   187,   185,
     185,     4,     4,     4,   187,   185,   185,   185,     4,     4,
       4,   185,   185,     4,     4,     3,   185,     6,   185,     4,
     185,   185,   185,     4,     8,   185,   185,   901,   184,   184,
     904,   901,   184,   907,   184,   184,   910,   184,   907,   901,
     910,   907,   184,   901,     8,   184,     8,   921,   901,     3,
     924,   904,   910,   927,   907,   901,     8,   910,   184,   184,
     184,   901,     4,   921,   910,   901,   924,     4,   921,   943,
     910,   924,   901,   947,   910,   904,   950,   187,   907,   901,
       4,   910,   956,   904,   901,   959,   907,   901,   910,   910,
     943,     4,   921,   910,   947,   924,   910,   950,   956,   910,
     921,   959,   184,   956,   901,   910,   959,   185,   901,   184,
     184,   901,     5,   910,   943,   184,   901,   910,   947,   901,
     910,   950,   901,     7,     4,   910,     4,   956,   910,   950,
     959,   910,     4,     4,   187,   185,   185,     4,   184,   184,
     636,   661,   717,   643,   442,   956,   900,   895,   959,   913,
     446,   956,   919,   916,   959,   929,   927,   496,   936,   903,
     901,   912,  1095,   458,    81,   904,   906,   488,   493,   956,
     907,   909,   958,   961,   926,   397,   461,   924,   684,   959,
    1101,   943,   947,   511,   637,   468,   922,   642,  1114,  1135,
     513,   517,   951,  1155,    -1,   671,   478,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1095,    -1,    -1,    -1,  1095,    -1,  1101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1095,    -1,    -1,
    1114,    -1,  1095,  1101,    -1,    -1,    -1,    -1,  1101,  1095,
      -1,    -1,    -1,    -1,    -1,  1095,    -1,    -1,    -1,  1095,
      -1,  1114,    -1,    -1,    -1,    -1,  1095,    -1,    -1,    -1,
      -1,    -1,  1101,  1095,  1095,    -1,    -1,    -1,  1095,    -1,
    1101,  1095,    -1,    -1,  1095,  1114,    -1,    -1,    -1,    -1,
    1095,    -1,    -1,  1114,    -1,    -1,    -1,    -1,  1095,    -1,
      -1,    -1,  1095,    -1,    -1,  1095,    -1,    -1,    -1,    -1,
    1095,    -1,    -1,  1095,    -1,    -1,  1095
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,     0,     5,     7,     9,   184,   185,   186,   187,
     205,   206,   207,   212,     7,   221,     7,   227,     7,   250,
       7,   349,     7,   426,     7,   442,     7,   459,     7,   378,
       7,   384,     7,   408,     7,   325,     7,   520,     7,   567,
       7,   558,   213,   208,   222,   228,   251,   350,   427,   443,
     460,   379,   385,   409,   326,   521,   568,   559,   205,   214,
     215,   184,   210,   211,    10,   156,   166,   167,   168,   184,
     220,   223,   224,   225,   550,   552,   554,   565,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    78,    79,    85,    90,    91,    92,    93,    94,    96,
     101,   110,   113,   120,   128,   129,   132,   133,   154,   155,
     157,   220,   229,   230,   231,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   248,
     257,   259,   261,   299,   305,   311,   317,   319,   333,   343,
     363,   368,   376,   402,   432,   434,   453,   483,   495,   507,
     508,   516,   518,   546,   548,   556,   571,    16,    17,   220,
     252,   253,   254,   256,   432,   434,    70,    72,    80,    81,
      82,    83,    84,    97,   100,   108,   220,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   351,
     352,   353,   355,   357,   359,   361,   363,   366,   367,   402,
     420,   432,   434,   436,   453,   478,    71,   220,   359,   361,
     402,   428,   429,   430,   432,   434,    73,    74,    75,    76,
      77,   220,   359,   361,   402,   432,   434,   444,   445,   446,
     448,   449,   451,   452,    96,   102,   103,   104,   105,   106,
     107,   220,   402,   432,   434,   461,   462,   463,   464,   466,
     468,   470,   472,   474,   476,   376,    21,    61,    63,    64,
      67,    68,    69,   220,   279,   386,   387,   388,   389,   390,
     391,   392,   394,   396,   398,   399,   401,   432,   434,    62,
      65,    66,   220,   279,   390,   396,   410,   411,   412,   413,
     414,   416,   417,   418,   419,   432,   434,   111,   112,   220,
     327,   328,   329,   331,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   220,   432,   434,
     522,   523,   524,   525,   527,   529,   530,   532,   533,   534,
     537,   539,   540,   541,   544,   546,   548,   569,   570,   571,
      13,    14,   560,   561,   562,   564,     6,     3,     4,     8,
       3,   226,   566,   551,   553,   555,     4,     3,     8,   232,
     557,   249,   258,   260,   262,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   247,   344,
     377,   403,   433,   435,   364,   369,   306,   318,   312,   300,
     484,   454,   320,   334,   496,     4,   509,   517,   519,   547,
     549,   572,     3,     8,   255,     4,     3,     8,   421,   437,
     354,   356,   358,     4,     4,   362,   360,   479,     3,     8,
     431,     3,     8,   447,     4,   450,     4,     4,     3,     8,
     477,   465,   467,   469,   471,   473,   475,     8,     3,     8,
     393,   280,     4,   397,   395,   400,     4,     8,     3,   415,
       4,     4,     8,     3,   330,   332,     3,     8,     4,   526,
     528,     4,   531,     4,     4,   535,   538,     4,     4,   542,
     545,     3,     8,     3,     8,   563,     4,     3,     8,   205,
     205,   184,     4,     4,     4,     4,     4,   224,     4,     4,
       4,     4,     4,     4,   185,   185,   185,   185,   185,   185,
     185,   185,   187,   187,   186,   186,   185,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   185,     4,     4,     4,     4,     4,
       4,   230,     4,   187,   253,     4,     4,     4,     4,     4,
     185,   187,     4,     4,     4,   352,     4,   429,     4,   185,
       4,   185,   185,   445,     4,     4,     4,     4,     4,     4,
       4,   463,     4,     4,   185,     4,     4,     4,   187,   388,
       4,   187,   187,   412,     4,     4,   328,   187,     4,     4,
     185,     4,   185,   185,     4,     4,   187,   187,     4,     4,
     523,   570,     4,   185,   561,     4,     7,     7,   205,   205,
     205,   184,     7,     7,     7,     7,     5,   184,     5,     5,
       5,   207,   209,   184,    86,    87,    88,    89,   365,     5,
       5,     5,     5,     7,     5,     5,     5,     7,     7,     7,
     209,     7,   184,   184,     5,     5,   216,     5,     5,   184,
     184,   184,   216,   184,     7,   184,   184,   184,   216,   216,
     216,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   205,   184,   184,   184,   147,   148,   536,   149,
     150,   151,   152,   153,   187,   543,   184,     5,   205,   229,
     569,   560,   252,    21,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,   220,   267,   268,   269,   272,   274,   276,   278,
     279,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   292,   293,   295,   297,   267,     7,   263,   264,   265,
       7,   345,   346,   347,     7,   380,   381,   382,     7,   404,
     405,   406,     7,   370,   371,   372,   104,   184,   307,   308,
     309,   310,   214,   105,   107,   309,   313,   314,   315,   316,
      95,   301,   302,   303,     7,   485,   486,     7,   455,   456,
     457,     7,   321,   322,   323,   114,   115,   116,   117,   118,
     119,   335,   336,   337,   338,   339,   340,   341,   342,    21,
     124,   125,   126,   127,   220,   281,   432,   434,   497,   498,
     499,   502,   503,   505,   506,   130,   131,   220,   432,   434,
     510,   511,   512,   514,   522,     7,   573,   574,   217,     7,
     422,   423,   424,     7,   438,   439,   440,   109,   464,   480,
     481,   263,     8,     8,     8,     8,   270,   273,   275,   277,
       4,     4,     4,     4,     4,   291,     4,     4,   294,   296,
     298,     4,     4,     4,     4,     3,     8,     8,   266,     6,
       3,   348,     6,     3,   383,     6,     3,   407,     6,     3,
     373,     6,     3,     3,     6,     6,     3,     6,   304,     3,
       8,   487,     3,     6,   458,     6,     3,   324,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   500,   504,
       4,     4,     4,     3,     8,   513,   515,     3,     8,     8,
     575,     3,     6,   184,   218,   219,   425,     6,     3,   441,
       6,     3,   482,     8,     6,     4,     4,     4,     4,   185,
     187,   185,   187,   185,     4,   185,   185,     4,     4,     4,
     185,   185,   187,   185,   268,   267,   265,   351,   347,   386,
     382,   410,   406,   220,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   279,   343,   355,   357,
     359,   361,   363,   367,   374,   375,   402,   432,   434,   478,
     372,   308,   314,     4,   302,    98,    99,   220,   279,   402,
     432,   434,   488,   489,   490,   491,   492,   494,   486,   461,
     457,   327,   323,   185,   185,   185,   185,   185,   185,   336,
       4,     4,   185,   185,   185,   498,     4,     4,   511,   158,
     160,   161,   220,   279,   432,   434,   576,   577,   578,   579,
     581,   574,     6,     3,   428,   424,   444,   440,     4,    22,
      23,    24,    25,   271,   184,   184,   184,   184,   184,   184,
     184,     8,     8,     8,     8,     3,     8,   184,   493,     4,
       8,     3,     8,     8,   121,   122,   123,   501,   184,   184,
     184,   582,     4,   580,     3,     8,   184,     8,     8,   184,
     375,     4,   187,   490,     4,   185,     4,   577,   184,     5,
     184,     7,   583,   584,   585,     3,     6,   159,   162,   163,
     164,   165,   586,   587,   588,   590,   591,   592,   593,   584,
     589,     4,     4,     4,   594,     3,     8,     4,   187,   185,
     185,     4,   587,   184,   184
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   188,   190,   189,   191,   189,   192,   189,   193,   189,
     194,   189,   195,   189,   196,   189,   197,   189,   198,   189,
     199,   189,   200,   189,   201,   189,   202,   189,   203,   189,
     204,   189,   205,   205,   205,   205,   205,   205,   205,   206,
     208,   207,   209,   210,   210,   211,   211,   213,   212,   214,
     214,   215,   215,   217,   216,   218,   218,   219,   219,   220,
     222,   221,   223,   223,   224,   224,   224,   224,   224,   224,
     226,   225,   228,   227,   229,   229,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     232,   231,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   247,   246,   249,   248,   251,
     250,   252,   252,   253,   253,   253,   253,   253,   255,   254,
     256,   258,   257,   260,   259,   262,   261,   263,   263,   264,
     264,   266,   265,   267,   267,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   270,   269,   271,   271,
     271,   271,   273,   272,   275,   274,   277,   276,   278,   280,
     279,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     291,   290,   292,   294,   293,   296,   295,   298,   297,   300,
     299,   301,   301,   302,   304,   303,   306,   305,   307,   307,
     308,   308,   309,   310,   312,   311,   313,   313,   314,   314,
     314,   315,   316,   318,   317,   320,   319,   321,   321,   322,
     322,   324,   323,   326,   325,   327,   327,   327,   328,   328,
     330,   329,   332,   331,   334,   333,   335,   335,   336,   336,
     336,   336,   336,   336,   337,   338,   339,   340,   341,   342,
     344,   343,   345,   345,   346,   346,   348,   347,   350,   349,
     351,   351,   352,   352,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   352,   352,   352,   352,   352,
     354,   353,   356,   355,   358,   357,   360,   359,   362,   361,
     364,   363,   365,   365,   365,   365,   366,   367,   369,   368,
     370,   370,   371,   371,   373,   372,   374,   374,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   377,   376,   379,   378,   380,   380,   381,
     381,   383,   382,   385,   384,   386,   386,   387,   387,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   389,
     390,   391,   393,   392,   395,   394,   397,   396,   398,   400,
     399,   401,   403,   402,   404,   404,   405,   405,   407,   406,
     409,   408,   410,   410,   411,   411,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   413,   415,   414,   416,   417,
     418,   419,   421,   420,   422,   422,   423,   423,   425,   424,
     427,   426,   428,   428,   429,   429,   429,   429,   429,   429,
     429,   431,   430,   433,   432,   435,   434,   437,   436,   438,
     438,   439,   439,   441,   440,   443,   442,   444,   444,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     447,   446,   448,   450,   449,   451,   452,   454,   453,   455,
     455,   456,   456,   458,   457,   460,   459,   461,   461,   462,
     462,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   465,   464,   467,   466,   469,   468,   471,   470,
     473,   472,   475,   474,   477,   476,   479,   478,   480,   480,
     482,   481,   484,   483,   485,   485,   487,   486,   488,   488,
     489,   489,   490,   490,   490,   490,   490,   490,   490,   491,
     493,   492,   494,   496,   495,   497,   497,   498,   498,   498,
     498,   498,   498,   498,   498,   498,   500,   499,   501,   501,
     501,   502,   504,   503,   505,   506,   507,   509,   508,   510,
     510,   511,   511,   511,   511,   511,   513,   512,   515,   514,
     517,   516,   519,   518,   521,   520,   522,   522,   523,   523,
     523,   523,   523,   523,   523,   523,   523,   523,   523,   523,
     523,   523,   523,   523,   523,   523,   524,   526,   525,   528,
     527,   529,   531,   530,   532,   533,   535,   534,   536,   536,
     538,   537,   539,   540,   542,   541,   543,   543,   543,   543,
     543,   545,   544,   547,   546,   549,   548,   551,   550,   553,
     552,   555,   554,   557,   556,   559,   558,   560,   560,   561,
     561,   563,   562,   564,   566,   565,   568,   567,   569,   569,
     570,   572,   571,   573,   573,   575,   574,   576,   576,   577,
     577,   577,   577,   577,   577,   577,   578,   580,   579,   582,
     581,   583,   583,   585,   584,   586,   586,   587,   587,   587,
     587,   587,   589,   588,   590,   591,   592,   594,   593
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
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     0,     6,     3,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "\"renew-timer\"", "\"rebind-timer\"", "\"allow-static-leases\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet6\"",
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
  "renew_timer", "rebind_timer", "allow_static_leases",
  "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@23", "interfaces_config",
  "$@24", "sub_interfaces6", "$@25", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@26", "re_detect",
  "lease_database", "$@27", "hosts_database", "$@28", "hosts_databases",
  "$@29", "database_list", "not_empty_database_list", "database", "$@30",
  "database_map_params", "database_map_param", "database_type", "$@31",
  "db_type", "user", "$@32", "password", "$@33", "host", "$@34", "port",
  "name", "$@35", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "max_row_errors", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@36",
  "max_reconnect_tries", "keyspace", "$@37", "consistency", "$@38",
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
       0,   272,   272,   272,   273,   273,   274,   274,   275,   275,
     276,   276,   277,   277,   278,   278,   279,   279,   280,   280,
     281,   281,   282,   282,   283,   283,   284,   284,   285,   285,
     286,   286,   294,   295,   296,   297,   298,   299,   300,   303,
     308,   308,   319,   322,   323,   326,   330,   337,   337,   344,
     345,   348,   352,   359,   359,   366,   367,   370,   374,   385,
     395,   395,   410,   411,   415,   416,   417,   418,   419,   420,
     423,   423,   438,   438,   447,   448,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     499,   499,   507,   512,   517,   522,   527,   532,   537,   542,
     547,   552,   557,   562,   567,   572,   572,   580,   580,   591,
     591,   600,   601,   604,   605,   606,   607,   608,   611,   611,
     621,   627,   627,   639,   639,   651,   651,   661,   662,   665,
     666,   669,   669,   679,   680,   683,   684,   685,   686,   687,
     688,   689,   690,   691,   692,   693,   694,   695,   696,   697,
     698,   699,   700,   701,   702,   703,   706,   706,   713,   714,
     715,   716,   719,   719,   727,   727,   735,   735,   743,   748,
     748,   756,   761,   766,   771,   776,   781,   786,   791,   796,
     801,   801,   809,   814,   814,   822,   822,   830,   830,   838,
     838,   848,   849,   851,   853,   853,   871,   871,   881,   882,
     885,   886,   889,   894,   899,   899,   909,   910,   913,   914,
     915,   918,   923,   930,   930,   940,   940,   950,   951,   954,
     955,   958,   958,   968,   968,   978,   979,   980,   983,   984,
     987,   987,   995,   995,  1003,  1003,  1014,  1015,  1018,  1019,
    1020,  1021,  1022,  1023,  1026,  1031,  1036,  1041,  1046,  1051,
    1059,  1059,  1072,  1073,  1076,  1077,  1084,  1084,  1110,  1110,
    1121,  1122,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,
    1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,
    1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,  1153,
    1156,  1156,  1164,  1164,  1172,  1172,  1180,  1180,  1188,  1188,
    1198,  1198,  1205,  1206,  1207,  1208,  1211,  1216,  1224,  1224,
    1235,  1236,  1240,  1241,  1244,  1244,  1252,  1253,  1256,  1257,
    1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,
    1268,  1269,  1270,  1271,  1272,  1273,  1274,  1275,  1276,  1277,
    1278,  1279,  1280,  1287,  1287,  1300,  1300,  1309,  1310,  1313,
    1314,  1319,  1319,  1334,  1334,  1348,  1349,  1352,  1353,  1356,
    1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,  1365,  1368,
    1370,  1375,  1377,  1377,  1385,  1385,  1393,  1393,  1401,  1403,
    1403,  1411,  1420,  1420,  1432,  1433,  1438,  1439,  1444,  1444,
    1456,  1456,  1468,  1469,  1474,  1475,  1480,  1481,  1482,  1483,
    1484,  1485,  1486,  1487,  1488,  1491,  1493,  1493,  1501,  1503,
    1505,  1510,  1518,  1518,  1530,  1531,  1534,  1535,  1538,  1538,
    1548,  1548,  1557,  1558,  1561,  1562,  1563,  1564,  1565,  1566,
    1567,  1570,  1570,  1578,  1578,  1603,  1603,  1633,  1633,  1645,
    1646,  1649,  1650,  1653,  1653,  1665,  1665,  1677,  1678,  1681,
    1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,
    1694,  1694,  1702,  1707,  1707,  1715,  1720,  1728,  1728,  1738,
    1739,  1742,  1743,  1746,  1746,  1755,  1755,  1764,  1765,  1768,
    1769,  1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,
    1782,  1783,  1786,  1786,  1796,  1796,  1806,  1806,  1814,  1814,
    1822,  1822,  1830,  1830,  1838,  1838,  1851,  1851,  1861,  1862,
    1865,  1865,  1876,  1876,  1886,  1887,  1890,  1890,  1900,  1901,
    1904,  1905,  1908,  1909,  1910,  1911,  1912,  1913,  1914,  1917,
    1919,  1919,  1927,  1935,  1935,  1947,  1948,  1951,  1952,  1953,
    1954,  1955,  1956,  1957,  1958,  1959,  1962,  1962,  1969,  1970,
    1971,  1974,  1979,  1979,  1987,  1992,  1999,  2006,  2006,  2016,
    2017,  2020,  2021,  2022,  2023,  2024,  2027,  2027,  2035,  2035,
    2045,  2045,  2085,  2085,  2097,  2097,  2107,  2108,  2111,  2112,
    2113,  2114,  2115,  2116,  2117,  2118,  2119,  2120,  2121,  2122,
    2123,  2124,  2125,  2126,  2127,  2128,  2131,  2136,  2136,  2144,
    2144,  2152,  2157,  2157,  2165,  2170,  2175,  2175,  2183,  2184,
    2187,  2187,  2195,  2200,  2205,  2205,  2213,  2216,  2219,  2222,
    2225,  2231,  2231,  2239,  2239,  2247,  2247,  2257,  2257,  2264,
    2264,  2271,  2271,  2280,  2280,  2291,  2291,  2301,  2302,  2306,
    2307,  2310,  2310,  2320,  2330,  2330,  2340,  2340,  2351,  2352,
    2356,  2360,  2360,  2372,  2373,  2377,  2377,  2385,  2386,  2389,
    2390,  2391,  2392,  2393,  2394,  2395,  2398,  2403,  2403,  2411,
    2411,  2421,  2422,  2425,  2425,  2433,  2434,  2437,  2438,  2439,
    2440,  2441,  2444,  2444,  2452,  2457,  2462,  2467,  2467
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
#line 5307 "dhcp6_parser.cc"

#line 2475 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
