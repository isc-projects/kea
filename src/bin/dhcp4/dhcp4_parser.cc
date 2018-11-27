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

#if YY_CPLUSPLUS < 201103L
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
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3432 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2078 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3442 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2084 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2088 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3461 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2102 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3472 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2107 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3481 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2117 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3492 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2122 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3501 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2127 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3511 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3519 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 612:
#line 2147 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3530 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 613:
#line 2152 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3539 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2164 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3549 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2168 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3557 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 627:
#line 2185 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3566 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 628:
#line 2190 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3574 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2192 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3584 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2198 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3595 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2203 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3604 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 634:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3614 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2216 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3622 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 642:
#line 2230 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3630 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 643:
#line 2232 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3640 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 644:
#line 2238 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3649 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 645:
#line 2243 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3658 "dhcp4_parser.cc" // lalr1.cc:907
    break;

  case 646:
#line 2248 "dhcp4_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3667 "dhcp4_parser.cc" // lalr1.cc:907
    break;


#line 3671 "dhcp4_parser.cc" // lalr1.cc:907
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


  const short Dhcp4Parser::yypact_ninf_ = -797;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     403,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,    43,    35,    38,    50,    58,
      60,    64,   103,   110,   142,   148,   161,   163,   185,   189,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,    35,   -20,
      17,    71,    32,   152,   -15,   239,   146,   242,    54,   -25,
     361,    76,   206,  -797,   219,   224,   233,   237,   244,  -797,
    -797,  -797,  -797,  -797,   287,  -797,    55,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,   295,   297,   299,  -797,
    -797,  -797,  -797,  -797,  -797,   303,   326,   354,   364,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   367,  -797,  -797,  -797,  -797,    61,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,   369,  -797,    72,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   371,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,    86,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,   135,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,   273,   286,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,   342,  -797,  -797,
     375,  -797,  -797,  -797,   382,  -797,  -797,   345,   362,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   383,   385,  -797,  -797,  -797,  -797,   387,   388,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   138,  -797,  -797,  -797,   386,  -797,  -797,   389,
    -797,   392,   396,  -797,  -797,   397,   398,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   166,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   186,  -797,  -797,  -797,   187,  -797,  -797,  -797,
      35,    35,  -797,    77,   405,   408,   409,   410,   411,  -797,
      17,  -797,   415,   418,   422,   250,   259,   265,   430,   432,
     435,   436,   437,   438,   278,   279,   280,   282,   439,   445,
     446,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   311,   488,   489,   490,    71,  -797,   491,   492,   493,
     332,    32,  -797,   497,   498,   499,   500,   501,   504,   343,
     506,   507,   509,   152,  -797,   510,   -15,  -797,   511,   512,
     513,   514,   515,   516,   517,   518,  -797,   239,  -797,   519,
     520,   365,   523,   524,   526,   366,  -797,   242,   528,   368,
     373,  -797,    54,   529,   531,   -13,  -797,   374,   533,   535,
     378,   541,   380,   381,   544,   545,   384,   400,   546,   566,
     568,   569,   361,  -797,   570,    76,  -797,   571,   206,  -797,
    -797,  -797,   572,   573,   574,    35,    35,    35,  -797,   575,
     576,   577,  -797,  -797,  -797,   412,   413,   420,   579,   580,
     583,  -797,  -797,  -797,  -797,   424,   585,   586,   587,   588,
     589,   429,   172,   590,   592,   593,   594,   595,  -797,   596,
     589,   597,  -797,   600,   304,   309,  -797,  -797,   441,   442,
     443,   604,   447,   448,  -797,   600,   449,   603,  -797,   450,
    -797,   600,   451,   452,   453,   454,   455,   456,   457,  -797,
     458,   459,  -797,   460,   461,   462,  -797,  -797,   473,  -797,
    -797,  -797,   474,    35,  -797,  -797,   475,   476,  -797,   477,
    -797,  -797,    11,   479,  -797,  -797,   -29,   478,   480,   481,
    -797,   623,  -797,   624,  -797,    35,    71,    76,  -797,  -797,
    -797,   206,    32,   578,  -797,  -797,  -797,   414,   414,   625,
    -797,   626,   627,   628,   629,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,    66,   630,   637,   640,     5,    95,  -797,
     361,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   641,  -797,  -797,  -797,  -797,   263,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   642,   625,  -797,   190,   196,   231,   238,  -797,   261,
    -797,  -797,  -797,  -797,  -797,  -797,   646,   647,   648,   649,
     650,  -797,  -797,   651,   652,   653,   654,   655,  -797,   262,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   270,  -797,
     656,   657,  -797,  -797,   658,   660,  -797,  -797,   659,   663,
    -797,  -797,   661,   665,  -797,  -797,   664,   666,  -797,  -797,
    -797,  -797,  -797,  -797,   211,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   232,  -797,  -797,   667,   668,  -797,  -797,   669,
     671,  -797,   672,   673,   674,   675,   676,   677,   274,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   276,  -797,  -797,  -797,   277,   496,  -797,   678,   679,
    -797,  -797,  -797,  -797,   622,  -797,   335,  -797,   680,  -797,
    -797,  -797,  -797,   681,   578,  -797,   683,   684,   685,   686,
     434,   525,   530,   527,   532,   687,   688,   534,   536,   537,
     538,   539,   414,  -797,  -797,   414,  -797,   625,   152,  -797,
     626,   242,  -797,   627,    54,  -797,   628,   195,  -797,   629,
      66,  -797,   234,   630,  -797,   239,  -797,   637,   -25,  -797,
     640,   540,   542,   543,   547,   548,   549,     5,  -797,   690,
     693,    95,  -797,  -797,  -797,   695,   696,   -15,  -797,   641,
     701,  -797,    10,   642,  -797,  -797,   551,  -797,   347,   552,
     553,   554,  -797,  -797,  -797,  -797,  -797,   555,   556,  -797,
    -797,  -797,  -797,  -797,  -797,   284,  -797,   285,  -797,   702,
    -797,   703,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,   292,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,   708,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,   714,   720,  -797,
    -797,  -797,  -797,  -797,   716,  -797,   319,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,   560,   561,  -797,  -797,   562,
     337,  -797,   600,  -797,   724,  -797,  -797,  -797,  -797,  -797,
     339,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   195,  -797,   725,   563,  -797,   234,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   726,   567,   728,    10,  -797,  -797,
     581,  -797,  -797,   729,  -797,   582,  -797,  -797,   730,  -797,
    -797,   349,  -797,   -10,   730,  -797,  -797,   731,   732,   734,
     346,  -797,  -797,  -797,  -797,  -797,  -797,   735,   584,   607,
     610,   -10,  -797,   598,  -797,  -797,  -797,  -797,  -797
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
     230,    23,   537,    25,   607,    27,   598,    29,    47,    41,
       0,     0,     0,     0,     0,   447,     0,   355,   392,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     605,   590,   592,   594,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   596,   117,   143,     0,     0,     0,   466,
     468,   470,   141,   150,   152,     0,     0,     0,     0,   112,
     257,   343,   382,   314,   433,   435,   307,   208,   494,   437,
     222,   241,     0,   520,   533,   535,   107,     0,    72,    74,
      75,    76,    77,   105,    94,    95,    96,    80,    81,   102,
      82,    83,    84,    88,    89,    78,   106,    79,    86,    87,
     100,   101,   103,    97,    98,    99,    85,    90,    91,    92,
      93,   104,   130,   132,   136,     0,   127,     0,   119,   121,
     122,   123,   124,   125,   126,   295,   297,   299,   412,   293,
     301,     0,   305,   303,   490,   292,   269,   270,   271,   282,
     283,     0,   267,   274,   287,   288,   289,   275,   277,   278,
     280,   276,   272,   273,   290,   291,   279,   284,   285,   286,
     281,   431,   430,   426,   427,   425,     0,   422,   424,   428,
     429,   488,   476,   478,   482,   480,   486,   484,   472,   465,
     459,   463,   464,     0,   448,   449,   460,   461,   462,   456,
     451,   457,   453,   454,   455,   458,   452,     0,   372,   193,
       0,   376,   374,   379,     0,   368,   369,     0,   356,   357,
     359,   371,   360,   361,   362,   378,   363,   364,   365,   366,
     367,   406,     0,     0,   404,   405,   408,   409,     0,   393,
     394,   396,   397,   398,   399,   400,   401,   402,   403,   237,
     239,   234,     0,   232,   235,   236,     0,   560,   562,     0,
     565,     0,     0,   569,   573,     0,     0,   577,   584,   586,
     588,   558,   556,   557,     0,   539,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   612,     0,   609,   611,   603,     0,   600,   602,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   266,     0,     0,   421,     0,     0,
       0,     0,     0,     0,     0,     0,   446,     0,   346,     0,
       0,     0,     0,     0,     0,     0,   354,     0,     0,     0,
       0,   391,     0,     0,     0,     0,   231,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   538,     0,     0,   608,     0,     0,   599,
      50,    43,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,   114,   115,   116,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   519,     0,
       0,     0,    73,     0,     0,     0,   140,   120,     0,     0,
       0,     0,     0,     0,   313,     0,     0,     0,   268,     0,
     423,     0,     0,     0,     0,     0,     0,     0,     0,   450,
       0,     0,   370,     0,     0,     0,   381,   358,     0,   410,
     411,   395,     0,     0,   233,   559,     0,     0,   564,     0,
     567,   568,     0,     0,   575,   576,     0,     0,     0,     0,
     540,     0,   610,     0,   601,     0,     0,     0,   591,   593,
     595,     0,     0,     0,   467,   469,   471,     0,     0,   154,
     113,   259,   347,   384,   316,    40,   434,   436,   309,   310,
     311,   312,   308,     0,     0,   439,   224,     0,     0,   534,
       0,    51,   131,   134,   135,   133,   138,   139,   137,   296,
     298,   300,   414,   294,   302,   306,   304,     0,   432,   489,
     477,   479,   483,   481,   487,   485,   473,   373,   194,   377,
     375,   380,   407,   238,   240,   561,   563,   566,   571,   572,
     570,   574,   579,   580,   581,   582,   583,   578,   585,   587,
     589,     0,   154,    44,     0,     0,     0,     0,   148,     0,
     145,   147,   180,   186,   188,   190,     0,     0,     0,     0,
       0,   202,   204,     0,     0,     0,     0,     0,   179,     0,
     160,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   175,   176,   177,   172,   178,   173,   174,     0,   158,
       0,   155,   156,   263,     0,   260,   261,   351,     0,   348,
     349,   388,     0,   385,   386,   320,     0,   317,   318,   217,
     218,   219,   220,   221,     0,   210,   212,   213,   214,   215,
     216,   498,     0,   496,   443,     0,   440,   441,   228,     0,
     225,   226,     0,     0,     0,     0,     0,     0,     0,   243,
     245,   246,   247,   248,   249,   250,   529,   531,   528,   526,
     527,     0,   522,   524,   525,     0,    53,   418,     0,   415,
     416,   474,   492,   493,     0,   616,     0,   614,     0,    69,
     606,   597,   118,     0,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   142,   151,     0,   153,     0,     0,   258,
       0,   355,   344,     0,   392,   383,     0,     0,   315,     0,
       0,   209,   500,     0,   495,   447,   438,     0,     0,   223,
       0,     0,     0,     0,     0,     0,     0,     0,   242,     0,
       0,     0,   521,   536,    55,     0,    54,     0,   413,     0,
       0,   491,     0,     0,   613,   604,     0,   146,     0,     0,
       0,     0,   192,   195,   196,   197,   198,     0,     0,   206,
     207,   199,   200,   201,   161,     0,   157,     0,   262,     0,
     350,     0,   387,   342,   339,   327,   328,   330,   331,   324,
     325,   326,   337,   338,   336,     0,   322,   329,   340,   341,
     332,   333,   334,   335,   319,   211,   516,     0,   514,   515,
     507,   508,   512,   513,   509,   510,   511,     0,   501,   502,
     504,   505,   506,   497,     0,   442,     0,   227,   251,   252,
     253,   254,   255,   256,   244,     0,     0,   523,    52,     0,
       0,   417,     0,   630,     0,   628,   626,   620,   624,   625,
       0,   618,   622,   623,   621,   615,   149,   182,   183,   184,
     185,   181,   187,   189,   191,   203,   205,   159,   264,   352,
     389,     0,   321,     0,     0,   499,     0,   444,   229,   530,
     532,    56,   419,   475,     0,     0,     0,     0,   617,   323,
       0,   518,   503,     0,   627,     0,   619,   517,     0,   629,
     634,     0,   632,     0,     0,   631,   642,     0,     0,     0,
       0,   636,   638,   639,   640,   641,   633,     0,     0,     0,
       0,     0,   635,     0,   644,   645,   646,   637,   643
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,   -46,  -797,  -451,  -797,
     121,  -797,  -797,  -797,  -797,  -797,  -797,  -501,  -797,  -797,
    -797,   -70,  -797,  -797,  -797,   312,  -797,  -797,  -797,  -797,
     107,   348,   -47,   -44,     4,  -797,  -797,  -797,  -797,    12,
      15,  -797,  -797,   158,   340,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   -52,  -797,  -797,  -797,  -797,  -797,  -797,    82,  -797,
     -72,  -797,  -563,   -59,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   -26,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   -81,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   -90,  -797,  -797,  -797,   -83,   321,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,   -61,  -797,  -797,  -797,  -797,
    -797,  -797,  -796,  -797,  -797,  -797,   -43,  -797,  -797,  -797,
     -34,   377,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -795,  -797,   -68,  -797,   -55,  -797,    19,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   -38,  -797,  -797,  -184,   -63,  -797,
    -797,  -797,  -797,  -797,   -16,  -797,  -797,  -797,   -18,  -797,
     372,  -797,   -66,  -797,  -797,  -797,  -797,  -797,   -64,  -797,
    -797,  -797,  -797,  -797,   -19,  -797,  -797,  -797,   -22,  -797,
    -797,  -797,   -14,  -797,   379,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,   -45,  -797,  -797,  -797,
     -40,   425,  -797,  -797,   -57,  -797,   -39,  -797,   -62,  -797,
    -797,  -797,     7,  -797,  -797,  -797,    -8,  -797,   407,    -7,
    -797,    -3,  -797,     8,  -797,   192,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -790,  -797,  -797,  -797,  -797,  -797,    14,
    -797,  -797,  -797,  -141,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,    -2,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,   240,   390,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   267,   391,  -797,  -797,  -797,  -797,  -797,  -797,   281,
     395,  -797,  -797,  -797,   -12,  -797,  -797,  -144,  -797,  -797,
    -797,  -797,  -797,  -797,  -160,  -797,  -797,  -176,  -797,  -797,
    -797,  -797,  -797
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     596,    87,    88,    41,    68,    84,    85,   612,   776,   855,
     856,   688,    43,    70,    96,    97,    98,   354,    45,    71,
     137,   138,   139,   140,   141,   142,   143,   378,   144,   145,
     146,   147,   363,   177,   178,    47,    72,   179,   397,   180,
     398,   615,   181,   399,   618,   182,   148,   371,   149,   364,
     669,   670,   671,   793,   150,   372,   151,   373,   710,   711,
     712,   815,   689,   690,   691,   796,   971,   692,   797,   693,
     798,   694,   799,   695,   696,   430,   697,   698,   699,   700,
     701,   702,   703,   704,   805,   705,   806,   706,   707,   152,
     386,   734,   735,   736,   737,   738,   739,   740,   153,   389,
     749,   750,   751,   838,    61,    79,   302,   303,   304,   443,
     305,   444,   154,   390,   758,   759,   760,   761,   762,   763,
     764,   765,   155,   379,   714,   715,   716,   818,    49,    73,
     201,   202,   203,   407,   204,   403,   205,   404,   206,   405,
     207,   408,   208,   411,   209,   410,   156,   385,   602,   211,
     157,   382,   726,   727,   728,   827,   905,   906,   158,   380,
      55,    76,   718,   719,   720,   821,    57,    77,   267,   268,
     269,   270,   271,   272,   273,   429,   274,   433,   275,   432,
     276,   277,   434,   278,   159,   381,   722,   723,   724,   824,
      59,    78,   288,   289,   290,   291,   292,   438,   293,   294,
     295,   296,   213,   406,   778,   779,   780,   857,    51,    74,
     226,   227,   228,   415,   160,   383,   161,   384,   162,   388,
     745,   746,   747,   835,    53,    75,   243,   244,   245,   163,
     368,   164,   369,   165,   370,   249,   425,   783,   860,   250,
     419,   251,   420,   252,   422,   253,   421,   254,   424,   255,
     423,   256,   418,   220,   412,   784,   166,   387,   742,   743,
     832,   927,   928,   929,   930,   931,   983,   932,   167,   168,
     392,   771,   772,   773,   849,   774,   850,   169,   393,   170,
     394,    63,    80,   324,   325,   326,   327,   448,   328,   449,
     329,   330,   451,   331,   332,   333,   454,   650,   334,   455,
     335,   336,   337,   458,   657,   338,   459,   339,   460,   340,
     461,    99,   356,   100,   357,   101,   358,   171,   362,    67,
      82,   346,   347,   348,   467,   102,   355,    65,    81,   342,
     343,   344,   464,   786,   787,   862,   960,   961,   962,   963,
     996,   964,   994,  1011,  1012,  1013,  1020,  1021,  1022,  1027,
    1023,  1024,  1025
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   136,   176,   195,   222,   239,   223,   265,   284,   301,
     321,   216,   286,   257,   287,   183,   214,   229,   241,   224,
     279,   297,    83,   322,   625,   708,   196,    89,   648,   197,
     629,   900,   901,   184,   215,   230,   242,   913,   280,   298,
      31,   323,    32,    30,    33,    42,   172,   173,   122,   595,
     174,   266,   285,   175,   212,   225,   240,    44,   360,   595,
     221,   124,   125,   361,   395,    46,   217,    48,   246,   396,
     218,    50,   247,   192,   259,   401,   193,   198,   299,   300,
     402,   219,   103,   248,   104,   199,   124,   125,   200,   413,
     299,   300,   210,   105,   414,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   652,   653,   654,   655,   124,   125,
      52,   752,   753,   754,   755,   756,   757,    54,   259,   281,
     260,   261,   282,   283,   115,   116,   117,   118,   119,   120,
     124,   125,  1016,   121,   122,  1017,  1018,  1019,   416,   656,
      94,   445,   649,   417,   123,    86,   446,   124,   125,    56,
      94,   953,   126,   954,   955,    58,    90,   127,   128,   729,
     730,   731,   732,   129,   733,    91,    92,    93,    60,   462,
      62,   124,   125,   130,   463,    94,   131,   107,   108,   109,
     110,   111,    94,   132,   133,   900,   901,   134,   135,   465,
     468,   913,    64,   395,   466,   469,    66,    94,   789,   465,
      34,    35,    36,    37,   790,   115,   116,   117,   121,   766,
     767,   185,   186,   187,   830,   122,   341,   831,   345,    94,
     107,   108,   109,   110,   111,   349,   188,   350,   124,   125,
     189,   190,   191,   126,   468,   833,    94,   351,   834,   791,
     192,   401,   472,   193,   129,   352,   792,   353,   115,   116,
     117,   194,   885,   120,   598,   599,   600,   601,   122,   259,
      94,   109,   110,   111,   794,   812,   109,   110,   111,   795,
     813,   124,   125,   812,   190,   258,   126,   847,   814,   851,
     462,   426,   848,   192,   852,   853,   193,   812,   413,   427,
      95,   359,   977,   978,   194,   981,   121,   122,   259,   365,
     982,   366,   122,   367,   470,   471,   259,   374,   260,   261,
     124,   125,   262,   263,   264,   124,   125,    94,   124,   125,
     613,   614,   445,   916,   917,   136,   231,   988,   616,   617,
     375,   176,   232,   233,   234,   235,   236,   237,   863,   238,
     416,   864,   997,   195,   183,   992,   222,   998,   223,  1031,
     428,   216,  1014,   436,  1032,  1015,   214,   239,   376,   229,
      94,   224,   184,   238,   781,   437,   196,   265,   377,   197,
     241,   391,   284,   400,   215,   409,   286,   230,   287,   431,
     279,   967,   968,   969,   970,   297,   435,   439,   242,   440,
     447,   442,   321,   450,   212,   441,   452,   225,   280,    94,
     453,   456,   457,   298,    94,   322,   217,    94,   240,   473,
     218,   266,   474,   475,   476,   477,   285,   198,   482,   479,
     246,   219,   480,   323,   247,   199,   481,   483,   200,   578,
     579,   580,   210,   484,   485,   248,   486,   124,   125,   487,
     488,   489,   490,   495,   491,   492,   493,   672,   494,   496,
     497,   993,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   259,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   509,   510,   511,   513,   514,   515,   319,   320,
     516,   518,   519,   520,   521,   522,   136,   644,   523,   524,
     525,   526,   176,   527,   529,   531,   532,   533,   534,   535,
     536,   537,   538,   540,   541,   183,    94,   543,   544,   663,
     545,   542,   548,   552,   546,   553,   549,   556,   768,   557,
     321,   550,   555,   184,   558,   559,   560,   561,   562,   563,
     566,   769,   564,   322,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   565,   770,
     567,   323,   568,   569,   571,   573,   575,   584,   585,    94,
     576,   577,   581,   582,   583,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   597,   603,    32,   604,   605,   606,
     872,   668,   607,   608,   610,   611,   619,   620,   621,   622,
     627,   651,   623,   624,   626,   628,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   639,   640,   641,   661,   662,
     861,   609,   709,   713,   717,   721,   725,   741,   642,   643,
     645,   646,   647,   658,   744,   659,   660,   748,   777,   785,
     800,   801,   802,   803,   804,   807,   808,   809,   810,   811,
     817,   854,   816,   820,   819,   822,   823,   825,   826,   829,
     828,   837,   478,   836,   840,   839,   841,   842,   843,   844,
     845,   846,   859,   664,   858,   866,   865,   868,   869,   870,
     871,   877,   878,   873,   945,   875,   874,   946,   876,   949,
     879,   948,   880,   881,   882,   952,   938,   883,   939,   940,
     979,   980,   984,   941,   942,   943,   966,   972,   973,   974,
     975,   976,   985,   986,   987,   989,   990,   991,   995,  1000,
    1003,  1001,  1005,  1004,  1008,  1028,  1029,  1010,  1030,  1033,
     667,   517,   867,   512,   788,   886,  1007,  1009,   195,   915,
     937,   265,  1034,   884,   284,   936,   216,   893,   286,   902,
     287,   214,   918,  1038,   279,   239,   554,   297,   301,   920,
     908,   196,   903,  1035,   197,   922,  1036,   888,   241,   215,
     894,   768,   280,   895,   887,   298,   944,   222,   909,   223,
     528,   914,   956,   923,   769,   266,   242,   999,   285,   212,
     229,   899,   224,   889,   892,   958,   919,   890,   907,   547,
     891,   217,   770,   921,   951,   218,   240,   950,   230,   782,
     910,   551,   198,   959,   911,   924,   219,   934,   246,   925,
     199,   896,   247,   200,   539,   912,   957,   210,   225,   897,
     926,   530,   898,   248,   935,  1002,   904,   933,   666,   947,
     775,   965,   570,  1006,  1026,  1037,     0,     0,   665,   574,
     572,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   893,     0,   902,     0,     0,   918,     0,     0,     0,
       0,     0,     0,   920,   908,     0,   903,   956,     0,   922,
       0,     0,     0,     0,   894,     0,     0,   895,     0,     0,
     958,     0,   909,     0,     0,     0,     0,   923,     0,     0,
       0,     0,     0,     0,     0,   899,     0,     0,   959,     0,
     919,     0,   907,     0,     0,     0,     0,   921,     0,     0,
       0,   957,     0,     0,   910,     0,     0,     0,   911,   924,
       0,     0,     0,   925,     0,   896,     0,     0,     0,   912,
       0,     0,     0,   897,   926,     0,   898,     0,     0,     0,
     904
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,    74,
      77,    78,    68,    80,   525,   588,    73,    10,    17,    73,
     531,   827,   827,    72,    73,    74,    75,   827,    77,    78,
       5,    80,     7,     0,     9,     7,    14,    15,    63,   500,
      18,    77,    78,    21,    73,    74,    75,     7,     3,   510,
      75,    76,    77,     8,     3,     7,    73,     7,    75,     8,
      73,     7,    75,    88,    64,     3,    91,    73,   103,   104,
       8,    73,    11,    75,    13,    73,    76,    77,    73,     3,
     103,   104,    73,    22,     8,    24,    25,    26,    27,    28,
      29,    30,    31,    32,   133,   134,   135,   136,    76,    77,
       7,   106,   107,   108,   109,   110,   111,     7,    64,    65,
      66,    67,    68,    69,    53,    54,    55,    56,    57,    58,
      76,    77,   142,    62,    63,   145,   146,   147,     3,   168,
     165,     3,   131,     8,    73,   165,     8,    76,    77,     7,
     165,   141,    81,   143,   144,     7,   139,    86,    87,    93,
      94,    95,    96,    92,    98,   148,   149,   150,     7,     3,
       7,    76,    77,   102,     8,   165,   105,    25,    26,    27,
      28,    29,   165,   112,   113,   981,   981,   116,   117,     3,
       3,   981,     7,     3,     8,     8,     7,   165,     8,     3,
     165,   166,   167,   168,     8,    53,    54,    55,    62,   114,
     115,    59,    60,    61,     3,    63,   140,     6,    12,   165,
      25,    26,    27,    28,    29,     6,    74,     3,    76,    77,
      78,    79,    80,    81,     3,     3,   165,     4,     6,     8,
      88,     3,   165,    91,    92,     8,     8,     3,    53,    54,
      55,    99,   815,    58,    82,    83,    84,    85,    63,    64,
     165,    27,    28,    29,     3,     3,    27,    28,    29,     8,
       8,    76,    77,     3,    79,    33,    81,     3,     8,     3,
       3,     8,     8,    88,     8,     8,    91,     3,     3,     3,
     360,     4,     8,     8,    99,     3,    62,    63,    64,     4,
       8,     4,    63,     4,   350,   351,    64,     4,    66,    67,
      76,    77,    70,    71,    72,    76,    77,   165,    76,    77,
      16,    17,     3,    89,    90,   395,    87,     8,    19,    20,
       4,   401,    93,    94,    95,    96,    97,    98,     3,   100,
       3,     6,     3,   413,   401,     8,   416,     8,   416,     3,
       8,   413,     3,     8,     8,     6,   413,   427,     4,   416,
     165,   416,   401,   100,   101,     3,   413,   437,     4,   413,
     427,     4,   442,     4,   413,     4,   442,   416,   442,     4,
     437,    34,    35,    36,    37,   442,     4,     4,   427,     4,
       4,     3,   462,     4,   413,     8,     4,   416,   437,   165,
       4,     4,     4,   442,   165,   462,   413,   165,   427,     4,
     413,   437,     4,     4,     4,     4,   442,   413,   168,     4,
     427,   413,     4,   462,   427,   413,     4,   168,   413,   475,
     476,   477,   413,   168,     4,   427,     4,    76,    77,     4,
       4,     4,     4,     4,   166,   166,   166,    33,   166,     4,
       4,   952,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   166,    64,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     4,     4,     4,     4,     4,     4,   137,   138,
     168,     4,     4,     4,     4,     4,   576,   553,     4,   166,
       4,     4,   582,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   582,   165,     4,     4,   575,
       4,   166,     4,     4,   168,     4,   168,     4,   608,     4,
     610,   168,   168,   582,   166,     4,   166,   166,     4,     4,
       4,   608,   168,   610,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   168,   608,
       4,   610,     4,     4,     4,     4,     4,   165,   165,   165,
       7,     7,     7,     7,     7,   165,     7,     7,     5,   165,
       5,     5,     5,     5,   165,     5,     7,     5,     5,     5,
     166,    23,     7,     7,     7,     5,   165,   165,   165,     5,
       7,   132,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,     5,     5,
       8,   510,     7,     7,     7,     7,     7,     7,   165,   165,
     165,   165,   165,   165,     7,   165,   165,     7,     7,     7,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   165,     6,     3,     6,     6,     3,     6,     3,     3,
       6,     3,   360,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     3,   576,     6,     4,     6,     4,     4,     4,
       4,     4,     4,   168,     4,   168,   166,     4,   166,     3,
     166,     6,   166,   166,   166,     4,   166,   168,   166,   166,
       8,     8,     4,   166,   166,   166,   165,   165,   165,   165,
     165,   165,     8,     3,     8,   165,   165,   165,     4,     4,
       4,   168,     4,   166,     5,     4,     4,     7,     4,     4,
     582,   401,   794,   395,   662,   817,   165,   165,   818,   830,
     840,   821,   168,   812,   824,   838,   818,   827,   824,   827,
     824,   818,   832,   165,   821,   835,   445,   824,   838,   832,
     827,   818,   827,   166,   818,   832,   166,   820,   835,   818,
     827,   851,   821,   827,   818,   824,   847,   857,   827,   857,
     413,   829,   862,   832,   851,   821,   835,   981,   824,   818,
     857,   827,   857,   821,   826,   862,   832,   823,   827,   437,
     824,   818,   851,   832,   859,   818,   835,   857,   857,   627,
     827,   442,   818,   862,   827,   832,   818,   835,   835,   832,
     818,   827,   835,   818,   427,   827,   862,   818,   857,   827,
     832,   416,   827,   835,   837,   986,   827,   833,   581,   851,
     610,   863,   462,   997,  1014,  1031,    -1,    -1,   577,   468,
     465,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   981,    -1,   981,    -1,    -1,   986,    -1,    -1,    -1,
      -1,    -1,    -1,   986,   981,    -1,   981,   997,    -1,   986,
      -1,    -1,    -1,    -1,   981,    -1,    -1,   981,    -1,    -1,
     997,    -1,   981,    -1,    -1,    -1,    -1,   986,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   981,    -1,    -1,   997,    -1,
     986,    -1,   981,    -1,    -1,    -1,    -1,   986,    -1,    -1,
      -1,   997,    -1,    -1,   981,    -1,    -1,    -1,   981,   986,
      -1,    -1,    -1,   986,    -1,   981,    -1,    -1,    -1,   981,
      -1,    -1,    -1,   981,   986,    -1,   981,    -1,    -1,    -1,
     981
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
       7,   293,     7,   470,     7,   516,     7,   508,   193,   188,
     202,   208,   225,   318,   398,   414,   350,   356,   380,   294,
     471,   517,   509,   185,   194,   195,   165,   190,   191,    10,
     139,   148,   149,   150,   165,   200,   203,   204,   205,   500,
     502,   504,   514,    11,    13,    22,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    53,    54,    55,    56,    57,
      58,    62,    63,    73,    76,    77,    81,    86,    87,    92,
     102,   105,   112,   113,   116,   117,   200,   209,   210,   211,
     212,   213,   214,   215,   217,   218,   219,   220,   235,   237,
     243,   245,   278,   287,   301,   311,   335,   339,   347,   373,
     403,   405,   407,   418,   420,   422,   445,   457,   458,   466,
     468,   506,    14,    15,    18,    21,   200,   222,   223,   226,
     228,   231,   234,   403,   405,    59,    60,    61,    74,    78,
      79,    80,    88,    91,    99,   200,   211,   212,   213,   218,
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
     498,   140,   518,   519,   520,    12,   510,   511,   512,     6,
       3,     4,     8,     3,   206,   515,   501,   503,   505,     4,
       3,     8,   507,   221,   238,     4,     4,     4,   419,   421,
     423,   236,   244,   246,     4,     4,     4,     4,   216,   312,
     348,   374,   340,   404,   406,   336,   279,   446,   408,   288,
     302,     4,   459,   467,   469,     3,     8,   227,   229,   232,
       4,     3,     8,   324,   326,   328,   392,   322,   330,     4,
     334,   332,   443,     3,     8,   402,     3,     8,   441,   429,
     431,   435,   433,   439,   437,   425,     8,     3,     8,   364,
     264,     4,   368,   366,   371,     4,     8,     3,   386,     4,
       4,     8,     3,   298,   300,     3,     8,     4,   476,   478,
       4,   481,     4,     4,   485,   488,     4,     4,   492,   495,
     497,   499,     3,     8,   521,     3,     8,   513,     3,     8,
     185,   185,   165,     4,     4,     4,     4,     4,   204,     4,
       4,     4,   168,   168,   168,     4,     4,     4,     4,     4,
       4,   166,   166,   166,   166,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   166,     4,
       4,     4,   210,     4,     4,     4,   168,   223,     4,     4,
       4,     4,     4,     4,   166,     4,     4,     4,   320,     4,
     400,     4,     4,     4,     4,     4,     4,     4,     4,   417,
       4,     4,   166,     4,     4,     4,   168,   359,     4,   168,
     168,   383,     4,     4,   296,   168,     4,     4,   166,     4,
     166,   166,     4,     4,   168,   168,     4,     4,     4,     4,
     473,     4,   519,     4,   511,     4,     7,     7,   185,   185,
     185,     7,     7,     7,   165,   165,   165,     7,     7,     5,
     165,     5,     5,     5,     5,   187,   189,   165,    82,    83,
      84,    85,   337,     5,     5,     5,     5,     7,     7,   189,
       7,     5,   196,    16,    17,   230,    19,    20,   233,   165,
     165,   165,     5,   165,   165,   196,   165,     7,   165,   196,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   185,   165,   165,   165,    17,   131,
     486,   132,   133,   134,   135,   136,   168,   493,   165,   165,
     165,     5,     5,   185,   209,   518,   510,   222,    23,   239,
     240,   241,    33,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,   200,   251,
     252,   253,   256,   258,   260,   262,   263,   265,   266,   267,
     268,   269,   270,   271,   272,   274,   276,   277,   251,     7,
     247,   248,   249,     7,   313,   314,   315,     7,   351,   352,
     353,     7,   375,   376,   377,     7,   341,   342,   343,    93,
      94,    95,    96,    98,   280,   281,   282,   283,   284,   285,
     286,     7,   447,   448,     7,   409,   410,   411,     7,   289,
     290,   291,   106,   107,   108,   109,   110,   111,   303,   304,
     305,   306,   307,   308,   309,   310,   114,   115,   200,   403,
     405,   460,   461,   462,   464,   472,   197,     7,   393,   394,
     395,   101,   424,   426,   444,     7,   522,   523,   247,     8,
       8,     8,     8,   242,     3,     8,   254,   257,   259,   261,
       4,     4,     4,     4,     4,   273,   275,     4,     4,     4,
       4,     4,     3,     8,     8,   250,     6,     3,   316,     6,
       3,   354,     6,     3,   378,     6,     3,   344,     6,     3,
       3,     6,   449,     3,     6,   412,     6,     3,   292,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   463,
     465,     3,     8,     8,   165,   198,   199,   396,     6,     3,
     427,     8,   524,     3,     6,     6,     4,   240,     4,     4,
       4,     4,   166,   168,   166,   168,   166,     4,     4,   166,
     166,   166,   166,   168,   252,   251,   249,   319,   315,   357,
     353,   381,   377,   200,   211,   212,   213,   218,   219,   263,
     311,   329,   331,   333,   335,   345,   346,   373,   403,   405,
     418,   420,   422,   442,   343,   281,    89,    90,   200,   263,
     347,   373,   403,   405,   418,   420,   422,   450,   451,   452,
     453,   454,   456,   448,   415,   411,   295,   291,   166,   166,
     166,   166,   166,   166,   304,     4,     4,   461,     6,     3,
     399,   395,     4,   141,   143,   144,   200,   263,   403,   405,
     525,   526,   527,   528,   530,   523,   165,    34,    35,    36,
      37,   255,   165,   165,   165,   165,   165,     8,     8,     8,
       8,     3,     8,   455,     4,     8,     3,     8,     8,   165,
     165,   165,     8,   196,   531,     4,   529,     3,     8,   346,
       4,   168,   452,     4,   166,     4,   526,   165,     5,   165,
       7,   532,   533,   534,     3,     6,   142,   145,   146,   147,
     535,   536,   537,   539,   540,   541,   533,   538,     4,     4,
       4,     3,     8,     4,   168,   166,   166,   536,   165
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
     501,   500,   503,   502,   505,   504,   507,   506,   509,   508,
     510,   510,   511,   513,   512,   515,   514,   517,   516,   518,
     518,   519,   521,   520,   522,   522,   524,   523,   525,   525,
     526,   526,   526,   526,   526,   526,   526,   527,   529,   528,
     531,   530,   532,   532,   534,   533,   535,   535,   536,   536,
     536,   536,   538,   537,   539,   540,   541
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
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     0,     6,     0,     6,     0,     4,     1,
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
    2052,  2052,  2059,  2059,  2066,  2066,  2073,  2073,  2084,  2084,
    2094,  2095,  2099,  2102,  2102,  2117,  2117,  2127,  2127,  2138,
    2139,  2143,  2147,  2147,  2159,  2160,  2164,  2164,  2172,  2173,
    2176,  2177,  2178,  2179,  2180,  2181,  2182,  2185,  2190,  2190,
    2198,  2198,  2208,  2209,  2212,  2212,  2220,  2221,  2224,  2225,
    2226,  2227,  2230,  2230,  2238,  2243,  2248
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
#line 4947 "dhcp4_parser.cc" // lalr1.cc:1218
#line 2253 "dhcp4_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
