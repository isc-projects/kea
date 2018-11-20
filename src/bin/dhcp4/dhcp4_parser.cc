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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:438

#include <dhcp4/parser_context.h>

#line 51 "dhcp4_parser.cc" // lalr1.cc:438


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

#line 14 "dhcp4_parser.yy" // lalr1.cc:513
namespace isc { namespace dhcp {
#line 146 "dhcp4_parser.cc" // lalr1.cc:513

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


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
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
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 486: // ncr_protocol_value
      case 493: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 168: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 167: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 166: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 165: // "constant string"
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

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 486: // ncr_protocol_value
      case 493: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 168: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 167: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 166: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 165: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if !defined __cplusplus || __cplusplus < 201103L
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 486: // ncr_protocol_value
      case 493: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 168: // "boolean"
        value.move< bool > (that.value);
        break;

      case 167: // "floating point"
        value.move< double > (that.value);
        break;

      case 166: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 165: // "constant string"
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 165: // "constant string"

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 166: // "integer"

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 167: // "floating point"

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 168: // "boolean"

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 185: // value

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 189: // map_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 230: // socket_type

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 233: // outbound_interface_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 450 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 255: // db_type

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 457 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 337: // hr_mode

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 464 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 486: // ncr_protocol_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 471 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 493: // replace_client_name_value

#line 245 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 478 "dhcp4_parser.cc" // lalr1.cc:672
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
#if defined __cplusplus && 201103L <= __cplusplus
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
      case 185: // value
      case 189: // map_value
      case 230: // socket_type
      case 233: // outbound_interface_value
      case 255: // db_type
      case 337: // hr_mode
      case 486: // ncr_protocol_value
      case 493: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 168: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 167: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 166: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 165: // "constant string"
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
#line 254 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 255 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 256 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP4; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 257 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 258 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET4; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 259 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 260 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 774 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 261 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP4; }
#line 780 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 262 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 786 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 263 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 792 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 264 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 798 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 265 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 804 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 266 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 810 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 267 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 816 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 275 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 822 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 31:
#line 276 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 277 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 278 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 279 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 280 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 852 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 281 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 284 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 867 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 289 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 294 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 300 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 894 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 43:
#line 307 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 903 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 44:
#line 311 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 913 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 318 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 922 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 321 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 930 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 49:
#line 329 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 939 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 50:
#line 333 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 340 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 342 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 965 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 55:
#line 351 "dhcp4_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 974 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 56:
#line 355 "dhcp4_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 983 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 366 "dhcp4_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 376 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 381 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 68:
#line 405 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1031 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 69:
#line 412 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 70:
#line 420 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 71:
#line 424 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 107:
#line 470 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1069 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 108:
#line 475 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1078 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 480 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1087 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 485 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1096 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 490 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 492 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 498 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1123 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 503 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 508 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1141 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 514 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 519 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 127:
#line 538 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 542 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 547 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1192 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 552 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1201 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 557 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 559 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 564 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1224 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 134:
#line 565 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1230 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 135:
#line 568 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 136:
#line 570 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 137:
#line 575 "dhcp4_parser.yy" // lalr1.cc:907
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 577 "dhcp4_parser.yy" // lalr1.cc:907
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1263 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 581 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 140:
#line 587 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 141:
#line 592 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 142:
#line 599 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1305 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 143:
#line 604 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 147:
#line 614 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 616 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 1342 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 632 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1353 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 150:
#line 637 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 151:
#line 644 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 152:
#line 649 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 157:
#line 662 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 158:
#line 666 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 179:
#line 696 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 698 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1421 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 703 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1427 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 704 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1433 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 705 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1439 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 706 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1445 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 709 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 711 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1463 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 717 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1471 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 719 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1481 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 725 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 727 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 191:
#line 733 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 192:
#line 738 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 740 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 746 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1535 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 195:
#line 751 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 756 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 761 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 766 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1571 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 771 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 776 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1589 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 781 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 783 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 789 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 791 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 797 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 206:
#line 802 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1643 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 207:
#line 807 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 208:
#line 812 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 216:
#line 828 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 217:
#line 833 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 218:
#line 838 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 219:
#line 843 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 848 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 853 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 858 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 227:
#line 871 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 228:
#line 875 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1748 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 881 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 885 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1768 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 236:
#line 900 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 237:
#line 902 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1786 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 238:
#line 908 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 239:
#line 910 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 240:
#line 916 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 241:
#line 921 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 250:
#line 939 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 251:
#line 944 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 252:
#line 949 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 253:
#line 954 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 254:
#line 959 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 255:
#line 964 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1878 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 972 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 257:
#line 977 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 262:
#line 997 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1908 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 263:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 1934 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 264:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1944 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 265:
#line 1027 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 292:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 293:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 294:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1980 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 295:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1990 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2008 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2026 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 301:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 302:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 303:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 304:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 305:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 306:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 307:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 308:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2105 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 309:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2111 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 310:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2117 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 311:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2123 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 312:
#line 1136 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 313:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 314:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 319:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2162 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 320:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 342:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 343:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 344:
#line 1213 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2199 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 345:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 350:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 351:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 352:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 353:
#line 1251 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 369:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 371:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 372:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 373:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2286 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 376:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 378:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 379:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 380:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 381:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 382:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 387:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2371 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 388:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 389:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 390:
#line 1373 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 405:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 406:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 409:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 410:
#line 1423 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 411:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 417:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 418:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2475 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 419:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 420:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 430:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 431:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 432:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2521 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 433:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 2548 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 434:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 435:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 2585 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1547 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2596 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 437:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 442:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2615 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 443:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2624 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 444:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2634 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 445:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2643 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 465:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 466:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 467:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 468:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2679 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 469:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 470:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2697 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 471:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 472:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2715 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 473:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 474:
#line 1646 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 475:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 476:
#line 1653 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 477:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2761 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 482:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2807 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 483:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2815 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2825 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2843 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2874 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2883 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 493:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2894 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 494:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2903 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 497:
#line 1743 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 515:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 518:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 519:
#line 1800 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2970 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 520:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2979 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 528:
#line 1821 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 529:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 530:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 531:
#line 1831 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 532:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3023 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 533:
#line 1842 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr qc = yystack_[0].value.as< ElementPtr > ();
    ctx.stack_.back()->set("dhcp-queue-control", qc);

    if (!qc->contains("queue-type")) {
        std::stringstream msg;
        msg << "'queue-type' is required: ";
        msg  << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    ctx.leave();
}
#line 3041 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3052 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1863 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 558:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3092 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 559:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3100 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 560:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3110 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3118 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 562:
#line 1919 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3128 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 563:
#line 1925 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 564:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3145 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 565:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3155 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 566:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3164 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 567:
#line 1943 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 568:
#line 1948 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3181 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 569:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3190 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 570:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3196 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 571:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3202 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 572:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3210 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 573:
#line 1962 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3220 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 574:
#line 1968 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3229 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3238 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3246 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3255 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 578:
#line 1986 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3263 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3271 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 1992 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3279 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 581:
#line 1995 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3287 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3296 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 584:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 585:
#line 2012 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3322 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 586:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3332 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 587:
#line 2020 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3340 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 588:
#line 2022 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3350 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3358 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2033 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3367 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3375 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3384 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3392 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3401 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3411 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2056 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3419 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3430 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3440 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3450 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3459 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3470 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2096 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3479 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2106 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2111 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3499 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3509 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3517 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2136 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3528 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2141 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3537 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2153 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3547 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2157 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3555 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3564 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2179 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3572 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2181 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3593 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2192 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3602 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2201 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3612 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2205 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3620 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 644:
#line 2219 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3628 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 645:
#line 2221 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3638 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 646:
#line 2227 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3647 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 647:
#line 2232 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3656 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 648:
#line 2237 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3665 "dhcp4_parser.cc" // lalr1.cc:907
    break;


#line 3669 "dhcp4_parser.cc" // lalr1.cc:907
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


