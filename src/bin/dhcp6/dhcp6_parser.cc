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
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:435

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc" // lalr1.cc:435


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

#line 14 "dhcp6_parser.yy" // lalr1.cc:510
namespace isc { namespace dhcp {
#line 146 "dhcp6_parser.cc" // lalr1.cc:510

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
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 180: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 179: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 178: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 177: // "constant string"
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
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 180: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 179: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 178: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 177: // "constant string"
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
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 180: // "boolean"
        value.move< bool > (that.value);
        break;

      case 179: // "floating point"
        value.move< double > (that.value);
        break;

      case 178: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 177: // "constant string"
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
      case 177: // "constant string"
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 178: // "integer"
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 179: // "floating point"
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 180: // "boolean"
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 198: // value
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 202: // map_value
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 259: // db_type
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 352: // hr_mode
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 488: // duid_type
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 523: // ncr_protocol_value
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 530: // replace_client_name_value
#line 256 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc" // lalr1.cc:676
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
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 180: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 179: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 178: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 177: // "constant string"
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
#line 265 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 266 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 267 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 742 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 268 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 748 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 269 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET6; }
#line 754 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 270 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 760 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 271 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 272 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 772 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 273 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 274 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 784 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 275 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 790 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 276 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 796 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 277 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 802 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 278 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 808 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 279 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 814 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 287 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 820 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 288 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 826 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 289 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 832 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 290 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 838 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 291 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 844 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 292 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 850 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 293 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 856 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 296 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 301 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 306 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 312 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 892 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 319 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 323 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 47:
#line 330 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 920 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 48:
#line 333 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 928 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 341 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 345 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 352 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 354 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 363 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 972 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 367 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 981 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 378 "dhcp6_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 992 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 388 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 393 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1016 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 70:
#line 416 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 71:
#line 423 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 72:
#line 431 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 73:
#line 435 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 485 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 487 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 493 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 498 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 503 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 508 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 513 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 518 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1130 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 523 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 122:
#line 528 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 123:
#line 533 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1156 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 124:
#line 535 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1166 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 125:
#line 541 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1177 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 126:
#line 546 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 127:
#line 552 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1197 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 128:
#line 556 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 572 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 577 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1226 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 582 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 588 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1246 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 593 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1257 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 600 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1268 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 605 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 612 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1290 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 617 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1299 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 630 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 634 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 173:
#line 666 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 174:
#line 668 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 175:
#line 673 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1342 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 176:
#line 674 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1348 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 177:
#line 675 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1354 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 676 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1360 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 679 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 681 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1378 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 687 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 182:
#line 689 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 695 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1404 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 697 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 703 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 708 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 710 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 716 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 721 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 726 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 731 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 736 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 741 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1495 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 746 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 751 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 756 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 758 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 764 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 769 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1548 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 771 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 201:
#line 777 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1566 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 202:
#line 779 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1576 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 785 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1584 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 787 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1594 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 793 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 798 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1614 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 210:
#line 808 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1622 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 810 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1642 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 826 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1653 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 831 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1662 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 844 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1671 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 219:
#line 849 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 220:
#line 854 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 859 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 227:
#line 873 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1709 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 228:
#line 878 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 229:
#line 885 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1729 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 890 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 895 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1749 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 900 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 237:
#line 913 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 238:
#line 917 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1778 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 239:
#line 923 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 927 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1798 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 246:
#line 942 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 247:
#line 944 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1816 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 248:
#line 950 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1824 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 952 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1833 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 958 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1844 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 963 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1854 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 260:
#line 981 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 261:
#line 986 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1872 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 262:
#line 991 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 263:
#line 996 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 264:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1899 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1908 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1919 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 272:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 273:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1964 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 274:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1974 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 275:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 301:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1992 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 302:
#line 1108 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 303:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 304:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2020 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 305:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2028 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 306:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2038 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 307:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 308:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2056 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2076 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2084 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 312:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 313:
#line 1155 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2099 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2105 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2111 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1158 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2117 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 318:
#line 1166 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 319:
#line 1174 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 320:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 325:
#line 1194 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 326:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2173 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 349:
#line 1232 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 350:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 351:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 352:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2210 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 357:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 358:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 359:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 360:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 376:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2263 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 378:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 379:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 380:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 381:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 382:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 383:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 385:
#line 1348 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 386:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 387:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 388:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 389:
#line 1370 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2364 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2374 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 395:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 396:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 397:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 412:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2410 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 413:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2420 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 416:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 417:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 418:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2449 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 419:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 424:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2468 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 426:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2488 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 427:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2497 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2515 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 440:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2550 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 441:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 442:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2587 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 443:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 444:
#line 1583 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2607 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 449:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2629 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 451:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 466:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 467:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 468:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 469:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 470:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 471:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2705 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 472:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 473:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2725 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 474:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 479:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 480:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 481:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 482:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2772 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2783 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2792 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2812 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 502:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1753 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2830 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2838 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2856 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 507:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2866 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 508:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 509:
#line 1777 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2884 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 510:
#line 1783 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2895 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 511:
#line 1788 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2904 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 512:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 513:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 516:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2942 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 518:
#line 1821 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2953 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 519:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 522:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2972 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 523:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2982 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 536:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2990 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 537:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 538:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1885 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3031 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1907 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3054 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3060 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 557:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3075 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 558:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 559:
#line 1926 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 560:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3102 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 561:
#line 1937 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 562:
#line 1944 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3120 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 563:
#line 1951 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3131 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 564:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3140 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 572:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3148 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 573:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3158 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 574:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3166 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 575:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3176 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 576:
#line 1990 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 577:
#line 1992 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 3224 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 578:
#line 2030 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3235 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 579:
#line 2035 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 2042 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3256 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 581:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3266 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2076 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2081 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3283 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2083 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2089 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2091 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2097 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3320 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2102 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3328 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3338 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2115 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3356 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2120 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3364 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2122 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3373 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3379 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2129 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3385 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2132 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3393 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3403 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3412 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 619:
#line 2145 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3421 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 620:
#line 2150 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3429 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 621:
#line 2152 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3438 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 622:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3446 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2161 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3454 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2164 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3462 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2167 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3470 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2170 "dhcp6_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3479 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2176 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3487 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2178 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3497 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2184 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3505 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 630:
#line 2186 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3515 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 631:
#line 2192 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3523 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 632:
#line 2194 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3533 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 633:
#line 2202 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3541 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2204 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3550 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 635:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3558 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2211 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3567 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2216 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3575 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 638:
#line 2218 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3584 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 639:
#line 2225 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3595 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 640:
#line 2230 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3605 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 641:
#line 2236 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3615 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 642:
#line 2240 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3624 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 647:
#line 2255 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3635 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2260 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3644 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 649:
#line 2265 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3653 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 650:
#line 2275 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3664 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 651:
#line 2280 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3673 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 652:
#line 2285 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3683 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 653:
#line 2289 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3691 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 657:
#line 2305 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3702 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 658:
#line 2310 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3711 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 661:
#line 2322 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3721 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 662:
#line 2326 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3729 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 672:
#line 2343 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3738 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 673:
#line 2348 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3746 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 674:
#line 2350 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3756 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 675:
#line 2356 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3767 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 676:
#line 2361 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3776 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 679:
#line 2370 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3786 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 680:
#line 2374 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3794 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 687:
#line 2388 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3802 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 688:
#line 2390 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3812 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 689:
#line 2396 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3821 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 690:
#line 2401 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3830 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 691:
#line 2406 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3839 "dhcp6_parser.cc" // lalr1.cc:919
    break;


#line 3843 "dhcp6_parser.cc" // lalr1.cc:919
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


