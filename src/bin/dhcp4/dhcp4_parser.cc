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
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 339: // hr_mode
      case 488: // ncr_protocol_value
      case 495: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 169: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 168: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 167: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 166: // "constant string"
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
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 339: // hr_mode
      case 488: // ncr_protocol_value
      case 495: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 169: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 168: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 167: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 166: // "constant string"
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
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 339: // hr_mode
      case 488: // ncr_protocol_value
      case 495: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 169: // "boolean"
        value.move< bool > (that.value);
        break;

      case 168: // "floating point"
        value.move< double > (that.value);
        break;

      case 167: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 166: // "constant string"
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
            case 166: // "constant string"

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 167: // "integer"

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 168: // "floating point"

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 169: // "boolean"

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 186: // value

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 190: // map_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 231: // socket_type

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 234: // outbound_interface_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 450 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 256: // db_type

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 457 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 339: // hr_mode

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 464 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 488: // ncr_protocol_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 471 "dhcp4_parser.cc" // lalr1.cc:672
        break;

      case 495: // replace_client_name_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:672
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
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 339: // hr_mode
      case 488: // ncr_protocol_value
      case 495: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 169: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 168: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 167: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 166: // "constant string"
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
#line 255 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 256 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 257 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP4; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 258 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 259 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET4; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 260 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 261 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 774 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 262 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP4; }
#line 780 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 263 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 786 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 264 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 792 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 265 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 798 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 266 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 804 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 267 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 810 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 268 "dhcp4_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 816 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 276 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 822 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 31:
#line 277 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 278 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 279 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 280 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 281 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 852 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 282 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 285 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 867 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 290 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 295 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 301 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 894 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 43:
#line 308 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 903 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 44:
#line 312 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 913 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 319 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 922 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 322 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 930 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 49:
#line 330 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 939 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 50:
#line 334 "dhcp4_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 341 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 956 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 343 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 965 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 55:
#line 352 "dhcp4_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 974 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 56:
#line 356 "dhcp4_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 983 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 367 "dhcp4_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 994 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 377 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1005 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 382 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 406 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 413 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 70:
#line 421 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 71:
#line 425 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 108:
#line 472 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1069 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 477 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1078 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 482 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1087 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 487 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1096 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 492 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 494 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 500 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1123 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 505 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 510 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1141 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 516 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 118:
#line 521 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 540 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 544 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 549 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1192 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 554 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1201 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 559 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1209 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 561 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 134:
#line 566 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1224 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 135:
#line 567 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1230 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 136:
#line 570 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 137:
#line 572 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 577 "dhcp4_parser.yy" // lalr1.cc:907
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 579 "dhcp4_parser.yy" // lalr1.cc:907
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1263 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 140:
#line 583 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 141:
#line 589 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 142:
#line 594 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 143:
#line 601 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1305 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 144:
#line 606 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 616 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 618 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 634 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1353 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 151:
#line 639 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 152:
#line 646 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 153:
#line 651 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 158:
#line 664 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1394 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 159:
#line 668 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 699 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1412 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 701 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1421 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 706 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1427 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 707 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1433 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 708 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1439 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 709 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1445 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 712 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 714 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1463 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 720 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1471 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 722 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1481 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 191:
#line 728 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 192:
#line 730 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 736 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 741 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 195:
#line 743 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 749 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1535 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 754 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 759 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 764 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 769 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1571 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 774 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 779 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1589 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 784 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 786 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 792 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 206:
#line 794 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 207:
#line 800 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 208:
#line 805 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1643 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 209:
#line 810 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 210:
#line 815 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 211:
#line 820 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 219:
#line 836 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 841 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 846 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 851 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 856 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1717 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 224:
#line 861 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 225:
#line 866 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 879 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 883 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 232:
#line 889 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 233:
#line 893 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1777 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 239:
#line 908 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 240:
#line 910 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1795 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 241:
#line 916 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 242:
#line 918 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 243:
#line 924 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 244:
#line 929 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 253:
#line 947 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 254:
#line 952 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 255:
#line 957 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 962 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 257:
#line 967 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1878 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 258:
#line 972 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 259:
#line 980 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 260:
#line 985 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 265:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1917 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 266:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 1943 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 267:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 268:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 295:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2007 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2017 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 301:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 302:
#line 1099 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2035 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 303:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2043 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 304:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2053 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 305:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2061 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 306:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2071 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 307:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 308:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 309:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 310:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2108 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 311:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2114 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 312:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2120 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 313:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2126 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 314:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2132 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 315:
#line 1144 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 316:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 317:
#line 1156 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 322:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 323:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 345:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 346:
#line 1213 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2199 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 347:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 348:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 353:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 354:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2238 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 355:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 356:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 372:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2269 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 376:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2295 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 377:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 378:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 379:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 381:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 382:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 383:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 384:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 385:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 390:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 391:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 392:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 393:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 408:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 409:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1426 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2435 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 413:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 414:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 415:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 420:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 421:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2484 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 422:
#line 1469 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2494 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 423:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2504 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 433:
#line 1492 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2512 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 434:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2522 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 435:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 2557 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 437:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 438:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 2594 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 439:
#line 1555 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2605 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 440:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2614 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 445:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2624 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 446:
#line 1577 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2633 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 447:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2643 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 448:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2652 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 468:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2660 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 469:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 470:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 471:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2688 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 472:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 473:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2706 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 474:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 475:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2724 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 476:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 477:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 482:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2788 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 483:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2798 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2816 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2824 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 491:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 492:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2883 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 493:
#line 1725 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2892 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 496:
#line 1737 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2903 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 497:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2912 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 501:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2932 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 518:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 519:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 520:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 521:
#line 1801 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 522:
#line 1808 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2979 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 523:
#line 1813 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 531:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 532:
#line 1831 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 533:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1848 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:907
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
#line 3070 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3081 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 538:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3092 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1898 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3102 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1902 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3112 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 562:
#line 1937 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 563:
#line 1939 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3139 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 564:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3147 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 565:
#line 1947 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3157 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 566:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3166 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 567:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3174 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 568:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3184 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 569:
#line 1966 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3193 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 570:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3202 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 571:
#line 1976 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3210 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 572:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3219 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 573:
#line 1984 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3225 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 574:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3231 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3239 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1990 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 578:
#line 2001 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3267 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3284 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 581:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3292 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 2017 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3300 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 2020 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3308 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 584:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3316 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 585:
#line 2026 "dhcp4_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3325 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 586:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3333 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 587:
#line 2034 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3343 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 588:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3351 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3361 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3369 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2050 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3379 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2059 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3387 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3396 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3404 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3413 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3421 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2075 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3430 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2080 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3441 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2085 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3451 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3461 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 601:
#line 2095 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3470 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2109 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3481 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2114 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2124 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3501 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2129 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3510 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2134 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3520 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2138 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3528 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2154 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3539 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2159 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3548 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2171 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3558 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2175 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3566 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2192 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3575 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2197 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3583 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2199 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3593 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2205 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3604 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2210 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3613 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2219 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3623 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2223 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3631 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 644:
#line 2237 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 645:
#line 2239 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3649 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 646:
#line 2245 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3658 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 647:
#line 2250 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3667 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 648:
#line 2255 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3676 "dhcp4_parser.cc" // lalr1.cc:907
    break;


