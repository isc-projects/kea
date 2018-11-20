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

  case 108:
#line 471 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1069 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 476 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1078 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 481 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1087 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 486 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1096 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 491 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 493 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 499 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1123 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 504 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 509 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1141 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 515 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 118:
#line 520 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 539 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 543 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 548 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1192 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 553 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1201 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 558 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 560 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 134:
#line 565 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1224 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 135:
#line 566 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1230 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 136:
#line 569 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 137:
#line 571 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 576 "dhcp4_parser.yy" // lalr1.cc:907
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 578 "dhcp4_parser.yy" // lalr1.cc:907
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1263 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 140:
#line 582 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 141:
#line 588 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 142:
#line 593 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 143:
#line 600 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1305 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 144:
#line 605 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 615 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 617 "dhcp4_parser.yy" // lalr1.cc:907
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

  case 150:
#line 633 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1353 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 151:
#line 638 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 152:
#line 645 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 153:
#line 650 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 158:
#line 663 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 159:
#line 667 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 697 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 699 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1421 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 704 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1427 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 705 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1433 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 706 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1439 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 707 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1445 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 710 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 712 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1463 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 718 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1471 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 720 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1481 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 726 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 191:
#line 728 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 192:
#line 734 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 739 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 741 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 195:
#line 747 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1535 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 752 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 757 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 762 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 767 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1571 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 772 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 777 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1589 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 782 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 784 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 790 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 792 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 206:
#line 798 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 207:
#line 803 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1643 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 208:
#line 808 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 209:
#line 813 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 217:
#line 829 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 218:
#line 834 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 219:
#line 839 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 844 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 849 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 854 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 859 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 228:
#line 872 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 876 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1748 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 882 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 886 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1768 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 237:
#line 901 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 238:
#line 903 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1786 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 239:
#line 909 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 240:
#line 911 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 241:
#line 917 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 242:
#line 922 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 251:
#line 940 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 252:
#line 945 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 253:
#line 950 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 254:
#line 955 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 255:
#line 960 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 965 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1878 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 257:
#line 973 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 258:
#line 978 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 263:
#line 998 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1908 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 264:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:907
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

  case 265:
#line 1024 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1944 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 266:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 293:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 294:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 295:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1980 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1990 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2008 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2026 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 301:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 302:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 303:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 304:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 305:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 306:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 307:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 308:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 309:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2105 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 310:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2111 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 311:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2117 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 312:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2123 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 313:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 314:
#line 1144 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 315:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 320:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2162 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 321:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 343:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 344:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 345:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2199 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 346:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 351:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 352:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 353:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 354:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 370:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 372:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 373:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2286 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 376:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 377:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 379:
#line 1317 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 380:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 381:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 382:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 383:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 388:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2371 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 389:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 390:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 391:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 406:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 407:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 410:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 411:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 413:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 418:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 419:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2475 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 420:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 421:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 431:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 432:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 433:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2521 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 434:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:907
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

  case 435:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:907
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

  case 437:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2596 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 438:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 443:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2615 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 444:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2624 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 445:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2634 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 446:
#line 1579 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2643 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 466:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 467:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 468:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 469:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2679 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 470:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 471:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2697 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 472:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 473:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2715 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 474:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 475:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 476:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 477:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2761 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 482:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 483:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2807 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2815 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2825 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1694 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2843 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2874 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 491:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2883 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 494:
#line 1730 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2894 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 495:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2903 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1748 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 518:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 519:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 520:
#line 1801 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2970 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 521:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2979 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 529:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2987 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 530:
#line 1824 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 531:
#line 1830 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 532:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 533:
#line 1841 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3023 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1843 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 3061 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1879 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3072 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3093 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 538:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3103 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 559:
#line 1925 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3112 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 560:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3120 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 562:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 563:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 564:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3157 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 565:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3165 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 566:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3175 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 567:
#line 1959 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3184 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 568:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3193 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 569:
#line 1969 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3201 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 570:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3210 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 571:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3216 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 572:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3222 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 573:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 574:
#line 1983 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1994 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 578:
#line 2001 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3283 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 2010 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3291 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 581:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3299 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3307 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 2019 "dhcp4_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3316 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 584:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3324 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 585:
#line 2027 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3334 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 586:
#line 2033 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3342 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 587:
#line 2035 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3352 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 588:
#line 2041 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3360 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3370 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2054 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3387 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2059 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3395 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3404 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3412 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3421 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3431 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2077 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3439 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3450 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2087 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2093 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3470 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 601:
#line 2097 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3479 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2112 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2117 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3499 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2127 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3510 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2132 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3519 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2137 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3529 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 611:
#line 2141 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3537 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2157 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3548 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2162 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3557 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3567 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2178 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3575 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2195 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3584 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2200 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3592 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2202 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3602 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2208 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3613 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 634:
#line 2213 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3622 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2222 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3632 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 638:
#line 2226 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3640 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 645:
#line 2240 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3648 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 646:
#line 2242 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3658 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 647:
#line 2248 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3667 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 648:
#line 2253 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3676 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 649:
#line 2258 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3685 "dhcp4_parser.cc" // lalr1.cc:907
    break;


