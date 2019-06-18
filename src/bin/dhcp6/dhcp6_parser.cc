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
      case 202: // value
      case 206: // map_value
      case 267: // db_type
      case 360: // hr_mode
      case 496: // duid_type
      case 531: // ncr_protocol_value
      case 538: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 184: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 183: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 182: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 181: // "constant string"
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
      case 202: // value
      case 206: // map_value
      case 267: // db_type
      case 360: // hr_mode
      case 496: // duid_type
      case 531: // ncr_protocol_value
      case 538: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 184: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 183: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 182: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 181: // "constant string"
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
      case 202: // value
      case 206: // map_value
      case 267: // db_type
      case 360: // hr_mode
      case 496: // duid_type
      case 531: // ncr_protocol_value
      case 538: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 184: // "boolean"
        value.move< bool > (that.value);
        break;

      case 183: // "floating point"
        value.move< double > (that.value);
        break;

      case 182: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 181: // "constant string"
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
      case 181: // "constant string"
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 405 "dhcp6_parser.cc"
        break;

      case 182: // "integer"
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 411 "dhcp6_parser.cc"
        break;

      case 183: // "floating point"
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case 184: // "boolean"
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case 202: // value
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case 206: // map_value
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case 267: // db_type
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case 360: // hr_mode
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case 496: // duid_type
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case 531: // ncr_protocol_value
#line 260 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case 538: // replace_client_name_value
#line 260 "dhcp6_parser.yy"
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
      case 202: // value
      case 206: // map_value
      case 267: // db_type
      case 360: // hr_mode
      case 496: // duid_type
      case 531: // ncr_protocol_value
      case 538: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 184: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 183: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 182: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 181: // "constant string"
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
#line 269 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 731 "dhcp6_parser.cc"
    break;

  case 4:
#line 270 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 737 "dhcp6_parser.cc"
    break;

  case 6:
#line 271 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 743 "dhcp6_parser.cc"
    break;

  case 8:
#line 272 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 749 "dhcp6_parser.cc"
    break;

  case 10:
#line 273 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.SUBNET6; }
#line 755 "dhcp6_parser.cc"
    break;

  case 12:
#line 274 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 761 "dhcp6_parser.cc"
    break;

  case 14:
#line 275 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 767 "dhcp6_parser.cc"
    break;

  case 16:
#line 276 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 773 "dhcp6_parser.cc"
    break;

  case 18:
#line 277 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 779 "dhcp6_parser.cc"
    break;

  case 20:
#line 278 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 785 "dhcp6_parser.cc"
    break;

  case 22:
#line 279 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 791 "dhcp6_parser.cc"
    break;

  case 24:
#line 280 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 797 "dhcp6_parser.cc"
    break;

  case 26:
#line 281 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 803 "dhcp6_parser.cc"
    break;

  case 28:
#line 282 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 809 "dhcp6_parser.cc"
    break;

  case 30:
#line 283 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 815 "dhcp6_parser.cc"
    break;

  case 32:
#line 291 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 821 "dhcp6_parser.cc"
    break;

  case 33:
#line 292 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 827 "dhcp6_parser.cc"
    break;

  case 34:
#line 293 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 833 "dhcp6_parser.cc"
    break;

  case 35:
#line 294 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp6_parser.cc"
    break;

  case 36:
#line 295 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp6_parser.cc"
    break;

  case 37:
#line 296 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 851 "dhcp6_parser.cc"
    break;

  case 38:
#line 297 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 857 "dhcp6_parser.cc"
    break;

  case 39:
#line 300 "dhcp6_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 866 "dhcp6_parser.cc"
    break;

  case 40:
#line 305 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 877 "dhcp6_parser.cc"
    break;

  case 41:
#line 310 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 887 "dhcp6_parser.cc"
    break;

  case 42:
#line 316 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 893 "dhcp6_parser.cc"
    break;

  case 45:
#line 323 "dhcp6_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 902 "dhcp6_parser.cc"
    break;

  case 46:
#line 327 "dhcp6_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 912 "dhcp6_parser.cc"
    break;

  case 47:
#line 334 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 921 "dhcp6_parser.cc"
    break;

  case 48:
#line 337 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 929 "dhcp6_parser.cc"
    break;

  case 51:
#line 345 "dhcp6_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 938 "dhcp6_parser.cc"
    break;

  case 52:
#line 349 "dhcp6_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp6_parser.cc"
    break;

  case 53:
#line 356 "dhcp6_parser.yy"
    {
    // List parsing about to start
}
#line 955 "dhcp6_parser.cc"
    break;

  case 54:
#line 358 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 964 "dhcp6_parser.cc"
    break;

  case 57:
#line 367 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 973 "dhcp6_parser.cc"
    break;

  case 58:
#line 371 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp6_parser.cc"
    break;

  case 59:
#line 382 "dhcp6_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 993 "dhcp6_parser.cc"
    break;

  case 60:
#line 392 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1004 "dhcp6_parser.cc"
    break;

  case 61:
#line 397 "dhcp6_parser.yy"
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
#line 420 "dhcp6_parser.yy"
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
#line 427 "dhcp6_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1040 "dhcp6_parser.cc"
    break;

  case 72:
#line 435 "dhcp6_parser.yy"
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1050 "dhcp6_parser.cc"
    break;

  case 73:
#line 439 "dhcp6_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 119:
#line 495 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 120:
#line 497 "dhcp6_parser.yy"
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc"
    break;

  case 121:
#line 503 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1086 "dhcp6_parser.cc"
    break;

  case 122:
#line 508 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1095 "dhcp6_parser.cc"
    break;

  case 123:
#line 513 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 124:
#line 518 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1113 "dhcp6_parser.cc"
    break;

  case 125:
#line 523 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1122 "dhcp6_parser.cc"
    break;

  case 126:
#line 528 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1131 "dhcp6_parser.cc"
    break;

  case 127:
#line 533 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1140 "dhcp6_parser.cc"
    break;

  case 128:
#line 538 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1149 "dhcp6_parser.cc"
    break;

  case 129:
#line 543 "dhcp6_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1158 "dhcp6_parser.cc"
    break;

  case 130:
#line 548 "dhcp6_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1167 "dhcp6_parser.cc"
    break;

  case 131:
#line 553 "dhcp6_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1176 "dhcp6_parser.cc"
    break;

  case 132:
#line 558 "dhcp6_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 133:
#line 563 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 134:
#line 565 "dhcp6_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 135:
#line 571 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 136:
#line 576 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 137:
#line 582 "dhcp6_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 138:
#line 586 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 146:
#line 602 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 147:
#line 607 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 148:
#line 612 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 149:
#line 618 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 150:
#line 623 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "dhcp6_parser.cc"
    break;

  case 151:
#line 630 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 152:
#line 635 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc"
    break;

  case 153:
#line 642 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1327 "dhcp6_parser.cc"
    break;

  case 154:
#line 647 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc"
    break;

  case 159:
#line 660 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1346 "dhcp6_parser.cc"
    break;

  case 160:
#line 664 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1356 "dhcp6_parser.cc"
    break;

  case 183:
#line 696 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1364 "dhcp6_parser.cc"
    break;

  case 184:
#line 698 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 185:
#line 703 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1379 "dhcp6_parser.cc"
    break;

  case 186:
#line 704 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1385 "dhcp6_parser.cc"
    break;

  case 187:
#line 705 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1391 "dhcp6_parser.cc"
    break;

  case 188:
#line 706 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1397 "dhcp6_parser.cc"
    break;

  case 189:
#line 709 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1405 "dhcp6_parser.cc"
    break;

  case 190:
#line 711 "dhcp6_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1415 "dhcp6_parser.cc"
    break;

  case 191:
#line 717 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp6_parser.cc"
    break;

  case 192:
#line 719 "dhcp6_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1433 "dhcp6_parser.cc"
    break;

  case 193:
#line 725 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 194:
#line 727 "dhcp6_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 195:
#line 733 "dhcp6_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 196:
#line 738 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp6_parser.cc"
    break;

  case 197:
#line 740 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1478 "dhcp6_parser.cc"
    break;

  case 198:
#line 746 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1487 "dhcp6_parser.cc"
    break;

  case 199:
#line 751 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1496 "dhcp6_parser.cc"
    break;

  case 200:
#line 756 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1505 "dhcp6_parser.cc"
    break;

  case 201:
#line 761 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1514 "dhcp6_parser.cc"
    break;

  case 202:
#line 766 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1523 "dhcp6_parser.cc"
    break;

  case 203:
#line 771 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 204:
#line 776 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 205:
#line 781 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 206:
#line 786 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp6_parser.cc"
    break;

  case 207:
#line 788 "dhcp6_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1568 "dhcp6_parser.cc"
    break;

  case 208:
#line 794 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 209:
#line 799 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1585 "dhcp6_parser.cc"
    break;

  case 210:
