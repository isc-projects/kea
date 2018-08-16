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
      case 177: // value
      case 181: // map_value
      case 219: // socket_type
      case 222: // outbound_interface_value
      case 238: // db_type
      case 322: // hr_mode
      case 470: // ncr_protocol_value
      case 478: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 161: // "boolean"
        value.move< bool > (that.value);
        break;

      case 160: // "floating point"
        value.move< double > (that.value);
        break;

      case 159: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 158: // "constant string"
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
      case 177: // value
      case 181: // map_value
      case 219: // socket_type
      case 222: // outbound_interface_value
      case 238: // db_type
      case 322: // hr_mode
      case 470: // ncr_protocol_value
      case 478: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 161: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 160: // "floating point"
        value.copy< double > (that.value);
        break;

      case 159: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 158: // "constant string"
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
            case 158: // "constant string"

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 159: // "integer"

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 160: // "floating point"

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 161: // "boolean"

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 177: // value

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 181: // map_value

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 219: // socket_type

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 222: // outbound_interface_value

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 238: // db_type

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 322: // hr_mode

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 470: // ncr_protocol_value

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 478: // replace_client_name_value

#line 236 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 177: // value
      case 181: // map_value
      case 219: // socket_type
      case 222: // outbound_interface_value
      case 238: // db_type
      case 322: // hr_mode
      case 470: // ncr_protocol_value
      case 478: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 161: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 160: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 159: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 158: // "constant string"
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
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 297 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 323 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 341 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1979 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1080 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1096 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1101 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2158 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1250 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1252 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1258 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2269 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2373 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2419 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2567 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2577 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2585 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2595 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2603 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2641 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2723 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1807 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1935 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3220 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3295 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2024 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2050 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2090 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3432 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3436 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -756;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     419,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,    37,    25,    42,    46,    53,    57,
      73,   108,   152,   167,   202,   203,   215,   224,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,    25,   -92,    36,   141,    56,    63,
      19,   177,    14,   218,   157,   -48,   437,   110,  -756,    72,
     150,   247,   233,   249,  -756,  -756,  -756,  -756,  -756,   261,
    -756,    32,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   270,
     281,  -756,  -756,  -756,  -756,  -756,  -756,   290,   301,   305,
     310,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,   316,  -756,  -756,  -756,    59,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   317,  -756,
      71,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   319,   320,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,    74,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,    88,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
     254,   284,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,   300,  -756,  -756,   322,  -756,  -756,
    -756,   323,  -756,  -756,   321,   333,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   334,
     337,  -756,  -756,  -756,  -756,   335,   339,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   111,
    -756,  -756,  -756,   340,  -756,  -756,   341,  -756,   342,   348,
    -756,  -756,   351,   352,   353,  -756,  -756,  -756,  -756,  -756,
     120,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,   122,  -756,  -756,
    -756,    25,    25,  -756,   201,   356,   358,   363,   365,   367,
    -756,    36,  -756,   368,   213,   220,   378,   380,   382,   384,
     386,   388,   236,   242,   243,   245,   392,   401,   402,   408,
     410,   411,   412,   414,   415,   416,   417,   263,   420,   422,
     141,  -756,   423,   424,   425,   262,    56,  -756,   426,   427,
     428,   429,   430,   434,   436,   282,   285,   438,   439,   443,
     444,    63,  -756,   445,    19,  -756,   446,   447,   448,   449,
     450,   451,   452,   455,  -756,   177,  -756,   457,   458,   306,
     459,   462,   463,   307,  -756,   218,   465,   309,   311,  -756,
     157,   471,   472,     5,  -756,   318,   473,   476,   325,   477,
     326,   327,   483,   484,   328,   329,   330,   489,   490,   437,
    -756,   492,   110,  -756,  -756,  -756,   493,   494,   497,    25,
      25,    25,  -756,   498,  -756,  -756,   354,   355,   359,   499,
     502,   495,  -756,  -756,  -756,  -756,   505,   506,   511,   513,
     514,   362,   517,   534,   535,   536,   537,  -756,   539,   540,
    -756,   543,   107,   127,  -756,  -756,   421,   431,   432,   572,
     433,   435,   440,  -756,  -756,   238,   543,   441,   571,  -756,
     442,  -756,   543,   453,   454,   456,   460,   461,   464,   466,
    -756,   467,   468,  -756,   469,   470,   474,  -756,  -756,   475,
    -756,  -756,  -756,   478,    25,  -756,  -756,   479,   480,  -756,
     481,  -756,  -756,    21,   370,  -756,  -756,  -756,   -37,   482,
    -756,   575,  -756,    25,   141,   110,  -756,  -756,  -756,    56,
    -756,  -756,  -756,   491,   491,   574,   576,   577,   578,   579,
    -756,  -756,  -756,   165,   580,   581,   585,   100,   -12,   437,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,   587,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,    99,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,   589,  -756,   146,   173,   227,  -756,
    -756,  -756,  -756,   593,   597,   598,   599,   600,  -756,  -756,
     601,   602,   603,   604,   605,  -756,   229,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   230,  -756,   607,   496,  -756,
    -756,   609,   613,  -756,  -756,   611,   617,  -756,  -756,   615,
     620,  -756,  -756,   623,   627,  -756,  -756,  -756,  -756,  -756,
    -756,   126,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   154,
    -756,  -756,   625,   631,  -756,  -756,   629,   638,  -756,   606,
     639,   640,   641,   642,   643,   237,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   255,  -756,
    -756,  -756,   269,   500,  -756,   636,   645,  -756,  -756,  -756,
    -756,   644,  -756,   169,  -756,  -756,  -756,  -756,   646,   647,
     649,   650,   501,   503,   504,   507,   508,   651,   652,   510,
     512,   515,   516,   509,   491,  -756,  -756,   491,  -756,   574,
      63,  -756,   576,   218,  -756,   577,   157,  -756,   578,   387,
    -756,   579,   165,  -756,    85,   580,  -756,   177,  -756,   581,
     -48,  -756,   585,   518,   519,   520,   521,   522,   523,   100,
    -756,   653,   655,   -12,  -756,  -756,  -756,   656,   658,    19,
    -756,   587,   661,  -756,   155,   589,  -756,   302,   525,   526,
     527,  -756,  -756,  -756,  -756,  -756,   528,   529,  -756,  -756,
    -756,  -756,  -756,  -756,   283,  -756,   292,  -756,   664,  -756,
     665,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,   293,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   662,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   668,   685,  -756,  -756,  -756,
    -756,  -756,   681,  -756,   294,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,   532,   533,  -756,  -756,   538,   295,  -756,
     543,  -756,   688,  -756,  -756,  -756,  -756,  -756,   303,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   387,  -756,
     689,   541,  -756,    85,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,   690,   542,   691,   155,  -756,  -756,   545,  -756,  -756,
     692,  -756,   547,  -756,  -756,   693,  -756,  -756,   258,  -756,
     -39,   693,  -756,  -756,   694,   695,   702,   304,  -756,  -756,
    -756,  -756,  -756,  -756,   704,   548,   552,   553,   -39,  -756,
     559,  -756,  -756,  -756,  -756,  -756
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   117,     9,   247,    11,   405,    13,
     430,    15,   330,    17,   338,    19,   375,    21,   212,    23,
     520,    25,   577,    27,    45,    39,     0,     0,     0,     0,
       0,   432,     0,   340,   377,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   575,   569,   571,   573,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   106,     0,
       0,   451,   453,   455,   130,   132,   134,     0,     0,     0,
       0,   239,   328,   367,   300,   418,   420,   190,   479,   422,
     204,   223,     0,   505,   518,    99,     0,    70,    72,    73,
      74,    75,    91,    92,    78,    79,    80,    81,    82,    86,
      87,    76,    77,    84,    85,    96,    97,    98,    93,    94,
      95,    83,    88,    89,    90,   119,   121,   125,     0,   116,
       0,   108,   110,   111,   112,   113,   114,   115,   278,   280,
     282,   397,   276,   284,   286,     0,     0,   292,   290,   288,
     475,   275,   251,   252,   253,   266,     0,   249,   256,   270,
     271,   272,   257,   258,   261,   262,   264,   259,   260,   254,
     255,   273,   274,   263,   267,   268,   269,   265,   416,   415,
     411,   412,   410,     0,   407,   409,   413,   414,   473,   461,
     463,   467,   465,   471,   469,   457,   450,   444,   448,   449,
       0,   433,   434,   445,   446,   447,   441,   436,   442,   438,
     439,   440,   443,   437,     0,   357,   175,     0,   361,   359,
     364,     0,   353,   354,     0,   341,   342,   344,   356,   345,
     346,   347,   363,   348,   349,   350,   351,   352,   391,     0,
       0,   389,   390,   393,   394,     0,   378,   379,   381,   382,
     383,   384,   385,   386,   387,   388,   219,   221,   216,     0,
     214,   217,   218,     0,   542,   544,     0,   547,     0,     0,
     551,   555,     0,     0,     0,   560,   567,   540,   538,   539,
       0,   522,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   582,     0,   579,   581,
      44,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      55,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   248,     0,     0,   406,     0,     0,     0,     0,
       0,     0,     0,     0,   431,     0,   331,     0,     0,     0,
       0,     0,     0,     0,   339,     0,     0,     0,     0,   376,
       0,     0,     0,     0,   213,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     521,     0,     0,   578,    48,    41,     0,     0,     0,     0,
       0,     0,    59,     0,   104,   105,     0,     0,     0,     0,
       0,     0,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   504,     0,     0,
      71,     0,     0,     0,   129,   109,     0,     0,     0,     0,
       0,     0,     0,   298,   299,     0,     0,     0,     0,   250,
       0,   408,     0,     0,     0,     0,     0,     0,     0,     0,
     435,     0,     0,   355,     0,     0,     0,   366,   343,     0,
     395,   396,   380,     0,     0,   215,   541,     0,     0,   546,
       0,   549,   550,     0,     0,   557,   558,   559,     0,     0,
     523,     0,   580,     0,     0,     0,   570,   572,   574,     0,
     452,   454,   456,     0,     0,   136,   241,   332,   369,   302,
      38,   419,   421,     0,     0,   424,   206,     0,     0,     0,
      49,   120,   123,   124,   122,   127,   128,   126,   279,   281,
     283,   399,   277,   285,   287,   294,   295,   296,   297,   293,
     291,   289,     0,   417,   474,   462,   464,   468,   466,   472,
     470,   458,   358,   176,   362,   360,   365,   392,   220,   222,
     543,   545,   548,   553,   554,   552,   556,   562,   563,   564,
     565,   566,   561,   568,     0,    42,     0,     0,     0,   162,
     168,   170,   172,     0,     0,     0,     0,     0,   184,   186,
       0,     0,     0,     0,     0,   161,     0,   142,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   157,   158,
     159,   154,   160,   155,   156,     0,   140,     0,   137,   138,
     245,     0,   242,   243,   336,     0,   333,   334,   373,     0,
     370,   371,   306,     0,   303,   304,   199,   200,   201,   202,
     203,     0,   192,   194,   195,   196,   197,   198,   483,     0,
     481,   428,     0,   425,   426,   210,     0,   207,   208,     0,
       0,     0,     0,     0,     0,     0,   225,   227,   228,   229,
     230,   231,   232,   514,   516,   513,   511,   512,     0,   507,
     509,   510,     0,    51,   403,     0,   400,   401,   459,   477,
     478,     0,   586,     0,   584,    67,   576,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   133,     0,   135,     0,
       0,   240,     0,   340,   329,     0,   377,   368,     0,     0,
     301,     0,     0,   191,   485,     0,   480,   432,   423,     0,
       0,   205,     0,     0,     0,     0,     0,     0,     0,     0,
     224,     0,     0,     0,   506,   519,    53,     0,    52,     0,
     398,     0,     0,   476,     0,     0,   583,     0,     0,     0,
       0,   174,   177,   178,   179,   180,     0,     0,   188,   189,
     181,   182,   183,   143,     0,   139,     0,   244,     0,   335,
       0,   372,   327,   324,   313,   314,   316,   310,   311,   312,
     322,   323,   321,     0,   308,   315,   325,   326,   317,   318,
     319,   320,   305,   193,   501,     0,   499,   500,   492,   493,
     497,   498,   494,   495,   496,     0,   486,   487,   489,   490,
     491,   482,     0,   427,     0,   209,   233,   234,   235,   236,
     237,   238,   226,     0,     0,   508,    50,     0,     0,   402,
       0,   600,     0,   598,   596,   590,   594,   595,     0,   588,
     592,   593,   591,   585,   164,   165,   166,   167,   163,   169,
     171,   173,   185,   187,   141,   246,   337,   374,     0,   307,
       0,     0,   484,     0,   429,   211,   515,   517,    54,   404,
     460,     0,     0,     0,     0,   587,   309,     0,   503,   488,
       0,   597,     0,   589,   502,     0,   599,   604,     0,   602,
       0,     0,   601,   612,     0,     0,     0,     0,   606,   608,
     609,   610,   611,   603,     0,     0,     0,     0,     0,   605,
       0,   614,   615,   616,   607,   613
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   -51,  -756,   112,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -475,  -756,  -756,  -756,
     -66,  -756,  -756,  -756,   397,  -756,  -756,  -756,  -756,   185,
     371,   -44,   -43,   -28,  -756,  -756,    -4,  -756,  -756,   191,
     376,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
     -23,  -756,  -531,   -10,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,   -45,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,   -25,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,   -33,  -756,  -756,  -756,   -22,   344,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   -35,  -756,  -756,  -756,  -756,
    -756,  -756,  -755,  -756,  -756,  -756,     6,  -756,  -756,  -756,
       4,   389,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -746,  -756,  -756,  -756,   -64,  -756,   -16,  -756,  -741,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,     3,  -756,  -756,
    -143,   -61,  -756,  -756,  -756,  -756,  -756,    15,  -756,  -756,
    -756,    24,  -756,   372,  -756,   -62,  -756,  -756,  -756,  -756,
    -756,   -56,  -756,  -756,  -756,  -756,  -756,   -14,  -756,  -756,
    -756,    16,  -756,  -756,  -756,    22,  -756,   381,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   -19,
    -756,  -756,  -756,    -9,   409,  -756,  -756,   -54,  -756,   -26,
    -756,   -38,  -756,  -756,  -756,    13,  -756,  -756,  -756,    17,
    -756,   400,    -8,  -756,     2,  -756,    12,  -756,   214,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -740,  -756,  -756,  -756,
    -756,  -756,    23,  -756,  -756,  -756,  -126,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,     7,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,   240,   373,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   266,
     374,  -756,  -756,  -756,    -2,  -756,  -756,  -130,  -756,  -756,
    -756,  -756,  -756,  -756,  -146,  -756,  -756,  -161,  -756,  -756,
    -756,  -756,  -756
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   561,
      82,    83,    39,    64,    79,    80,   571,   733,   807,   808,
     645,    41,    66,    91,    92,    93,   335,    43,    67,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   343,   160,
     161,    45,    68,   162,   372,   163,   373,   574,   164,   374,
     577,   165,   135,   349,   136,   350,   137,   351,   667,   668,
     669,   767,   646,   647,   648,   748,   918,   649,   749,   650,
     750,   651,   751,   652,   653,   408,   654,   655,   656,   657,
     658,   659,   660,   661,   757,   662,   758,   663,   664,   138,
     362,   691,   692,   693,   694,   695,   696,   697,   139,   365,
     706,   707,   708,   790,    59,    75,   289,   290,   291,   421,
     292,   422,   140,   366,   715,   716,   717,   718,   719,   720,
     721,   722,   141,   356,   671,   672,   673,   770,    47,    69,
     186,   187,   188,   382,   189,   378,   190,   379,   191,   380,
     192,   383,   193,   384,   194,   389,   195,   388,   196,   387,
     589,   197,   198,   142,   359,   683,   684,   685,   779,   853,
     854,   143,   357,    53,    72,   675,   676,   677,   773,    55,
      73,   254,   255,   256,   257,   258,   259,   260,   407,   261,
     411,   262,   410,   263,   264,   412,   265,   144,   358,   679,
     680,   681,   776,    57,    74,   275,   276,   277,   278,   279,
     416,   280,   281,   282,   283,   200,   381,   735,   736,   737,
     809,    49,    70,   213,   214,   215,   393,   145,   360,   146,
     361,   147,   364,   702,   703,   704,   787,    51,    71,   230,
     231,   232,   148,   346,   149,   347,   150,   348,   236,   403,
     740,   812,   237,   397,   238,   398,   239,   400,   240,   399,
     241,   402,   242,   401,   243,   396,   207,   390,   741,   151,
     363,   699,   700,   784,   875,   876,   877,   878,   879,   930,
     880,   152,   153,   368,   728,   729,   730,   801,   731,   802,
     154,   369,    61,    76,   310,   311,   312,   313,   426,   314,
     427,   315,   316,   429,   317,   318,   319,   432,   615,   320,
     433,   321,   322,   323,   324,   437,   622,   325,   438,    94,
     337,    95,   338,    96,   339,    97,   336,    63,    77,   327,
     328,   329,   441,   743,   744,   814,   908,   909,   910,   911,
     943,   912,   941,   958,   959,   960,   967,   968,   969,   974,
     970,   971,   972
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   125,   159,   181,   209,   226,   210,   252,   271,   288,
     307,   244,   273,    78,   166,   201,   216,   228,   274,   266,
     284,   590,   308,   665,   848,   182,   183,   594,   253,   272,
      29,   203,    30,   849,    31,   341,   613,    28,   852,   861,
     342,   184,   167,   202,   217,   229,    84,   267,   285,    40,
     309,   286,   287,    42,   211,   199,   212,   227,   115,   116,
      44,   204,   370,   233,    46,   185,    81,   371,   155,   156,
     112,   205,   157,   234,   376,   158,   113,   391,   330,   377,
      48,   206,   392,   235,   100,   101,   102,   103,   208,   115,
     116,   394,   617,   618,   619,   620,   395,   963,   723,   724,
     964,   965,   966,   178,   286,   287,   179,   101,   102,   103,
      89,   107,   108,   109,   423,    50,   168,   169,   170,   424,
     113,   572,   573,   439,   621,   442,   115,   116,   440,   782,
     443,   171,   783,   115,   116,   172,   173,   174,   175,   176,
     177,   112,   113,   246,   575,   576,    89,   178,   614,   370,
     179,   119,    98,   331,   745,   115,   116,   785,   180,    52,
     786,    99,   100,   101,   102,   103,   104,   105,   106,    85,
     864,   865,   815,   848,    54,   816,   442,    89,    86,    87,
      88,   746,   849,    32,    33,    34,    35,   852,   861,   107,
     108,   109,   110,   111,    89,   225,   738,   112,   113,   101,
     102,   103,   709,   710,   711,   712,   713,   714,   114,    56,
      58,   115,   116,   246,    89,   246,   268,   247,   248,   269,
     270,    89,    60,   117,   118,   115,   116,   115,   116,   119,
     376,    62,   764,   764,   113,   747,   834,   765,   766,   120,
     799,   333,   121,    89,   326,   800,   245,   115,   116,   122,
     123,   332,   334,   124,   686,   687,   688,   689,   803,   690,
     218,   961,   404,   804,   962,   340,   219,   220,   221,   222,
     223,   224,   439,   225,   344,    90,   246,   805,   247,   248,
     444,   445,   249,   250,   251,   345,   764,   405,   115,   116,
     901,   924,   902,   903,   352,   391,   928,   423,   394,    89,
     925,   929,   935,   939,   125,   353,   944,   978,   406,   354,
     159,   945,   979,    89,   355,    89,   585,   586,   587,   588,
     367,   375,   166,   385,   386,   181,   409,   413,   209,   414,
     210,   914,   915,   916,   917,    89,   415,   201,   417,   226,
     216,   418,   420,   419,   425,   428,   430,   182,   183,   252,
     167,   228,   431,   203,   271,   434,   435,   436,   273,   446,
     447,   266,   448,   184,   274,   202,   284,   449,   217,   450,
     253,   451,   453,   307,   454,   272,    89,   199,   211,   229,
     212,   455,   456,   204,   457,   308,   458,   185,   459,   267,
     460,   227,   461,   205,   285,   462,   466,   233,   546,   547,
     548,   463,   464,   206,   465,   467,   468,   234,   100,   101,
     102,   103,   469,   309,   470,   471,   472,   235,   473,   474,
     475,   476,   477,   484,   478,   940,   479,   481,   482,   483,
     486,   487,   488,   489,   490,   107,   108,   109,   491,   111,
     492,   493,   495,   496,   113,   246,   494,   497,   498,   500,
     502,   503,   504,   505,   506,   507,   508,   115,   116,   509,
     173,   511,   512,   514,   177,   513,   515,   516,   517,   519,
     520,   178,   521,   609,   179,   523,   524,   527,   125,   526,
     528,   530,   180,   159,   529,   531,   532,   533,   534,   535,
     536,   537,   625,   538,   539,   166,   541,   543,   616,   769,
     555,   544,   725,   307,   545,   549,   553,   115,   116,   554,
     556,   557,   550,   551,   726,   308,   558,   552,   559,   629,
     562,    30,   563,   167,   630,   631,   632,   633,   634,   635,
     636,   637,   638,   639,   640,   641,   642,   643,   644,   564,
     565,   566,   727,   309,   567,    89,   568,   569,   570,   246,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   581,   592,   578,
     624,   666,   560,   670,   674,   678,   682,   698,   701,   579,
     580,   582,   705,   583,   734,    89,   742,   752,   584,   591,
     593,   753,   754,   755,   756,   759,   760,   761,   762,   763,
     793,   595,   596,   768,   597,   771,   772,   774,   598,   599,
     775,   777,   600,   778,   601,   602,   603,   604,   605,   780,
     781,   788,   606,   607,   789,   791,   608,   610,   611,   612,
     623,   792,   810,   794,   795,   796,   797,   798,   811,    89,
     817,   818,   813,   819,   820,   826,   827,   893,   806,   894,
     821,   897,   896,   823,   822,   900,   931,   825,   824,   828,
     832,   829,   926,   927,   830,   831,   932,   886,   887,   888,
     889,   890,   891,   919,   920,   921,   922,   923,   933,   934,
     936,   937,   942,   947,   950,   952,   938,   955,   975,   976,
     957,   951,   948,   954,   181,   956,   977,   252,   980,   981,
     271,   982,   983,   842,   273,   850,   201,   985,   866,   266,
     274,   226,   284,   868,   288,   856,   182,   183,   253,   626,
     870,   272,   203,   228,   847,   843,   844,   725,   452,   867,
     628,   480,   184,   209,   202,   210,   835,   267,   904,   726,
     285,   845,   485,   857,   833,   216,   199,   863,   871,   885,
     906,   229,   204,   851,   892,   855,   185,   525,   884,   905,
     869,   858,   205,   227,   836,   846,   872,   727,   837,   233,
     499,   859,   206,   217,   862,   946,   873,   518,   907,   234,
     839,   860,   899,   211,   841,   212,   874,   838,   840,   235,
     898,   522,   883,   501,   882,   510,   739,   949,   881,   732,
     895,   627,   540,   913,   953,   973,   542,   984,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   842,     0,   850,     0,     0,   866,     0,     0,
       0,     0,   868,     0,   856,     0,     0,     0,   904,   870,
       0,     0,     0,   847,   843,   844,     0,     0,   867,     0,
     906,     0,     0,     0,     0,     0,     0,     0,     0,   905,
     845,     0,   857,     0,     0,     0,     0,   871,     0,     0,
       0,     0,   851,     0,   855,     0,     0,     0,   907,   869,
     858,     0,     0,     0,   846,   872,     0,     0,     0,     0,
     859,     0,     0,     0,     0,   873,     0,     0,     0,     0,
     860,     0,     0,     0,     0,   874
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    70,    73,    74,    75,
      76,    72,    74,    64,    68,    69,    70,    71,    74,    73,
      74,   496,    76,   554,   779,    69,    69,   502,    73,    74,
       5,    69,     7,   779,     9,     3,    15,     0,   779,   779,
       8,    69,    68,    69,    70,    71,    10,    73,    74,     7,
      76,    99,   100,     7,    70,    69,    70,    71,    70,    71,
       7,    69,     3,    71,     7,    69,   158,     8,    12,    13,
      56,    69,    16,    71,     3,    19,    57,     3,     6,     8,
       7,    69,     8,    71,    21,    22,    23,    24,    69,    70,
      71,     3,   129,   130,   131,   132,     8,   136,   110,   111,
     139,   140,   141,    84,    99,   100,    87,    22,    23,    24,
     158,    48,    49,    50,     3,     7,    53,    54,    55,     8,
      57,    14,    15,     3,   161,     3,    70,    71,     8,     3,
       8,    68,     6,    70,    71,    72,    73,    74,    75,    76,
      77,    56,    57,    58,    17,    18,   158,    84,   127,     3,
      87,    88,    11,     3,     8,    70,    71,     3,    95,     7,
       6,    20,    21,    22,    23,    24,    25,    26,    27,   133,
      85,    86,     3,   928,     7,     6,     3,   158,   142,   143,
     144,     8,   928,   158,   159,   160,   161,   928,   928,    48,
      49,    50,    51,    52,   158,    96,    97,    56,    57,    22,
      23,    24,   102,   103,   104,   105,   106,   107,    67,     7,
       7,    70,    71,    58,   158,    58,    59,    60,    61,    62,
      63,   158,     7,    82,    83,    70,    71,    70,    71,    88,
       3,     7,     3,     3,    57,     8,   767,     8,     8,    98,
       3,     8,   101,   158,   134,     8,    28,    70,    71,   108,
     109,     4,     3,   112,    89,    90,    91,    92,     3,    94,
      83,     3,     8,     8,     6,     4,    89,    90,    91,    92,
      93,    94,     3,    96,     4,   341,    58,     8,    60,    61,
     331,   332,    64,    65,    66,     4,     3,     3,    70,    71,
     135,     8,   137,   138,     4,     3,     3,     3,     3,   158,
       8,     8,     8,     8,   370,     4,     3,     3,     8,     4,
     376,     8,     8,   158,     4,   158,    78,    79,    80,    81,
       4,     4,   376,     4,     4,   391,     4,     4,   394,     8,
     394,    29,    30,    31,    32,   158,     3,   391,     4,   405,
     394,     4,     3,     8,     4,     4,     4,   391,   391,   415,
     376,   405,     4,   391,   420,     4,     4,     4,   420,   158,
       4,   415,     4,   391,   420,   391,   420,     4,   394,     4,
     415,     4,     4,   439,   161,   420,   158,   391,   394,   405,
     394,   161,     4,   391,     4,   439,     4,   391,     4,   415,
       4,   405,     4,   391,   420,   159,     4,   405,   449,   450,
     451,   159,   159,   391,   159,     4,     4,   405,    21,    22,
      23,    24,     4,   439,     4,     4,     4,   405,     4,     4,
       4,     4,   159,   161,     4,   900,     4,     4,     4,     4,
       4,     4,     4,     4,     4,    48,    49,    50,     4,    52,
       4,   159,     4,     4,    57,    58,   161,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,    70,    71,     4,
      73,     4,     4,     4,    77,   159,     4,     4,   161,     4,
     161,    84,   161,   524,    87,     4,     4,     4,   544,   161,
       4,     4,    95,   549,   159,   159,   159,     4,     4,   161,
     161,   161,   543,     4,     4,   549,     4,     4,   128,     3,
       5,     7,   568,   569,     7,     7,     7,    70,    71,     7,
       5,     5,   158,   158,   568,   569,     5,   158,     5,    28,
     158,     7,     5,   549,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     5,
       5,     5,   568,   569,     7,   158,     7,     7,     5,    58,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     5,     7,   158,
       5,     7,   470,     7,     7,     7,     7,     7,     7,   158,
     158,   158,     7,   158,     7,   158,     7,     4,   158,   158,
     158,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   158,   158,     6,   158,     6,     3,     6,   158,   158,
       3,     6,   158,     3,   158,   158,   158,   158,   158,     6,
       3,     6,   158,   158,     3,     6,   158,   158,   158,   158,
     158,     3,     6,     4,     4,     4,     4,     4,     3,   158,
       4,     4,     8,     4,     4,     4,     4,     4,   158,     4,
     159,     3,     6,   159,   161,     4,     4,   159,   161,   159,
     161,   159,     8,     8,   159,   159,     8,   159,   159,   159,
     159,   159,   159,   158,   158,   158,   158,   158,     3,     8,
     158,   158,     4,     4,     4,     4,   158,     5,     4,     4,
       7,   159,   161,   158,   770,   158,     4,   773,     4,   161,
     776,   159,   159,   779,   776,   779,   770,   158,   784,   773,
     776,   787,   776,   784,   790,   779,   770,   770,   773,   544,
     784,   776,   770,   787,   779,   779,   779,   803,   341,   784,
     549,   370,   770,   809,   770,   809,   769,   773,   814,   803,
     776,   779,   376,   779,   764,   809,   770,   782,   784,   792,
     814,   787,   770,   779,   799,   779,   770,   423,   790,   814,
     784,   779,   770,   787,   770,   779,   784,   803,   772,   787,
     391,   779,   770,   809,   781,   928,   784,   415,   814,   787,
     775,   779,   811,   809,   778,   809,   784,   773,   776,   787,
     809,   420,   789,   394,   787,   405,   592,   933,   785,   569,
     803,   545,   439,   815,   944,   961,   442,   978,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   928,    -1,   928,    -1,    -1,   933,    -1,    -1,
      -1,    -1,   933,    -1,   928,    -1,    -1,    -1,   944,   933,
      -1,    -1,    -1,   928,   928,   928,    -1,    -1,   933,    -1,
     944,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   944,
     928,    -1,   928,    -1,    -1,    -1,    -1,   933,    -1,    -1,
      -1,    -1,   928,    -1,   928,    -1,    -1,    -1,   944,   933,
     928,    -1,    -1,    -1,   928,   933,    -1,    -1,    -1,    -1,
     928,    -1,    -1,    -1,    -1,   933,    -1,    -1,    -1,    -1,
     928,    -1,    -1,    -1,    -1,   933
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,     0,     5,
       7,     9,   158,   159,   160,   161,   177,   178,   179,   184,
       7,   193,     7,   199,     7,   213,     7,   300,     7,   383,
       7,   399,     7,   335,     7,   341,     7,   365,     7,   276,
       7,   454,     7,   489,   185,   180,   194,   200,   214,   301,
     384,   400,   336,   342,   366,   277,   455,   490,   177,   186,
     187,   158,   182,   183,    10,   133,   142,   143,   144,   158,
     192,   195,   196,   197,   481,   483,   485,   487,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    48,    49,    50,
      51,    52,    56,    57,    67,    70,    71,    82,    83,    88,
      98,   101,   108,   109,   112,   192,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   224,   226,   228,   261,   270,
     284,   294,   325,   333,   359,   389,   391,   393,   404,   406,
     408,   431,   443,   444,   452,    12,    13,    16,    19,   192,
     211,   212,   215,   217,   220,   223,   389,   391,    53,    54,
      55,    68,    72,    73,    74,    75,    76,    77,    84,    87,
      95,   192,   203,   204,   205,   208,   302,   303,   304,   306,
     308,   310,   312,   314,   316,   318,   320,   323,   324,   359,
     377,   389,   391,   393,   404,   406,   408,   428,    69,   192,
     316,   318,   359,   385,   386,   387,   389,   391,    83,    89,
      90,    91,    92,    93,    94,    96,   192,   359,   389,   391,
     401,   402,   403,   404,   406,   408,   410,   414,   416,   418,
     420,   422,   424,   426,   333,    28,    58,    60,    61,    64,
      65,    66,   192,   246,   343,   344,   345,   346,   347,   348,
     349,   351,   353,   355,   356,   358,   389,   391,    59,    62,
      63,   192,   246,   347,   353,   367,   368,   369,   370,   371,
     373,   374,   375,   376,   389,   391,    99,   100,   192,   278,
     279,   280,   282,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   192,   389,   391,
     456,   457,   458,   459,   461,   463,   464,   466,   467,   468,
     471,   473,   474,   475,   476,   479,   134,   491,   492,   493,
       6,     3,     4,     8,     3,   198,   488,   482,   484,   486,
       4,     3,     8,   210,     4,     4,   405,   407,   409,   225,
     227,   229,     4,     4,     4,     4,   295,   334,   360,   326,
     390,   392,   262,   432,   394,   271,   285,     4,   445,   453,
       3,     8,   216,   218,   221,     4,     3,     8,   307,   309,
     311,   378,   305,   313,   315,     4,     4,   321,   319,   317,
     429,     3,     8,   388,     3,     8,   427,   415,   417,   421,
     419,   425,   423,   411,     8,     3,     8,   350,   247,     4,
     354,   352,   357,     4,     8,     3,   372,     4,     4,     8,
       3,   281,   283,     3,     8,     4,   460,   462,     4,   465,
       4,     4,   469,   472,     4,     4,     4,   477,   480,     3,
       8,   494,     3,     8,   177,   177,   158,     4,     4,     4,
       4,     4,   196,     4,   161,   161,     4,     4,     4,     4,
       4,     4,   159,   159,   159,   159,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   159,     4,     4,
     202,     4,     4,     4,   161,   212,     4,     4,     4,     4,
       4,     4,     4,   159,   161,     4,     4,     4,     4,   303,
       4,   386,     4,     4,     4,     4,     4,     4,     4,     4,
     403,     4,     4,   159,     4,     4,     4,   161,   345,     4,
     161,   161,   369,     4,     4,   279,   161,     4,     4,   159,
       4,   159,   159,     4,     4,   161,   161,   161,     4,     4,
     457,     4,   492,     4,     7,     7,   177,   177,   177,     7,
     158,   158,   158,     7,     7,     5,     5,     5,     5,     5,
     179,   181,   158,     5,     5,     5,     5,     7,     7,     7,
       5,   188,    14,    15,   219,    17,    18,   222,   158,   158,
     158,     5,   158,   158,   158,    78,    79,    80,    81,   322,
     188,   158,     7,   158,   188,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   177,
     158,   158,   158,    15,   127,   470,   128,   129,   130,   131,
     132,   161,   478,   158,     5,   177,   201,   491,   211,    28,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,   192,   234,   235,   236,   239,
     241,   243,   245,   246,   248,   249,   250,   251,   252,   253,
     254,   255,   257,   259,   260,   234,     7,   230,   231,   232,
       7,   296,   297,   298,     7,   337,   338,   339,     7,   361,
     362,   363,     7,   327,   328,   329,    89,    90,    91,    92,
      94,   263,   264,   265,   266,   267,   268,   269,     7,   433,
     434,     7,   395,   396,   397,     7,   272,   273,   274,   102,
     103,   104,   105,   106,   107,   286,   287,   288,   289,   290,
     291,   292,   293,   110,   111,   192,   389,   391,   446,   447,
     448,   450,   456,   189,     7,   379,   380,   381,    97,   410,
     412,   430,     7,   495,   496,     8,     8,     8,   237,   240,
     242,   244,     4,     4,     4,     4,     4,   256,   258,     4,
       4,     4,     4,     4,     3,     8,     8,   233,     6,     3,
     299,     6,     3,   340,     6,     3,   364,     6,     3,   330,
       6,     3,     3,     6,   435,     3,     6,   398,     6,     3,
     275,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   449,   451,     3,     8,     8,   158,   190,   191,   382,
       6,     3,   413,     8,   497,     3,     6,     4,     4,     4,
       4,   159,   161,   159,   161,   159,     4,     4,   159,   159,
     159,   159,   161,   235,   234,   232,   302,   298,   343,   339,
     367,   363,   192,   203,   204,   205,   208,   246,   294,   312,
     316,   318,   320,   331,   332,   359,   389,   391,   404,   406,
     408,   428,   329,   264,    85,    86,   192,   246,   333,   359,
     389,   391,   404,   406,   408,   436,   437,   438,   439,   440,
     442,   434,   401,   397,   278,   274,   159,   159,   159,   159,
     159,   159,   287,     4,     4,   447,     6,     3,   385,   381,
       4,   135,   137,   138,   192,   246,   389,   391,   498,   499,
     500,   501,   503,   496,    29,    30,    31,    32,   238,   158,
     158,   158,   158,   158,     8,     8,     8,     8,     3,     8,
     441,     4,     8,     3,     8,     8,   158,   158,   158,     8,
     188,   504,     4,   502,     3,     8,   332,     4,   161,   438,
       4,   159,     4,   499,   158,     5,   158,     7,   505,   506,
     507,     3,     6,   136,   139,   140,   141,   508,   509,   510,
     512,   513,   514,   506,   511,     4,     4,     4,     3,     8,
       4,   161,   159,   159,   509,   158
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   162,   164,   163,   165,   163,   166,   163,   167,   163,
     168,   163,   169,   163,   170,   163,   171,   163,   172,   163,
     173,   163,   174,   163,   175,   163,   176,   163,   177,   177,
     177,   177,   177,   177,   177,   178,   180,   179,   181,   182,
     182,   183,   183,   185,   184,   186,   186,   187,   187,   189,
     188,   190,   190,   191,   191,   192,   194,   193,   195,   195,
     196,   196,   196,   196,   196,   196,   198,   197,   200,   199,
     201,   201,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     203,   204,   205,   206,   207,   208,   210,   209,   211,   211,
     212,   212,   212,   212,   212,   212,   212,   214,   213,   216,
     215,   218,   217,   219,   219,   221,   220,   222,   222,   223,
     225,   224,   227,   226,   229,   228,   230,   230,   231,   231,
     233,   232,   234,   234,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   237,   236,   238,   238,   238,   238,   240,   239,
     242,   241,   244,   243,   245,   247,   246,   248,   249,   250,
     251,   252,   253,   254,   256,   255,   258,   257,   259,   260,
     262,   261,   263,   263,   264,   264,   264,   264,   264,   265,
     266,   267,   268,   269,   271,   270,   272,   272,   273,   273,
     275,   274,   277,   276,   278,   278,   278,   279,   279,   281,
     280,   283,   282,   285,   284,   286,   286,   287,   287,   287,
     287,   287,   287,   288,   289,   290,   291,   292,   293,   295,
     294,   296,   296,   297,   297,   299,   298,   301,   300,   302,
     302,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   305,   304,   307,   306,
     309,   308,   311,   310,   313,   312,   315,   314,   317,   316,
     319,   318,   321,   320,   322,   322,   322,   322,   323,   324,
     326,   325,   327,   327,   328,   328,   330,   329,   331,   331,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   334,   333,
     336,   335,   337,   337,   338,   338,   340,   339,   342,   341,
     343,   343,   344,   344,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   346,   347,   348,   350,   349,   352,
     351,   354,   353,   355,   357,   356,   358,   360,   359,   361,
     361,   362,   362,   364,   363,   366,   365,   367,   367,   368,
     368,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     370,   372,   371,   373,   374,   375,   376,   378,   377,   379,
     379,   380,   380,   382,   381,   384,   383,   385,   385,   386,
     386,   386,   386,   386,   386,   386,   388,   387,   390,   389,
     392,   391,   394,   393,   395,   395,   396,   396,   398,   397,
     400,   399,   401,   401,   402,   402,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   405,   404,   407,   406,   409,   408,   411,   410,   413,
     412,   415,   414,   417,   416,   419,   418,   421,   420,   423,
     422,   425,   424,   427,   426,   429,   428,   430,   430,   432,
     431,   433,   433,   435,   434,   436,   436,   437,   437,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     439,   441,   440,   442,   443,   445,   444,   446,   446,   447,
     447,   447,   447,   447,   449,   448,   451,   450,   453,   452,
     455,   454,   456,   456,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   458,   460,   459,   462,   461,   463,   465,   464,   466,
     467,   469,   468,   470,   470,   472,   471,   473,   474,   475,
     477,   476,   478,   478,   478,   478,   478,   480,   479,   482,
     481,   484,   483,   486,   485,   488,   487,   490,   489,   491,
     491,   492,   494,   493,   495,   495,   497,   496,   498,   498,
     499,   499,   499,   499,   499,   499,   499,   500,   502,   501,
     504,   503,   505,   505,   507,   506,   508,   508,   509,   509,
     509,   509,   511,   510,   512,   513,   514
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
       3,     3,     3,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
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
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
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
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
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
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_LOGGING", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp4_object", "$@18", "sub_dhcp4",
  "$@19", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@20",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@21", "interfaces_list", "$@22", "dhcp_socket_type", "$@23",
  "socket_type", "outbound_interface", "$@24", "outbound_interface_value",
  "re_detect", "lease_database", "$@25", "hosts_database", "$@26",
  "hosts_databases", "$@27", "database_list", "not_empty_database_list",
  "database", "$@28", "database_map_params", "database_map_param",
  "database_type", "$@29", "db_type", "user", "$@30", "password", "$@31",
  "host", "$@32", "port", "name", "$@33", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@34", "keyspace", "$@35",
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@37", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@38",
  "sub_hooks_library", "$@39", "hooks_params", "hooks_param", "library",
  "$@40", "parameters", "$@41", "expired_leases_processing", "$@42",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@43",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@44",
  "sub_subnet4", "$@45", "subnet4_params", "subnet4_param", "subnet",
  "$@46", "subnet_4o6_interface", "$@47", "subnet_4o6_interface_id",
  "$@48", "subnet_4o6_subnet", "$@49", "interface", "$@50", "interface_id",
  "$@51", "client_class", "$@52", "require_client_classes", "$@53",
  "reservation_mode", "$@54", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@55", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@56",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@57", "sub_option_def_list", "$@58", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@59",
  "sub_option_def", "$@60", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@61",
  "option_def_record_types", "$@62", "space", "$@63", "option_def_space",
  "option_def_encapsulate", "$@64", "option_def_array", "option_data_list",
  "$@65", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@66", "sub_option_data", "$@67",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@68",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@69", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@70", "sub_pool4", "$@71",
  "pool_params", "pool_param", "pool_entry", "$@72", "user_context",
  "$@73", "comment", "$@74", "reservations", "$@75", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@76", "sub_reservation",
  "$@77", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@78", "server_hostname", "$@79",
  "boot_file_name", "$@80", "ip_address", "$@81", "ip_addresses", "$@82",
  "duid", "$@83", "hw_address", "$@84", "client_id_value", "$@85",
  "circuit_id_value", "$@86", "flex_id_value", "$@87", "hostname", "$@88",
  "reservation_client_classes", "$@89", "relay", "$@90", "relay_map",
  "client_classes", "$@91", "client_classes_list", "client_class_entry",
  "$@92", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@93",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@94",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@95", "control_socket_name", "$@96", "dhcp_ddns", "$@97",
  "sub_dhcp_ddns", "$@98", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@99", "server_ip", "$@100",
  "server_port", "sender_ip", "$@101", "sender_port", "max_queue_size",
  "ncr_protocol", "$@102", "ncr_protocol_value", "ncr_format", "$@103",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@104", "replace_client_name_value",
  "generated_prefix", "$@105", "dhcp6_json_object", "$@106",
  "dhcpddns_json_object", "$@107", "control_agent_json_object", "$@108",
  "logging_object", "$@109", "sub_logging", "$@110", "logging_params",
  "logging_param", "loggers", "$@111", "loggers_entries", "logger_entry",
  "$@112", "logger_params", "logger_param", "debuglevel", "severity",
  "$@113", "output_options_list", "$@114", "output_options_list_content",
  "output_entry", "$@115", "output_params_list", "output_params", "output",
  "$@116", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   245,   245,   245,   246,   246,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   251,   252,   252,   253,   253,
     254,   254,   255,   255,   256,   256,   257,   257,   265,   266,
     267,   268,   269,   270,   271,   274,   279,   279,   290,   293,
     294,   297,   301,   308,   308,   315,   316,   319,   323,   330,
     330,   337,   338,   341,   345,   356,   366,   366,   382,   383,
     387,   388,   389,   390,   391,   392,   395,   395,   410,   410,
     419,   420,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     455,   460,   465,   470,   475,   480,   486,   486,   497,   498,
     501,   502,   503,   504,   505,   506,   507,   510,   510,   519,
     519,   529,   529,   536,   537,   540,   540,   547,   549,   553,
     559,   559,   571,   571,   583,   583,   593,   594,   597,   598,
     601,   601,   611,   612,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   635,   635,   642,   643,   644,   645,   648,   648,
     656,   656,   664,   664,   672,   677,   677,   685,   690,   695,
     700,   705,   710,   715,   720,   720,   728,   728,   736,   741,
     746,   746,   756,   757,   760,   761,   762,   763,   764,   767,
     772,   777,   782,   787,   792,   792,   802,   803,   806,   807,
     810,   810,   820,   820,   830,   831,   832,   835,   836,   839,
     839,   847,   847,   855,   855,   866,   867,   870,   871,   872,
     873,   874,   875,   878,   883,   888,   893,   898,   903,   911,
     911,   924,   925,   928,   929,   936,   936,   962,   962,   973,
     974,   978,   979,   980,   981,   982,   983,   984,   985,   986,
     987,   988,   989,   990,   991,   992,   993,   994,   995,   996,
     997,   998,   999,  1000,  1001,  1002,  1005,  1005,  1013,  1013,
    1021,  1021,  1029,  1029,  1037,  1037,  1045,  1045,  1053,  1053,
    1061,  1061,  1071,  1071,  1078,  1079,  1080,  1081,  1084,  1089,
    1096,  1096,  1107,  1108,  1112,  1113,  1116,  1116,  1124,  1125,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1152,  1152,
    1165,  1165,  1174,  1175,  1178,  1179,  1184,  1184,  1199,  1199,
    1213,  1214,  1217,  1218,  1221,  1222,  1223,  1224,  1225,  1226,
    1227,  1228,  1229,  1230,  1233,  1235,  1240,  1242,  1242,  1250,
    1250,  1258,  1258,  1266,  1268,  1268,  1276,  1285,  1285,  1297,
    1298,  1303,  1304,  1309,  1309,  1321,  1321,  1333,  1334,  1339,
    1340,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,
    1356,  1358,  1358,  1366,  1368,  1370,  1375,  1383,  1383,  1395,
    1396,  1399,  1400,  1403,  1403,  1413,  1413,  1423,  1424,  1427,
    1428,  1429,  1430,  1431,  1432,  1433,  1436,  1436,  1444,  1444,
    1469,  1469,  1499,  1499,  1509,  1510,  1513,  1514,  1517,  1517,
    1526,  1526,  1535,  1536,  1539,  1540,  1544,  1545,  1546,  1547,
    1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,  1556,  1557,
    1558,  1561,  1561,  1569,  1569,  1577,  1577,  1585,  1585,  1593,
    1593,  1603,  1603,  1611,  1611,  1619,  1619,  1627,  1627,  1635,
    1635,  1643,  1643,  1651,  1651,  1664,  1664,  1674,  1675,  1681,
    1681,  1691,  1692,  1695,  1695,  1705,  1706,  1709,  1710,  1713,
    1714,  1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,  1723,
    1726,  1728,  1728,  1736,  1745,  1752,  1752,  1762,  1763,  1766,
    1767,  1768,  1769,  1770,  1773,  1773,  1781,  1781,  1791,  1791,
    1803,  1803,  1813,  1814,  1817,  1818,  1819,  1820,  1821,  1822,
    1823,  1824,  1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,
    1833,  1836,  1841,  1841,  1849,  1849,  1857,  1862,  1862,  1870,
    1875,  1880,  1880,  1888,  1889,  1892,  1892,  1900,  1905,  1910,
    1915,  1915,  1923,  1926,  1929,  1932,  1935,  1941,  1941,  1951,
    1951,  1958,  1958,  1965,  1965,  1977,  1977,  1987,  1987,  1998,
    1999,  2003,  2007,  2007,  2019,  2020,  2024,  2024,  2032,  2033,
    2036,  2037,  2038,  2039,  2040,  2041,  2042,  2045,  2050,  2050,
    2058,  2058,  2068,  2069,  2072,  2072,  2080,  2081,  2084,  2085,
    2086,  2087,  2090,  2090,  2098,  2103,  2108
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
#line 4662 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2113 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
