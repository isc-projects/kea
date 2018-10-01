// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

#line 39 "dhcp4_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp4_parser.h"

// User implementation prologue.

#line 53 "dhcp4_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:413

#include <dhcp4/parser_context.h>

#line 59 "dhcp4_parser.cc" // lalr1.cc:413


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
      *yycdebug_ << std::endl;                  \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc" // lalr1.cc:479

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
  inline
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 184: // value
      case 188: // map_value
      case 228: // socket_type
      case 231: // outbound_interface_value
      case 253: // db_type
      case 335: // hr_mode
      case 482: // ncr_protocol_value
      case 490: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 167: // "boolean"
        value.move< bool > (that.value);
        break;

      case 166: // "floating point"
        value.move< double > (that.value);
        break;

      case 165: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 164: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 184: // value
      case 188: // map_value
      case 228: // socket_type
      case 231: // outbound_interface_value
      case 253: // db_type
      case 335: // hr_mode
      case 482: // ncr_protocol_value
      case 490: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 167: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 166: // "floating point"
        value.copy< double > (that.value);
        break;

      case 165: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 164: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
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
            case 164: // "constant string"

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 165: // "integer"

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 166: // "floating point"

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 167: // "boolean"

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 184: // value

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 188: // map_value

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 228: // socket_type

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 231: // outbound_interface_value

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 253: // db_type

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 335: // hr_mode

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 482: // ncr_protocol_value

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 490: // replace_client_name_value

#line 243 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp4Parser::yypop_ (unsigned int n)
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

  inline Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
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
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

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
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 184: // value
      case 188: // map_value
      case 228: // socket_type
      case 231: // outbound_interface_value
      case 253: // db_type
      case 335: // hr_mode
      case 482: // ncr_protocol_value
      case 490: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 167: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 166: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 165: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 164: // "constant string"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 298 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 327 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 349 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 353 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 374 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1285 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1355 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 694 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 992 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1115 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1138 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1225 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2295 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2491 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2567 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1919 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1928 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1962 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1968 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1971 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1974 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3345 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3376 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2129 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3481 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2163 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3519 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2177 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2197 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 641:
#line 2203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 642:
#line 2208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 643:
#line 2213 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3591 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3595 "dhcp4_parser.cc" // lalr1.cc:859
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
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
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
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
    error (yyexc.location, yyexc.what());
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
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const short int Dhcp4Parser::yypact_ninf_ = -794;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     328,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,    38,    24,    42,    53,    57,
     105,   129,   143,   150,   152,   161,   173,   186,   188,   196,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,    24,    -9,
      13,    52,    70,   148,   185,   223,   125,   391,    35,   -49,
     450,    66,    34,  -794,   205,   189,   215,   212,   226,  -794,
    -794,  -794,  -794,  -794,   227,  -794,    86,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   233,   244,  -794,
    -794,  -794,  -794,  -794,  -794,   260,   261,   270,   276,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   279,  -794,  -794,  -794,    87,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     282,  -794,   113,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   283,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   146,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   162,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   222,   290,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,   292,  -794,  -794,   297,  -794,  -794,  -794,   303,
    -794,  -794,   302,   308,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   334,   337,  -794,
    -794,  -794,  -794,   340,   339,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   163,  -794,  -794,
    -794,   346,  -794,  -794,   347,  -794,   349,   352,  -794,  -794,
     353,   354,   356,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     175,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   176,
    -794,  -794,  -794,  -794,   179,  -794,  -794,  -794,    24,    24,
    -794,   197,   364,   366,   367,   370,   373,  -794,    13,  -794,
      34,   374,   378,   379,   217,   218,   384,   387,   389,   390,
     393,   394,   235,   240,   242,   246,   408,   415,   416,   417,
     421,   422,   424,   443,   448,   449,   451,   455,   300,   464,
     465,    52,  -794,   466,   467,   468,   306,    70,  -794,   470,
     471,   488,   489,   490,   491,   331,   493,   494,   495,   496,
     148,  -794,   497,   185,  -794,   498,   499,   501,   503,   504,
     505,   506,   508,  -794,   223,  -794,   509,   510,   350,   514,
     515,   516,   355,  -794,   391,   517,   357,   360,  -794,    35,
     524,   526,   -55,  -794,   368,   527,   530,   371,   533,   375,
     376,   534,   535,   380,   381,   382,   538,   542,   546,   547,
     450,  -794,   549,    66,  -794,   550,    34,  -794,  -794,  -794,
     552,   551,   553,    24,    24,    24,  -794,   201,   554,   555,
     556,  -794,  -794,   418,   419,   420,   573,   574,   580,  -794,
    -794,  -794,  -794,   425,   583,   585,   586,   587,   588,   429,
     589,   591,   592,   593,   594,  -794,   595,   596,  -794,   599,
      80,    67,  -794,  -794,   435,   436,   441,   601,   444,   445,
    -794,   252,   599,   446,   600,  -794,   447,  -794,   599,   452,
     453,   454,   456,   457,   458,   459,  -794,   460,   461,  -794,
     462,   463,   469,  -794,  -794,   472,  -794,  -794,  -794,   473,
      24,  -794,  -794,   474,   475,  -794,   476,  -794,  -794,    28,
     426,  -794,  -794,  -794,   -15,   477,   478,   479,  -794,   607,
    -794,   608,  -794,    24,    52,    66,  -794,  -794,  -794,  -794,
      34,    70,   605,  -794,  -794,  -794,   395,   395,   612,  -794,
     622,   623,   624,   625,  -794,  -794,  -794,    47,   627,   628,
     637,   147,    17,   450,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,   638,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,   -28,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   639,
     612,  -794,   210,   214,   237,   255,  -794,   259,  -794,  -794,
    -794,  -794,  -794,  -794,   611,   643,   644,   645,   646,  -794,
    -794,   647,   648,   649,   650,   651,  -794,   263,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   273,  -794,   652,   653,
    -794,  -794,   654,   656,  -794,  -794,   655,   659,  -794,  -794,
     657,   661,  -794,  -794,   660,   662,  -794,  -794,  -794,  -794,
    -794,  -794,    55,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     119,  -794,  -794,   663,   664,  -794,  -794,   665,   667,  -794,
     668,   669,   670,   671,   672,   673,   274,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   281,
    -794,  -794,  -794,   287,   518,  -794,   674,   675,  -794,  -794,
    -794,  -794,   676,  -794,   120,  -794,   677,  -794,  -794,  -794,
    -794,   681,   605,  -794,   682,   683,   684,   685,   492,   512,
     525,   528,   529,   687,   688,   531,   532,   536,   537,   539,
     395,  -794,  -794,   395,  -794,   612,   148,  -794,   622,   391,
    -794,   623,    35,  -794,   624,   216,  -794,   625,    47,  -794,
     388,   627,  -794,   223,  -794,   628,   -49,  -794,   637,   540,
     543,   544,   545,   548,   557,   147,  -794,   689,   694,    17,
    -794,  -794,  -794,   693,   678,   185,  -794,   638,   696,  -794,
      72,   639,  -794,  -794,   559,  -794,   311,   560,   561,   562,
    -794,  -794,  -794,  -794,  -794,   563,   564,  -794,  -794,  -794,
    -794,  -794,  -794,   294,  -794,   305,  -794,   695,  -794,   699,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,   320,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   700,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   703,   709,  -794,  -794,  -794,  -794,
    -794,   706,  -794,   321,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,   565,   566,  -794,  -794,   567,   322,  -794,   599,
    -794,   711,  -794,  -794,  -794,  -794,  -794,   323,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   216,  -794,
     712,   568,  -794,   388,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   713,   569,   714,    72,  -794,  -794,   572,  -794,  -794,
     715,  -794,   575,  -794,  -794,   725,  -794,  -794,   166,  -794,
     -12,   725,  -794,  -794,   717,   729,   733,   329,  -794,  -794,
    -794,  -794,  -794,  -794,   734,   577,   576,   582,   -12,  -794,
     578,  -794,  -794,  -794,  -794,  -794
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   124,     9,   261,    11,
     414,    13,   439,    15,   339,    17,   347,    19,   384,    21,
     226,    23,   529,    25,   604,    27,   594,    29,    47,    41,
       0,     0,     0,     0,     0,   441,     0,   349,   386,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     602,   584,   586,   588,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   590,   592,   113,   139,     0,     0,   460,
     462,   464,   137,   146,   148,     0,     0,     0,     0,   109,
     253,   337,   376,   309,   427,   429,   204,   488,   431,   218,
     237,     0,   514,   527,   104,     0,    72,    74,    75,    76,
      77,   103,    93,    94,    80,    81,   100,    82,    83,    84,
      88,    89,    78,    79,    86,    87,    98,    99,   101,    95,
      96,    97,    85,    90,    91,    92,   102,   126,   128,   132,
       0,   123,     0,   115,   117,   118,   119,   120,   121,   122,
     290,   292,   294,   406,   288,   296,     0,   302,   300,   298,
     484,   287,   265,   266,   267,   278,     0,   263,   270,   282,
     283,   284,   271,   273,   274,   276,   272,   268,   269,   285,
     286,   275,   279,   280,   281,   277,   425,   424,   420,   421,
     419,     0,   416,   418,   422,   423,   482,   470,   472,   476,
     474,   480,   478,   466,   459,   453,   457,   458,     0,   442,
     443,   454,   455,   456,   450,   445,   451,   447,   448,   449,
     452,   446,     0,   366,   189,     0,   370,   368,   373,     0,
     362,   363,     0,   350,   351,   353,   365,   354,   355,   356,
     372,   357,   358,   359,   360,   361,   400,     0,     0,   398,
     399,   402,   403,     0,   387,   388,   390,   391,   392,   393,
     394,   395,   396,   397,   233,   235,   230,     0,   228,   231,
     232,     0,   553,   555,     0,   558,     0,     0,   562,   566,
       0,     0,     0,   571,   578,   580,   582,   551,   549,   550,
       0,   531,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   609,     0,
     606,   608,   600,   599,     0,   596,   598,    46,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    57,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   262,     0,     0,   415,     0,     0,     0,     0,     0,
       0,     0,     0,   440,     0,   340,     0,     0,     0,     0,
       0,     0,     0,   348,     0,     0,     0,     0,   385,     0,
       0,     0,     0,   227,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   530,     0,     0,   605,     0,     0,   595,    50,    43,
       0,     0,     0,     0,     0,     0,    61,     0,     0,     0,
       0,   111,   112,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   513,     0,     0,    73,     0,
       0,     0,   136,   116,     0,     0,     0,     0,     0,     0,
     308,     0,     0,     0,     0,   264,     0,   417,     0,     0,
       0,     0,     0,     0,     0,     0,   444,     0,     0,   364,
       0,     0,     0,   375,   352,     0,   404,   405,   389,     0,
       0,   229,   552,     0,     0,   557,     0,   560,   561,     0,
       0,   568,   569,   570,     0,     0,     0,     0,   532,     0,
     607,     0,   597,     0,     0,     0,   585,   587,   589,   591,
       0,     0,     0,   461,   463,   465,     0,     0,   150,   110,
     255,   341,   378,   311,    40,   428,   430,     0,     0,   433,
     220,     0,     0,     0,    51,   127,   130,   131,   129,   134,
     135,   133,   291,   293,   295,   408,   289,   297,   304,   305,
     306,   307,   303,   301,   299,     0,   426,   483,   471,   473,
     477,   475,   481,   479,   467,   367,   190,   371,   369,   374,
     401,   234,   236,   554,   556,   559,   564,   565,   563,   567,
     573,   574,   575,   576,   577,   572,   579,   581,   583,     0,
     150,    44,     0,     0,     0,     0,   144,     0,   141,   143,
     176,   182,   184,   186,     0,     0,     0,     0,     0,   198,
     200,     0,     0,     0,     0,     0,   175,     0,   156,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   171,
     172,   173,   168,   174,   169,   170,     0,   154,     0,   151,
     152,   259,     0,   256,   257,   345,     0,   342,   343,   382,
       0,   379,   380,   315,     0,   312,   313,   213,   214,   215,
     216,   217,     0,   206,   208,   209,   210,   211,   212,   492,
       0,   490,   437,     0,   434,   435,   224,     0,   221,   222,
       0,     0,     0,     0,     0,     0,     0,   239,   241,   242,
     243,   244,   245,   246,   523,   525,   522,   520,   521,     0,
     516,   518,   519,     0,    53,   412,     0,   409,   410,   468,
     486,   487,     0,   613,     0,   611,     0,    69,   603,   593,
     114,     0,     0,   140,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   138,   147,     0,   149,     0,     0,   254,     0,   349,
     338,     0,   386,   377,     0,     0,   310,     0,     0,   205,
     494,     0,   489,   441,   432,     0,     0,   219,     0,     0,
       0,     0,     0,     0,     0,     0,   238,     0,     0,     0,
     515,   528,    55,     0,    54,     0,   407,     0,     0,   485,
       0,     0,   610,   601,     0,   142,     0,     0,     0,     0,
     188,   191,   192,   193,   194,     0,     0,   202,   203,   195,
     196,   197,   157,     0,   153,     0,   258,     0,   344,     0,
     381,   336,   333,   322,   323,   325,   319,   320,   321,   331,
     332,   330,     0,   317,   324,   334,   335,   326,   327,   328,
     329,   314,   207,   510,     0,   508,   509,   501,   502,   506,
     507,   503,   504,   505,     0,   495,   496,   498,   499,   500,
     491,     0,   436,     0,   223,   247,   248,   249,   250,   251,
     252,   240,     0,     0,   517,    52,     0,     0,   411,     0,
     627,     0,   625,   623,   617,   621,   622,     0,   615,   619,
     620,   618,   612,   145,   178,   179,   180,   181,   177,   183,
     185,   187,   199,   201,   155,   260,   346,   383,     0,   316,
       0,     0,   493,     0,   438,   225,   524,   526,    56,   413,
     469,     0,     0,     0,     0,   614,   318,     0,   512,   497,
       0,   624,     0,   616,   511,     0,   626,   631,     0,   629,
       0,     0,   628,   639,     0,     0,     0,     0,   633,   635,
     636,   637,   638,   630,     0,     0,     0,     0,     0,   632,
       0,   641,   642,   643,   634,   640
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   -44,  -794,   170,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -501,  -794,  -794,
    -794,   -70,  -794,  -794,  -794,   361,  -794,  -794,  -794,  -794,
     171,   359,   -48,   -45,   -43,  -794,  -794,  -794,  -794,   -11,
    -794,  -794,   167,   362,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     -41,  -794,  -794,  -794,  -794,  -794,  -794,    93,  -794,   -61,
    -794,  -581,   -53,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   -26,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   -54,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,   -68,  -794,  -794,  -794,   -50,   341,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,   -69,  -794,  -794,  -794,  -794,  -794,
    -794,  -793,  -794,  -794,  -794,   -30,  -794,  -794,  -794,   -27,
     396,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -784,
    -794,   -24,  -794,    -4,  -794,  -782,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   -33,  -794,  -794,  -178,   -65,  -794,  -794,
    -794,  -794,  -794,   -13,  -794,  -794,  -794,   -16,  -794,   386,
    -794,   -66,  -794,  -794,  -794,  -794,  -794,   -60,  -794,  -794,
    -794,  -794,  -794,   -18,  -794,  -794,  -794,     4,  -794,  -794,
    -794,     7,  -794,   397,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,   -25,  -794,  -794,  -794,   -42,
     427,  -794,  -794,   -58,  -794,   -38,  -794,   -47,  -794,  -794,
    -794,     3,  -794,  -794,  -794,     2,  -794,   423,    -7,  -794,
      -6,  -794,     0,  -794,   219,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -781,  -794,  -794,  -794,  -794,  -794,     8,  -794,
    -794,  -794,  -142,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,    -3,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     239,   383,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -347,   392,  -794,  -794,  -794,  -794,  -794,  -794,   275,   385,
    -794,  -794,  -794,    -8,  -794,  -794,  -149,  -794,  -794,  -794,
    -794,  -794,  -794,  -162,  -794,  -794,  -176,  -794,  -794,  -794,
    -794,  -794
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     595,    87,    88,    41,    68,    84,    85,   605,   774,   853,
     854,   343,    43,    70,    96,    97,    98,   352,    45,    71,
     135,   136,   137,   138,   139,   140,   141,   376,   142,   143,
     144,   362,   172,   173,    47,    72,   174,   393,   175,   394,
     608,   176,   395,   611,   177,   145,   369,   146,   363,   667,
     668,   669,   791,   147,   370,   148,   371,   708,   709,   710,
     813,   687,   688,   689,   794,   968,   690,   795,   691,   796,
     692,   797,   693,   694,   427,   695,   696,   697,   698,   699,
     700,   701,   702,   803,   703,   804,   704,   705,   149,   383,
     732,   733,   734,   735,   736,   737,   738,   150,   386,   747,
     748,   749,   836,    61,    79,   297,   298,   299,   440,   300,
     441,   151,   387,   756,   757,   758,   759,   760,   761,   762,
     763,   152,   377,   712,   713,   714,   816,    49,    73,   196,
     197,   198,   403,   199,   399,   200,   400,   201,   401,   202,
     404,   203,   408,   204,   407,   205,   406,   622,   206,   153,
     380,   724,   725,   726,   825,   902,   903,   154,   378,    55,
      76,   716,   717,   718,   819,    57,    77,   262,   263,   264,
     265,   266,   267,   268,   426,   269,   430,   270,   429,   271,
     272,   431,   273,   155,   379,   720,   721,   722,   822,    59,
      78,   283,   284,   285,   286,   287,   435,   288,   289,   290,
     291,   208,   402,   776,   777,   778,   855,    51,    74,   221,
     222,   223,   412,   156,   381,   157,   382,   158,   385,   743,
     744,   745,   833,    53,    75,   238,   239,   240,   159,   366,
     160,   367,   161,   368,   244,   422,   781,   858,   245,   416,
     246,   417,   247,   419,   248,   418,   249,   421,   250,   420,
     251,   415,   215,   409,   782,   162,   384,   740,   741,   830,
     924,   925,   926,   927,   928,   980,   929,   163,   164,   389,
     769,   770,   771,   847,   772,   848,   165,   390,    63,    80,
     320,   321,   322,   323,   445,   324,   446,   325,   326,   448,
     327,   328,   329,   451,   648,   330,   452,   331,   332,   333,
     334,   456,   655,   335,   457,   336,   458,   337,   459,    99,
     354,   100,   355,   101,   356,   166,   360,   361,    67,    82,
     344,   345,   346,   465,   102,   353,    65,    81,   339,   340,
     341,   462,   784,   785,   860,   957,   958,   959,   960,   993,
     961,   991,  1008,  1009,  1010,  1017,  1018,  1019,  1024,  1020,
    1021,  1022
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   134,   171,   191,   217,   234,   706,   260,   279,   296,
     317,   252,   281,   477,   178,   209,   224,   236,   282,   274,
     292,   623,   318,    89,    83,   192,   211,   627,   193,    31,
     194,    32,   897,    33,   179,   210,   225,   237,    30,   275,
     293,   898,   319,   901,   910,   646,   342,   294,   295,    42,
     218,   261,   280,   294,   295,   207,   220,   235,   828,   103,
      44,   829,   195,   104,    46,   105,   212,   213,   241,   242,
     219,   233,   779,   214,   106,   243,   107,   108,   109,   110,
     111,   112,   113,   114,   167,   168,   609,   610,   169,   358,
     391,   170,   124,   125,   359,   392,   606,   607,   254,   276,
     255,   256,   277,   278,   115,   116,   117,   118,   119,   120,
     124,   125,    48,   121,   122,    94,   397,   650,   651,   652,
     653,   398,   831,   861,   123,   832,   862,   124,   125,  1013,
     764,   765,  1014,  1015,  1016,   254,    50,   126,   127,   727,
     728,   729,   730,   128,   731,   124,   125,   124,   125,   410,
      52,    90,   654,   129,   411,    86,   130,    54,   647,    56,
      91,    92,    93,   131,   132,   413,   442,   133,    58,  1011,
     414,   443,  1012,   108,   109,   110,   111,    94,   460,   463,
      60,    94,   466,   461,   464,   897,   121,   467,    34,    35,
      36,    37,   348,    62,   898,    64,   901,   910,    94,    94,
     115,   116,   117,    66,   466,   338,   180,   181,   182,   579,
     122,   347,   950,   391,   951,   952,    94,   463,   787,   349,
     350,   183,   788,   124,   125,   184,   185,   186,   187,   351,
     423,   357,   883,   664,    94,   188,    94,   364,   189,   128,
     466,   108,   109,   110,   111,   789,   190,   122,   365,   109,
     110,   111,   750,   751,   752,   753,   754,   755,   397,   216,
     124,   125,   792,   790,   372,   373,   810,   793,   115,   116,
     117,   811,   188,   120,   374,   189,   810,   845,   122,   254,
     375,   812,   846,   388,   849,   122,   396,   405,    95,   850,
     460,   124,   125,   424,   185,   851,   187,   810,   124,   125,
     425,   428,   974,   188,   468,   469,   189,   432,   410,   226,
     433,   434,    94,   975,   190,   227,   228,   229,   230,   231,
     232,   134,   233,   978,   442,   413,   994,   171,   979,   985,
     989,   995,  1028,   618,   619,   620,   621,  1029,   436,   178,
     191,   437,   439,   217,   964,   965,   966,   967,   438,    94,
     444,   447,   209,   449,   234,   224,   450,   453,   454,   179,
     455,   470,   192,   211,   260,   193,   236,   194,   471,   279,
     472,   473,   210,   281,   474,   225,   274,   475,   478,   282,
      94,   292,   479,   480,   481,   482,   237,    94,   483,   218,
     317,   484,   207,   485,   486,   220,   275,   487,   488,   195,
     489,   293,   318,   212,   213,   490,   235,   491,   261,   219,
     214,   492,   493,   280,   109,   110,   111,   241,   242,   494,
     495,   496,   319,   253,   243,   497,   498,   670,   499,   576,
     577,   578,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   684,   685,   500,   990,   121,
     122,   254,   501,   502,   254,   503,   255,   256,   254,   504,
     257,   258,   259,   124,   125,   505,   124,   125,   506,   507,
     509,   510,   511,   512,   514,   515,   913,   914,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   526,   528,   529,   134,   530,   642,   531,   532,   533,
     534,   171,   535,   537,   538,   539,   686,   686,   540,   541,
     542,   545,   543,   178,   546,   124,   125,   547,   549,   661,
     550,   553,   766,   317,   554,   552,   555,   556,   559,   560,
     557,   558,   564,   179,   767,   318,   565,   561,   562,   563,
     566,   567,    94,   569,   571,    94,   573,   649,   574,    94,
     575,   580,   581,   582,   768,   319,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     586,   587,   583,   584,   585,   588,   315,   316,   590,   589,
     591,   592,   593,   596,   597,    32,   598,   599,   600,   612,
     613,   601,   602,   603,   604,   614,   615,   625,   616,   617,
     624,   626,   659,   660,    94,   798,   628,   629,   630,   707,
     631,   632,   633,   634,   635,   636,   637,   638,   666,   711,
     715,   719,   723,   639,   739,   742,   640,   641,   643,   644,
     645,   656,   657,   658,   746,   775,   783,   799,   800,   801,
     802,   805,   806,   807,   808,   809,   815,   870,   814,   818,
     817,   820,   821,   823,   824,   827,   826,   835,   594,   834,
     838,   837,   839,   840,   841,   842,   843,   844,   857,   871,
     856,   946,   852,   863,   859,   864,   866,   867,   868,   869,
     872,   875,   876,   942,   874,   873,   877,   878,   943,   945,
     949,   879,   880,   976,   981,   935,   881,   977,   936,   937,
     938,   982,   983,   939,   984,   992,   997,  1000,  1002,   476,
    1005,  1025,   940,   963,   969,   970,   971,   972,   973,   986,
     987,   988,  1007,  1026,  1001,   998,  1004,  1027,  1030,  1006,
     686,  1032,  1035,   686,  1031,   662,   191,  1033,   665,   260,
     508,   865,   279,   786,   884,   891,   281,   882,   209,   513,
     915,   274,   282,   234,   292,   917,   296,   905,   192,   211,
     934,   193,   919,   194,   912,   236,   941,   892,   210,   766,
     893,   275,   894,   551,   293,   217,   933,   906,   886,   885,
     953,   767,   920,   261,   911,   237,   280,   224,   207,   896,
     996,   899,   955,   887,   916,   195,   525,   904,   888,   212,
     213,   768,   918,   947,   895,   235,   214,   225,   907,   908,
     544,   900,   956,   921,   922,   909,   241,   242,   890,   889,
     923,   218,   948,   243,   954,   931,   548,   220,   932,   930,
     527,   999,   773,   568,   780,  1003,   944,   536,   570,  1023,
     663,   219,  1034,   962,     0,     0,     0,     0,   572,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   891,     0,
       0,     0,     0,   915,     0,     0,     0,     0,   917,     0,
     905,     0,     0,     0,   953,   919,     0,     0,     0,     0,
     892,     0,     0,   893,     0,   894,   955,     0,     0,     0,
     906,     0,     0,     0,     0,   920,     0,     0,     0,     0,
       0,     0,   896,     0,   899,     0,   956,   916,     0,     0,
     904,     0,     0,     0,     0,   918,     0,   895,   954,     0,
       0,   907,   908,     0,   900,     0,   921,   922,   909,     0,
       0,     0,     0,   923
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,   587,    77,    78,    79,
      80,    76,    78,   360,    72,    73,    74,    75,    78,    77,
      78,   522,    80,    10,    68,    73,    73,   528,    73,     5,
      73,     7,   825,     9,    72,    73,    74,    75,     0,    77,
      78,   825,    80,   825,   825,    17,    12,   102,   103,     7,
      74,    77,    78,   102,   103,    73,    74,    75,     3,     7,
       7,     6,    73,    11,     7,    13,    73,    73,    75,    75,
      74,    99,   100,    73,    22,    75,    24,    25,    26,    27,
      28,    29,    30,    31,    14,    15,    19,    20,    18,     3,
       3,    21,    75,    76,     8,     8,    16,    17,    63,    64,
      65,    66,    67,    68,    52,    53,    54,    55,    56,    57,
      75,    76,     7,    61,    62,   164,     3,   132,   133,   134,
     135,     8,     3,     3,    72,     6,     6,    75,    76,   141,
     113,   114,   144,   145,   146,    63,     7,    85,    86,    92,
      93,    94,    95,    91,    97,    75,    76,    75,    76,     3,
       7,   138,   167,   101,     8,   164,   104,     7,   130,     7,
     147,   148,   149,   111,   112,     3,     3,   115,     7,     3,
       8,     8,     6,    25,    26,    27,    28,   164,     3,     3,
       7,   164,     3,     8,     8,   978,    61,     8,   164,   165,
     166,   167,     3,     7,   978,     7,   978,   978,   164,   164,
      52,    53,    54,     7,     3,   139,    58,    59,    60,     8,
      62,     6,   140,     3,   142,   143,   164,     3,     8,     4,
       8,    73,     8,    75,    76,    77,    78,    79,    80,     3,
       8,     4,   813,   580,   164,    87,   164,     4,    90,    91,
       3,    25,    26,    27,    28,     8,    98,    62,     4,    26,
      27,    28,   105,   106,   107,   108,   109,   110,     3,    74,
      75,    76,     3,     8,     4,     4,     3,     8,    52,    53,
      54,     8,    87,    57,     4,    90,     3,     3,    62,    63,
       4,     8,     8,     4,     3,    62,     4,     4,   358,     8,
       3,    75,    76,     3,    78,     8,    80,     3,    75,    76,
       8,     4,     8,    87,   348,   349,    90,     4,     3,    86,
       8,     3,   164,     8,    98,    92,    93,    94,    95,    96,
      97,   391,    99,     3,     3,     3,     3,   397,     8,     8,
       8,     8,     3,    81,    82,    83,    84,     8,     4,   397,
     410,     4,     3,   413,    33,    34,    35,    36,     8,   164,
       4,     4,   410,     4,   424,   413,     4,     4,     4,   397,
       4,   164,   410,   410,   434,   410,   424,   410,     4,   439,
       4,     4,   410,   439,     4,   413,   434,     4,     4,   439,
     164,   439,     4,     4,   167,   167,   424,   164,     4,   413,
     460,     4,   410,     4,     4,   413,   434,     4,     4,   410,
     165,   439,   460,   410,   410,   165,   424,   165,   434,   413,
     410,   165,     4,   439,    26,    27,    28,   424,   424,     4,
       4,     4,   460,    32,   424,     4,     4,    32,     4,   473,
     474,   475,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,     4,   949,    61,
      62,    63,     4,     4,    63,     4,    65,    66,    63,     4,
      69,    70,    71,    75,    76,   165,    75,    76,     4,     4,
       4,     4,     4,   167,     4,     4,    88,    89,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,     4,     4,     4,     4,   165,     4,     4,     4,
       4,     4,     4,     4,   574,     4,   550,     4,     4,     4,
       4,   581,     4,     4,     4,   165,   586,   587,     4,     4,
       4,     4,   167,   581,   167,    75,    76,   167,     4,   573,
       4,     4,   602,   603,     4,   167,   165,     4,     4,     4,
     165,   165,     4,   581,   602,   603,     4,   167,   167,   167,
       4,     4,   164,     4,     4,   164,     4,   131,     7,   164,
       7,     7,     7,     7,   602,   603,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
       7,     7,   164,   164,   164,     5,   136,   137,     5,   164,
       5,     5,     5,   164,     5,     7,     5,     5,     5,   164,
     164,     7,     7,     7,     5,   164,     5,     7,   164,   164,
     164,   164,     5,     5,   164,     4,   164,   164,   164,     7,
     164,   164,   164,   164,   164,   164,   164,   164,    23,     7,
       7,     7,     7,   164,     7,     7,   164,   164,   164,   164,
     164,   164,   164,   164,     7,     7,     7,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,   165,     6,     3,
       6,     6,     3,     6,     3,     3,     6,     3,   498,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     3,   167,
       6,     3,   164,     6,     8,     4,     4,     4,     4,     4,
     165,     4,     4,     4,   165,   167,   165,   165,     4,     6,
       4,   165,   165,     8,     4,   165,   167,     8,   165,   165,
     165,     8,     3,   165,     8,     4,     4,     4,     4,   358,
       5,     4,   165,   164,   164,   164,   164,   164,   164,   164,
     164,   164,     7,     4,   165,   167,   164,     4,     4,   164,
     810,   165,   164,   813,   167,   574,   816,   165,   581,   819,
     391,   792,   822,   660,   815,   825,   822,   810,   816,   397,
     830,   819,   822,   833,   822,   830,   836,   825,   816,   816,
     838,   816,   830,   816,   828,   833,   845,   825,   816,   849,
     825,   819,   825,   442,   822,   855,   836,   825,   818,   816,
     860,   849,   830,   819,   827,   833,   822,   855,   816,   825,
     978,   825,   860,   819,   830,   816,   410,   825,   821,   816,
     816,   849,   830,   855,   825,   833,   816,   855,   825,   825,
     434,   825,   860,   830,   830,   825,   833,   833,   824,   822,
     830,   855,   857,   833,   860,   833,   439,   855,   835,   831,
     413,   983,   603,   460,   625,   994,   849,   424,   463,  1011,
     575,   855,  1028,   861,    -1,    -1,    -1,    -1,   466,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   978,    -1,
      -1,    -1,    -1,   983,    -1,    -1,    -1,    -1,   983,    -1,
     978,    -1,    -1,    -1,   994,   983,    -1,    -1,    -1,    -1,
     978,    -1,    -1,   978,    -1,   978,   994,    -1,    -1,    -1,
     978,    -1,    -1,    -1,    -1,   983,    -1,    -1,    -1,    -1,
      -1,    -1,   978,    -1,   978,    -1,   994,   983,    -1,    -1,
     978,    -1,    -1,    -1,    -1,   983,    -1,   978,   994,    -1,
      -1,   978,   978,    -1,   978,    -1,   983,   983,   978,    -1,
      -1,    -1,    -1,   983
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
       0,     5,     7,     9,   164,   165,   166,   167,   184,   185,
     186,   191,     7,   200,     7,   206,     7,   222,     7,   315,
       7,   395,     7,   411,     7,   347,     7,   353,     7,   377,
       7,   291,     7,   466,     7,   514,     7,   506,   192,   187,
     201,   207,   223,   316,   396,   412,   348,   354,   378,   292,
     467,   515,   507,   184,   193,   194,   164,   189,   190,    10,
     138,   147,   148,   149,   164,   199,   202,   203,   204,   497,
     499,   501,   512,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    52,    53,    54,    55,    56,
      57,    61,    62,    72,    75,    76,    85,    86,    91,   101,
     104,   111,   112,   115,   199,   208,   209,   210,   211,   212,
     213,   214,   216,   217,   218,   233,   235,   241,   243,   276,
     285,   299,   309,   337,   345,   371,   401,   403,   405,   416,
     418,   420,   443,   455,   456,   464,   503,    14,    15,    18,
      21,   199,   220,   221,   224,   226,   229,   232,   401,   403,
      58,    59,    60,    73,    77,    78,    79,    80,    87,    90,
      98,   199,   210,   211,   212,   217,   317,   318,   319,   321,
     323,   325,   327,   329,   331,   333,   336,   371,   389,   401,
     403,   405,   416,   418,   420,   440,    74,   199,   329,   331,
     371,   397,   398,   399,   401,   403,    86,    92,    93,    94,
      95,    96,    97,    99,   199,   371,   401,   403,   413,   414,
     415,   416,   418,   420,   422,   426,   428,   430,   432,   434,
     436,   438,   345,    32,    63,    65,    66,    69,    70,    71,
     199,   261,   355,   356,   357,   358,   359,   360,   361,   363,
     365,   367,   368,   370,   401,   403,    64,    67,    68,   199,
     261,   359,   365,   379,   380,   381,   382,   383,   385,   386,
     387,   388,   401,   403,   102,   103,   199,   293,   294,   295,
     297,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   136,   137,   199,   401,   403,
     468,   469,   470,   471,   473,   475,   476,   478,   479,   480,
     483,   485,   486,   487,   488,   491,   493,   495,   139,   516,
     517,   518,    12,   199,   508,   509,   510,     6,     3,     4,
       8,     3,   205,   513,   498,   500,   502,     4,     3,     8,
     504,   505,   219,   236,     4,     4,   417,   419,   421,   234,
     242,   244,     4,     4,     4,     4,   215,   310,   346,   372,
     338,   402,   404,   277,   444,   406,   286,   300,     4,   457,
     465,     3,     8,   225,   227,   230,     4,     3,     8,   322,
     324,   326,   390,   320,   328,     4,   334,   332,   330,   441,
       3,     8,   400,     3,     8,   439,   427,   429,   433,   431,
     437,   435,   423,     8,     3,     8,   362,   262,     4,   366,
     364,   369,     4,     8,     3,   384,     4,     4,     8,     3,
     296,   298,     3,     8,     4,   472,   474,     4,   477,     4,
       4,   481,   484,     4,     4,     4,   489,   492,   494,   496,
       3,     8,   519,     3,     8,   511,     3,     8,   184,   184,
     164,     4,     4,     4,     4,     4,   203,   508,     4,     4,
       4,   167,   167,     4,     4,     4,     4,     4,     4,   165,
     165,   165,   165,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   165,     4,     4,   209,     4,
       4,     4,   167,   221,     4,     4,     4,     4,     4,     4,
     165,     4,     4,     4,     4,   318,     4,   398,     4,     4,
       4,     4,     4,     4,     4,     4,   415,     4,     4,   165,
       4,     4,     4,   167,   357,     4,   167,   167,   381,     4,
       4,   294,   167,     4,     4,   165,     4,   165,   165,     4,
       4,   167,   167,   167,     4,     4,     4,     4,   469,     4,
     517,     4,   509,     4,     7,     7,   184,   184,   184,     8,
       7,     7,     7,   164,   164,   164,     7,     7,     5,   164,
       5,     5,     5,     5,   186,   188,   164,     5,     5,     5,
       5,     7,     7,     7,     5,   195,    16,    17,   228,    19,
      20,   231,   164,   164,   164,     5,   164,   164,    81,    82,
      83,    84,   335,   195,   164,     7,   164,   195,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   184,   164,   164,   164,    17,   130,   482,   131,
     132,   133,   134,   135,   167,   490,   164,   164,   164,     5,
       5,   184,   208,   516,   508,   220,    23,   237,   238,   239,
      32,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,   199,   249,   250,   251,
     254,   256,   258,   260,   261,   263,   264,   265,   266,   267,
     268,   269,   270,   272,   274,   275,   249,     7,   245,   246,
     247,     7,   311,   312,   313,     7,   349,   350,   351,     7,
     373,   374,   375,     7,   339,   340,   341,    92,    93,    94,
      95,    97,   278,   279,   280,   281,   282,   283,   284,     7,
     445,   446,     7,   407,   408,   409,     7,   287,   288,   289,
     105,   106,   107,   108,   109,   110,   301,   302,   303,   304,
     305,   306,   307,   308,   113,   114,   199,   401,   403,   458,
     459,   460,   462,   468,   196,     7,   391,   392,   393,   100,
     422,   424,   442,     7,   520,   521,   245,     8,     8,     8,
       8,   240,     3,     8,   252,   255,   257,   259,     4,     4,
       4,     4,     4,   271,   273,     4,     4,     4,     4,     4,
       3,     8,     8,   248,     6,     3,   314,     6,     3,   352,
       6,     3,   376,     6,     3,   342,     6,     3,     3,     6,
     447,     3,     6,   410,     6,     3,   290,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   461,   463,     3,
       8,     8,   164,   197,   198,   394,     6,     3,   425,     8,
     522,     3,     6,     6,     4,   238,     4,     4,     4,     4,
     165,   167,   165,   167,   165,     4,     4,   165,   165,   165,
     165,   167,   250,   249,   247,   317,   313,   355,   351,   379,
     375,   199,   210,   211,   212,   217,   261,   309,   327,   329,
     331,   333,   343,   344,   371,   401,   403,   416,   418,   420,
     440,   341,   279,    88,    89,   199,   261,   345,   371,   401,
     403,   416,   418,   420,   448,   449,   450,   451,   452,   454,
     446,   413,   409,   293,   289,   165,   165,   165,   165,   165,
     165,   302,     4,     4,   459,     6,     3,   397,   393,     4,
     140,   142,   143,   199,   261,   401,   403,   523,   524,   525,
     526,   528,   521,   164,    33,    34,    35,    36,   253,   164,
     164,   164,   164,   164,     8,     8,     8,     8,     3,     8,
     453,     4,     8,     3,     8,     8,   164,   164,   164,     8,
     195,   529,     4,   527,     3,     8,   344,     4,   167,   450,
       4,   165,     4,   524,   164,     5,   164,     7,   530,   531,
     532,     3,     6,   141,   144,   145,   146,   533,   534,   535,
     537,   538,   539,   531,   536,     4,     4,     4,     3,     8,
       4,   167,   165,   165,   534,   164
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   168,   170,   169,   171,   169,   172,   169,   173,   169,
     174,   169,   175,   169,   176,   169,   177,   169,   178,   169,
     179,   169,   180,   169,   181,   169,   182,   169,   183,   169,
     184,   184,   184,   184,   184,   184,   184,   185,   187,   186,
     188,   189,   189,   190,   190,   192,   191,   193,   193,   194,
     194,   196,   195,   197,   197,   198,   198,   199,   201,   200,
     202,   202,   203,   203,   203,   203,   203,   203,   205,   204,
     207,   206,   208,   208,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   210,   211,   212,   213,   215,
     214,   216,   217,   219,   218,   220,   220,   221,   221,   221,
     221,   221,   221,   221,   223,   222,   225,   224,   227,   226,
     228,   228,   230,   229,   231,   231,   232,   234,   233,   236,
     235,   237,   237,   238,   240,   239,   242,   241,   244,   243,
     245,   245,   246,   246,   248,   247,   249,   249,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   252,   251,   253,   253,
     253,   253,   255,   254,   257,   256,   259,   258,   260,   262,
     261,   263,   264,   265,   266,   267,   268,   269,   271,   270,
     273,   272,   274,   275,   277,   276,   278,   278,   279,   279,
     279,   279,   279,   280,   281,   282,   283,   284,   286,   285,
     287,   287,   288,   288,   290,   289,   292,   291,   293,   293,
     293,   294,   294,   296,   295,   298,   297,   300,   299,   301,
     301,   302,   302,   302,   302,   302,   302,   303,   304,   305,
     306,   307,   308,   310,   309,   311,   311,   312,   312,   314,
     313,   316,   315,   317,   317,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   320,   319,
     322,   321,   324,   323,   326,   325,   328,   327,   330,   329,
     332,   331,   334,   333,   335,   335,   335,   335,   336,   338,
     337,   339,   339,   340,   340,   342,   341,   343,   343,   344,
     344,   344,   344,   344,   344,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   346,   345,   348,
     347,   349,   349,   350,   350,   352,   351,   354,   353,   355,
     355,   356,   356,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   358,   359,   360,   362,   361,   364,   363,
     366,   365,   367,   369,   368,   370,   372,   371,   373,   373,
     374,   374,   376,   375,   378,   377,   379,   379,   380,   380,
     381,   381,   381,   381,   381,   381,   381,   381,   381,   382,
     384,   383,   385,   386,   387,   388,   390,   389,   391,   391,
     392,   392,   394,   393,   396,   395,   397,   397,   398,   398,
     398,   398,   398,   398,   398,   400,   399,   402,   401,   404,
     403,   406,   405,   407,   407,   408,   408,   410,   409,   412,
     411,   413,   413,   414,   414,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     417,   416,   419,   418,   421,   420,   423,   422,   425,   424,
     427,   426,   429,   428,   431,   430,   433,   432,   435,   434,
     437,   436,   439,   438,   441,   440,   442,   442,   444,   443,
     445,   445,   447,   446,   448,   448,   449,   449,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   451,
     453,   452,   454,   455,   457,   456,   458,   458,   459,   459,
     459,   459,   459,   461,   460,   463,   462,   465,   464,   467,
     466,   468,   468,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   470,   472,   471,   474,   473,   475,   477,   476,
     478,   479,   481,   480,   482,   482,   484,   483,   485,   486,
     487,   489,   488,   490,   490,   490,   490,   490,   492,   491,
     494,   493,   496,   495,   498,   497,   500,   499,   502,   501,
     504,   503,   505,   503,   507,   506,   508,   508,   509,   509,
     511,   510,   513,   512,   515,   514,   516,   516,   517,   519,
     518,   520,   520,   522,   521,   523,   523,   524,   524,   524,
     524,   524,   524,   524,   525,   527,   526,   529,   528,   530,
     530,   532,   531,   533,   533,   534,   534,   534,   534,   536,
     535,   537,   538,   539
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     4,     1,     1,     3,     0,     6,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       0,     4,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     6,     0,     6,     0,     4,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     3,     3,     3
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
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
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
  "echo_client_id", "match_client_id", "interfaces_config", "$@22",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@23", "interfaces_list", "$@24", "dhcp_socket_type", "$@25",
  "socket_type", "outbound_interface", "$@26", "outbound_interface_value",
  "re_detect", "lease_database", "$@27", "sanity_checks", "$@28",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@29",
  "hosts_database", "$@30", "hosts_databases", "$@31", "database_list",
  "not_empty_database_list", "database", "$@32", "database_map_params",
  "database_map_param", "database_type", "$@33", "db_type", "user", "$@34",
  "password", "$@35", "host", "$@36", "port", "name", "$@37", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@38", "keyspace",
  "$@39", "max_reconnect_tries", "reconnect_wait_time",
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
  "$@98", "control_socket_name", "$@99", "dhcp_ddns", "$@100",
  "sub_dhcp_ddns", "$@101", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@102", "server_ip", "$@103",
  "server_port", "sender_ip", "$@104", "sender_port", "max_queue_size",
  "ncr_protocol", "$@105", "ncr_protocol_value", "ncr_format", "$@106",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@107", "replace_client_name_value",
  "generated_prefix", "$@108", "hostname_char_set", "$@109",
  "hostname_char_replacement", "$@110", "dhcp6_json_object", "$@111",
  "dhcpddns_json_object", "$@112", "control_agent_json_object", "$@113",
  "config_control", "$@114", "$@115", "sub_config_control", "$@116",
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
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   252,   252,   252,   253,   253,   254,   254,   255,   255,
     256,   256,   257,   257,   258,   258,   259,   259,   260,   260,
     261,   261,   262,   262,   263,   263,   264,   264,   265,   265,
     273,   274,   275,   276,   277,   278,   279,   282,   287,   287,
     298,   301,   302,   305,   309,   316,   316,   323,   324,   327,
     331,   338,   338,   345,   346,   349,   353,   364,   374,   374,
     390,   391,   395,   396,   397,   398,   399,   400,   403,   403,
     418,   418,   427,   428,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   466,   471,   476,   481,   486,
     486,   494,   499,   505,   505,   516,   517,   520,   521,   522,
     523,   524,   525,   526,   529,   529,   538,   538,   548,   548,
     555,   556,   559,   559,   566,   568,   572,   578,   578,   590,
     590,   600,   601,   603,   605,   605,   623,   623,   635,   635,
     645,   646,   649,   650,   653,   653,   663,   664,   667,   668,
     669,   670,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   684,   687,   687,   694,   695,
     696,   697,   700,   700,   708,   708,   716,   716,   724,   729,
     729,   737,   742,   747,   752,   757,   762,   767,   772,   772,
     780,   780,   788,   793,   798,   798,   808,   809,   812,   813,
     814,   815,   816,   819,   824,   829,   834,   839,   844,   844,
     854,   855,   858,   859,   862,   862,   872,   872,   882,   883,
     884,   887,   888,   891,   891,   899,   899,   907,   907,   918,
     919,   922,   923,   924,   925,   926,   927,   930,   935,   940,
     945,   950,   955,   963,   963,   976,   977,   980,   981,   988,
     988,  1014,  1014,  1025,  1026,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,
    1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,  1055,  1055,
    1063,  1063,  1071,  1071,  1079,  1079,  1087,  1087,  1095,  1095,
    1103,  1103,  1113,  1113,  1120,  1121,  1122,  1123,  1126,  1133,
    1133,  1144,  1145,  1149,  1150,  1153,  1153,  1161,  1162,  1165,
    1166,  1167,  1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,
    1176,  1177,  1178,  1179,  1180,  1181,  1182,  1189,  1189,  1202,
    1202,  1211,  1212,  1215,  1216,  1221,  1221,  1236,  1236,  1250,
    1251,  1254,  1255,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265,  1266,  1267,  1270,  1272,  1277,  1279,  1279,  1287,  1287,
    1295,  1295,  1303,  1305,  1305,  1313,  1322,  1322,  1334,  1335,
    1340,  1341,  1346,  1346,  1358,  1358,  1370,  1371,  1376,  1377,
    1382,  1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1393,
    1395,  1395,  1403,  1405,  1407,  1412,  1420,  1420,  1432,  1433,
    1436,  1437,  1440,  1440,  1450,  1450,  1460,  1461,  1464,  1465,
    1466,  1467,  1468,  1469,  1470,  1473,  1473,  1481,  1481,  1506,
    1506,  1536,  1536,  1546,  1547,  1550,  1551,  1554,  1554,  1563,
    1563,  1572,  1573,  1576,  1577,  1581,  1582,  1583,  1584,  1585,
    1586,  1587,  1588,  1589,  1590,  1591,  1592,  1593,  1594,  1595,
    1598,  1598,  1606,  1606,  1614,  1614,  1622,  1622,  1630,  1630,
    1640,  1640,  1648,  1648,  1656,  1656,  1664,  1664,  1672,  1672,
    1680,  1680,  1688,  1688,  1701,  1701,  1711,  1712,  1718,  1718,
    1728,  1729,  1732,  1732,  1742,  1743,  1746,  1747,  1750,  1751,
    1752,  1753,  1754,  1755,  1756,  1757,  1758,  1759,  1760,  1763,
    1765,  1765,  1773,  1782,  1789,  1789,  1799,  1800,  1803,  1804,
    1805,  1806,  1807,  1810,  1810,  1818,  1818,  1828,  1828,  1840,
    1840,  1850,  1851,  1854,  1855,  1856,  1857,  1858,  1859,  1860,
    1861,  1862,  1863,  1864,  1865,  1866,  1867,  1868,  1869,  1870,
    1871,  1872,  1875,  1880,  1880,  1888,  1888,  1896,  1901,  1901,
    1909,  1914,  1919,  1919,  1927,  1928,  1931,  1931,  1939,  1944,
    1949,  1954,  1954,  1962,  1965,  1968,  1971,  1974,  1980,  1980,
    1988,  1988,  1996,  1996,  2007,  2007,  2014,  2014,  2021,  2021,
    2028,  2028,  2037,  2037,  2048,  2048,  2058,  2059,  2063,  2064,
    2067,  2067,  2082,  2082,  2092,  2092,  2103,  2104,  2108,  2112,
    2112,  2124,  2125,  2129,  2129,  2137,  2138,  2141,  2142,  2143,
    2144,  2145,  2146,  2147,  2150,  2155,  2155,  2163,  2163,  2173,
    2174,  2177,  2177,  2185,  2186,  2189,  2190,  2191,  2192,  2195,
    2195,  2203,  2208,  2213
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
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4863 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2218 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