  const short Dhcp6Parser::yypact_ninf_ = -864;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     356,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,    43,    35,    51,   112,
     118,   120,   128,   140,   163,   178,   191,   194,   201,   231,
     233,   235,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,    35,   -94,    23,   175,    32,    64,   202,   108,
     386,   200,    59,   278,   -54,   364,   104,   143,  -864,   251,
     266,   276,   273,   285,  -864,  -864,  -864,  -864,  -864,   299,
    -864,   126,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,   303,   313,   320,   323,   324,   337,
     343,   349,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   351,
    -864,  -864,  -864,  -864,  -864,   141,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,   352,  -864,   157,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,   355,   363,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
     164,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,   236,  -864,  -864,  -864,  -864,  -864,   370,  -864,
     371,   381,  -864,  -864,  -864,  -864,  -864,  -864,   268,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,   394,   406,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,   404,  -864,  -864,   385,
    -864,  -864,  -864,   422,  -864,  -864,   420,   435,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,   438,   448,  -864,  -864,  -864,  -864,   445,   453,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,   269,  -864,  -864,  -864,   462,  -864,  -864,   467,  -864,
     468,   469,  -864,  -864,   471,   473,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,   275,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
     283,  -864,  -864,  -864,   474,   284,  -864,  -864,  -864,  -864,
      35,    35,  -864,   280,   475,   476,   477,   484,   485,  -864,
      23,  -864,   486,   487,   501,   502,   503,   504,   331,   332,
     333,   336,   357,   359,   360,   358,   529,   530,   536,   539,
     540,   541,   542,   543,   544,   546,   547,   548,   549,   550,
     551,   552,   553,   384,   554,   555,   557,   560,   175,  -864,
     561,   392,    32,  -864,   562,   565,   567,   569,   570,   397,
     396,   573,   574,   575,    64,  -864,   576,   202,  -864,   577,
     405,   578,   409,   411,   108,  -864,   580,   586,   587,   588,
     589,   590,   591,  -864,   386,  -864,   592,   593,   425,   594,
     596,   598,   426,  -864,    59,   600,   427,   428,  -864,   278,
     601,   605,    86,  -864,   430,   607,   608,   436,   609,   437,
     439,   612,   614,   440,   442,   615,   619,   620,   621,   364,
    -864,   104,  -864,   624,   452,   143,  -864,  -864,  -864,   627,
     625,   626,    35,    35,    35,  -864,   457,   628,   629,   630,
     631,   634,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
     463,   636,   637,   638,   639,   470,   380,   640,   643,   644,
     645,   646,   647,   649,   650,   651,   652,  -864,   653,   639,
     654,   657,  -864,   658,  -864,  -864,   659,   660,   479,   480,
     489,  -864,  -864,   658,   490,   661,  -864,   492,  -864,   493,
    -864,   494,  -864,  -864,  -864,   658,   658,   658,   495,   496,
     497,   498,  -864,   499,   500,  -864,   505,   506,   507,  -864,
    -864,   508,  -864,  -864,  -864,   509,    35,  -864,  -864,   510,
     511,  -864,   512,  -864,  -864,    75,   535,  -864,  -864,   185,
     513,   514,   515,  -864,  -864,   674,  -864,  -864,    35,   175,
     104,  -864,  -864,  -864,  -864,   143,    32,    60,    60,   673,
    -864,   686,   687,   688,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,   689,   -53,    35,   366,   610,   690,   691,   693,
     122,   131,    81,  -864,   364,   694,  -864,  -864,   695,   696,
    -864,  -864,  -864,  -864,  -864,    30,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
     673,  -864,   287,   291,   297,   301,  -864,  -864,  -864,  -864,
     677,   700,   701,   702,   703,  -864,   704,   705,  -864,  -864,
    -864,   706,   707,   708,  -864,   315,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,   317,  -864,   709,   641,
    -864,  -864,   710,   648,  -864,  -864,   711,   715,  -864,  -864,
     713,   717,  -864,  -864,   716,   718,  -864,  -864,  -864,    63,
    -864,  -864,  -864,   719,  -864,  -864,  -864,    76,  -864,  -864,
    -864,  -864,   346,  -864,  -864,  -864,   100,  -864,  -864,   720,
     721,  -864,  -864,   722,   724,  -864,   725,   726,   727,   728,
     729,   730,   354,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,   731,   732,   733,  -864,  -864,  -864,  -864,   365,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,   369,  -864,  -864,  -864,   379,  -864,   142,  -864,   537,
    -864,   734,   735,  -864,  -864,   736,   738,  -864,  -864,  -864,
     737,  -864,   740,  -864,  -864,  -864,  -864,   739,   743,   744,
     745,   545,   533,   566,   559,   572,   747,   579,   581,   748,
     749,   750,   582,   583,   584,    60,  -864,  -864,    60,  -864,
     673,    64,  -864,   686,    59,  -864,   687,   278,  -864,   688,
     267,  -864,   689,   -53,  -864,  -864,   366,  -864,   751,   610,
    -864,    96,   690,  -864,   386,  -864,   691,   -54,  -864,   693,
     585,   595,   597,   599,   602,   603,   122,  -864,   752,   754,
     604,   606,   611,   131,  -864,   758,   761,    81,  -864,  -864,
      91,   694,  -864,  -864,   760,   764,   202,  -864,   695,   108,
    -864,   696,   765,  -864,  -864,   423,   613,   616,   617,  -864,
    -864,  -864,  -864,  -864,   618,  -864,  -864,   622,   635,   642,
    -864,  -864,  -864,  -864,   383,  -864,   389,  -864,   762,  -864,
     763,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   391,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,   667,  -864,  -864,
     768,  -864,  -864,  -864,  -864,  -864,   766,   773,  -864,  -864,
    -864,  -864,  -864,   770,  -864,   402,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,   353,   670,  -864,  -864,  -864,  -864,
     671,   676,  -864,  -864,   775,  -864,  -864,  -864,  -864,  -864,
     403,  -864,  -864,  -864,  -864,  -864,  -864,   681,   413,  -864,
     417,  -864,   692,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   267,
    -864,  -864,   779,   698,  -864,    96,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,   781,   633,   782,    91,  -864,
    -864,  -864,  -864,  -864,  -864,   712,  -864,  -864,   783,  -864,
     723,  -864,  -864,   780,  -864,  -864,   168,  -864,  -103,   780,
    -864,  -864,   787,   788,   792,   424,  -864,  -864,  -864,  -864,
    -864,  -864,   794,   714,   697,   741,  -103,  -864,   753,  -864,
    -864,  -864,  -864,  -864
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   127,     9,
     274,    11,   426,    13,   451,    15,   481,    17,   351,    19,
     359,    21,   396,    23,   239,    25,   580,    27,   652,    29,
     641,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     483,     0,   361,   398,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   650,   633,   635,   637,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   113,   639,
     125,   139,   141,   143,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   266,   349,   388,   439,   441,   311,   319,
     212,   229,   220,   205,   518,   473,   231,   250,   539,     0,
     563,   576,   578,   657,   112,     0,    74,    76,    77,    78,
      79,    80,   108,   109,   110,    81,   106,    84,    85,    86,
      87,   103,    88,    90,    89,    94,    95,    82,   107,    83,
      92,    93,   101,   102,   104,    91,    96,    97,    98,    99,
     100,   105,   111,   136,     0,   135,     0,   129,   131,   132,
     133,   134,   418,   443,   301,   303,   305,     0,     0,   309,
     307,   512,   300,   278,   279,   280,   281,   297,   298,   299,
       0,   276,   285,   286,   287,   290,   291,   293,   288,   289,
     282,   283,   295,   296,   284,   292,   294,   437,   436,   432,
     433,   431,     0,   428,   430,   434,   435,   466,     0,   469,
       0,     0,   465,   459,   460,   458,   463,   464,     0,   453,
     455,   456,   461,   462,   457,   510,   498,   500,   502,   504,
     506,   508,   497,   494,   495,   496,     0,   484,   485,   489,
     490,   487,   491,   492,   493,   488,     0,   378,   186,     0,
     382,   380,   385,     0,   374,   375,     0,   362,   363,   365,
     377,   366,   367,   368,   384,   369,   370,   371,   372,   373,
     412,     0,     0,   410,   411,   414,   415,     0,   399,   400,
     402,   403,   404,   405,   406,   407,   408,   409,   246,   248,
     243,     0,   241,   244,   245,     0,   603,   605,     0,   608,
       0,     0,   612,   616,     0,     0,   620,   627,   629,   631,
     601,   599,   600,     0,   582,   584,   585,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
       0,   654,   656,   647,     0,     0,   643,   645,   646,    48,
       0,     0,    41,     0,     0,     0,     0,     0,     0,    59,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   275,     0,     0,   427,     0,
       0,     0,     0,     0,     0,   452,     0,     0,     0,     0,
       0,     0,     0,   482,     0,   352,     0,     0,     0,     0,
       0,     0,     0,   360,     0,     0,     0,     0,   397,     0,
       0,     0,     0,   240,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     581,     0,   653,     0,     0,     0,   642,    52,    45,     0,
       0,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   562,     0,     0,
       0,     0,    75,     0,   138,   130,     0,     0,     0,     0,
       0,   317,   318,     0,     0,     0,   277,     0,   429,     0,
     468,     0,   471,   472,   454,     0,     0,     0,     0,     0,
       0,     0,   486,     0,     0,   376,     0,     0,     0,   387,
     364,     0,   416,   417,   401,     0,     0,   242,   602,     0,
       0,   607,     0,   610,   611,     0,     0,   618,   619,     0,
       0,     0,     0,   583,   655,     0,   649,   644,     0,     0,
       0,   634,   636,   638,   114,     0,     0,     0,     0,   145,
     124,   268,   353,   390,    42,   440,   442,   313,   314,   315,
     316,   312,   321,     0,    49,     0,     0,     0,   475,   233,
       0,     0,     0,   577,     0,     0,    53,   137,   420,   445,
     302,   304,   306,   310,   308,     0,   438,   467,   470,   511,
     499,   501,   503,   505,   507,   509,   379,   187,   383,   381,
     386,   413,   247,   249,   604,   606,   609,   614,   615,   613,
     617,   622,   623,   624,   625,   626,   621,   628,   630,   632,
     145,    46,     0,     0,     0,     0,   173,   179,   181,   183,
       0,     0,     0,     0,     0,   196,     0,     0,   199,   201,
     203,     0,     0,     0,   172,     0,   151,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   165,   166,   167,
     168,   163,   164,   169,   170,   171,     0,   149,     0,   146,
     147,   272,     0,   269,   270,   357,     0,   354,   355,   394,
       0,   391,   392,   325,     0,   322,   323,   218,   219,     0,
     214,   216,   217,     0,   227,   228,   224,     0,   222,   225,
     226,   210,     0,   207,   209,   522,     0,   520,   479,     0,
     476,   477,   237,     0,   234,   235,     0,     0,     0,     0,
       0,     0,     0,   252,   254,   255,   256,   257,   258,   259,
     552,   558,     0,     0,     0,   551,   548,   549,   550,     0,
     541,   543,   546,   544,   545,   547,   572,   574,   571,   569,
     570,     0,   565,   567,   568,     0,   661,     0,   659,    55,
     424,     0,   421,   422,   449,     0,   446,   447,   516,   515,
       0,   514,     0,    71,   651,   640,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   140,   142,     0,   144,
       0,     0,   267,     0,   361,   350,     0,   398,   389,     0,
       0,   320,     0,     0,   213,   230,     0,   221,     0,     0,
     206,   524,     0,   519,   483,   474,     0,     0,   232,     0,
       0,     0,     0,     0,     0,     0,     0,   251,     0,     0,
       0,     0,     0,     0,   540,     0,     0,     0,   564,   579,
       0,     0,   658,    57,     0,    56,     0,   419,     0,     0,
     444,     0,     0,   513,   648,     0,     0,     0,     0,   185,
     188,   189,   190,   191,     0,   198,   192,     0,     0,     0,
     193,   194,   195,   152,     0,   148,     0,   271,     0,   356,
       0,   393,   348,   340,   342,   333,   334,   345,   346,   347,
     329,   330,   331,   332,   338,   339,   337,   341,     0,   327,
     335,   343,   344,   336,   324,   215,   223,     0,   208,   536,
       0,   534,   535,   531,   532,   533,     0,   525,   526,   528,
     529,   530,   521,     0,   478,     0,   236,   260,   261,   262,
     263,   264,   265,   253,     0,     0,   557,   560,   561,   542,
       0,     0,   566,   675,     0,   673,   671,   665,   669,   670,
       0,   663,   667,   668,   666,   660,    54,     0,     0,   423,
       0,   448,     0,   175,   176,   177,   178,   174,   180,   182,
     184,   197,   200,   202,   204,   150,   273,   358,   395,     0,
     326,   211,     0,     0,   523,     0,   480,   238,   554,   555,
     556,   553,   559,   573,   575,     0,     0,     0,     0,   662,
      58,   425,   450,   517,   328,     0,   538,   527,     0,   672,
       0,   664,   537,     0,   674,   679,     0,   677,     0,     0,
     676,   687,     0,     0,     0,     0,   681,   683,   684,   685,
     686,   678,     0,     0,     0,     0,     0,   680,     0,   689,
     690,   691,   682,   688
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,    13,  -864,  -483,
    -864,   229,  -864,  -864,  -864,  -864,   170,  -864,  -494,  -864,
    -864,  -864,   -74,  -864,  -864,  -864,   434,  -864,  -864,  -864,
    -864,   193,   387,  -864,  -864,   -70,   -58,   -38,   -31,   -30,
     -20,   -17,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   209,
     407,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
     117,  -864,   -43,  -864,  -602,   -49,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,   -46,  -864,  -629,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   -59,  -864,
    -864,  -864,  -864,  -864,   -57,  -622,  -864,  -864,  -864,  -864,
     -19,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   -62,
    -864,  -864,  -864,   -26,   408,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,   -40,  -864,  -864,  -864,  -864,  -864,  -864,  -863,
    -864,  -864,  -864,    10,  -864,  -864,  -864,    16,   450,  -864,
    -864,  -862,  -864,  -852,  -864,   -44,  -864,     6,  -864,     1,
    -864,  -864,  -864,  -849,  -864,  -864,  -864,  -864,     8,  -864,
    -864,  -167,   812,  -864,  -864,  -864,  -864,  -864,    19,  -864,
    -864,  -864,    22,  -864,   433,  -864,   -68,  -864,  -864,  -864,
    -864,  -864,   -45,  -864,  -864,  -864,  -864,  -864,    -3,  -864,
    -864,  -864,    20,  -864,  -864,  -864,    24,  -864,   441,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
     -25,  -864,  -864,  -864,   -22,   472,  -864,  -864,   -56,  -864,
     -15,  -864,  -864,  -864,  -864,  -864,   -24,  -864,  -864,  -864,
     -23,   464,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   -63,
    -864,  -864,  -864,    17,  -864,  -864,  -864,    18,  -864,   461,
     261,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -848,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,    25,  -864,  -864,  -864,  -147,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,     7,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,     4,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,   281,   444,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,  -864,   307,   429,  -864,  -864,
    -864,  -864,  -864,  -864,  -864,   318,   443,   -61,  -864,  -864,
      15,  -864,  -864,  -151,  -864,  -864,  -864,  -864,  -864,  -864,
    -170,  -864,  -864,  -185,  -864,  -864,  -864,  -864,  -864
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   625,    92,    93,    43,    72,    89,    90,   647,   829,
     924,   925,   714,    45,    74,   101,   102,   103,   374,    47,
      75,   145,   146,   147,   382,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   396,   157,   384,    49,    76,   186,
     187,   188,   420,   189,   158,   385,   159,   386,   160,   387,
     738,   739,   740,   868,   715,   716,   717,   847,  1047,   718,
     848,   719,   849,   720,   850,   721,   722,   457,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   856,   732,   733,
     859,   734,   860,   735,   861,   161,   407,   772,   773,   774,
     888,   162,   404,   759,   760,   761,   762,   163,   406,   767,
     768,   769,   770,   164,   405,   165,   410,   783,   784,   785,
     897,    65,    84,   321,   322,   323,   470,   324,   471,   166,
     411,   792,   793,   794,   795,   796,   797,   798,   799,   167,
     397,   742,   743,   744,   871,    51,    77,   210,   211,   212,
     426,   213,   427,   214,   428,   215,   432,   216,   431,   168,
     402,   631,   218,   219,   169,   403,   754,   755,   756,   880,
     978,   979,   170,   398,    59,    81,   746,   747,   748,   874,
      61,    82,   286,   287,   288,   289,   290,   291,   292,   456,
     293,   460,   294,   459,   295,   296,   461,   297,   171,   399,
     750,   751,   752,   877,    63,    83,   307,   308,   309,   310,
     311,   465,   312,   313,   314,   315,   221,   424,   831,   832,
     833,   926,    53,    78,   232,   233,   234,   436,   172,   400,
     173,   401,   224,   425,   835,   836,   837,   929,    55,    79,
     248,   249,   250,   439,   251,   252,   441,   253,   254,   174,
     409,   779,   780,   781,   894,    57,    80,   266,   267,   268,
     269,   447,   270,   448,   271,   449,   272,   450,   273,   451,
     274,   452,   275,   446,   226,   433,   840,   841,   932,   175,
     408,   776,   777,   891,   996,   997,   998,   999,  1000,  1062,
    1001,   176,   412,   809,   810,   811,   908,  1071,   812,   813,
     909,   814,   815,   177,   178,   414,   821,   822,   823,   915,
     824,   916,   179,   415,   180,   416,    67,    85,   343,   344,
     345,   346,   475,   347,   476,   348,   349,   478,   350,   351,
     352,   481,   679,   353,   482,   354,   355,   356,   485,   686,
     357,   486,   358,   487,   359,   488,   104,   376,   105,   377,
     106,   378,   181,   383,    71,    87,   365,   366,   367,   493,
     368,   107,   375,    69,    86,   360,   361,   182,   417,   827,
     828,   920,  1030,  1031,  1032,  1033,  1077,  1034,  1075,  1096,
    1097,  1098,  1105,  1106,  1107,  1112,  1108,  1109,  1110
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   144,   185,   202,   228,   242,   262,   203,   284,   303,
     320,   340,   806,   766,   225,   305,   736,   971,   972,   204,
     190,   222,   235,   246,   264,   362,   298,   316,   973,   341,
      40,   977,   983,    94,   229,   243,   285,   304,   306,   205,
      33,   624,    34,    32,    35,   757,   206,   207,   183,   184,
    1101,   318,   319,  1102,  1103,  1104,   624,   208,    44,   653,
     209,   191,   223,   236,   247,   265,   883,   299,   317,   884,
     342,   659,   660,   661,   220,   231,   245,   263,   217,   886,
     277,   696,   887,    91,   230,   244,   697,   698,   699,   700,
     701,   702,   703,   704,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   892,   126,   127,   893,   114,   115,   116,
     117,   118,   119,   120,   278,   278,   279,   280,   125,    46,
     281,   282,   283,    99,   758,    48,   256,    50,   192,   380,
     193,   126,   127,   838,   381,    52,   126,   127,   194,   195,
     196,   197,   198,   128,   418,   921,   278,    54,   922,   419,
     125,   278,   800,   126,   127,   199,   363,   364,   200,   135,
     422,   701,   125,   126,   127,   423,   201,   434,   126,   127,
      56,  1099,   435,    95,  1100,   237,   238,   239,   240,   241,
     126,   127,    96,    97,    98,    58,   108,   109,   989,   990,
     110,   318,   319,   111,   112,   113,   971,   972,    60,   199,
      99,    62,   200,   126,   127,   816,   817,   973,    64,    99,
     977,   983,    36,    37,    38,    39,   677,   678,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     786,   787,   788,   789,   790,   791,    99,    99,    66,   437,
      68,    99,    70,  1023,   438,  1024,  1025,   126,   127,   801,
     802,   803,   804,   124,   128,   143,   125,   369,    99,   129,
     130,   131,   132,   133,   766,   134,   954,   227,    99,   370,
     135,   444,   472,    99,   126,   127,   445,   473,   489,   136,
     371,   372,   137,   490,   806,    99,   491,   495,   373,   138,
     418,   492,   496,   199,   491,   843,   200,   139,   140,   844,
     495,   141,   142,   379,   422,   845,   100,   388,    99,   846,
     114,   115,   116,   117,   118,   119,   120,   389,   865,   123,
     865,   125,   278,   866,   390,   867,   143,   391,   392,   681,
     682,   683,   684,   278,   300,   279,   280,   301,   302,   126,
     127,   393,   195,   196,   144,   198,   128,   394,   185,   889,
     126,   127,    99,   395,   890,   413,   421,   906,   199,   429,
     202,   200,   907,   228,   203,   685,   190,   430,   913,   201,
     242,   225,   917,   914,   440,   442,   204,   918,   222,    99,
     262,   235,   489,   497,   498,   443,   865,   919,   246,   458,
     284,  1055,   434,   229,  1059,   303,   205,  1056,   264,  1060,
     243,   305,   453,   206,   207,   472,  1078,   191,   298,   454,
    1067,  1079,   455,   316,   208,   340,   437,   209,   285,   223,
     444,  1081,   236,   304,   306,  1082,   462,  1116,   463,   247,
     362,   220,  1117,   341,   231,   217,   126,   127,   464,   265,
     125,   245,   466,   230,    99,  1043,  1044,  1045,  1046,   299,
     244,   263,   467,   468,   317,    99,   469,   499,   126,   127,
     627,   628,   629,   630,   757,   764,   474,   765,  1068,  1069,
    1070,   477,   479,   480,   342,   483,   255,   484,   494,   500,
     501,   502,   256,   257,   258,   259,   260,   261,   503,   504,
     506,   507,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   508,   509,   510,   511,   512,
     513,   514,   338,   339,   515,   611,   612,   613,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   520,   521,   144,   519,   516,   517,   518,
     522,    99,   185,   523,   524,   525,   526,   527,   528,   362,
     529,   530,   531,   532,   533,   534,   535,   536,   538,   539,
     190,   540,   537,    99,   541,   543,   546,   805,   818,   547,
     340,   548,   544,   549,   550,   551,   552,   553,   554,   555,
     557,   559,   561,   560,   565,   807,   819,   562,   341,   563,
     566,   567,   568,   569,   570,   571,   573,   574,   576,   673,
     577,   191,   578,   575,   581,   585,   579,   582,   583,   586,
     588,   589,   590,   592,   591,   593,   595,   594,   596,   599,
     597,   691,   598,   600,   601,   602,   808,   820,   605,   342,
     606,   608,   609,   610,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   870,   632,    34,   626,   633,   634,
     635,   873,   637,   636,   638,   639,   650,   651,   640,   641,
     642,   644,   645,   646,   648,   649,   652,   654,   655,   656,
     657,   658,   662,   663,   664,   665,   666,   667,   680,   690,
     737,   851,   668,   669,   670,   671,   672,   674,   675,   676,
     687,   688,   689,   741,   745,   749,   753,   775,   778,   771,
     782,   826,   830,   834,   852,   853,   854,   855,   857,   858,
     862,   863,   864,   940,   923,   869,   872,   875,   876,   878,
     879,   882,   881,   939,   896,   885,   895,   899,   898,   900,
     901,   902,   903,   904,   905,   910,   911,   912,   928,   942,
     927,   931,   930,   935,   941,   933,   934,   936,   937,   938,
     943,   944,   947,   948,   949,   987,  1014,   945,  1015,   946,
     950,   951,  1020,  1007,   952,  1021,  1036,  1037,   643,  1042,
    1057,  1058,  1063,  1008,  1064,  1009,  1065,  1010,  1066,  1076,
    1011,  1012,  1016,  1085,  1017,  1088,  1090,  1095,  1093,  1018,
    1048,  1113,  1114,  1049,  1050,  1051,  1115,   202,  1118,  1052,
     284,   203,   692,   303,   763,   542,   962,   842,   225,   305,
     963,  1089,  1053,   204,   505,   222,   953,   991,   298,  1054,
     262,   316,   964,   320,   981,   695,   985,   955,   285,   545,
     988,   304,   306,   205,   970,   994,   974,  1006,   264,   805,
     206,   207,   965,   818,  1061,   992,  1026,  1072,  1073,   966,
     967,   208,   228,  1074,   209,   242,   223,   807,  1080,   299,
     968,   819,   317,   969,  1028,   982,  1013,   986,   220,  1083,
     235,  1005,   217,   246,  1027,  1120,   995,   980,  1086,   265,
     587,   976,   229,   957,   556,   243,   975,   956,   993,  1092,
     984,   263,  1084,   276,  1119,   959,   958,   580,   808,   961,
    1094,   960,   820,  1039,  1038,  1029,  1040,  1041,   564,   558,
     584,   236,  1003,  1004,   247,   572,   839,  1002,  1087,  1121,
    1019,  1022,   694,   231,   607,   825,   245,  1091,   693,  1111,
    1123,  1122,   230,   603,   604,   244,  1035,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   962,     0,     0,     0,   963,
       0,   991,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   964,     0,   981,  1026,     0,     0,     0,     0,   994,
       0,     0,     0,   970,     0,   974,     0,     0,     0,   992,
       0,   965,  1028,     0,     0,     0,     0,     0,   966,   967,
       0,     0,  1027,     0,     0,     0,     0,     0,     0,   968,
       0,     0,   969,     0,   982,     0,     0,     0,     0,     0,
     995,     0,     0,     0,     0,     0,   980,     0,     0,     0,
     976,     0,   993,  1029,     0,   975
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,   641,   635,    77,    83,   618,   880,   880,    77,
      76,    77,    78,    79,    80,    86,    82,    83,   880,    85,
      17,   880,   880,    10,    78,    79,    82,    83,    83,    77,
       5,   524,     7,     0,     9,    98,    77,    77,    16,    17,
     153,   105,   106,   156,   157,   158,   539,    77,     7,   553,
      77,    76,    77,    78,    79,    80,     3,    82,    83,     6,
      85,   565,   566,   567,    77,    78,    79,    80,    77,     3,
      21,    21,     6,   177,    78,    79,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,    72,    73,     6,    43,    44,    45,
      46,    47,    48,    49,    55,    55,    57,    58,    54,     7,
      61,    62,    63,   177,   177,     7,    96,     7,    64,     3,
      66,    72,    73,   103,     8,     7,    72,    73,    74,    75,
      76,    77,    78,    79,     3,     3,    55,     7,     6,     8,
      54,    55,    21,    72,    73,    91,    13,    14,    94,    95,
       3,    30,    54,    72,    73,     8,   102,     3,    72,    73,
       7,     3,     8,   150,     6,    67,    68,    69,    70,    71,
      72,    73,   159,   160,   161,     7,    11,    12,    92,    93,
      15,   105,   106,    18,    19,    20,  1059,  1059,     7,    91,
     177,     7,    94,    72,    73,   124,   125,  1059,     7,   177,
    1059,  1059,   177,   178,   179,   180,   141,   142,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     108,   109,   110,   111,   112,   113,   177,   177,     7,     3,
       7,   177,     7,   152,     8,   154,   155,    72,    73,   118,
     119,   120,   121,    53,    79,   151,    54,     6,   177,    84,
      85,    86,    87,    88,   886,    90,   868,    65,   177,     3,
      95,     3,     3,   177,    72,    73,     8,     8,     3,   104,
       4,     8,   107,     8,   913,   177,     3,     3,     3,   114,
       3,     8,     8,    91,     3,     8,    94,   122,   123,     8,
       3,   126,   127,     4,     3,     8,   380,     4,   177,     8,
      43,    44,    45,    46,    47,    48,    49,     4,     3,    52,
       3,    54,    55,     8,     4,     8,   151,     4,     4,   144,
     145,   146,   147,    55,    56,    57,    58,    59,    60,    72,
      73,     4,    75,    76,   418,    78,    79,     4,   422,     3,
      72,    73,   177,     4,     8,     4,     4,     3,    91,     4,
     434,    94,     8,   437,   434,   180,   422,     4,     3,   102,
     444,   434,     3,     8,     4,     4,   434,     8,   434,   177,
     454,   437,     3,   370,   371,     4,     3,     8,   444,     4,
     464,     8,     3,   437,     3,   469,   434,     8,   454,     8,
     444,   469,     8,   434,   434,     3,     3,   422,   464,     3,
       8,     8,     8,   469,   434,   489,     3,   434,   464,   434,
       3,     8,   437,   469,   469,     8,     4,     3,     8,   444,
     491,   434,     8,   489,   437,   434,    72,    73,     3,   454,
      54,   444,     4,   437,   177,    22,    23,    24,    25,   464,
     444,   454,     4,     8,   469,   177,     3,   177,    72,    73,
      80,    81,    82,    83,    98,    99,     4,   101,   115,   116,
     117,     4,     4,     4,   489,     4,    90,     4,     4,     4,
       4,     4,    96,    97,    98,    99,   100,   101,     4,     4,
       4,     4,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     4,     4,     4,     4,   178,
     178,   178,   148,   149,   178,   502,   503,   504,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,     4,     4,   609,   178,   180,   179,   179,
       4,   177,   616,     4,     4,     4,     4,     4,     4,   610,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     616,     4,   178,   177,     4,     4,     4,   641,   642,     4,
     644,     4,   180,     4,     4,   178,   180,     4,     4,     4,
       4,     4,     4,   178,     4,   641,   642,   178,   644,   178,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   586,
       4,   616,     4,   178,     4,     4,   180,   180,   180,     4,
     180,     4,     4,     4,   178,   178,     4,   178,     4,     4,
     180,   608,   180,     4,     4,     4,   641,   642,     4,   644,
     178,     4,     7,     7,   177,     7,     7,     7,     7,     5,
     177,     5,     5,     5,     3,     5,     7,   177,     5,     5,
       5,     3,     5,     7,     5,     5,   177,   177,     7,     7,
       7,     7,     5,     5,     5,     5,   177,   177,     7,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   143,     5,
       7,     4,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,     7,     7,     7,     7,     7,     7,    89,
       7,     7,     7,     7,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   180,   177,     6,     6,     6,     3,     6,
       3,     3,     6,   178,     3,     6,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   180,
       6,     3,     6,     4,   178,     8,     6,     4,     4,     4,
     178,     4,     4,     4,     4,     4,     4,   178,     4,   178,
     178,   178,     4,   178,   180,     4,     6,     3,   539,     4,
       8,     8,     4,   178,     8,   178,     3,   178,     8,     4,
     178,   178,   178,     4,   178,     4,     4,     7,     5,   178,
     177,     4,     4,   177,   177,   177,     4,   871,     4,   177,
     874,   871,   609,   877,   634,   418,   880,   690,   871,   877,
     880,   178,   177,   871,   380,   871,   865,   891,   874,   177,
     894,   877,   880,   897,   880,   616,   883,   870,   874,   422,
     889,   877,   877,   871,   880,   891,   880,   899,   894,   913,
     871,   871,   880,   917,   177,   891,   920,   177,   177,   880,
     880,   871,   926,   177,   871,   929,   871,   913,   177,   874,
     880,   917,   877,   880,   920,   880,   906,   886,   871,   177,
     926,   897,   871,   929,   920,   178,   891,   880,   180,   894,
     472,   880,   926,   873,   434,   929,   880,   871,   891,   177,
     882,   894,  1059,    81,   180,   876,   874,   464,   913,   879,
     177,   877,   917,   928,   926,   920,   929,   931,   444,   437,
     469,   926,   894,   896,   929,   454,   655,   892,  1065,   178,
     913,   917,   615,   926,   495,   644,   929,  1078,   610,  1099,
     177,  1116,   926,   489,   491,   929,   921,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1059,    -1,    -1,    -1,  1059,
      -1,  1065,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1059,    -1,  1059,  1078,    -1,    -1,    -1,    -1,  1065,
      -1,    -1,    -1,  1059,    -1,  1059,    -1,    -1,    -1,  1065,
      -1,  1059,  1078,    -1,    -1,    -1,    -1,    -1,  1059,  1059,
      -1,    -1,  1078,    -1,    -1,    -1,    -1,    -1,    -1,  1059,
      -1,    -1,  1059,    -1,  1059,    -1,    -1,    -1,    -1,    -1,
    1065,    -1,    -1,    -1,    -1,    -1,  1059,    -1,    -1,    -1,
    1059,    -1,  1065,  1078,    -1,  1059
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,     0,     5,     7,     9,   177,   178,   179,   180,
     198,   199,   200,   205,     7,   214,     7,   220,     7,   238,
       7,   336,     7,   413,     7,   429,     7,   446,     7,   365,
       7,   371,     7,   395,     7,   312,     7,   507,     7,   554,
       7,   545,   206,   201,   215,   221,   239,   337,   414,   430,
     447,   366,   372,   396,   313,   508,   555,   546,   198,   207,
     208,   177,   203,   204,    10,   150,   159,   160,   161,   177,
     213,   216,   217,   218,   537,   539,   541,   552,    11,    12,
      15,    18,    19,    20,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    72,    73,    79,    84,
      85,    86,    87,    88,    90,    95,   104,   107,   114,   122,
     123,   126,   127,   151,   213,   222,   223,   224,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   236,   245,   247,
     249,   286,   292,   298,   304,   306,   320,   330,   350,   355,
     363,   389,   419,   421,   440,   470,   482,   494,   495,   503,
     505,   543,   558,    16,    17,   213,   240,   241,   242,   244,
     419,   421,    64,    66,    74,    75,    76,    77,    78,    91,
      94,   102,   213,   226,   227,   228,   229,   230,   231,   232,
     338,   339,   340,   342,   344,   346,   348,   350,   353,   354,
     389,   407,   419,   421,   423,   440,   465,    65,   213,   346,
     348,   389,   415,   416,   417,   419,   421,    67,    68,    69,
      70,    71,   213,   346,   348,   389,   419,   421,   431,   432,
     433,   435,   436,   438,   439,    90,    96,    97,    98,    99,
     100,   101,   213,   389,   419,   421,   448,   449,   450,   451,
     453,   455,   457,   459,   461,   463,   363,    21,    55,    57,
      58,    61,    62,    63,   213,   267,   373,   374,   375,   376,
     377,   378,   379,   381,   383,   385,   386,   388,   419,   421,
      56,    59,    60,   213,   267,   377,   383,   397,   398,   399,
     400,   401,   403,   404,   405,   406,   419,   421,   105,   106,
     213,   314,   315,   316,   318,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   148,   149,
     213,   419,   421,   509,   510,   511,   512,   514,   516,   517,
     519,   520,   521,   524,   526,   527,   528,   531,   533,   535,
     556,   557,   558,    13,    14,   547,   548,   549,   551,     6,
       3,     4,     8,     3,   219,   553,   538,   540,   542,     4,
       3,     8,   225,   544,   237,   246,   248,   250,     4,     4,
       4,     4,     4,     4,     4,     4,   235,   331,   364,   390,
     420,   422,   351,   356,   293,   305,   299,   287,   471,   441,
     307,   321,   483,     4,   496,   504,   506,   559,     3,     8,
     243,     4,     3,     8,   408,   424,   341,   343,   345,     4,
       4,   349,   347,   466,     3,     8,   418,     3,     8,   434,
       4,   437,     4,     4,     3,     8,   464,   452,   454,   456,
     458,   460,   462,     8,     3,     8,   380,   268,     4,   384,
     382,   387,     4,     8,     3,   402,     4,     4,     8,     3,
     317,   319,     3,     8,     4,   513,   515,     4,   518,     4,
       4,   522,   525,     4,     4,   529,   532,   534,   536,     3,
       8,     3,     8,   550,     4,     3,     8,   198,   198,   177,
       4,     4,     4,     4,     4,   217,     4,     4,     4,     4,
       4,     4,   178,   178,   178,   178,   180,   179,   179,   178,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   178,     4,     4,
       4,     4,   223,     4,   180,   241,     4,     4,     4,     4,
       4,   178,   180,     4,     4,     4,   339,     4,   416,     4,
     178,     4,   178,   178,   432,     4,     4,     4,     4,     4,
       4,     4,   450,     4,     4,   178,     4,     4,     4,   180,
     375,     4,   180,   180,   399,     4,     4,   315,   180,     4,
       4,   178,     4,   178,   178,     4,     4,   180,   180,     4,
       4,     4,     4,   510,   557,     4,   178,   548,     4,     7,
       7,   198,   198,   198,   177,     7,     7,     7,     7,     5,
     177,     5,     5,     5,   200,   202,   177,    80,    81,    82,
      83,   352,     5,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,   202,     7,     5,     5,   209,     5,     5,
     177,   177,   177,   209,   177,     7,   177,   177,   177,   209,
     209,   209,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   198,   177,   177,   177,   141,   142,   523,
     143,   144,   145,   146,   147,   180,   530,   177,   177,   177,
       5,   198,   222,   556,   547,   240,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,   213,   255,   256,   257,   260,   262,
     264,   266,   267,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   279,   280,   282,   284,   255,     7,   251,   252,
     253,     7,   332,   333,   334,     7,   367,   368,   369,     7,
     391,   392,   393,     7,   357,   358,   359,    98,   177,   294,
     295,   296,   297,   207,    99,   101,   296,   300,   301,   302,
     303,    89,   288,   289,   290,     7,   472,   473,     7,   442,
     443,   444,     7,   308,   309,   310,   108,   109,   110,   111,
     112,   113,   322,   323,   324,   325,   326,   327,   328,   329,
      21,   118,   119,   120,   121,   213,   269,   419,   421,   484,
     485,   486,   489,   490,   492,   493,   124,   125,   213,   419,
     421,   497,   498,   499,   501,   509,     7,   560,   561,   210,
       7,   409,   410,   411,     7,   425,   426,   427,   103,   451,
     467,   468,   251,     8,     8,     8,     8,   258,   261,   263,
     265,     4,     4,     4,     4,     4,   278,     4,     4,   281,
     283,   285,     4,     4,     4,     3,     8,     8,   254,     6,
       3,   335,     6,     3,   370,     6,     3,   394,     6,     3,
     360,     6,     3,     3,     6,     6,     3,     6,   291,     3,
       8,   474,     3,     6,   445,     6,     3,   311,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   487,   491,
       4,     4,     4,     3,     8,   500,   502,     3,     8,     8,
     562,     3,     6,   177,   211,   212,   412,     6,     3,   428,
       6,     3,   469,     8,     6,     4,     4,     4,     4,   178,
     180,   178,   180,   178,     4,   178,   178,     4,     4,     4,
     178,   178,   180,   256,   255,   253,   338,   334,   373,   369,
     397,   393,   213,   226,   227,   228,   229,   230,   231,   232,
     267,   330,   342,   344,   346,   348,   350,   354,   361,   362,
     389,   419,   421,   465,   359,   295,   301,     4,   289,    92,
      93,   213,   267,   389,   419,   421,   475,   476,   477,   478,
     479,   481,   473,   448,   444,   314,   310,   178,   178,   178,
     178,   178,   178,   323,     4,     4,   178,   178,   178,   485,
       4,     4,   498,   152,   154,   155,   213,   267,   419,   421,
     563,   564,   565,   566,   568,   561,     6,     3,   415,   411,
     431,   427,     4,    22,    23,    24,    25,   259,   177,   177,
     177,   177,   177,   177,   177,     8,     8,     8,     8,     3,
       8,   177,   480,     4,     8,     3,     8,     8,   115,   116,
     117,   488,   177,   177,   177,   569,     4,   567,     3,     8,
     177,     8,     8,   177,   362,     4,   180,   477,     4,   178,
       4,   564,   177,     5,   177,     7,   570,   571,   572,     3,
       6,   153,   156,   157,   158,   573,   574,   575,   577,   578,
     579,   571,   576,     4,     4,     4,     3,     8,     4,   180,
     178,   178,   574,   177
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   181,   183,   182,   184,   182,   185,   182,   186,   182,
     187,   182,   188,   182,   189,   182,   190,   182,   191,   182,
     192,   182,   193,   182,   194,   182,   195,   182,   196,   182,
     197,   182,   198,   198,   198,   198,   198,   198,   198,   199,
     201,   200,   202,   203,   203,   204,   204,   206,   205,   207,
     207,   208,   208,   210,   209,   211,   211,   212,   212,   213,
     215,   214,   216,   216,   217,   217,   217,   217,   217,   217,
     219,   218,   221,   220,   222,   222,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   225,   224,   226,   227,   228,   229,   230,
     231,   232,   233,   235,   234,   237,   236,   239,   238,   240,
     240,   241,   241,   241,   241,   241,   243,   242,   244,   246,
     245,   248,   247,   250,   249,   251,   251,   252,   252,   254,
     253,   255,   255,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   258,   257,   259,   259,   259,   259,   261,
     260,   263,   262,   265,   264,   266,   268,   267,   269,   270,
     271,   272,   273,   274,   275,   276,   278,   277,   279,   281,
     280,   283,   282,   285,   284,   287,   286,   288,   288,   289,
     291,   290,   293,   292,   294,   294,   295,   295,   296,   297,
     299,   298,   300,   300,   301,   301,   301,   302,   303,   305,
     304,   307,   306,   308,   308,   309,   309,   311,   310,   313,
     312,   314,   314,   314,   315,   315,   317,   316,   319,   318,
     321,   320,   322,   322,   323,   323,   323,   323,   323,   323,
     324,   325,   326,   327,   328,   329,   331,   330,   332,   332,
     333,   333,   335,   334,   337,   336,   338,   338,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   341,   340,   343,   342,   345,   344,   347,   346,   349,
     348,   351,   350,   352,   352,   352,   352,   353,   354,   356,
     355,   357,   357,   358,   358,   360,   359,   361,   361,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   364,
     363,   366,   365,   367,   367,   368,   368,   370,   369,   372,
     371,   373,   373,   374,   374,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   376,   377,   378,   380,   379,
     382,   381,   384,   383,   385,   387,   386,   388,   390,   389,
     391,   391,   392,   392,   394,   393,   396,   395,   397,   397,
     398,   398,   399,   399,   399,   399,   399,   399,   399,   399,
     399,   400,   402,   401,   403,   404,   405,   406,   408,   407,
     409,   409,   410,   410,   412,   411,   414,   413,   415,   415,
     416,   416,   416,   416,   416,   416,   416,   418,   417,   420,
     419,   422,   421,   424,   423,   425,   425,   426,   426,   428,
     427,   430,   429,   431,   431,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   434,   433,   435,   437,
     436,   438,   439,   441,   440,   442,   442,   443,   443,   445,
     444,   447,   446,   448,   448,   449,   449,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   452,   451,
     454,   453,   456,   455,   458,   457,   460,   459,   462,   461,
     464,   463,   466,   465,   467,   467,   469,   468,   471,   470,
     472,   472,   474,   473,   475,   475,   476,   476,   477,   477,
     477,   477,   477,   477,   477,   478,   480,   479,   481,   483,
     482,   484,   484,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   487,   486,   488,   488,   488,   489,   491,   490,
     492,   493,   494,   496,   495,   497,   497,   498,   498,   498,
     498,   498,   500,   499,   502,   501,   504,   503,   506,   505,
     508,   507,   509,   509,   510,   510,   510,   510,   510,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     510,   510,   511,   513,   512,   515,   514,   516,   518,   517,
     519,   520,   522,   521,   523,   523,   525,   524,   526,   527,
     529,   528,   530,   530,   530,   530,   530,   532,   531,   534,
     533,   536,   535,   538,   537,   540,   539,   542,   541,   544,
     543,   546,   545,   547,   547,   548,   548,   550,   549,   551,
     553,   552,   555,   554,   556,   556,   557,   559,   558,   560,
     560,   562,   561,   563,   563,   564,   564,   564,   564,   564,
     564,   564,   565,   567,   566,   569,   568,   570,   570,   572,
     571,   573,   573,   574,   574,   574,   574,   576,   575,   577,
     578,   579
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
       1,     1,     1,     0,     4,     3,     3,     3,     3,     3,
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
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
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
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
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
  "\"tcp-nodelay\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
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
  "preferred_lifetime", "valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@23", "interfaces_config",
  "$@24", "sub_interfaces6", "$@25", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@26", "re_detect",
  "lease_database", "$@27", "hosts_database", "$@28", "hosts_databases",
  "$@29", "database_list", "not_empty_database_list", "database", "$@30",
  "database_map_params", "database_map_param", "database_type", "$@31",
  "db_type", "user", "$@32", "password", "$@33", "host", "$@34", "port",
  "name", "$@35", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
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
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   265,   265,   265,   266,   266,   267,   267,   268,   268,
     269,   269,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     279,   279,   287,   288,   289,   290,   291,   292,   293,   296,
     301,   301,   312,   315,   316,   319,   323,   330,   330,   337,
     338,   341,   345,   352,   352,   359,   360,   363,   367,   378,
     388,   388,   403,   404,   408,   409,   410,   411,   412,   413,
     416,   416,   431,   431,   440,   441,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   485,   485,   493,   498,   503,   508,   513,
     518,   523,   528,   533,   533,   541,   541,   552,   552,   561,
     562,   565,   566,   567,   568,   569,   572,   572,   582,   588,
     588,   600,   600,   612,   612,   622,   623,   626,   627,   630,
     630,   640,   641,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   666,   666,   673,   674,   675,   676,   679,
     679,   687,   687,   695,   695,   703,   708,   708,   716,   721,
     726,   731,   736,   741,   746,   751,   756,   756,   764,   769,
     769,   777,   777,   785,   785,   793,   793,   803,   804,   806,
     808,   808,   826,   826,   836,   837,   840,   841,   844,   849,
     854,   854,   864,   865,   868,   869,   870,   873,   878,   885,
     885,   895,   895,   905,   906,   909,   910,   913,   913,   923,
     923,   933,   934,   935,   938,   939,   942,   942,   950,   950,
     958,   958,   969,   970,   973,   974,   975,   976,   977,   978,
     981,   986,   991,   996,  1001,  1006,  1014,  1014,  1027,  1028,
    1031,  1032,  1039,  1039,  1065,  1065,  1076,  1077,  1081,  1082,
    1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1106,  1106,  1114,  1114,  1122,  1122,  1130,  1130,  1138,
    1138,  1148,  1148,  1155,  1156,  1157,  1158,  1161,  1166,  1174,
    1174,  1185,  1186,  1190,  1191,  1194,  1194,  1202,  1203,  1206,
    1207,  1208,  1209,  1210,  1211,  1212,  1213,  1214,  1215,  1216,
    1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,  1232,
    1232,  1245,  1245,  1254,  1255,  1258,  1259,  1264,  1264,  1279,
    1279,  1293,  1294,  1297,  1298,  1301,  1302,  1303,  1304,  1305,
    1306,  1307,  1308,  1309,  1310,  1313,  1315,  1320,  1322,  1322,
    1330,  1330,  1338,  1338,  1346,  1348,  1348,  1356,  1365,  1365,
    1377,  1378,  1383,  1384,  1389,  1389,  1401,  1401,  1413,  1414,
    1419,  1420,  1425,  1426,  1427,  1428,  1429,  1430,  1431,  1432,
    1433,  1436,  1438,  1438,  1446,  1448,  1450,  1455,  1463,  1463,
    1475,  1476,  1479,  1480,  1483,  1483,  1493,  1493,  1502,  1503,
    1506,  1507,  1508,  1509,  1510,  1511,  1512,  1515,  1515,  1523,
    1523,  1548,  1548,  1578,  1578,  1590,  1591,  1594,  1595,  1598,
    1598,  1610,  1610,  1622,  1623,  1626,  1627,  1628,  1629,  1630,
    1631,  1632,  1633,  1634,  1635,  1636,  1639,  1639,  1647,  1652,
    1652,  1660,  1665,  1673,  1673,  1683,  1684,  1687,  1688,  1691,
    1691,  1700,  1700,  1709,  1710,  1713,  1714,  1718,  1719,  1720,
    1721,  1722,  1723,  1724,  1725,  1726,  1727,  1728,  1731,  1731,
    1741,  1741,  1751,  1751,  1759,  1759,  1767,  1767,  1775,  1775,
    1783,  1783,  1796,  1796,  1806,  1807,  1810,  1810,  1821,  1821,
    1831,  1832,  1835,  1835,  1845,  1846,  1849,  1850,  1853,  1854,
    1855,  1856,  1857,  1858,  1859,  1862,  1864,  1864,  1872,  1880,
    1880,  1892,  1893,  1896,  1897,  1898,  1899,  1900,  1901,  1902,
    1903,  1904,  1907,  1907,  1914,  1915,  1916,  1919,  1924,  1924,
    1932,  1937,  1944,  1951,  1951,  1961,  1962,  1965,  1966,  1967,
    1968,  1969,  1972,  1972,  1980,  1980,  1990,  1990,  2030,  2030,
    2042,  2042,  2052,  2053,  2056,  2057,  2058,  2059,  2060,  2061,
    2062,  2063,  2064,  2065,  2066,  2067,  2068,  2069,  2070,  2071,
    2072,  2073,  2076,  2081,  2081,  2089,  2089,  2097,  2102,  2102,
    2110,  2115,  2120,  2120,  2128,  2129,  2132,  2132,  2140,  2145,
    2150,  2150,  2158,  2161,  2164,  2167,  2170,  2176,  2176,  2184,
    2184,  2192,  2192,  2202,  2202,  2209,  2209,  2216,  2216,  2225,
    2225,  2236,  2236,  2246,  2247,  2251,  2252,  2255,  2255,  2265,
    2275,  2275,  2285,  2285,  2296,  2297,  2301,  2305,  2305,  2317,
    2318,  2322,  2322,  2330,  2331,  2334,  2335,  2336,  2337,  2338,
    2339,  2340,  2343,  2348,  2348,  2356,  2356,  2366,  2367,  2370,
    2370,  2378,  2379,  2382,  2383,  2384,  2385,  2388,  2388,  2396,
    2401,  2406
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


#line 14 "dhcp6_parser.yy" // lalr1.cc:1242
} } // isc::dhcp
#line 5197 "dhcp6_parser.cc" // lalr1.cc:1242
#line 2411 "dhcp6_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
