// A Bison parser, made by GNU Bison 3.3.1.

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
      case 220: // value
      case 224: // map_value
      case 266: // ddns_replace_client_name_value
      case 291: // socket_type
      case 294: // outbound_interface_value
      case 316: // db_type
      case 345: // on_fail_mode
      case 416: // hr_mode
      case 571: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 204: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 203: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 202: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 201: // "constant string"
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
      case 220: // value
      case 224: // map_value
      case 266: // ddns_replace_client_name_value
      case 291: // socket_type
      case 294: // outbound_interface_value
      case 316: // db_type
      case 345: // on_fail_mode
      case 416: // hr_mode
      case 571: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 204: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 203: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 202: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 201: // "constant string"
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
      case 220: // value
      case 224: // map_value
      case 266: // ddns_replace_client_name_value
      case 291: // socket_type
      case 294: // outbound_interface_value
      case 316: // db_type
      case 345: // on_fail_mode
      case 416: // hr_mode
      case 571: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 204: // "boolean"
        value.move< bool > (that.value);
        break;

      case 203: // "floating point"
        value.move< double > (that.value);
        break;

      case 202: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 201: // "constant string"
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
      case 201: // "constant string"
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 410 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 202: // "integer"
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 416 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 203: // "floating point"
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 204: // "boolean"
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 428 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 220: // value
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 224: // map_value
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 266: // ddns_replace_client_name_value
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 291: // socket_type
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 294: // outbound_interface_value
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 316: // db_type
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 345: // on_fail_mode
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 470 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 416: // hr_mode
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 476 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 571: // ncr_protocol_value
#line 285 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 482 "dhcp4_parser.cc" // lalr1.cc:676
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
      case 220: // value
      case 224: // map_value
      case 266: // ddns_replace_client_name_value
      case 291: // socket_type
      case 294: // outbound_interface_value
      case 316: // db_type
      case 345: // on_fail_mode
      case 416: // hr_mode
      case 571: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 204: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 203: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 202: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 201: // "constant string"
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
#line 294 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 295 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 296 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 297 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 298 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 299 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 300 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 301 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 302 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 303 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 304 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 305 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 306 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 314 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 29:
#line 315 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 316 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 31:
#line 317 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 318 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 319 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 320 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 323 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 328 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 333 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 339 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 346 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 351 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 43:
#line 359 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 930 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 44:
#line 362 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 938 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 47:
#line 370 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 48:
#line 374 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 49:
#line 381 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 50:
#line 383 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 392 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 396 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 991 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 55:
#line 407 "dhcp4_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1002 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 56:
#line 416 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1013 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 421 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 431 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1041 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 440 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 448 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1061 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 452 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1070 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 126:
#line 527 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 127:
#line 533 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 128:
#line 539 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 129:
#line 545 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1110 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 551 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 557 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1130 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 563 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1140 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 569 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1150 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 575 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 581 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 587 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 593 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 596 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 602 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 608 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1219 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 614 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 620 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 626 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 632 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1259 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 145:
#line 638 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1269 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 644 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 647 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1287 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 653 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1295 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 656 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1303 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 659 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1311 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 151:
#line 662 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1319 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 152:
#line 665 "dhcp4_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1328 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 153:
#line 671 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 154:
#line 674 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 155:
#line 680 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 156:
#line 683 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 157:
#line 689 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 158:
#line 695 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1386 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 159:
#line 701 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 160:
#line 704 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 161:
#line 710 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 162:
#line 713 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 163:
#line 719 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 164:
#line 725 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 731 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 737 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1464 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 167:
#line 743 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 168:
#line 749 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 768 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 772 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 777 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1517 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 783 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 182:
#line 788 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1535 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 791 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 796 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1550 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 797 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1556 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 800 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1565 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 803 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 808 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 810 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1590 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 814 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 821 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1612 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 827 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1623 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 834 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1635 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 840 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 850 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 853 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 1673 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 869 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 201:
#line 875 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1696 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 202:
#line 882 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 888 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1717 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 208:
#line 901 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 209:
#line 905 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 939 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 942 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 236:
#line 947 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1761 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 237:
#line 948 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1767 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 238:
#line 949 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1773 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 239:
#line 950 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1779 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 953 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 956 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 962 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 965 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 971 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1826 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 245:
#line 974 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 246:
#line 980 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 247:
#line 986 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 248:
#line 989 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 995 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1885 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1895 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1925 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 255:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1935 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 256:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1944 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 257:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 258:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 259:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 260:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1982 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 261:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 262:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 263:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 264:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2031 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2055 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 269:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2061 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 270:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2067 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 271:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 272:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2089 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 273:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2098 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 281:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2107 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 282:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2116 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 283:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2125 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 284:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2134 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 285:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 286:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 287:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2166 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 296:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 297:
#line 1185 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 298:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 299:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 300:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 305:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 306:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2237 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 307:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 308:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1254 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 318:
#line 1263 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2306 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 319:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2316 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 328:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 329:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2336 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 330:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2346 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 331:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 332:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 333:
#line 1317 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2376 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 334:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 335:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 340:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 341:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2433 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 342:
#line 1378 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2443 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 343:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2453 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 391:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 392:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 393:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2481 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 395:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 396:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2510 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 397:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 398:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2529 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 399:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 401:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2557 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 402:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2567 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 403:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 404:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2588 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 405:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2598 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 406:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2608 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 407:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 408:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 409:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2636 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 410:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2642 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 411:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2648 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 412:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2654 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 413:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2660 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 414:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 415:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2682 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 416:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2691 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 421:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2701 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 422:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2709 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 465:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2721 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 466:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2730 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 467:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2739 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 468:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 473:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2757 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 474:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2769 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 475:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2779 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 476:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2810 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2820 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2839 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1738 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2858 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1746 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2867 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 502:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2877 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 510:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 511:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 512:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2937 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 513:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2946 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 528:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2955 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 529:
#line 1842 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2965 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 532:
#line 1852 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2975 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 533:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2985 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 534:
#line 1867 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 535:
#line 1873 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3016 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 541:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3026 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 542:
#line 1898 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3036 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 543:
#line 1902 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3046 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3055 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1924 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3065 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 3100 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 557:
#line 1955 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3108 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 558:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 3137 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 559:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3149 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 560:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 565:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 566:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 567:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3187 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 568:
#line 2017 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3196 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 588:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3205 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2051 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3215 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2057 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3224 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3234 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3243 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2069 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3253 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2075 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3262 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2078 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3272 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2084 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3284 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2090 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3293 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2095 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3302 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2098 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3312 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2104 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3321 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2107 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2113 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3340 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3350 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2122 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3359 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2125 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3369 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2134 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3388 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3397 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2143 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3407 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2149 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3419 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2155 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3428 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2163 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3440 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2169 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3449 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2181 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3461 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3470 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 620:
#line 2196 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3480 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 621:
#line 2200 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 641:
#line 2232 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3499 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 642:
#line 2235 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3509 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 643:
#line 2241 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3519 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 644:
#line 2249 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3529 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 645:
#line 2257 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3541 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 646:
#line 2263 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3550 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 654:
#line 2279 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3559 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 655:
#line 2282 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3569 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 656:
#line 2288 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3578 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 657:
#line 2291 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3588 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 658:
#line 2300 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3600 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 659:
#line 2306 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3611 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 668:
#line 2325 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3621 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 669:
#line 2331 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3630 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 670:
#line 2334 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3640 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 671:
#line 2340 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3650 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 672:
#line 2346 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3659 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 673:
#line 2349 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3668 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 674:
#line 2356 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 675:
#line 2362 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3691 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 676:
#line 2369 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3701 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 677:
#line 2373 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3711 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 698:
#line 2403 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3721 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 699:
#line 2409 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3730 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 700:
#line 2412 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3740 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 701:
#line 2418 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3750 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 702:
#line 2424 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3759 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 703:
#line 2427 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3769 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 704:
#line 2433 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3779 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 705:
#line 2439 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3789 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 706:
#line 2445 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3798 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 707:
#line 2448 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3807 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 708:
#line 2454 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3813 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 709:
#line 2455 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3819 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 710:
#line 2458 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3828 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 711:
#line 2461 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3838 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 712:
#line 2468 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3847 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 713:
#line 2471 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3857 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 714:
#line 2478 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3867 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 715:
#line 2485 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3877 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 716:
#line 2492 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3886 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 717:
#line 2495 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3895 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 718:
#line 2501 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3904 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 719:
#line 2504 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3914 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 720:
#line 2511 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3923 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 721:
#line 2514 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3933 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 722:
#line 2521 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3942 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 723:
#line 2524 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3952 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 724:
#line 2533 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3964 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 725:
#line 2539 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3974 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 726:
#line 2545 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3984 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 727:
#line 2549 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3993 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 732:
#line 2564 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4005 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 733:
#line 2570 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4014 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 734:
#line 2575 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4024 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 735:
#line 2583 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4036 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 736:
#line 2589 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4045 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 739:
#line 2601 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4055 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 740:
#line 2605 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 4063 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 750:
#line 2622 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4073 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 751:
#line 2628 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4082 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 752:
#line 2631 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4092 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 753:
#line 2637 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4104 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 754:
#line 2643 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4113 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 757:
#line 2652 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4123 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 758:
#line 2656 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 4131 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 766:
#line 2671 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4140 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 767:
#line 2674 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4150 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 768:
#line 2680 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4160 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 769:
#line 2686 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 770:
#line 2692 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4180 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 771:
#line 2698 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4189 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 772:
#line 2701 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4199 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 773:
#line 2707 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4211 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 774:
#line 2713 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4220 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 779:
#line 2726 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4230 "dhcp4_parser.cc" // lalr1.cc:919
    break;


