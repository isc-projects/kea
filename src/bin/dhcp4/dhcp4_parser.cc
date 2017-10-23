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
      case 439: // ncr_protocol_value
      case 447: // replace_client_name_value
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
      case 439: // ncr_protocol_value
      case 447: // replace_client_name_value
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

      case 439: // ncr_protocol_value

#line 224 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 447: // replace_client_name_value

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
      case 439: // ncr_protocol_value
      case 447: // replace_client_name_value
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

  case 374:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2521 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2936 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1801 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -713;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     248,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,    40,    32,    35,    43,    45,    49,    65,
      67,    71,    78,    97,   106,   115,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
      32,   -48,     8,   140,   113,    22,     4,   180,    70,    -1,
     141,   -27,   266,  -713,   161,   196,   202,   224,   230,  -713,
    -713,  -713,  -713,  -713,   252,  -713,    94,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,   253,   271,  -713,  -713,  -713,  -713,
    -713,   284,   285,   286,   287,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,   288,  -713,  -713,  -713,   102,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,   290,   109,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,   291,   293,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,   128,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,   144,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,   228,
     240,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,   238,  -713,  -713,   296,  -713,  -713,  -713,
     298,  -713,  -713,   246,   300,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,   301,   305,  -713,  -713,
    -713,  -713,   261,   309,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,   145,  -713,  -713,  -713,   313,  -713,
    -713,   327,  -713,   328,   329,  -713,  -713,   330,   332,   333,
    -713,  -713,  -713,   184,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
      32,    32,  -713,   158,   334,   335,   336,   339,   341,  -713,
       8,  -713,   342,   170,   208,   354,   355,   356,   357,   358,
     216,   247,   249,   251,   391,   393,   395,   396,   397,   398,
     399,   400,   258,   402,   403,   140,  -713,   404,   405,   406,
     267,   113,  -713,    25,   407,   409,   410,   411,   413,   414,
     415,   416,   274,   273,   419,   420,   421,   422,    22,  -713,
     423,     4,  -713,   424,   425,   426,   427,   428,   429,   430,
     431,  -713,   180,  -713,   432,   433,   292,   434,   436,   437,
     294,  -713,    -1,   438,   295,   297,  -713,   141,   441,   443,
      55,  -713,   299,   446,   447,   306,   448,   307,   308,   454,
     455,   311,   316,   318,   458,   464,   266,  -713,  -713,  -713,
     465,   463,   466,    32,    32,    32,  -713,   468,  -713,  -713,
     325,   326,   331,   469,   472,  -713,  -713,  -713,  -713,   475,
     477,   478,   479,   481,   482,   483,   484,  -713,   485,   486,
    -713,   489,   155,   171,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,   487,   493,  -713,  -713,  -713,   343,
     344,   352,   494,   496,   360,   361,   362,  -713,  -713,   207,
     363,   495,   497,  -713,   365,  -713,   489,   366,   367,   368,
     369,   370,   371,   372,  -713,   373,   374,  -713,   375,   376,
     377,  -713,  -713,   378,  -713,  -713,  -713,   379,    32,  -713,
    -713,   380,   381,  -713,   382,  -713,  -713,    17,   384,  -713,
    -713,  -713,   -38,   383,  -713,    32,   140,   408,  -713,  -713,
    -713,   113,  -713,  -713,  -713,   315,   315,   523,   525,   526,
     527,   129,    26,   528,    81,   126,   266,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,   532,  -713,    25,  -713,  -713,
    -713,   530,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,   531,   453,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,   197,  -713,   214,  -713,
    -713,   220,  -713,  -713,  -713,  -713,   536,   537,   538,   539,
     540,  -713,  -713,  -713,   221,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,   231,  -713,
     541,   542,  -713,  -713,   543,   545,  -713,  -713,   544,   548,
    -713,  -713,   546,   550,  -713,  -713,  -713,  -713,  -713,  -713,
      57,  -713,  -713,  -713,  -713,  -713,  -713,  -713,   131,  -713,
     549,   551,  -713,   552,   553,   554,   555,   556,   557,   232,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,   239,
    -713,  -713,  -713,   241,   417,   418,  -713,  -713,   559,   563,
    -713,  -713,   561,   565,  -713,  -713,   562,  -713,   558,   408,
    -713,  -713,   567,   568,   569,   570,   435,   439,   440,   442,
     445,   571,   572,   315,  -713,  -713,    22,  -713,   523,    -1,
    -713,   525,   141,  -713,   526,    72,  -713,   527,   129,  -713,
      26,  -713,   -27,  -713,   528,   449,   450,   451,   452,   456,
     457,    81,  -713,   573,   574,   126,  -713,  -713,  -713,   575,
     566,  -713,     4,  -713,   530,   180,  -713,   531,   576,  -713,
     578,  -713,   254,   444,   459,   460,  -713,  -713,  -713,  -713,
    -713,   461,   462,  -713,   242,  -713,   577,  -713,   581,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
     250,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
     262,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,   467,
     470,  -713,  -713,   471,   264,  -713,   585,  -713,   473,   579,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,    72,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,   152,  -713,  -713,   -18,   579,  -713,  -713,
     580,  -713,  -713,  -713,   265,  -713,  -713,  -713,  -713,  -713,
     590,   474,   591,   -18,  -713,   595,  -713,   476,  -713,   594,
    -713,  -713,   153,  -713,    91,   594,  -713,  -713,   598,   605,
     606,   268,  -713,  -713,  -713,  -713,  -713,  -713,   607,   480,
     488,   490,    91,  -713,   492,  -713,  -713,  -713,  -713,  -713
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   108,     9,   220,    11,   366,    13,   386,    15,
     295,    17,   303,    19,   338,    21,   185,    23,   465,    25,
      43,    37,     0,     0,     0,     0,     0,   388,     0,   305,
     340,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     518,   512,   514,   516,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   100,     0,     0,   405,   407,   409,   121,
     123,     0,     0,     0,     0,   212,   293,   330,   268,   163,
     431,   177,   196,     0,   453,   463,    93,     0,    68,    70,
      71,    72,    73,    88,    89,    76,    77,    78,    79,    83,
      84,    74,    75,    81,    82,    90,    91,    92,    80,    85,
      86,    87,   110,   112,   116,     0,     0,   102,   104,   105,
     106,   107,   435,   249,   251,   253,   358,   376,   247,   255,
     257,     0,     0,   261,   259,   378,   427,   246,   224,   225,
     226,   238,     0,   222,   229,   242,   243,   244,   230,   231,
     234,   236,   232,   233,   227,   228,   245,   235,   239,   240,
     241,   237,   374,   373,   371,     0,   368,   370,   372,   425,
     413,   415,   419,   417,   423,   421,   411,   404,   400,     0,
     389,   390,   401,   402,   403,   397,   392,   398,   394,   395,
     396,   399,   393,     0,   320,   153,     0,   324,   322,   327,
       0,   316,   317,     0,   306,   307,   309,   319,   310,   311,
     312,   326,   313,   314,   315,   352,     0,     0,   350,   351,
     354,   355,     0,   341,   342,   344,   345,   346,   347,   348,
     349,   192,   194,   189,     0,   187,   190,   191,     0,   485,
     487,     0,   490,     0,     0,   494,   498,     0,     0,     0,
     503,   510,   483,     0,   467,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,    42,
       0,     0,    35,     0,     0,     0,     0,     0,     0,    53,
       0,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,     0,   109,   437,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   221,
       0,     0,   367,     0,     0,     0,     0,     0,     0,     0,
       0,   387,     0,   296,     0,     0,     0,     0,     0,     0,
       0,   304,     0,     0,     0,     0,   339,     0,     0,     0,
       0,   186,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,    46,    39,
       0,     0,     0,     0,     0,     0,    57,     0,    98,    99,
       0,     0,     0,     0,     0,    94,    95,    96,    97,     0,
       0,     0,     0,     0,     0,     0,     0,   452,     0,     0,
      69,     0,     0,     0,   120,   103,   450,   448,   449,   443,
     444,   445,   446,   447,     0,   438,   439,   441,   442,     0,
       0,     0,     0,     0,     0,     0,     0,   266,   267,     0,
       0,     0,     0,   223,     0,   369,     0,     0,     0,     0,
       0,     0,     0,     0,   391,     0,     0,   318,     0,     0,
       0,   329,   308,     0,   356,   357,   343,     0,     0,   188,
     484,     0,     0,   489,     0,   492,   493,     0,     0,   500,
     501,   502,     0,     0,   468,     0,     0,     0,   513,   515,
     517,     0,   406,   408,   410,     0,     0,   214,   297,   332,
     270,     0,     0,   179,     0,     0,     0,    47,   111,   114,
     115,   113,   118,   119,   117,     0,   436,     0,   250,   252,
     254,   360,    36,   377,   248,   256,   258,   263,   264,   265,
     262,   260,   380,     0,   375,   426,   414,   416,   420,   418,
     424,   422,   412,   321,   154,   325,   323,   328,   353,   193,
     195,   486,   488,   491,   496,   497,   495,   499,   505,   506,
     507,   508,   509,   504,   511,    40,     0,   523,     0,   520,
     522,     0,   140,   146,   148,   150,     0,     0,     0,     0,
       0,   159,   161,   139,     0,   125,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,     0,   218,
       0,   215,   216,   301,     0,   298,   299,   336,     0,   333,
     334,   274,     0,   271,   272,   172,   173,   174,   175,   176,
       0,   165,   167,   168,   169,   170,   171,   433,     0,   183,
       0,   180,   181,     0,     0,     0,     0,     0,     0,     0,
     198,   200,   201,   202,   203,   204,   205,   459,   461,     0,
     455,   457,   458,     0,    49,     0,   440,   364,     0,   361,
     362,   384,     0,   381,   382,   429,     0,    65,     0,     0,
     519,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   122,   124,     0,   213,     0,   305,
     294,     0,   340,   331,     0,     0,   269,     0,     0,   164,
       0,   432,     0,   178,     0,     0,     0,     0,     0,     0,
       0,     0,   197,     0,     0,     0,   454,   464,    51,     0,
      50,   451,     0,   359,     0,   388,   379,     0,     0,   428,
       0,   521,     0,     0,     0,     0,   152,   155,   156,   157,
     158,     0,     0,   126,     0,   217,     0,   300,     0,   335,
     292,   291,   281,   282,   284,   278,   279,   280,   290,   289,
       0,   276,   283,   285,   286,   287,   288,   273,   166,   434,
       0,   182,   206,   207,   208,   209,   210,   211,   199,     0,
       0,   456,    48,     0,     0,   363,     0,   383,     0,     0,
     142,   143,   144,   145,   141,   147,   149,   151,   160,   162,
     219,   302,   337,     0,   275,   184,   460,   462,    52,   365,
     385,   430,   527,     0,   525,   277,     0,     0,   524,   539,
       0,   537,   535,   531,     0,   529,   533,   534,   532,   526,
       0,     0,     0,     0,   528,     0,   536,     0,   530,     0,
     538,   543,     0,   541,     0,     0,   540,   551,     0,     0,
       0,     0,   545,   547,   548,   549,   550,   542,     0,     0,
       0,     0,     0,   544,     0,   553,   554,   555,   546,   552
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,   -49,  -713,    83,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,   103,  -713,  -713,  -713,   -62,
    -713,  -713,  -713,   302,  -713,  -713,  -713,  -713,    98,   280,
     -44,   -34,   -30,  -713,  -713,   -29,  -713,  -713,    99,   277,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,   100,   -90,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,   -69,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -104,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -109,  -713,  -713,  -713,  -105,   243,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -113,  -713,  -713,  -713,  -713,  -713,  -713,
    -712,  -713,  -713,  -713,   -88,  -713,  -713,  -713,   -85,   276,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -706,  -713,
    -713,  -713,  -518,  -713,  -698,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,   -95,  -713,  -713,  -197,   -66,  -713,  -713,
    -713,  -713,  -713,   -82,  -713,  -713,  -713,   -79,  -713,   259,
    -713,   -64,  -713,  -713,  -713,  -713,  -713,   -46,  -713,  -713,
    -713,  -713,  -713,   -50,  -713,  -713,  -713,   -81,  -713,  -713,
    -713,   -80,  -713,   260,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -108,  -713,  -713,  -713,  -107,
     289,  -713,  -713,   -54,  -713,  -713,  -713,  -713,  -713,  -102,
    -713,  -713,  -713,  -106,  -713,   312,   -45,  -713,   -42,  -713,
     -37,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -687,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,   101,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,   -93,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,   123,   255,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,
    -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,  -713,   -35,
    -713,  -713,  -713,  -185,  -713,  -713,  -198,  -713,  -713,  -713,
    -713,  -713,  -713,  -208,  -713,  -713,  -224,  -713,  -713,  -713,
    -713,  -713
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   553,    77,
      78,    37,    60,    74,    75,   538,   684,   749,   750,   116,
      39,    62,    86,    87,    88,   304,    41,    63,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   312,   146,   147,
      43,    64,   148,   337,   149,   338,   541,   150,   339,   544,
     151,   126,   318,   127,   319,   614,   615,   616,   702,   824,
     617,   703,   618,   704,   619,   705,   620,   232,   375,   622,
     623,   624,   625,   626,   711,   627,   712,   128,   328,   650,
     651,   652,   653,   654,   655,   656,   129,   330,   660,   661,
     662,   732,    57,    71,   264,   265,   266,   388,   267,   389,
     130,   331,   669,   670,   671,   672,   673,   674,   675,   676,
     131,   324,   630,   631,   632,   716,    45,    65,   172,   173,
     174,   349,   175,   344,   176,   345,   177,   346,   178,   350,
     179,   351,   180,   355,   181,   354,   560,   182,   183,   132,
     327,   642,   643,   644,   725,   790,   791,   133,   325,    51,
      68,   634,   635,   636,   719,    53,    69,   233,   234,   235,
     236,   237,   238,   239,   374,   240,   378,   241,   377,   242,
     243,   379,   244,   134,   326,   638,   639,   640,   722,    55,
      70,   252,   253,   254,   255,   256,   383,   257,   258,   259,
     260,   185,   347,   688,   689,   690,   752,    47,    66,   195,
     196,   197,   360,   186,   348,   187,   356,   692,   693,   694,
     755,    49,    67,   209,   210,   211,   135,   315,   136,   316,
     137,   317,   215,   370,   216,   364,   217,   365,   218,   367,
     219,   366,   220,   369,   221,   368,   222,   363,   191,   357,
     696,   758,   138,   329,   658,   343,   454,   455,   456,   457,
     458,   545,   139,   140,   333,   679,   680,   681,   743,   682,
     744,   141,   334,    59,    72,   283,   284,   285,   286,   393,
     287,   394,   288,   289,   396,   290,   291,   292,   399,   586,
     293,   400,   294,   295,   296,   297,   404,   593,   298,   405,
      89,   306,    90,   307,    91,   308,    92,   305,   598,   599,
     600,   698,   843,   844,   846,   854,   855,   856,   857,   862,
     858,   860,   872,   873,   874,   881,   882,   883,   888,   884,
     885,   886
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   249,   223,   167,   193,   207,   250,   231,   248,   263,
     282,    73,   198,   786,   657,   184,   194,   208,    79,   787,
     188,   168,   212,   189,   251,   213,   224,   789,   190,   152,
     214,   169,   584,   152,   225,   170,   171,    27,   796,    28,
      26,    29,    38,    95,    96,    97,    98,    96,    97,    98,
      40,   225,    42,   226,   227,   107,    44,   228,   229,   230,
     728,   261,   262,   729,   101,   102,   103,   192,   157,   153,
     154,   155,    46,   107,    48,   106,   107,   225,    50,   152,
     588,   589,   590,   591,   156,    52,   157,   158,   159,   160,
     161,   162,   163,    95,    96,    97,    98,   310,    76,   164,
     165,   446,   311,   164,    54,   335,   849,   166,   850,   851,
     336,   592,   341,    56,   101,   102,   103,   342,   105,    84,
     106,   786,    58,   107,   225,   142,   143,   787,    84,   144,
      80,   358,   145,   585,   730,   789,   359,   731,   159,    81,
      82,    83,   163,   261,   262,    84,   796,   361,   390,   164,
      84,    93,   362,   391,    84,   847,   875,   166,   848,   876,
      94,    95,    96,    97,    98,    99,   100,   299,    84,   539,
     540,    84,   663,   664,   665,   666,   667,   668,    30,    31,
      32,    33,   101,   102,   103,   104,   105,   406,   542,   543,
     106,   107,   407,   225,   245,   226,   227,   246,   247,   300,
     335,   108,    96,    97,    98,   697,   301,   788,   645,   646,
     647,   648,   799,   649,   109,   110,   877,   699,    84,   878,
     879,   880,   700,   341,   713,   677,   678,   111,   701,   714,
     112,   107,   302,   303,   713,   741,   371,   113,   114,   715,
     742,   115,   745,   372,   406,   358,   373,   746,    85,   747,
     830,   408,   409,   833,   381,   199,   309,   313,   834,   200,
     201,   202,   203,   204,   205,   390,   206,   361,   863,   386,
     835,   892,   839,   864,   448,   314,   893,   449,   557,   558,
     559,   447,   820,   821,   822,   823,    84,    84,   320,   321,
     322,   323,   332,   450,   340,   352,   167,   353,   451,   193,
     376,   452,   380,   382,   410,   384,   453,   198,   184,   385,
     207,   194,   387,   188,   168,   788,   189,   392,   249,   418,
     231,   190,   208,   250,   169,   248,    84,   212,   170,   171,
     213,   395,   397,   398,   401,   214,   402,   403,   411,   412,
     413,   251,   602,   414,   282,   415,   417,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   419,   420,   421,
     422,   423,   424,   425,   518,   519,   520,   225,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,   426,   429,   427,   430,   428,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   441,   442,
     443,   459,    84,   460,   461,   462,   444,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   474,   476,   477,
     478,   479,   480,   481,   482,   483,   485,   486,   488,   487,
     489,   490,   493,   491,   494,   497,   495,   498,   500,   580,
     501,   502,   504,   503,   505,   506,   621,   621,   507,   508,
     509,    84,   512,   613,   613,   510,   595,   511,   513,   515,
     516,   522,   523,   517,   282,   521,   525,   524,   448,   526,
     527,   449,   528,   529,   530,   447,   531,   532,   533,   548,
     549,   534,   535,   536,   537,   546,   547,   450,   550,   551,
     562,   587,   451,    28,   563,   452,   554,   555,   556,   561,
     453,   564,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   581,   582,   583,   594,
     629,   597,   633,   637,   641,   659,   685,   687,   691,   695,
     706,   707,   708,   709,   710,   718,   552,   717,   721,   720,
     723,   724,   726,   727,   734,   733,   735,   736,   737,   738,
     739,   740,   760,   748,   751,   753,   754,   756,   757,   813,
     759,   762,   763,   764,   765,   771,   772,   809,   810,   565,
     818,   812,   766,   819,   861,   831,   842,   768,   767,   832,
     825,   769,   770,   840,   865,   867,   802,   803,   804,   805,
     869,   871,   889,   806,   807,   826,   827,   828,   829,   890,
     891,   894,   416,   836,   596,   440,   837,   838,   445,   841,
     601,   866,   870,   773,   798,   801,   628,   800,   808,   895,
     775,   774,   797,   499,   473,   896,   845,   897,   899,   777,
     776,   492,   778,   779,   621,   814,   815,   496,   686,   816,
     475,   613,   811,   249,   167,   817,   785,   231,   250,   683,
     248,   514,   859,   780,   761,   868,   184,   887,   898,     0,
     263,   188,   168,     0,   189,   792,   251,     0,     0,   190,
     793,   781,   169,   794,   484,     0,   170,   171,   795,     0,
     193,   782,     0,   207,     0,   783,   784,     0,   198,     0,
       0,     0,   194,     0,     0,   208,     0,     0,     0,     0,
     212,     0,     0,   213,     0,     0,     0,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   785,     0,     0,     0,     0,     0,
       0,   780,     0,     0,     0,     0,     0,   853,     0,     0,
       0,     0,     0,   792,   852,     0,     0,     0,   793,   781,
       0,   794,     0,     0,   853,     0,   795,     0,     0,   782,
       0,   852,     0,   783,   784
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    68,    65,    66,    67,    70,    69,    70,    71,
      72,    60,    66,   725,   532,    65,    66,    67,    10,   725,
      65,    65,    67,    65,    70,    67,    27,   725,    65,     7,
      67,    65,    15,     7,    52,    65,    65,     5,   725,     7,
       0,     9,     7,    21,    22,    23,    24,    22,    23,    24,
       7,    52,     7,    54,    55,    51,     7,    58,    59,    60,
       3,    88,    89,     6,    42,    43,    44,    63,    64,    47,
      48,    49,     7,    51,     7,    50,    51,    52,     7,     7,
     118,   119,   120,   121,    62,     7,    64,    65,    66,    67,
      68,    69,    70,    21,    22,    23,    24,     3,   146,    77,
      78,    76,     8,    77,     7,     3,   124,    85,   126,   127,
       8,   149,     3,     7,    42,    43,    44,     8,    46,   146,
      50,   833,     7,    51,    52,    12,    13,   833,   146,    16,
     122,     3,    19,   116,     3,   833,     8,     6,    66,   131,
     132,   133,    70,    88,    89,   146,   833,     3,     3,    77,
     146,    11,     8,     8,   146,     3,     3,    85,     6,     6,
      20,    21,    22,    23,    24,    25,    26,     6,   146,    14,
      15,   146,    91,    92,    93,    94,    95,    96,   146,   147,
     148,   149,    42,    43,    44,    45,    46,     3,    17,    18,
      50,    51,     8,    52,    53,    54,    55,    56,    57,     3,
       3,    61,    22,    23,    24,     8,     4,   725,    79,    80,
      81,    82,   730,    84,    74,    75,   125,     3,   146,   128,
     129,   130,     8,     3,     3,    99,   100,    87,     8,     8,
      90,    51,     8,     3,     3,     3,     8,    97,    98,     8,
       8,   101,     3,     3,     3,     3,     8,     8,   310,     8,
       8,   300,   301,     3,     8,    75,     4,     4,     8,    79,
      80,    81,    82,    83,    84,     3,    86,     3,     3,     8,
       8,     3,     8,     8,   343,     4,     8,   343,    71,    72,
      73,   343,    28,    29,    30,    31,   146,   146,     4,     4,
       4,     4,     4,   343,     4,     4,   358,     4,   343,   361,
       4,   343,     4,     3,   146,     4,   343,   361,   358,     4,
     372,   361,     3,   358,   358,   833,   358,     4,   387,   149,
     382,   358,   372,   387,   358,   387,   146,   372,   358,   358,
     372,     4,     4,     4,     4,   372,     4,     4,     4,     4,
       4,   387,    27,     4,   406,     4,     4,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,   149,     4,     4,
       4,     4,     4,   147,   413,   414,   415,    52,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   147,     4,   147,     4,   147,     4,
       4,     4,     4,     4,     4,   147,     4,     4,     4,     4,
       4,     4,   146,     4,     4,     4,   149,     4,     4,     4,
       4,   147,   149,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   147,
       4,     4,     4,   149,   149,     4,   149,     4,   149,   498,
       4,     4,     4,   147,   147,   147,   525,   526,     4,     4,
     149,   146,     4,   525,   526,   149,   515,   149,     4,     4,
       7,   146,   146,     7,   536,     7,     7,   146,   547,     7,
       5,   547,     5,     5,     5,   547,     5,     5,     5,   146,
     146,     7,     7,     7,     5,     8,     3,   547,   146,     5,
       5,   117,   547,     7,     7,   547,   146,   146,   146,   146,
     547,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
       7,   123,     7,     7,     7,     7,     4,     7,     7,    86,
       4,     4,     4,     4,     4,     3,   463,     6,     3,     6,
       6,     3,     6,     3,     3,     6,     4,     4,     4,     4,
       4,     4,     4,   146,   146,     6,     3,     6,     3,     3,
       8,     4,     4,     4,     4,     4,     4,     4,     4,   476,
       4,     6,   147,     5,     4,     8,     7,   147,   149,     8,
     146,   149,   147,     8,     4,     4,   147,   147,   147,   147,
       5,     7,     4,   147,   147,   146,   146,   146,   146,     4,
       4,     4,   310,   146,   516,   335,   146,   146,   341,   146,
     521,   147,   146,   713,   728,   734,   526,   732,   741,   149,
     718,   716,   727,   390,   358,   147,   833,   147,   146,   721,
     719,   382,   722,   724,   713,   752,   754,   387,   547,   755,
     361,   713,   745,   722,   716,   757,   725,   719,   722,   536,
     722,   406,   847,   725,   699,   863,   716,   875,   892,    -1,
     732,   716,   716,    -1,   716,   725,   722,    -1,    -1,   716,
     725,   725,   716,   725,   372,    -1,   716,   716,   725,    -1,
     752,   725,    -1,   755,    -1,   725,   725,    -1,   752,    -1,
      -1,    -1,   752,    -1,    -1,   755,    -1,    -1,    -1,    -1,
     755,    -1,    -1,   755,    -1,    -1,    -1,    -1,   755,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   833,    -1,    -1,    -1,    -1,    -1,
      -1,   833,    -1,    -1,    -1,    -1,    -1,   846,    -1,    -1,
      -1,    -1,    -1,   833,   846,    -1,    -1,    -1,   833,   833,
      -1,   833,    -1,    -1,   863,    -1,   833,    -1,    -1,   833,
      -1,   863,    -1,   833,   833
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,     0,     5,     7,     9,
     146,   147,   148,   149,   164,   165,   166,   171,     7,   180,
       7,   186,     7,   200,     7,   276,     7,   357,     7,   371,
       7,   309,     7,   315,     7,   339,     7,   252,     7,   423,
     172,   167,   181,   187,   201,   277,   358,   372,   310,   316,
     340,   253,   424,   164,   173,   174,   146,   169,   170,    10,
     122,   131,   132,   133,   146,   179,   182,   183,   184,   450,
     452,   454,   456,    11,    20,    21,    22,    23,    24,    25,
      26,    42,    43,    44,    45,    46,    50,    51,    61,    74,
      75,    87,    90,    97,    98,   101,   179,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   211,   213,   237,   246,
     260,   270,   299,   307,   333,   376,   378,   380,   402,   412,
     413,   421,    12,    13,    16,    19,   198,   199,   202,   204,
     207,   210,     7,    47,    48,    49,    62,    64,    65,    66,
      67,    68,    69,    70,    77,    78,    85,   179,   190,   191,
     192,   195,   278,   279,   280,   282,   284,   286,   288,   290,
     292,   294,   297,   298,   333,   351,   363,   365,   376,   378,
     380,   398,    63,   179,   333,   359,   360,   361,   363,    75,
      79,    80,    81,    82,    83,    84,    86,   179,   333,   373,
     374,   375,   376,   378,   380,   382,   384,   386,   388,   390,
     392,   394,   396,   307,    27,    52,    54,    55,    58,    59,
      60,   179,   227,   317,   318,   319,   320,   321,   322,   323,
     325,   327,   329,   330,   332,    53,    56,    57,   179,   227,
     321,   327,   341,   342,   343,   344,   345,   347,   348,   349,
     350,    88,    89,   179,   254,   255,   256,   258,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   179,   425,   426,   427,   428,   430,   432,   433,
     435,   436,   437,   440,   442,   443,   444,   445,   448,     6,
       3,     4,     8,     3,   185,   457,   451,   453,   455,     4,
       3,     8,   197,     4,     4,   377,   379,   381,   212,   214,
       4,     4,     4,     4,   271,   308,   334,   300,   238,   403,
     247,   261,     4,   414,   422,     3,     8,   203,   205,   208,
       4,     3,     8,   405,   283,   285,   287,   352,   364,   281,
     289,   291,     4,     4,   295,   293,   366,   399,     3,     8,
     362,     3,     8,   397,   385,   387,   391,   389,   395,   393,
     383,     8,     3,     8,   324,   228,     4,   328,   326,   331,
       4,     8,     3,   346,     4,     4,     8,     3,   257,   259,
       3,     8,     4,   429,   431,     4,   434,     4,     4,   438,
     441,     4,     4,     4,   446,   449,     3,     8,   164,   164,
     146,     4,     4,     4,     4,     4,   183,     4,   149,   149,
       4,     4,     4,     4,     4,   147,   147,   147,   147,     4,
       4,     4,     4,     4,     4,     4,     4,   147,     4,     4,
     189,     4,     4,     4,   149,   199,    76,   179,   227,   307,
     333,   376,   378,   380,   406,   407,   408,   409,   410,     4,
       4,     4,     4,     4,     4,     4,     4,   147,   149,     4,
       4,     4,     4,   279,     4,   360,     4,     4,     4,     4,
       4,     4,     4,     4,   375,     4,     4,   147,     4,     4,
       4,   149,   319,     4,   149,   149,   343,     4,     4,   255,
     149,     4,     4,   147,     4,   147,   147,     4,     4,   149,
     149,   149,     4,     4,   426,     4,     7,     7,   164,   164,
     164,     7,   146,   146,   146,     7,     7,     5,     5,     5,
       5,     5,     5,     5,     7,     7,     7,     5,   175,    14,
      15,   206,    17,    18,   209,   411,     8,     3,   146,   146,
     146,     5,   166,   168,   146,   146,   146,    71,    72,    73,
     296,   146,     5,     7,   146,   175,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     164,   146,   146,   146,    15,   116,   439,   117,   118,   119,
     120,   121,   149,   447,   146,   164,   188,   123,   458,   459,
     460,   198,    27,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,   179,   215,   216,   217,   220,   222,   224,
     226,   227,   229,   230,   231,   232,   233,   235,   215,     7,
     272,   273,   274,     7,   311,   312,   313,     7,   335,   336,
     337,     7,   301,   302,   303,    79,    80,    81,    82,    84,
     239,   240,   241,   242,   243,   244,   245,   292,   404,     7,
     248,   249,   250,    91,    92,    93,    94,    95,    96,   262,
     263,   264,   265,   266,   267,   268,   269,    99,   100,   415,
     416,   417,   419,   425,   176,     4,   408,     7,   353,   354,
     355,     7,   367,   368,   369,    86,   400,     8,   461,     3,
       8,     8,   218,   221,   223,   225,     4,     4,     4,     4,
       4,   234,   236,     3,     8,     8,   275,     6,     3,   314,
       6,     3,   338,     6,     3,   304,     6,     3,     3,     6,
       3,     6,   251,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   418,   420,     3,     8,     8,   146,   177,
     178,   146,   356,     6,     3,   370,     6,     3,   401,     8,
       4,   459,     4,     4,     4,     4,   147,   149,   147,   149,
     147,     4,     4,   216,   278,   274,   317,   313,   341,   337,
     179,   190,   191,   192,   195,   227,   270,   288,   292,   294,
     305,   306,   333,   376,   378,   380,   398,   303,   240,   292,
     254,   250,   147,   147,   147,   147,   147,   147,   263,     4,
       4,   416,     6,     3,   359,   355,   373,   369,     4,     5,
      28,    29,    30,    31,   219,   146,   146,   146,   146,   146,
       8,     8,     8,     3,     8,     8,   146,   146,   146,     8,
       8,   146,     7,   462,   463,   306,   464,     3,     6,   124,
     126,   127,   179,   227,   465,   466,   467,   468,   470,   463,
     471,     4,   469,     3,     8,     4,   147,     4,   466,     5,
     146,     7,   472,   473,   474,     3,     6,   125,   128,   129,
     130,   475,   476,   477,   479,   480,   481,   473,   478,     4,
       4,     4,     3,     8,     4,   149,   147,   147,   476,   146
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
     360,   360,   360,   360,   362,   361,   364,   363,   366,   365,
     367,   367,   368,   368,   370,   369,   372,   371,   373,   373,
     374,   374,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   377,   376,   379,   378,   381,
     380,   383,   382,   385,   384,   387,   386,   389,   388,   391,
     390,   393,   392,   395,   394,   397,   396,   399,   398,   401,
     400,   403,   402,   404,   404,   405,   292,   406,   406,   407,
     407,   408,   408,   408,   408,   408,   408,   408,   408,   409,
     411,   410,   412,   414,   413,   415,   415,   416,   416,   418,
     417,   420,   419,   422,   421,   424,   423,   425,   425,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   427,   429,   428,   431,   430,   432,
     434,   433,   435,   436,   438,   437,   439,   439,   441,   440,
     442,   443,   444,   446,   445,   447,   447,   447,   447,   447,
     449,   448,   451,   450,   453,   452,   455,   454,   457,   456,
     458,   458,   459,   461,   460,   462,   462,   464,   463,   465,
     465,   466,   466,   466,   466,   466,   467,   469,   468,   471,
     470,   472,   472,   474,   473,   475,   475,   476,   476,   476,
     476,   478,   477,   479,   480,   481
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
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
  "$@85", "client_classes", "$@86", "client_classes_list", "$@87",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@88",
  "dhcp4o6_port", "control_socket", "$@89", "control_socket_params",
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
    1330,  1331,  1332,  1333,  1336,  1336,  1344,  1344,  1354,  1354,
    1364,  1365,  1368,  1369,  1372,  1372,  1381,  1381,  1390,  1391,
    1394,  1395,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,
    1407,  1408,  1409,  1410,  1411,  1414,  1414,  1422,  1422,  1430,
    1430,  1438,  1438,  1446,  1446,  1454,  1454,  1462,  1462,  1470,
    1470,  1478,  1478,  1486,  1486,  1494,  1494,  1507,  1507,  1517,
    1517,  1528,  1528,  1538,  1539,  1542,  1542,  1552,  1553,  1556,
    1557,  1560,  1561,  1562,  1563,  1564,  1565,  1566,  1567,  1570,
    1572,  1572,  1584,  1591,  1591,  1601,  1602,  1605,  1606,  1609,
    1609,  1617,  1617,  1627,  1627,  1639,  1639,  1649,  1650,  1653,
    1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,
    1664,  1665,  1666,  1667,  1670,  1675,  1675,  1683,  1683,  1691,
    1696,  1696,  1704,  1709,  1714,  1714,  1722,  1723,  1726,  1726,
    1734,  1739,  1744,  1749,  1749,  1757,  1760,  1763,  1766,  1769,
    1775,  1775,  1785,  1785,  1792,  1792,  1799,  1799,  1811,  1811,
    1824,  1825,  1829,  1833,  1833,  1845,  1846,  1850,  1850,  1858,
    1859,  1862,  1863,  1864,  1865,  1866,  1869,  1874,  1874,  1882,
    1882,  1892,  1893,  1896,  1896,  1904,  1905,  1908,  1909,  1910,
    1911,  1914,  1914,  1922,  1927,  1932
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
#line 4377 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1937 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