#line 3689 "dhcp4_parser.cc" // lalr1.cc:907
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


  const short Dhcp4Parser::yypact_ninf_ = -796;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     343,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,    50,    35,    56,    62,    64,
     110,   129,   151,   183,   191,   222,   224,   228,   243,   262,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,    35,    95,
      18,    69,    43,   167,   148,   188,   205,    77,   111,   -56,
     463,   147,    41,  -796,   295,   290,   300,   303,   309,  -796,
    -796,  -796,  -796,  -796,   319,  -796,    57,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,   323,   325,   337,
    -796,  -796,  -796,  -796,  -796,  -796,   348,   357,   359,   362,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   363,  -796,  -796,  -796,  -796,    59,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   364,  -796,    70,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,   367,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,    76,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,   125,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,   366,   373,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   370,  -796,
    -796,   378,  -796,  -796,  -796,   380,  -796,  -796,   377,   383,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   385,   386,  -796,  -796,  -796,  -796,   379,
     390,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   126,  -796,  -796,  -796,   392,  -796,  -796,
     394,  -796,   395,   398,  -796,  -796,   399,   403,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,   127,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   181,  -796,  -796,  -796,  -796,   201,  -796,
    -796,  -796,    35,    35,  -796,   166,   408,   411,   412,   413,
     414,  -796,    18,  -796,    41,   417,   418,   421,   226,   261,
     268,   426,   433,   435,   436,   437,   438,   277,   278,   279,
     280,   443,   445,   446,   447,   464,   466,   469,   470,   471,
     472,   473,   474,   476,   315,   478,   479,   480,    69,  -796,
     481,   482,   483,   320,    43,  -796,   485,   486,   487,   488,
     504,   505,   346,   509,   510,   511,   167,  -796,   512,   148,
    -796,   514,   515,   516,   517,   520,   521,   522,   523,  -796,
     188,  -796,   524,   525,   365,   528,   530,   531,   368,  -796,
      77,   533,   374,   376,  -796,   111,   534,   537,   -72,  -796,
     381,   542,   543,   384,   547,   387,   388,   548,   551,   389,
     391,   556,   557,   558,   559,   463,  -796,   560,   147,  -796,
     561,    41,  -796,  -796,  -796,   562,   563,   564,    35,    35,
      35,  -796,   202,   565,   566,   568,  -796,  -796,  -796,   402,
     404,   429,   570,   571,   574,  -796,  -796,  -796,  -796,   430,
     591,   592,   593,   594,   595,   439,   195,   598,   600,   601,
     602,   603,  -796,   604,   595,   605,  -796,   608,   153,   234,
    -796,  -796,   444,   449,   450,   611,   452,   453,  -796,   608,
     454,   613,  -796,   456,  -796,   608,   457,   458,   459,   460,
     461,   462,   465,  -796,   467,   468,  -796,   475,   477,   484,
    -796,  -796,   489,  -796,  -796,  -796,   490,    35,  -796,  -796,
     491,   492,  -796,   493,  -796,  -796,    29,   497,  -796,  -796,
     -28,   494,   495,   496,  -796,   626,  -796,   629,  -796,    35,
      69,   147,  -796,  -796,  -796,  -796,    41,    43,   545,  -796,
    -796,  -796,   415,   415,   628,  -796,   630,   631,   632,   634,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   244,   636,
     637,   638,   208,    -2,  -796,   463,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,   639,  -796,  -796,
    -796,  -796,    72,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   640,   628,  -796,   204,
     210,   211,   229,  -796,   230,  -796,  -796,  -796,  -796,  -796,
    -796,   644,   646,   647,   648,   649,  -796,  -796,   658,   659,
     660,   661,   662,  -796,   253,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   254,  -796,   663,   633,  -796,  -796,   664,
     665,  -796,  -796,   666,   668,  -796,  -796,   667,   671,  -796,
    -796,   669,   673,  -796,  -796,  -796,  -796,  -796,  -796,    83,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,    84,  -796,  -796,
     672,   674,  -796,  -796,   675,   676,  -796,   678,   679,   680,
     681,   682,   683,   260,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   286,  -796,  -796,  -796,
     287,   502,  -796,   684,   677,  -796,  -796,  -796,  -796,   685,
    -796,   115,  -796,   686,  -796,  -796,  -796,  -796,   687,   545,
    -796,   690,   691,   692,   693,   442,   532,   535,   536,   539,
     694,   695,   540,   541,   544,   546,   549,   415,  -796,  -796,
     415,  -796,   628,   167,  -796,   630,    77,  -796,   631,   111,
    -796,   632,   245,  -796,   634,   244,  -796,    75,   636,  -796,
     188,  -796,   637,   -56,  -796,   638,   550,   552,   553,   554,
     555,   567,   208,  -796,   698,   699,    -2,  -796,  -796,  -796,
     702,   706,   148,  -796,   639,   707,  -796,   328,   640,  -796,
    -796,   569,  -796,   321,   572,   573,   575,  -796,  -796,  -796,
    -796,  -796,   576,   577,  -796,  -796,  -796,  -796,  -796,  -796,
     288,  -796,   294,  -796,   705,  -796,   714,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
     302,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,   710,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,   715,   712,  -796,  -796,  -796,  -796,  -796,   716,
    -796,   317,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
     578,   579,  -796,  -796,   580,   327,  -796,   608,  -796,   721,
    -796,  -796,  -796,  -796,  -796,   340,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   245,  -796,   722,   581,
    -796,    75,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   723,
     582,   724,   328,  -796,  -796,   586,  -796,  -796,   725,  -796,
     587,  -796,  -796,   728,  -796,  -796,   156,  -796,   -31,   728,
    -796,  -796,   727,   732,   735,   342,  -796,  -796,  -796,  -796,
    -796,  -796,   742,   589,   588,   612,   -31,  -796,   590,  -796,
    -796,  -796,  -796,  -796
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   128,     9,   265,    11,
     420,    13,   445,    15,   345,    17,   353,    19,   390,    21,
     230,    23,   537,    25,   610,    27,   600,    29,    47,    41,
       0,     0,     0,     0,     0,   447,     0,   355,   392,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     608,   590,   592,   594,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   596,   598,   117,   143,     0,     0,     0,
     466,   468,   470,   141,   150,   152,     0,     0,     0,     0,
     112,   257,   343,   382,   314,   433,   435,   307,   208,   494,
     437,   222,   241,     0,   520,   533,   535,   107,     0,    72,
      74,    75,    76,    77,   105,    94,    95,    96,    80,    81,
     102,    82,    83,    84,    88,    89,    78,   106,    79,    86,
      87,   100,   101,   103,    97,    98,    99,    85,    90,    91,
      92,    93,   104,   130,   132,   136,     0,   127,     0,   119,
     121,   122,   123,   124,   125,   126,   295,   297,   299,   412,
     293,   301,     0,   305,   303,   490,   292,   269,   270,   271,
     282,   283,     0,   267,   274,   287,   288,   289,   275,   277,
     278,   280,   276,   272,   273,   290,   291,   279,   284,   285,
     286,   281,   431,   430,   426,   427,   425,     0,   422,   424,
     428,   429,   488,   476,   478,   482,   480,   486,   484,   472,
     465,   459,   463,   464,     0,   448,   449,   460,   461,   462,
     456,   451,   457,   453,   454,   455,   458,   452,     0,   372,
     193,     0,   376,   374,   379,     0,   368,   369,     0,   356,
     357,   359,   371,   360,   361,   362,   378,   363,   364,   365,
     366,   367,   406,     0,     0,   404,   405,   408,   409,     0,
     393,   394,   396,   397,   398,   399,   400,   401,   402,   403,
     237,   239,   234,     0,   232,   235,   236,     0,   560,   562,
       0,   565,     0,     0,   569,   573,     0,     0,   577,   584,
     586,   588,   558,   556,   557,     0,   539,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   615,     0,   612,   614,   606,   605,     0,   602,
     604,    46,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    57,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    71,
       0,     0,     0,     0,     0,   129,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   266,     0,     0,
     421,     0,     0,     0,     0,     0,     0,     0,     0,   446,
       0,   346,     0,     0,     0,     0,     0,     0,     0,   354,
       0,     0,     0,     0,   391,     0,     0,     0,     0,   231,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   538,     0,     0,   611,
       0,     0,   601,    50,    43,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,   114,   115,   116,     0,
       0,     0,     0,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   519,     0,     0,     0,    73,     0,     0,     0,
     140,   120,     0,     0,     0,     0,     0,     0,   313,     0,
       0,     0,   268,     0,   423,     0,     0,     0,     0,     0,
       0,     0,     0,   450,     0,     0,   370,     0,     0,     0,
     381,   358,     0,   410,   411,   395,     0,     0,   233,   559,
       0,     0,   564,     0,   567,   568,     0,     0,   575,   576,
       0,     0,     0,     0,   540,     0,   613,     0,   603,     0,
       0,     0,   591,   593,   595,   597,     0,     0,     0,   467,
     469,   471,     0,     0,   154,   113,   259,   347,   384,   316,
      40,   434,   436,   309,   310,   311,   312,   308,     0,     0,
     439,   224,     0,     0,   534,     0,    51,   131,   134,   135,
     133,   138,   139,   137,   296,   298,   300,   414,   294,   302,
     306,   304,     0,   432,   489,   477,   479,   483,   481,   487,
     485,   473,   373,   194,   377,   375,   380,   407,   238,   240,
     561,   563,   566,   571,   572,   570,   574,   579,   580,   581,
     582,   583,   578,   585,   587,   589,     0,   154,    44,     0,
       0,     0,     0,   148,     0,   145,   147,   180,   186,   188,
     190,     0,     0,     0,     0,     0,   202,   204,     0,     0,
       0,     0,     0,   179,     0,   160,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   175,   176,   177,   172,
     178,   173,   174,     0,   158,     0,   155,   156,   263,     0,
     260,   261,   351,     0,   348,   349,   388,     0,   385,   386,
     320,     0,   317,   318,   217,   218,   219,   220,   221,     0,
     210,   212,   213,   214,   215,   216,   498,     0,   496,   443,
       0,   440,   441,   228,     0,   225,   226,     0,     0,     0,
       0,     0,     0,     0,   243,   245,   246,   247,   248,   249,
     250,   529,   531,   528,   526,   527,     0,   522,   524,   525,
       0,    53,   418,     0,   415,   416,   474,   492,   493,     0,
     619,     0,   617,     0,    69,   609,   599,   118,     0,     0,
     144,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   142,   151,
       0,   153,     0,     0,   258,     0,   355,   344,     0,   392,
     383,     0,     0,   315,     0,     0,   209,   500,     0,   495,
     447,   438,     0,     0,   223,     0,     0,     0,     0,     0,
       0,     0,     0,   242,     0,     0,     0,   521,   536,    55,
       0,    54,     0,   413,     0,     0,   491,     0,     0,   616,
     607,     0,   146,     0,     0,     0,     0,   192,   195,   196,
     197,   198,     0,     0,   206,   207,   199,   200,   201,   161,
       0,   157,     0,   262,     0,   350,     0,   387,   342,   339,
     327,   328,   330,   331,   324,   325,   326,   337,   338,   336,
       0,   322,   329,   340,   341,   332,   333,   334,   335,   319,
     211,   516,     0,   514,   515,   507,   508,   512,   513,   509,
     510,   511,     0,   501,   502,   504,   505,   506,   497,     0,
     442,     0,   227,   251,   252,   253,   254,   255,   256,   244,
       0,     0,   523,    52,     0,     0,   417,     0,   633,     0,
     631,   629,   623,   627,   628,     0,   621,   625,   626,   624,
     618,   149,   182,   183,   184,   185,   181,   187,   189,   191,
     203,   205,   159,   264,   352,   389,     0,   321,     0,     0,
     499,     0,   444,   229,   530,   532,    56,   419,   475,     0,
       0,     0,     0,   620,   323,     0,   518,   503,     0,   630,
       0,   622,   517,     0,   632,   637,     0,   635,     0,     0,
     634,   645,     0,     0,     0,     0,   639,   641,   642,   643,
     644,   636,     0,     0,     0,     0,     0,   638,     0,   647,
     648,   649,   640,   646
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   -46,  -796,  -455,  -796,
     174,  -796,  -796,  -796,  -796,  -796,  -796,  -505,  -796,  -796,
    -796,   -70,  -796,  -796,  -796,   396,  -796,  -796,  -796,  -796,
     109,   331,   -47,   -44,     4,  -796,  -796,  -796,  -796,    12,
      15,  -796,  -796,   145,   356,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,   -18,  -796,  -796,  -796,  -796,  -796,  -796,   101,  -796,
     -51,  -796,  -568,   -35,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,   -26,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,   -40,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,   -54,  -796,  -796,  -796,   -41,   341,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,   -43,  -796,  -796,  -796,  -796,
    -796,  -796,  -795,  -796,  -796,  -796,   -29,  -796,  -796,  -796,
     -15,   406,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -789,  -796,   -68,  -796,   -55,  -796,    19,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,   -22,  -796,  -796,  -172,   -63,  -796,
    -796,  -796,  -796,  -796,   -13,  -796,  -796,  -796,     0,  -796,
     409,  -796,   -66,  -796,  -796,  -796,  -796,  -796,   -64,  -796,
    -796,  -796,  -796,  -796,   -19,  -796,  -796,  -796,   -12,  -796,
    -796,  -796,    -5,  -796,   401,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,   -32,  -796,  -796,  -796,
     -23,   431,  -796,  -796,   -57,  -796,   -39,  -796,   -62,  -796,
    -796,  -796,    10,  -796,  -796,  -796,    13,  -796,   424,    -7,
    -796,    -3,  -796,     8,  -796,   223,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -787,  -796,  -796,  -796,  -796,  -796,    20,
    -796,  -796,  -796,  -135,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,     1,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   246,   397,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -337,   393,  -796,  -796,  -796,  -796,  -796,  -796,
     282,   400,  -796,  -796,  -796,    -9,  -796,  -796,  -142,  -796,
    -796,  -796,  -796,  -796,  -796,  -154,  -796,  -796,  -170,  -796,
    -796,  -796,  -796,  -796
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     601,    87,    88,    41,    68,    84,    85,   617,   781,   860,
     861,   347,    43,    70,    96,    97,    98,   356,    45,    71,
     138,   139,   140,   141,   142,   143,   144,   381,   145,   146,
     147,   148,   366,   178,   179,    47,    72,   180,   400,   181,
     401,   620,   182,   402,   623,   183,   149,   374,   150,   367,
     674,   675,   676,   798,   151,   375,   152,   376,   715,   716,
     717,   820,   694,   695,   696,   801,   976,   697,   802,   698,
     803,   699,   804,   700,   701,   433,   702,   703,   704,   705,
     706,   707,   708,   709,   810,   710,   811,   711,   712,   153,
     389,   739,   740,   741,   742,   743,   744,   745,   154,   392,
     754,   755,   756,   843,    61,    79,   303,   304,   305,   446,
     306,   447,   155,   393,   763,   764,   765,   766,   767,   768,
     769,   770,   156,   382,   719,   720,   721,   823,    49,    73,
     202,   203,   204,   410,   205,   406,   206,   407,   207,   408,
     208,   411,   209,   414,   210,   413,   157,   388,   607,   212,
     158,   385,   731,   732,   733,   832,   910,   911,   159,   383,
      55,    76,   723,   724,   725,   826,    57,    77,   268,   269,
     270,   271,   272,   273,   274,   432,   275,   436,   276,   435,
     277,   278,   437,   279,   160,   384,   727,   728,   729,   829,
      59,    78,   289,   290,   291,   292,   293,   441,   294,   295,
     296,   297,   214,   409,   783,   784,   785,   862,    51,    74,
     227,   228,   229,   418,   161,   386,   162,   387,   163,   391,
     750,   751,   752,   840,    53,    75,   244,   245,   246,   164,
     371,   165,   372,   166,   373,   250,   428,   788,   865,   251,
     422,   252,   423,   253,   425,   254,   424,   255,   427,   256,
     426,   257,   421,   221,   415,   789,   167,   390,   747,   748,
     837,   932,   933,   934,   935,   936,   988,   937,   168,   169,
     395,   776,   777,   778,   854,   779,   855,   170,   396,   171,
     397,    63,    80,   325,   326,   327,   328,   451,   329,   452,
     330,   331,   454,   332,   333,   334,   457,   655,   335,   458,
     336,   337,   338,   461,   662,   339,   462,   340,   463,   341,
     464,    99,   358,   100,   359,   101,   360,   172,   364,   365,
      67,    82,   348,   349,   350,   470,   102,   357,    65,    81,
     343,   344,   345,   467,   791,   792,   867,   965,   966,   967,
     968,  1001,   969,   999,  1016,  1017,  1018,  1025,  1026,  1027,
    1032,  1028,  1029,  1030
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   137,   177,   196,   223,   240,   224,   266,   285,   302,
     322,   217,   287,   258,   288,   184,   215,   230,   242,   225,
     280,   298,    83,   323,   630,   713,   197,   482,    89,   198,
     634,   300,   301,   185,   216,   231,   243,   905,   281,   299,
      31,   324,    32,   906,    33,   918,   653,   300,   301,   600,
      30,   267,   286,   346,   213,   226,   241,   173,   174,   600,
     362,   175,   398,    42,   176,   363,   218,   399,   247,    44,
     219,    46,   248,   404,   125,   126,   103,   199,   405,   416,
     104,   220,   105,   249,   417,   200,   835,   838,   201,   836,
     839,   106,   211,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   110,   111,   112,   657,   658,   659,   660,    94,
     259,  1021,   771,   772,  1022,  1023,  1024,    48,   868,   125,
     126,   869,   116,   117,   118,   119,   120,   121,   419,   448,
     465,   122,   123,   420,   449,   466,    50,   122,   123,   260,
     661,   260,   124,   261,   262,   125,   126,   263,   264,   265,
     127,   125,   126,   125,   126,   128,   129,    90,    52,  1019,
     654,   130,  1020,    94,   921,   922,    91,    92,    93,   618,
     619,   131,   239,   786,   132,   260,   282,   261,   262,   283,
     284,   133,   134,    94,   468,   135,   136,   125,   126,   469,
      54,   905,   108,   109,   110,   111,   112,   906,    56,   918,
      34,    35,    36,    37,   471,   471,    94,   398,    94,   472,
     585,   123,   794,   468,   471,   110,   111,   112,   795,   796,
     116,   117,   118,   222,   125,   126,   186,   187,   188,    58,
     123,    60,   404,   799,    94,    62,   193,   797,   800,   194,
      94,   189,    94,   125,   126,   190,   191,   192,   127,   671,
      64,   123,   890,   621,   622,   193,   817,   817,   194,   130,
      86,   818,   819,   852,   125,   126,   195,   122,   853,    66,
     108,   109,   110,   111,   112,   232,    94,   603,   604,   605,
     606,   233,   234,   235,   236,   237,   238,   342,   239,   856,
     465,   817,    95,   352,   857,   858,   982,   416,   116,   117,
     118,   351,   983,   121,   353,   986,   473,   474,   123,   260,
     987,   354,   355,    94,   757,   758,   759,   760,   761,   762,
     448,   125,   126,   361,   191,   993,   127,   368,   137,   369,
     419,   475,    94,   193,   177,   997,   194,   734,   735,   736,
     737,   370,   738,  1002,   195,  1036,   196,   184,  1003,   223,
    1037,   224,   377,    94,   217,   972,   973,   974,   975,   215,
     240,   378,   230,   379,   225,   185,   380,   394,   403,   197,
     266,   412,   198,   242,   429,   285,   430,   216,   431,   287,
     231,   288,   434,   280,   438,   439,   440,   444,   298,   442,
     443,   243,   260,   445,   486,   322,   450,   213,   453,   455,
     226,   281,   456,   459,   125,   126,   299,   460,   323,   218,
      94,   241,   476,   219,   267,   477,   478,   479,   480,   286,
     199,   483,   484,   247,   220,   485,   324,   248,   200,   487,
     489,   201,   582,   583,   584,   211,   488,   490,   249,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   677,   500,
     501,   502,   998,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   503,   958,
     504,   959,   960,   505,   506,   507,   508,   509,   510,   260,
     511,   512,   513,   514,   515,   517,   518,   519,   520,   522,
     523,   524,   525,    94,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   526,   527,
     137,   649,   528,   529,   530,   531,   533,   177,   535,   536,
     537,   538,   693,   693,   539,   540,   541,   542,   544,   545,
     184,   546,   547,   668,   548,   549,   550,   552,   556,   125,
     126,   557,   553,   773,   554,   322,   560,   561,   185,   559,
     562,   563,   566,   564,   565,   567,   774,   568,   323,   569,
     570,   571,   572,   573,   575,   577,   579,   589,   673,   590,
     580,   581,   586,   587,   775,   588,   324,   592,   593,   594,
      94,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   591,   595,   596,   597,   598,   599,
     320,   321,    32,   608,   602,   609,   610,   611,   877,   624,
     612,   613,   615,   616,   625,   626,   627,   628,   629,   631,
     632,   633,   635,   636,   637,   638,   639,   640,    94,   656,
     641,   666,   642,   643,   667,   714,   822,   718,   722,   726,
     644,   730,   645,   746,   749,   753,   782,   790,   805,   646,
     806,   807,   808,   809,   647,   648,   650,   651,   652,   663,
     664,   665,   812,   813,   814,   815,   816,   859,   825,   821,
     824,   828,   827,   830,   831,   833,   834,   842,   841,   845,
     864,   844,   846,   847,   848,   849,   850,   851,   614,   669,
     863,   871,   870,   866,   873,   874,   875,   876,   882,   883,
     878,   879,   950,   951,   880,   881,   884,   885,   953,   954,
     886,   957,   887,   984,   989,   991,   943,   888,   944,   945,
     946,   947,   985,   990,   992,  1000,  1005,  1008,  1010,   516,
    1013,  1033,   672,   948,   971,  1015,  1034,   977,   978,  1035,
     979,   980,   981,   994,   995,   996,  1038,   693,  1009,  1006,
     693,  1012,  1014,   196,  1040,  1043,   266,  1039,   481,   285,
     521,   217,   898,   287,   907,   288,   215,   923,   793,   280,
     240,   891,   298,   302,   925,   913,   197,   908,  1041,   198,
     927,   872,   889,   242,   216,   899,   773,   281,   900,   558,
     299,   942,   223,   914,   224,   920,   893,   961,   928,   774,
     267,   243,   941,   286,   213,   230,   904,   225,   892,   949,
     963,   924,   919,   912,  1004,   895,   218,   775,   926,   897,
     219,   241,   532,   231,   896,   915,   894,   199,   964,   916,
     929,   220,   956,   247,   930,   200,   901,   248,   201,   955,
     917,   962,   211,   226,   902,   931,   555,   903,   249,   551,
     534,   909,   940,   939,   543,   787,  1007,   952,   938,   970,
    1011,   780,   574,   670,   578,  1031,  1042,     0,   576,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   898,     0,   907,     0,
       0,   923,     0,     0,     0,     0,     0,     0,   925,   913,
       0,   908,   961,     0,   927,     0,     0,     0,     0,   899,
       0,     0,   900,     0,     0,   963,     0,   914,     0,     0,
       0,     0,   928,     0,     0,     0,     0,     0,     0,     0,
     904,     0,     0,   964,     0,   924,     0,   912,     0,     0,
       0,     0,   926,     0,     0,     0,   962,     0,     0,   915,
       0,     0,     0,   916,   929,     0,     0,     0,   930,     0,
     901,     0,     0,     0,   917,     0,     0,     0,   902,   931,
       0,   903,     0,     0,     0,   909
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,    74,
      77,    78,    68,    80,   529,   593,    73,   364,    10,    73,
     535,   103,   104,    72,    73,    74,    75,   832,    77,    78,
       5,    80,     7,   832,     9,   832,    17,   103,   104,   504,
       0,    77,    78,    12,    73,    74,    75,    14,    15,   514,
       3,    18,     3,     7,    21,     8,    73,     8,    75,     7,
      73,     7,    75,     3,    76,    77,     7,    73,     8,     3,
      11,    73,    13,    75,     8,    73,     3,     3,    73,     6,
       6,    22,    73,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    27,    28,    29,   133,   134,   135,   136,   165,
      33,   142,   114,   115,   145,   146,   147,     7,     3,    76,
      77,     6,    53,    54,    55,    56,    57,    58,     3,     3,
       3,    62,    63,     8,     8,     8,     7,    62,    63,    64,
     168,    64,    73,    66,    67,    76,    77,    70,    71,    72,
      81,    76,    77,    76,    77,    86,    87,   139,     7,     3,
     131,    92,     6,   165,    89,    90,   148,   149,   150,    16,
      17,   102,   100,   101,   105,    64,    65,    66,    67,    68,
      69,   112,   113,   165,     3,   116,   117,    76,    77,     8,
       7,   986,    25,    26,    27,    28,    29,   986,     7,   986,
     165,   166,   167,   168,     3,     3,   165,     3,   165,     8,
       8,    63,     8,     3,     3,    27,    28,    29,     8,     8,
      53,    54,    55,    75,    76,    77,    59,    60,    61,     7,
      63,     7,     3,     3,   165,     7,    88,     8,     8,    91,
     165,    74,   165,    76,    77,    78,    79,    80,    81,   586,
       7,    63,   820,    19,    20,    88,     3,     3,    91,    92,
     165,     8,     8,     3,    76,    77,    99,    62,     8,     7,
      25,    26,    27,    28,    29,    87,   165,    82,    83,    84,
      85,    93,    94,    95,    96,    97,    98,   140,   100,     3,
       3,     3,   362,     3,     8,     8,     8,     3,    53,    54,
      55,     6,     8,    58,     4,     3,   352,   353,    63,    64,
       8,     8,     3,   165,   106,   107,   108,   109,   110,   111,
       3,    76,    77,     4,    79,     8,    81,     4,   398,     4,
       3,   165,   165,    88,   404,     8,    91,    93,    94,    95,
      96,     4,    98,     3,    99,     3,   416,   404,     8,   419,
       8,   419,     4,   165,   416,    34,    35,    36,    37,   416,
     430,     4,   419,     4,   419,   404,     4,     4,     4,   416,
     440,     4,   416,   430,     8,   445,     3,   416,     8,   445,
     419,   445,     4,   440,     4,     8,     3,     8,   445,     4,
       4,   430,    64,     3,   168,   465,     4,   416,     4,     4,
     419,   440,     4,     4,    76,    77,   445,     4,   465,   416,
     165,   430,     4,   416,   440,     4,     4,     4,     4,   445,
     416,     4,     4,   430,   416,     4,   465,   430,   416,   168,
       4,   416,   478,   479,   480,   416,   168,     4,   430,     4,
       4,     4,     4,   166,   166,   166,   166,     4,    33,     4,
       4,     4,   957,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,     4,   141,
       4,   143,   144,     4,     4,     4,     4,     4,     4,    64,
       4,   166,     4,     4,     4,     4,     4,     4,   168,     4,
       4,     4,     4,   165,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,     4,     4,
     580,   557,   166,     4,     4,     4,     4,   587,     4,     4,
       4,     4,   592,   593,     4,     4,     4,     4,     4,     4,
     587,   166,     4,   579,     4,     4,   168,     4,     4,    76,
      77,     4,   168,   613,   168,   615,     4,     4,   587,   168,
     166,     4,     4,   166,   166,     4,   613,   168,   615,   168,
       4,     4,     4,     4,     4,     4,     4,   165,    23,   165,
       7,     7,     7,     7,   613,     7,   615,     7,     7,     5,
     165,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   165,   165,     5,     5,     5,     5,
     137,   138,     7,     5,   165,     5,     5,     5,   166,   165,
       7,     7,     7,     5,   165,   165,     5,   165,   165,   165,
       7,   165,   165,   165,   165,   165,   165,   165,   165,   132,
     165,     5,   165,   165,     5,     7,     3,     7,     7,     7,
     165,     7,   165,     7,     7,     7,     7,     7,     4,   165,
       4,     4,     4,     4,   165,   165,   165,   165,   165,   165,
     165,   165,     4,     4,     4,     4,     4,   165,     3,     6,
       6,     3,     6,     6,     3,     6,     3,     3,     6,     3,
       3,     6,     4,     4,     4,     4,     4,     4,   514,   580,
       6,     4,     6,     8,     4,     4,     4,     4,     4,     4,
     168,   166,     4,     4,   168,   166,   166,   166,     6,     3,
     166,     4,   166,     8,     4,     3,   166,   168,   166,   166,
     166,   166,     8,     8,     8,     4,     4,     4,     4,   398,
       5,     4,   587,   166,   165,     7,     4,   165,   165,     4,
     165,   165,   165,   165,   165,   165,     4,   817,   166,   168,
     820,   165,   165,   823,   166,   165,   826,   168,   362,   829,
     404,   823,   832,   829,   832,   829,   823,   837,   667,   826,
     840,   822,   829,   843,   837,   832,   823,   832,   166,   823,
     837,   799,   817,   840,   823,   832,   856,   826,   832,   448,
     829,   845,   862,   832,   862,   835,   825,   867,   837,   856,
     826,   840,   843,   829,   823,   862,   832,   862,   823,   852,
     867,   837,   834,   832,   986,   828,   823,   856,   837,   831,
     823,   840,   416,   862,   829,   832,   826,   823,   867,   832,
     837,   823,   864,   840,   837,   823,   832,   840,   823,   862,
     832,   867,   823,   862,   832,   837,   445,   832,   840,   440,
     419,   832,   842,   840,   430,   632,   991,   856,   838,   868,
    1002,   615,   465,   581,   471,  1019,  1036,    -1,   468,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   986,    -1,   986,    -1,
      -1,   991,    -1,    -1,    -1,    -1,    -1,    -1,   991,   986,
      -1,   986,  1002,    -1,   991,    -1,    -1,    -1,    -1,   986,
      -1,    -1,   986,    -1,    -1,  1002,    -1,   986,    -1,    -1,
      -1,    -1,   991,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     986,    -1,    -1,  1002,    -1,   991,    -1,   986,    -1,    -1,
      -1,    -1,   991,    -1,    -1,    -1,  1002,    -1,    -1,   986,
      -1,    -1,    -1,   986,   991,    -1,    -1,    -1,   991,    -1,
     986,    -1,    -1,    -1,   986,    -1,    -1,    -1,   986,   991,
      -1,   986,    -1,    -1,    -1,   986
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
      57,    58,    62,    63,    73,    76,    77,    81,    86,    87,
      92,   102,   105,   112,   113,   116,   117,   200,   209,   210,
     211,   212,   213,   214,   215,   217,   218,   219,   220,   235,
     237,   243,   245,   278,   287,   301,   311,   335,   339,   347,
     373,   403,   405,   407,   418,   420,   422,   445,   457,   458,
     466,   468,   506,    14,    15,    18,    21,   200,   222,   223,
     226,   228,   231,   234,   403,   405,    59,    60,    61,    74,
      78,    79,    80,    88,    91,    99,   200,   211,   212,   213,
     218,   219,   319,   320,   321,   323,   325,   327,   329,   331,
     333,   335,   338,   373,   391,   403,   405,   407,   418,   420,
     422,   442,    75,   200,   331,   333,   373,   399,   400,   401,
     403,   405,    87,    93,    94,    95,    96,    97,    98,   100,
     200,   373,   403,   405,   415,   416,   417,   418,   420,   422,
     424,   428,   430,   432,   434,   436,   438,   440,   347,    33,
      64,    66,    67,    70,    71,    72,   200,   263,   357,   358,
     359,   360,   361,   362,   363,   365,   367,   369,   370,   372,
     403,   405,    65,    68,    69,   200,   263,   361,   367,   381,
     382,   383,   384,   385,   387,   388,   389,   390,   403,   405,
     103,   104,   200,   295,   296,   297,   299,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     137,   138,   200,   403,   405,   472,   473,   474,   475,   477,
     479,   480,   482,   483,   484,   487,   489,   490,   491,   494,
     496,   498,   140,   519,   520,   521,    12,   200,   511,   512,
     513,     6,     3,     4,     8,     3,   206,   516,   501,   503,
     505,     4,     3,     8,   507,   508,   221,   238,     4,     4,
       4,   419,   421,   423,   236,   244,   246,     4,     4,     4,
       4,   216,   312,   348,   374,   340,   404,   406,   336,   279,
     446,   408,   288,   302,     4,   459,   467,   469,     3,     8,
     227,   229,   232,     4,     3,     8,   324,   326,   328,   392,
     322,   330,     4,   334,   332,   443,     3,     8,   402,     3,
       8,   441,   429,   431,   435,   433,   439,   437,   425,     8,
       3,     8,   364,   264,     4,   368,   366,   371,     4,     8,
       3,   386,     4,     4,     8,     3,   298,   300,     3,     8,
       4,   476,   478,     4,   481,     4,     4,   485,   488,     4,
       4,   492,   495,   497,   499,     3,     8,   522,     3,     8,
     514,     3,     8,   185,   185,   165,     4,     4,     4,     4,
       4,   204,   511,     4,     4,     4,   168,   168,   168,     4,
       4,     4,     4,     4,     4,   166,   166,   166,   166,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   166,     4,     4,     4,   210,     4,     4,     4,
     168,   223,     4,     4,     4,     4,     4,     4,   166,     4,
       4,     4,   320,     4,   400,     4,     4,     4,     4,     4,
       4,     4,     4,   417,     4,     4,   166,     4,     4,     4,
     168,   359,     4,   168,   168,   383,     4,     4,   296,   168,
       4,     4,   166,     4,   166,   166,     4,     4,   168,   168,
       4,     4,     4,     4,   473,     4,   520,     4,   512,     4,
       7,     7,   185,   185,   185,     8,     7,     7,     7,   165,
     165,   165,     7,     7,     5,   165,     5,     5,     5,     5,
     187,   189,   165,    82,    83,    84,    85,   337,     5,     5,
       5,     5,     7,     7,   189,     7,     5,   196,    16,    17,
     230,    19,    20,   233,   165,   165,   165,     5,   165,   165,
     196,   165,     7,   165,   196,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   185,
     165,   165,   165,    17,   131,   486,   132,   133,   134,   135,
     136,   168,   493,   165,   165,   165,     5,     5,   185,   209,
     519,   511,   222,    23,   239,   240,   241,    33,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,   200,   251,   252,   253,   256,   258,   260,
     262,   263,   265,   266,   267,   268,   269,   270,   271,   272,
     274,   276,   277,   251,     7,   247,   248,   249,     7,   313,
     314,   315,     7,   351,   352,   353,     7,   375,   376,   377,
       7,   341,   342,   343,    93,    94,    95,    96,    98,   280,
     281,   282,   283,   284,   285,   286,     7,   447,   448,     7,
     409,   410,   411,     7,   289,   290,   291,   106,   107,   108,
     109,   110,   111,   303,   304,   305,   306,   307,   308,   309,
     310,   114,   115,   200,   403,   405,   460,   461,   462,   464,
     472,   197,     7,   393,   394,   395,   101,   424,   426,   444,
       7,   523,   524,   247,     8,     8,     8,     8,   242,     3,
       8,   254,   257,   259,   261,     4,     4,     4,     4,     4,
     273,   275,     4,     4,     4,     4,     4,     3,     8,     8,
     250,     6,     3,   316,     6,     3,   354,     6,     3,   378,
       6,     3,   344,     6,     3,     3,     6,   449,     3,     6,
     412,     6,     3,   292,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   463,   465,     3,     8,     8,   165,
     198,   199,   396,     6,     3,   427,     8,   525,     3,     6,
       6,     4,   240,     4,     4,     4,     4,   166,   168,   166,
     168,   166,     4,     4,   166,   166,   166,   166,   168,   252,
     251,   249,   319,   315,   357,   353,   381,   377,   200,   211,
     212,   213,   218,   219,   263,   311,   329,   331,   333,   335,
     345,   346,   373,   403,   405,   418,   420,   422,   442,   343,
     281,    89,    90,   200,   263,   347,   373,   403,   405,   418,
     420,   422,   450,   451,   452,   453,   454,   456,   448,   415,
     411,   295,   291,   166,   166,   166,   166,   166,   166,   304,
       4,     4,   461,     6,     3,   399,   395,     4,   141,   143,
     144,   200,   263,   403,   405,   526,   527,   528,   529,   531,
     524,   165,    34,    35,    36,    37,   255,   165,   165,   165,
     165,   165,     8,     8,     8,     8,     3,     8,   455,     4,
       8,     3,     8,     8,   165,   165,   165,     8,   196,   532,
       4,   530,     3,     8,   346,     4,   168,   452,     4,   166,
       4,   527,   165,     5,   165,     7,   533,   534,   535,     3,
       6,   142,   145,   146,   147,   536,   537,   538,   540,   541,
     542,   534,   539,     4,     4,     4,     3,     8,     4,   168,
     166,   166,   537,   165
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
     210,   210,   210,   210,   210,   210,   210,   210,   211,   212,
     213,   214,   216,   215,   217,   218,   219,   221,   220,   222,
     222,   223,   223,   223,   223,   223,   223,   223,   225,   224,
     227,   226,   229,   228,   230,   230,   232,   231,   233,   233,
     234,   236,   235,   238,   237,   239,   239,   240,   242,   241,
     244,   243,   246,   245,   247,   247,   248,   248,   250,   249,
     251,   251,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     254,   253,   255,   255,   255,   255,   257,   256,   259,   258,
     261,   260,   262,   264,   263,   265,   266,   267,   268,   269,
     270,   271,   273,   272,   275,   274,   276,   277,   279,   278,
     280,   280,   281,   281,   281,   281,   281,   282,   283,   284,
     285,   286,   288,   287,   289,   289,   290,   290,   292,   291,
     294,   293,   295,   295,   295,   296,   296,   298,   297,   300,
     299,   302,   301,   303,   303,   304,   304,   304,   304,   304,
     304,   305,   306,   307,   308,   309,   310,   312,   311,   313,
     313,   314,   314,   316,   315,   318,   317,   319,   319,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   322,   321,   324,   323,   326,   325,   328,
     327,   330,   329,   332,   331,   334,   333,   336,   335,   337,
     337,   337,   337,   338,   340,   339,   341,   341,   342,   342,
     344,   343,   345,   345,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   348,   347,   350,   349,   351,   351,   352,
     352,   354,   353,   356,   355,   357,   357,   358,   358,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   360,
     361,   362,   364,   363,   366,   365,   368,   367,   369,   371,
     370,   372,   374,   373,   375,   375,   376,   376,   378,   377,
     380,   379,   381,   381,   382,   382,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   384,   386,   385,   387,   388,
     389,   390,   392,   391,   393,   393,   394,   394,   396,   395,
     398,   397,   399,   399,   400,   400,   400,   400,   400,   400,
     400,   402,   401,   404,   403,   406,   405,   408,   407,   409,
     409,   410,   410,   412,   411,   414,   413,   415,   415,   416,
     416,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   417,   417,   417,   419,   418,   421,   420,
     423,   422,   425,   424,   427,   426,   429,   428,   431,   430,
     433,   432,   435,   434,   437,   436,   439,   438,   441,   440,
     443,   442,   444,   444,   446,   445,   447,   447,   449,   448,
     450,   450,   451,   451,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   453,   455,   454,   456,   457,
     459,   458,   460,   460,   461,   461,   461,   461,   461,   463,
     462,   465,   464,   467,   466,   469,   468,   471,   470,   472,
     472,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   474,
     476,   475,   478,   477,   479,   481,   480,   482,   483,   485,
     484,   486,   486,   488,   487,   489,   490,   492,   491,   493,
     493,   493,   493,   493,   495,   494,   497,   496,   499,   498,
     501,   500,   503,   502,   505,   504,   507,   506,   508,   506,
     510,   509,   511,   511,   512,   512,   514,   513,   516,   515,
     518,   517,   519,   519,   520,   522,   521,   523,   523,   525,
     524,   526,   526,   527,   527,   527,   527,   527,   527,   527,
     528,   530,   529,   532,   531,   533,   533,   535,   534,   536,
     536,   537,   537,   537,   537,   539,   538,   540,   541,   542
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     0,     4,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     1,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     0,     6,
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
     461,   462,   463,   464,   465,   466,   467,   468,   471,   476,
     481,   486,   491,   491,   499,   504,   509,   515,   515,   526,
     527,   530,   531,   532,   533,   534,   535,   536,   539,   539,
     548,   548,   558,   558,   565,   566,   569,   569,   576,   578,
     582,   588,   588,   600,   600,   610,   611,   613,   615,   615,
     633,   633,   645,   645,   655,   656,   659,   660,   663,   663,
     673,   674,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     697,   697,   704,   705,   706,   707,   710,   710,   718,   718,
     726,   726,   734,   739,   739,   747,   752,   757,   762,   767,
     772,   777,   782,   782,   790,   790,   798,   803,   808,   808,
     818,   819,   822,   823,   824,   825,   826,   829,   834,   839,
     844,   849,   854,   854,   864,   865,   868,   869,   872,   872,
     882,   882,   892,   893,   894,   897,   898,   901,   901,   909,
     909,   917,   917,   928,   929,   932,   933,   934,   935,   936,
     937,   940,   945,   950,   955,   960,   965,   973,   973,   986,
     987,   990,   991,   998,   998,  1024,  1024,  1035,  1036,  1040,
    1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,
    1061,  1062,  1063,  1066,  1066,  1074,  1074,  1082,  1082,  1090,
    1090,  1098,  1098,  1106,  1106,  1114,  1114,  1124,  1124,  1131,
    1132,  1133,  1134,  1137,  1144,  1144,  1155,  1156,  1160,  1161,
    1164,  1164,  1172,  1173,  1176,  1177,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,
    1192,  1193,  1194,  1201,  1201,  1214,  1214,  1223,  1224,  1227,
    1228,  1233,  1233,  1248,  1248,  1262,  1263,  1266,  1267,  1270,
    1271,  1272,  1273,  1274,  1275,  1276,  1277,  1278,  1279,  1282,
    1284,  1289,  1291,  1291,  1299,  1299,  1307,  1307,  1315,  1317,
    1317,  1325,  1334,  1334,  1346,  1347,  1352,  1353,  1358,  1358,
    1370,  1370,  1382,  1383,  1388,  1389,  1394,  1395,  1396,  1397,
    1398,  1399,  1400,  1401,  1402,  1405,  1407,  1407,  1415,  1417,
    1419,  1424,  1432,  1432,  1444,  1445,  1448,  1449,  1452,  1452,
    1462,  1462,  1472,  1473,  1476,  1477,  1478,  1479,  1480,  1481,
    1482,  1485,  1485,  1493,  1493,  1518,  1518,  1548,  1548,  1558,
    1559,  1562,  1563,  1566,  1566,  1575,  1575,  1584,  1585,  1588,
    1589,  1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,
    1602,  1603,  1604,  1605,  1606,  1607,  1610,  1610,  1618,  1618,
    1626,  1626,  1634,  1634,  1642,  1642,  1652,  1652,  1660,  1660,
    1668,  1668,  1676,  1676,  1684,  1684,  1692,  1692,  1700,  1700,
    1713,  1713,  1723,  1724,  1730,  1730,  1740,  1741,  1744,  1744,
    1754,  1755,  1758,  1759,  1762,  1763,  1764,  1765,  1766,  1767,
    1768,  1769,  1770,  1771,  1772,  1775,  1777,  1777,  1785,  1794,
    1801,  1801,  1811,  1812,  1815,  1816,  1817,  1818,  1819,  1822,
    1822,  1830,  1830,  1841,  1841,  1879,  1879,  1891,  1891,  1901,
    1902,  1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,
    1914,  1915,  1916,  1917,  1918,  1919,  1920,  1921,  1922,  1925,
    1930,  1930,  1938,  1938,  1946,  1951,  1951,  1959,  1964,  1969,
    1969,  1977,  1978,  1981,  1981,  1989,  1994,  1999,  1999,  2007,
    2010,  2013,  2016,  2019,  2025,  2025,  2033,  2033,  2041,  2041,
    2052,  2052,  2059,  2059,  2066,  2066,  2073,  2073,  2082,  2082,
    2093,  2093,  2103,  2104,  2108,  2109,  2112,  2112,  2127,  2127,
    2137,  2137,  2148,  2149,  2153,  2157,  2157,  2169,  2170,  2174,
    2174,  2182,  2183,  2186,  2187,  2188,  2189,  2190,  2191,  2192,
    2195,  2200,  2200,  2208,  2208,  2218,  2219,  2222,  2222,  2230,
    2231,  2234,  2235,  2236,  2237,  2240,  2240,  2248,  2253,  2258
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
#line 4968 "dhcp4_parser.cc" // lalr1.cc:1218
#line 2263 "dhcp4_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