#line 801 "dhcp6_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1595 "dhcp6_parser.cc"
    break;

  case 211:
#line 807 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc"
    break;

  case 212:
#line 809 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc"
    break;

  case 213:
#line 815 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 214:
#line 817 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 215:
#line 823 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1642 "dhcp6_parser.cc"
    break;

  case 216:
#line 828 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1651 "dhcp6_parser.cc"
    break;

  case 220:
#line 838 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1659 "dhcp6_parser.cc"
    break;

  case 221:
#line 840 "dhcp6_parser.yy"
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
#line 1679 "dhcp6_parser.cc"
    break;

  case 222:
#line 856 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1690 "dhcp6_parser.cc"
    break;

  case 223:
#line 861 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 228:
#line 874 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 229:
#line 879 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1717 "dhcp6_parser.cc"
    break;

  case 230:
#line 884 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 231:
#line 889 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 237:
#line 903 "dhcp6_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 238:
#line 908 "dhcp6_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 239:
#line 915 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp6_parser.cc"
    break;

  case 240:
#line 920 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 241:
#line 925 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1786 "dhcp6_parser.cc"
    break;

  case 242:
#line 930 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 247:
#line 943 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 248:
#line 947 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 249:
#line 953 "dhcp6_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 250:
#line 957 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 256:
#line 972 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1843 "dhcp6_parser.cc"
    break;

  case 257:
#line 974 "dhcp6_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 258:
#line 980 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc"
    break;

  case 259:
#line 982 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 260:
#line 988 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1881 "dhcp6_parser.cc"
    break;

  case 261:
#line 993 "dhcp6_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1891 "dhcp6_parser.cc"
    break;

  case 270:
#line 1011 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 271:
#line 1016 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 272:
#line 1021 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 273:
#line 1026 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1927 "dhcp6_parser.cc"
    break;

  case 274:
#line 1031 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 275:
#line 1036 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1945 "dhcp6_parser.cc"
    break;

  case 276:
#line 1044 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 277:
#line 1049 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1965 "dhcp6_parser.cc"
    break;

  case 282:
#line 1069 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 283:
#line 1073 "dhcp6_parser.yy"
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
#line 2001 "dhcp6_parser.cc"
    break;

  case 284:
#line 1095 "dhcp6_parser.yy"
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 285:
#line 1099 "dhcp6_parser.yy"
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 315:
#line 1140 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 316:
#line 1142 "dhcp6_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2039 "dhcp6_parser.cc"
    break;

  case 317:
#line 1148 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 318:
#line 1150 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 319:
#line 1156 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 320:
#line 1158 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 321:
#line 1164 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 322:
#line 1166 "dhcp6_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 323:
#line 1172 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2104 "dhcp6_parser.cc"
    break;

  case 324:
#line 1177 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 325:
#line 1182 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2121 "dhcp6_parser.cc"
    break;

  case 326:
#line 1184 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2130 "dhcp6_parser.cc"
    break;

  case 327:
#line 1189 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2136 "dhcp6_parser.cc"
    break;

  case 328:
#line 1190 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2142 "dhcp6_parser.cc"
    break;

  case 329:
#line 1191 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2148 "dhcp6_parser.cc"
    break;

  case 330:
#line 1192 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2154 "dhcp6_parser.cc"
    break;

  case 331:
#line 1195 "dhcp6_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2163 "dhcp6_parser.cc"
    break;

  case 332:
#line 1200 "dhcp6_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2172 "dhcp6_parser.cc"
    break;

  case 333:
#line 1208 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 334:
#line 1213 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 339:
#line 1228 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 340:
#line 1232 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2210 "dhcp6_parser.cc"
    break;

  case 367:
#line 1270 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 368:
#line 1275 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2230 "dhcp6_parser.cc"
    break;

  case 369:
#line 1283 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 370:
#line 1286 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 2247 "dhcp6_parser.cc"
    break;

  case 375:
#line 1302 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 376:
#line 1306 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 377:
#line 1317 "dhcp6_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2279 "dhcp6_parser.cc"
    break;

  case 378:
#line 1321 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2291 "dhcp6_parser.cc"
    break;

  case 394:
#line 1353 "dhcp6_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2300 "dhcp6_parser.cc"
    break;

  case 396:
#line 1360 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp6_parser.cc"
    break;

  case 397:
#line 1362 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 398:
#line 1368 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc"
    break;

  case 399:
#line 1370 "dhcp6_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 400:
#line 1376 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 401:
#line 1378 "dhcp6_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2354 "dhcp6_parser.cc"
    break;

  case 403:
#line 1386 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 404:
#line 1388 "dhcp6_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 405:
#line 1394 "dhcp6_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2381 "dhcp6_parser.cc"
    break;

  case 406:
#line 1403 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2392 "dhcp6_parser.cc"
    break;

  case 407:
#line 1408 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2401 "dhcp6_parser.cc"
    break;

  case 412:
#line 1427 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2411 "dhcp6_parser.cc"
    break;

  case 413:
#line 1431 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2420 "dhcp6_parser.cc"
    break;

  case 414:
#line 1439 "dhcp6_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2430 "dhcp6_parser.cc"
    break;

  case 415:
#line 1443 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2439 "dhcp6_parser.cc"
    break;

  case 430:
#line 1476 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2447 "dhcp6_parser.cc"
    break;

  case 431:
#line 1478 "dhcp6_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2457 "dhcp6_parser.cc"
    break;

  case 434:
#line 1488 "dhcp6_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 435:
#line 1493 "dhcp6_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 436:
#line 1501 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 437:
#line 1506 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2495 "dhcp6_parser.cc"
    break;

  case 442:
#line 1521 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2505 "dhcp6_parser.cc"
    break;

  case 443:
#line 1525 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2515 "dhcp6_parser.cc"
    break;

  case 444:
#line 1531 "dhcp6_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 445:
#line 1535 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2534 "dhcp6_parser.cc"
    break;

  case 455:
#line 1553 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2542 "dhcp6_parser.cc"
    break;

  case 456:
#line 1555 "dhcp6_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2552 "dhcp6_parser.cc"
    break;

  case 457:
#line 1561 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 458:
#line 1563 "dhcp6_parser.yy"
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
#line 2587 "dhcp6_parser.cc"
    break;

  case 459:
#line 1586 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2595 "dhcp6_parser.cc"
    break;

  case 460:
#line 1588 "dhcp6_parser.yy"
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
#line 2624 "dhcp6_parser.cc"
    break;

  case 461:
#line 1616 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2635 "dhcp6_parser.cc"
    break;

  case 462:
#line 1621 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2644 "dhcp6_parser.cc"
    break;

  case 467:
#line 1636 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2654 "dhcp6_parser.cc"
    break;

  case 468:
#line 1640 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 469:
#line 1648 "dhcp6_parser.yy"
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp6_parser.cc"
    break;

  case 470:
#line 1652 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 484:
#line 1677 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp6_parser.cc"
    break;

  case 485:
#line 1679 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc"
    break;

  case 486:
#line 1685 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 487:
#line 1690 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 488:
#line 1692 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc"
    break;

  case 489:
#line 1698 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2742 "dhcp6_parser.cc"
    break;

  case 490:
#line 1703 "dhcp6_parser.yy"
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 491:
#line 1711 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2762 "dhcp6_parser.cc"
    break;

  case 492:
#line 1716 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2771 "dhcp6_parser.cc"
    break;

  case 497:
#line 1729 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 498:
#line 1733 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2790 "dhcp6_parser.cc"
    break;

  case 499:
#line 1738 "dhcp6_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2800 "dhcp6_parser.cc"
    break;

  case 500:
#line 1742 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2809 "dhcp6_parser.cc"
    break;

  case 516:
#line 1769 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp6_parser.cc"
    break;

  case 517:
#line 1774 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 518:
#line 1779 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2840 "dhcp6_parser.cc"
    break;

  case 519:
#line 1784 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 520:
#line 1789 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2857 "dhcp6_parser.cc"
    break;

  case 521:
#line 1791 "dhcp6_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 522:
#line 1797 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 523:
#line 1799 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 524:
#line 1805 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 525:
#line 1807 "dhcp6_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 526:
#line 1813 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 527:
#line 1815 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 528:
#line 1821 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp6_parser.cc"
    break;

  case 529:
#line 1826 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 530:
#line 1834 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 531:
#line 1839 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2961 "dhcp6_parser.cc"
    break;

  case 534:
#line 1848 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2969 "dhcp6_parser.cc"
    break;

  case 535:
#line 1850 "dhcp6_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2979 "dhcp6_parser.cc"
    break;

  case 536:
#line 1859 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2990 "dhcp6_parser.cc"
    break;

  case 537:
#line 1864 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2999 "dhcp6_parser.cc"
    break;

  case 540:
#line 1873 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3009 "dhcp6_parser.cc"
    break;

  case 541:
#line 1877 "dhcp6_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3019 "dhcp6_parser.cc"
    break;

  case 554:
#line 1902 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 555:
#line 1904 "dhcp6_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 556:
#line 1910 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3046 "dhcp6_parser.cc"
    break;

  case 557:
#line 1918 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 558:
#line 1923 "dhcp6_parser.yy"
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3068 "dhcp6_parser.cc"
    break;

  case 570:
#line 1945 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 571:
#line 1947 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3085 "dhcp6_parser.cc"
    break;

  case 572:
#line 1952 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3091 "dhcp6_parser.cc"
    break;

  case 573:
#line 1953 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3097 "dhcp6_parser.cc"
    break;

  case 574:
#line 1954 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3103 "dhcp6_parser.cc"
    break;

  case 575:
#line 1957 "dhcp6_parser.yy"
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 576:
#line 1962 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3120 "dhcp6_parser.cc"
    break;

  case 577:
#line 1964 "dhcp6_parser.yy"
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 578:
#line 1970 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3139 "dhcp6_parser.cc"
    break;

  case 579:
#line 1975 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3148 "dhcp6_parser.cc"
    break;

  case 580:
#line 1982 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 581:
#line 1989 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 582:
#line 1994 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 590:
#line 2010 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp6_parser.cc"
    break;

  case 591:
#line 2012 "dhcp6_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 592:
#line 2018 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp6_parser.cc"
    break;

  case 593:
#line 2020 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3213 "dhcp6_parser.cc"
    break;

  case 594:
#line 2028 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 595:
#line 2030 "dhcp6_parser.yy"
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
#line 3261 "dhcp6_parser.cc"
    break;

  case 596:
#line 2068 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3272 "dhcp6_parser.cc"
    break;

  case 597:
#line 2073 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3283 "dhcp6_parser.cc"
    break;

  case 598:
#line 2080 "dhcp6_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 599:
#line 2084 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3303 "dhcp6_parser.cc"
    break;

  case 620:
#line 2114 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3312 "dhcp6_parser.cc"
    break;

  case 621:
#line 2119 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3320 "dhcp6_parser.cc"
    break;

  case 622:
#line 2121 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3330 "dhcp6_parser.cc"
    break;

  case 623:
#line 2127 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 624:
#line 2129 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 625:
#line 2135 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 626:
#line 2140 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3365 "dhcp6_parser.cc"
    break;

  case 627:
#line 2142 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3375 "dhcp6_parser.cc"
    break;

  case 628:
#line 2148 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 629:
#line 2153 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 630:
#line 2158 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3401 "dhcp6_parser.cc"
    break;

  case 631:
#line 2160 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 632:
#line 2166 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3416 "dhcp6_parser.cc"
    break;

  case 633:
#line 2167 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3422 "dhcp6_parser.cc"
    break;

  case 634:
#line 2170 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3430 "dhcp6_parser.cc"
    break;

  case 635:
#line 2172 "dhcp6_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3440 "dhcp6_parser.cc"
    break;

  case 636:
#line 2178 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 637:
#line 2183 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 638:
#line 2188 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3466 "dhcp6_parser.cc"
    break;

  case 639:
#line 2190 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3475 "dhcp6_parser.cc"
    break;

  case 640:
#line 2196 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3483 "dhcp6_parser.cc"
    break;

  case 641:
#line 2199 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3491 "dhcp6_parser.cc"
    break;

  case 642:
#line 2202 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3499 "dhcp6_parser.cc"
    break;

  case 643:
#line 2205 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3507 "dhcp6_parser.cc"
    break;

  case 644:
#line 2208 "dhcp6_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3516 "dhcp6_parser.cc"
    break;

  case 645:
#line 2214 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3524 "dhcp6_parser.cc"
    break;

  case 646:
#line 2216 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 647:
#line 2222 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 648:
#line 2224 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 649:
#line 2230 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 650:
#line 2232 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 651:
#line 2240 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 652:
#line 2242 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3587 "dhcp6_parser.cc"
    break;

  case 653:
#line 2247 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 654:
#line 2249 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 655:
#line 2254 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp6_parser.cc"
    break;

  case 656:
#line 2256 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 657:
#line 2263 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3632 "dhcp6_parser.cc"
    break;

  case 658:
#line 2268 "dhcp6_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 659:
#line 2274 "dhcp6_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 660:
#line 2278 "dhcp6_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3661 "dhcp6_parser.cc"
    break;

  case 665:
#line 2293 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3672 "dhcp6_parser.cc"
    break;

  case 666:
#line 2298 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3681 "dhcp6_parser.cc"
    break;

  case 667:
#line 2303 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 668:
#line 2313 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 669:
#line 2318 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3710 "dhcp6_parser.cc"
    break;

  case 670:
#line 2323 "dhcp6_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 671:
#line 2327 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 675:
#line 2343 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 676:
#line 2348 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3748 "dhcp6_parser.cc"
    break;

  case 679:
#line 2360 "dhcp6_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 680:
#line 2364 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 690:
#line 2381 "dhcp6_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 691:
#line 2386 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3783 "dhcp6_parser.cc"
    break;

  case 692:
#line 2388 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 693:
#line 2394 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 694:
#line 2399 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 697:
#line 2408 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3823 "dhcp6_parser.cc"
    break;

  case 698:
#line 2412 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 705:
#line 2426 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3839 "dhcp6_parser.cc"
    break;

  case 706:
#line 2428 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3849 "dhcp6_parser.cc"
    break;

  case 707:
#line 2434 "dhcp6_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3858 "dhcp6_parser.cc"
    break;

  case 708:
#line 2439 "dhcp6_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 709:
#line 2444 "dhcp6_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3876 "dhcp6_parser.cc"
    break;


