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
      case 179: // value
      case 183: // map_value
      case 221: // socket_type
      case 224: // outbound_interface_value
      case 246: // db_type
      case 328: // hr_mode
      case 475: // ncr_protocol_value
      case 483: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 163: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 162: // "floating point"
        value.copy< double > (that.value);
        break;

      case 161: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 160: // "constant string"
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
      case 179: // value
      case 183: // map_value
      case 221: // socket_type
      case 224: // outbound_interface_value
      case 246: // db_type
      case 328: // hr_mode
      case 475: // ncr_protocol_value
      case 483: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 163: // "boolean"
        value.move< bool > (that.value);
        break;

      case 162: // "floating point"
        value.move< double > (that.value);
        break;

      case 161: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 160: // "constant string"
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
      case 179: // value
      case 183: // map_value
      case 221: // socket_type
      case 224: // outbound_interface_value
      case 246: // db_type
      case 328: // hr_mode
      case 475: // ncr_protocol_value
      case 483: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 163: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 162: // "floating point"
        value.copy< double > (that.value);
        break;

      case 161: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 160: // "constant string"
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
            case 160: // "constant string"

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< std::string > (); }
#line 393 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 161: // "integer"

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 400 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 162: // "floating point"

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< double > (); }
#line 407 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 163: // "boolean"

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< bool > (); }
#line 414 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 179: // value

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 421 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 183: // map_value

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 428 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 221: // socket_type

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 435 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 224: // outbound_interface_value

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 442 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 246: // db_type

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 449 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 328: // hr_mode

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 456 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 475: // ncr_protocol_value

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 463 "dhcp4_parser.cc" // lalr1.cc:635
        break;

      case 483: // replace_client_name_value

#line 239 "dhcp4_parser.yy" // lalr1.cc:635
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
      case 179: // value
      case 183: // map_value
      case 221: // socket_type
      case 224: // outbound_interface_value
      case 246: // db_type
      case 328: // hr_mode
      case 475: // ncr_protocol_value
      case 483: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 163: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 162: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 161: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 160: // "constant string"
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
#line 248 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 715 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 249 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.CONFIG; }
#line 721 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 250 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP4; }
#line 727 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 251 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 733 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 252 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.SUBNET4; }
#line 739 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 253 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.POOLS; }
#line 745 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 254 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 751 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 255 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP4; }
#line 757 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 256 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 763 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 257 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 769 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 22:
#line 258 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 775 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 259 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 781 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 260 "dhcp4_parser.yy" // lalr1.cc:856
    { ctx.ctx_ = ctx.LOGGING; }
#line 787 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 28:
#line 268 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 793 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 29:
#line 269 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 799 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 270 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 805 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 31:
#line 271 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 811 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 32:
#line 272 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 273 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 823 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 34:
#line 274 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 829 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 35:
#line 277 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 36:
#line 282 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 849 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 37:
#line 287 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 859 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 38:
#line 293 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 865 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 41:
#line 300 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 874 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 42:
#line 304 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 884 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 43:
#line 311 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 893 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 44:
#line 314 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // list parsing complete. Put any sanity checking here
}
#line 901 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 47:
#line 322 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 48:
#line 326 "dhcp4_parser.yy" // lalr1.cc:856
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 919 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 49:
#line 333 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // List parsing about to start
}
#line 927 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 50:
#line 335 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 936 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 53:
#line 344 "dhcp4_parser.yy" // lalr1.cc:856
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 945 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 54:
#line 348 "dhcp4_parser.yy" // lalr1.cc:856
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 954 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 55:
#line 359 "dhcp4_parser.yy" // lalr1.cc:856
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 965 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 56:
#line 369 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 976 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 57:
#line 374 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 398 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 405 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 68:
#line 413 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1022 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 69:
#line 417 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No global parameter is required
    // parsing completed
}
#line 1031 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 101:
#line 459 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1040 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 102:
#line 464 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1049 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 103:
#line 469 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1058 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 104:
#line 474 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1067 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 105:
#line 479 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1076 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 106:
#line 484 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 107:
#line 490 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1096 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 108:
#line 495 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 118:
#line 514 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 119:
#line 518 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 120:
#line 523 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1136 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 121:
#line 528 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1145 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 122:
#line 533 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 123:
#line 535 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 124:
#line 540 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1168 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 125:
#line 541 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1174 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 126:
#line 544 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1182 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 127:
#line 546 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 128:
#line 551 "dhcp4_parser.yy" // lalr1.cc:856
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1199 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 129:
#line 553 "dhcp4_parser.yy" // lalr1.cc:856
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1207 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 130:
#line 557 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1216 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 131:
#line 563 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1227 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 132:
#line 568 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 133:
#line 575 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 134:
#line 580 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1258 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 138:
#line 590 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 139:
#line 592 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 608 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1297 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 141:
#line 613 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1308 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 142:
#line 620 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 143:
#line 625 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1328 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 148:
#line 638 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 149:
#line 642 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1348 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 170:
#line 672 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 171:
#line 674 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1365 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 172:
#line 679 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1371 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 173:
#line 680 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1377 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 174:
#line 681 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1383 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 175:
#line 682 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1389 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 176:
#line 685 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 177:
#line 687 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1407 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 178:
#line 693 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 179:
#line 695 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1425 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 180:
#line 701 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 181:
#line 703 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1443 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 182:
#line 709 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 183:
#line 714 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 184:
#line 716 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 185:
#line 722 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 186:
#line 727 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 187:
#line 732 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1497 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 188:
#line 737 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1506 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 189:
#line 742 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1515 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 190:
#line 747 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 191:
#line 752 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 192:
#line 757 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 193:
#line 759 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 194:
#line 765 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 195:
#line 767 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 196:
#line 773 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 197:
#line 778 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1587 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 198:
#line 783 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 199:
#line 788 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 207:
#line 804 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 208:
#line 809 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 209:
#line 814 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 210:
#line 819 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1643 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 211:
#line 824 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1652 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 212:
#line 829 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 213:
#line 834 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 218:
#line 847 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1682 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 219:
#line 851 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1692 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 220:
#line 857 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1702 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 221:
#line 861 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1712 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 227:
#line 876 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 228:
#line 878 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1730 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 229:
#line 884 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1738 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 230:
#line 886 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 231:
#line 892 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 232:
#line 897 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1768 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 241:
#line 915 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1777 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 242:
#line 920 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1786 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 243:
#line 925 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1795 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 244:
#line 930 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1804 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 245:
#line 935 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 246:
#line 940 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1822 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 247:
#line 948 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 248:
#line 953 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 253:
#line 973 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1852 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 254:
#line 977 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 999 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1888 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 256:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 282:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1906 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 283:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1916 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 284:
#line 1048 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 285:
#line 1050 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 286:
#line 1056 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1942 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 287:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1952 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 288:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1960 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 289:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1970 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 290:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1978 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 291:
#line 1074 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 292:
#line 1080 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1996 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 293:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2006 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 294:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2017 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 295:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2026 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 296:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 297:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2043 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 298:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2049 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 299:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2055 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 300:
#line 1107 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2061 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 301:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2067 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 302:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2076 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 303:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 304:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2096 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 309:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2106 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 310:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 2114 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 331:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2125 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 332:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2134 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 333:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 334:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 2151 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 339:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 340:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2173 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 341:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2183 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 342:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2195 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 358:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 360:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 361:
#line 1266 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 362:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 363:
#line 1274 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 364:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2248 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 365:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 367:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 368:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 369:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2285 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 370:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 371:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 376:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2315 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 377:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 378:
#line 1343 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2334 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 379:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 394:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 395:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 398:
#line 1392 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 399:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 400:
#line 1405 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 401:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 406:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 407:
#line 1429 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2419 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 408:
#line 1435 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2429 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 409:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2439 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 419:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 420:
#line 1460 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2457 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 421:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2465 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 422:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 2492 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 423:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 424:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:856
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
#line 2529 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 425:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 426:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 431:
#line 1539 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2559 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 432:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 433:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 434:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:856
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2587 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 454:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2595 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 455:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2605 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 456:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 457:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2623 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 458:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 459:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2641 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 460:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2649 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 461:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2659 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 462:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 463:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2679 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 464:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 465:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2697 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 466:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 467:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2715 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 468:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 469:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2733 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 470:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 471:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2751 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 472:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 473:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 474:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 475:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2787 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 476:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2798 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 477:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2807 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 478:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 479:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2827 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 482:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2838 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 483:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2847 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 486:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2857 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 487:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2867 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 504:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 505:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2885 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 506:
#line 1758 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2894 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 507:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2903 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 508:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2914 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 509:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 517:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 518:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 519:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2949 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 520:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 521:
#line 1813 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2970 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 522:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2981 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 523:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2991 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 524:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3001 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 546:
#line 1860 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3010 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 547:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3018 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 548:
#line 1867 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3028 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 549:
#line 1873 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3036 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 550:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3046 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 551:
#line 1881 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3055 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 552:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 553:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 554:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3082 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 555:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3091 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 556:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3099 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 557:
#line 1906 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3108 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 558:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3114 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 559:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:856
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3120 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 560:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3128 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 561:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3138 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 562:
#line 1924 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3147 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 563:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3156 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 564:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3165 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 565:
#line 1939 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 566:
#line 1941 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3182 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 567:
#line 1947 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3190 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 568:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3198 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 569:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3206 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 570:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:856
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3214 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 571:
#line 1959 "dhcp4_parser.yy" // lalr1.cc:856
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3223 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 572:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3231 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 573:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3241 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 574:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 575:
#line 1975 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3259 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 576:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3267 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 577:
#line 1983 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3277 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 578:
#line 1992 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 579:
#line 1994 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 580:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3302 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 581:
#line 2001 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3311 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 582:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3319 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 583:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3328 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 584:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3339 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 585:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3348 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 586:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3358 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 587:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:856
    {
    // parsing completed
}
#line 3366 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 591:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3377 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 592:
#line 2053 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3386 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 595:
#line 2065 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3396 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 596:
#line 2069 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 3404 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 606:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3413 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 607:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3421 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 608:
#line 2093 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3431 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 609:
#line 2099 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3442 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 610:
#line 2104 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3451 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 613:
#line 2113 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3461 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 614:
#line 2117 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.stack_.pop_back();
}
#line 3469 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 621:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 622:
#line 2133 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3487 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 623:
#line 2139 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3496 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 624:
#line 2144 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3505 "dhcp4_parser.cc" // lalr1.cc:856
    break;

  case 625:
