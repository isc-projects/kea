// A Bison parser, made by GNU Bison 3.0.5.

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

// Take the name prefix into account.
#define yylex   parser4_lex

// First part of user declarations.

#line 39 "dhcp4_parser.cc" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp4_parser.h"

// User implementation prologue.

#line 53 "dhcp4_parser.cc" // lalr1.cc:414
// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:415

#include <dhcp4/parser_context.h>

#line 59 "dhcp4_parser.cc" // lalr1.cc:415


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

#line 14 "dhcp4_parser.yy" // lalr1.cc:481
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc" // lalr1.cc:481

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

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    switch (that.type_get ())
    {
      case 180: // value
      case 184: // map_value
      case 222: // socket_type
      case 225: // outbound_interface_value
      case 247: // db_type
      case 329: // hr_mode
      case 477: // ncr_protocol_value
      case 485: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 164: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 163: // "floating point"
        value.copy< double > (that.value);
        break;

      case 162: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 161: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 180: // value
      case 184: // map_value
      case 222: // socket_type
      case 225: // outbound_interface_value
      case 247: // db_type
      case 329: // hr_mode
      case 477: // ncr_protocol_value
      case 485: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 164: // "boolean"
        value.move< bool > (that.value);
        break;

      case 163: // "floating point"
        value.move< double > (that.value);
        break;

      case 162: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 161: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 180: // value
      case 184: // map_value
      case 222: // socket_type
      case 225: // outbound_interface_value
      case 247: // db_type
      case 329: // hr_mode
      case 477: // ncr_protocol_value
      case 485: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 164: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 163: // "floating point"
        value.copy< double > (that.value);
        break;

      case 162: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 161: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


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
            case 161: // "constant string"

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< std::string > (); }
#line 393 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 162: // "integer"

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 400 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 163: // "floating point"

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< double > (); }
#line 407 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 164: // "boolean"

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< bool > (); }
#line 414 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 180: // value

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 421 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 184: // map_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 428 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 222: // socket_type

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 435 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 225: // outbound_interface_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 442 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 247: // db_type

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 449 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 329: // hr_mode

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 456 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 477: // ncr_protocol_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 463 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 485: // replace_client_name_value

#line 240 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 470 "dhcp4_parser.cc" // lalr1.cc:635
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  Dhcp4Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  Dhcp4Parser::yypop_ (unsigned n)
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

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
        try
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
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
    yypush_ ("Shifting", yyn, yyla);
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
      case 180: // value
      case 184: // map_value
      case 222: // socket_type
      case 225: // outbound_interface_value
      case 247: // db_type
      case 329: // hr_mode
      case 477: // ncr_protocol_value
      case 485: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 164: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 163: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 162: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 161: // "constant string"
        yylhs.value.build< std::string > ();
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
      try
        {
          switch (yyn)
            {
  case 2:
#line 249 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 715 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 250 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.CONFIG; }
#line 721 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 251 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP4; }
#line 727 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 252 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 733 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 253 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.SUBNET4; }
#line 739 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 254 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.POOLS; }
#line 745 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 255 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 751 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 256 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP4; }
#line 757 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 257 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 763 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 258 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 769 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 22:
#line 259 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 775 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 260 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 781 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 261 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.LOGGING; }
#line 787 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 28:
#line 269 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 793 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 29:
#line 270 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 799 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 271 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 805 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 31:
#line 272 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 811 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 32:
#line 273 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 274 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 823 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 34:
#line 275 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 829 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 35:
#line 278 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 36:
#line 283 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 37:
#line 288 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 38:
#line 294 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 865 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 41:
#line 301 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 874 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 42:
#line 305 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 884 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 43:
#line 312 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 893 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 44:
#line 315 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // list parsing complete. Put any sanity checking here
}
#line 901 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 47:
#line 323 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 48:
#line 327 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 919 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 49:
#line 334 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // List parsing about to start
}
#line 927 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 50:
#line 336 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 936 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 53:
#line 345 "dhcp4_parser.yy" // lalr1.cc:856
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 945 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 54:
#line 349 "dhcp4_parser.yy" // lalr1.cc:856
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 954 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 55:
#line 360 "dhcp4_parser.yy" // lalr1.cc:856
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 965 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 56:
#line 370 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 57:
#line 375 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 989 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 66:
#line 399 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1002 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 67:
#line 406 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 68:
#line 414 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 69:
#line 418 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No global parameter is required
    // parsing completed
}
#line 1031 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 101:
#line 460 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1040 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 102:
#line 465 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1049 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 103:
#line 470 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1058 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 104:
#line 475 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1067 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 105:
#line 480 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1076 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 106:
#line 485 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 107:
#line 491 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1096 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 108:
#line 496 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 118:
#line 515 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 119:
#line 519 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 120:
#line 524 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1136 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 121:
#line 529 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1145 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 122:
#line 534 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 123:
#line 536 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 124:
#line 541 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1168 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 125:
#line 542 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1174 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 126:
#line 545 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1182 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 127:
#line 547 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 128:
#line 552 "dhcp4_parser.yy" // lalr1.cc:856
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 129:
#line 554 "dhcp4_parser.yy" // lalr1.cc:856
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1207 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 130:
#line 558 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1216 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 131:
#line 564 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1227 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 132:
#line 569 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 133:
#line 576 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 134:
#line 581 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1258 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 138:
#line 591 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 139:
#line 593 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 1286 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 140:
#line 609 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1297 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 141:
#line 614 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1308 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 142:
#line 621 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 143:
#line 626 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1328 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 148:
#line 639 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 149:
#line 643 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1348 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 170:
#line 673 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 171:
#line 675 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1365 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 172:
#line 680 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1371 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 173:
#line 681 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1377 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 174:
#line 682 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1383 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 175:
#line 683 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1389 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 176:
#line 686 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 177:
#line 688 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1407 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 178:
#line 694 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 179:
#line 696 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1425 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 180:
#line 702 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 181:
#line 704 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1443 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 182:
#line 710 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 183:
#line 715 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 184:
#line 717 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 185:
#line 723 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 186:
#line 728 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 187:
#line 733 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1497 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 188:
#line 738 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 189:
#line 743 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1515 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 190:
#line 748 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 191:
#line 753 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 192:
#line 758 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 193:
#line 760 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 194:
#line 766 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 195:
#line 768 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 196:
#line 774 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 197:
#line 779 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1587 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 198:
#line 784 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 199:
#line 789 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 207:
#line 805 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 208:
#line 810 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 209:
#line 815 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 210:
#line 820 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1643 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 211:
#line 825 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 212:
#line 830 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 213:
#line 835 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 218:
#line 848 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1682 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 219:
#line 852 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 220:
#line 858 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 221:
#line 862 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1712 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 227:
#line 877 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 228:
#line 879 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1730 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 229:
#line 885 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 230:
#line 887 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 231:
#line 893 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 232:
#line 898 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1768 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 241:
#line 916 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1777 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 242:
#line 921 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1786 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 243:
#line 926 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1795 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 244:
#line 931 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1804 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 245:
#line 936 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 246:
#line 941 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1822 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 247:
#line 949 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 248:
#line 954 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 253:
#line 974 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1852 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 254:
#line 978 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 1878 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 255:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1888 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 256:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 283:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1906 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 284:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1916 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 285:
#line 1050 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 286:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 287:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1942 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 288:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1952 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 289:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1960 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 290:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1970 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 291:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1978 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 292:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 293:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1996 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 294:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2006 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 295:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2017 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 296:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2026 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 297:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 298:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2043 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 299:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2049 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 300:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2055 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 301:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2061 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 302:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2067 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 303:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2076 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 304:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 305:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2096 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 306:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 311:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 312:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 333:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2134 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 334:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 335:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 336:
#line 1197 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 341:
#line 1213 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 342:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2182 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 343:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2192 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 344:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 360:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 362:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 363:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 364:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 365:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 366:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 367:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 369:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 370:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 371:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 372:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 373:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 378:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 379:
#line 1342 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 380:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 381:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 396:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 397:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 400:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 401:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 402:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 403:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 408:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2418 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 409:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 410:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 411:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2448 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 421:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 422:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 423:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 424:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 2501 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 425:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2509 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 426:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 2538 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 427:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 428:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2558 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 433:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 434:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2577 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 435:
#line 1555 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2587 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 436:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2596 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 456:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 457:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2614 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 458:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 459:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2632 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 460:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 461:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2650 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 462:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 463:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2668 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 464:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2679 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 465:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2688 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 466:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 467:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2706 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 468:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 469:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2724 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 470:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 471:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2742 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 472:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 473:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2760 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 474:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 475:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2778 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 476:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 477:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2796 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 478:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 479:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2816 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 480:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2827 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 481:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 484:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2847 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 485:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 488:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 489:
#line 1728 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 506:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 507:
#line 1759 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2894 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 508:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2903 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 509:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2912 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 510:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 511:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2932 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 519:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 520:
#line 1804 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 521:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 522:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 523:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2979 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 524:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2990 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 525:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3000 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 526:
#line 1836 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3010 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 548:
#line 1867 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3019 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 549:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3027 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 550:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3037 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 551:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3045 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 552:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3055 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 553:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3064 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 554:
#line 1893 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3072 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 555:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3082 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 556:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3091 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 557:
#line 1906 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3100 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 558:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3108 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 559:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3117 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 560:
#line 1919 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3123 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 561:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3129 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 562:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 563:
#line 1925 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3147 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 564:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3156 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 565:
#line 1936 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3165 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 566:
#line 1941 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3174 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 567:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3182 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 568:
#line 1948 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3191 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 569:
#line 1954 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3199 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 570:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3207 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 571:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3215 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 572:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3223 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 573:
#line 1966 "dhcp4_parser.yy" // lalr1.cc:856
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3232 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 574:
#line 1972 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 575:
#line 1974 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3250 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 576:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 577:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3268 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 578:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3276 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 579:
#line 1990 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3286 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 580:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3294 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 581:
#line 2001 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3303 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 582:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 583:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3320 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 584:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3328 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 585:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3337 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 586:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3348 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 587:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3357 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 588:
#line 2035 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3367 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 589:
#line 2039 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 3375 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 593:
#line 2055 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3386 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 594:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3395 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 597:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3405 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 598:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 3413 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 608:
#line 2093 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3422 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 609:
#line 2098 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3430 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 610:
#line 2100 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3440 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 611:
#line 2106 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3451 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 612:
#line 2111 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 615:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3470 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 616:
#line 2124 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 3478 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 623:
#line 2138 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3486 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 624:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3496 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 625:
#line 2146 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3505 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 626:
#line 2151 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3514 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 627:
#line 2156 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3523 "dhcp4_parser.cc" // lalr1.cc:856
    break;


