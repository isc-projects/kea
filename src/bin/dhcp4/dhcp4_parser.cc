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
      case 209: // value
      case 213: // map_value
      case 254: // ddns_replace_client_name_value
      case 273: // socket_type
      case 276: // outbound_interface_value
      case 298: // db_type
      case 394: // hr_mode
      case 549: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 192: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 191: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 190: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 189: // "constant string"
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
      case 209: // value
      case 213: // map_value
      case 254: // ddns_replace_client_name_value
      case 273: // socket_type
      case 276: // outbound_interface_value
      case 298: // db_type
      case 394: // hr_mode
      case 549: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 192: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 191: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 190: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 189: // "constant string"
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
      case 209: // value
      case 213: // map_value
      case 254: // ddns_replace_client_name_value
      case 273: // socket_type
      case 276: // outbound_interface_value
      case 298: // db_type
      case 394: // hr_mode
      case 549: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 192: // "boolean"
        value.move< bool > (that.value);
        break;

      case 191: // "floating point"
        value.move< double > (that.value);
        break;

      case 190: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 189: // "constant string"
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
      case 189: // "constant string"
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 407 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 190: // "integer"
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 191: // "floating point"
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 419 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 192: // "boolean"
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 425 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 209: // value
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 431 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 213: // map_value
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 254: // ddns_replace_client_name_value
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 273: // socket_type
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 276: // outbound_interface_value
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 298: // db_type
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 394: // hr_mode
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 549: // ncr_protocol_value
#line 271 "dhcp4_parser.yy" // lalr1.cc:676
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
      case 209: // value
      case 213: // map_value
      case 254: // ddns_replace_client_name_value
      case 273: // socket_type
      case 276: // outbound_interface_value
      case 298: // db_type
      case 394: // hr_mode
      case 549: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 192: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 191: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 190: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 189: // "constant string"
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
#line 280 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 281 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 282 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 752 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 283 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 758 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 284 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET4; }
#line 764 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 285 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 286 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 776 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 287 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 782 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 288 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 788 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 289 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 794 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 290 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 800 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 291 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 806 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 292 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 812 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 293 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 818 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 301 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 824 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 31:
#line 302 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 830 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 303 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 304 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 842 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 305 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 848 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 306 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 854 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 307 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 860 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 310 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 869 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 315 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 320 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 890 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 326 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 43:
#line 333 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 44:
#line 337 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 915 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 344 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 924 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 347 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 932 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 49:
#line 355 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 941 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 50:
#line 359 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 950 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 366 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 958 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 368 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 55:
#line 377 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 976 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 56:
#line 381 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 985 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 392 "dhcp4_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 996 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 402 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1007 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 407 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 431 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 438 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 70:
#line 446 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 71:
#line 450 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 122:
#line 511 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 123:
#line 516 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 124:
#line 521 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 125:
#line 526 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 126:
#line 531 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1107 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 127:
#line 536 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 128:
#line 541 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 129:
#line 546 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 551 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 556 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 558 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 564 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 569 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1179 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 574 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1188 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 579 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1197 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 584 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1206 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 589 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 594 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1223 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 596 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1232 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 602 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1240 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 605 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1248 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 608 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1256 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 611 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 145:
#line 614 "dhcp4_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1273 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 620 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1281 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 622 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 628 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1299 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 630 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 636 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 151:
#line 638 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 152:
#line 644 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 153:
#line 646 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1345 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 154:
#line 652 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 155:
#line 657 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 676 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1376 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 680 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1385 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 167:
#line 685 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 168:
#line 690 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 169:
#line 695 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 170:
#line 697 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1422 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 171:
#line 702 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1428 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 172:
#line 703 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1434 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 173:
#line 706 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 174:
#line 708 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 175:
#line 713 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 176:
#line 715 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1467 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 177:
#line 719 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 725 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 730 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 737 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1509 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 742 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 752 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 754 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 1546 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 770 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1557 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 775 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 782 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 787 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 800 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 804 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1608 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 225:
#line 842 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 226:
#line 844 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 227:
#line 849 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1631 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 228:
#line 850 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1637 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 229:
#line 851 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1643 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 852 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1649 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 855 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 857 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 863 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 865 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 871 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 236:
#line 873 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1703 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 237:
#line 879 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1712 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 238:
#line 884 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 239:
#line 886 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1730 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 892 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 897 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1748 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 902 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 907 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1766 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 912 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 245:
#line 917 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 246:
#line 922 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 247:
#line 927 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 248:
#line 929 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1811 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 935 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 937 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1829 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 943 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 945 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 951 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 953 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 255:
#line 959 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 256:
#line 964 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 257:
#line 969 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 258:
#line 974 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl", n);
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 259:
#line 979 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1909 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 260:
#line 981 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-ca", sslca);
    ctx.leave();
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 261:
#line 987 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1927 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 262:
#line 989 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslc(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-cert", sslc);
    ctx.leave();
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 263:
#line 995 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 264:
#line 997 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslk(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-key", sslk);
    ctx.leave();
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-password", sslp);
    ctx.leave();
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1984 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1016 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1993 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 276:
#line 1032 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2002 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 277:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 278:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 279:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2029 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 280:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2038 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 281:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 282:
#line 1062 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2058 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 287:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 288:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 289:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2088 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 290:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2098 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 296:
#line 1104 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2106 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 297:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2116 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 298:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 299:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 300:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2144 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 301:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2154 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2163 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 312:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 313:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2199 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2219 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2228 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 322:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2238 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 323:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2264 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 324:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2274 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 325:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 365:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2292 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 366:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 367:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2310 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 368:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2320 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 369:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2328 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 371:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 373:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 374:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2374 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 375:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2382 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 376:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2392 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 377:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 378:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2412 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 379:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2420 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 380:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2429 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 381:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2435 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 382:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2441 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 383:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2447 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 384:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2453 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 385:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 386:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2473 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 387:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 392:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 393:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 428:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1435 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2529 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 436:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2547 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2559 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2569 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2581 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2590 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 457:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2598 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 458:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 459:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2616 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 460:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2626 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 461:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2644 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 464:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2652 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 465:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2662 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 466:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2671 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 467:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2682 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 468:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2691 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 473:
#line 1587 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2701 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 474:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2710 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 475:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 476:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2737 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2765 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2776 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2785 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2805 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2815 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2825 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 516:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2843 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 518:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2851 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 519:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2878 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 520:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2886 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 521:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2915 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 522:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2926 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 523:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 528:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2945 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 529:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2954 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 530:
#line 1804 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2964 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 531:
#line 1808 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2981 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1841 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2991 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1847 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2999 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3009 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1855 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3027 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 557:
#line 1863 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3035 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 558:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3045 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 559:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 560:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3065 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 561:
#line 1881 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 562:
#line 1883 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 563:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3091 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 564:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3101 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 565:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3109 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 566:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3119 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 567:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3127 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 568:
#line 1907 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 569:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3145 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 570:
#line 1915 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3155 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 571:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 572:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 573:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 574:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3193 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 575:
#line 1942 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3204 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 576:
#line 1947 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 579:
#line 1959 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3224 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3233 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3243 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3253 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3261 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3271 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3280 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3289 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3300 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2035 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3309 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2051 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3317 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2053 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3327 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2059 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3335 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3345 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2070 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 619:
#line 2075 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3367 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2094 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3376 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2099 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3384 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 630:
#line 2101 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3394 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 631:
#line 2107 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3403 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 632:
#line 2112 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3411 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 633:
#line 2114 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3420 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2121 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3431 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 635:
#line 2126 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3442 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2133 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2137 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3462 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 658:
#line 2167 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3471 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 659:
#line 2172 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 660:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3489 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 661:
#line 2180 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3498 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 662:
#line 2185 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3506 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 663:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3516 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2193 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3525 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2198 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3534 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 666:
#line 2203 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3542 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 667:
#line 2205 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3551 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 668:
#line 2211 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3557 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 669:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3563 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 670:
#line 2215 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3571 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 671:
#line 2217 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3581 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 672:
#line 2224 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3589 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 673:
#line 2226 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3599 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 674:
#line 2233 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3608 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 675:
#line 2239 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3617 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 676:
#line 2245 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3625 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 677:
#line 2247 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3634 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 678:
#line 2253 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3642 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 679:
#line 2255 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3652 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 680:
#line 2262 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3660 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 681:
#line 2264 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3670 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 682:
#line 2271 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3678 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 683:
#line 2273 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3688 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 684:
#line 2282 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3696 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 685:
#line 2284 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3705 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 686:
#line 2289 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3713 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 687:
#line 2291 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3722 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 688:
#line 2296 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3730 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 689:
#line 2298 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3739 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 690:
#line 2303 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3750 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 691:
#line 2308 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3760 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 692:
#line 2314 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 693:
#line 2318 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3779 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 698:
#line 2333 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3790 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 699:
#line 2338 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3799 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 700:
#line 2343 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3808 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 701:
#line 2353 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3819 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 702:
#line 2358 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3828 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 703:
#line 2363 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3838 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 704:
#line 2367 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3846 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 708:
#line 2383 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3857 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 709:
#line 2388 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3866 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 712:
#line 2400 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3876 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 713:
#line 2404 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3884 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 723:
#line 2421 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3893 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 724:
#line 2426 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3901 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 725:
#line 2428 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3911 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 726:
#line 2434 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3922 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 727:
#line 2439 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3931 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 730:
#line 2448 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3941 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 731:
#line 2452 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3949 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 739:
#line 2467 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3957 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 740:
#line 2469 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3967 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 741:
#line 2475 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3976 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 742:
#line 2480 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3985 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 743:
#line 2485 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3994 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 744:
#line 2490 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4002 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 745:
#line 2492 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4012 "dhcp4_parser.cc" // lalr1.cc:919
    break;


