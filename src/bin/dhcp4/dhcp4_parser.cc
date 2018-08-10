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
      case 181: // value
      case 185: // map_value
      case 223: // socket_type
      case 226: // outbound_interface_value
      case 248: // db_type
      case 332: // hr_mode
      case 480: // ncr_protocol_value
      case 488: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 165: // "boolean"
        value.move< bool > (that.value);
        break;

      case 164: // "floating point"
        value.move< double > (that.value);
        break;

      case 163: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 162: // "constant string"
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
      case 181: // value
      case 185: // map_value
      case 223: // socket_type
      case 226: // outbound_interface_value
      case 248: // db_type
      case 332: // hr_mode
      case 480: // ncr_protocol_value
      case 488: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 165: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 164: // "floating point"
        value.copy< double > (that.value);
        break;

      case 163: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 162: // "constant string"
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
            case 162: // "constant string"

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 163: // "integer"

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 164: // "floating point"

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 165: // "boolean"

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 181: // value

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 185: // map_value

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 223: // socket_type

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 226: // outbound_interface_value

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 248: // db_type

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 332: // hr_mode

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 480: // ncr_protocol_value

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 488: // replace_client_name_value

#line 241 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 181: // value
      case 185: // map_value
      case 223: // socket_type
      case 226: // outbound_interface_value
      case 248: // db_type
      case 332: // hr_mode
      case 480: // ncr_protocol_value
      case 488: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 165: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 164: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 163: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 162: // "constant string"
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
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 295 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 346 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 350 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 376 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 400 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 419 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 681 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 684 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1481 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 761 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 853 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1060 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1135 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1159 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1191 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1223 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1283 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2250 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2260 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2336 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2345 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2363 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1427 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2502 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2625 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2643 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2689 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2725 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2916 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2925 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3038 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1903 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3192 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1970 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1976 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1992 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3269 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2000 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3368 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2156 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3516 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3520 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -777;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     274,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,    37,    27,    71,   102,   152,   156,
     179,   188,   189,   205,   220,   221,   222,   230,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,    27,  -113,    14,    68,    70,   183,
      39,   427,    22,   151,    84,   -63,   457,   -21,  -777,   168,
     264,   272,   269,   279,  -777,  -777,  -777,  -777,  -777,   287,
    -777,    38,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     304,   308,  -777,  -777,  -777,  -777,  -777,  -777,   311,   312,
     319,   320,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   321,  -777,  -777,  -777,    61,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     322,  -777,   147,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,   323,   324,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   167,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,   185,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,   284,   307,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   328,  -777,  -777,   326,
    -777,  -777,  -777,   334,  -777,  -777,   331,   337,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,   338,   339,  -777,  -777,  -777,  -777,   333,   345,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,   191,  -777,  -777,  -777,   346,  -777,  -777,   347,  -777,
     348,   349,  -777,  -777,   355,   356,   359,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,   194,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   195,  -777,  -777,  -777,    27,    27,  -777,
     187,   360,   362,   363,   365,   366,  -777,    14,  -777,   370,
     372,   212,   214,   376,   377,   383,   385,   389,   391,   234,
     235,   237,   239,   401,   407,   408,   415,   417,   432,   433,
     434,   439,   441,   442,   285,   443,   450,    68,  -777,   451,
     452,   453,   293,    70,  -777,   455,   456,   460,   462,   463,
     464,   466,   298,   309,   467,   468,   469,   471,   183,  -777,
     473,    39,  -777,   474,   476,   477,   478,   480,   481,   484,
     485,  -777,   427,  -777,   487,   488,   330,   490,   492,   493,
     336,  -777,   151,   494,   340,   341,  -777,    84,   498,   499,
     -41,  -777,   343,   505,   506,   350,   507,   351,   354,   520,
     522,   367,   368,   369,   527,   532,   533,   534,   457,  -777,
     535,   -21,  -777,  -777,  -777,   536,   537,   538,    27,    27,
      27,  -777,   539,   540,  -777,  -777,   379,   380,   381,   541,
     542,   545,  -777,  -777,  -777,  -777,   546,   548,   549,   552,
     551,   397,   555,   556,   557,   558,   559,  -777,   560,   561,
    -777,   564,   109,   121,  -777,  -777,   402,   403,   409,   565,
     424,   425,   426,  -777,  -777,   -10,   564,   428,   584,  -777,
     435,  -777,   564,   436,   437,   438,   440,   444,   445,   446,
    -777,   447,   448,  -777,   449,   454,   458,  -777,  -777,   459,
    -777,  -777,  -777,   461,    27,  -777,  -777,   465,   470,  -777,
     472,  -777,  -777,    25,   475,  -777,  -777,  -777,   -80,   479,
     482,   483,  -777,   589,  -777,    27,    68,   -21,  -777,  -777,
    -777,    70,   574,  -777,  -777,  -777,   258,   258,   594,   596,
     597,   605,   606,  -777,  -777,  -777,    73,   607,   608,   610,
      -1,    60,   457,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,   611,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,    86,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   615,
    -777,   197,   207,   213,  -777,   217,  -777,  -777,  -777,  -777,
    -777,  -777,   592,   620,   621,   622,   624,  -777,  -777,   625,
     626,   627,   629,   631,  -777,   223,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,   233,  -777,   630,   634,  -777,  -777,
     632,   636,  -777,  -777,   637,   639,  -777,  -777,   640,   644,
    -777,  -777,   642,   646,  -777,  -777,  -777,  -777,  -777,  -777,
      81,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   110,  -777,
    -777,   645,   647,  -777,  -777,   648,   649,  -777,   651,   652,
     653,   654,   655,   656,   240,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,   241,  -777,  -777,
    -777,   260,   491,  -777,   657,   658,  -777,  -777,  -777,  -777,
     659,  -777,   244,  -777,  -777,  -777,  -777,   660,   574,  -777,
     661,   662,   664,   665,   508,   497,   509,   510,   511,   666,
     669,   513,   514,   515,   516,   517,   258,  -777,  -777,   258,
    -777,   594,   183,  -777,   596,   151,  -777,   597,    84,  -777,
     605,   390,  -777,   606,    73,  -777,    42,   607,  -777,   427,
    -777,   608,   -63,  -777,   610,   518,   521,   523,   524,   525,
     526,    -1,  -777,   676,   679,    60,  -777,  -777,  -777,   684,
     682,    39,  -777,   611,   687,  -777,   192,   615,  -777,   530,
    -777,   288,   531,   543,   544,  -777,  -777,  -777,  -777,  -777,
     547,   550,  -777,  -777,  -777,  -777,  -777,  -777,   263,  -777,
     267,  -777,   686,  -777,   688,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,   271,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   691,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   689,
     695,  -777,  -777,  -777,  -777,  -777,   692,  -777,   275,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,   553,   554,  -777,
    -777,   562,   281,  -777,   564,  -777,   697,  -777,  -777,  -777,
    -777,  -777,   282,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   390,  -777,   698,   563,  -777,    42,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   699,   567,   700,   192,
    -777,  -777,   569,  -777,  -777,   635,  -777,   571,  -777,  -777,
     701,  -777,  -777,   248,  -777,    -9,   701,  -777,  -777,   703,
     706,   707,   306,  -777,  -777,  -777,  -777,  -777,  -777,   709,
     583,   576,   587,    -9,  -777,   572,  -777,  -777,  -777,  -777,
    -777
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   118,     9,   255,    11,   413,    13,
     438,    15,   338,    17,   346,    19,   383,    21,   220,    23,
     528,    25,   591,    27,    45,    39,     0,     0,     0,     0,
       0,   440,     0,   348,   385,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   589,   583,   585,   587,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   107,   133,
       0,     0,   459,   461,   463,   131,   140,   142,     0,     0,
       0,     0,   247,   336,   375,   308,   426,   428,   198,   487,
     430,   212,   231,     0,   513,   526,   100,     0,    70,    72,
      73,    74,    75,    91,    92,    78,    79,    98,    80,    81,
      82,    86,    87,    76,    77,    84,    85,    96,    97,    99,
      93,    94,    95,    83,    88,    89,    90,   120,   122,   126,
       0,   117,     0,   109,   111,   112,   113,   114,   115,   116,
     286,   288,   290,   405,   284,   292,   294,     0,     0,   300,
     298,   296,   483,   283,   259,   260,   261,   274,     0,   257,
     264,   278,   279,   280,   265,   266,   269,   270,   272,   267,
     268,   262,   263,   281,   282,   271,   275,   276,   277,   273,
     424,   423,   419,   420,   418,     0,   415,   417,   421,   422,
     481,   469,   471,   475,   473,   479,   477,   465,   458,   452,
     456,   457,     0,   441,   442,   453,   454,   455,   449,   444,
     450,   446,   447,   448,   451,   445,     0,   365,   183,     0,
     369,   367,   372,     0,   361,   362,     0,   349,   350,   352,
     364,   353,   354,   355,   371,   356,   357,   358,   359,   360,
     399,     0,     0,   397,   398,   401,   402,     0,   386,   387,
     389,   390,   391,   392,   393,   394,   395,   396,   227,   229,
     224,     0,   222,   225,   226,     0,   552,   554,     0,   557,
       0,     0,   561,   565,     0,     0,     0,   570,   577,   579,
     581,   550,   548,   549,     0,   530,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   596,     0,   593,   595,    44,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    55,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    69,     0,
       0,     0,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   256,
       0,     0,   414,     0,     0,     0,     0,     0,     0,     0,
       0,   439,     0,   339,     0,     0,     0,     0,     0,     0,
       0,   347,     0,     0,     0,     0,   384,     0,     0,     0,
       0,   221,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   529,
       0,     0,   592,    48,    41,     0,     0,     0,     0,     0,
       0,    59,     0,     0,   105,   106,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   512,     0,     0,
      71,     0,     0,     0,   130,   110,     0,     0,     0,     0,
       0,     0,     0,   306,   307,     0,     0,     0,     0,   258,
       0,   416,     0,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,   363,     0,     0,     0,   374,   351,     0,
     403,   404,   388,     0,     0,   223,   551,     0,     0,   556,
       0,   559,   560,     0,     0,   567,   568,   569,     0,     0,
       0,     0,   531,     0,   594,     0,     0,     0,   584,   586,
     588,     0,     0,   460,   462,   464,     0,     0,   144,   249,
     340,   377,   310,    38,   427,   429,     0,     0,   432,   214,
       0,     0,     0,    49,   121,   124,   125,   123,   128,   129,
     127,   287,   289,   291,   407,   285,   293,   295,   302,   303,
     304,   305,   301,   299,   297,     0,   425,   482,   470,   472,
     476,   474,   480,   478,   466,   366,   184,   370,   368,   373,
     400,   228,   230,   553,   555,   558,   563,   564,   562,   566,
     572,   573,   574,   575,   576,   571,   578,   580,   582,     0,
      42,     0,     0,     0,   138,     0,   135,   137,   170,   176,
     178,   180,     0,     0,     0,     0,     0,   192,   194,     0,
       0,     0,     0,     0,   169,     0,   150,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   165,   166,   167,
     162,   168,   163,   164,     0,   148,     0,   145,   146,   253,
       0,   250,   251,   344,     0,   341,   342,   381,     0,   378,
     379,   314,     0,   311,   312,   207,   208,   209,   210,   211,
       0,   200,   202,   203,   204,   205,   206,   491,     0,   489,
     436,     0,   433,   434,   218,     0,   215,   216,     0,     0,
       0,     0,     0,     0,     0,   233,   235,   236,   237,   238,
     239,   240,   522,   524,   521,   519,   520,     0,   515,   517,
     518,     0,    51,   411,     0,   408,   409,   467,   485,   486,
       0,   600,     0,   598,    67,   590,   108,     0,     0,   134,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,   141,     0,
     143,     0,     0,   248,     0,   348,   337,     0,   385,   376,
       0,     0,   309,     0,     0,   199,   493,     0,   488,   440,
     431,     0,     0,   213,     0,     0,     0,     0,     0,     0,
       0,     0,   232,     0,     0,     0,   514,   527,    53,     0,
      52,     0,   406,     0,     0,   484,     0,     0,   597,     0,
     136,     0,     0,     0,     0,   182,   185,   186,   187,   188,
       0,     0,   196,   197,   189,   190,   191,   151,     0,   147,
       0,   252,     0,   343,     0,   380,   335,   332,   321,   322,
     324,   318,   319,   320,   330,   331,   329,     0,   316,   323,
     333,   334,   325,   326,   327,   328,   313,   201,   509,     0,
     507,   508,   500,   501,   505,   506,   502,   503,   504,     0,
     494,   495,   497,   498,   499,   490,     0,   435,     0,   217,
     241,   242,   243,   244,   245,   246,   234,     0,     0,   516,
      50,     0,     0,   410,     0,   614,     0,   612,   610,   604,
     608,   609,     0,   602,   606,   607,   605,   599,   139,   172,
     173,   174,   175,   171,   177,   179,   181,   193,   195,   149,
     254,   345,   382,     0,   315,     0,     0,   492,     0,   437,
     219,   523,   525,    54,   412,   468,     0,     0,     0,     0,
     601,   317,     0,   511,   496,     0,   611,     0,   603,   510,
       0,   613,   618,     0,   616,     0,     0,   615,   626,     0,
       0,     0,     0,   620,   622,   623,   624,   625,   617,     0,
       0,     0,     0,     0,   619,     0,   628,   629,   630,   621,
     627
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,   -51,  -777,   219,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -485,  -777,  -777,  -777,
     -66,  -777,  -777,  -777,   371,  -777,  -777,  -777,  -777,   158,
     342,   -43,   -14,    -7,  -777,  -777,    12,  -777,  -777,   159,
     344,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,   -47,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,   -74,  -777,  -544,   -33,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     -44,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   -82,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   -91,  -777,
    -777,  -777,   -87,   361,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,   -60,  -777,  -777,  -777,  -777,  -777,  -777,  -776,  -777,
    -777,  -777,   -34,  -777,  -777,  -777,   -29,   375,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -773,  -777,  -777,  -777,
     -64,  -777,   -11,  -777,  -770,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,   -39,  -777,  -777,  -185,   -61,  -777,  -777,
    -777,  -777,  -777,   -23,  -777,  -777,  -777,   -19,  -777,   386,
    -777,   -62,  -777,  -777,  -777,  -777,  -777,   -56,  -777,  -777,
    -777,  -777,  -777,   -13,  -777,  -777,  -777,   -16,  -777,  -777,
    -777,   -17,  -777,   374,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,   -31,  -777,  -777,  -777,   -42,
     416,  -777,  -777,   -54,  -777,   -26,  -777,   -36,  -777,  -777,
    -777,    -2,  -777,  -777,  -777,     7,  -777,   410,    -6,  -777,
       5,  -777,     6,  -777,   216,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -766,  -777,  -777,  -777,  -777,  -777,    16,  -777,
    -777,  -777,  -139,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,     0,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
     242,   378,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,
    -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,  -777,   270,
     382,  -777,  -777,  -777,    -8,  -777,  -777,  -141,  -777,  -777,
    -777,  -777,  -777,  -777,  -156,  -777,  -777,  -172,  -777,  -777,
    -777,  -777,  -777
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   574,
      82,    83,    39,    64,    79,    80,   584,   752,   829,   830,
     664,    41,    66,    91,    92,    93,   341,    43,    67,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   349,   162,
     163,    45,    68,   164,   379,   165,   380,   587,   166,   381,
     590,   167,   136,   356,   137,   350,   645,   646,   647,   767,
     138,   357,   139,   358,   686,   687,   688,   789,   665,   666,
     667,   770,   943,   668,   771,   669,   772,   670,   773,   671,
     672,   415,   673,   674,   675,   676,   677,   678,   679,   680,
     779,   681,   780,   682,   683,   140,   369,   710,   711,   712,
     713,   714,   715,   716,   141,   372,   725,   726,   727,   812,
      59,    75,   291,   292,   293,   428,   294,   429,   142,   373,
     734,   735,   736,   737,   738,   739,   740,   741,   143,   363,
     690,   691,   692,   792,    47,    69,   188,   189,   190,   389,
     191,   385,   192,   386,   193,   387,   194,   390,   195,   391,
     196,   396,   197,   395,   198,   394,   602,   199,   200,   144,
     366,   702,   703,   704,   801,   877,   878,   145,   364,    53,
      72,   694,   695,   696,   795,    55,    73,   256,   257,   258,
     259,   260,   261,   262,   414,   263,   418,   264,   417,   265,
     266,   419,   267,   146,   365,   698,   699,   700,   798,    57,
      74,   277,   278,   279,   280,   281,   423,   282,   283,   284,
     285,   202,   388,   754,   755,   756,   831,    49,    70,   215,
     216,   217,   400,   147,   367,   148,   368,   149,   371,   721,
     722,   723,   809,    51,    71,   232,   233,   234,   150,   353,
     151,   354,   152,   355,   238,   410,   759,   834,   239,   404,
     240,   405,   241,   407,   242,   406,   243,   409,   244,   408,
     245,   403,   209,   397,   760,   153,   370,   718,   719,   806,
     899,   900,   901,   902,   903,   955,   904,   154,   155,   375,
     747,   748,   749,   823,   750,   824,   156,   376,    61,    76,
     314,   315,   316,   317,   433,   318,   434,   319,   320,   436,
     321,   322,   323,   439,   628,   324,   440,   325,   326,   327,
     328,   444,   635,   329,   445,   330,   446,   331,   447,    94,
     343,    95,   344,    96,   345,    97,   342,    63,    77,   333,
     334,   335,   450,   762,   763,   836,   932,   933,   934,   935,
     968,   936,   966,   983,   984,   985,   992,   993,   994,   999,
     995,   996,   997
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   126,   161,   183,   211,   228,   212,   254,   273,   290,
     311,   246,   275,    78,   168,   203,   218,   230,   276,   268,
     286,   603,   312,   684,    84,   872,   184,   607,   873,   255,
     274,   876,    29,   205,    30,   885,    31,    28,   288,   289,
     626,   347,   169,   204,   219,   231,   348,   269,   287,    81,
     313,   630,   631,   632,   633,   185,   201,   214,   229,   213,
     288,   289,   186,   206,   377,   235,   102,   103,   104,   378,
     598,   599,   600,   601,   207,   208,   236,   237,    40,    98,
     113,   187,   157,   158,   804,   634,   159,   805,    99,   160,
     100,   101,   102,   103,   104,   105,   106,   107,   114,    89,
     113,   114,   248,   728,   729,   730,   731,   732,   733,    42,
     210,   116,   117,   807,   116,   117,   808,   332,   108,   109,
     110,   111,   112,   585,   586,   180,   113,   114,   181,   888,
     889,   988,   116,   117,   989,   990,   991,   115,   588,   589,
     116,   117,   116,   117,   248,   270,   249,   250,   271,   272,
     383,    85,   118,   119,   627,   384,   116,   117,   120,    44,
      86,    87,    88,    46,   705,   706,   707,   708,   121,   709,
     398,   122,   742,   743,   336,   399,    89,   872,   123,   124,
     873,   247,   125,   876,   227,   757,    48,   885,   401,    32,
      33,    34,    35,   402,   430,    50,    52,   448,   451,   431,
     377,    89,   449,   452,    89,   764,   101,   102,   103,   104,
     451,   248,    54,   249,   250,   765,   383,   251,   252,   253,
     768,   766,    89,   116,   117,   769,   786,    56,    58,    60,
      89,   787,    89,   108,   109,   110,   786,    62,   170,   171,
     172,   788,   114,   821,   825,   858,    89,   837,   822,   826,
     838,   986,   248,   173,   987,   116,   117,   174,   175,   176,
     177,   178,   179,   448,   116,   117,   786,   337,   827,   180,
     398,   949,   181,   120,   953,   950,   338,   339,   430,   954,
     182,    90,   340,   960,   401,   969,   453,   454,   648,   964,
     970,   346,   411,   649,   650,   651,   652,   653,   654,   655,
     656,   657,   658,   659,   660,   661,   662,   663,   351,  1003,
     412,   126,   352,    89,  1004,   359,   360,   161,   248,   939,
     940,   941,   942,   361,   362,   374,   382,   392,   393,   168,
     416,   925,   183,   926,   927,   211,   413,   212,   420,   421,
     422,   426,   424,   425,   203,    89,   228,   218,   427,   455,
     432,   435,   437,   438,    89,   184,   254,   169,   230,   441,
     442,   273,   205,   443,   456,   275,   457,   458,   268,   459,
     460,   276,   204,   286,   462,   219,   463,   464,   255,   465,
     466,   467,   311,   274,   185,   201,   231,   468,   214,   469,
     213,   186,   206,   470,   312,   471,   269,   472,   473,   229,
     474,   287,   475,   207,   208,   476,   235,   558,   559,   560,
     187,   477,   478,   101,   102,   103,   104,   236,   237,   479,
      89,   480,   313,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   481,   482,   483,   965,
     108,   109,   110,   484,   112,   485,   486,   488,   487,   114,
     248,   102,   103,   104,   489,   491,   492,   493,   494,   496,
     497,   503,   116,   117,   498,   175,   499,   500,   501,   179,
     502,   505,   506,   507,   504,   508,   180,   510,   512,   181,
     513,   514,   515,   622,   516,   517,   114,   182,   518,   519,
     126,   521,   522,   523,   524,   161,   525,   526,   529,   116,
     117,   527,   533,   534,   640,   530,   531,   168,   536,   537,
     538,   540,   220,   539,   541,   744,   311,   542,   221,   222,
     223,   224,   225,   226,   543,   227,   544,   745,   312,   116,
     117,   548,   545,   546,   547,   169,   549,   550,   551,   553,
     555,   563,   564,   565,   556,   557,   561,   562,   566,   567,
     568,   569,    89,   570,   571,   746,   313,   572,    30,   575,
     576,   577,   578,   579,   591,   592,   580,   581,   582,   583,
     594,   593,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   595,   596,   597,    89,
     604,   605,   309,   310,   639,   644,   774,   606,   608,   609,
     610,   685,   611,   689,   693,   629,   612,   613,   614,   615,
     616,   617,   697,   701,   717,   720,   618,   724,   753,    89,
     619,   620,   761,   621,   775,   776,   777,   623,   778,   781,
     782,   783,   624,   784,   625,   785,   790,   791,   793,   794,
     980,   636,   797,   796,   637,   638,   799,   800,   802,   803,
     811,   810,   814,   828,   813,   815,   816,   817,   818,   819,
     820,   833,   846,   832,   839,   841,   842,   835,   843,   844,
     850,   845,   847,   851,   849,   848,   852,   853,   854,   855,
     917,   910,   856,   918,   911,   921,   912,   913,   914,   915,
     920,   924,   938,   944,   951,   956,   952,   957,   958,   573,
     959,   967,   972,   975,   977,   945,   946,  1000,   982,   947,
    1001,  1002,   948,  1005,   641,   961,   962,   859,   461,   490,
     643,   840,   887,   909,   963,   908,   183,   495,   973,   254,
     976,   979,   273,   981,  1010,   866,   275,   874,   203,  1007,
     890,   268,   276,   228,   286,   892,   290,   880,  1006,   184,
    1008,   255,   894,   857,   274,   230,   205,   871,   867,   744,
     861,   916,   891,   860,   886,   211,   204,   212,   971,   269,
     928,   745,   287,   509,   863,   881,   862,   218,   185,   201,
     895,   864,   930,   231,   865,   186,   206,   868,   879,   922,
     875,   535,   929,   893,   869,   882,   229,   207,   208,   746,
     896,   532,   923,   235,   187,   219,   883,   884,   528,   907,
     931,   897,   898,   870,   236,   237,   906,   511,   214,   974,
     213,   758,   520,   905,   751,   919,   552,   642,   978,   937,
     998,  1009,     0,   554,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   866,     0,   874,
       0,     0,   890,     0,     0,     0,     0,   892,     0,   880,
       0,     0,     0,   928,   894,     0,     0,     0,     0,   871,
     867,     0,     0,     0,   891,   930,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   929,     0,   881,     0,     0,
       0,     0,   895,     0,     0,     0,     0,     0,     0,   868,
     879,     0,   875,   931,     0,   893,   869,   882,     0,     0,
       0,     0,   896,     0,     0,     0,     0,     0,   883,   884,
       0,     0,     0,   897,   898,   870
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    70,    73,    74,    75,
      76,    72,    74,    64,    68,    69,    70,    71,    74,    73,
      74,   506,    76,   567,    10,   801,    69,   512,   801,    73,
      74,   801,     5,    69,     7,   801,     9,     0,   101,   102,
      15,     3,    68,    69,    70,    71,     8,    73,    74,   162,
      76,   131,   132,   133,   134,    69,    69,    70,    71,    70,
     101,   102,    69,    69,     3,    71,    24,    25,    26,     8,
      80,    81,    82,    83,    69,    69,    71,    71,     7,    11,
      58,    69,    12,    13,     3,   165,    16,     6,    20,    19,
      22,    23,    24,    25,    26,    27,    28,    29,    59,   162,
      58,    59,    60,   104,   105,   106,   107,   108,   109,     7,
      71,    72,    73,     3,    72,    73,     6,   138,    50,    51,
      52,    53,    54,    14,    15,    86,    58,    59,    89,    87,
      88,   140,    72,    73,   143,   144,   145,    69,    17,    18,
      72,    73,    72,    73,    60,    61,    62,    63,    64,    65,
       3,   137,    84,    85,   129,     8,    72,    73,    90,     7,
     146,   147,   148,     7,    91,    92,    93,    94,   100,    96,
       3,   103,   112,   113,     6,     8,   162,   953,   110,   111,
     953,    30,   114,   953,    98,    99,     7,   953,     3,   162,
     163,   164,   165,     8,     3,     7,     7,     3,     3,     8,
       3,   162,     8,     8,   162,     8,    23,    24,    25,    26,
       3,    60,     7,    62,    63,     8,     3,    66,    67,    68,
       3,     8,   162,    72,    73,     8,     3,     7,     7,     7,
     162,     8,   162,    50,    51,    52,     3,     7,    55,    56,
      57,     8,    59,     3,     3,   789,   162,     3,     8,     8,
       6,     3,    60,    70,     6,    72,    73,    74,    75,    76,
      77,    78,    79,     3,    72,    73,     3,     3,     8,    86,
       3,     8,    89,    90,     3,     8,     4,     8,     3,     8,
      97,   347,     3,     8,     3,     3,   337,   338,    30,     8,
       8,     4,     8,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,     4,     3,
       3,   377,     4,   162,     8,     4,     4,   383,    60,    31,
      32,    33,    34,     4,     4,     4,     4,     4,     4,   383,
       4,   139,   398,   141,   142,   401,     8,   401,     4,     8,
       3,     8,     4,     4,   398,   162,   412,   401,     3,   162,
       4,     4,     4,     4,   162,   398,   422,   383,   412,     4,
       4,   427,   398,     4,     4,   427,     4,     4,   422,     4,
       4,   427,   398,   427,     4,   401,     4,   165,   422,   165,
       4,     4,   448,   427,   398,   398,   412,     4,   401,     4,
     401,   398,   398,     4,   448,     4,   422,   163,   163,   412,
     163,   427,   163,   398,   398,     4,   412,   458,   459,   460,
     398,     4,     4,    23,    24,    25,    26,   412,   412,     4,
     162,     4,   448,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,     4,     4,     4,   924,
      50,    51,    52,     4,    54,     4,     4,     4,   163,    59,
      60,    24,    25,    26,     4,     4,     4,     4,   165,     4,
       4,   163,    72,    73,     4,    75,     4,     4,     4,    79,
       4,     4,     4,     4,   165,     4,    86,     4,     4,    89,
       4,     4,     4,   534,     4,     4,    59,    97,     4,     4,
     556,     4,     4,   163,     4,   561,     4,     4,     4,    72,
      73,   165,     4,     4,   555,   165,   165,   561,   165,     4,
       4,     4,    85,   163,   163,   581,   582,   163,    91,    92,
      93,    94,    95,    96,     4,    98,     4,   581,   582,    72,
      73,     4,   165,   165,   165,   561,     4,     4,     4,     4,
       4,   162,   162,   162,     7,     7,     7,     7,     7,     7,
       5,     5,   162,     5,     5,   581,   582,     5,     7,   162,
       5,     5,     5,     5,   162,   162,     7,     7,     7,     5,
       5,   162,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   162,   162,   162,   162,
     162,     7,   135,   136,     5,    21,     4,   162,   162,   162,
     162,     7,   162,     7,     7,   130,   162,   162,   162,   162,
     162,   162,     7,     7,     7,     7,   162,     7,     7,   162,
     162,   162,     7,   162,     4,     4,     4,   162,     4,     4,
       4,     4,   162,     4,   162,     4,     6,     3,     6,     3,
       5,   162,     3,     6,   162,   162,     6,     3,     6,     3,
       3,     6,     3,   162,     6,     4,     4,     4,     4,     4,
       4,     3,   165,     6,     4,     4,     4,     8,     4,     4,
       4,   163,   163,     4,   163,   165,   163,   163,   163,   163,
       4,   163,   165,     4,   163,     3,   163,   163,   163,   163,
       6,     4,   162,   162,     8,     4,     8,     8,     3,   480,
       8,     4,     4,     4,     4,   162,   162,     4,     7,   162,
       4,     4,   162,     4,   556,   162,   162,   791,   347,   377,
     561,   768,   804,   814,   162,   812,   792,   383,   165,   795,
     163,   162,   798,   162,   162,   801,   798,   801,   792,   163,
     806,   795,   798,   809,   798,   806,   812,   801,   165,   792,
     163,   795,   806,   786,   798,   809,   792,   801,   801,   825,
     794,   821,   806,   792,   803,   831,   792,   831,   953,   795,
     836,   825,   798,   398,   797,   801,   795,   831,   792,   792,
     806,   798,   836,   809,   800,   792,   792,   801,   801,   831,
     801,   430,   836,   806,   801,   801,   809,   792,   792,   825,
     806,   427,   833,   809,   792,   831,   801,   801,   422,   811,
     836,   806,   806,   801,   809,   809,   809,   401,   831,   958,
     831,   605,   412,   807,   582,   825,   448,   557,   969,   837,
     986,  1003,    -1,   451,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   953,    -1,   953,
      -1,    -1,   958,    -1,    -1,    -1,    -1,   958,    -1,   953,
      -1,    -1,    -1,   969,   958,    -1,    -1,    -1,    -1,   953,
     953,    -1,    -1,    -1,   958,   969,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   969,    -1,   953,    -1,    -1,
      -1,    -1,   958,    -1,    -1,    -1,    -1,    -1,    -1,   953,
     953,    -1,   953,   969,    -1,   958,   953,   953,    -1,    -1,
      -1,    -1,   958,    -1,    -1,    -1,    -1,    -1,   953,   953,
      -1,    -1,    -1,   958,   958,   953
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,     0,     5,
       7,     9,   162,   163,   164,   165,   181,   182,   183,   188,
       7,   197,     7,   203,     7,   217,     7,   310,     7,   393,
       7,   409,     7,   345,     7,   351,     7,   375,     7,   286,
       7,   464,     7,   503,   189,   184,   198,   204,   218,   311,
     394,   410,   346,   352,   376,   287,   465,   504,   181,   190,
     191,   162,   186,   187,    10,   137,   146,   147,   148,   162,
     196,   199,   200,   201,   495,   497,   499,   501,    11,    20,
      22,    23,    24,    25,    26,    27,    28,    29,    50,    51,
      52,    53,    54,    58,    59,    69,    72,    73,    84,    85,
      90,   100,   103,   110,   111,   114,   196,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   228,   230,   236,   238,
     271,   280,   294,   304,   335,   343,   369,   399,   401,   403,
     414,   416,   418,   441,   453,   454,   462,    12,    13,    16,
      19,   196,   215,   216,   219,   221,   224,   227,   399,   401,
      55,    56,    57,    70,    74,    75,    76,    77,    78,    79,
      86,    89,    97,   196,   207,   208,   209,   212,   312,   313,
     314,   316,   318,   320,   322,   324,   326,   328,   330,   333,
     334,   369,   387,   399,   401,   403,   414,   416,   418,   438,
      71,   196,   326,   328,   369,   395,   396,   397,   399,   401,
      85,    91,    92,    93,    94,    95,    96,    98,   196,   369,
     399,   401,   411,   412,   413,   414,   416,   418,   420,   424,
     426,   428,   430,   432,   434,   436,   343,    30,    60,    62,
      63,    66,    67,    68,   196,   256,   353,   354,   355,   356,
     357,   358,   359,   361,   363,   365,   366,   368,   399,   401,
      61,    64,    65,   196,   256,   357,   363,   377,   378,   379,
     380,   381,   383,   384,   385,   386,   399,   401,   101,   102,
     196,   288,   289,   290,   292,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   135,
     136,   196,   399,   401,   466,   467,   468,   469,   471,   473,
     474,   476,   477,   478,   481,   483,   484,   485,   486,   489,
     491,   493,   138,   505,   506,   507,     6,     3,     4,     8,
       3,   202,   502,   496,   498,   500,     4,     3,     8,   214,
     231,     4,     4,   415,   417,   419,   229,   237,   239,     4,
       4,     4,     4,   305,   344,   370,   336,   400,   402,   272,
     442,   404,   281,   295,     4,   455,   463,     3,     8,   220,
     222,   225,     4,     3,     8,   317,   319,   321,   388,   315,
     323,   325,     4,     4,   331,   329,   327,   439,     3,     8,
     398,     3,     8,   437,   425,   427,   431,   429,   435,   433,
     421,     8,     3,     8,   360,   257,     4,   364,   362,   367,
       4,     8,     3,   382,     4,     4,     8,     3,   291,   293,
       3,     8,     4,   470,   472,     4,   475,     4,     4,   479,
     482,     4,     4,     4,   487,   490,   492,   494,     3,     8,
     508,     3,     8,   181,   181,   162,     4,     4,     4,     4,
       4,   200,     4,     4,   165,   165,     4,     4,     4,     4,
       4,     4,   163,   163,   163,   163,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   163,     4,     4,
     206,     4,     4,     4,   165,   216,     4,     4,     4,     4,
       4,     4,     4,   163,   165,     4,     4,     4,     4,   313,
       4,   396,     4,     4,     4,     4,     4,     4,     4,     4,
     413,     4,     4,   163,     4,     4,     4,   165,   355,     4,
     165,   165,   379,     4,     4,   289,   165,     4,     4,   163,
       4,   163,   163,     4,     4,   165,   165,   165,     4,     4,
       4,     4,   467,     4,   506,     4,     7,     7,   181,   181,
     181,     7,     7,   162,   162,   162,     7,     7,     5,     5,
       5,     5,     5,   183,   185,   162,     5,     5,     5,     5,
       7,     7,     7,     5,   192,    14,    15,   223,    17,    18,
     226,   162,   162,   162,     5,   162,   162,   162,    80,    81,
      82,    83,   332,   192,   162,     7,   162,   192,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   181,   162,   162,   162,    15,   129,   480,   130,
     131,   132,   133,   134,   165,   488,   162,   162,   162,     5,
     181,   205,   505,   215,    21,   232,   233,   234,    30,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,   196,   244,   245,   246,   249,   251,
     253,   255,   256,   258,   259,   260,   261,   262,   263,   264,
     265,   267,   269,   270,   244,     7,   240,   241,   242,     7,
     306,   307,   308,     7,   347,   348,   349,     7,   371,   372,
     373,     7,   337,   338,   339,    91,    92,    93,    94,    96,
     273,   274,   275,   276,   277,   278,   279,     7,   443,   444,
       7,   405,   406,   407,     7,   282,   283,   284,   104,   105,
     106,   107,   108,   109,   296,   297,   298,   299,   300,   301,
     302,   303,   112,   113,   196,   399,   401,   456,   457,   458,
     460,   466,   193,     7,   389,   390,   391,    99,   420,   422,
     440,     7,   509,   510,     8,     8,     8,   235,     3,     8,
     247,   250,   252,   254,     4,     4,     4,     4,     4,   266,
     268,     4,     4,     4,     4,     4,     3,     8,     8,   243,
       6,     3,   309,     6,     3,   350,     6,     3,   374,     6,
       3,   340,     6,     3,     3,     6,   445,     3,     6,   408,
       6,     3,   285,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   459,   461,     3,     8,     8,   162,   194,
     195,   392,     6,     3,   423,     8,   511,     3,     6,     4,
     233,     4,     4,     4,     4,   163,   165,   163,   165,   163,
       4,     4,   163,   163,   163,   163,   165,   245,   244,   242,
     312,   308,   353,   349,   377,   373,   196,   207,   208,   209,
     212,   256,   304,   322,   326,   328,   330,   341,   342,   369,
     399,   401,   414,   416,   418,   438,   339,   274,    87,    88,
     196,   256,   343,   369,   399,   401,   414,   416,   418,   446,
     447,   448,   449,   450,   452,   444,   411,   407,   288,   284,
     163,   163,   163,   163,   163,   163,   297,     4,     4,   457,
       6,     3,   395,   391,     4,   139,   141,   142,   196,   256,
     399,   401,   512,   513,   514,   515,   517,   510,   162,    31,
      32,    33,    34,   248,   162,   162,   162,   162,   162,     8,
       8,     8,     8,     3,     8,   451,     4,     8,     3,     8,
       8,   162,   162,   162,     8,   192,   518,     4,   516,     3,
       8,   342,     4,   165,   448,     4,   163,     4,   513,   162,
       5,   162,     7,   519,   520,   521,     3,     6,   140,   143,
     144,   145,   522,   523,   524,   526,   527,   528,   520,   525,
       4,     4,     4,     3,     8,     4,   165,   163,   163,   523,
     162
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   166,   168,   167,   169,   167,   170,   167,   171,   167,
     172,   167,   173,   167,   174,   167,   175,   167,   176,   167,
     177,   167,   178,   167,   179,   167,   180,   167,   181,   181,
     181,   181,   181,   181,   181,   182,   184,   183,   185,   186,
     186,   187,   187,   189,   188,   190,   190,   191,   191,   193,
     192,   194,   194,   195,   195,   196,   198,   197,   199,   199,
     200,   200,   200,   200,   200,   200,   202,   201,   204,   203,
     205,   205,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   207,   208,   209,   210,   211,   212,   214,   213,   215,
     215,   216,   216,   216,   216,   216,   216,   216,   218,   217,
     220,   219,   222,   221,   223,   223,   225,   224,   226,   226,
     227,   229,   228,   231,   230,   232,   232,   233,   235,   234,
     237,   236,   239,   238,   240,   240,   241,   241,   243,   242,
     244,   244,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     247,   246,   248,   248,   248,   248,   250,   249,   252,   251,
     254,   253,   255,   257,   256,   258,   259,   260,   261,   262,
     263,   264,   266,   265,   268,   267,   269,   270,   272,   271,
     273,   273,   274,   274,   274,   274,   274,   275,   276,   277,
     278,   279,   281,   280,   282,   282,   283,   283,   285,   284,
     287,   286,   288,   288,   288,   289,   289,   291,   290,   293,
     292,   295,   294,   296,   296,   297,   297,   297,   297,   297,
     297,   298,   299,   300,   301,   302,   303,   305,   304,   306,
     306,   307,   307,   309,   308,   311,   310,   312,   312,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   315,   314,   317,   316,   319,   318,
     321,   320,   323,   322,   325,   324,   327,   326,   329,   328,
     331,   330,   332,   332,   332,   332,   333,   334,   336,   335,
     337,   337,   338,   338,   340,   339,   341,   341,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   344,   343,   346,   345,
     347,   347,   348,   348,   350,   349,   352,   351,   353,   353,
     354,   354,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   356,   357,   358,   360,   359,   362,   361,   364,
     363,   365,   367,   366,   368,   370,   369,   371,   371,   372,
     372,   374,   373,   376,   375,   377,   377,   378,   378,   379,
     379,   379,   379,   379,   379,   379,   379,   379,   380,   382,
     381,   383,   384,   385,   386,   388,   387,   389,   389,   390,
     390,   392,   391,   394,   393,   395,   395,   396,   396,   396,
     396,   396,   396,   396,   398,   397,   400,   399,   402,   401,
     404,   403,   405,   405,   406,   406,   408,   407,   410,   409,
     411,   411,   412,   412,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   415,
     414,   417,   416,   419,   418,   421,   420,   423,   422,   425,
     424,   427,   426,   429,   428,   431,   430,   433,   432,   435,
     434,   437,   436,   439,   438,   440,   440,   442,   441,   443,
     443,   445,   444,   446,   446,   447,   447,   448,   448,   448,
     448,   448,   448,   448,   448,   448,   448,   448,   449,   451,
     450,   452,   453,   455,   454,   456,   456,   457,   457,   457,
     457,   457,   459,   458,   461,   460,   463,   462,   465,   464,
     466,   466,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   468,   470,   469,   472,   471,   473,   475,   474,   476,
     477,   479,   478,   480,   480,   482,   481,   483,   484,   485,
     487,   486,   488,   488,   488,   488,   488,   490,   489,   492,
     491,   494,   493,   496,   495,   498,   497,   500,   499,   502,
     501,   504,   503,   505,   505,   506,   508,   507,   509,   509,
     511,   510,   512,   512,   513,   513,   513,   513,   513,   513,
     513,   514,   516,   515,   518,   517,   519,   519,   521,   520,
     522,   522,   523,   523,   523,   523,   525,   524,   526,   527,
     528
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
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
  "$@50", "subnet_4o6_subnet", "$@51", "interface", "$@52", "interface_id",
  "$@53", "client_class", "$@54", "require_client_classes", "$@55",
  "reservation_mode", "$@56", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@57", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@58",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@59", "sub_option_def_list", "$@60", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@61",
  "sub_option_def", "$@62", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@63",
  "option_def_record_types", "$@64", "space", "$@65", "option_def_space",
  "option_def_encapsulate", "$@66", "option_def_array", "option_data_list",
  "$@67", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@68", "sub_option_data", "$@69",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@70",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@71", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@72", "sub_pool4", "$@73",
  "pool_params", "pool_param", "pool_entry", "$@74", "user_context",
  "$@75", "comment", "$@76", "reservations", "$@77", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@78", "sub_reservation",
  "$@79", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@80", "server_hostname", "$@81",
  "boot_file_name", "$@82", "ip_address", "$@83", "ip_addresses", "$@84",
  "duid", "$@85", "hw_address", "$@86", "client_id_value", "$@87",
  "circuit_id_value", "$@88", "flex_id_value", "$@89", "hostname", "$@90",
  "reservation_client_classes", "$@91", "relay", "$@92", "relay_map",
  "client_classes", "$@93", "client_classes_list", "client_class_entry",
  "$@94", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@95",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@96",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@97", "control_socket_name", "$@98", "dhcp_ddns", "$@99",
  "sub_dhcp_ddns", "$@100", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@101", "server_ip", "$@102",
  "server_port", "sender_ip", "$@103", "sender_port", "max_queue_size",
  "ncr_protocol", "$@104", "ncr_protocol_value", "ncr_format", "$@105",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@106", "replace_client_name_value",
  "generated_prefix", "$@107", "hostname_char_set", "$@108",
  "hostname_char_replacement", "$@109", "dhcp6_json_object", "$@110",
  "dhcpddns_json_object", "$@111", "control_agent_json_object", "$@112",
  "logging_object", "$@113", "sub_logging", "$@114", "logging_params",
  "logging_param", "loggers", "$@115", "loggers_entries", "logger_entry",
  "$@116", "logger_params", "logger_param", "debuglevel", "severity",
  "$@117", "output_options_list", "$@118", "output_options_list_content",
  "output_entry", "$@119", "output_params_list", "output_params", "output",
  "$@120", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   250,   250,   250,   251,   251,   252,   252,   253,   253,
     254,   254,   255,   255,   256,   256,   257,   257,   258,   258,
     259,   259,   260,   260,   261,   261,   262,   262,   270,   271,
     272,   273,   274,   275,   276,   279,   284,   284,   295,   298,
     299,   302,   306,   313,   313,   320,   321,   324,   328,   335,
     335,   342,   343,   346,   350,   361,   371,   371,   387,   388,
     392,   393,   394,   395,   396,   397,   400,   400,   415,   415,
     424,   425,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   461,   466,   471,   476,   481,   486,   492,   492,   503,
     504,   507,   508,   509,   510,   511,   512,   513,   516,   516,
     525,   525,   535,   535,   542,   543,   546,   546,   553,   555,
     559,   565,   565,   577,   577,   587,   588,   590,   592,   592,
     610,   610,   622,   622,   632,   633,   636,   637,   640,   640,
     650,   651,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     674,   674,   681,   682,   683,   684,   687,   687,   695,   695,
     703,   703,   711,   716,   716,   724,   729,   734,   739,   744,
     749,   754,   759,   759,   767,   767,   775,   780,   785,   785,
     795,   796,   799,   800,   801,   802,   803,   806,   811,   816,
     821,   826,   831,   831,   841,   842,   845,   846,   849,   849,
     859,   859,   869,   870,   871,   874,   875,   878,   878,   886,
     886,   894,   894,   905,   906,   909,   910,   911,   912,   913,
     914,   917,   922,   927,   932,   937,   942,   950,   950,   963,
     964,   967,   968,   975,   975,  1001,  1001,  1012,  1013,  1017,
    1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1044,  1044,  1052,  1052,  1060,  1060,
    1068,  1068,  1076,  1076,  1084,  1084,  1092,  1092,  1100,  1100,
    1110,  1110,  1117,  1118,  1119,  1120,  1123,  1128,  1135,  1135,
    1146,  1147,  1151,  1152,  1155,  1155,  1163,  1164,  1167,  1168,
    1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,
    1179,  1180,  1181,  1182,  1183,  1184,  1191,  1191,  1204,  1204,
    1213,  1214,  1217,  1218,  1223,  1223,  1238,  1238,  1252,  1253,
    1256,  1257,  1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,
    1268,  1269,  1272,  1274,  1279,  1281,  1281,  1289,  1289,  1297,
    1297,  1305,  1307,  1307,  1315,  1324,  1324,  1336,  1337,  1342,
    1343,  1348,  1348,  1360,  1360,  1372,  1373,  1378,  1379,  1384,
    1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,  1395,  1397,
    1397,  1405,  1407,  1409,  1414,  1422,  1422,  1434,  1435,  1438,
    1439,  1442,  1442,  1452,  1452,  1462,  1463,  1466,  1467,  1468,
    1469,  1470,  1471,  1472,  1475,  1475,  1483,  1483,  1508,  1508,
    1538,  1538,  1548,  1549,  1552,  1553,  1556,  1556,  1565,  1565,
    1574,  1575,  1578,  1579,  1583,  1584,  1585,  1586,  1587,  1588,
    1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1600,
    1600,  1608,  1608,  1616,  1616,  1624,  1624,  1632,  1632,  1642,
    1642,  1650,  1650,  1658,  1658,  1666,  1666,  1674,  1674,  1682,
    1682,  1690,  1690,  1703,  1703,  1713,  1714,  1720,  1720,  1730,
    1731,  1734,  1734,  1744,  1745,  1748,  1749,  1752,  1753,  1754,
    1755,  1756,  1757,  1758,  1759,  1760,  1761,  1762,  1765,  1767,
    1767,  1775,  1784,  1791,  1791,  1801,  1802,  1805,  1806,  1807,
    1808,  1809,  1812,  1812,  1820,  1820,  1830,  1830,  1842,  1842,
    1852,  1853,  1856,  1857,  1858,  1859,  1860,  1861,  1862,  1863,
    1864,  1865,  1866,  1867,  1868,  1869,  1870,  1871,  1872,  1873,
    1874,  1877,  1882,  1882,  1890,  1890,  1898,  1903,  1903,  1911,
    1916,  1921,  1921,  1929,  1930,  1933,  1933,  1941,  1946,  1951,
    1956,  1956,  1964,  1967,  1970,  1973,  1976,  1982,  1982,  1990,
    1990,  1998,  1998,  2009,  2009,  2016,  2016,  2023,  2023,  2035,
    2035,  2045,  2045,  2056,  2057,  2061,  2065,  2065,  2077,  2078,
    2082,  2082,  2090,  2091,  2094,  2095,  2096,  2097,  2098,  2099,
    2100,  2103,  2108,  2108,  2116,  2116,  2126,  2127,  2130,  2130,
    2138,  2139,  2142,  2143,  2144,  2145,  2148,  2148,  2156,  2161,
    2166
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
#line 4770 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2171 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