#line 4234 "dhcp4_parser.cc" // lalr1.cc:919
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


  const short Dhcp4Parser::yypact_ninf_ = -958;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     204,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,    31,    38,    48,    60,    74,    78,
      80,    90,    99,   114,   132,   157,   189,   200,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,    38,  -130,   107,   183,    67,   612,
     190,   247,    11,    89,   249,   -96,   418,   116,  -958,   129,
     177,   184,   213,   220,  -958,   221,  -958,  -958,  -958,   232,
     285,   291,  -958,  -958,  -958,  -958,  -958,  -958,   306,   317,
     327,   331,   334,   372,   385,   401,   402,   413,   414,  -958,
     415,   417,   419,   420,   421,  -958,  -958,  -958,   422,   423,
     425,  -958,  -958,  -958,   426,  -958,  -958,  -958,  -958,   430,
     431,   432,  -958,  -958,  -958,  -958,  -958,   433,  -958,  -958,
    -958,  -958,  -958,  -958,   434,  -958,  -958,   435,  -958,    56,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   437,  -958,    85,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,   439,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,    92,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,    93,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   266,   278,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   312,  -958,
    -958,   441,  -958,  -958,  -958,   442,  -958,  -958,   443,   446,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   449,   455,  -958,  -958,  -958,  -958,   454,
     461,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   100,  -958,  -958,  -958,   462,  -958,  -958,
     463,  -958,   465,   466,  -958,  -958,   467,   472,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   110,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   474,   128,  -958,  -958,  -958,  -958,    38,
      38,  -958,   264,   475,  -958,   477,   480,   481,   218,   284,
     288,   485,   491,   492,   493,   496,   498,   301,   302,   304,
     305,   307,   310,   322,   323,   328,   308,   311,   504,   313,
     321,   315,   325,   329,   523,   528,   530,   333,   335,   339,
     540,   543,   545,   348,   547,   551,   553,   557,   358,   361,
     362,   563,   565,   566,   567,   568,   384,   583,   584,   585,
     586,   587,   590,   391,   592,   593,  -958,   183,  -958,   594,
     595,   596,   397,    67,  -958,   598,   599,   600,   601,   602,
     603,   407,   604,   606,   608,   612,  -958,   610,   190,  -958,
     611,   613,   614,   616,   617,   618,   620,   621,  -958,   247,
    -958,   622,   623,   428,   624,   627,   628,   429,  -958,    89,
     630,   440,   445,  -958,   249,   631,   632,   -85,  -958,   447,
     633,   639,   444,   641,   450,   451,   651,   652,   453,   456,
     654,   655,   657,   658,   418,  -958,   663,   468,   116,  -958,
    -958,  -958,   664,   609,   662,   676,   677,  -958,  -958,  -958,
     470,   484,   495,   679,   693,   697,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   502,  -958,  -958,
    -958,  -958,  -958,  -120,   503,   509,  -958,  -958,  -958,   700,
     706,   707,  -958,   709,   714,   521,   236,  -958,  -958,  -958,
     718,   719,   723,   724,   725,  -958,   728,   729,   730,   731,
     538,   539,  -958,   726,   735,  -958,   738,    52,   142,  -958,
    -958,   544,   546,   548,   739,   549,   550,  -958,   738,   552,
     741,  -958,   554,  -958,   738,   555,   556,   558,   559,   560,
     561,   562,  -958,   564,   569,  -958,   570,   571,   572,  -958,
    -958,   573,  -958,  -958,  -958,   574,   714,  -958,  -958,   575,
     576,  -958,   577,  -958,  -958,    15,   589,  -958,  -958,  -120,
     578,   579,   580,  -958,   747,  -958,  -958,    38,   183,   116,
      67,   722,  -958,  -958,  -958,   108,   108,   757,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   759,   760,   761,
     762,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   -48,
     775,   776,   777,   242,    87,   121,   210,   418,  -958,  -958,
     778,  -143,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   781,  -958,  -958,  -958,  -958,   173,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   757,  -958,   138,
     181,   192,  -958,   235,  -958,  -958,  -958,  -958,  -958,  -958,
     750,   785,   786,   787,   788,  -958,  -958,  -958,  -958,   789,
     790,  -958,   791,   792,   793,   794,  -958,   270,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
     277,  -958,   795,   796,  -958,  -958,   797,   799,  -958,  -958,
     798,   802,  -958,  -958,   800,   804,  -958,  -958,   803,   805,
    -958,  -958,  -958,  -958,  -958,  -958,    36,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   104,  -958,  -958,   806,   807,  -958,
    -958,   808,   812,  -958,   813,   814,   815,   816,   817,   818,
     298,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   819,   820,
     821,  -958,   299,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   309,  -958,  -958,  -958,   822,  -958,
     823,  -958,  -958,  -958,   316,  -958,  -958,  -958,  -958,  -958,
     320,  -958,   214,  -958,   824,  -958,   324,  -958,  -958,   615,
    -958,   825,   826,  -958,  -958,  -958,  -958,   827,   828,  -958,
    -958,  -958,   829,   722,  -958,   832,   833,   834,   835,   638,
     607,   640,   626,   642,   837,   839,   841,   842,   645,   646,
     845,   648,   649,   650,   653,   108,  -958,  -958,   108,  -958,
     757,   612,  -958,   759,    89,  -958,   760,   249,  -958,   761,
    1228,  -958,   762,   -48,  -958,   115,   775,  -958,   247,  -958,
     776,   -96,  -958,   777,   656,   659,   660,   661,   665,   666,
     242,  -958,   667,   668,   670,    87,  -958,   848,   849,   121,
    -958,   669,   852,   672,   853,   210,  -958,  -958,    21,   778,
    -958,   671,  -143,  -958,  -958,   854,   856,   190,  -958,   781,
     860,  -958,  -958,   675,  -958,   330,   678,   680,   681,  -958,
    -958,  -958,  -958,  -958,   682,   683,   684,   685,  -958,  -958,
     332,  -958,  -958,  -958,  -958,  -958,   326,  -958,   346,  -958,
     857,  -958,   858,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   382,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   865,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,   869,   875,  -958,  -958,  -958,  -958,  -958,   872,
    -958,   404,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   686,   687,  -958,  -958,   688,  -958,
      38,  -958,  -958,   886,  -958,  -958,  -958,  -958,  -958,   405,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   690,   406,
    -958,   738,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  1228,  -958,   888,   689,  -958,   115,  -958,
    -958,  -958,  -958,  -958,  -958,   891,   694,   894,    21,  -958,
    -958,  -958,  -958,  -958,   698,  -958,  -958,   896,  -958,   701,
    -958,  -958,   900,  -958,  -958,   224,  -958,   -10,   900,  -958,
    -958,   905,   908,   913,  -958,   412,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   914,   732,   737,   749,   929,   -10,  -958,
     767,  -958,  -958,  -958,   768,  -958,  -958,  -958
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   178,     9,   342,    11,   542,    13,
     567,    15,   467,    17,   475,    19,   512,    21,   307,    23,
     676,    25,   726,    27,    45,    39,     0,     0,     0,     0,
       0,   569,     0,   477,   514,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   724,   167,   193,     0,
       0,     0,   588,   590,   592,   191,   200,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
       0,     0,     0,     0,     0,   146,   153,   155,     0,     0,
       0,   334,   465,   504,     0,   415,   555,   557,   408,     0,
       0,     0,   272,   616,   559,   299,   318,     0,   286,   645,
     658,   674,   159,   161,     0,   735,   773,     0,   125,     0,
      62,    64,    65,    66,    67,    68,   102,   103,   104,   105,
     106,    69,    97,   124,    86,    87,    88,   110,   111,   112,
     113,   114,   115,   116,   117,   108,   109,   118,   119,   120,
     122,    72,    73,    94,    74,    75,    76,   121,    80,    81,
      70,    99,   100,   101,    98,    71,    78,    79,    92,    93,
      95,    89,    90,    91,    77,    82,    83,    84,    85,    96,
     107,   123,   180,   182,   186,     0,   177,     0,   169,   171,
     172,   173,   174,   175,   176,   393,   395,   397,   534,   391,
     399,     0,   403,   401,   612,   390,   346,   347,   348,   349,
     350,   374,   375,   376,   377,   378,   364,   365,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,     0,
     344,   353,   369,   370,   371,   354,   356,   357,   360,   361,
     362,   359,   355,   351,   352,   372,   373,   358,   366,   367,
     368,   363,   553,   552,   548,   549,   547,     0,   544,   546,
     550,   551,   610,   598,   600,   604,   602,   608,   606,   594,
     587,   581,   585,   586,     0,   570,   571,   582,   583,   584,
     578,   573,   579,   575,   576,   577,   580,   574,     0,   494,
     247,     0,   498,   496,   501,     0,   490,   491,     0,   478,
     479,   481,   493,   482,   483,   484,   500,   485,   486,   487,
     488,   489,   528,     0,     0,   526,   527,   530,   531,     0,
     515,   516,   518,   519,   520,   521,   522,   523,   524,   525,
     314,   316,   311,     0,   309,   312,   313,     0,   712,   699,
       0,   702,     0,     0,   706,   710,     0,     0,   716,   718,
     720,   722,   697,   695,   696,     0,   678,   680,   681,   682,
     683,   684,   685,   686,   687,   692,   688,   689,   690,   691,
     693,   694,   732,     0,     0,   728,   730,   731,    44,     0,
       0,    37,     0,     0,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,     0,    61,     0,
       0,     0,     0,     0,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   343,     0,     0,   543,
       0,     0,     0,     0,     0,     0,     0,     0,   568,     0,
     468,     0,     0,     0,     0,     0,     0,     0,   476,     0,
       0,     0,     0,   513,     0,     0,     0,     0,   308,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   677,     0,     0,     0,   727,
      48,    41,     0,     0,     0,     0,     0,   140,   141,   142,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     0,   164,   165,
     143,   144,   145,     0,     0,     0,   157,   158,   163,     0,
       0,     0,   139,     0,     0,     0,     0,   405,   406,   407,
       0,     0,     0,     0,     0,   644,     0,     0,     0,     0,
       0,     0,   166,     0,     0,    63,     0,     0,     0,   190,
     170,     0,     0,     0,     0,     0,     0,   414,     0,     0,
       0,   345,     0,   545,     0,     0,     0,     0,     0,     0,
       0,     0,   572,     0,     0,   492,     0,     0,     0,   503,
     480,     0,   532,   533,   517,     0,     0,   310,   698,     0,
       0,   701,     0,   704,   705,     0,     0,   714,   715,     0,
       0,     0,     0,   679,     0,   734,   729,     0,     0,     0,
       0,     0,   589,   591,   593,     0,     0,   204,   138,   148,
     149,   150,   151,   152,   147,   154,   156,   336,   469,   506,
     417,    38,   556,   558,   410,   411,   412,   413,   409,     0,
       0,   561,   301,     0,     0,     0,     0,     0,   160,   162,
       0,     0,    49,   181,   184,   185,   183,   188,   189,   187,
     394,   396,   398,   536,   392,   400,   404,   402,     0,   554,
     611,   599,   601,   605,   603,   609,   607,   595,   495,   248,
     499,   497,   502,   529,   315,   317,   713,   700,   703,   708,
     709,   707,   711,   717,   719,   721,   723,   204,    42,     0,
       0,     0,   198,     0,   195,   197,   234,   240,   242,   244,
       0,     0,     0,     0,     0,   256,   258,   260,   262,     0,
       0,   266,     0,     0,     0,     0,   233,     0,   210,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   226,
     227,   228,   222,   229,   230,   231,   223,   224,   225,   232,
       0,   208,     0,   205,   206,   340,     0,   337,   338,   473,
       0,   470,   471,   510,     0,   507,   508,   421,     0,   418,
     419,   281,   282,   283,   284,   285,     0,   274,   276,   277,
     278,   279,   280,   620,     0,   618,   565,     0,   562,   563,
     305,     0,   302,   303,     0,     0,     0,     0,     0,     0,
       0,   320,   322,   323,   324,   325,   326,   327,     0,     0,
       0,   295,     0,   288,   290,   291,   292,   293,   294,   654,
     656,   653,   651,   652,     0,   647,   649,   650,     0,   669,
       0,   672,   665,   666,     0,   660,   662,   663,   664,   667,
       0,   739,     0,   737,     0,   778,     0,   775,   777,    51,
     540,     0,   537,   538,   596,   614,   615,     0,     0,    59,
     725,   168,     0,     0,   194,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,   201,     0,   203,
       0,     0,   335,     0,   477,   466,     0,   514,   505,     0,
       0,   416,     0,     0,   273,   622,     0,   617,   569,   560,
       0,     0,   300,     0,     0,     0,     0,     0,     0,     0,
       0,   319,     0,     0,     0,     0,   287,     0,     0,     0,
     646,     0,     0,     0,     0,     0,   659,   675,     0,     0,
     736,     0,     0,   774,    53,     0,    52,     0,   535,     0,
       0,   613,   733,     0,   196,     0,     0,     0,     0,   246,
     249,   250,   251,   252,     0,     0,     0,     0,   264,   265,
       0,   253,   254,   255,   271,   211,     0,   207,     0,   339,
       0,   472,     0,   509,   464,   443,   444,   445,   428,   429,
     448,   449,   450,   451,   452,   431,   432,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   425,   426,
     427,   441,   442,   438,   439,   440,   437,     0,   423,   430,
     446,   447,   433,   434,   435,   436,   420,   275,   641,     0,
     636,   637,   638,   639,   640,   629,   630,   634,   635,   631,
     632,   633,     0,   623,   624,   626,   627,   628,   619,     0,
     564,     0,   304,   328,   329,   330,   331,   332,   333,   321,
     296,   297,   298,   289,     0,     0,   648,   668,     0,   671,
       0,   661,   753,     0,   751,   749,   743,   747,   748,     0,
     741,   745,   746,   744,   738,   779,   776,    50,     0,     0,
     539,     0,   199,   236,   237,   238,   239,   235,   241,   243,
     245,   257,   259,   261,   263,   268,   269,   270,   267,   209,
     341,   474,   511,     0,   422,     0,     0,   621,     0,   566,
     306,   655,   657,   670,   673,     0,     0,     0,     0,   740,
      54,   541,   597,   424,     0,   643,   625,     0,   750,     0,
     742,   642,     0,   752,   757,     0,   755,     0,     0,   754,
     766,     0,     0,     0,   771,     0,   759,   761,   762,   763,
     764,   765,   756,     0,     0,     0,     0,     0,     0,   758,
       0,   768,   769,   770,     0,   760,   767,   772
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   -54,  -958,  -566,  -958,   144,
    -958,  -958,  -958,  -958,  -958,  -958,  -607,  -958,  -958,  -958,
     -67,  -958,  -958,  -958,  -958,  -958,  -958,   154,   499,     4,
      10,    23,   -40,   -23,   -12,    22,    25,    29,    33,  -958,
    -958,  -958,  -958,  -958,    35,    40,    43,    45,    46,    47,
    -958,   292,    50,  -958,    51,  -958,    53,    57,    58,  -958,
      61,  -958,    63,  -958,  -958,  -958,  -958,  -958,   297,   489,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,    55,  -958,  -958,  -958,
    -958,  -958,  -958,   222,  -958,    42,  -958,  -674,    77,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   -33,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,    71,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,    41,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,    54,  -958,  -958,  -958,    62,   514,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,    59,  -958,  -958,  -958,  -958,
    -958,  -958,  -957,  -958,  -958,  -958,    79,  -958,  -958,  -958,
      84,   581,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -955,  -958,   -65,  -958,    70,  -958,    64,    65,    68,    69,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,    75,  -958,  -958,
    -137,   -46,  -958,  -958,  -958,  -958,  -958,    82,  -958,  -958,
    -958,    86,  -958,   532,  -958,   -63,  -958,  -958,  -958,  -958,
    -958,   -42,  -958,  -958,  -958,  -958,  -958,   -35,  -958,  -958,
    -958,    83,  -958,  -958,  -958,    88,  -958,   529,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,    37,
    -958,  -958,  -958,    44,   582,  -958,  -958,   -51,  -958,    -8,
    -958,   -39,  -958,  -958,  -958,    91,  -958,  -958,  -958,    76,
    -958,   588,   -55,  -958,   -15,  -958,     3,  -958,   319,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -946,  -958,  -958,  -958,
    -958,  -958,    94,  -958,  -958,  -958,  -129,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,    66,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,    72,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   341,   516,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   383,   515,  -958,  -958,  -958,
    -958,  -958,  -958,    73,  -958,  -958,  -134,  -958,  -958,  -958,
    -958,  -958,  -958,  -152,  -958,  -958,  -171,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,    81,  -958
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   702,
      82,    83,    39,    64,    79,    80,   723,   919,  1015,  1016,
     796,    41,    66,    85,   413,    43,    67,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   438,   163,   164,   165,   166,   167,   168,   169,   170,
     444,   694,   171,   445,   172,   446,   173,   174,   175,   471,
     176,   472,   177,   178,   179,   180,   181,   416,   217,   218,
      45,    68,   219,   479,   220,   480,   726,   221,   481,   729,
     222,   182,   424,   183,   417,   773,   774,   775,   932,   184,
     425,   185,   426,   822,   823,   824,   958,   797,   798,   799,
     935,  1167,   800,   936,   801,   937,   802,   938,   803,   804,
     512,   805,   806,   807,   808,   809,   810,   811,   812,   944,
     813,   945,   814,   946,   815,   947,   816,   817,   818,   950,
    1178,   819,   186,   461,   846,   847,   848,   849,   850,   851,
     852,   187,   467,   882,   883,   884,   885,   886,   188,   464,
     861,   862,   863,   981,    59,    75,   363,   364,   365,   525,
     366,   526,   189,   465,   870,   871,   872,   873,   874,   875,
     876,   877,   190,   450,   826,   827,   828,   961,    47,    69,
     259,   260,   261,   489,   262,   485,   263,   486,   264,   487,
     265,   490,   266,   493,   267,   492,   191,   192,   193,   194,
     457,   708,   272,   195,   454,   838,   839,   840,   970,  1087,
    1088,   196,   451,    53,    72,   830,   831,   832,   964,    55,
      73,   328,   329,   330,   331,   332,   333,   334,   511,   335,
     515,   336,   514,   337,   338,   516,   339,   197,   452,   834,
     835,   836,   967,    57,    74,   349,   350,   351,   352,   353,
     520,   354,   355,   356,   357,   274,   488,   921,   922,   923,
    1017,    49,    70,   287,   288,   289,   497,   198,   455,   199,
     456,   200,   463,   857,   858,   859,   978,    51,    71,   304,
     305,   306,   201,   421,   202,   422,   203,   423,   310,   507,
     926,  1020,   311,   501,   312,   502,   313,   504,   314,   503,
     315,   506,   316,   505,   317,   500,   281,   494,   927,   204,
     462,   854,   855,   975,  1112,  1113,  1114,  1115,  1116,  1185,
    1117,   205,   206,   468,   894,   895,   896,   997,   897,   998,
     207,   469,   904,   905,   906,   907,  1002,   908,   909,  1004,
     208,   470,    61,    76,   385,   386,   387,   388,   531,   389,
     390,   533,   391,   392,   393,   536,   761,   394,   537,   395,
     530,   396,   397,   398,   540,   399,   541,   400,   542,   401,
     543,   209,   415,    63,    77,   404,   405,   406,   546,   407,
     210,   474,   912,   913,  1008,  1149,  1150,  1151,  1152,  1197,
    1153,  1195,  1215,  1216,  1217,  1225,  1226,  1227,  1233,  1228,
    1229,  1230,  1231,  1237,   211,   475,   916,   917,   918
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
     148,   216,   235,   283,   300,   284,   326,   345,   362,   382,
      78,   347,   820,  1079,   278,  1080,   307,   223,   275,   290,
     302,   736,   340,   358,  1095,   383,   318,   740,   701,   239,
     277,    28,   348,   759,   273,   286,   301,   360,   361,   973,
     327,   346,   974,    29,   914,    30,   240,    31,   360,   361,
     689,   690,   691,   692,   279,    40,   308,   241,   147,   477,
     224,   276,   291,   303,   478,   341,   359,    42,   384,   724,
     725,    81,   280,   236,   309,   841,   842,   843,   844,   237,
     845,    44,   212,   213,   693,    46,   214,    48,   483,   215,
     701,   242,   238,   484,   243,   495,   498,    50,   244,   122,
     496,   499,   245,   527,   246,   147,    52,   976,   528,   247,
     977,   320,   248,   544,   249,   250,   251,    84,   545,   252,
     253,    54,   254,   319,   126,   127,   255,   256,   402,   403,
     257,   548,   258,   268,   269,   408,   549,   270,   271,    56,
     285,   477,   776,    92,    93,    94,   929,   777,   778,   779,
     780,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   727,   728,    58,   792,   793,   794,   795,  1220,
     126,   127,  1221,  1222,  1223,  1224,    98,    99,   100,   320,
     409,   321,   322,   760,   548,   323,   324,   325,   410,   930,
     126,   127,   126,   127,    86,   483,    60,    87,   320,  1142,
     931,  1143,  1144,   122,   123,   320,    88,    62,    89,    90,
      91,    92,    93,    94,    95,    96,    97,  1009,   126,   127,
    1010,   411,   147,   412,   126,   127,  1079,  1218,  1080,   414,
    1219,   878,   879,   880,  1098,  1099,   418,  1095,   933,    32,
      33,    34,    35,   934,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   147,   889,
     890,   122,   123,   955,   508,    92,    93,    94,   956,   123,
     955,   509,   124,   125,  1046,   957,   126,   127,   147,   419,
     147,   128,   282,   126,   127,   420,   129,   130,   131,   132,
     133,   990,   995,   299,   924,   134,   991,   996,   232,   147,
     427,   233,   999,   126,   127,   135,   147,  1000,   136,  1005,
     510,   428,   147,   544,  1006,   137,   138,  1012,  1007,   955,
     139,   429,  1013,   140,  1179,   430,   123,   141,   431,   320,
     342,   321,   322,   343,   344,   704,   705,   706,   707,   495,
     126,   127,   126,   127,  1180,   550,   551,   142,   143,   144,
     145,   898,   899,   900,   292,  1163,  1164,  1165,  1166,   146,
     293,   294,   295,   296,   297,   298,   432,   299,   864,   865,
     866,   867,   868,   869,   147,  1183,  1175,  1176,  1177,   433,
    1184,   147,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   434,   435,   527,  1198,   498,
     148,   901,  1190,  1199,  1201,  1238,   216,   436,   437,   439,
    1239,   440,   557,   441,   442,   443,   447,   448,   235,   449,
     453,   283,   223,   284,   458,   459,   460,   466,   473,   476,
     278,   482,   300,   491,   275,   513,   517,   290,   147,   519,
     147,   518,   326,   521,   307,   239,   277,   345,   302,   522,
     273,   347,   523,   286,   524,   552,   529,   532,   340,   534,
     535,   538,   240,   358,   301,   224,   539,   382,   547,   553,
     279,   554,   348,   241,   555,   556,   327,   276,   558,   560,
     291,   346,   559,   383,   308,   561,   562,   563,   280,   236,
     564,   303,   565,   566,   567,   237,   568,   569,   577,   570,
     575,   341,   309,   576,   571,   578,   359,   242,   238,   580,
     243,   126,   127,   579,   244,   572,   573,   583,   245,   581,
     246,   574,   584,   582,   585,   247,   384,   586,   248,   587,
     249,   250,   251,   588,   589,   252,   253,   590,   254,   591,
     592,   593,   255,   256,  1202,   594,   257,   595,   258,   268,
     269,   596,   597,   270,   271,   598,   599,   600,   285,   601,
     602,   603,   604,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   605,   606,   607,   608,
     609,   610,   380,   381,   611,   612,   613,   614,   616,   617,
     618,   619,   621,   622,   623,   624,   625,   626,   628,   627,
     629,   148,   630,   216,   632,   634,   678,   635,   636,   147,
     637,   638,   639,   768,   640,   641,   643,   644,   646,   223,
     645,   647,   648,   649,   651,   655,   656,   659,    90,    91,
      92,    93,    94,   660,   652,   662,   661,   881,   891,   653,
     382,   658,   663,   664,   915,   665,   666,   667,   669,   670,
     668,   671,   672,   887,   892,   902,   383,   674,   677,   679,
     675,   682,   224,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   680,   681,   683,   685,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   684,   225,   226,   227,
     686,   123,   687,   688,   695,   697,   888,   893,   903,   384,
     696,   698,   699,   228,   700,   126,   127,   229,   230,   231,
     128,    30,   703,   709,   710,   129,   130,   131,   711,   712,
     232,   720,   713,   233,   134,   714,   715,   716,   717,   718,
     719,   234,   721,   722,   733,   730,   772,   731,   738,   732,
     734,   735,   767,   737,   939,   739,   741,   742,   762,   743,
     744,   745,   746,   747,   821,   748,   825,   829,   833,   837,
     749,   750,   751,   752,   753,   754,   756,   757,   758,   764,
     765,   766,   853,   856,   860,   911,   142,   143,   920,   940,
     941,   942,   943,   948,   949,   951,   952,   953,   954,   960,
     755,   959,   963,   962,   965,   966,   968,   969,   972,   971,
     980,  1030,   979,   147,   982,   983,  1014,   984,   985,   986,
     987,   988,   989,   992,   993,   994,  1001,  1003,  1011,  1019,
    1032,  1018,   769,  1023,  1022,  1021,  1025,  1026,  1027,  1028,
    1029,  1034,  1031,  1035,  1033,  1036,  1037,  1038,  1039,  1040,
    1041,  1042,  1134,  1135,  1043,  1044,  1138,  1140,  1123,  1158,
    1157,  1124,  1125,  1126,  1161,  1181,  1182,  1127,  1128,  1186,
    1131,  1130,  1132,  1137,  1139,  1155,  1162,  1187,  1188,  1168,
    1189,  1169,  1170,  1171,  1172,  1173,  1174,  1191,  1192,  1193,
    1196,  1200,  1204,  1205,   235,  1207,  1208,   326,  1209,  1211,
     345,  1212,  1213,  1054,   347,  1081,   278,  1214,  1100,  1234,
     275,   300,  1235,   340,   362,  1092,   358,  1236,  1240,  1090,
    1109,   239,   277,   307,  1107,   348,   273,   302,   881,  1105,
    1058,   327,   891,  1244,   346,  1089,  1241,  1078,   240,  1242,
    1106,  1145,  1104,   301,   887,   915,   279,  1059,   892,   241,
     283,  1243,   284,   276,   902,  1093,   341,  1147,  1060,   359,
    1110,   763,  1091,   308,   280,   236,   290,  1108,  1246,  1247,
     303,   237,   620,  1094,  1055,  1146,   615,   771,  1111,  1101,
    1056,   309,   286,   242,   238,  1102,   243,   888,  1024,   928,
     244,   893,  1061,  1057,   245,  1062,   246,   903,  1103,  1063,
    1148,   247,  1047,  1064,   248,  1065,   249,   250,   251,   291,
    1066,   252,   253,  1067,   254,  1068,  1069,  1070,   255,   256,
    1071,  1072,   257,  1073,   258,   268,   269,  1074,  1075,   270,
     271,  1076,  1045,  1077,  1083,  1084,  1133,  1122,  1085,  1086,
    1082,   657,  1049,  1121,  1097,  1048,  1203,  1096,  1051,  1129,
    1050,   650,  1053,   654,  1119,  1052,  1160,   925,   910,  1206,
     673,  1159,   770,   676,  1210,  1136,  1232,  1245,     0,     0,
    1118,  1120,     0,     0,     0,     0,   631,  1141,     0,     0,
     633,     0,  1154,     0,     0,     0,  1194,   285,     0,     0,
       0,     0,     0,  1156,     0,     0,     0,   642,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1054,     0,  1081,     0,
       0,  1100,     0,     0,     0,     0,     0,     0,  1092,     0,
       0,  1145,  1090,  1109,     0,     0,     0,  1107,     0,     0,
       0,     0,  1105,  1058,     0,     0,     0,  1147,  1089,     0,
    1078,     0,     0,  1106,     0,  1104,     0,     0,     0,     0,
    1059,     0,     0,     0,     0,  1146,     0,     0,  1093,     0,
       0,  1060,     0,  1110,     0,  1091,     0,     0,     0,     0,
    1108,     0,     0,     0,     0,     0,  1094,  1055,     0,     0,
    1148,  1111,  1101,  1056,     0,     0,     0,     0,  1102,     0,
       0,     0,     0,     0,     0,  1061,  1057,     0,  1062,     0,
       0,  1103,  1063,     0,     0,     0,  1064,     0,  1065,     0,
       0,     0,     0,  1066,     0,     0,  1067,     0,  1068,  1069,
    1070,     0,     0,  1071,  1072,     0,  1073,     0,     0,     0,
    1074,  1075,     0,     0,  1076,     0,  1077,  1083,  1084,     0,
       0,  1085,  1086,  1082,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,   123,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,     0,   230,     0,   128,     0,     0,     0,
       0,   129,   130,   131,     0,     0,   232,     0,     0,   233,
       0,     0,     0,     0,     0,     0,     0,   234,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   147
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   686,   970,    69,   970,    71,    68,    69,    70,
      71,   628,    73,    74,   970,    76,    72,   634,   594,    69,
      69,     0,    74,    18,    69,    70,    71,   133,   134,     3,
      73,    74,     6,     5,   187,     7,    69,     9,   133,   134,
     170,   171,   172,   173,    69,     7,    71,    69,   201,     3,
      68,    69,    70,    71,     8,    73,    74,     7,    76,    17,
      18,   201,    69,    69,    71,   123,   124,   125,   126,    69,
     128,     7,    15,    16,   204,     7,    19,     7,     3,    22,
     656,    69,    69,     8,    69,     3,     3,     7,    69,    88,
       8,     8,    69,     3,    69,   201,     7,     3,     8,    69,
       6,    90,    69,     3,    69,    69,    69,    10,     8,    69,
      69,     7,    69,    34,   103,   104,    69,    69,    12,    13,
      69,     3,    69,    69,    69,     6,     8,    69,    69,     7,
      70,     3,    34,    28,    29,    30,     8,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    20,    21,     7,    57,    58,    59,    60,   179,
     103,   104,   182,   183,   184,   185,    61,    62,    63,    90,
       3,    92,    93,   168,     3,    96,    97,    98,     4,     8,
     103,   104,   103,   104,    11,     3,     7,    14,    90,   178,
       8,   180,   181,    88,    89,    90,    23,     7,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     3,   103,   104,
       6,     8,   201,     3,   103,   104,  1183,     3,  1183,     8,
       6,   144,   145,   146,   119,   120,     4,  1183,     3,   201,
     202,   203,   204,     8,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   201,   148,
     149,    88,    89,     3,     8,    28,    29,    30,     8,    89,
       3,     3,    99,   100,   958,     8,   103,   104,   201,     4,
     201,   108,   102,   103,   104,     4,   113,   114,   115,   116,
     117,     3,     3,   130,   131,   122,     8,     8,   118,   201,
       4,   121,     3,   103,   104,   132,   201,     8,   135,     3,
       8,     4,   201,     3,     8,   142,   143,     3,     8,     3,
     147,     4,     8,   150,     8,     4,    89,   154,     4,    90,
      91,    92,    93,    94,    95,   109,   110,   111,   112,     3,
     103,   104,   103,   104,     8,   409,   410,   174,   175,   176,
     177,   151,   152,   153,   117,    35,    36,    37,    38,   186,
     123,   124,   125,   126,   127,   128,     4,   130,   136,   137,
     138,   139,   140,   141,   201,     3,    54,    55,    56,     4,
       8,   201,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,     4,     4,     3,     3,     3,
     477,   201,     8,     8,     8,     3,   483,     4,     4,     4,
       8,     4,   204,     4,     4,     4,     4,     4,   495,     4,
       4,   498,   483,   498,     4,     4,     4,     4,     4,     4,
     495,     4,   509,     4,   495,     4,     4,   498,   201,     3,
     201,     8,   519,     4,   509,   495,   495,   524,   509,     4,
     495,   524,     8,   498,     3,   201,     4,     4,   519,     4,
       4,     4,   495,   524,   509,   483,     4,   544,     4,     4,
     495,     4,   524,   495,     4,     4,   519,   495,   204,     4,
     498,   524,   204,   544,   509,     4,     4,     4,   495,   495,
       4,   509,     4,   202,   202,   495,   202,   202,     4,   202,
     202,   519,   509,   202,   204,   202,   524,   495,   495,   204,
     495,   103,   104,   202,   495,   203,   203,     4,   495,   204,
     495,   203,     4,   204,     4,   495,   544,   204,   495,   204,
     495,   495,   495,   204,     4,   495,   495,     4,   495,     4,
     202,     4,   495,   495,  1161,     4,   495,     4,   495,   495,
     495,     4,   204,   495,   495,   204,   204,     4,   498,     4,
       4,     4,     4,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   202,     4,     4,     4,
       4,     4,   174,   175,     4,   204,     4,     4,     4,     4,
       4,   204,     4,     4,     4,     4,     4,     4,     4,   202,
       4,   678,     4,   680,     4,     4,     7,     4,     4,   201,
       4,     4,     4,   677,     4,     4,     4,     4,     4,   680,
     202,     4,     4,   204,     4,     4,     4,     4,    26,    27,
      28,    29,    30,     4,   204,     4,   202,   714,   715,   204,
     717,   204,   202,   202,   721,     4,     4,   204,     4,     4,
     204,     4,     4,   714,   715,   716,   717,     4,     4,     7,
     202,   201,   680,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     7,     7,   201,     7,    75,    76,    77,
      78,    79,    80,    81,    82,    83,   201,    85,    86,    87,
       7,    89,     5,   201,   201,     5,   714,   715,   716,   717,
     201,     5,     5,   101,     5,   103,   104,   105,   106,   107,
     108,     7,   201,     5,     5,   113,   114,   115,     5,     5,
     118,     5,     7,   121,   122,     7,     7,     7,     7,   201,
     201,   129,     7,     5,     5,   201,    24,   201,     7,   201,
     201,   201,     5,   201,     4,   201,   201,   201,   169,   201,
     201,   201,   201,   201,     7,   201,     7,     7,     7,     7,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,     7,     7,     7,     7,   174,   175,     7,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     656,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   204,     6,   201,     6,     3,   201,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     204,     6,   678,     4,     6,     8,     4,     4,     4,     4,
     202,     4,   202,     4,   202,     4,     4,   202,   202,     4,
     202,   202,     4,     4,   204,   202,     4,     4,   202,     3,
       6,   202,   202,   202,     4,     8,     8,   202,   202,     4,
     202,   204,   202,   204,   202,   204,   201,     8,     3,   201,
       8,   201,   201,   201,   201,   201,   201,   201,   201,   201,
       4,   201,     4,   204,   961,     4,   202,   964,     4,   201,
     967,     5,   201,   970,   967,   970,   961,     7,   975,     4,
     961,   978,     4,   964,   981,   970,   967,     4,     4,   970,
     975,   961,   961,   978,   975,   967,   961,   978,   995,   975,
     970,   964,   999,     4,   967,   970,   204,   970,   961,   202,
     975,  1008,   975,   978,   995,  1012,   961,   970,   999,   961,
    1017,   202,  1017,   961,  1005,   970,   964,  1008,   970,   967,
     975,   669,   970,   978,   961,   961,  1017,   975,   201,   201,
     978,   961,   483,   970,   970,  1008,   477,   680,   975,   975,
     970,   978,  1017,   961,   961,   975,   961,   995,   933,   767,
     961,   999,   970,   970,   961,   970,   961,  1005,   975,   970,
    1008,   961,   960,   970,   961,   970,   961,   961,   961,  1017,
     970,   961,   961,   970,   961,   970,   970,   970,   961,   961,
     970,   970,   961,   970,   961,   961,   961,   970,   970,   961,
     961,   970,   955,   970,   970,   970,   995,   983,   970,   970,
     970,   527,   963,   981,   973,   961,  1183,   972,   966,   990,
     964,   519,   969,   524,   978,   967,  1019,   738,   717,  1188,
     544,  1017,   679,   548,  1198,   999,  1218,  1238,    -1,    -1,
     976,   980,    -1,    -1,    -1,    -1,   495,  1005,    -1,    -1,
     498,    -1,  1009,    -1,    -1,    -1,  1140,  1017,    -1,    -1,
      -1,    -1,    -1,  1012,    -1,    -1,    -1,   509,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1183,    -1,  1183,    -1,
      -1,  1188,    -1,    -1,    -1,    -1,    -1,    -1,  1183,    -1,
      -1,  1198,  1183,  1188,    -1,    -1,    -1,  1188,    -1,    -1,
      -1,    -1,  1188,  1183,    -1,    -1,    -1,  1198,  1183,    -1,
    1183,    -1,    -1,  1188,    -1,  1188,    -1,    -1,    -1,    -1,
    1183,    -1,    -1,    -1,    -1,  1198,    -1,    -1,  1183,    -1,
      -1,  1183,    -1,  1188,    -1,  1183,    -1,    -1,    -1,    -1,
    1188,    -1,    -1,    -1,    -1,    -1,  1183,  1183,    -1,    -1,
    1198,  1188,  1188,  1183,    -1,    -1,    -1,    -1,  1188,    -1,
      -1,    -1,    -1,    -1,    -1,  1183,  1183,    -1,  1183,    -1,
      -1,  1188,  1183,    -1,    -1,    -1,  1183,    -1,  1183,    -1,
      -1,    -1,    -1,  1183,    -1,    -1,  1183,    -1,  1183,  1183,
    1183,    -1,    -1,  1183,  1183,    -1,  1183,    -1,    -1,    -1,
    1183,  1183,    -1,    -1,  1183,    -1,  1183,  1183,  1183,    -1,
      -1,  1183,  1183,  1183,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,
      -1,   113,   114,   115,    -1,    -1,   118,    -1,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   201
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,     0,     5,
       7,     9,   201,   202,   203,   204,   220,   221,   222,   227,
       7,   236,     7,   240,     7,   285,     7,   393,     7,   476,
       7,   492,     7,   428,     7,   434,     7,   458,     7,   369,
       7,   557,     7,   588,   228,   223,   237,   241,   286,   394,
     477,   493,   429,   435,   459,   370,   558,   589,   220,   229,
     230,   201,   225,   226,    10,   238,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    88,    89,    99,   100,   103,   104,   108,   113,
     114,   115,   116,   117,   122,   132,   135,   142,   143,   147,
     150,   154,   174,   175,   176,   177,   186,   201,   235,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   257,   258,   259,   260,   261,   262,   263,
     264,   267,   269,   271,   272,   273,   275,   277,   278,   279,
     280,   281,   296,   298,   304,   306,   347,   356,   363,   377,
     387,   411,   412,   413,   414,   418,   426,   452,   482,   484,
     486,   497,   499,   501,   524,   536,   537,   545,   555,   586,
     595,   619,    15,    16,    19,    22,   235,   283,   284,   287,
     289,   292,   295,   482,   484,    85,    86,    87,   101,   105,
     106,   107,   118,   121,   129,   235,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   259,   260,   261,   262,
     263,   264,   267,   269,   271,   272,   273,   275,   277,   395,
     396,   397,   399,   401,   403,   405,   407,   409,   411,   412,
     413,   414,   417,   452,   470,   482,   484,   486,   497,   499,
     501,   521,   102,   235,   407,   409,   452,   478,   479,   480,
     482,   484,   117,   123,   124,   125,   126,   127,   128,   130,
     235,   452,   482,   484,   494,   495,   496,   497,   499,   501,
     503,   507,   509,   511,   513,   515,   517,   519,   426,    34,
      90,    92,    93,    96,    97,    98,   235,   324,   436,   437,
     438,   439,   440,   441,   442,   444,   446,   448,   449,   451,
     482,   484,    91,    94,    95,   235,   324,   440,   446,   460,
     461,   462,   463,   464,   466,   467,   468,   469,   482,   484,
     133,   134,   235,   371,   372,   373,   375,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     174,   175,   235,   482,   484,   559,   560,   561,   562,   564,
     565,   567,   568,   569,   572,   574,   576,   577,   578,   580,
     582,   584,    12,    13,   590,   591,   592,   594,     6,     3,
       4,     8,     3,   239,     8,   587,   282,   299,     4,     4,
       4,   498,   500,   502,   297,   305,   307,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   256,     4,
       4,     4,     4,     4,   265,   268,   270,     4,     4,     4,
     388,   427,   453,     4,   419,   483,   485,   415,     4,     4,
       4,   348,   525,   487,   364,   378,     4,   357,   538,   546,
     556,   274,   276,     4,   596,   620,     4,     3,     8,   288,
     290,   293,     4,     3,     8,   400,   402,   404,   471,   398,
     406,     4,   410,   408,   522,     3,     8,   481,     3,     8,
     520,   508,   510,   514,   512,   518,   516,   504,     8,     3,
       8,   443,   325,     4,   447,   445,   450,     4,     8,     3,
     465,     4,     4,     8,     3,   374,   376,     3,     8,     4,
     575,   563,     4,   566,     4,     4,   570,   573,     4,     4,
     579,   581,   583,   585,     3,     8,   593,     4,     3,     8,
     220,   220,   201,     4,     4,     4,     4,   204,   204,   204,
       4,     4,     4,     4,     4,     4,   202,   202,   202,   202,
     202,   204,   203,   203,   203,   202,   202,     4,   202,   202,
     204,   204,   204,     4,     4,     4,   204,   204,   204,     4,
       4,     4,   202,     4,     4,     4,     4,   204,   204,   204,
       4,     4,     4,     4,     4,   202,     4,     4,     4,     4,
       4,     4,   204,     4,     4,   243,     4,     4,     4,   204,
     284,     4,     4,     4,     4,     4,     4,   202,     4,     4,
       4,   396,     4,   479,     4,     4,     4,     4,     4,     4,
       4,     4,   496,     4,     4,   202,     4,     4,     4,   204,
     438,     4,   204,   204,   462,     4,     4,   372,   204,     4,
       4,   202,     4,   202,   202,     4,     4,   204,   204,     4,
       4,     4,     4,   560,     4,   202,   591,     4,     7,     7,
       7,     7,   201,   201,   201,     7,     7,     5,   201,   170,
     171,   172,   173,   204,   266,   201,   201,     5,     5,     5,
       5,   222,   224,   201,   109,   110,   111,   112,   416,     5,
       5,     5,     5,     7,     7,     7,     7,     7,   201,   201,
       5,     7,     5,   231,    17,    18,   291,    20,    21,   294,
     201,   201,   201,     5,   201,   201,   231,   201,     7,   201,
     231,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   224,   201,   201,   201,    18,
     168,   571,   169,   266,   201,   201,   201,     5,   220,   242,
     590,   283,    24,   300,   301,   302,    34,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    57,    58,    59,    60,   235,   312,   313,   314,
     317,   319,   321,   323,   324,   326,   327,   328,   329,   330,
     331,   332,   333,   335,   337,   339,   341,   342,   343,   346,
     312,     7,   308,   309,   310,     7,   389,   390,   391,     7,
     430,   431,   432,     7,   454,   455,   456,     7,   420,   421,
     422,   123,   124,   125,   126,   128,   349,   350,   351,   352,
     353,   354,   355,     7,   526,   527,     7,   488,   489,   490,
       7,   365,   366,   367,   136,   137,   138,   139,   140,   141,
     379,   380,   381,   382,   383,   384,   385,   386,   144,   145,
     146,   235,   358,   359,   360,   361,   362,   482,   484,   148,
     149,   235,   482,   484,   539,   540,   541,   543,   151,   152,
     153,   201,   482,   484,   547,   548,   549,   550,   552,   553,
     559,     7,   597,   598,   187,   235,   621,   622,   623,   232,
       7,   472,   473,   474,   131,   503,   505,   523,   308,     8,
       8,     8,   303,     3,     8,   315,   318,   320,   322,     4,
       4,     4,     4,     4,   334,   336,   338,   340,     4,     4,
     344,     4,     4,     4,     4,     3,     8,     8,   311,     6,
       3,   392,     6,     3,   433,     6,     3,   457,     6,     3,
     423,     6,     3,     3,     6,   528,     3,     6,   491,     6,
       3,   368,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,     4,     4,     4,     3,     8,   542,   544,     3,
       8,     4,   551,     4,   554,     3,     8,     8,   599,     3,
       6,     4,     3,     8,   201,   233,   234,   475,     6,     3,
     506,     8,     6,     4,   301,     4,     4,     4,     4,   202,
     204,   202,   204,   202,     4,     4,     4,     4,   202,   202,
       4,   202,   202,   204,   202,   313,   312,   310,   395,   391,
     436,   432,   460,   456,   235,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   259,   260,   261,   262,   263,
     264,   267,   269,   271,   272,   273,   275,   277,   324,   387,
     405,   407,   409,   411,   412,   413,   414,   424,   425,   452,
     482,   484,   497,   499,   501,   521,   422,   350,   119,   120,
     235,   244,   245,   246,   324,   426,   452,   482,   484,   497,
     499,   501,   529,   530,   531,   532,   533,   535,   527,   494,
     490,   371,   367,   202,   202,   202,   202,   202,   202,   380,
     204,   202,   202,   359,     4,     4,   540,   204,     4,   202,
       4,   548,   178,   180,   181,   235,   324,   482,   484,   600,
     601,   602,   603,   605,   598,   204,   622,     6,     3,   478,
     474,     4,   201,    35,    36,    37,    38,   316,   201,   201,
     201,   201,   201,   201,   201,    54,    55,    56,   345,     8,
       8,     8,     8,     3,     8,   534,     4,     8,     3,     8,
       8,   201,   201,   201,   220,   606,     4,   604,     3,     8,
     201,     8,   231,   425,     4,   204,   531,     4,   202,     4,
     601,   201,     5,   201,     7,   607,   608,   609,     3,     6,
     179,   182,   183,   184,   185,   610,   611,   612,   614,   615,
     616,   617,   608,   613,     4,     4,     4,   618,     3,     8,
       4,   204,   202,   202,     4,   611,   201,   201
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   205,   207,   206,   208,   206,   209,   206,   210,   206,
     211,   206,   212,   206,   213,   206,   214,   206,   215,   206,
     216,   206,   217,   206,   218,   206,   219,   206,   220,   220,
     220,   220,   220,   220,   220,   221,   223,   222,   224,   225,
     225,   226,   226,   228,   227,   229,   229,   230,   230,   232,
     231,   233,   233,   234,   234,   235,   237,   236,   239,   238,
     241,   240,   242,   242,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   256,   255,   257,
     258,   259,   260,   261,   262,   263,   265,   264,   266,   266,
     266,   266,   266,   268,   267,   270,   269,   271,   272,   274,
     273,   276,   275,   277,   278,   279,   280,   282,   281,   283,
     283,   284,   284,   284,   284,   284,   284,   284,   286,   285,
     288,   287,   290,   289,   291,   291,   293,   292,   294,   294,
     295,   297,   296,   299,   298,   300,   300,   301,   303,   302,
     305,   304,   307,   306,   308,   308,   309,   309,   311,   310,
     312,   312,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   315,   314,   316,   316,   316,   316,
     318,   317,   320,   319,   322,   321,   323,   325,   324,   326,
     327,   328,   329,   330,   331,   332,   334,   333,   336,   335,
     338,   337,   340,   339,   341,   342,   344,   343,   345,   345,
     345,   346,   348,   347,   349,   349,   350,   350,   350,   350,
     350,   351,   352,   353,   354,   355,   357,   356,   358,   358,
     359,   359,   359,   359,   359,   359,   360,   361,   362,   364,
     363,   365,   365,   366,   366,   368,   367,   370,   369,   371,
     371,   371,   372,   372,   374,   373,   376,   375,   378,   377,
     379,   379,   380,   380,   380,   380,   380,   380,   381,   382,
     383,   384,   385,   386,   388,   387,   389,   389,   390,   390,
     392,   391,   394,   393,   395,   395,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   398,   397,   400,   399,   402,   401,   404,   403,   406,
     405,   408,   407,   410,   409,   411,   412,   413,   415,   414,
     416,   416,   416,   416,   417,   419,   418,   420,   420,   421,
     421,   423,   422,   424,   424,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   427,   426,   429,   428,   430,
     430,   431,   431,   433,   432,   435,   434,   436,   436,   437,
     437,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   439,   440,   441,   443,   442,   445,   444,   447,   446,
     448,   450,   449,   451,   453,   452,   454,   454,   455,   455,
     457,   456,   459,   458,   460,   460,   461,   461,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   463,   465,   464,
     466,   467,   468,   469,   471,   470,   472,   472,   473,   473,
     475,   474,   477,   476,   478,   478,   479,   479,   479,   479,
     479,   479,   479,   481,   480,   483,   482,   485,   484,   487,
     486,   488,   488,   489,   489,   491,   490,   493,   492,   494,
     494,   495,   495,   496,   496,   496,   496,   496,   496,   496,
     496,   496,   496,   496,   496,   496,   496,   496,   498,   497,
     500,   499,   502,   501,   504,   503,   506,   505,   508,   507,
     510,   509,   512,   511,   514,   513,   516,   515,   518,   517,
     520,   519,   522,   521,   523,   523,   525,   524,   526,   526,
     528,   527,   529,   529,   530,   530,   531,   531,   531,   531,
     531,   531,   531,   531,   531,   531,   531,   531,   531,   531,
     532,   534,   533,   535,   536,   538,   537,   539,   539,   540,
     540,   540,   540,   540,   542,   541,   544,   543,   546,   545,
     547,   547,   548,   548,   548,   548,   548,   548,   549,   551,
     550,   552,   554,   553,   556,   555,   558,   557,   559,   559,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   561,   563,
     562,   564,   566,   565,   567,   568,   570,   569,   571,   571,
     573,   572,   575,   574,   576,   577,   579,   578,   581,   580,
     583,   582,   585,   584,   587,   586,   589,   588,   590,   590,
     591,   591,   593,   592,   594,   596,   595,   597,   597,   599,
     598,   600,   600,   601,   601,   601,   601,   601,   601,   601,
     602,   604,   603,   606,   605,   607,   607,   609,   608,   610,
     610,   611,   611,   611,   611,   611,   613,   612,   614,   615,
     616,   618,   617,   620,   619,   621,   621,   622,   622,   623
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     1,     3,     1,     1,     3
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
  "\"reconnect-wait-time\"", "\"on-fail\"", "\"stop-retry-exit\"",
  "\"serve-retry-exit\"", "\"serve-retry-continue\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"max-row-errors\"", "\"valid-lifetime\"", "\"min-valid-lifetime\"",
  "\"max-valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
  "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"store-extended-info\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"parked-packet-limit\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"id\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"global\"",
  "\"all\"", "\"reservations-global\"", "\"reservations-in-subnet\"",
  "\"reservations-out-of-pool\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"only-if-required\"", "\"client-class\"", "\"reservations\"",
  "\"duid\"", "\"hw-address\"", "\"circuit-id\"", "\"client-id\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"ip-addresses\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"ip-reservations-unique\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_object", "$@18", "sub_dhcp4", "$@19", "global_params",
  "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "parked_packet_limit", "echo_client_id", "match_client_id",
  "authoritative", "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@21",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@22",
  "ddns_qualifying_suffix", "$@23", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "hostname_char_set", "$@24",
  "hostname_char_replacement", "$@25", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "ip_reservations_unique", "interfaces_config", "$@26",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@27", "interfaces_list", "$@28", "dhcp_socket_type", "$@29",
  "socket_type", "outbound_interface", "$@30", "outbound_interface_value",
  "re_detect", "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@42", "keyspace",
  "$@43", "consistency", "$@44", "serial_consistency", "$@45",
  "max_reconnect_tries", "reconnect_wait_time", "on_fail", "$@46",
  "on_fail_mode", "max_row_errors", "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@48", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@49", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@50",
  "sub_hooks_library", "$@51", "hooks_params", "hooks_param", "library",
  "$@52", "parameters", "$@53", "expired_leases_processing", "$@54",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@55",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@56",
  "sub_subnet4", "$@57", "subnet4_params", "subnet4_param", "subnet",
  "$@58", "subnet_4o6_interface", "$@59", "subnet_4o6_interface_id",
  "$@60", "subnet_4o6_subnet", "$@61", "interface", "$@62", "client_class",
  "$@63", "require_client_classes", "$@64", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@65", "hr_mode", "id", "shared_networks", "$@66",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@67", "shared_network_params", "shared_network_param",
  "option_def_list", "$@68", "sub_option_def_list", "$@69",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@70", "sub_option_def", "$@71",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@72",
  "option_def_record_types", "$@73", "space", "$@74", "option_def_space",
  "option_def_encapsulate", "$@75", "option_def_array", "option_data_list",
  "$@76", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@77", "sub_option_data", "$@78",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@79",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@80", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@81", "sub_pool4", "$@82",
  "pool_params", "pool_param", "pool_entry", "$@83", "user_context",
  "$@84", "comment", "$@85", "reservations", "$@86", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@87", "sub_reservation",
  "$@88", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@89", "server_hostname", "$@90",
  "boot_file_name", "$@91", "ip_address", "$@92", "ip_addresses", "$@93",
  "duid", "$@94", "hw_address", "$@95", "client_id_value", "$@96",
  "circuit_id_value", "$@97", "flex_id_value", "$@98", "hostname", "$@99",
  "reservation_client_classes", "$@100", "relay", "$@101", "relay_map",
  "client_classes", "$@102", "client_classes_list", "client_class_entry",
  "$@103", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@104",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@105",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@106", "control_socket_name", "$@107", "dhcp_queue_control", "$@108",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@109", "capacity", "arbitrary_map_entry", "$@110",
  "dhcp_ddns", "$@111", "sub_dhcp_ddns", "$@112", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@113", "server_port",
  "sender_ip", "$@114", "sender_port", "max_queue_size", "ncr_protocol",
  "$@115", "ncr_protocol_value", "ncr_format", "$@116",
  "dep_qualifying_suffix", "$@117", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@118",
  "dep_generated_prefix", "$@119", "dep_hostname_char_set", "$@120",
  "dep_hostname_char_replacement", "$@121", "config_control", "$@122",
  "sub_config_control", "$@123", "config_control_params",
  "config_control_param", "config_databases", "$@124",
  "config_fetch_wait_time", "loggers", "$@125", "loggers_entries",
  "logger_entry", "$@126", "logger_params", "logger_param", "debuglevel",
  "severity", "$@127", "output_options_list", "$@128",
  "output_options_list_content", "output_entry", "$@129",
  "output_params_list", "output_params", "output", "$@130", "flush",
  "maxsize", "maxver", "pattern", "$@131", "compatibility", "$@132",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   294,   294,   294,   295,   295,   296,   296,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   314,   315,
     316,   317,   318,   319,   320,   323,   328,   328,   339,   342,
     343,   346,   351,   359,   359,   366,   367,   370,   374,   381,
     381,   388,   389,   392,   396,   407,   416,   416,   431,   431,
     448,   448,   457,   458,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   527,   533,   539,   545,
     551,   557,   563,   569,   575,   581,   587,   593,   593,   602,
     608,   614,   620,   626,   632,   638,   644,   644,   653,   656,
     659,   662,   665,   671,   671,   680,   680,   689,   695,   701,
     701,   710,   710,   719,   725,   731,   737,   743,   743,   755,
     756,   759,   760,   761,   762,   763,   764,   765,   768,   768,
     777,   777,   788,   788,   796,   797,   800,   800,   808,   810,
     814,   821,   821,   834,   834,   845,   846,   848,   850,   850,
     869,   869,   882,   882,   893,   894,   897,   898,   901,   901,
     911,   912,   915,   916,   917,   918,   919,   920,   921,   922,
     923,   924,   925,   926,   927,   928,   929,   930,   931,   932,
     933,   934,   935,   936,   939,   939,   947,   948,   949,   950,
     953,   953,   962,   962,   971,   971,   980,   986,   986,   995,
    1001,  1007,  1013,  1019,  1025,  1031,  1037,  1037,  1046,  1046,
    1055,  1055,  1064,  1064,  1073,  1079,  1085,  1085,  1093,  1094,
    1095,  1098,  1105,  1105,  1116,  1117,  1120,  1121,  1122,  1123,
    1124,  1127,  1132,  1137,  1142,  1147,  1154,  1154,  1167,  1168,
    1171,  1172,  1173,  1174,  1175,  1176,  1179,  1185,  1191,  1197,
    1197,  1208,  1209,  1212,  1213,  1216,  1216,  1226,  1226,  1236,
    1237,  1238,  1241,  1242,  1245,  1245,  1254,  1254,  1263,  1263,
    1275,  1276,  1279,  1280,  1281,  1282,  1283,  1284,  1287,  1293,
    1299,  1305,  1311,  1317,  1326,  1326,  1340,  1341,  1344,  1345,
    1352,  1352,  1378,  1378,  1389,  1390,  1394,  1395,  1396,  1397,
    1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,  1407,
    1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,
    1418,  1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,  1427,
    1428,  1429,  1430,  1431,  1432,  1433,  1434,  1435,  1436,  1437,
    1438,  1441,  1441,  1450,  1450,  1459,  1459,  1468,  1468,  1477,
    1477,  1486,  1486,  1495,  1495,  1506,  1512,  1518,  1524,  1524,
    1532,  1533,  1534,  1535,  1538,  1546,  1546,  1558,  1559,  1563,
    1564,  1567,  1567,  1575,  1576,  1579,  1580,  1581,  1582,  1583,
    1584,  1585,  1586,  1587,  1588,  1589,  1590,  1591,  1592,  1593,
    1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,  1603,
    1604,  1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,
    1614,  1615,  1616,  1617,  1618,  1625,  1625,  1639,  1639,  1648,
    1649,  1652,  1653,  1658,  1658,  1673,  1673,  1687,  1688,  1691,
    1692,  1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,
    1704,  1707,  1709,  1715,  1717,  1717,  1726,  1726,  1735,  1735,
    1744,  1746,  1746,  1755,  1765,  1765,  1778,  1779,  1784,  1785,
    1790,  1790,  1802,  1802,  1814,  1815,  1820,  1821,  1826,  1827,
    1828,  1829,  1830,  1831,  1832,  1833,  1834,  1837,  1839,  1839,
    1848,  1850,  1852,  1858,  1867,  1867,  1880,  1881,  1884,  1885,
    1888,  1888,  1898,  1898,  1908,  1909,  1912,  1913,  1914,  1915,
    1916,  1917,  1918,  1921,  1921,  1930,  1930,  1955,  1955,  1985,
    1985,  1996,  1997,  2000,  2001,  2004,  2004,  2013,  2013,  2022,
    2023,  2026,  2027,  2031,  2032,  2033,  2034,  2035,  2036,  2037,
    2038,  2039,  2040,  2041,  2042,  2043,  2044,  2045,  2048,  2048,
    2057,  2057,  2066,  2066,  2075,  2075,  2084,  2084,  2095,  2095,
    2104,  2104,  2113,  2113,  2122,  2122,  2131,  2131,  2140,  2140,
    2149,  2149,  2163,  2163,  2174,  2175,  2181,  2181,  2192,  2193,
    2196,  2196,  2206,  2207,  2210,  2211,  2214,  2215,  2216,  2217,
    2218,  2219,  2220,  2221,  2222,  2223,  2224,  2225,  2226,  2227,
    2230,  2232,  2232,  2241,  2249,  2257,  2257,  2268,  2269,  2272,
    2273,  2274,  2275,  2276,  2279,  2279,  2288,  2288,  2300,  2300,
    2313,  2314,  2317,  2318,  2319,  2320,  2321,  2322,  2325,  2331,
    2331,  2340,  2346,  2346,  2356,  2356,  2369,  2369,  2379,  2380,
    2383,  2384,  2385,  2386,  2387,  2388,  2389,  2390,  2391,  2392,
    2393,  2394,  2395,  2396,  2397,  2398,  2399,  2400,  2403,  2409,
    2409,  2418,  2424,  2424,  2433,  2439,  2445,  2445,  2454,  2455,
    2458,  2458,  2468,  2468,  2478,  2485,  2492,  2492,  2501,  2501,
    2511,  2511,  2521,  2521,  2533,  2533,  2545,  2545,  2555,  2556,
    2560,  2561,  2564,  2564,  2575,  2583,  2583,  2596,  2597,  2601,
    2601,  2609,  2610,  2613,  2614,  2615,  2616,  2617,  2618,  2619,
    2622,  2628,  2628,  2637,  2637,  2648,  2649,  2652,  2652,  2660,
    2661,  2664,  2665,  2666,  2667,  2668,  2671,  2671,  2680,  2686,
    2692,  2698,  2698,  2707,  2707,  2718,  2719,  2722,  2723,  2726
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
#line 5747 "dhcp4_parser.cc" // lalr1.cc:1242
#line 2732 "dhcp4_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
