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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy"

#include <dhcp4/parser_context.h>

#line 51 "dhcp4_parser.cc"


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

#line 14 "dhcp4_parser.yy"
namespace isc { namespace dhcp {
#line 146 "dhcp4_parser.cc"


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
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case 172: // "integer"
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case 173: // "floating point"
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case 174: // "boolean"
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case 191: // value
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case 195: // map_value
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case 239: // socket_type
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case 242: // outbound_interface_value
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case 264: // db_type
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case 350: // hr_mode
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case 499: // ncr_protocol_value
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case 506: // replace_client_name_value
#line 253 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
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
#line 262 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 741 "dhcp4_parser.cc"
    break;

  case 4:
#line 263 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 747 "dhcp4_parser.cc"
    break;

  case 6:
#line 264 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 753 "dhcp4_parser.cc"
    break;

  case 8:
#line 265 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 759 "dhcp4_parser.cc"
    break;

  case 10:
#line 266 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.SUBNET4; }
#line 765 "dhcp4_parser.cc"
    break;

  case 12:
#line 267 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 771 "dhcp4_parser.cc"
    break;

  case 14:
#line 268 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 777 "dhcp4_parser.cc"
    break;

  case 16:
#line 269 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 783 "dhcp4_parser.cc"
    break;

  case 18:
#line 270 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 789 "dhcp4_parser.cc"
    break;

  case 20:
#line 271 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 795 "dhcp4_parser.cc"
    break;

  case 22:
#line 272 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 801 "dhcp4_parser.cc"
    break;

  case 24:
#line 273 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 26:
#line 274 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 813 "dhcp4_parser.cc"
    break;

  case 28:
#line 275 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 819 "dhcp4_parser.cc"
    break;

  case 30:
#line 283 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 825 "dhcp4_parser.cc"
    break;

  case 31:
#line 284 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 831 "dhcp4_parser.cc"
    break;

  case 32:
#line 285 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 837 "dhcp4_parser.cc"
    break;

  case 33:
#line 286 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 843 "dhcp4_parser.cc"
    break;

  case 34:
#line 287 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 849 "dhcp4_parser.cc"
    break;

  case 35:
#line 288 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 855 "dhcp4_parser.cc"
    break;

  case 36:
#line 289 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 861 "dhcp4_parser.cc"
    break;

  case 37:
#line 292 "dhcp4_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 870 "dhcp4_parser.cc"
    break;

  case 38:
#line 297 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 881 "dhcp4_parser.cc"
    break;

  case 39:
#line 302 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 891 "dhcp4_parser.cc"
    break;

  case 40:
#line 308 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp4_parser.cc"
    break;

  case 43:
#line 315 "dhcp4_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 906 "dhcp4_parser.cc"
    break;

  case 44:
#line 319 "dhcp4_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp4_parser.cc"
    break;

  case 45:
#line 326 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp4_parser.cc"
    break;

  case 46:
#line 329 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp4_parser.cc"
    break;

  case 49:
#line 337 "dhcp4_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp4_parser.cc"
    break;

  case 50:
#line 341 "dhcp4_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp4_parser.cc"
    break;

  case 51:
#line 348 "dhcp4_parser.yy"
    {
    // List parsing about to start
}
#line 959 "dhcp4_parser.cc"
    break;

  case 52:
#line 350 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp4_parser.cc"
    break;

  case 55:
#line 359 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp4_parser.cc"
    break;

  case 56:
#line 363 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp4_parser.cc"
    break;

  case 57:
#line 374 "dhcp4_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp4_parser.cc"
    break;

  case 58:
#line 384 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp4_parser.cc"
    break;

  case 59:
#line 389 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1021 "dhcp4_parser.cc"
    break;

  case 68:
#line 413 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1034 "dhcp4_parser.cc"
    break;

  case 69:
#line 420 "dhcp4_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1044 "dhcp4_parser.cc"
    break;

  case 70:
#line 428 "dhcp4_parser.yy"
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1054 "dhcp4_parser.cc"
    break;

  case 71:
#line 432 "dhcp4_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1063 "dhcp4_parser.cc"
    break;

  case 114:
#line 485 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 115:
#line 490 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 116:
#line 495 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 117:
#line 500 "dhcp4_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1099 "dhcp4_parser.cc"
    break;

  case 118:
#line 505 "dhcp4_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1108 "dhcp4_parser.cc"
    break;

  case 119:
#line 510 "dhcp4_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1117 "dhcp4_parser.cc"
    break;

  case 120:
#line 515 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1126 "dhcp4_parser.cc"
    break;

  case 121:
#line 520 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1134 "dhcp4_parser.cc"
    break;

  case 122:
#line 522 "dhcp4_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1144 "dhcp4_parser.cc"
    break;

  case 123:
#line 528 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1153 "dhcp4_parser.cc"
    break;

  case 124:
#line 533 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1162 "dhcp4_parser.cc"
    break;

  case 125:
#line 538 "dhcp4_parser.yy"
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 126:
#line 544 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1182 "dhcp4_parser.cc"
    break;

  case 127:
#line 549 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1192 "dhcp4_parser.cc"
    break;

  case 137:
#line 568 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1202 "dhcp4_parser.cc"
    break;

  case 138:
#line 572 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 139:
#line 577 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1222 "dhcp4_parser.cc"
    break;

  case 140:
#line 582 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 141:
#line 587 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1239 "dhcp4_parser.cc"
    break;

  case 142:
#line 589 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 143:
#line 594 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1254 "dhcp4_parser.cc"
    break;

  case 144:
#line 595 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1260 "dhcp4_parser.cc"
    break;

  case 145:
#line 598 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 146:
#line 600 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 147:
#line 605 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 148:
#line 607 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1293 "dhcp4_parser.cc"
    break;

  case 149:
#line 611 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1302 "dhcp4_parser.cc"
    break;

  case 150:
#line 617 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1313 "dhcp4_parser.cc"
    break;

  case 151:
#line 622 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1324 "dhcp4_parser.cc"
    break;

  case 152:
#line 629 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 153:
#line 634 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1344 "dhcp4_parser.cc"
    break;

  case 157:
#line 644 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1352 "dhcp4_parser.cc"
    break;

  case 158:
#line 646 "dhcp4_parser.yy"
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
#line 1372 "dhcp4_parser.cc"
    break;

  case 159:
#line 662 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1383 "dhcp4_parser.cc"
    break;

  case 160:
#line 667 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 161:
#line 674 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1405 "dhcp4_parser.cc"
    break;

  case 162:
#line 679 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1414 "dhcp4_parser.cc"
    break;

  case 167:
#line 692 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 168:
#line 696 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 191:
#line 728 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 192:
#line 730 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc"
    break;

  case 193:
#line 735 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1457 "dhcp4_parser.cc"
    break;

  case 194:
#line 736 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1463 "dhcp4_parser.cc"
    break;

  case 195:
#line 737 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1469 "dhcp4_parser.cc"
    break;

  case 196:
#line 738 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1475 "dhcp4_parser.cc"
    break;

  case 197:
#line 741 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1483 "dhcp4_parser.cc"
    break;

  case 198:
#line 743 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1493 "dhcp4_parser.cc"
    break;

  case 199:
#line 749 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1501 "dhcp4_parser.cc"
    break;

  case 200:
#line 751 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1511 "dhcp4_parser.cc"
    break;

  case 201:
#line 757 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1519 "dhcp4_parser.cc"
    break;

  case 202:
#line 759 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1529 "dhcp4_parser.cc"
    break;

  case 203:
#line 765 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1538 "dhcp4_parser.cc"
    break;

  case 204:
#line 770 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1546 "dhcp4_parser.cc"
    break;

  case 205:
#line 772 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 206:
#line 778 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1565 "dhcp4_parser.cc"
    break;

  case 207:
#line 783 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 208:
#line 788 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 209:
#line 793 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1592 "dhcp4_parser.cc"
    break;

  case 210:
#line 798 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 211:
#line 803 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1610 "dhcp4_parser.cc"
    break;

  case 212:
#line 808 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1619 "dhcp4_parser.cc"
    break;

  case 213:
#line 813 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp4_parser.cc"
    break;

  case 214:
#line 815 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1637 "dhcp4_parser.cc"
    break;

  case 215:
#line 821 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 216:
#line 823 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 217:
#line 829 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 218:
#line 831 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 219:
#line 837 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1681 "dhcp4_parser.cc"
    break;

  case 220:
#line 839 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1691 "dhcp4_parser.cc"
    break;

  case 221:
#line 845 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1700 "dhcp4_parser.cc"
    break;

  case 222:
#line 850 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 223:
#line 855 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1720 "dhcp4_parser.cc"
    break;

