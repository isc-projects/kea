// A Bison parser, made by GNU Bison 3.2.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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
#line 34 "dhcp6_parser.yy" // lalr1.cc:438

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc" // lalr1.cc:438


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
    while (/*CONSTCOND*/ false)
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

#line 14 "dhcp6_parser.yy" // lalr1.cc:513
namespace isc { namespace dhcp {
#line 146 "dhcp6_parser.cc" // lalr1.cc:513

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
        std::string yyr = "";
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
              // Fall through.
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


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
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

#if defined __cplusplus && 201103L <= __cplusplus
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

#if !defined __cplusplus || __cplusplus < 201103L
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 177: // "constant string"

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 178: // "integer"

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 179: // "floating point"

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 180: // "boolean"

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 198: // value

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 202: // map_value

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 259: // db_type

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 352: // hr_mode

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 488: // duid_type

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 523: // ncr_protocol_value

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 530: // replace_client_name_value

#line 256 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 468 "dhcp6_parser.cc" // lalr1.cc:672
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
#if defined __cplusplus && 201103L <= __cplusplus
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

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
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
  | yyreduce -- Do a reduction.  |
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
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
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
#line 265 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 266 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 267 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 268 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 269 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 272 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 273 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 274 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 275 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 276 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 277 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 278 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 279 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 287 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 288 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 289 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 290 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 291 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 292 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 293 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 296 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 301 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 41:
#line 306 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 42:
#line 312 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 319 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 323 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 47:
#line 330 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 48:
#line 333 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 341 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 345 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 53:
#line 352 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 54:
#line 354 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 363 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 367 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 378 "dhcp6_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 60:
#line 388 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 61:
#line 393 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1013 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 70:
#line 416 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 71:
#line 423 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 72:
#line 431 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 73:
#line 435 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 484 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 486 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 492 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 497 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 502 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 507 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 118:
#line 512 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 119:
#line 517 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 120:
#line 522 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 121:
#line 527 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1145 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 122:
#line 532 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1153 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 123:
#line 534 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 124:
#line 540 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1174 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 125:
#line 545 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 126:
#line 551 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1194 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 127:
#line 555 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 135:
#line 571 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 136:
#line 576 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1223 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 137:
#line 581 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1232 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 587 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 592 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1254 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 140:
#line 599 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1265 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 141:
#line 604 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 142:
#line 611 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1287 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 143:
#line 616 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1296 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 629 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 633 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1316 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 172:
#line 665 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 173:
#line 667 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1333 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 174:
#line 672 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1339 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 175:
#line 673 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1345 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 176:
#line 674 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1351 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 177:
#line 675 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1357 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 178:
#line 678 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1365 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 179:
#line 680 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 686 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 688 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 694 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 696 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 702 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1420 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 707 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 709 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 715 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 720 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 725 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 730 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 191:
#line 735 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 192:
#line 740 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 745 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1501 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 750 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 195:
#line 755 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 757 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1528 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 763 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1537 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 768 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 770 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 776 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 778 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1573 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 784 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 786 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1591 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 792 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 797 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 209:
#line 807 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 210:
#line 809 "dhcp6_parser.yy" // lalr1.cc:907
    {

    if ( (string(yystack_[0].value.as< std::string > ()) == "none") ||
         (string(yystack_[0].value.as< std::string > ()) == "warn") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as< std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as< std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1639 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 211:
#line 825 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 212:
#line 830 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1659 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 217:
#line 843 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1668 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 218:
#line 848 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1677 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 219:
#line 853 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1688 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 858 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1697 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 226:
#line 872 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1706 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 227:
#line 877 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1715 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 228:
#line 884 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 889 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 894 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 899 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 236:
#line 912 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1765 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 237:
#line 916 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 238:
#line 922 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 239:
#line 926 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1795 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 245:
#line 941 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 246:
#line 943 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1813 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 247:
#line 949 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 248:
#line 951 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1830 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 249:
#line 957 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 250:
#line 962 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 259:
#line 980 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1860 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 260:
#line 985 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1869 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 261:
#line 990 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1878 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 262:
#line 995 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1887 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 263:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 264:
#line 1005 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 265:
#line 1013 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1916 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 266:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 271:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1935 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 272:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1961 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 273:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1971 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 274:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1981 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 301:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 302:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2007 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 303:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2017 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 304:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 305:
#line 1123 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 306:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2043 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 307:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2053 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 308:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 309:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 310:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2081 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 311:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 312:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2096 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 313:
#line 1155 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2102 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 314:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 315:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2114 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 316:
#line 1160 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 317:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2132 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 318:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2143 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 319:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2152 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 324:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2162 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 325:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2170 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 348:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 349:
#line 1236 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2190 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 350:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2199 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 351:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2207 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 356:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2217 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 357:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2229 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 358:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 359:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1314 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2260 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 377:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 378:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2278 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 379:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 380:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 381:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 382:
#line 1339 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 384:
#line 1347 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 385:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2332 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 386:
#line 1355 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2341 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 387:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2352 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 388:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2361 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 393:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2371 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 394:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2380 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 395:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 396:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2399 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 411:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 415:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2426 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 416:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 417:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 418:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2455 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 423:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 424:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 425:
#line 1492 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 426:
#line 1496 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 437:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2512 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 438:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2520 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 439:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
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
#line 2547 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 440:
#line 1547 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 441:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
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
#line 2584 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 442:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2595 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 443:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2604 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 448:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2614 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 449:
#line 1601 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 450:
#line 1609 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2636 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 451:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2648 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 465:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2656 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 466:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 467:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 468:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 469:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 470:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2702 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 471:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 472:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2722 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 473:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2731 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2741 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2750 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 497:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2780 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2809 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 501:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 502:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2827 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 503:
#line 1758 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 504:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 505:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 506:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 507:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2871 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 508:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2881 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 509:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2892 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 510:
#line 1787 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2901 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 511:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2912 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 512:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 515:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2929 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2939 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2950 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 518:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2959 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 521:
#line 1834 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 522:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2979 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2997 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3006 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 538:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3028 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 551:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 552:
#line 1908 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3045 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 553:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3051 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 554:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3057 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 555:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 556:
#line 1918 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3072 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 557:
#line 1923 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 558:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 559:
#line 1931 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3099 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 560:
#line 1936 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3117 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 562:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3128 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 563:
#line 1955 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3137 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 571:
#line 1971 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3145 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 572:
#line 1973 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 573:
#line 1979 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 574:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr qc = yystack_[0].value.as< ElementPtr > ();
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
#line 3221 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3232 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 578:
#line 2034 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3243 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 2045 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3263 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 601:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3272 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 602:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3280 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3290 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2088 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3298 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3308 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2096 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3317 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3325 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2103 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3335 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2109 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3344 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2114 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3353 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 611:
#line 2119 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3361 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 612:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3370 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 613:
#line 2127 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3376 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3382 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2131 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3390 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2133 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3400 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2139 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3409 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2144 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3418 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3426 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2151 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3435 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2157 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3443 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 622:
#line 2160 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3451 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 623:
#line 2163 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3459 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 624:
#line 2166 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3467 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 625:
#line 2169 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3476 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 626:
#line 2175 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3484 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 627:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3494 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 628:
#line 2183 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3502 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3512 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2191 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3520 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2193 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2201 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3538 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2203 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3547 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 634:
#line 2208 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3555 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2210 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3564 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2215 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3572 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2217 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3581 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 638:
#line 2224 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3592 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 639:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3602 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 640:
#line 2235 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3612 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 641:
#line 2239 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3621 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 646:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3632 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 647:
#line 2259 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3641 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 648:
#line 2264 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 649:
#line 2274 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3661 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 650:
#line 2279 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3670 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 651:
#line 2284 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3680 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 652:
#line 2288 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3688 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 656:
#line 2304 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3699 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 657:
#line 2309 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3708 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 660:
#line 2321 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3718 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 661:
#line 2325 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3726 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 671:
#line 2342 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3735 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 672:
#line 2347 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3743 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 673:
#line 2349 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3753 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 674:
#line 2355 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3764 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 675:
#line 2360 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3773 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 678:
#line 2369 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3783 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 679:
#line 2373 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3791 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 686:
#line 2387 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 687:
#line 2389 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3809 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 688:
#line 2395 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3818 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 689:
#line 2400 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3827 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 690:
#line 2405 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3836 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 3840 "dhcp6_parser.cc" // lalr1.cc:907
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
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

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

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


  const short Dhcp6Parser::yypact_ninf_ = -851;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     380,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,    94,    40,    53,    78,
     103,   105,   121,   123,   145,   170,   176,   183,   204,   238,
     241,   249,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,    40,    37,    28,    72,    23,   237,    81,   196,
     253,   208,    76,   263,   -64,   387,   111,    60,  -851,   269,
     273,   275,   288,   299,  -851,  -851,  -851,  -851,  -851,   302,
    -851,    74,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,   304,   313,   320,   323,   326,   333,
     340,   343,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   344,
    -851,  -851,  -851,  -851,   124,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,   353,  -851,   133,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,   359,   365,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   139,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
     147,  -851,  -851,  -851,  -851,  -851,   395,  -851,   397,   401,
    -851,  -851,  -851,  -851,  -851,  -851,   160,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,   348,   331,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,   373,  -851,  -851,   408,  -851,  -851,
    -851,   412,  -851,  -851,   409,   338,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   415,
     416,  -851,  -851,  -851,  -851,   414,   364,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   177,
    -851,  -851,  -851,   419,  -851,  -851,   421,  -851,   422,   423,
    -851,  -851,   438,   449,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,   188,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   189,
    -851,  -851,  -851,   451,   198,  -851,  -851,  -851,  -851,    40,
      40,  -851,   281,   457,   472,   475,   478,   479,  -851,    28,
    -851,   480,   481,   482,   484,   485,   486,   274,   314,   316,
     317,   311,   318,   321,   324,   494,   495,   497,   499,   501,
     502,   506,   507,   508,   509,   510,   524,   525,   526,   527,
     528,   529,   360,   533,   535,   536,    72,  -851,   554,   379,
      23,  -851,   556,   557,   558,   559,   561,   390,   391,   566,
     568,   569,   237,  -851,   570,    81,  -851,   571,   398,   573,
     400,   403,   196,  -851,   576,   580,   582,   583,   584,   585,
     588,  -851,   253,  -851,   589,   590,   417,   592,   593,   594,
     420,  -851,    76,   595,   424,   425,  -851,   263,   597,   598,
      98,  -851,   426,   599,   603,   430,   605,   432,   433,   608,
     610,   435,   440,   614,   617,   618,   619,   387,  -851,   620,
     111,  -851,   621,   450,    60,  -851,  -851,  -851,   622,   623,
     624,    40,    40,    40,  -851,   452,   625,   626,   627,   628,
     631,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   460,
     633,   634,   635,   636,   464,   386,   637,   639,   640,   641,
     642,   643,   645,   646,   647,   648,  -851,   649,   636,   650,
    -851,   653,  -851,  -851,   654,   655,   470,   476,   487,  -851,
    -851,   653,   488,   656,  -851,   489,  -851,   490,  -851,   491,
    -851,  -851,  -851,   653,   653,   653,   492,   493,   496,   498,
    -851,   500,   503,  -851,   504,   505,   511,  -851,  -851,   512,
    -851,  -851,  -851,   513,    40,  -851,  -851,   514,   515,  -851,
     516,  -851,  -851,    85,   518,  -851,  -851,   -82,   517,   519,
     520,  -851,   657,  -851,   666,  -851,  -851,    40,    72,   111,
    -851,  -851,  -851,  -851,    60,    23,   202,   202,   665,  -851,
     667,   669,   671,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,   672,   -48,    40,   -55,   538,   676,   677,   678,    -9,
     152,    97,  -851,   387,  -851,  -851,   679,   680,  -851,  -851,
    -851,  -851,  -851,   -17,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   688,   665,
    -851,   199,   243,   244,   251,  -851,  -851,  -851,  -851,   694,
     695,   696,   697,   698,  -851,   699,   700,  -851,  -851,  -851,
     701,   702,   703,  -851,   252,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,   286,  -851,   704,   705,  -851,
    -851,   706,   708,  -851,  -851,   707,   711,  -851,  -851,   709,
     713,  -851,  -851,   712,   714,  -851,  -851,  -851,   108,  -851,
    -851,  -851,   715,  -851,  -851,  -851,   137,  -851,  -851,  -851,
    -851,   289,  -851,  -851,  -851,   168,  -851,  -851,   716,   717,
    -851,  -851,   718,   720,  -851,   721,   722,   723,   724,   725,
     726,   290,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,   727,   728,   729,  -851,  -851,  -851,  -851,   292,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
     296,  -851,  -851,  -851,   330,   532,  -851,   730,   731,  -851,
    -851,   732,   734,  -851,  -851,  -851,   644,  -851,  -851,   178,
    -851,   733,  -851,  -851,  -851,  -851,   736,   737,   738,   739,
     541,   555,   567,   564,   572,   742,   574,   575,   743,   744,
     745,   577,   578,   579,   202,  -851,  -851,   202,  -851,   665,
     237,  -851,   667,    76,  -851,   669,   263,  -851,   671,   402,
    -851,   672,   -48,  -851,  -851,   -55,  -851,   747,   538,  -851,
      16,   676,  -851,   253,  -851,   677,   -64,  -851,   678,   586,
     587,   591,   596,   600,   601,    -9,  -851,   750,   753,   602,
     604,   606,   152,  -851,   754,   756,    97,  -851,  -851,  -851,
     755,   759,    81,  -851,   679,   196,  -851,   680,   762,  -851,
     310,   688,  -851,  -851,   448,   609,   611,   612,  -851,  -851,
    -851,  -851,  -851,   613,  -851,  -851,   615,   616,   652,  -851,
    -851,  -851,  -851,   337,  -851,   352,  -851,   760,  -851,   763,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,   356,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,   662,  -851,  -851,   766,
    -851,  -851,  -851,  -851,  -851,   764,   770,  -851,  -851,  -851,
    -851,  -851,   767,  -851,   363,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,   319,   663,  -851,  -851,  -851,  -851,   668,
     670,  -851,  -851,   684,   377,  -851,   392,  -851,   685,  -851,
     772,  -851,  -851,  -851,  -851,  -851,   399,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   402,  -851,
    -851,   773,   607,  -851,    16,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   777,   687,
     779,   310,  -851,  -851,   686,  -851,  -851,   758,  -851,   693,
    -851,  -851,   778,  -851,  -851,   207,  -851,     8,   778,  -851,
    -851,   787,   790,   791,   407,  -851,  -851,  -851,  -851,  -851,
    -851,   793,   651,   719,   735,     8,  -851,   710,  -851,  -851,
    -851,  -851,  -851
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   126,     9,
     273,    11,   425,    13,   450,    15,   480,    17,   350,    19,
     358,    21,   395,    23,   238,    25,   579,    27,   651,    29,
     640,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     482,     0,   360,   397,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   649,   632,   634,   636,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   112,   638,
     124,   138,   140,   142,     0,     0,     0,     0,     0,     0,
       0,     0,   122,   265,   348,   387,   438,   440,   310,   318,
     211,   228,   219,   204,   517,   472,   230,   249,   538,     0,
     562,   575,   577,   111,     0,    74,    76,    77,    78,    79,
      80,   108,   109,   110,    81,   106,    84,    85,    86,    87,
     103,    88,    90,    89,    94,    95,    82,   107,    83,    92,
      93,   101,   102,   104,    91,    96,    97,    98,    99,   100,
     105,   135,     0,   134,     0,   128,   130,   131,   132,   133,
     417,   442,   300,   302,   304,     0,     0,   308,   306,   511,
     299,   277,   278,   279,   280,   296,   297,   298,     0,   275,
     284,   285,   286,   289,   290,   292,   287,   288,   281,   282,
     294,   295,   283,   291,   293,   436,   435,   431,   432,   430,
       0,   427,   429,   433,   434,   465,     0,   468,     0,     0,
     464,   458,   459,   457,   462,   463,     0,   452,   454,   455,
     460,   461,   456,   509,   497,   499,   501,   503,   505,   507,
     496,   493,   494,   495,     0,   483,   484,   488,   489,   486,
     490,   491,   492,   487,     0,   377,   185,     0,   381,   379,
     384,     0,   373,   374,     0,   361,   362,   364,   376,   365,
     366,   367,   383,   368,   369,   370,   371,   372,   411,     0,
       0,   409,   410,   413,   414,     0,   398,   399,   401,   402,
     403,   404,   405,   406,   407,   408,   245,   247,   242,     0,
     240,   243,   244,     0,   602,   604,     0,   607,     0,     0,
     611,   615,     0,     0,   619,   626,   628,   630,   600,   598,
     599,     0,   581,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   656,     0,
     653,   655,   646,     0,     0,   642,   644,   645,    48,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    59,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   127,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   274,     0,     0,   426,     0,     0,     0,
       0,     0,     0,   451,     0,     0,     0,     0,     0,     0,
       0,   481,     0,   351,     0,     0,     0,     0,     0,     0,
       0,   359,     0,     0,     0,     0,   396,     0,     0,     0,
       0,   239,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   580,     0,
       0,   652,     0,     0,     0,   641,    52,    45,     0,     0,
       0,     0,     0,     0,    63,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   561,     0,     0,     0,
      75,     0,   137,   129,     0,     0,     0,     0,     0,   316,
     317,     0,     0,     0,   276,     0,   428,     0,   467,     0,
     470,   471,   453,     0,     0,     0,     0,     0,     0,     0,
     485,     0,     0,   375,     0,     0,     0,   386,   363,     0,
     415,   416,   400,     0,     0,   241,   601,     0,     0,   606,
       0,   609,   610,     0,     0,   617,   618,     0,     0,     0,
       0,   582,     0,   654,     0,   648,   643,     0,     0,     0,
     633,   635,   637,   113,     0,     0,     0,     0,   144,   123,
     267,   352,   389,    42,   439,   441,   312,   313,   314,   315,
     311,   320,     0,    49,     0,     0,     0,   474,   232,     0,
       0,     0,   576,     0,    53,   136,   419,   444,   301,   303,
     305,   309,   307,     0,   437,   466,   469,   510,   498,   500,
     502,   504,   506,   508,   378,   186,   382,   380,   385,   412,
     246,   248,   603,   605,   608,   613,   614,   612,   616,   621,
     622,   623,   624,   625,   620,   627,   629,   631,     0,   144,
      46,     0,     0,     0,     0,   172,   178,   180,   182,     0,
       0,     0,     0,     0,   195,     0,     0,   198,   200,   202,
       0,     0,     0,   171,     0,   150,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   164,   165,   166,   167,
     162,   163,   168,   169,   170,     0,   148,     0,   145,   146,
     271,     0,   268,   269,   356,     0,   353,   354,   393,     0,
     390,   391,   324,     0,   321,   322,   217,   218,     0,   213,
     215,   216,     0,   226,   227,   223,     0,   221,   224,   225,
     209,     0,   206,   208,   521,     0,   519,   478,     0,   475,
     476,   236,     0,   233,   234,     0,     0,     0,     0,     0,
       0,     0,   251,   253,   254,   255,   256,   257,   258,   551,
     557,     0,     0,     0,   550,   547,   548,   549,     0,   540,
     542,   545,   543,   544,   546,   571,   573,   570,   568,   569,
       0,   564,   566,   567,     0,    55,   423,     0,   420,   421,
     448,     0,   445,   446,   515,   514,     0,   513,   660,     0,
     658,     0,    71,   650,   639,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   139,   141,     0,   143,     0,
       0,   266,     0,   360,   349,     0,   397,   388,     0,     0,
     319,     0,     0,   212,   229,     0,   220,     0,     0,   205,
     523,     0,   518,   482,   473,     0,     0,   231,     0,     0,
       0,     0,     0,     0,     0,     0,   250,     0,     0,     0,
       0,     0,     0,   539,     0,     0,     0,   563,   578,    57,
       0,    56,     0,   418,     0,     0,   443,     0,     0,   512,
       0,     0,   657,   647,     0,     0,     0,     0,   184,   187,
     188,   189,   190,     0,   197,   191,     0,     0,     0,   192,
     193,   194,   151,     0,   147,     0,   270,     0,   355,     0,
     392,   347,   339,   341,   332,   333,   344,   345,   346,   328,
     329,   330,   331,   337,   338,   336,   340,     0,   326,   334,
     342,   343,   335,   323,   214,   222,     0,   207,   535,     0,
     533,   534,   530,   531,   532,     0,   524,   525,   527,   528,
     529,   520,     0,   477,     0,   235,   259,   260,   261,   262,
     263,   264,   252,     0,     0,   556,   559,   560,   541,     0,
       0,   565,    54,     0,     0,   422,     0,   447,     0,   674,
       0,   672,   670,   664,   668,   669,     0,   662,   666,   667,
     665,   659,   174,   175,   176,   177,   173,   179,   181,   183,
     196,   199,   201,   203,   149,   272,   357,   394,     0,   325,
     210,     0,     0,   522,     0,   479,   237,   553,   554,   555,
     552,   558,   572,   574,    58,   424,   449,   516,     0,     0,
       0,     0,   661,   327,     0,   537,   526,     0,   671,     0,
     663,   536,     0,   673,   678,     0,   676,     0,     0,   675,
     686,     0,     0,     0,     0,   680,   682,   683,   684,   685,
     677,     0,     0,     0,     0,     0,   679,     0,   688,   689,
     690,   681,   687
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,     6,  -851,  -466,
    -851,   229,  -851,  -851,  -851,  -851,   165,  -851,  -458,  -851,
    -851,  -851,   -74,  -851,  -851,  -851,   434,  -851,  -851,  -851,
    -851,   193,   388,  -851,  -851,   -62,   -46,   -45,   -43,   -42,
     -29,   -26,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   211,
     394,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
     122,  -851,   -39,  -851,  -589,   -41,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,   -70,  -851,  -624,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   -31,  -851,
    -851,  -851,  -851,  -851,    -8,  -608,  -851,  -851,  -851,  -851,
     -12,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   -23,
    -851,  -851,  -851,   -53,   413,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,   -28,  -851,  -851,  -851,  -851,  -851,  -851,  -850,
    -851,  -851,  -851,    12,  -851,  -851,  -851,    15,   446,  -851,
    -851,  -849,  -851,  -846,  -851,    -3,  -851,     2,  -851,     1,
    -851,  -851,  -851,  -843,  -851,  -851,  -851,  -851,     5,  -851,
    -851,  -169,   809,  -851,  -851,  -851,  -851,  -851,    18,  -851,
    -851,  -851,    21,  -851,   429,  -851,   -76,  -851,  -851,  -851,
    -851,  -851,   -69,  -851,  -851,  -851,  -851,  -851,   -11,  -851,
    -851,  -851,    17,  -851,  -851,  -851,    20,  -851,   436,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
     -25,  -851,  -851,  -851,   -22,   467,  -851,  -851,   -58,  -851,
     -24,  -851,  -851,  -851,  -851,  -851,   -20,  -851,  -851,  -851,
     -21,   463,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   -60,
    -851,  -851,  -851,    13,  -851,  -851,  -851,    19,  -851,   458,
     256,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -842,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,    24,  -851,  -851,  -851,  -148,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,     9,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,     4,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,   280,   431,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,  -851,   303,   437,  -851,  -851,
    -851,  -851,  -851,  -851,  -851,   325,   439,  -851,  -851,  -851,
      -6,  -851,  -851,  -155,  -851,  -851,  -851,  -851,  -851,  -851,
    -170,  -851,  -851,  -185,  -851,  -851,  -851,  -851,  -851
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   624,    92,    93,    43,    72,    89,    90,   645,   825,
     920,   921,   713,    45,    74,   101,   102,   103,   373,    47,
      75,   144,   145,   146,   381,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   395,   156,   383,    49,    76,   184,
     185,   186,   418,   187,   157,   384,   158,   385,   159,   386,
     737,   738,   739,   867,   714,   715,   716,   846,  1046,   717,
     847,   718,   848,   719,   849,   720,   721,   455,   722,   723,
     724,   725,   726,   727,   728,   729,   730,   855,   731,   732,
     858,   733,   859,   734,   860,   160,   406,   771,   772,   773,
     887,   161,   403,   758,   759,   760,   761,   162,   405,   766,
     767,   768,   769,   163,   404,   164,   409,   782,   783,   784,
     896,    65,    84,   319,   320,   321,   468,   322,   469,   165,
     410,   791,   792,   793,   794,   795,   796,   797,   798,   166,
     396,   741,   742,   743,   870,    51,    77,   208,   209,   210,
     424,   211,   425,   212,   426,   213,   430,   214,   429,   167,
     401,   630,   216,   217,   168,   402,   753,   754,   755,   879,
     977,   978,   169,   397,    59,    81,   745,   746,   747,   873,
      61,    82,   284,   285,   286,   287,   288,   289,   290,   454,
     291,   458,   292,   457,   293,   294,   459,   295,   170,   398,
     749,   750,   751,   876,    63,    83,   305,   306,   307,   308,
     309,   463,   310,   311,   312,   313,   219,   422,   827,   828,
     829,   922,    53,    78,   230,   231,   232,   434,   171,   399,
     172,   400,   222,   423,   831,   832,   833,   925,    55,    79,
     246,   247,   248,   437,   249,   250,   439,   251,   252,   173,
     408,   778,   779,   780,   893,    57,    80,   264,   265,   266,
     267,   445,   268,   446,   269,   447,   270,   448,   271,   449,
     272,   450,   273,   444,   224,   431,   836,   837,   928,   174,
     407,   775,   776,   890,   995,   996,   997,   998,   999,  1061,
    1000,   175,   411,   808,   809,   810,   907,  1070,   811,   812,
     908,   813,   814,   176,   177,   413,   820,   821,   822,   914,
     823,   915,   178,   414,   179,   415,    67,    85,   341,   342,
     343,   344,   473,   345,   474,   346,   347,   476,   348,   349,
     350,   479,   677,   351,   480,   352,   353,   354,   483,   684,
     355,   484,   356,   485,   357,   486,   104,   375,   105,   376,
     106,   377,   180,   382,    71,    87,   364,   365,   366,   492,
     367,   107,   374,    69,    86,   359,   360,   361,   489,   839,
     840,   930,  1036,  1037,  1038,  1039,  1080,  1040,  1078,  1095,
    1096,  1097,  1104,  1105,  1106,  1111,  1107,  1108,  1109
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   143,   183,   200,   226,   240,   260,   303,   282,   301,
     318,   338,   283,   302,   304,   201,   805,   223,   188,   220,
     233,   244,   262,    40,   296,   314,   765,   339,   735,   970,
     971,   202,   203,   972,   204,   205,   976,   982,    94,   181,
     182,   316,   317,   756,   763,    33,   764,    34,   206,    35,
     756,   207,   189,   221,   234,   245,   263,   623,   297,   315,
      44,   340,   679,   680,   681,   682,   218,   229,   243,   261,
     125,   276,   623,   362,   363,   227,   241,   379,   215,   254,
     228,   242,   380,   108,   109,    46,   834,   110,   126,   127,
     111,   112,   113,   651,    32,   126,   127,   275,   683,   785,
     786,   787,   788,   789,   790,   657,   658,   659,   988,   989,
      48,   882,    50,    99,   883,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   416,    52,   757,
      54,   276,   417,   277,   278,   125,   420,   279,   280,   281,
     885,   421,   432,   886,   126,   127,   225,   433,   126,   127,
     435,   128,    56,   126,   127,   436,   129,   130,   131,   132,
     133,  1100,   134,   442,  1101,  1102,  1103,   135,   443,   126,
     127,   891,   197,   799,   892,   198,   136,    58,    95,   137,
     470,   931,   700,    60,   932,   471,   138,    96,    97,    98,
      62,   487,   490,    99,   139,   140,   488,   491,   141,   142,
      99,   494,   416,   316,   317,    99,   495,   842,   970,   971,
    1098,    64,   972,  1099,    91,   976,   982,    36,    37,    38,
      39,   815,   816,   695,   126,   127,   675,   676,   696,   697,
     698,   699,   700,   701,   702,   703,   704,   705,   706,   707,
     708,   709,   710,   711,   712,    66,   490,   494,    68,    99,
     125,   843,   844,    99,   420,   864,    70,   276,    99,   845,
     865,   124,   358,   235,   236,   237,   238,   239,   126,   127,
     800,   801,   802,   803,    99,   368,   369,   765,   953,   370,
     114,   115,   116,   117,   118,   119,   120,   197,   805,   864,
     198,   125,   888,   905,   866,   912,   371,   889,   906,   916,
     913,   190,   372,   191,   917,   100,   378,   125,   387,   126,
     127,   192,   193,   194,   195,   196,   128,   388,   276,   298,
     277,   278,   299,   300,   389,   126,   127,   390,   197,    99,
     391,   198,   135,   487,   452,   126,   127,   392,   918,   199,
     864,   462,   143,   253,   393,  1054,   183,   394,   412,   254,
     255,   256,   257,   258,   259,   432,   451,   419,   200,  1058,
    1055,   226,   188,   427,  1059,   276,   470,   467,   240,   428,
     201,  1066,   223,    99,   220,   496,   497,   233,   260,    99,
     435,   453,   126,   127,   244,  1075,   202,   203,   282,   204,
     205,   303,   283,   301,   262,   442,   189,   302,   304,   438,
    1076,   440,  1081,   206,   296,   441,   207,  1082,   221,   314,
    1115,   234,   456,   338,    99,  1116,   460,   461,   245,   464,
     465,   218,   466,   472,   229,   475,   477,   478,   263,   339,
      99,   243,   227,   215,  1067,  1068,  1069,   228,   297,   241,
      99,   261,   481,   315,   242,   114,   115,   116,   117,   118,
     119,   120,   511,   482,   123,   493,   125,   276,   498,   126,
     127,   499,  1029,   340,  1030,  1031,   626,   627,   628,   629,
    1042,  1043,  1044,  1045,   126,   127,   500,   193,   194,   501,
     196,   128,   502,   503,   505,   506,   507,    99,   508,   509,
     510,   515,   512,   197,   513,   514,   198,   516,   519,   520,
     517,   521,   518,   522,   199,   523,   524,   610,   611,   612,
     525,   526,   527,   528,   529,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   530,   531,
     532,   533,   534,   535,   143,   336,   337,   537,   536,   538,
     539,   183,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   188,   541,   542,
     544,   545,   546,   547,    99,   548,   804,   817,   549,   338,
     551,   550,   552,   553,   555,   557,   558,   559,   560,    99,
     563,   561,   806,   818,   564,   339,   565,   566,   567,   568,
     671,   189,   569,   571,   572,   573,   574,   575,   576,   579,
     577,   583,   584,   587,   580,   581,   586,   588,   589,   590,
     591,   592,   593,   690,   594,   595,   807,   819,   597,   340,
     596,   598,   599,   600,   602,   604,   607,   770,   605,   613,
     608,   609,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   625,   631,    34,   632,   633,   634,   648,   636,   635,
     637,   638,   929,   649,   639,   640,   641,   643,   644,   646,
     647,   678,   688,   653,   650,   652,   654,   655,   656,   660,
     661,   689,   736,   662,   740,   663,   744,   664,   748,   752,
     665,   666,   667,   774,   777,   781,   826,   830,   668,   669,
     670,   672,   673,   674,   685,   838,   686,   687,   850,   851,
     852,   853,   854,   856,   857,   861,   862,   863,   869,   919,
     868,   872,   871,   874,   875,   877,   878,   881,   880,   938,
     895,   884,   894,   898,   897,   899,   900,   901,   902,   903,
     904,   909,   910,   911,   924,   939,   923,   927,   926,   933,
     934,   935,   936,   937,   941,   940,   943,   946,   947,   948,
     942,   986,   944,   945,  1013,   949,   950,  1014,  1019,   951,
    1020,  1022,  1023,  1092,  1006,  1007,  1028,   642,  1056,  1008,
    1062,  1057,  1063,  1064,  1009,  1065,  1079,  1084,  1010,  1011,
    1015,  1087,  1016,  1089,  1017,  1094,  1047,  1085,  1048,  1049,
    1050,  1112,  1051,  1052,  1113,  1114,   200,  1117,   762,   282,
     303,   691,   301,   283,   540,   961,   302,   304,   201,   969,
     223,   841,   220,   504,   543,   296,   990,   962,   314,   260,
     991,   980,   318,   952,   202,   203,   694,   204,   205,  1053,
     954,  1118,   993,   963,   964,   262,   965,   966,   804,  1060,
    1071,   206,   817,  1004,   207,  1072,   221,  1073,   226,   297,
     967,   240,   315,   968,   806,   981,  1032,   987,   818,   218,
    1033,  1074,  1077,  1091,   233,  1088,   994,   244,   979,   263,
    1093,   215,  1034,   985,   984,  1005,   973,  1012,   554,   992,
     975,   974,   261,   585,   956,   955,   983,  1122,   807,  1083,
     274,   578,   819,   958,   957,   960,   959,  1119,   234,  1025,
    1024,   245,   556,   582,  1026,   562,  1035,  1027,  1003,   835,
     570,   229,  1002,  1120,   243,  1001,  1086,   693,   601,   227,
    1021,  1018,   241,   824,   228,  1041,  1090,   242,  1110,   603,
    1121,   606,     0,     0,   692,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   961,     0,     0,     0,   969,     0,
     990,     0,     0,     0,   991,     0,   962,     0,     0,     0,
     980,     0,     0,     0,     0,     0,   993,  1032,     0,     0,
       0,  1033,   963,   964,     0,   965,   966,     0,     0,     0,
       0,     0,     0,  1034,     0,     0,     0,     0,     0,   967,
       0,     0,   968,     0,   981,     0,     0,     0,     0,     0,
     994,     0,     0,     0,     0,     0,     0,   979,     0,     0,
       0,     0,     0,   992,     0,   973,     0,  1035,     0,   975,
     974
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    82,    83,    83,    77,   640,    77,    76,    77,
      78,    79,    80,    17,    82,    83,   634,    85,   617,   879,
     879,    77,    77,   879,    77,    77,   879,   879,    10,    16,
      17,   105,   106,    98,    99,     5,   101,     7,    77,     9,
      98,    77,    76,    77,    78,    79,    80,   523,    82,    83,
       7,    85,   144,   145,   146,   147,    77,    78,    79,    80,
      54,    55,   538,    13,    14,    78,    79,     3,    77,    96,
      78,    79,     8,    11,    12,     7,   103,    15,    72,    73,
      18,    19,    20,   551,     0,    72,    73,    21,   180,   108,
     109,   110,   111,   112,   113,   563,   564,   565,    92,    93,
       7,     3,     7,   177,     6,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,     3,     7,   177,
       7,    55,     8,    57,    58,    54,     3,    61,    62,    63,
       3,     8,     3,     6,    72,    73,    65,     8,    72,    73,
       3,    79,     7,    72,    73,     8,    84,    85,    86,    87,
      88,   153,    90,     3,   156,   157,   158,    95,     8,    72,
      73,     3,    91,    21,     6,    94,   104,     7,   150,   107,
       3,     3,    30,     7,     6,     8,   114,   159,   160,   161,
       7,     3,     3,   177,   122,   123,     8,     8,   126,   127,
     177,     3,     3,   105,   106,   177,     8,     8,  1058,  1058,
       3,     7,  1058,     6,   177,  1058,  1058,   177,   178,   179,
     180,   124,   125,    21,    72,    73,   141,   142,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     7,     3,     3,     7,   177,
      54,     8,     8,   177,     3,     3,     7,    55,   177,     8,
       8,    53,   151,    67,    68,    69,    70,    71,    72,    73,
     118,   119,   120,   121,   177,     6,     3,   885,   867,     4,
      43,    44,    45,    46,    47,    48,    49,    91,   912,     3,
      94,    54,     3,     3,     8,     3,     8,     8,     8,     3,
       8,    64,     3,    66,     8,   379,     4,    54,     4,    72,
      73,    74,    75,    76,    77,    78,    79,     4,    55,    56,
      57,    58,    59,    60,     4,    72,    73,     4,    91,   177,
       4,    94,    95,     3,     3,    72,    73,     4,     8,   102,
       3,     3,   416,    90,     4,     8,   420,     4,     4,    96,
      97,    98,    99,   100,   101,     3,     8,     4,   432,     3,
       8,   435,   420,     4,     8,    55,     3,     3,   442,     4,
     432,     8,   432,   177,   432,   369,   370,   435,   452,   177,
       3,     8,    72,    73,   442,     8,   432,   432,   462,   432,
     432,   467,   462,   467,   452,     3,   420,   467,   467,     4,
       8,     4,     3,   432,   462,     4,   432,     8,   432,   467,
       3,   435,     4,   487,   177,     8,     4,     8,   442,     4,
       4,   432,     8,     4,   435,     4,     4,     4,   452,   487,
     177,   442,   435,   432,   115,   116,   117,   435,   462,   442,
     177,   452,     4,   467,   442,    43,    44,    45,    46,    47,
      48,    49,   178,     4,    52,     4,    54,    55,   177,    72,
      73,     4,   152,   487,   154,   155,    80,    81,    82,    83,
      22,    23,    24,    25,    72,    73,     4,    75,    76,     4,
      78,    79,     4,     4,     4,     4,     4,   177,     4,     4,
       4,   180,   178,    91,   178,   178,    94,   179,     4,     4,
     179,     4,   178,     4,   102,     4,     4,   501,   502,   503,
       4,     4,     4,     4,     4,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     4,     4,
       4,     4,     4,     4,   608,   148,   149,     4,   178,     4,
       4,   615,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   615,     4,   180,
       4,     4,     4,     4,   177,     4,   640,   641,   178,   643,
       4,   180,     4,     4,     4,     4,   178,     4,   178,   177,
       4,   178,   640,   641,     4,   643,     4,     4,     4,     4,
     584,   615,     4,     4,     4,   178,     4,     4,     4,     4,
     180,     4,     4,     4,   180,   180,   180,     4,   178,     4,
     178,   178,     4,   607,     4,   180,   640,   641,     4,   643,
     180,     4,     4,     4,     4,     4,     4,    89,   178,   177,
       7,     7,     7,     7,     7,     7,     5,   177,     5,     5,
       5,   177,     5,     7,     5,     5,     5,   177,     5,     7,
       5,     5,     8,   177,     7,     7,     7,     7,     5,     5,
       5,   143,     5,     7,   177,   177,   177,   177,   177,   177,
     177,     5,     7,   177,     7,   177,     7,   177,     7,     7,
     177,   177,   177,     7,     7,     7,     7,     7,   177,   177,
     177,   177,   177,   177,   177,     7,   177,   177,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   177,
       6,     3,     6,     6,     3,     6,     3,     3,     6,   178,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   180,     6,     3,     6,     6,
       4,     4,     4,     4,   180,   178,     4,     4,     4,     4,
     178,     4,   178,   178,     4,   178,   178,     4,     4,   180,
       4,     6,     3,     5,   178,   178,     4,   538,     8,   178,
       4,     8,     8,     3,   178,     8,     4,     4,   178,   178,
     178,     4,   178,     4,   178,     7,   177,   180,   177,   177,
     177,     4,   177,   177,     4,     4,   870,     4,   633,   873,
     876,   608,   876,   873,   416,   879,   876,   876,   870,   879,
     870,   689,   870,   379,   420,   873,   890,   879,   876,   893,
     890,   879,   896,   864,   870,   870,   615,   870,   870,   177,
     869,   180,   890,   879,   879,   893,   879,   879,   912,   177,
     177,   870,   916,   896,   870,   177,   870,   177,   922,   873,
     879,   925,   876,   879,   912,   879,   930,   888,   916,   870,
     930,   177,   177,   177,   922,   178,   890,   925,   879,   893,
     177,   870,   930,   885,   882,   898,   879,   905,   432,   890,
     879,   879,   893,   470,   872,   870,   881,   177,   912,  1058,
      81,   462,   916,   875,   873,   878,   876,   178,   922,   924,
     922,   925,   435,   467,   925,   442,   930,   927,   895,   653,
     452,   922,   893,   178,   925,   891,  1064,   614,   487,   922,
     916,   912,   925,   643,   922,   931,  1081,   925,  1098,   490,
    1115,   494,    -1,    -1,   609,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1058,    -1,    -1,    -1,  1058,    -1,
    1064,    -1,    -1,    -1,  1064,    -1,  1058,    -1,    -1,    -1,
    1058,    -1,    -1,    -1,    -1,    -1,  1064,  1081,    -1,    -1,
      -1,  1081,  1058,  1058,    -1,  1058,  1058,    -1,    -1,    -1,
      -1,    -1,    -1,  1081,    -1,    -1,    -1,    -1,    -1,  1058,
      -1,    -1,  1058,    -1,  1058,    -1,    -1,    -1,    -1,    -1,
    1064,    -1,    -1,    -1,    -1,    -1,    -1,  1058,    -1,    -1,
      -1,    -1,    -1,  1064,    -1,  1058,    -1,  1081,    -1,  1058,
    1058
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
     123,   126,   127,   213,   222,   223,   224,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   236,   245,   247,   249,
     286,   292,   298,   304,   306,   320,   330,   350,   355,   363,
     389,   419,   421,   440,   470,   482,   494,   495,   503,   505,
     543,    16,    17,   213,   240,   241,   242,   244,   419,   421,
      64,    66,    74,    75,    76,    77,    78,    91,    94,   102,
     213,   226,   227,   228,   229,   230,   231,   232,   338,   339,
     340,   342,   344,   346,   348,   350,   353,   354,   389,   407,
     419,   421,   423,   440,   465,    65,   213,   346,   348,   389,
     415,   416,   417,   419,   421,    67,    68,    69,    70,    71,
     213,   346,   348,   389,   419,   421,   431,   432,   433,   435,
     436,   438,   439,    90,    96,    97,    98,    99,   100,   101,
     213,   389,   419,   421,   448,   449,   450,   451,   453,   455,
     457,   459,   461,   463,   363,    21,    55,    57,    58,    61,
      62,    63,   213,   267,   373,   374,   375,   376,   377,   378,
     379,   381,   383,   385,   386,   388,   419,   421,    56,    59,
      60,   213,   267,   377,   383,   397,   398,   399,   400,   401,
     403,   404,   405,   406,   419,   421,   105,   106,   213,   314,
     315,   316,   318,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   148,   149,   213,   419,
     421,   509,   510,   511,   512,   514,   516,   517,   519,   520,
     521,   524,   526,   527,   528,   531,   533,   535,   151,   556,
     557,   558,    13,    14,   547,   548,   549,   551,     6,     3,
       4,     8,     3,   219,   553,   538,   540,   542,     4,     3,
       8,   225,   544,   237,   246,   248,   250,     4,     4,     4,
       4,     4,     4,     4,     4,   235,   331,   364,   390,   420,
     422,   351,   356,   293,   305,   299,   287,   471,   441,   307,
     321,   483,     4,   496,   504,   506,     3,     8,   243,     4,
       3,     8,   408,   424,   341,   343,   345,     4,     4,   349,
     347,   466,     3,     8,   418,     3,     8,   434,     4,   437,
       4,     4,     3,     8,   464,   452,   454,   456,   458,   460,
     462,     8,     3,     8,   380,   268,     4,   384,   382,   387,
       4,     8,     3,   402,     4,     4,     8,     3,   317,   319,
       3,     8,     4,   513,   515,     4,   518,     4,     4,   522,
     525,     4,     4,   529,   532,   534,   536,     3,     8,   559,
       3,     8,   550,     4,     3,     8,   198,   198,   177,     4,
       4,     4,     4,     4,   217,     4,     4,     4,     4,     4,
       4,   178,   178,   178,   178,   180,   179,   179,   178,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   178,     4,     4,     4,
     223,     4,   180,   241,     4,     4,     4,     4,     4,   178,
     180,     4,     4,     4,   339,     4,   416,     4,   178,     4,
     178,   178,   432,     4,     4,     4,     4,     4,     4,     4,
     450,     4,     4,   178,     4,     4,     4,   180,   375,     4,
     180,   180,   399,     4,     4,   315,   180,     4,     4,   178,
       4,   178,   178,     4,     4,   180,   180,     4,     4,     4,
       4,   510,     4,   557,     4,   178,   548,     4,     7,     7,
     198,   198,   198,   177,     7,     7,     7,     7,     5,   177,
       5,     5,     5,   200,   202,   177,    80,    81,    82,    83,
     352,     5,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,   202,     7,     5,   209,     5,     5,   177,   177,
     177,   209,   177,     7,   177,   177,   177,   209,   209,   209,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   198,   177,   177,   177,   141,   142,   523,   143,   144,
     145,   146,   147,   180,   530,   177,   177,   177,     5,     5,
     198,   222,   556,   547,   240,    21,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,   213,   255,   256,   257,   260,   262,   264,
     266,   267,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   279,   280,   282,   284,   255,     7,   251,   252,   253,
       7,   332,   333,   334,     7,   367,   368,   369,     7,   391,
     392,   393,     7,   357,   358,   359,    98,   177,   294,   295,
     296,   297,   207,    99,   101,   296,   300,   301,   302,   303,
      89,   288,   289,   290,     7,   472,   473,     7,   442,   443,
     444,     7,   308,   309,   310,   108,   109,   110,   111,   112,
     113,   322,   323,   324,   325,   326,   327,   328,   329,    21,
     118,   119,   120,   121,   213,   269,   419,   421,   484,   485,
     486,   489,   490,   492,   493,   124,   125,   213,   419,   421,
     497,   498,   499,   501,   509,   210,     7,   409,   410,   411,
       7,   425,   426,   427,   103,   451,   467,   468,     7,   560,
     561,   251,     8,     8,     8,     8,   258,   261,   263,   265,
       4,     4,     4,     4,     4,   278,     4,     4,   281,   283,
     285,     4,     4,     4,     3,     8,     8,   254,     6,     3,
     335,     6,     3,   370,     6,     3,   394,     6,     3,   360,
       6,     3,     3,     6,     6,     3,     6,   291,     3,     8,
     474,     3,     6,   445,     6,     3,   311,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   487,   491,     4,
       4,     4,     3,     8,   500,   502,     3,     8,     8,   177,
     211,   212,   412,     6,     3,   428,     6,     3,   469,     8,
     562,     3,     6,     6,     4,     4,     4,     4,   178,   180,
     178,   180,   178,     4,   178,   178,     4,     4,     4,   178,
     178,   180,   256,   255,   253,   338,   334,   373,   369,   397,
     393,   213,   226,   227,   228,   229,   230,   231,   232,   267,
     330,   342,   344,   346,   348,   350,   354,   361,   362,   389,
     419,   421,   465,   359,   295,   301,     4,   289,    92,    93,
     213,   267,   389,   419,   421,   475,   476,   477,   478,   479,
     481,   473,   448,   444,   314,   310,   178,   178,   178,   178,
     178,   178,   323,     4,     4,   178,   178,   178,   485,     4,
       4,   498,     6,     3,   415,   411,   431,   427,     4,   152,
     154,   155,   213,   267,   419,   421,   563,   564,   565,   566,
     568,   561,    22,    23,    24,    25,   259,   177,   177,   177,
     177,   177,   177,   177,     8,     8,     8,     8,     3,     8,
     177,   480,     4,     8,     3,     8,     8,   115,   116,   117,
     488,   177,   177,   177,   177,     8,     8,   177,   569,     4,
     567,     3,     8,   362,     4,   180,   477,     4,   178,     4,
     564,   177,     5,   177,     7,   570,   571,   572,     3,     6,
     153,   156,   157,   158,   573,   574,   575,   577,   578,   579,
     571,   576,     4,     4,     4,     3,     8,     4,   180,   178,
     178,   574,   177
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
     223,   223,   225,   224,   226,   227,   228,   229,   230,   231,
     232,   233,   235,   234,   237,   236,   239,   238,   240,   240,
     241,   241,   241,   241,   241,   243,   242,   244,   246,   245,
     248,   247,   250,   249,   251,   251,   252,   252,   254,   253,
     255,   255,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   258,   257,   259,   259,   259,   259,   261,   260,
     263,   262,   265,   264,   266,   268,   267,   269,   270,   271,
     272,   273,   274,   275,   276,   278,   277,   279,   281,   280,
     283,   282,   285,   284,   287,   286,   288,   288,   289,   291,
     290,   293,   292,   294,   294,   295,   295,   296,   297,   299,
     298,   300,   300,   301,   301,   301,   302,   303,   305,   304,
     307,   306,   308,   308,   309,   309,   311,   310,   313,   312,
     314,   314,   314,   315,   315,   317,   316,   319,   318,   321,
     320,   322,   322,   323,   323,   323,   323,   323,   323,   324,
     325,   326,   327,   328,   329,   331,   330,   332,   332,   333,
     333,   335,   334,   337,   336,   338,   338,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     341,   340,   343,   342,   345,   344,   347,   346,   349,   348,
     351,   350,   352,   352,   352,   352,   353,   354,   356,   355,
     357,   357,   358,   358,   360,   359,   361,   361,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   364,   363,
     366,   365,   367,   367,   368,   368,   370,   369,   372,   371,
     373,   373,   374,   374,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   376,   377,   378,   380,   379,   382,
     381,   384,   383,   385,   387,   386,   388,   390,   389,   391,
     391,   392,   392,   394,   393,   396,   395,   397,   397,   398,
     398,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     400,   402,   401,   403,   404,   405,   406,   408,   407,   409,
     409,   410,   410,   412,   411,   414,   413,   415,   415,   416,
     416,   416,   416,   416,   416,   416,   418,   417,   420,   419,
     422,   421,   424,   423,   425,   425,   426,   426,   428,   427,
     430,   429,   431,   431,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   434,   433,   435,   437,   436,
     438,   439,   441,   440,   442,   442,   443,   443,   445,   444,
     447,   446,   448,   448,   449,   449,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   452,   451,   454,
     453,   456,   455,   458,   457,   460,   459,   462,   461,   464,
     463,   466,   465,   467,   467,   469,   468,   471,   470,   472,
     472,   474,   473,   475,   475,   476,   476,   477,   477,   477,
     477,   477,   477,   477,   478,   480,   479,   481,   483,   482,
     484,   484,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   487,   486,   488,   488,   488,   489,   491,   490,   492,
     493,   494,   496,   495,   497,   497,   498,   498,   498,   498,
     498,   500,   499,   502,   501,   504,   503,   506,   505,   508,
     507,   509,   509,   510,   510,   510,   510,   510,   510,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     510,   511,   513,   512,   515,   514,   516,   518,   517,   519,
     520,   522,   521,   523,   523,   525,   524,   526,   527,   529,
     528,   530,   530,   530,   530,   530,   532,   531,   534,   533,
     536,   535,   538,   537,   540,   539,   542,   541,   544,   543,
     546,   545,   547,   547,   548,   548,   550,   549,   551,   553,
     552,   555,   554,   556,   556,   557,   559,   558,   560,   560,
     562,   561,   563,   563,   564,   564,   564,   564,   564,   564,
     564,   565,   567,   566,   569,   568,   570,   570,   572,   571,
     573,   573,   574,   574,   574,   574,   576,   575,   577,   578,
     579
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
       1,     1,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
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
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     3,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
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
     480,   481,   484,   484,   492,   497,   502,   507,   512,   517,
     522,   527,   532,   532,   540,   540,   551,   551,   560,   561,
     564,   565,   566,   567,   568,   571,   571,   581,   587,   587,
     599,   599,   611,   611,   621,   622,   625,   626,   629,   629,
     639,   640,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   665,   665,   672,   673,   674,   675,   678,   678,
     686,   686,   694,   694,   702,   707,   707,   715,   720,   725,
     730,   735,   740,   745,   750,   755,   755,   763,   768,   768,
     776,   776,   784,   784,   792,   792,   802,   803,   805,   807,
     807,   825,   825,   835,   836,   839,   840,   843,   848,   853,
     853,   863,   864,   867,   868,   869,   872,   877,   884,   884,
     894,   894,   904,   905,   908,   909,   912,   912,   922,   922,
     932,   933,   934,   937,   938,   941,   941,   949,   949,   957,
     957,   968,   969,   972,   973,   974,   975,   976,   977,   980,
     985,   990,   995,  1000,  1005,  1013,  1013,  1026,  1027,  1030,
    1031,  1038,  1038,  1064,  1064,  1075,  1076,  1080,  1081,  1082,
    1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1105,  1105,  1113,  1113,  1121,  1121,  1129,  1129,  1137,  1137,
    1147,  1147,  1154,  1155,  1156,  1157,  1160,  1165,  1173,  1173,
    1184,  1185,  1189,  1190,  1193,  1193,  1201,  1202,  1205,  1206,
    1207,  1208,  1209,  1210,  1211,  1212,  1213,  1214,  1215,  1216,
    1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,  1231,  1231,
    1244,  1244,  1253,  1254,  1257,  1258,  1263,  1263,  1278,  1278,
    1292,  1293,  1296,  1297,  1300,  1301,  1302,  1303,  1304,  1305,
    1306,  1307,  1308,  1309,  1312,  1314,  1319,  1321,  1321,  1329,
    1329,  1337,  1337,  1345,  1347,  1347,  1355,  1364,  1364,  1376,
    1377,  1382,  1383,  1388,  1388,  1400,  1400,  1412,  1413,  1418,
    1419,  1424,  1425,  1426,  1427,  1428,  1429,  1430,  1431,  1432,
    1435,  1437,  1437,  1445,  1447,  1449,  1454,  1462,  1462,  1474,
    1475,  1478,  1479,  1482,  1482,  1492,  1492,  1501,  1502,  1505,
    1506,  1507,  1508,  1509,  1510,  1511,  1514,  1514,  1522,  1522,
    1547,  1547,  1577,  1577,  1589,  1590,  1593,  1594,  1597,  1597,
    1609,  1609,  1621,  1622,  1625,  1626,  1627,  1628,  1629,  1630,
    1631,  1632,  1633,  1634,  1635,  1638,  1638,  1646,  1651,  1651,
    1659,  1664,  1672,  1672,  1682,  1683,  1686,  1687,  1690,  1690,
    1699,  1699,  1708,  1709,  1712,  1713,  1717,  1718,  1719,  1720,
    1721,  1722,  1723,  1724,  1725,  1726,  1727,  1730,  1730,  1740,
    1740,  1750,  1750,  1758,  1758,  1766,  1766,  1774,  1774,  1782,
    1782,  1795,  1795,  1805,  1806,  1809,  1809,  1820,  1820,  1830,
    1831,  1834,  1834,  1844,  1845,  1848,  1849,  1852,  1853,  1854,
    1855,  1856,  1857,  1858,  1861,  1863,  1863,  1871,  1879,  1879,
    1891,  1892,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,
    1903,  1906,  1906,  1913,  1914,  1915,  1918,  1923,  1923,  1931,
    1936,  1943,  1950,  1950,  1960,  1961,  1964,  1965,  1966,  1967,
    1968,  1971,  1971,  1979,  1979,  1989,  1989,  2029,  2029,  2041,
    2041,  2051,  2052,  2055,  2056,  2057,  2058,  2059,  2060,  2061,
    2062,  2063,  2064,  2065,  2066,  2067,  2068,  2069,  2070,  2071,
    2072,  2075,  2080,  2080,  2088,  2088,  2096,  2101,  2101,  2109,
    2114,  2119,  2119,  2127,  2128,  2131,  2131,  2139,  2144,  2149,
    2149,  2157,  2160,  2163,  2166,  2169,  2175,  2175,  2183,  2183,
    2191,  2191,  2201,  2201,  2208,  2208,  2215,  2215,  2224,  2224,
    2235,  2235,  2245,  2246,  2250,  2251,  2254,  2254,  2264,  2274,
    2274,  2284,  2284,  2295,  2296,  2300,  2304,  2304,  2316,  2317,
    2321,  2321,  2329,  2330,  2333,  2334,  2335,  2336,  2337,  2338,
    2339,  2342,  2347,  2347,  2355,  2355,  2365,  2366,  2369,  2369,
    2377,  2378,  2381,  2382,  2383,  2384,  2387,  2387,  2395,  2400,
    2405
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


#line 14 "dhcp6_parser.yy" // lalr1.cc:1218
} } // isc::dhcp
#line 5182 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2410 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
