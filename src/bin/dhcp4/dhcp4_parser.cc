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
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 338: // hr_mode
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 169: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 168: // "floating point"
        value.copy< double > (that.value);
        break;

      case 167: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 166: // "constant string"
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
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 338: // hr_mode
      case 487: // ncr_protocol_value
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

    // that is emptied.
    that.type = empty_symbol;
  }

  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 338: // hr_mode
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 169: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 168: // "floating point"
        value.copy< double > (that.value);
        break;

      case 167: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 166: // "constant string"
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
            case 166: // "constant string"

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< std::string > (); }
#line 393 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 167: // "integer"

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 400 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 168: // "floating point"

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< double > (); }
#line 407 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 169: // "boolean"

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< bool > (); }
#line 414 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 186: // value

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 421 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 190: // map_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 428 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 231: // socket_type

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 435 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 234: // outbound_interface_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 442 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 256: // db_type

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 449 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 338: // hr_mode

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 456 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 487: // ncr_protocol_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 463 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 495: // replace_client_name_value

#line 246 "dhcp4_parser.yy" // lalr1.cc:635
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
      case 186: // value
      case 190: // map_value
      case 231: // socket_type
      case 234: // outbound_interface_value
      case 256: // db_type
      case 338: // hr_mode
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 169: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 168: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 167: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 166: // "constant string"
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
#line 255 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 715 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 256 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.CONFIG; }
#line 721 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 257 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP4; }
#line 727 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 258 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 733 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 259 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.SUBNET4; }
#line 739 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 260 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.POOLS; }
#line 745 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 261 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 751 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 262 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP4; }
#line 757 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 263 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 763 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 264 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 769 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 22:
#line 265 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 775 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 266 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 781 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 267 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.LOGGING; }
#line 787 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 28:
#line 268 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 793 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 276 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 799 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 31:
#line 277 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 805 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 32:
#line 278 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 811 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 279 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 34:
#line 280 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 35:
#line 281 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 829 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 36:
#line 282 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 835 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 37:
#line 285 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 844 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 38:
#line 290 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 855 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 39:
#line 295 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 865 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 40:
#line 301 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 871 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 43:
#line 308 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 880 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 44:
#line 312 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 45:
#line 319 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 899 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 46:
#line 322 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // list parsing complete. Put any sanity checking here
}
#line 907 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 49:
#line 330 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 916 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 50:
#line 334 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 925 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 51:
#line 341 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // List parsing about to start
}
#line 933 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 52:
#line 343 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 942 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 55:
#line 352 "dhcp4_parser.yy" // lalr1.cc:856
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 951 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 56:
#line 356 "dhcp4_parser.yy" // lalr1.cc:856
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 960 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 57:
#line 367 "dhcp4_parser.yy" // lalr1.cc:856
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 971 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 58:
#line 377 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 59:
#line 382 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 995 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 68:
#line 406 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 69:
#line 413 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 70:
#line 421 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1028 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 71:
#line 425 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No global parameter is required
    // parsing completed
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 107:
#line 471 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 108:
#line 476 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1055 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 109:
#line 481 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 110:
#line 486 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1073 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 111:
#line 491 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 112:
#line 493 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 113:
#line 499 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 114:
#line 504 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1109 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 115:
#line 509 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1118 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 116:
#line 515 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1129 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 117:
#line 520 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1139 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 127:
#line 539 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1149 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 128:
#line 543 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1158 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 129:
#line 548 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1169 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 130:
#line 553 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 131:
#line 558 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1186 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 132:
#line 560 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1195 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 133:
#line 565 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 134:
#line 566 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1207 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 135:
#line 569 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 136:
#line 571 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 137:
#line 576 "dhcp4_parser.yy" // lalr1.cc:856
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1232 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 138:
#line 578 "dhcp4_parser.yy" // lalr1.cc:856
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1240 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 139:
#line 582 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 140:
#line 588 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1260 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 141:
#line 593 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1271 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 142:
#line 600 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1282 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 143:
#line 605 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1291 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 147:
#line 615 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1299 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 148:
#line 617 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 1319 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 149:
#line 633 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 150:
#line 638 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 151:
#line 645 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 152:
#line 650 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1361 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 157:
#line 663 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1371 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 158:
#line 667 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1381 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 179:
#line 697 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1389 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 180:
#line 699 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 181:
#line 704 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1404 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 182:
#line 705 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1410 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 183:
#line 706 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1416 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 184:
#line 707 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1422 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 185:
#line 710 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 186:
#line 712 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1440 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 187:
#line 718 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1448 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 188:
#line 720 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1458 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 189:
#line 726 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1466 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 190:
#line 728 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 191:
#line 734 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 192:
#line 739 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1493 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 193:
#line 741 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 194:
#line 747 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1512 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 195:
#line 752 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1521 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 196:
#line 757 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1530 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 197:
#line 762 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1539 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 198:
#line 767 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 199:
#line 772 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1557 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 200:
#line 777 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 201:
#line 782 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 202:
#line 784 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1584 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 203:
#line 790 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1592 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 204:
#line 792 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1602 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 205:
#line 798 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1611 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 206:
#line 803 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1620 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 207:
#line 808 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 208:
#line 813 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 216:
#line 829 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 217:
#line 834 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 218:
#line 839 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 219:
#line 844 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1676 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 220:
#line 849 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 221:
#line 854 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1696 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 222:
#line 859 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1705 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 227:
#line 872 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1715 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 228:
#line 876 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1725 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 229:
#line 882 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1735 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 230:
#line 886 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 236:
#line 901 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 237:
#line 903 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 238:
#line 909 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 239:
#line 911 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 240:
#line 917 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1791 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 241:
#line 922 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 250:
#line 940 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 251:
#line 945 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1819 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 252:
#line 950 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1828 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 253:
#line 955 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 254:
#line 960 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 255:
#line 965 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1855 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 256:
#line 973 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 257:
#line 978 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 262:
#line 998 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1885 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 263:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 1911 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 264:
#line 1024 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1921 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 265:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1931 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 292:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 293:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1949 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 294:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1957 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 295:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 296:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 297:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 298:
#line 1090 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 299:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 300:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 301:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 302:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 303:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 304:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 305:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 306:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 307:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2076 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 308:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2082 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 309:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2088 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 310:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2094 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 311:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2100 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 312:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 313:
#line 1144 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2120 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 314:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2129 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 319:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 320:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 342:
#line 1201 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2158 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 343:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2167 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 344:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 345:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 2184 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 350:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 351:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2206 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 352:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 353:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2228 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 369:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2237 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 371:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 372:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2255 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 373:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2263 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 374:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2273 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 375:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 376:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2291 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 378:
#line 1317 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2299 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 379:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2309 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 380:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 381:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 382:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 387:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2348 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 388:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 389:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 390:
#line 1374 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2376 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 405:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2384 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 406:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2394 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 409:
#line 1419 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2403 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 410:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2412 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 411:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 412:
#line 1437 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 417:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 418:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2452 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 419:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 420:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 430:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 431:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2490 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 432:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2498 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 433:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 2525 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 434:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2533 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 435:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 2562 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 436:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 437:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2582 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 442:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 443:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 444:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2611 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 445:
#line 1579 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2620 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 465:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 466:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2638 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 467:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 468:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2656 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 469:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2664 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 470:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2674 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 471:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2682 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 472:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2692 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 473:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2703 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 474:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 475:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 476:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2730 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 477:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 478:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2748 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 479:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 480:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2766 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 481:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2774 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 482:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2784 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 483:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 484:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2802 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 485:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2810 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 486:
#line 1694 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2820 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 487:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 488:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 489:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2851 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 490:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2860 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 493:
#line 1730 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2871 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 494:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2880 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 497:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 498:
#line 1748 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2900 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 515:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 516:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 517:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 518:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2936 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 519:
#line 1801 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2947 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 520:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2956 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 528:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2964 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 529:
#line 1824 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2974 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 530:
#line 1830 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2982 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 531:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2992 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 532:
#line 1841 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3000 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 533:
#line 1843 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 3018 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 534:
#line 1859 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3029 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 535:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3040 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 536:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3050 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 537:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3060 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 559:
#line 1906 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3069 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 560:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3077 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 561:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 562:
#line 1919 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 563:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 564:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3114 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 565:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3122 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 566:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3132 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 567:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3141 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 568:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3150 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 569:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 570:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 571:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3173 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 572:
#line 1959 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3179 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 573:
#line 1962 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3187 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 574:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3197 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 575:
#line 1970 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3206 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 576:
#line 1975 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3215 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 577:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3224 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 578:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3232 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 579:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3241 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 580:
#line 1993 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3249 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 581:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3257 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 582:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3265 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 583:
#line 2002 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3273 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 584:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:856
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3282 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 585:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3290 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 586:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3300 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 587:
#line 2019 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3308 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 588:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3318 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 589:
#line 2027 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3326 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 590:
#line 2029 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3336 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 591:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3344 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 592:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3353 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 593:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3361 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 594:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3370 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 595:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 596:
#line 2054 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3387 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 597:
#line 2059 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3397 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 598:
#line 2063 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 3405 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 599:
#line 2068 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3416 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 600:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3426 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 601:
#line 2079 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3436 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 602:
#line 2083 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No config_control params are required
    // parsing completed
}
#line 3445 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 607:
#line 2098 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3456 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 608:
#line 2103 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3465 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 609:
#line 2113 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3476 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 610:
#line 2118 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3485 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 611:
#line 2123 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3495 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 612:
#line 2127 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 3503 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 616:
#line 2143 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3514 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 617:
#line 2148 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3523 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 620:
#line 2160 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3533 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 621:
#line 2164 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 3541 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 631:
#line 2181 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3550 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 632:
#line 2186 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3558 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 633:
#line 2188 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3568 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 634:
#line 2194 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3579 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 635:
#line 2199 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3588 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 638:
#line 2208 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3598 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 639:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 3606 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 646:
#line 2226 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3614 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 647:
#line 2228 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3624 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 648:
#line 2234 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3633 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 649:
#line 2239 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3642 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 650:
#line 2244 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3651 "dhcp4_parser.cc" // lalr1.cc:856
    break;


