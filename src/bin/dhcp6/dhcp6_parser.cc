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

  case 117:
#line 493 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 118:
#line 495 "dhcp6_parser.yy"
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc"
    break;

  case 119:
#line 501 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1086 "dhcp6_parser.cc"
    break;

  case 120:
#line 506 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1095 "dhcp6_parser.cc"
    break;

  case 121:
#line 511 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 122:
#line 516 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1113 "dhcp6_parser.cc"
    break;

  case 123:
#line 521 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1122 "dhcp6_parser.cc"
    break;

  case 124:
#line 526 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1131 "dhcp6_parser.cc"
    break;

  case 125:
#line 531 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1140 "dhcp6_parser.cc"
    break;

  case 126:
#line 536 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1149 "dhcp6_parser.cc"
    break;

  case 127:
#line 541 "dhcp6_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1158 "dhcp6_parser.cc"
    break;

  case 128:
#line 546 "dhcp6_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1167 "dhcp6_parser.cc"
    break;

  case 129:
#line 551 "dhcp6_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1176 "dhcp6_parser.cc"
    break;

  case 130:
#line 556 "dhcp6_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 131:
#line 561 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 132:
#line 563 "dhcp6_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 133:
#line 569 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 134:
#line 574 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 135:
#line 580 "dhcp6_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 136:
#line 584 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 144:
#line 600 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 145:
#line 605 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 146:
#line 610 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 147:
#line 616 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 148:
#line 621 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "dhcp6_parser.cc"
    break;

  case 149:
#line 628 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 150:
#line 633 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc"
    break;

  case 151:
#line 640 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1327 "dhcp6_parser.cc"
    break;

  case 152:
#line 645 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc"
    break;

  case 157:
#line 658 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1346 "dhcp6_parser.cc"
    break;

  case 158:
#line 662 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1356 "dhcp6_parser.cc"
    break;

  case 181:
#line 694 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1364 "dhcp6_parser.cc"
    break;

  case 182:
#line 696 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 183:
#line 701 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1379 "dhcp6_parser.cc"
    break;

  case 184:
#line 702 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1385 "dhcp6_parser.cc"
    break;

  case 185:
#line 703 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1391 "dhcp6_parser.cc"
    break;

  case 186:
#line 704 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1397 "dhcp6_parser.cc"
    break;

  case 187:
#line 707 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1405 "dhcp6_parser.cc"
    break;

  case 188:
#line 709 "dhcp6_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1415 "dhcp6_parser.cc"
    break;

  case 189:
#line 715 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp6_parser.cc"
    break;

  case 190:
#line 717 "dhcp6_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1433 "dhcp6_parser.cc"
    break;

  case 191:
#line 723 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 192:
#line 725 "dhcp6_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 193:
#line 731 "dhcp6_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 194:
#line 736 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp6_parser.cc"
    break;

  case 195:
#line 738 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1478 "dhcp6_parser.cc"
    break;

  case 196:
#line 744 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1487 "dhcp6_parser.cc"
    break;

  case 197:
#line 749 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1496 "dhcp6_parser.cc"
    break;

  case 198:
#line 754 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1505 "dhcp6_parser.cc"
    break;

  case 199:
#line 759 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1514 "dhcp6_parser.cc"
    break;

  case 200:
#line 764 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1523 "dhcp6_parser.cc"
    break;

  case 201:
#line 769 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 202:
#line 774 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 203:
#line 779 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 204:
#line 784 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp6_parser.cc"
    break;

  case 205:
#line 786 "dhcp6_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1568 "dhcp6_parser.cc"
    break;

  case 206:
#line 792 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 207:
#line 797 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1585 "dhcp6_parser.cc"
    break;

  case 208:
#line 799 "dhcp6_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1595 "dhcp6_parser.cc"
    break;

  case 209:
#line 805 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc"
    break;

  case 210:
#line 807 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc"
    break;

  case 211:
#line 813 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 212:
#line 815 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 213:
#line 821 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1642 "dhcp6_parser.cc"
    break;

  case 214:
#line 826 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1651 "dhcp6_parser.cc"
    break;

  case 218:
#line 836 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1659 "dhcp6_parser.cc"
    break;

  case 219:
#line 838 "dhcp6_parser.yy"
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

  case 220:
#line 854 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1690 "dhcp6_parser.cc"
    break;

  case 221:
#line 859 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 226:
#line 872 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 227:
#line 877 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1717 "dhcp6_parser.cc"
    break;

  case 228:
#line 882 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 229:
#line 887 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 235:
#line 901 "dhcp6_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 236:
#line 906 "dhcp6_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 237:
#line 913 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp6_parser.cc"
    break;

  case 238:
#line 918 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 239:
#line 923 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1786 "dhcp6_parser.cc"
    break;

  case 240:
#line 928 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 245:
#line 941 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 246:
#line 945 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 247:
#line 951 "dhcp6_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 248:
#line 955 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 254:
#line 970 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1843 "dhcp6_parser.cc"
    break;

  case 255:
#line 972 "dhcp6_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 256:
#line 978 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc"
    break;

  case 257:
#line 980 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 258:
#line 986 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1881 "dhcp6_parser.cc"
    break;

  case 259:
#line 991 "dhcp6_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1891 "dhcp6_parser.cc"
    break;

  case 268:
#line 1009 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 269:
#line 1014 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 270:
#line 1019 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 271:
#line 1024 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1927 "dhcp6_parser.cc"
    break;

  case 272:
#line 1029 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 273:
#line 1034 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1945 "dhcp6_parser.cc"
    break;

  case 274:
#line 1042 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 275:
#line 1047 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1965 "dhcp6_parser.cc"
    break;

  case 280:
#line 1067 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 281:
#line 1071 "dhcp6_parser.yy"
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

  case 282:
#line 1093 "dhcp6_parser.yy"
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 283:
#line 1097 "dhcp6_parser.yy"
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 313:
#line 1138 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 314:
#line 1140 "dhcp6_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2039 "dhcp6_parser.cc"
    break;

  case 315:
#line 1146 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 316:
#line 1148 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 317:
#line 1154 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 318:
#line 1156 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 319:
#line 1162 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 320:
#line 1164 "dhcp6_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 321:
#line 1170 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2104 "dhcp6_parser.cc"
    break;

  case 322:
#line 1175 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 323:
#line 1180 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2121 "dhcp6_parser.cc"
    break;

  case 324:
#line 1182 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2130 "dhcp6_parser.cc"
    break;

  case 325:
#line 1187 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2136 "dhcp6_parser.cc"
    break;

  case 326:
#line 1188 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2142 "dhcp6_parser.cc"
    break;

  case 327:
#line 1189 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2148 "dhcp6_parser.cc"
    break;

  case 328:
#line 1190 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2154 "dhcp6_parser.cc"
    break;

  case 329:
#line 1193 "dhcp6_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2163 "dhcp6_parser.cc"
    break;

  case 330:
#line 1198 "dhcp6_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2172 "dhcp6_parser.cc"
    break;

  case 331:
#line 1206 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 332:
#line 1211 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 337:
#line 1226 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 338:
#line 1230 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2210 "dhcp6_parser.cc"
    break;

  case 365:
#line 1268 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 366:
#line 1273 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2230 "dhcp6_parser.cc"
    break;

  case 367:
#line 1281 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 368:
#line 1284 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 2247 "dhcp6_parser.cc"
    break;

  case 373:
#line 1300 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 374:
#line 1304 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 375:
#line 1315 "dhcp6_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2279 "dhcp6_parser.cc"
    break;

  case 376:
#line 1319 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2291 "dhcp6_parser.cc"
    break;

  case 392:
#line 1351 "dhcp6_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2300 "dhcp6_parser.cc"
    break;

  case 394:
#line 1358 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp6_parser.cc"
    break;

  case 395:
#line 1360 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 396:
#line 1366 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc"
    break;

  case 397:
#line 1368 "dhcp6_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 398:
#line 1374 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 399:
#line 1376 "dhcp6_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2354 "dhcp6_parser.cc"
    break;

  case 401:
#line 1384 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 402:
#line 1386 "dhcp6_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 403:
#line 1392 "dhcp6_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2381 "dhcp6_parser.cc"
    break;

  case 404:
#line 1401 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2392 "dhcp6_parser.cc"
    break;

  case 405:
#line 1406 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2401 "dhcp6_parser.cc"
    break;

  case 410:
#line 1425 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2411 "dhcp6_parser.cc"
    break;

  case 411:
#line 1429 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2420 "dhcp6_parser.cc"
    break;

  case 412:
#line 1437 "dhcp6_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2430 "dhcp6_parser.cc"
    break;

  case 413:
#line 1441 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2439 "dhcp6_parser.cc"
    break;

  case 428:
#line 1474 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2447 "dhcp6_parser.cc"
    break;

  case 429:
#line 1476 "dhcp6_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2457 "dhcp6_parser.cc"
    break;

  case 432:
#line 1486 "dhcp6_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 433:
#line 1491 "dhcp6_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 434:
#line 1499 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 435:
#line 1504 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2495 "dhcp6_parser.cc"
    break;

  case 440:
#line 1519 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2505 "dhcp6_parser.cc"
    break;

  case 441:
#line 1523 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2515 "dhcp6_parser.cc"
    break;

  case 442:
#line 1529 "dhcp6_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 443:
#line 1533 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2534 "dhcp6_parser.cc"
    break;

  case 453:
#line 1551 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2542 "dhcp6_parser.cc"
    break;

  case 454:
#line 1553 "dhcp6_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2552 "dhcp6_parser.cc"
    break;

  case 455:
#line 1559 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 456:
#line 1561 "dhcp6_parser.yy"
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

  case 457:
#line 1584 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2595 "dhcp6_parser.cc"
    break;

  case 458:
#line 1586 "dhcp6_parser.yy"
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

  case 459:
#line 1614 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2635 "dhcp6_parser.cc"
    break;

  case 460:
#line 1619 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2644 "dhcp6_parser.cc"
    break;

  case 465:
#line 1634 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2654 "dhcp6_parser.cc"
    break;

  case 466:
#line 1638 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 467:
#line 1646 "dhcp6_parser.yy"
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp6_parser.cc"
    break;

  case 468:
#line 1650 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 482:
#line 1675 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp6_parser.cc"
    break;

  case 483:
#line 1677 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc"
    break;

  case 484:
#line 1683 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 485:
#line 1688 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 486:
#line 1690 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc"
    break;

  case 487:
#line 1696 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2742 "dhcp6_parser.cc"
    break;

  case 488:
#line 1701 "dhcp6_parser.yy"
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 489:
#line 1709 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2762 "dhcp6_parser.cc"
    break;

  case 490:
#line 1714 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2771 "dhcp6_parser.cc"
    break;

  case 495:
#line 1727 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 496:
#line 1731 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2790 "dhcp6_parser.cc"
    break;

  case 497:
#line 1736 "dhcp6_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2800 "dhcp6_parser.cc"
    break;

  case 498:
#line 1740 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2809 "dhcp6_parser.cc"
    break;

  case 514:
#line 1767 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp6_parser.cc"
    break;

  case 515:
#line 1772 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 516:
#line 1777 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2840 "dhcp6_parser.cc"
    break;

  case 517:
#line 1782 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 518:
#line 1787 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2857 "dhcp6_parser.cc"
    break;

  case 519:
#line 1789 "dhcp6_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 520:
#line 1795 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 521:
#line 1797 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 522:
#line 1803 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 523:
#line 1805 "dhcp6_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 524:
#line 1811 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 525:
#line 1813 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 526:
#line 1819 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp6_parser.cc"
    break;

  case 527:
#line 1824 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 528:
#line 1832 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 529:
#line 1837 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2961 "dhcp6_parser.cc"
    break;

  case 532:
#line 1846 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2969 "dhcp6_parser.cc"
    break;

  case 533:
#line 1848 "dhcp6_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2979 "dhcp6_parser.cc"
    break;

  case 534:
#line 1857 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2990 "dhcp6_parser.cc"
    break;

  case 535:
#line 1862 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2999 "dhcp6_parser.cc"
    break;

  case 538:
#line 1871 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3009 "dhcp6_parser.cc"
    break;

  case 539:
#line 1875 "dhcp6_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3019 "dhcp6_parser.cc"
    break;

  case 552:
#line 1900 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 553:
#line 1902 "dhcp6_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 554:
#line 1908 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3046 "dhcp6_parser.cc"
    break;

  case 555:
#line 1916 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 556:
#line 1921 "dhcp6_parser.yy"
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3068 "dhcp6_parser.cc"
    break;

  case 568:
#line 1943 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 569:
#line 1945 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3085 "dhcp6_parser.cc"
    break;

  case 570:
#line 1950 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3091 "dhcp6_parser.cc"
    break;

  case 571:
#line 1951 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3097 "dhcp6_parser.cc"
    break;

  case 572:
#line 1952 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3103 "dhcp6_parser.cc"
    break;

  case 573:
#line 1955 "dhcp6_parser.yy"
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 574:
#line 1960 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3120 "dhcp6_parser.cc"
    break;

  case 575:
#line 1962 "dhcp6_parser.yy"
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 576:
#line 1968 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3139 "dhcp6_parser.cc"
    break;

  case 577:
#line 1973 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3148 "dhcp6_parser.cc"
    break;

  case 578:
#line 1980 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 579:
#line 1987 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 580:
#line 1992 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 588:
#line 2008 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp6_parser.cc"
    break;

  case 589:
#line 2010 "dhcp6_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 590:
#line 2016 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp6_parser.cc"
    break;

  case 591:
#line 2018 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3213 "dhcp6_parser.cc"
    break;

  case 592:
#line 2026 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 593:
#line 2028 "dhcp6_parser.yy"
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

  case 594:
#line 2066 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3272 "dhcp6_parser.cc"
    break;

  case 595:
#line 2071 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3283 "dhcp6_parser.cc"
    break;

  case 596:
#line 2078 "dhcp6_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 597:
#line 2082 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3303 "dhcp6_parser.cc"
    break;

  case 618:
#line 2112 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3312 "dhcp6_parser.cc"
    break;

  case 619:
#line 2117 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3320 "dhcp6_parser.cc"
    break;

  case 620:
#line 2119 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3330 "dhcp6_parser.cc"
    break;

  case 621:
#line 2125 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 622:
#line 2127 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 623:
#line 2133 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 624:
#line 2138 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3365 "dhcp6_parser.cc"
    break;

  case 625:
#line 2140 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3375 "dhcp6_parser.cc"
    break;

  case 626:
#line 2146 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 627:
#line 2151 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 628:
#line 2156 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3401 "dhcp6_parser.cc"
    break;

  case 629:
#line 2158 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 630:
#line 2164 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3416 "dhcp6_parser.cc"
    break;

  case 631:
#line 2165 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3422 "dhcp6_parser.cc"
    break;

  case 632:
#line 2168 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3430 "dhcp6_parser.cc"
    break;

  case 633:
#line 2170 "dhcp6_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3440 "dhcp6_parser.cc"
    break;

  case 634:
#line 2176 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 635:
#line 2181 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 636:
#line 2186 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3466 "dhcp6_parser.cc"
    break;

  case 637:
#line 2188 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3475 "dhcp6_parser.cc"
    break;

  case 638:
#line 2194 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3483 "dhcp6_parser.cc"
    break;

  case 639:
#line 2197 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3491 "dhcp6_parser.cc"
    break;

  case 640:
#line 2200 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3499 "dhcp6_parser.cc"
    break;

  case 641:
#line 2203 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3507 "dhcp6_parser.cc"
    break;

  case 642:
#line 2206 "dhcp6_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3516 "dhcp6_parser.cc"
    break;

  case 643:
#line 2212 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3524 "dhcp6_parser.cc"
    break;

  case 644:
#line 2214 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 645:
#line 2220 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 646:
#line 2222 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 647:
#line 2228 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 648:
#line 2230 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 649:
#line 2238 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 650:
#line 2240 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3587 "dhcp6_parser.cc"
    break;

  case 651:
#line 2245 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 652:
#line 2247 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 653:
#line 2252 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp6_parser.cc"
    break;

  case 654:
#line 2254 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 655:
#line 2261 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3632 "dhcp6_parser.cc"
    break;

  case 656:
#line 2266 "dhcp6_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 657:
#line 2272 "dhcp6_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 658:
#line 2276 "dhcp6_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3661 "dhcp6_parser.cc"
    break;

  case 663:
#line 2291 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3672 "dhcp6_parser.cc"
    break;

  case 664:
#line 2296 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3681 "dhcp6_parser.cc"
    break;

  case 665:
#line 2301 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 666:
#line 2311 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 667:
#line 2316 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3710 "dhcp6_parser.cc"
    break;

  case 668:
#line 2321 "dhcp6_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 669:
#line 2325 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 673:
#line 2341 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 674:
#line 2346 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3748 "dhcp6_parser.cc"
    break;

  case 677:
#line 2358 "dhcp6_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 678:
#line 2362 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 688:
#line 2379 "dhcp6_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 689:
#line 2384 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3783 "dhcp6_parser.cc"
    break;

  case 690:
#line 2386 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 691:
#line 2392 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 692:
#line 2397 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 695:
#line 2406 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3823 "dhcp6_parser.cc"
    break;

  case 696:
#line 2410 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 703:
#line 2424 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3839 "dhcp6_parser.cc"
    break;

  case 704:
#line 2426 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3849 "dhcp6_parser.cc"
    break;

  case 705:
#line 2432 "dhcp6_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3858 "dhcp6_parser.cc"
    break;

  case 706:
#line 2437 "dhcp6_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 707:
#line 2442 "dhcp6_parser.yy"
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


  const short Dhcp6Parser::yypact_ninf_ = -873;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     486,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,    38,    36,    33,    47,
      49,    62,   114,   118,   149,   161,   162,   175,   195,   199,
     203,   205,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,    36,  -133,    24,   181,    42,   448,    81,    72,
      59,    31,    61,   261,   -57,   214,    40,   127,  -873,   235,
     253,   299,   257,   281,  -873,  -873,  -873,  -873,  -873,   313,
    -873,    41,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,   338,   339,   355,   357,   367,   368,
     369,   371,   377,   383,   387,   395,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,   404,  -873,  -873,  -873,  -873,  -873,    84,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,   405,  -873,   172,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,   406,   409,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,   178,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,   182,  -873,  -873,  -873,  -873,  -873,
     411,  -873,   414,   417,  -873,  -873,  -873,  -873,  -873,  -873,
     251,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,   298,   382,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,   333,  -873,
    -873,   418,  -873,  -873,  -873,   428,  -873,  -873,   393,   400,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,   432,   433,  -873,  -873,  -873,  -873,   435,
     437,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,   273,  -873,  -873,  -873,   440,  -873,  -873,
     444,  -873,   449,   450,  -873,  -873,   452,   454,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,   279,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,   290,  -873,  -873,  -873,   456,   292,  -873,  -873,
    -873,  -873,    36,    36,  -873,   271,   457,   462,   465,   467,
     469,  -873,    24,  -873,   470,   472,   473,   474,   480,   481,
     259,   304,   305,   306,   307,   320,   321,   322,   328,   334,
     340,   329,   501,   503,   504,   505,   506,   515,   516,   517,
     518,   528,   529,   530,   531,   532,   533,   534,   535,   358,
     537,   538,   540,   541,   181,  -873,   544,   365,    42,  -873,
     546,   547,   548,   549,   552,   375,   374,   555,   556,   557,
     448,  -873,   559,    81,  -873,   560,   384,   561,   385,   386,
      72,  -873,   566,   567,   568,   569,   570,   571,   572,  -873,
      59,  -873,   573,   574,   401,   575,   577,   578,   402,  -873,
      61,   580,   407,   408,  -873,   261,   581,   585,   112,  -873,
     410,   589,   591,   415,   594,   420,   421,   595,   596,   412,
     423,   600,   605,   606,   607,   214,  -873,    40,  -873,   608,
     431,   127,  -873,  -873,  -873,   610,   609,   611,    36,    36,
      36,  -873,   434,   612,   613,   615,   617,   620,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
     436,   621,   622,   623,   624,   451,   341,   625,   628,   629,
     662,   663,   668,   671,   672,   673,   674,  -873,   675,   624,
     676,   679,  -873,   680,  -873,  -873,   681,   683,   497,   498,
     508,  -873,  -873,   680,   510,   685,  -873,   512,  -873,   513,
    -873,   514,  -873,  -873,  -873,   680,   680,   680,   519,   520,
     521,   522,  -873,   523,   524,  -873,   525,   526,   527,  -873,
    -873,   536,  -873,  -873,  -873,   539,    36,  -873,  -873,   542,
     543,  -873,   545,  -873,  -873,   170,   550,  -873,  -873,    23,
     551,   553,   554,  -873,  -873,   691,  -873,  -873,    36,   181,
      40,  -873,  -873,  -873,  -873,   127,    42,    74,    74,   692,
    -873,   702,   703,   704,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,   705,   -52,    36,    29,   626,   706,   707,   708,
     135,   121,   132,  -873,   214,   709,  -873,  -873,   711,   714,
    -873,  -873,  -873,  -873,  -873,   -65,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
     692,  -873,   293,   301,   302,   311,  -873,  -873,  -873,  -873,
     718,   721,   723,   724,   725,  -873,   726,   727,  -873,  -873,
    -873,   729,   732,   733,  -873,   323,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,   324,  -873,   734,   735,
    -873,  -873,   736,   738,  -873,  -873,   737,   741,  -873,  -873,
     739,   743,  -873,  -873,   742,   744,  -873,  -873,  -873,    93,
    -873,  -873,  -873,   745,  -873,  -873,  -873,   188,  -873,  -873,
    -873,  -873,   325,  -873,  -873,  -873,   260,  -873,  -873,   746,
     747,  -873,  -873,   748,   750,  -873,   751,   752,   753,   754,
     755,   756,   326,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,   757,   758,   759,  -873,  -873,  -873,  -873,   327,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,   336,  -873,  -873,  -873,   337,  -873,   280,  -873,   558,
    -873,   760,   761,  -873,  -873,   762,   764,  -873,  -873,  -873,
     763,  -873,   766,  -873,  -873,  -873,  -873,   765,   770,   771,
     772,   583,   565,   588,   593,   597,   774,   598,   599,   778,
     779,   780,   603,   604,   614,    74,  -873,  -873,    74,  -873,
     692,   448,  -873,   702,    61,  -873,   703,   261,  -873,   704,
     592,  -873,   705,   -52,  -873,  -873,    29,  -873,   783,   626,
    -873,   107,   706,  -873,    59,  -873,   707,   -57,  -873,   708,
     618,   619,   627,   630,   631,   632,   135,  -873,   784,   785,
     633,   634,   636,   121,  -873,   786,   787,   132,  -873,  -873,
      -4,   709,  -873,  -873,   788,   789,    81,  -873,   711,    72,
    -873,   714,   791,  -873,  -873,   458,   616,   638,   641,  -873,
    -873,  -873,  -873,  -873,   643,  -873,  -873,   644,   646,   651,
    -873,  -873,  -873,  -873,   360,  -873,   362,  -873,   794,  -873,
     795,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,   366,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,   653,  -873,  -873,   792,  -873,  -873,  -873,  -873,  -873,
     796,   790,  -873,  -873,  -873,  -873,  -873,   797,  -873,   380,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,   -40,   655,
    -873,  -873,  -873,  -873,   658,   664,  -873,  -873,   802,  -873,
    -873,  -873,  -873,  -873,   381,  -873,  -873,  -873,  -873,  -873,
    -873,   665,   390,  -873,   397,  -873,   666,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,   592,  -873,  -873,   803,   684,  -873,   107,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,   804,
     667,   806,    -4,  -873,  -873,  -873,  -873,  -873,  -873,   669,
    -873,  -873,   847,  -873,   686,  -873,  -873,   849,  -873,  -873,
     291,  -873,   117,   849,  -873,  -873,   807,   853,   860,   399,
    -873,  -873,  -873,  -873,  -873,  -873,   869,   694,   713,   716,
     117,  -873,   710,  -873,  -873,  -873,  -873,  -873
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   135,     9,
     282,    11,   442,    13,   467,    15,   497,    17,   367,    19,
     375,    21,   412,    23,   247,    25,   596,    27,   668,    29,
     657,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     499,     0,   377,   414,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   666,   649,   651,   653,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   117,   655,
     133,   147,   149,   151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   274,   365,   404,
     455,   457,   323,   331,   220,   237,   228,   213,   534,   489,
     239,   258,   555,     0,   579,   592,   594,   673,   116,     0,
      74,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     112,   113,   114,    85,   110,    88,    89,    90,    91,   107,
      92,    94,    93,    98,    99,    86,   111,    87,    96,    97,
     105,   106,   108,    95,   100,   101,   102,   103,   104,   109,
     115,   144,     0,   143,     0,   137,   139,   140,   141,   142,
     434,   459,   313,   315,   317,     0,     0,   321,   319,   528,
     312,   286,   287,   288,   289,   290,   291,   292,   293,   309,
     310,   311,     0,   284,   297,   298,   299,   302,   303,   305,
     300,   301,   294,   295,   307,   308,   296,   304,   306,   453,
     452,   448,   449,   447,     0,   444,   446,   450,   451,   482,
       0,   485,     0,     0,   481,   475,   476,   474,   479,   480,
       0,   469,   471,   472,   477,   478,   473,   526,   514,   516,
     518,   520,   522,   524,   513,   510,   511,   512,     0,   500,
     501,   505,   506,   503,   507,   508,   509,   504,     0,   394,
     194,     0,   398,   396,   401,     0,   390,   391,     0,   378,
     379,   381,   393,   382,   383,   384,   400,   385,   386,   387,
     388,   389,   428,     0,     0,   426,   427,   430,   431,     0,
     415,   416,   418,   419,   420,   421,   422,   423,   424,   425,
     254,   256,   251,     0,   249,   252,   253,     0,   619,   621,
       0,   624,     0,     0,   628,   632,     0,     0,   636,   643,
     645,   647,   617,   615,   616,     0,   598,   600,   601,   602,
     603,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     613,   614,     0,   670,   672,   663,     0,     0,   659,   661,
     662,    48,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    59,     0,    61,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,   136,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   283,     0,     0,   443,     0,     0,     0,     0,     0,
       0,   468,     0,     0,     0,     0,     0,     0,     0,   498,
       0,   368,     0,     0,     0,     0,     0,     0,     0,   376,
       0,     0,     0,     0,   413,     0,     0,     0,     0,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   597,     0,   669,     0,
       0,     0,   658,    52,    45,     0,     0,     0,     0,     0,
       0,    63,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   578,     0,     0,
       0,     0,    75,     0,   146,   138,     0,     0,     0,     0,
       0,   329,   330,     0,     0,     0,   285,     0,   445,     0,
     484,     0,   487,   488,   470,     0,     0,     0,     0,     0,
       0,     0,   502,     0,     0,   392,     0,     0,     0,   403,
     380,     0,   432,   433,   417,     0,     0,   250,   618,     0,
       0,   623,     0,   626,   627,     0,     0,   634,   635,     0,
       0,     0,     0,   599,   671,     0,   665,   660,     0,     0,
       0,   650,   652,   654,   118,     0,     0,     0,     0,   153,
     132,   276,   369,   406,    42,   456,   458,   325,   326,   327,
     328,   324,   333,     0,    49,     0,     0,     0,   491,   241,
       0,     0,     0,   593,     0,     0,    53,   145,   436,   461,
     314,   316,   318,   322,   320,     0,   454,   483,   486,   527,
     515,   517,   519,   521,   523,   525,   395,   195,   399,   397,
     402,   429,   255,   257,   620,   622,   625,   630,   631,   629,
     633,   638,   639,   640,   641,   642,   637,   644,   646,   648,
     153,    46,     0,     0,     0,     0,   181,   187,   189,   191,
       0,     0,     0,     0,     0,   204,     0,     0,   207,   209,
     211,     0,     0,     0,   180,     0,   159,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   173,   174,   175,
     176,   171,   172,   177,   178,   179,     0,   157,     0,   154,
     155,   280,     0,   277,   278,   373,     0,   370,   371,   410,
       0,   407,   408,   337,     0,   334,   335,   226,   227,     0,
     222,   224,   225,     0,   235,   236,   232,     0,   230,   233,
     234,   218,     0,   215,   217,   538,     0,   536,   495,     0,
     492,   493,   245,     0,   242,   243,     0,     0,     0,     0,
       0,     0,     0,   260,   262,   263,   264,   265,   266,   267,
     568,   574,     0,     0,     0,   567,   564,   565,   566,     0,
     557,   559,   562,   560,   561,   563,   588,   590,   587,   585,
     586,     0,   581,   583,   584,     0,   677,     0,   675,    55,
     440,     0,   437,   438,   465,     0,   462,   463,   532,   531,
       0,   530,     0,    71,   667,   656,   134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   150,     0,   152,
       0,     0,   275,     0,   377,   366,     0,   414,   405,     0,
       0,   332,     0,     0,   221,   238,     0,   229,     0,     0,
     214,   540,     0,   535,   499,   490,     0,     0,   240,     0,
       0,     0,     0,     0,     0,     0,     0,   259,     0,     0,
       0,     0,     0,     0,   556,     0,     0,     0,   580,   595,
       0,     0,   674,    57,     0,    56,     0,   435,     0,     0,
     460,     0,     0,   529,   664,     0,     0,     0,     0,   193,
     196,   197,   198,   199,     0,   206,   200,     0,     0,     0,
     201,   202,   203,   160,     0,   156,     0,   279,     0,   372,
       0,   409,   364,   352,   353,   354,   356,   357,   358,   345,
     346,   361,   362,   363,   341,   342,   343,   344,   350,   351,
     349,   355,     0,   339,   347,   359,   360,   348,   336,   223,
     231,     0,   216,   552,     0,   550,   551,   547,   548,   549,
       0,   541,   542,   544,   545,   546,   537,     0,   494,     0,
     244,   268,   269,   270,   271,   272,   273,   261,     0,     0,
     573,   576,   577,   558,     0,     0,   582,   691,     0,   689,
     687,   681,   685,   686,     0,   679,   683,   684,   682,   676,
      54,     0,     0,   439,     0,   464,     0,   183,   184,   185,
     186,   182,   188,   190,   192,   205,   208,   210,   212,   158,
     281,   374,   411,     0,   338,   219,     0,     0,   539,     0,
     496,   246,   570,   571,   572,   569,   575,   589,   591,     0,
       0,     0,     0,   678,    58,   441,   466,   533,   340,     0,
     554,   543,     0,   688,     0,   680,   553,     0,   690,   695,
       0,   693,     0,     0,   692,   703,     0,     0,     0,     0,
     697,   699,   700,   701,   702,   694,     0,     0,     0,     0,
       0,   696,     0,   705,   706,   707,   698,   704
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,    -5,  -873,  -493,
    -873,   240,  -873,  -873,  -873,  -873,   232,  -873,  -502,  -873,
    -873,  -873,   -74,  -873,  -873,  -873,   495,  -873,  -873,  -873,
    -873,   277,   455,  -873,  -873,   -70,   -58,   -38,   -31,   -30,
     -20,   -17,     1,     9,    12,    13,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,   266,   478,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,   197,  -873,    20,  -873,  -620,    32,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
     -46,  -873,  -648,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,    11,  -873,  -873,  -873,  -873,  -873,    18,  -639,
    -873,  -873,  -873,  -873,    17,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,     5,  -873,  -873,  -873,    10,   438,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,     2,  -873,  -873,  -873,
    -873,  -873,  -873,  -872,  -873,  -873,  -873,    37,  -873,  -873,
    -873,    44,   479,  -873,  -873,  -870,  -873,  -869,  -873,    15,
    -873,    19,  -873,    14,  -873,  -873,  -873,  -868,  -873,  -873,
    -873,  -873,    30,  -873,  -873,  -150,   855,  -873,  -873,  -873,
    -873,  -873,    43,  -873,  -873,  -873,    46,  -873,   461,  -873,
     -69,  -873,  -873,  -873,  -873,  -873,   -68,  -873,  -873,  -873,
    -873,  -873,    -3,  -873,  -873,  -873,    39,  -873,  -873,  -873,
      45,  -873,   459,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,   -11,  -873,  -873,  -873,    -1,   494,
    -873,  -873,   -56,  -873,   -15,  -873,  -873,  -873,  -873,  -873,
      -2,  -873,  -873,  -873,     3,   488,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,   -60,  -873,  -873,  -873,    34,  -873,  -873,
    -873,    48,  -873,   483,   276,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -867,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,    51,  -873,  -873,  -873,
    -135,  -873,  -873,  -873,  -873,  -873,  -873,  -873,    22,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,    21,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,   295,   464,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
    -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,  -873,
     331,   445,  -873,  -873,  -873,  -873,  -873,  -873,  -873,   330,
     460,   -61,  -873,  -873,    16,  -873,  -873,  -132,  -873,  -873,
    -873,  -873,  -873,  -873,  -152,  -873,  -873,  -168,  -873,  -873,
    -873,  -873,  -873
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   645,    92,    93,    43,    72,    89,    90,   667,   849,
     944,   945,   734,    45,    74,   101,   102,   103,   386,    47,
      75,   149,   150,   151,   394,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   412,   165,
     396,    49,    76,   194,   195,   196,   436,   197,   166,   397,
     167,   398,   168,   399,   758,   759,   760,   888,   735,   736,
     737,   867,  1071,   738,   868,   739,   869,   740,   870,   741,
     742,   473,   743,   744,   745,   746,   747,   748,   749,   750,
     751,   876,   752,   753,   879,   754,   880,   755,   881,   169,
     423,   792,   793,   794,   908,   170,   420,   779,   780,   781,
     782,   171,   422,   787,   788,   789,   790,   172,   421,   173,
     426,   803,   804,   805,   917,    65,    84,   333,   334,   335,
     486,   336,   487,   174,   427,   812,   813,   814,   815,   816,
     817,   818,   819,   175,   413,   762,   763,   764,   891,    51,
      77,   222,   223,   224,   442,   225,   443,   226,   444,   227,
     448,   228,   447,   176,   418,   651,   230,   231,   177,   419,
     774,   775,   776,   900,  1002,  1003,   178,   414,    59,    81,
     766,   767,   768,   894,    61,    82,   298,   299,   300,   301,
     302,   303,   304,   472,   305,   476,   306,   475,   307,   308,
     477,   309,   179,   415,   770,   771,   772,   897,    63,    83,
     319,   320,   321,   322,   323,   481,   324,   325,   326,   327,
     233,   440,   851,   852,   853,   946,    53,    78,   244,   245,
     246,   452,   180,   416,   181,   417,   236,   441,   855,   856,
     857,   949,    55,    79,   260,   261,   262,   455,   263,   264,
     457,   265,   266,   182,   425,   799,   800,   801,   914,    57,
      80,   278,   279,   280,   281,   463,   282,   464,   283,   465,
     284,   466,   285,   467,   286,   468,   287,   462,   238,   449,
     860,   861,   952,   183,   424,   796,   797,   911,  1020,  1021,
    1022,  1023,  1024,  1086,  1025,   184,   428,   829,   830,   831,
     928,  1095,   832,   833,   929,   834,   835,   185,   186,   430,
     841,   842,   843,   935,   844,   936,   187,   431,   188,   432,
      67,    85,   355,   356,   357,   358,   491,   359,   492,   360,
     361,   494,   362,   363,   364,   497,   699,   365,   498,   366,
     367,   368,   501,   706,   369,   502,   370,   503,   371,   504,
     104,   388,   105,   389,   106,   390,   189,   395,    71,    87,
     377,   378,   379,   509,   380,   107,   387,    69,    86,   372,
     373,   190,   433,   847,   848,   940,  1054,  1055,  1056,  1057,
    1101,  1058,  1099,  1120,  1121,  1122,  1129,  1130,  1131,  1136,
    1132,  1133,  1134
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   148,   193,   210,   240,   254,   274,   211,   296,   315,
     332,   352,    40,   826,   317,   318,   786,   237,   756,   212,
     198,   234,   247,   258,   276,   374,   310,   328,   995,   353,
     996,   997,  1001,  1007,    94,   268,   297,   316,    32,   213,
      44,    33,   858,    34,   392,    35,   214,   215,    91,   393,
     777,   644,   330,   331,    46,   290,    48,   216,   191,   192,
     217,   199,   235,   248,   259,   277,   644,   311,   329,    50,
     354,   673,   130,   131,   232,   243,   257,   275,   218,  1092,
    1093,  1094,   289,   679,   680,   681,   219,   434,   128,   220,
     221,   229,   435,   241,   255,   716,   903,   242,   256,   904,
     717,   718,   719,   720,   721,   722,   723,   724,   725,   726,
     727,   728,   729,   730,   731,   732,   733,   129,   130,   131,
     290,    52,   291,   292,    99,    54,   293,   294,   295,   778,
     129,   777,   784,   290,   785,   130,   131,   130,   131,   129,
     375,   376,   820,   249,   250,   251,   252,   253,   130,   131,
     239,   721,  1047,   267,  1048,  1049,    56,   130,   131,   268,
     269,   270,   271,   272,   273,   129,   290,   207,    58,    60,
     208,   701,   702,   703,   704,   438,   207,    99,    95,   208,
     439,   450,    62,   130,   131,   453,   451,    96,    97,    98,
     454,   906,   108,   109,   907,   147,   110,   130,   131,   111,
     112,   113,    64,  1013,  1014,    99,    66,   705,   130,   131,
      68,   995,    70,   996,   997,  1001,  1007,    36,    37,    38,
      39,   330,   331,    99,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
      99,   381,    99,   821,   822,   823,   824,   806,   807,   808,
     809,   810,   811,    99,   460,    99,   382,   130,   131,   461,
     836,   837,    99,   912,   132,   384,   913,   786,   974,   133,
     134,   135,   136,   137,  1125,   138,   488,  1126,  1127,  1128,
     139,   489,   505,   941,   385,   826,   942,   506,    99,   140,
     130,   131,   141,   507,  1123,   511,   434,  1124,   508,   142,
     512,   863,    99,   383,   507,   511,   469,   143,   144,   864,
     865,   145,   146,    99,   438,   697,   698,   391,   100,   866,
     290,   312,   291,   292,   313,   314,   885,   885,   909,   926,
     933,   886,   887,   910,   927,   934,   147,   130,   131,   937,
     505,   471,   400,   401,   938,   939,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   402,
     148,   403,    99,   885,   193,   450,   350,   351,  1079,  1083,
    1080,   404,   405,   406,  1084,   407,   210,   513,   514,   240,
     211,   408,   198,   488,  1102,   470,   254,   409,  1091,  1103,
     237,   410,   212,   453,   234,    99,   274,   247,  1105,   411,
     460,   479,  1140,   480,   258,  1106,   296,  1141,   429,   437,
     445,   315,   213,   446,   276,   456,   317,   318,   458,   214,
     215,   459,   474,   199,   310,   647,   648,   649,   650,   328,
     216,   352,   478,   217,   297,   235,   482,   483,   248,   316,
     485,   528,    99,   484,   490,   259,   374,   232,   493,   353,
     243,   218,   515,   495,   496,   277,   499,   257,   500,   219,
     510,   516,   220,   221,   229,   311,   517,   275,   241,   518,
     329,   519,   242,   520,   522,   255,   523,   524,   525,   256,
    1067,  1068,  1069,  1070,   526,   527,   529,   530,   531,   532,
     354,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   533,   534,   535,   540,   129,   541,   542,   543,
     544,   539,   536,   631,   632,   633,   200,   537,   201,   545,
     546,   547,   548,   538,   130,   131,   202,   203,   204,   205,
     206,   132,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   207,   560,   561,   208,   139,   563,   564,
     566,   567,   568,   569,   209,   148,   570,   571,   572,   573,
     574,   575,   193,   577,   579,   581,   580,   582,   583,   374,
     585,   586,   587,   588,   589,   590,   591,   593,   594,   596,
     198,   597,   598,   595,   601,   605,   599,   825,   838,   606,
     352,   602,   603,   609,   608,   610,   617,   611,   612,   615,
     616,   693,   613,   614,   619,   827,   839,   618,   353,   620,
     621,   622,   625,   626,   628,   634,   629,   640,   630,   635,
     636,   199,   637,   711,   638,   639,   641,   642,   643,    99,
     652,    34,   646,   653,   654,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   828,   840,   127,   354,
     129,   290,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   655,   130,   131,
     656,   203,   204,   657,   206,   132,   658,   659,   670,   671,
     660,   661,   662,   664,   665,   666,   668,   207,   669,   672,
     208,   674,   675,   676,   677,   678,   710,   700,   209,   757,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   761,
     765,   769,   773,   795,   798,   802,   846,   691,   850,   791,
     692,   854,   871,   694,   695,   872,   696,   873,   874,   875,
     877,   878,   707,   882,   708,   709,   883,   884,   890,   943,
     889,   893,   892,   895,   896,   898,   899,   902,   901,   960,
     916,   905,   915,   919,   918,   920,   921,   922,   923,   924,
     925,   930,   931,   932,   948,   959,   947,   951,   950,   955,
     961,   953,   954,    99,   956,   957,   958,   962,   964,   963,
     965,   966,   967,   968,   969,   970,   971,  1011,  1038,  1039,
    1044,  1045,  1061,  1089,  1060,  1066,  1087,  1072,   972,   663,
    1031,  1032,  1081,  1082,  1088,  1090,  1100,  1109,  1112,  1033,
    1114,  1137,  1034,  1035,  1036,  1040,  1041,   210,  1042,  1073,
     296,   211,  1074,   315,  1075,  1076,   982,  1077,   317,   318,
     983,   237,  1078,   212,  1085,   234,  1096,  1015,   310,  1097,
     274,   328,   984,   332,  1005,  1098,  1104,  1107,   297,  1113,
    1116,   316,  1117,   213,   994,  1018,  1119,  1138,   276,   825,
     214,   215,   985,   838,  1139,  1016,  1050,  1118,  1110,   986,
     987,   216,   240,  1142,   217,   254,   235,   827,  1143,   311,
     988,   839,   329,   989,  1052,  1006,   783,   521,   232,   562,
     247,  1147,   218,   258,  1051,  1144,  1019,  1004,  1145,   277,
     219,   990,   715,   220,   221,   229,   712,   862,  1017,   991,
     975,   275,   992,   993,  1000,   998,   565,   973,   828,   999,
    1012,  1009,   840,  1010,  1030,  1053,   607,  1029,  1037,   576,
     977,   248,  1008,  1108,   259,   976,   288,  1063,   981,   979,
     978,   600,   980,   243,   604,  1062,   257,   578,   584,  1065,
    1028,   859,  1064,   592,  1111,  1043,   627,  1059,  1046,   845,
     713,   241,  1027,  1026,   255,   242,   714,   624,   256,   623,
    1115,  1135,  1146,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   982,
       0,     0,     0,   983,     0,  1015,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   984,     0,  1005,  1050,     0,
       0,     0,     0,  1018,     0,     0,     0,   994,     0,     0,
       0,     0,     0,  1016,     0,   985,  1052,     0,     0,     0,
       0,     0,   986,   987,     0,     0,  1051,     0,     0,     0,
       0,     0,     0,   988,     0,     0,   989,     0,  1006,     0,
       0,     0,     0,     0,  1019,     0,     0,     0,     0,     0,
    1004,     0,     0,     0,   990,     0,  1017,  1053,     0,     0,
       0,     0,   991,     0,     0,   992,   993,  1000,   998,     0,
       0,     0,   999
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    17,   661,    83,    83,   655,    77,   638,    77,
      76,    77,    78,    79,    80,    86,    82,    83,   900,    85,
     900,   900,   900,   900,    10,   100,    82,    83,     0,    77,
       7,     5,   107,     7,     3,     9,    77,    77,   181,     8,
     102,   544,   109,   110,     7,    59,     7,    77,    16,    17,
      77,    76,    77,    78,    79,    80,   559,    82,    83,     7,
      85,   573,    76,    77,    77,    78,    79,    80,    77,   119,
     120,   121,    21,   585,   586,   587,    77,     3,    57,    77,
      77,    77,     8,    78,    79,    21,     3,    78,    79,     6,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    58,    76,    77,
      59,     7,    61,    62,   181,     7,    65,    66,    67,   181,
      58,   102,   103,    59,   105,    76,    77,    76,    77,    58,
      13,    14,    21,    71,    72,    73,    74,    75,    76,    77,
      69,    30,   156,    94,   158,   159,     7,    76,    77,   100,
     101,   102,   103,   104,   105,    58,    59,    95,     7,     7,
      98,   148,   149,   150,   151,     3,    95,   181,   154,    98,
       8,     3,     7,    76,    77,     3,     8,   163,   164,   165,
       8,     3,    11,    12,     6,   155,    15,    76,    77,    18,
      19,    20,     7,    96,    97,   181,     7,   184,    76,    77,
       7,  1083,     7,  1083,  1083,  1083,  1083,   181,   182,   183,
     184,   109,   110,   181,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
     181,     6,   181,   122,   123,   124,   125,   112,   113,   114,
     115,   116,   117,   181,     3,   181,     3,    76,    77,     8,
     128,   129,   181,     3,    83,     8,     6,   906,   888,    88,
      89,    90,    91,    92,   157,    94,     3,   160,   161,   162,
      99,     8,     3,     3,     3,   933,     6,     8,   181,   108,
      76,    77,   111,     3,     3,     3,     3,     6,     8,   118,
       8,     8,   181,     4,     3,     3,     8,   126,   127,     8,
       8,   130,   131,   181,     3,   145,   146,     4,   392,     8,
      59,    60,    61,    62,    63,    64,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,   155,    76,    77,     3,
       3,     8,     4,     4,     8,     8,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     4,
     434,     4,   181,     3,   438,     3,   152,   153,     8,     3,
       8,     4,     4,     4,     8,     4,   450,   382,   383,   453,
     450,     4,   438,     3,     3,     3,   460,     4,     8,     8,
     450,     4,   450,     3,   450,   181,   470,   453,     8,     4,
       3,     8,     3,     3,   460,     8,   480,     8,     4,     4,
       4,   485,   450,     4,   470,     4,   485,   485,     4,   450,
     450,     4,     4,   438,   480,    84,    85,    86,    87,   485,
     450,   505,     4,   450,   480,   450,     4,     4,   453,   485,
       3,   182,   181,     8,     4,   460,   507,   450,     4,   505,
     453,   450,   181,     4,     4,   470,     4,   460,     4,   450,
       4,     4,   450,   450,   450,   480,     4,   470,   453,     4,
     485,     4,   453,     4,     4,   460,     4,     4,     4,   460,
      22,    23,    24,    25,     4,     4,   182,   182,   182,   182,
     505,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   182,   182,   182,     4,    58,     4,     4,     4,
       4,   182,   184,   518,   519,   520,    68,   183,    70,     4,
       4,     4,     4,   183,    76,    77,    78,    79,    80,    81,
      82,    83,     4,     4,     4,     4,     4,     4,     4,     4,
     182,     4,     4,    95,     4,     4,    98,    99,     4,   184,
       4,     4,     4,     4,   106,   629,     4,   182,   184,     4,
       4,     4,   636,     4,     4,     4,   182,   182,   182,   630,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     636,     4,     4,   182,     4,     4,   184,   661,   662,     4,
     664,   184,   184,     4,   184,     4,   184,   182,     4,     4,
       4,   606,   182,   182,     4,   661,   662,   184,   664,     4,
       4,     4,     4,   182,     4,   181,     7,   181,     7,     7,
       7,   636,     7,   628,     7,     5,     5,     5,     5,   181,
       5,     7,   181,     5,     5,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,   661,   662,    56,   664,
      58,    59,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,     5,    76,    77,
       7,    79,    80,     5,    82,    83,     5,     5,   181,   181,
       7,     7,     7,     7,     5,     5,     5,    95,     5,   181,
      98,   181,     7,   181,   181,   181,     5,   147,   106,     7,
     181,   181,   181,   181,   181,   181,   181,   181,   181,     7,
       7,     7,     7,     7,     7,     7,     7,   181,     7,    93,
     181,     7,     4,   181,   181,     4,   181,     4,     4,     4,
       4,     4,   181,     4,   181,   181,     4,     4,     3,   181,
       6,     3,     6,     6,     3,     6,     3,     3,     6,   184,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   182,     6,     3,     6,     4,
     182,     8,     6,   181,     4,     4,     4,   184,     4,   182,
     182,   182,     4,     4,     4,   182,   182,     4,     4,     4,
       4,     4,     3,     3,     6,     4,     4,   181,   184,   559,
     182,   182,     8,     8,     8,     8,     4,     4,     4,   182,
       4,     4,   182,   182,   182,   182,   182,   891,   182,   181,
     894,   891,   181,   897,   181,   181,   900,   181,   897,   897,
     900,   891,   181,   891,   181,   891,   181,   911,   894,   181,
     914,   897,   900,   917,   900,   181,   181,   181,   894,   182,
     181,   897,     5,   891,   900,   911,     7,     4,   914,   933,
     891,   891,   900,   937,     4,   911,   940,   181,   184,   900,
     900,   891,   946,     4,   891,   949,   891,   933,   184,   894,
     900,   937,   897,   900,   940,   900,   654,   392,   891,   434,
     946,   181,   891,   949,   940,   182,   911,   900,   182,   914,
     891,   900,   636,   891,   891,   891,   629,   710,   911,   900,
     890,   914,   900,   900,   900,   900,   438,   885,   933,   900,
     909,   903,   937,   906,   919,   940,   488,   917,   926,   450,
     893,   946,   902,  1083,   949,   891,    81,   948,   899,   896,
     894,   480,   897,   946,   485,   946,   949,   453,   460,   951,
     916,   675,   949,   470,  1089,   933,   511,   941,   937,   664,
     630,   946,   914,   912,   949,   946,   635,   507,   949,   505,
    1102,  1123,  1140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1083,
      -1,    -1,    -1,  1083,    -1,  1089,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1083,    -1,  1083,  1102,    -1,
      -1,    -1,    -1,  1089,    -1,    -1,    -1,  1083,    -1,    -1,
      -1,    -1,    -1,  1089,    -1,  1083,  1102,    -1,    -1,    -1,
      -1,    -1,  1083,  1083,    -1,    -1,  1102,    -1,    -1,    -1,
      -1,    -1,    -1,  1083,    -1,    -1,  1083,    -1,  1083,    -1,
      -1,    -1,    -1,    -1,  1089,    -1,    -1,    -1,    -1,    -1,
    1083,    -1,    -1,    -1,  1083,    -1,  1089,  1102,    -1,    -1,
      -1,    -1,  1083,    -1,    -1,  1083,  1083,  1083,  1083,    -1,
      -1,    -1,  1083
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
     108,   111,   118,   126,   127,   130,   131,   155,   217,   226,
     227,   228,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   244,   253,   255,   257,   294,
     300,   306,   312,   314,   328,   338,   358,   363,   371,   397,
     427,   429,   448,   478,   490,   502,   503,   511,   513,   551,
     566,    16,    17,   217,   248,   249,   250,   252,   427,   429,
      68,    70,    78,    79,    80,    81,    82,    95,    98,   106,
     217,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   346,   347,   348,   350,   352,   354,   356,   358,
     361,   362,   397,   415,   427,   429,   431,   448,   473,    69,
     217,   354,   356,   397,   423,   424,   425,   427,   429,    71,
      72,    73,    74,    75,   217,   354,   356,   397,   427,   429,
     439,   440,   441,   443,   444,   446,   447,    94,   100,   101,
     102,   103,   104,   105,   217,   397,   427,   429,   456,   457,
     458,   459,   461,   463,   465,   467,   469,   471,   371,    21,
      59,    61,    62,    65,    66,    67,   217,   275,   381,   382,
     383,   384,   385,   386,   387,   389,   391,   393,   394,   396,
     427,   429,    60,    63,    64,   217,   275,   385,   391,   405,
     406,   407,   408,   409,   411,   412,   413,   414,   427,   429,
     109,   110,   217,   322,   323,   324,   326,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     152,   153,   217,   427,   429,   517,   518,   519,   520,   522,
     524,   525,   527,   528,   529,   532,   534,   535,   536,   539,
     541,   543,   564,   565,   566,    13,    14,   555,   556,   557,
     559,     6,     3,     4,     8,     3,   223,   561,   546,   548,
     550,     4,     3,     8,   229,   552,   245,   254,   256,   258,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   243,   339,   372,   398,   428,   430,   359,   364,
     301,   313,   307,   295,   479,   449,   315,   329,   491,     4,
     504,   512,   514,   567,     3,     8,   251,     4,     3,     8,
     416,   432,   349,   351,   353,     4,     4,   357,   355,   474,
       3,     8,   426,     3,     8,   442,     4,   445,     4,     4,
       3,     8,   472,   460,   462,   464,   466,   468,   470,     8,
       3,     8,   388,   276,     4,   392,   390,   395,     4,     8,
       3,   410,     4,     4,     8,     3,   325,   327,     3,     8,
       4,   521,   523,     4,   526,     4,     4,   530,   533,     4,
       4,   537,   540,   542,   544,     3,     8,     3,     8,   558,
       4,     3,     8,   202,   202,   181,     4,     4,     4,     4,
       4,   221,     4,     4,     4,     4,     4,     4,   182,   182,
     182,   182,   182,   182,   182,   182,   184,   183,   183,   182,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   182,     4,     4,
       4,     4,   227,     4,   184,   249,     4,     4,     4,     4,
       4,   182,   184,     4,     4,     4,   347,     4,   424,     4,
     182,     4,   182,   182,   440,     4,     4,     4,     4,     4,
       4,     4,   458,     4,     4,   182,     4,     4,     4,   184,
     383,     4,   184,   184,   407,     4,     4,   323,   184,     4,
       4,   182,     4,   182,   182,     4,     4,   184,   184,     4,
       4,     4,     4,   518,   565,     4,   182,   556,     4,     7,
       7,   202,   202,   202,   181,     7,     7,     7,     7,     5,
     181,     5,     5,     5,   204,   206,   181,    84,    85,    86,
      87,   360,     5,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,   206,     7,     5,     5,   213,     5,     5,
     181,   181,   181,   213,   181,     7,   181,   181,   181,   213,
     213,   213,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   202,   181,   181,   181,   145,   146,   531,
     147,   148,   149,   150,   151,   184,   538,   181,   181,   181,
       5,   202,   226,   564,   555,   248,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,   217,   263,   264,   265,   268,   270,
     272,   274,   275,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   287,   288,   290,   292,   263,     7,   259,   260,
     261,     7,   340,   341,   342,     7,   375,   376,   377,     7,
     399,   400,   401,     7,   365,   366,   367,   102,   181,   302,
     303,   304,   305,   211,   103,   105,   304,   308,   309,   310,
     311,    93,   296,   297,   298,     7,   480,   481,     7,   450,
     451,   452,     7,   316,   317,   318,   112,   113,   114,   115,
     116,   117,   330,   331,   332,   333,   334,   335,   336,   337,
      21,   122,   123,   124,   125,   217,   277,   427,   429,   492,
     493,   494,   497,   498,   500,   501,   128,   129,   217,   427,
     429,   505,   506,   507,   509,   517,     7,   568,   569,   214,
       7,   417,   418,   419,     7,   433,   434,   435,   107,   459,
     475,   476,   259,     8,     8,     8,     8,   266,   269,   271,
     273,     4,     4,     4,     4,     4,   286,     4,     4,   289,
     291,   293,     4,     4,     4,     3,     8,     8,   262,     6,
       3,   343,     6,     3,   378,     6,     3,   402,     6,     3,
     368,     6,     3,     3,     6,     6,     3,     6,   299,     3,
       8,   482,     3,     6,   453,     6,     3,   319,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   495,   499,
       4,     4,     4,     3,     8,   508,   510,     3,     8,     8,
     570,     3,     6,   181,   215,   216,   420,     6,     3,   436,
       6,     3,   477,     8,     6,     4,     4,     4,     4,   182,
     184,   182,   184,   182,     4,   182,   182,     4,     4,     4,
     182,   182,   184,   264,   263,   261,   346,   342,   381,   377,
     405,   401,   217,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   275,   338,   350,   352,   354,   356,
     358,   362,   369,   370,   397,   427,   429,   473,   367,   303,
     309,     4,   297,    96,    97,   217,   275,   397,   427,   429,
     483,   484,   485,   486,   487,   489,   481,   456,   452,   322,
     318,   182,   182,   182,   182,   182,   182,   331,     4,     4,
     182,   182,   182,   493,     4,     4,   506,   156,   158,   159,
     217,   275,   427,   429,   571,   572,   573,   574,   576,   569,
       6,     3,   423,   419,   439,   435,     4,    22,    23,    24,
      25,   267,   181,   181,   181,   181,   181,   181,   181,     8,
       8,     8,     8,     3,     8,   181,   488,     4,     8,     3,
       8,     8,   119,   120,   121,   496,   181,   181,   181,   577,
       4,   575,     3,     8,   181,     8,     8,   181,   370,     4,
     184,   485,     4,   182,     4,   572,   181,     5,   181,     7,
     578,   579,   580,     3,     6,   157,   160,   161,   162,   581,
     582,   583,   585,   586,   587,   579,   584,     4,     4,     4,
       3,     8,     4,   184,   182,   182,   582,   181
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
     227,   227,   227,   227,   227,   227,   227,   229,   228,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   243,   242,   245,   244,   247,   246,   248,   248,   249,
     249,   249,   249,   249,   251,   250,   252,   254,   253,   256,
     255,   258,   257,   259,   259,   260,   260,   262,   261,   263,
     263,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   266,   265,   267,   267,   267,   267,   269,   268,   271,
     270,   273,   272,   274,   276,   275,   277,   278,   279,   280,
     281,   282,   283,   284,   286,   285,   287,   289,   288,   291,
     290,   293,   292,   295,   294,   296,   296,   297,   299,   298,
     301,   300,   302,   302,   303,   303,   304,   305,   307,   306,
     308,   308,   309,   309,   309,   310,   311,   313,   312,   315,
     314,   316,   316,   317,   317,   319,   318,   321,   320,   322,
     322,   322,   323,   323,   325,   324,   327,   326,   329,   328,
     330,   330,   331,   331,   331,   331,   331,   331,   332,   333,
     334,   335,   336,   337,   339,   338,   340,   340,   341,   341,
     343,   342,   345,   344,   346,   346,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   349,   348,   351,   350,   353,   352,   355,
     354,   357,   356,   359,   358,   360,   360,   360,   360,   361,
     362,   364,   363,   365,   365,   366,   366,   368,   367,   369,
     369,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   372,   371,   374,   373,   375,
     375,   376,   376,   378,   377,   380,   379,   381,   381,   382,
     382,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   384,   385,   386,   388,   387,   390,   389,   392,   391,
     393,   395,   394,   396,   398,   397,   399,   399,   400,   400,
     402,   401,   404,   403,   405,   405,   406,   406,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   408,   410,   409,
     411,   412,   413,   414,   416,   415,   417,   417,   418,   418,
     420,   419,   422,   421,   423,   423,   424,   424,   424,   424,
     424,   424,   424,   426,   425,   428,   427,   430,   429,   432,
     431,   433,   433,   434,   434,   436,   435,   438,   437,   439,
     439,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   442,   441,   443,   445,   444,   446,   447,   449,
     448,   450,   450,   451,   451,   453,   452,   455,   454,   456,
     456,   457,   457,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   460,   459,   462,   461,   464,   463,
     466,   465,   468,   467,   470,   469,   472,   471,   474,   473,
     475,   475,   477,   476,   479,   478,   480,   480,   482,   481,
     483,   483,   484,   484,   485,   485,   485,   485,   485,   485,
     485,   486,   488,   487,   489,   491,   490,   492,   492,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   495,   494,
     496,   496,   496,   497,   499,   498,   500,   501,   502,   504,
     503,   505,   505,   506,   506,   506,   506,   506,   508,   507,
     510,   509,   512,   511,   514,   513,   516,   515,   517,   517,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   519,   521,
     520,   523,   522,   524,   526,   525,   527,   528,   530,   529,
     531,   531,   533,   532,   534,   535,   537,   536,   538,   538,
     538,   538,   538,   540,   539,   542,   541,   544,   543,   546,
     545,   548,   547,   550,   549,   552,   551,   554,   553,   555,
     555,   556,   556,   558,   557,   559,   561,   560,   563,   562,
     564,   564,   565,   567,   566,   568,   568,   570,   569,   571,
     571,   572,   572,   572,   572,   572,   572,   572,   573,   575,
     574,   577,   576,   578,   578,   580,   579,   581,   581,   582,
     582,   582,   582,   584,   583,   585,   586,   587
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     3,     0,     6,     0,     4,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     3,     3,     3
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
     484,   485,   486,   487,   488,   489,   490,   493,   493,   501,
     506,   511,   516,   521,   526,   531,   536,   541,   546,   551,
     556,   561,   561,   569,   569,   580,   580,   589,   590,   593,
     594,   595,   596,   597,   600,   600,   610,   616,   616,   628,
     628,   640,   640,   650,   651,   654,   655,   658,   658,   668,
     669,   672,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   688,   689,   690,
     691,   694,   694,   701,   702,   703,   704,   707,   707,   715,
     715,   723,   723,   731,   736,   736,   744,   749,   754,   759,
     764,   769,   774,   779,   784,   784,   792,   797,   797,   805,
     805,   813,   813,   821,   821,   831,   832,   834,   836,   836,
     854,   854,   864,   865,   868,   869,   872,   877,   882,   882,
     892,   893,   896,   897,   898,   901,   906,   913,   913,   923,
     923,   933,   934,   937,   938,   941,   941,   951,   951,   961,
     962,   963,   966,   967,   970,   970,   978,   978,   986,   986,
     997,   998,  1001,  1002,  1003,  1004,  1005,  1006,  1009,  1014,
    1019,  1024,  1029,  1034,  1042,  1042,  1055,  1056,  1059,  1060,
    1067,  1067,  1093,  1093,  1104,  1105,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,
    1133,  1134,  1135,  1138,  1138,  1146,  1146,  1154,  1154,  1162,
    1162,  1170,  1170,  1180,  1180,  1187,  1188,  1189,  1190,  1193,
    1198,  1206,  1206,  1217,  1218,  1222,  1223,  1226,  1226,  1234,
    1235,  1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,
    1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,
    1257,  1258,  1259,  1260,  1261,  1268,  1268,  1281,  1281,  1290,
    1291,  1294,  1295,  1300,  1300,  1315,  1315,  1329,  1330,  1333,
    1334,  1337,  1338,  1339,  1340,  1341,  1342,  1343,  1344,  1345,
    1346,  1349,  1351,  1356,  1358,  1358,  1366,  1366,  1374,  1374,
    1382,  1384,  1384,  1392,  1401,  1401,  1413,  1414,  1419,  1420,
    1425,  1425,  1437,  1437,  1449,  1450,  1455,  1456,  1461,  1462,
    1463,  1464,  1465,  1466,  1467,  1468,  1469,  1472,  1474,  1474,
    1482,  1484,  1486,  1491,  1499,  1499,  1511,  1512,  1515,  1516,
    1519,  1519,  1529,  1529,  1538,  1539,  1542,  1543,  1544,  1545,
    1546,  1547,  1548,  1551,  1551,  1559,  1559,  1584,  1584,  1614,
    1614,  1626,  1627,  1630,  1631,  1634,  1634,  1646,  1646,  1658,
    1659,  1662,  1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,
    1671,  1672,  1675,  1675,  1683,  1688,  1688,  1696,  1701,  1709,
    1709,  1719,  1720,  1723,  1724,  1727,  1727,  1736,  1736,  1745,
    1746,  1749,  1750,  1754,  1755,  1756,  1757,  1758,  1759,  1760,
    1761,  1762,  1763,  1764,  1767,  1767,  1777,  1777,  1787,  1787,
    1795,  1795,  1803,  1803,  1811,  1811,  1819,  1819,  1832,  1832,
    1842,  1843,  1846,  1846,  1857,  1857,  1867,  1868,  1871,  1871,
    1881,  1882,  1885,  1886,  1889,  1890,  1891,  1892,  1893,  1894,
    1895,  1898,  1900,  1900,  1908,  1916,  1916,  1928,  1929,  1932,
    1933,  1934,  1935,  1936,  1937,  1938,  1939,  1940,  1943,  1943,
    1950,  1951,  1952,  1955,  1960,  1960,  1968,  1973,  1980,  1987,
    1987,  1997,  1998,  2001,  2002,  2003,  2004,  2005,  2008,  2008,
    2016,  2016,  2026,  2026,  2066,  2066,  2078,  2078,  2088,  2089,
    2092,  2093,  2094,  2095,  2096,  2097,  2098,  2099,  2100,  2101,
    2102,  2103,  2104,  2105,  2106,  2107,  2108,  2109,  2112,  2117,
    2117,  2125,  2125,  2133,  2138,  2138,  2146,  2151,  2156,  2156,
    2164,  2165,  2168,  2168,  2176,  2181,  2186,  2186,  2194,  2197,
    2200,  2203,  2206,  2212,  2212,  2220,  2220,  2228,  2228,  2238,
    2238,  2245,  2245,  2252,  2252,  2261,  2261,  2272,  2272,  2282,
    2283,  2287,  2288,  2291,  2291,  2301,  2311,  2311,  2321,  2321,
    2332,  2333,  2337,  2341,  2341,  2353,  2354,  2358,  2358,  2366,
    2367,  2370,  2371,  2372,  2373,  2374,  2375,  2376,  2379,  2384,
    2384,  2392,  2392,  2402,  2403,  2406,  2406,  2414,  2415,  2418,
    2419,  2420,  2421,  2424,  2424,  2432,  2437,  2442
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

#line 2447 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