#line 2149 "dhcp4_parser.yy" // lalr1.cc:856
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3514 "dhcp4_parser.cc" // lalr1.cc:856
    break;


#line 3518 "dhcp4_parser.cc" // lalr1.cc:856
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


  const short int Dhcp4Parser::yypact_ninf_ = -769;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     381,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,    53,    27,    39,    73,    79,    81,
     100,   123,   152,   161,   175,   179,   186,   197,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,    27,   -92,    25,   183,    54,    59,
      69,   401,    13,   191,   101,   -48,   449,    45,  -769,   216,
     213,   222,   242,   221,  -769,  -769,  -769,  -769,  -769,   256,
    -769,    46,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     258,   283,  -769,  -769,  -769,  -769,  -769,  -769,   304,   308,
     314,   316,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,   317,  -769,  -769,  -769,    61,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     318,  -769,   105,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,   319,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,   136,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,   164,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   268,   321,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,   278,  -769,  -769,   323,  -769,  -769,  -769,   324,
    -769,  -769,   309,   327,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,   328,   329,  -769,
    -769,  -769,  -769,   326,   332,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,   176,  -769,  -769,
    -769,   333,  -769,  -769,   335,  -769,   338,   340,  -769,  -769,
     341,   342,   343,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     210,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   212,
    -769,  -769,  -769,    27,    27,  -769,   188,   350,   353,   354,
     356,   357,  -769,    25,  -769,   359,   360,   173,   205,   366,
     367,   369,   370,   371,   377,   226,   228,   230,   231,   379,
     390,   392,   395,   406,   409,   410,   411,   413,   414,   415,
     259,   419,   420,   183,  -769,   424,   425,   426,   274,    54,
    -769,   427,   431,   435,   436,   439,   440,   284,   442,   443,
     444,   445,    59,  -769,   446,    69,  -769,   447,   448,   452,
     454,   457,   458,   459,   460,  -769,   401,  -769,   461,   463,
     292,   464,   466,   467,   315,  -769,   191,   468,   320,   322,
    -769,   101,   472,   475,   -39,  -769,   337,   476,   477,   344,
     494,   345,   351,   497,   498,   347,   348,   352,   499,   500,
     509,   510,   449,  -769,   512,    45,  -769,  -769,  -769,   513,
     511,   516,    27,    27,    27,  -769,   517,   518,  -769,  -769,
     383,   384,   385,   519,   534,   541,  -769,  -769,  -769,  -769,
     544,   545,   546,   547,   548,   393,   549,   551,   552,   553,
     569,  -769,   570,   571,  -769,   554,    64,   174,  -769,  -769,
     400,   421,   428,   574,   429,   430,  -769,    41,   554,   432,
     573,  -769,   433,  -769,   554,   434,   437,   438,   441,   450,
     451,   453,  -769,   455,   456,  -769,   462,   465,   469,  -769,
    -769,   470,  -769,  -769,  -769,   471,    27,  -769,  -769,   473,
     474,  -769,   478,  -769,  -769,    22,   479,  -769,  -769,  -769,
     -91,   480,   481,   482,  -769,   579,  -769,    27,   183,    45,
    -769,  -769,  -769,    54,   564,  -769,  -769,  -769,    57,    57,
     580,   584,   588,   589,   592,  -769,  -769,  -769,   178,   593,
     595,   596,    95,    85,   449,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,   597,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,   143,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     598,  -769,   220,   235,   270,  -769,   271,  -769,  -769,  -769,
    -769,  -769,  -769,   582,   602,   604,   608,   610,  -769,  -769,
     613,   614,   615,   616,   617,  -769,   272,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,   282,  -769,   618,   620,  -769,
    -769,   621,   623,  -769,  -769,   622,   629,  -769,  -769,   630,
     632,  -769,  -769,   631,   636,  -769,  -769,  -769,  -769,  -769,
    -769,   142,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   149,
    -769,  -769,   637,   641,  -769,  -769,   639,   643,  -769,   644,
     645,   646,   647,   648,   649,   285,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   286,  -769,
    -769,  -769,   293,   487,  -769,   650,   651,  -769,  -769,  -769,
    -769,   652,  -769,   172,  -769,  -769,  -769,  -769,   653,   564,
    -769,   654,   655,   657,   658,   502,   492,   503,   504,   505,
     661,   664,   508,   514,   515,   520,   507,    57,  -769,  -769,
      57,  -769,   580,    59,  -769,   584,   191,  -769,   588,   101,
    -769,   589,   382,  -769,   592,   178,  -769,    65,   593,  -769,
     401,  -769,   595,   -48,  -769,   596,   521,   522,   523,   524,
     525,   526,    95,  -769,   667,   668,    85,  -769,  -769,  -769,
     671,   670,    69,  -769,   597,   674,  -769,   349,   598,  -769,
     528,  -769,   215,   529,   530,   531,  -769,  -769,  -769,  -769,
    -769,   532,   533,  -769,  -769,  -769,  -769,  -769,  -769,   294,
    -769,   295,  -769,   666,  -769,   672,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   296,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     675,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     686,   692,  -769,  -769,  -769,  -769,  -769,   688,  -769,   297,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   537,   538,
    -769,  -769,   539,   303,  -769,   554,  -769,   696,  -769,  -769,
    -769,  -769,  -769,   306,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,   382,  -769,   697,   540,  -769,    65,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,   698,   543,   701,
     349,  -769,  -769,   550,  -769,  -769,   702,  -769,   555,  -769,
    -769,   699,  -769,  -769,   313,  -769,    89,   699,  -769,  -769,
     704,   705,   707,   307,  -769,  -769,  -769,  -769,  -769,  -769,
     708,   556,   557,   560,    89,  -769,   562,  -769,  -769,  -769,
    -769,  -769
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   118,     9,   255,    11,   408,    13,
     433,    15,   333,    17,   341,    19,   378,    21,   220,    23,
     523,    25,   586,    27,    45,    39,     0,     0,     0,     0,
       0,   435,     0,   343,   380,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   584,   578,   580,   582,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   107,   133,
       0,     0,   454,   456,   458,   131,   140,   142,     0,     0,
       0,     0,   247,   331,   370,   303,   421,   423,   198,   482,
     425,   212,   231,     0,   508,   521,   100,     0,    70,    72,
      73,    74,    75,    91,    92,    78,    79,    98,    80,    81,
      82,    86,    87,    76,    77,    84,    85,    96,    97,    99,
      93,    94,    95,    83,    88,    89,    90,   120,   122,   126,
       0,   117,     0,   109,   111,   112,   113,   114,   115,   116,
     284,   286,   288,   400,   282,   290,     0,   296,   294,   292,
     478,   281,   259,   260,   261,   272,     0,   257,   264,   276,
     277,   278,   265,   267,   268,   270,   266,   262,   263,   279,
     280,   269,   273,   274,   275,   271,   419,   418,   414,   415,
     413,     0,   410,   412,   416,   417,   476,   464,   466,   470,
     468,   474,   472,   460,   453,   447,   451,   452,     0,   436,
     437,   448,   449,   450,   444,   439,   445,   441,   442,   443,
     446,   440,     0,   360,   183,     0,   364,   362,   367,     0,
     356,   357,     0,   344,   345,   347,   359,   348,   349,   350,
     366,   351,   352,   353,   354,   355,   394,     0,     0,   392,
     393,   396,   397,     0,   381,   382,   384,   385,   386,   387,
     388,   389,   390,   391,   227,   229,   224,     0,   222,   225,
     226,     0,   547,   549,     0,   552,     0,     0,   556,   560,
       0,     0,     0,   565,   572,   574,   576,   545,   543,   544,
       0,   525,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   591,     0,
     588,   590,    44,     0,     0,    37,     0,     0,     0,     0,
       0,     0,    55,     0,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,     0,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   256,     0,     0,   409,     0,     0,     0,
       0,     0,     0,     0,     0,   434,     0,   334,     0,     0,
       0,     0,     0,     0,     0,   342,     0,     0,     0,     0,
     379,     0,     0,     0,     0,   221,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   524,     0,     0,   587,    48,    41,     0,
       0,     0,     0,     0,     0,    59,     0,     0,   105,   106,
       0,     0,     0,     0,     0,     0,   101,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   507,     0,     0,    71,     0,     0,     0,   130,   110,
       0,     0,     0,     0,     0,     0,   302,     0,     0,     0,
       0,   258,     0,   411,     0,     0,     0,     0,     0,     0,
       0,     0,   438,     0,     0,   358,     0,     0,     0,   369,
     346,     0,   398,   399,   383,     0,     0,   223,   546,     0,
       0,   551,     0,   554,   555,     0,     0,   562,   563,   564,
       0,     0,     0,     0,   526,     0,   589,     0,     0,     0,
     579,   581,   583,     0,     0,   455,   457,   459,     0,     0,
     144,   249,   335,   372,   305,    38,   422,   424,     0,     0,
     427,   214,     0,     0,     0,    49,   121,   124,   125,   123,
     128,   129,   127,   285,   287,   289,   402,   283,   291,   298,
     299,   300,   301,   297,   295,   293,     0,   420,   477,   465,
     467,   471,   469,   475,   473,   461,   361,   184,   365,   363,
     368,   395,   228,   230,   548,   550,   553,   558,   559,   557,
     561,   567,   568,   569,   570,   571,   566,   573,   575,   577,
       0,    42,     0,     0,     0,   138,     0,   135,   137,   170,
     176,   178,   180,     0,     0,     0,     0,     0,   192,   194,
       0,     0,     0,     0,     0,   169,     0,   150,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   165,   166,
     167,   162,   168,   163,   164,     0,   148,     0,   145,   146,
     253,     0,   250,   251,   339,     0,   336,   337,   376,     0,
     373,   374,   309,     0,   306,   307,   207,   208,   209,   210,
     211,     0,   200,   202,   203,   204,   205,   206,   486,     0,
     484,   431,     0,   428,   429,   218,     0,   215,   216,     0,
       0,     0,     0,     0,     0,     0,   233,   235,   236,   237,
     238,   239,   240,   517,   519,   516,   514,   515,     0,   510,
     512,   513,     0,    51,   406,     0,   403,   404,   462,   480,
     481,     0,   595,     0,   593,    67,   585,   108,     0,     0,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   132,   141,
       0,   143,     0,     0,   248,     0,   343,   332,     0,   380,
     371,     0,     0,   304,     0,     0,   199,   488,     0,   483,
     435,   426,     0,     0,   213,     0,     0,     0,     0,     0,
       0,     0,     0,   232,     0,     0,     0,   509,   522,    53,
       0,    52,     0,   401,     0,     0,   479,     0,     0,   592,
       0,   136,     0,     0,     0,     0,   182,   185,   186,   187,
     188,     0,     0,   196,   197,   189,   190,   191,   151,     0,
     147,     0,   252,     0,   338,     0,   375,   330,   327,   316,
     317,   319,   313,   314,   315,   325,   326,   324,     0,   311,
     318,   328,   329,   320,   321,   322,   323,   308,   201,   504,
       0,   502,   503,   495,   496,   500,   501,   497,   498,   499,
       0,   489,   490,   492,   493,   494,   485,     0,   430,     0,
     217,   241,   242,   243,   244,   245,   246,   234,     0,     0,
     511,    50,     0,     0,   405,     0,   609,     0,   607,   605,
     599,   603,   604,     0,   597,   601,   602,   600,   594,   139,
     172,   173,   174,   175,   171,   177,   179,   181,   193,   195,
     149,   254,   340,   377,     0,   310,     0,     0,   487,     0,
     432,   219,   518,   520,    54,   407,   463,     0,     0,     0,
       0,   596,   312,     0,   506,   491,     0,   606,     0,   598,
     505,     0,   608,   613,     0,   611,     0,     0,   610,   621,
       0,     0,     0,     0,   615,   617,   618,   619,   620,   612,
       0,     0,     0,     0,     0,   614,     0,   623,   624,   625,
     616,   622
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,   -51,  -769,   239,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -477,  -769,  -769,  -769,
     -66,  -769,  -769,  -769,   373,  -769,  -769,  -769,  -769,   166,
     368,   -43,   -14,    -7,  -769,  -769,    12,  -769,  -769,   171,
     346,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,   -29,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,   -38,  -769,  -536,   -25,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     -44,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   -41,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   -50,  -769,
    -769,  -769,   -52,   358,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,   -73,  -769,  -769,  -769,  -769,  -769,  -769,  -768,  -769,
    -769,  -769,   -21,  -769,  -769,  -769,   -24,   375,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -767,  -769,   -64,  -769,
     -11,  -769,  -764,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     -22,  -769,  -769,  -179,   -61,  -769,  -769,  -769,  -769,  -769,
      -8,  -769,  -769,  -769,     7,  -769,   376,  -769,   -62,  -769,
    -769,  -769,  -769,  -769,   -56,  -769,  -769,  -769,  -769,  -769,
     -13,  -769,  -769,  -769,   -16,  -769,  -769,  -769,    10,  -769,
     386,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,   -12,  -769,  -769,  -769,    -9,   405,  -769,  -769,
     -54,  -769,   -26,  -769,   -36,  -769,  -769,  -769,     8,  -769,
    -769,  -769,    14,  -769,   402,    -6,  -769,     5,  -769,     6,
    -769,   219,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -761,
    -769,  -769,  -769,  -769,  -769,    18,  -769,  -769,  -769,  -132,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,     2,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,   245,   378,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,   273,   380,  -769,  -769,
    -769,    -5,  -769,  -769,  -139,  -769,  -769,  -769,  -769,  -769,
    -769,  -153,  -769,  -769,  -168,  -769,  -769,  -769,  -769,  -769
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   566,
      82,    83,    39,    64,    79,    80,   576,   743,   820,   821,
     655,    41,    66,    91,    92,    93,   337,    43,    67,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   345,   162,
     163,    45,    68,   164,   375,   165,   376,   579,   166,   377,
     582,   167,   136,   352,   137,   346,   636,   637,   638,   758,
     138,   353,   139,   354,   677,   678,   679,   780,   656,   657,
     658,   761,   934,   659,   762,   660,   763,   661,   764,   662,
     663,   409,   664,   665,   666,   667,   668,   669,   670,   671,
     770,   672,   771,   673,   674,   140,   365,   701,   702,   703,
     704,   705,   706,   707,   141,   368,   716,   717,   718,   803,
      59,    75,   287,   288,   289,   422,   290,   423,   142,   369,
     725,   726,   727,   728,   729,   730,   731,   732,   143,   359,
     681,   682,   683,   783,    47,    69,   186,   187,   188,   385,
     189,   381,   190,   382,   191,   383,   192,   386,   193,   390,
     194,   389,   195,   388,   593,   196,   144,   362,   693,   694,
     695,   792,   868,   869,   145,   360,    53,    72,   685,   686,
     687,   786,    55,    73,   252,   253,   254,   255,   256,   257,
     258,   408,   259,   412,   260,   411,   261,   262,   413,   263,
     146,   361,   689,   690,   691,   789,    57,    74,   273,   274,
     275,   276,   277,   417,   278,   279,   280,   281,   198,   384,
     745,   746,   747,   822,    49,    70,   211,   212,   213,   394,
     147,   363,   148,   364,   149,   367,   712,   713,   714,   800,
      51,    71,   228,   229,   230,   150,   349,   151,   350,   152,
     351,   234,   404,   750,   825,   235,   398,   236,   399,   237,
     401,   238,   400,   239,   403,   240,   402,   241,   397,   205,
     391,   751,   153,   366,   709,   710,   797,   890,   891,   892,
     893,   894,   946,   895,   154,   155,   371,   738,   739,   740,
     814,   741,   815,   156,   372,    61,    76,   310,   311,   312,
     313,   427,   314,   428,   315,   316,   430,   317,   318,   319,
     433,   619,   320,   434,   321,   322,   323,   324,   438,   626,
     325,   439,   326,   440,   327,   441,    94,   339,    95,   340,
      96,   341,    97,   338,    63,    77,   329,   330,   331,   444,
     753,   754,   827,   923,   924,   925,   926,   959,   927,   957,
     974,   975,   976,   983,   984,   985,   990,   986,   987,   988
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   126,   161,   181,   207,   224,   208,   250,   269,   286,
     307,   242,   271,    78,   168,   199,   214,   226,   272,   264,
     282,   594,   308,   675,   863,   864,   182,   598,   867,   251,
     270,   876,    29,   201,    30,    84,    31,   617,   621,   622,
     623,   624,   169,   200,   215,   227,    40,   265,   283,   343,
     309,   284,   285,    28,   344,   183,   197,   210,   225,   209,
     284,   285,   184,   202,   373,   231,   157,   158,    81,   374,
     159,   113,   625,   160,   203,   204,   232,   233,   577,   578,
      42,   185,   101,   102,   103,   104,    44,   639,    46,   102,
     103,   104,   640,   641,   642,   643,   644,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,    48,   379,   108,
     109,   110,    89,   380,   170,   171,   172,   244,   114,   589,
     590,   591,   592,   113,   114,   244,   116,   117,   114,   173,
      50,   116,   117,   174,   175,   176,   177,   116,   117,   392,
     206,   116,   117,   178,   393,   795,   179,   120,   796,   618,
     879,   880,   798,   178,   180,   799,   179,   116,   117,    52,
      85,   244,   266,   245,   246,   267,   268,   395,    54,    86,
      87,    88,   396,   116,   117,   828,   863,   864,   829,   424,
     867,   328,    56,   876,   425,    89,    58,    32,    33,    34,
      35,   580,   581,    60,    98,   733,   734,   719,   720,   721,
     722,   723,   724,    99,    62,   100,   101,   102,   103,   104,
     105,   106,   107,   442,    89,   445,   333,    89,   443,    89,
     446,   243,   332,   373,   336,    89,   334,   979,   755,    89,
     980,   981,   982,   108,   109,   110,   111,   112,   445,   223,
     748,   113,   114,   756,   849,    89,   930,   931,   932,   933,
     335,   244,   115,   245,   246,   116,   117,   247,   248,   249,
     342,    89,   347,   116,   117,   118,   119,   696,   697,   698,
     699,   120,   700,   379,   759,   777,   405,    90,   757,   760,
     778,   121,   447,   448,   122,   777,   407,   348,   812,   816,
     779,   123,   124,   813,   817,   125,   442,   777,   392,   944,
     424,   818,   940,   941,   945,   951,   395,   126,   355,   960,
     994,   955,   356,   161,   961,   995,   977,   415,   357,   978,
     358,   370,   378,   387,   406,   168,   181,   410,   414,   207,
     416,   208,   418,   419,   420,   421,   458,   426,   199,   429,
     224,   214,   431,    89,   432,   435,   436,   437,   449,   182,
     250,    89,   226,   169,   450,   269,   201,   451,   452,   271,
     453,   454,   264,   456,   457,   272,   200,   282,   459,   215,
     460,   461,   251,   462,   463,   464,   307,   270,   183,   197,
     227,   465,   210,   470,   209,   184,   202,   466,   308,   467,
     265,   468,   469,   225,   471,   283,   472,   203,   204,   473,
     231,   550,   551,   552,   185,   101,   102,   103,   104,   244,
     474,   232,   233,   475,   476,   477,   309,   478,   479,   480,
     481,   116,   117,   482,   483,   102,   103,   104,   485,   486,
     487,   490,   108,   109,   110,   491,   112,   488,   956,   492,
     493,   114,   244,   494,   495,   496,   497,   498,   499,   500,
     502,   504,   505,   515,   116,   117,   506,   175,   507,   177,
     114,   508,   509,   510,   511,   513,   178,   514,   516,   179,
     517,   518,   521,   116,   117,   613,   525,   180,   519,   526,
     529,   530,   126,   522,   216,   523,   916,   161,   917,   918,
     217,   218,   219,   220,   221,   222,   631,   223,   532,   168,
     528,   535,   536,   540,   541,   531,   533,   735,   307,    89,
     537,   538,   534,   542,   543,   539,   545,   547,   548,   736,
     308,   116,   117,   549,   553,   554,   558,   169,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   559,    89,   555,   556,   557,   560,   737,   309,   561,
     562,   563,   564,   567,   568,    30,   569,   570,   571,   575,
     583,    89,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   572,   573,   574,   586,
     596,   584,   305,   306,   630,   635,   765,   676,   585,   587,
     588,   680,   595,   597,   599,   684,   688,   600,   601,   692,
     708,   602,   711,   715,   744,   752,   766,   620,   767,    89,
     603,   604,   768,   605,   769,   606,   607,   772,   773,   774,
     775,   776,   608,   782,   781,   609,   785,   784,   787,   610,
     611,   612,   788,   614,   615,   791,   790,   793,   616,   794,
     627,   628,   629,   801,   802,   804,   805,   819,   806,   807,
     808,   809,   810,   811,   824,   837,   823,   830,   832,   833,
     826,   834,   835,   836,   838,   841,   840,   839,   842,   843,
     847,   908,   909,   912,   942,   844,   845,   911,   915,   947,
     943,   846,   901,   902,   903,   904,   905,   906,   929,   935,
     936,   937,   938,   939,   948,   949,   950,   952,   953,   954,
     958,   963,   966,   964,   967,   968,   973,   971,   991,   992,
     970,   993,   996,   565,   632,   972,   455,   181,   998,   997,
     250,   999,  1001,   269,   634,   489,   857,   271,   865,   199,
     831,   881,   264,   272,   224,   282,   883,   286,   871,   907,
     182,   484,   251,   885,   850,   270,   226,   201,   862,   858,
     735,   899,   848,   882,   878,   900,   207,   200,   208,   851,
     265,   919,   736,   283,   852,   962,   872,   501,   214,   183,
     197,   886,   877,   921,   227,   856,   184,   202,   859,   870,
     854,   866,   527,   920,   884,   860,   873,   225,   203,   204,
     737,   887,   520,   853,   231,   185,   215,   874,   875,   855,
     503,   922,   888,   889,   861,   232,   233,   524,   512,   210,
     898,   209,   914,   913,   897,   749,   896,   965,   910,   742,
     544,   969,   633,   928,   989,   546,  1000,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   857,     0,
     865,     0,     0,   881,     0,     0,     0,     0,   883,     0,
     871,     0,     0,     0,   919,   885,     0,     0,     0,     0,
     862,   858,     0,     0,     0,   882,   921,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   920,     0,   872,     0,
       0,     0,     0,   886,     0,     0,     0,     0,     0,     0,
     859,   870,     0,   866,   922,     0,   884,   860,   873,     0,
       0,     0,     0,   887,     0,     0,     0,     0,     0,   874,
     875,     0,     0,     0,   888,   889,   861
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    70,    73,    74,    75,
      76,    72,    74,    64,    68,    69,    70,    71,    74,    73,
      74,   498,    76,   559,   792,   792,    69,   504,   792,    73,
      74,   792,     5,    69,     7,    10,     9,    15,   129,   130,
     131,   132,    68,    69,    70,    71,     7,    73,    74,     3,
      76,    99,   100,     0,     8,    69,    69,    70,    71,    70,
      99,   100,    69,    69,     3,    71,    12,    13,   160,     8,
      16,    58,   163,    19,    69,    69,    71,    71,    14,    15,
       7,    69,    23,    24,    25,    26,     7,    30,     7,    24,
      25,    26,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,     7,     3,    50,
      51,    52,   160,     8,    55,    56,    57,    60,    59,    78,
      79,    80,    81,    58,    59,    60,    72,    73,    59,    70,
       7,    72,    73,    74,    75,    76,    77,    72,    73,     3,
      71,    72,    73,    84,     8,     3,    87,    88,     6,   127,
      85,    86,     3,    84,    95,     6,    87,    72,    73,     7,
     135,    60,    61,    62,    63,    64,    65,     3,     7,   144,
     145,   146,     8,    72,    73,     3,   944,   944,     6,     3,
     944,   136,     7,   944,     8,   160,     7,   160,   161,   162,
     163,    17,    18,     7,    11,   110,   111,   102,   103,   104,
     105,   106,   107,    20,     7,    22,    23,    24,    25,    26,
      27,    28,    29,     3,   160,     3,     3,   160,     8,   160,
       8,    30,     6,     3,     3,   160,     4,   138,     8,   160,
     141,   142,   143,    50,    51,    52,    53,    54,     3,    96,
      97,    58,    59,     8,   780,   160,    31,    32,    33,    34,
       8,    60,    69,    62,    63,    72,    73,    66,    67,    68,
       4,   160,     4,    72,    73,    82,    83,    89,    90,    91,
      92,    88,    94,     3,     3,     3,     8,   343,     8,     8,
       8,    98,   333,   334,   101,     3,     8,     4,     3,     3,
       8,   108,   109,     8,     8,   112,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,     3,   373,     4,     3,
       3,     8,     4,   379,     8,     8,     3,     8,     4,     6,
       4,     4,     4,     4,     3,   379,   392,     4,     4,   395,
       3,   395,     4,     4,     8,     3,   163,     4,   392,     4,
     406,   395,     4,   160,     4,     4,     4,     4,   160,   392,
     416,   160,   406,   379,     4,   421,   392,     4,     4,   421,
       4,     4,   416,     4,     4,   421,   392,   421,   163,   395,
       4,     4,   416,     4,     4,     4,   442,   421,   392,   392,
     406,     4,   395,     4,   395,   392,   392,   161,   442,   161,
     416,   161,   161,   406,     4,   421,     4,   392,   392,     4,
     406,   452,   453,   454,   392,    23,    24,    25,    26,    60,
       4,   406,   406,     4,     4,     4,   442,     4,     4,     4,
     161,    72,    73,     4,     4,    24,    25,    26,     4,     4,
       4,     4,    50,    51,    52,     4,    54,   163,   915,     4,
       4,    59,    60,     4,     4,   161,     4,     4,     4,     4,
       4,     4,     4,   161,    72,    73,     4,    75,     4,    77,
      59,     4,     4,     4,     4,     4,    84,     4,     4,    87,
       4,     4,     4,    72,    73,   526,     4,    95,   163,     4,
       4,     4,   548,   163,    83,   163,   137,   553,   139,   140,
      89,    90,    91,    92,    93,    94,   547,    96,     4,   553,
     163,     4,     4,     4,     4,   161,   161,   573,   574,   160,
     163,   163,   161,     4,     4,   163,     4,     4,     7,   573,
     574,    72,    73,     7,     7,     7,     7,   553,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,     7,   160,   160,   160,   160,     5,   573,   574,     5,
       5,     5,     5,   160,     5,     7,     5,     5,     5,     5,
     160,   160,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     7,     7,     7,     5,
       7,   160,   133,   134,     5,    21,     4,     7,   160,   160,
     160,     7,   160,   160,   160,     7,     7,   160,   160,     7,
       7,   160,     7,     7,     7,     7,     4,   128,     4,   160,
     160,   160,     4,   160,     4,   160,   160,     4,     4,     4,
       4,     4,   160,     3,     6,   160,     3,     6,     6,   160,
     160,   160,     3,   160,   160,     3,     6,     6,   160,     3,
     160,   160,   160,     6,     3,     6,     3,   160,     4,     4,
       4,     4,     4,     4,     3,   163,     6,     4,     4,     4,
       8,     4,     4,   161,   161,     4,   161,   163,     4,   161,
     163,     4,     4,     3,     8,   161,   161,     6,     4,     4,
       8,   161,   161,   161,   161,   161,   161,   161,   160,   160,
     160,   160,   160,   160,     8,     3,     8,   160,   160,   160,
       4,     4,     4,   163,   161,     4,     7,     5,     4,     4,
     160,     4,     4,   474,   548,   160,   343,   783,   161,   163,
     786,   161,   160,   789,   553,   379,   792,   789,   792,   783,
     759,   797,   786,   789,   800,   789,   797,   803,   792,   812,
     783,   373,   786,   797,   782,   789,   800,   783,   792,   792,
     816,   803,   777,   797,   795,   805,   822,   783,   822,   783,
     786,   827,   816,   789,   785,   944,   792,   392,   822,   783,
     783,   797,   794,   827,   800,   791,   783,   783,   792,   792,
     788,   792,   424,   827,   797,   792,   792,   800,   783,   783,
     816,   797,   416,   786,   800,   783,   822,   792,   792,   789,
     395,   827,   797,   797,   792,   800,   800,   421,   406,   822,
     802,   822,   824,   822,   800,   596,   798,   949,   816,   574,
     442,   960,   549,   828,   977,   445,   994,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   944,    -1,
     944,    -1,    -1,   949,    -1,    -1,    -1,    -1,   949,    -1,
     944,    -1,    -1,    -1,   960,   949,    -1,    -1,    -1,    -1,
     944,   944,    -1,    -1,    -1,   949,   960,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   960,    -1,   944,    -1,
      -1,    -1,    -1,   949,    -1,    -1,    -1,    -1,    -1,    -1,
     944,   944,    -1,   944,   960,    -1,   949,   944,   944,    -1,
      -1,    -1,    -1,   949,    -1,    -1,    -1,    -1,    -1,   944,
     944,    -1,    -1,    -1,   949,   949,   944
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,     0,     5,
       7,     9,   160,   161,   162,   163,   179,   180,   181,   186,
       7,   195,     7,   201,     7,   215,     7,   308,     7,   388,
       7,   404,     7,   340,     7,   346,     7,   370,     7,   284,
       7,   459,     7,   498,   187,   182,   196,   202,   216,   309,
     389,   405,   341,   347,   371,   285,   460,   499,   179,   188,
     189,   160,   184,   185,    10,   135,   144,   145,   146,   160,
     194,   197,   198,   199,   490,   492,   494,   496,    11,    20,
      22,    23,    24,    25,    26,    27,    28,    29,    50,    51,
      52,    53,    54,    58,    59,    69,    72,    73,    82,    83,
      88,    98,   101,   108,   109,   112,   194,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   226,   228,   234,   236,
     269,   278,   292,   302,   330,   338,   364,   394,   396,   398,
     409,   411,   413,   436,   448,   449,   457,    12,    13,    16,
      19,   194,   213,   214,   217,   219,   222,   225,   394,   396,
      55,    56,    57,    70,    74,    75,    76,    77,    84,    87,
      95,   194,   205,   206,   207,   210,   310,   311,   312,   314,
     316,   318,   320,   322,   324,   326,   329,   364,   382,   394,
     396,   398,   409,   411,   413,   433,    71,   194,   322,   324,
     364,   390,   391,   392,   394,   396,    83,    89,    90,    91,
      92,    93,    94,    96,   194,   364,   394,   396,   406,   407,
     408,   409,   411,   413,   415,   419,   421,   423,   425,   427,
     429,   431,   338,    30,    60,    62,    63,    66,    67,    68,
     194,   254,   348,   349,   350,   351,   352,   353,   354,   356,
     358,   360,   361,   363,   394,   396,    61,    64,    65,   194,
     254,   352,   358,   372,   373,   374,   375,   376,   378,   379,
     380,   381,   394,   396,    99,   100,   194,   286,   287,   288,
     290,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   133,   134,   194,   394,   396,
     461,   462,   463,   464,   466,   468,   469,   471,   472,   473,
     476,   478,   479,   480,   481,   484,   486,   488,   136,   500,
     501,   502,     6,     3,     4,     8,     3,   200,   497,   491,
     493,   495,     4,     3,     8,   212,   229,     4,     4,   410,
     412,   414,   227,   235,   237,     4,     4,     4,     4,   303,
     339,   365,   331,   395,   397,   270,   437,   399,   279,   293,
       4,   450,   458,     3,     8,   218,   220,   223,     4,     3,
       8,   315,   317,   319,   383,   313,   321,     4,   327,   325,
     323,   434,     3,     8,   393,     3,     8,   432,   420,   422,
     426,   424,   430,   428,   416,     8,     3,     8,   355,   255,
       4,   359,   357,   362,     4,     8,     3,   377,     4,     4,
       8,     3,   289,   291,     3,     8,     4,   465,   467,     4,
     470,     4,     4,   474,   477,     4,     4,     4,   482,   485,
     487,   489,     3,     8,   503,     3,     8,   179,   179,   160,
       4,     4,     4,     4,     4,   198,     4,     4,   163,   163,
       4,     4,     4,     4,     4,     4,   161,   161,   161,   161,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   161,     4,     4,   204,     4,     4,     4,   163,   214,
       4,     4,     4,     4,     4,     4,   161,     4,     4,     4,
       4,   311,     4,   391,     4,     4,     4,     4,     4,     4,
       4,     4,   408,     4,     4,   161,     4,     4,     4,   163,
     350,     4,   163,   163,   374,     4,     4,   287,   163,     4,
       4,   161,     4,   161,   161,     4,     4,   163,   163,   163,
       4,     4,     4,     4,   462,     4,   501,     4,     7,     7,
     179,   179,   179,     7,     7,   160,   160,   160,     7,     7,
       5,     5,     5,     5,     5,   181,   183,   160,     5,     5,
       5,     5,     7,     7,     7,     5,   190,    14,    15,   221,
      17,    18,   224,   160,   160,   160,     5,   160,   160,    78,
      79,    80,    81,   328,   190,   160,     7,   160,   190,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   179,   160,   160,   160,    15,   127,   475,
     128,   129,   130,   131,   132,   163,   483,   160,   160,   160,
       5,   179,   203,   500,   213,    21,   230,   231,   232,    30,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,   194,   242,   243,   244,   247,
     249,   251,   253,   254,   256,   257,   258,   259,   260,   261,
     262,   263,   265,   267,   268,   242,     7,   238,   239,   240,
       7,   304,   305,   306,     7,   342,   343,   344,     7,   366,
     367,   368,     7,   332,   333,   334,    89,    90,    91,    92,
      94,   271,   272,   273,   274,   275,   276,   277,     7,   438,
     439,     7,   400,   401,   402,     7,   280,   281,   282,   102,
     103,   104,   105,   106,   107,   294,   295,   296,   297,   298,
     299,   300,   301,   110,   111,   194,   394,   396,   451,   452,
     453,   455,   461,   191,     7,   384,   385,   386,    97,   415,
     417,   435,     7,   504,   505,     8,     8,     8,   233,     3,
       8,   245,   248,   250,   252,     4,     4,     4,     4,     4,
     264,   266,     4,     4,     4,     4,     4,     3,     8,     8,
     241,     6,     3,   307,     6,     3,   345,     6,     3,   369,
       6,     3,   335,     6,     3,     3,     6,   440,     3,     6,
     403,     6,     3,   283,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   454,   456,     3,     8,     8,   160,
     192,   193,   387,     6,     3,   418,     8,   506,     3,     6,
       4,   231,     4,     4,     4,     4,   161,   163,   161,   163,
     161,     4,     4,   161,   161,   161,   161,   163,   243,   242,
     240,   310,   306,   348,   344,   372,   368,   194,   205,   206,
     207,   210,   254,   302,   320,   322,   324,   326,   336,   337,
     364,   394,   396,   409,   411,   413,   433,   334,   272,    85,
      86,   194,   254,   338,   364,   394,   396,   409,   411,   413,
     441,   442,   443,   444,   445,   447,   439,   406,   402,   286,
     282,   161,   161,   161,   161,   161,   161,   295,     4,     4,
     452,     6,     3,   390,   386,     4,   137,   139,   140,   194,
     254,   394,   396,   507,   508,   509,   510,   512,   505,   160,
      31,    32,    33,    34,   246,   160,   160,   160,   160,   160,
       8,     8,     8,     8,     3,     8,   446,     4,     8,     3,
       8,     8,   160,   160,   160,     8,   190,   513,     4,   511,
       3,     8,   337,     4,   163,   443,     4,   161,     4,   508,
     160,     5,   160,     7,   514,   515,   516,     3,     6,   138,
     141,   142,   143,   517,   518,   519,   521,   522,   523,   515,
     520,     4,     4,     4,     3,     8,     4,   163,   161,   161,
     518,   160
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   164,   166,   165,   167,   165,   168,   165,   169,   165,
     170,   165,   171,   165,   172,   165,   173,   165,   174,   165,
     175,   165,   176,   165,   177,   165,   178,   165,   179,   179,
     179,   179,   179,   179,   179,   180,   182,   181,   183,   184,
     184,   185,   185,   187,   186,   188,   188,   189,   189,   191,
     190,   192,   192,   193,   193,   194,   196,   195,   197,   197,
     198,   198,   198,   198,   198,   198,   200,   199,   202,   201,
     203,   203,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   205,   206,   207,   208,   209,   210,   212,   211,   213,
     213,   214,   214,   214,   214,   214,   214,   214,   216,   215,
     218,   217,   220,   219,   221,   221,   223,   222,   224,   224,
     225,   227,   226,   229,   228,   230,   230,   231,   233,   232,
     235,   234,   237,   236,   238,   238,   239,   239,   241,   240,
     242,   242,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     245,   244,   246,   246,   246,   246,   248,   247,   250,   249,
     252,   251,   253,   255,   254,   256,   257,   258,   259,   260,
     261,   262,   264,   263,   266,   265,   267,   268,   270,   269,
     271,   271,   272,   272,   272,   272,   272,   273,   274,   275,
     276,   277,   279,   278,   280,   280,   281,   281,   283,   282,
     285,   284,   286,   286,   286,   287,   287,   289,   288,   291,
     290,   293,   292,   294,   294,   295,   295,   295,   295,   295,
     295,   296,   297,   298,   299,   300,   301,   303,   302,   304,
     304,   305,   305,   307,   306,   309,   308,   310,   310,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   313,   312,   315,   314,   317,   316,   319,   318,
     321,   320,   323,   322,   325,   324,   327,   326,   328,   328,
     328,   328,   329,   331,   330,   332,   332,   333,   333,   335,
     334,   336,   336,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   339,   338,   341,   340,   342,   342,   343,   343,   345,
     344,   347,   346,   348,   348,   349,   349,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   351,   352,   353,
     355,   354,   357,   356,   359,   358,   360,   362,   361,   363,
     365,   364,   366,   366,   367,   367,   369,   368,   371,   370,
     372,   372,   373,   373,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   375,   377,   376,   378,   379,   380,   381,
     383,   382,   384,   384,   385,   385,   387,   386,   389,   388,
     390,   390,   391,   391,   391,   391,   391,   391,   391,   393,
     392,   395,   394,   397,   396,   399,   398,   400,   400,   401,
     401,   403,   402,   405,   404,   406,   406,   407,   407,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   410,   409,   412,   411,   414,   413,
     416,   415,   418,   417,   420,   419,   422,   421,   424,   423,
     426,   425,   428,   427,   430,   429,   432,   431,   434,   433,
     435,   435,   437,   436,   438,   438,   440,   439,   441,   441,
     442,   442,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   444,   446,   445,   447,   448,   450,   449,
     451,   451,   452,   452,   452,   452,   452,   454,   453,   456,
     455,   458,   457,   460,   459,   461,   461,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   463,   465,   464,   467,
     466,   468,   470,   469,   471,   472,   474,   473,   475,   475,
     477,   476,   478,   479,   480,   482,   481,   483,   483,   483,
     483,   483,   485,   484,   487,   486,   489,   488,   491,   490,
     493,   492,   495,   494,   497,   496,   499,   498,   500,   500,
     501,   503,   502,   504,   504,   506,   505,   507,   507,   508,
     508,   508,   508,   508,   508,   508,   509,   511,   510,   513,
     512,   514,   514,   516,   515,   517,   517,   518,   518,   518,
     518,   520,   519,   521,   522,   523
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
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
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
  "hr_mode", "id", "shared_networks", "$@56", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@57",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@58", "sub_option_def_list", "$@59", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@60",
  "sub_option_def", "$@61", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@62",
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
       0,   248,   248,   248,   249,   249,   250,   250,   251,   251,
     252,   252,   253,   253,   254,   254,   255,   255,   256,   256,
     257,   257,   258,   258,   259,   259,   260,   260,   268,   269,
     270,   271,   272,   273,   274,   277,   282,   282,   293,   296,
     297,   300,   304,   311,   311,   318,   319,   322,   326,   333,
     333,   340,   341,   344,   348,   359,   369,   369,   385,   386,
     390,   391,   392,   393,   394,   395,   398,   398,   413,   413,
     422,   423,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   459,   464,   469,   474,   479,   484,   490,   490,   501,
     502,   505,   506,   507,   508,   509,   510,   511,   514,   514,
     523,   523,   533,   533,   540,   541,   544,   544,   551,   553,
     557,   563,   563,   575,   575,   585,   586,   588,   590,   590,
     608,   608,   620,   620,   630,   631,   634,   635,   638,   638,
     648,   649,   652,   653,   654,   655,   656,   657,   658,   659,
     660,   661,   662,   663,   664,   665,   666,   667,   668,   669,
     672,   672,   679,   680,   681,   682,   685,   685,   693,   693,
     701,   701,   709,   714,   714,   722,   727,   732,   737,   742,
     747,   752,   757,   757,   765,   765,   773,   778,   783,   783,
     793,   794,   797,   798,   799,   800,   801,   804,   809,   814,
     819,   824,   829,   829,   839,   840,   843,   844,   847,   847,
     857,   857,   867,   868,   869,   872,   873,   876,   876,   884,
     884,   892,   892,   903,   904,   907,   908,   909,   910,   911,
     912,   915,   920,   925,   930,   935,   940,   948,   948,   961,
     962,   965,   966,   973,   973,   999,   999,  1010,  1011,  1015,
    1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,
    1036,  1037,  1040,  1040,  1048,  1048,  1056,  1056,  1064,  1064,
    1072,  1072,  1080,  1080,  1088,  1088,  1098,  1098,  1105,  1106,
    1107,  1108,  1111,  1118,  1118,  1129,  1130,  1134,  1135,  1138,
    1138,  1146,  1147,  1150,  1151,  1152,  1153,  1154,  1155,  1156,
    1157,  1158,  1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,
    1167,  1174,  1174,  1187,  1187,  1196,  1197,  1200,  1201,  1206,
    1206,  1221,  1221,  1235,  1236,  1239,  1240,  1243,  1244,  1245,
    1246,  1247,  1248,  1249,  1250,  1251,  1252,  1255,  1257,  1262,
    1264,  1264,  1272,  1272,  1280,  1280,  1288,  1290,  1290,  1298,
    1307,  1307,  1319,  1320,  1325,  1326,  1331,  1331,  1343,  1343,
    1355,  1356,  1361,  1362,  1367,  1368,  1369,  1370,  1371,  1372,
    1373,  1374,  1375,  1378,  1380,  1380,  1388,  1390,  1392,  1397,
    1405,  1405,  1417,  1418,  1421,  1422,  1425,  1425,  1435,  1435,
    1445,  1446,  1449,  1450,  1451,  1452,  1453,  1454,  1455,  1458,
    1458,  1466,  1466,  1491,  1491,  1521,  1521,  1531,  1532,  1535,
    1536,  1539,  1539,  1548,  1548,  1557,  1558,  1561,  1562,  1566,
    1567,  1568,  1569,  1570,  1571,  1572,  1573,  1574,  1575,  1576,
    1577,  1578,  1579,  1580,  1583,  1583,  1591,  1591,  1599,  1599,
    1607,  1607,  1615,  1615,  1625,  1625,  1633,  1633,  1641,  1641,
    1649,  1649,  1657,  1657,  1665,  1665,  1673,  1673,  1686,  1686,
    1696,  1697,  1703,  1703,  1713,  1714,  1717,  1717,  1727,  1728,
    1731,  1732,  1735,  1736,  1737,  1738,  1739,  1740,  1741,  1742,
    1743,  1744,  1745,  1748,  1750,  1750,  1758,  1767,  1774,  1774,
    1784,  1785,  1788,  1789,  1790,  1791,  1792,  1795,  1795,  1803,
    1803,  1813,  1813,  1825,  1825,  1835,  1836,  1839,  1840,  1841,
    1842,  1843,  1844,  1845,  1846,  1847,  1848,  1849,  1850,  1851,
    1852,  1853,  1854,  1855,  1856,  1857,  1860,  1865,  1865,  1873,
    1873,  1881,  1886,  1886,  1894,  1899,  1904,  1904,  1912,  1913,
    1916,  1916,  1924,  1929,  1934,  1939,  1939,  1947,  1950,  1953,
    1956,  1959,  1965,  1965,  1973,  1973,  1981,  1981,  1992,  1992,
    1999,  1999,  2006,  2006,  2018,  2018,  2028,  2028,  2039,  2040,
    2044,  2048,  2048,  2060,  2061,  2065,  2065,  2073,  2074,  2077,
    2078,  2079,  2080,  2081,  2082,  2083,  2086,  2091,  2091,  2099,
    2099,  2109,  2110,  2113,  2113,  2121,  2122,  2125,  2126,  2127,
    2128,  2131,  2131,  2139,  2144,  2149
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
#line 4756 "dhcp4_parser.cc" // lalr1.cc:1163
#line 2154 "dhcp4_parser.yy" // lalr1.cc:1164


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