#line 4016 "dhcp4_parser.cc" // lalr1.cc:919
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


  const short Dhcp4Parser::yypact_ninf_ = -915;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     520,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,    47,    39,    64,    69,    73,
      77,    79,   113,   159,   183,   190,   200,   207,   220,   227,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    39,  -147,
      20,   173,    21,   575,    68,   258,   -26,   228,   261,   -73,
     417,  -100,    93,  -915,    86,    91,    92,   166,   222,  -915,
    -915,  -915,  -915,  -915,   271,  -915,    56,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   277,   279,   287,  -915,
    -915,  -915,  -915,  -915,  -915,   290,   303,   306,   317,   319,
     324,   331,   339,   340,  -915,   347,   348,   349,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   352,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,    62,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   355,  -915,    66,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   356,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,    74,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,    75,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,   285,   358,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   359,  -915,
    -915,   360,  -915,  -915,  -915,   362,  -915,  -915,   369,   365,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   375,   376,  -915,  -915,  -915,  -915,   374,
     383,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,    85,  -915,  -915,  -915,   390,  -915,  -915,
     391,  -915,   392,   397,  -915,  -915,   399,   400,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,    87,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,   111,  -915,  -915,  -915,   401,   149,  -915,  -915,
    -915,  -915,    39,    39,  -915,   174,   402,   404,   405,   410,
     412,  -915,    20,  -915,   420,   423,   426,   239,   241,   243,
     434,   435,   436,   438,   439,   440,   263,   266,   267,   270,
     276,   254,   260,   273,   280,   451,   275,   282,   288,   454,
     467,   468,   473,   475,   478,   480,   482,   484,   487,   488,
     490,   492,   493,   497,   312,   508,   511,   512,   516,   519,
     521,   173,  -915,   523,   524,   526,   332,    21,  -915,   527,
     529,   553,   567,   569,   570,   385,   576,   577,   579,   575,
    -915,   580,    68,  -915,   581,   582,   583,   584,   585,   586,
     587,   588,  -915,   258,  -915,   589,   590,   406,   593,   594,
     595,   415,  -915,   228,   604,   418,   419,  -915,   261,   605,
     608,   -11,  -915,   421,   610,   611,   427,   615,   430,   431,
     619,   620,   433,   441,   622,   623,   624,   630,   417,  -915,
    -100,  -915,   631,   446,    93,  -915,  -915,  -915,   641,   639,
     646,    39,    39,    39,  -915,   650,   652,   653,  -915,  -915,
    -915,   472,   474,   476,   655,   657,   665,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   489,  -915,  -915,  -915,
       3,   491,   496,   672,   674,   676,   677,   681,   500,   316,
     685,   686,   687,   688,   702,  -915,   703,   704,   705,   525,
     528,   708,  -915,   710,   125,   168,  -915,  -915,   530,   531,
     532,   711,   533,   534,  -915,   710,   535,   718,  -915,   537,
    -915,   710,   538,   539,   540,   541,   542,   543,   544,  -915,
     545,   548,  -915,   549,   550,   551,  -915,  -915,   552,  -915,
    -915,  -915,   554,    39,  -915,  -915,   555,   556,  -915,   557,
    -915,  -915,    23,   563,  -915,  -915,     3,   558,   559,   560,
    -915,  -915,   737,  -915,  -915,    39,   173,  -100,  -915,  -915,
    -915,    93,    21,   726,  -915,  -915,  -915,   495,   495,   744,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   745,
     746,   747,   748,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,   224,   749,   750,   751,   262,    89,   115,   417,  -915,
    -915,   752,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   753,  -915,  -915,  -915,  -915,   206,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   744,  -915,   150,
     164,   167,   205,  -915,   214,  -915,  -915,  -915,  -915,  -915,
    -915,   757,   758,   759,   761,   762,  -915,  -915,  -915,  -915,
     763,   764,   765,   766,   767,   768,   769,  -915,  -915,  -915,
    -915,  -915,   218,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   255,
    -915,   770,   771,  -915,  -915,   772,   774,  -915,  -915,   773,
     777,  -915,  -915,   775,   779,  -915,  -915,   778,   780,  -915,
    -915,  -915,  -915,  -915,  -915,   121,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   127,  -915,  -915,   781,   782,  -915,  -915,
     783,   785,  -915,   786,   787,   788,   789,   790,   791,   256,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,   257,  -915,  -915,  -915,   792,  -915,   793,  -915,
    -915,  -915,   264,  -915,  -915,  -915,  -915,  -915,   265,  -915,
     175,  -915,   597,  -915,   794,   795,  -915,  -915,  -915,  -915,
     796,   797,  -915,  -915,  -915,  -915,   798,   726,  -915,   801,
     802,   803,   804,   609,   617,   621,   618,   625,   808,   809,
     810,   812,   627,   628,   629,   632,   633,   634,   635,   816,
     817,   819,   822,   495,  -915,  -915,   495,  -915,   744,   575,
    -915,   745,   228,  -915,   746,   261,  -915,   747,    72,  -915,
     748,   224,  -915,   301,   749,  -915,   258,  -915,   750,   -73,
    -915,   751,   638,   640,   642,   643,   644,   645,   262,  -915,
     825,   827,    89,  -915,   647,   832,   648,   833,   115,  -915,
    -915,   -35,   752,  -915,  -915,   834,   838,    68,  -915,   753,
     839,  -915,  -915,   612,  -915,    -3,   656,   658,   659,  -915,
    -915,  -915,  -915,  -915,   660,   661,   662,   663,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   664,   666,   667,   668,  -915,
     268,  -915,   274,  -915,   836,  -915,   846,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   281,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   842,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   850,   857,  -915,  -915,  -915,
    -915,  -915,   853,  -915,   289,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   675,   694,  -915,  -915,   695,  -915,    39,
    -915,  -915,   859,  -915,  -915,  -915,  -915,  -915,   300,  -915,
    -915,  -915,  -915,  -915,  -915,   698,   308,  -915,   710,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
      72,  -915,   862,   678,  -915,   301,  -915,  -915,  -915,  -915,
    -915,  -915,   870,   700,   873,   -35,  -915,  -915,  -915,  -915,
    -915,   699,  -915,  -915,   837,  -915,   709,  -915,  -915,   890,
    -915,  -915,   212,  -915,   131,   890,  -915,  -915,   896,   898,
     899,  -915,   314,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     902,   716,   720,   723,   912,   131,  -915,   728,  -915,  -915,
    -915,   730,  -915,  -915,  -915
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   165,     9,   324,    11,
     505,    13,   530,    15,   430,    17,   438,    19,   475,    21,
     289,    23,   636,    25,   703,    27,   692,    29,    47,    41,
       0,     0,     0,     0,     0,   532,     0,   440,   477,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     701,   684,   686,   688,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   690,   154,   180,     0,     0,     0,   551,
     553,   555,   178,   187,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,     0,     0,     0,   139,   146,
     148,   316,   428,   467,   386,   518,   520,   379,   267,   579,
     522,   281,   300,     0,   605,   618,   634,   150,   152,   708,
     121,     0,    72,    74,    75,    76,    77,    78,   109,   110,
     111,    79,   107,    96,    97,    98,   115,   116,   117,   118,
     119,   120,   113,   114,    82,    83,   104,    84,    85,    86,
      90,    91,    80,   108,    81,    88,    89,   102,   103,   105,
      99,   100,   101,    87,    92,    93,    94,    95,   106,   112,
     167,   169,   173,     0,   164,     0,   156,   158,   159,   160,
     161,   162,   163,   367,   369,   371,   497,   365,   373,     0,
     377,   375,   575,   364,   328,   329,   330,   331,   332,   353,
     354,   355,   343,   344,   356,   357,   358,   359,   360,   361,
     362,   363,     0,   326,   335,   348,   349,   350,   336,   338,
     339,   341,   337,   333,   334,   351,   352,   340,   345,   346,
     347,   342,   516,   515,   511,   512,   510,     0,   507,   509,
     513,   514,   573,   561,   563,   567,   565,   571,   569,   557,
     550,   544,   548,   549,     0,   533,   534,   545,   546,   547,
     541,   536,   542,   538,   539,   540,   543,   537,     0,   457,
     238,     0,   461,   459,   464,     0,   453,   454,     0,   441,
     442,   444,   456,   445,   446,   447,   463,   448,   449,   450,
     451,   452,   491,     0,     0,   489,   490,   493,   494,     0,
     478,   479,   481,   482,   483,   484,   485,   486,   487,   488,
     296,   298,   293,     0,   291,   294,   295,     0,   672,   659,
       0,   662,     0,     0,   666,   670,     0,     0,   676,   678,
     680,   682,   657,   655,   656,     0,   638,   640,   641,   642,
     643,   644,   645,   646,   647,   652,   648,   649,   650,   651,
     653,   654,     0,   705,   707,   698,     0,     0,   694,   696,
     697,    46,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    57,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,   166,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     325,     0,     0,   506,     0,     0,     0,     0,     0,     0,
       0,     0,   531,     0,   431,     0,     0,     0,     0,     0,
       0,     0,   439,     0,     0,     0,     0,   476,     0,     0,
       0,     0,   290,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   637,
       0,   704,     0,     0,     0,   693,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   133,   134,
     135,     0,     0,     0,     0,     0,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     0,   136,   137,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   604,     0,     0,     0,     0,
       0,     0,    73,     0,     0,     0,   177,   157,     0,     0,
       0,     0,     0,     0,   385,     0,     0,     0,   327,     0,
     508,     0,     0,     0,     0,     0,     0,     0,     0,   535,
       0,     0,   455,     0,     0,     0,   466,   443,     0,   495,
     496,   480,     0,     0,   292,   658,     0,     0,   661,     0,
     664,   665,     0,     0,   674,   675,     0,     0,     0,     0,
     639,   706,     0,   700,   695,     0,     0,     0,   685,   687,
     689,     0,     0,     0,   552,   554,   556,     0,     0,   191,
     132,   141,   142,   143,   144,   145,   140,   147,   149,   318,
     432,   469,   388,    40,   519,   521,   381,   382,   383,   384,
     380,     0,     0,   524,   283,     0,     0,     0,     0,   151,
     153,     0,    51,   168,   171,   172,   170,   175,   176,   174,
     368,   370,   372,   499,   366,   374,   378,   376,     0,   517,
     574,   562,   564,   568,   566,   572,   570,   558,   458,   239,
     462,   460,   465,   492,   297,   299,   673,   660,   663,   668,
     669,   667,   671,   677,   679,   681,   683,   191,    44,     0,
       0,     0,     0,   185,     0,   182,   184,   225,   231,   233,
     235,     0,     0,     0,     0,     0,   247,   249,   251,   253,
       0,     0,     0,     0,     0,     0,     0,   259,   261,   263,
     265,   224,     0,   197,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   212,   213,   214,   209,   215,   216,
     217,   210,   211,   218,   219,   220,   221,   222,   223,     0,
     195,     0,   192,   193,   322,     0,   319,   320,   436,     0,
     433,   434,   473,     0,   470,   471,   392,     0,   389,   390,
     276,   277,   278,   279,   280,     0,   269,   271,   272,   273,
     274,   275,   583,     0,   581,   528,     0,   525,   526,   287,
       0,   284,   285,     0,     0,     0,     0,     0,     0,     0,
     302,   304,   305,   306,   307,   308,   309,   614,   616,   613,
     611,   612,     0,   607,   609,   610,     0,   629,     0,   632,
     625,   626,     0,   620,   622,   623,   624,   627,     0,   712,
       0,   710,    53,   503,     0,   500,   501,   559,   577,   578,
       0,     0,    69,   702,   691,   155,     0,     0,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,   188,     0,   190,     0,     0,
     317,     0,   440,   429,     0,   477,   468,     0,     0,   387,
       0,     0,   268,   585,     0,   580,   532,   523,     0,     0,
     282,     0,     0,     0,     0,     0,     0,     0,     0,   301,
       0,     0,     0,   606,     0,     0,     0,     0,     0,   619,
     635,     0,     0,   709,    55,     0,    54,     0,   498,     0,
       0,   576,   699,     0,   183,     0,     0,     0,     0,   237,
     240,   241,   242,   243,     0,     0,     0,     0,   255,   256,
     244,   245,   246,   257,   258,     0,     0,     0,     0,   198,
       0,   194,     0,   321,     0,   435,     0,   472,   427,   411,
     412,   413,   399,   400,   416,   417,   418,   402,   403,   419,
     420,   421,   422,   423,   424,   425,   426,   396,   397,   398,
     409,   410,   408,     0,   394,   401,   414,   415,   404,   405,
     406,   407,   391,   270,   601,     0,   599,   600,   592,   593,
     597,   598,   594,   595,   596,     0,   586,   587,   589,   590,
     591,   582,     0,   527,     0,   286,   310,   311,   312,   313,
     314,   315,   303,     0,     0,   608,   628,     0,   631,     0,
     621,   726,     0,   724,   722,   716,   720,   721,     0,   714,
     718,   719,   717,   711,    52,     0,     0,   502,     0,   186,
     227,   228,   229,   230,   226,   232,   234,   236,   248,   250,
     252,   254,   260,   262,   264,   266,   196,   323,   437,   474,
       0,   393,     0,     0,   584,     0,   529,   288,   615,   617,
     630,   633,     0,     0,     0,     0,   713,    56,   504,   560,
     395,     0,   603,   588,     0,   723,     0,   715,   602,     0,
     725,   730,     0,   728,     0,     0,   727,   739,     0,     0,
       0,   744,     0,   732,   734,   735,   736,   737,   738,   729,
       0,     0,     0,     0,     0,     0,   731,     0,   741,   742,
     743,     0,   733,   740,   745
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   -23,  -915,   208,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -576,  -915,  -915,
    -915,   -70,  -915,  -915,  -915,   522,  -915,  -915,  -915,  -915,
     284,   470,   -47,   -44,    -1,    16,    18,    24,    30,    31,
    -915,  -915,  -915,  -915,    34,    35,    36,    37,    38,    42,
    -915,   291,    48,  -915,    49,  -915,    50,  -915,    52,  -915,
    -915,  -915,   309,   483,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
      28,  -915,  -915,  -915,  -915,  -915,  -915,   196,  -915,    55,
    -915,  -636,    61,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   -39,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,    44,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,    43,  -915,  -915,  -915,    40,
     494,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    41,  -915,
    -915,  -915,  -915,  -915,  -915,  -914,  -915,  -915,  -915,    65,
    -915,  -915,  -915,    71,   536,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -911,  -915,   -43,  -915,    54,  -915,    53,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,    57,  -915,  -915,
    -137,   -63,  -915,  -915,  -915,  -915,  -915,    67,  -915,  -915,
    -915,    70,  -915,   505,  -915,   -66,  -915,  -915,  -915,  -915,
    -915,   -64,  -915,  -915,  -915,  -915,  -915,    -7,  -915,  -915,
    -915,    76,  -915,  -915,  -915,    80,  -915,   506,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    27,
    -915,  -915,  -915,    26,   546,  -915,  -915,   -57,  -915,   -20,
    -915,   -62,  -915,  -915,  -915,    59,  -915,  -915,  -915,    63,
    -915,   547,     0,  -915,     6,  -915,    12,  -915,   302,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -910,  -915,  -915,  -915,
    -915,  -915,    78,  -915,  -915,  -915,  -127,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,    58,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,    46,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,   323,   498,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,   361,   499,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     370,   501,   -75,  -915,  -915,    60,  -915,  -915,  -126,  -915,
    -915,  -915,  -915,  -915,  -915,  -141,  -915,  -915,  -160,  -915,
    -915,  -915,  -915,  -915,  -915,  -915
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     674,    87,    88,    41,    68,    84,    85,   693,   882,   975,
     976,   771,    43,    70,    96,    97,    98,   396,    45,    71,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   425,   163,   164,   165,   166,   167,   168,   169,
     429,   666,   170,   430,   171,   431,   172,   448,   173,   449,
     174,   405,   205,   206,    47,    72,   207,   453,   208,   454,
     696,   209,   455,   699,   210,   175,   413,   176,   406,   744,
     745,   746,   896,   177,   414,   178,   415,   801,   802,   803,
     926,   772,   773,   774,   899,  1114,   775,   900,   776,   901,
     777,   902,   778,   779,   486,   780,   781,   782,   783,   784,
     785,   786,   787,   908,   788,   909,   789,   910,   790,   911,
     791,   792,   793,   794,   795,   919,   796,   920,   797,   921,
     798,   922,   179,   439,   825,   826,   827,   828,   829,   830,
     831,   180,   442,   840,   841,   842,   949,    61,    79,   343,
     344,   345,   499,   346,   500,   181,   443,   849,   850,   851,
     852,   853,   854,   855,   856,   182,   432,   805,   806,   807,
     929,    49,    73,   242,   243,   244,   463,   245,   459,   246,
     460,   247,   461,   248,   464,   249,   467,   250,   466,   183,
     438,   680,   252,   184,   435,   817,   818,   819,   938,  1043,
    1044,   185,   433,    55,    76,   809,   810,   811,   932,    57,
      77,   308,   309,   310,   311,   312,   313,   314,   485,   315,
     489,   316,   488,   317,   318,   490,   319,   186,   434,   813,
     814,   815,   935,    59,    78,   329,   330,   331,   332,   333,
     494,   334,   335,   336,   337,   254,   462,   884,   885,   886,
     977,    51,    74,   267,   268,   269,   471,   187,   436,   188,
     437,   189,   441,   836,   837,   838,   946,    53,    75,   284,
     285,   286,   190,   410,   191,   411,   192,   412,   290,   481,
     889,   980,   291,   475,   292,   476,   293,   478,   294,   477,
     295,   480,   296,   479,   297,   474,   261,   468,   890,   193,
     440,   833,   834,   943,  1065,  1066,  1067,  1068,  1069,  1132,
    1070,   194,   195,   445,   862,   863,   864,   960,   865,   961,
     196,   446,   872,   873,   874,   875,   965,   876,   877,   967,
     197,   447,    63,    80,   365,   366,   367,   368,   505,   369,
     370,   507,   371,   372,   373,   510,   731,   374,   511,   375,
     504,   376,   377,   378,   514,   379,   515,   380,   516,   381,
     517,    99,   398,   100,   399,   101,   400,   198,   404,    67,
      82,   387,   388,   389,   522,   390,   102,   397,    65,    81,
     382,   383,   199,   450,   880,   881,   971,  1098,  1099,  1100,
    1101,  1144,  1102,  1142,  1162,  1163,  1164,  1172,  1173,  1174,
    1180,  1175,  1176,  1177,  1178,  1184
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   150,   204,   223,   263,   280,   384,   306,   325,   342,
     362,   257,   327,   298,   328,   211,   255,   270,   282,   706,
     320,   338,   799,   363,  1038,   710,   224,  1039,  1051,   225,
      89,   264,  1110,  1111,  1112,  1113,   200,   201,   307,   326,
     202,   729,    86,   203,    31,    83,    32,    30,    33,   300,
     340,   341,   212,   256,   271,   283,   132,   321,   339,   402,
     364,   135,   136,   149,   403,   451,   253,   266,   281,   457,
     452,    42,   226,   258,   458,   287,    44,   469,   472,   259,
      46,   288,   470,   473,    48,   260,    50,   289,   501,   227,
     518,   228,   391,   502,   392,   519,   393,   229,   107,   108,
     109,   110,   111,   230,   231,   385,   386,   232,   233,   234,
     235,   236,   340,   341,   520,   237,    94,   135,   136,   521,
      52,   238,   239,   240,   941,   241,   251,   942,   265,  1091,
     944,  1092,  1093,   945,   115,   116,   117,   118,   119,   120,
     121,   122,   694,   695,   125,   126,   127,   128,   129,   130,
     131,   133,   524,   451,    94,   133,   300,   525,   892,   661,
     662,   663,   664,   262,   135,   136,    54,   520,   135,   136,
     524,   218,   893,   137,   394,   894,   220,   730,   972,   221,
     220,   973,    90,   221,   103,   135,   136,   104,   697,   698,
      56,   222,    91,    92,    93,   665,   105,    58,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    60,   457,    94,
      94,   135,   136,   895,    62,  1165,  1038,   897,  1166,  1039,
    1051,   923,   898,   857,   858,   395,   924,    64,    34,    35,
      36,    37,   147,   148,    66,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   866,   867,   868,   132,   133,    94,   923,   958,
     962,    94,   299,   925,   959,   963,   134,   968,   518,   135,
     136,   923,   969,   970,   137,   401,  1126,   469,    94,   138,
     139,   407,  1127,   408,  1130,   140,   109,   110,   111,  1131,
    1010,   409,   501,   482,   416,   141,  1167,  1137,   142,  1168,
    1169,  1170,  1171,  1145,   869,   143,   144,   417,  1146,   145,
     418,   472,   300,   146,   301,   302,  1148,  1185,   303,   304,
     305,   419,  1186,   420,   135,   136,   279,   887,   421,   109,
     110,   111,    95,   147,   148,   422,   149,   820,   821,   822,
     823,   133,   824,   423,   424,   300,   322,   301,   302,   323,
     324,   426,   427,   428,   135,   136,   444,   135,   136,   456,
     465,   483,    94,   528,   487,   272,   491,   484,   493,   526,
     527,   273,   274,   275,   276,   277,   278,   492,   279,   495,
     496,   150,   497,   132,   133,   300,   498,   204,   843,   844,
     845,   846,   847,   848,   503,   506,   508,   135,   136,   223,
     211,   509,   263,   512,   513,   523,   529,   257,   530,   531,
    1054,  1055,   255,   280,   532,   270,   533,    94,   676,   677,
     678,   679,   224,   306,   535,   225,   282,   536,   325,   264,
     537,   538,   327,   539,   328,   540,   320,   212,   541,   542,
     543,   338,   544,   545,   546,   384,   552,    94,   362,   256,
      94,   553,   271,   547,   307,   556,   548,   549,   560,   326,
     550,   363,   253,   283,   554,   266,   551,   557,   226,   258,
     555,   561,   562,   321,   558,   259,   281,   563,   339,   564,
     559,   260,   565,   287,   566,   227,   567,   228,   568,   288,
      94,   569,   570,   229,   571,   289,   572,   573,   364,   230,
     231,   574,   575,   232,   233,   234,   235,   236,   648,   649,
     650,   237,   576,   135,   136,   577,   578,   238,   239,   240,
     579,   241,   251,   580,   586,   581,   265,   583,   584,   747,
     585,   588,  1149,   589,   748,   749,   750,   751,   752,   753,
     754,   755,   756,   757,   758,   759,   760,   761,   762,   763,
     764,   765,   766,   767,   768,   769,   770,   590,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   591,   384,   592,   593,   594,   150,   360,   361,   300,
     595,   596,   204,   597,   599,   601,   602,   603,   604,   605,
     606,   607,   608,   610,   611,   211,   612,   613,   614,   615,
     725,   107,   108,   109,   110,   111,    94,   616,   618,   622,
     619,   620,   623,   625,   626,   627,   859,   628,   362,   629,
     630,   631,   738,   632,   633,   634,   636,   637,   638,   860,
     870,   363,   212,   635,   639,   642,   643,   115,   116,   117,
     118,   119,   120,   121,   122,   645,   646,   125,   126,   127,
     128,   129,   130,   647,   213,   214,   215,   651,   133,   652,
     653,   654,   657,   655,   658,   656,   861,   871,   364,   216,
     659,   135,   136,   217,   218,   219,   137,   669,   660,   670,
     667,   671,   672,   220,    94,   668,   221,   140,    32,   675,
     681,   682,   683,   684,   222,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   685,
     686,   687,   688,   691,   689,   692,   703,   690,   732,   700,
     701,   702,   704,   705,   707,   708,   709,   711,   712,   713,
     714,   715,   716,   717,   718,   147,   148,   719,   720,   721,
     722,   723,   737,   724,   726,   727,   728,   734,   735,   736,
     743,   800,   804,   808,   812,   816,   832,   835,   839,   879,
     883,   903,   904,   905,    94,   906,   907,   912,   913,   914,
     915,   916,   917,   918,   928,   673,   927,   931,   930,   933,
     934,   936,   937,   940,   939,   948,   974,   947,   951,   950,
     952,   953,   954,   955,   956,   957,   964,   966,   979,   989,
     978,  1109,   983,   982,   981,   985,   986,   987,   988,   990,
     992,   991,   994,   995,   996,   993,   997,   998,   999,  1000,
    1005,  1006,  1001,  1007,  1003,  1002,  1008,  1004,  1076,  1083,
    1077,  1084,  1078,  1079,  1080,  1081,  1087,  1089,  1088,  1086,
    1104,  1105,  1159,  1108,  1128,  1115,  1133,  1116,  1117,  1118,
    1119,  1120,  1121,  1122,  1129,  1123,  1124,  1125,  1134,   223,
    1135,  1136,   306,  1143,  1138,   325,  1151,   257,  1018,   327,
    1152,   328,   255,  1056,  1154,   320,   280,  1156,   338,   342,
    1058,  1046,   224,  1139,  1140,   225,  1060,  1147,  1158,   282,
    1155,  1019,   859,   307,  1020,  1040,   326,  1161,  1160,  1037,
    1181,  1094,  1182,  1183,  1057,   860,  1187,   263,  1188,   256,
    1189,   870,   321,  1190,  1096,   339,  1191,  1193,  1047,  1194,
     270,   582,   253,  1061,   534,   984,   283,   733,   226,   258,
     739,  1045,  1095,   891,   264,   259,  1059,  1021,  1048,   281,
     587,   260,   861,  1062,  1049,   227,   287,   228,   871,  1063,
    1050,  1097,   288,   229,  1022,  1064,  1023,   271,   289,   230,
     231,   742,  1024,   232,   233,   234,   235,   236,  1025,  1026,
     266,   237,  1027,  1028,  1029,  1030,  1031,   238,   239,   240,
    1032,   241,   251,  1011,  1009,  1053,  1033,  1034,  1035,  1074,
    1036,  1042,  1041,  1150,  1075,   624,  1013,  1052,   617,  1082,
    1012,  1015,  1014,  1106,   621,   598,  1107,  1073,  1153,  1072,
     888,   878,   741,  1017,  1090,  1016,   640,   740,   600,  1157,
    1085,   641,  1071,   644,  1179,  1192,     0,     0,     0,     0,
     609,   265,  1103,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1018,     0,     0,     0,     0,  1056,  1141,     0,     0,     0,
       0,     0,  1058,  1046,     0,  1094,     0,     0,  1060,     0,
       0,     0,     0,  1019,     0,     0,  1020,  1040,  1096,     0,
       0,  1037,     0,     0,     0,     0,  1057,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1095,     0,     0,     0,
    1047,     0,     0,     0,     0,  1061,     0,     0,     0,     0,
       0,     0,     0,  1045,     0,  1097,     0,     0,  1059,  1021,
    1048,     0,     0,     0,     0,  1062,  1049,     0,     0,     0,
       0,  1063,  1050,     0,     0,     0,  1022,  1064,  1023,     0,
       0,     0,     0,     0,  1024,     0,     0,     0,     0,     0,
    1025,  1026,     0,     0,  1027,  1028,  1029,  1030,  1031,     0,
       0,     0,  1032,     0,     0,     0,     0,     0,  1033,  1034,
    1035,     0,  1036,  1042,  1041
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    81,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,   595,
      77,    78,   658,    80,   938,   601,    73,   938,   938,    73,
      10,    74,    35,    36,    37,    38,    15,    16,    77,    78,
      19,    18,   189,    22,     5,    68,     7,     0,     9,    84,
     123,   124,    72,    73,    74,    75,    82,    77,    78,     3,
      80,    96,    97,   163,     8,     3,    73,    74,    75,     3,
       8,     7,    73,    73,     8,    75,     7,     3,     3,    73,
       7,    75,     8,     8,     7,    73,     7,    75,     3,    73,
       3,    73,     6,     8,     3,     8,     4,    73,    26,    27,
      28,    29,    30,    73,    73,    12,    13,    73,    73,    73,
      73,    73,   123,   124,     3,    73,   189,    96,    97,     8,
       7,    73,    73,    73,     3,    73,    73,     6,    74,   164,
       3,   166,   167,     6,    62,    63,    64,    65,    66,    67,
      68,    69,    17,    18,    72,    73,    74,    75,    76,    77,
      78,    83,     3,     3,   189,    83,    84,     8,     8,   156,
     157,   158,   159,    95,    96,    97,     7,     3,    96,    97,
       3,    99,     8,   101,     8,     8,   108,   154,     3,   111,
     108,     6,   162,   111,    11,    96,    97,    14,    20,    21,
       7,   119,   172,   173,   174,   192,    23,     7,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     7,     3,   189,
     189,    96,    97,     8,     7,     3,  1130,     3,     6,  1130,
    1130,     3,     8,   134,   135,     3,     8,     7,   189,   190,
     191,   192,   160,   161,     7,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,   137,   138,   139,    82,    83,   189,     3,     3,
       3,   189,    34,     8,     8,     8,    93,     3,     3,    96,
      97,     3,     8,     8,   101,     4,     8,     3,   189,   106,
     107,     4,     8,     4,     3,   112,    28,    29,    30,     8,
     926,     4,     3,     8,     4,   122,   165,     8,   125,   168,
     169,   170,   171,     3,   189,   132,   133,     4,     8,   136,
       4,     3,    84,   140,    86,    87,     8,     3,    90,    91,
      92,     4,     8,     4,    96,    97,   120,   121,     4,    28,
      29,    30,   402,   160,   161,     4,   163,   113,   114,   115,
     116,    83,   118,     4,     4,    84,    85,    86,    87,    88,
      89,     4,     4,     4,    96,    97,     4,    96,    97,     4,
       4,     3,   189,   189,     4,   107,     4,     8,     3,   392,
     393,   113,   114,   115,   116,   117,   118,     8,   120,     4,
       4,   451,     8,    82,    83,    84,     3,   457,   126,   127,
     128,   129,   130,   131,     4,     4,     4,    96,    97,   469,
     457,     4,   472,     4,     4,     4,     4,   469,     4,     4,
     109,   110,   469,   483,     4,   472,     4,   189,   102,   103,
     104,   105,   469,   493,     4,   469,   483,     4,   498,   472,
       4,   192,   498,   192,   498,   192,   493,   457,     4,     4,
       4,   498,     4,     4,     4,   520,   192,   189,   518,   469,
     189,   191,   472,   190,   493,     4,   190,   190,     4,   498,
     190,   518,   469,   483,   191,   472,   190,   192,   469,   469,
     190,     4,     4,   493,   192,   469,   483,     4,   498,     4,
     192,   469,     4,   483,     4,   469,     4,   469,     4,   483,
     189,     4,     4,   469,     4,   483,     4,     4,   518,   469,
     469,     4,   190,   469,   469,   469,   469,   469,   531,   532,
     533,   469,     4,    96,    97,     4,     4,   469,   469,   469,
       4,   469,   469,     4,   192,     4,   472,     4,     4,    34,
       4,     4,  1108,     4,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,     4,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,     4,   647,     4,     4,   190,   646,   160,   161,    84,
       4,     4,   652,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   652,   190,     4,     4,     4,
     623,    26,    27,    28,    29,    30,   189,   192,     4,     4,
     192,   192,     4,   192,     4,     4,   686,   190,   688,     4,
     190,   190,   645,     4,     4,   192,     4,     4,     4,   686,
     687,   688,   652,   192,     4,     4,   190,    62,    63,    64,
      65,    66,    67,    68,    69,     4,     7,    72,    73,    74,
      75,    76,    77,     7,    79,    80,    81,     7,    83,     7,
       7,   189,     7,   189,     7,   189,   686,   687,   688,    94,
       5,    96,    97,    98,    99,   100,   101,     5,   189,     5,
     189,     5,     5,   108,   189,   189,   111,   112,     7,   189,
       5,     5,     5,     5,   119,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,     7,
       7,     7,     7,     5,   189,     5,     5,   189,   155,   189,
     189,   189,   189,   189,   189,     7,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   160,   161,   189,   189,   189,
     189,   189,     5,   189,   189,   189,   189,   189,   189,   189,
      24,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     4,     4,     4,   189,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   567,     6,     3,     6,     6,
       3,     6,     3,     3,     6,     3,   189,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   190,
       6,   189,     4,     6,     8,     4,     4,     4,     4,   192,
     192,   190,     4,     4,     4,   190,     4,   190,   190,   190,
       4,     4,   190,     4,   190,   192,     4,   192,   190,     4,
     190,     4,   190,   190,   190,   190,     4,     4,   190,   192,
       6,     3,     5,     4,     8,   189,     4,   189,   189,   189,
     189,   189,   189,   189,     8,   189,   189,   189,     8,   929,
       3,     8,   932,     4,   189,   935,     4,   929,   938,   935,
     192,   935,   929,   943,     4,   932,   946,     4,   935,   949,
     943,   938,   929,   189,   189,   929,   943,   189,   189,   946,
     190,   938,   962,   932,   938,   938,   935,     7,   189,   938,
       4,   971,     4,     4,   943,   962,     4,   977,   192,   929,
     190,   968,   932,   190,   971,   935,     4,   189,   938,   189,
     977,   451,   929,   943,   402,   897,   946,   636,   929,   929,
     646,   938,   971,   737,   977,   929,   943,   938,   938,   946,
     457,   929,   962,   943,   938,   929,   946,   929,   968,   943,
     938,   971,   946,   929,   938,   943,   938,   977,   946,   929,
     929,   652,   938,   929,   929,   929,   929,   929,   938,   938,
     977,   929,   938,   938,   938,   938,   938,   929,   929,   929,
     938,   929,   929,   928,   923,   941,   938,   938,   938,   949,
     938,   938,   938,  1130,   951,   501,   931,   940,   493,   958,
     929,   934,   932,   977,   498,   469,   979,   948,  1135,   946,
     708,   688,   651,   937,   968,   935,   518,   647,   472,  1145,
     962,   520,   944,   524,  1165,  1185,    -1,    -1,    -1,    -1,
     483,   977,   972,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1130,    -1,    -1,    -1,    -1,  1135,  1089,    -1,    -1,    -1,
      -1,    -1,  1135,  1130,    -1,  1145,    -1,    -1,  1135,    -1,
      -1,    -1,    -1,  1130,    -1,    -1,  1130,  1130,  1145,    -1,
      -1,  1130,    -1,    -1,    -1,    -1,  1135,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1145,    -1,    -1,    -1,
    1130,    -1,    -1,    -1,    -1,  1135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1130,    -1,  1145,    -1,    -1,  1135,  1130,
    1130,    -1,    -1,    -1,    -1,  1135,  1130,    -1,    -1,    -1,
      -1,  1135,  1130,    -1,    -1,    -1,  1130,  1135,  1130,    -1,
      -1,    -1,    -1,    -1,  1130,    -1,    -1,    -1,    -1,    -1,
    1130,  1130,    -1,    -1,  1130,  1130,  1130,  1130,  1130,    -1,
      -1,    -1,  1130,    -1,    -1,    -1,    -1,    -1,  1130,  1130,
    1130,    -1,  1130,  1130,  1130
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
       0,     5,     7,     9,   189,   190,   191,   192,   209,   210,
     211,   216,     7,   225,     7,   231,     7,   267,     7,   374,
       7,   454,     7,   470,     7,   406,     7,   412,     7,   436,
       7,   350,     7,   535,     7,   581,     7,   572,   217,   212,
     226,   232,   268,   375,   455,   471,   407,   413,   437,   351,
     536,   582,   573,   209,   218,   219,   189,   214,   215,    10,
     162,   172,   173,   174,   189,   224,   227,   228,   229,   564,
     566,   568,   579,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    82,    83,    93,    96,    97,   101,   106,   107,
     112,   122,   125,   132,   133,   136,   140,   160,   161,   163,
     224,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   246,   247,   248,   249,   250,   251,   252,
     255,   257,   259,   261,   263,   278,   280,   286,   288,   335,
     344,   358,   368,   392,   396,   404,   430,   460,   462,   464,
     475,   477,   479,   502,   514,   515,   523,   533,   570,   585,
      15,    16,    19,    22,   224,   265,   266,   269,   271,   274,
     277,   460,   462,    79,    80,    81,    94,    98,    99,   100,
     108,   111,   119,   224,   235,   236,   237,   238,   239,   240,
     241,   242,   247,   248,   249,   250,   251,   252,   255,   257,
     259,   261,   376,   377,   378,   380,   382,   384,   386,   388,
     390,   392,   395,   430,   448,   460,   462,   464,   475,   477,
     479,   499,    95,   224,   388,   390,   430,   456,   457,   458,
     460,   462,   107,   113,   114,   115,   116,   117,   118,   120,
     224,   430,   460,   462,   472,   473,   474,   475,   477,   479,
     481,   485,   487,   489,   491,   493,   495,   497,   404,    34,
      84,    86,    87,    90,    91,    92,   224,   306,   414,   415,
     416,   417,   418,   419,   420,   422,   424,   426,   427,   429,
     460,   462,    85,    88,    89,   224,   306,   418,   424,   438,
     439,   440,   441,   442,   444,   445,   446,   447,   460,   462,
     123,   124,   224,   352,   353,   354,   356,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     160,   161,   224,   460,   462,   537,   538,   539,   540,   542,
     543,   545,   546,   547,   550,   552,   554,   555,   556,   558,
     560,   562,   583,   584,   585,    12,    13,   574,   575,   576,
     578,     6,     3,     4,     8,     3,   230,   580,   565,   567,
     569,     4,     3,     8,   571,   264,   281,     4,     4,     4,
     476,   478,   480,   279,   287,   289,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   245,     4,     4,     4,   253,
     256,   258,   369,   405,   431,   397,   461,   463,   393,   336,
     503,   465,   345,   359,     4,   516,   524,   534,   260,   262,
     586,     3,     8,   270,   272,   275,     4,     3,     8,   381,
     383,   385,   449,   379,   387,     4,   391,   389,   500,     3,
       8,   459,     3,     8,   498,   486,   488,   492,   490,   496,
     494,   482,     8,     3,     8,   421,   307,     4,   425,   423,
     428,     4,     8,     3,   443,     4,     4,     8,     3,   355,
     357,     3,     8,     4,   553,   541,     4,   544,     4,     4,
     548,   551,     4,     4,   557,   559,   561,   563,     3,     8,
       3,     8,   577,     4,     3,     8,   209,   209,   189,     4,
       4,     4,     4,     4,   228,     4,     4,     4,   192,   192,
     192,     4,     4,     4,     4,     4,     4,   190,   190,   190,
     190,   190,   192,   191,   191,   190,     4,   192,   192,   192,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   190,     4,     4,     4,     4,
       4,     4,   234,     4,     4,     4,   192,   266,     4,     4,
       4,     4,     4,     4,   190,     4,     4,     4,   377,     4,
     457,     4,     4,     4,     4,     4,     4,     4,     4,   474,
       4,     4,   190,     4,     4,     4,   192,   416,     4,   192,
     192,   440,     4,     4,   353,   192,     4,     4,   190,     4,
     190,   190,     4,     4,   192,   192,     4,     4,     4,     4,
     538,   584,     4,   190,   575,     4,     7,     7,   209,   209,
     209,     7,     7,     7,   189,   189,   189,     7,     7,     5,
     189,   156,   157,   158,   159,   192,   254,   189,   189,     5,
       5,     5,     5,   211,   213,   189,   102,   103,   104,   105,
     394,     5,     5,     5,     5,     7,     7,     7,     7,   189,
     189,     5,     5,   220,    17,    18,   273,    20,    21,   276,
     189,   189,   189,     5,   189,   189,   220,   189,     7,   189,
     220,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   209,   189,   189,   189,    18,
     154,   549,   155,   254,   189,   189,   189,     5,   209,   233,
     583,   574,   265,    24,   282,   283,   284,    34,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,   224,   294,   295,   296,   299,   301,   303,   305,   306,
     308,   309,   310,   311,   312,   313,   314,   315,   317,   319,
     321,   323,   324,   325,   326,   327,   329,   331,   333,   294,
       7,   290,   291,   292,     7,   370,   371,   372,     7,   408,
     409,   410,     7,   432,   433,   434,     7,   398,   399,   400,
     113,   114,   115,   116,   118,   337,   338,   339,   340,   341,
     342,   343,     7,   504,   505,     7,   466,   467,   468,     7,
     346,   347,   348,   126,   127,   128,   129,   130,   131,   360,
     361,   362,   363,   364,   365,   366,   367,   134,   135,   224,
     460,   462,   517,   518,   519,   521,   137,   138,   139,   189,
     460,   462,   525,   526,   527,   528,   530,   531,   537,     7,
     587,   588,   221,     7,   450,   451,   452,   121,   481,   483,
     501,   290,     8,     8,     8,     8,   285,     3,     8,   297,
     300,   302,   304,     4,     4,     4,     4,     4,   316,   318,
     320,   322,     4,     4,     4,     4,     4,     4,     4,   328,
     330,   332,   334,     3,     8,     8,   293,     6,     3,   373,
       6,     3,   411,     6,     3,   435,     6,     3,   401,     6,
       3,     3,     6,   506,     3,     6,   469,     6,     3,   349,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     520,   522,     3,     8,     4,   529,     4,   532,     3,     8,
       8,   589,     3,     6,   189,   222,   223,   453,     6,     3,
     484,     8,     6,     4,   283,     4,     4,     4,     4,   190,
     192,   190,   192,   190,     4,     4,     4,     4,   190,   190,
     190,   190,   192,   190,   192,     4,     4,     4,     4,   295,
     294,   292,   376,   372,   414,   410,   438,   434,   224,   235,
     236,   237,   238,   239,   240,   241,   242,   247,   248,   249,
     250,   251,   252,   255,   257,   259,   261,   306,   368,   386,
     388,   390,   392,   402,   403,   430,   460,   462,   475,   477,
     479,   499,   400,   338,   109,   110,   224,   306,   404,   430,
     460,   462,   475,   477,   479,   507,   508,   509,   510,   511,
     513,   505,   472,   468,   352,   348,   190,   190,   190,   190,
     190,   190,   361,     4,     4,   518,   192,     4,   190,     4,
     526,   164,   166,   167,   224,   306,   460,   462,   590,   591,
     592,   593,   595,   588,     6,     3,   456,   452,     4,   189,
      35,    36,    37,    38,   298,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,     8,     8,     8,     8,
       3,     8,   512,     4,     8,     3,     8,     8,   189,   189,
     189,   209,   596,     4,   594,     3,     8,   189,     8,   220,
     403,     4,   192,   509,     4,   190,     4,   591,   189,     5,
     189,     7,   597,   598,   599,     3,     6,   165,   168,   169,
     170,   171,   600,   601,   602,   604,   605,   606,   607,   598,
     603,     4,     4,     4,   608,     3,     8,     4,   192,   190,
     190,     4,   601,   189,   189
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   193,   195,   194,   196,   194,   197,   194,   198,   194,
     199,   194,   200,   194,   201,   194,   202,   194,   203,   194,
     204,   194,   205,   194,   206,   194,   207,   194,   208,   194,
     209,   209,   209,   209,   209,   209,   209,   210,   212,   211,
     213,   214,   214,   215,   215,   217,   216,   218,   218,   219,
     219,   221,   220,   222,   222,   223,   223,   224,   226,   225,
     227,   227,   228,   228,   228,   228,   228,   228,   230,   229,
     232,   231,   233,   233,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   245,   244,   246,   247,   248,   249,   250,   251,   253,
     252,   254,   254,   254,   254,   254,   256,   255,   258,   257,
     260,   259,   262,   261,   264,   263,   265,   265,   266,   266,
     266,   266,   266,   266,   266,   268,   267,   270,   269,   272,
     271,   273,   273,   275,   274,   276,   276,   277,   279,   278,
     281,   280,   282,   282,   283,   285,   284,   287,   286,   289,
     288,   290,   290,   291,   291,   293,   292,   294,   294,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,   297,   296,   298,   298,   298,
     298,   300,   299,   302,   301,   304,   303,   305,   307,   306,
     308,   309,   310,   311,   312,   313,   314,   316,   315,   318,
     317,   320,   319,   322,   321,   323,   324,   325,   326,   328,
     327,   330,   329,   332,   331,   334,   333,   336,   335,   337,
     337,   338,   338,   338,   338,   338,   339,   340,   341,   342,
     343,   345,   344,   346,   346,   347,   347,   349,   348,   351,
     350,   352,   352,   352,   353,   353,   355,   354,   357,   356,
     359,   358,   360,   360,   361,   361,   361,   361,   361,   361,
     362,   363,   364,   365,   366,   367,   369,   368,   370,   370,
     371,   371,   373,   372,   375,   374,   376,   376,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   377,   377,
     377,   377,   377,   377,   377,   379,   378,   381,   380,   383,
     382,   385,   384,   387,   386,   389,   388,   391,   390,   393,
     392,   394,   394,   394,   394,   395,   397,   396,   398,   398,
     399,   399,   401,   400,   402,   402,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   405,   404,
     407,   406,   408,   408,   409,   409,   411,   410,   413,   412,
     414,   414,   415,   415,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   417,   418,   419,   421,   420,   423,
     422,   425,   424,   426,   428,   427,   429,   431,   430,   432,
     432,   433,   433,   435,   434,   437,   436,   438,   438,   439,
     439,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     441,   443,   442,   444,   445,   446,   447,   449,   448,   450,
     450,   451,   451,   453,   452,   455,   454,   456,   456,   457,
     457,   457,   457,   457,   457,   457,   459,   458,   461,   460,
     463,   462,   465,   464,   466,   466,   467,   467,   469,   468,
     471,   470,   472,   472,   473,   473,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   476,   475,   478,   477,   480,   479,   482,   481,   484,
     483,   486,   485,   488,   487,   490,   489,   492,   491,   494,
     493,   496,   495,   498,   497,   500,   499,   501,   501,   503,
     502,   504,   504,   506,   505,   507,   507,   508,   508,   509,
     509,   509,   509,   509,   509,   509,   509,   509,   509,   509,
     510,   512,   511,   513,   514,   516,   515,   517,   517,   518,
     518,   518,   518,   518,   520,   519,   522,   521,   524,   523,
     525,   525,   526,   526,   526,   526,   526,   526,   527,   529,
     528,   530,   532,   531,   534,   533,   536,   535,   537,   537,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   539,   541,
     540,   542,   544,   543,   545,   546,   548,   547,   549,   549,
     551,   550,   553,   552,   554,   555,   557,   556,   559,   558,
     561,   560,   563,   562,   565,   564,   567,   566,   569,   568,
     571,   570,   573,   572,   574,   574,   575,   575,   577,   576,
     578,   580,   579,   582,   581,   583,   583,   584,   586,   585,
     587,   587,   589,   588,   590,   590,   591,   591,   591,   591,
     591,   591,   591,   592,   594,   593,   596,   595,   597,   597,
     599,   598,   600,   600,   601,   601,   601,   601,   601,   603,
     602,   604,   605,   606,   608,   607
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     6,
       3,     0,     6,     0,     4,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4
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
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"ssl\"", "\"ssl-ca\"",
  "\"ssl-cert\"", "\"ssl-key\"", "\"ssl-password\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "interfaces_config", "$@27", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@28", "interfaces_list",
  "$@29", "dhcp_socket_type", "$@30", "socket_type", "outbound_interface",
  "$@31", "outbound_interface_value", "re_detect", "lease_database",
  "$@32", "sanity_checks", "$@33", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@34", "hosts_database", "$@35",
  "hosts_databases", "$@36", "database_list", "not_empty_database_list",
  "database", "$@37", "database_map_params", "database_map_param",
  "database_type", "$@38", "db_type", "user", "$@39", "password", "$@40",
  "host", "$@41", "port", "name", "$@42", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@43", "keyspace", "$@44",
  "consistency", "$@45", "serial_consistency", "$@46",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors", "ssl",
  "ssl_ca", "$@47", "ssl_cert", "$@48", "ssl_key", "$@49", "ssl_password",
  "$@50", "host_reservation_identifiers", "$@51",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@52", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@53",
  "sub_hooks_library", "$@54", "hooks_params", "hooks_param", "library",
  "$@55", "parameters", "$@56", "expired_leases_processing", "$@57",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@58",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@59",
  "sub_subnet4", "$@60", "subnet4_params", "subnet4_param", "subnet",
  "$@61", "subnet_4o6_interface", "$@62", "subnet_4o6_interface_id",
  "$@63", "subnet_4o6_subnet", "$@64", "interface", "$@65", "client_class",
  "$@66", "require_client_classes", "$@67", "reservation_mode", "$@68",
  "hr_mode", "id", "shared_networks", "$@69", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@70",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@71", "sub_option_def_list", "$@72", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@73",
  "sub_option_def", "$@74", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@75",
  "option_def_record_types", "$@76", "space", "$@77", "option_def_space",
  "option_def_encapsulate", "$@78", "option_def_array", "option_data_list",
  "$@79", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@80", "sub_option_data", "$@81",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@82",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@83", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@84", "sub_pool4", "$@85",
  "pool_params", "pool_param", "pool_entry", "$@86", "user_context",
  "$@87", "comment", "$@88", "reservations", "$@89", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@90", "sub_reservation",
  "$@91", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@92", "server_hostname", "$@93",
  "boot_file_name", "$@94", "ip_address", "$@95", "ip_addresses", "$@96",
  "duid", "$@97", "hw_address", "$@98", "client_id_value", "$@99",
  "circuit_id_value", "$@100", "flex_id_value", "$@101", "hostname",
  "$@102", "reservation_client_classes", "$@103", "relay", "$@104",
  "relay_map", "client_classes", "$@105", "client_classes_list",
  "client_class_entry", "$@106", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@107", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@108", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@109",
  "control_socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@116", "server_port",
  "sender_ip", "$@117", "sender_port", "max_queue_size", "ncr_protocol",
  "$@118", "ncr_protocol_value", "ncr_format", "$@119",
  "dep_qualifying_suffix", "$@120", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@121",
  "dep_generated_prefix", "$@122", "dep_hostname_char_set", "$@123",
  "dep_hostname_char_replacement", "$@124", "dhcp6_json_object", "$@125",
  "dhcpddns_json_object", "$@126", "control_agent_json_object", "$@127",
  "config_control", "$@128", "sub_config_control", "$@129",
  "config_control_params", "config_control_param", "config_databases",
  "$@130", "config_fetch_wait_time", "logging_object", "$@131",
  "sub_logging", "$@132", "logging_params", "logging_param", "loggers",
  "$@133", "loggers_entries", "logger_entry", "$@134", "logger_params",
  "logger_param", "debuglevel", "severity", "$@135", "output_options_list",
  "$@136", "output_options_list_content", "output_entry", "$@137",
  "output_params_list", "output_params", "output", "$@138", "flush",
  "maxsize", "maxver", "pattern", "$@139", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   280,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   289,   290,   290,   291,   291,   292,   292,   293,   293,
     301,   302,   303,   304,   305,   306,   307,   310,   315,   315,
     326,   329,   330,   333,   337,   344,   344,   351,   352,   355,
     359,   366,   366,   373,   374,   377,   381,   392,   402,   402,
     418,   419,   423,   424,   425,   426,   427,   428,   431,   431,
     446,   446,   455,   456,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   511,   516,   521,   526,   531,   536,   541,   546,
     551,   556,   556,   564,   569,   574,   579,   584,   589,   594,
     594,   602,   605,   608,   611,   614,   620,   620,   628,   628,
     636,   636,   644,   644,   652,   652,   663,   664,   667,   668,
     669,   670,   671,   672,   673,   676,   676,   685,   685,   695,
     695,   702,   703,   706,   706,   713,   715,   719,   725,   725,
     737,   737,   747,   748,   750,   752,   752,   770,   770,   782,
     782,   792,   793,   796,   797,   800,   800,   810,   811,   814,
     815,   816,   817,   818,   819,   820,   821,   822,   823,   824,
     825,   826,   827,   828,   829,   830,   831,   832,   833,   834,
     835,   836,   837,   838,   839,   842,   842,   849,   850,   851,
     852,   855,   855,   863,   863,   871,   871,   879,   884,   884,
     892,   897,   902,   907,   912,   917,   922,   927,   927,   935,
     935,   943,   943,   951,   951,   959,   964,   969,   974,   979,
     979,   987,   987,   995,   995,  1003,  1003,  1011,  1011,  1021,
    1022,  1025,  1026,  1027,  1028,  1029,  1032,  1037,  1042,  1047,
    1052,  1057,  1057,  1067,  1068,  1071,  1072,  1075,  1075,  1085,
    1085,  1095,  1096,  1097,  1100,  1101,  1104,  1104,  1112,  1112,
    1120,  1120,  1131,  1132,  1135,  1136,  1137,  1138,  1139,  1140,
    1143,  1148,  1153,  1158,  1163,  1168,  1176,  1176,  1189,  1190,
    1193,  1194,  1201,  1201,  1227,  1227,  1238,  1239,  1243,  1244,
    1245,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,
    1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,
    1275,  1276,  1277,  1278,  1279,  1282,  1282,  1290,  1290,  1298,
    1298,  1306,  1306,  1314,  1314,  1322,  1322,  1330,  1330,  1340,
    1340,  1347,  1348,  1349,  1350,  1353,  1360,  1360,  1371,  1372,
    1376,  1377,  1380,  1380,  1388,  1389,  1392,  1393,  1394,  1395,
    1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,
    1406,  1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,
    1416,  1417,  1418,  1419,  1420,  1421,  1422,  1423,  1430,  1430,
    1443,  1443,  1452,  1453,  1456,  1457,  1462,  1462,  1477,  1477,
    1491,  1492,  1495,  1496,  1499,  1500,  1501,  1502,  1503,  1504,
    1505,  1506,  1507,  1508,  1511,  1513,  1518,  1520,  1520,  1528,
    1528,  1536,  1536,  1544,  1546,  1546,  1554,  1563,  1563,  1575,
    1576,  1581,  1582,  1587,  1587,  1599,  1599,  1611,  1612,  1617,
    1618,  1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,
    1634,  1636,  1636,  1644,  1646,  1648,  1653,  1661,  1661,  1673,
    1674,  1677,  1678,  1681,  1681,  1691,  1691,  1701,  1702,  1705,
    1706,  1707,  1708,  1709,  1710,  1711,  1714,  1714,  1722,  1722,
    1747,  1747,  1777,  1777,  1787,  1788,  1791,  1792,  1795,  1795,
    1804,  1804,  1813,  1814,  1817,  1818,  1822,  1823,  1824,  1825,
    1826,  1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,  1835,
    1836,  1839,  1839,  1847,  1847,  1855,  1855,  1863,  1863,  1871,
    1871,  1881,  1881,  1889,  1889,  1897,  1897,  1905,  1905,  1913,
    1913,  1921,  1921,  1929,  1929,  1942,  1942,  1952,  1953,  1959,
    1959,  1969,  1970,  1973,  1973,  1983,  1984,  1987,  1988,  1991,
    1992,  1993,  1994,  1995,  1996,  1997,  1998,  1999,  2000,  2001,
    2004,  2006,  2006,  2014,  2023,  2030,  2030,  2040,  2041,  2044,
    2045,  2046,  2047,  2048,  2051,  2051,  2059,  2059,  2070,  2070,
    2082,  2083,  2086,  2087,  2088,  2089,  2090,  2091,  2094,  2099,
    2099,  2107,  2112,  2112,  2121,  2121,  2133,  2133,  2143,  2144,
    2147,  2148,  2149,  2150,  2151,  2152,  2153,  2154,  2155,  2156,
    2157,  2158,  2159,  2160,  2161,  2162,  2163,  2164,  2167,  2172,
    2172,  2180,  2185,  2185,  2193,  2198,  2203,  2203,  2211,  2212,
    2215,  2215,  2224,  2224,  2233,  2239,  2245,  2245,  2253,  2253,
    2262,  2262,  2271,  2271,  2282,  2282,  2289,  2289,  2296,  2296,
    2303,  2303,  2314,  2314,  2324,  2325,  2329,  2330,  2333,  2333,
    2343,  2353,  2353,  2363,  2363,  2374,  2375,  2379,  2383,  2383,
    2395,  2396,  2400,  2400,  2408,  2409,  2412,  2413,  2414,  2415,
    2416,  2417,  2418,  2421,  2426,  2426,  2434,  2434,  2444,  2445,
    2448,  2448,  2456,  2457,  2460,  2461,  2462,  2463,  2464,  2467,
    2467,  2475,  2480,  2485,  2490,  2490
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
#line 5445 "dhcp4_parser.cc" // lalr1.cc:1242
#line 2499 "dhcp4_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