#line 3655 "dhcp4_parser.cc" // lalr1.cc:856
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


  const short int Dhcp4Parser::yypact_ninf_ = -795;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     428,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,    38,    24,    42,   106,   143,
     149,   158,   162,   173,   196,   198,   206,   213,   223,   234,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,    24,  -101,
      13,    65,    84,   147,   -17,   229,    53,   402,    68,   -56,
     363,    46,    20,  -795,   190,   245,   247,   255,   266,  -795,
    -795,  -795,  -795,  -795,   271,  -795,   101,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   272,   274,   275,
    -795,  -795,  -795,  -795,  -795,  -795,   283,   287,   297,   304,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,   307,  -795,  -795,  -795,  -795,   108,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   314,  -795,   109,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
     317,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,   121,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,   122,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,   282,   333,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   292,  -795,  -795,
     345,  -795,  -795,  -795,   352,  -795,  -795,   329,   357,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,   360,   361,  -795,  -795,  -795,  -795,   359,   365,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,   123,  -795,  -795,  -795,   371,  -795,  -795,   373,
    -795,   374,   377,  -795,  -795,   380,   381,   383,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   140,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   151,  -795,  -795,  -795,  -795,   163,
    -795,  -795,  -795,    24,    24,  -795,   228,   394,   396,   397,
     400,   401,  -795,    13,  -795,    20,   403,   408,   410,   249,
     250,   253,   419,   422,   423,   424,   426,   429,   265,   276,
     277,   278,   437,   438,   443,   444,   445,   463,   466,   467,
     471,   472,   476,   491,   331,   492,   493,   495,    65,  -795,
     496,   499,   500,   336,    84,  -795,   502,   503,   504,   505,
     506,   507,   347,   508,   512,   513,   514,   147,  -795,   515,
     -17,  -795,   517,   518,   519,   520,   523,   524,   526,   527,
    -795,   229,  -795,   529,   530,   368,   532,   533,   535,   375,
    -795,   402,   536,   376,   378,  -795,    68,   538,   542,    -3,
    -795,   379,   545,   546,   384,   550,   389,   390,   554,   555,
     391,   392,   393,   559,   560,   561,   562,   363,  -795,   563,
      46,  -795,   565,    20,  -795,  -795,  -795,   566,   564,   567,
      24,    24,    24,  -795,   180,   569,   570,   571,  -795,  -795,
    -795,   406,   430,   431,   587,   588,   593,  -795,  -795,  -795,
    -795,   433,   595,   596,   597,   598,   599,   439,   602,   603,
     604,   605,   606,  -795,   607,   599,   608,  -795,   611,   195,
     120,  -795,  -795,   446,   451,   452,   614,   454,   455,  -795,
     269,   611,   456,   616,  -795,   458,  -795,   611,   459,   460,
     461,   462,   464,   465,   468,  -795,   469,   470,  -795,   473,
     474,   475,  -795,  -795,   477,  -795,  -795,  -795,   478,    24,
    -795,  -795,   479,   480,  -795,   481,  -795,  -795,    36,   509,
    -795,  -795,  -795,   -55,   482,   483,   484,  -795,   624,  -795,
     627,  -795,    24,    65,    46,  -795,  -795,  -795,  -795,    20,
      84,   581,  -795,  -795,  -795,   413,   413,   626,  -795,   630,
     631,   644,   645,  -795,  -795,  -795,   -10,   646,   647,   648,
     175,    70,  -795,   363,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   649,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   171,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   650,
     626,  -795,   186,   201,   237,   246,  -795,   252,  -795,  -795,
    -795,  -795,  -795,  -795,   654,   655,   656,   657,   658,  -795,
    -795,   659,   660,   661,   662,   663,  -795,   256,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,   259,  -795,   664,   665,
    -795,  -795,   666,   668,  -795,  -795,   667,   671,  -795,  -795,
     669,   673,  -795,  -795,   672,   674,  -795,  -795,  -795,  -795,
    -795,  -795,    58,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
     152,  -795,  -795,   675,   676,  -795,  -795,   677,   679,  -795,
     680,   681,   682,   683,   684,   685,   286,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   295,
    -795,  -795,  -795,   296,   525,  -795,   686,   687,  -795,  -795,
    -795,  -795,   688,  -795,   216,  -795,   689,  -795,  -795,  -795,
    -795,   690,   581,  -795,   693,   694,   695,   696,   534,   442,
     537,   511,   539,   698,   699,   540,   541,   543,   544,   547,
     413,  -795,  -795,   413,  -795,   626,   147,  -795,   630,   402,
    -795,   631,    68,  -795,   644,   189,  -795,   645,   -10,  -795,
     268,   646,  -795,   229,  -795,   647,   -56,  -795,   648,   548,
     551,   552,   553,   556,   557,   175,  -795,   701,   705,    70,
    -795,  -795,  -795,   706,   710,   -17,  -795,   649,   713,  -795,
     197,   650,  -795,  -795,   568,  -795,   355,   572,   573,   574,
    -795,  -795,  -795,  -795,  -795,   575,   576,  -795,  -795,  -795,
    -795,  -795,  -795,   299,  -795,   309,  -795,   714,  -795,   717,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,   311,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   722,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   719,   711,  -795,  -795,  -795,
    -795,  -795,   720,  -795,   312,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,   577,   578,  -795,  -795,   579,   330,  -795,
     611,  -795,   725,  -795,  -795,  -795,  -795,  -795,   332,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   189,
    -795,   726,   580,  -795,   268,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,   727,   584,   728,   197,  -795,  -795,   582,  -795,
    -795,   716,  -795,   586,  -795,  -795,   729,  -795,  -795,   226,
    -795,   -40,   729,  -795,  -795,   731,   733,   742,   340,  -795,
    -795,  -795,  -795,  -795,  -795,   743,   585,   590,   591,   -40,
    -795,   589,  -795,  -795,  -795,  -795,  -795
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   127,     9,   264,    11,
     419,    13,   444,    15,   344,    17,   352,    19,   389,    21,
     229,    23,   536,    25,   611,    27,   601,    29,    47,    41,
       0,     0,     0,     0,     0,   446,     0,   354,   391,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     609,   591,   593,   595,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   597,   599,   116,   142,     0,     0,     0,
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
     238,   233,     0,   231,   234,   235,     0,   560,   562,     0,
     565,     0,     0,   569,   573,     0,     0,     0,   578,   585,
     587,   589,   558,   556,   557,     0,   538,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   616,     0,   613,   615,   607,   606,     0,
     603,   605,    46,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    57,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    71,
       0,     0,     0,     0,     0,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   265,     0,
       0,   420,     0,     0,     0,     0,     0,     0,     0,     0,
     445,     0,   345,     0,     0,     0,     0,     0,     0,     0,
     353,     0,     0,     0,     0,   390,     0,     0,     0,     0,
     230,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   537,     0,
       0,   612,     0,     0,   602,    50,    43,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,     0,   113,   114,
     115,     0,     0,     0,     0,     0,     0,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   518,     0,     0,     0,    73,     0,     0,
       0,   139,   119,     0,     0,     0,     0,     0,     0,   312,
       0,     0,     0,     0,   267,     0,   422,     0,     0,     0,
       0,     0,     0,     0,     0,   449,     0,     0,   369,     0,
       0,     0,   380,   357,     0,   409,   410,   394,     0,     0,
     232,   559,     0,     0,   564,     0,   567,   568,     0,     0,
     575,   576,   577,     0,     0,     0,     0,   539,     0,   614,
       0,   604,     0,     0,     0,   592,   594,   596,   598,     0,
       0,     0,   466,   468,   470,     0,     0,   153,   112,   258,
     346,   383,   315,    40,   433,   435,     0,     0,   438,   223,
       0,     0,   533,     0,    51,   130,   133,   134,   132,   137,
     138,   136,   295,   297,   299,   413,   293,   301,   308,   309,
     310,   311,   307,   305,   303,     0,   431,   488,   476,   478,
     482,   480,   486,   484,   472,   372,   193,   376,   374,   379,
     406,   237,   239,   561,   563,   566,   571,   572,   570,   574,
     580,   581,   582,   583,   584,   579,   586,   588,   590,     0,
     153,    44,     0,     0,     0,     0,   147,     0,   144,   146,
     179,   185,   187,   189,     0,     0,     0,     0,     0,   201,
     203,     0,     0,     0,     0,     0,   178,     0,   159,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   174,
     175,   176,   171,   177,   172,   173,     0,   157,     0,   154,
     155,   262,     0,   259,   260,   350,     0,   347,   348,   387,
       0,   384,   385,   319,     0,   316,   317,   216,   217,   218,
     219,   220,     0,   209,   211,   212,   213,   214,   215,   497,
       0,   495,   442,     0,   439,   440,   227,     0,   224,   225,
       0,     0,     0,     0,     0,     0,     0,   242,   244,   245,
     246,   247,   248,   249,   528,   530,   527,   525,   526,     0,
     521,   523,   524,     0,    53,   417,     0,   414,   415,   473,
     491,   492,     0,   620,     0,   618,     0,    69,   610,   600,
     117,     0,     0,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   141,   150,     0,   152,     0,     0,   257,     0,   354,
     343,     0,   391,   382,     0,     0,   314,     0,     0,   208,
     499,     0,   494,   446,   437,     0,     0,   222,     0,     0,
       0,     0,     0,     0,     0,     0,   241,     0,     0,     0,
     520,   535,    55,     0,    54,     0,   412,     0,     0,   490,
       0,     0,   617,   608,     0,   145,     0,     0,     0,     0,
     191,   194,   195,   196,   197,     0,     0,   205,   206,   198,
     199,   200,   160,     0,   156,     0,   261,     0,   349,     0,
     386,   341,   338,   326,   327,   329,   330,   323,   324,   325,
     336,   337,   335,     0,   321,   328,   339,   340,   331,   332,
     333,   334,   318,   210,   515,     0,   513,   514,   506,   507,
     511,   512,   508,   509,   510,     0,   500,   501,   503,   504,
     505,   496,     0,   441,     0,   226,   250,   251,   252,   253,
     254,   255,   243,     0,     0,   522,    52,     0,     0,   416,
       0,   634,     0,   632,   630,   624,   628,   629,     0,   622,
     626,   627,   625,   619,   148,   181,   182,   183,   184,   180,
     186,   188,   190,   202,   204,   158,   263,   351,   388,     0,
     320,     0,     0,   498,     0,   443,   228,   529,   531,    56,
     418,   474,     0,     0,     0,     0,   621,   322,     0,   517,
     502,     0,   631,     0,   623,   516,     0,   633,   638,     0,
     636,     0,     0,   635,   646,     0,     0,     0,     0,   640,
     642,   643,   644,   645,   637,     0,     0,     0,     0,     0,
     639,     0,   648,   649,   650,   641,   647
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,   -44,  -795,  -452,  -795,
     154,  -795,  -795,  -795,  -795,  -795,  -795,  -510,  -795,  -795,
    -795,   -70,  -795,  -795,  -795,   370,  -795,  -795,  -795,  -795,
     110,   362,   -48,   -45,   -43,  -795,  -795,  -795,  -795,   -11,
       4,  -795,  -795,   174,   382,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,   -41,  -795,  -795,  -795,  -795,  -795,  -795,    93,  -795,
     -32,  -795,  -590,   -53,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   -26,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,   -69,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,   -68,  -795,  -795,  -795,   -62,   349,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   -59,  -795,  -795,  -795,  -795,
    -795,  -795,  -794,  -795,  -795,  -795,   -29,  -795,  -795,  -795,
     -22,   399,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -792,  -795,   -24,  -795,    -4,  -795,  -791,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   -27,  -795,  -795,  -176,   -65,  -795,
    -795,  -795,  -795,  -795,   -13,  -795,  -795,  -795,     9,  -795,
     404,  -795,   -66,  -795,  -795,  -795,  -795,  -795,   -60,  -795,
    -795,  -795,  -795,  -795,   -18,  -795,  -795,  -795,     8,  -795,
    -795,  -795,    -9,  -795,   405,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,   -21,  -795,  -795,  -795,
     -16,   432,  -795,  -795,   -58,  -795,   -38,  -795,   -47,  -795,
    -795,  -795,     3,  -795,  -795,  -795,     7,  -795,   425,    -7,
    -795,    -6,  -795,     0,  -795,   218,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -790,  -795,  -795,  -795,  -795,  -795,    14,
    -795,  -795,  -795,  -140,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,    -2,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,   251,   395,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -352,   385,  -795,  -795,  -795,  -795,  -795,
    -795,   279,   398,  -795,  -795,  -795,   -12,  -795,  -795,  -145,
    -795,  -795,  -795,  -795,  -795,  -795,  -157,  -795,  -795,  -173,
    -795,  -795,  -795,  -795,  -795
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     604,    87,    88,    41,    68,    84,    85,   615,   784,   863,
     864,   348,    43,    70,    96,    97,    98,   357,    45,    71,
     137,   138,   139,   140,   141,   142,   143,   382,   144,   145,
     146,   147,   367,   176,   177,    47,    72,   178,   400,   179,
     401,   618,   180,   402,   621,   181,   148,   375,   149,   368,
     677,   678,   679,   801,   150,   376,   151,   377,   718,   719,
     720,   823,   697,   698,   699,   804,   979,   700,   805,   701,
     806,   702,   807,   703,   704,   434,   705,   706,   707,   708,
     709,   710,   711,   712,   813,   713,   814,   714,   715,   152,
     389,   742,   743,   744,   745,   746,   747,   748,   153,   392,
     757,   758,   759,   846,    61,    79,   302,   303,   304,   447,
     305,   448,   154,   393,   766,   767,   768,   769,   770,   771,
     772,   773,   155,   383,   722,   723,   724,   826,    49,    73,
     201,   202,   203,   410,   204,   406,   205,   407,   206,   408,
     207,   411,   208,   415,   209,   414,   210,   413,   632,   211,
     156,   386,   734,   735,   736,   835,   913,   914,   157,   384,
      55,    76,   726,   727,   728,   829,    57,    77,   267,   268,
     269,   270,   271,   272,   273,   433,   274,   437,   275,   436,
     276,   277,   438,   278,   158,   385,   730,   731,   732,   832,
      59,    78,   288,   289,   290,   291,   292,   442,   293,   294,
     295,   296,   213,   409,   786,   787,   788,   865,    51,    74,
     226,   227,   228,   419,   159,   387,   160,   388,   161,   391,
     753,   754,   755,   843,    53,    75,   243,   244,   245,   162,
     372,   163,   373,   164,   374,   249,   429,   791,   868,   250,
     423,   251,   424,   252,   426,   253,   425,   254,   428,   255,
     427,   256,   422,   220,   416,   792,   165,   390,   750,   751,
     840,   935,   936,   937,   938,   939,   991,   940,   166,   167,
     395,   779,   780,   781,   857,   782,   858,   168,   396,   169,
     397,    63,    80,   325,   326,   327,   328,   452,   329,   453,
     330,   331,   455,   332,   333,   334,   458,   658,   335,   459,
     336,   337,   338,   339,   463,   665,   340,   464,   341,   465,
     342,   466,    99,   359,   100,   360,   101,   361,   170,   365,
     366,    67,    82,   349,   350,   351,   472,   102,   358,    65,
      81,   344,   345,   346,   469,   794,   795,   870,   968,   969,
     970,   971,  1004,   972,  1002,  1019,  1020,  1021,  1028,  1029,
    1030,  1035,  1031,  1032,  1033
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   136,   175,   195,   222,   239,   716,   265,   284,   301,
     322,   257,   286,   484,   182,   214,   229,   241,   287,   279,
     297,   633,   323,    89,    83,   196,   216,   637,   197,    31,
     198,    32,   347,    33,   183,   215,   230,   242,    30,   280,
     298,   908,   324,   909,   912,   921,   123,   299,   300,    42,
     223,   266,   285,   656,   603,   212,   225,   240,   221,   125,
     126,   838,   199,   603,   839,    86,   217,   218,   246,   247,
     224,   192,   103,   219,   193,   248,   104,   200,   105,   660,
     661,   662,   663,   737,   738,   739,   740,   106,   741,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   171,   172,
     299,   300,   173,  1024,   363,   174,  1025,  1026,  1027,   364,
      94,   398,   404,    44,   664,   122,   399,   405,   116,   117,
     118,   119,   120,   121,   417,   420,   449,   122,   123,   418,
     421,   450,   259,   281,   260,   261,   282,   283,   124,   619,
     620,   125,   126,   467,   125,   126,   125,   126,   468,    94,
      46,   127,   128,    90,   470,   841,    48,   129,   842,   471,
     125,   126,    91,    92,    93,    50,   473,   130,   657,    52,
     131,   474,   108,   109,   110,   111,   112,   132,   133,    94,
      54,   134,   135,   473,   774,   775,    94,   343,   588,   398,
      34,    35,    36,    37,   797,   908,   352,   909,   912,   921,
     116,   117,   118,    56,   470,    58,   184,   185,   186,   798,
     123,   616,   617,    60,   108,   109,   110,   111,   112,   871,
      62,   187,   872,   125,   126,   188,   189,   190,   191,  1022,
      64,    94,  1023,   893,    94,   192,    94,   674,   193,   129,
     473,    66,   116,   117,   118,   799,   194,   121,   353,   404,
      94,   354,   123,   259,   800,   802,   110,   111,   112,   820,
     803,   259,   820,   355,   821,   125,   126,   822,   189,   356,
     191,   238,   789,   125,   126,   362,   369,   192,   370,   371,
     193,   760,   761,   762,   763,   764,   765,   378,   194,   855,
     430,   379,   123,    95,   856,   110,   111,   112,   859,   467,
     432,   380,   820,   860,   861,   125,   126,   985,   381,   475,
     476,   394,   417,    94,   989,   449,   231,   986,   403,   990,
     996,   412,   232,   233,   234,   235,   236,   237,   136,   238,
     122,   123,   259,   420,   175,  1005,   431,   440,  1000,   961,
    1006,   962,   963,  1039,   125,   126,   182,   195,  1040,   435,
     222,   628,   629,   630,   631,    94,   439,   924,   925,   214,
     441,   239,   229,    94,   443,   444,   183,   445,   446,   196,
     216,   265,   197,   241,   198,   451,   284,   454,   456,   215,
     286,   457,   230,   279,   460,   461,   287,   462,   297,   975,
     976,   977,   978,   242,   477,    94,   223,   322,   478,   212,
     479,   480,   225,   280,   481,   482,   199,   485,   298,   323,
     217,   218,   486,   240,   487,   266,   224,   219,   488,   489,
     285,   200,   490,   491,   246,   247,   492,   493,   494,   324,
     495,   248,   497,   496,    94,   258,   585,   586,   587,   125,
     126,   501,   502,   498,   499,   500,   680,   503,   504,   505,
    1001,   681,   682,   683,   684,   685,   686,   687,   688,   689,
     690,   691,   692,   693,   694,   695,   259,   506,   260,   261,
     507,   508,   262,   263,   264,   509,   510,   259,   125,   126,
     511,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   512,   514,   515,   513,   516,
     518,   320,   321,   519,   520,   521,   523,   524,   525,   526,
     527,   528,   530,   136,   529,   652,   531,   532,   533,   535,
     175,   537,   538,   539,   540,   696,   696,   541,   542,    94,
     543,   544,   182,   546,   547,   548,   549,   550,   671,   551,
     554,   776,   558,   322,   552,   555,   559,   556,   561,   562,
     563,   564,   183,   777,   565,   323,   566,   567,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   578,    94,   580,
     582,   583,   592,   778,   584,   324,   589,   590,   591,    94,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   595,   596,   593,   594,   597,   598,
     599,   600,   601,   602,   676,   605,    32,   606,   607,   608,
     609,   881,   622,   610,   611,   613,   614,   623,   624,   625,
     626,   627,   634,   635,   636,   638,   639,   640,   641,   669,
     642,   643,   670,   717,   644,   645,   646,   721,   725,   647,
     648,   649,   659,   650,   651,   653,   654,   655,   666,   667,
     668,   729,   733,   749,   752,   756,   785,   793,   808,   809,
     810,   811,   812,   815,   816,   817,   818,   819,   825,   612,
     824,   828,   827,   830,   831,   833,   834,   837,   836,   845,
     883,   844,   848,   847,   849,   850,   851,   852,   853,   854,
     867,   862,   866,   672,   874,   873,   869,   876,   877,   878,
     879,   880,   885,   886,   882,   953,   884,   887,   888,   954,
     889,   890,   956,   957,   994,   946,   891,   960,   947,   948,
     949,  1016,   987,   950,   951,   988,   992,   993,   995,  1003,
    1008,  1011,  1013,   483,   974,  1036,  1018,  1037,   980,   981,
     982,   983,   984,   997,   998,   999,  1038,  1041,  1015,  1009,
     696,  1012,  1017,   696,  1042,  1046,   195,  1043,  1044,   265,
     517,   875,   284,   796,   675,   901,   286,   892,   214,   923,
     926,   279,   287,   239,   297,   928,   301,   916,   196,   216,
     945,   197,   930,   198,   944,   241,   522,   902,   215,   776,
     903,   280,   904,   894,   298,   222,   952,   917,   560,   896,
     964,   777,   931,   266,   895,   242,   285,   229,   212,   907,
     922,   910,   966,  1007,   927,   199,   534,   915,   898,   217,
     218,   778,   929,   899,   905,   240,   219,   230,   918,   919,
     200,   911,   967,   932,   933,   920,   246,   247,   897,   906,
     934,   223,   900,   248,   965,   553,   959,   225,   943,   958,
     942,   557,   536,   790,  1010,   941,   545,   955,   581,   973,
    1014,   224,   577,   673,   783,  1034,  1045,     0,   579,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   901,
       0,     0,     0,     0,   926,     0,     0,     0,     0,   928,
       0,   916,     0,     0,     0,   964,   930,     0,     0,     0,
       0,   902,     0,     0,   903,     0,   904,   966,     0,     0,
       0,   917,     0,     0,     0,     0,   931,     0,     0,     0,
       0,     0,     0,   907,     0,   910,     0,   967,   927,     0,
       0,   915,     0,     0,     0,     0,   929,     0,   905,   965,
       0,     0,   918,   919,     0,   911,     0,   932,   933,   920,
       0,     0,     0,   906,   934
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,   596,    77,    78,    79,
      80,    76,    78,   365,    72,    73,    74,    75,    78,    77,
      78,   531,    80,    10,    68,    73,    73,   537,    73,     5,
      73,     7,    12,     9,    72,    73,    74,    75,     0,    77,
      78,   835,    80,   835,   835,   835,    63,   103,   104,     7,
      74,    77,    78,    17,   506,    73,    74,    75,    75,    76,
      77,     3,    73,   515,     6,   166,    73,    73,    75,    75,
      74,    88,     7,    73,    91,    75,    11,    73,    13,   134,
     135,   136,   137,    93,    94,    95,    96,    22,    98,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    14,    15,
     103,   104,    18,   143,     3,    21,   146,   147,   148,     8,
     166,     3,     3,     7,   169,    62,     8,     8,    53,    54,
      55,    56,    57,    58,     3,     3,     3,    62,    63,     8,
       8,     8,    64,    65,    66,    67,    68,    69,    73,    19,
      20,    76,    77,     3,    76,    77,    76,    77,     8,   166,
       7,    86,    87,   140,     3,     3,     7,    92,     6,     8,
      76,    77,   149,   150,   151,     7,     3,   102,   132,     7,
     105,     8,    25,    26,    27,    28,    29,   112,   113,   166,
       7,   116,   117,     3,   114,   115,   166,   141,     8,     3,
     166,   167,   168,   169,     8,   989,     6,   989,   989,   989,
      53,    54,    55,     7,     3,     7,    59,    60,    61,     8,
      63,    16,    17,     7,    25,    26,    27,    28,    29,     3,
       7,    74,     6,    76,    77,    78,    79,    80,    81,     3,
       7,   166,     6,   823,   166,    88,   166,   589,    91,    92,
       3,     7,    53,    54,    55,     8,    99,    58,     3,     3,
     166,     4,    63,    64,     8,     3,    27,    28,    29,     3,
       8,    64,     3,     8,     8,    76,    77,     8,    79,     3,
      81,   100,   101,    76,    77,     4,     4,    88,     4,     4,
      91,   106,   107,   108,   109,   110,   111,     4,    99,     3,
       8,     4,    63,   363,     8,    27,    28,    29,     3,     3,
       8,     4,     3,     8,     8,    76,    77,     8,     4,   353,
     354,     4,     3,   166,     3,     3,    87,     8,     4,     8,
       8,     4,    93,    94,    95,    96,    97,    98,   398,   100,
      62,    63,    64,     3,   404,     3,     3,     8,     8,   142,
       8,   144,   145,     3,    76,    77,   404,   417,     8,     4,
     420,    82,    83,    84,    85,   166,     4,    89,    90,   417,
       3,   431,   420,   166,     4,     4,   404,     8,     3,   417,
     417,   441,   417,   431,   417,     4,   446,     4,     4,   417,
     446,     4,   420,   441,     4,     4,   446,     4,   446,    34,
      35,    36,    37,   431,   166,   166,   420,   467,     4,   417,
       4,     4,   420,   441,     4,     4,   417,     4,   446,   467,
     417,   417,     4,   431,     4,   441,   420,   417,   169,   169,
     446,   417,   169,     4,   431,   431,     4,     4,     4,   467,
       4,   431,   167,     4,   166,    33,   480,   481,   482,    76,
      77,     4,     4,   167,   167,   167,    33,     4,     4,     4,
     960,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    64,     4,    66,    67,
       4,     4,    70,    71,    72,     4,     4,    64,    76,    77,
       4,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,     4,     4,     4,   167,     4,
       4,   138,   139,     4,     4,   169,     4,     4,     4,     4,
       4,     4,     4,   583,   167,   559,     4,     4,     4,     4,
     590,     4,     4,     4,     4,   595,   596,     4,     4,   166,
       4,     4,   590,     4,     4,   167,     4,     4,   582,     4,
       4,   611,     4,   613,   169,   169,     4,   169,   169,     4,
       4,   167,   590,   611,     4,   613,   167,   167,     4,     4,
     169,   169,   169,     4,     4,     4,     4,     4,   166,     4,
       4,     7,   166,   611,     7,   613,     7,     7,     7,   166,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,     7,     7,   166,   166,     5,   166,
       5,     5,     5,     5,    23,   166,     7,     5,     5,     5,
       5,   169,   166,     7,     7,     7,     5,   166,   166,     5,
     166,   166,   166,     7,   166,   166,   166,   166,   166,     5,
     166,   166,     5,     7,   166,   166,   166,     7,     7,   166,
     166,   166,   133,   166,   166,   166,   166,   166,   166,   166,
     166,     7,     7,     7,     7,     7,     7,     7,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   515,
       6,     3,     6,     6,     3,     6,     3,     3,     6,     3,
     169,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       3,   166,     6,   583,     4,     6,     8,     4,     4,     4,
       4,   167,     4,     4,   167,     4,   167,   167,   167,     4,
     167,   167,     6,     3,     3,   167,   169,     4,   167,   167,
     167,     5,     8,   167,   167,     8,     4,     8,     8,     4,
       4,     4,     4,   363,   166,     4,     7,     4,   166,   166,
     166,   166,   166,   166,   166,   166,     4,     4,   166,   169,
     820,   167,   166,   823,   169,   166,   826,   167,   167,   829,
     398,   802,   832,   670,   590,   835,   832,   820,   826,   838,
     840,   829,   832,   843,   832,   840,   846,   835,   826,   826,
     848,   826,   840,   826,   846,   843,   404,   835,   826,   859,
     835,   829,   835,   825,   832,   865,   855,   835,   449,   828,
     870,   859,   840,   829,   826,   843,   832,   865,   826,   835,
     837,   835,   870,   989,   840,   826,   417,   835,   831,   826,
     826,   859,   840,   832,   835,   843,   826,   865,   835,   835,
     826,   835,   870,   840,   840,   835,   843,   843,   829,   835,
     840,   865,   834,   843,   870,   441,   867,   865,   845,   865,
     843,   446,   420,   635,   994,   841,   431,   859,   473,   871,
    1005,   865,   467,   584,   613,  1022,  1039,    -1,   470,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   989,
      -1,    -1,    -1,    -1,   994,    -1,    -1,    -1,    -1,   994,
      -1,   989,    -1,    -1,    -1,  1005,   994,    -1,    -1,    -1,
      -1,   989,    -1,    -1,   989,    -1,   989,  1005,    -1,    -1,
      -1,   989,    -1,    -1,    -1,    -1,   994,    -1,    -1,    -1,
      -1,    -1,    -1,   989,    -1,   989,    -1,  1005,   994,    -1,
      -1,   989,    -1,    -1,    -1,    -1,   994,    -1,   989,  1005,
      -1,    -1,   989,   989,    -1,   989,    -1,   994,   994,   989,
      -1,    -1,    -1,   989,   994
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     5,     7,     9,   166,   167,   168,   169,   186,   187,
     188,   193,     7,   202,     7,   208,     7,   225,     7,   318,
       7,   398,     7,   414,     7,   350,     7,   356,     7,   380,
       7,   294,     7,   471,     7,   519,     7,   511,   194,   189,
     203,   209,   226,   319,   399,   415,   351,   357,   381,   295,
     472,   520,   512,   186,   195,   196,   166,   191,   192,    10,
     140,   149,   150,   151,   166,   201,   204,   205,   206,   502,
     504,   506,   517,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    53,    54,    55,    56,
      57,    58,    62,    63,    73,    76,    77,    86,    87,    92,
     102,   105,   112,   113,   116,   117,   201,   210,   211,   212,
     213,   214,   215,   216,   218,   219,   220,   221,   236,   238,
     244,   246,   279,   288,   302,   312,   340,   348,   374,   404,
     406,   408,   419,   421,   423,   446,   458,   459,   467,   469,
     508,    14,    15,    18,    21,   201,   223,   224,   227,   229,
     232,   235,   404,   406,    59,    60,    61,    74,    78,    79,
      80,    81,    88,    91,    99,   201,   212,   213,   214,   219,
     220,   320,   321,   322,   324,   326,   328,   330,   332,   334,
     336,   339,   374,   392,   404,   406,   408,   419,   421,   423,
     443,    75,   201,   332,   334,   374,   400,   401,   402,   404,
     406,    87,    93,    94,    95,    96,    97,    98,   100,   201,
     374,   404,   406,   416,   417,   418,   419,   421,   423,   425,
     429,   431,   433,   435,   437,   439,   441,   348,    33,    64,
      66,    67,    70,    71,    72,   201,   264,   358,   359,   360,
     361,   362,   363,   364,   366,   368,   370,   371,   373,   404,
     406,    65,    68,    69,   201,   264,   362,   368,   382,   383,
     384,   385,   386,   388,   389,   390,   391,   404,   406,   103,
     104,   201,   296,   297,   298,   300,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     138,   139,   201,   404,   406,   473,   474,   475,   476,   478,
     480,   481,   483,   484,   485,   488,   490,   491,   492,   493,
     496,   498,   500,   141,   521,   522,   523,    12,   201,   513,
     514,   515,     6,     3,     4,     8,     3,   207,   518,   503,
     505,   507,     4,     3,     8,   509,   510,   222,   239,     4,
       4,     4,   420,   422,   424,   237,   245,   247,     4,     4,
       4,     4,   217,   313,   349,   375,   341,   405,   407,   280,
     447,   409,   289,   303,     4,   460,   468,   470,     3,     8,
     228,   230,   233,     4,     3,     8,   325,   327,   329,   393,
     323,   331,     4,   337,   335,   333,   444,     3,     8,   403,
       3,     8,   442,   430,   432,   436,   434,   440,   438,   426,
       8,     3,     8,   365,   265,     4,   369,   367,   372,     4,
       8,     3,   387,     4,     4,     8,     3,   299,   301,     3,
       8,     4,   477,   479,     4,   482,     4,     4,   486,   489,
       4,     4,     4,   494,   497,   499,   501,     3,     8,   524,
       3,     8,   516,     3,     8,   186,   186,   166,     4,     4,
       4,     4,     4,   205,   513,     4,     4,     4,   169,   169,
     169,     4,     4,     4,     4,     4,     4,   167,   167,   167,
     167,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   167,     4,     4,     4,   211,     4,     4,
       4,   169,   224,     4,     4,     4,     4,     4,     4,   167,
       4,     4,     4,     4,   321,     4,   401,     4,     4,     4,
       4,     4,     4,     4,     4,   418,     4,     4,   167,     4,
       4,     4,   169,   360,     4,   169,   169,   384,     4,     4,
     297,   169,     4,     4,   167,     4,   167,   167,     4,     4,
     169,   169,   169,     4,     4,     4,     4,   474,     4,   522,
       4,   514,     4,     7,     7,   186,   186,   186,     8,     7,
       7,     7,   166,   166,   166,     7,     7,     5,   166,     5,
       5,     5,     5,   188,   190,   166,     5,     5,     5,     5,
       7,     7,   190,     7,     5,   197,    16,    17,   231,    19,
      20,   234,   166,   166,   166,     5,   166,   166,    82,    83,
      84,    85,   338,   197,   166,     7,   166,   197,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   186,   166,   166,   166,    17,   132,   487,   133,
     134,   135,   136,   137,   169,   495,   166,   166,   166,     5,
       5,   186,   210,   521,   513,   223,    23,   240,   241,   242,
      33,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,   201,   252,   253,   254,
     257,   259,   261,   263,   264,   266,   267,   268,   269,   270,
     271,   272,   273,   275,   277,   278,   252,     7,   248,   249,
     250,     7,   314,   315,   316,     7,   352,   353,   354,     7,
     376,   377,   378,     7,   342,   343,   344,    93,    94,    95,
      96,    98,   281,   282,   283,   284,   285,   286,   287,     7,
     448,   449,     7,   410,   411,   412,     7,   290,   291,   292,
     106,   107,   108,   109,   110,   111,   304,   305,   306,   307,
     308,   309,   310,   311,   114,   115,   201,   404,   406,   461,
     462,   463,   465,   473,   198,     7,   394,   395,   396,   101,
     425,   427,   445,     7,   525,   526,   248,     8,     8,     8,
       8,   243,     3,     8,   255,   258,   260,   262,     4,     4,
       4,     4,     4,   274,   276,     4,     4,     4,     4,     4,
       3,     8,     8,   251,     6,     3,   317,     6,     3,   355,
       6,     3,   379,     6,     3,   345,     6,     3,     3,     6,
     450,     3,     6,   413,     6,     3,   293,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   464,   466,     3,
       8,     8,   166,   199,   200,   397,     6,     3,   428,     8,
     527,     3,     6,     6,     4,   241,     4,     4,     4,     4,
     167,   169,   167,   169,   167,     4,     4,   167,   167,   167,
     167,   169,   253,   252,   250,   320,   316,   358,   354,   382,
     378,   201,   212,   213,   214,   219,   220,   264,   312,   330,
     332,   334,   336,   346,   347,   374,   404,   406,   419,   421,
     423,   443,   344,   282,    89,    90,   201,   264,   348,   374,
     404,   406,   419,   421,   423,   451,   452,   453,   454,   455,
     457,   449,   416,   412,   296,   292,   167,   167,   167,   167,
     167,   167,   305,     4,     4,   462,     6,     3,   400,   396,
       4,   142,   144,   145,   201,   264,   404,   406,   528,   529,
     530,   531,   533,   526,   166,    34,    35,    36,    37,   256,
     166,   166,   166,   166,   166,     8,     8,     8,     8,     3,
       8,   456,     4,     8,     3,     8,     8,   166,   166,   166,
       8,   197,   534,     4,   532,     3,     8,   347,     4,   169,
     453,     4,   167,     4,   529,   166,     5,   166,     7,   535,
     536,   537,     3,     6,   143,   146,   147,   148,   538,   539,
     540,   542,   543,   544,   536,   541,     4,     4,     4,     3,
       8,     4,   169,   167,   167,   539,   166
  };

  const unsigned short int
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
     211,   211,   211,   211,   211,   211,   211,   212,   213,   214,
     215,   217,   216,   218,   219,   220,   222,   221,   223,   223,
     224,   224,   224,   224,   224,   224,   224,   226,   225,   228,
     227,   230,   229,   231,   231,   233,   232,   234,   234,   235,
     237,   236,   239,   238,   240,   240,   241,   243,   242,   245,
     244,   247,   246,   248,   248,   249,   249,   251,   250,   252,
     252,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   255,
     254,   256,   256,   256,   256,   258,   257,   260,   259,   262,
     261,   263,   265,   264,   266,   267,   268,   269,   270,   271,
     272,   274,   273,   276,   275,   277,   278,   280,   279,   281,
     281,   282,   282,   282,   282,   282,   283,   284,   285,   286,
     287,   289,   288,   290,   290,   291,   291,   293,   292,   295,
     294,   296,   296,   296,   297,   297,   299,   298,   301,   300,
     303,   302,   304,   304,   305,   305,   305,   305,   305,   305,
     306,   307,   308,   309,   310,   311,   313,   312,   314,   314,
     315,   315,   317,   316,   319,   318,   320,   320,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   323,   322,   325,   324,   327,   326,   329,   328,
     331,   330,   333,   332,   335,   334,   337,   336,   338,   338,
     338,   338,   339,   341,   340,   342,   342,   343,   343,   345,
     344,   346,   346,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   349,   348,   351,   350,   352,   352,   353,   353,
     355,   354,   357,   356,   358,   358,   359,   359,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   361,   362,
     363,   365,   364,   367,   366,   369,   368,   370,   372,   371,
     373,   375,   374,   376,   376,   377,   377,   379,   378,   381,
     380,   382,   382,   383,   383,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   385,   387,   386,   388,   389,   390,
     391,   393,   392,   394,   394,   395,   395,   397,   396,   399,
     398,   400,   400,   401,   401,   401,   401,   401,   401,   401,
     403,   402,   405,   404,   407,   406,   409,   408,   410,   410,
     411,   411,   413,   412,   415,   414,   416,   416,   417,   417,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   420,   419,   422,   421,   424,
     423,   426,   425,   428,   427,   430,   429,   432,   431,   434,
     433,   436,   435,   438,   437,   440,   439,   442,   441,   444,
     443,   445,   445,   447,   446,   448,   448,   450,   449,   451,
     451,   452,   452,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   454,   456,   455,   457,   458,   460,
     459,   461,   461,   462,   462,   462,   462,   462,   464,   463,
     466,   465,   468,   467,   470,   469,   472,   471,   473,   473,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   475,
     477,   476,   479,   478,   480,   482,   481,   483,   484,   486,
     485,   487,   487,   489,   488,   490,   491,   492,   494,   493,
     495,   495,   495,   495,   495,   497,   496,   499,   498,   501,
     500,   503,   502,   505,   504,   507,   506,   509,   508,   510,
     508,   512,   511,   513,   513,   514,   514,   516,   515,   518,
     517,   520,   519,   521,   521,   522,   524,   523,   525,   525,
     527,   526,   528,   528,   529,   529,   529,   529,   529,   529,
     529,   530,   532,   531,   534,   533,   535,   535,   537,   536,
     538,   538,   539,   539,   539,   539,   541,   540,   542,   543,
     544
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     0,     6,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
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
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"",
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
  "ncr_format", "$@107", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@108",
  "replace_client_name_value", "generated_prefix", "$@109",
  "hostname_char_set", "$@110", "hostname_char_replacement", "$@111",
  "dhcp6_json_object", "$@112", "dhcpddns_json_object", "$@113",
  "control_agent_json_object", "$@114", "config_control", "$@115", "$@116",
  "sub_config_control", "$@117", "config_control_params",
  "config_control_param", "config_databases", "$@118", "logging_object",
  "$@119", "sub_logging", "$@120", "logging_params", "logging_param",
  "loggers", "$@121", "loggers_entries", "logger_entry", "$@122",
  "logger_params", "logger_param", "debuglevel", "severity", "$@123",
  "output_options_list", "$@124", "output_options_list_content",
  "output_entry", "$@125", "output_params_list", "output_params", "output",
  "$@126", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
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
     462,   463,   464,   465,   466,   467,   468,   471,   476,   481,
     486,   491,   491,   499,   504,   509,   515,   515,   526,   527,
     530,   531,   532,   533,   534,   535,   536,   539,   539,   548,
     548,   558,   558,   565,   566,   569,   569,   576,   578,   582,
     588,   588,   600,   600,   610,   611,   613,   615,   615,   633,
     633,   645,   645,   655,   656,   659,   660,   663,   663,   673,
     674,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   690,   691,   692,   693,   694,   697,
     697,   704,   705,   706,   707,   710,   710,   718,   718,   726,
     726,   734,   739,   739,   747,   752,   757,   762,   767,   772,
     777,   782,   782,   790,   790,   798,   803,   808,   808,   818,
     819,   822,   823,   824,   825,   826,   829,   834,   839,   844,
     849,   854,   854,   864,   865,   868,   869,   872,   872,   882,
     882,   892,   893,   894,   897,   898,   901,   901,   909,   909,
     917,   917,   928,   929,   932,   933,   934,   935,   936,   937,
     940,   945,   950,   955,   960,   965,   973,   973,   986,   987,
     990,   991,   998,   998,  1024,  1024,  1035,  1036,  1040,  1041,
    1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,
    1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,  1061,
    1062,  1063,  1066,  1066,  1074,  1074,  1082,  1082,  1090,  1090,
    1098,  1098,  1106,  1106,  1114,  1114,  1124,  1124,  1131,  1132,
    1133,  1134,  1137,  1144,  1144,  1155,  1156,  1160,  1161,  1164,
    1164,  1172,  1173,  1176,  1177,  1178,  1179,  1180,  1181,  1182,
    1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,
    1193,  1194,  1201,  1201,  1214,  1214,  1223,  1224,  1227,  1228,
    1233,  1233,  1248,  1248,  1262,  1263,  1266,  1267,  1270,  1271,
    1272,  1273,  1274,  1275,  1276,  1277,  1278,  1279,  1282,  1284,
    1289,  1291,  1291,  1299,  1299,  1307,  1307,  1315,  1317,  1317,
    1325,  1334,  1334,  1346,  1347,  1352,  1353,  1358,  1358,  1370,
    1370,  1382,  1383,  1388,  1389,  1394,  1395,  1396,  1397,  1398,
    1399,  1400,  1401,  1402,  1405,  1407,  1407,  1415,  1417,  1419,
    1424,  1432,  1432,  1444,  1445,  1448,  1449,  1452,  1452,  1462,
    1462,  1472,  1473,  1476,  1477,  1478,  1479,  1480,  1481,  1482,
    1485,  1485,  1493,  1493,  1518,  1518,  1548,  1548,  1558,  1559,
    1562,  1563,  1566,  1566,  1575,  1575,  1584,  1585,  1588,  1589,
    1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,
    1603,  1604,  1605,  1606,  1607,  1610,  1610,  1618,  1618,  1626,
    1626,  1634,  1634,  1642,  1642,  1652,  1652,  1660,  1660,  1668,
    1668,  1676,  1676,  1684,  1684,  1692,  1692,  1700,  1700,  1713,
    1713,  1723,  1724,  1730,  1730,  1740,  1741,  1744,  1744,  1754,
    1755,  1758,  1759,  1762,  1763,  1764,  1765,  1766,  1767,  1768,
    1769,  1770,  1771,  1772,  1775,  1777,  1777,  1785,  1794,  1801,
    1801,  1811,  1812,  1815,  1816,  1817,  1818,  1819,  1822,  1822,
    1830,  1830,  1841,  1841,  1859,  1859,  1871,  1871,  1881,  1882,
    1885,  1886,  1887,  1888,  1889,  1890,  1891,  1892,  1893,  1894,
    1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,  1906,
    1911,  1911,  1919,  1919,  1927,  1932,  1932,  1940,  1945,  1950,
    1950,  1958,  1959,  1962,  1962,  1970,  1975,  1980,  1985,  1985,
    1993,  1996,  1999,  2002,  2005,  2011,  2011,  2019,  2019,  2027,
    2027,  2038,  2038,  2045,  2045,  2052,  2052,  2059,  2059,  2068,
    2068,  2079,  2079,  2089,  2090,  2094,  2095,  2098,  2098,  2113,
    2113,  2123,  2123,  2134,  2135,  2139,  2143,  2143,  2155,  2156,
    2160,  2160,  2168,  2169,  2172,  2173,  2174,  2175,  2176,  2177,
    2178,  2181,  2186,  2186,  2194,  2194,  2204,  2205,  2208,  2208,
    2216,  2217,  2220,  2221,  2222,  2223,  2226,  2226,  2234,  2239,
    2244
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
#line 4932 "dhcp4_parser.cc" // lalr1.cc:1163
#line 2249 "dhcp4_parser.yy" // lalr1.cc:1164


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