#line 3880 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -875;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     428,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    46,    70,    63,    65,
      69,    71,    84,    93,    96,   100,   108,   130,   156,   184,
     188,   190,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,    70,   -95,    29,    78,    41,   263,    80,   277,
     444,   170,    43,   179,   -65,   506,    58,   291,  -875,   144,
     273,   262,   275,   323,  -875,  -875,  -875,  -875,  -875,   332,
    -875,    91,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   334,   343,   353,   355,   359,   387,
     391,   393,   394,   398,   399,   401,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   403,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,    98,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   405,  -875,   136,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   408,
     413,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   137,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   143,  -875,
    -875,  -875,  -875,  -875,   415,  -875,   418,   420,  -875,  -875,
    -875,  -875,  -875,  -875,   150,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   320,   364,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   419,  -875,  -875,   422,  -875,  -875,  -875,   426,
    -875,  -875,   421,   439,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,   447,   458,  -875,
    -875,  -875,  -875,   435,   463,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,   168,  -875,  -875,
    -875,   466,  -875,  -875,   467,  -875,   469,   470,  -875,  -875,
     471,   472,  -875,  -875,  -875,  -875,  -875,   182,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   204,  -875,  -875,  -875,   473,   212,
    -875,  -875,  -875,  -875,    70,    70,  -875,   286,   486,   487,
     489,   492,   493,  -875,    29,  -875,   494,   495,   496,   497,
     499,   500,   325,   326,   327,   328,   329,   335,   340,   341,
     330,   342,   344,   346,   501,   502,   520,   522,   525,   526,
     528,   529,   531,   532,   533,   535,   536,   537,   539,   546,
     547,   372,   548,   549,   551,   552,   554,   555,    78,  -875,
     556,   377,    41,  -875,   558,   559,   561,   562,   563,   386,
     385,   566,   567,   568,   263,  -875,   569,    80,  -875,   573,
     396,   575,   402,   404,   277,  -875,   576,   577,   583,   587,
     608,   610,   612,  -875,   444,  -875,   614,   615,   438,   617,
     618,   619,   440,  -875,    43,   622,   443,   445,  -875,   179,
     624,   626,   246,  -875,   448,   627,   629,   454,   647,   474,
     475,   648,   649,   476,   477,   650,   651,   506,  -875,    58,
    -875,   658,   481,   291,  -875,  -875,  -875,   661,   659,   660,
      70,    70,    70,  -875,   488,   663,   664,   665,   666,   669,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   498,   670,   671,   672,   673,   504,   301,   676,
     677,   678,   681,   682,   683,   685,   686,   687,   688,  -875,
     689,   673,   690,   511,   512,   693,  -875,   694,  -875,  -875,
     695,   696,   521,   523,   524,  -875,  -875,   694,   527,   699,
    -875,   530,  -875,   534,  -875,   538,  -875,  -875,  -875,   694,
     694,   694,   540,   541,   542,   543,  -875,   544,   545,  -875,
     550,   553,   557,  -875,  -875,   560,  -875,  -875,  -875,   564,
      70,  -875,  -875,   565,   570,  -875,   571,  -875,  -875,   248,
     580,  -875,  -875,   -37,   572,  -875,  -875,   698,  -875,  -875,
      70,    78,    58,  -875,  -875,  -875,  -875,   291,    41,   260,
     260,   700,  -875,   702,   703,   705,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   706,   -33,    70,    79,   585,   707,
     709,   710,   157,   122,    97,  -875,   506,  -875,  -875,   711,
    -875,  -875,   713,   721,  -875,  -875,  -875,  -875,  -875,   -48,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   700,  -875,   220,   226,   254,   255,  -875,  -875,
    -875,  -875,   725,   726,   728,   729,   731,  -875,   732,   733,
    -875,  -875,  -875,   735,   736,   738,  -875,   257,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   272,  -875,
     662,   740,  -875,  -875,   741,   745,  -875,  -875,   743,   747,
    -875,  -875,   748,   752,  -875,  -875,   750,   754,  -875,  -875,
    -875,    37,  -875,  -875,  -875,   753,  -875,  -875,  -875,    82,
    -875,  -875,  -875,  -875,   274,  -875,  -875,  -875,   200,  -875,
    -875,   755,   757,  -875,  -875,   756,   760,  -875,   761,   762,
     763,   764,   765,   766,   276,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   767,   768,   769,  -875,  -875,  -875,
    -875,   314,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   315,  -875,  -875,  -875,   321,  -875,   211,
    -875,   593,  -875,   758,   772,  -875,  -875,   770,   774,  -875,
    -875,  -875,   771,  -875,   775,  -875,  -875,  -875,  -875,   776,
     778,   779,   780,   596,   574,   603,   602,   605,   784,   607,
     609,   786,   788,   789,   613,   616,   620,   260,  -875,  -875,
     260,  -875,   700,   263,  -875,   702,    43,  -875,   703,   179,
    -875,   705,   436,  -875,   706,   -33,  -875,  -875,    79,  -875,
     790,   585,  -875,    83,   707,  -875,   444,  -875,   709,   -65,
    -875,   710,   621,   623,   625,   628,   630,   631,   157,  -875,
     792,   793,   632,   633,   634,   122,  -875,   795,   796,    97,
    -875,  -875,     6,   711,  -875,  -875,   800,   798,    80,  -875,
     713,   277,  -875,   721,   804,  -875,  -875,   425,   636,   637,
     639,  -875,  -875,  -875,  -875,  -875,   640,  -875,  -875,   643,
     645,   646,  -875,  -875,  -875,  -875,   322,  -875,   324,  -875,
     794,  -875,   801,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   362,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   653,  -875,  -875,   807,  -875,  -875,  -875,
    -875,  -875,   821,   833,  -875,  -875,  -875,  -875,  -875,   829,
    -875,   363,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     129,   657,  -875,  -875,  -875,  -875,   667,   691,  -875,  -875,
     837,  -875,  -875,  -875,  -875,  -875,   370,  -875,  -875,  -875,
    -875,  -875,  -875,   718,   371,  -875,   373,  -875,   720,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,   436,  -875,  -875,   846,   668,
    -875,    83,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,   847,   701,   850,     6,  -875,  -875,  -875,  -875,  -875,
    -875,   723,  -875,  -875,   739,  -875,   734,  -875,  -875,   852,
    -875,  -875,   331,  -875,    75,   852,  -875,  -875,   865,   890,
     898,   374,  -875,  -875,  -875,  -875,  -875,  -875,   903,   730,
     742,   744,    75,  -875,   737,  -875,  -875,  -875,  -875,  -875
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   137,     9,
     284,    11,   444,    13,   469,    15,   499,    17,   369,    19,
     377,    21,   414,    23,   249,    25,   598,    27,   670,    29,
     659,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     501,     0,   379,   416,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   668,   651,   653,   655,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   119,   657,
     135,   149,   151,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   276,   367,   406,
     457,   459,   325,   333,   222,   239,   230,   215,   536,   491,
     241,   260,   557,     0,   581,   594,   596,   647,   649,   675,
     118,     0,    74,    76,    77,    78,    79,    80,    81,    82,
      83,    84,   112,   113,   114,    85,   110,    88,    89,    90,
      91,   107,    92,    94,    93,    98,    99,    86,   111,    87,
      96,    97,   105,   106,   108,    95,   100,   101,   102,   103,
     104,   116,   117,   109,   115,   146,     0,   145,     0,   139,
     141,   142,   143,   144,   436,   461,   315,   317,   319,     0,
       0,   323,   321,   530,   314,   288,   289,   290,   291,   292,
     293,   294,   295,   311,   312,   313,     0,   286,   299,   300,
     301,   304,   305,   307,   302,   303,   296,   297,   309,   310,
     298,   306,   308,   455,   454,   450,   451,   449,     0,   446,
     448,   452,   453,   484,     0,   487,     0,     0,   483,   477,
     478,   476,   481,   482,     0,   471,   473,   474,   479,   480,
     475,   528,   516,   518,   520,   522,   524,   526,   515,   512,
     513,   514,     0,   502,   503,   507,   508,   505,   509,   510,
     511,   506,     0,   396,   196,     0,   400,   398,   403,     0,
     392,   393,     0,   380,   381,   383,   395,   384,   385,   386,
     402,   387,   388,   389,   390,   391,   430,     0,     0,   428,
     429,   432,   433,     0,   417,   418,   420,   421,   422,   423,
     424,   425,   426,   427,   256,   258,   253,     0,   251,   254,
     255,     0,   621,   623,     0,   626,     0,     0,   630,   634,
       0,     0,   638,   645,   619,   617,   618,     0,   600,   602,
     603,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     613,   614,   615,   616,     0,   672,   674,   665,     0,     0,
     661,   663,   664,    48,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    59,     0,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,   138,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   285,     0,     0,   445,     0,
       0,     0,     0,     0,     0,   470,     0,     0,     0,     0,
       0,     0,     0,   500,     0,   370,     0,     0,     0,     0,
       0,     0,     0,   378,     0,     0,     0,     0,   415,     0,
       0,     0,     0,   250,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   599,     0,
     671,     0,     0,     0,   660,    52,    45,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   580,
       0,     0,     0,     0,     0,     0,    75,     0,   148,   140,
       0,     0,     0,     0,     0,   331,   332,     0,     0,     0,
     287,     0,   447,     0,   486,     0,   489,   490,   472,     0,
       0,     0,     0,     0,     0,     0,   504,     0,     0,   394,
       0,     0,     0,   405,   382,     0,   434,   435,   419,     0,
       0,   252,   620,     0,     0,   625,     0,   628,   629,     0,
       0,   636,   637,     0,     0,   601,   673,     0,   667,   662,
       0,     0,     0,   652,   654,   656,   120,     0,     0,     0,
       0,   155,   134,   278,   371,   408,    42,   458,   460,   327,
     328,   329,   330,   326,   335,     0,    49,     0,     0,     0,
     493,   243,     0,     0,     0,   595,     0,   648,   650,     0,
      53,   147,   438,   463,   316,   318,   320,   324,   322,     0,
     456,   485,   488,   529,   517,   519,   521,   523,   525,   527,
     397,   197,   401,   399,   404,   431,   257,   259,   622,   624,
     627,   632,   633,   631,   635,   640,   641,   642,   643,   644,
     639,   646,   155,    46,     0,     0,     0,     0,   183,   189,
     191,   193,     0,     0,     0,     0,     0,   206,     0,     0,
     209,   211,   213,     0,     0,     0,   182,     0,   161,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   175,
     176,   177,   178,   173,   174,   179,   180,   181,     0,   159,
       0,   156,   157,   282,     0,   279,   280,   375,     0,   372,
     373,   412,     0,   409,   410,   339,     0,   336,   337,   228,
     229,     0,   224,   226,   227,     0,   237,   238,   234,     0,
     232,   235,   236,   220,     0,   217,   219,   540,     0,   538,
     497,     0,   494,   495,   247,     0,   244,   245,     0,     0,
       0,     0,     0,     0,     0,   262,   264,   265,   266,   267,
     268,   269,   570,   576,     0,     0,     0,   569,   566,   567,
     568,     0,   559,   561,   564,   562,   563,   565,   590,   592,
     589,   587,   588,     0,   583,   585,   586,     0,   679,     0,
     677,    55,   442,     0,   439,   440,   467,     0,   464,   465,
     534,   533,     0,   532,     0,    71,   669,   658,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
     692,   697,     0,   695,     0,     0,   694,   705,     0,     0,
       0,     0,   699,   701,   702,   703,   704,   696,     0,     0,
       0,     0,     0,   698,     0,   707,   708,   709,   700,   706
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,    54,  -875,  -480,
    -875,   366,  -875,  -875,  -875,  -875,   267,  -875,  -389,  -875,
    -875,  -875,   -74,  -875,  -875,  -875,   578,  -875,  -875,  -875,
    -875,   285,   490,  -875,  -875,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,     3,     7,    10,    15,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   287,   491,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   217,  -875,    38,  -875,  -622,    44,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     -21,  -875,  -650,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,    21,  -875,  -875,  -875,  -875,  -875,    30,  -641,
    -875,  -875,  -875,  -875,    26,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,    17,  -875,  -875,  -875,    20,   449,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,     8,  -875,  -875,  -875,
    -875,  -875,  -875,  -874,  -875,  -875,  -875,    47,  -875,  -875,
    -875,    51,   503,  -875,  -875,  -869,  -875,  -867,  -875,   -11,
    -875,    -5,  -875,    18,  -875,  -875,  -875,  -866,  -875,  -875,
    -875,  -875,    45,  -875,  -875,  -140,   866,  -875,  -875,  -875,
    -875,  -875,    50,  -875,  -875,  -875,    55,  -875,   468,  -875,
     -69,  -875,  -875,  -875,  -875,  -875,   -66,  -875,  -875,  -875,
    -875,  -875,   -58,  -875,  -875,  -875,    49,  -875,  -875,  -875,
      56,  -875,   464,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,     4,  -875,  -875,  -875,    11,   505,
    -875,  -875,   -53,  -875,   -29,  -875,  -875,  -875,  -875,  -875,
       5,  -875,  -875,  -875,     9,   507,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   -62,  -875,  -875,  -875,    48,  -875,  -875,
    -875,    40,  -875,   508,   282,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -864,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    53,  -875,  -875,  -875,
    -128,  -875,  -875,  -875,  -875,  -875,  -875,  -875,    33,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,    25,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   299,   462,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   -73,  -875,   -51,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     333,   460,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   345,
     465,   -44,  -875,  -875,    32,  -875,  -875,  -126,  -875,  -875,
    -875,  -875,  -875,  -875,  -149,  -875,  -875,  -163,  -875,  -875,
    -875,  -875,  -875
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   647,    92,    93,    43,    72,    89,    90,   671,   851,
     946,   947,   736,    45,    74,   101,   102,   103,   388,    47,
      75,   151,   152,   153,   396,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   414,   167,
     398,    49,    76,   198,   199,   200,   440,   201,   168,   399,
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
    1103,  1060,  1101,  1122,  1123,  1124,  1131,  1132,  1133,  1138,
    1134,  1135,  1136
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   150,   197,   214,   244,   258,   278,   215,   300,   319,
     336,   354,   372,   828,   321,   241,   788,   322,   758,   236,
     247,   261,   279,   202,   238,   251,   262,   280,   997,   314,
     332,   216,   355,   998,   373,   999,  1003,   217,  1009,    94,
     905,   218,   376,   906,   334,   335,    32,   203,   239,   252,
     263,   281,   272,   315,   333,   219,   356,   195,   196,   860,
     220,   301,   320,   221,   293,   294,   646,   245,   259,   779,
      44,    40,    46,   246,   260,    33,    48,    34,    50,    35,
     222,   646,   130,   131,   223,   908,    91,   224,   909,   108,
     109,    52,   225,   110,   394,   233,   111,   112,   113,   395,
      54,   438,   294,    56,   295,   296,   439,    58,   297,   298,
     299,   705,   706,   707,   708,    60,    99,   130,   131,   130,
     131,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    62,   129,   442,
     454,   129,   294,   822,   443,   455,   457,   709,   780,   243,
     383,   458,   723,   464,   130,   131,   130,   131,   465,   130,
     131,   132,  1049,    64,  1050,  1051,   133,   134,   135,   136,
     137,   492,   138,   130,   131,   211,   493,   139,   212,  1015,
    1016,   779,   786,    95,   787,   507,   140,    99,   677,   141,
     508,    66,    96,    97,    98,    68,   142,    70,   130,   131,
     683,   684,   685,   914,   143,   144,   915,   509,   145,   146,
      99,   997,   510,   149,   943,   513,   998,   944,   999,  1003,
     514,  1009,    99,   438,    99,   838,   839,   128,   865,   509,
     147,   148,  1127,   149,   866,  1128,  1129,  1130,   294,   316,
     295,   296,   317,   318,   823,   824,   825,   826,  1094,  1095,
    1096,    36,    37,    38,    39,   130,   131,   513,   442,    99,
     887,    99,   867,   868,    99,   888,   385,   788,   976,   808,
     809,   810,   811,   812,   813,   887,   384,   911,    99,   928,
     889,   718,   912,   386,   929,   828,   719,   720,   721,   722,
     723,   724,   725,   726,   727,   728,   729,   730,   731,   732,
     733,   734,   735,    99,   377,   378,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   935,   939,   294,
     100,   129,   936,   940,   507,   887,   387,   454,   473,   941,
    1081,   204,  1082,   205,  1125,   129,   393,  1126,   402,   130,
     131,   206,   207,   208,   209,   210,   132,   403,   253,   254,
     255,   256,   257,   130,   131,   334,   335,   404,   211,   405,
      99,   212,   139,   406,   150,  1085,   492,   474,   197,   213,
    1086,  1093,   211,  1104,   457,   212,   464,  1142,  1105,  1107,
     214,  1108,  1143,   244,   215,   649,   650,   651,   652,   202,
     258,   407,   241,   701,   702,   408,   236,   409,   410,   247,
     278,   238,   411,   412,   251,   413,   261,   431,   216,   441,
     300,   262,   449,   203,   217,   319,   279,   450,   218,   460,
     321,   280,   462,   322,   463,   239,   478,   475,   252,   483,
     482,   314,   219,   354,   372,   263,   332,   220,   515,   516,
     221,    99,   484,   488,    99,   281,   245,  1069,  1070,  1071,
    1072,   486,   246,   259,   355,   315,   373,   222,    99,   260,
     333,   223,   487,   301,   224,   376,   489,   517,   320,   225,
     494,   497,   233,   499,   500,   503,   504,   512,   356,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     518,   519,   127,   520,   129,   294,   521,   522,   524,   525,
     526,   527,   129,   528,   529,   542,   543,   530,   531,   532,
     533,   534,   130,   131,   538,   207,   208,   535,   210,   132,
     130,   131,   536,   537,   544,   539,   545,   540,   541,   546,
     547,   211,   548,   549,   212,   550,   551,   552,   271,   553,
     554,   555,   213,   556,   272,   273,   274,   275,   276,   277,
     557,   558,   560,   561,   559,   562,   563,   150,   564,   565,
     567,   568,   570,   571,   197,   572,   573,   574,   575,   576,
     577,   578,   579,   581,   633,   634,   635,   583,   584,   585,
     589,   590,   130,   131,   586,   202,   587,   591,   376,   827,
     840,   592,   354,   372,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,   203,
     829,   841,   593,   355,   594,   373,   595,    99,   597,   598,
     599,   600,   601,   602,   603,    99,   605,   606,   609,   607,
     610,   613,   612,   614,   830,   842,   615,   356,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   616,   619,   620,   623,   624,   617,   618,   147,   148,
     621,   622,   627,   628,   697,   630,   631,   632,   891,   636,
     637,   638,   639,   640,   641,   643,   644,   645,   793,   642,
      34,   654,   655,   656,   713,   648,   657,    99,   659,   658,
     660,   661,   667,   668,   662,   663,   664,   666,   669,   670,
     672,   673,   674,   712,   675,   676,   679,   759,   678,   763,
     767,   680,   771,   775,   797,   681,   800,   804,   848,   682,
     852,   686,   687,   688,   689,   690,   691,   704,   856,   873,
     874,   692,   875,   876,   693,   877,   879,   880,   694,   884,
     885,   695,   886,   892,  1119,   696,   698,   894,   895,   897,
     898,   699,   700,   711,   900,   901,   903,   904,   962,   907,
     918,   917,   920,   921,   949,   922,   923,   924,   925,   926,
     927,   932,   933,   934,   945,   950,   952,   953,   961,   955,
     957,   956,   958,   959,   960,   963,   964,   965,   966,   967,
     969,   968,   970,   971,  1013,   972,  1040,  1041,   973,  1046,
    1047,  1063,  1083,  1033,   974,  1034,  1062,  1035,  1068,  1084,
    1036,  1089,  1037,  1038,  1042,  1043,  1044,  1074,  1075,   214,
    1076,  1077,   300,   215,  1078,   319,  1079,  1080,   984,  1090,
     321,   241,   985,   322,  1087,   236,  1091,  1092,  1098,  1017,
     238,  1102,   278,   314,  1006,   336,   332,   216,  1099,  1007,
    1111,  1114,  1112,   217,  1116,  1019,   986,   218,   279,  1121,
    1020,   827,   987,   280,   239,   840,   988,   315,  1052,  1139,
     333,   219,  1100,  1008,   244,   301,   220,   258,   320,   221,
     989,   996,   829,  1115,  1021,   990,   841,   281,   991,  1054,
     247,  1000,  1018,   261,  1140,   251,   222,  1001,   262,  1106,
     223,  1109,  1141,   224,  1118,   992,   830,  1144,   225,   993,
     842,   233,   994,  1055,  1145,  1120,   714,   995,  1149,   252,
    1002,  1053,   263,   785,  1146,   717,  1147,   665,   566,   864,
     977,   975,  1014,   569,  1012,  1011,  1039,   245,  1032,  1031,
     259,   611,   979,   246,   978,  1110,   260,   292,   981,  1010,
     983,   980,   604,   608,  1065,   982,  1029,   580,  1067,  1064,
    1066,   861,   582,  1113,  1048,   847,  1030,  1028,  1045,   625,
     716,   588,   523,   629,   626,  1061,  1137,   715,  1117,  1148,
       0,     0,   596,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   984,     0,     0,     0,   985,     0,  1017,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1006,     0,     0,
    1052,     0,  1007,  1019,     0,     0,     0,     0,  1020,   986,
       0,     0,     0,     0,     0,   987,     0,     0,     0,   988,
       0,  1054,     0,     0,     0,     0,  1008,     0,     0,     0,
       0,     0,  1021,   989,   996,     0,     0,     0,   990,     0,
    1018,   991,     0,     0,  1000,  1055,     0,     0,     0,     0,
    1001,     0,     0,  1053,     0,     0,     0,     0,   992,     0,
       0,     0,   993,     0,     0,   994,     0,     0,     0,     0,
     995,     0,     0,  1002
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    85,   663,    83,    77,   657,    83,   640,    77,
      78,    79,    80,    76,    77,    78,    79,    80,   902,    82,
      83,    77,    85,   902,    85,   902,   902,    77,   902,    10,
       3,    77,    86,     6,   109,   110,     0,    76,    77,    78,
      79,    80,   100,    82,    83,    77,    85,    16,    17,   107,
      77,    82,    83,    77,    21,    59,   546,    78,    79,   102,
       7,    17,     7,    78,    79,     5,     7,     7,     7,     9,
      77,   561,    76,    77,    77,     3,   181,    77,     6,    11,
      12,     7,    77,    15,     3,    77,    18,    19,    20,     8,
       7,     3,    59,     7,    61,    62,     8,     7,    65,    66,
      67,   148,   149,   150,   151,     7,   181,    76,    77,    76,
      77,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,     7,    58,     3,
       3,    58,    59,    21,     8,     8,     3,   184,   181,    69,
       6,     8,    30,     3,    76,    77,    76,    77,     8,    76,
      77,    83,   156,     7,   158,   159,    88,    89,    90,    91,
      92,     3,    94,    76,    77,    95,     8,    99,    98,    96,
      97,   102,   103,   154,   105,     3,   108,   181,   577,   111,
       8,     7,   163,   164,   165,     7,   118,     7,    76,    77,
     589,   590,   591,     3,   126,   127,     6,     3,   130,   131,
     181,  1085,     8,   155,     3,     3,  1085,     6,  1085,  1085,
       8,  1085,   181,     3,   181,   128,   129,    57,     8,     3,
     152,   153,   157,   155,     8,   160,   161,   162,    59,    60,
      61,    62,    63,    64,   122,   123,   124,   125,   119,   120,
     121,   181,   182,   183,   184,    76,    77,     3,     3,   181,
       3,   181,     8,     8,   181,     8,     4,   908,   890,   112,
     113,   114,   115,   116,   117,     3,     3,     3,   181,     3,
       8,    21,     8,     8,     8,   935,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,   181,    13,    14,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,     3,     3,    59,
     394,    58,     8,     8,     3,     3,     3,     3,     8,     8,
       8,    68,     8,    70,     3,    58,     4,     6,     4,    76,
      77,    78,    79,    80,    81,    82,    83,     4,    71,    72,
      73,    74,    75,    76,    77,   109,   110,     4,    95,     4,
     181,    98,    99,     4,   438,     3,     3,     3,   442,   106,
       8,     8,    95,     3,     3,    98,     3,     3,     8,     8,
     454,     8,     8,   457,   454,    84,    85,    86,    87,   442,
     464,     4,   454,   145,   146,     4,   454,     4,     4,   457,
     474,   454,     4,     4,   457,     4,   464,     4,   454,     4,
     484,   464,     4,   442,   454,   489,   474,     4,   454,     4,
     489,   474,     4,   489,     4,   454,     4,     8,   457,     8,
       4,   484,   454,   507,   507,   464,   489,   454,   384,   385,
     454,   181,     3,     8,   181,   474,   457,    22,    23,    24,
      25,     4,   457,   464,   507,   484,   507,   454,   181,   464,
     489,   454,     4,   484,   454,   509,     3,   181,   489,   454,
       4,     4,   454,     4,     4,     4,     4,     4,   507,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       4,     4,    56,     4,    58,    59,     4,     4,     4,     4,
       4,     4,    58,     4,     4,     4,     4,   182,   182,   182,
     182,   182,    76,    77,   184,    79,    80,   182,    82,    83,
      76,    77,   182,   182,     4,   183,     4,   183,   182,     4,
       4,    95,     4,     4,    98,     4,     4,     4,    94,     4,
       4,     4,   106,     4,   100,   101,   102,   103,   104,   105,
       4,     4,     4,     4,   182,     4,     4,   631,     4,     4,
       4,   184,     4,     4,   638,     4,     4,     4,   182,   184,
       4,     4,     4,     4,   520,   521,   522,     4,   182,     4,
       4,     4,    76,    77,   182,   638,   182,     4,   632,   663,
     664,     4,   666,   666,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   638,
     663,   664,     4,   666,     4,   666,     4,   181,     4,     4,
     182,     4,     4,     4,   184,   181,     4,   184,     4,   184,
       4,     4,   184,     4,   663,   664,   182,   666,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,     4,     4,     4,     4,     4,   182,   182,   152,   153,
     184,   184,     4,   182,   610,     4,     7,     7,     6,   181,
       7,     7,     7,     7,     5,     5,     5,     5,    93,   181,
       7,     5,     5,     5,   630,   181,     5,   181,     5,     7,
       5,     5,   181,   181,     7,     7,     7,     7,     5,     5,
       5,     5,   181,     5,   181,   181,     7,     7,   181,     7,
       7,   181,     7,     7,     7,   181,     7,     7,     7,   181,
       7,   181,   181,   181,   181,   181,   181,   147,     7,     4,
       4,   181,     4,     4,   181,     4,     4,     4,   181,     4,
       4,   181,     4,     3,     5,   181,   181,     6,     3,     6,
       3,   181,   181,   181,     6,     3,     6,     3,   184,     6,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   181,     3,     6,     3,   182,     8,
       4,     6,     4,     4,     4,   182,   184,   182,     4,   182,
       4,   182,     4,     4,     4,   182,     4,     4,   182,     4,
       4,     3,     8,   182,   184,   182,     6,   182,     4,     8,
     182,     4,   182,   182,   182,   182,   182,   181,   181,   893,
     181,   181,   896,   893,   181,   899,   181,   181,   902,     8,
     899,   893,   902,   899,   181,   893,     3,     8,   181,   913,
     893,     4,   916,   896,   902,   919,   899,   893,   181,   902,
       4,     4,   184,   893,     4,   913,   902,   893,   916,     7,
     913,   935,   902,   916,   893,   939,   902,   896,   942,     4,
     899,   893,   181,   902,   948,   896,   893,   951,   899,   893,
     902,   902,   935,   182,   913,   902,   939,   916,   902,   942,
     948,   902,   913,   951,     4,   948,   893,   902,   951,   181,
     893,   181,     4,   893,   181,   902,   935,     4,   893,   902,
     939,   893,   902,   942,   184,   181,   631,   902,   181,   948,
     902,   942,   951,   656,   182,   638,   182,   561,   438,   712,
     892,   887,   911,   442,   908,   905,   928,   948,   921,   919,
     951,   492,   895,   948,   893,  1085,   951,    81,   898,   904,
     901,   896,   484,   489,   950,   899,   916,   454,   953,   948,
     951,   679,   457,  1091,   939,   666,   918,   914,   935,   507,
     637,   464,   394,   513,   509,   943,  1125,   632,  1104,  1142,
      -1,    -1,   474,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1085,    -1,    -1,    -1,  1085,    -1,  1091,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1085,    -1,    -1,
    1104,    -1,  1085,  1091,    -1,    -1,    -1,    -1,  1091,  1085,
      -1,    -1,    -1,    -1,    -1,  1085,    -1,    -1,    -1,  1085,
      -1,  1104,    -1,    -1,    -1,    -1,  1085,    -1,    -1,    -1,
      -1,    -1,  1091,  1085,  1085,    -1,    -1,    -1,  1085,    -1,
    1091,  1085,    -1,    -1,  1085,  1104,    -1,    -1,    -1,    -1,
    1085,    -1,    -1,  1104,    -1,    -1,    -1,    -1,  1085,    -1,
      -1,    -1,  1085,    -1,    -1,  1085,    -1,    -1,    -1,    -1,
    1085,    -1,    -1,  1085
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,     0,     5,     7,     9,   181,   182,   183,   184,
     202,   203,   204,   209,     7,   218,     7,   224,     7,   246,
       7,   344,     7,   421,     7,   437,     7,   454,     7,   373,
       7,   379,     7,   403,     7,   320,     7,   515,     7,   562,
       7,   553,   210,   205,   219,   225,   247,   345,   422,   438,
     455,   374,   380,   404,   321,   516,   563,   554,   202,   211,
     212,   181,   207,   208,    10,   154,   163,   164,   165,   181,
     217,   220,   221,   222,   545,   547,   549,   560,    11,    12,
      15,    18,    19,    20,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      76,    77,    83,    88,    89,    90,    91,    92,    94,    99,
     108,   111,   118,   126,   127,   130,   131,   152,   153,   155,
     217,   226,   227,   228,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   244,   253,   255,
     257,   294,   300,   306,   312,   314,   328,   338,   358,   363,
     371,   397,   427,   429,   448,   478,   490,   502,   503,   511,
     513,   541,   543,   551,   566,    16,    17,   217,   248,   249,
     250,   252,   427,   429,    68,    70,    78,    79,    80,    81,
      82,    95,    98,   106,   217,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   346,   347,   348,   350,
     352,   354,   356,   358,   361,   362,   397,   415,   427,   429,
     431,   448,   473,    69,   217,   354,   356,   397,   423,   424,
     425,   427,   429,    71,    72,    73,    74,    75,   217,   354,
     356,   397,   427,   429,   439,   440,   441,   443,   444,   446,
     447,    94,   100,   101,   102,   103,   104,   105,   217,   397,
     427,   429,   456,   457,   458,   459,   461,   463,   465,   467,
     469,   471,   371,    21,    59,    61,    62,    65,    66,    67,
     217,   275,   381,   382,   383,   384,   385,   386,   387,   389,
     391,   393,   394,   396,   427,   429,    60,    63,    64,   217,
     275,   385,   391,   405,   406,   407,   408,   409,   411,   412,
     413,   414,   427,   429,   109,   110,   217,   322,   323,   324,
     326,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   217,   427,   429,   517,   518,   519,
     520,   522,   524,   525,   527,   528,   529,   532,   534,   535,
     536,   539,   541,   543,   564,   565,   566,    13,    14,   555,
     556,   557,   559,     6,     3,     4,     8,     3,   223,   561,
     546,   548,   550,     4,     3,     8,   229,   552,   245,   254,
     256,   258,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   243,   339,   372,   398,   428,   430,
     359,   364,   301,   313,   307,   295,   479,   449,   315,   329,
     491,     4,   504,   512,   514,   542,   544,   567,     3,     8,
     251,     4,     3,     8,   416,   432,   349,   351,   353,     4,
       4,   357,   355,   474,     3,     8,   426,     3,     8,   442,
       4,   445,     4,     4,     3,     8,   472,   460,   462,   464,
     466,   468,   470,     8,     3,     8,   388,   276,     4,   392,
     390,   395,     4,     8,     3,   410,     4,     4,     8,     3,
     325,   327,     3,     8,     4,   521,   523,     4,   526,     4,
       4,   530,   533,     4,     4,   537,   540,     3,     8,     3,
       8,   558,     4,     3,     8,   202,   202,   181,     4,     4,
       4,     4,     4,   221,     4,     4,     4,     4,     4,     4,
     182,   182,   182,   182,   182,   182,   182,   182,   184,   183,
     183,   182,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   182,
       4,     4,     4,     4,     4,     4,   227,     4,   184,   249,
       4,     4,     4,     4,     4,   182,   184,     4,     4,     4,
     347,     4,   424,     4,   182,     4,   182,   182,   440,     4,
       4,     4,     4,     4,     4,     4,   458,     4,     4,   182,
       4,     4,     4,   184,   383,     4,   184,   184,   407,     4,
       4,   323,   184,     4,     4,   182,     4,   182,   182,     4,
       4,   184,   184,     4,     4,   518,   565,     4,   182,   556,
       4,     7,     7,   202,   202,   202,   181,     7,     7,     7,
       7,     5,   181,     5,     5,     5,   204,   206,   181,    84,
      85,    86,    87,   360,     5,     5,     5,     5,     7,     5,
       5,     5,     7,     7,     7,   206,     7,   181,   181,     5,
       5,   213,     5,     5,   181,   181,   181,   213,   181,     7,
     181,   181,   181,   213,   213,   213,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   202,   181,   181,
     181,   145,   146,   531,   147,   148,   149,   150,   151,   184,
     538,   181,     5,   202,   226,   564,   555,   248,    21,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,   217,   263,   264,   265,
     268,   270,   272,   274,   275,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   287,   288,   290,   292,   263,     7,
     259,   260,   261,     7,   340,   341,   342,     7,   375,   376,
     377,     7,   399,   400,   401,     7,   365,   366,   367,   102,
     181,   302,   303,   304,   305,   211,   103,   105,   304,   308,
     309,   310,   311,    93,   296,   297,   298,     7,   480,   481,
       7,   450,   451,   452,     7,   316,   317,   318,   112,   113,
     114,   115,   116,   117,   330,   331,   332,   333,   334,   335,
     336,   337,    21,   122,   123,   124,   125,   217,   277,   427,
     429,   492,   493,   494,   497,   498,   500,   501,   128,   129,
     217,   427,   429,   505,   506,   507,   509,   517,     7,   568,
     569,   214,     7,   417,   418,   419,     7,   433,   434,   435,
     107,   459,   475,   476,   259,     8,     8,     8,     8,   266,
     269,   271,   273,     4,     4,     4,     4,     4,   286,     4,
       4,   289,   291,   293,     4,     4,     4,     3,     8,     8,
     262,     6,     3,   343,     6,     3,   378,     6,     3,   402,
       6,     3,   368,     6,     3,     3,     6,     6,     3,     6,
     299,     3,     8,   482,     3,     6,   453,     6,     3,   319,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     495,   499,     4,     4,     4,     3,     8,   508,   510,     3,
       8,     8,   570,     3,     6,   181,   215,   216,   420,     6,
       3,   436,     6,     3,   477,     8,     6,     4,     4,     4,
       4,   182,   184,   182,   184,   182,     4,   182,   182,     4,
       4,     4,   182,   182,   184,   264,   263,   261,   346,   342,
     381,   377,   405,   401,   217,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   275,   338,   350,   352,
     354,   356,   358,   362,   369,   370,   397,   427,   429,   473,
     367,   303,   309,     4,   297,    96,    97,   217,   275,   397,
     427,   429,   483,   484,   485,   486,   487,   489,   481,   456,
     452,   322,   318,   182,   182,   182,   182,   182,   182,   331,
       4,     4,   182,   182,   182,   493,     4,     4,   506,   156,
     158,   159,   217,   275,   427,   429,   571,   572,   573,   574,
     576,   569,     6,     3,   423,   419,   439,   435,     4,    22,
      23,    24,    25,   267,   181,   181,   181,   181,   181,   181,
     181,     8,     8,     8,     8,     3,     8,   181,   488,     4,
       8,     3,     8,     8,   119,   120,   121,   496,   181,   181,
     181,   577,     4,   575,     3,     8,   181,     8,     8,   181,
     370,     4,   184,   485,     4,   182,     4,   572,   181,     5,
     181,     7,   578,   579,   580,     3,     6,   157,   160,   161,
     162,   581,   582,   583,   585,   586,   587,   579,   584,     4,
       4,     4,     3,     8,     4,   184,   182,   182,   582,   181
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   185,   187,   186,   188,   186,   189,   186,   190,   186,
     191,   186,   192,   186,   193,   186,   194,   186,   195,   186,
     196,   186,   197,   186,   198,   186,   199,   186,   200,   186,
     201,   186,   202,   202,   202,   202,   202,   202,   202,   203,
     205,   204,   206,   207,   207,   208,   208,   210,   209,   211,
     211,   212,   212,   214,   213,   215,   215,   216,   216,   217,
     219,   218,   220,   220,   221,   221,   221,   221,   221,   221,
     223,   222,   225,   224,   226,   226,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   229,
     228,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   243,   242,   245,   244,   247,   246,   248,
     248,   249,   249,   249,   249,   249,   251,   250,   252,   254,
     253,   256,   255,   258,   257,   259,   259,   260,   260,   262,
     261,   263,   263,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   266,   265,   267,   267,   267,   267,   269,
     268,   271,   270,   273,   272,   274,   276,   275,   277,   278,
     279,   280,   281,   282,   283,   284,   286,   285,   287,   289,
     288,   291,   290,   293,   292,   295,   294,   296,   296,   297,
     299,   298,   301,   300,   302,   302,   303,   303,   304,   305,
     307,   306,   308,   308,   309,   309,   309,   310,   311,   313,
     312,   315,   314,   316,   316,   317,   317,   319,   318,   321,
     320,   322,   322,   322,   323,   323,   325,   324,   327,   326,
     329,   328,   330,   330,   331,   331,   331,   331,   331,   331,
     332,   333,   334,   335,   336,   337,   339,   338,   340,   340,
     341,   341,   343,   342,   345,   344,   346,   346,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   349,   348,   351,   350,   353,
     352,   355,   354,   357,   356,   359,   358,   360,   360,   360,
     360,   361,   362,   364,   363,   365,   365,   366,   366,   368,
     367,   369,   369,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   372,   371,   374,
     373,   375,   375,   376,   376,   378,   377,   380,   379,   381,
     381,   382,   382,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   384,   385,   386,   388,   387,   390,   389,
     392,   391,   393,   395,   394,   396,   398,   397,   399,   399,
     400,   400,   402,   401,   404,   403,   405,   405,   406,   406,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   408,
     410,   409,   411,   412,   413,   414,   416,   415,   417,   417,
     418,   418,   420,   419,   422,   421,   423,   423,   424,   424,
     424,   424,   424,   424,   424,   426,   425,   428,   427,   430,
     429,   432,   431,   433,   433,   434,   434,   436,   435,   438,
     437,   439,   439,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   442,   441,   443,   445,   444,   446,
     447,   449,   448,   450,   450,   451,   451,   453,   452,   455,
     454,   456,   456,   457,   457,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   460,   459,   462,   461,
     464,   463,   466,   465,   468,   467,   470,   469,   472,   471,
     474,   473,   475,   475,   477,   476,   479,   478,   480,   480,
     482,   481,   483,   483,   484,   484,   485,   485,   485,   485,
     485,   485,   485,   486,   488,   487,   489,   491,   490,   492,
     492,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     495,   494,   496,   496,   496,   497,   499,   498,   500,   501,
     502,   504,   503,   505,   505,   506,   506,   506,   506,   506,
     508,   507,   510,   509,   512,   511,   514,   513,   516,   515,
     517,   517,   518,   518,   518,   518,   518,   518,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     519,   521,   520,   523,   522,   524,   526,   525,   527,   528,
     530,   529,   531,   531,   533,   532,   534,   535,   537,   536,
     538,   538,   538,   538,   538,   540,   539,   542,   541,   544,
     543,   546,   545,   548,   547,   550,   549,   552,   551,   554,
     553,   555,   555,   556,   556,   558,   557,   559,   561,   560,
     563,   562,   564,   564,   565,   567,   566,   568,   568,   570,
     569,   571,   571,   572,   572,   572,   572,   572,   572,   572,
     573,   575,   574,   577,   576,   578,   578,   580,   579,   581,
     581,   582,   582,   582,   582,   584,   583,   585,   586,   587
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
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     3,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"tcp-nodelay\"", "\"preferred-lifetime\"",
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
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
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
  "readonly", "connect_timeout", "reconnect_wait_time", "request_timeout",
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
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   269,   269,   269,   270,   270,   271,   271,   272,   272,
     273,   273,   274,   274,   275,   275,   276,   276,   277,   277,
     278,   278,   279,   279,   280,   280,   281,   281,   282,   282,
     283,   283,   291,   292,   293,   294,   295,   296,   297,   300,
     305,   305,   316,   319,   320,   323,   327,   334,   334,   341,
     342,   345,   349,   356,   356,   363,   364,   367,   371,   382,
     392,   392,   407,   408,   412,   413,   414,   415,   416,   417,
     420,   420,   435,   435,   444,   445,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   495,
     495,   503,   508,   513,   518,   523,   528,   533,   538,   543,
     548,   553,   558,   563,   563,   571,   571,   582,   582,   591,
     592,   595,   596,   597,   598,   599,   602,   602,   612,   618,
     618,   630,   630,   642,   642,   652,   653,   656,   657,   660,
     660,   670,   671,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   688,   689,   690,
     691,   692,   693,   696,   696,   703,   704,   705,   706,   709,
     709,   717,   717,   725,   725,   733,   738,   738,   746,   751,
     756,   761,   766,   771,   776,   781,   786,   786,   794,   799,
     799,   807,   807,   815,   815,   823,   823,   833,   834,   836,
     838,   838,   856,   856,   866,   867,   870,   871,   874,   879,
     884,   884,   894,   895,   898,   899,   900,   903,   908,   915,
     915,   925,   925,   935,   936,   939,   940,   943,   943,   953,
     953,   963,   964,   965,   968,   969,   972,   972,   980,   980,
     988,   988,   999,  1000,  1003,  1004,  1005,  1006,  1007,  1008,
    1011,  1016,  1021,  1026,  1031,  1036,  1044,  1044,  1057,  1058,
    1061,  1062,  1069,  1069,  1095,  1095,  1106,  1107,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,
    1133,  1134,  1135,  1136,  1137,  1140,  1140,  1148,  1148,  1156,
    1156,  1164,  1164,  1172,  1172,  1182,  1182,  1189,  1190,  1191,
    1192,  1195,  1200,  1208,  1208,  1219,  1220,  1224,  1225,  1228,
    1228,  1236,  1237,  1240,  1241,  1242,  1243,  1244,  1245,  1246,
    1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,
    1257,  1258,  1259,  1260,  1261,  1262,  1263,  1270,  1270,  1283,
    1283,  1292,  1293,  1296,  1297,  1302,  1302,  1317,  1317,  1331,
    1332,  1335,  1336,  1339,  1340,  1341,  1342,  1343,  1344,  1345,
    1346,  1347,  1348,  1351,  1353,  1358,  1360,  1360,  1368,  1368,
    1376,  1376,  1384,  1386,  1386,  1394,  1403,  1403,  1415,  1416,
    1421,  1422,  1427,  1427,  1439,  1439,  1451,  1452,  1457,  1458,
    1463,  1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,  1474,
    1476,  1476,  1484,  1486,  1488,  1493,  1501,  1501,  1513,  1514,
    1517,  1518,  1521,  1521,  1531,  1531,  1540,  1541,  1544,  1545,
    1546,  1547,  1548,  1549,  1550,  1553,  1553,  1561,  1561,  1586,
    1586,  1616,  1616,  1628,  1629,  1632,  1633,  1636,  1636,  1648,
    1648,  1660,  1661,  1664,  1665,  1666,  1667,  1668,  1669,  1670,
    1671,  1672,  1673,  1674,  1677,  1677,  1685,  1690,  1690,  1698,
    1703,  1711,  1711,  1721,  1722,  1725,  1726,  1729,  1729,  1738,
    1738,  1747,  1748,  1751,  1752,  1756,  1757,  1758,  1759,  1760,
    1761,  1762,  1763,  1764,  1765,  1766,  1769,  1769,  1779,  1779,
    1789,  1789,  1797,  1797,  1805,  1805,  1813,  1813,  1821,  1821,
    1834,  1834,  1844,  1845,  1848,  1848,  1859,  1859,  1869,  1870,
    1873,  1873,  1883,  1884,  1887,  1888,  1891,  1892,  1893,  1894,
    1895,  1896,  1897,  1900,  1902,  1902,  1910,  1918,  1918,  1930,
    1931,  1934,  1935,  1936,  1937,  1938,  1939,  1940,  1941,  1942,
    1945,  1945,  1952,  1953,  1954,  1957,  1962,  1962,  1970,  1975,
    1982,  1989,  1989,  1999,  2000,  2003,  2004,  2005,  2006,  2007,
    2010,  2010,  2018,  2018,  2028,  2028,  2068,  2068,  2080,  2080,
    2090,  2091,  2094,  2095,  2096,  2097,  2098,  2099,  2100,  2101,
    2102,  2103,  2104,  2105,  2106,  2107,  2108,  2109,  2110,  2111,
    2114,  2119,  2119,  2127,  2127,  2135,  2140,  2140,  2148,  2153,
    2158,  2158,  2166,  2167,  2170,  2170,  2178,  2183,  2188,  2188,
    2196,  2199,  2202,  2205,  2208,  2214,  2214,  2222,  2222,  2230,
    2230,  2240,  2240,  2247,  2247,  2254,  2254,  2263,  2263,  2274,
    2274,  2284,  2285,  2289,  2290,  2293,  2293,  2303,  2313,  2313,
    2323,  2323,  2334,  2335,  2339,  2343,  2343,  2355,  2356,  2360,
    2360,  2368,  2369,  2372,  2373,  2374,  2375,  2376,  2377,  2378,
    2381,  2386,  2386,  2394,  2394,  2404,  2405,  2408,  2408,  2416,
    2417,  2420,  2421,  2422,  2423,  2426,  2426,  2434,  2439,  2444
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
#line 5258 "dhcp6_parser.cc"

#line 2449 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
