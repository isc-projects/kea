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
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1158 "dhcp6_parser.cc"
    break;

  case 131:
#line 552 "dhcp6_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1167 "dhcp6_parser.cc"
    break;

  case 132:
#line 557 "dhcp6_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1176 "dhcp6_parser.cc"
    break;

  case 133:
#line 562 "dhcp6_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 134:
#line 567 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 135:
#line 569 "dhcp6_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 136:
#line 575 "dhcp6_parser.yy"
    {
    ElementPtr er(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-reconfiguration", er);
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

  case 319:
#line 1155 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 320:
#line 1157 "dhcp6_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 321:
#line 1163 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 322:
#line 1165 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 323:
#line 1171 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 324:
#line 1173 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 325:
#line 1179 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2101 "dhcp6_parser.cc"
    break;

  case 326:
#line 1181 "dhcp6_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2111 "dhcp6_parser.cc"
    break;

  case 327:
#line 1187 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2122 "dhcp6_parser.cc"
    break;

  case 328:
#line 1192 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 329:
#line 1197 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2139 "dhcp6_parser.cc"
    break;

  case 330:
#line 1199 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2148 "dhcp6_parser.cc"
    break;

  case 331:
#line 1204 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2154 "dhcp6_parser.cc"
    break;

  case 332:
#line 1205 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2160 "dhcp6_parser.cc"
    break;

  case 333:
#line 1206 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2166 "dhcp6_parser.cc"
    break;

  case 334:
#line 1207 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2172 "dhcp6_parser.cc"
    break;

  case 335:
#line 1210 "dhcp6_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2181 "dhcp6_parser.cc"
    break;

  case 336:
#line 1215 "dhcp6_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2190 "dhcp6_parser.cc"
    break;

  case 337:
#line 1223 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 338:
#line 1228 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2210 "dhcp6_parser.cc"
    break;

  case 343:
#line 1243 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2220 "dhcp6_parser.cc"
    break;

  case 344:
#line 1247 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 371:
#line 1285 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 372:
#line 1290 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2248 "dhcp6_parser.cc"
    break;

  case 373:
#line 1298 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 374:
#line 1301 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 2265 "dhcp6_parser.cc"
    break;

  case 379:
#line 1317 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2275 "dhcp6_parser.cc"
    break;

  case 380:
#line 1321 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2287 "dhcp6_parser.cc"
    break;

  case 381:
#line 1332 "dhcp6_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2297 "dhcp6_parser.cc"
    break;

  case 382:
#line 1336 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2309 "dhcp6_parser.cc"
    break;

  case 398:
#line 1368 "dhcp6_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 400:
#line 1375 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc"
    break;

  case 401:
#line 1377 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 402:
#line 1383 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 403:
#line 1385 "dhcp6_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2354 "dhcp6_parser.cc"
    break;

  case 404:
#line 1391 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 405:
#line 1393 "dhcp6_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 407:
#line 1401 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2380 "dhcp6_parser.cc"
    break;

  case 408:
#line 1403 "dhcp6_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2390 "dhcp6_parser.cc"
    break;

  case 409:
#line 1409 "dhcp6_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2399 "dhcp6_parser.cc"
    break;

  case 410:
#line 1418 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2410 "dhcp6_parser.cc"
    break;

  case 411:
#line 1423 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2419 "dhcp6_parser.cc"
    break;

  case 416:
#line 1442 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2429 "dhcp6_parser.cc"
    break;

  case 417:
#line 1446 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2438 "dhcp6_parser.cc"
    break;

  case 418:
#line 1454 "dhcp6_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 419:
#line 1458 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2457 "dhcp6_parser.cc"
    break;

  case 434:
#line 1491 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 435:
#line 1493 "dhcp6_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 438:
#line 1503 "dhcp6_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2484 "dhcp6_parser.cc"
    break;

  case 439:
#line 1508 "dhcp6_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2493 "dhcp6_parser.cc"
    break;

  case 440:
#line 1516 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2504 "dhcp6_parser.cc"
    break;

  case 441:
#line 1521 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc"
    break;

  case 446:
#line 1536 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2523 "dhcp6_parser.cc"
    break;

  case 447:
#line 1540 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2533 "dhcp6_parser.cc"
    break;

  case 448:
#line 1546 "dhcp6_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2543 "dhcp6_parser.cc"
    break;

  case 449:
#line 1550 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2552 "dhcp6_parser.cc"
    break;

  case 459:
#line 1568 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 460:
#line 1570 "dhcp6_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 461:
#line 1576 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2578 "dhcp6_parser.cc"
    break;

  case 462:
#line 1578 "dhcp6_parser.yy"
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

  case 463:
#line 1601 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2613 "dhcp6_parser.cc"
    break;

  case 464:
#line 1603 "dhcp6_parser.yy"
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

  case 465:
#line 1631 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 466:
#line 1636 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2662 "dhcp6_parser.cc"
    break;

  case 471:
#line 1651 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2672 "dhcp6_parser.cc"
    break;

  case 472:
#line 1655 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2684 "dhcp6_parser.cc"
    break;

  case 473:
#line 1663 "dhcp6_parser.yy"
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 474:
#line 1667 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2706 "dhcp6_parser.cc"
    break;

  case 488:
#line 1692 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp6_parser.cc"
    break;

  case 489:
#line 1694 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc"
    break;

  case 490:
#line 1700 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2733 "dhcp6_parser.cc"
    break;

  case 491:
#line 1705 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 492:
#line 1707 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 493:
#line 1713 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2760 "dhcp6_parser.cc"
    break;

  case 494:
#line 1718 "dhcp6_parser.yy"
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2769 "dhcp6_parser.cc"
    break;

  case 495:
#line 1726 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2780 "dhcp6_parser.cc"
    break;

  case 496:
#line 1731 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc"
    break;

  case 501:
#line 1744 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2799 "dhcp6_parser.cc"
    break;

  case 502:
#line 1748 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2808 "dhcp6_parser.cc"
    break;

  case 503:
#line 1753 "dhcp6_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2818 "dhcp6_parser.cc"
    break;

  case 504:
#line 1757 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2827 "dhcp6_parser.cc"
    break;

  case 520:
#line 1784 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 521:
#line 1789 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2847 "dhcp6_parser.cc"
    break;

  case 522:
#line 1794 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 523:
#line 1799 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 524:
#line 1804 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 525:
#line 1806 "dhcp6_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 526:
#line 1812 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 527:
#line 1814 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 528:
#line 1820 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 529:
#line 1822 "dhcp6_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 530:
#line 1828 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2929 "dhcp6_parser.cc"
    break;

  case 531:
#line 1830 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2939 "dhcp6_parser.cc"
    break;

  case 532:
#line 1836 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2950 "dhcp6_parser.cc"
    break;

  case 533:
#line 1841 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2959 "dhcp6_parser.cc"
    break;

  case 534:
#line 1849 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2970 "dhcp6_parser.cc"
    break;

  case 535:
#line 1854 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2979 "dhcp6_parser.cc"
    break;

  case 538:
#line 1863 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp6_parser.cc"
    break;

  case 539:
#line 1865 "dhcp6_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2997 "dhcp6_parser.cc"
    break;

  case 540:
#line 1874 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3008 "dhcp6_parser.cc"
    break;

  case 541:
#line 1879 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 544:
#line 1888 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 545:
#line 1892 "dhcp6_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 558:
#line 1917 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 559:
#line 1919 "dhcp6_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 560:
#line 1925 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 561:
#line 1933 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3075 "dhcp6_parser.cc"
    break;

  case 562:
#line 1938 "dhcp6_parser.yy"
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp6_parser.cc"
    break;

  case 574:
#line 1960 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3094 "dhcp6_parser.cc"
    break;

  case 575:
#line 1962 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3103 "dhcp6_parser.cc"
    break;

  case 576:
#line 1967 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3109 "dhcp6_parser.cc"
    break;

  case 577:
#line 1968 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3115 "dhcp6_parser.cc"
    break;

  case 578:
#line 1969 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3121 "dhcp6_parser.cc"
    break;

  case 579:
#line 1972 "dhcp6_parser.yy"
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 580:
#line 1977 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp6_parser.cc"
    break;

  case 581:
#line 1979 "dhcp6_parser.yy"
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3148 "dhcp6_parser.cc"
    break;

  case 582:
#line 1985 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 583:
#line 1990 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3166 "dhcp6_parser.cc"
    break;

  case 584:
#line 1997 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3175 "dhcp6_parser.cc"
    break;

  case 585:
#line 2004 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3186 "dhcp6_parser.cc"
    break;

  case 586:
#line 2009 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 594:
#line 2025 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp6_parser.cc"
    break;

  case 595:
#line 2027 "dhcp6_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3213 "dhcp6_parser.cc"
    break;

  case 596:
#line 2033 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 597:
#line 2035 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 598:
#line 2043 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 599:
#line 2045 "dhcp6_parser.yy"
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

  case 600:
#line 2083 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3290 "dhcp6_parser.cc"
    break;

  case 601:
#line 2088 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3301 "dhcp6_parser.cc"
    break;

  case 602:
#line 2095 "dhcp6_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3311 "dhcp6_parser.cc"
    break;

  case 603:
#line 2099 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3321 "dhcp6_parser.cc"
    break;

  case 624:
#line 2129 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3330 "dhcp6_parser.cc"
    break;

  case 625:
#line 2134 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 626:
#line 2136 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 627:
#line 2142 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3356 "dhcp6_parser.cc"
    break;

  case 628:
#line 2144 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 629:
#line 2150 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3375 "dhcp6_parser.cc"
    break;

  case 630:
#line 2155 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3383 "dhcp6_parser.cc"
    break;

  case 631:
#line 2157 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 632:
#line 2163 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3402 "dhcp6_parser.cc"
    break;

  case 633:
#line 2168 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3411 "dhcp6_parser.cc"
    break;

  case 634:
#line 2173 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3419 "dhcp6_parser.cc"
    break;

  case 635:
#line 2175 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 636:
#line 2181 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3434 "dhcp6_parser.cc"
    break;

  case 637:
#line 2182 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3440 "dhcp6_parser.cc"
    break;

  case 638:
#line 2185 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 639:
#line 2187 "dhcp6_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 640:
#line 2193 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 641:
#line 2198 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 642:
#line 2203 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 643:
#line 2205 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3493 "dhcp6_parser.cc"
    break;

  case 644:
#line 2211 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3501 "dhcp6_parser.cc"
    break;

  case 645:
#line 2214 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3509 "dhcp6_parser.cc"
    break;

  case 646:
#line 2217 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3517 "dhcp6_parser.cc"
    break;

  case 647:
#line 2220 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3525 "dhcp6_parser.cc"
    break;

  case 648:
#line 2223 "dhcp6_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3534 "dhcp6_parser.cc"
    break;

  case 649:
#line 2229 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 650:
#line 2231 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 651:
#line 2237 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 652:
#line 2239 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 653:
#line 2245 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 654:
#line 2247 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3588 "dhcp6_parser.cc"
    break;

  case 655:
#line 2255 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 656:
#line 2257 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3605 "dhcp6_parser.cc"
    break;

  case 657:
#line 2262 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 658:
#line 2264 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3622 "dhcp6_parser.cc"
    break;

  case 659:
#line 2269 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 660:
#line 2271 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 661:
#line 2278 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3650 "dhcp6_parser.cc"
    break;

  case 662:
#line 2283 "dhcp6_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3660 "dhcp6_parser.cc"
    break;

  case 663:
#line 2289 "dhcp6_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3670 "dhcp6_parser.cc"
    break;

  case 664:
#line 2293 "dhcp6_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3679 "dhcp6_parser.cc"
    break;

  case 669:
#line 2308 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 670:
#line 2313 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 671:
#line 2318 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 672:
#line 2328 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3719 "dhcp6_parser.cc"
    break;

  case 673:
#line 2333 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 674:
#line 2338 "dhcp6_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3738 "dhcp6_parser.cc"
    break;

  case 675:
#line 2342 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 679:
#line 2358 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 680:
#line 2363 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 683:
#line 2375 "dhcp6_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 684:
#line 2379 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 694:
#line 2396 "dhcp6_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 695:
#line 2401 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3801 "dhcp6_parser.cc"
    break;

  case 696:
#line 2403 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3811 "dhcp6_parser.cc"
    break;

  case 697:
#line 2409 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3822 "dhcp6_parser.cc"
    break;

  case 698:
#line 2414 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 701:
#line 2423 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3841 "dhcp6_parser.cc"
    break;

  case 702:
#line 2427 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3849 "dhcp6_parser.cc"
    break;

  case 710:
#line 2442 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3857 "dhcp6_parser.cc"
    break;

  case 711:
#line 2444 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 712:
#line 2450 "dhcp6_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 713:
#line 2455 "dhcp6_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3885 "dhcp6_parser.cc"
    break;

  case 714:
#line 2460 "dhcp6_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3894 "dhcp6_parser.cc"
    break;

  case 715:
#line 2465 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 716:
#line 2467 "dhcp6_parser.yy"
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


  const short Dhcp6Parser::yypact_ninf_ = -877;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     400,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,    44,    70,    50,    52,
      71,    78,   134,   156,   194,   209,   211,   251,   253,   278,
     279,   280,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,    70,   -80,    30,    79,    29,   281,   131,    43,
     401,   217,    81,   448,   -30,   466,   153,   163,  -877,   310,
     314,   319,   338,   345,  -877,  -877,  -877,  -877,  -877,   368,
    -877,    85,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,   372,   373,   375,   376,   380,   381,
     384,   386,   387,   390,   392,   396,  -877,   397,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,   402,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,    93,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   404,  -877,
      97,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,   406,   408,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   103,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
     144,  -877,  -877,  -877,  -877,  -877,   411,  -877,   416,   418,
    -877,  -877,  -877,  -877,  -877,  -877,   171,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,   417,   424,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,   421,  -877,  -877,   426,  -877,  -877,
    -877,   428,  -877,  -877,   425,   438,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   441,
     442,  -877,  -877,  -877,  -877,   434,   447,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   182,
    -877,  -877,  -877,   449,  -877,  -877,   450,  -877,   465,   469,
    -877,  -877,   470,   472,  -877,  -877,  -877,  -877,  -877,   192,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,   221,  -877,  -877,  -877,
     473,   227,  -877,  -877,  -877,  -877,    70,    70,  -877,   260,
     474,   478,   479,   491,   492,  -877,    30,  -877,   495,   498,
     511,   512,   513,   516,   220,   267,   285,   343,   348,   353,
     354,   356,   264,   357,   360,   362,   519,   342,   526,   527,
     528,   538,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   377,   559,   560,   561,   562,   563,
     580,    79,  -877,   582,   403,    29,  -877,   583,   584,   587,
     591,   594,   414,   429,   614,   618,   619,   281,  -877,   622,
     131,  -877,   623,   443,   625,   445,   446,    43,  -877,   629,
     630,   631,   632,   633,   636,   638,  -877,   401,  -877,   639,
     640,   461,   643,   644,   645,   464,  -877,    81,   648,   467,
     468,  -877,   448,   649,   652,    82,  -877,   471,   653,   655,
     475,   657,   477,   480,   659,   660,   481,   482,   662,   663,
     466,  -877,   153,  -877,   666,   486,   163,  -877,  -877,  -877,
     668,   667,   669,    70,    70,    70,  -877,   489,   670,   671,
     672,   673,   676,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,   499,  -877,   677,   679,   680,
     681,   502,    26,   682,   684,   685,   686,   687,   688,   690,
     691,   692,   693,  -877,   694,   681,   695,   508,   514,   698,
    -877,   699,  -877,  -877,   700,   701,   523,   524,   525,  -877,
    -877,   699,   529,   703,  -877,   530,  -877,   531,  -877,   532,
    -877,  -877,  -877,   699,   699,   699,   533,   534,   535,   536,
    -877,   537,   539,  -877,   540,   541,   542,  -877,  -877,   543,
    -877,  -877,  -877,   544,    70,  -877,  -877,   557,   558,  -877,
     564,  -877,  -877,    98,   573,  -877,  -877,    90,   565,  -877,
    -877,   706,  -877,  -877,    70,    79,   153,  -877,  -877,  -877,
    -877,   163,    29,   263,   263,   705,  -877,   722,   723,   724,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   725,   -33,
      70,   -35,   602,   726,   727,   728,   164,   125,    31,  -877,
     466,  -877,  -877,   729,  -877,  -877,   730,   731,  -877,  -877,
    -877,  -877,  -877,   -26,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,   705,  -877,   229,   245,
     256,   258,  -877,  -877,  -877,  -877,   735,   736,   739,   740,
     741,  -877,   742,   743,  -877,  -877,  -877,   746,   747,   748,
     749,  -877,   259,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,   265,  -877,   750,   751,  -877,  -877,
     752,   754,  -877,  -877,   753,   757,  -877,  -877,   755,   759,
    -877,  -877,   758,   760,  -877,  -877,  -877,    83,  -877,  -877,
    -877,   761,  -877,  -877,  -877,   150,  -877,  -877,  -877,  -877,
     266,  -877,  -877,  -877,   241,  -877,  -877,   762,   763,  -877,
    -877,   764,   766,  -877,   767,   768,   769,   770,   771,   772,
     304,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
     773,   774,   775,  -877,  -877,  -877,  -877,   305,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   311,
    -877,  -877,  -877,   334,  -877,   269,  -877,   571,  -877,   776,
     777,  -877,  -877,   778,   780,  -877,  -877,  -877,   779,  -877,
     782,  -877,  -877,  -877,  -877,   781,   785,   786,   787,   490,
     578,   596,   599,   607,   789,   609,   610,   792,   793,   794,
     615,   616,   612,   617,   263,  -877,  -877,   263,  -877,   705,
     281,  -877,   722,    81,  -877,   723,   448,  -877,   724,   440,
    -877,   725,   -33,  -877,  -877,   -35,  -877,   799,   602,  -877,
     127,   726,  -877,   401,  -877,   727,   -30,  -877,   728,   620,
     621,   624,   626,   627,   628,   164,  -877,   800,   803,   634,
     635,   637,   125,  -877,   804,   806,    31,  -877,  -877,   160,
     729,  -877,  -877,   808,   812,   131,  -877,   730,    43,  -877,
     731,   813,  -877,  -877,   143,   641,   647,   650,  -877,  -877,
    -877,  -877,  -877,   661,  -877,  -877,   664,   674,   675,  -877,
    -877,  -877,  -877,  -877,   335,  -877,   337,  -877,   810,  -877,
     815,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,   344,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,   717,  -877,  -877,   817,  -877,  -877,  -877,  -877,  -877,
     816,   824,  -877,  -877,  -877,  -877,  -877,   820,  -877,   346,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   235,   737,
    -877,  -877,  -877,  -877,   738,   756,  -877,  -877,   829,  -877,
    -877,  -877,  -877,  -877,   347,  -877,  -877,  -877,  -877,  -877,
    -877,   765,   365,  -877,   366,  -877,   783,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,   440,  -877,  -877,   832,   654,  -877,   127,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   839,
     721,   840,   160,  -877,  -877,  -877,  -877,  -877,  -877,   784,
    -877,  -877,   811,  -877,   788,  -877,  -877,   848,  -877,  -877,
     333,  -877,    19,   848,  -877,  -877,   853,   857,   862,  -877,
     367,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   872,   744,
     745,   790,   875,    19,  -877,   795,  -877,  -877,  -877,   796,
    -877,  -877,  -877
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   139,     9,
     288,    11,   448,    13,   473,    15,   503,    17,   373,    19,
     381,    21,   418,    23,   253,    25,   602,    27,   674,    29,
     663,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     505,     0,   383,   420,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   672,   655,   657,   659,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   120,   661,
     137,   151,   153,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   134,     0,   280,   371,
     410,   461,   463,   329,   337,   226,   243,   234,   219,   540,
     495,   245,   264,   561,     0,   585,   598,   600,   651,   653,
     679,   119,     0,    74,    76,    77,    78,    79,    80,    81,
      82,    83,    84,   112,   113,   114,    85,   110,   118,    88,
      89,    90,    91,   107,    92,    94,    93,    98,    99,    86,
     111,    87,    96,    97,   105,   106,   108,    95,   100,   101,
     102,   103,   104,   116,   117,   109,   115,   148,     0,   147,
       0,   141,   143,   144,   145,   146,   440,   465,   319,   321,
     323,     0,     0,   327,   325,   534,   318,   292,   293,   294,
     295,   296,   297,   298,   299,   315,   316,   317,     0,   290,
     303,   304,   305,   308,   309,   311,   306,   307,   300,   301,
     313,   314,   302,   310,   312,   459,   458,   454,   455,   453,
       0,   450,   452,   456,   457,   488,     0,   491,     0,     0,
     487,   481,   482,   480,   485,   486,     0,   475,   477,   478,
     483,   484,   479,   532,   520,   522,   524,   526,   528,   530,
     519,   516,   517,   518,     0,   506,   507,   511,   512,   509,
     513,   514,   515,   510,     0,   400,   199,     0,   404,   402,
     407,     0,   396,   397,     0,   384,   385,   387,   399,   388,
     389,   390,   406,   391,   392,   393,   394,   395,   434,     0,
       0,   432,   433,   436,   437,     0,   421,   422,   424,   425,
     426,   427,   428,   429,   430,   431,   260,   262,   257,     0,
     255,   258,   259,     0,   625,   627,     0,   630,     0,     0,
     634,   638,     0,     0,   642,   649,   623,   621,   622,     0,
     604,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,     0,   676,   678,   669,
       0,     0,   665,   667,   668,    48,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    59,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,     0,     0,     0,   140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   289,     0,
       0,   449,     0,     0,     0,     0,     0,     0,   474,     0,
       0,     0,     0,     0,     0,     0,   504,     0,   374,     0,
       0,     0,     0,     0,     0,     0,   382,     0,     0,     0,
       0,   419,     0,     0,     0,     0,   254,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   603,     0,   675,     0,     0,     0,   664,    52,    45,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,     0,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,     0,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   584,     0,     0,     0,     0,     0,     0,
      75,     0,   150,   142,     0,     0,     0,     0,     0,   335,
     336,     0,     0,     0,   291,     0,   451,     0,   490,     0,
     493,   494,   476,     0,     0,     0,     0,     0,     0,     0,
     508,     0,     0,   398,     0,     0,     0,   409,   386,     0,
     438,   439,   423,     0,     0,   256,   624,     0,     0,   629,
       0,   632,   633,     0,     0,   640,   641,     0,     0,   605,
     677,     0,   671,   666,     0,     0,     0,   656,   658,   660,
     121,     0,     0,     0,     0,   157,   135,   282,   375,   412,
      42,   462,   464,   331,   332,   333,   334,   330,   339,     0,
      49,     0,     0,     0,   497,   247,     0,     0,     0,   599,
       0,   652,   654,     0,    53,   149,   442,   467,   320,   322,
     324,   328,   326,     0,   460,   489,   492,   533,   521,   523,
     525,   527,   529,   531,   401,   200,   405,   403,   408,   435,
     261,   263,   626,   628,   631,   636,   637,   635,   639,   644,
     645,   646,   647,   648,   643,   650,   157,    46,     0,     0,
       0,     0,   186,   192,   194,   196,     0,     0,     0,     0,
       0,   210,     0,     0,   213,   215,   217,     0,     0,     0,
       0,   185,     0,   163,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   177,   184,   178,   179,   180,   175,
     176,   181,   182,   183,     0,   161,     0,   158,   159,   286,
       0,   283,   284,   379,     0,   376,   377,   416,     0,   413,
     414,   343,     0,   340,   341,   232,   233,     0,   228,   230,
     231,     0,   241,   242,   238,     0,   236,   239,   240,   224,
       0,   221,   223,   544,     0,   542,   501,     0,   498,   499,
     251,     0,   248,   249,     0,     0,     0,     0,     0,     0,
       0,   266,   268,   269,   270,   271,   272,   273,   574,   580,
       0,     0,     0,   573,   570,   571,   572,     0,   563,   565,
     568,   566,   567,   569,   594,   596,   593,   591,   592,     0,
     587,   589,   590,     0,   683,     0,   681,    55,   446,     0,
     443,   444,   471,     0,   468,   469,   538,   537,     0,   536,
       0,    71,   673,   662,   138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,   154,     0,   156,     0,
       0,   281,     0,   383,   372,     0,   420,   411,     0,     0,
     338,     0,     0,   227,   244,     0,   235,     0,     0,   220,
     546,     0,   541,   505,   496,     0,     0,   246,     0,     0,
       0,     0,     0,     0,     0,     0,   265,     0,     0,     0,
       0,     0,     0,   562,     0,     0,     0,   586,   601,     0,
       0,   680,    57,     0,    56,     0,   441,     0,     0,   466,
       0,     0,   535,   670,     0,     0,     0,     0,   198,   201,
     202,   203,   204,     0,   212,   205,     0,     0,     0,   207,
     208,   209,   206,   164,     0,   160,     0,   285,     0,   378,
       0,   415,   370,   358,   359,   360,   362,   363,   364,   351,
     352,   367,   368,   369,   347,   348,   349,   350,   356,   357,
     355,   361,     0,   345,   353,   365,   366,   354,   342,   229,
     237,     0,   222,   558,     0,   556,   557,   553,   554,   555,
       0,   547,   548,   550,   551,   552,   543,     0,   500,     0,
     250,   274,   275,   276,   277,   278,   279,   267,     0,     0,
     579,   582,   583,   564,     0,     0,   588,   697,     0,   695,
     693,   687,   691,   692,     0,   685,   689,   690,   688,   682,
      54,     0,     0,   445,     0,   470,     0,   188,   189,   190,
     191,   187,   193,   195,   197,   211,   214,   216,   218,   162,
     287,   380,   417,     0,   344,   225,     0,     0,   545,     0,
     502,   252,   576,   577,   578,   575,   581,   595,   597,     0,
       0,     0,     0,   684,    58,   447,   472,   539,   346,     0,
     560,   549,     0,   694,     0,   686,   559,     0,   696,   701,
       0,   699,     0,     0,   698,   710,     0,     0,     0,   715,
       0,   703,   705,   706,   707,   708,   709,   700,     0,     0,
       0,     0,     0,     0,   702,     0,   712,   713,   714,     0,
     704,   711,   716
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,    11,  -877,  -507,
    -877,   325,  -877,  -877,  -877,  -877,   248,  -877,  -529,  -877,
    -877,  -877,   -74,  -877,  -877,  -877,   515,  -877,  -877,  -877,
    -877,   274,   484,  -877,  -877,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,     3,     7,    10,    15,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,   272,   487,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,   207,  -877,    34,  -877,  -626,
      40,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,   -21,  -877,  -654,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,    17,  -877,  -877,  -877,  -877,  -877,
      24,  -645,  -877,  -877,  -877,  -877,    22,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,    13,  -877,  -877,  -877,    12,
     444,  -877,  -877,  -877,  -877,  -877,  -877,  -877,     8,  -877,
    -877,  -877,  -877,  -877,  -877,  -876,  -877,  -877,  -877,    46,
    -877,  -877,  -877,    42,   488,  -877,  -877,  -874,  -877,  -873,
    -877,   -11,  -877,    -5,  -877,    18,  -877,  -877,  -877,  -871,
    -877,  -877,  -877,  -877,    35,  -877,  -877,  -142,   871,  -877,
    -877,  -877,  -877,  -877,    49,  -877,  -877,  -877,    53,  -877,
     476,  -877,   -69,  -877,  -877,  -877,  -877,  -877,   -66,  -877,
    -877,  -877,  -877,  -877,   -58,  -877,  -877,  -877,    47,  -877,
    -877,  -877,    51,  -877,   485,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,     1,  -877,  -877,  -877,
       4,   500,  -877,  -877,   -53,  -877,   -29,  -877,  -877,  -877,
    -877,  -877,     2,  -877,  -877,  -877,     6,   494,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,   -62,  -877,  -877,  -877,    41,
    -877,  -877,  -877,    48,  -877,   493,   282,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -870,  -877,  -877,  -877,  -877,  -877,  -877,  -877,    55,  -877,
    -877,  -877,  -130,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
      32,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,    27,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,   308,   483,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,   -73,  -877,
     -51,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,  -877,   340,   496,  -877,  -877,  -877,  -877,  -877,  -877,
    -877,   349,   497,   -44,  -877,  -877,    33,  -877,  -877,  -128,
    -877,  -877,  -877,  -877,  -877,  -877,  -151,  -877,  -877,  -167,
    -877,  -877,  -877,  -877,  -877,  -877,  -877
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   651,    92,    93,    43,    72,    89,    90,   675,   857,
     953,   954,   741,    45,    74,   101,   102,   103,   390,    47,
      75,   152,   153,   154,   398,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   416,   168,
     169,   400,    49,    76,   200,   201,   202,   443,   203,   170,
     401,   171,   402,   172,   403,   766,   767,   768,   897,   742,
     743,   744,   875,  1081,   745,   876,   746,   877,   747,   878,
     748,   749,   480,   750,   751,   752,   753,   754,   755,   756,
     757,   758,   759,   884,   760,   761,   887,   762,   888,   763,
     889,   173,   428,   800,   801,   802,   917,   174,   425,   787,
     788,   789,   790,   175,   427,   795,   796,   797,   798,   176,
     426,   177,   431,   811,   812,   813,   926,    65,    84,   339,
     340,   341,   493,   342,   494,   178,   432,   820,   821,   822,
     823,   824,   825,   826,   827,   179,   418,   770,   771,   772,
     900,    51,    77,   228,   229,   230,   449,   231,   450,   232,
     451,   233,   455,   234,   454,   180,   423,   657,   236,   237,
     181,   424,   782,   783,   784,   909,  1012,  1013,   182,   419,
      59,    81,   774,   775,   776,   903,    61,    82,   304,   305,
     306,   307,   308,   309,   310,   479,   311,   483,   312,   482,
     313,   314,   484,   315,   183,   420,   778,   779,   780,   906,
      63,    83,   325,   326,   327,   328,   329,   488,   330,   331,
     332,   333,   239,   447,   859,   860,   861,   955,    53,    78,
     250,   251,   252,   459,   184,   421,   185,   422,   242,   448,
     863,   864,   865,   958,    55,    79,   266,   267,   268,   462,
     269,   270,   464,   271,   272,   186,   430,   807,   808,   809,
     923,    57,    80,   284,   285,   286,   287,   470,   288,   471,
     289,   472,   290,   473,   291,   474,   292,   475,   293,   469,
     244,   456,   868,   869,   961,   187,   429,   804,   805,   920,
    1030,  1031,  1032,  1033,  1034,  1096,  1035,   188,   433,   837,
     838,   839,   937,  1105,   840,   841,   938,   842,   843,   189,
     190,   435,   849,   850,   851,   944,   852,   945,   191,   436,
     192,   437,    67,    85,   359,   360,   361,   362,   498,   363,
     499,   364,   365,   501,   366,   367,   368,   504,   707,   369,
     505,   370,   371,   372,   508,   714,   373,   509,   193,   438,
     194,   439,   104,   392,   105,   393,   106,   394,   195,   399,
      71,    87,   381,   382,   383,   514,   384,   107,   391,    69,
      86,   376,   377,   196,   440,   855,   856,   949,  1064,  1065,
    1066,  1067,  1111,  1068,  1109,  1130,  1131,  1132,  1140,  1141,
    1142,  1148,  1143,  1144,  1145,  1146,  1152
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   151,   199,   216,   246,   260,   280,   217,   302,   321,
     338,   356,   374,   834,   323,   243,   794,   324,   764,   238,
     249,   263,   281,   204,   240,   253,   264,   282,    40,   316,
     334,   218,   357,  1005,   375,  1006,  1007,   219,  1011,  1017,
      94,   220,   378,   650,    32,   197,   198,   205,   241,   254,
     265,   283,   681,   317,   335,   221,   358,    44,   650,    46,
     222,   303,   322,   223,   687,   688,   689,   247,   261,   785,
     792,   785,   793,   248,   262,    33,   274,    34,    48,    35,
     224,   336,   337,   866,   225,    50,   912,   226,   396,   913,
     108,   109,   227,   397,   110,   235,   441,   111,   112,   113,
     445,   442,   295,   130,    91,   446,   457,   131,   132,   131,
     132,   458,   653,   654,   655,   656,   255,   256,   257,   258,
     259,   131,   132,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     213,    52,   296,   214,   297,   298,   828,   460,   299,   300,
     301,   786,   461,   915,    99,   727,   916,   131,   132,   131,
     132,   844,   845,    54,   133,  1077,  1078,  1079,  1080,   134,
     135,   136,   137,   138,   467,   139,   379,   380,  1135,   468,
     140,  1136,  1137,  1138,  1139,   495,    95,   130,   296,   141,
     496,   130,   142,   336,   337,   510,    96,    97,    98,   143,
     511,    56,   245,   131,   132,   131,   132,   144,   145,   131,
     132,   146,   147,    99,    99,    99,    58,  1005,    60,  1006,
    1007,   296,  1011,  1017,   512,  1023,  1024,    99,   213,   513,
     516,   214,   441,   148,   149,   517,   150,   871,   131,   132,
     709,   710,   711,   712,   921,   705,   706,   922,   512,   829,
     830,   831,   832,   872,    36,    37,    38,    39,    62,   516,
      64,   445,   894,    99,   873,    99,   874,   895,   894,   918,
     794,   984,   950,   896,   919,   951,   129,   713,   814,   815,
     816,   817,   818,   819,   722,    66,    68,    70,   834,   723,
     724,   725,   726,   727,   728,   729,   730,   731,   732,   733,
     734,   735,   736,   737,   738,   739,   740,   935,   942,    99,
     150,    99,   936,   943,   946,    99,   385,   386,  1057,   947,
    1058,  1059,   100,   387,   296,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,  1133,   510,   894,  1134,
     457,   130,   948,  1089,    99,  1090,   388,  1093,   389,   495,
    1112,   206,  1094,   207,  1101,  1113,  1102,  1103,  1104,   131,
     132,   208,   209,   210,   211,   212,   133,   151,   460,   467,
    1153,   199,   395,  1115,  1116,  1154,   404,   405,   213,   406,
     407,   214,   140,   216,   408,   409,   246,   217,   410,   215,
     411,   412,   204,   260,   413,   243,   414,   518,   519,   238,
     415,   417,   249,   280,   240,   533,   434,   253,   444,   263,
     452,   218,   453,   302,   264,   463,   205,   219,   321,   281,
     465,   220,   466,   323,   282,   476,   324,   477,   241,   478,
     481,   254,   485,   486,   316,   221,   356,   374,   265,   334,
     222,   487,   491,   223,   520,   489,   490,    99,   283,   247,
     492,   541,   534,   497,   500,   248,   261,   357,   317,   375,
     224,   130,   262,   335,   225,    99,   303,   226,   378,   502,
     535,   322,   227,   503,   506,   235,   507,   515,   521,   131,
     132,   358,   522,   523,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   524,   525,   273,   128,   527,
     130,   296,   528,   274,   275,   276,   277,   278,   279,   296,
     318,   297,   298,   319,   320,   529,   530,   531,   131,   132,
     532,   209,   210,   545,   212,   133,   131,   132,   536,   546,
     547,   548,   549,   537,   637,   638,   639,   213,   538,   539,
     214,   540,   550,   542,   131,   132,   543,   544,   215,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   151,   563,   564,   565,   566,   567,   568,   199,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   569,    99,   571,   574,   575,   204,
     572,   576,   378,   833,   846,   577,   356,   374,   578,   579,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   205,   835,   847,   580,   357,   581,   375,
     148,   149,   582,   583,    99,   701,   585,   587,   588,   589,
     590,   591,    99,   593,   594,   595,   596,   597,   836,   848,
     598,   358,   599,   601,   602,   717,   603,   604,   605,   606,
      99,   607,   609,   613,   610,   611,   614,   617,   616,   618,
     619,   620,   621,   623,   624,   622,   627,   628,   625,   626,
     631,   632,   634,   640,   635,   968,   636,   641,   642,   643,
     644,   645,   647,   646,   648,   649,   652,   658,    34,   659,
     660,   661,   671,   663,   662,   664,   665,   799,   672,   666,
     667,   668,   670,   673,   674,   676,   677,   678,   679,   680,
     683,   716,   765,   682,   684,   685,   686,   690,   691,   692,
     693,   694,   708,   695,   696,   697,   698,   699,   700,   769,
     773,   777,   781,   803,   806,   810,   854,   858,   862,   879,
     880,   702,   703,   881,   882,   883,   885,   886,   704,   715,
     890,   891,   892,   893,   899,   952,   898,   902,   901,   904,
     905,   907,   908,   911,   910,   969,   925,   914,   924,   928,
     927,   929,   930,   931,   932,   933,   934,   939,   940,   941,
     957,   970,   956,   960,   959,   964,   971,   962,   963,   965,
     966,   967,   972,   973,   974,   975,   976,   977,   978,   981,
     979,   980,   982,  1021,  1048,  1041,  1042,  1049,  1054,  1043,
    1055,  1044,  1045,  1046,  1070,  1071,  1127,  1076,  1091,  1050,
    1051,  1097,  1052,  1092,  1098,  1082,   216,  1099,  1100,   302,
     217,  1083,   321,  1110,  1084,   992,  1119,   323,   243,   993,
     324,  1120,   238,  1122,  1124,  1085,  1025,   240,  1086,   280,
     316,  1014,   338,   334,   218,  1129,  1015,  1149,  1087,  1088,
     219,  1150,  1027,   994,   220,   281,  1151,  1028,   833,   995,
     282,   241,   846,   996,   317,  1060,  1155,   335,   221,  1159,
    1016,   246,   303,   222,   260,   322,   223,   997,  1004,   835,
     669,  1029,   998,   847,   283,   999,  1062,   249,  1008,  1026,
     263,  1095,   253,   224,  1009,   264,  1123,   225,   791,   718,
     226,   526,  1000,   836,   721,   227,  1001,   848,   235,  1002,
    1063,  1106,  1107,   870,  1003,   570,   254,  1010,  1061,   265,
    1157,  1156,   573,   985,   983,  1022,  1019,  1020,  1039,   615,
    1108,  1040,   986,  1047,   247,   584,  1018,   261,   987,  1114,
     248,  1118,   294,   262,   989,   991,   988,   990,  1073,  1072,
     586,   592,  1075,   608,  1074,   867,  1038,  1117,  1126,  1121,
     600,  1037,  1128,  1056,  1053,  1158,  1036,   612,   853,  1161,
    1162,   720,  1147,  1069,  1125,   719,  1160,     0,     0,     0,
       0,     0,     0,   629,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   630,
       0,     0,   633,     0,     0,     0,     0,     0,     0,   992,
       0,     0,     0,   993,     0,  1025,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1014,     0,     0,  1060,     0,
    1015,  1027,     0,     0,     0,     0,  1028,   994,     0,     0,
       0,     0,     0,   995,     0,     0,     0,   996,     0,  1062,
       0,     0,     0,     0,  1016,     0,     0,     0,     0,     0,
    1029,   997,  1004,     0,     0,     0,   998,     0,  1026,   999,
       0,     0,  1008,  1063,     0,     0,     0,     0,  1009,     0,
       0,  1061,     0,     0,     0,     0,  1000,     0,     0,     0,
    1001,     0,     0,  1002,     0,     0,     0,     0,  1003,     0,
       0,  1010
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    85,   667,    83,    77,   661,    83,   644,    77,
      78,    79,    80,    76,    77,    78,    79,    80,    17,    82,
      83,    77,    85,   909,    85,   909,   909,    77,   909,   909,
      10,    77,    86,   550,     0,    16,    17,    76,    77,    78,
      79,    80,   581,    82,    83,    77,    85,     7,   565,     7,
      77,    82,    83,    77,   593,   594,   595,    78,    79,   104,
     105,   104,   107,    78,    79,     5,   102,     7,     7,     9,
      77,   111,   112,   109,    77,     7,     3,    77,     3,     6,
      11,    12,    77,     8,    15,    77,     3,    18,    19,    20,
       3,     8,    21,    60,   184,     8,     3,    78,    79,    78,
      79,     8,    86,    87,    88,    89,    73,    74,    75,    76,
      77,    78,    79,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      97,     7,    61,   100,    63,    64,    21,     3,    67,    68,
      69,   184,     8,     3,   184,    30,     6,    78,    79,    78,
      79,   130,   131,     7,    85,    22,    23,    24,    25,    90,
      91,    92,    93,    94,     3,    96,    13,    14,   159,     8,
     101,   162,   163,   164,   165,     3,   156,    60,    61,   110,
       8,    60,   113,   111,   112,     3,   166,   167,   168,   120,
       8,     7,    71,    78,    79,    78,    79,   128,   129,    78,
      79,   132,   133,   184,   184,   184,     7,  1093,     7,  1093,
    1093,    61,  1093,  1093,     3,    98,    99,   184,    97,     8,
       3,   100,     3,   154,   155,     8,   157,     8,    78,    79,
     150,   151,   152,   153,     3,   147,   148,     6,     3,   124,
     125,   126,   127,     8,   184,   185,   186,   187,     7,     3,
       7,     3,     3,   184,     8,   184,     8,     8,     3,     3,
     915,   897,     3,     8,     8,     6,    59,   187,   114,   115,
     116,   117,   118,   119,    21,     7,     7,     7,   942,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,     3,     3,   184,
     157,   184,     8,     8,     3,   184,     6,     3,   158,     8,
     160,   161,   396,     4,    61,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     3,     3,     3,     6,
       3,    60,     8,     8,   184,     8,     8,     3,     3,     3,
       3,    70,     8,    72,     8,     8,   121,   122,   123,    78,
      79,    80,    81,    82,    83,    84,    85,   441,     3,     3,
       3,   445,     4,     8,     8,     8,     4,     4,    97,     4,
       4,   100,   101,   457,     4,     4,   460,   457,     4,   108,
       4,     4,   445,   467,     4,   457,     4,   386,   387,   457,
       4,     4,   460,   477,   457,   185,     4,   460,     4,   467,
       4,   457,     4,   487,   467,     4,   445,   457,   492,   477,
       4,   457,     4,   492,   477,     8,   492,     3,   457,     8,
       4,   460,     4,     8,   487,   457,   510,   510,   467,   492,
     457,     3,     8,   457,   184,     4,     4,   184,   477,   460,
       3,   187,   185,     4,     4,   460,   467,   510,   487,   510,
     457,    60,   467,   492,   457,   184,   487,   457,   512,     4,
     185,   492,   457,     4,     4,   457,     4,     4,     4,    78,
      79,   510,     4,     4,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,     4,     4,    96,    58,     4,
      60,    61,     4,   102,   103,   104,   105,   106,   107,    61,
      62,    63,    64,    65,    66,     4,     4,     4,    78,    79,
       4,    81,    82,     4,    84,    85,    78,    79,   185,   187,
       4,     4,     4,   185,   523,   524,   525,    97,   185,   185,
     100,   185,     4,   186,    78,    79,   186,   185,   108,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   635,   185,     4,     4,     4,     4,     4,   642,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,     4,   184,     4,     4,     4,   642,
     187,     4,   636,   667,   668,     4,   670,   670,     4,   185,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   642,   667,   668,   187,   670,     4,   670,
     154,   155,     4,     4,   184,   614,     4,     4,   185,     4,
     185,   185,   184,     4,     4,     4,     4,     4,   667,   668,
       4,   670,     4,     4,     4,   634,   185,     4,     4,     4,
     184,   187,     4,     4,   187,   187,     4,     4,   187,     4,
     185,     4,   185,     4,     4,   185,     4,     4,   187,   187,
       4,   185,     4,   184,     7,   185,     7,     7,     7,     7,
       7,     5,     5,   184,     5,     5,   184,     5,     7,     5,
       5,     5,   184,     5,     7,     5,     5,    95,   184,     7,
       7,     7,     7,     5,     5,     5,     5,   184,   184,   184,
       7,     5,     7,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   149,   184,   184,   184,   184,   184,   184,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     4,
       4,   184,   184,     4,     4,     4,     4,     4,   184,   184,
       4,     4,     4,     4,     3,   184,     6,     3,     6,     6,
       3,     6,     3,     3,     6,   187,     3,     6,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   185,     6,     3,     6,     4,   187,     8,     6,     4,
       4,     4,   185,     4,   185,   185,     4,     4,     4,   187,
     185,   185,   185,     4,     4,   185,   185,     4,     4,   185,
       4,   185,   185,   185,     6,     3,     5,     4,     8,   185,
     185,     4,   185,     8,     8,   184,   900,     3,     8,   903,
     900,   184,   906,     4,   184,   909,     4,   906,   900,   909,
     906,   187,   900,     4,     4,   184,   920,   900,   184,   923,
     903,   909,   926,   906,   900,     7,   909,     4,   184,   184,
     900,     4,   920,   909,   900,   923,     4,   920,   942,   909,
     923,   900,   946,   909,   903,   949,     4,   906,   900,     4,
     909,   955,   903,   900,   958,   906,   900,   909,   909,   942,
     565,   920,   909,   946,   923,   909,   949,   955,   909,   920,
     958,   184,   955,   900,   909,   958,   185,   900,   660,   635,
     900,   396,   909,   942,   642,   900,   909,   946,   900,   909,
     949,   184,   184,   716,   909,   441,   955,   909,   949,   958,
     185,   187,   445,   899,   894,   918,   912,   915,   926,   495,
     184,   928,   900,   935,   955,   457,   911,   958,   902,   184,
     955,  1093,    81,   958,   905,   908,   903,   906,   957,   955,
     460,   467,   960,   487,   958,   683,   925,   184,   184,  1099,
     477,   923,   184,   946,   942,   185,   921,   492,   670,   184,
     184,   641,  1133,   950,  1112,   636,  1153,    -1,    -1,    -1,
      -1,    -1,    -1,   510,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   512,
      -1,    -1,   516,    -1,    -1,    -1,    -1,    -1,    -1,  1093,
      -1,    -1,    -1,  1093,    -1,  1099,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1093,    -1,    -1,  1112,    -1,
    1093,  1099,    -1,    -1,    -1,    -1,  1099,  1093,    -1,    -1,
      -1,    -1,    -1,  1093,    -1,    -1,    -1,  1093,    -1,  1112,
      -1,    -1,    -1,    -1,  1093,    -1,    -1,    -1,    -1,    -1,
    1099,  1093,  1093,    -1,    -1,    -1,  1093,    -1,  1099,  1093,
      -1,    -1,  1093,  1112,    -1,    -1,    -1,    -1,  1093,    -1,
      -1,  1112,    -1,    -1,    -1,    -1,  1093,    -1,    -1,    -1,
    1093,    -1,    -1,  1093,    -1,    -1,    -1,    -1,  1093,    -1,
      -1,  1093
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
     238,   239,   240,   241,   242,   243,   244,   245,   247,   248,
     257,   259,   261,   299,   305,   311,   317,   319,   333,   343,
     363,   368,   376,   402,   432,   434,   453,   483,   495,   507,
     508,   516,   518,   546,   548,   556,   571,    16,    17,   220,
     252,   253,   254,   256,   432,   434,    70,    72,    80,    81,
      82,    83,    84,    97,   100,   108,   220,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   351,   352,
     353,   355,   357,   359,   361,   363,   366,   367,   402,   420,
     432,   434,   436,   453,   478,    71,   220,   359,   361,   402,
     428,   429,   430,   432,   434,    73,    74,    75,    76,    77,
     220,   359,   361,   402,   432,   434,   444,   445,   446,   448,
     449,   451,   452,    96,   102,   103,   104,   105,   106,   107,
     220,   402,   432,   434,   461,   462,   463,   464,   466,   468,
     470,   472,   474,   476,   376,    21,    61,    63,    64,    67,
      68,    69,   220,   279,   386,   387,   388,   389,   390,   391,
     392,   394,   396,   398,   399,   401,   432,   434,    62,    65,
      66,   220,   279,   390,   396,   410,   411,   412,   413,   414,
     416,   417,   418,   419,   432,   434,   111,   112,   220,   327,
     328,   329,   331,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   220,   432,   434,   522,
     523,   524,   525,   527,   529,   530,   532,   533,   534,   537,
     539,   540,   541,   544,   546,   548,   569,   570,   571,    13,
      14,   560,   561,   562,   564,     6,     3,     4,     8,     3,
     226,   566,   551,   553,   555,     4,     3,     8,   232,   557,
     249,   258,   260,   262,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   246,     4,   344,   377,
     403,   433,   435,   364,   369,   306,   318,   312,   300,   484,
     454,   320,   334,   496,     4,   509,   517,   519,   547,   549,
     572,     3,     8,   255,     4,     3,     8,   421,   437,   354,
     356,   358,     4,     4,   362,   360,   479,     3,     8,   431,
       3,     8,   447,     4,   450,     4,     4,     3,     8,   477,
     465,   467,   469,   471,   473,   475,     8,     3,     8,   393,
     280,     4,   397,   395,   400,     4,     8,     3,   415,     4,
       4,     8,     3,   330,   332,     3,     8,     4,   526,   528,
       4,   531,     4,     4,   535,   538,     4,     4,   542,   545,
       3,     8,     3,     8,   563,     4,     3,     8,   205,   205,
     184,     4,     4,     4,     4,     4,   224,     4,     4,     4,
       4,     4,     4,   185,   185,   185,   185,   185,   185,   185,
     185,   187,   186,   186,   185,     4,   187,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   185,     4,     4,     4,     4,     4,     4,
     230,     4,   187,   253,     4,     4,     4,     4,     4,   185,
     187,     4,     4,     4,   352,     4,   429,     4,   185,     4,
     185,   185,   445,     4,     4,     4,     4,     4,     4,     4,
     463,     4,     4,   185,     4,     4,     4,   187,   388,     4,
     187,   187,   412,     4,     4,   328,   187,     4,     4,   185,
       4,   185,   185,     4,     4,   187,   187,     4,     4,   523,
     570,     4,   185,   561,     4,     7,     7,   205,   205,   205,
     184,     7,     7,     7,     7,     5,   184,     5,     5,     5,
     207,   209,   184,    86,    87,    88,    89,   365,     5,     5,
       5,     5,     7,     5,     5,     5,     7,     7,     7,   209,
       7,   184,   184,     5,     5,   216,     5,     5,   184,   184,
     184,   216,   184,     7,   184,   184,   184,   216,   216,   216,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   205,   184,   184,   184,   147,   148,   536,   149,   150,
     151,   152,   153,   187,   543,   184,     5,   205,   229,   569,
     560,   252,    21,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,   220,   267,   268,   269,   272,   274,   276,   278,   279,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     292,   293,   295,   297,   267,     7,   263,   264,   265,     7,
     345,   346,   347,     7,   380,   381,   382,     7,   404,   405,
     406,     7,   370,   371,   372,   104,   184,   307,   308,   309,
     310,   214,   105,   107,   309,   313,   314,   315,   316,    95,
     301,   302,   303,     7,   485,   486,     7,   455,   456,   457,
       7,   321,   322,   323,   114,   115,   116,   117,   118,   119,
     335,   336,   337,   338,   339,   340,   341,   342,    21,   124,
     125,   126,   127,   220,   281,   432,   434,   497,   498,   499,
     502,   503,   505,   506,   130,   131,   220,   432,   434,   510,
     511,   512,   514,   522,     7,   573,   574,   217,     7,   422,
     423,   424,     7,   438,   439,   440,   109,   464,   480,   481,
     263,     8,     8,     8,     8,   270,   273,   275,   277,     4,
       4,     4,     4,     4,   291,     4,     4,   294,   296,   298,
       4,     4,     4,     4,     3,     8,     8,   266,     6,     3,
     348,     6,     3,   383,     6,     3,   407,     6,     3,   373,
       6,     3,     3,     6,     6,     3,     6,   304,     3,     8,
     487,     3,     6,   458,     6,     3,   324,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   500,   504,     4,
       4,     4,     3,     8,   513,   515,     3,     8,     8,   575,
       3,     6,   184,   218,   219,   425,     6,     3,   441,     6,
       3,   482,     8,     6,     4,     4,     4,     4,   185,   187,
     185,   187,   185,     4,   185,   185,     4,     4,     4,   185,
     185,   187,   185,   268,   267,   265,   351,   347,   386,   382,
     410,   406,   220,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   279,   343,   355,   357,   359,   361,
     363,   367,   374,   375,   402,   432,   434,   478,   372,   308,
     314,     4,   302,    98,    99,   220,   279,   402,   432,   434,
     488,   489,   490,   491,   492,   494,   486,   461,   457,   327,
     323,   185,   185,   185,   185,   185,   185,   336,     4,     4,
     185,   185,   185,   498,     4,     4,   511,   158,   160,   161,
     220,   279,   432,   434,   576,   577,   578,   579,   581,   574,
       6,     3,   428,   424,   444,   440,     4,    22,    23,    24,
      25,   271,   184,   184,   184,   184,   184,   184,   184,     8,
       8,     8,     8,     3,     8,   184,   493,     4,     8,     3,
       8,     8,   121,   122,   123,   501,   184,   184,   184,   582,
       4,   580,     3,     8,   184,     8,     8,   184,   375,     4,
     187,   490,     4,   185,     4,   577,   184,     5,   184,     7,
     583,   584,   585,     3,     6,   159,   162,   163,   164,   165,
     586,   587,   588,   590,   591,   592,   593,   584,   589,     4,
       4,     4,   594,     3,     8,     4,   187,   185,   185,     4,
     587,   184,   184
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
     241,   242,   243,   244,   246,   245,   247,   249,   248,   251,
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
     352,   352,   352,   352,   352,   352,   352,   352,   352,   354,
     353,   356,   355,   358,   357,   360,   359,   362,   361,   364,
     363,   365,   365,   365,   365,   366,   367,   369,   368,   370,
     370,   371,   371,   373,   372,   374,   374,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   377,   376,   379,   378,   380,   380,   381,   381,   383,
     382,   385,   384,   386,   386,   387,   387,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   389,   390,   391,
     393,   392,   395,   394,   397,   396,   398,   400,   399,   401,
     403,   402,   404,   404,   405,   405,   407,   406,   409,   408,
     410,   410,   411,   411,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   413,   415,   414,   416,   417,   418,   419,
     421,   420,   422,   422,   423,   423,   425,   424,   427,   426,
     428,   428,   429,   429,   429,   429,   429,   429,   429,   431,
     430,   433,   432,   435,   434,   437,   436,   438,   438,   439,
     439,   441,   440,   443,   442,   444,   444,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   447,   446,
     448,   450,   449,   451,   452,   454,   453,   455,   455,   456,
     456,   458,   457,   460,   459,   461,   461,   462,   462,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     465,   464,   467,   466,   469,   468,   471,   470,   473,   472,
     475,   474,   477,   476,   479,   478,   480,   480,   482,   481,
     484,   483,   485,   485,   487,   486,   488,   488,   489,   489,
     490,   490,   490,   490,   490,   490,   490,   491,   493,   492,
     494,   496,   495,   497,   497,   498,   498,   498,   498,   498,
     498,   498,   498,   498,   500,   499,   501,   501,   501,   502,
     504,   503,   505,   506,   507,   509,   508,   510,   510,   511,
     511,   511,   511,   511,   513,   512,   515,   514,   517,   516,
     519,   518,   521,   520,   522,   522,   523,   523,   523,   523,
     523,   523,   523,   523,   523,   523,   523,   523,   523,   523,
     523,   523,   523,   523,   524,   526,   525,   528,   527,   529,
     531,   530,   532,   533,   535,   534,   536,   536,   538,   537,
     539,   540,   542,   541,   543,   543,   543,   543,   543,   545,
     544,   547,   546,   549,   548,   551,   550,   553,   552,   555,
     554,   557,   556,   559,   558,   560,   560,   561,   561,   563,
     562,   564,   566,   565,   568,   567,   569,   569,   570,   572,
     571,   573,   573,   575,   574,   576,   576,   577,   577,   577,
     577,   577,   577,   577,   578,   580,   579,   582,   581,   583,
     583,   585,   584,   586,   586,   587,   587,   587,   587,   587,
     589,   588,   590,   591,   592,   594,   593
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
       3,     3,     3,     3,     0,     4,     3,     0,     6,     0,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     0,
       6,     3,     0,     6,     0,     4,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
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
  "\"server-tag\"", "\"enable-reconfiguration\"", "\"subnet6\"",
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
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "decline_probation_period", "server_tag", "$@23",
  "enable_reconfiguration", "interfaces_config", "$@24", "sub_interfaces6",
  "$@25", "interfaces_config_params", "interfaces_config_param",
  "interfaces_list", "$@26", "re_detect", "lease_database", "$@27",
  "hosts_database", "$@28", "hosts_databases", "$@29", "database_list",
  "not_empty_database_list", "database", "$@30", "database_map_params",
  "database_map_param", "database_type", "$@31", "db_type", "user", "$@32",
  "password", "$@33", "host", "$@34", "port", "name", "$@35", "persist",
  "lfc_interval", "readonly", "connect_timeout", "reconnect_wait_time",
  "max_row_errors", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@36", "max_reconnect_tries", "keyspace", "$@37",
  "consistency", "$@38", "serial_consistency", "$@39", "sanity_checks",
  "$@40", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@41", "mac_sources", "$@42", "mac_sources_list", "mac_sources_value",
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
     547,   552,   557,   562,   567,   567,   575,   580,   580,   591,
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
    1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,  1155,
    1155,  1163,  1163,  1171,  1171,  1179,  1179,  1187,  1187,  1197,
    1197,  1204,  1205,  1206,  1207,  1210,  1215,  1223,  1223,  1234,
    1235,  1239,  1240,  1243,  1243,  1251,  1252,  1255,  1256,  1257,
    1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,
    1268,  1269,  1270,  1271,  1272,  1273,  1274,  1275,  1276,  1277,
    1278,  1285,  1285,  1298,  1298,  1307,  1308,  1311,  1312,  1317,
    1317,  1332,  1332,  1346,  1347,  1350,  1351,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,  1361,  1362,  1363,  1366,  1368,  1373,
    1375,  1375,  1383,  1383,  1391,  1391,  1399,  1401,  1401,  1409,
    1418,  1418,  1430,  1431,  1436,  1437,  1442,  1442,  1454,  1454,
    1466,  1467,  1472,  1473,  1478,  1479,  1480,  1481,  1482,  1483,
    1484,  1485,  1486,  1489,  1491,  1491,  1499,  1501,  1503,  1508,
    1516,  1516,  1528,  1529,  1532,  1533,  1536,  1536,  1546,  1546,
    1555,  1556,  1559,  1560,  1561,  1562,  1563,  1564,  1565,  1568,
    1568,  1576,  1576,  1601,  1601,  1631,  1631,  1643,  1644,  1647,
    1648,  1651,  1651,  1663,  1663,  1675,  1676,  1679,  1680,  1681,
    1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1692,  1692,
    1700,  1705,  1705,  1713,  1718,  1726,  1726,  1736,  1737,  1740,
    1741,  1744,  1744,  1753,  1753,  1762,  1763,  1766,  1767,  1771,
    1772,  1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,
    1784,  1784,  1794,  1794,  1804,  1804,  1812,  1812,  1820,  1820,
    1828,  1828,  1836,  1836,  1849,  1849,  1859,  1860,  1863,  1863,
    1874,  1874,  1884,  1885,  1888,  1888,  1898,  1899,  1902,  1903,
    1906,  1907,  1908,  1909,  1910,  1911,  1912,  1915,  1917,  1917,
    1925,  1933,  1933,  1945,  1946,  1949,  1950,  1951,  1952,  1953,
    1954,  1955,  1956,  1957,  1960,  1960,  1967,  1968,  1969,  1972,
    1977,  1977,  1985,  1990,  1997,  2004,  2004,  2014,  2015,  2018,
    2019,  2020,  2021,  2022,  2025,  2025,  2033,  2033,  2043,  2043,
    2083,  2083,  2095,  2095,  2105,  2106,  2109,  2110,  2111,  2112,
    2113,  2114,  2115,  2116,  2117,  2118,  2119,  2120,  2121,  2122,
    2123,  2124,  2125,  2126,  2129,  2134,  2134,  2142,  2142,  2150,
    2155,  2155,  2163,  2168,  2173,  2173,  2181,  2182,  2185,  2185,
    2193,  2198,  2203,  2203,  2211,  2214,  2217,  2220,  2223,  2229,
    2229,  2237,  2237,  2245,  2245,  2255,  2255,  2262,  2262,  2269,
    2269,  2278,  2278,  2289,  2289,  2299,  2300,  2304,  2305,  2308,
    2308,  2318,  2328,  2328,  2338,  2338,  2349,  2350,  2354,  2358,
    2358,  2370,  2371,  2375,  2375,  2383,  2384,  2387,  2388,  2389,
    2390,  2391,  2392,  2393,  2396,  2401,  2401,  2409,  2409,  2419,
    2420,  2423,  2423,  2431,  2432,  2435,  2436,  2437,  2438,  2439,
    2442,  2442,  2450,  2455,  2460,  2465,  2465
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
#line 5306 "dhcp6_parser.cc"

#line 2473 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