  case 224:
#line 860 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc"
    break;

  case 232:
#line 876 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 233:
#line 881 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1747 "dhcp4_parser.cc"
    break;

  case 234:
#line 886 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 235:
#line 891 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 236:
#line 896 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 237:
#line 901 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1785 "dhcp4_parser.cc"
    break;

  case 238:
#line 906 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc"
    break;

  case 243:
#line 919 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1804 "dhcp4_parser.cc"
    break;

  case 244:
#line 923 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1814 "dhcp4_parser.cc"
    break;

  case 245:
#line 929 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1824 "dhcp4_parser.cc"
    break;

  case 246:
#line 933 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 252:
#line 948 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1842 "dhcp4_parser.cc"
    break;

  case 253:
#line 950 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 254:
#line 956 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 255:
#line 958 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 256:
#line 964 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1880 "dhcp4_parser.cc"
    break;

  case 257:
#line 969 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 266:
#line 987 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1899 "dhcp4_parser.cc"
    break;

  case 267:
#line 992 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1908 "dhcp4_parser.cc"
    break;

  case 268:
#line 997 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1917 "dhcp4_parser.cc"
    break;

  case 269:
#line 1002 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 270:
#line 1007 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 271:
#line 1012 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 272:
#line 1020 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1955 "dhcp4_parser.cc"
    break;

  case 273:
#line 1025 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1964 "dhcp4_parser.cc"
    break;

  case 278:
#line 1045 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1974 "dhcp4_parser.cc"
    break;

  case 279:
#line 1049 "dhcp4_parser.yy"
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
#line 2000 "dhcp4_parser.cc"
    break;

  case 280:
#line 1071 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 281:
#line 1075 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 311:
#line 1116 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2028 "dhcp4_parser.cc"
    break;

  case 312:
#line 1118 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2038 "dhcp4_parser.cc"
    break;

  case 313:
#line 1124 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp4_parser.cc"
    break;

  case 314:
#line 1126 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 315:
#line 1132 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc"
    break;

  case 316:
#line 1134 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 317:
#line 1140 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2082 "dhcp4_parser.cc"
    break;

  case 318:
#line 1142 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2092 "dhcp4_parser.cc"
    break;

  case 319:
#line 1148 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 320:
#line 1150 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 321:
#line 1156 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp4_parser.cc"
    break;

  case 322:
#line 1158 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2128 "dhcp4_parser.cc"
    break;

  case 323:
#line 1164 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 324:
#line 1169 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2148 "dhcp4_parser.cc"
    break;

  case 325:
#line 1174 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2156 "dhcp4_parser.cc"
    break;

  case 326:
#line 1176 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2165 "dhcp4_parser.cc"
    break;

  case 327:
#line 1181 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2171 "dhcp4_parser.cc"
    break;

  case 328:
#line 1182 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2177 "dhcp4_parser.cc"
    break;

  case 329:
#line 1183 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2183 "dhcp4_parser.cc"
    break;

  case 330:
#line 1184 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2189 "dhcp4_parser.cc"
    break;

  case 331:
#line 1187 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2198 "dhcp4_parser.cc"
    break;

  case 332:
#line 1194 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 333:
#line 1199 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc"
    break;

  case 338:
#line 1214 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2228 "dhcp4_parser.cc"
    break;

  case 339:
#line 1218 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2236 "dhcp4_parser.cc"
    break;

  case 364:
#line 1254 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2247 "dhcp4_parser.cc"
    break;

  case 365:
#line 1259 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2256 "dhcp4_parser.cc"
    break;

  case 366:
#line 1267 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2265 "dhcp4_parser.cc"
    break;

  case 367:
#line 1270 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2273 "dhcp4_parser.cc"
    break;

  case 372:
#line 1286 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 373:
#line 1290 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2295 "dhcp4_parser.cc"
    break;

  case 374:
#line 1301 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2305 "dhcp4_parser.cc"
    break;

  case 375:
#line 1305 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 391:
#line 1337 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2326 "dhcp4_parser.cc"
    break;

  case 393:
#line 1344 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc"
    break;

  case 394:
#line 1346 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 395:
#line 1352 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc"
    break;

  case 396:
#line 1354 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc"
    break;

  case 397:
#line 1360 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp4_parser.cc"
    break;

  case 398:
#line 1362 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc"
    break;

  case 400:
#line 1370 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp4_parser.cc"
    break;

  case 401:
#line 1372 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 402:
#line 1378 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 403:
#line 1387 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2418 "dhcp4_parser.cc"
    break;

  case 404:
#line 1392 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2427 "dhcp4_parser.cc"
    break;

  case 409:
#line 1411 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2437 "dhcp4_parser.cc"
    break;

  case 410:
#line 1415 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2446 "dhcp4_parser.cc"
    break;

  case 411:
#line 1423 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2456 "dhcp4_parser.cc"
    break;

  case 412:
#line 1427 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 427:
#line 1460 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 428:
#line 1462 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 431:
#line 1472 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 432:
#line 1477 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 433:
#line 1485 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2512 "dhcp4_parser.cc"
    break;

  case 434:
#line 1490 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 439:
#line 1505 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2531 "dhcp4_parser.cc"
    break;

  case 440:
#line 1509 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2541 "dhcp4_parser.cc"
    break;

  case 441:
#line 1515 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2551 "dhcp4_parser.cc"
    break;

  case 442:
#line 1519 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2561 "dhcp4_parser.cc"
    break;

  case 452:
#line 1538 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2569 "dhcp4_parser.cc"
    break;

  case 453:
#line 1540 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2579 "dhcp4_parser.cc"
    break;

  case 454:
#line 1546 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 455:
#line 1548 "dhcp4_parser.yy"
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
#line 2614 "dhcp4_parser.cc"
    break;

  case 456:
#line 1571 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2622 "dhcp4_parser.cc"
    break;

  case 457:
#line 1573 "dhcp4_parser.yy"
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
#line 2651 "dhcp4_parser.cc"
    break;

  case 458:
#line 1601 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2662 "dhcp4_parser.cc"
    break;

  case 459:
#line 1606 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2671 "dhcp4_parser.cc"
    break;

  case 464:
#line 1619 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2681 "dhcp4_parser.cc"
    break;

  case 465:
#line 1623 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2690 "dhcp4_parser.cc"
    break;

  case 466:
#line 1628 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2700 "dhcp4_parser.cc"
    break;

  case 467:
#line 1632 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2709 "dhcp4_parser.cc"
    break;

  case 487:
#line 1663 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2717 "dhcp4_parser.cc"
    break;

  case 488:
#line 1665 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2727 "dhcp4_parser.cc"
    break;

  case 489:
#line 1671 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2735 "dhcp4_parser.cc"
    break;

  case 490:
#line 1673 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 491:
#line 1679 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp4_parser.cc"
    break;

  case 492:
#line 1681 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2763 "dhcp4_parser.cc"
    break;

  case 493:
#line 1687 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 494:
#line 1689 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 495:
#line 1695 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 496:
#line 1700 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 497:
#line 1705 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2809 "dhcp4_parser.cc"
    break;

  case 498:
#line 1707 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2819 "dhcp4_parser.cc"
    break;

  case 499:
#line 1713 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2827 "dhcp4_parser.cc"
    break;

  case 500:
#line 1715 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2837 "dhcp4_parser.cc"
    break;

  case 501:
#line 1721 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2845 "dhcp4_parser.cc"
    break;

  case 502:
#line 1723 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2855 "dhcp4_parser.cc"
    break;

  case 503:
#line 1729 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 504:
#line 1731 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2873 "dhcp4_parser.cc"
    break;

  case 505:
#line 1737 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 506:
#line 1739 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 507:
#line 1745 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 508:
#line 1747 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 509:
#line 1753 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 510:
#line 1758 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2929 "dhcp4_parser.cc"
    break;

  case 511:
#line 1766 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2940 "dhcp4_parser.cc"
    break;

  case 512:
#line 1771 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2949 "dhcp4_parser.cc"
    break;

  case 515:
#line 1783 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 516:
#line 1788 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2969 "dhcp4_parser.cc"
    break;

  case 519:
#line 1797 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2979 "dhcp4_parser.cc"
    break;

  case 520:
#line 1801 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 537:
#line 1830 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2997 "dhcp4_parser.cc"
    break;

  case 538:
#line 1832 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3007 "dhcp4_parser.cc"
    break;

  case 539:
#line 1838 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3016 "dhcp4_parser.cc"
    break;

  case 540:
#line 1847 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3025 "dhcp4_parser.cc"
    break;

  case 541:
#line 1854 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3036 "dhcp4_parser.cc"
    break;

  case 542:
#line 1859 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3045 "dhcp4_parser.cc"
    break;

