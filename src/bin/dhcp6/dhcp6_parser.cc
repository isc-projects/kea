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
      case 204: // value
      case 208: // map_value
      case 269: // db_type
      case 363: // hr_mode
      case 499: // duid_type
      case 534: // ncr_protocol_value
      case 541: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 186: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 185: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 184: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 183: // "constant string"
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
      case 204: // value
      case 208: // map_value
      case 269: // db_type
      case 363: // hr_mode
      case 499: // duid_type
      case 534: // ncr_protocol_value
      case 541: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 186: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 185: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 184: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 183: // "constant string"
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
      case 204: // value
      case 208: // map_value
      case 269: // db_type
      case 363: // hr_mode
      case 499: // duid_type
      case 534: // ncr_protocol_value
      case 541: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 186: // "boolean"
        value.move< bool > (that.value);
        break;

      case 185: // "floating point"
        value.move< double > (that.value);
        break;

      case 184: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 183: // "constant string"
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
      case 183: // "constant string"
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 405 "dhcp6_parser.cc"
        break;

      case 184: // "integer"
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 411 "dhcp6_parser.cc"
        break;

      case 185: // "floating point"
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case 186: // "boolean"
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case 204: // value
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case 208: // map_value
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case 269: // db_type
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case 363: // hr_mode
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case 499: // duid_type
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case 534: // ncr_protocol_value
#line 262 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case 541: // replace_client_name_value
#line 262 "dhcp6_parser.yy"
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
      case 204: // value
      case 208: // map_value
      case 269: // db_type
      case 363: // hr_mode
      case 499: // duid_type
      case 534: // ncr_protocol_value
      case 541: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 186: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 185: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 184: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 183: // "constant string"
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
#line 271 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 731 "dhcp6_parser.cc"
    break;

  case 4:
#line 272 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 737 "dhcp6_parser.cc"
    break;

  case 6:
#line 273 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 743 "dhcp6_parser.cc"
    break;

  case 8:
#line 274 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 749 "dhcp6_parser.cc"
    break;

  case 10:
#line 275 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.SUBNET6; }
#line 755 "dhcp6_parser.cc"
    break;

  case 12:
#line 276 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 761 "dhcp6_parser.cc"
    break;

  case 14:
#line 277 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 767 "dhcp6_parser.cc"
    break;

  case 16:
#line 278 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 773 "dhcp6_parser.cc"
    break;

  case 18:
#line 279 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 779 "dhcp6_parser.cc"
    break;

  case 20:
#line 280 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 785 "dhcp6_parser.cc"
    break;

  case 22:
#line 281 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 791 "dhcp6_parser.cc"
    break;

  case 24:
#line 282 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 797 "dhcp6_parser.cc"
    break;

  case 26:
#line 283 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 803 "dhcp6_parser.cc"
    break;

  case 28:
#line 284 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 809 "dhcp6_parser.cc"
    break;

  case 30:
#line 285 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 815 "dhcp6_parser.cc"
    break;

  case 32:
#line 293 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 821 "dhcp6_parser.cc"
    break;

  case 33:
#line 294 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 827 "dhcp6_parser.cc"
    break;

  case 34:
#line 295 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 833 "dhcp6_parser.cc"
    break;

  case 35:
#line 296 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp6_parser.cc"
    break;

  case 36:
#line 297 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp6_parser.cc"
    break;

  case 37:
#line 298 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 851 "dhcp6_parser.cc"
    break;

  case 38:
#line 299 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 857 "dhcp6_parser.cc"
    break;

  case 39:
#line 302 "dhcp6_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 866 "dhcp6_parser.cc"
    break;

  case 40:
#line 307 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 877 "dhcp6_parser.cc"
    break;

  case 41:
#line 312 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 887 "dhcp6_parser.cc"
    break;

  case 42:
#line 318 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 893 "dhcp6_parser.cc"
    break;

  case 45:
#line 325 "dhcp6_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 902 "dhcp6_parser.cc"
    break;

  case 46:
#line 329 "dhcp6_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 912 "dhcp6_parser.cc"
    break;

  case 47:
#line 336 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 921 "dhcp6_parser.cc"
    break;

  case 48:
#line 339 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 929 "dhcp6_parser.cc"
    break;

  case 51:
#line 347 "dhcp6_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 938 "dhcp6_parser.cc"
    break;

  case 52:
#line 351 "dhcp6_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp6_parser.cc"
    break;

  case 53:
#line 358 "dhcp6_parser.yy"
    {
    // List parsing about to start
}
#line 955 "dhcp6_parser.cc"
    break;

  case 54:
#line 360 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 964 "dhcp6_parser.cc"
    break;

  case 57:
#line 369 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 973 "dhcp6_parser.cc"
    break;

  case 58:
#line 373 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp6_parser.cc"
    break;

  case 59:
#line 384 "dhcp6_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 993 "dhcp6_parser.cc"
    break;

  case 60:
#line 394 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1004 "dhcp6_parser.cc"
    break;

  case 61:
#line 399 "dhcp6_parser.yy"
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
#line 422 "dhcp6_parser.yy"
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
#line 429 "dhcp6_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1040 "dhcp6_parser.cc"
    break;

  case 72:
#line 437 "dhcp6_parser.yy"
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1050 "dhcp6_parser.cc"
    break;

  case 73:
#line 441 "dhcp6_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 119:
#line 497 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 120:
#line 499 "dhcp6_parser.yy"
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc"
    break;

  case 121:
#line 505 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1086 "dhcp6_parser.cc"
    break;

  case 122:
#line 510 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1095 "dhcp6_parser.cc"
    break;

  case 123:
#line 515 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 124:
#line 520 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1113 "dhcp6_parser.cc"
    break;

  case 125:
#line 525 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1122 "dhcp6_parser.cc"
    break;

  case 126:
#line 530 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1131 "dhcp6_parser.cc"
    break;

  case 127:
#line 535 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1140 "dhcp6_parser.cc"
    break;

  case 128:
#line 540 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1149 "dhcp6_parser.cc"
    break;

  case 129:
#line 545 "dhcp6_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1158 "dhcp6_parser.cc"
    break;

  case 130:
#line 550 "dhcp6_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1167 "dhcp6_parser.cc"
    break;

  case 131:
#line 555 "dhcp6_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1176 "dhcp6_parser.cc"
    break;

  case 132:
#line 560 "dhcp6_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 133:
#line 565 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 134:
#line 567 "dhcp6_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 135:
#line 573 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 136:
#line 578 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 137:
#line 584 "dhcp6_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 138:
#line 588 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 146:
#line 604 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 147:
#line 609 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 148:
#line 614 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 149:
#line 620 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 150:
#line 625 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "dhcp6_parser.cc"
    break;

  case 151:
#line 632 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 152:
#line 637 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc"
    break;

  case 153:
#line 644 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1327 "dhcp6_parser.cc"
    break;

  case 154:
#line 649 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc"
    break;

  case 159:
#line 662 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1346 "dhcp6_parser.cc"
    break;

  case 160:
#line 666 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1356 "dhcp6_parser.cc"
    break;

  case 184:
#line 699 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1364 "dhcp6_parser.cc"
    break;

  case 185:
#line 701 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 186:
#line 706 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1379 "dhcp6_parser.cc"
    break;

  case 187:
#line 707 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1385 "dhcp6_parser.cc"
    break;

  case 188:
#line 708 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1391 "dhcp6_parser.cc"
    break;

  case 189:
#line 709 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1397 "dhcp6_parser.cc"
    break;

  case 190:
#line 712 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1405 "dhcp6_parser.cc"
    break;

  case 191:
#line 714 "dhcp6_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1415 "dhcp6_parser.cc"
    break;

  case 192:
#line 720 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp6_parser.cc"
    break;

  case 193:
#line 722 "dhcp6_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1433 "dhcp6_parser.cc"
    break;

  case 194:
#line 728 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 195:
#line 730 "dhcp6_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 196:
#line 736 "dhcp6_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 197:
#line 741 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp6_parser.cc"
    break;

  case 198:
#line 743 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1478 "dhcp6_parser.cc"
    break;

  case 199:
#line 749 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1487 "dhcp6_parser.cc"
    break;

  case 200:
#line 754 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1496 "dhcp6_parser.cc"
    break;

  case 201:
#line 759 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1505 "dhcp6_parser.cc"
    break;

  case 202:
#line 764 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1514 "dhcp6_parser.cc"
    break;

  case 203:
#line 769 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1523 "dhcp6_parser.cc"
    break;

  case 204:
#line 774 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 205:
#line 779 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 206:
#line 784 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 207:
#line 789 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1559 "dhcp6_parser.cc"
    break;

  case 208:
#line 794 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1567 "dhcp6_parser.cc"
    break;

  case 209:
#line 796 "dhcp6_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 210:
#line 802 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1586 "dhcp6_parser.cc"
    break;

  case 211:
#line 807 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp6_parser.cc"
    break;

  case 212:
#line 809 "dhcp6_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1604 "dhcp6_parser.cc"
    break;

  case 213:
#line 815 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1612 "dhcp6_parser.cc"
    break;

  case 214:
#line 817 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1622 "dhcp6_parser.cc"
    break;

  case 215:
#line 823 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1630 "dhcp6_parser.cc"
    break;

  case 216:
#line 825 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1640 "dhcp6_parser.cc"
    break;

  case 217:
#line 831 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1651 "dhcp6_parser.cc"
    break;

  case 218:
#line 836 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 222:
#line 846 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 223:
#line 848 "dhcp6_parser.yy"
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
#line 1688 "dhcp6_parser.cc"
    break;

  case 224:
#line 864 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 225:
#line 869 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 230:
#line 882 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1717 "dhcp6_parser.cc"
    break;

  case 231:
#line 887 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 232:
#line 892 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 233:
#line 897 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 239:
#line 911 "dhcp6_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 240:
#line 916 "dhcp6_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 241:
#line 923 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 242:
#line 928 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1784 "dhcp6_parser.cc"
    break;

  case 243:
#line 933 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 244:
#line 938 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1804 "dhcp6_parser.cc"
    break;

  case 249:
#line 951 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1814 "dhcp6_parser.cc"
    break;

  case 250:
#line 955 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1824 "dhcp6_parser.cc"
    break;

  case 251:
#line 961 "dhcp6_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 252:
#line 965 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 258:
#line 980 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1852 "dhcp6_parser.cc"
    break;

  case 259:
#line 982 "dhcp6_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 260:
#line 988 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 261:
#line 990 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1879 "dhcp6_parser.cc"
    break;

  case 262:
#line 996 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1890 "dhcp6_parser.cc"
    break;

  case 263:
#line 1001 "dhcp6_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 272:
#line 1019 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 273:
#line 1024 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 274:
#line 1029 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1927 "dhcp6_parser.cc"
    break;

  case 275:
#line 1034 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 276:
#line 1039 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1945 "dhcp6_parser.cc"
    break;

  case 277:
#line 1044 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 278:
#line 1052 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1965 "dhcp6_parser.cc"
    break;

  case 279:
#line 1057 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1974 "dhcp6_parser.cc"
    break;

  case 284:
#line 1077 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1984 "dhcp6_parser.cc"
    break;

  case 285:
#line 1081 "dhcp6_parser.yy"
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
#line 2010 "dhcp6_parser.cc"
    break;

  case 286:
#line 1103 "dhcp6_parser.yy"
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2020 "dhcp6_parser.cc"
    break;

  case 287:
#line 1107 "dhcp6_parser.yy"
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2030 "dhcp6_parser.cc"
    break;

  case 317:
#line 1148 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2038 "dhcp6_parser.cc"
    break;

  case 318:
#line 1150 "dhcp6_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2048 "dhcp6_parser.cc"
    break;

  case 319:
#line 1156 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 320:
#line 1158 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 321:
#line 1164 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2074 "dhcp6_parser.cc"
    break;

  case 322:
#line 1166 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2084 "dhcp6_parser.cc"
    break;

  case 323:
#line 1172 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2092 "dhcp6_parser.cc"
    break;

  case 324:
#line 1174 "dhcp6_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2102 "dhcp6_parser.cc"
    break;

  case 325:
#line 1180 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 326:
#line 1185 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2122 "dhcp6_parser.cc"
    break;

  case 327:
#line 1190 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2130 "dhcp6_parser.cc"
    break;

  case 328:
#line 1192 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2139 "dhcp6_parser.cc"
    break;

  case 329:
#line 1197 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2145 "dhcp6_parser.cc"
    break;

  case 330:
#line 1198 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2151 "dhcp6_parser.cc"
    break;

  case 331:
#line 1199 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2157 "dhcp6_parser.cc"
    break;

  case 332:
#line 1200 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2163 "dhcp6_parser.cc"
    break;

  case 333:
#line 1203 "dhcp6_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2172 "dhcp6_parser.cc"
    break;

  case 334:
#line 1208 "dhcp6_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2181 "dhcp6_parser.cc"
    break;

  case 335:
#line 1216 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 336:
#line 1221 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 341:
#line 1236 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 342:
#line 1240 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2219 "dhcp6_parser.cc"
    break;

  case 369:
#line 1278 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2230 "dhcp6_parser.cc"
    break;

  case 370:
#line 1283 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 371:
#line 1291 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2248 "dhcp6_parser.cc"
    break;

  case 372:
#line 1294 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 2256 "dhcp6_parser.cc"
    break;

  case 377:
#line 1310 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2266 "dhcp6_parser.cc"
    break;

  case 378:
#line 1314 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 379:
#line 1325 "dhcp6_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2288 "dhcp6_parser.cc"
    break;

  case 380:
#line 1329 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2300 "dhcp6_parser.cc"
    break;

  case 396:
#line 1361 "dhcp6_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2309 "dhcp6_parser.cc"
    break;

  case 398:
#line 1368 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2317 "dhcp6_parser.cc"
    break;

  case 399:
#line 1370 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2327 "dhcp6_parser.cc"
    break;

  case 400:
#line 1376 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 401:
#line 1378 "dhcp6_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2345 "dhcp6_parser.cc"
    break;

  case 402:
#line 1384 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2353 "dhcp6_parser.cc"
    break;

  case 403:
#line 1386 "dhcp6_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2363 "dhcp6_parser.cc"
    break;

  case 405:
#line 1394 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2371 "dhcp6_parser.cc"
    break;

  case 406:
#line 1396 "dhcp6_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2381 "dhcp6_parser.cc"
    break;

  case 407:
#line 1402 "dhcp6_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2390 "dhcp6_parser.cc"
    break;

  case 408:
#line 1411 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2401 "dhcp6_parser.cc"
    break;

  case 409:
#line 1416 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2410 "dhcp6_parser.cc"
    break;

  case 414:
#line 1435 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2420 "dhcp6_parser.cc"
    break;

  case 415:
#line 1439 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2429 "dhcp6_parser.cc"
    break;

  case 416:
#line 1447 "dhcp6_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2439 "dhcp6_parser.cc"
    break;

  case 417:
#line 1451 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 432:
#line 1484 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 433:
#line 1486 "dhcp6_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 436:
#line 1496 "dhcp6_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 437:
#line 1501 "dhcp6_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2484 "dhcp6_parser.cc"
    break;

  case 438:
#line 1509 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2495 "dhcp6_parser.cc"
    break;

  case 439:
#line 1514 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2504 "dhcp6_parser.cc"
    break;

  case 444:
#line 1529 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2514 "dhcp6_parser.cc"
    break;

  case 445:
#line 1533 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2524 "dhcp6_parser.cc"
    break;

  case 446:
#line 1539 "dhcp6_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2534 "dhcp6_parser.cc"
    break;

  case 447:
#line 1543 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2543 "dhcp6_parser.cc"
    break;

  case 457:
#line 1561 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2551 "dhcp6_parser.cc"
    break;

  case 458:
#line 1563 "dhcp6_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2561 "dhcp6_parser.cc"
    break;

  case 459:
#line 1569 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 460:
#line 1571 "dhcp6_parser.yy"
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
#line 2596 "dhcp6_parser.cc"
    break;

  case 461:
#line 1594 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2604 "dhcp6_parser.cc"
    break;

  case 462:
#line 1596 "dhcp6_parser.yy"
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
#line 2633 "dhcp6_parser.cc"
    break;

  case 463:
#line 1624 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2644 "dhcp6_parser.cc"
    break;

  case 464:
#line 1629 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 469:
#line 1644 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2663 "dhcp6_parser.cc"
    break;

  case 470:
#line 1648 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 471:
#line 1656 "dhcp6_parser.yy"
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 472:
#line 1660 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2697 "dhcp6_parser.cc"
    break;

  case 486:
#line 1685 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp6_parser.cc"
    break;

  case 487:
#line 1687 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 488:
#line 1693 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2724 "dhcp6_parser.cc"
    break;

  case 489:
#line 1698 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 490:
#line 1700 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2742 "dhcp6_parser.cc"
    break;

  case 491:
#line 1706 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 492:
#line 1711 "dhcp6_parser.yy"
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2760 "dhcp6_parser.cc"
    break;

  case 493:
#line 1719 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2771 "dhcp6_parser.cc"
    break;

  case 494:
#line 1724 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2780 "dhcp6_parser.cc"
    break;

  case 499:
#line 1737 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2790 "dhcp6_parser.cc"
    break;

  case 500:
#line 1741 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2799 "dhcp6_parser.cc"
    break;

  case 501:
#line 1746 "dhcp6_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2809 "dhcp6_parser.cc"
    break;

  case 502:
#line 1750 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2818 "dhcp6_parser.cc"
    break;

  case 518:
#line 1777 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 519:
#line 1782 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 520:
#line 1787 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 521:
#line 1792 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 522:
#line 1797 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2866 "dhcp6_parser.cc"
    break;

  case 523:
#line 1799 "dhcp6_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2876 "dhcp6_parser.cc"
    break;

  case 524:
#line 1805 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 525:
#line 1807 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 526:
#line 1813 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2902 "dhcp6_parser.cc"
    break;

  case 527:
#line 1815 "dhcp6_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2912 "dhcp6_parser.cc"
    break;

  case 528:
#line 1821 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2920 "dhcp6_parser.cc"
    break;

  case 529:
#line 1823 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2930 "dhcp6_parser.cc"
    break;

  case 530:
#line 1829 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 531:
#line 1834 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2950 "dhcp6_parser.cc"
    break;

  case 532:
#line 1842 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2961 "dhcp6_parser.cc"
    break;

  case 533:
#line 1847 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2970 "dhcp6_parser.cc"
    break;

  case 536:
#line 1856 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2978 "dhcp6_parser.cc"
    break;

  case 537:
#line 1858 "dhcp6_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2988 "dhcp6_parser.cc"
    break;

  case 538:
#line 1867 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2999 "dhcp6_parser.cc"
    break;

  case 539:
#line 1872 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3008 "dhcp6_parser.cc"
    break;

  case 542:
#line 1881 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3018 "dhcp6_parser.cc"
    break;

  case 543:
#line 1885 "dhcp6_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3028 "dhcp6_parser.cc"
    break;

  case 556:
#line 1910 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3036 "dhcp6_parser.cc"
    break;

  case 557:
#line 1912 "dhcp6_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3046 "dhcp6_parser.cc"
    break;

  case 558:
#line 1918 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 559:
#line 1926 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3066 "dhcp6_parser.cc"
    break;

  case 560:
#line 1931 "dhcp6_parser.yy"
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3077 "dhcp6_parser.cc"
    break;

  case 572:
#line 1953 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3085 "dhcp6_parser.cc"
    break;

  case 573:
#line 1955 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc"
    break;

  case 574:
#line 1960 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3100 "dhcp6_parser.cc"
    break;

  case 575:
#line 1961 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3106 "dhcp6_parser.cc"
    break;

  case 576:
#line 1962 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3112 "dhcp6_parser.cc"
    break;

  case 577:
#line 1965 "dhcp6_parser.yy"
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 578:
#line 1970 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp6_parser.cc"
    break;

  case 579:
#line 1972 "dhcp6_parser.yy"
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3139 "dhcp6_parser.cc"
    break;

  case 580:
#line 1978 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3148 "dhcp6_parser.cc"
    break;

  case 581:
#line 1983 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 582:
#line 1990 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3166 "dhcp6_parser.cc"
    break;

  case 583:
#line 1997 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 584:
#line 2002 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3186 "dhcp6_parser.cc"
    break;

  case 592:
#line 2018 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3194 "dhcp6_parser.cc"
    break;

  case 593:
#line 2020 "dhcp6_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3204 "dhcp6_parser.cc"
    break;

  case 594:
#line 2026 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3212 "dhcp6_parser.cc"
    break;

  case 595:
#line 2028 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3222 "dhcp6_parser.cc"
    break;

  case 596:
#line 2036 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp6_parser.cc"
    break;

  case 597:
#line 2038 "dhcp6_parser.yy"
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
#line 3270 "dhcp6_parser.cc"
    break;

  case 598:
#line 2076 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3281 "dhcp6_parser.cc"
    break;

  case 599:
#line 2081 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3292 "dhcp6_parser.cc"
    break;

  case 600:
#line 2088 "dhcp6_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3302 "dhcp6_parser.cc"
    break;

  case 601:
#line 2092 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3312 "dhcp6_parser.cc"
    break;

  case 622:
#line 2122 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3321 "dhcp6_parser.cc"
    break;

  case 623:
#line 2127 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3329 "dhcp6_parser.cc"
    break;

  case 624:
#line 2129 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3339 "dhcp6_parser.cc"
    break;

  case 625:
#line 2135 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3347 "dhcp6_parser.cc"
    break;

  case 626:
#line 2137 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 627:
#line 2143 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 628:
#line 2148 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3374 "dhcp6_parser.cc"
    break;

  case 629:
#line 2150 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 630:
#line 2156 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 631:
#line 2161 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3402 "dhcp6_parser.cc"
    break;

  case 632:
#line 2166 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 633:
#line 2168 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3419 "dhcp6_parser.cc"
    break;

  case 634:
#line 2174 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3425 "dhcp6_parser.cc"
    break;

  case 635:
#line 2175 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3431 "dhcp6_parser.cc"
    break;

  case 636:
#line 2178 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3439 "dhcp6_parser.cc"
    break;

  case 637:
#line 2180 "dhcp6_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 638:
#line 2186 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 639:
#line 2191 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 640:
#line 2196 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3475 "dhcp6_parser.cc"
    break;

  case 641:
#line 2198 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 642:
#line 2204 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3492 "dhcp6_parser.cc"
    break;

  case 643:
#line 2207 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3500 "dhcp6_parser.cc"
    break;

  case 644:
#line 2210 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3508 "dhcp6_parser.cc"
    break;

  case 645:
#line 2213 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3516 "dhcp6_parser.cc"
    break;

  case 646:
#line 2216 "dhcp6_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3525 "dhcp6_parser.cc"
    break;

  case 647:
#line 2222 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3533 "dhcp6_parser.cc"
    break;

  case 648:
#line 2224 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3543 "dhcp6_parser.cc"
    break;

  case 649:
#line 2230 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3551 "dhcp6_parser.cc"
    break;

  case 650:
#line 2232 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3561 "dhcp6_parser.cc"
    break;

  case 651:
#line 2238 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3569 "dhcp6_parser.cc"
    break;

  case 652:
#line 2240 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3579 "dhcp6_parser.cc"
    break;

  case 653:
#line 2248 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3587 "dhcp6_parser.cc"
    break;

  case 654:
#line 2250 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 655:
#line 2255 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 656:
#line 2257 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 657:
#line 2262 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 658:
#line 2264 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 659:
#line 2271 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3641 "dhcp6_parser.cc"
    break;

  case 660:
#line 2276 "dhcp6_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3651 "dhcp6_parser.cc"
    break;

  case 661:
#line 2282 "dhcp6_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3661 "dhcp6_parser.cc"
    break;

  case 662:
#line 2286 "dhcp6_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3670 "dhcp6_parser.cc"
    break;

  case 667:
#line 2301 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3681 "dhcp6_parser.cc"
    break;

  case 668:
#line 2306 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 669:
#line 2311 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 670:
#line 2321 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3710 "dhcp6_parser.cc"
    break;

  case 671:
#line 2326 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3719 "dhcp6_parser.cc"
    break;

  case 672:
#line 2331 "dhcp6_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3729 "dhcp6_parser.cc"
    break;

  case 673:
#line 2335 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 677:
#line 2351 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3748 "dhcp6_parser.cc"
    break;

  case 678:
#line 2356 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 681:
#line 2368 "dhcp6_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 682:
#line 2372 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 692:
#line 2389 "dhcp6_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 693:
#line 2394 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3792 "dhcp6_parser.cc"
    break;

  case 694:
#line 2396 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3802 "dhcp6_parser.cc"
    break;

  case 695:
#line 2402 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 696:
#line 2407 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3822 "dhcp6_parser.cc"
    break;

  case 699:
#line 2416 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3832 "dhcp6_parser.cc"
    break;

  case 700:
#line 2420 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3840 "dhcp6_parser.cc"
    break;

  case 708:
#line 2435 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3848 "dhcp6_parser.cc"
    break;

  case 709:
#line 2437 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3858 "dhcp6_parser.cc"
    break;

  case 710:
#line 2443 "dhcp6_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 711:
#line 2448 "dhcp6_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 712:
#line 2453 "dhcp6_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3885 "dhcp6_parser.cc"
    break;

  case 713:
#line 2458 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 714:
#line 2460 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3903 "dhcp6_parser.cc"
    break;


#line 3907 "dhcp6_parser.cc"

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
     519,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,    39,    70,    52,    69,
      78,   134,   183,   185,   192,   193,   194,   201,   208,   220,
     227,   250,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,    70,  -137,    30,    79,    41,   435,    81,   164,
     268,    24,    43,   275,   -67,   463,   -48,   153,  -878,   154,
     190,   254,   251,   262,  -878,  -878,  -878,  -878,  -878,   265,
    -878,    75,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   278,   279,   285,   311,   315,   327,
     328,   329,   337,   338,   363,   371,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,   375,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   114,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,   381,  -878,   170,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   390,
     391,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,   186,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   206,  -878,
    -878,  -878,  -878,  -878,   399,  -878,   401,   403,  -878,  -878,
    -878,  -878,  -878,  -878,   213,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   260,   319,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   350,  -878,  -878,   405,  -878,  -878,  -878,   408,
    -878,  -878,   370,   384,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   413,   415,  -878,
    -878,  -878,  -878,   414,   395,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   244,  -878,  -878,
    -878,   420,  -878,  -878,   422,  -878,   423,   425,  -878,  -878,
     426,   437,  -878,  -878,  -878,  -878,  -878,   258,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   306,  -878,  -878,  -878,   438,   308,
    -878,  -878,  -878,  -878,    70,    70,  -878,   261,   439,   444,
     445,   446,   458,  -878,    30,  -878,   462,   466,   467,   469,
     470,   471,   283,   292,   293,   307,   312,   313,   314,   316,
     304,   317,   323,   321,   488,   489,   491,   495,   497,   499,
     503,   505,   506,   507,   516,   517,   518,   520,   521,   522,
     523,   339,   524,   525,   526,   528,   529,   532,    79,  -878,
     533,   352,    41,  -878,   535,   539,   540,   541,   542,   364,
     361,   545,   546,   547,   435,  -878,   548,    81,  -878,   549,
     372,   550,   376,   377,   164,  -878,   551,   554,   555,   558,
     559,   561,   562,  -878,   268,  -878,   563,   564,   386,   565,
     567,   568,   387,  -878,    43,   573,   392,   393,  -878,   275,
     576,   577,     4,  -878,   396,   580,   582,   407,   583,   410,
     411,   608,   610,   397,   433,   616,   617,   463,  -878,   -48,
    -878,   618,   456,   153,  -878,  -878,  -878,   637,   635,   636,
      70,    70,    70,  -878,   461,   638,   640,   641,   642,   645,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   468,   647,   648,   649,   651,   472,   158,   656,
     660,   661,   662,   663,   664,   666,   667,   669,   670,  -878,
     672,   651,   673,   485,   490,   676,  -878,   677,  -878,  -878,
     678,   680,   527,   530,   531,  -878,  -878,   677,   534,   695,
    -878,   536,  -878,   537,  -878,   538,  -878,  -878,  -878,   677,
     677,   677,   543,   544,   552,   553,  -878,   556,   557,  -878,
     560,   566,   569,  -878,  -878,   570,  -878,  -878,  -878,   571,
      70,  -878,  -878,   572,   574,  -878,   575,  -878,  -878,    29,
     581,  -878,  -878,    -2,   578,  -878,  -878,   698,  -878,  -878,
      70,    79,   -48,  -878,  -878,  -878,  -878,   153,    41,   264,
     264,   697,  -878,   699,   700,   701,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   702,   -38,    70,   -34,   611,   704,
     705,   708,   159,   125,    35,  -878,   463,  -878,  -878,   709,
    -878,  -878,   711,   715,  -878,  -878,  -878,  -878,  -878,   -56,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,   697,  -878,   309,   310,   318,   320,  -878,  -878,
    -878,  -878,   719,   720,   721,   724,   726,  -878,   727,   728,
    -878,  -878,  -878,   729,   730,   733,   734,  -878,   322,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     326,  -878,   668,   738,  -878,  -878,   736,   741,  -878,  -878,
     739,   743,  -878,  -878,   742,   744,  -878,  -878,   745,   747,
    -878,  -878,  -878,    83,  -878,  -878,  -878,   750,  -878,  -878,
    -878,    90,  -878,  -878,  -878,  -878,   340,  -878,  -878,  -878,
     101,  -878,  -878,   753,   757,  -878,  -878,   758,   760,  -878,
     761,   762,   763,   764,   765,   766,   341,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,   767,   768,   769,  -878,
    -878,  -878,  -878,   347,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   348,  -878,  -878,  -878,   351,
    -878,   136,  -878,   591,  -878,   770,   772,  -878,  -878,   771,
     775,  -878,  -878,  -878,   773,  -878,   774,  -878,  -878,  -878,
    -878,   778,   779,   780,   781,   595,   600,   603,   602,   605,
     786,   607,   609,   788,   790,   791,   612,   613,   614,   615,
     264,  -878,  -878,   264,  -878,   697,   435,  -878,   699,    43,
    -878,   700,   275,  -878,   701,   579,  -878,   702,   -38,  -878,
    -878,   -34,  -878,   794,   611,  -878,    84,   704,  -878,   268,
    -878,   705,   -67,  -878,   708,   619,   620,   621,   622,   623,
     624,   159,  -878,   797,   798,   625,   626,   627,   125,  -878,
     808,   809,    35,  -878,  -878,   127,   709,  -878,  -878,   810,
     811,    81,  -878,   711,   164,  -878,   715,   813,  -878,  -878,
     256,   632,   644,   646,  -878,  -878,  -878,  -878,  -878,   654,
    -878,  -878,   657,   658,   671,  -878,  -878,  -878,  -878,  -878,
     354,  -878,   357,  -878,   812,  -878,   815,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   358,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   674,  -878,  -878,
     814,  -878,  -878,  -878,  -878,  -878,   816,   818,  -878,  -878,
    -878,  -878,  -878,   822,  -878,   373,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,    32,   679,  -878,  -878,  -878,  -878,
     689,   692,  -878,  -878,   828,  -878,  -878,  -878,  -878,  -878,
     374,  -878,  -878,  -878,  -878,  -878,  -878,   703,   383,  -878,
     385,  -878,   714,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,   579,
    -878,  -878,   835,   633,  -878,    84,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,   840,   718,   847,   127,  -878,
    -878,  -878,  -878,  -878,  -878,   722,  -878,  -878,   848,  -878,
     735,  -878,  -878,   897,  -878,  -878,   180,  -878,    67,   897,
    -878,  -878,   851,   903,   906,  -878,   394,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   913,   740,   737,   746,   915,    67,
    -878,   748,  -878,  -878,  -878,   749,  -878,  -878,  -878
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
     696,   708,     0,     0,     0,   713,     0,   701,   703,   704,
     705,   706,   707,   698,     0,     0,     0,     0,     0,     0,
     700,     0,   710,   711,   712,     0,   702,   709,   714
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,    54,  -878,  -480,
    -878,   366,  -878,  -878,  -878,  -878,   272,  -878,  -489,  -878,
    -878,  -878,   -74,  -878,  -878,  -878,   584,  -878,  -878,  -878,
    -878,   298,   496,  -878,  -878,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,     3,     7,    10,    15,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,   295,   493,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   224,  -878,    42,  -878,  -622,    48,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     -21,  -878,  -650,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,    25,  -878,  -878,  -878,  -878,  -878,    33,
    -641,  -878,  -878,  -878,  -878,    31,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,    20,  -878,  -878,  -878,    23,   455,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,    17,  -878,  -878,
    -878,  -878,  -878,  -878,  -877,  -878,  -878,  -878,    53,  -878,
    -878,  -878,    56,   500,  -878,  -878,  -872,  -878,  -870,  -878,
     -11,  -878,    -5,  -878,    18,  -878,  -878,  -878,  -869,  -878,
    -878,  -878,  -878,    46,  -878,  -878,  -139,   874,  -878,  -878,
    -878,  -878,  -878,    55,  -878,  -878,  -878,    58,  -878,   474,
    -878,   -69,  -878,  -878,  -878,  -878,  -878,   -66,  -878,  -878,
    -878,  -878,  -878,   -58,  -878,  -878,  -878,    57,  -878,  -878,
    -878,    60,  -878,   475,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,     6,  -878,  -878,  -878,     9,
     508,  -878,  -878,   -53,  -878,   -29,  -878,  -878,  -878,  -878,
    -878,    11,  -878,  -878,  -878,    12,   504,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   -62,  -878,  -878,  -878,    49,  -878,
    -878,  -878,    44,  -878,   498,   290,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -867,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,    59,  -878,  -878,
    -878,  -124,  -878,  -878,  -878,  -878,  -878,  -878,  -878,    36,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,    37,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,   324,   473,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,   -73,  -878,   -51,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   336,   464,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
     343,   476,   -44,  -878,  -878,    38,  -878,  -878,  -127,  -878,
    -878,  -878,  -878,  -878,  -878,  -147,  -878,  -878,  -166,  -878,
    -878,  -878,  -878,  -878,  -878,  -878
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
    1063,  1107,  1064,  1105,  1126,  1127,  1128,  1136,  1137,  1138,
    1144,  1139,  1140,  1141,  1142,  1148
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   150,   197,   214,   244,   258,   278,   215,   300,   319,
     336,   354,   372,   830,   321,   241,   790,   322,   760,   236,
     247,   261,   279,   202,   238,   251,   262,   280,  1001,   314,
     332,   216,   355,  1002,   373,  1003,  1007,   217,  1013,    32,
      94,   218,   376,   334,   335,   272,    91,   203,   239,   252,
     263,   281,   862,   315,   333,   219,   356,   195,   196,    44,
     220,   301,   320,   221,   293,   781,   646,   245,   259,   781,
     788,    40,   789,   246,   260,    33,    46,    34,   394,    35,
     222,   646,   128,   395,   223,    48,   908,   224,   677,   909,
     108,   109,   225,   911,   110,   233,   912,   111,   112,   113,
     683,   684,   685,   294,   917,   295,   296,   918,   149,   297,
     298,   299,   130,   131,   334,   335,    99,   438,   130,   131,
     130,   131,   439,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   946,
     129,    50,   947,   129,   294,   782,   824,   705,   706,   707,
     708,   243,  1098,  1099,  1100,   723,   130,   131,   130,   131,
     383,   130,   131,   132,   840,   841,   377,   378,   133,   134,
     135,   136,   137,   442,   138,   701,   702,   211,   443,   139,
     212,  1019,  1020,  1129,   709,    95,  1130,   294,   140,   454,
      52,   141,    54,   384,   455,    96,    97,    98,   142,    56,
      58,    60,   130,   131,   130,   131,   143,   144,    62,   457,
     145,   146,  1001,    99,   458,    64,   464,  1002,    99,  1003,
    1007,   465,  1013,   129,    99,  1131,    99,    66,  1132,  1133,
    1134,  1135,   147,   148,    68,   149,   253,   254,   255,   256,
     257,   130,   131,   649,   650,   651,   652,   492,   825,   826,
     827,   828,   493,    36,    37,    38,    39,    70,   385,   386,
     211,   507,    99,   212,    99,   387,   508,    99,   473,   393,
     790,   980,   810,   811,   812,   813,   814,   815,  1073,  1074,
    1075,  1076,   402,   403,  1053,   718,  1054,  1055,   830,   404,
     719,   720,   721,   722,   723,   724,   725,   726,   727,   728,
     729,   730,   731,   732,   733,   734,   735,   736,    99,   509,
      99,   513,   438,   509,   510,   405,   514,   867,   868,   406,
     100,   513,   474,   442,   294,   890,   869,   129,   870,   890,
     891,   407,   408,   409,   892,   294,   316,   295,   296,   317,
     318,   410,   411,   914,   931,   130,   131,    99,   915,   932,
     938,   942,   130,   131,   507,   939,   943,   890,   475,   944,
     454,  1089,  1085,   271,   150,  1086,  1090,   412,   197,   272,
     273,   274,   275,   276,   277,   413,   492,  1108,   483,   431,
     214,  1097,  1109,   244,   215,   441,   457,   484,   464,   202,
     258,  1111,   241,  1112,   449,   450,   236,  1149,   489,   247,
     278,   238,  1150,   460,   251,   462,   261,   463,   216,   478,
     300,   262,   482,   203,   217,   319,   279,   486,   218,   487,
     321,   280,   488,   322,   494,   239,   497,   499,   252,   500,
     503,   314,   219,   354,   372,   263,   332,   220,   515,   516,
     221,   504,   512,   518,   517,   281,   245,    99,   519,   520,
     521,    99,   246,   259,   355,   315,   373,   222,    99,   260,
     333,   223,   522,   301,   224,   376,   524,   530,   320,   225,
     525,   526,   233,   527,   528,   529,   531,   532,   356,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     538,   533,   542,   543,   129,   544,   534,   535,   536,   545,
     537,   546,   539,   547,   204,   541,   205,   548,   540,   549,
     550,   551,   130,   131,   206,   207,   208,   209,   210,   132,
     552,   553,   554,   559,   555,   556,   557,   558,   560,   561,
     562,   211,   563,   564,   212,   139,   565,   567,   568,   570,
     130,   131,   213,   571,   572,   573,   574,   576,   575,   577,
     578,   579,   581,   583,   585,   589,   584,   150,   590,   591,
     586,   587,   592,   593,   197,   594,   595,   597,   598,   600,
     599,   601,   602,   603,   633,   634,   635,   605,   606,   607,
     609,   610,   612,   621,   613,   202,   614,   616,   376,   829,
     842,   615,   354,   372,   617,   618,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   203,
     831,   843,   619,   355,   620,   373,   147,   148,    99,   622,
     623,   624,   627,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   832,   844,   127,   356,   129,   294,
     628,   630,   631,   632,   636,   637,    99,   638,   639,   640,
     641,   642,   643,   644,   645,   648,   130,   131,    34,   207,
     208,   654,   210,   132,   697,   655,   656,   657,   667,   659,
     658,   660,   661,   668,   894,   211,   662,   663,   212,   664,
     666,   669,   670,   672,   713,   673,   213,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   679,   712,   761,   795,   765,   769,   773,   777,
     674,   799,   802,   675,   676,   806,   850,   678,   854,   680,
     681,   682,   858,   875,   876,   877,   686,   687,   878,   704,
     879,   881,   882,   886,   887,   688,   689,   888,   889,   690,
     691,   895,   897,   692,   898,   900,   901,   904,   903,   693,
     907,   906,   694,   695,   696,   698,   910,   699,   700,   920,
     921,   711,    99,   924,   923,   925,   926,   927,   928,   929,
     930,   935,   936,   937,   948,   953,   952,   955,   956,   964,
     959,   958,   960,   961,   962,   963,   965,   966,   967,   968,
     969,   970,   972,   971,   973,   974,   975,   976,  1017,   978,
     977,  1044,  1045,  1037,  1038,  1039,  1040,  1041,  1042,  1046,
    1047,  1048,  1050,  1051,  1067,  1078,  1066,  1072,  1093,  1116,
    1087,  1095,   214,  1088,  1094,   300,   215,  1079,   319,  1080,
    1096,   988,  1106,   321,   241,   989,   322,  1081,   236,  1115,
    1082,  1083,  1021,   238,  1118,   278,   314,  1010,   336,   332,
     216,  1120,  1011,  1123,  1084,  1145,   217,  1091,  1023,   990,
     218,   279,  1102,  1024,   829,   991,   280,   239,   842,   992,
     315,  1056,  1103,   333,   219,  1104,  1012,   244,   301,   220,
     258,   320,   221,   993,  1000,   831,  1110,  1025,   994,   843,
     281,   995,  1058,   247,  1004,  1022,   261,  1113,   251,   222,
    1005,   262,  1119,   223,  1125,  1122,   224,  1146,   996,   832,
    1147,   225,   997,   844,   233,   998,  1059,  1151,  1124,  1155,
     999,  1153,   252,  1006,  1057,   263,  1152,   665,   787,   714,
    1154,  1157,  1158,   717,   566,   569,   866,   981,   979,  1018,
     245,  1015,  1016,   259,  1036,  1035,   246,   611,  1043,   260,
    1114,   983,   982,  1014,   580,   292,   985,   984,   604,  1069,
    1068,   987,   986,  1033,   608,   582,  1070,  1071,   588,   863,
    1034,  1117,   596,   716,  1049,   715,  1032,   629,   523,  1052,
     625,  1121,  1143,  1156,  1065,   626,     0,     0,     0,     0,
     849,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
      78,    79,    80,    76,    77,    78,    79,    80,   905,    82,
      83,    77,    85,   905,    85,   905,   905,    77,   905,     0,
      10,    77,    86,   110,   111,   101,   183,    76,    77,    78,
      79,    80,   108,    82,    83,    77,    85,    16,    17,     7,
      77,    82,    83,    77,    21,   103,   546,    78,    79,   103,
     104,    17,   106,    78,    79,     5,     7,     7,     3,     9,
      77,   561,    58,     8,    77,     7,     3,    77,   577,     6,
      11,    12,    77,     3,    15,    77,     6,    18,    19,    20,
     589,   590,   591,    60,     3,    62,    63,     6,   156,    66,
      67,    68,    77,    78,   110,   111,   183,     3,    77,    78,
      77,    78,     8,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     3,
      59,     7,     6,    59,    60,   183,    21,   149,   150,   151,
     152,    70,   120,   121,   122,    30,    77,    78,    77,    78,
       6,    77,    78,    84,   129,   130,    13,    14,    89,    90,
      91,    92,    93,     3,    95,   146,   147,    96,     8,   100,
      99,    97,    98,     3,   186,   155,     6,    60,   109,     3,
       7,   112,     7,     3,     8,   165,   166,   167,   119,     7,
       7,     7,    77,    78,    77,    78,   127,   128,     7,     3,
     131,   132,  1089,   183,     8,     7,     3,  1089,   183,  1089,
    1089,     8,  1089,    59,   183,   158,   183,     7,   161,   162,
     163,   164,   153,   154,     7,   156,    72,    73,    74,    75,
      76,    77,    78,    85,    86,    87,    88,     3,   123,   124,
     125,   126,     8,   183,   184,   185,   186,     7,     4,     8,
      96,     3,   183,    99,   183,     3,     8,   183,     8,     4,
     911,   893,   113,   114,   115,   116,   117,   118,    22,    23,
      24,    25,     4,     4,   157,    21,   159,   160,   938,     4,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,   183,     3,
     183,     3,     3,     3,     8,     4,     8,     8,     8,     4,
     394,     3,     3,     3,    60,     3,     8,    59,     8,     3,
       8,     4,     4,     4,     8,    60,    61,    62,    63,    64,
      65,     4,     4,     3,     3,    77,    78,   183,     8,     8,
       3,     3,    77,    78,     3,     8,     8,     3,     8,     8,
       3,     3,     8,    95,   438,     8,     8,     4,   442,   101,
     102,   103,   104,   105,   106,     4,     3,     3,     8,     4,
     454,     8,     8,   457,   454,     4,     3,     3,     3,   442,
     464,     8,   454,     8,     4,     4,   454,     3,     3,   457,
     474,   454,     8,     4,   457,     4,   464,     4,   454,     4,
     484,   464,     4,   442,   454,   489,   474,     4,   454,     4,
     489,   474,     8,   489,     4,   454,     4,     4,   457,     4,
       4,   484,   454,   507,   507,   464,   489,   454,   384,   385,
     454,     4,     4,     4,   183,   474,   457,   183,     4,     4,
       4,   183,   457,   464,   507,   484,   507,   454,   183,   464,
     489,   454,     4,   484,   454,   509,     4,   184,   489,   454,
       4,     4,   454,     4,     4,     4,   184,   184,   507,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     186,   184,     4,     4,    59,     4,   184,   184,   184,     4,
     184,     4,   185,     4,    69,   184,    71,     4,   185,     4,
       4,     4,    77,    78,    79,    80,    81,    82,    83,    84,
       4,     4,     4,   184,     4,     4,     4,     4,     4,     4,
       4,    96,     4,     4,    99,   100,     4,     4,   186,     4,
      77,    78,   107,     4,     4,     4,     4,   186,   184,     4,
       4,     4,     4,     4,     4,     4,   184,   631,     4,     4,
     184,   184,     4,     4,   638,     4,     4,     4,     4,     4,
     184,     4,     4,   186,   520,   521,   522,     4,   186,   186,
       4,     4,   186,   186,     4,   638,     4,     4,   632,   663,
     664,   184,   666,   666,   184,   184,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   638,
     663,   664,     4,   666,     4,   666,   153,   154,   183,   186,
       4,     4,     4,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,   663,   664,    57,   666,    59,    60,
     184,     4,     7,     7,   183,     7,   183,     7,     7,     7,
       5,   183,     5,     5,     5,   183,    77,    78,     7,    80,
      81,     5,    83,    84,   610,     5,     5,     5,   183,     5,
       7,     5,     5,   183,     6,    96,     7,     7,    99,     7,
       7,     5,     5,     5,   630,     5,   107,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,     7,     5,     7,    94,     7,     7,     7,     7,
     183,     7,     7,   183,   183,     7,     7,   183,     7,   183,
     183,   183,     7,     4,     4,     4,   183,   183,     4,   148,
       4,     4,     4,     4,     4,   183,   183,     4,     4,   183,
     183,     3,     6,   183,     3,     6,     3,     3,     6,   183,
       3,     6,   183,   183,   183,   183,     6,   183,   183,     6,
       3,   183,   183,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   183,     3,     6,     6,     3,   184,
       6,     8,     4,     4,     4,     4,   186,   184,   186,   184,
       4,   184,     4,   184,     4,     4,   184,   184,     4,   184,
     186,     4,     4,   184,   184,   184,   184,   184,   184,   184,
     184,   184,     4,     4,     3,   183,     6,     4,     4,   186,
       8,     3,   896,     8,     8,   899,   896,   183,   902,   183,
       8,   905,     4,   902,   896,   905,   902,   183,   896,     4,
     183,   183,   916,   896,     4,   919,   899,   905,   922,   902,
     896,     4,   905,     5,   183,     4,   896,   183,   916,   905,
     896,   919,   183,   916,   938,   905,   919,   896,   942,   905,
     899,   945,   183,   902,   896,   183,   905,   951,   899,   896,
     954,   902,   896,   905,   905,   938,   183,   916,   905,   942,
     919,   905,   945,   951,   905,   916,   954,   183,   951,   896,
     905,   954,   184,   896,     7,   183,   896,     4,   905,   938,
       4,   896,   905,   942,   896,   905,   945,     4,   183,     4,
     905,   184,   951,   905,   945,   954,   186,   561,   656,   631,
     184,   183,   183,   638,   438,   442,   712,   895,   890,   914,
     951,   908,   911,   954,   924,   922,   951,   492,   931,   954,
    1089,   898,   896,   907,   454,    81,   901,   899,   484,   953,
     951,   904,   902,   919,   489,   457,   954,   956,   464,   679,
     921,  1095,   474,   637,   938,   632,   917,   513,   394,   942,
     507,  1108,  1129,  1149,   946,   509,    -1,    -1,    -1,    -1,
     666,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
       0,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,     0,     5,     7,     9,   183,   184,   185,   186,
     204,   205,   206,   211,     7,   220,     7,   226,     7,   248,
       7,   347,     7,   424,     7,   440,     7,   457,     7,   376,
       7,   382,     7,   406,     7,   323,     7,   518,     7,   565,
       7,   556,   212,   207,   221,   227,   249,   348,   425,   441,
     458,   377,   383,   407,   324,   519,   566,   557,   204,   213,
     214,   183,   209,   210,    10,   155,   165,   166,   167,   183,
     219,   222,   223,   224,   548,   550,   552,   563,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      77,    78,    84,    89,    90,    91,    92,    93,    95,   100,
     109,   112,   119,   127,   128,   131,   132,   153,   154,   156,
     219,   228,   229,   230,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   246,   255,   257,
     259,   297,   303,   309,   315,   317,   331,   341,   361,   366,
     374,   400,   430,   432,   451,   481,   493,   505,   506,   514,
     516,   544,   546,   554,   569,    16,    17,   219,   250,   251,
     252,   254,   430,   432,    69,    71,    79,    80,    81,    82,
      83,    96,    99,   107,   219,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   349,   350,   351,   353,
     355,   357,   359,   361,   364,   365,   400,   418,   430,   432,
     434,   451,   476,    70,   219,   357,   359,   400,   426,   427,
     428,   430,   432,    72,    73,    74,    75,    76,   219,   357,
     359,   400,   430,   432,   442,   443,   444,   446,   447,   449,
     450,    95,   101,   102,   103,   104,   105,   106,   219,   400,
     430,   432,   459,   460,   461,   462,   464,   466,   468,   470,
     472,   474,   374,    21,    60,    62,    63,    66,    67,    68,
     219,   277,   384,   385,   386,   387,   388,   389,   390,   392,
     394,   396,   397,   399,   430,   432,    61,    64,    65,   219,
     277,   388,   394,   408,   409,   410,   411,   412,   414,   415,
     416,   417,   430,   432,   110,   111,   219,   325,   326,   327,
     329,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   219,   430,   432,   520,   521,   522,
     523,   525,   527,   528,   530,   531,   532,   535,   537,   538,
     539,   542,   544,   546,   567,   568,   569,    13,    14,   558,
     559,   560,   562,     6,     3,     4,     8,     3,   225,   564,
     549,   551,   553,     4,     3,     8,   231,   555,   247,   256,
     258,   260,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   245,   342,   375,   401,   431,   433,
     362,   367,   304,   316,   310,   298,   482,   452,   318,   332,
     494,     4,   507,   515,   517,   545,   547,   570,     3,     8,
     253,     4,     3,     8,   419,   435,   352,   354,   356,     4,
       4,   360,   358,   477,     3,     8,   429,     3,     8,   445,
       4,   448,     4,     4,     3,     8,   475,   463,   465,   467,
     469,   471,   473,     8,     3,     8,   391,   278,     4,   395,
     393,   398,     4,     8,     3,   413,     4,     4,     8,     3,
     328,   330,     3,     8,     4,   524,   526,     4,   529,     4,
       4,   533,   536,     4,     4,   540,   543,     3,     8,     3,
       8,   561,     4,     3,     8,   204,   204,   183,     4,     4,
       4,     4,     4,   223,     4,     4,     4,     4,     4,     4,
     184,   184,   184,   184,   184,   184,   184,   184,   186,   185,
     185,   184,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   184,
       4,     4,     4,     4,     4,     4,   229,     4,   186,   251,
       4,     4,     4,     4,     4,   184,   186,     4,     4,     4,
     350,     4,   427,     4,   184,     4,   184,   184,   443,     4,
       4,     4,     4,     4,     4,     4,   461,     4,     4,   184,
       4,     4,     4,   186,   386,     4,   186,   186,   410,     4,
       4,   326,   186,     4,     4,   184,     4,   184,   184,     4,
       4,   186,   186,     4,     4,   521,   568,     4,   184,   559,
       4,     7,     7,   204,   204,   204,   183,     7,     7,     7,
       7,     5,   183,     5,     5,     5,   206,   208,   183,    85,
      86,    87,    88,   363,     5,     5,     5,     5,     7,     5,
       5,     5,     7,     7,     7,   208,     7,   183,   183,     5,
       5,   215,     5,     5,   183,   183,   183,   215,   183,     7,
     183,   183,   183,   215,   215,   215,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   204,   183,   183,
     183,   146,   147,   534,   148,   149,   150,   151,   152,   186,
     541,   183,     5,   204,   228,   567,   558,   250,    21,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,   219,   265,   266,
     267,   270,   272,   274,   276,   277,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   290,   291,   293,   295,
     265,     7,   261,   262,   263,     7,   343,   344,   345,     7,
     378,   379,   380,     7,   402,   403,   404,     7,   368,   369,
     370,   103,   183,   305,   306,   307,   308,   213,   104,   106,
     307,   311,   312,   313,   314,    94,   299,   300,   301,     7,
     483,   484,     7,   453,   454,   455,     7,   319,   320,   321,
     113,   114,   115,   116,   117,   118,   333,   334,   335,   336,
     337,   338,   339,   340,    21,   123,   124,   125,   126,   219,
     279,   430,   432,   495,   496,   497,   500,   501,   503,   504,
     129,   130,   219,   430,   432,   508,   509,   510,   512,   520,
       7,   571,   572,   216,     7,   420,   421,   422,     7,   436,
     437,   438,   108,   462,   478,   479,   261,     8,     8,     8,
       8,   268,   271,   273,   275,     4,     4,     4,     4,     4,
     289,     4,     4,   292,   294,   296,     4,     4,     4,     4,
       3,     8,     8,   264,     6,     3,   346,     6,     3,   381,
       6,     3,   405,     6,     3,   371,     6,     3,     3,     6,
       6,     3,     6,   302,     3,     8,   485,     3,     6,   456,
       6,     3,   322,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   498,   502,     4,     4,     4,     3,     8,
     511,   513,     3,     8,     8,   573,     3,     6,   183,   217,
     218,   423,     6,     3,   439,     6,     3,   480,     8,     6,
       4,     4,     4,     4,   184,   186,   184,   186,   184,     4,
     184,   184,     4,     4,     4,   184,   184,   186,   184,   266,
     265,   263,   349,   345,   384,   380,   408,   404,   219,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     277,   341,   353,   355,   357,   359,   361,   365,   372,   373,
     400,   430,   432,   476,   370,   306,   312,     4,   300,    97,
      98,   219,   277,   400,   430,   432,   486,   487,   488,   489,
     490,   492,   484,   459,   455,   325,   321,   184,   184,   184,
     184,   184,   184,   334,     4,     4,   184,   184,   184,   496,
       4,     4,   509,   157,   159,   160,   219,   277,   430,   432,
     574,   575,   576,   577,   579,   572,     6,     3,   426,   422,
     442,   438,     4,    22,    23,    24,    25,   269,   183,   183,
     183,   183,   183,   183,   183,     8,     8,     8,     8,     3,
       8,   183,   491,     4,     8,     3,     8,     8,   120,   121,
     122,   499,   183,   183,   183,   580,     4,   578,     3,     8,
     183,     8,     8,   183,   373,     4,   186,   488,     4,   184,
       4,   575,   183,     5,   183,     7,   581,   582,   583,     3,
       6,   158,   161,   162,   163,   164,   584,   585,   586,   588,
     589,   590,   591,   582,   587,     4,     4,     4,   592,     3,
       8,     4,   186,   184,   184,     4,   585,   183,   183
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   187,   189,   188,   190,   188,   191,   188,   192,   188,
     193,   188,   194,   188,   195,   188,   196,   188,   197,   188,
     198,   188,   199,   188,   200,   188,   201,   188,   202,   188,
     203,   188,   204,   204,   204,   204,   204,   204,   204,   205,
     207,   206,   208,   209,   209,   210,   210,   212,   211,   213,
     213,   214,   214,   216,   215,   217,   217,   218,   218,   219,
     221,   220,   222,   222,   223,   223,   223,   223,   223,   223,
     225,   224,   227,   226,   228,   228,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   231,
     230,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   245,   244,   247,   246,   249,   248,   250,
     250,   251,   251,   251,   251,   251,   253,   252,   254,   256,
     255,   258,   257,   260,   259,   261,   261,   262,   262,   264,
     263,   265,   265,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   268,   267,   269,   269,   269,   269,
     271,   270,   273,   272,   275,   274,   276,   278,   277,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   289,   288,
     290,   292,   291,   294,   293,   296,   295,   298,   297,   299,
     299,   300,   302,   301,   304,   303,   305,   305,   306,   306,
     307,   308,   310,   309,   311,   311,   312,   312,   312,   313,
     314,   316,   315,   318,   317,   319,   319,   320,   320,   322,
     321,   324,   323,   325,   325,   325,   326,   326,   328,   327,
     330,   329,   332,   331,   333,   333,   334,   334,   334,   334,
     334,   334,   335,   336,   337,   338,   339,   340,   342,   341,
     343,   343,   344,   344,   346,   345,   348,   347,   349,   349,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   352,   351,   354,
     353,   356,   355,   358,   357,   360,   359,   362,   361,   363,
     363,   363,   363,   364,   365,   367,   366,   368,   368,   369,
     369,   371,   370,   372,   372,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   375,
     374,   377,   376,   378,   378,   379,   379,   381,   380,   383,
     382,   384,   384,   385,   385,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   387,   388,   389,   391,   390,
     393,   392,   395,   394,   396,   398,   397,   399,   401,   400,
     402,   402,   403,   403,   405,   404,   407,   406,   408,   408,
     409,   409,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   411,   413,   412,   414,   415,   416,   417,   419,   418,
     420,   420,   421,   421,   423,   422,   425,   424,   426,   426,
     427,   427,   427,   427,   427,   427,   427,   429,   428,   431,
     430,   433,   432,   435,   434,   436,   436,   437,   437,   439,
     438,   441,   440,   442,   442,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   445,   444,   446,   448,
     447,   449,   450,   452,   451,   453,   453,   454,   454,   456,
     455,   458,   457,   459,   459,   460,   460,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   463,   462,
     465,   464,   467,   466,   469,   468,   471,   470,   473,   472,
     475,   474,   477,   476,   478,   478,   480,   479,   482,   481,
     483,   483,   485,   484,   486,   486,   487,   487,   488,   488,
     488,   488,   488,   488,   488,   489,   491,   490,   492,   494,
     493,   495,   495,   496,   496,   496,   496,   496,   496,   496,
     496,   496,   498,   497,   499,   499,   499,   500,   502,   501,
     503,   504,   505,   507,   506,   508,   508,   509,   509,   509,
     509,   509,   511,   510,   513,   512,   515,   514,   517,   516,
     519,   518,   520,   520,   521,   521,   521,   521,   521,   521,
     521,   521,   521,   521,   521,   521,   521,   521,   521,   521,
     521,   521,   522,   524,   523,   526,   525,   527,   529,   528,
     530,   531,   533,   532,   534,   534,   536,   535,   537,   538,
     540,   539,   541,   541,   541,   541,   541,   543,   542,   545,
     544,   547,   546,   549,   548,   551,   550,   553,   552,   555,
     554,   557,   556,   558,   558,   559,   559,   561,   560,   562,
     564,   563,   566,   565,   567,   567,   568,   570,   569,   571,
     571,   573,   572,   574,   574,   575,   575,   575,   575,   575,
     575,   575,   576,   578,   577,   580,   579,   581,   581,   583,
     582,   584,   584,   585,   585,   585,   585,   585,   587,   586,
     588,   589,   590,   592,   591
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     0,     6,     3,
       0,     6,     0,     4,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4
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
       0,   271,   271,   271,   272,   272,   273,   273,   274,   274,
     275,   275,   276,   276,   277,   277,   278,   278,   279,   279,
     280,   280,   281,   281,   282,   282,   283,   283,   284,   284,
     285,   285,   293,   294,   295,   296,   297,   298,   299,   302,
     307,   307,   318,   321,   322,   325,   329,   336,   336,   343,
     344,   347,   351,   358,   358,   365,   366,   369,   373,   384,
     394,   394,   409,   410,   414,   415,   416,   417,   418,   419,
     422,   422,   437,   437,   446,   447,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   497,
     497,   505,   510,   515,   520,   525,   530,   535,   540,   545,
     550,   555,   560,   565,   565,   573,   573,   584,   584,   593,
     594,   597,   598,   599,   600,   601,   604,   604,   614,   620,
     620,   632,   632,   644,   644,   654,   655,   658,   659,   662,
     662,   672,   673,   676,   677,   678,   679,   680,   681,   682,
     683,   684,   685,   686,   687,   688,   689,   690,   691,   692,
     693,   694,   695,   696,   699,   699,   706,   707,   708,   709,
     712,   712,   720,   720,   728,   728,   736,   741,   741,   749,
     754,   759,   764,   769,   774,   779,   784,   789,   794,   794,
     802,   807,   807,   815,   815,   823,   823,   831,   831,   841,
     842,   844,   846,   846,   864,   864,   874,   875,   878,   879,
     882,   887,   892,   892,   902,   903,   906,   907,   908,   911,
     916,   923,   923,   933,   933,   943,   944,   947,   948,   951,
     951,   961,   961,   971,   972,   973,   976,   977,   980,   980,
     988,   988,   996,   996,  1007,  1008,  1011,  1012,  1013,  1014,
    1015,  1016,  1019,  1024,  1029,  1034,  1039,  1044,  1052,  1052,
    1065,  1066,  1069,  1070,  1077,  1077,  1103,  1103,  1114,  1115,
    1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,  1128,
    1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,
    1139,  1140,  1141,  1142,  1143,  1144,  1145,  1148,  1148,  1156,
    1156,  1164,  1164,  1172,  1172,  1180,  1180,  1190,  1190,  1197,
    1198,  1199,  1200,  1203,  1208,  1216,  1216,  1227,  1228,  1232,
    1233,  1236,  1236,  1244,  1245,  1248,  1249,  1250,  1251,  1252,
    1253,  1254,  1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,
    1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1271,  1278,
    1278,  1291,  1291,  1300,  1301,  1304,  1305,  1310,  1310,  1325,
    1325,  1339,  1340,  1343,  1344,  1347,  1348,  1349,  1350,  1351,
    1352,  1353,  1354,  1355,  1356,  1359,  1361,  1366,  1368,  1368,
    1376,  1376,  1384,  1384,  1392,  1394,  1394,  1402,  1411,  1411,
    1423,  1424,  1429,  1430,  1435,  1435,  1447,  1447,  1459,  1460,
    1465,  1466,  1471,  1472,  1473,  1474,  1475,  1476,  1477,  1478,
    1479,  1482,  1484,  1484,  1492,  1494,  1496,  1501,  1509,  1509,
    1521,  1522,  1525,  1526,  1529,  1529,  1539,  1539,  1548,  1549,
    1552,  1553,  1554,  1555,  1556,  1557,  1558,  1561,  1561,  1569,
    1569,  1594,  1594,  1624,  1624,  1636,  1637,  1640,  1641,  1644,
    1644,  1656,  1656,  1668,  1669,  1672,  1673,  1674,  1675,  1676,
    1677,  1678,  1679,  1680,  1681,  1682,  1685,  1685,  1693,  1698,
    1698,  1706,  1711,  1719,  1719,  1729,  1730,  1733,  1734,  1737,
    1737,  1746,  1746,  1755,  1756,  1759,  1760,  1764,  1765,  1766,
    1767,  1768,  1769,  1770,  1771,  1772,  1773,  1774,  1777,  1777,
    1787,  1787,  1797,  1797,  1805,  1805,  1813,  1813,  1821,  1821,
    1829,  1829,  1842,  1842,  1852,  1853,  1856,  1856,  1867,  1867,
    1877,  1878,  1881,  1881,  1891,  1892,  1895,  1896,  1899,  1900,
    1901,  1902,  1903,  1904,  1905,  1908,  1910,  1910,  1918,  1926,
    1926,  1938,  1939,  1942,  1943,  1944,  1945,  1946,  1947,  1948,
    1949,  1950,  1953,  1953,  1960,  1961,  1962,  1965,  1970,  1970,
    1978,  1983,  1990,  1997,  1997,  2007,  2008,  2011,  2012,  2013,
    2014,  2015,  2018,  2018,  2026,  2026,  2036,  2036,  2076,  2076,
    2088,  2088,  2098,  2099,  2102,  2103,  2104,  2105,  2106,  2107,
    2108,  2109,  2110,  2111,  2112,  2113,  2114,  2115,  2116,  2117,
    2118,  2119,  2122,  2127,  2127,  2135,  2135,  2143,  2148,  2148,
    2156,  2161,  2166,  2166,  2174,  2175,  2178,  2178,  2186,  2191,
    2196,  2196,  2204,  2207,  2210,  2213,  2216,  2222,  2222,  2230,
    2230,  2238,  2238,  2248,  2248,  2255,  2255,  2262,  2262,  2271,
    2271,  2282,  2282,  2292,  2293,  2297,  2298,  2301,  2301,  2311,
    2321,  2321,  2331,  2331,  2342,  2343,  2347,  2351,  2351,  2363,
    2364,  2368,  2368,  2376,  2377,  2380,  2381,  2382,  2383,  2384,
    2385,  2386,  2389,  2394,  2394,  2402,  2402,  2412,  2413,  2416,
    2416,  2424,  2425,  2428,  2429,  2430,  2431,  2432,  2435,  2435,
    2443,  2448,  2453,  2458,  2458
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
#line 5291 "dhcp6_parser.cc"

#line 2466 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