#line 3680 "dhcp4_parser.cc" // lalr1.cc:907
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


  const short Dhcp4Parser::yypact_ninf_ = -800;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     318,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,    43,    35,    38,    58,    67,
      97,    99,   107,   109,   117,   131,   135,   139,   149,   158,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,    35,   -12,
      17,    71,    32,   153,    55,   183,    77,    40,   391,   -45,
     453,    28,   164,  -800,   214,   194,   225,   240,   255,  -800,
    -800,  -800,  -800,  -800,   268,  -800,    61,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,   272,   279,   281,  -800,
    -800,  -800,  -800,  -800,  -800,   285,   295,   306,   317,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,   322,  -800,  -800,  -800,  -800,    68,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,   336,  -800,    72,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,   337,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,    86,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,   112,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,   327,   339,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,   342,  -800,  -800,
     341,  -800,  -800,  -800,   343,  -800,  -800,   350,   357,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,   359,   360,  -800,  -800,  -800,  -800,   363,   362,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,   133,  -800,  -800,  -800,   364,  -800,  -800,   369,
    -800,   371,   375,  -800,  -800,   382,   383,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,   147,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,   188,  -800,  -800,  -800,   191,  -800,  -800,  -800,
      35,    35,  -800,   224,   387,   389,   392,   395,   396,  -800,
      17,  -800,   397,   398,   403,   226,   243,   244,   405,   410,
     411,   414,   415,   418,   259,   260,   270,   287,   430,   432,
     458,   459,   460,   462,   463,   480,   481,   482,   483,   484,
     485,   323,   487,   488,   489,    71,  -800,   490,   491,   492,
     328,    32,  -800,   494,   495,   496,   497,   498,   499,   338,
     500,   504,   505,   153,  -800,   506,    55,  -800,   507,   509,
     510,   511,   512,   513,   514,   515,  -800,   183,  -800,   516,
     517,   355,   519,   520,   522,   358,  -800,    40,   524,   365,
     366,  -800,   391,   528,   529,   -14,  -800,   367,   533,   535,
     374,   538,   377,   378,   542,   543,   379,   380,   546,   548,
     550,   551,   453,  -800,   552,    28,  -800,   554,   164,  -800,
    -800,  -800,   555,   553,   556,    35,    35,    35,  -800,   557,
     558,   560,  -800,  -800,  -800,   402,   404,   419,   579,   580,
     583,  -800,  -800,  -800,  -800,   423,   585,   588,   589,   590,
     591,   431,   269,   594,   595,   596,   597,   598,  -800,   599,
     591,   600,  -800,   603,    62,   103,  -800,  -800,   437,   438,
     443,   605,   445,   446,  -800,   603,   447,   607,  -800,   449,
    -800,   603,   450,   451,   452,   454,   455,   456,   457,  -800,
     461,   464,  -800,   465,   466,   467,  -800,  -800,   468,  -800,
    -800,  -800,   469,    35,  -800,  -800,   470,   471,  -800,   472,
    -800,  -800,    11,   428,  -800,  -800,    26,   473,   474,   475,
    -800,   619,  -800,   620,  -800,    35,    71,    28,  -800,  -800,
    -800,   164,    32,   539,  -800,  -800,  -800,   400,   400,   621,
    -800,   622,   635,   636,   637,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,    76,   638,   639,   640,   115,   -29,  -800,
     453,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,   641,  -800,  -800,  -800,  -800,   207,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,   642,   621,  -800,   197,   233,   235,   236,  -800,   246,
    -800,  -800,  -800,  -800,  -800,  -800,   592,   646,   647,   648,
     649,  -800,  -800,   650,   651,   652,   653,   654,   655,  -800,
     254,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
     265,  -800,   656,   623,  -800,  -800,   657,   658,  -800,  -800,
     659,   661,  -800,  -800,   660,   664,  -800,  -800,   662,   666,
    -800,  -800,  -800,  -800,  -800,  -800,   187,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,   253,  -800,  -800,   665,   667,  -800,
    -800,   668,   669,  -800,   671,   672,   673,   674,   675,   676,
     266,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,   267,  -800,  -800,  -800,   288,   518,  -800,
     677,   670,  -800,  -800,  -800,  -800,   678,  -800,   292,  -800,
     679,  -800,  -800,  -800,  -800,   683,   539,  -800,   684,   685,
     686,   687,   493,   523,   526,   525,   530,   691,   692,   531,
     532,   534,   536,   537,   540,   400,  -800,  -800,   400,  -800,
     621,   153,  -800,   622,    40,  -800,   635,   391,  -800,   636,
     238,  -800,   637,    76,  -800,   223,   638,  -800,   183,  -800,
     639,   -45,  -800,   640,   541,   544,   545,   547,   549,   559,
     115,  -800,   696,   698,   -29,  -800,  -800,  -800,   699,   701,
      55,  -800,   641,   705,  -800,    74,   642,  -800,  -800,   561,
    -800,   347,   562,   563,   564,  -800,  -800,  -800,  -800,  -800,
     565,   566,  -800,  -800,  -800,  -800,  -800,  -800,  -800,   303,
    -800,   304,  -800,   702,  -800,   707,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,   314,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,   709,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,   710,   714,  -800,  -800,  -800,  -800,  -800,   711,  -800,
     320,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,   567,
     568,  -800,  -800,   569,   321,  -800,   603,  -800,   716,  -800,
    -800,  -800,  -800,  -800,   329,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,   238,  -800,   717,   570,  -800,
     223,  -800,  -800,  -800,  -800,  -800,  -800,  -800,   718,   571,
     719,    74,  -800,  -800,   574,  -800,  -800,   720,  -800,   575,
    -800,  -800,   729,  -800,  -800,   330,  -800,   -85,   729,  -800,
    -800,   733,   738,   739,   331,  -800,  -800,  -800,  -800,  -800,
    -800,   740,   576,   581,   582,   -85,  -800,   584,  -800,  -800,
    -800,  -800,  -800
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   128,     9,   267,    11,
     422,    13,   447,    15,   347,    17,   355,    19,   392,    21,
     232,    23,   539,    25,   609,    27,   600,    29,    47,    41,
       0,     0,     0,     0,     0,   449,     0,   357,   394,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     607,   592,   594,   596,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   598,   117,   143,     0,     0,     0,   468,
     470,   472,   141,   150,   152,     0,     0,     0,     0,   112,
     259,   345,   384,   316,   435,   437,   309,   210,   496,   439,
     224,   243,     0,   522,   535,   537,   107,     0,    72,    74,
      75,    76,    77,   105,    94,    95,    96,    80,    81,   102,
      82,    83,    84,    88,    89,    78,   106,    79,    86,    87,
     100,   101,   103,    97,    98,    99,    85,    90,    91,    92,
      93,   104,   130,   132,   136,     0,   127,     0,   119,   121,
     122,   123,   124,   125,   126,   297,   299,   301,   414,   295,
     303,     0,   307,   305,   492,   294,   271,   272,   273,   284,
     285,     0,   269,   276,   289,   290,   291,   277,   279,   280,
     282,   278,   274,   275,   292,   293,   281,   286,   287,   288,
     283,   433,   432,   428,   429,   427,     0,   424,   426,   430,
     431,   490,   478,   480,   484,   482,   488,   486,   474,   467,
     461,   465,   466,     0,   450,   451,   462,   463,   464,   458,
     453,   459,   455,   456,   457,   460,   454,     0,   374,   194,
       0,   378,   376,   381,     0,   370,   371,     0,   358,   359,
     361,   373,   362,   363,   364,   380,   365,   366,   367,   368,
     369,   408,     0,     0,   406,   407,   410,   411,     0,   395,
     396,   398,   399,   400,   401,   402,   403,   404,   405,   239,
     241,   236,     0,   234,   237,   238,     0,   562,   564,     0,
     567,     0,     0,   571,   575,     0,     0,   579,   586,   588,
     590,   560,   558,   559,     0,   541,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   614,     0,   611,   613,   605,     0,   602,   604,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   268,     0,     0,   423,     0,     0,
       0,     0,     0,     0,     0,     0,   448,     0,   348,     0,
       0,     0,     0,     0,     0,     0,   356,     0,     0,     0,
       0,   393,     0,     0,     0,     0,   233,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   540,     0,     0,   610,     0,     0,   601,
      50,    43,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,   114,   115,   116,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   521,     0,
       0,     0,    73,     0,     0,     0,   140,   120,     0,     0,
       0,     0,     0,     0,   315,     0,     0,     0,   270,     0,
     425,     0,     0,     0,     0,     0,     0,     0,     0,   452,
       0,     0,   372,     0,     0,     0,   383,   360,     0,   412,
     413,   397,     0,     0,   235,   561,     0,     0,   566,     0,
     569,   570,     0,     0,   577,   578,     0,     0,     0,     0,
     542,     0,   612,     0,   603,     0,     0,     0,   593,   595,
     597,     0,     0,     0,   469,   471,   473,     0,     0,   154,
     113,   261,   349,   386,   318,    40,   436,   438,   311,   312,
     313,   314,   310,     0,     0,   441,   226,     0,     0,   536,
       0,    51,   131,   134,   135,   133,   138,   139,   137,   298,
     300,   302,   416,   296,   304,   308,   306,     0,   434,   491,
     479,   481,   485,   483,   489,   487,   475,   375,   195,   379,
     377,   382,   409,   240,   242,   563,   565,   568,   573,   574,
     572,   576,   581,   582,   583,   584,   585,   580,   587,   589,
     591,     0,   154,    44,     0,     0,     0,     0,   148,     0,
     145,   147,   181,   187,   189,   191,     0,     0,     0,     0,
       0,   203,   205,     0,     0,     0,     0,     0,     0,   180,
       0,   160,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   175,   176,   177,   172,   178,   173,   174,   179,
       0,   158,     0,   155,   156,   265,     0,   262,   263,   353,
       0,   350,   351,   390,     0,   387,   388,   322,     0,   319,
     320,   219,   220,   221,   222,   223,     0,   212,   214,   215,
     216,   217,   218,   500,     0,   498,   445,     0,   442,   443,
     230,     0,   227,   228,     0,     0,     0,     0,     0,     0,
       0,   245,   247,   248,   249,   250,   251,   252,   531,   533,
     530,   528,   529,     0,   524,   526,   527,     0,    53,   420,
       0,   417,   418,   476,   494,   495,     0,   618,     0,   616,
       0,    69,   608,   599,   118,     0,     0,   144,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   142,   151,     0,   153,
       0,     0,   260,     0,   357,   346,     0,   394,   385,     0,
       0,   317,     0,     0,   211,   502,     0,   497,   449,   440,
       0,     0,   225,     0,     0,     0,     0,     0,     0,     0,
       0,   244,     0,     0,     0,   523,   538,    55,     0,    54,
       0,   415,     0,     0,   493,     0,     0,   615,   606,     0,
     146,     0,     0,     0,     0,   193,   196,   197,   198,   199,
       0,     0,   207,   208,   200,   201,   202,   209,   161,     0,
     157,     0,   264,     0,   352,     0,   389,   344,   341,   329,
     330,   332,   333,   326,   327,   328,   339,   340,   338,     0,
     324,   331,   342,   343,   334,   335,   336,   337,   321,   213,
     518,     0,   516,   517,   509,   510,   514,   515,   511,   512,
     513,     0,   503,   504,   506,   507,   508,   499,     0,   444,
       0,   229,   253,   254,   255,   256,   257,   258,   246,     0,
       0,   525,    52,     0,     0,   419,     0,   632,     0,   630,
     628,   622,   626,   627,     0,   620,   624,   625,   623,   617,
     149,   183,   184,   185,   186,   182,   188,   190,   192,   204,
     206,   159,   266,   354,   391,     0,   323,     0,     0,   501,
       0,   446,   231,   532,   534,    56,   421,   477,     0,     0,
       0,     0,   619,   325,     0,   520,   505,     0,   629,     0,
     621,   519,     0,   631,   636,     0,   634,     0,     0,   633,
     644,     0,     0,     0,     0,   638,   640,   641,   642,   643,
     635,     0,     0,     0,     0,     0,   637,     0,   646,   647,
     648,   639,   645
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,   -46,  -800,  -443,  -800,
     171,  -800,  -800,  -800,  -800,  -800,  -800,  -501,  -800,  -800,
    -800,   -70,  -800,  -800,  -800,   386,  -800,  -800,  -800,  -800,
     106,   352,   -47,   -44,     4,  -800,  -800,  -800,  -800,    12,
      15,  -800,  -800,   142,   351,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,   -43,  -800,  -800,  -800,  -800,  -800,  -800,    93,  -800,
     -54,  -800,  -563,   -59,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,   -26,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,   -75,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,   -74,  -800,  -800,  -800,   -65,   334,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,   -61,  -800,  -800,  -800,
    -800,  -800,  -800,  -799,  -800,  -800,  -800,   -36,  -800,  -800,
    -800,   -41,   381,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -798,  -800,   -68,  -800,   -55,  -800,    19,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,   -32,  -800,  -800,  -192,   -63,
    -800,  -800,  -800,  -800,  -800,   -20,  -800,  -800,  -800,   -17,
    -800,   373,  -800,   -66,  -800,  -800,  -800,  -800,  -800,   -64,
    -800,  -800,  -800,  -800,  -800,   -19,  -800,  -800,  -800,   -16,
    -800,  -800,  -800,   -15,  -800,   388,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,   -42,  -800,  -800,
    -800,   -38,   401,  -800,  -800,   -57,  -800,   -39,  -800,   -62,
    -800,  -800,  -800,     7,  -800,  -800,  -800,    -1,  -800,   417,
      -7,  -800,    -3,  -800,     8,  -800,   221,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -793,  -800,  -800,  -800,  -800,  -800,
      14,  -800,  -800,  -800,  -166,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,    -2,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,   241,   393,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,  -800,
    -800,  -800,   273,   385,  -800,  -800,  -800,  -800,  -800,  -800,
     280,   394,  -800,  -800,  -800,   -10,  -800,  -800,  -143,  -800,
    -800,  -800,  -800,  -800,  -800,  -158,  -800,  -800,  -174,  -800,
    -800,  -800,  -800,  -800
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     596,    87,    88,    41,    68,    84,    85,   612,   778,   858,
     859,   689,    43,    70,    96,    97,    98,   354,    45,    71,
     137,   138,   139,   140,   141,   142,   143,   378,   144,   145,
     146,   147,   363,   177,   178,    47,    72,   179,   397,   180,
     398,   615,   181,   399,   618,   182,   148,   371,   149,   364,
     669,   670,   671,   795,   150,   372,   151,   373,   712,   713,
     714,   818,   690,   691,   692,   798,   975,   693,   799,   694,
     800,   695,   801,   696,   697,   430,   698,   699,   700,   701,
     702,   703,   704,   705,   807,   706,   808,   707,   708,   709,
     152,   386,   736,   737,   738,   739,   740,   741,   742,   153,
     389,   751,   752,   753,   841,    61,    79,   302,   303,   304,
     443,   305,   444,   154,   390,   760,   761,   762,   763,   764,
     765,   766,   767,   155,   379,   716,   717,   718,   821,    49,
      73,   201,   202,   203,   407,   204,   403,   205,   404,   206,
     405,   207,   408,   208,   411,   209,   410,   156,   385,   602,
     211,   157,   382,   728,   729,   730,   830,   909,   910,   158,
     380,    55,    76,   720,   721,   722,   824,    57,    77,   267,
     268,   269,   270,   271,   272,   273,   429,   274,   433,   275,
     432,   276,   277,   434,   278,   159,   381,   724,   725,   726,
     827,    59,    78,   288,   289,   290,   291,   292,   438,   293,
     294,   295,   296,   213,   406,   780,   781,   782,   860,    51,
      74,   226,   227,   228,   415,   160,   383,   161,   384,   162,
     388,   747,   748,   749,   838,    53,    75,   243,   244,   245,
     163,   368,   164,   369,   165,   370,   249,   425,   785,   863,
     250,   419,   251,   420,   252,   422,   253,   421,   254,   424,
     255,   423,   256,   418,   220,   412,   786,   166,   387,   744,
     745,   835,   931,   932,   933,   934,   935,   987,   936,   167,
     168,   392,   773,   774,   775,   852,   776,   853,   169,   393,
     170,   394,    63,    80,   324,   325,   326,   327,   448,   328,
     449,   329,   330,   451,   331,   332,   333,   454,   650,   334,
     455,   335,   336,   337,   458,   657,   338,   459,   339,   460,
     340,   461,    99,   356,   100,   357,   101,   358,   171,   362,
      67,    82,   346,   347,   348,   467,   102,   355,    65,    81,
     342,   343,   344,   464,   788,   789,   865,   964,   965,   966,
     967,  1000,   968,   998,  1015,  1016,  1017,  1024,  1025,  1026,
    1031,  1027,  1028,  1029
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   136,   176,   195,   222,   239,   223,   265,   284,   301,
     321,   216,   286,   257,   287,   183,   214,   229,   241,   224,
     279,   297,    83,   322,   625,   710,   196,    89,   648,   197,
     629,   904,   905,   184,   215,   230,   242,   917,   280,   298,
      31,   323,    32,    30,    33,    42,   172,   173,   124,   125,
     174,   266,   285,   175,   212,   225,   240,   595,  1020,   299,
     300,  1021,  1022,  1023,   360,    44,   217,   595,   246,   361,
     218,   395,   247,   258,    46,   401,   396,   198,   613,   614,
     402,   219,   103,   248,   104,   199,   768,   769,   200,   413,
     299,   300,   210,   105,   414,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    48,   259,    50,   260,   261,   124,
     125,   262,   263,   264,    52,   416,    54,   124,   125,   122,
     417,    94,   616,   617,    56,   115,   116,   117,   118,   119,
     120,   221,   124,   125,   121,   122,   445,    94,    58,   259,
     121,   446,    60,   649,   192,   123,    62,   193,   124,   125,
     462,   124,   125,   126,    86,   463,    64,    90,   127,   128,
     652,   653,   654,   655,   129,    66,    91,    92,    93,   341,
     731,   732,   733,   734,   130,   735,   345,   131,   107,   108,
     109,   110,   111,    94,   132,   133,   904,   905,   134,   135,
     833,   465,   917,   834,   468,   656,   466,   350,    94,   469,
     395,    34,    35,    36,    37,   791,    94,   115,   116,   117,
     109,   110,   111,   185,   186,   187,   957,   122,   958,   959,
     349,    94,   754,   755,   756,   757,   758,   759,   188,   351,
     124,   125,   189,   190,   191,   126,   465,    94,   468,   401,
      94,   792,   192,   793,   794,   193,   129,   122,   352,   796,
     109,   110,   111,   194,   797,   889,   836,   815,   353,   837,
     124,   125,   816,   107,   108,   109,   110,   111,   815,   850,
     854,   231,   359,   817,   851,   855,   365,   232,   233,   234,
     235,   236,   237,   366,   238,   367,   121,   122,   259,   374,
      95,   462,   115,   116,   117,   866,   856,   120,   867,   375,
     124,   125,   122,   259,   470,   471,   815,   413,   238,   783,
     376,   981,   982,   920,   921,   124,   125,   985,   190,    94,
     126,   377,   986,   445,   416,   136,   391,   192,   992,   996,
     193,   176,  1001,  1018,  1035,   426,  1019,  1002,   194,  1036,
     400,   409,   427,   195,   183,   431,   222,   435,   223,    94,
     428,   216,   598,   599,   600,   601,   214,   239,   436,   229,
     437,   224,   184,   439,   440,   442,   196,   265,   447,   197,
     241,   441,   284,   450,   215,   452,   286,   230,   287,   453,
     279,   971,   972,   973,   974,   297,   456,   457,   242,    94,
     472,   473,   321,   474,   212,   482,   475,   225,   280,   476,
     477,   479,   480,   298,    94,   322,   217,   481,   240,   485,
     218,   266,   483,   484,   486,   487,   285,   198,   488,   489,
     246,   219,   490,   323,   247,   199,   491,   492,   200,   578,
     579,   580,   210,   672,   495,   248,   496,   493,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   494,   997,   259,   281,   260,   261,
     282,   283,   497,   498,   499,   259,   500,   501,   124,   125,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   513,   514,   515,   516,   518,   519,
     520,   521,   522,   523,   525,   524,   136,   644,   526,   527,
     529,   531,   176,   532,   533,   534,   535,   536,   537,   538,
     540,   541,   542,   543,   544,   183,   545,   546,   548,   663,
     124,   125,   552,   553,   549,   550,   555,   556,   770,   557,
     321,   558,   559,   184,   560,   561,   562,   563,   564,   565,
     566,   771,   567,   322,   568,   569,   571,    94,   573,   575,
     576,   651,   668,   577,   581,   582,    94,   583,   584,   772,
     585,   323,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   586,   587,   588,   589,   590,
     591,   319,   320,   592,   593,   594,   802,   597,    32,   603,
     604,   605,   606,   619,   620,   607,   608,   610,   611,   621,
     622,   623,   624,   626,   627,   628,   630,   631,   632,    94,
     633,   634,   635,   636,   661,   662,   820,   637,   711,   715,
     638,   639,   640,   641,   642,   643,   645,   646,   647,   658,
     659,   660,   719,   723,   727,   743,   746,   750,   779,   787,
     803,   804,   805,   806,   809,   810,   811,   812,   813,   814,
     875,   823,   819,   822,   826,   825,   828,   829,   831,   832,
     840,   839,   843,   862,   842,   844,   845,   846,   847,   848,
     849,   609,   664,   861,   857,   868,   864,   869,   871,   872,
     873,   874,   876,   877,   878,   880,   881,   879,   882,   883,
     949,   884,   950,   885,   953,   952,   886,   887,   942,   956,
     983,   943,   944,   988,   945,   984,   946,   990,   989,   991,
     999,  1004,  1007,  1009,   667,  1012,   947,   970,   976,   977,
     978,   979,   980,   993,   994,   995,  1014,  1032,  1008,  1005,
    1011,  1013,  1033,  1034,  1037,  1038,   478,   512,  1039,  1040,
    1042,   195,   517,   870,   265,   790,   888,   284,   919,   216,
     897,   286,   906,   287,   214,   922,   890,   279,   239,   941,
     297,   301,   924,   912,   196,   907,   940,   197,   926,   554,
     891,   241,   215,   898,   770,   280,   899,   892,   298,   948,
     222,   913,   223,  1003,   528,   960,   927,   771,   266,   242,
     918,   285,   212,   229,   903,   224,   894,   893,   962,   923,
     547,   911,   895,   896,   217,   772,   925,   530,   218,   240,
     955,   230,   954,   914,  1006,   198,   963,   915,   928,   219,
     551,   246,   929,   199,   900,   247,   200,   938,   916,   961,
     210,   225,   901,   930,   539,   902,   248,   939,   784,   908,
     937,   777,   951,   574,   666,   570,   969,   665,  1010,   572,
    1030,  1041,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   897,     0,   906,     0,     0,
     922,     0,     0,     0,     0,     0,     0,   924,   912,     0,
     907,   960,     0,   926,     0,     0,     0,     0,   898,     0,
       0,   899,     0,     0,   962,     0,   913,     0,     0,     0,
       0,   927,     0,     0,     0,     0,     0,     0,     0,   903,
       0,     0,   963,     0,   923,     0,   911,     0,     0,     0,
       0,   925,     0,     0,     0,   961,     0,     0,   914,     0,
       0,     0,   915,   928,     0,     0,     0,   929,     0,   900,
       0,     0,     0,   916,     0,     0,     0,   901,   930,     0,
     902,     0,     0,     0,   908
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,    74,
      77,    78,    68,    80,   525,   588,    73,    10,    17,    73,
     531,   830,   830,    72,    73,    74,    75,   830,    77,    78,
       5,    80,     7,     0,     9,     7,    14,    15,    77,    78,
      18,    77,    78,    21,    73,    74,    75,   500,   143,   104,
     105,   146,   147,   148,     3,     7,    73,   510,    75,     8,
      73,     3,    75,    33,     7,     3,     8,    73,    16,    17,
       8,    73,    11,    75,    13,    73,   115,   116,    73,     3,
     104,   105,    73,    22,     8,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     7,    65,     7,    67,    68,    77,
      78,    71,    72,    73,     7,     3,     7,    77,    78,    64,
       8,   166,    19,    20,     7,    54,    55,    56,    57,    58,
      59,    76,    77,    78,    63,    64,     3,   166,     7,    65,
      63,     8,     7,   132,    89,    74,     7,    92,    77,    78,
       3,    77,    78,    82,   166,     8,     7,   140,    87,    88,
     134,   135,   136,   137,    93,     7,   149,   150,   151,   141,
      94,    95,    96,    97,   103,    99,    12,   106,    25,    26,
      27,    28,    29,   166,   113,   114,   985,   985,   117,   118,
       3,     3,   985,     6,     3,   169,     8,     3,   166,     8,
       3,   166,   167,   168,   169,     8,   166,    54,    55,    56,
      27,    28,    29,    60,    61,    62,   142,    64,   144,   145,
       6,   166,   107,   108,   109,   110,   111,   112,    75,     4,
      77,    78,    79,    80,    81,    82,     3,   166,     3,     3,
     166,     8,    89,     8,     8,    92,    93,    64,     8,     3,
      27,    28,    29,   100,     8,   818,     3,     3,     3,     6,
      77,    78,     8,    25,    26,    27,    28,    29,     3,     3,
       3,    88,     4,     8,     8,     8,     4,    94,    95,    96,
      97,    98,    99,     4,   101,     4,    63,    64,    65,     4,
     360,     3,    54,    55,    56,     3,     8,    59,     6,     4,
      77,    78,    64,    65,   350,   351,     3,     3,   101,   102,
       4,     8,     8,    90,    91,    77,    78,     3,    80,   166,
      82,     4,     8,     3,     3,   395,     4,    89,     8,     8,
      92,   401,     3,     3,     3,     8,     6,     8,   100,     8,
       4,     4,     3,   413,   401,     4,   416,     4,   416,   166,
       8,   413,    83,    84,    85,    86,   413,   427,     8,   416,
       3,   416,   401,     4,     4,     3,   413,   437,     4,   413,
     427,     8,   442,     4,   413,     4,   442,   416,   442,     4,
     437,    34,    35,    36,    37,   442,     4,     4,   427,   166,
     166,     4,   462,     4,   413,   169,     4,   416,   437,     4,
       4,     4,     4,   442,   166,   462,   413,     4,   427,     4,
     413,   437,   169,   169,     4,     4,   442,   413,     4,     4,
     427,   413,     4,   462,   427,   413,   167,   167,   413,   475,
     476,   477,   413,    33,     4,   427,     4,   167,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   167,   956,    65,    66,    67,    68,
      69,    70,     4,     4,     4,    65,     4,     4,    77,    78,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,     4,     4,     4,     4,     4,     4,
     167,     4,     4,     4,     4,     4,     4,   169,     4,     4,
       4,     4,     4,     4,     4,   167,   576,   553,     4,     4,
       4,     4,   582,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   167,     4,     4,   582,     4,   169,     4,   575,
      77,    78,     4,     4,   169,   169,   169,     4,   608,     4,
     610,   167,     4,   582,   167,   167,     4,     4,   169,   169,
       4,   608,     4,   610,     4,     4,     4,   166,     4,     4,
       7,   133,    23,     7,     7,     7,   166,     7,   166,   608,
     166,   610,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   166,     7,     7,     5,   166,
       5,   138,   139,     5,     5,     5,     4,   166,     7,     5,
       5,     5,     5,   166,   166,     7,     7,     7,     5,   166,
       5,   166,   166,   166,     7,   166,   166,   166,   166,   166,
     166,   166,   166,   166,     5,     5,     3,   166,     7,     7,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,     7,     7,     7,     7,     7,     7,     7,     7,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     167,     3,     6,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,   510,   576,     6,   166,     6,     8,     4,     4,     4,
       4,     4,   169,   167,   169,     4,     4,   167,   167,   167,
       4,   167,     4,   167,     3,     6,   169,   167,   167,     4,
       8,   167,   167,     4,   167,     8,   167,     3,     8,     8,
       4,     4,     4,     4,   582,     5,   167,   166,   166,   166,
     166,   166,   166,   166,   166,   166,     7,     4,   167,   169,
     166,   166,     4,     4,     4,   169,   360,   395,   167,   167,
     166,   821,   401,   796,   824,   662,   815,   827,   833,   821,
     830,   827,   830,   827,   821,   835,   820,   824,   838,   843,
     827,   841,   835,   830,   821,   830,   841,   821,   835,   445,
     821,   838,   821,   830,   854,   824,   830,   823,   827,   850,
     860,   830,   860,   985,   413,   865,   835,   854,   824,   838,
     832,   827,   821,   860,   830,   860,   826,   824,   865,   835,
     437,   830,   827,   829,   821,   854,   835,   416,   821,   838,
     862,   860,   860,   830,   990,   821,   865,   830,   835,   821,
     442,   838,   835,   821,   830,   838,   821,   838,   830,   865,
     821,   860,   830,   835,   427,   830,   838,   840,   627,   830,
     836,   610,   854,   468,   581,   462,   866,   577,  1001,   465,
    1018,  1035,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   985,    -1,   985,    -1,    -1,
     990,    -1,    -1,    -1,    -1,    -1,    -1,   990,   985,    -1,
     985,  1001,    -1,   990,    -1,    -1,    -1,    -1,   985,    -1,
      -1,   985,    -1,    -1,  1001,    -1,   985,    -1,    -1,    -1,
      -1,   990,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   985,
      -1,    -1,  1001,    -1,   990,    -1,   985,    -1,    -1,    -1,
      -1,   990,    -1,    -1,    -1,  1001,    -1,    -1,   985,    -1,
      -1,    -1,   985,   990,    -1,    -1,    -1,   990,    -1,   985,
      -1,    -1,    -1,   985,    -1,    -1,    -1,   985,   990,    -1,
     985,    -1,    -1,    -1,   985
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     5,     7,     9,   166,   167,   168,   169,   186,   187,
     188,   193,     7,   202,     7,   208,     7,   225,     7,   319,
       7,   399,     7,   415,     7,   351,     7,   357,     7,   381,
       7,   295,     7,   472,     7,   518,     7,   510,   194,   189,
     203,   209,   226,   320,   400,   416,   352,   358,   382,   296,
     473,   519,   511,   186,   195,   196,   166,   191,   192,    10,
     140,   149,   150,   151,   166,   201,   204,   205,   206,   502,
     504,   506,   516,    11,    13,    22,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    54,    55,    56,    57,    58,
      59,    63,    64,    74,    77,    78,    82,    87,    88,    93,
     103,   106,   113,   114,   117,   118,   201,   210,   211,   212,
     213,   214,   215,   216,   218,   219,   220,   221,   236,   238,
     244,   246,   280,   289,   303,   313,   337,   341,   349,   375,
     405,   407,   409,   420,   422,   424,   447,   459,   460,   468,
     470,   508,    14,    15,    18,    21,   201,   223,   224,   227,
     229,   232,   235,   405,   407,    60,    61,    62,    75,    79,
      80,    81,    89,    92,   100,   201,   212,   213,   214,   219,
     220,   321,   322,   323,   325,   327,   329,   331,   333,   335,
     337,   340,   375,   393,   405,   407,   409,   420,   422,   424,
     444,    76,   201,   333,   335,   375,   401,   402,   403,   405,
     407,    88,    94,    95,    96,    97,    98,    99,   101,   201,
     375,   405,   407,   417,   418,   419,   420,   422,   424,   426,
     430,   432,   434,   436,   438,   440,   442,   349,    33,    65,
      67,    68,    71,    72,    73,   201,   264,   359,   360,   361,
     362,   363,   364,   365,   367,   369,   371,   372,   374,   405,
     407,    66,    69,    70,   201,   264,   363,   369,   383,   384,
     385,   386,   387,   389,   390,   391,   392,   405,   407,   104,
     105,   201,   297,   298,   299,   301,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   138,
     139,   201,   405,   407,   474,   475,   476,   477,   479,   481,
     482,   484,   485,   486,   489,   491,   492,   493,   496,   498,
     500,   141,   520,   521,   522,    12,   512,   513,   514,     6,
       3,     4,     8,     3,   207,   517,   503,   505,   507,     4,
       3,     8,   509,   222,   239,     4,     4,     4,   421,   423,
     425,   237,   245,   247,     4,     4,     4,     4,   217,   314,
     350,   376,   342,   406,   408,   338,   281,   448,   410,   290,
     304,     4,   461,   469,   471,     3,     8,   228,   230,   233,
       4,     3,     8,   326,   328,   330,   394,   324,   332,     4,
     336,   334,   445,     3,     8,   404,     3,     8,   443,   431,
     433,   437,   435,   441,   439,   427,     8,     3,     8,   366,
     265,     4,   370,   368,   373,     4,     8,     3,   388,     4,
       4,     8,     3,   300,   302,     3,     8,     4,   478,   480,
       4,   483,     4,     4,   487,   490,     4,     4,   494,   497,
     499,   501,     3,     8,   523,     3,     8,   515,     3,     8,
     186,   186,   166,     4,     4,     4,     4,     4,   205,     4,
       4,     4,   169,   169,   169,     4,     4,     4,     4,     4,
       4,   167,   167,   167,   167,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   167,     4,
       4,     4,   211,     4,     4,     4,   169,   224,     4,     4,
       4,     4,     4,     4,   167,     4,     4,     4,   322,     4,
     402,     4,     4,     4,     4,     4,     4,     4,     4,   419,
       4,     4,   167,     4,     4,     4,   169,   361,     4,   169,
     169,   385,     4,     4,   298,   169,     4,     4,   167,     4,
     167,   167,     4,     4,   169,   169,     4,     4,     4,     4,
     475,     4,   521,     4,   513,     4,     7,     7,   186,   186,
     186,     7,     7,     7,   166,   166,   166,     7,     7,     5,
     166,     5,     5,     5,     5,   188,   190,   166,    83,    84,
      85,    86,   339,     5,     5,     5,     5,     7,     7,   190,
       7,     5,   197,    16,    17,   231,    19,    20,   234,   166,
     166,   166,     5,   166,   166,   197,   166,     7,   166,   197,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   186,   166,   166,   166,    17,   132,
     488,   133,   134,   135,   136,   137,   169,   495,   166,   166,
     166,     5,     5,   186,   210,   520,   512,   223,    23,   240,
     241,   242,    33,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,   201,
     252,   253,   254,   257,   259,   261,   263,   264,   266,   267,
     268,   269,   270,   271,   272,   273,   275,   277,   278,   279,
     252,     7,   248,   249,   250,     7,   315,   316,   317,     7,
     353,   354,   355,     7,   377,   378,   379,     7,   343,   344,
     345,    94,    95,    96,    97,    99,   282,   283,   284,   285,
     286,   287,   288,     7,   449,   450,     7,   411,   412,   413,
       7,   291,   292,   293,   107,   108,   109,   110,   111,   112,
     305,   306,   307,   308,   309,   310,   311,   312,   115,   116,
     201,   405,   407,   462,   463,   464,   466,   474,   198,     7,
     395,   396,   397,   102,   426,   428,   446,     7,   524,   525,
     248,     8,     8,     8,     8,   243,     3,     8,   255,   258,
     260,   262,     4,     4,     4,     4,     4,   274,   276,     4,
       4,     4,     4,     4,     4,     3,     8,     8,   251,     6,
       3,   318,     6,     3,   356,     6,     3,   380,     6,     3,
     346,     6,     3,     3,     6,   451,     3,     6,   414,     6,
       3,   294,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   465,   467,     3,     8,     8,   166,   199,   200,
     398,     6,     3,   429,     8,   526,     3,     6,     6,     4,
     241,     4,     4,     4,     4,   167,   169,   167,   169,   167,
       4,     4,   167,   167,   167,   167,   169,   167,   253,   252,
     250,   321,   317,   359,   355,   383,   379,   201,   212,   213,
     214,   219,   220,   264,   313,   331,   333,   335,   337,   347,
     348,   375,   405,   407,   420,   422,   424,   444,   345,   283,
      90,    91,   201,   264,   349,   375,   405,   407,   420,   422,
     424,   452,   453,   454,   455,   456,   458,   450,   417,   413,
     297,   293,   167,   167,   167,   167,   167,   167,   306,     4,
       4,   463,     6,     3,   401,   397,     4,   142,   144,   145,
     201,   264,   405,   407,   527,   528,   529,   530,   532,   525,
     166,    34,    35,    36,    37,   256,   166,   166,   166,   166,
     166,     8,     8,     8,     8,     3,     8,   457,     4,     8,
       3,     8,     8,   166,   166,   166,     8,   197,   533,     4,
     531,     3,     8,   348,     4,   169,   454,     4,   167,     4,
     528,   166,     5,   166,     7,   534,   535,   536,     3,     6,
     143,   146,   147,   148,   537,   538,   539,   541,   542,   543,
     535,   540,     4,     4,     4,     3,     8,     4,   169,   167,
     167,   538,   166
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   170,   172,   171,   173,   171,   174,   171,   175,   171,
     176,   171,   177,   171,   178,   171,   179,   171,   180,   171,
     181,   171,   182,   171,   183,   171,   184,   171,   185,   171,
     186,   186,   186,   186,   186,   186,   186,   187,   189,   188,
     190,   191,   191,   192,   192,   194,   193,   195,   195,   196,
     196,   198,   197,   199,   199,   200,   200,   201,   203,   202,
     204,   204,   205,   205,   205,   205,   205,   205,   207,   206,
     209,   208,   210,   210,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   212,   213,
     214,   215,   217,   216,   218,   219,   220,   222,   221,   223,
     223,   224,   224,   224,   224,   224,   224,   224,   226,   225,
     228,   227,   230,   229,   231,   231,   233,   232,   234,   234,
     235,   237,   236,   239,   238,   240,   240,   241,   243,   242,
     245,   244,   247,   246,   248,   248,   249,   249,   251,   250,
     252,   252,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   255,   254,   256,   256,   256,   256,   258,   257,   260,
     259,   262,   261,   263,   265,   264,   266,   267,   268,   269,
     270,   271,   272,   274,   273,   276,   275,   277,   278,   279,
     281,   280,   282,   282,   283,   283,   283,   283,   283,   284,
     285,   286,   287,   288,   290,   289,   291,   291,   292,   292,
     294,   293,   296,   295,   297,   297,   297,   298,   298,   300,
     299,   302,   301,   304,   303,   305,   305,   306,   306,   306,
     306,   306,   306,   307,   308,   309,   310,   311,   312,   314,
     313,   315,   315,   316,   316,   318,   317,   320,   319,   321,
     321,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   324,   323,   326,   325,   328,
     327,   330,   329,   332,   331,   334,   333,   336,   335,   338,
     337,   339,   339,   339,   339,   340,   342,   341,   343,   343,
     344,   344,   346,   345,   347,   347,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   350,   349,   352,   351,   353,
     353,   354,   354,   356,   355,   358,   357,   359,   359,   360,
     360,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   362,   363,   364,   366,   365,   368,   367,   370,   369,
     371,   373,   372,   374,   376,   375,   377,   377,   378,   378,
     380,   379,   382,   381,   383,   383,   384,   384,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   386,   388,   387,
     389,   390,   391,   392,   394,   393,   395,   395,   396,   396,
     398,   397,   400,   399,   401,   401,   402,   402,   402,   402,
     402,   402,   402,   404,   403,   406,   405,   408,   407,   410,
     409,   411,   411,   412,   412,   414,   413,   416,   415,   417,
     417,   418,   418,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   421,   420,
     423,   422,   425,   424,   427,   426,   429,   428,   431,   430,
     433,   432,   435,   434,   437,   436,   439,   438,   441,   440,
     443,   442,   445,   444,   446,   446,   448,   447,   449,   449,
     451,   450,   452,   452,   453,   453,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   455,   457,   456,
     458,   459,   461,   460,   462,   462,   463,   463,   463,   463,
     463,   465,   464,   467,   466,   469,   468,   471,   470,   473,
     472,   474,   474,   475,   475,   475,   475,   475,   475,   475,
     475,   475,   475,   475,   475,   475,   475,   475,   475,   475,
     475,   476,   478,   477,   480,   479,   481,   483,   482,   484,
     485,   487,   486,   488,   488,   490,   489,   491,   492,   494,
     493,   495,   495,   495,   495,   495,   497,   496,   499,   498,
     501,   500,   503,   502,   505,   504,   507,   506,   509,   508,
     511,   510,   512,   512,   513,   515,   514,   517,   516,   519,
     518,   520,   520,   521,   523,   522,   524,   524,   526,   525,
     527,   527,   528,   528,   528,   528,   528,   528,   528,   529,
     531,   530,   533,   532,   534,   534,   536,   535,   537,   537,
     538,   538,   538,   538,   540,   539,   541,   542,   543
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
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     0,     6,     0,
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
  "\"max-row-errors\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"server-tag\"",
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
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
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
  "config_control", "$@115", "sub_config_control", "$@116",
  "config_control_params", "config_control_param", "config_databases",
  "$@117", "logging_object", "$@118", "sub_logging", "$@119",
  "logging_params", "logging_param", "loggers", "$@120", "loggers_entries",
  "logger_entry", "$@121", "logger_params", "logger_param", "debuglevel",
  "severity", "$@122", "output_options_list", "$@123",
  "output_options_list_content", "output_entry", "$@124",
  "output_params_list", "output_params", "output", "$@125", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   255,   255,   255,   256,   256,   257,   257,   258,   258,
     259,   259,   260,   260,   261,   261,   262,   262,   263,   263,
     264,   264,   265,   265,   266,   266,   267,   267,   268,   268,
     276,   277,   278,   279,   280,   281,   282,   285,   290,   290,
     301,   304,   305,   308,   312,   319,   319,   326,   327,   330,
     334,   341,   341,   348,   349,   352,   356,   367,   377,   377,
     393,   394,   398,   399,   400,   401,   402,   403,   406,   406,
     421,   421,   430,   431,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   472,   477,
     482,   487,   492,   492,   500,   505,   510,   516,   516,   527,
     528,   531,   532,   533,   534,   535,   536,   537,   540,   540,
     549,   549,   559,   559,   566,   567,   570,   570,   577,   579,
     583,   589,   589,   601,   601,   611,   612,   614,   616,   616,
     634,   634,   646,   646,   656,   657,   660,   661,   664,   664,
     674,   675,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   690,   691,   692,   693,   694,   695,
     696,   699,   699,   706,   707,   708,   709,   712,   712,   720,
     720,   728,   728,   736,   741,   741,   749,   754,   759,   764,
     769,   774,   779,   784,   784,   792,   792,   800,   805,   810,
     815,   815,   825,   826,   829,   830,   831,   832,   833,   836,
     841,   846,   851,   856,   861,   861,   871,   872,   875,   876,
     879,   879,   889,   889,   899,   900,   901,   904,   905,   908,
     908,   916,   916,   924,   924,   935,   936,   939,   940,   941,
     942,   943,   944,   947,   952,   957,   962,   967,   972,   980,
     980,   993,   994,   997,   998,  1005,  1005,  1031,  1031,  1042,
    1043,  1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,
    1056,  1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,
    1066,  1067,  1068,  1069,  1070,  1073,  1073,  1081,  1081,  1089,
    1089,  1097,  1097,  1105,  1105,  1113,  1113,  1121,  1121,  1131,
    1131,  1138,  1139,  1140,  1141,  1144,  1151,  1151,  1162,  1163,
    1167,  1168,  1171,  1171,  1179,  1180,  1183,  1184,  1185,  1186,
    1187,  1188,  1189,  1190,  1191,  1192,  1193,  1194,  1195,  1196,
    1197,  1198,  1199,  1200,  1201,  1208,  1208,  1221,  1221,  1230,
    1231,  1234,  1235,  1240,  1240,  1255,  1255,  1269,  1270,  1273,
    1274,  1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,
    1286,  1289,  1291,  1296,  1298,  1298,  1306,  1306,  1314,  1314,
    1322,  1324,  1324,  1332,  1341,  1341,  1353,  1354,  1359,  1360,
    1365,  1365,  1377,  1377,  1389,  1390,  1395,  1396,  1401,  1402,
    1403,  1404,  1405,  1406,  1407,  1408,  1409,  1412,  1414,  1414,
    1422,  1424,  1426,  1431,  1439,  1439,  1451,  1452,  1455,  1456,
    1459,  1459,  1469,  1469,  1479,  1480,  1483,  1484,  1485,  1486,
    1487,  1488,  1489,  1492,  1492,  1500,  1500,  1525,  1525,  1555,
    1555,  1565,  1566,  1569,  1570,  1573,  1573,  1582,  1582,  1591,
    1592,  1595,  1596,  1600,  1601,  1602,  1603,  1604,  1605,  1606,
    1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1617,  1617,
    1625,  1625,  1633,  1633,  1641,  1641,  1649,  1649,  1659,  1659,
    1667,  1667,  1675,  1675,  1683,  1683,  1691,  1691,  1699,  1699,
    1707,  1707,  1720,  1720,  1730,  1731,  1737,  1737,  1747,  1748,
    1751,  1751,  1761,  1762,  1765,  1766,  1769,  1770,  1771,  1772,
    1773,  1774,  1775,  1776,  1777,  1778,  1779,  1782,  1784,  1784,
    1792,  1801,  1808,  1808,  1818,  1819,  1822,  1823,  1824,  1825,
    1826,  1829,  1829,  1837,  1837,  1848,  1848,  1886,  1886,  1898,
    1898,  1908,  1909,  1912,  1913,  1914,  1915,  1916,  1917,  1918,
    1919,  1920,  1921,  1922,  1923,  1924,  1925,  1926,  1927,  1928,
    1929,  1932,  1937,  1937,  1945,  1945,  1953,  1958,  1958,  1966,
    1971,  1976,  1976,  1984,  1985,  1988,  1988,  1996,  2001,  2006,
    2006,  2014,  2017,  2020,  2023,  2026,  2032,  2032,  2040,  2040,
    2048,  2048,  2059,  2059,  2066,  2066,  2073,  2073,  2080,  2080,
    2091,  2091,  2101,  2102,  2106,  2109,  2109,  2124,  2124,  2134,
    2134,  2145,  2146,  2150,  2154,  2154,  2166,  2167,  2171,  2171,
    2179,  2180,  2183,  2184,  2185,  2186,  2187,  2188,  2189,  2192,
    2197,  2197,  2205,  2205,  2215,  2216,  2219,  2219,  2227,  2228,
    2231,  2232,  2233,  2234,  2237,  2237,  2245,  2250,  2255
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
#line 4959 "dhcp4_parser.cc" // lalr1.cc:1218
#line 2260 "dhcp4_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