#line 3527 "dhcp4_parser.cc" // lalr1.cc:856
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
      yypush_ ("Shifting", error_token);
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
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
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


  const short int Dhcp4Parser::yypact_ninf_ = -774;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     317,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,    35,    33,    36,    69,    73,    75,
      77,    81,    99,   101,   120,   148,   170,   176,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,    33,  -128,    24,    89,    47,   181,
     231,   202,     7,   152,    61,   -56,   425,   -59,  -774,   180,
     190,   199,   205,   214,  -774,  -774,  -774,  -774,  -774,   217,
    -774,    49,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     219,   225,  -774,  -774,  -774,  -774,  -774,  -774,   245,   248,
     280,   281,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   287,  -774,  -774,  -774,    64,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     294,  -774,    65,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,   313,   314,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,    71,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   128,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     264,   305,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   312,  -774,  -774,   320,  -774,  -774,
    -774,   333,  -774,  -774,   330,   336,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   364,
     365,  -774,  -774,  -774,  -774,   340,   357,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   141,
    -774,  -774,  -774,   368,  -774,  -774,   369,  -774,   370,   373,
    -774,  -774,   376,   377,   386,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   149,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   156,  -774,  -774,  -774,    33,    33,  -774,   206,   389,
     390,   392,   393,   396,  -774,    24,  -774,   398,   399,   241,
     242,   406,   407,   408,   410,   412,   413,   246,   256,   257,
     258,   418,   419,   422,   424,   429,   431,   432,   433,   450,
     451,   452,   267,   453,   454,    89,  -774,   455,   456,   457,
     299,    47,  -774,   458,   474,   475,   476,   477,   478,   321,
     324,   480,   481,   483,   485,   181,  -774,   486,   231,  -774,
     488,   489,   490,   491,   492,   495,   496,   497,  -774,   202,
    -774,   498,   500,   345,   502,   504,   505,   346,  -774,   152,
     509,   350,   351,  -774,    61,   512,   513,    45,  -774,   354,
     515,   516,   359,   518,   366,   367,   521,   523,   371,   372,
     374,   526,   527,   528,   529,   425,  -774,   530,   -59,  -774,
    -774,  -774,   549,   547,   548,    33,    33,    33,  -774,   554,
     555,  -774,  -774,   395,   402,   403,   559,   560,   563,  -774,
    -774,  -774,  -774,   564,   565,   566,   567,   568,   415,   569,
     572,   573,   574,   575,  -774,   576,   577,  -774,   580,   175,
     183,  -774,  -774,   420,   426,   427,   584,   430,   434,  -774,
    -774,    17,   580,   435,   583,  -774,   436,  -774,   580,   437,
     438,   439,   440,   441,   442,   443,  -774,   444,   445,  -774,
     446,   447,   448,  -774,  -774,   449,  -774,  -774,  -774,   459,
      33,  -774,  -774,   460,   461,  -774,   462,  -774,  -774,    26,
     463,  -774,  -774,  -774,   150,   464,   465,   466,  -774,   588,
    -774,    33,    89,   -59,  -774,  -774,  -774,    47,   552,  -774,
    -774,  -774,   404,   404,   587,   604,   605,   606,   607,  -774,
    -774,  -774,   151,   608,   609,   610,   -13,   -26,   425,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     611,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     112,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   612,  -774,   184,   208,   227,  -774,
     259,  -774,  -774,  -774,  -774,  -774,  -774,   620,   624,   625,
     626,   627,  -774,  -774,   628,   629,   630,   631,   632,  -774,
     268,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   270,
    -774,   633,   634,  -774,  -774,   635,   637,  -774,  -774,   636,
     640,  -774,  -774,   638,   642,  -774,  -774,   641,   643,  -774,
    -774,  -774,  -774,  -774,  -774,    52,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,    58,  -774,  -774,   644,   645,  -774,  -774,
     646,   648,  -774,   649,   650,   651,   652,   653,   654,   297,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   298,  -774,  -774,  -774,   304,   499,  -774,   655,
     656,  -774,  -774,  -774,  -774,   657,  -774,   104,  -774,  -774,
    -774,  -774,   658,   552,  -774,   659,   660,   662,   663,   487,
     416,   506,   507,   508,   665,   668,   511,   514,   517,   519,
     510,   404,  -774,  -774,   404,  -774,   587,   181,  -774,   604,
     152,  -774,   605,    61,  -774,   606,    78,  -774,   607,   151,
    -774,   263,   608,  -774,   202,  -774,   609,   -56,  -774,   610,
     520,   522,   524,   525,   531,   532,   -13,  -774,   671,   673,
     -26,  -774,  -774,  -774,   672,   677,   231,  -774,   611,   679,
    -774,   107,   612,  -774,   534,  -774,   352,   535,   536,   537,
    -774,  -774,  -774,  -774,  -774,   538,   539,  -774,  -774,  -774,
    -774,  -774,  -774,   322,  -774,   323,  -774,   680,  -774,   681,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   325,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   686,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   683,   682,  -774,  -774,  -774,  -774,
    -774,   684,  -774,   337,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   540,   541,  -774,  -774,   542,   344,  -774,   580,
    -774,   700,  -774,  -774,  -774,  -774,  -774,   356,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,    78,  -774,
     701,   543,  -774,   263,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   702,   546,   705,   107,  -774,  -774,   550,  -774,  -774,
     707,  -774,   553,  -774,  -774,   703,  -774,  -774,   162,  -774,
     121,   703,  -774,  -774,   709,   711,   712,   363,  -774,  -774,
    -774,  -774,  -774,  -774,   713,   556,   557,   561,   121,  -774,
     590,  -774,  -774,  -774,  -774,  -774
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   118,     9,   255,    11,   410,    13,
     435,    15,   335,    17,   343,    19,   380,    21,   220,    23,
     525,    25,   588,    27,    45,    39,     0,     0,     0,     0,
       0,   437,     0,   345,   382,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   586,   580,   582,   584,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   107,   133,
       0,     0,   456,   458,   460,   131,   140,   142,     0,     0,
       0,     0,   247,   333,   372,   305,   423,   425,   198,   484,
     427,   212,   231,     0,   510,   523,   100,     0,    70,    72,
      73,    74,    75,    91,    92,    78,    79,    98,    80,    81,
      82,    86,    87,    76,    77,    84,    85,    96,    97,    99,
      93,    94,    95,    83,    88,    89,    90,   120,   122,   126,
       0,   117,     0,   109,   111,   112,   113,   114,   115,   116,
     285,   287,   289,   402,   283,   291,     0,     0,   297,   295,
     293,   480,   282,   259,   260,   261,   273,     0,   257,   264,
     277,   278,   279,   265,   268,   269,   271,   266,   267,   262,
     263,   280,   281,   270,   274,   275,   276,   272,   421,   420,
     416,   417,   415,     0,   412,   414,   418,   419,   478,   466,
     468,   472,   470,   476,   474,   462,   455,   449,   453,   454,
       0,   438,   439,   450,   451,   452,   446,   441,   447,   443,
     444,   445,   448,   442,     0,   362,   183,     0,   366,   364,
     369,     0,   358,   359,     0,   346,   347,   349,   361,   350,
     351,   352,   368,   353,   354,   355,   356,   357,   396,     0,
       0,   394,   395,   398,   399,     0,   383,   384,   386,   387,
     388,   389,   390,   391,   392,   393,   227,   229,   224,     0,
     222,   225,   226,     0,   549,   551,     0,   554,     0,     0,
     558,   562,     0,     0,     0,   567,   574,   576,   578,   547,
     545,   546,     0,   527,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     593,     0,   590,   592,    44,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    55,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,   119,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   256,     0,     0,   411,
       0,     0,     0,     0,     0,     0,     0,     0,   436,     0,
     336,     0,     0,     0,     0,     0,     0,     0,   344,     0,
       0,     0,     0,   381,     0,     0,     0,     0,   221,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   526,     0,     0,   589,
      48,    41,     0,     0,     0,     0,     0,     0,    59,     0,
       0,   105,   106,     0,     0,     0,     0,     0,     0,   101,
     102,   103,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   509,     0,     0,    71,     0,     0,
       0,   130,   110,     0,     0,     0,     0,     0,     0,   303,
     304,     0,     0,     0,     0,   258,     0,   413,     0,     0,
       0,     0,     0,     0,     0,     0,   440,     0,     0,   360,
       0,     0,     0,   371,   348,     0,   400,   401,   385,     0,
       0,   223,   548,     0,     0,   553,     0,   556,   557,     0,
       0,   564,   565,   566,     0,     0,     0,     0,   528,     0,
     591,     0,     0,     0,   581,   583,   585,     0,     0,   457,
     459,   461,     0,     0,   144,   249,   337,   374,   307,    38,
     424,   426,     0,     0,   429,   214,     0,     0,     0,    49,
     121,   124,   125,   123,   128,   129,   127,   286,   288,   290,
     404,   284,   292,   299,   300,   301,   302,   298,   296,   294,
       0,   422,   479,   467,   469,   473,   471,   477,   475,   463,
     363,   184,   367,   365,   370,   397,   228,   230,   550,   552,
     555,   560,   561,   559,   563,   569,   570,   571,   572,   573,
     568,   575,   577,   579,     0,    42,     0,     0,     0,   138,
       0,   135,   137,   170,   176,   178,   180,     0,     0,     0,
       0,     0,   192,   194,     0,     0,     0,     0,     0,   169,
       0,   150,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   165,   166,   167,   162,   168,   163,   164,     0,
     148,     0,   145,   146,   253,     0,   250,   251,   341,     0,
     338,   339,   378,     0,   375,   376,   311,     0,   308,   309,
     207,   208,   209,   210,   211,     0,   200,   202,   203,   204,
     205,   206,   488,     0,   486,   433,     0,   430,   431,   218,
       0,   215,   216,     0,     0,     0,     0,     0,     0,     0,
     233,   235,   236,   237,   238,   239,   240,   519,   521,   518,
     516,   517,     0,   512,   514,   515,     0,    51,   408,     0,
     405,   406,   464,   482,   483,     0,   597,     0,   595,    67,
     587,   108,     0,     0,   134,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   141,     0,   143,     0,     0,   248,     0,
     345,   334,     0,   382,   373,     0,     0,   306,     0,     0,
     199,   490,     0,   485,   437,   428,     0,     0,   213,     0,
       0,     0,     0,     0,     0,     0,     0,   232,     0,     0,
       0,   511,   524,    53,     0,    52,     0,   403,     0,     0,
     481,     0,     0,   594,     0,   136,     0,     0,     0,     0,
     182,   185,   186,   187,   188,     0,     0,   196,   197,   189,
     190,   191,   151,     0,   147,     0,   252,     0,   340,     0,
     377,   332,   329,   318,   319,   321,   315,   316,   317,   327,
     328,   326,     0,   313,   320,   330,   331,   322,   323,   324,
     325,   310,   201,   506,     0,   504,   505,   497,   498,   502,
     503,   499,   500,   501,     0,   491,   492,   494,   495,   496,
     487,     0,   432,     0,   217,   241,   242,   243,   244,   245,
     246,   234,     0,     0,   513,    50,     0,     0,   407,     0,
     611,     0,   609,   607,   601,   605,   606,     0,   599,   603,
     604,   602,   596,   139,   172,   173,   174,   175,   171,   177,
     179,   181,   193,   195,   149,   254,   342,   379,     0,   312,
       0,     0,   489,     0,   434,   219,   520,   522,    54,   409,
     465,     0,     0,     0,     0,   598,   314,     0,   508,   493,
       0,   608,     0,   600,   507,     0,   610,   615,     0,   613,
       0,     0,   612,   623,     0,     0,     0,     0,   617,   619,
     620,   621,   622,   614,     0,     0,     0,     0,     0,   616,
       0,   625,   626,   627,   618,   624
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,   -25,  -774,   161,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -481,  -774,  -774,  -774,
     -66,  -774,  -774,  -774,   380,  -774,  -774,  -774,  -774,   166,
     347,   -44,   -41,   -39,  -774,  -774,    -7,  -774,  -774,   169,
     348,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,   -35,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,   -49,  -774,  -550,   -47,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
     -37,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   -36,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   -51,  -774,
    -774,  -774,   -46,   341,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   -45,  -774,  -774,  -774,  -774,  -774,  -774,  -773,  -774,
    -774,  -774,   -14,  -774,  -774,  -774,   -18,   383,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -772,  -774,   -64,  -774,
     -52,  -774,  -767,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   -19,  -774,  -774,  -166,   -61,  -774,  -774,  -774,  -774,
    -774,    -9,  -774,  -774,  -774,    -5,  -774,   378,  -774,   -62,
    -774,  -774,  -774,  -774,  -774,   -48,  -774,  -774,  -774,  -774,
    -774,     0,  -774,  -774,  -774,    -4,  -774,  -774,  -774,    -3,
    -774,   362,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   -40,  -774,  -774,  -774,   -34,   397,  -774,
    -774,   -54,  -774,   -20,  -774,   -38,  -774,  -774,  -774,    -8,
    -774,  -774,  -774,    -1,  -774,   400,     6,  -774,    12,  -774,
      18,  -774,   212,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -764,  -774,  -774,  -774,  -774,  -774,    13,  -774,  -774,  -774,
    -136,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,    -2,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   243,   375,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,   271,   379,  -774,
    -774,  -774,     1,  -774,  -774,  -141,  -774,  -774,  -774,  -774,
    -774,  -774,  -156,  -774,  -774,  -170,  -774,  -774,  -774,  -774,
    -774
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   570,
      82,    83,    39,    64,    79,    80,   580,   747,   824,   825,
     659,    41,    66,    91,    92,    93,   339,    43,    67,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   347,   162,
     163,    45,    68,   164,   377,   165,   378,   583,   166,   379,
     586,   167,   136,   354,   137,   348,   640,   641,   642,   762,
     138,   355,   139,   356,   681,   682,   683,   784,   660,   661,
     662,   765,   938,   663,   766,   664,   767,   665,   768,   666,
     667,   412,   668,   669,   670,   671,   672,   673,   674,   675,
     774,   676,   775,   677,   678,   140,   367,   705,   706,   707,
     708,   709,   710,   711,   141,   370,   720,   721,   722,   807,
      59,    75,   289,   290,   291,   425,   292,   426,   142,   371,
     729,   730,   731,   732,   733,   734,   735,   736,   143,   361,
     685,   686,   687,   787,    47,    69,   187,   188,   189,   387,
     190,   383,   191,   384,   192,   385,   193,   388,   194,   393,
     195,   392,   196,   391,   597,   197,   198,   144,   364,   697,
     698,   699,   796,   872,   873,   145,   362,    53,    72,   689,
     690,   691,   790,    55,    73,   254,   255,   256,   257,   258,
     259,   260,   411,   261,   415,   262,   414,   263,   264,   416,
     265,   146,   363,   693,   694,   695,   793,    57,    74,   275,
     276,   277,   278,   279,   420,   280,   281,   282,   283,   200,
     386,   749,   750,   751,   826,    49,    70,   213,   214,   215,
     397,   147,   365,   148,   366,   149,   369,   716,   717,   718,
     804,    51,    71,   230,   231,   232,   150,   351,   151,   352,
     152,   353,   236,   407,   754,   829,   237,   401,   238,   402,
     239,   404,   240,   403,   241,   406,   242,   405,   243,   400,
     207,   394,   755,   153,   368,   713,   714,   801,   894,   895,
     896,   897,   898,   950,   899,   154,   155,   373,   742,   743,
     744,   818,   745,   819,   156,   374,    61,    76,   312,   313,
     314,   315,   430,   316,   431,   317,   318,   433,   319,   320,
     321,   436,   623,   322,   437,   323,   324,   325,   326,   441,
     630,   327,   442,   328,   443,   329,   444,    94,   341,    95,
     342,    96,   343,    97,   340,    63,    77,   331,   332,   333,
     447,   757,   758,   831,   927,   928,   929,   930,   963,   931,
     961,   978,   979,   980,   987,   988,   989,   994,   990,   991,
     992
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   126,   161,   182,   209,   226,   210,   252,   271,   288,
     309,   244,   273,   679,   168,   201,   216,   228,   211,   266,
     284,   598,   310,   867,   868,   183,   274,   602,   184,   871,
     185,   203,   880,    81,    84,    28,   253,   272,    29,    78,
      30,   621,    31,    40,   286,   287,   116,   117,   169,   202,
     217,   229,   345,   267,   285,   799,   311,   346,   800,   157,
     158,   802,   186,   159,   803,   113,   160,   375,   381,   199,
     212,   227,   376,   382,   395,   204,    42,   233,   330,   396,
      44,   205,    46,   234,    48,   737,   738,   206,    50,   235,
     723,   724,   725,   726,   727,   728,   593,   594,   595,   596,
      98,   101,   102,   103,   104,    89,    52,   832,    54,    99,
     833,   100,   101,   102,   103,   104,   105,   106,   107,   116,
     117,   246,   268,   247,   248,   269,   270,    56,   108,   109,
     110,   398,   112,   116,   117,    89,   399,   114,   246,   108,
     109,   110,   111,   112,   427,   286,   287,   113,   114,   428,
     116,   117,   445,   175,   622,    58,   178,   446,   115,   448,
      85,   116,   117,   179,   449,   981,   180,   246,   982,    86,
      87,    88,   118,   119,   181,   867,   868,    60,   120,   116,
     117,   871,   245,    62,   880,    89,   334,   375,   121,   581,
     582,   122,   759,   335,    32,    33,    34,    35,   123,   124,
     584,   585,   125,   336,   101,   102,   103,   104,    89,   225,
     752,   448,   246,   337,   247,   248,   760,   338,   249,   250,
     251,   344,    89,   349,   116,   117,   102,   103,   104,   350,
     381,   108,   109,   110,   853,   761,   170,   171,   172,    89,
     114,   700,   701,   702,   703,   920,   704,   921,   922,   357,
      89,   173,   358,   116,   117,   174,   175,   176,   177,   178,
     983,   114,   763,   984,   985,   986,   179,   764,    89,   180,
     120,   781,   408,   781,   116,   117,   782,   181,   783,    90,
     625,   626,   627,   628,   359,   360,   218,   102,   103,   104,
     114,   372,   219,   220,   221,   222,   223,   224,   380,   225,
     816,   820,   208,   116,   117,   817,   821,   445,   409,   126,
     450,   451,   822,    89,   629,   161,   179,   389,   390,   180,
     410,   113,   114,   246,   413,   781,   395,   168,   948,   182,
     944,   945,   209,   949,   210,   116,   117,   417,   418,   419,
     427,   201,    89,   226,   216,   955,   211,   398,   423,   883,
     884,   183,   959,   252,   184,   228,   185,   203,   271,   964,
     424,   169,   273,    89,   965,   266,   998,   452,   421,   422,
     284,   999,   429,   432,   434,   202,   274,   435,   217,   309,
     438,   439,   253,   934,   935,   936,   937,   272,   186,   229,
     440,   310,    89,   453,   454,   199,   455,   456,   212,   267,
     457,   204,   459,   460,   285,   461,   462,   205,   469,   227,
     463,   464,   465,   206,   466,   233,   467,   468,   470,   471,
     472,   234,   473,   474,    89,   311,   475,   235,   476,   484,
     554,   555,   556,   477,   643,   478,   479,   480,   960,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   481,   482,   483,   485,   486,   488,
     489,   490,   493,   491,   246,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   494,   495,
     496,   497,   498,   499,   501,   502,   126,   503,   500,   504,
     506,   161,   508,   509,   510,   511,   512,   116,   117,   513,
     514,   515,   517,   168,   518,   617,   520,   519,   521,   522,
     523,   739,   309,   525,   526,   527,   529,   530,   532,   533,
     534,   535,   536,   740,   310,   539,   635,   540,   537,   538,
     544,   545,   546,   547,   549,   541,   542,   169,   543,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   551,   552,   553,   559,   741,   311,   307,
     308,   557,   558,   560,   561,    89,   562,   563,   564,   565,
     566,   567,   568,   639,   572,    30,   571,   573,   574,   575,
     841,   587,   576,   577,   578,   579,    89,   588,   589,   590,
     600,   591,   624,   634,   680,   592,   599,   601,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   684,   688,   692,   696,   712,   715,   719,   748,   756,
     616,   618,   619,   620,   769,   631,   632,   633,   770,   771,
     772,   773,   776,   777,   778,   779,   780,   786,   569,   785,
     789,   788,   791,   792,   794,   795,   798,   797,   806,   840,
     805,   809,   808,   810,   811,   812,   813,   814,   815,   828,
     823,   827,   834,   836,   837,   830,   838,   839,   842,   845,
     844,   843,   846,   847,   851,   912,   848,   913,   915,   849,
     916,   850,   905,   919,   906,   953,   907,   908,   946,   947,
     951,   952,   954,   909,   910,   933,   939,   940,   941,   942,
     943,   956,   957,   958,   962,   967,   970,   968,   971,   972,
     977,   974,   975,   995,   976,   996,   997,  1000,   636,  1002,
    1001,   182,   487,  1003,   252,   458,   638,   271,   835,   492,
     861,   273,   869,   201,   852,   885,   266,   854,   226,   284,
     887,   288,   875,   183,   870,   274,   184,   889,   185,   203,
     228,  1005,   862,   253,   739,   863,   272,   864,   904,   866,
     209,   903,   210,   882,   886,   923,   740,   202,   531,   855,
     267,   911,   216,   285,   211,   856,   876,   925,   505,   881,
     186,   890,   966,   858,   229,   857,   528,   199,   918,   865,
     859,   860,   917,   204,   924,   507,   874,   524,   902,   205,
     741,   888,   877,   901,   227,   206,   217,   891,   878,   516,
     233,   926,   753,   892,   879,   900,   234,   969,   914,   893,
     548,   746,   235,   973,   637,   993,   212,   550,  1004,     0,
       0,     0,     0,   932,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   861,     0,   869,     0,     0,   885,     0,     0,
       0,     0,   887,     0,   875,     0,   870,     0,   923,   889,
       0,     0,     0,     0,   862,     0,     0,   863,     0,   864,
     925,   866,     0,     0,     0,     0,   886,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   924,   876,     0,
       0,     0,     0,   890,     0,     0,     0,     0,     0,     0,
       0,   865,     0,     0,   926,     0,     0,     0,   874,     0,
       0,     0,     0,   888,   877,     0,     0,     0,     0,   891,
     878,     0,     0,     0,     0,   892,   879,     0,     0,     0,
       0,   893
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    70,    73,    74,    75,
      76,    72,    74,   563,    68,    69,    70,    71,    70,    73,
      74,   502,    76,   796,   796,    69,    74,   508,    69,   796,
      69,    69,   796,   161,    10,     0,    73,    74,     5,    64,
       7,    15,     9,     7,   100,   101,    72,    73,    68,    69,
      70,    71,     3,    73,    74,     3,    76,     8,     6,    12,
      13,     3,    69,    16,     6,    58,    19,     3,     3,    69,
      70,    71,     8,     8,     3,    69,     7,    71,   137,     8,
       7,    69,     7,    71,     7,   111,   112,    69,     7,    71,
     103,   104,   105,   106,   107,   108,    79,    80,    81,    82,
      11,    23,    24,    25,    26,   161,     7,     3,     7,    20,
       6,    22,    23,    24,    25,    26,    27,    28,    29,    72,
      73,    60,    61,    62,    63,    64,    65,     7,    50,    51,
      52,     3,    54,    72,    73,   161,     8,    59,    60,    50,
      51,    52,    53,    54,     3,   100,   101,    58,    59,     8,
      72,    73,     3,    75,   128,     7,    78,     8,    69,     3,
     136,    72,    73,    85,     8,     3,    88,    60,     6,   145,
     146,   147,    83,    84,    96,   948,   948,     7,    89,    72,
      73,   948,    30,     7,   948,   161,     6,     3,    99,    14,
      15,   102,     8,     3,   161,   162,   163,   164,   109,   110,
      17,    18,   113,     4,    23,    24,    25,    26,   161,    97,
      98,     3,    60,     8,    62,    63,     8,     3,    66,    67,
      68,     4,   161,     4,    72,    73,    24,    25,    26,     4,
       3,    50,    51,    52,   784,     8,    55,    56,    57,   161,
      59,    90,    91,    92,    93,   138,    95,   140,   141,     4,
     161,    70,     4,    72,    73,    74,    75,    76,    77,    78,
     139,    59,     3,   142,   143,   144,    85,     8,   161,    88,
      89,     3,     8,     3,    72,    73,     8,    96,     8,   345,
     130,   131,   132,   133,     4,     4,    84,    24,    25,    26,
      59,     4,    90,    91,    92,    93,    94,    95,     4,    97,
       3,     3,    71,    72,    73,     8,     8,     3,     3,   375,
     335,   336,     8,   161,   164,   381,    85,     4,     4,    88,
       8,    58,    59,    60,     4,     3,     3,   381,     3,   395,
       8,     8,   398,     8,   398,    72,    73,     4,     8,     3,
       3,   395,   161,   409,   398,     8,   398,     3,     8,    86,
      87,   395,     8,   419,   395,   409,   395,   395,   424,     3,
       3,   381,   424,   161,     8,   419,     3,   161,     4,     4,
     424,     8,     4,     4,     4,   395,   424,     4,   398,   445,
       4,     4,   419,    31,    32,    33,    34,   424,   395,   409,
       4,   445,   161,     4,     4,   395,     4,     4,   398,   419,
       4,   395,     4,     4,   424,   164,   164,   395,   162,   409,
       4,     4,     4,   395,     4,   409,     4,     4,   162,   162,
     162,   409,     4,     4,   161,   445,     4,   409,     4,   162,
     455,   456,   457,     4,    30,     4,     4,     4,   919,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   164,    60,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,     4,     4,
       4,     4,     4,   162,     4,     4,   552,     4,   164,     4,
       4,   557,     4,     4,     4,     4,     4,    72,    73,     4,
       4,     4,     4,   557,     4,   530,     4,   162,     4,     4,
     164,   577,   578,     4,   164,   164,     4,     4,   164,     4,
       4,   162,     4,   577,   578,     4,   551,     4,   162,   162,
       4,     4,     4,     4,     4,   164,   164,   557,   164,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     4,     7,     7,   161,   577,   578,   134,
     135,     7,     7,   161,   161,   161,     7,     7,     5,     5,
       5,     5,     5,    21,     5,     7,   161,     5,     5,     5,
     164,   161,     7,     7,     7,     5,   161,   161,   161,     5,
       7,   161,   129,     5,     7,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,     7,     7,     7,     7,     7,     7,     7,     7,     7,
     161,   161,   161,   161,     4,   161,   161,   161,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   477,     6,
       3,     6,     6,     3,     6,     3,     3,     6,     3,   162,
       6,     3,     6,     4,     4,     4,     4,     4,     4,     3,
     161,     6,     4,     4,     4,     8,     4,     4,   162,     4,
     162,   164,     4,   162,   164,     4,   162,     4,     6,   162,
       3,   162,   162,     4,   162,     3,   162,   162,     8,     8,
       4,     8,     8,   162,   162,   161,   161,   161,   161,   161,
     161,   161,   161,   161,     4,     4,     4,   164,   162,     4,
       7,   161,     5,     4,   161,     4,     4,     4,   552,   162,
     164,   787,   375,   162,   790,   345,   557,   793,   763,   381,
     796,   793,   796,   787,   781,   801,   790,   786,   804,   793,
     801,   807,   796,   787,   796,   793,   787,   801,   787,   787,
     804,   161,   796,   790,   820,   796,   793,   796,   809,   796,
     826,   807,   826,   799,   801,   831,   820,   787,   427,   787,
     790,   816,   826,   793,   826,   789,   796,   831,   395,   798,
     787,   801,   948,   792,   804,   790,   424,   787,   828,   796,
     793,   795,   826,   787,   831,   398,   796,   419,   806,   787,
     820,   801,   796,   804,   804,   787,   826,   801,   796,   409,
     804,   831,   600,   801,   796,   802,   804,   953,   820,   801,
     445,   578,   804,   964,   553,   981,   826,   448,   998,    -1,
      -1,    -1,    -1,   832,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   948,    -1,   948,    -1,    -1,   953,    -1,    -1,
      -1,    -1,   953,    -1,   948,    -1,   948,    -1,   964,   953,
      -1,    -1,    -1,    -1,   948,    -1,    -1,   948,    -1,   948,
     964,   948,    -1,    -1,    -1,    -1,   953,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   964,   948,    -1,
      -1,    -1,    -1,   953,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   948,    -1,    -1,   964,    -1,    -1,    -1,   948,    -1,
      -1,    -1,    -1,   953,   948,    -1,    -1,    -1,    -1,   953,
     948,    -1,    -1,    -1,    -1,   953,   948,    -1,    -1,    -1,
      -1,   953
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,     0,     5,
       7,     9,   161,   162,   163,   164,   180,   181,   182,   187,
       7,   196,     7,   202,     7,   216,     7,   309,     7,   390,
       7,   406,     7,   342,     7,   348,     7,   372,     7,   285,
       7,   461,     7,   500,   188,   183,   197,   203,   217,   310,
     391,   407,   343,   349,   373,   286,   462,   501,   180,   189,
     190,   161,   185,   186,    10,   136,   145,   146,   147,   161,
     195,   198,   199,   200,   492,   494,   496,   498,    11,    20,
      22,    23,    24,    25,    26,    27,    28,    29,    50,    51,
      52,    53,    54,    58,    59,    69,    72,    73,    83,    84,
      89,    99,   102,   109,   110,   113,   195,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   227,   229,   235,   237,
     270,   279,   293,   303,   332,   340,   366,   396,   398,   400,
     411,   413,   415,   438,   450,   451,   459,    12,    13,    16,
      19,   195,   214,   215,   218,   220,   223,   226,   396,   398,
      55,    56,    57,    70,    74,    75,    76,    77,    78,    85,
      88,    96,   195,   206,   207,   208,   211,   311,   312,   313,
     315,   317,   319,   321,   323,   325,   327,   330,   331,   366,
     384,   396,   398,   400,   411,   413,   415,   435,    71,   195,
     323,   325,   366,   392,   393,   394,   396,   398,    84,    90,
      91,    92,    93,    94,    95,    97,   195,   366,   396,   398,
     408,   409,   410,   411,   413,   415,   417,   421,   423,   425,
     427,   429,   431,   433,   340,    30,    60,    62,    63,    66,
      67,    68,   195,   255,   350,   351,   352,   353,   354,   355,
     356,   358,   360,   362,   363,   365,   396,   398,    61,    64,
      65,   195,   255,   354,   360,   374,   375,   376,   377,   378,
     380,   381,   382,   383,   396,   398,   100,   101,   195,   287,
     288,   289,   291,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   134,   135,   195,
     396,   398,   463,   464,   465,   466,   468,   470,   471,   473,
     474,   475,   478,   480,   481,   482,   483,   486,   488,   490,
     137,   502,   503,   504,     6,     3,     4,     8,     3,   201,
     499,   493,   495,   497,     4,     3,     8,   213,   230,     4,
       4,   412,   414,   416,   228,   236,   238,     4,     4,     4,
       4,   304,   341,   367,   333,   397,   399,   271,   439,   401,
     280,   294,     4,   452,   460,     3,     8,   219,   221,   224,
       4,     3,     8,   316,   318,   320,   385,   314,   322,     4,
       4,   328,   326,   324,   436,     3,     8,   395,     3,     8,
     434,   422,   424,   428,   426,   432,   430,   418,     8,     3,
       8,   357,   256,     4,   361,   359,   364,     4,     8,     3,
     379,     4,     4,     8,     3,   290,   292,     3,     8,     4,
     467,   469,     4,   472,     4,     4,   476,   479,     4,     4,
       4,   484,   487,   489,   491,     3,     8,   505,     3,     8,
     180,   180,   161,     4,     4,     4,     4,     4,   199,     4,
       4,   164,   164,     4,     4,     4,     4,     4,     4,   162,
     162,   162,   162,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   162,     4,     4,   205,     4,     4,
       4,   164,   215,     4,     4,     4,     4,     4,     4,   162,
     164,     4,     4,     4,     4,   312,     4,   393,     4,     4,
       4,     4,     4,     4,     4,     4,   410,     4,     4,   162,
       4,     4,     4,   164,   352,     4,   164,   164,   376,     4,
       4,   288,   164,     4,     4,   162,     4,   162,   162,     4,
       4,   164,   164,   164,     4,     4,     4,     4,   464,     4,
     503,     4,     7,     7,   180,   180,   180,     7,     7,   161,
     161,   161,     7,     7,     5,     5,     5,     5,     5,   182,
     184,   161,     5,     5,     5,     5,     7,     7,     7,     5,
     191,    14,    15,   222,    17,    18,   225,   161,   161,   161,
       5,   161,   161,    79,    80,    81,    82,   329,   191,   161,
       7,   161,   191,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   180,   161,   161,
     161,    15,   128,   477,   129,   130,   131,   132,   133,   164,
     485,   161,   161,   161,     5,   180,   204,   502,   214,    21,
     231,   232,   233,    30,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,   195,
     243,   244,   245,   248,   250,   252,   254,   255,   257,   258,
     259,   260,   261,   262,   263,   264,   266,   268,   269,   243,
       7,   239,   240,   241,     7,   305,   306,   307,     7,   344,
     345,   346,     7,   368,   369,   370,     7,   334,   335,   336,
      90,    91,    92,    93,    95,   272,   273,   274,   275,   276,
     277,   278,     7,   440,   441,     7,   402,   403,   404,     7,
     281,   282,   283,   103,   104,   105,   106,   107,   108,   295,
     296,   297,   298,   299,   300,   301,   302,   111,   112,   195,
     396,   398,   453,   454,   455,   457,   463,   192,     7,   386,
     387,   388,    98,   417,   419,   437,     7,   506,   507,     8,
       8,     8,   234,     3,     8,   246,   249,   251,   253,     4,
       4,     4,     4,     4,   265,   267,     4,     4,     4,     4,
       4,     3,     8,     8,   242,     6,     3,   308,     6,     3,
     347,     6,     3,   371,     6,     3,   337,     6,     3,     3,
       6,   442,     3,     6,   405,     6,     3,   284,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   456,   458,
       3,     8,     8,   161,   193,   194,   389,     6,     3,   420,
       8,   508,     3,     6,     4,   232,     4,     4,     4,     4,
     162,   164,   162,   164,   162,     4,     4,   162,   162,   162,
     162,   164,   244,   243,   241,   311,   307,   350,   346,   374,
     370,   195,   206,   207,   208,   211,   255,   303,   321,   323,
     325,   327,   338,   339,   366,   396,   398,   411,   413,   415,
     435,   336,   273,    86,    87,   195,   255,   340,   366,   396,
     398,   411,   413,   415,   443,   444,   445,   446,   447,   449,
     441,   408,   404,   287,   283,   162,   162,   162,   162,   162,
     162,   296,     4,     4,   454,     6,     3,   392,   388,     4,
     138,   140,   141,   195,   255,   396,   398,   509,   510,   511,
     512,   514,   507,   161,    31,    32,    33,    34,   247,   161,
     161,   161,   161,   161,     8,     8,     8,     8,     3,     8,
     448,     4,     8,     3,     8,     8,   161,   161,   161,     8,
     191,   515,     4,   513,     3,     8,   339,     4,   164,   445,
       4,   162,     4,   510,   161,     5,   161,     7,   516,   517,
     518,     3,     6,   139,   142,   143,   144,   519,   520,   521,
     523,   524,   525,   517,   522,     4,     4,     4,     3,     8,
       4,   164,   162,   162,   520,   161
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   165,   167,   166,   168,   166,   169,   166,   170,   166,
     171,   166,   172,   166,   173,   166,   174,   166,   175,   166,
     176,   166,   177,   166,   178,   166,   179,   166,   180,   180,
     180,   180,   180,   180,   180,   181,   183,   182,   184,   185,
     185,   186,   186,   188,   187,   189,   189,   190,   190,   192,
     191,   193,   193,   194,   194,   195,   197,   196,   198,   198,
     199,   199,   199,   199,   199,   199,   201,   200,   203,   202,
     204,   204,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   206,   207,   208,   209,   210,   211,   213,   212,   214,
     214,   215,   215,   215,   215,   215,   215,   215,   217,   216,
     219,   218,   221,   220,   222,   222,   224,   223,   225,   225,
     226,   228,   227,   230,   229,   231,   231,   232,   234,   233,
     236,   235,   238,   237,   239,   239,   240,   240,   242,   241,
     243,   243,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     246,   245,   247,   247,   247,   247,   249,   248,   251,   250,
     253,   252,   254,   256,   255,   257,   258,   259,   260,   261,
     262,   263,   265,   264,   267,   266,   268,   269,   271,   270,
     272,   272,   273,   273,   273,   273,   273,   274,   275,   276,
     277,   278,   280,   279,   281,   281,   282,   282,   284,   283,
     286,   285,   287,   287,   287,   288,   288,   290,   289,   292,
     291,   294,   293,   295,   295,   296,   296,   296,   296,   296,
     296,   297,   298,   299,   300,   301,   302,   304,   303,   305,
     305,   306,   306,   308,   307,   310,   309,   311,   311,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   314,   313,   316,   315,   318,   317,   320,
     319,   322,   321,   324,   323,   326,   325,   328,   327,   329,
     329,   329,   329,   330,   331,   333,   332,   334,   334,   335,
     335,   337,   336,   338,   338,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   341,   340,   343,   342,   344,   344,   345,
     345,   347,   346,   349,   348,   350,   350,   351,   351,   352,
     352,   352,   352,   352,   352,   352,   352,   352,   352,   353,
     354,   355,   357,   356,   359,   358,   361,   360,   362,   364,
     363,   365,   367,   366,   368,   368,   369,   369,   371,   370,
     373,   372,   374,   374,   375,   375,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   377,   379,   378,   380,   381,
     382,   383,   385,   384,   386,   386,   387,   387,   389,   388,
     391,   390,   392,   392,   393,   393,   393,   393,   393,   393,
     393,   395,   394,   397,   396,   399,   398,   401,   400,   402,
     402,   403,   403,   405,   404,   407,   406,   408,   408,   409,
     409,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   412,   411,   414,   413,
     416,   415,   418,   417,   420,   419,   422,   421,   424,   423,
     426,   425,   428,   427,   430,   429,   432,   431,   434,   433,
     436,   435,   437,   437,   439,   438,   440,   440,   442,   441,
     443,   443,   444,   444,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   446,   448,   447,   449,   450,
     452,   451,   453,   453,   454,   454,   454,   454,   454,   456,
     455,   458,   457,   460,   459,   462,   461,   463,   463,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   465,   467,
     466,   469,   468,   470,   472,   471,   473,   474,   476,   475,
     477,   477,   479,   478,   480,   481,   482,   484,   483,   485,
     485,   485,   485,   485,   487,   486,   489,   488,   491,   490,
     493,   492,   495,   494,   497,   496,   499,   498,   501,   500,
     502,   502,   503,   505,   504,   506,   506,   508,   507,   509,
     509,   510,   510,   510,   510,   510,   510,   510,   511,   513,
     512,   515,   514,   516,   516,   518,   517,   519,   519,   520,
     520,   520,   520,   522,   521,   523,   524,   525
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     1,
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
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
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
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
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
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"next-server\"", "\"server-hostname\"", "\"boot-file-name\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
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
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
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
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "value",
  "sub_json", "map2", "$@14", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@15", "list_content", "not_empty_list", "list_strings",
  "$@16", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@17", "global_objects",
  "global_object", "dhcp4_object", "$@18", "sub_dhcp4", "$@19",
  "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@20",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@21", "interfaces_list", "$@22", "dhcp_socket_type", "$@23",
  "socket_type", "outbound_interface", "$@24", "outbound_interface_value",
  "re_detect", "lease_database", "$@25", "sanity_checks", "$@26",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@27",
  "hosts_database", "$@28", "hosts_databases", "$@29", "database_list",
  "not_empty_database_list", "database", "$@30", "database_map_params",
  "database_map_param", "database_type", "$@31", "db_type", "user", "$@32",
  "password", "$@33", "host", "$@34", "port", "name", "$@35", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@36", "keyspace",
  "$@37", "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@38",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@39", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@40",
  "sub_hooks_library", "$@41", "hooks_params", "hooks_param", "library",
  "$@42", "parameters", "$@43", "expired_leases_processing", "$@44",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@45",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@46",
  "sub_subnet4", "$@47", "subnet4_params", "subnet4_param", "subnet",
  "$@48", "subnet_4o6_interface", "$@49", "subnet_4o6_interface_id",
  "$@50", "subnet_4o6_subnet", "$@51", "interface", "$@52", "client_class",
  "$@53", "require_client_classes", "$@54", "reservation_mode", "$@55",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@56",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@57", "shared_network_params", "shared_network_param",
  "option_def_list", "$@58", "sub_option_def_list", "$@59",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@60", "sub_option_def", "$@61",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@62",
  "option_def_record_types", "$@63", "space", "$@64", "option_def_space",
  "option_def_encapsulate", "$@65", "option_def_array", "option_data_list",
  "$@66", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@67", "sub_option_data", "$@68",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@69",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@70", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@71", "sub_pool4", "$@72",
  "pool_params", "pool_param", "pool_entry", "$@73", "user_context",
  "$@74", "comment", "$@75", "reservations", "$@76", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@77", "sub_reservation",
  "$@78", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@79", "server_hostname", "$@80",
  "boot_file_name", "$@81", "ip_address", "$@82", "ip_addresses", "$@83",
  "duid", "$@84", "hw_address", "$@85", "client_id_value", "$@86",
  "circuit_id_value", "$@87", "flex_id_value", "$@88", "hostname", "$@89",
  "reservation_client_classes", "$@90", "relay", "$@91", "relay_map",
  "client_classes", "$@92", "client_classes_list", "client_class_entry",
  "$@93", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@94",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@95",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@96", "control_socket_name", "$@97", "dhcp_ddns", "$@98",
  "sub_dhcp_ddns", "$@99", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@100", "server_ip", "$@101",
  "server_port", "sender_ip", "$@102", "sender_port", "max_queue_size",
  "ncr_protocol", "$@103", "ncr_protocol_value", "ncr_format", "$@104",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@105", "replace_client_name_value",
  "generated_prefix", "$@106", "hostname_char_set", "$@107",
  "hostname_char_replacement", "$@108", "dhcp6_json_object", "$@109",
  "dhcpddns_json_object", "$@110", "control_agent_json_object", "$@111",
  "logging_object", "$@112", "sub_logging", "$@113", "logging_params",
  "logging_param", "loggers", "$@114", "loggers_entries", "logger_entry",
  "$@115", "logger_params", "logger_param", "debuglevel", "severity",
  "$@116", "output_options_list", "$@117", "output_options_list_content",
  "output_entry", "$@118", "output_params_list", "output_params", "output",
  "$@119", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   249,   249,   249,   250,   250,   251,   251,   252,   252,
     253,   253,   254,   254,   255,   255,   256,   256,   257,   257,
     258,   258,   259,   259,   260,   260,   261,   261,   269,   270,
     271,   272,   273,   274,   275,   278,   283,   283,   294,   297,
     298,   301,   305,   312,   312,   319,   320,   323,   327,   334,
     334,   341,   342,   345,   349,   360,   370,   370,   386,   387,
     391,   392,   393,   394,   395,   396,   399,   399,   414,   414,
     423,   424,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   460,   465,   470,   475,   480,   485,   491,   491,   502,
     503,   506,   507,   508,   509,   510,   511,   512,   515,   515,
     524,   524,   534,   534,   541,   542,   545,   545,   552,   554,
     558,   564,   564,   576,   576,   586,   587,   589,   591,   591,
     609,   609,   621,   621,   631,   632,   635,   636,   639,   639,
     649,   650,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     673,   673,   680,   681,   682,   683,   686,   686,   694,   694,
     702,   702,   710,   715,   715,   723,   728,   733,   738,   743,
     748,   753,   758,   758,   766,   766,   774,   779,   784,   784,
     794,   795,   798,   799,   800,   801,   802,   805,   810,   815,
     820,   825,   830,   830,   840,   841,   844,   845,   848,   848,
     858,   858,   868,   869,   870,   873,   874,   877,   877,   885,
     885,   893,   893,   904,   905,   908,   909,   910,   911,   912,
     913,   916,   921,   926,   931,   936,   941,   949,   949,   962,
     963,   966,   967,   974,   974,  1000,  1000,  1011,  1012,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,
    1037,  1038,  1039,  1042,  1042,  1050,  1050,  1058,  1058,  1066,
    1066,  1074,  1074,  1082,  1082,  1090,  1090,  1100,  1100,  1107,
    1108,  1109,  1110,  1113,  1118,  1125,  1125,  1136,  1137,  1141,
    1142,  1145,  1145,  1153,  1154,  1157,  1158,  1159,  1160,  1161,
    1162,  1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,
    1172,  1173,  1174,  1181,  1181,  1194,  1194,  1203,  1204,  1207,
    1208,  1213,  1213,  1228,  1228,  1242,  1243,  1246,  1247,  1250,
    1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,  1259,  1262,
    1264,  1269,  1271,  1271,  1279,  1279,  1287,  1287,  1295,  1297,
    1297,  1305,  1314,  1314,  1326,  1327,  1332,  1333,  1338,  1338,
    1350,  1350,  1362,  1363,  1368,  1369,  1374,  1375,  1376,  1377,
    1378,  1379,  1380,  1381,  1382,  1385,  1387,  1387,  1395,  1397,
    1399,  1404,  1412,  1412,  1424,  1425,  1428,  1429,  1432,  1432,
    1442,  1442,  1452,  1453,  1456,  1457,  1458,  1459,  1460,  1461,
    1462,  1465,  1465,  1473,  1473,  1498,  1498,  1528,  1528,  1538,
    1539,  1542,  1543,  1546,  1546,  1555,  1555,  1564,  1565,  1568,
    1569,  1573,  1574,  1575,  1576,  1577,  1578,  1579,  1580,  1581,
    1582,  1583,  1584,  1585,  1586,  1587,  1590,  1590,  1598,  1598,
    1606,  1606,  1614,  1614,  1622,  1622,  1632,  1632,  1640,  1640,
    1648,  1648,  1656,  1656,  1664,  1664,  1672,  1672,  1680,  1680,
    1693,  1693,  1703,  1704,  1710,  1710,  1720,  1721,  1724,  1724,
    1734,  1735,  1738,  1739,  1742,  1743,  1744,  1745,  1746,  1747,
    1748,  1749,  1750,  1751,  1752,  1755,  1757,  1757,  1765,  1774,
    1781,  1781,  1791,  1792,  1795,  1796,  1797,  1798,  1799,  1802,
    1802,  1810,  1810,  1820,  1820,  1832,  1832,  1842,  1843,  1846,
    1847,  1848,  1849,  1850,  1851,  1852,  1853,  1854,  1855,  1856,
    1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,  1867,  1872,
    1872,  1880,  1880,  1888,  1893,  1893,  1901,  1906,  1911,  1911,
    1919,  1920,  1923,  1923,  1931,  1936,  1941,  1946,  1946,  1954,
    1957,  1960,  1963,  1966,  1972,  1972,  1980,  1980,  1988,  1988,
    1999,  1999,  2006,  2006,  2013,  2013,  2025,  2025,  2035,  2035,
    2046,  2047,  2051,  2055,  2055,  2067,  2068,  2072,  2072,  2080,
    2081,  2084,  2085,  2086,  2087,  2088,  2089,  2090,  2093,  2098,
    2098,  2106,  2106,  2116,  2117,  2120,  2120,  2128,  2129,  2132,
    2133,  2134,  2135,  2138,  2138,  2146,  2151,  2156
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


#line 14 "dhcp4_parser.yy" // lalr1.cc:1163
} } // isc::dhcp
#line 4771 "dhcp4_parser.cc" // lalr1.cc:1163
#line 2161 "dhcp4_parser.yy" // lalr1.cc:1164


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