  case 550:
#line 1875 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3053 "dhcp4_parser.cc"
    break;

  case 551:
#line 1877 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 552:
#line 1883 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 553:
#line 1885 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 554:
#line 1894 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp4_parser.cc"
    break;

  case 555:
#line 1896 "dhcp4_parser.yy"
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
#line 3127 "dhcp4_parser.cc"
    break;

  case 556:
#line 1932 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3138 "dhcp4_parser.cc"
    break;

  case 557:
#line 1937 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 558:
#line 1944 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 559:
#line 1948 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 580:
#line 1978 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 581:
#line 1983 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 582:
#line 1985 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3196 "dhcp4_parser.cc"
    break;

  case 583:
#line 1991 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3204 "dhcp4_parser.cc"
    break;

  case 584:
#line 1993 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 585:
#line 1999 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3223 "dhcp4_parser.cc"
    break;

  case 586:
#line 2004 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3231 "dhcp4_parser.cc"
    break;

  case 587:
#line 2006 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3241 "dhcp4_parser.cc"
    break;

  case 588:
#line 2012 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3250 "dhcp4_parser.cc"
    break;

  case 589:
#line 2017 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3259 "dhcp4_parser.cc"
    break;

  case 590:
#line 2022 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3267 "dhcp4_parser.cc"
    break;

  case 591:
#line 2024 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3276 "dhcp4_parser.cc"
    break;

  case 592:
#line 2030 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3282 "dhcp4_parser.cc"
    break;

  case 593:
#line 2031 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3288 "dhcp4_parser.cc"
    break;

  case 594:
#line 2034 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3296 "dhcp4_parser.cc"
    break;

  case 595:
#line 2036 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3306 "dhcp4_parser.cc"
    break;

  case 596:
#line 2042 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3315 "dhcp4_parser.cc"
    break;

  case 597:
#line 2047 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3324 "dhcp4_parser.cc"
    break;

  case 598:
#line 2052 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 599:
#line 2054 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 600:
#line 2060 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3349 "dhcp4_parser.cc"
    break;

  case 601:
#line 2063 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3357 "dhcp4_parser.cc"
    break;

  case 602:
#line 2066 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3365 "dhcp4_parser.cc"
    break;

  case 603:
#line 2069 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3373 "dhcp4_parser.cc"
    break;

  case 604:
#line 2072 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3382 "dhcp4_parser.cc"
    break;

  case 605:
#line 2078 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3390 "dhcp4_parser.cc"
    break;

  case 606:
#line 2080 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3400 "dhcp4_parser.cc"
    break;

  case 607:
#line 2086 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 608:
#line 2088 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 609:
#line 2094 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3426 "dhcp4_parser.cc"
    break;

  case 610:
#line 2096 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3436 "dhcp4_parser.cc"
    break;

  case 611:
#line 2105 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 612:
#line 2107 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 613:
#line 2112 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3461 "dhcp4_parser.cc"
    break;

  case 614:
#line 2114 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3470 "dhcp4_parser.cc"
    break;

  case 615:
#line 2119 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3478 "dhcp4_parser.cc"
    break;

  case 616:
#line 2121 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3487 "dhcp4_parser.cc"
    break;

  case 617:
#line 2126 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3498 "dhcp4_parser.cc"
    break;

  case 618:
#line 2131 "dhcp4_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3508 "dhcp4_parser.cc"
    break;

  case 619:
#line 2137 "dhcp4_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3518 "dhcp4_parser.cc"
    break;

  case 620:
#line 2141 "dhcp4_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3527 "dhcp4_parser.cc"
    break;

  case 625:
#line 2156 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3538 "dhcp4_parser.cc"
    break;

  case 626:
#line 2161 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3547 "dhcp4_parser.cc"
    break;

  case 627:
#line 2166 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3556 "dhcp4_parser.cc"
    break;

  case 628:
#line 2176 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3567 "dhcp4_parser.cc"
    break;

  case 629:
#line 2181 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3576 "dhcp4_parser.cc"
    break;

  case 630:
#line 2186 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3586 "dhcp4_parser.cc"
    break;

  case 631:
#line 2190 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 635:
#line 2206 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3605 "dhcp4_parser.cc"
    break;

  case 636:
#line 2211 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3614 "dhcp4_parser.cc"
    break;

  case 639:
#line 2223 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3624 "dhcp4_parser.cc"
    break;

  case 640:
#line 2227 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 650:
#line 2244 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 651:
#line 2249 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3649 "dhcp4_parser.cc"
    break;

  case 652:
#line 2251 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3659 "dhcp4_parser.cc"
    break;

  case 653:
#line 2257 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3670 "dhcp4_parser.cc"
    break;

  case 654:
#line 2262 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 657:
#line 2271 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 658:
#line 2275 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3697 "dhcp4_parser.cc"
    break;

  case 665:
#line 2289 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3705 "dhcp4_parser.cc"
    break;

  case 666:
#line 2291 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3715 "dhcp4_parser.cc"
    break;

  case 667:
#line 2297 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3724 "dhcp4_parser.cc"
    break;

