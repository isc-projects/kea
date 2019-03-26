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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:435

#include <dhcp4/parser_context.h>

#line 51 "dhcp4_parser.cc" // lalr1.cc:435


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:510
namespace isc { namespace dhcp {
#line 146 "dhcp4_parser.cc" // lalr1.cc:510

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
    :
#if PARSER4_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}

  Dhcp4Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp4Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp4Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 191: // value
      case 195: // map_value
      case 239: // socket_type
      case 242: // outbound_interface_value
      case 264: // db_type
      case 350: // hr_mode
      case 499: // ncr_protocol_value
      case 506: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 174: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 173: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 172: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 171: // "constant string"
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

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 191: // value
      case 195: // map_value
      case 239: // socket_type
      case 242: // outbound_interface_value
      case 264: // db_type
      case 350: // hr_mode
      case 499: // ncr_protocol_value
      case 506: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 174: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 173: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 172: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 171: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 191: // value
      case 195: // map_value
      case 239: // socket_type
      case 242: // outbound_interface_value
      case 264: // db_type
      case 350: // hr_mode
      case 499: // ncr_protocol_value
      case 506: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 174: // "boolean"
        value.move< bool > (that.value);
        break;

      case 173: // "floating point"
        value.move< double > (that.value);
        break;

      case 172: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 171: // "constant string"
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo,
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
      case 171: // "constant string"
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 407 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 172: // "integer"
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 173: // "floating point"
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 419 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 174: // "boolean"
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 425 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 191: // value
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 431 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 195: // map_value
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 239: // socket_type
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 242: // outbound_interface_value
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 264: // db_type
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 350: // hr_mode
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 499: // ncr_protocol_value
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 506: // replace_client_name_value
#line 253 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp4Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp4Parser::parse ()
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
      case 191: // value
      case 195: // map_value
      case 239: // socket_type
      case 242: // outbound_interface_value
      case 264: // db_type
      case 350: // hr_mode
      case 499: // ncr_protocol_value
      case 506: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 174: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 173: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 172: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 171: // "constant string"
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
#line 262 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 263 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 264 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 752 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 265 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 758 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 266 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET4; }
#line 764 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 267 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 268 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 776 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 269 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 782 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 270 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 788 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 271 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 794 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 272 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 800 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 273 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 806 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 274 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 812 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 275 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 818 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 283 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 824 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 31:
#line 284 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 830 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 285 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 286 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 842 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 287 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 848 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 288 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 854 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 289 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 860 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 292 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 869 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 297 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 302 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 890 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 308 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 43:
#line 315 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 44:
#line 319 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 915 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 326 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 924 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 329 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 932 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 49:
#line 337 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 941 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 50:
#line 341 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 950 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 348 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 958 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 350 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 55:
#line 359 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 976 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 56:
#line 363 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 985 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 374 "dhcp4_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 996 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 384 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1007 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 389 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1020 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 68:
#line 413 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 69:
#line 420 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 70:
#line 428 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 71:
#line 432 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 111:
#line 482 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 112:
#line 487 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 492 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 497 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 502 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1107 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 507 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 512 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 517 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 519 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 525 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 530 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 122:
#line 535 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 123:
#line 541 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 124:
#line 546 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 565 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1201 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 569 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1210 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 574 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 579 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 584 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 586 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 591 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 592 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 595 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 597 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 602 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 145:
#line 604 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1292 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 608 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 614 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 619 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 626 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 631 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 154:
#line 641 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 155:
#line 643 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 1371 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 156:
#line 659 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 157:
#line 664 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 158:
#line 671 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 159:
#line 676 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 164:
#line 689 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 693 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 725 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 727 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 732 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1456 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 733 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1462 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 734 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1468 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 735 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1474 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 738 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 740 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1492 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 746 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 748 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1510 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 754 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 756 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 762 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 201:
#line 767 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 202:
#line 769 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 775 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1564 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 780 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 785 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 790 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 207:
#line 795 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 208:
#line 800 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 209:
#line 805 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 210:
#line 810 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 812 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 818 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 820 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 826 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 828 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 216:
#line 834 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 217:
#line 836 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 842 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 219:
#line 847 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 220:
#line 852 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 857 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 229:
#line 873 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 878 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 883 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 888 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 893 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 898 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 903 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 916 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 920 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 926 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 930 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 945 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 947 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 953 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1859 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 955 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 961 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 966 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 263:
#line 984 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 264:
#line 989 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 994 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1916 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 999 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1925 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 269:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 270:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 275:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 276:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 277:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 278:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 308:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 312:
#line 1129 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 313:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 318:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 319:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 320:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2138 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 321:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 322:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 323:
#line 1173 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 324:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 325:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2176 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 326:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2182 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 327:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2188 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 328:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 329:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 330:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 335:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 336:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2235 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 361:
#line 1251 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 362:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2255 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 363:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2264 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 364:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 369:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 371:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2316 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 388:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 390:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 391:
#line 1343 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 392:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 393:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 395:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 397:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 398:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 399:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 401:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 406:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 407:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 408:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 409:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 424:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 428:
#line 1469 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1474 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 436:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 449:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 451:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2613 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 453:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 454:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2650 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 456:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 461:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2689 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 463:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 464:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 484:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 485:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1702 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2854 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1728 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 502:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2919 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 507:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 508:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 509:
#line 1768 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 512:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 513:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 516:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1798 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 534:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 535:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 536:
#line 1835 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 537:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 538:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3035 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 547:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 548:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 549:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 550:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1893 "dhcp4_parser.yy" // lalr1.cc:919
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

    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

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
#line 3126 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1941 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 577:
#line 1975 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 578:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 579:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 581:
#line 1990 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 582:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 2001 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 2003 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 585:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 586:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 587:
#line 2019 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 588:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2027 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3281 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3287 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3295 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2033 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3305 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2039 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2044 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2051 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3340 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2057 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3348 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2063 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3364 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3372 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2069 "dhcp4_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3381 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2075 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3389 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2077 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3399 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2083 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3407 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2085 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2093 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3435 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2102 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3443 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2104 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2109 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2111 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3469 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2118 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3486 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2123 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3497 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2128 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2134 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3517 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2138 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3526 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 622:
#line 2153 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2158 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2163 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3555 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2173 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3566 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2178 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3575 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2183 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3585 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3593 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 632:
#line 2203 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3604 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 633:
#line 2208 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3613 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2220 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3623 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2224 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3631 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 647:
#line 2241 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3640 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2246 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3648 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 649:
#line 2248 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3658 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 650:
#line 2254 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3669 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 651:
#line 2259 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3678 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 654:
#line 2268 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3688 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 655:
#line 2272 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3696 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 662:
#line 2286 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3704 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 663:
#line 2288 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3714 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2294 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3723 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2299 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3732 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 666:
#line 2304 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3741 "dhcp4_parser.cc" // lalr1.cc:919
    break;


#line 3745 "dhcp4_parser.cc" // lalr1.cc:919
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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Dhcp4Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short Dhcp4Parser::yypact_ninf_ = -828;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     332,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,    32,    35,    38,    52,    56,
      71,    75,    82,    84,   102,   110,   125,   143,   153,   163,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,    35,  -102,
      17,   170,    42,   520,    39,    45,   168,   188,   281,   -12,
     344,    37,   178,  -828,    74,   191,   217,   239,   253,  -828,
    -828,  -828,  -828,  -828,   269,  -828,    57,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,   279,   294,   296,  -828,
    -828,  -828,  -828,  -828,  -828,   298,   299,   321,   322,   323,
     324,   325,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,   328,  -828,  -828,  -828,  -828,
      59,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,   329,  -828,    68,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,   330,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
      76,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,   115,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,   268,   284,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,   334,  -828,  -828,   333,
    -828,  -828,  -828,   336,  -828,  -828,   335,   341,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,   342,   343,  -828,  -828,  -828,  -828,   340,   346,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,   123,  -828,  -828,  -828,   357,  -828,  -828,   362,  -828,
     363,   364,  -828,  -828,   365,   368,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,   126,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,   127,  -828,  -828,  -828,   370,   155,  -828,  -828,  -828,
    -828,    35,    35,  -828,   165,   373,   374,   375,   378,   381,
    -828,    17,  -828,   383,   385,   389,   164,   176,   221,   392,
     393,   394,   396,   397,   399,   233,   235,   237,   230,   241,
     245,   238,   409,   411,   412,   417,   419,   424,   425,   428,
     429,   436,   437,   439,   440,   273,   443,   444,   447,   170,
    -828,   451,   452,   453,   288,    42,  -828,   454,   460,   461,
     462,   463,   477,   310,   479,   480,   481,   520,  -828,   482,
      39,  -828,   499,   500,   501,   502,   503,   504,   505,   506,
    -828,    45,  -828,   507,   508,   345,   509,   510,   512,   347,
    -828,   188,   514,   348,   349,  -828,   281,   515,   516,    95,
    -828,   350,   522,   523,   356,   525,   358,   360,   529,   530,
     361,   367,   532,   533,   534,   535,   344,  -828,   538,    37,
    -828,   539,   379,   178,  -828,  -828,  -828,   541,   545,   546,
      35,    35,    35,  -828,   547,   548,   549,  -828,  -828,  -828,
     387,   390,   395,   553,   557,   560,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,   398,   562,   563,   566,   568,   567,   404,
     206,   577,   578,   579,   586,   585,  -828,   587,   567,   588,
    -828,   591,   194,   204,  -828,  -828,   422,   426,   427,   594,
     430,   442,  -828,   591,   445,   608,  -828,   448,  -828,   591,
     449,   450,   455,   456,   457,   458,   459,  -828,   464,   465,
    -828,   466,   473,   474,  -828,  -828,   476,  -828,  -828,  -828,
     478,    35,  -828,  -828,   483,   484,  -828,   485,  -828,  -828,
      28,   486,  -828,  -828,   -35,   487,   488,   489,  -828,   617,
    -828,   618,  -828,  -828,    35,   170,    37,  -828,  -828,  -828,
     178,    42,   607,  -828,  -828,  -828,   265,   265,   625,  -828,
     626,   627,   641,   643,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,    11,   646,   650,   654,    62,   -34,  -828,   344,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,   655,  -828,  -828,  -828,  -828,   108,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
     656,   625,  -828,   158,   177,   179,   215,  -828,   232,  -828,
    -828,  -828,  -828,  -828,  -828,   662,   664,   666,   667,   668,
    -828,  -828,  -828,  -828,   669,   670,   671,   673,   674,  -828,
     234,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,   240,  -828,   675,   677,  -828,  -828,   676,   680,  -828,
    -828,   678,   682,  -828,  -828,   683,   685,  -828,  -828,   684,
     689,  -828,  -828,  -828,  -828,  -828,  -828,    44,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,   113,  -828,  -828,   687,   691,
    -828,  -828,   690,   692,  -828,   693,   694,   695,   696,   697,
     698,   242,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,   243,  -828,  -828,  -828,   251,   536,
    -828,   699,   700,  -828,  -828,  -828,  -828,   701,  -828,   151,
    -828,   702,  -828,  -828,  -828,  -828,   706,   607,  -828,   707,
     708,   709,   710,   543,   542,   550,   544,   551,   713,   715,
     716,   717,   552,   554,   555,   556,   558,   265,  -828,  -828,
     265,  -828,   625,   520,  -828,   626,   188,  -828,   627,   281,
    -828,   641,   582,  -828,   643,    11,  -828,    73,   646,  -828,
      45,  -828,   650,   -12,  -828,   654,   559,   561,   564,   565,
     569,   570,    62,  -828,   721,   725,   -34,  -828,  -828,  -828,
     724,   703,    39,  -828,   655,   730,  -828,    70,   656,  -828,
    -828,   572,  -828,   286,   573,   574,   575,  -828,  -828,  -828,
    -828,  -828,   576,   580,   581,   583,  -828,  -828,  -828,  -828,
    -828,  -828,   264,  -828,   266,  -828,   727,  -828,   731,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,   272,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,   734,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,   732,   745,  -828,
    -828,  -828,  -828,  -828,   741,  -828,   274,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,   584,   589,  -828,  -828,   590,
     276,  -828,   591,  -828,   746,  -828,  -828,  -828,  -828,  -828,
     282,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,   582,  -828,   752,   592,  -828,    73,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,   753,   593,   754,    70,
    -828,  -828,   596,  -828,  -828,   681,  -828,   597,  -828,  -828,
     755,  -828,  -828,   161,  -828,   -58,   755,  -828,  -828,   759,
     760,   765,   283,  -828,  -828,  -828,  -828,  -828,  -828,   766,
     598,   599,   602,   -58,  -828,   604,  -828,  -828,  -828,  -828,
    -828
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   134,     9,   277,    11,
     438,    13,   463,    15,   363,    17,   371,    19,   408,    21,
     242,    23,   555,    25,   627,    27,   616,    29,    47,    41,
       0,     0,     0,     0,     0,   465,     0,   373,   410,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     625,   608,   610,   612,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   614,   123,   149,     0,     0,     0,   484,
     486,   488,   147,   156,   158,     0,     0,     0,     0,     0,
       0,     0,   118,   269,   361,   400,   329,   451,   453,   322,
     220,   512,   455,   234,   253,     0,   538,   551,   553,   110,
       0,    72,    74,    75,    76,   107,   108,   109,    77,   105,
      94,    95,    96,    80,    81,   102,    82,    83,    84,    88,
      89,    78,   106,    79,    86,    87,   100,   101,   103,    97,
      98,    99,    85,    90,    91,    92,    93,   104,   136,   138,
     142,     0,   133,     0,   125,   127,   128,   129,   130,   131,
     132,   310,   312,   314,   430,   308,   316,     0,   320,   318,
     508,   307,   281,   282,   283,   304,   305,   306,   294,   295,
       0,   279,   286,   299,   300,   301,   287,   289,   290,   292,
     288,   284,   285,   302,   303,   291,   296,   297,   298,   293,
     449,   448,   444,   445,   443,     0,   440,   442,   446,   447,
     506,   494,   496,   500,   498,   504,   502,   490,   483,   477,
     481,   482,     0,   466,   467,   478,   479,   480,   474,   469,
     475,   471,   472,   473,   476,   470,     0,   390,   201,     0,
     394,   392,   397,     0,   386,   387,     0,   374,   375,   377,
     389,   378,   379,   380,   396,   381,   382,   383,   384,   385,
     424,     0,     0,   422,   423,   426,   427,     0,   411,   412,
     414,   415,   416,   417,   418,   419,   420,   421,   249,   251,
     246,     0,   244,   247,   248,     0,   578,   580,     0,   583,
       0,     0,   587,   591,     0,     0,   595,   602,   604,   606,
     576,   574,   575,     0,   557,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     632,     0,   629,   631,   622,     0,     0,   618,   620,   621,
      46,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      57,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,   135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   278,     0,
       0,   439,     0,     0,     0,     0,     0,     0,     0,     0,
     464,     0,   364,     0,     0,     0,     0,     0,     0,     0,
     372,     0,     0,     0,     0,   409,     0,     0,     0,     0,
     243,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   556,     0,     0,
     628,     0,     0,     0,   617,    50,    43,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,   120,   121,   122,
       0,     0,     0,     0,     0,     0,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   537,     0,     0,     0,
      73,     0,     0,     0,   146,   126,     0,     0,     0,     0,
       0,     0,   328,     0,     0,     0,   280,     0,   441,     0,
       0,     0,     0,     0,     0,     0,     0,   468,     0,     0,
     388,     0,     0,     0,   399,   376,     0,   428,   429,   413,
       0,     0,   245,   577,     0,     0,   582,     0,   585,   586,
       0,     0,   593,   594,     0,     0,     0,     0,   558,     0,
     630,     0,   624,   619,     0,     0,     0,   609,   611,   613,
       0,     0,     0,   485,   487,   489,     0,     0,   160,   119,
     271,   365,   402,   331,    40,   452,   454,   324,   325,   326,
     327,   323,     0,     0,   457,   236,     0,     0,   552,     0,
      51,   137,   140,   141,   139,   144,   145,   143,   311,   313,
     315,   432,   309,   317,   321,   319,     0,   450,   507,   495,
     497,   501,   499,   505,   503,   491,   391,   202,   395,   393,
     398,   425,   250,   252,   579,   581,   584,   589,   590,   588,
     592,   597,   598,   599,   600,   601,   596,   603,   605,   607,
       0,   160,    44,     0,     0,     0,     0,   154,     0,   151,
     153,   188,   194,   196,   198,     0,     0,     0,     0,     0,
     210,   212,   214,   216,     0,     0,     0,     0,     0,   187,
       0,   166,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   181,   182,   183,   178,   184,   185,   186,   179,
     180,     0,   164,     0,   161,   162,   275,     0,   272,   273,
     369,     0,   366,   367,   406,     0,   403,   404,   335,     0,
     332,   333,   229,   230,   231,   232,   233,     0,   222,   224,
     225,   226,   227,   228,   516,     0,   514,   461,     0,   458,
     459,   240,     0,   237,   238,     0,     0,     0,     0,     0,
       0,     0,   255,   257,   258,   259,   260,   261,   262,   547,
     549,   546,   544,   545,     0,   540,   542,   543,     0,    53,
     436,     0,   433,   434,   492,   510,   511,     0,   636,     0,
     634,     0,    69,   626,   615,   124,     0,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   148,   157,
       0,   159,     0,     0,   270,     0,   373,   362,     0,   410,
     401,     0,     0,   330,     0,     0,   221,   518,     0,   513,
     465,   456,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,   254,     0,     0,     0,   539,   554,    55,
       0,    54,     0,   431,     0,     0,   509,     0,     0,   633,
     623,     0,   152,     0,     0,     0,     0,   200,   203,   204,
     205,   206,     0,     0,     0,     0,   218,   219,   207,   208,
     209,   167,     0,   163,     0,   274,     0,   368,     0,   405,
     360,   354,   342,   343,   357,   358,   359,   345,   346,   339,
     340,   341,   352,   353,   351,     0,   337,   344,   355,   356,
     347,   348,   349,   350,   334,   223,   534,     0,   532,   533,
     525,   526,   530,   531,   527,   528,   529,     0,   519,   520,
     522,   523,   524,   515,     0,   460,     0,   239,   263,   264,
     265,   266,   267,   268,   256,     0,     0,   541,    52,     0,
       0,   435,     0,   650,     0,   648,   646,   640,   644,   645,
       0,   638,   642,   643,   641,   635,   155,   190,   191,   192,
     193,   189,   195,   197,   199,   211,   213,   215,   217,   165,
     276,   370,   407,     0,   336,     0,     0,   517,     0,   462,
     241,   548,   550,    56,   437,   493,     0,     0,     0,     0,
     637,   338,     0,   536,   521,     0,   647,     0,   639,   535,
       0,   649,   654,     0,   652,     0,     0,   651,   662,     0,
       0,     0,     0,   656,   658,   659,   660,   661,   653,     0,
       0,     0,     0,     0,   655,     0,   664,   665,   666,   657,
     663
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,   -31,  -828,  -475,  -828,
     231,  -828,  -828,  -828,  -828,  -828,  -828,  -519,  -828,  -828,
    -828,   -70,  -828,  -828,  -828,   406,  -828,  -828,  -828,  -828,
     109,   369,   -47,   -44,     4,    12,    15,    19,  -828,  -828,
    -828,  -828,    23,    26,  -828,  -828,   187,   376,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,   -37,  -828,  -828,  -828,  -828,  -828,
    -828,   117,  -828,   -41,  -828,  -585,   -28,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,   -26,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,   -53,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,   -54,
    -828,  -828,  -828,   -48,   380,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,   -56,  -828,  -828,  -828,  -828,  -828,  -828,  -827,
    -828,  -828,  -828,   -23,  -828,  -828,  -828,   -15,   402,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -824,  -828,   -68,
    -828,   -55,  -828,    27,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,   -22,  -828,  -828,  -179,   -63,  -828,  -828,  -828,  -828,
    -828,   -13,  -828,  -828,  -828,    -4,  -828,   401,  -828,   -66,
    -828,  -828,  -828,  -828,  -828,   -64,  -828,  -828,  -828,  -828,
    -828,   -19,  -828,  -828,  -828,    -5,  -828,  -828,  -828,    10,
    -828,   388,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,   -11,  -828,  -828,  -828,   -10,   446,  -828,
    -828,   -57,  -828,   -39,  -828,   -62,  -828,  -828,  -828,    18,
    -828,  -828,  -828,    14,  -828,   441,    -7,  -828,    -3,  -828,
       8,  -828,   244,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -821,  -828,  -828,  -828,  -828,  -828,    25,  -828,  -828,  -828,
    -141,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,     5,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
     255,   410,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,  -828,   285,   405,
    -828,  -828,  -828,  -828,  -828,  -828,  -828,   291,   413,  -828,
    -828,  -828,     1,  -828,  -828,  -138,  -828,  -828,  -828,  -828,
    -828,  -828,  -153,  -828,  -828,  -169,  -828,  -828,  -828,  -828,
    -828
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     615,    87,    88,    41,    68,    84,    85,   631,   799,   880,
     881,   709,    43,    70,    96,    97,    98,   365,    45,    71,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     392,   150,   151,   152,   153,   374,   183,   184,    47,    72,
     185,   411,   186,   412,   634,   187,   413,   637,   188,   154,
     382,   155,   375,   688,   689,   690,   816,   156,   383,   157,
     384,   733,   734,   735,   840,   710,   711,   712,   819,  1001,
     713,   820,   714,   821,   715,   822,   716,   717,   444,   718,
     719,   720,   721,   722,   723,   724,   725,   828,   726,   829,
     727,   830,   728,   831,   729,   730,   158,   400,   757,   758,
     759,   760,   761,   762,   763,   159,   403,   772,   773,   774,
     863,    61,    79,   311,   312,   313,   457,   314,   458,   160,
     404,   781,   782,   783,   784,   785,   786,   787,   788,   161,
     393,   737,   738,   739,   843,    49,    73,   210,   211,   212,
     421,   213,   417,   214,   418,   215,   419,   216,   422,   217,
     425,   218,   424,   162,   399,   621,   220,   163,   396,   749,
     750,   751,   852,   935,   936,   164,   394,    55,    76,   741,
     742,   743,   846,    57,    77,   276,   277,   278,   279,   280,
     281,   282,   443,   283,   447,   284,   446,   285,   286,   448,
     287,   165,   395,   745,   746,   747,   849,    59,    78,   297,
     298,   299,   300,   301,   452,   302,   303,   304,   305,   222,
     420,   801,   802,   803,   882,    51,    74,   235,   236,   237,
     429,   166,   397,   167,   398,   168,   402,   768,   769,   770,
     860,    53,    75,   252,   253,   254,   169,   379,   170,   380,
     171,   381,   258,   439,   806,   885,   259,   433,   260,   434,
     261,   436,   262,   435,   263,   438,   264,   437,   265,   432,
     229,   426,   807,   172,   401,   765,   766,   857,   957,   958,
     959,   960,   961,  1015,   962,   173,   174,   406,   794,   795,
     796,   874,   797,   875,   175,   407,   176,   408,    63,    80,
     333,   334,   335,   336,   462,   337,   463,   338,   339,   465,
     340,   341,   342,   468,   669,   343,   469,   344,   345,   346,
     472,   676,   347,   473,   348,   474,   349,   475,    99,   367,
     100,   368,   101,   369,   177,   373,    67,    82,   356,   357,
     358,   481,   359,   102,   366,    65,    81,   351,   352,   353,
     478,   809,   810,   887,   990,   991,   992,   993,  1028,   994,
    1026,  1043,  1044,  1045,  1052,  1053,  1054,  1059,  1055,  1056,
    1057
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   139,   182,   201,   231,   248,   232,   274,   293,   310,
     330,   225,   295,   266,   296,   189,   223,   238,   250,   233,
     288,   306,   731,   331,   644,   930,   202,    89,   931,   203,
     648,   943,    30,   190,   224,   239,   251,    83,   289,   307,
      31,   332,    32,   614,    33,    42,   667,   855,   127,   128,
     856,   275,   294,   614,   221,   234,   249,   178,   179,    44,
     371,   180,   409,    46,   181,   372,   226,   410,   255,    86,
     227,   415,   256,   109,   110,   111,   416,   204,    48,   427,
     360,   228,    50,   257,   428,   205,   789,   790,   206,    52,
    1048,    54,   207,  1049,  1050,  1051,   208,   308,   309,   209,
     219,   109,   110,   111,   671,   672,   673,   674,   125,    56,
     752,   753,   754,   755,   125,   756,   858,    58,   430,   859,
     230,   127,   128,   431,   127,   128,   459,   127,   128,   476,
     479,   460,    60,   198,   477,   480,   199,    94,   240,   675,
     268,   124,   125,   268,   241,   242,   243,   244,   245,   246,
      62,   247,   127,   128,   888,   127,   128,   889,   483,    94,
      64,   409,    90,   484,  1046,   668,   812,  1047,   946,   947,
      66,    91,    92,    93,   775,   776,   777,   778,   779,   780,
     479,   103,   483,   350,   104,   813,   930,   814,    94,   931,
     354,   355,   943,   105,   361,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   308,   309,    34,    35,    36,    37,
      94,   632,   633,    94,   247,   804,    94,   983,   415,   984,
     985,   362,   267,   815,   635,   636,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   817,   124,   837,   124,   125,
     818,    94,   838,   837,    94,   872,   876,   363,   839,   126,
     873,   877,   127,   128,   476,   912,   364,   129,   268,   878,
     269,   270,   130,   131,   271,   272,   273,   837,   132,   427,
     127,   128,  1009,   370,  1010,  1013,   440,   459,   133,   430,
    1014,   134,  1020,   376,  1024,  1029,  1063,   441,   135,   136,
    1030,  1064,   137,   138,   617,   618,   619,   620,   377,   691,
     378,    95,   385,   386,   692,   693,   694,   695,   696,   697,
     698,   699,   700,   701,   702,   703,   704,   705,   706,   707,
     708,   997,   998,   999,  1000,   387,   388,   389,   390,   391,
     485,   486,   405,   414,   423,   268,   487,   445,   497,   139,
     449,    94,   442,   450,   451,   182,   453,   454,   455,   456,
     498,   268,   290,   269,   270,   291,   292,   201,   189,    94,
     231,   461,   232,   127,   128,   225,   464,   466,   467,   470,
     223,   248,   471,   238,   482,   233,   190,   488,   489,   490,
     202,   274,   491,   203,   250,   492,   293,   494,   224,   495,
     295,   239,   296,   496,   288,   499,   500,   501,   502,   306,
     503,   504,   251,   505,   509,   506,   330,   507,   221,   508,
     512,   234,   289,   513,   510,   514,   515,   307,   511,   331,
     226,   516,   249,   517,   227,   275,   127,   128,   518,   519,
     294,   204,   520,   521,   255,   228,    94,   332,   256,   205,
     522,   523,   206,   524,   525,   526,   207,   527,   528,   257,
     208,   529,    94,   209,   219,   531,   532,   533,   536,   597,
     598,   599,   534,  1025,   537,   538,   539,   540,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   541,   542,   543,   544,   545,   547,   328,   329,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   549,   550,   551,   552,   553,   554,   555,
     556,   558,   559,   561,   562,    94,   563,   560,   566,   570,
     571,   564,   567,   568,   573,   139,   574,   575,   576,   577,
     578,   182,   579,   580,   581,   582,   584,   585,   586,   587,
     663,   583,   589,   591,   189,   594,   107,   108,   109,   110,
     111,   592,   595,   596,   600,   601,   602,   791,   603,   330,
     606,   604,   190,   682,   607,   608,   605,   610,   611,   609,
     792,   612,   331,   613,    32,   616,   115,   116,   117,   118,
     119,   120,   622,   623,   624,   191,   192,   193,   793,   125,
     332,   625,   626,   638,   627,   629,   630,   639,   640,   641,
     194,   642,   127,   128,   195,   196,   197,   129,   107,   108,
     109,   110,   111,   643,   198,   646,   645,   199,   132,   647,
     649,   650,   680,   681,   670,   200,   651,   652,   653,   654,
     655,   687,   732,   736,   740,   656,   657,   658,   115,   116,
     117,   118,   119,   120,   659,   660,   123,   661,   744,   662,
     748,   125,   268,   764,   664,   665,   666,   767,   677,   678,
     679,   771,   800,   808,   127,   128,   823,   196,   824,   129,
     825,   826,   827,   832,   833,   834,   198,   835,   836,   199,
     842,   841,   844,   845,   847,   848,  1040,   200,   851,   850,
     853,    94,   854,   861,   862,   865,   864,   866,   867,   868,
     869,   870,   871,   884,   683,   883,   979,   879,   890,   886,
     891,   893,   894,   895,   896,   897,   898,   902,   900,   903,
     904,   905,   899,   901,   906,   975,   907,   908,   909,   976,
     978,   968,   910,   969,   982,  1011,   970,   971,  1016,  1012,
    1017,   972,   973,   996,  1002,  1003,  1004,  1005,  1018,  1019,
    1027,  1006,  1007,    94,  1008,  1021,  1032,  1035,  1037,   628,
    1022,  1023,  1042,  1060,  1061,  1036,  1033,  1039,  1041,  1062,
    1065,  1067,  1066,   201,  1068,  1070,   274,   493,   530,   293,
     892,   225,   920,   295,   932,   296,   223,   948,   686,   288,
     248,   535,   306,   310,   950,   938,   202,   933,   811,   203,
     952,   913,   945,   250,   224,   921,   791,   289,   922,   911,
     307,   967,   231,   939,   232,   966,   974,   986,   953,   792,
     275,   251,   915,   294,   221,   238,   929,   233,   914,   546,
     988,   949,   944,   937,  1031,   917,   226,   793,   951,   572,
     227,   249,   916,   239,   569,   940,   919,   204,   989,   941,
     954,   228,   565,   255,   955,   205,   923,   256,   206,   918,
     942,   987,   207,   234,   924,   956,   208,   925,   257,   209,
     219,   926,   980,   981,   964,   927,   548,  1034,   928,   934,
     965,   977,   557,   963,   798,   685,   588,   684,   593,   995,
     805,  1038,   590,  1058,  1069,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   920,     0,   932,     0,     0,   948,     0,
       0,     0,     0,     0,     0,   950,   938,     0,   933,   986,
       0,   952,     0,     0,     0,     0,   921,     0,     0,   922,
       0,     0,   988,     0,   939,     0,     0,     0,     0,   953,
       0,     0,     0,     0,     0,     0,     0,   929,     0,     0,
     989,     0,   949,     0,   937,     0,     0,     0,     0,   951,
       0,     0,     0,   987,     0,     0,   940,     0,     0,     0,
     941,   954,     0,     0,     0,   955,     0,   923,     0,     0,
       0,   942,     0,     0,     0,   924,   956,     0,   925,     0,
       0,     0,   926,     0,     0,     0,   927,     0,     0,   928,
     934
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,    74,
      77,    78,   607,    80,   543,   852,    73,    10,   852,    73,
     549,   852,     0,    72,    73,    74,    75,    68,    77,    78,
       5,    80,     7,   518,     9,     7,    18,     3,    82,    83,
       6,    77,    78,   528,    73,    74,    75,    15,    16,     7,
       3,    19,     3,     7,    22,     8,    73,     8,    75,   171,
      73,     3,    75,    28,    29,    30,     8,    73,     7,     3,
       6,    73,     7,    75,     8,    73,   120,   121,    73,     7,
     148,     7,    73,   151,   152,   153,    73,   109,   110,    73,
      73,    28,    29,    30,   139,   140,   141,   142,    69,     7,
      99,   100,   101,   102,    69,   104,     3,     7,     3,     6,
      81,    82,    83,     8,    82,    83,     3,    82,    83,     3,
       3,     8,     7,    94,     8,     8,    97,   171,    93,   174,
      70,    68,    69,    70,    99,   100,   101,   102,   103,   104,
       7,   106,    82,    83,     3,    82,    83,     6,     3,   171,
       7,     3,   145,     8,     3,   137,     8,     6,    95,    96,
       7,   154,   155,   156,   112,   113,   114,   115,   116,   117,
       3,    11,     3,   146,    14,     8,  1013,     8,   171,  1013,
      12,    13,  1013,    23,     3,    25,    26,    27,    28,    29,
      30,    31,    32,    33,   109,   110,   171,   172,   173,   174,
     171,    17,    18,   171,   106,   107,   171,   147,     3,   149,
     150,     4,    34,     8,    20,    21,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     3,    68,     3,    68,    69,
       8,   171,     8,     3,   171,     3,     3,     8,     8,    79,
       8,     8,    82,    83,     3,   840,     3,    87,    70,     8,
      72,    73,    92,    93,    76,    77,    78,     3,    98,     3,
      82,    83,     8,     4,     8,     3,     8,     3,   108,     3,
       8,   111,     8,     4,     8,     3,     3,     3,   118,   119,
       8,     8,   122,   123,    88,    89,    90,    91,     4,    34,
       4,   371,     4,     4,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    35,    36,    37,    38,     4,     4,     4,     4,     4,
     361,   362,     4,     4,     4,    70,   171,     4,   174,   409,
       4,   171,     8,     8,     3,   415,     4,     4,     8,     3,
     174,    70,    71,    72,    73,    74,    75,   427,   415,   171,
     430,     4,   430,    82,    83,   427,     4,     4,     4,     4,
     427,   441,     4,   430,     4,   430,   415,     4,     4,     4,
     427,   451,     4,   427,   441,     4,   456,     4,   427,     4,
     456,   430,   456,     4,   451,   174,     4,     4,     4,   456,
       4,     4,   441,     4,   174,   172,   476,   172,   427,   172,
     172,   430,   451,     4,   173,     4,     4,   456,   173,   476,
     427,     4,   441,     4,   427,   451,    82,    83,     4,     4,
     456,   427,     4,     4,   441,   427,   171,   476,   441,   427,
       4,     4,   427,     4,     4,   172,   427,     4,     4,   441,
     427,     4,   171,   427,   427,     4,     4,     4,     4,   490,
     491,   492,   174,   982,     4,     4,     4,     4,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,     4,   172,     4,     4,     4,     4,   143,   144,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   171,     4,   172,     4,     4,
       4,   174,   174,   174,   174,   595,     4,     4,   172,     4,
     172,   601,   172,     4,     4,   174,     4,     4,     4,     4,
     571,   174,     4,     4,   601,     4,    26,    27,    28,    29,
      30,   172,     7,     7,     7,     7,     7,   627,   171,   629,
       7,   171,   601,   594,     7,     5,   171,     5,     5,   171,
     627,     5,   629,     5,     7,   171,    56,    57,    58,    59,
      60,    61,     5,     5,     5,    65,    66,    67,   627,    69,
     629,     5,     7,   171,     7,     7,     5,   171,   171,     5,
      80,   171,    82,    83,    84,    85,    86,    87,    26,    27,
      28,    29,    30,   171,    94,     7,   171,    97,    98,   171,
     171,   171,     5,     5,   138,   105,   171,   171,   171,   171,
     171,    24,     7,     7,     7,   171,   171,   171,    56,    57,
      58,    59,    60,    61,   171,   171,    64,   171,     7,   171,
       7,    69,    70,     7,   171,   171,   171,     7,   171,   171,
     171,     7,     7,     7,    82,    83,     4,    85,     4,    87,
       4,     4,     4,     4,     4,     4,    94,     4,     4,    97,
       3,     6,     6,     3,     6,     3,     5,   105,     3,     6,
       6,   171,     3,     6,     3,     3,     6,     4,     4,     4,
       4,     4,     4,     3,   595,     6,     3,   171,     6,     8,
       4,     4,     4,     4,     4,   172,   174,     4,   174,     4,
       4,     4,   172,   172,   172,     4,   172,   172,   172,     4,
       6,   172,   174,   172,     4,     8,   172,   172,     4,     8,
       8,   172,   172,   171,   171,   171,   171,   171,     3,     8,
       4,   171,   171,   171,   171,   171,     4,     4,     4,   528,
     171,   171,     7,     4,     4,   172,   174,   171,   171,     4,
       4,   172,   174,   843,   172,   171,   846,   371,   409,   849,
     817,   843,   852,   849,   852,   849,   843,   857,   601,   846,
     860,   415,   849,   863,   857,   852,   843,   852,   681,   843,
     857,   842,   855,   860,   843,   852,   876,   846,   852,   837,
     849,   865,   882,   852,   882,   863,   872,   887,   857,   876,
     846,   860,   845,   849,   843,   882,   852,   882,   843,   427,
     887,   857,   854,   852,  1013,   848,   843,   876,   857,   459,
     843,   860,   846,   882,   456,   852,   851,   843,   887,   852,
     857,   843,   451,   860,   857,   843,   852,   860,   843,   849,
     852,   887,   843,   882,   852,   857,   843,   852,   860,   843,
     843,   852,   882,   884,   860,   852,   430,  1018,   852,   852,
     862,   876,   441,   858,   629,   600,   476,   596,   483,   888,
     646,  1029,   479,  1046,  1063,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1013,    -1,  1013,    -1,    -1,  1018,    -1,
      -1,    -1,    -1,    -1,    -1,  1018,  1013,    -1,  1013,  1029,
      -1,  1018,    -1,    -1,    -1,    -1,  1013,    -1,    -1,  1013,
      -1,    -1,  1029,    -1,  1013,    -1,    -1,    -1,    -1,  1018,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1013,    -1,    -1,
    1029,    -1,  1018,    -1,  1013,    -1,    -1,    -1,    -1,  1018,
      -1,    -1,    -1,  1029,    -1,    -1,  1013,    -1,    -1,    -1,
    1013,  1018,    -1,    -1,    -1,  1018,    -1,  1013,    -1,    -1,
      -1,  1013,    -1,    -1,    -1,  1013,  1018,    -1,  1013,    -1,
      -1,    -1,  1013,    -1,    -1,    -1,  1013,    -1,    -1,  1013,
    1013
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
       0,     5,     7,     9,   171,   172,   173,   174,   191,   192,
     193,   198,     7,   207,     7,   213,     7,   233,     7,   330,
       7,   410,     7,   426,     7,   362,     7,   368,     7,   392,
       7,   306,     7,   483,     7,   530,     7,   521,   199,   194,
     208,   214,   234,   331,   411,   427,   363,   369,   393,   307,
     484,   531,   522,   191,   200,   201,   171,   196,   197,    10,
     145,   154,   155,   156,   171,   206,   209,   210,   211,   513,
     515,   517,   528,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    68,    69,    79,    82,    83,    87,
      92,    93,    98,   108,   111,   118,   119,   122,   123,   206,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     226,   227,   228,   229,   244,   246,   252,   254,   291,   300,
     314,   324,   348,   352,   360,   386,   416,   418,   420,   431,
     433,   435,   458,   470,   471,   479,   481,   519,    15,    16,
      19,    22,   206,   231,   232,   235,   237,   240,   243,   416,
     418,    65,    66,    67,    80,    84,    85,    86,    94,    97,
     105,   206,   217,   218,   219,   220,   221,   222,   227,   228,
     332,   333,   334,   336,   338,   340,   342,   344,   346,   348,
     351,   386,   404,   416,   418,   420,   431,   433,   435,   455,
      81,   206,   344,   346,   386,   412,   413,   414,   416,   418,
      93,    99,   100,   101,   102,   103,   104,   106,   206,   386,
     416,   418,   428,   429,   430,   431,   433,   435,   437,   441,
     443,   445,   447,   449,   451,   453,   360,    34,    70,    72,
      73,    76,    77,    78,   206,   272,   370,   371,   372,   373,
     374,   375,   376,   378,   380,   382,   383,   385,   416,   418,
      71,    74,    75,   206,   272,   374,   380,   394,   395,   396,
     397,   398,   400,   401,   402,   403,   416,   418,   109,   110,
     206,   308,   309,   310,   312,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   143,   144,
     206,   416,   418,   485,   486,   487,   488,   490,   492,   493,
     495,   496,   497,   500,   502,   503,   504,   507,   509,   511,
     146,   532,   533,   534,    12,    13,   523,   524,   525,   527,
       6,     3,     4,     8,     3,   212,   529,   514,   516,   518,
       4,     3,     8,   520,   230,   247,     4,     4,     4,   432,
     434,   436,   245,   253,   255,     4,     4,     4,     4,     4,
       4,     4,   225,   325,   361,   387,   353,   417,   419,   349,
     292,   459,   421,   301,   315,     4,   472,   480,   482,     3,
       8,   236,   238,   241,     4,     3,     8,   337,   339,   341,
     405,   335,   343,     4,   347,   345,   456,     3,     8,   415,
       3,     8,   454,   442,   444,   448,   446,   452,   450,   438,
       8,     3,     8,   377,   273,     4,   381,   379,   384,     4,
       8,     3,   399,     4,     4,     8,     3,   311,   313,     3,
       8,     4,   489,   491,     4,   494,     4,     4,   498,   501,
       4,     4,   505,   508,   510,   512,     3,     8,   535,     3,
       8,   526,     4,     3,     8,   191,   191,   171,     4,     4,
       4,     4,     4,   210,     4,     4,     4,   174,   174,   174,
       4,     4,     4,     4,     4,     4,   172,   172,   172,   174,
     173,   173,   172,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   172,     4,     4,     4,
     216,     4,     4,     4,   174,   232,     4,     4,     4,     4,
       4,     4,   172,     4,     4,     4,   333,     4,   413,     4,
       4,     4,     4,     4,     4,     4,     4,   430,     4,     4,
     172,     4,     4,     4,   174,   372,     4,   174,   174,   396,
       4,     4,   309,   174,     4,     4,   172,     4,   172,   172,
       4,     4,   174,   174,     4,     4,     4,     4,   486,     4,
     533,     4,   172,   524,     4,     7,     7,   191,   191,   191,
       7,     7,     7,   171,   171,   171,     7,     7,     5,   171,
       5,     5,     5,     5,   193,   195,   171,    88,    89,    90,
      91,   350,     5,     5,     5,     5,     7,     7,   195,     7,
       5,   202,    17,    18,   239,    20,    21,   242,   171,   171,
     171,     5,   171,   171,   202,   171,     7,   171,   202,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   191,   171,   171,   171,    18,   137,   499,
     138,   139,   140,   141,   142,   174,   506,   171,   171,   171,
       5,     5,   191,   215,   532,   523,   231,    24,   248,   249,
     250,    34,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,   206,
     260,   261,   262,   265,   267,   269,   271,   272,   274,   275,
     276,   277,   278,   279,   280,   281,   283,   285,   287,   289,
     290,   260,     7,   256,   257,   258,     7,   326,   327,   328,
       7,   364,   365,   366,     7,   388,   389,   390,     7,   354,
     355,   356,    99,   100,   101,   102,   104,   293,   294,   295,
     296,   297,   298,   299,     7,   460,   461,     7,   422,   423,
     424,     7,   302,   303,   304,   112,   113,   114,   115,   116,
     117,   316,   317,   318,   319,   320,   321,   322,   323,   120,
     121,   206,   416,   418,   473,   474,   475,   477,   485,   203,
       7,   406,   407,   408,   107,   437,   439,   457,     7,   536,
     537,   256,     8,     8,     8,     8,   251,     3,     8,   263,
     266,   268,   270,     4,     4,     4,     4,     4,   282,   284,
     286,   288,     4,     4,     4,     4,     4,     3,     8,     8,
     259,     6,     3,   329,     6,     3,   367,     6,     3,   391,
       6,     3,   357,     6,     3,     3,     6,   462,     3,     6,
     425,     6,     3,   305,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   476,   478,     3,     8,     8,   171,
     204,   205,   409,     6,     3,   440,     8,   538,     3,     6,
       6,     4,   249,     4,     4,     4,     4,   172,   174,   172,
     174,   172,     4,     4,     4,     4,   172,   172,   172,   172,
     174,   261,   260,   258,   332,   328,   370,   366,   394,   390,
     206,   217,   218,   219,   220,   221,   222,   227,   228,   272,
     324,   342,   344,   346,   348,   358,   359,   386,   416,   418,
     431,   433,   435,   455,   356,   294,    95,    96,   206,   272,
     360,   386,   416,   418,   431,   433,   435,   463,   464,   465,
     466,   467,   469,   461,   428,   424,   308,   304,   172,   172,
     172,   172,   172,   172,   317,     4,     4,   474,     6,     3,
     412,   408,     4,   147,   149,   150,   206,   272,   416,   418,
     539,   540,   541,   542,   544,   537,   171,    35,    36,    37,
      38,   264,   171,   171,   171,   171,   171,   171,   171,     8,
       8,     8,     8,     3,     8,   468,     4,     8,     3,     8,
       8,   171,   171,   171,     8,   202,   545,     4,   543,     3,
       8,   359,     4,   174,   465,     4,   172,     4,   540,   171,
       5,   171,     7,   546,   547,   548,     3,     6,   148,   151,
     152,   153,   549,   550,   551,   553,   554,   555,   547,   552,
       4,     4,     4,     3,     8,     4,   174,   172,   172,   550,
     171
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   175,   177,   176,   178,   176,   179,   176,   180,   176,
     181,   176,   182,   176,   183,   176,   184,   176,   185,   176,
     186,   176,   187,   176,   188,   176,   189,   176,   190,   176,
     191,   191,   191,   191,   191,   191,   191,   192,   194,   193,
     195,   196,   196,   197,   197,   199,   198,   200,   200,   201,
     201,   203,   202,   204,   204,   205,   205,   206,   208,   207,
     209,   209,   210,   210,   210,   210,   210,   210,   212,   211,
     214,   213,   215,   215,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   217,   218,   219,   220,   221,   222,   223,   225,   224,
     226,   227,   228,   230,   229,   231,   231,   232,   232,   232,
     232,   232,   232,   232,   234,   233,   236,   235,   238,   237,
     239,   239,   241,   240,   242,   242,   243,   245,   244,   247,
     246,   248,   248,   249,   251,   250,   253,   252,   255,   254,
     256,   256,   257,   257,   259,   258,   260,   260,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   263,   262,
     264,   264,   264,   264,   266,   265,   268,   267,   270,   269,
     271,   273,   272,   274,   275,   276,   277,   278,   279,   280,
     282,   281,   284,   283,   286,   285,   288,   287,   289,   290,
     292,   291,   293,   293,   294,   294,   294,   294,   294,   295,
     296,   297,   298,   299,   301,   300,   302,   302,   303,   303,
     305,   304,   307,   306,   308,   308,   308,   309,   309,   311,
     310,   313,   312,   315,   314,   316,   316,   317,   317,   317,
     317,   317,   317,   318,   319,   320,   321,   322,   323,   325,
     324,   326,   326,   327,   327,   329,   328,   331,   330,   332,
     332,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   335,   334,
     337,   336,   339,   338,   341,   340,   343,   342,   345,   344,
     347,   346,   349,   348,   350,   350,   350,   350,   351,   353,
     352,   354,   354,   355,   355,   357,   356,   358,   358,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   361,   360,   363,   362,   364,   364,   365,   365,   367,
     366,   369,   368,   370,   370,   371,   371,   372,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   373,   374,   375,
     377,   376,   379,   378,   381,   380,   382,   384,   383,   385,
     387,   386,   388,   388,   389,   389,   391,   390,   393,   392,
     394,   394,   395,   395,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   397,   399,   398,   400,   401,   402,   403,
     405,   404,   406,   406,   407,   407,   409,   408,   411,   410,
     412,   412,   413,   413,   413,   413,   413,   413,   413,   415,
     414,   417,   416,   419,   418,   421,   420,   422,   422,   423,
     423,   425,   424,   427,   426,   428,   428,   429,   429,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   432,   431,   434,   433,   436,   435,
     438,   437,   440,   439,   442,   441,   444,   443,   446,   445,
     448,   447,   450,   449,   452,   451,   454,   453,   456,   455,
     457,   457,   459,   458,   460,   460,   462,   461,   463,   463,
     464,   464,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   466,   468,   467,   469,   470,   472,   471,
     473,   473,   474,   474,   474,   474,   474,   476,   475,   478,
     477,   480,   479,   482,   481,   484,   483,   485,   485,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   487,   489,   488,
     491,   490,   492,   494,   493,   495,   496,   498,   497,   499,
     499,   501,   500,   502,   503,   505,   504,   506,   506,   506,
     506,   506,   508,   507,   510,   509,   512,   511,   514,   513,
     516,   515,   518,   517,   520,   519,   522,   521,   523,   523,
     524,   524,   526,   525,   527,   529,   528,   531,   530,   532,
     532,   533,   535,   534,   536,   536,   538,   537,   539,   539,
     540,   540,   540,   540,   540,   540,   540,   541,   543,   542,
     545,   544,   546,   546,   548,   547,   549,   549,   550,   550,
     550,   550,   552,   551,   553,   554,   555
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     4,     1,     1,     3,     0,     6,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
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
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     3,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"config-fetch-wait-time\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"authoritative\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"consistency\"", "\"serial-consistency\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"id\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"global\"",
  "\"all\"", "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "interfaces_config", "$@22",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@23", "interfaces_list", "$@24", "dhcp_socket_type", "$@25",
  "socket_type", "outbound_interface", "$@26", "outbound_interface_value",
  "re_detect", "lease_database", "$@27", "sanity_checks", "$@28",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@29",
  "hosts_database", "$@30", "hosts_databases", "$@31", "database_list",
  "not_empty_database_list", "database", "$@32", "database_map_params",
  "database_map_param", "database_type", "$@33", "db_type", "user", "$@34",
  "password", "$@35", "host", "$@36", "port", "name", "$@37", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@38", "keyspace",
  "$@39", "consistency", "$@40", "serial_consistency", "$@41",
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@42",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@43", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@44",
  "sub_hooks_library", "$@45", "hooks_params", "hooks_param", "library",
  "$@46", "parameters", "$@47", "expired_leases_processing", "$@48",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@49",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@50",
  "sub_subnet4", "$@51", "subnet4_params", "subnet4_param", "subnet",
  "$@52", "subnet_4o6_interface", "$@53", "subnet_4o6_interface_id",
  "$@54", "subnet_4o6_subnet", "$@55", "interface", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "shared_networks", "$@60", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@61",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@62", "sub_option_def_list", "$@63", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@64",
  "sub_option_def", "$@65", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool4", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "reservations", "$@80", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@81", "sub_reservation",
  "$@82", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@83", "server_hostname", "$@84",
  "boot_file_name", "$@85", "ip_address", "$@86", "ip_addresses", "$@87",
  "duid", "$@88", "hw_address", "$@89", "client_id_value", "$@90",
  "circuit_id_value", "$@91", "flex_id_value", "$@92", "hostname", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "client_classes", "$@96", "client_classes_list", "client_class_entry",
  "$@97", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@98",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@99",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@100", "control_socket_name", "$@101", "dhcp_queue_control", "$@102",
  "dhcp_ddns", "$@103", "sub_dhcp_ddns", "$@104", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@105",
  "server_ip", "$@106", "server_port", "sender_ip", "$@107", "sender_port",
  "max_queue_size", "ncr_protocol", "$@108", "ncr_protocol_value",
  "ncr_format", "$@109", "override_no_update", "override_client_update",
  "replace_client_name", "$@110", "replace_client_name_value",
  "generated_prefix", "$@111", "hostname_char_set", "$@112",
  "hostname_char_replacement", "$@113", "dhcp6_json_object", "$@114",
  "dhcpddns_json_object", "$@115", "control_agent_json_object", "$@116",
  "config_control", "$@117", "sub_config_control", "$@118",
  "config_control_params", "config_control_param", "config_databases",
  "$@119", "config_fetch_wait_time", "logging_object", "$@120",
  "sub_logging", "$@121", "logging_params", "logging_param", "loggers",
  "$@122", "loggers_entries", "logger_entry", "$@123", "logger_params",
  "logger_param", "debuglevel", "severity", "$@124", "output_options_list",
  "$@125", "output_options_list_content", "output_entry", "$@126",
  "output_params_list", "output_params", "output", "$@127", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   262,   262,   262,   263,   263,   264,   264,   265,   265,
     266,   266,   267,   267,   268,   268,   269,   269,   270,   270,
     271,   271,   272,   272,   273,   273,   274,   274,   275,   275,
     283,   284,   285,   286,   287,   288,   289,   292,   297,   297,
     308,   311,   312,   315,   319,   326,   326,   333,   334,   337,
     341,   348,   348,   355,   356,   359,   363,   374,   384,   384,
     400,   401,   405,   406,   407,   408,   409,   410,   413,   413,
     428,   428,   437,   438,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   482,   487,   492,   497,   502,   507,   512,   517,   517,
     525,   530,   535,   541,   541,   552,   553,   556,   557,   558,
     559,   560,   561,   562,   565,   565,   574,   574,   584,   584,
     591,   592,   595,   595,   602,   604,   608,   614,   614,   626,
     626,   636,   637,   639,   641,   641,   659,   659,   671,   671,
     681,   682,   685,   686,   689,   689,   699,   700,   703,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   725,   725,
     732,   733,   734,   735,   738,   738,   746,   746,   754,   754,
     762,   767,   767,   775,   780,   785,   790,   795,   800,   805,
     810,   810,   818,   818,   826,   826,   834,   834,   842,   847,
     852,   852,   862,   863,   866,   867,   868,   869,   870,   873,
     878,   883,   888,   893,   898,   898,   908,   909,   912,   913,
     916,   916,   926,   926,   936,   937,   938,   941,   942,   945,
     945,   953,   953,   961,   961,   972,   973,   976,   977,   978,
     979,   980,   981,   984,   989,   994,   999,  1004,  1009,  1017,
    1017,  1030,  1031,  1034,  1035,  1042,  1042,  1068,  1068,  1079,
    1080,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,  1113,  1113,
    1121,  1121,  1129,  1129,  1137,  1137,  1145,  1145,  1153,  1153,
    1161,  1161,  1171,  1171,  1178,  1179,  1180,  1181,  1184,  1191,
    1191,  1202,  1203,  1207,  1208,  1211,  1211,  1219,  1220,  1223,
    1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,  1233,
    1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,
    1244,  1251,  1251,  1264,  1264,  1273,  1274,  1277,  1278,  1283,
    1283,  1298,  1298,  1312,  1313,  1316,  1317,  1320,  1321,  1322,
    1323,  1324,  1325,  1326,  1327,  1328,  1329,  1332,  1334,  1339,
    1341,  1341,  1349,  1349,  1357,  1357,  1365,  1367,  1367,  1375,
    1384,  1384,  1396,  1397,  1402,  1403,  1408,  1408,  1420,  1420,
    1432,  1433,  1438,  1439,  1444,  1445,  1446,  1447,  1448,  1449,
    1450,  1451,  1452,  1455,  1457,  1457,  1465,  1467,  1469,  1474,
    1482,  1482,  1494,  1495,  1498,  1499,  1502,  1502,  1512,  1512,
    1522,  1523,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1535,
    1535,  1543,  1543,  1568,  1568,  1598,  1598,  1608,  1609,  1612,
    1613,  1616,  1616,  1625,  1625,  1634,  1635,  1638,  1639,  1643,
    1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,  1653,
    1654,  1655,  1656,  1657,  1660,  1660,  1668,  1668,  1676,  1676,
    1684,  1684,  1692,  1692,  1702,  1702,  1710,  1710,  1718,  1718,
    1726,  1726,  1734,  1734,  1742,  1742,  1750,  1750,  1763,  1763,
    1773,  1774,  1780,  1780,  1790,  1791,  1794,  1794,  1804,  1805,
    1808,  1809,  1812,  1813,  1814,  1815,  1816,  1817,  1818,  1819,
    1820,  1821,  1822,  1825,  1827,  1827,  1835,  1844,  1851,  1851,
    1861,  1862,  1865,  1866,  1867,  1868,  1869,  1872,  1872,  1880,
    1880,  1891,  1891,  1929,  1929,  1941,  1941,  1951,  1952,  1955,
    1956,  1957,  1958,  1959,  1960,  1961,  1962,  1963,  1964,  1965,
    1966,  1967,  1968,  1969,  1970,  1971,  1972,  1975,  1980,  1980,
    1988,  1988,  1996,  2001,  2001,  2009,  2014,  2019,  2019,  2027,
    2028,  2031,  2031,  2039,  2044,  2049,  2049,  2057,  2060,  2063,
    2066,  2069,  2075,  2075,  2083,  2083,  2091,  2091,  2102,  2102,
    2109,  2109,  2116,  2116,  2123,  2123,  2134,  2134,  2144,  2145,
    2149,  2150,  2153,  2153,  2163,  2173,  2173,  2183,  2183,  2194,
    2195,  2199,  2203,  2203,  2215,  2216,  2220,  2220,  2228,  2229,
    2232,  2233,  2234,  2235,  2236,  2237,  2238,  2241,  2246,  2246,
    2254,  2254,  2264,  2265,  2268,  2268,  2276,  2277,  2280,  2281,
    2282,  2283,  2286,  2286,  2294,  2299,  2304
  };

  // Print the state stack on the debug stream.
  void
  Dhcp4Parser::yystack_print_ ()
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1242
} } // isc::dhcp
#line 5064 "dhcp4_parser.cc" // lalr1.cc:1242
#line 2309 "dhcp4_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
