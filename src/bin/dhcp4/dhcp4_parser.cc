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
      case 164: // value
      case 168: // map_value
      case 206: // socket_type
      case 209: // outbound_interface_value
      case 219: // db_type
      case 296: // hr_mode
      case 440: // ncr_protocol_value
      case 448: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 149: // "boolean"
        value.move< bool > (that.value);
        break;

      case 148: // "floating point"
        value.move< double > (that.value);
        break;

      case 147: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 146: // "constant string"
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
      case 164: // value
      case 168: // map_value
      case 206: // socket_type
      case 209: // outbound_interface_value
      case 219: // db_type
      case 296: // hr_mode
      case 440: // ncr_protocol_value
      case 448: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 149: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 148: // "floating point"
        value.copy< double > (that.value);
        break;

      case 147: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 146: // "constant string"
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
            case 146: // "constant string"

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 147: // "integer"

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 148: // "floating point"

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 149: // "boolean"

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 164: // value

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // map_value

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 206: // socket_type

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 209: // outbound_interface_value

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 219: // db_type

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 296: // hr_mode

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 440: // ncr_protocol_value

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 448: // replace_client_name_value

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 164: // value
      case 168: // map_value
      case 206: // socket_type
      case 209: // outbound_interface_value
      case 219: // db_type
      case 296: // hr_mode
      case 440: // ncr_protocol_value
      case 448: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 149: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 148: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 147: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 146: // "constant string"
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
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 310 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 317 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 801 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 974 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 994 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1006 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1059 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1064 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1091 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1095 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1173 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1218 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1425 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2521 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2936 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1758 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1764 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1770 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3231 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3235 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -694;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     234,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,    11,    22,    72,    80,    84,   102,   106,
     119,   176,   180,   187,   205,   222,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
      22,  -109,    -8,    31,    91,   131,    38,   138,    -5,   213,
     150,   -56,   243,  -694,    65,    96,   153,   237,   246,  -694,
    -694,  -694,  -694,  -694,   272,  -694,    35,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   279,   281,  -694,  -694,  -694,  -694,
    -694,   282,   283,   284,   285,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,   286,  -694,  -694,  -694,    36,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   287,    64,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
     288,   289,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,    92,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   108,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   291,
     294,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,   292,  -694,  -694,   290,  -694,  -694,  -694,
     297,  -694,  -694,   295,   299,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,   300,   301,  -694,  -694,
    -694,  -694,   303,   305,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   155,  -694,  -694,  -694,   309,  -694,
    -694,   312,  -694,   314,   316,  -694,  -694,   319,   321,   326,
    -694,  -694,  -694,   156,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
      22,    22,  -694,   185,   330,   331,   332,   333,   335,  -694,
      -8,  -694,   337,   211,   212,   358,   359,   360,   376,   377,
     235,   236,   238,   239,   380,   383,   384,   386,   387,   388,
     389,   390,   249,   391,   393,    31,  -694,   394,   395,   396,
     253,    91,  -694,   397,   399,   400,   401,   402,   403,   404,
     405,   263,   262,   408,   409,   410,   411,   131,  -694,   412,
      38,  -694,   413,   414,   415,   416,   417,   418,   419,   420,
    -694,   138,  -694,   421,   422,   280,   424,   425,   426,   296,
    -694,   213,   427,   298,   302,  -694,   150,   428,   429,    51,
    -694,   304,   430,   431,   293,   432,   308,   310,   434,   435,
     307,   313,   315,   437,   440,   243,  -694,  -694,  -694,   442,
     441,   445,    22,    22,    22,  -694,   451,  -694,  -694,   317,
     320,   322,   452,   454,  -694,  -694,  -694,  -694,   460,   462,
     464,   465,   466,   467,   468,   469,  -694,   470,   471,  -694,
     474,   136,   148,  -694,  -694,   328,   329,   334,   476,   475,
     338,   339,   340,  -694,  -694,   209,   341,   478,   481,  -694,
     343,  -694,   474,   344,   345,   346,   347,   348,   349,   350,
    -694,   351,   352,  -694,   353,   354,   355,  -694,  -694,   356,
    -694,  -694,  -694,   357,    22,  -694,  -694,   361,   362,  -694,
     363,  -694,  -694,    15,   398,  -694,  -694,  -694,   -71,   364,
    -694,    22,    31,   381,  -694,  -694,  -694,    91,  -694,  -694,
    -694,   198,   198,   498,   499,   504,   505,   162,   506,   507,
      52,   179,   243,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   509,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   510,   433,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   164,
    -694,   173,  -694,  -694,   182,  -694,  -694,  -694,  -694,   514,
     516,   517,   518,   519,  -694,  -694,  -694,   183,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,   207,  -694,   520,   521,  -694,  -694,   522,   524,  -694,
    -694,   523,   527,  -694,  -694,   525,   529,  -694,  -694,  -694,
    -694,  -694,  -694,    77,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,   114,  -694,  -694,   528,   530,  -694,   531,   532,   533,
     534,   535,   536,   244,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,   248,  -694,  -694,  -694,   252,   379,  -694,
     537,   538,  -694,  -694,   539,   541,  -694,  -694,   540,  -694,
     542,   381,  -694,  -694,   543,   545,   546,   547,   406,   407,
     423,   436,   439,   548,   550,   198,  -694,  -694,   131,  -694,
     498,   213,  -694,   499,   150,  -694,   504,    42,  -694,   505,
     162,  -694,    46,   506,  -694,   -56,  -694,   507,   443,   444,
     446,   447,   448,   449,    52,  -694,   551,   553,   179,  -694,
    -694,  -694,   552,   556,    38,  -694,   509,   138,  -694,   510,
     557,  -694,   555,  -694,    30,   438,   453,   455,  -694,  -694,
    -694,  -694,  -694,   456,   457,  -694,   254,  -694,   554,  -694,
     558,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,   255,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   559,
     560,  -694,  -694,  -694,  -694,   256,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   458,   459,  -694,  -694,   461,   258,
    -694,   561,  -694,   463,   564,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,    42,  -694,
     568,  -694,    46,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,   127,  -694,  -694,   472,  -694,    10,   564,  -694,  -694,
    -694,   569,  -694,  -694,  -694,   266,  -694,  -694,  -694,  -694,
    -694,   570,   450,   571,    10,  -694,   563,  -694,   473,  -694,
     572,  -694,  -694,   208,  -694,    98,   572,  -694,  -694,   573,
     574,   576,   267,  -694,  -694,  -694,  -694,  -694,  -694,   577,
     479,   477,   480,    98,  -694,   483,  -694,  -694,  -694,  -694,
    -694
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   108,     9,   220,    11,   366,    13,   387,    15,
     295,    17,   303,    19,   338,    21,   185,    23,   466,    25,
      43,    37,     0,     0,     0,     0,     0,   389,     0,   305,
     340,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     519,   513,   515,   517,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   100,     0,     0,   406,   408,   410,   121,
     123,     0,     0,     0,     0,   212,   293,   330,   268,   163,
     432,   177,   196,     0,   454,   464,    93,     0,    68,    70,
      71,    72,    73,    88,    89,    76,    77,    78,    79,    83,
      84,    74,    75,    81,    82,    90,    91,    92,    80,    85,
      86,    87,   110,   112,   116,     0,     0,   102,   104,   105,
     106,   107,   249,   251,   253,   358,   377,   247,   255,   257,
       0,     0,   261,   259,   379,   428,   246,   224,   225,   226,
     238,     0,   222,   229,   242,   243,   244,   230,   231,   234,
     236,   232,   233,   227,   228,   245,   235,   239,   240,   241,
     237,   375,   374,   372,   371,     0,   368,   370,   373,   426,
     414,   416,   420,   418,   424,   422,   412,   405,   401,     0,
     390,   391,   402,   403,   404,   398,   393,   399,   395,   396,
     397,   400,   394,     0,   320,   153,     0,   324,   322,   327,
       0,   316,   317,     0,   306,   307,   309,   319,   310,   311,
     312,   326,   313,   314,   315,   352,     0,     0,   350,   351,
     354,   355,     0,   341,   342,   344,   345,   346,   347,   348,
     349,   192,   194,   189,     0,   187,   190,   191,     0,   486,
     488,     0,   491,     0,     0,   495,   499,     0,     0,     0,
     504,   511,   484,     0,   468,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,    42,
       0,     0,    35,     0,     0,     0,     0,     0,     0,    53,
       0,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,     0,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   221,     0,
       0,   367,     0,     0,     0,     0,     0,     0,     0,     0,
     388,     0,   296,     0,     0,     0,     0,     0,     0,     0,
     304,     0,     0,     0,     0,   339,     0,     0,     0,     0,
     186,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   467,    46,    39,     0,
       0,     0,     0,     0,     0,    57,     0,    98,    99,     0,
       0,     0,     0,     0,    94,    95,    96,    97,     0,     0,
       0,     0,     0,     0,     0,     0,   453,     0,     0,    69,
       0,     0,     0,   120,   103,     0,     0,     0,     0,     0,
       0,     0,     0,   266,   267,     0,     0,     0,     0,   223,
       0,   369,     0,     0,     0,     0,     0,     0,     0,     0,
     392,     0,     0,   318,     0,     0,     0,   329,   308,     0,
     356,   357,   343,     0,     0,   188,   485,     0,     0,   490,
       0,   493,   494,     0,     0,   501,   502,   503,     0,     0,
     469,     0,     0,     0,   514,   516,   518,     0,   407,   409,
     411,     0,     0,   214,   297,   332,   270,     0,     0,   179,
       0,     0,     0,    47,   111,   114,   115,   113,   118,   119,
     117,   250,   252,   254,   360,    36,   378,   248,   256,   258,
     263,   264,   265,   262,   260,   381,     0,   376,   427,   415,
     417,   421,   419,   425,   423,   413,   321,   154,   325,   323,
     328,   353,   193,   195,   487,   489,   492,   497,   498,   496,
     500,   506,   507,   508,   509,   510,   505,   512,    40,     0,
     524,     0,   521,   523,     0,   140,   146,   148,   150,     0,
       0,     0,     0,     0,   159,   161,   139,     0,   125,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,     0,   218,     0,   215,   216,   301,     0,   298,   299,
     336,     0,   333,   334,   274,     0,   271,   272,   172,   173,
     174,   175,   176,     0,   165,   167,   168,   169,   170,   171,
     436,     0,   434,   183,     0,   180,   181,     0,     0,     0,
       0,     0,     0,     0,   198,   200,   201,   202,   203,   204,
     205,   460,   462,     0,   456,   458,   459,     0,    49,   364,
       0,   361,   362,   385,     0,   382,   383,   430,     0,    65,
       0,     0,   520,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   122,   124,     0,   213,
       0,   305,   294,     0,   340,   331,     0,     0,   269,     0,
       0,   164,   438,     0,   433,     0,   178,     0,     0,     0,
       0,     0,     0,     0,     0,   197,     0,     0,     0,   455,
     465,    51,     0,    50,     0,   359,     0,   389,   380,     0,
       0,   429,     0,   522,     0,     0,     0,     0,   152,   155,
     156,   157,   158,     0,     0,   126,     0,   217,     0,   300,
       0,   335,   292,   291,   281,   282,   284,   278,   279,   280,
     290,   289,     0,   276,   283,   285,   286,   287,   288,   273,
     166,   451,   449,   450,   444,   445,   446,   447,   448,     0,
     439,   440,   442,   443,   435,     0,   182,   206,   207,   208,
     209,   210,   211,   199,     0,     0,   457,    48,     0,     0,
     363,     0,   384,     0,     0,   142,   143,   144,   145,   141,
     147,   149,   151,   160,   162,   219,   302,   337,     0,   275,
       0,   437,     0,   184,   461,   463,    52,   365,   386,   431,
     528,     0,   526,   277,     0,   441,     0,     0,   525,   452,
     540,     0,   538,   536,   532,     0,   530,   534,   535,   533,
     527,     0,     0,     0,     0,   529,     0,   537,     0,   531,
       0,   539,   544,     0,   542,     0,     0,   541,   552,     0,
       0,     0,     0,   546,   548,   549,   550,   551,   543,     0,
       0,     0,     0,     0,   545,     0,   554,   555,   556,   547,
     553
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   -47,  -694,    93,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   103,  -694,  -694,  -694,   -62,
    -694,  -694,  -694,   273,  -694,  -694,  -694,  -694,    62,   241,
     -30,   -25,   -24,  -694,  -694,   -19,  -694,  -694,    75,   247,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,    86,  -108,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,   -69,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -121,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -125,  -694,  -694,  -694,  -115,   217,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -116,  -694,  -694,  -694,  -694,  -694,  -694,
    -693,  -694,  -694,  -694,   -90,  -694,  -694,  -694,   -87,   257,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -687,  -694,
    -694,  -694,   -48,  -694,  -686,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,   -97,  -694,  -694,  -215,   -49,  -694,  -694,
    -694,  -694,  -694,   -88,  -694,  -694,  -694,   -85,  -694,   240,
    -694,   -64,  -694,  -694,  -694,  -694,  -694,   -44,  -694,  -694,
    -694,  -694,  -694,   -50,  -694,  -694,  -694,   -89,  -694,  -694,
    -694,   -84,  -694,   245,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -114,  -694,  -694,  -694,  -111,
     265,  -694,  -694,   -54,  -694,  -694,  -694,  -694,  -694,  -107,
    -694,  -694,  -694,  -103,  -694,   259,   -43,  -694,   -42,  -694,
     -31,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -679,  -694,
    -694,  -694,  -694,  -694,  -694,   -76,  -694,  -694,  -694,  -191,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,   -82,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,   122,   242,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
     -32,  -694,  -694,  -694,  -196,  -694,  -694,  -212,  -694,  -694,
    -694,  -694,  -694,  -694,  -222,  -694,  -694,  -235,  -694,  -694,
    -694,  -694,  -694
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   536,    77,
      78,    37,    60,    74,    75,   524,   668,   732,   733,   116,
      39,    62,    86,    87,    88,   304,    41,    63,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   312,   146,   147,
      43,    64,   148,   337,   149,   338,   527,   150,   339,   530,
     151,   126,   318,   127,   319,   597,   598,   599,   684,   819,
     600,   685,   601,   686,   602,   687,   603,   232,   374,   605,
     606,   607,   608,   609,   693,   610,   694,   128,   328,   633,
     634,   635,   636,   637,   638,   639,   129,   330,   644,   645,
     646,   715,    57,    71,   264,   265,   266,   387,   267,   388,
     130,   331,   653,   654,   655,   656,   657,   658,   659,   660,
     131,   324,   613,   614,   615,   698,    45,    65,   171,   172,
     173,   348,   174,   343,   175,   344,   176,   345,   177,   349,
     178,   350,   179,   354,   180,   353,   543,   181,   182,   132,
     327,   625,   626,   627,   707,   772,   773,   133,   325,    51,
      68,   617,   618,   619,   701,    53,    69,   233,   234,   235,
     236,   237,   238,   239,   373,   240,   377,   241,   376,   242,
     243,   378,   244,   134,   326,   621,   622,   623,   704,    55,
      70,   252,   253,   254,   255,   256,   382,   257,   258,   259,
     260,   184,   346,   670,   671,   672,   734,    47,    66,   195,
     196,   197,   359,   185,   347,   186,   355,   674,   675,   676,
     737,    49,    67,   209,   210,   211,   135,   315,   136,   316,
     137,   317,   215,   369,   216,   363,   217,   364,   218,   366,
     219,   365,   220,   368,   221,   367,   222,   362,   190,   356,
     678,   740,   138,   329,   641,   642,   712,   789,   790,   791,
     792,   793,   830,   139,   140,   333,   663,   664,   665,   726,
     666,   727,   141,   334,    59,    72,   283,   284,   285,   286,
     392,   287,   393,   288,   289,   395,   290,   291,   292,   398,
     569,   293,   399,   294,   295,   296,   297,   403,   576,   298,
     404,    89,   306,    90,   307,    91,   308,    92,   305,   581,
     582,   583,   680,   841,   842,   846,   855,   856,   857,   858,
     863,   859,   861,   873,   874,   875,   882,   883,   884,   889,
     885,   886,   887
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   249,    79,   166,   192,   207,   250,   231,   248,   263,
     282,    26,   198,    73,   768,   183,   194,   208,   193,   223,
     769,   771,   187,   188,   212,   213,   251,    27,   778,    28,
     567,    29,   261,   262,   189,   167,   214,    76,   310,   335,
     168,   169,    93,   311,   336,   106,   170,   571,   572,   573,
     574,    94,    95,    96,    97,    98,    99,   100,   815,   816,
     817,   818,   225,    95,    96,    97,    98,   341,    96,    97,
      98,   299,   342,   101,   102,   103,   104,   105,   575,    38,
     710,   106,   107,   711,   101,   102,   103,    40,   105,   107,
      84,    42,   108,   107,   225,   357,   106,   107,   225,   300,
     358,   191,   156,   142,   143,   109,   110,   144,   158,    44,
     145,   360,   162,    46,    80,   163,   361,   713,   111,   163,
     714,   112,   781,    81,    82,    83,    48,   165,   113,   114,
     847,   568,   115,   848,   850,   768,   851,   852,    84,   261,
     262,   769,   771,   647,   648,   649,   650,   651,   652,   778,
     525,   526,    95,    96,    97,    98,    84,   301,   389,   405,
      96,    97,    98,   390,   406,   528,   529,   335,    30,    31,
      32,    33,   679,   101,   102,   103,   681,    84,   152,   153,
     154,   682,   107,    50,    84,   341,   695,    52,    84,   107,
     683,   696,    84,   155,    54,   156,   157,   158,   159,   160,
     161,   162,   225,   245,   226,   227,   246,   247,   163,   164,
     695,   876,    56,   199,   877,   697,   165,   200,   201,   202,
     203,   204,   205,   878,   206,   585,   879,   880,   881,    58,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     224,   628,   629,   630,   631,   302,   632,   724,    85,   303,
     225,   728,   725,   407,   408,   405,   729,   357,   828,   389,
     730,   360,   825,   829,   833,   225,   837,   226,   227,   864,
     893,   228,   229,   230,   865,   894,   309,    84,   661,   662,
     540,   541,   542,   313,    84,   314,   320,   321,   322,   323,
     332,   340,   351,   352,   375,   166,    84,   371,   192,   370,
     372,   379,   381,   380,   383,   384,   198,   183,   386,   207,
     194,   385,   193,   391,   187,   188,   394,   249,   396,   231,
     397,   208,   250,   400,   248,   401,   189,   167,   212,   213,
     402,   409,   168,   169,   410,   411,   412,   413,   170,   414,
     214,   416,   251,   282,    84,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,    84,
     417,   418,   419,   420,   421,   504,   505,   506,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
     422,   423,   424,   425,   428,   426,   427,   429,   430,    84,
     431,   432,   433,   434,   435,   437,   436,   438,   440,   441,
     442,   445,   443,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   460,   462,   463,   464,
     465,   466,   467,   468,   469,   471,   472,   473,   474,   475,
     476,   479,   483,   484,   487,   488,   490,   563,   493,   494,
     489,   498,   604,   604,   499,   477,   501,   480,   502,   596,
     596,   481,   503,   486,   578,   491,   495,   492,   507,   511,
     282,   512,   496,   508,   497,   513,   509,   514,   510,   515,
     516,   517,   518,   519,   531,   532,   520,   521,   522,   523,
     533,   534,    28,   545,   537,   538,   539,   544,   546,   547,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   580,   612,   616,   564,   565,   566,
     577,   620,   624,   640,   643,   570,   669,   673,   688,   677,
     689,   690,   691,   692,   700,   731,   699,   703,   702,   705,
     706,   708,   709,   717,   716,   718,   719,   720,   721,   722,
     723,   736,   535,   735,   739,   738,   742,   744,   741,   745,
     746,   747,   753,   748,   754,   804,   749,   805,   807,   808,
     814,   813,   826,   832,   579,   548,   827,   831,   870,   838,
     750,   840,   844,   862,   866,   868,   439,   890,   891,   872,
     892,   895,   584,   415,   820,   751,   752,   755,   444,   780,
     797,   798,   796,   799,   800,   801,   802,   867,   611,   821,
     795,   822,   823,   824,   834,   835,   485,   836,   803,   839,
     757,   756,   779,   843,   459,   759,   758,   761,   849,   871,
     760,   478,   810,   809,   897,   461,   604,   898,   896,   900,
     470,   482,   812,   596,   811,   249,   166,   794,   767,   231,
     250,   845,   248,   783,   667,   762,   806,   500,   183,   743,
     782,   860,   869,   263,   888,   187,   188,   774,   899,   770,
     251,     0,   785,   784,   775,   776,     0,   189,   167,   786,
     787,     0,   192,   168,   169,   207,   777,   763,     0,   170,
     198,   788,   764,   765,   194,     0,   193,   208,   766,     0,
       0,     0,     0,     0,   212,   213,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   214,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   767,
       0,     0,     0,   783,     0,     0,   762,     0,     0,     0,
     782,     0,     0,     0,     0,     0,     0,   854,   774,     0,
     770,     0,   785,   784,   853,   775,   776,     0,     0,   786,
     787,     0,     0,     0,     0,   854,     0,   777,   763,     0,
       0,   788,   853,   764,   765,     0,     0,     0,     0,   766
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    10,    65,    66,    67,    70,    69,    70,    71,
      72,     0,    66,    60,   707,    65,    66,    67,    66,    68,
     707,   707,    65,    65,    67,    67,    70,     5,   707,     7,
      15,     9,    88,    89,    65,    65,    67,   146,     3,     3,
      65,    65,    11,     8,     8,    50,    65,   118,   119,   120,
     121,    20,    21,    22,    23,    24,    25,    26,    28,    29,
      30,    31,    52,    21,    22,    23,    24,     3,    22,    23,
      24,     6,     8,    42,    43,    44,    45,    46,   149,     7,
       3,    50,    51,     6,    42,    43,    44,     7,    46,    51,
     146,     7,    61,    51,    52,     3,    50,    51,    52,     3,
       8,    63,    64,    12,    13,    74,    75,    16,    66,     7,
      19,     3,    70,     7,   122,    77,     8,     3,    87,    77,
       6,    90,    76,   131,   132,   133,     7,    85,    97,    98,
       3,   116,   101,     6,   124,   828,   126,   127,   146,    88,
      89,   828,   828,    91,    92,    93,    94,    95,    96,   828,
      14,    15,    21,    22,    23,    24,   146,     4,     3,     3,
      22,    23,    24,     8,     8,    17,    18,     3,   146,   147,
     148,   149,     8,    42,    43,    44,     3,   146,    47,    48,
      49,     8,    51,     7,   146,     3,     3,     7,   146,    51,
       8,     8,   146,    62,     7,    64,    65,    66,    67,    68,
      69,    70,    52,    53,    54,    55,    56,    57,    77,    78,
       3,     3,     7,    75,     6,     8,    85,    79,    80,    81,
      82,    83,    84,   125,    86,    27,   128,   129,   130,     7,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      27,    79,    80,    81,    82,     8,    84,     3,   310,     3,
      52,     3,     8,   300,   301,     3,     8,     3,     3,     3,
       8,     3,     8,     8,     8,    52,     8,    54,    55,     3,
       3,    58,    59,    60,     8,     8,     4,   146,    99,   100,
      71,    72,    73,     4,   146,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   357,   146,     3,   360,     8,
       8,     4,     3,     8,     4,     4,   360,   357,     3,   371,
     360,     8,   360,     4,   357,   357,     4,   386,     4,   381,
       4,   371,   386,     4,   386,     4,   357,   357,   371,   371,
       4,   146,   357,   357,     4,     4,     4,     4,   357,     4,
     371,     4,   386,   405,   146,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   146,
     149,   149,     4,     4,     4,   412,   413,   414,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
       4,     4,   147,   147,     4,   147,   147,     4,     4,   146,
       4,     4,     4,     4,     4,     4,   147,     4,     4,     4,
       4,     4,   149,     4,     4,     4,     4,     4,     4,     4,
     147,   149,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   147,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   484,     4,     4,
     147,     4,   511,   512,     4,   149,     4,   149,     7,   511,
     512,   149,     7,   149,   501,   147,   149,   147,     7,     7,
     522,     7,   149,   146,   149,     5,   146,     5,   146,     5,
       5,     5,     5,     5,   146,   146,     7,     7,     7,     5,
     146,     5,     7,     5,   146,   146,   146,   146,     7,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   123,     7,     7,   146,   146,   146,
     146,     7,     7,     7,     7,   117,     7,     7,     4,    86,
       4,     4,     4,     4,     3,   146,     6,     3,     6,     6,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,     3,   449,     6,     3,     6,     4,     4,     8,     4,
       4,     4,     4,   147,     4,     4,   149,     4,     6,     3,
       5,     4,     8,     3,   502,   462,     8,     8,     5,     8,
     147,     7,     4,     4,     4,     4,   335,     4,     4,     7,
       4,     4,   507,   310,   146,   149,   147,   695,   341,   710,
     147,   147,   717,   147,   147,   147,   147,   147,   512,   146,
     715,   146,   146,   146,   146,   146,   389,   146,   724,   146,
     700,   698,   709,   828,   357,   703,   701,   706,   146,   146,
     704,   381,   736,   734,   147,   360,   695,   147,   149,   146,
     371,   386,   739,   695,   737,   704,   698,   713,   707,   701,
     704,   832,   704,   712,   522,   707,   728,   405,   698,   681,
     712,   847,   864,   715,   876,   698,   698,   707,   893,   707,
     704,    -1,   712,   712,   707,   707,    -1,   698,   698,   712,
     712,    -1,   734,   698,   698,   737,   707,   707,    -1,   698,
     734,   712,   707,   707,   734,    -1,   734,   737,   707,    -1,
      -1,    -1,    -1,    -1,   737,   737,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   737,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   828,
      -1,    -1,    -1,   832,    -1,    -1,   828,    -1,    -1,    -1,
     832,    -1,    -1,    -1,    -1,    -1,    -1,   846,   828,    -1,
     828,    -1,   832,   832,   846,   828,   828,    -1,    -1,   832,
     832,    -1,    -1,    -1,    -1,   864,    -1,   828,   828,    -1,
      -1,   832,   864,   828,   828,    -1,    -1,    -1,    -1,   828
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,     0,     5,     7,     9,
     146,   147,   148,   149,   164,   165,   166,   171,     7,   180,
       7,   186,     7,   200,     7,   276,     7,   357,     7,   371,
       7,   309,     7,   315,     7,   339,     7,   252,     7,   424,
     172,   167,   181,   187,   201,   277,   358,   372,   310,   316,
     340,   253,   425,   164,   173,   174,   146,   169,   170,    10,
     122,   131,   132,   133,   146,   179,   182,   183,   184,   451,
     453,   455,   457,    11,    20,    21,    22,    23,    24,    25,
      26,    42,    43,    44,    45,    46,    50,    51,    61,    74,
      75,    87,    90,    97,    98,   101,   179,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   211,   213,   237,   246,
     260,   270,   299,   307,   333,   376,   378,   380,   402,   413,
     414,   422,    12,    13,    16,    19,   198,   199,   202,   204,
     207,   210,    47,    48,    49,    62,    64,    65,    66,    67,
      68,    69,    70,    77,    78,    85,   179,   190,   191,   192,
     195,   278,   279,   280,   282,   284,   286,   288,   290,   292,
     294,   297,   298,   333,   351,   363,   365,   376,   378,   380,
     398,    63,   179,   292,   333,   359,   360,   361,   363,    75,
      79,    80,    81,    82,    83,    84,    86,   179,   333,   373,
     374,   375,   376,   378,   380,   382,   384,   386,   388,   390,
     392,   394,   396,   307,    27,    52,    54,    55,    58,    59,
      60,   179,   227,   317,   318,   319,   320,   321,   322,   323,
     325,   327,   329,   330,   332,    53,    56,    57,   179,   227,
     321,   327,   341,   342,   343,   344,   345,   347,   348,   349,
     350,    88,    89,   179,   254,   255,   256,   258,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   179,   426,   427,   428,   429,   431,   433,   434,
     436,   437,   438,   441,   443,   444,   445,   446,   449,     6,
       3,     4,     8,     3,   185,   458,   452,   454,   456,     4,
       3,     8,   197,     4,     4,   377,   379,   381,   212,   214,
       4,     4,     4,     4,   271,   308,   334,   300,   238,   403,
     247,   261,     4,   415,   423,     3,     8,   203,   205,   208,
       4,     3,     8,   283,   285,   287,   352,   364,   281,   289,
     291,     4,     4,   295,   293,   366,   399,     3,     8,   362,
       3,     8,   397,   385,   387,   391,   389,   395,   393,   383,
       8,     3,     8,   324,   228,     4,   328,   326,   331,     4,
       8,     3,   346,     4,     4,     8,     3,   257,   259,     3,
       8,     4,   430,   432,     4,   435,     4,     4,   439,   442,
       4,     4,     4,   447,   450,     3,     8,   164,   164,   146,
       4,     4,     4,     4,     4,   183,     4,   149,   149,     4,
       4,     4,     4,     4,   147,   147,   147,   147,     4,     4,
       4,     4,     4,     4,     4,     4,   147,     4,     4,   189,
       4,     4,     4,   149,   199,     4,     4,     4,     4,     4,
       4,     4,     4,   147,   149,     4,     4,     4,     4,   279,
       4,   360,     4,     4,     4,     4,     4,     4,     4,     4,
     375,     4,     4,   147,     4,     4,     4,   149,   319,     4,
     149,   149,   343,     4,     4,   255,   149,     4,     4,   147,
       4,   147,   147,     4,     4,   149,   149,   149,     4,     4,
     427,     4,     7,     7,   164,   164,   164,     7,   146,   146,
     146,     7,     7,     5,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     5,   175,    14,    15,   206,    17,    18,
     209,   146,   146,   146,     5,   166,   168,   146,   146,   146,
      71,    72,    73,   296,   146,     5,     7,   146,   175,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   164,   146,   146,   146,    15,   116,   440,
     117,   118,   119,   120,   121,   149,   448,   146,   164,   188,
     123,   459,   460,   461,   198,    27,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,   179,   215,   216,   217,
     220,   222,   224,   226,   227,   229,   230,   231,   232,   233,
     235,   215,     7,   272,   273,   274,     7,   311,   312,   313,
       7,   335,   336,   337,     7,   301,   302,   303,    79,    80,
      81,    82,    84,   239,   240,   241,   242,   243,   244,   245,
       7,   404,   405,     7,   248,   249,   250,    91,    92,    93,
      94,    95,    96,   262,   263,   264,   265,   266,   267,   268,
     269,    99,   100,   416,   417,   418,   420,   426,   176,     7,
     353,   354,   355,     7,   367,   368,   369,    86,   400,     8,
     462,     3,     8,     8,   218,   221,   223,   225,     4,     4,
       4,     4,     4,   234,   236,     3,     8,     8,   275,     6,
       3,   314,     6,     3,   338,     6,     3,   304,     6,     3,
       3,     6,   406,     3,     6,   251,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   419,   421,     3,     8,
       8,   146,   177,   178,   356,     6,     3,   370,     6,     3,
     401,     8,     4,   460,     4,     4,     4,     4,   147,   149,
     147,   149,   147,     4,     4,   216,   278,   274,   317,   313,
     341,   337,   179,   190,   191,   192,   195,   227,   270,   288,
     292,   294,   305,   306,   333,   376,   378,   380,   398,   303,
     240,    76,   179,   227,   307,   333,   376,   378,   380,   407,
     408,   409,   410,   411,   405,   254,   250,   147,   147,   147,
     147,   147,   147,   263,     4,     4,   417,     6,     3,   359,
     355,   373,   369,     4,     5,    28,    29,    30,    31,   219,
     146,   146,   146,   146,   146,     8,     8,     8,     3,     8,
     412,     8,     3,     8,   146,   146,   146,     8,     8,   146,
       7,   463,   464,   306,     4,   409,   465,     3,     6,   146,
     124,   126,   127,   179,   227,   466,   467,   468,   469,   471,
     464,   472,     4,   470,     3,     8,     4,   147,     4,   467,
       5,   146,     7,   473,   474,   475,     3,     6,   125,   128,
     129,   130,   476,   477,   478,   480,   481,   482,   474,   479,
       4,     4,     4,     3,     8,     4,   149,   147,   147,   477,
     146
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   150,   152,   151,   153,   151,   154,   151,   155,   151,
     156,   151,   157,   151,   158,   151,   159,   151,   160,   151,
     161,   151,   162,   151,   163,   151,   164,   164,   164,   164,
     164,   164,   164,   165,   167,   166,   168,   169,   169,   170,
     170,   172,   171,   173,   173,   174,   174,   176,   175,   177,
     177,   178,   178,   179,   181,   180,   182,   182,   183,   183,
     183,   183,   183,   183,   185,   184,   187,   186,   188,   188,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   190,   191,   192,   193,   194,   195,
     197,   196,   198,   198,   199,   199,   199,   199,   201,   200,
     203,   202,   205,   204,   206,   206,   208,   207,   209,   209,
     210,   212,   211,   214,   213,   215,   215,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     218,   217,   219,   219,   219,   219,   221,   220,   223,   222,
     225,   224,   226,   228,   227,   229,   230,   231,   232,   234,
     233,   236,   235,   238,   237,   239,   239,   240,   240,   240,
     240,   240,   241,   242,   243,   244,   245,   247,   246,   248,
     248,   249,   249,   251,   250,   253,   252,   254,   254,   254,
     255,   255,   257,   256,   259,   258,   261,   260,   262,   262,
     263,   263,   263,   263,   263,   263,   264,   265,   266,   267,
     268,   269,   271,   270,   272,   272,   273,   273,   275,   274,
     277,   276,   278,   278,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   281,   280,   283,
     282,   285,   284,   287,   286,   289,   288,   291,   290,   293,
     292,   295,   294,   296,   296,   296,   297,   298,   300,   299,
     301,   301,   302,   302,   304,   303,   305,   305,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   308,   307,   310,   309,   311,   311,   312,
     312,   314,   313,   316,   315,   317,   317,   318,   318,   319,
     319,   319,   319,   319,   319,   319,   319,   320,   321,   322,
     324,   323,   326,   325,   328,   327,   329,   331,   330,   332,
     334,   333,   335,   335,   336,   336,   338,   337,   340,   339,
     341,   341,   342,   342,   343,   343,   343,   343,   343,   343,
     343,   344,   346,   345,   347,   348,   349,   350,   352,   351,
     353,   353,   354,   354,   356,   355,   358,   357,   359,   359,
     360,   360,   360,   360,   360,   362,   361,   364,   363,   366,
     365,   367,   367,   368,   368,   370,   369,   372,   371,   373,
     373,   374,   374,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   377,   376,   379,   378,
     381,   380,   383,   382,   385,   384,   387,   386,   389,   388,
     391,   390,   393,   392,   395,   394,   397,   396,   399,   398,
     401,   400,   403,   402,   404,   404,   406,   405,   407,   407,
     408,   408,   409,   409,   409,   409,   409,   409,   409,   409,
     410,   412,   411,   413,   415,   414,   416,   416,   417,   417,
     419,   418,   421,   420,   423,   422,   425,   424,   426,   426,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   428,   430,   429,   432,   431,
     433,   435,   434,   436,   437,   439,   438,   440,   440,   442,
     441,   443,   444,   445,   447,   446,   448,   448,   448,   448,
     448,   450,   449,   452,   451,   454,   453,   456,   455,   458,
     457,   459,   459,   460,   462,   461,   463,   463,   465,   464,
     466,   466,   467,   467,   467,   467,   467,   468,   470,   469,
     472,   471,   473,   473,   475,   474,   476,   476,   477,   477,
     477,   477,   479,   478,   480,   481,   482
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     0,     1,     3,
       5,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     4,
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
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"subnet\"", "\"interface\"", "\"interface-id\"", "\"id\"",
  "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"duid\"", "\"hw-address\"", "\"circuit-id\"", "\"client-id\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "value", "sub_json",
  "map2", "$@13", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@14", "list_content", "not_empty_list", "list_strings",
  "$@15", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@16", "global_objects",
  "global_object", "dhcp4_object", "$@17", "sub_dhcp4", "$@18",
  "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@19",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@20", "interfaces_list", "$@21", "dhcp_socket_type", "$@22",
  "socket_type", "outbound_interface", "$@23", "outbound_interface_value",
  "re_detect", "lease_database", "$@24", "hosts_database", "$@25",
  "database_map_params", "database_map_param", "database_type", "$@26",
  "db_type", "user", "$@27", "password", "$@28", "host", "$@29", "port",
  "name", "$@30", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@31", "keyspace", "$@32",
  "host_reservation_identifiers", "$@33",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@34", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@35",
  "sub_hooks_library", "$@36", "hooks_params", "hooks_param", "library",
  "$@37", "parameters", "$@38", "expired_leases_processing", "$@39",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@40",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@41",
  "sub_subnet4", "$@42", "subnet4_params", "subnet4_param", "subnet",
  "$@43", "subnet_4o6_interface", "$@44", "subnet_4o6_interface_id",
  "$@45", "subnet_4o6_subnet", "$@46", "interface", "$@47", "interface_id",
  "$@48", "client_class", "$@49", "reservation_mode", "$@50", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@51",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@52", "shared_network_params", "shared_network_param",
  "option_def_list", "$@53", "sub_option_def_list", "$@54",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@55", "sub_option_def", "$@56",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@57",
  "option_def_record_types", "$@58", "space", "$@59", "option_def_space",
  "option_def_encapsulate", "$@60", "option_def_array", "option_data_list",
  "$@61", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@62", "sub_option_data", "$@63",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@64",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@65", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@66", "sub_pool4", "$@67",
  "pool_params", "pool_param", "pool_entry", "$@68", "user_context",
  "$@69", "reservations", "$@70", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@71", "sub_reservation",
  "$@72", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@73", "server_hostname", "$@74",
  "boot_file_name", "$@75", "ip_address", "$@76", "duid", "$@77",
  "hw_address", "$@78", "client_id_value", "$@79", "circuit_id_value",
  "$@80", "flex_id_value", "$@81", "hostname", "$@82",
  "reservation_client_classes", "$@83", "relay", "$@84", "relay_map",
  "$@85", "client_classes", "$@86", "client_classes_list",
  "client_class_entry", "$@87", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@88", "dhcp4o6_port",
  "control_socket", "$@89", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@90",
  "control_socket_name", "$@91", "dhcp_ddns", "$@92", "sub_dhcp_ddns",
  "$@93", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@94", "server_ip", "$@95", "server_port",
  "sender_ip", "$@96", "sender_port", "max_queue_size", "ncr_protocol",
  "$@97", "ncr_protocol_value", "ncr_format", "$@98",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@99", "replace_client_name_value",
  "generated_prefix", "$@100", "dhcp6_json_object", "$@101",
  "dhcpddns_json_object", "$@102", "control_agent_json_object", "$@103",
  "logging_object", "$@104", "logging_params", "logging_param", "loggers",
  "$@105", "loggers_entries", "logger_entry", "$@106", "logger_params",
  "logger_param", "debuglevel", "severity", "$@107", "output_options_list",
  "$@108", "output_options_list_content", "output_entry", "$@109",
  "output_params_list", "output_params", "output", "$@110", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   233,   233,   233,   234,   234,   235,   235,   236,   236,
     237,   237,   238,   238,   239,   239,   240,   240,   241,   241,
     242,   242,   243,   243,   244,   244,   252,   253,   254,   255,
     256,   257,   258,   261,   266,   266,   277,   280,   281,   284,
     288,   295,   295,   302,   303,   306,   310,   317,   317,   324,
     325,   328,   332,   343,   353,   353,   369,   370,   374,   375,
     376,   377,   378,   379,   382,   382,   397,   397,   406,   407,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   438,   443,   448,   453,   458,   463,
     469,   469,   480,   481,   484,   485,   486,   487,   490,   490,
     499,   499,   509,   509,   516,   517,   520,   520,   527,   529,
     533,   539,   539,   551,   551,   563,   564,   567,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   578,   579,
     582,   582,   589,   590,   591,   592,   595,   595,   603,   603,
     611,   611,   619,   624,   624,   632,   637,   642,   647,   652,
     652,   660,   660,   669,   669,   679,   680,   683,   684,   685,
     686,   687,   690,   695,   700,   705,   710,   715,   715,   725,
     726,   729,   730,   733,   733,   743,   743,   753,   754,   755,
     758,   759,   762,   762,   770,   770,   778,   778,   789,   790,
     793,   794,   795,   796,   797,   798,   801,   806,   811,   816,
     821,   826,   834,   834,   847,   848,   851,   852,   859,   859,
     885,   885,   896,   897,   901,   902,   903,   904,   905,   906,
     907,   908,   909,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   926,   926,   934,
     934,   942,   942,   950,   950,   958,   958,   966,   966,   974,
     974,   982,   982,   989,   990,   991,   994,   999,  1006,  1006,
    1017,  1018,  1022,  1023,  1026,  1026,  1034,  1035,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1059,  1059,  1072,  1072,  1081,  1082,  1085,
    1086,  1091,  1091,  1106,  1106,  1120,  1121,  1124,  1125,  1128,
    1129,  1130,  1131,  1132,  1133,  1134,  1135,  1138,  1140,  1145,
    1147,  1147,  1155,  1155,  1163,  1163,  1171,  1173,  1173,  1181,
    1190,  1190,  1202,  1203,  1208,  1209,  1214,  1214,  1226,  1226,
    1238,  1239,  1244,  1245,  1250,  1251,  1252,  1253,  1254,  1255,
    1256,  1259,  1261,  1261,  1269,  1271,  1273,  1278,  1286,  1286,
    1298,  1299,  1302,  1303,  1306,  1306,  1316,  1316,  1326,  1327,
    1330,  1331,  1332,  1333,  1334,  1337,  1337,  1345,  1345,  1355,
    1355,  1365,  1366,  1369,  1370,  1373,  1373,  1382,  1382,  1391,
    1392,  1395,  1396,  1400,  1401,  1402,  1403,  1404,  1405,  1406,
    1407,  1408,  1409,  1410,  1411,  1412,  1415,  1415,  1423,  1423,
    1431,  1431,  1439,  1439,  1447,  1447,  1455,  1455,  1463,  1463,
    1471,  1471,  1479,  1479,  1487,  1487,  1495,  1495,  1508,  1508,
    1518,  1518,  1529,  1529,  1539,  1540,  1543,  1543,  1553,  1554,
    1557,  1558,  1561,  1562,  1563,  1564,  1565,  1566,  1567,  1568,
    1571,  1573,  1573,  1585,  1592,  1592,  1602,  1603,  1606,  1607,
    1610,  1610,  1618,  1618,  1628,  1628,  1640,  1640,  1650,  1651,
    1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,
    1664,  1665,  1666,  1667,  1668,  1671,  1676,  1676,  1684,  1684,
    1692,  1697,  1697,  1705,  1710,  1715,  1715,  1723,  1724,  1727,
    1727,  1735,  1740,  1745,  1750,  1750,  1758,  1761,  1764,  1767,
    1770,  1776,  1776,  1786,  1786,  1793,  1793,  1800,  1800,  1812,
    1812,  1825,  1826,  1830,  1834,  1834,  1846,  1847,  1851,  1851,
    1859,  1860,  1863,  1864,  1865,  1866,  1867,  1870,  1875,  1875,
    1883,  1883,  1893,  1894,  1897,  1897,  1905,  1906,  1909,  1910,
    1911,  1912,  1915,  1915,  1923,  1928,  1933
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
#line 4381 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1938 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