  const short Dhcp4Parser::yypact_ninf_ = -808;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     453,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,    40,    27,    51,    53,    59,
      71,    73,    75,    79,    89,   128,   137,   147,   154,   156,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,    27,    47,
      23,    63,    54,   178,   -24,   186,   158,   245,    36,     5,
     465,    87,    37,  -808,   224,   233,   249,   236,   258,  -808,
    -808,  -808,  -808,  -808,   285,  -808,    76,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,   304,   306,   323,
    -808,  -808,  -808,  -808,  -808,  -808,   324,   335,   336,   345,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,   348,  -808,  -808,  -808,  -808,   119,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,   359,  -808,   134,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
     360,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,   135,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,   145,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,   256,   265,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,   354,  -808,  -808,
     375,  -808,  -808,  -808,   385,  -808,  -808,   368,   388,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,   389,   392,  -808,  -808,  -808,  -808,   393,   399,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,   148,  -808,  -808,  -808,   400,  -808,  -808,   401,
    -808,   404,   408,  -808,  -808,   411,   412,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,   161,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,   182,  -808,  -808,  -808,  -808,   215,  -808,  -808,
    -808,    27,    27,  -808,   253,   417,   418,   420,   421,   422,
    -808,    23,  -808,    37,   429,   431,   432,   270,   274,   275,
     440,   441,   442,   443,   444,   446,   286,   287,   288,   289,
     447,   455,   456,   458,   459,   460,   461,   464,   466,   467,
     468,   469,   303,   470,   471,   472,    63,  -808,   473,   474,
     477,   318,    54,  -808,   479,   481,   483,   484,   485,   486,
     326,   489,   491,   492,   493,   178,  -808,   494,   -24,  -808,
     495,   496,   497,   499,   500,   501,   502,   503,  -808,   186,
    -808,   504,   506,   346,   507,   509,   510,   347,  -808,   245,
     513,   351,   352,  -808,    36,   519,   520,    20,  -808,   357,
     522,   523,   363,   526,   365,   366,   529,   530,   367,   370,
     532,   539,   540,   541,   465,  -808,   542,    87,  -808,   543,
      37,  -808,  -808,  -808,   544,   545,   546,    27,    27,    27,
    -808,   218,   547,   548,   550,  -808,  -808,  -808,   394,   395,
     396,   551,   555,   558,  -808,  -808,  -808,  -808,   402,   559,
     560,   561,   564,   563,   406,   567,   568,   569,   570,   571,
    -808,   573,   563,   574,  -808,   577,   170,   231,  -808,  -808,
     433,   434,   435,   591,   436,   454,  -808,   114,   577,   457,
     590,  -808,   462,  -808,   577,   463,   475,   476,   478,   480,
     482,   487,  -808,   488,   490,  -808,   498,   505,   508,  -808,
    -808,   511,  -808,  -808,  -808,   512,    27,  -808,  -808,   514,
     515,  -808,   516,  -808,  -808,    21,   517,  -808,  -808,    48,
     518,   521,   524,  -808,   613,  -808,   615,  -808,    27,    63,
      87,  -808,  -808,  -808,  -808,    37,    54,   527,  -808,  -808,
    -808,   255,   255,   614,  -808,   616,   617,   618,   619,  -808,
    -808,  -808,   260,   622,   624,   625,   227,    52,  -808,   465,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,   626,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,   230,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,   627,   614,  -808,   226,   239,
     240,   257,  -808,   264,  -808,  -808,  -808,  -808,  -808,  -808,
     572,   631,   632,   633,   634,  -808,  -808,   635,   638,   640,
     642,   644,  -808,   282,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,   284,  -808,   645,   647,  -808,  -808,   648,   653,
    -808,  -808,   651,   655,  -808,  -808,   654,   656,  -808,  -808,
     658,   659,  -808,  -808,  -808,  -808,  -808,  -808,    56,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,   104,  -808,  -808,   660,
     662,  -808,  -808,   661,   665,  -808,   657,   667,   668,   670,
     671,   674,   315,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,   317,  -808,  -808,  -808,   321,
     525,  -808,   663,   679,  -808,  -808,  -808,  -808,   676,  -808,
     108,  -808,   681,  -808,  -808,  -808,  -808,   684,   527,  -808,
     687,   688,   689,   690,   531,   528,   533,   534,   535,   691,
     694,   537,   538,   549,   552,   553,   255,  -808,  -808,   255,
    -808,   614,   178,  -808,   616,   245,  -808,   617,    36,  -808,
     618,   403,  -808,   619,   260,  -808,    70,   622,  -808,   186,
    -808,   624,     5,  -808,   625,   554,   556,   557,   562,   565,
     566,   227,  -808,   696,   701,    52,  -808,  -808,  -808,   700,
     682,   -24,  -808,   626,   703,  -808,    81,   627,  -808,  -808,
     575,  -808,   174,   576,   578,   579,  -808,  -808,  -808,  -808,
    -808,   580,   582,  -808,  -808,  -808,  -808,  -808,  -808,   338,
    -808,   339,  -808,   702,  -808,   704,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,   358,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,   705,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,   706,   708,  -808,  -808,  -808,  -808,  -808,   709,  -808,
     362,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,   583,
     585,  -808,  -808,   586,   372,  -808,   577,  -808,   712,  -808,
    -808,  -808,  -808,  -808,   374,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,   403,  -808,   715,   588,  -808,
      70,  -808,  -808,  -808,  -808,  -808,  -808,  -808,   720,   587,
     721,    81,  -808,  -808,   589,  -808,  -808,   722,  -808,   592,
    -808,  -808,   719,  -808,  -808,   171,  -808,   129,   719,  -808,
    -808,   725,   726,   729,   384,  -808,  -808,  -808,  -808,  -808,
    -808,   730,   597,   593,   594,   129,  -808,   612,  -808,  -808,
    -808,  -808,  -808
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   127,     9,   264,    11,
     419,    13,   444,    15,   344,    17,   352,    19,   389,    21,
     229,    23,   536,    25,   609,    27,   599,    29,    47,    41,
       0,     0,     0,     0,     0,   446,     0,   354,   391,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     607,   589,   591,   593,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   595,   597,   116,   142,     0,     0,     0,
     465,   467,   469,   140,   149,   151,     0,     0,     0,     0,
     111,   256,   342,   381,   313,   432,   434,   207,   493,   436,
     221,   240,     0,   519,   532,   534,   106,     0,    72,    74,
      75,    76,    77,   105,    94,    95,    96,    80,    81,   102,
      82,    83,    84,    88,    89,    78,    79,    86,    87,   100,
     101,   103,    97,    98,    99,    85,    90,    91,    92,    93,
     104,   129,   131,   135,     0,   126,     0,   118,   120,   121,
     122,   123,   124,   125,   294,   296,   298,   411,   292,   300,
       0,   306,   304,   302,   489,   291,   268,   269,   270,   281,
     282,     0,   266,   273,   286,   287,   288,   274,   276,   277,
     279,   275,   271,   272,   289,   290,   278,   283,   284,   285,
     280,   430,   429,   425,   426,   424,     0,   421,   423,   427,
     428,   487,   475,   477,   481,   479,   485,   483,   471,   464,
     458,   462,   463,     0,   447,   448,   459,   460,   461,   455,
     450,   456,   452,   453,   454,   457,   451,     0,   371,   192,
       0,   375,   373,   378,     0,   367,   368,     0,   355,   356,
     358,   370,   359,   360,   361,   377,   362,   363,   364,   365,
     366,   405,     0,     0,   403,   404,   407,   408,     0,   392,
     393,   395,   396,   397,   398,   399,   400,   401,   402,   236,
     238,   233,     0,   231,   234,   235,     0,   559,   561,     0,
     564,     0,     0,   568,   572,     0,     0,   576,   583,   585,
     587,   557,   555,   556,     0,   538,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   614,     0,   611,   613,   605,   604,     0,   601,   603,
      46,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      57,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   265,     0,     0,   420,
       0,     0,     0,     0,     0,     0,     0,     0,   445,     0,
     345,     0,     0,     0,     0,     0,     0,     0,   353,     0,
       0,     0,     0,   390,     0,     0,     0,     0,   230,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   537,     0,     0,   610,     0,
       0,   600,    50,    43,     0,     0,     0,     0,     0,     0,
      61,     0,     0,     0,     0,   113,   114,   115,     0,     0,
       0,     0,     0,     0,   107,   108,   109,   110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     518,     0,     0,     0,    73,     0,     0,     0,   139,   119,
       0,     0,     0,     0,     0,     0,   312,     0,     0,     0,
       0,   267,     0,   422,     0,     0,     0,     0,     0,     0,
       0,     0,   449,     0,     0,   369,     0,     0,     0,   380,
     357,     0,   409,   410,   394,     0,     0,   232,   558,     0,
       0,   563,     0,   566,   567,     0,     0,   574,   575,     0,
       0,     0,     0,   539,     0,   612,     0,   602,     0,     0,
       0,   590,   592,   594,   596,     0,     0,     0,   466,   468,
     470,     0,     0,   153,   112,   258,   346,   383,   315,    40,
     433,   435,     0,     0,   438,   223,     0,     0,   533,     0,
      51,   130,   133,   134,   132,   137,   138,   136,   295,   297,
     299,   413,   293,   301,   308,   309,   310,   311,   307,   305,
     303,     0,   431,   488,   476,   478,   482,   480,   486,   484,
     472,   372,   193,   376,   374,   379,   406,   237,   239,   560,
     562,   565,   570,   571,   569,   573,   578,   579,   580,   581,
     582,   577,   584,   586,   588,     0,   153,    44,     0,     0,
       0,     0,   147,     0,   144,   146,   179,   185,   187,   189,
       0,     0,     0,     0,     0,   201,   203,     0,     0,     0,
       0,     0,   178,     0,   159,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   174,   175,   176,   171,   177,
     172,   173,     0,   157,     0,   154,   155,   262,     0,   259,
     260,   350,     0,   347,   348,   387,     0,   384,   385,   319,
       0,   316,   317,   216,   217,   218,   219,   220,     0,   209,
     211,   212,   213,   214,   215,   497,     0,   495,   442,     0,
     439,   440,   227,     0,   224,   225,     0,     0,     0,     0,
       0,     0,     0,   242,   244,   245,   246,   247,   248,   249,
     528,   530,   527,   525,   526,     0,   521,   523,   524,     0,
      53,   417,     0,   414,   415,   473,   491,   492,     0,   618,
       0,   616,     0,    69,   608,   598,   117,     0,     0,   143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   141,   150,     0,
     152,     0,     0,   257,     0,   354,   343,     0,   391,   382,
       0,     0,   314,     0,     0,   208,   499,     0,   494,   446,
     437,     0,     0,   222,     0,     0,     0,     0,     0,     0,
       0,     0,   241,     0,     0,     0,   520,   535,    55,     0,
      54,     0,   412,     0,     0,   490,     0,     0,   615,   606,
       0,   145,     0,     0,     0,     0,   191,   194,   195,   196,
     197,     0,     0,   205,   206,   198,   199,   200,   160,     0,
     156,     0,   261,     0,   349,     0,   386,   341,   338,   326,
     327,   329,   330,   323,   324,   325,   336,   337,   335,     0,
     321,   328,   339,   340,   331,   332,   333,   334,   318,   210,
     515,     0,   513,   514,   506,   507,   511,   512,   508,   509,
     510,     0,   500,   501,   503,   504,   505,   496,     0,   441,
       0,   226,   250,   251,   252,   253,   254,   255,   243,     0,
       0,   522,    52,     0,     0,   416,     0,   632,     0,   630,
     628,   622,   626,   627,     0,   620,   624,   625,   623,   617,
     148,   181,   182,   183,   184,   180,   186,   188,   190,   202,
     204,   158,   263,   351,   388,     0,   320,     0,     0,   498,
       0,   443,   228,   529,   531,    56,   418,   474,     0,     0,
       0,     0,   619,   322,     0,   517,   502,     0,   629,     0,
     621,   516,     0,   631,   636,     0,   634,     0,     0,   633,
     644,     0,     0,     0,     0,   638,   640,   641,   642,   643,
     635,     0,     0,     0,     0,     0,   637,     0,   646,   647,
     648,   639,   645
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,   -38,  -808,  -397,  -808,
     196,  -808,  -808,  -808,  -808,  -808,  -808,  -507,  -808,  -808,
    -808,   -70,  -808,  -808,  -808,   376,  -808,  -808,  -808,  -808,
     157,   342,   -48,   -47,   -32,  -808,  -808,  -808,  -808,    -8,
       4,  -808,  -808,   127,   333,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,   -59,  -808,  -808,  -808,  -808,  -808,  -808,   120,  -808,
     -79,  -808,  -579,   -28,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,   -49,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,   -45,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,   -50,  -808,  -808,  -808,   -40,   353,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,   -46,  -808,  -808,  -808,  -808,
    -808,  -808,  -807,  -808,  -808,  -808,   -17,  -808,  -808,  -808,
     -10,   407,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -796,  -808,   -68,  -808,   -20,  -808,  -794,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,    -5,  -808,  -808,  -170,   -65,  -808,
    -808,  -808,  -808,  -808,   -11,  -808,  -808,  -808,     7,  -808,
     409,  -808,   -66,  -808,  -808,  -808,  -808,  -808,   -60,  -808,
    -808,  -808,  -808,  -808,   -18,  -808,  -808,  -808,     3,  -808,
    -808,  -808,    10,  -808,   398,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,   -23,  -808,  -808,  -808,
     -16,   428,  -808,  -808,   -58,  -808,   -30,  -808,   -42,  -808,
    -808,  -808,     9,  -808,  -808,  -808,    12,  -808,   423,   -12,
    -808,    -2,  -808,     8,  -808,   222,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -785,  -808,  -808,  -808,  -808,  -808,    17,
    -808,  -808,  -808,  -141,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,     0,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,   247,   397,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -340,   387,  -808,  -808,  -808,  -808,  -808,  -808,
     278,   405,  -808,  -808,  -808,    -7,  -808,  -808,  -142,  -808,
    -808,  -808,  -808,  -808,  -808,  -156,  -808,  -808,  -172,  -808,
    -808,  -808,  -808,  -808
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     600,    87,    88,    41,    68,    84,    85,   611,   780,   859,
     860,   346,    43,    70,    96,    97,    98,   355,    45,    71,
     137,   138,   139,   140,   141,   142,   143,   380,   144,   145,
     146,   147,   365,   176,   177,    47,    72,   178,   398,   179,
     399,   614,   180,   400,   617,   181,   148,   373,   149,   366,
     673,   674,   675,   797,   150,   374,   151,   375,   714,   715,
     716,   819,   693,   694,   695,   800,   975,   696,   801,   697,
     802,   698,   803,   699,   700,   432,   701,   702,   703,   704,
     705,   706,   707,   708,   809,   709,   810,   710,   711,   152,
     387,   738,   739,   740,   741,   742,   743,   744,   153,   390,
     753,   754,   755,   842,    61,    79,   302,   303,   304,   445,
     305,   446,   154,   391,   762,   763,   764,   765,   766,   767,
     768,   769,   155,   381,   718,   719,   720,   822,    49,    73,
     201,   202,   203,   408,   204,   404,   205,   405,   206,   406,
     207,   409,   208,   413,   209,   412,   210,   411,   628,   211,
     156,   384,   730,   731,   732,   831,   909,   910,   157,   382,
      55,    76,   722,   723,   724,   825,    57,    77,   267,   268,
     269,   270,   271,   272,   273,   431,   274,   435,   275,   434,
     276,   277,   436,   278,   158,   383,   726,   727,   728,   828,
      59,    78,   288,   289,   290,   291,   292,   440,   293,   294,
     295,   296,   213,   407,   782,   783,   784,   861,    51,    74,
     226,   227,   228,   417,   159,   385,   160,   386,   161,   389,
     749,   750,   751,   839,    53,    75,   243,   244,   245,   162,
     370,   163,   371,   164,   372,   249,   427,   787,   864,   250,
     421,   251,   422,   252,   424,   253,   423,   254,   426,   255,
     425,   256,   420,   220,   414,   788,   165,   388,   746,   747,
     836,   931,   932,   933,   934,   935,   987,   936,   166,   167,
     393,   775,   776,   777,   853,   778,   854,   168,   394,   169,
     395,    63,    80,   324,   325,   326,   327,   450,   328,   451,
     329,   330,   453,   331,   332,   333,   456,   654,   334,   457,
     335,   336,   337,   460,   661,   338,   461,   339,   462,   340,
     463,    99,   357,   100,   358,   101,   359,   170,   363,   364,
      67,    82,   347,   348,   349,   469,   102,   356,    65,    81,
     342,   343,   344,   466,   790,   791,   866,   964,   965,   966,
     967,  1000,   968,   998,  1015,  1016,  1017,  1024,  1025,  1026,
    1031,  1027,  1028,  1029
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   136,   175,   195,   222,   239,   223,   265,   284,   301,
     321,   257,   286,   712,   182,   214,   229,   241,   287,   279,
     297,   629,   322,   481,   904,   196,   197,   633,   266,   285,
      83,   216,    31,    89,    32,   905,    33,   908,   652,   123,
      30,   198,   183,   215,   230,   242,   917,   280,   298,   345,
     323,   221,   125,   126,   224,   212,   225,   240,    42,   834,
      44,   217,   835,   246,   192,   199,    46,   193,   171,   172,
     103,   218,   173,   247,   104,   174,   105,   200,    48,   361,
      50,   219,    52,   248,   362,   106,    54,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    56,   110,   111,   112,
     259,   281,   260,   261,   282,   283,   599,   837,   299,   300,
     838,   867,   125,   126,   868,   599,   116,   117,   118,   119,
     120,   121,   396,   299,   300,   122,   123,   397,   125,   126,
     125,   126,   122,   123,   259,    58,   124,   402,   415,   125,
     126,    94,   403,   416,    60,   259,   125,   126,   418,   127,
     128,   447,   653,   419,    62,   129,   448,   125,   126,   920,
     921,    64,    90,    66,   464,   130,   770,   771,   131,   465,
      94,    91,    92,    93,  1018,   132,   133,  1019,   904,   134,
     135,   656,   657,   658,   659,   467,   612,   613,    94,   905,
     468,   908,    34,    35,    36,    37,   624,   625,   626,   627,
     917,    94,    94,   108,   109,   110,   111,   112,   971,   972,
     973,   974,    86,   110,   111,   112,   660,    94,   470,    94,
     122,   470,   957,   471,   958,   959,   584,   341,    94,   396,
     350,   116,   117,   118,   793,    94,   351,   184,   185,   186,
     889,   123,   467,   470,   353,   670,    94,   794,   795,   123,
     615,   616,   187,   352,   125,   126,   188,   189,   190,   191,
     402,   354,   125,   126,   428,   796,   192,   798,   429,   193,
     129,  1020,   799,   231,  1021,  1022,  1023,   194,   258,   232,
     233,   234,   235,   236,   237,   816,   238,   816,   676,   360,
     817,    95,   818,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   367,   259,
     368,   260,   261,   472,   473,   262,   263,   264,   851,   259,
     855,   125,   126,   852,   464,   856,   136,   369,   376,   857,
     238,   785,   175,   756,   757,   758,   759,   760,   761,   377,
     378,   816,   415,    94,   182,   195,   981,   982,   222,   379,
     223,    94,   392,   733,   734,   735,   736,   214,   737,   239,
     229,   985,   430,   401,   410,   447,   986,   196,   197,   265,
     992,   241,   183,   216,   284,   418,   438,  1001,   286,   433,
     996,   279,  1002,   198,   287,   215,   297,  1035,   230,   437,
     266,   439,  1036,   441,   321,   285,   442,   212,   224,   242,
     225,   443,   444,   217,   449,   452,   322,   199,   454,   280,
      94,   240,   455,   218,   298,   458,   459,   246,   474,   200,
      94,   475,   476,   219,   477,   478,   479,   247,   108,   109,
     110,   111,   112,   482,   323,   483,   484,   248,   485,   581,
     582,   583,   486,   487,   488,   489,   490,   491,   492,   997,
     493,   498,   494,   495,   496,   497,   116,   117,   118,   499,
     500,   121,   501,   502,   503,   504,   123,   259,   505,   510,
     506,   507,   508,   509,   511,   512,   513,   515,   516,   125,
     126,   517,   189,   520,   191,   521,   518,   522,   523,   524,
     525,   192,   526,   527,   193,   528,   529,   530,   532,   534,
     535,   536,   194,   537,   538,   539,   540,   541,   543,   136,
     544,   546,   545,   547,   548,   549,   175,   551,   648,   552,
     553,   692,   692,   555,   556,   558,   559,   560,   182,   561,
     562,   563,   564,   565,   566,   567,   569,   772,   568,   321,
     667,   125,   126,   570,   571,   572,   574,   576,   578,   773,
     672,   322,   579,   580,   585,   586,   183,   587,   591,   588,
     589,   590,   592,   593,   595,   596,   597,   594,    94,   598,
      32,   601,   602,   603,   604,   605,   804,   774,   606,   323,
     607,   609,   610,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   621,   631,   618,   619,
     620,   622,   319,   320,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   665,   623,
     666,   713,   630,   717,   721,   725,   729,   632,   634,   745,
      94,   748,   752,   781,   789,   805,   806,   807,   808,   811,
     635,   636,   812,   637,   813,   638,   814,   639,   815,   655,
     821,   820,   640,   641,   823,   642,   824,   826,   827,   830,
     829,   845,   833,   643,   832,   841,   840,   843,   844,   862,
     644,   846,   847,   645,   848,   849,   646,   647,   850,   649,
     650,   651,   863,   662,   865,   953,   663,   869,   870,   664,
     858,   872,   873,   874,   875,   881,   877,   876,   882,   878,
     949,   880,   879,   883,   884,   950,   952,   956,   608,   988,
     983,   990,   984,   671,   989,   885,   999,   991,   886,  1004,
     942,   887,   943,   944,  1007,  1009,  1014,  1012,   945,  1032,
    1033,   946,   947,  1034,  1037,   519,   668,   480,   514,   871,
     970,   976,   890,   977,   978,   979,   692,   980,   993,   692,
     994,   995,   195,  1008,  1011,   265,  1005,  1013,   284,  1039,
    1040,   897,   286,   906,   214,  1038,   922,   279,   287,   239,
     297,   924,   301,   912,   196,   197,   266,  1042,   926,   285,
     216,   241,   903,   898,   899,   772,   792,   923,   888,   919,
     198,   222,   215,   223,   941,   280,   960,   773,   298,   900,
     557,   913,   940,   229,   212,   948,   927,   892,   962,   242,
     217,   907,   891,   911,   199,  1003,   894,   961,   925,   914,
     218,   240,   531,   901,   928,   774,   200,   246,   918,   915,
     219,   230,   893,   896,   929,   902,   963,   247,   895,   916,
     955,   224,   554,   225,   930,   954,   533,   248,   550,  1006,
     939,   938,   542,   786,   937,   951,   779,   577,   669,  1010,
     969,   573,  1030,  1041,     0,     0,     0,     0,     0,     0,
       0,     0,   575,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   897,     0,   906,     0,     0,
     922,     0,     0,     0,     0,   924,     0,   912,     0,     0,
       0,   960,   926,     0,     0,     0,   903,   898,   899,     0,
       0,   923,     0,   962,     0,     0,     0,     0,     0,     0,
       0,     0,   961,   900,     0,   913,     0,     0,     0,     0,
     927,     0,     0,     0,     0,   907,     0,   911,     0,     0,
       0,   963,   925,   914,     0,     0,     0,   901,   928,     0,
       0,     0,     0,   915,     0,     0,     0,     0,   929,   902,
       0,     0,     0,   916,     0,     0,     0,     0,   930
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    76,    78,   592,    72,    73,    74,    75,    78,    77,
      78,   528,    80,   363,   831,    73,    73,   534,    77,    78,
      68,    73,     5,    10,     7,   831,     9,   831,    17,    63,
       0,    73,    72,    73,    74,    75,   831,    77,    78,    12,
      80,    75,    76,    77,    74,    73,    74,    75,     7,     3,
       7,    73,     6,    75,    88,    73,     7,    91,    14,    15,
       7,    73,    18,    75,    11,    21,    13,    73,     7,     3,
       7,    73,     7,    75,     8,    22,     7,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     7,    27,    28,    29,
      64,    65,    66,    67,    68,    69,   503,     3,   103,   104,
       6,     3,    76,    77,     6,   512,    53,    54,    55,    56,
      57,    58,     3,   103,   104,    62,    63,     8,    76,    77,
      76,    77,    62,    63,    64,     7,    73,     3,     3,    76,
      77,   165,     8,     8,     7,    64,    76,    77,     3,    86,
      87,     3,   131,     8,     7,    92,     8,    76,    77,    89,
      90,     7,   139,     7,     3,   102,   114,   115,   105,     8,
     165,   148,   149,   150,     3,   112,   113,     6,   985,   116,
     117,   133,   134,   135,   136,     3,    16,    17,   165,   985,
       8,   985,   165,   166,   167,   168,    82,    83,    84,    85,
     985,   165,   165,    25,    26,    27,    28,    29,    34,    35,
      36,    37,   165,    27,    28,    29,   168,   165,     3,   165,
      62,     3,   141,     8,   143,   144,     8,   140,   165,     3,
       6,    53,    54,    55,     8,   165,     3,    59,    60,    61,
     819,    63,     3,     3,     8,   585,   165,     8,     8,    63,
      19,    20,    74,     4,    76,    77,    78,    79,    80,    81,
       3,     3,    76,    77,     8,     8,    88,     3,     3,    91,
      92,   142,     8,    87,   145,   146,   147,    99,    33,    93,
      94,    95,    96,    97,    98,     3,   100,     3,    33,     4,
       8,   361,     8,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,     4,    64,
       4,    66,    67,   351,   352,    70,    71,    72,     3,    64,
       3,    76,    77,     8,     3,     8,   396,     4,     4,     8,
     100,   101,   402,   106,   107,   108,   109,   110,   111,     4,
       4,     3,     3,   165,   402,   415,     8,     8,   418,     4,
     418,   165,     4,    93,    94,    95,    96,   415,    98,   429,
     418,     3,     8,     4,     4,     3,     8,   415,   415,   439,
       8,   429,   402,   415,   444,     3,     8,     3,   444,     4,
       8,   439,     8,   415,   444,   415,   444,     3,   418,     4,
     439,     3,     8,     4,   464,   444,     4,   415,   418,   429,
     418,     8,     3,   415,     4,     4,   464,   415,     4,   439,
     165,   429,     4,   415,   444,     4,     4,   429,   165,   415,
     165,     4,     4,   415,     4,     4,     4,   429,    25,    26,
      27,    28,    29,     4,   464,     4,     4,   429,   168,   477,
     478,   479,   168,   168,     4,     4,     4,     4,     4,   956,
       4,     4,   166,   166,   166,   166,    53,    54,    55,     4,
       4,    58,     4,     4,     4,     4,    63,    64,     4,   166,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    76,
      77,     4,    79,     4,    81,     4,   168,     4,     4,     4,
       4,    88,   166,     4,    91,     4,     4,     4,     4,     4,
       4,     4,    99,     4,     4,     4,     4,     4,     4,   579,
       4,     4,   166,     4,     4,   168,   586,     4,   556,   168,
     168,   591,   592,     4,     4,   168,     4,     4,   586,   166,
       4,   166,   166,     4,     4,   168,     4,   607,   168,   609,
     578,    76,    77,     4,     4,     4,     4,     4,     4,   607,
      23,   609,     7,     7,     7,     7,   586,     7,     7,   165,
     165,   165,     7,     5,     5,     5,     5,   165,   165,     5,
       7,   165,     5,     5,     5,     5,     4,   607,     7,   609,
       7,     7,     5,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     5,     7,   165,   165,
     165,   165,   137,   138,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,     5,   165,
       5,     7,   165,     7,     7,     7,     7,   165,   165,     7,
     165,     7,     7,     7,     7,     4,     4,     4,     4,     4,
     165,   165,     4,   165,     4,   165,     4,   165,     4,   132,
       3,     6,   165,   165,     6,   165,     3,     6,     3,     3,
       6,     4,     3,   165,     6,     3,     6,     6,     3,     6,
     165,     4,     4,   165,     4,     4,   165,   165,     4,   165,
     165,   165,     3,   165,     8,     3,   165,     6,     4,   165,
     165,     4,     4,     4,     4,     4,   168,   166,     4,   166,
       4,   166,   168,   166,   166,     4,     6,     4,   512,     4,
       8,     3,     8,   586,     8,   166,     4,     8,   166,     4,
     166,   168,   166,   166,     4,     4,     7,     5,   166,     4,
       4,   166,   166,     4,     4,   402,   579,   361,   396,   798,
     165,   165,   821,   165,   165,   165,   816,   165,   165,   819,
     165,   165,   822,   166,   165,   825,   168,   165,   828,   166,
     166,   831,   828,   831,   822,   168,   836,   825,   828,   839,
     828,   836,   842,   831,   822,   822,   825,   165,   836,   828,
     822,   839,   831,   831,   831,   855,   666,   836,   816,   834,
     822,   861,   822,   861,   844,   825,   866,   855,   828,   831,
     447,   831,   842,   861,   822,   851,   836,   824,   866,   839,
     822,   831,   822,   831,   822,   985,   827,   866,   836,   831,
     822,   839,   415,   831,   836,   855,   822,   839,   833,   831,
     822,   861,   825,   830,   836,   831,   866,   839,   828,   831,
     863,   861,   444,   861,   836,   861,   418,   839,   439,   990,
     841,   839,   429,   631,   837,   855,   609,   470,   580,  1001,
     867,   464,  1018,  1035,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   467,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   985,    -1,   985,    -1,    -1,
     990,    -1,    -1,    -1,    -1,   990,    -1,   985,    -1,    -1,
      -1,  1001,   990,    -1,    -1,    -1,   985,   985,   985,    -1,
      -1,   990,    -1,  1001,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1001,   985,    -1,   985,    -1,    -1,    -1,    -1,
     990,    -1,    -1,    -1,    -1,   985,    -1,   985,    -1,    -1,
      -1,  1001,   990,   985,    -1,    -1,    -1,   985,   990,    -1,
      -1,    -1,    -1,   985,    -1,    -1,    -1,    -1,   990,   985,
      -1,    -1,    -1,   985,    -1,    -1,    -1,    -1,   990
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
       0,     5,     7,     9,   165,   166,   167,   168,   185,   186,
     187,   192,     7,   201,     7,   207,     7,   224,     7,   317,
       7,   397,     7,   413,     7,   349,     7,   355,     7,   379,
       7,   293,     7,   470,     7,   517,     7,   509,   193,   188,
     202,   208,   225,   318,   398,   414,   350,   356,   380,   294,
     471,   518,   510,   185,   194,   195,   165,   190,   191,    10,
     139,   148,   149,   150,   165,   200,   203,   204,   205,   500,
     502,   504,   515,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    53,    54,    55,    56,
      57,    58,    62,    63,    73,    76,    77,    86,    87,    92,
     102,   105,   112,   113,   116,   117,   200,   209,   210,   211,
     212,   213,   214,   215,   217,   218,   219,   220,   235,   237,
     243,   245,   278,   287,   301,   311,   339,   347,   373,   403,
     405,   407,   418,   420,   422,   445,   457,   458,   466,   468,
     506,    14,    15,    18,    21,   200,   222,   223,   226,   228,
     231,   234,   403,   405,    59,    60,    61,    74,    78,    79,
      80,    81,    88,    91,    99,   200,   211,   212,   213,   218,
     219,   319,   320,   321,   323,   325,   327,   329,   331,   333,
     335,   338,   373,   391,   403,   405,   407,   418,   420,   422,
     442,    75,   200,   331,   333,   373,   399,   400,   401,   403,
     405,    87,    93,    94,    95,    96,    97,    98,   100,   200,
     373,   403,   405,   415,   416,   417,   418,   420,   422,   424,
     428,   430,   432,   434,   436,   438,   440,   347,    33,    64,
      66,    67,    70,    71,    72,   200,   263,   357,   358,   359,
     360,   361,   362,   363,   365,   367,   369,   370,   372,   403,
     405,    65,    68,    69,   200,   263,   361,   367,   381,   382,
     383,   384,   385,   387,   388,   389,   390,   403,   405,   103,
     104,   200,   295,   296,   297,   299,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   137,
     138,   200,   403,   405,   472,   473,   474,   475,   477,   479,
     480,   482,   483,   484,   487,   489,   490,   491,   494,   496,
     498,   140,   519,   520,   521,    12,   200,   511,   512,   513,
       6,     3,     4,     8,     3,   206,   516,   501,   503,   505,
       4,     3,     8,   507,   508,   221,   238,     4,     4,     4,
     419,   421,   423,   236,   244,   246,     4,     4,     4,     4,
     216,   312,   348,   374,   340,   404,   406,   279,   446,   408,
     288,   302,     4,   459,   467,   469,     3,     8,   227,   229,
     232,     4,     3,     8,   324,   326,   328,   392,   322,   330,
       4,   336,   334,   332,   443,     3,     8,   402,     3,     8,
     441,   429,   431,   435,   433,   439,   437,   425,     8,     3,
       8,   364,   264,     4,   368,   366,   371,     4,     8,     3,
     386,     4,     4,     8,     3,   298,   300,     3,     8,     4,
     476,   478,     4,   481,     4,     4,   485,   488,     4,     4,
     492,   495,   497,   499,     3,     8,   522,     3,     8,   514,
       3,     8,   185,   185,   165,     4,     4,     4,     4,     4,
     204,   511,     4,     4,     4,   168,   168,   168,     4,     4,
       4,     4,     4,     4,   166,   166,   166,   166,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     166,     4,     4,     4,   210,     4,     4,     4,   168,   223,
       4,     4,     4,     4,     4,     4,   166,     4,     4,     4,
       4,   320,     4,   400,     4,     4,     4,     4,     4,     4,
       4,     4,   417,     4,     4,   166,     4,     4,     4,   168,
     359,     4,   168,   168,   383,     4,     4,   296,   168,     4,
       4,   166,     4,   166,   166,     4,     4,   168,   168,     4,
       4,     4,     4,   473,     4,   520,     4,   512,     4,     7,
       7,   185,   185,   185,     8,     7,     7,     7,   165,   165,
     165,     7,     7,     5,   165,     5,     5,     5,     5,   187,
     189,   165,     5,     5,     5,     5,     7,     7,   189,     7,
       5,   196,    16,    17,   230,    19,    20,   233,   165,   165,
     165,     5,   165,   165,    82,    83,    84,    85,   337,   196,
     165,     7,   165,   196,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   185,   165,
     165,   165,    17,   131,   486,   132,   133,   134,   135,   136,
     168,   493,   165,   165,   165,     5,     5,   185,   209,   519,
     511,   222,    23,   239,   240,   241,    33,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,   200,   251,   252,   253,   256,   258,   260,   262,
     263,   265,   266,   267,   268,   269,   270,   271,   272,   274,
     276,   277,   251,     7,   247,   248,   249,     7,   313,   314,
     315,     7,   351,   352,   353,     7,   375,   376,   377,     7,
     341,   342,   343,    93,    94,    95,    96,    98,   280,   281,
     282,   283,   284,   285,   286,     7,   447,   448,     7,   409,
     410,   411,     7,   289,   290,   291,   106,   107,   108,   109,
     110,   111,   303,   304,   305,   306,   307,   308,   309,   310,
     114,   115,   200,   403,   405,   460,   461,   462,   464,   472,
     197,     7,   393,   394,   395,   101,   424,   426,   444,     7,
     523,   524,   247,     8,     8,     8,     8,   242,     3,     8,
     254,   257,   259,   261,     4,     4,     4,     4,     4,   273,
     275,     4,     4,     4,     4,     4,     3,     8,     8,   250,
       6,     3,   316,     6,     3,   354,     6,     3,   378,     6,
       3,   344,     6,     3,     3,     6,   449,     3,     6,   412,
       6,     3,   292,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   463,   465,     3,     8,     8,   165,   198,
     199,   396,     6,     3,   427,     8,   525,     3,     6,     6,
       4,   240,     4,     4,     4,     4,   166,   168,   166,   168,
     166,     4,     4,   166,   166,   166,   166,   168,   252,   251,
     249,   319,   315,   357,   353,   381,   377,   200,   211,   212,
     213,   218,   219,   263,   311,   329,   331,   333,   335,   345,
     346,   373,   403,   405,   418,   420,   422,   442,   343,   281,
      89,    90,   200,   263,   347,   373,   403,   405,   418,   420,
     422,   450,   451,   452,   453,   454,   456,   448,   415,   411,
     295,   291,   166,   166,   166,   166,   166,   166,   304,     4,
       4,   461,     6,     3,   399,   395,     4,   141,   143,   144,
     200,   263,   403,   405,   526,   527,   528,   529,   531,   524,
     165,    34,    35,    36,    37,   255,   165,   165,   165,   165,
     165,     8,     8,     8,     8,     3,     8,   455,     4,     8,
       3,     8,     8,   165,   165,   165,     8,   196,   532,     4,
     530,     3,     8,   346,     4,   168,   452,     4,   166,     4,
     527,   165,     5,   165,     7,   533,   534,   535,     3,     6,
     142,   145,   146,   147,   536,   537,   538,   540,   541,   542,
     534,   539,     4,     4,     4,     3,     8,     4,   168,   166,
     166,   537,   165
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   169,   171,   170,   172,   170,   173,   170,   174,   170,
     175,   170,   176,   170,   177,   170,   178,   170,   179,   170,
     180,   170,   181,   170,   182,   170,   183,   170,   184,   170,
     185,   185,   185,   185,   185,   185,   185,   186,   188,   187,
     189,   190,   190,   191,   191,   193,   192,   194,   194,   195,
     195,   197,   196,   198,   198,   199,   199,   200,   202,   201,
     203,   203,   204,   204,   204,   204,   204,   204,   206,   205,
     208,   207,   209,   209,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   211,   212,   213,
     214,   216,   215,   217,   218,   219,   221,   220,   222,   222,
     223,   223,   223,   223,   223,   223,   223,   225,   224,   227,
     226,   229,   228,   230,   230,   232,   231,   233,   233,   234,
     236,   235,   238,   237,   239,   239,   240,   242,   241,   244,
     243,   246,   245,   247,   247,   248,   248,   250,   249,   251,
     251,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   254,
     253,   255,   255,   255,   255,   257,   256,   259,   258,   261,
     260,   262,   264,   263,   265,   266,   267,   268,   269,   270,
     271,   273,   272,   275,   274,   276,   277,   279,   278,   280,
     280,   281,   281,   281,   281,   281,   282,   283,   284,   285,
     286,   288,   287,   289,   289,   290,   290,   292,   291,   294,
     293,   295,   295,   295,   296,   296,   298,   297,   300,   299,
     302,   301,   303,   303,   304,   304,   304,   304,   304,   304,
     305,   306,   307,   308,   309,   310,   312,   311,   313,   313,
     314,   314,   316,   315,   318,   317,   319,   319,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   322,   321,   324,   323,   326,   325,   328,   327,
     330,   329,   332,   331,   334,   333,   336,   335,   337,   337,
     337,   337,   338,   340,   339,   341,   341,   342,   342,   344,
     343,   345,   345,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   348,   347,   350,   349,   351,   351,   352,   352,
     354,   353,   356,   355,   357,   357,   358,   358,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   360,   361,
     362,   364,   363,   366,   365,   368,   367,   369,   371,   370,
     372,   374,   373,   375,   375,   376,   376,   378,   377,   380,
     379,   381,   381,   382,   382,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   384,   386,   385,   387,   388,   389,
     390,   392,   391,   393,   393,   394,   394,   396,   395,   398,
     397,   399,   399,   400,   400,   400,   400,   400,   400,   400,
     402,   401,   404,   403,   406,   405,   408,   407,   409,   409,
     410,   410,   412,   411,   414,   413,   415,   415,   416,   416,
     417,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   417,   417,   419,   418,   421,   420,   423,
     422,   425,   424,   427,   426,   429,   428,   431,   430,   433,
     432,   435,   434,   437,   436,   439,   438,   441,   440,   443,
     442,   444,   444,   446,   445,   447,   447,   449,   448,   450,
     450,   451,   451,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   453,   455,   454,   456,   457,   459,
     458,   460,   460,   461,   461,   461,   461,   461,   463,   462,
     465,   464,   467,   466,   469,   468,   471,   470,   472,   472,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   473,   474,   476,
     475,   478,   477,   479,   481,   480,   482,   483,   485,   484,
     486,   486,   488,   487,   489,   490,   492,   491,   493,   493,
     493,   493,   493,   495,   494,   497,   496,   499,   498,   501,
     500,   503,   502,   505,   504,   507,   506,   508,   506,   510,
     509,   511,   511,   512,   512,   514,   513,   516,   515,   518,
     517,   519,   519,   520,   522,   521,   523,   523,   525,   524,
     526,   526,   527,   527,   527,   527,   527,   527,   527,   528,
     530,   529,   532,   531,   533,   533,   535,   534,   536,   536,
     537,   537,   537,   537,   539,   538,   540,   541,   542
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
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     1,     3,     1,     0,     4,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     0,     4,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     0,     6,     0,
       4,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet4\"",
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
  "rebind_timer", "decline_probation_period", "server_tag", "$@21",
  "echo_client_id", "match_client_id", "authoritative",
  "interfaces_config", "$@22", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@23", "interfaces_list",
  "$@24", "dhcp_socket_type", "$@25", "socket_type", "outbound_interface",
  "$@26", "outbound_interface_value", "re_detect", "lease_database",
  "$@27", "sanity_checks", "$@28", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@29", "hosts_database", "$@30",
  "hosts_databases", "$@31", "database_list", "not_empty_database_list",
  "database", "$@32", "database_map_params", "database_map_param",
  "database_type", "$@33", "db_type", "user", "$@34", "password", "$@35",
  "host", "$@36", "port", "name", "$@37", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@38", "keyspace", "$@39",
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@40",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@41", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@42",
  "sub_hooks_library", "$@43", "hooks_params", "hooks_param", "library",
  "$@44", "parameters", "$@45", "expired_leases_processing", "$@46",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@47",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@48",
  "sub_subnet4", "$@49", "subnet4_params", "subnet4_param", "subnet",
  "$@50", "subnet_4o6_interface", "$@51", "subnet_4o6_interface_id",
  "$@52", "subnet_4o6_subnet", "$@53", "interface", "$@54", "client_class",
  "$@55", "require_client_classes", "$@56", "reservation_mode", "$@57",
  "hr_mode", "id", "shared_networks", "$@58", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@59",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@60", "sub_option_def_list", "$@61", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@62",
  "sub_option_def", "$@63", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@64",
  "option_def_record_types", "$@65", "space", "$@66", "option_def_space",
  "option_def_encapsulate", "$@67", "option_def_array", "option_data_list",
  "$@68", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@69", "sub_option_data", "$@70",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@71",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@72", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@73", "sub_pool4", "$@74",
  "pool_params", "pool_param", "pool_entry", "$@75", "user_context",
  "$@76", "comment", "$@77", "reservations", "$@78", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@79", "sub_reservation",
  "$@80", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@81", "server_hostname", "$@82",
  "boot_file_name", "$@83", "ip_address", "$@84", "ip_addresses", "$@85",
  "duid", "$@86", "hw_address", "$@87", "client_id_value", "$@88",
  "circuit_id_value", "$@89", "flex_id_value", "$@90", "hostname", "$@91",
  "reservation_client_classes", "$@92", "relay", "$@93", "relay_map",
  "client_classes", "$@94", "client_classes_list", "client_class_entry",
  "$@95", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@96",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@97",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@98", "control_socket_name", "$@99", "dhcp_queue_control", "$@100",
  "dhcp_ddns", "$@101", "sub_dhcp_ddns", "$@102", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@103",
  "server_ip", "$@104", "server_port", "sender_ip", "$@105", "sender_port",
  "max_queue_size", "ncr_protocol", "$@106", "ncr_protocol_value",
  "ncr_format", "$@107", "override_no_update", "override_client_update",
  "replace_client_name", "$@108", "replace_client_name_value",
  "generated_prefix", "$@109", "hostname_char_set", "$@110",
  "hostname_char_replacement", "$@111", "dhcp6_json_object", "$@112",
  "dhcpddns_json_object", "$@113", "control_agent_json_object", "$@114",
  "config_control", "$@115", "$@116", "sub_config_control", "$@117",
  "config_control_params", "config_control_param", "config_databases",
  "$@118", "logging_object", "$@119", "sub_logging", "$@120",
  "logging_params", "logging_param", "loggers", "$@121", "loggers_entries",
  "logger_entry", "$@122", "logger_params", "logger_param", "debuglevel",
  "severity", "$@123", "output_options_list", "$@124",
  "output_options_list_content", "output_entry", "$@125",
  "output_params_list", "output_params", "output", "$@126", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   254,   254,   254,   255,   255,   256,   256,   257,   257,
     258,   258,   259,   259,   260,   260,   261,   261,   262,   262,
     263,   263,   264,   264,   265,   265,   266,   266,   267,   267,
     275,   276,   277,   278,   279,   280,   281,   284,   289,   289,
     300,   303,   304,   307,   311,   318,   318,   325,   326,   329,
     333,   340,   340,   347,   348,   351,   355,   366,   376,   376,
     392,   393,   397,   398,   399,   400,   401,   402,   405,   405,
     420,   420,   429,   430,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   470,   475,   480,
     485,   490,   490,   498,   503,   508,   514,   514,   525,   526,
     529,   530,   531,   532,   533,   534,   535,   538,   538,   547,
     547,   557,   557,   564,   565,   568,   568,   575,   577,   581,
     587,   587,   599,   599,   609,   610,   612,   614,   614,   632,
     632,   644,   644,   654,   655,   658,   659,   662,   662,   672,
     673,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   696,
     696,   703,   704,   705,   706,   709,   709,   717,   717,   725,
     725,   733,   738,   738,   746,   751,   756,   761,   766,   771,
     776,   781,   781,   789,   789,   797,   802,   807,   807,   817,
     818,   821,   822,   823,   824,   825,   828,   833,   838,   843,
     848,   853,   853,   863,   864,   867,   868,   871,   871,   881,
     881,   891,   892,   893,   896,   897,   900,   900,   908,   908,
     916,   916,   927,   928,   931,   932,   933,   934,   935,   936,
     939,   944,   949,   954,   959,   964,   972,   972,   985,   986,
     989,   990,   997,   997,  1023,  1023,  1034,  1035,  1039,  1040,
    1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,
    1061,  1062,  1065,  1065,  1073,  1073,  1081,  1081,  1089,  1089,
    1097,  1097,  1105,  1105,  1113,  1113,  1123,  1123,  1130,  1131,
    1132,  1133,  1136,  1143,  1143,  1154,  1155,  1159,  1160,  1163,
    1163,  1171,  1172,  1175,  1176,  1177,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,
    1192,  1193,  1200,  1200,  1213,  1213,  1222,  1223,  1226,  1227,
    1232,  1232,  1247,  1247,  1261,  1262,  1265,  1266,  1269,  1270,
    1271,  1272,  1273,  1274,  1275,  1276,  1277,  1278,  1281,  1283,
    1288,  1290,  1290,  1298,  1298,  1306,  1306,  1314,  1316,  1316,
    1324,  1333,  1333,  1345,  1346,  1351,  1352,  1357,  1357,  1369,
    1369,  1381,  1382,  1387,  1388,  1393,  1394,  1395,  1396,  1397,
    1398,  1399,  1400,  1401,  1404,  1406,  1406,  1414,  1416,  1418,
    1423,  1431,  1431,  1443,  1444,  1447,  1448,  1451,  1451,  1461,
    1461,  1471,  1472,  1475,  1476,  1477,  1478,  1479,  1480,  1481,
    1484,  1484,  1492,  1492,  1517,  1517,  1547,  1547,  1557,  1558,
    1561,  1562,  1565,  1565,  1574,  1574,  1583,  1584,  1587,  1588,
    1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,
    1602,  1603,  1604,  1605,  1606,  1609,  1609,  1617,  1617,  1625,
    1625,  1633,  1633,  1641,  1641,  1651,  1651,  1659,  1659,  1667,
    1667,  1675,  1675,  1683,  1683,  1691,  1691,  1699,  1699,  1712,
    1712,  1722,  1723,  1729,  1729,  1739,  1740,  1743,  1743,  1753,
    1754,  1757,  1758,  1761,  1762,  1763,  1764,  1765,  1766,  1767,
    1768,  1769,  1770,  1771,  1774,  1776,  1776,  1784,  1793,  1800,
    1800,  1810,  1811,  1814,  1815,  1816,  1817,  1818,  1821,  1821,
    1829,  1829,  1840,  1840,  1858,  1858,  1870,  1870,  1880,  1881,
    1884,  1885,  1886,  1887,  1888,  1889,  1890,  1891,  1892,  1893,
    1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1904,  1909,
    1909,  1917,  1917,  1925,  1930,  1930,  1938,  1943,  1948,  1948,
    1956,  1957,  1960,  1960,  1968,  1973,  1978,  1978,  1986,  1989,
    1992,  1995,  1998,  2004,  2004,  2012,  2012,  2020,  2020,  2031,
    2031,  2038,  2038,  2045,  2045,  2052,  2052,  2061,  2061,  2072,
    2072,  2082,  2083,  2087,  2088,  2091,  2091,  2106,  2106,  2116,
    2116,  2127,  2128,  2132,  2136,  2136,  2148,  2149,  2153,  2153,
    2161,  2162,  2165,  2166,  2167,  2168,  2169,  2170,  2171,  2174,
    2179,  2179,  2187,  2187,  2197,  2198,  2201,  2201,  2209,  2210,
    2213,  2214,  2215,  2216,  2219,  2219,  2227,  2232,  2237
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


#line 14 "dhcp4_parser.yy" // lalr1.cc:1218
} } // isc::dhcp
#line 4946 "dhcp4_parser.cc" // lalr1.cc:1218
#line 2242 "dhcp4_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