  case 668:
#line 2302 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 669:
#line 2307 "dhcp4_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3742 "dhcp4_parser.cc"
    break;


#line 3746 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -827;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     356,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,    48,    21,    37,    64,    80,
      86,    88,   100,   125,   134,   136,   150,   163,   167,   169,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,    21,    16,
      17,   152,    54,    62,    71,   228,   128,    26,   217,   -47,
     504,    60,    93,  -827,   234,   244,   245,   240,   252,  -827,
    -827,  -827,  -827,  -827,   257,  -827,    42,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   258,   261,   272,  -827,
    -827,  -827,  -827,  -827,  -827,   275,   279,   297,   301,   305,
     312,   318,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,   320,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,    44,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   342,  -827,    75,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,   345,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,    78,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,   147,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   353,   266,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,   354,  -827,  -827,   346,  -827,  -827,  -827,   360,
    -827,  -827,   357,   323,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   363,   364,  -827,
    -827,  -827,  -827,   362,   368,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   161,  -827,  -827,
    -827,   369,  -827,  -827,   372,  -827,   376,   379,  -827,  -827,
     380,   381,  -827,  -827,  -827,  -827,  -827,   183,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,   196,  -827,  -827,  -827,   382,   199,
    -827,  -827,  -827,  -827,    21,    21,  -827,   201,   387,   389,
     394,   396,   397,  -827,    17,  -827,   399,   400,   401,   237,
     238,   241,   403,   417,   426,   427,   446,   447,   280,   281,
     282,   283,   285,   286,   284,   451,   456,   458,   465,   466,
     468,   469,   471,   474,   475,   476,   477,   478,   311,   480,
     481,   482,   483,   484,   487,   152,  -827,   489,   491,   492,
     324,    54,  -827,   493,   495,   496,   498,   499,   501,   335,
     502,   505,   506,    62,  -827,   507,    71,  -827,   523,   525,
     526,   528,   529,   531,   532,   533,  -827,   228,  -827,   534,
     535,   371,   536,   537,   540,   373,  -827,    26,   541,   374,
     375,  -827,   217,   542,   546,     7,  -827,   378,   549,   550,
     383,   552,   385,   386,   557,   559,   390,   392,   563,   565,
     504,  -827,    60,  -827,   566,   402,    93,  -827,  -827,  -827,
     567,   568,   569,    21,    21,    21,  -827,   570,   572,   573,
    -827,  -827,  -827,   337,   388,   410,   575,   576,   579,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   419,   583,   587,   607,
     609,   608,   445,   265,   612,   613,   614,   615,   616,  -827,
     617,   608,   619,   450,   470,   622,  -827,   637,   108,   202,
    -827,  -827,   472,   473,   479,   640,   485,   486,  -827,   637,
     488,   639,  -827,   490,  -827,   637,   494,   497,   500,   503,
     508,   509,   510,  -827,   511,   512,  -827,   513,   514,   515,
    -827,  -827,   516,  -827,  -827,  -827,   517,    21,  -827,  -827,
     518,   519,  -827,   520,  -827,  -827,    14,   435,  -827,  -827,
     112,   521,  -827,  -827,   644,  -827,  -827,    21,   152,    60,
    -827,  -827,  -827,    93,    54,   598,  -827,  -827,  -827,   555,
     555,   645,  -827,   646,   647,   648,   651,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,   213,   653,   655,   656,    -2,
      18,  -827,   504,  -827,  -827,   657,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   659,  -827,  -827,
    -827,  -827,   123,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,   645,  -827,   216,   229,   233,   235,
    -827,   256,  -827,  -827,  -827,  -827,  -827,  -827,   663,   665,
     666,   668,   669,  -827,  -827,  -827,  -827,   672,   673,   674,
     689,   690,  -827,   269,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,   270,  -827,   691,   692,  -827,  -827,
     693,   695,  -827,  -827,   694,   698,  -827,  -827,   696,   700,
    -827,  -827,   699,   701,  -827,  -827,  -827,  -827,  -827,  -827,
      74,  -827,  -827,  -827,  -827,  -827,  -827,  -827,    91,  -827,
    -827,   702,   703,  -827,  -827,   704,   706,  -827,   707,   708,
     709,   710,   711,   712,   299,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   300,  -827,  -827,
    -827,   317,  -827,   155,  -827,   547,  -827,   713,   714,  -827,
    -827,  -827,  -827,   643,   715,  -827,  -827,  -827,  -827,   716,
     598,  -827,   718,   719,   720,   721,   524,   553,   556,   558,
     561,   725,   726,   727,   730,   564,   571,   574,   577,   578,
     555,  -827,  -827,   555,  -827,   645,    62,  -827,   646,    26,
    -827,   647,   217,  -827,   648,   407,  -827,   651,   213,  -827,
     198,   653,  -827,   228,  -827,   655,   -47,  -827,   656,   581,
     582,   584,   585,   586,   588,    -2,  -827,   731,   733,    18,
    -827,  -827,   135,   657,  -827,  -827,   732,   736,    71,  -827,
     659,   737,  -827,  -827,   580,  -827,   322,   590,   591,   592,
    -827,  -827,  -827,  -827,  -827,   593,   594,   595,   596,  -827,
    -827,  -827,  -827,  -827,  -827,   330,  -827,   332,  -827,   734,
    -827,   739,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   333,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
     740,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
     742,   745,  -827,  -827,  -827,  -827,  -827,   747,  -827,   334,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   597,   599,
    -827,  -827,   741,  -827,  -827,  -827,  -827,  -827,   336,  -827,
    -827,  -827,  -827,  -827,  -827,   600,   340,  -827,   637,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   407,  -827,   755,   601,
    -827,   198,  -827,  -827,  -827,  -827,   765,   602,   768,   135,
    -827,  -827,  -827,  -827,  -827,   606,  -827,  -827,   735,  -827,
     610,  -827,  -827,   766,  -827,  -827,   197,  -827,   -18,   766,
    -827,  -827,   774,   779,   780,   344,  -827,  -827,  -827,  -827,
    -827,  -827,   785,   624,   627,   632,   -18,  -827,   635,  -827,
    -827,  -827,  -827,  -827
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   137,     9,   280,    11,
     441,    13,   466,    15,   366,    17,   374,    19,   411,    21,
     245,    23,   558,    25,   630,    27,   619,    29,    47,    41,
       0,     0,     0,     0,     0,   468,     0,   376,   413,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     628,   611,   613,   615,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   617,   126,   152,     0,     0,     0,   487,
     489,   491,   150,   159,   161,     0,     0,     0,     0,     0,
       0,     0,   121,   272,   364,   403,   332,   454,   456,   325,
     223,   515,   458,   237,   256,     0,   541,   554,   556,   607,
     609,   635,   113,     0,    72,    74,    75,    76,   107,   108,
     109,    77,   105,    94,    95,    96,    80,    81,   102,    82,
      83,    84,    88,    89,    78,   106,    79,    86,    87,   100,
     101,   103,    97,    98,    99,    85,    90,    91,    92,    93,
     111,   112,   104,   110,   139,   141,   145,     0,   136,     0,
     128,   130,   131,   132,   133,   134,   135,   313,   315,   317,
     433,   311,   319,     0,   323,   321,   511,   310,   284,   285,
     286,   307,   308,   309,   297,   298,     0,   282,   289,   302,
     303,   304,   290,   292,   293,   295,   291,   287,   288,   305,
     306,   294,   299,   300,   301,   296,   452,   451,   447,   448,
     446,     0,   443,   445,   449,   450,   509,   497,   499,   503,
     501,   507,   505,   493,   486,   480,   484,   485,     0,   469,
     470,   481,   482,   483,   477,   472,   478,   474,   475,   476,
     479,   473,     0,   393,   204,     0,   397,   395,   400,     0,
     389,   390,     0,   377,   378,   380,   392,   381,   382,   383,
     399,   384,   385,   386,   387,   388,   427,     0,     0,   425,
     426,   429,   430,     0,   414,   415,   417,   418,   419,   420,
     421,   422,   423,   424,   252,   254,   249,     0,   247,   250,
     251,     0,   581,   583,     0,   586,     0,     0,   590,   594,
       0,     0,   598,   605,   579,   577,   578,     0,   560,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   575,   576,     0,   632,   634,   625,     0,     0,
     621,   623,   624,    46,     0,     0,    39,     0,     0,     0,
       0,     0,     0,    57,     0,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,   138,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   281,     0,     0,   442,     0,     0,
       0,     0,     0,     0,     0,     0,   467,     0,   367,     0,
       0,     0,     0,     0,     0,     0,   375,     0,     0,     0,
       0,   412,     0,     0,     0,     0,   246,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   559,     0,   631,     0,     0,     0,   620,    50,    43,
       0,     0,     0,     0,     0,     0,    61,     0,     0,     0,
     123,   124,   125,     0,     0,     0,     0,     0,     0,   114,
     115,   116,   117,   118,   119,   120,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   540,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     0,
     149,   129,     0,     0,     0,     0,     0,     0,   331,     0,
       0,     0,   283,     0,   444,     0,     0,     0,     0,     0,
       0,     0,     0,   471,     0,     0,   391,     0,     0,     0,
     402,   379,     0,   431,   432,   416,     0,     0,   248,   580,
       0,     0,   585,     0,   588,   589,     0,     0,   596,   597,
       0,     0,   561,   633,     0,   627,   622,     0,     0,     0,
     612,   614,   616,     0,     0,     0,   488,   490,   492,     0,
       0,   163,   122,   274,   368,   405,   334,    40,   455,   457,
     327,   328,   329,   330,   326,     0,     0,   460,   239,     0,
       0,   555,     0,   608,   610,     0,    51,   140,   143,   144,
     142,   147,   148,   146,   314,   316,   318,   435,   312,   320,
     324,   322,     0,   453,   510,   498,   500,   504,   502,   508,
     506,   494,   394,   205,   398,   396,   401,   428,   253,   255,
     582,   584,   587,   592,   593,   591,   595,   600,   601,   602,
     603,   604,   599,   606,   163,    44,     0,     0,     0,     0,
     157,     0,   154,   156,   191,   197,   199,   201,     0,     0,
       0,     0,     0,   213,   215,   217,   219,     0,     0,     0,
       0,     0,   190,     0,   169,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   184,   185,   186,   181,   187,
     188,   189,   182,   183,     0,   167,     0,   164,   165,   278,
       0,   275,   276,   372,     0,   369,   370,   409,     0,   406,
     407,   338,     0,   335,   336,   232,   233,   234,   235,   236,
       0,   225,   227,   228,   229,   230,   231,   519,     0,   517,
     464,     0,   461,   462,   243,     0,   240,   241,     0,     0,
       0,     0,     0,     0,     0,   258,   260,   261,   262,   263,
     264,   265,   550,   552,   549,   547,   548,     0,   543,   545,
     546,     0,   639,     0,   637,    53,   439,     0,   436,   437,
     495,   513,   514,     0,     0,    69,   629,   618,   127,     0,
       0,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   151,   160,     0,   162,     0,     0,   273,     0,   376,
     365,     0,   413,   404,     0,     0,   333,     0,     0,   224,
     521,     0,   516,   468,   459,     0,     0,   238,     0,     0,
       0,     0,     0,     0,     0,     0,   257,     0,     0,     0,
     542,   557,     0,     0,   636,    55,     0,    54,     0,   434,
       0,     0,   512,   626,     0,   155,     0,     0,     0,     0,
     203,   206,   207,   208,   209,     0,     0,     0,     0,   221,
     222,   210,   211,   212,   170,     0,   166,     0,   277,     0,
     371,     0,   408,   363,   357,   345,   346,   360,   361,   362,
     348,   349,   342,   343,   344,   355,   356,   354,     0,   340,
     347,   358,   359,   350,   351,   352,   353,   337,   226,   537,
       0,   535,   536,   528,   529,   533,   534,   530,   531,   532,
       0,   522,   523,   525,   526,   527,   518,     0,   463,     0,
     242,   266,   267,   268,   269,   270,   271,   259,     0,     0,
     544,   653,     0,   651,   649,   643,   647,   648,     0,   641,
     645,   646,   644,   638,    52,     0,     0,   438,     0,   158,
     193,   194,   195,   196,   192,   198,   200,   202,   214,   216,
     218,   220,   168,   279,   373,   410,     0,   339,     0,     0,
     520,     0,   465,   244,   551,   553,     0,     0,     0,     0,
     640,    56,   440,   496,   341,     0,   539,   524,     0,   650,
       0,   642,   538,     0,   652,   657,     0,   655,     0,     0,
     654,   665,     0,     0,     0,     0,   659,   661,   662,   663,
     664,   656,     0,     0,     0,     0,     0,   658,     0,   667,
     668,   669,   660,   666
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   -46,  -827,  -456,  -827,
     176,  -827,  -827,  -827,  -827,  -827,  -827,  -524,  -827,  -827,
    -827,   -70,  -827,  -827,  -827,   441,  -827,  -827,  -827,  -827,
     225,   411,   -55,   -54,   -27,   -24,    -9,     6,  -827,  -827,
    -827,  -827,     9,    11,  -827,  -827,   230,   408,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,    15,  -827,  -827,  -827,  -827,  -827,
    -827,   158,  -827,     5,  -827,  -597,    28,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   -35,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,    19,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,     2,
    -827,  -827,  -827,   -15,   409,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,    -3,  -827,  -827,  -827,  -827,  -827,  -827,  -826,
    -827,  -827,  -827,    25,  -827,  -827,  -827,    29,   443,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -818,  -827,   -23,
    -827,   -17,  -827,    12,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,    22,  -827,  -827,  -138,   -65,  -827,  -827,  -827,  -827,
    -827,    31,  -827,  -827,  -827,    34,  -827,   423,  -827,   -72,
    -827,  -827,  -827,  -827,  -827,   -66,  -827,  -827,  -827,  -827,
    -827,    -7,  -827,  -827,  -827,    30,  -827,  -827,  -827,    33,
    -827,   424,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,     0,  -827,  -827,  -827,     1,   452,  -827,
    -827,   -39,  -827,   -19,  -827,   -59,  -827,  -827,  -827,    27,
    -827,  -827,  -827,    24,  -827,   444,   -58,  -827,   -52,  -827,
      -1,  -827,   242,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -815,  -827,  -827,  -827,  -827,  -827,    32,  -827,  -827,  -827,
    -126,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,    20,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
     264,   418,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,   -64,  -827,   -60,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   294,   414,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   302,   420,   -57,
    -827,  -827,    23,  -827,  -827,  -125,  -827,  -827,  -827,  -827,
    -827,  -827,  -146,  -827,  -827,  -161,  -827,  -827,  -827,  -827,
    -827
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     618,    87,    88,    41,    68,    84,    85,   637,   805,   886,
     887,   712,    43,    70,    96,    97,    98,   368,    45,    71,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     395,   153,   154,   155,   156,   377,   189,   190,    47,    72,
     191,   417,   192,   418,   640,   193,   419,   643,   194,   157,
     385,   158,   378,   691,   692,   693,   819,   159,   386,   160,
     387,   736,   737,   738,   843,   713,   714,   715,   822,  1004,
     716,   823,   717,   824,   718,   825,   719,   720,   450,   721,
     722,   723,   724,   725,   726,   727,   728,   831,   729,   832,
     730,   833,   731,   834,   732,   733,   161,   403,   760,   761,
     762,   763,   764,   765,   766,   162,   406,   775,   776,   777,
     866,    61,    79,   317,   318,   319,   463,   320,   464,   163,
     407,   784,   785,   786,   787,   788,   789,   790,   791,   164,
     396,   740,   741,   742,   846,    49,    73,   216,   217,   218,
     427,   219,   423,   220,   424,   221,   425,   222,   428,   223,
     431,   224,   430,   165,   402,   624,   226,   166,   399,   752,
     753,   754,   855,   938,   939,   167,   397,    55,    76,   744,
     745,   746,   849,    57,    77,   282,   283,   284,   285,   286,
     287,   288,   449,   289,   453,   290,   452,   291,   292,   454,
     293,   168,   398,   748,   749,   750,   852,    59,    78,   303,
     304,   305,   306,   307,   458,   308,   309,   310,   311,   228,
     426,   807,   808,   809,   888,    51,    74,   241,   242,   243,
     435,   169,   400,   170,   401,   171,   405,   771,   772,   773,
     863,    53,    75,   258,   259,   260,   172,   382,   173,   383,
     174,   384,   264,   445,   812,   891,   265,   439,   266,   440,
     267,   442,   268,   441,   269,   444,   270,   443,   271,   438,
     235,   432,   813,   175,   404,   768,   769,   860,   960,   961,
     962,   963,   964,  1018,   965,   176,   177,   409,   797,   798,
     799,   877,   800,   878,   178,   410,   179,   411,    63,    80,
     337,   338,   339,   340,   468,   341,   469,   342,   343,   471,
     344,   345,   346,   474,   675,   347,   475,   348,   349,   350,
     478,   682,   351,   479,   180,   412,   181,   413,    99,   370,
     100,   371,   101,   372,   182,   376,    67,    82,   359,   360,
     361,   484,   362,   102,   369,    65,    81,   354,   355,   183,
     414,   803,   804,   882,   988,   989,   990,   991,  1028,   992,
    1026,  1046,  1047,  1048,  1055,  1056,  1057,  1062,  1058,  1059,
    1060
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   142,   188,   207,   237,   254,   301,   280,   299,   316,
     334,   272,   302,   734,   231,   232,   352,   261,   208,   209,
     353,   233,    83,   262,   356,   650,    31,    89,    32,   933,
      33,   654,   673,   195,   229,   244,   256,   934,   294,   312,
     946,   335,   281,   300,    42,   374,   210,   415,    30,   211,
     375,   238,   416,   196,   230,   245,   257,   239,   295,   313,
     273,   336,   314,   315,   212,   617,   227,   240,   255,   184,
     185,    44,   234,   186,   263,   617,   187,   858,   421,   213,
     859,   433,   214,   422,   215,   225,   434,    46,   107,   108,
     109,   110,   111,    48,   861,    50,   274,   862,   275,   276,
     127,   128,   277,   278,   279,   357,   358,    52,   127,   128,
     778,   779,   780,   781,   782,   783,   314,   315,   115,   116,
     117,   118,   119,   120,    94,   638,   639,   197,   198,   199,
    1051,   125,    54,  1052,  1053,  1054,   127,   128,   792,   793,
     125,    56,   200,    58,   127,   128,   201,   202,   203,   129,
     436,   674,   236,   127,   128,   437,   204,    60,   883,   205,
     132,   884,    90,   103,   465,   204,   104,   206,   205,   466,
      62,    91,    92,    93,    64,   105,    66,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   480,    86,    94,    94,
     933,   481,    34,    35,    36,    37,   124,    94,   934,   482,
    1049,   946,   486,  1050,   483,   274,   141,   487,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   127,   128,   415,
     124,   125,   641,   642,   815,    94,   109,   110,   111,   253,
     810,   126,   482,    94,   127,   128,   486,   816,   421,   129,
     363,   817,    94,   818,   130,   131,   915,   364,   366,   365,
     132,   677,   678,   679,   680,   367,   109,   110,   111,   820,
     133,   373,   379,   134,   821,   380,   124,   125,   274,   447,
     135,   136,   840,   840,   137,   138,   381,   841,   842,   388,
     127,   128,   981,   389,   982,   983,   681,   274,   296,   275,
     276,   297,   298,   949,   950,   139,   140,   125,   141,   127,
     128,   390,   875,   879,    95,   391,    94,   876,   880,   392,
     127,   128,   755,   756,   757,   758,   393,   759,   488,   489,
     480,   246,   394,    94,   408,   881,   457,   247,   248,   249,
     250,   251,   252,   840,   253,   433,  1016,   465,  1012,  1029,
    1013,  1017,  1023,   436,  1030,   142,   420,  1066,  1032,   429,
     451,   188,  1067,   620,   621,   622,   623,  1000,  1001,  1002,
    1003,   446,   448,   207,   455,   456,   237,   459,   460,    94,
     461,   462,   490,   467,   231,   232,   470,   254,   208,   209,
     472,   233,   195,   473,   476,   477,   485,   280,    94,   261,
     301,   491,   299,   492,   229,   262,   302,   244,   493,    94,
     494,   495,   196,   497,   498,   499,   210,   503,   256,   211,
     334,   500,   501,   238,   230,   502,   352,   245,   294,   239,
     353,   504,   281,   312,   212,   356,   227,   300,   257,   240,
     505,   506,   234,   107,   108,   109,   110,   111,   295,   213,
     255,   335,   214,   313,   215,   225,   263,   600,   601,   602,
     507,   508,   509,   510,   511,   516,   515,   512,   513,   514,
     517,   336,   518,   115,   116,   117,   118,   119,   120,   519,
     520,   123,   521,   522,  1033,   523,   125,   274,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   127,
     128,   535,   202,   537,   129,   538,   539,   542,   540,   543,
     544,   204,   545,   546,   205,   547,   549,   548,   606,   550,
     551,   553,   206,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   555,   142,   556,
     557,   669,   558,   559,   188,   560,   561,   562,   564,   565,
     567,   568,   356,   566,   569,   572,   576,   570,   573,   574,
     577,   685,   579,   580,   581,   582,   583,   584,   585,   607,
     794,   586,   334,   587,   588,   195,   589,   590,   352,   591,
     594,   597,   353,   676,   595,   598,   599,   603,    94,   604,
     605,   608,   609,   610,   611,   196,   127,   128,   613,   694,
     612,   795,   614,   335,   695,   696,   697,   698,   699,   700,
     701,   702,   703,   704,   705,   706,   707,   708,   709,   710,
     711,   796,   615,   336,   616,    32,   619,   625,   626,   627,
     628,   633,   690,   629,   630,   274,   632,   635,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   634,   636,   644,   645,   647,   652,   139,   140,   684,
     646,   892,   735,   739,   743,   747,   648,   649,   751,   651,
     767,   653,   770,   774,   802,   655,   806,   826,   656,   827,
     828,   657,   829,   830,   658,    94,   835,   836,   837,   659,
     660,   661,   662,   663,   664,   665,   666,   667,   668,   670,
     671,   672,   683,   838,   839,   845,   900,   844,   848,   847,
     850,   851,   853,   854,   857,   856,   865,   631,   864,   868,
     867,   869,   870,   871,   872,   873,   874,   890,   885,   889,
     894,   893,   896,   897,   898,   899,    94,   901,   902,   905,
     906,   907,   903,   904,   908,   978,   909,   979,   994,   995,
    1043,   998,  1014,   910,  1019,  1027,   911,  1015,  1021,   912,
    1020,   999,   913,   971,   972,  1022,   973,   974,   975,  1035,
     976,  1005,  1006,  1007,  1008,  1009,  1010,  1011,  1024,  1038,
    1025,  1031,  1040,  1045,  1039,  1036,   207,  1042,  1063,   280,
     301,  1044,   299,  1064,  1065,   923,   302,   231,   232,  1068,
     951,   208,   209,   254,   233,   953,   316,   943,  1069,  1070,
     924,   925,   957,   944,  1071,   261,  1073,   229,   958,   794,
     294,   262,   984,   312,   281,   496,   941,   300,   237,   210,
     932,   955,   211,   686,   256,   952,   536,   230,   926,   541,
     295,   927,   935,   313,   689,   895,   942,   212,   936,   227,
     795,   956,   814,   986,   257,   234,   928,   985,   940,   244,
     916,   969,   213,   954,   945,   214,   255,   215,   225,   959,
     796,   929,   263,   987,   930,   238,   931,   937,   914,   245,
     970,   239,   977,   918,   578,   917,   552,   948,  1034,   947,
     571,   240,   920,   919,   922,   921,   575,   967,   554,   996,
     997,   563,   968,   966,   811,  1037,   801,   688,   592,   980,
     596,   687,   593,  1061,  1041,  1072,   993,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   923,     0,     0,     0,
       0,   951,     0,     0,     0,     0,   953,     0,   943,   984,
       0,   924,   925,   957,   944,     0,     0,     0,     0,   958,
       0,     0,     0,     0,     0,     0,     0,   941,     0,     0,
       0,   932,   955,     0,     0,     0,   952,     0,     0,   926,
     986,     0,   927,   935,   985,     0,     0,   942,     0,   936,
       0,     0,   956,     0,     0,     0,     0,   928,     0,   940,
     987,     0,     0,     0,   954,   945,     0,     0,     0,     0,
     959,     0,   929,     0,     0,   930,     0,   931,   937
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,   610,    73,    73,    80,    75,    73,    73,
      80,    73,    68,    75,    81,   549,     5,    10,     7,   855,
       9,   555,    18,    72,    73,    74,    75,   855,    77,    78,
     855,    80,    77,    78,     7,     3,    73,     3,     0,    73,
       8,    74,     8,    72,    73,    74,    75,    74,    77,    78,
      34,    80,   109,   110,    73,   521,    73,    74,    75,    15,
      16,     7,    73,    19,    75,   531,    22,     3,     3,    73,
       6,     3,    73,     8,    73,    73,     8,     7,    26,    27,
      28,    29,    30,     7,     3,     7,    70,     6,    72,    73,
      82,    83,    76,    77,    78,    12,    13,     7,    82,    83,
     112,   113,   114,   115,   116,   117,   109,   110,    56,    57,
      58,    59,    60,    61,   171,    17,    18,    65,    66,    67,
     148,    69,     7,   151,   152,   153,    82,    83,   120,   121,
      69,     7,    80,     7,    82,    83,    84,    85,    86,    87,
       3,   137,    81,    82,    83,     8,    94,     7,     3,    97,
      98,     6,   145,    11,     3,    94,    14,   105,    97,     8,
       7,   154,   155,   156,     7,    23,     7,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     3,   171,   171,   171,
    1016,     8,   171,   172,   173,   174,    68,   171,  1016,     3,
       3,  1016,     3,     6,     8,    70,   146,     8,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    82,    83,     3,
      68,    69,    20,    21,     8,   171,    28,    29,    30,   106,
     107,    79,     3,   171,    82,    83,     3,     8,     3,    87,
       6,     8,   171,     8,    92,    93,   843,     3,     8,     4,
      98,   139,   140,   141,   142,     3,    28,    29,    30,     3,
     108,     4,     4,   111,     8,     4,    68,    69,    70,     3,
     118,   119,     3,     3,   122,   123,     4,     8,     8,     4,
      82,    83,   147,     4,   149,   150,   174,    70,    71,    72,
      73,    74,    75,    95,    96,   143,   144,    69,   146,    82,
      83,     4,     3,     3,   374,     4,   171,     8,     8,     4,
      82,    83,    99,   100,   101,   102,     4,   104,   364,   365,
       3,    93,     4,   171,     4,     8,     3,    99,   100,   101,
     102,   103,   104,     3,   106,     3,     3,     3,     8,     3,
       8,     8,     8,     3,     8,   415,     4,     3,     8,     4,
       4,   421,     8,    88,    89,    90,    91,    35,    36,    37,
      38,     8,     8,   433,     4,     8,   436,     4,     4,   171,
       8,     3,   171,     4,   433,   433,     4,   447,   433,   433,
       4,   433,   421,     4,     4,     4,     4,   457,   171,   447,
     462,     4,   462,     4,   433,   447,   462,   436,     4,   171,
       4,     4,   421,     4,     4,     4,   433,     4,   447,   433,
     480,   174,   174,   436,   433,   174,   480,   436,   457,   436,
     480,     4,   457,   462,   433,   482,   433,   462,   447,   436,
       4,     4,   433,    26,    27,    28,    29,    30,   457,   433,
     447,   480,   433,   462,   433,   433,   447,   493,   494,   495,
       4,     4,   172,   172,   172,     4,   172,   174,   173,   173,
       4,   480,     4,    56,    57,    58,    59,    60,    61,     4,
       4,    64,     4,     4,   998,     4,    69,    70,     4,     4,
       4,     4,     4,   172,     4,     4,     4,     4,     4,    82,
      83,     4,    85,     4,    87,     4,     4,     4,   174,     4,
       4,    94,     4,     4,    97,     4,     4,   172,   171,     4,
       4,     4,   105,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,     4,   598,     4,
       4,   577,     4,     4,   604,     4,     4,     4,     4,     4,
       4,     4,   599,   172,     4,     4,     4,   174,   174,   174,
       4,   597,   174,     4,     4,   172,     4,   172,   172,   171,
     630,     4,   632,     4,   174,   604,   174,     4,   632,     4,
       4,     4,   632,   138,   172,     7,     7,     7,   171,     7,
       7,   171,     7,     7,     5,   604,    82,    83,     5,    34,
     171,   630,     5,   632,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,   630,     5,   632,     5,     7,   171,     5,     5,     5,
       5,   171,    24,     7,     7,    70,     7,     5,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   171,     5,   171,   171,     5,     7,   143,   144,     5,
     171,     8,     7,     7,     7,     7,   171,   171,     7,   171,
       7,   171,     7,     7,     7,   171,     7,     4,   171,     4,
       4,   171,     4,     4,   171,   171,     4,     4,     4,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,     4,     4,     3,   172,     6,     3,     6,
       6,     3,     6,     3,     3,     6,     3,   531,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     3,   171,     6,
       4,     6,     4,     4,     4,     4,   171,   174,   172,     4,
       4,     4,   174,   172,     4,     4,   172,     4,     6,     3,
       5,     4,     8,   172,     4,     4,   172,     8,     3,   172,
       8,   171,   174,   172,   172,     8,   172,   172,   172,     4,
     172,   171,   171,   171,   171,   171,   171,   171,   171,     4,
     171,   171,     4,     7,   172,   174,   846,   171,     4,   849,
     852,   171,   852,     4,     4,   855,   852,   846,   846,     4,
     860,   846,   846,   863,   846,   860,   866,   855,   174,   172,
     855,   855,   860,   855,   172,   863,   171,   846,   860,   879,
     849,   863,   882,   852,   849,   374,   855,   852,   888,   846,
     855,   860,   846,   598,   863,   860,   415,   846,   855,   421,
     849,   855,   855,   852,   604,   820,   855,   846,   855,   846,
     879,   860,   684,   882,   863,   846,   855,   882,   855,   888,
     845,   866,   846,   860,   855,   846,   863,   846,   846,   860,
     879,   855,   863,   882,   855,   888,   855,   855,   840,   888,
     868,   888,   875,   848,   465,   846,   433,   858,  1016,   857,
     457,   888,   851,   849,   854,   852,   462,   863,   436,   888,
     890,   447,   865,   861,   652,  1021,   632,   603,   480,   879,
     486,   599,   482,  1049,  1029,  1066,   883,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1016,    -1,    -1,    -1,
      -1,  1021,    -1,    -1,    -1,    -1,  1021,    -1,  1016,  1029,
      -1,  1016,  1016,  1021,  1016,    -1,    -1,    -1,    -1,  1021,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1016,    -1,    -1,
      -1,  1016,  1021,    -1,    -1,    -1,  1021,    -1,    -1,  1016,
    1029,    -1,  1016,  1016,  1029,    -1,    -1,  1016,    -1,  1016,
      -1,    -1,  1021,    -1,    -1,    -1,    -1,  1016,    -1,  1016,
    1029,    -1,    -1,    -1,  1021,  1016,    -1,    -1,    -1,    -1,
    1021,    -1,  1016,    -1,    -1,  1016,    -1,  1016,  1016
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
      92,    93,    98,   108,   111,   118,   119,   122,   123,   143,
     144,   146,   206,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   226,   227,   228,   229,   244,   246,   252,
     254,   291,   300,   314,   324,   348,   352,   360,   386,   416,
     418,   420,   431,   433,   435,   458,   470,   471,   479,   481,
     509,   511,   519,   534,    15,    16,    19,    22,   206,   231,
     232,   235,   237,   240,   243,   416,   418,    65,    66,    67,
      80,    84,    85,    86,    94,    97,   105,   206,   217,   218,
     219,   220,   221,   222,   227,   228,   332,   333,   334,   336,
     338,   340,   342,   344,   346,   348,   351,   386,   404,   416,
     418,   420,   431,   433,   435,   455,    81,   206,   344,   346,
     386,   412,   413,   414,   416,   418,    93,    99,   100,   101,
     102,   103,   104,   106,   206,   386,   416,   418,   428,   429,
     430,   431,   433,   435,   437,   441,   443,   445,   447,   449,
     451,   453,   360,    34,    70,    72,    73,    76,    77,    78,
     206,   272,   370,   371,   372,   373,   374,   375,   376,   378,
     380,   382,   383,   385,   416,   418,    71,    74,    75,   206,
     272,   374,   380,   394,   395,   396,   397,   398,   400,   401,
     402,   403,   416,   418,   109,   110,   206,   308,   309,   310,
     312,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   206,   416,   418,   485,   486,   487,
     488,   490,   492,   493,   495,   496,   497,   500,   502,   503,
     504,   507,   509,   511,   532,   533,   534,    12,    13,   523,
     524,   525,   527,     6,     3,     4,     8,     3,   212,   529,
     514,   516,   518,     4,     3,     8,   520,   230,   247,     4,
       4,     4,   432,   434,   436,   245,   253,   255,     4,     4,
       4,     4,     4,     4,     4,   225,   325,   361,   387,   353,
     417,   419,   349,   292,   459,   421,   301,   315,     4,   472,
     480,   482,   510,   512,   535,     3,     8,   236,   238,   241,
       4,     3,     8,   337,   339,   341,   405,   335,   343,     4,
     347,   345,   456,     3,     8,   415,     3,     8,   454,   442,
     444,   448,   446,   452,   450,   438,     8,     3,     8,   377,
     273,     4,   381,   379,   384,     4,     8,     3,   399,     4,
       4,     8,     3,   311,   313,     3,     8,     4,   489,   491,
       4,   494,     4,     4,   498,   501,     4,     4,   505,   508,
       3,     8,     3,     8,   526,     4,     3,     8,   191,   191,
     171,     4,     4,     4,     4,     4,   210,     4,     4,     4,
     174,   174,   174,     4,     4,     4,     4,     4,     4,   172,
     172,   172,   174,   173,   173,   172,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   172,
       4,     4,     4,     4,     4,     4,   216,     4,     4,     4,
     174,   232,     4,     4,     4,     4,     4,     4,   172,     4,
       4,     4,   333,     4,   413,     4,     4,     4,     4,     4,
       4,     4,     4,   430,     4,     4,   172,     4,     4,     4,
     174,   372,     4,   174,   174,   396,     4,     4,   309,   174,
       4,     4,   172,     4,   172,   172,     4,     4,   174,   174,
       4,     4,   486,   533,     4,   172,   524,     4,     7,     7,
     191,   191,   191,     7,     7,     7,   171,   171,   171,     7,
       7,     5,   171,     5,     5,     5,     5,   193,   195,   171,
      88,    89,    90,    91,   350,     5,     5,     5,     5,     7,
       7,   195,     7,   171,   171,     5,     5,   202,    17,    18,
     239,    20,    21,   242,   171,   171,   171,     5,   171,   171,
     202,   171,     7,   171,   202,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   191,
     171,   171,   171,    18,   137,   499,   138,   139,   140,   141,
     142,   174,   506,   171,     5,   191,   215,   532,   523,   231,
      24,   248,   249,   250,    34,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,   206,   260,   261,   262,   265,   267,   269,   271,
     272,   274,   275,   276,   277,   278,   279,   280,   281,   283,
     285,   287,   289,   290,   260,     7,   256,   257,   258,     7,
     326,   327,   328,     7,   364,   365,   366,     7,   388,   389,
     390,     7,   354,   355,   356,    99,   100,   101,   102,   104,
     293,   294,   295,   296,   297,   298,   299,     7,   460,   461,
       7,   422,   423,   424,     7,   302,   303,   304,   112,   113,
     114,   115,   116,   117,   316,   317,   318,   319,   320,   321,
     322,   323,   120,   121,   206,   416,   418,   473,   474,   475,
     477,   485,     7,   536,   537,   203,     7,   406,   407,   408,
     107,   437,   439,   457,   256,     8,     8,     8,     8,   251,
       3,     8,   263,   266,   268,   270,     4,     4,     4,     4,
       4,   282,   284,   286,   288,     4,     4,     4,     4,     4,
       3,     8,     8,   259,     6,     3,   329,     6,     3,   367,
       6,     3,   391,     6,     3,   357,     6,     3,     3,     6,
     462,     3,     6,   425,     6,     3,   305,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   476,   478,     3,
       8,     8,   538,     3,     6,   171,   204,   205,   409,     6,
       3,   440,     8,     6,     4,   249,     4,     4,     4,     4,
     172,   174,   172,   174,   172,     4,     4,     4,     4,   172,
     172,   172,   172,   174,   261,   260,   258,   332,   328,   370,
     366,   394,   390,   206,   217,   218,   219,   220,   221,   222,
     227,   228,   272,   324,   342,   344,   346,   348,   358,   359,
     386,   416,   418,   431,   433,   435,   455,   356,   294,    95,
      96,   206,   272,   360,   386,   416,   418,   431,   433,   435,
     463,   464,   465,   466,   467,   469,   461,   428,   424,   308,
     304,   172,   172,   172,   172,   172,   172,   317,     4,     4,
     474,   147,   149,   150,   206,   272,   416,   418,   539,   540,
     541,   542,   544,   537,     6,     3,   412,   408,     4,   171,
      35,    36,    37,    38,   264,   171,   171,   171,   171,   171,
     171,   171,     8,     8,     8,     8,     3,     8,   468,     4,
       8,     3,     8,     8,   171,   171,   545,     4,   543,     3,
       8,   171,     8,   202,   359,     4,   174,   465,     4,   172,
       4,   540,   171,     5,   171,     7,   546,   547,   548,     3,
       6,   148,   151,   152,   153,   549,   550,   551,   553,   554,
     555,   547,   552,     4,     4,     4,     3,     8,     4,   174,
     172,   172,   550,   171
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
     216,   216,   216,   216,   217,   218,   219,   220,   221,   222,
     223,   225,   224,   226,   227,   228,   230,   229,   231,   231,
     232,   232,   232,   232,   232,   232,   232,   234,   233,   236,
     235,   238,   237,   239,   239,   241,   240,   242,   242,   243,
     245,   244,   247,   246,   248,   248,   249,   251,   250,   253,
     252,   255,   254,   256,   256,   257,   257,   259,   258,   260,
     260,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   263,   262,   264,   264,   264,   264,   266,   265,   268,
     267,   270,   269,   271,   273,   272,   274,   275,   276,   277,
     278,   279,   280,   282,   281,   284,   283,   286,   285,   288,
     287,   289,   290,   292,   291,   293,   293,   294,   294,   294,
     294,   294,   295,   296,   297,   298,   299,   301,   300,   302,
     302,   303,   303,   305,   304,   307,   306,   308,   308,   308,
     309,   309,   311,   310,   313,   312,   315,   314,   316,   316,
     317,   317,   317,   317,   317,   317,   318,   319,   320,   321,
     322,   323,   325,   324,   326,   326,   327,   327,   329,   328,
     331,   330,   332,   332,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   335,   334,   337,   336,   339,   338,   341,   340,   343,
     342,   345,   344,   347,   346,   349,   348,   350,   350,   350,
     350,   351,   353,   352,   354,   354,   355,   355,   357,   356,
     358,   358,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   361,   360,   363,   362,   364,   364,
     365,   365,   367,   366,   369,   368,   370,   370,   371,   371,
     372,   372,   372,   372,   372,   372,   372,   372,   372,   372,
     373,   374,   375,   377,   376,   379,   378,   381,   380,   382,
     384,   383,   385,   387,   386,   388,   388,   389,   389,   391,
     390,   393,   392,   394,   394,   395,   395,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   397,   399,   398,   400,
     401,   402,   403,   405,   404,   406,   406,   407,   407,   409,
     408,   411,   410,   412,   412,   413,   413,   413,   413,   413,
     413,   413,   415,   414,   417,   416,   419,   418,   421,   420,
     422,   422,   423,   423,   425,   424,   427,   426,   428,   428,
     429,   429,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   432,   431,   434,
     433,   436,   435,   438,   437,   440,   439,   442,   441,   444,
     443,   446,   445,   448,   447,   450,   449,   452,   451,   454,
     453,   456,   455,   457,   457,   459,   458,   460,   460,   462,
     461,   463,   463,   464,   464,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   466,   468,   467,   469,
     470,   472,   471,   473,   473,   474,   474,   474,   474,   474,
     476,   475,   478,   477,   480,   479,   482,   481,   484,   483,
     485,   485,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     487,   489,   488,   491,   490,   492,   494,   493,   495,   496,
     498,   497,   499,   499,   501,   500,   502,   503,   505,   504,
     506,   506,   506,   506,   506,   508,   507,   510,   509,   512,
     511,   514,   513,   516,   515,   518,   517,   520,   519,   522,
     521,   523,   523,   524,   524,   526,   525,   527,   529,   528,
     531,   530,   532,   532,   533,   535,   534,   536,   536,   538,
     537,   539,   539,   540,   540,   540,   540,   540,   540,   540,
     541,   543,   542,   545,   544,   546,   546,   548,   547,   549,
     549,   550,   550,   550,   550,   552,   551,   553,   554,   555
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     1,     3,     1,     0,     4,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
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
     479,   480,   481,   482,   485,   490,   495,   500,   505,   510,
     515,   520,   520,   528,   533,   538,   544,   544,   555,   556,
     559,   560,   561,   562,   563,   564,   565,   568,   568,   577,
     577,   587,   587,   594,   595,   598,   598,   605,   607,   611,
     617,   617,   629,   629,   639,   640,   642,   644,   644,   662,
     662,   674,   674,   684,   685,   688,   689,   692,   692,   702,
     703,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   723,   724,
     725,   728,   728,   735,   736,   737,   738,   741,   741,   749,
     749,   757,   757,   765,   770,   770,   778,   783,   788,   793,
     798,   803,   808,   813,   813,   821,   821,   829,   829,   837,
     837,   845,   850,   855,   855,   865,   866,   869,   870,   871,
     872,   873,   876,   881,   886,   891,   896,   901,   901,   911,
     912,   915,   916,   919,   919,   929,   929,   939,   940,   941,
     944,   945,   948,   948,   956,   956,   964,   964,   975,   976,
     979,   980,   981,   982,   983,   984,   987,   992,   997,  1002,
    1007,  1012,  1020,  1020,  1033,  1034,  1037,  1038,  1045,  1045,
    1071,  1071,  1082,  1083,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,  1112,
    1113,  1116,  1116,  1124,  1124,  1132,  1132,  1140,  1140,  1148,
    1148,  1156,  1156,  1164,  1164,  1174,  1174,  1181,  1182,  1183,
    1184,  1187,  1194,  1194,  1205,  1206,  1210,  1211,  1214,  1214,
    1222,  1223,  1226,  1227,  1228,  1229,  1230,  1231,  1232,  1233,
    1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,
    1244,  1245,  1246,  1247,  1254,  1254,  1267,  1267,  1276,  1277,
    1280,  1281,  1286,  1286,  1301,  1301,  1315,  1316,  1319,  1320,
    1323,  1324,  1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,
    1335,  1337,  1342,  1344,  1344,  1352,  1352,  1360,  1360,  1368,
    1370,  1370,  1378,  1387,  1387,  1399,  1400,  1405,  1406,  1411,
    1411,  1423,  1423,  1435,  1436,  1441,  1442,  1447,  1448,  1449,
    1450,  1451,  1452,  1453,  1454,  1455,  1458,  1460,  1460,  1468,
    1470,  1472,  1477,  1485,  1485,  1497,  1498,  1501,  1502,  1505,
    1505,  1515,  1515,  1525,  1526,  1529,  1530,  1531,  1532,  1533,
    1534,  1535,  1538,  1538,  1546,  1546,  1571,  1571,  1601,  1601,
    1611,  1612,  1615,  1616,  1619,  1619,  1628,  1628,  1637,  1638,
    1641,  1642,  1646,  1647,  1648,  1649,  1650,  1651,  1652,  1653,
    1654,  1655,  1656,  1657,  1658,  1659,  1660,  1663,  1663,  1671,
    1671,  1679,  1679,  1687,  1687,  1695,  1695,  1705,  1705,  1713,
    1713,  1721,  1721,  1729,  1729,  1737,  1737,  1745,  1745,  1753,
    1753,  1766,  1766,  1776,  1777,  1783,  1783,  1793,  1794,  1797,
    1797,  1807,  1808,  1811,  1812,  1815,  1816,  1817,  1818,  1819,
    1820,  1821,  1822,  1823,  1824,  1825,  1828,  1830,  1830,  1838,
    1847,  1854,  1854,  1864,  1865,  1868,  1869,  1870,  1871,  1872,
    1875,  1875,  1883,  1883,  1894,  1894,  1932,  1932,  1944,  1944,
    1954,  1955,  1958,  1959,  1960,  1961,  1962,  1963,  1964,  1965,
    1966,  1967,  1968,  1969,  1970,  1971,  1972,  1973,  1974,  1975,
    1978,  1983,  1983,  1991,  1991,  1999,  2004,  2004,  2012,  2017,
    2022,  2022,  2030,  2031,  2034,  2034,  2042,  2047,  2052,  2052,
    2060,  2063,  2066,  2069,  2072,  2078,  2078,  2086,  2086,  2094,
    2094,  2105,  2105,  2112,  2112,  2119,  2119,  2126,  2126,  2137,
    2137,  2147,  2148,  2152,  2153,  2156,  2156,  2166,  2176,  2176,
    2186,  2186,  2197,  2198,  2202,  2206,  2206,  2218,  2219,  2223,
    2223,  2231,  2232,  2235,  2236,  2237,  2238,  2239,  2240,  2241,
    2244,  2249,  2249,  2257,  2257,  2267,  2268,  2271,  2271,  2279,
    2280,  2283,  2284,  2285,  2286,  2289,  2289,  2297,  2302,  2307
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


#line 14 "dhcp4_parser.yy"
} } // isc::dhcp
#line 5062 "dhcp4_parser.cc"

#line 2312 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
