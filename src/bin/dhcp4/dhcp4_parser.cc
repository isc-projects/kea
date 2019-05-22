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

  case 112:
#line 483 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 488 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 493 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 498 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 503 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1107 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 508 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 513 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 518 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 520 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 526 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 122:
#line 531 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 123:
#line 536 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 124:
#line 542 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 125:
#line 547 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 566 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1201 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 570 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1210 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 575 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 580 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 585 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 587 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 592 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 593 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 596 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 598 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 145:
#line 603 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 605 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1292 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 609 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 615 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 620 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 627 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 151:
#line 632 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 155:
#line 642 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 156:
#line 644 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 157:
#line 660 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 158:
#line 665 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 159:
#line 672 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 160:
#line 677 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 690 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 694 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 726 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 728 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 733 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1456 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 734 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1462 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 735 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1468 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 736 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1474 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 739 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 741 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1492 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 747 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 749 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1510 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 755 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 757 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 201:
#line 763 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 202:
#line 768 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 770 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 776 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1564 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 781 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 786 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 207:
#line 791 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 208:
#line 796 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 209:
#line 801 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 210:
#line 806 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 811 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 813 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 819 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 821 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 827 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 216:
#line 829 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 217:
#line 835 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 837 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 219:
#line 843 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 220:
#line 848 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 853 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 222:
#line 858 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 874 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 879 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 884 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 889 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 894 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 899 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 236:
#line 904 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 917 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 921 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 927 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 931 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 946 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 948 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 954 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1859 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 956 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 962 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 255:
#line 967 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 264:
#line 985 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 990 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 995 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1916 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1925 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 269:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 270:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 271:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 276:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 277:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 278:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 279:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 312:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 313:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1146 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 318:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 319:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 320:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 321:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2138 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 322:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 323:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 324:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 325:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 326:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2176 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 327:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2182 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 328:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2188 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 329:
#line 1185 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 330:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 331:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 336:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 337:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2235 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 362:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 363:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2255 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 364:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2264 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 365:
#line 1268 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 371:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 373:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2316 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 389:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 391:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 392:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 393:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 395:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 396:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 398:
#line 1368 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 399:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 401:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 402:
#line 1390 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 407:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 408:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 409:
#line 1421 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 410:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 426:
#line 1460 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 432:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 440:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 451:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 453:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 454:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 456:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 457:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 463:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2689 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 464:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 465:
#line 1630 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 485:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1711 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1719 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2854 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 502:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1737 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1743 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 507:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2919 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 508:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 509:
#line 1764 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 510:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 513:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 514:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 518:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 535:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 536:
#line 1830 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 537:
#line 1836 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 538:
#line 1845 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1852 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3035 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 548:
#line 1873 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 549:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 550:
#line 1881 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1883 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 554:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1935 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1942 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 557:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 578:
#line 1976 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 579:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 1983 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 581:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 582:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 2002 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 585:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 586:
#line 2010 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 587:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 588:
#line 2020 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2022 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3281 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2029 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3287 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3295 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2034 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3305 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2050 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3340 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2058 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3348 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2064 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3364 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2067 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3372 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2070 "dhcp4_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3381 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3389 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2078 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3399 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2084 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3407 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2092 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2094 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3435 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2103 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3443 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2105 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2110 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2112 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3469 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2117 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2119 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3486 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2124 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3497 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2129 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2135 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3517 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2139 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3526 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2154 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2159 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2164 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3555 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3566 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2179 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3575 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2184 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3585 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2188 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3593 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 633:
#line 2204 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3604 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2209 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3613 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2221 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3623 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 638:
#line 2225 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3631 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2242 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3640 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 649:
#line 2247 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3648 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 650:
#line 2249 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3658 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 651:
#line 2255 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3669 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 652:
#line 2260 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3678 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 655:
#line 2269 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3688 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 656:
#line 2273 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3696 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 663:
#line 2287 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3704 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2289 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3714 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2295 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3723 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 666:
#line 2300 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3732 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 667:
#line 2305 "dhcp4_parser.yy" // lalr1.cc:919
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


  const short Dhcp4Parser::yypact_ninf_ = -837;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     454,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    44,    38,    41,    49,    59,
      73,    90,    96,   113,   124,   134,   151,   167,   200,   209,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,    38,  -108,
       6,   107,    60,   207,   214,     9,     2,   395,    74,   -48,
     459,   -41,    76,  -837,   179,   188,   228,   216,   237,  -837,
    -837,  -837,  -837,  -837,   243,  -837,    43,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   257,   258,   284,  -837,
    -837,  -837,  -837,  -837,  -837,   296,   302,   303,   309,   312,
     313,   342,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   344,  -837,  -837,  -837,  -837,
    -837,    56,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   345,  -837,    78,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   346,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,    98,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   111,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   277,   307,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   291,  -837,
    -837,   356,  -837,  -837,  -837,   360,  -837,  -837,   332,   365,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   366,   367,  -837,  -837,  -837,  -837,   368,
     371,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   114,  -837,  -837,  -837,   375,  -837,  -837,
     377,  -837,   380,   383,  -837,  -837,   386,   389,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   184,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   198,  -837,  -837,  -837,   391,   205,  -837,  -837,
    -837,  -837,    38,    38,  -837,   225,   394,   396,   398,   400,
     403,  -837,     6,  -837,   406,   414,   415,   208,   246,   256,
     427,   428,   430,   432,   438,   440,   227,   265,   273,   282,
     293,   297,   283,   453,   460,   465,   470,   471,   472,   475,
     476,   478,   479,   480,   481,   482,   315,   484,   491,   492,
     494,   107,  -837,   495,   496,   497,   330,    60,  -837,   501,
     502,   503,   504,   505,   506,   339,   508,   509,   510,   207,
    -837,   513,   214,  -837,   515,   517,   518,   519,   520,   521,
     527,   529,  -837,     9,  -837,   530,   531,   372,   532,   533,
     535,   369,  -837,   395,   536,   373,   374,  -837,    74,   541,
     542,    63,  -837,   379,   545,   548,   382,   551,   384,   385,
     555,   557,   388,   390,   559,   561,   563,   564,   459,  -837,
     -41,  -837,   565,   399,    76,  -837,  -837,  -837,   566,   567,
     568,    38,    38,    38,  -837,   570,   572,   573,  -837,  -837,
    -837,   401,   402,   410,   589,   590,   593,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   429,   594,   596,   600,   601,   602,
     436,    64,   620,   621,   622,   623,   624,  -837,   625,   602,
     626,   629,  -837,   630,   180,   218,  -837,  -837,   458,   466,
     467,   631,   468,   469,  -837,   630,   473,   634,  -837,   474,
    -837,   630,   477,   483,   485,   486,   487,   488,   489,  -837,
     490,   493,  -837,   498,   499,   500,  -837,  -837,   507,  -837,
    -837,  -837,   511,    38,  -837,  -837,   512,   514,  -837,   516,
    -837,  -837,    13,   524,  -837,  -837,   -15,   522,   523,   525,
    -837,  -837,   637,  -837,  -837,    38,   107,   -41,  -837,  -837,
    -837,    76,    60,   619,  -837,  -837,  -837,   281,   281,   639,
    -837,   640,   642,   643,   644,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   150,   645,   646,   648,   240,   100,  -837,
     459,   656,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   658,  -837,  -837,  -837,  -837,   152,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   639,  -837,   211,   219,   220,   238,  -837,   252,
    -837,  -837,  -837,  -837,  -837,  -837,   662,   663,   664,   668,
     669,  -837,  -837,  -837,  -837,   670,   671,   672,   673,   675,
    -837,   272,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   274,  -837,   674,   678,  -837,  -837,   680,   681,
    -837,  -837,   682,   686,  -837,  -837,   684,   688,  -837,  -837,
     689,   694,  -837,  -837,  -837,  -837,  -837,  -837,    26,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,    71,  -837,  -837,   692,
     696,  -837,  -837,   695,   697,  -837,   698,   699,   700,   701,
     702,   703,   276,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   278,  -837,  -837,  -837,   295,
    -837,   101,  -837,   537,  -837,   704,   706,  -837,  -837,  -837,
    -837,   705,   708,  -837,  -837,  -837,  -837,   707,   619,  -837,
     711,   712,   713,   714,   540,   546,   547,   549,   550,   717,
     720,   721,   722,   556,   558,   560,   562,   553,   281,  -837,
    -837,   281,  -837,   639,   207,  -837,   640,   395,  -837,   642,
      74,  -837,   643,   433,  -837,   644,   150,  -837,   174,   645,
    -837,     9,  -837,   646,   -48,  -837,   648,   569,   571,   574,
     575,   576,   577,   240,  -837,   725,   727,   100,  -837,  -837,
      46,   656,  -837,  -837,   729,   730,   214,  -837,   658,   732,
    -837,  -837,   579,  -837,   378,   580,   581,   582,  -837,  -837,
    -837,  -837,  -837,   583,   584,   585,   586,  -837,  -837,  -837,
    -837,  -837,  -837,   306,  -837,   334,  -837,   731,  -837,   734,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   335,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   733,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   736,   735,
    -837,  -837,  -837,  -837,  -837,   737,  -837,   336,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   587,   588,  -837,  -837,
     756,  -837,  -837,  -837,  -837,  -837,   355,  -837,  -837,  -837,
    -837,  -837,  -837,   591,   358,  -837,   630,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   433,  -837,   757,   592,  -837,   174,
    -837,  -837,  -837,  -837,   759,   595,   760,    46,  -837,  -837,
    -837,  -837,  -837,   597,  -837,  -837,   687,  -837,   598,  -837,
    -837,   758,  -837,  -837,   178,  -837,   -53,   758,  -837,  -837,
     766,   767,   768,   364,  -837,  -837,  -837,  -837,  -837,  -837,
     769,   605,   603,   604,   -53,  -837,   610,  -837,  -837,  -837,
    -837,  -837
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   135,     9,   278,    11,
     439,    13,   464,    15,   364,    17,   372,    19,   409,    21,
     243,    23,   556,    25,   628,    27,   617,    29,    47,    41,
       0,     0,     0,     0,     0,   466,     0,   374,   411,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     626,   609,   611,   613,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   615,   124,   150,     0,     0,     0,   485,
     487,   489,   148,   157,   159,     0,     0,     0,     0,     0,
       0,     0,   119,   270,   362,   401,   330,   452,   454,   323,
     221,   513,   456,   235,   254,     0,   539,   552,   554,   633,
     111,     0,    72,    74,    75,    76,   107,   108,   109,    77,
     105,    94,    95,    96,    80,    81,   102,    82,    83,    84,
      88,    89,    78,   106,    79,    86,    87,   100,   101,   103,
      97,    98,    99,    85,    90,    91,    92,    93,   104,   110,
     137,   139,   143,     0,   134,     0,   126,   128,   129,   130,
     131,   132,   133,   311,   313,   315,   431,   309,   317,     0,
     321,   319,   509,   308,   282,   283,   284,   305,   306,   307,
     295,   296,     0,   280,   287,   300,   301,   302,   288,   290,
     291,   293,   289,   285,   286,   303,   304,   292,   297,   298,
     299,   294,   450,   449,   445,   446,   444,     0,   441,   443,
     447,   448,   507,   495,   497,   501,   499,   505,   503,   491,
     484,   478,   482,   483,     0,   467,   468,   479,   480,   481,
     475,   470,   476,   472,   473,   474,   477,   471,     0,   391,
     202,     0,   395,   393,   398,     0,   387,   388,     0,   375,
     376,   378,   390,   379,   380,   381,   397,   382,   383,   384,
     385,   386,   425,     0,     0,   423,   424,   427,   428,     0,
     412,   413,   415,   416,   417,   418,   419,   420,   421,   422,
     250,   252,   247,     0,   245,   248,   249,     0,   579,   581,
       0,   584,     0,     0,   588,   592,     0,     0,   596,   603,
     605,   607,   577,   575,   576,     0,   558,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   574,     0,   630,   632,   623,     0,     0,   619,   621,
     622,    46,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    57,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,     0,     0,   440,     0,     0,     0,     0,     0,     0,
       0,     0,   465,     0,   365,     0,     0,     0,     0,     0,
       0,     0,   373,     0,     0,     0,     0,   410,     0,     0,
       0,     0,   244,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   557,
       0,   629,     0,     0,     0,   618,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   121,   122,
     123,     0,     0,     0,     0,     0,     0,   112,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   538,     0,     0,
       0,     0,    73,     0,     0,     0,   147,   127,     0,     0,
       0,     0,     0,     0,   329,     0,     0,     0,   281,     0,
     442,     0,     0,     0,     0,     0,     0,     0,     0,   469,
       0,     0,   389,     0,     0,     0,   400,   377,     0,   429,
     430,   414,     0,     0,   246,   578,     0,     0,   583,     0,
     586,   587,     0,     0,   594,   595,     0,     0,     0,     0,
     559,   631,     0,   625,   620,     0,     0,     0,   610,   612,
     614,     0,     0,     0,   486,   488,   490,     0,     0,   161,
     120,   272,   366,   403,   332,    40,   453,   455,   325,   326,
     327,   328,   324,     0,     0,   458,   237,     0,     0,   553,
       0,     0,    51,   138,   141,   142,   140,   145,   146,   144,
     312,   314,   316,   433,   310,   318,   322,   320,     0,   451,
     508,   496,   498,   502,   500,   506,   504,   492,   392,   203,
     396,   394,   399,   426,   251,   253,   580,   582,   585,   590,
     591,   589,   593,   598,   599,   600,   601,   602,   597,   604,
     606,   608,   161,    44,     0,     0,     0,     0,   155,     0,
     152,   154,   189,   195,   197,   199,     0,     0,     0,     0,
       0,   211,   213,   215,   217,     0,     0,     0,     0,     0,
     188,     0,   167,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   182,   183,   184,   179,   185,   186,   187,
     180,   181,     0,   165,     0,   162,   163,   276,     0,   273,
     274,   370,     0,   367,   368,   407,     0,   404,   405,   336,
       0,   333,   334,   230,   231,   232,   233,   234,     0,   223,
     225,   226,   227,   228,   229,   517,     0,   515,   462,     0,
     459,   460,   241,     0,   238,   239,     0,     0,     0,     0,
       0,     0,     0,   256,   258,   259,   260,   261,   262,   263,
     548,   550,   547,   545,   546,     0,   541,   543,   544,     0,
     637,     0,   635,    53,   437,     0,   434,   435,   493,   511,
     512,     0,     0,    69,   627,   616,   125,     0,     0,   151,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   149,
     158,     0,   160,     0,     0,   271,     0,   374,   363,     0,
     411,   402,     0,     0,   331,     0,     0,   222,   519,     0,
     514,   466,   457,     0,     0,   236,     0,     0,     0,     0,
       0,     0,     0,     0,   255,     0,     0,     0,   540,   555,
       0,     0,   634,    55,     0,    54,     0,   432,     0,     0,
     510,   624,     0,   153,     0,     0,     0,     0,   201,   204,
     205,   206,   207,     0,     0,     0,     0,   219,   220,   208,
     209,   210,   168,     0,   164,     0,   275,     0,   369,     0,
     406,   361,   355,   343,   344,   358,   359,   360,   346,   347,
     340,   341,   342,   353,   354,   352,     0,   338,   345,   356,
     357,   348,   349,   350,   351,   335,   224,   535,     0,   533,
     534,   526,   527,   531,   532,   528,   529,   530,     0,   520,
     521,   523,   524,   525,   516,     0,   461,     0,   240,   264,
     265,   266,   267,   268,   269,   257,     0,     0,   542,   651,
       0,   649,   647,   641,   645,   646,     0,   639,   643,   644,
     642,   636,    52,     0,     0,   436,     0,   156,   191,   192,
     193,   194,   190,   196,   198,   200,   212,   214,   216,   218,
     166,   277,   371,   408,     0,   337,     0,     0,   518,     0,
     463,   242,   549,   551,     0,     0,     0,     0,   638,    56,
     438,   494,   339,     0,   537,   522,     0,   648,     0,   640,
     536,     0,   650,   655,     0,   653,     0,     0,   652,   663,
       0,     0,     0,     0,   657,   659,   660,   661,   662,   654,
       0,     0,     0,     0,     0,   656,     0,   665,   666,   667,
     658,   664
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -44,  -837,  -479,  -837,
     253,  -837,  -837,  -837,  -837,  -837,  -837,  -515,  -837,  -837,
    -837,   -70,  -837,  -837,  -837,   413,  -837,  -837,  -837,  -837,
     144,   376,   -54,   -24,    -5,    -4,    -1,    11,  -837,  -837,
    -837,  -837,    14,    17,  -837,  -837,   187,   409,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   -22,  -837,  -837,  -837,  -837,  -837,
    -837,   115,  -837,   -43,  -837,  -593,   -35,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   -36,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   -51,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   -58,
    -837,  -837,  -837,   -62,   351,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   -50,  -837,  -837,  -837,  -837,  -837,  -837,  -836,
    -837,  -837,  -837,   -31,  -837,  -837,  -837,   -25,   408,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -835,  -837,    19,
    -837,    22,  -837,    21,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,   -23,  -837,  -837,  -183,   -65,  -837,  -837,  -837,  -837,
    -837,   -14,  -837,  -837,  -837,     0,  -837,   416,  -837,   -72,
    -837,  -837,  -837,  -837,  -837,   -64,  -837,  -837,  -837,  -837,
    -837,   -40,  -837,  -837,  -837,    24,  -837,  -837,  -837,    12,
    -837,   419,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   -10,  -837,  -837,  -837,   -13,   447,  -837,
    -837,   -52,  -837,   -20,  -837,   -60,  -837,  -837,  -837,    18,
    -837,  -837,  -837,    23,  -837,   437,    -8,  -837,    -2,  -837,
      10,  -837,   234,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -826,  -837,  -837,  -837,  -837,  -837,    27,  -837,  -837,  -837,
    -136,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,     8,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     259,   412,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   286,   404,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   294,   417,   -69,
    -837,  -837,    15,  -837,  -837,  -135,  -837,  -837,  -837,  -837,
    -837,  -837,  -154,  -837,  -837,  -170,  -837,  -837,  -837,  -837,
    -837
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     616,    87,    88,    41,    68,    84,    85,   633,   803,   884,
     885,   710,    43,    70,    96,    97,    98,   366,    45,    71,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     393,   151,   152,   153,   154,   375,   185,   186,    47,    72,
     187,   413,   188,   414,   636,   189,   415,   639,   190,   155,
     383,   156,   376,   689,   690,   691,   817,   157,   384,   158,
     385,   734,   735,   736,   841,   711,   712,   713,   820,  1002,
     714,   821,   715,   822,   716,   823,   717,   718,   446,   719,
     720,   721,   722,   723,   724,   725,   726,   829,   727,   830,
     728,   831,   729,   832,   730,   731,   159,   401,   758,   759,
     760,   761,   762,   763,   764,   160,   404,   773,   774,   775,
     864,    61,    79,   313,   314,   315,   459,   316,   460,   161,
     405,   782,   783,   784,   785,   786,   787,   788,   789,   162,
     394,   738,   739,   740,   844,    49,    73,   212,   213,   214,
     423,   215,   419,   216,   420,   217,   421,   218,   424,   219,
     427,   220,   426,   163,   400,   622,   222,   164,   397,   750,
     751,   752,   853,   936,   937,   165,   395,    55,    76,   742,
     743,   744,   847,    57,    77,   278,   279,   280,   281,   282,
     283,   284,   445,   285,   449,   286,   448,   287,   288,   450,
     289,   166,   396,   746,   747,   748,   850,    59,    78,   299,
     300,   301,   302,   303,   454,   304,   305,   306,   307,   224,
     422,   805,   806,   807,   886,    51,    74,   237,   238,   239,
     431,   167,   398,   168,   399,   169,   403,   769,   770,   771,
     861,    53,    75,   254,   255,   256,   170,   380,   171,   381,
     172,   382,   260,   441,   810,   889,   261,   435,   262,   436,
     263,   438,   264,   437,   265,   440,   266,   439,   267,   434,
     231,   428,   811,   173,   402,   766,   767,   858,   958,   959,
     960,   961,   962,  1016,   963,   174,   175,   407,   795,   796,
     797,   875,   798,   876,   176,   408,   177,   409,    63,    80,
     335,   336,   337,   338,   464,   339,   465,   340,   341,   467,
     342,   343,   344,   470,   671,   345,   471,   346,   347,   348,
     474,   678,   349,   475,   350,   476,   351,   477,    99,   368,
     100,   369,   101,   370,   178,   374,    67,    82,   357,   358,
     359,   482,   360,   102,   367,    65,    81,   352,   353,   179,
     410,   801,   802,   880,   986,   987,   988,   989,  1026,   990,
    1024,  1044,  1045,  1046,  1053,  1054,  1055,  1060,  1056,  1057,
    1058
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   140,   184,   203,   233,   250,   297,   276,   295,   312,
     332,   268,   354,   227,   298,   732,    89,   931,   932,   204,
     191,   225,   240,   252,    83,   290,   308,   944,   333,   856,
     646,   669,   857,   223,   236,   251,   650,   109,   110,   111,
     615,   277,   296,    31,    30,    32,   372,    33,    42,   205,
     615,   373,   192,   226,   241,   253,    44,   291,   309,   411,
     334,   310,   311,    86,   412,   228,    46,   257,   206,   207,
     124,   229,   208,   258,   859,   180,   181,   860,   125,   182,
      48,   417,   183,   230,   209,   259,   418,   210,   355,   356,
     211,   127,   128,   234,   221,  1049,   235,    50,  1050,  1051,
    1052,   429,   242,    52,   881,   139,   430,   882,   243,   244,
     245,   246,   247,   248,   432,   249,   270,   461,   103,   433,
      54,   104,   462,    94,   673,   674,   675,   676,   127,   128,
     105,    56,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    58,   127,   128,   270,   292,   271,   272,   293,   294,
     670,    90,   618,   619,   620,   621,   127,   128,    60,   677,
      91,    92,    93,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   310,   311,    62,   124,   125,    94,   931,   932,
      94,  1047,   127,   128,  1048,   361,   126,   478,   944,   127,
     128,   362,   479,   979,   129,   980,   981,   634,   635,   130,
     131,   480,   109,   110,   111,   132,   481,    64,   484,    34,
      35,    36,    37,   485,   411,   133,    66,    94,   134,   813,
     790,   791,   480,   484,   364,   135,   136,   814,   815,   137,
     138,    94,   363,   107,   108,   109,   110,   111,   637,   638,
     365,   417,   124,   125,   270,    94,   816,   371,   913,   753,
     754,   755,   756,   139,   757,   818,   127,   128,   249,   808,
     819,   377,   378,   115,   116,   117,   118,   119,   120,   947,
     948,    94,   193,   194,   195,   838,   125,   838,    94,   873,
     839,   877,   840,   125,   874,   442,   878,   196,   379,   127,
     128,   197,   198,   199,   129,   232,   127,   128,   478,   444,
     386,   200,    95,   879,   201,   132,   387,   388,   200,   838,
     443,   201,   202,   389,  1010,   692,   390,   391,   486,   487,
     693,   694,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   705,   706,   707,   708,   709,   429,  1014,   461,
     452,   140,  1011,  1015,  1021,    94,   392,   184,   406,   416,
     425,   270,   776,   777,   778,   779,   780,   781,  1027,   203,
     447,   432,   233,  1028,   451,   191,  1030,  1064,   453,   227,
     455,   456,  1065,   250,   458,   204,   457,   225,    94,   463,
     240,   466,   498,   276,   468,    94,   297,   469,   295,   223,
     472,   252,   236,   473,   298,   483,   488,   192,   489,   507,
     490,   290,   491,   251,   492,   205,   308,   493,   332,   226,
     495,   354,   241,   998,   999,  1000,  1001,   277,   496,   497,
     499,   228,   296,   253,   206,   207,   333,   229,   208,   269,
     500,   501,   502,   291,   503,   257,   504,   508,   309,   230,
     209,   258,   505,   210,   506,   509,   211,   598,   599,   600,
     221,   234,    94,   259,   235,   513,   510,   514,   334,   107,
     108,   109,   110,   111,   515,   270,   511,   271,   272,   516,
     512,   273,   274,   275,   517,   518,   519,   127,   128,   520,
     521,  1031,   522,   523,   524,   525,   526,   527,   528,   115,
     116,   117,   118,   119,   120,   529,   530,   123,   531,   533,
     534,   535,   125,   270,   536,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   127,   128,   549,   198,   551,
     129,   552,   553,   554,   555,   556,   140,   200,   354,   665,
     201,   557,   184,   558,   560,   561,   563,   564,   202,   565,
     568,   127,   128,   566,   562,   572,   573,   569,   570,   576,
     191,   683,   577,   575,   578,   579,   580,   581,   792,   582,
     332,   583,   584,   586,   585,   587,    94,   588,   589,   592,
     595,   593,   604,   605,   596,   597,   793,   601,   333,   602,
     603,   606,   192,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   607,   608,   609,   611,
     610,   612,   330,   331,    94,   613,   614,   617,   794,    32,
     334,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   623,   624,   625,   626,   640,
      94,   627,   628,   630,   631,   632,   643,   641,   642,   644,
     645,   648,   682,   688,   647,   649,   733,   737,   651,   741,
     745,   749,   765,   768,   652,   772,   653,   654,   655,   656,
     657,   658,   672,   800,   659,   804,   824,   825,   826,   660,
     661,   662,   827,   828,   833,   834,   835,   836,   663,   837,
     842,   843,   664,   666,   846,   667,   845,   668,   848,   849,
     851,   852,  1041,   679,   680,   854,   681,   855,   862,   863,
     866,   865,   867,   868,   869,   870,   871,   872,   883,   888,
     887,   892,   898,   890,   891,   894,   895,   896,   897,   900,
     899,   903,   902,   901,   904,   905,   906,   911,   907,   976,
     908,   977,   909,   993,   910,   992,   996,  1017,  1019,  1012,
     684,   969,  1013,   970,  1018,  1020,   971,   972,   973,   974,
     997,  1003,  1004,  1005,  1006,  1007,  1008,  1009,  1022,  1023,
    1025,  1033,  1029,  1036,  1038,  1043,  1034,  1037,  1040,  1042,
    1061,  1062,  1063,  1066,   203,  1068,  1069,   276,   297,  1067,
     295,  1071,   629,   921,   227,   494,   298,   532,   949,   687,
     204,   250,   225,   951,   312,   290,   893,   812,   308,   922,
     914,   939,   967,   912,   223,   946,   953,   792,   968,   252,
     982,   277,   574,   938,   296,   916,   233,   930,   952,   915,
     205,   251,   950,   975,   226,   793,   537,   291,   984,   923,
     309,  1032,   945,   940,   240,   918,   228,   548,   954,   206,
     207,   253,   229,   208,   983,   941,   236,   917,   924,   925,
     955,   942,   926,   257,   230,   209,   956,   794,   210,   258,
     985,   211,   919,   943,   927,   221,   241,   928,   957,   567,
     929,   259,   933,   994,   935,   934,   920,   571,   995,   550,
     559,   966,   809,  1035,   965,   978,   964,   686,   594,   799,
     590,   685,  1039,  1059,  1070,     0,   991,   591,     0,     0,
       0,     0,     0,     0,     0,   234,     0,     0,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   921,     0,     0,     0,     0,   949,
       0,     0,     0,     0,   951,     0,     0,   982,     0,     0,
     922,     0,   939,     0,     0,     0,     0,   953,     0,     0,
       0,     0,     0,     0,   938,   984,     0,     0,   930,   952,
       0,     0,     0,   950,     0,     0,     0,     0,     0,     0,
     923,   983,     0,     0,   940,     0,     0,     0,     0,   954,
       0,     0,     0,     0,     0,     0,   941,   985,     0,   924,
     925,   955,   942,   926,     0,     0,     0,   956,     0,     0,
       0,     0,     0,     0,   943,   927,     0,     0,   928,   957,
       0,   929,     0,   933,     0,   935,   934
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    81,    73,    78,   608,    10,   853,   853,    73,
      72,    73,    74,    75,    68,    77,    78,   853,    80,     3,
     545,    18,     6,    73,    74,    75,   551,    28,    29,    30,
     519,    77,    78,     5,     0,     7,     3,     9,     7,    73,
     529,     8,    72,    73,    74,    75,     7,    77,    78,     3,
      80,   109,   110,   171,     8,    73,     7,    75,    73,    73,
      68,    73,    73,    75,     3,    15,    16,     6,    69,    19,
       7,     3,    22,    73,    73,    75,     8,    73,    12,    13,
      73,    82,    83,    74,    73,   148,    74,     7,   151,   152,
     153,     3,    93,     7,     3,   146,     8,     6,    99,   100,
     101,   102,   103,   104,     3,   106,    70,     3,    11,     8,
       7,    14,     8,   171,   139,   140,   141,   142,    82,    83,
      23,     7,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     7,    82,    83,    70,    71,    72,    73,    74,    75,
     137,   145,    88,    89,    90,    91,    82,    83,     7,   174,
     154,   155,   156,    56,    57,    58,    59,    60,    61,    62,
      63,    64,   109,   110,     7,    68,    69,   171,  1014,  1014,
     171,     3,    82,    83,     6,     6,    79,     3,  1014,    82,
      83,     3,     8,   147,    87,   149,   150,    17,    18,    92,
      93,     3,    28,    29,    30,    98,     8,     7,     3,   171,
     172,   173,   174,     8,     3,   108,     7,   171,   111,     8,
     120,   121,     3,     3,     8,   118,   119,     8,     8,   122,
     123,   171,     4,    26,    27,    28,    29,    30,    20,    21,
       3,     3,    68,    69,    70,   171,     8,     4,   841,    99,
     100,   101,   102,   146,   104,     3,    82,    83,   106,   107,
       8,     4,     4,    56,    57,    58,    59,    60,    61,    95,
      96,   171,    65,    66,    67,     3,    69,     3,   171,     3,
       8,     3,     8,    69,     8,     8,     8,    80,     4,    82,
      83,    84,    85,    86,    87,    81,    82,    83,     3,     8,
       4,    94,   372,     8,    97,    98,     4,     4,    94,     3,
       3,    97,   105,     4,     8,    34,     4,     4,   362,   363,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,     3,     3,     3,
       8,   411,     8,     8,     8,   171,     4,   417,     4,     4,
       4,    70,   112,   113,   114,   115,   116,   117,     3,   429,
       4,     3,   432,     8,     4,   417,     8,     3,     3,   429,
       4,     4,     8,   443,     3,   429,     8,   429,   171,     4,
     432,     4,   174,   453,     4,   171,   458,     4,   458,   429,
       4,   443,   432,     4,   458,     4,   171,   417,     4,   172,
       4,   453,     4,   443,     4,   429,   458,     4,   478,   429,
       4,   480,   432,    35,    36,    37,    38,   453,     4,     4,
     174,   429,   458,   443,   429,   429,   478,   429,   429,    34,
     174,     4,     4,   453,     4,   443,     4,   172,   458,   429,
     429,   443,     4,   429,     4,   172,   429,   491,   492,   493,
     429,   432,   171,   443,   432,   172,   174,     4,   478,    26,
      27,    28,    29,    30,     4,    70,   173,    72,    73,     4,
     173,    76,    77,    78,     4,     4,     4,    82,    83,     4,
       4,   996,     4,     4,     4,     4,     4,   172,     4,    56,
      57,    58,    59,    60,    61,     4,     4,    64,     4,     4,
       4,     4,    69,    70,   174,     4,     4,     4,     4,     4,
       4,   172,     4,     4,     4,    82,    83,     4,    85,     4,
      87,     4,     4,     4,     4,     4,   596,    94,   597,   573,
      97,     4,   602,     4,     4,     4,     4,     4,   105,     4,
       4,    82,    83,   174,   172,     4,     4,   174,   174,     4,
     602,   595,     4,   174,   172,     4,   172,   172,   628,     4,
     630,     4,   174,     4,   174,     4,   171,     4,     4,     4,
       4,   172,   171,   171,     7,     7,   628,     7,   630,     7,
       7,   171,   602,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,     7,     7,     5,     5,
     171,     5,   143,   144,   171,     5,     5,   171,   628,     7,
     630,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,     5,     5,     5,     5,   171,
     171,     7,     7,     7,     5,     5,     5,   171,   171,   171,
     171,     7,     5,    24,   171,   171,     7,     7,   171,     7,
       7,     7,     7,     7,   171,     7,   171,   171,   171,   171,
     171,   171,   138,     7,   171,     7,     4,     4,     4,   171,
     171,   171,     4,     4,     4,     4,     4,     4,   171,     4,
       6,     3,   171,   171,     3,   171,     6,   171,     6,     3,
       6,     3,     5,   171,   171,     6,   171,     3,     6,     3,
       3,     6,     4,     4,     4,     4,     4,     4,   171,     3,
       6,     4,   172,     8,     6,     4,     4,     4,     4,   172,
     174,     4,   172,   174,     4,     4,     4,   174,   172,     4,
     172,     4,   172,     3,   172,     6,     4,     4,     3,     8,
     596,   172,     8,   172,     8,     8,   172,   172,   172,   172,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
       4,     4,   171,     4,     4,     7,   174,   172,   171,   171,
       4,     4,     4,     4,   844,   172,   172,   847,   850,   174,
     850,   171,   529,   853,   844,   372,   850,   411,   858,   602,
     844,   861,   844,   858,   864,   847,   818,   682,   850,   853,
     843,   853,   864,   838,   844,   856,   858,   877,   866,   861,
     880,   847,   461,   853,   850,   846,   886,   853,   858,   844,
     844,   861,   858,   873,   844,   877,   417,   847,   880,   853,
     850,  1014,   855,   853,   886,   849,   844,   429,   858,   844,
     844,   861,   844,   844,   880,   853,   886,   847,   853,   853,
     858,   853,   853,   861,   844,   844,   858,   877,   844,   861,
     880,   844,   850,   853,   853,   844,   886,   853,   858,   453,
     853,   861,   853,   886,   853,   853,   852,   458,   888,   432,
     443,   863,   648,  1019,   861,   877,   859,   601,   484,   630,
     478,   597,  1027,  1047,  1064,    -1,   881,   480,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   886,    -1,    -1,   886,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1014,    -1,    -1,    -1,    -1,  1019,
      -1,    -1,    -1,    -1,  1019,    -1,    -1,  1027,    -1,    -1,
    1014,    -1,  1014,    -1,    -1,    -1,    -1,  1019,    -1,    -1,
      -1,    -1,    -1,    -1,  1014,  1027,    -1,    -1,  1014,  1019,
      -1,    -1,    -1,  1019,    -1,    -1,    -1,    -1,    -1,    -1,
    1014,  1027,    -1,    -1,  1014,    -1,    -1,    -1,    -1,  1019,
      -1,    -1,    -1,    -1,    -1,    -1,  1014,  1027,    -1,  1014,
    1014,  1019,  1014,  1014,    -1,    -1,    -1,  1019,    -1,    -1,
      -1,    -1,    -1,    -1,  1014,  1014,    -1,    -1,  1014,  1019,
      -1,  1014,    -1,  1014,    -1,  1014,  1014
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
      92,    93,    98,   108,   111,   118,   119,   122,   123,   146,
     206,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   226,   227,   228,   229,   244,   246,   252,   254,   291,
     300,   314,   324,   348,   352,   360,   386,   416,   418,   420,
     431,   433,   435,   458,   470,   471,   479,   481,   519,   534,
      15,    16,    19,    22,   206,   231,   232,   235,   237,   240,
     243,   416,   418,    65,    66,    67,    80,    84,    85,    86,
      94,    97,   105,   206,   217,   218,   219,   220,   221,   222,
     227,   228,   332,   333,   334,   336,   338,   340,   342,   344,
     346,   348,   351,   386,   404,   416,   418,   420,   431,   433,
     435,   455,    81,   206,   344,   346,   386,   412,   413,   414,
     416,   418,    93,    99,   100,   101,   102,   103,   104,   106,
     206,   386,   416,   418,   428,   429,   430,   431,   433,   435,
     437,   441,   443,   445,   447,   449,   451,   453,   360,    34,
      70,    72,    73,    76,    77,    78,   206,   272,   370,   371,
     372,   373,   374,   375,   376,   378,   380,   382,   383,   385,
     416,   418,    71,    74,    75,   206,   272,   374,   380,   394,
     395,   396,   397,   398,   400,   401,   402,   403,   416,   418,
     109,   110,   206,   308,   309,   310,   312,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     143,   144,   206,   416,   418,   485,   486,   487,   488,   490,
     492,   493,   495,   496,   497,   500,   502,   503,   504,   507,
     509,   511,   532,   533,   534,    12,    13,   523,   524,   525,
     527,     6,     3,     4,     8,     3,   212,   529,   514,   516,
     518,     4,     3,     8,   520,   230,   247,     4,     4,     4,
     432,   434,   436,   245,   253,   255,     4,     4,     4,     4,
       4,     4,     4,   225,   325,   361,   387,   353,   417,   419,
     349,   292,   459,   421,   301,   315,     4,   472,   480,   482,
     535,     3,     8,   236,   238,   241,     4,     3,     8,   337,
     339,   341,   405,   335,   343,     4,   347,   345,   456,     3,
       8,   415,     3,     8,   454,   442,   444,   448,   446,   452,
     450,   438,     8,     3,     8,   377,   273,     4,   381,   379,
     384,     4,     8,     3,   399,     4,     4,     8,     3,   311,
     313,     3,     8,     4,   489,   491,     4,   494,     4,     4,
     498,   501,     4,     4,   505,   508,   510,   512,     3,     8,
       3,     8,   526,     4,     3,     8,   191,   191,   171,     4,
       4,     4,     4,     4,   210,     4,     4,     4,   174,   174,
     174,     4,     4,     4,     4,     4,     4,   172,   172,   172,
     174,   173,   173,   172,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   172,     4,     4,
       4,     4,   216,     4,     4,     4,   174,   232,     4,     4,
       4,     4,     4,     4,   172,     4,     4,     4,   333,     4,
     413,     4,     4,     4,     4,     4,     4,     4,     4,   430,
       4,     4,   172,     4,     4,     4,   174,   372,     4,   174,
     174,   396,     4,     4,   309,   174,     4,     4,   172,     4,
     172,   172,     4,     4,   174,   174,     4,     4,     4,     4,
     486,   533,     4,   172,   524,     4,     7,     7,   191,   191,
     191,     7,     7,     7,   171,   171,   171,     7,     7,     5,
     171,     5,     5,     5,     5,   193,   195,   171,    88,    89,
      90,    91,   350,     5,     5,     5,     5,     7,     7,   195,
       7,     5,     5,   202,    17,    18,   239,    20,    21,   242,
     171,   171,   171,     5,   171,   171,   202,   171,     7,   171,
     202,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   191,   171,   171,   171,    18,
     137,   499,   138,   139,   140,   141,   142,   174,   506,   171,
     171,   171,     5,   191,   215,   532,   523,   231,    24,   248,
     249,   250,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
     206,   260,   261,   262,   265,   267,   269,   271,   272,   274,
     275,   276,   277,   278,   279,   280,   281,   283,   285,   287,
     289,   290,   260,     7,   256,   257,   258,     7,   326,   327,
     328,     7,   364,   365,   366,     7,   388,   389,   390,     7,
     354,   355,   356,    99,   100,   101,   102,   104,   293,   294,
     295,   296,   297,   298,   299,     7,   460,   461,     7,   422,
     423,   424,     7,   302,   303,   304,   112,   113,   114,   115,
     116,   117,   316,   317,   318,   319,   320,   321,   322,   323,
     120,   121,   206,   416,   418,   473,   474,   475,   477,   485,
       7,   536,   537,   203,     7,   406,   407,   408,   107,   437,
     439,   457,   256,     8,     8,     8,     8,   251,     3,     8,
     263,   266,   268,   270,     4,     4,     4,     4,     4,   282,
     284,   286,   288,     4,     4,     4,     4,     4,     3,     8,
       8,   259,     6,     3,   329,     6,     3,   367,     6,     3,
     391,     6,     3,   357,     6,     3,     3,     6,   462,     3,
       6,   425,     6,     3,   305,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   476,   478,     3,     8,     8,
     538,     3,     6,   171,   204,   205,   409,     6,     3,   440,
       8,     6,     4,   249,     4,     4,     4,     4,   172,   174,
     172,   174,   172,     4,     4,     4,     4,   172,   172,   172,
     172,   174,   261,   260,   258,   332,   328,   370,   366,   394,
     390,   206,   217,   218,   219,   220,   221,   222,   227,   228,
     272,   324,   342,   344,   346,   348,   358,   359,   386,   416,
     418,   431,   433,   435,   455,   356,   294,    95,    96,   206,
     272,   360,   386,   416,   418,   431,   433,   435,   463,   464,
     465,   466,   467,   469,   461,   428,   424,   308,   304,   172,
     172,   172,   172,   172,   172,   317,     4,     4,   474,   147,
     149,   150,   206,   272,   416,   418,   539,   540,   541,   542,
     544,   537,     6,     3,   412,   408,     4,   171,    35,    36,
      37,    38,   264,   171,   171,   171,   171,   171,   171,   171,
       8,     8,     8,     8,     3,     8,   468,     4,     8,     3,
       8,     8,   171,   171,   545,     4,   543,     3,     8,   171,
       8,   202,   359,     4,   174,   465,     4,   172,     4,   540,
     171,     5,   171,     7,   546,   547,   548,     3,     6,   148,
     151,   152,   153,   549,   550,   551,   553,   554,   555,   547,
     552,     4,     4,     4,     3,     8,     4,   174,   172,   172,
     550,   171
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
     216,   216,   217,   218,   219,   220,   221,   222,   223,   225,
     224,   226,   227,   228,   230,   229,   231,   231,   232,   232,
     232,   232,   232,   232,   232,   234,   233,   236,   235,   238,
     237,   239,   239,   241,   240,   242,   242,   243,   245,   244,
     247,   246,   248,   248,   249,   251,   250,   253,   252,   255,
     254,   256,   256,   257,   257,   259,   258,   260,   260,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   263,
     262,   264,   264,   264,   264,   266,   265,   268,   267,   270,
     269,   271,   273,   272,   274,   275,   276,   277,   278,   279,
     280,   282,   281,   284,   283,   286,   285,   288,   287,   289,
     290,   292,   291,   293,   293,   294,   294,   294,   294,   294,
     295,   296,   297,   298,   299,   301,   300,   302,   302,   303,
     303,   305,   304,   307,   306,   308,   308,   308,   309,   309,
     311,   310,   313,   312,   315,   314,   316,   316,   317,   317,
     317,   317,   317,   317,   318,   319,   320,   321,   322,   323,
     325,   324,   326,   326,   327,   327,   329,   328,   331,   330,
     332,   332,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   335,
     334,   337,   336,   339,   338,   341,   340,   343,   342,   345,
     344,   347,   346,   349,   348,   350,   350,   350,   350,   351,
     353,   352,   354,   354,   355,   355,   357,   356,   358,   358,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   361,   360,   363,   362,   364,   364,   365,   365,
     367,   366,   369,   368,   370,   370,   371,   371,   372,   372,
     372,   372,   372,   372,   372,   372,   372,   372,   373,   374,
     375,   377,   376,   379,   378,   381,   380,   382,   384,   383,
     385,   387,   386,   388,   388,   389,   389,   391,   390,   393,
     392,   394,   394,   395,   395,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   397,   399,   398,   400,   401,   402,
     403,   405,   404,   406,   406,   407,   407,   409,   408,   411,
     410,   412,   412,   413,   413,   413,   413,   413,   413,   413,
     415,   414,   417,   416,   419,   418,   421,   420,   422,   422,
     423,   423,   425,   424,   427,   426,   428,   428,   429,   429,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   432,   431,   434,   433,   436,
     435,   438,   437,   440,   439,   442,   441,   444,   443,   446,
     445,   448,   447,   450,   449,   452,   451,   454,   453,   456,
     455,   457,   457,   459,   458,   460,   460,   462,   461,   463,
     463,   464,   464,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   466,   468,   467,   469,   470,   472,
     471,   473,   473,   474,   474,   474,   474,   474,   476,   475,
     478,   477,   480,   479,   482,   481,   484,   483,   485,   485,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   487,   489,
     488,   491,   490,   492,   494,   493,   495,   496,   498,   497,
     499,   499,   501,   500,   502,   503,   505,   504,   506,   506,
     506,   506,   506,   508,   507,   510,   509,   512,   511,   514,
     513,   516,   515,   518,   517,   520,   519,   522,   521,   523,
     523,   524,   524,   526,   525,   527,   529,   528,   531,   530,
     532,   532,   533,   535,   534,   536,   536,   538,   537,   539,
     539,   540,   540,   540,   540,   540,   540,   540,   541,   543,
     542,   545,   544,   546,   546,   548,   547,   549,   549,   550,
     550,   550,   550,   552,   551,   553,   554,   555
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
       1,     1,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     0,
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
     479,   480,   483,   488,   493,   498,   503,   508,   513,   518,
     518,   526,   531,   536,   542,   542,   553,   554,   557,   558,
     559,   560,   561,   562,   563,   566,   566,   575,   575,   585,
     585,   592,   593,   596,   596,   603,   605,   609,   615,   615,
     627,   627,   637,   638,   640,   642,   642,   660,   660,   672,
     672,   682,   683,   686,   687,   690,   690,   700,   701,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   723,   726,
     726,   733,   734,   735,   736,   739,   739,   747,   747,   755,
     755,   763,   768,   768,   776,   781,   786,   791,   796,   801,
     806,   811,   811,   819,   819,   827,   827,   835,   835,   843,
     848,   853,   853,   863,   864,   867,   868,   869,   870,   871,
     874,   879,   884,   889,   894,   899,   899,   909,   910,   913,
     914,   917,   917,   927,   927,   937,   938,   939,   942,   943,
     946,   946,   954,   954,   962,   962,   973,   974,   977,   978,
     979,   980,   981,   982,   985,   990,   995,  1000,  1005,  1010,
    1018,  1018,  1031,  1032,  1035,  1036,  1043,  1043,  1069,  1069,
    1080,  1081,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,  1114,
    1114,  1122,  1122,  1130,  1130,  1138,  1138,  1146,  1146,  1154,
    1154,  1162,  1162,  1172,  1172,  1179,  1180,  1181,  1182,  1185,
    1192,  1192,  1203,  1204,  1208,  1209,  1212,  1212,  1220,  1221,
    1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,  1233,
    1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,
    1244,  1245,  1252,  1252,  1265,  1265,  1274,  1275,  1278,  1279,
    1284,  1284,  1299,  1299,  1313,  1314,  1317,  1318,  1321,  1322,
    1323,  1324,  1325,  1326,  1327,  1328,  1329,  1330,  1333,  1335,
    1340,  1342,  1342,  1350,  1350,  1358,  1358,  1366,  1368,  1368,
    1376,  1385,  1385,  1397,  1398,  1403,  1404,  1409,  1409,  1421,
    1421,  1433,  1434,  1439,  1440,  1445,  1446,  1447,  1448,  1449,
    1450,  1451,  1452,  1453,  1456,  1458,  1458,  1466,  1468,  1470,
    1475,  1483,  1483,  1495,  1496,  1499,  1500,  1503,  1503,  1513,
    1513,  1523,  1524,  1527,  1528,  1529,  1530,  1531,  1532,  1533,
    1536,  1536,  1544,  1544,  1569,  1569,  1599,  1599,  1609,  1610,
    1613,  1614,  1617,  1617,  1626,  1626,  1635,  1636,  1639,  1640,
    1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,  1653,
    1654,  1655,  1656,  1657,  1658,  1661,  1661,  1669,  1669,  1677,
    1677,  1685,  1685,  1693,  1693,  1703,  1703,  1711,  1711,  1719,
    1719,  1727,  1727,  1735,  1735,  1743,  1743,  1751,  1751,  1764,
    1764,  1774,  1775,  1781,  1781,  1791,  1792,  1795,  1795,  1805,
    1806,  1809,  1810,  1813,  1814,  1815,  1816,  1817,  1818,  1819,
    1820,  1821,  1822,  1823,  1826,  1828,  1828,  1836,  1845,  1852,
    1852,  1862,  1863,  1866,  1867,  1868,  1869,  1870,  1873,  1873,
    1881,  1881,  1892,  1892,  1930,  1930,  1942,  1942,  1952,  1953,
    1956,  1957,  1958,  1959,  1960,  1961,  1962,  1963,  1964,  1965,
    1966,  1967,  1968,  1969,  1970,  1971,  1972,  1973,  1976,  1981,
    1981,  1989,  1989,  1997,  2002,  2002,  2010,  2015,  2020,  2020,
    2028,  2029,  2032,  2032,  2040,  2045,  2050,  2050,  2058,  2061,
    2064,  2067,  2070,  2076,  2076,  2084,  2084,  2092,  2092,  2103,
    2103,  2110,  2110,  2117,  2117,  2124,  2124,  2135,  2135,  2145,
    2146,  2150,  2151,  2154,  2154,  2164,  2174,  2174,  2184,  2184,
    2195,  2196,  2200,  2204,  2204,  2216,  2217,  2221,  2221,  2229,
    2230,  2233,  2234,  2235,  2236,  2237,  2238,  2239,  2242,  2247,
    2247,  2255,  2255,  2265,  2266,  2269,  2269,  2277,  2278,  2281,
    2282,  2283,  2284,  2287,  2287,  2295,  2300,  2305
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
#line 5062 "dhcp4_parser.cc" // lalr1.cc:1242
#line 2310 "dhcp4_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
