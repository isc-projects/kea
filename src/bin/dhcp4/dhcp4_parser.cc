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

  case 92:
#line 436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 588 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 861 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 218:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 970 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 986 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1104 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1159 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1169 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1426 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2521 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2936 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1754 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
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
     211,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,    37,    18,    56,    61,    65,    73,    86,
     125,   135,   143,   154,   156,   198,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
      18,    -2,    16,   176,   162,    22,   -11,    34,    45,    69,
      99,   -27,   222,  -694,   187,   166,   203,   205,   239,  -694,
    -694,  -694,  -694,  -694,   242,  -694,    33,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   281,   285,  -694,  -694,  -694,   290,
     291,   292,   293,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,   294,  -694,  -694,  -694,    42,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,   295,    43,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,   298,   299,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,    51,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,    52,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   301,   307,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   304,
    -694,  -694,   309,  -694,  -694,  -694,   311,  -694,  -694,   312,
     316,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,   334,   335,  -694,  -694,  -694,  -694,   333,   339,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
      71,  -694,  -694,  -694,   353,  -694,  -694,   354,  -694,   355,
     356,  -694,  -694,   360,   361,   363,  -694,  -694,  -694,    75,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,    18,    18,  -694,   223,
     366,   367,   368,   369,   370,  -694,    16,  -694,   371,   227,
     228,   374,   375,   376,   234,   235,   236,   237,   381,   382,
     383,   384,   385,   386,   387,   388,   246,   390,   391,   176,
    -694,   392,   393,   394,   250,   162,  -694,    25,   396,   397,
     398,   399,   400,   401,   402,   403,   263,   260,   404,   407,
     408,   409,    22,  -694,   410,   -11,  -694,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,  -694,    34,  -694,
     421,   422,   280,   424,   425,   426,   282,  -694,    69,   428,
     284,   286,  -694,    99,   430,   432,    88,  -694,   288,   434,
     435,   296,   436,   297,   300,   437,   438,   303,   305,   306,
     441,   444,   222,  -694,  -694,  -694,   445,   446,   449,    18,
      18,    18,  -694,   452,  -694,  -694,   314,   454,   455,  -694,
    -694,  -694,  -694,   459,   460,   461,   462,   464,   465,   466,
     467,  -694,   468,   469,  -694,   472,   210,   270,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   470,   477,
    -694,  -694,  -694,   327,   336,   337,   476,   478,   340,   341,
     342,  -694,  -694,   163,   343,   486,   485,  -694,   347,  -694,
     348,   349,   472,   351,   352,   357,   358,   359,   362,   364,
    -694,   365,   372,  -694,   373,   377,   378,  -694,  -694,   379,
    -694,  -694,  -694,   380,    18,  -694,  -694,   389,   395,  -694,
     405,  -694,  -694,    17,   423,  -694,  -694,  -694,    39,   406,
    -694,    18,   176,   427,  -694,  -694,  -694,   162,  -694,   220,
     220,   492,   493,   494,   495,   159,    31,   499,   137,   179,
     222,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   503,
    -694,    25,  -694,  -694,  -694,   502,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,   505,   429,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,   102,  -694,   128,  -694,  -694,   182,  -694,  -694,
    -694,  -694,   509,   510,   512,   513,   516,  -694,  -694,  -694,
     183,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   186,  -694,   515,   519,  -694,  -694,
     521,   525,  -694,  -694,   523,   527,  -694,  -694,   526,   528,
    -694,  -694,  -694,  -694,  -694,  -694,    36,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,    91,  -694,   530,   531,  -694,   529,
     533,   534,   535,   538,   539,   192,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   196,  -694,  -694,  -694,   200,
     431,   433,  -694,  -694,   540,   541,  -694,  -694,   542,   544,
    -694,  -694,   537,  -694,   545,   427,  -694,  -694,   549,   550,
     551,   552,   439,   440,   443,   442,   447,   553,   554,   220,
    -694,  -694,    22,  -694,   492,    69,  -694,   493,    99,  -694,
     494,    60,  -694,   495,   159,  -694,    31,  -694,   -27,  -694,
     499,   448,   450,   451,   453,   456,   457,   137,  -694,   555,
     556,   179,  -694,  -694,  -694,   557,   558,  -694,   -11,  -694,
     502,    34,  -694,   505,   560,  -694,   561,  -694,   253,   463,
     471,   473,  -694,  -694,  -694,  -694,  -694,   474,   475,  -694,
     206,  -694,   559,  -694,   562,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,   208,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   259,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,   479,   480,  -694,  -694,   481,   261,  -694,
     563,  -694,   482,   565,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,    60,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,   119,  -694,  -694,
      46,   565,  -694,  -694,   564,  -694,  -694,  -694,   262,  -694,
    -694,  -694,  -694,  -694,   569,   458,   570,    46,  -694,   571,
    -694,   483,  -694,   568,  -694,  -694,   140,  -694,    54,   568,
    -694,  -694,   574,   576,   577,   268,  -694,  -694,  -694,  -694,
    -694,  -694,   578,   484,   487,   488,    54,  -694,   490,  -694,
    -694,  -694,  -694,  -694
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   106,     9,   218,    11,   360,    13,   380,    15,
     289,    17,   297,    19,   332,    21,   183,    23,   459,    25,
      43,    37,     0,     0,     0,     0,     0,   382,     0,   299,
     334,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     512,   506,   508,   510,     0,    63,     0,    56,    58,    60,
      61,    62,    59,    98,     0,     0,   399,   119,   121,     0,
       0,     0,     0,   210,   287,   324,   264,   161,   425,   175,
     194,     0,   447,   457,    91,     0,    68,    70,    71,    72,
      73,    88,    89,    76,    77,    78,    79,    83,    84,    74,
      75,    81,    82,    90,    80,    85,    86,    87,   108,   110,
     114,     0,     0,   100,   102,   103,   104,   105,   429,   245,
     247,   249,   352,   370,   243,   251,   253,     0,     0,   257,
     255,   372,   421,   242,   222,   223,   224,   236,     0,   220,
     227,   238,   239,   240,   228,   229,   232,   234,   230,   231,
     225,   226,   241,   233,   237,   235,   368,   367,   365,     0,
     362,   364,   366,   401,   403,   419,   407,   409,   413,   411,
     417,   415,   405,   398,   394,     0,   383,   384,   395,   396,
     397,   391,   386,   392,   388,   389,   390,   393,   387,     0,
     314,   151,     0,   318,   316,   321,     0,   310,   311,     0,
     300,   301,   303,   313,   304,   305,   306,   320,   307,   308,
     309,   346,     0,     0,   344,   345,   348,   349,     0,   335,
     336,   338,   339,   340,   341,   342,   343,   190,   192,   187,
       0,   185,   188,   189,     0,   479,   481,     0,   484,     0,
       0,   488,   492,     0,     0,     0,   497,   504,   477,     0,
     461,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,    42,     0,     0,    35,     0,
       0,     0,     0,     0,     0,    53,     0,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,     0,   107,   431,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,     0,     0,   361,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   381,     0,   290,
       0,     0,     0,     0,     0,     0,     0,   298,     0,     0,
       0,     0,   333,     0,     0,     0,     0,   184,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   460,    46,    39,     0,     0,     0,     0,
       0,     0,    57,     0,    96,    97,     0,     0,     0,    92,
      93,    94,    95,     0,     0,     0,     0,     0,     0,     0,
       0,   446,     0,     0,    69,     0,     0,     0,   118,   101,
     444,   442,   443,   437,   438,   439,   440,   441,     0,   432,
     433,   435,   436,     0,     0,     0,     0,     0,     0,     0,
       0,   262,   263,     0,     0,     0,     0,   221,     0,   363,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     385,     0,     0,   312,     0,     0,     0,   323,   302,     0,
     350,   351,   337,     0,     0,   186,   478,     0,     0,   483,
       0,   486,   487,     0,     0,   494,   495,   496,     0,     0,
     462,     0,     0,     0,   507,   509,   511,     0,   400,     0,
       0,   212,   291,   326,   266,     0,     0,   177,     0,     0,
       0,    47,   109,   112,   113,   111,   116,   117,   115,     0,
     430,     0,   246,   248,   250,   354,    36,   371,   244,   252,
     254,   259,   260,   261,   258,   256,   374,     0,   369,   402,
     404,   420,   408,   410,   414,   412,   418,   416,   406,   315,
     152,   319,   317,   322,   347,   191,   193,   480,   482,   485,
     490,   491,   489,   493,   499,   500,   501,   502,   503,   498,
     505,    40,     0,   517,     0,   514,   516,     0,   138,   144,
     146,   148,     0,     0,     0,     0,     0,   157,   159,   137,
       0,   123,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,     0,   216,     0,   213,   214,   295,
       0,   292,   293,   330,     0,   327,   328,   270,     0,   267,
     268,   170,   171,   172,   173,   174,     0,   163,   165,   166,
     167,   168,   169,   427,     0,   181,     0,   178,   179,     0,
       0,     0,     0,     0,     0,     0,   196,   198,   199,   200,
     201,   202,   203,   453,   455,     0,   449,   451,   452,     0,
      49,     0,   434,   358,     0,   355,   356,   378,     0,   375,
     376,   423,     0,    65,     0,     0,   513,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,   122,     0,   211,     0,   299,   288,     0,   334,   325,
       0,     0,   265,     0,     0,   162,     0,   426,     0,   176,
       0,     0,     0,     0,     0,     0,     0,     0,   195,     0,
       0,     0,   448,   458,    51,     0,    50,   445,     0,   353,
       0,   382,   373,     0,     0,   422,     0,   515,     0,     0,
       0,     0,   150,   153,   154,   155,   156,     0,     0,   124,
       0,   215,     0,   294,     0,   329,   286,   285,   277,   278,
     280,   274,   275,   276,   284,   283,     0,   272,   279,   281,
     282,   269,   164,   428,     0,   180,   204,   205,   206,   207,
     208,   209,   197,     0,     0,   450,    48,     0,     0,   357,
       0,   377,     0,     0,   140,   141,   142,   143,   139,   145,
     147,   149,   158,   160,   217,   296,   331,     0,   271,   182,
     454,   456,    52,   359,   379,   424,   521,     0,   519,   273,
       0,     0,   518,   533,     0,   531,   529,   525,     0,   523,
     527,   528,   526,   520,     0,     0,     0,     0,   522,     0,
     530,     0,   524,     0,   532,   537,     0,   535,     0,     0,
     534,   545,     0,     0,     0,     0,   539,   541,   542,   543,
     544,   536,     0,     0,     0,     0,     0,   538,     0,   547,
     548,   549,   540,   546
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,   -48,  -694,   105,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,    93,  -694,  -694,  -694,   -62,
    -694,  -694,  -694,   277,  -694,  -694,  -694,  -694,    57,   255,
     -52,   -47,   -44,  -694,  -694,   -41,  -694,  -694,    68,   252,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,    72,  -121,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,   -69,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -131,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -134,  -694,  -694,  -694,  -129,   215,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -135,  -694,  -694,  -694,  -694,  -694,  -694,
    -693,  -694,  -694,  -694,  -108,  -694,  -694,  -694,  -105,   256,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -688,  -694,
    -694,  -694,  -509,  -694,  -687,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -113,  -694,  -694,  -216,   -57,  -694,  -694,
    -694,  -694,  -694,  -104,  -694,  -694,  -694,  -103,  -694,   238,
    -694,   -40,  -694,  -694,  -694,  -694,  -694,   -39,  -694,  -694,
    -694,  -694,  -694,   -51,  -694,  -694,  -694,  -106,  -694,  -694,
    -694,  -100,  -694,   232,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -128,  -694,  -694,  -694,  -125,
     269,  -694,  -694,   -64,  -694,  -694,  -694,  -694,  -694,  -123,
    -694,  -694,  -694,  -120,  -694,   264,   -45,  -694,  -331,  -694,
    -318,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -686,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,    96,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -102,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,   108,   240,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,
    -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,  -694,   -54,
    -694,  -694,  -694,  -198,  -694,  -694,  -213,  -694,  -694,  -694,
    -694,  -694,  -694,  -224,  -694,  -694,  -240,  -694,  -694,  -694,
    -694,  -694
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   547,    77,
      78,    37,    60,    74,    75,   532,   680,   745,   746,   114,
      39,    62,    86,    87,    88,   300,    41,    63,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   308,   142,   143,
      43,    64,   144,   331,   145,   332,   535,   146,   333,   538,
     147,   124,   312,   125,   313,   610,   611,   612,   698,   818,
     613,   699,   614,   700,   615,   701,   616,   228,   371,   618,
     619,   620,   621,   622,   707,   623,   708,   126,   322,   646,
     647,   648,   649,   650,   651,   652,   127,   324,   656,   657,
     658,   728,    57,    71,   260,   261,   262,   384,   263,   385,
     128,   325,   665,   666,   667,   668,   669,   670,   671,   672,
     129,   318,   626,   627,   628,   712,    45,    65,   168,   169,
     170,   343,   171,   338,   172,   339,   173,   340,   174,   344,
     175,   345,   176,   349,   177,   348,   554,   178,   179,   130,
     321,   638,   639,   640,   721,   786,   787,   131,   319,    51,
      68,   630,   631,   632,   715,    53,    69,   229,   230,   231,
     232,   233,   234,   235,   370,   236,   374,   237,   373,   238,
     239,   375,   240,   132,   320,   634,   635,   636,   718,    55,
      70,   248,   249,   250,   251,   252,   379,   253,   254,   255,
     256,   181,   341,   684,   685,   686,   748,    47,    66,   189,
     190,   191,   354,   182,   342,   183,   350,   688,   689,   690,
     751,    49,    67,   205,   206,   207,   133,   311,   209,   357,
     210,   358,   211,   366,   212,   360,   213,   361,   214,   363,
     215,   362,   216,   365,   217,   364,   218,   359,   185,   351,
     692,   754,   134,   323,   654,   337,   448,   449,   450,   451,
     452,   539,   135,   136,   327,   675,   676,   677,   739,   678,
     740,   137,   328,    59,    72,   279,   280,   281,   282,   389,
     283,   390,   284,   285,   392,   286,   287,   288,   395,   582,
     289,   396,   290,   291,   292,   293,   400,   589,   294,   401,
      89,   302,    90,   303,    91,   304,    92,   301,   594,   595,
     596,   694,   837,   838,   840,   848,   849,   850,   851,   856,
     852,   854,   866,   867,   868,   875,   876,   877,   882,   878,
     879,   880
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   245,   192,   163,   187,   203,   446,   227,   244,   259,
     278,   219,    73,   164,   180,   188,   204,   653,   165,   447,
     184,   166,   208,    27,   167,    28,    79,    29,   782,   148,
     246,   247,   580,   783,   785,   790,   306,    26,   148,   724,
     105,   307,   725,    95,    96,   329,   335,    96,   193,   194,
     330,   336,   186,   153,   352,   355,    96,   193,   194,   353,
     356,   257,   258,    38,    99,   100,   101,   148,    40,   149,
     150,   151,    42,   105,   386,   104,   105,   221,   402,   387,
      44,    95,    96,   403,   152,   105,   153,   154,   155,   156,
     157,   158,   159,    46,   726,   104,   220,   727,   221,   160,
     161,   440,    99,   100,   101,   329,   103,   162,   160,   195,
     693,   105,   221,   196,   197,   198,   199,   200,   201,    84,
     202,   221,   841,   222,   223,   842,   155,   224,   225,   226,
     159,   695,    48,   581,   782,    84,   696,   160,    80,   783,
     785,   790,    50,   869,    76,   162,   870,    81,    82,    83,
      52,   221,   241,   222,   223,   242,   243,   584,   585,   586,
     587,    54,    84,    56,    30,    31,    32,    33,    84,   296,
     843,    84,   844,   845,   138,   139,   257,   258,   140,   871,
      84,   141,   872,   873,   874,   335,   709,    93,   588,   709,
     697,   710,    84,   295,   711,   737,    94,    95,    96,   741,
     738,    97,    98,   402,   742,    58,    84,   297,   743,   352,
     446,   827,   784,   298,   824,    84,   828,   793,    99,   100,
     101,   102,   103,   447,   533,   534,   104,   105,   659,   660,
     661,   662,   663,   664,   551,   552,   553,   106,   641,   642,
     643,   644,   299,   645,    85,    84,   305,   598,   404,   405,
     107,   108,   599,   600,   601,   602,   603,   604,   605,   606,
     607,   608,   386,   109,   355,   857,   110,   829,   442,   833,
     858,   886,   221,   111,   112,   441,   887,   113,   673,   674,
     443,   814,   815,   816,   817,   309,   444,   536,   537,   310,
     163,   192,   445,   187,   314,   315,   316,   317,   326,   334,
     164,   180,   346,   347,   188,   165,   203,   184,   166,   367,
     368,   167,   369,   372,   245,   376,   227,   204,   784,   378,
     377,   244,    84,   208,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   380,   381,
     278,   382,   383,   246,   247,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,   388,   391,   393,
     394,   514,   515,   516,   397,   398,    84,   399,    84,   406,
     407,   408,   409,   410,   411,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   435,   436,   437,   438,
     453,   454,   455,   456,   457,   458,   459,   460,   463,   462,
     461,   464,   465,   466,   468,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   481,   482,   483,   484,   485,
     486,   487,   489,   490,   493,   491,   494,   496,   497,   498,
     500,   503,   504,   499,   501,   508,   576,   502,   509,   511,
     617,   617,   505,   512,   506,   507,   513,   609,   609,   517,
     518,   519,   520,   591,   521,   522,   523,   524,   278,   525,
     526,   527,   442,   542,   528,   529,   530,   531,   540,   441,
     541,   545,   543,   544,   443,    28,   548,   549,   550,   555,
     444,   556,   557,   558,   559,   560,   445,   562,   563,   625,
     629,   633,   637,   564,   565,   566,   655,   681,   567,   683,
     568,   569,   687,   702,   703,   691,   704,   705,   570,   571,
     706,   713,   714,   572,   573,   574,   575,   716,   717,   719,
     720,   723,   722,   731,   730,   577,   729,   732,   733,   734,
     583,   578,   735,   736,   750,   755,   749,   753,   752,   756,
     593,   579,   590,   758,   759,   760,   761,   767,   768,   803,
     804,   807,   546,   806,   812,   561,   813,   825,   855,   592,
     826,   834,   836,   859,   861,   865,   863,   744,   883,   747,
     884,   885,   888,   412,   434,   597,   762,   439,   769,   763,
     764,   765,   624,   792,   766,   796,   795,   797,   798,   794,
     799,   495,   802,   800,   801,   860,   771,   770,   467,   819,
     791,   839,   772,   773,   775,   492,   488,   820,   774,   821,
     822,   823,   809,   808,   469,   830,   831,   832,   835,   864,
     811,   810,   480,   889,   890,   891,   893,   682,   679,   805,
     617,   757,   510,   853,   862,   881,   892,   609,     0,   245,
     163,     0,   781,   227,     0,     0,   244,     0,     0,   776,
     164,   180,     0,     0,     0,   165,   259,   184,   166,   777,
     788,   167,     0,     0,   778,     0,   789,   779,   246,   247,
     780,     0,     0,     0,   192,     0,   187,     0,     0,   203,
       0,     0,     0,     0,     0,     0,     0,   188,     0,     0,
     204,     0,     0,     0,     0,     0,   208,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   781,     0,
       0,     0,     0,     0,     0,   776,     0,     0,     0,     0,
       0,   847,     0,     0,     0,   777,   788,     0,   846,     0,
     778,     0,   789,   779,     0,     0,   780,     0,   847,     0,
       0,     0,     0,     0,     0,   846
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    66,    65,    66,    67,   337,    69,    70,    71,
      72,    68,    60,    65,    65,    66,    67,   526,    65,   337,
      65,    65,    67,     5,    65,     7,    10,     9,   721,     7,
      70,    70,    15,   721,   721,   721,     3,     0,     7,     3,
      51,     8,     6,    21,    22,     3,     3,    22,    23,    24,
       8,     8,    63,    64,     3,     3,    22,    23,    24,     8,
       8,    88,    89,     7,    42,    43,    44,     7,     7,    47,
      48,    49,     7,    51,     3,    50,    51,    52,     3,     8,
       7,    21,    22,     8,    62,    51,    64,    65,    66,    67,
      68,    69,    70,     7,     3,    50,    27,     6,    52,    77,
      78,    76,    42,    43,    44,     3,    46,    85,    77,    75,
       8,    51,    52,    79,    80,    81,    82,    83,    84,   146,
      86,    52,     3,    54,    55,     6,    66,    58,    59,    60,
      70,     3,     7,   116,   827,   146,     8,    77,   122,   827,
     827,   827,     7,     3,   146,    85,     6,   131,   132,   133,
       7,    52,    53,    54,    55,    56,    57,   118,   119,   120,
     121,     7,   146,     7,   146,   147,   148,   149,   146,     3,
     124,   146,   126,   127,    12,    13,    88,    89,    16,   125,
     146,    19,   128,   129,   130,     3,     3,    11,   149,     3,
       8,     8,   146,     6,     8,     3,    20,    21,    22,     3,
       8,    25,    26,     3,     8,     7,   146,     4,     8,     3,
     541,     3,   721,     8,     8,   146,     8,   726,    42,    43,
      44,    45,    46,   541,    14,    15,    50,    51,    91,    92,
      93,    94,    95,    96,    71,    72,    73,    61,    79,    80,
      81,    82,     3,    84,   306,   146,     4,    27,   296,   297,
      74,    75,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     3,    87,     3,     3,    90,     8,   337,     8,
       8,     3,    52,    97,    98,   337,     8,   101,    99,   100,
     337,    28,    29,    30,    31,     4,   337,    17,    18,     4,
     352,   355,   337,   355,     4,     4,     4,     4,     4,     4,
     352,   352,     4,     4,   355,   352,   368,   352,   352,     8,
       3,   352,     8,     4,   383,     4,   378,   368,   827,     3,
       8,   383,   146,   368,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     4,     4,
     402,     8,     3,   383,   383,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,     4,     4,     4,
       4,   409,   410,   411,     4,     4,   146,     4,   146,   146,
       4,     4,     4,     4,     4,     4,   149,   149,     4,     4,
       4,   147,   147,   147,   147,     4,     4,     4,     4,     4,
       4,     4,     4,   147,     4,     4,     4,     4,     4,   149,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   149,
     147,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   147,     4,     4,
       4,   149,     4,   149,     4,   149,     4,   149,     4,     4,
       4,     4,     4,   147,   147,     4,   494,   147,     4,     4,
     519,   520,   149,     7,   149,   149,     7,   519,   520,     7,
     146,     7,     7,   511,     5,     5,     5,     5,   530,     5,
       5,     5,   541,   146,     7,     7,     7,     5,     8,   541,
       3,     5,   146,   146,   541,     7,   146,   146,   146,   146,
     541,     5,     7,   146,   146,   146,   541,   146,   146,     7,
       7,     7,     7,   146,   146,   146,     7,     4,   146,     7,
     146,   146,     7,     4,     4,    86,     4,     4,   146,   146,
       4,     6,     3,   146,   146,   146,   146,     6,     3,     6,
       3,     3,     6,     4,     3,   146,     6,     4,     4,     4,
     117,   146,     4,     4,     3,     8,     6,     3,     6,     4,
     123,   146,   146,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   457,     6,     4,   472,     5,     8,     4,   512,
       8,     8,     7,     4,     4,     7,     5,   146,     4,   146,
       4,     4,     4,   306,   329,   517,   147,   335,   709,   149,
     147,   149,   520,   724,   147,   147,   730,   147,   147,   728,
     147,   386,   737,   147,   147,   147,   714,   712,   352,   146,
     723,   827,   715,   717,   720,   383,   378,   146,   718,   146,
     146,   146,   750,   748,   355,   146,   146,   146,   146,   146,
     753,   751,   368,   149,   147,   147,   146,   541,   530,   741,
     709,   695,   402,   841,   857,   869,   886,   709,    -1,   718,
     712,    -1,   721,   715,    -1,    -1,   718,    -1,    -1,   721,
     712,   712,    -1,    -1,    -1,   712,   728,   712,   712,   721,
     721,   712,    -1,    -1,   721,    -1,   721,   721,   718,   718,
     721,    -1,    -1,    -1,   748,    -1,   748,    -1,    -1,   751,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   748,    -1,    -1,
     751,    -1,    -1,    -1,    -1,    -1,   751,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   827,    -1,
      -1,    -1,    -1,    -1,    -1,   827,    -1,    -1,    -1,    -1,
      -1,   840,    -1,    -1,    -1,   827,   827,    -1,   840,    -1,
     827,    -1,   827,   827,    -1,    -1,   827,    -1,   857,    -1,
      -1,    -1,    -1,    -1,    -1,   857
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
     452,   454,   456,    11,    20,    21,    22,    25,    26,    42,
      43,    44,    45,    46,    50,    51,    61,    74,    75,    87,
      90,    97,    98,   101,   179,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   211,   213,   237,   246,   260,   270,
     299,   307,   333,   376,   402,   412,   413,   421,    12,    13,
      16,    19,   198,   199,   202,   204,   207,   210,     7,    47,
      48,    49,    62,    64,    65,    66,    67,    68,    69,    70,
      77,    78,    85,   179,   190,   191,   192,   195,   278,   279,
     280,   282,   284,   286,   288,   290,   292,   294,   297,   298,
     333,   351,   363,   365,   376,   398,    63,   179,   333,   359,
     360,   361,   363,    23,    24,    75,    79,    80,    81,    82,
      83,    84,    86,   179,   333,   373,   374,   375,   376,   378,
     380,   382,   384,   386,   388,   390,   392,   394,   396,   307,
      27,    52,    54,    55,    58,    59,    60,   179,   227,   317,
     318,   319,   320,   321,   322,   323,   325,   327,   329,   330,
     332,    53,    56,    57,   179,   227,   321,   327,   341,   342,
     343,   344,   345,   347,   348,   349,   350,    88,    89,   179,
     254,   255,   256,   258,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   179,   425,
     426,   427,   428,   430,   432,   433,   435,   436,   437,   440,
     442,   443,   444,   445,   448,     6,     3,     4,     8,     3,
     185,   457,   451,   453,   455,     4,     3,     8,   197,     4,
       4,   377,   212,   214,     4,     4,     4,     4,   271,   308,
     334,   300,   238,   403,   247,   261,     4,   414,   422,     3,
       8,   203,   205,   208,     4,     3,     8,   405,   283,   285,
     287,   352,   364,   281,   289,   291,     4,     4,   295,   293,
     366,   399,     3,     8,   362,     3,     8,   379,   381,   397,
     385,   387,   391,   389,   395,   393,   383,     8,     3,     8,
     324,   228,     4,   328,   326,   331,     4,     8,     3,   346,
       4,     4,     8,     3,   257,   259,     3,     8,     4,   429,
     431,     4,   434,     4,     4,   438,   441,     4,     4,     4,
     446,   449,     3,     8,   164,   164,   146,     4,     4,     4,
       4,     4,   183,     4,   149,   149,     4,     4,     4,   147,
     147,   147,   147,     4,     4,     4,     4,     4,     4,     4,
       4,   147,     4,     4,   189,     4,     4,     4,   149,   199,
      76,   179,   227,   307,   333,   376,   378,   380,   406,   407,
     408,   409,   410,     4,     4,     4,     4,     4,     4,     4,
       4,   147,   149,     4,     4,     4,     4,   279,     4,   360,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     375,     4,     4,   147,     4,     4,     4,   149,   319,     4,
     149,   149,   343,     4,     4,   255,   149,     4,     4,   147,
       4,   147,   147,     4,     4,   149,   149,   149,     4,     4,
     426,     4,     7,     7,   164,   164,   164,     7,   146,     7,
       7,     5,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     5,   175,    14,    15,   206,    17,    18,   209,   411,
       8,     3,   146,   146,   146,     5,   166,   168,   146,   146,
     146,    71,    72,    73,   296,   146,     5,     7,   146,   146,
     146,   175,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   164,   146,   146,   146,
      15,   116,   439,   117,   118,   119,   120,   121,   149,   447,
     146,   164,   188,   123,   458,   459,   460,   198,    27,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,   179,
     215,   216,   217,   220,   222,   224,   226,   227,   229,   230,
     231,   232,   233,   235,   215,     7,   272,   273,   274,     7,
     311,   312,   313,     7,   335,   336,   337,     7,   301,   302,
     303,    79,    80,    81,    82,    84,   239,   240,   241,   242,
     243,   244,   245,   292,   404,     7,   248,   249,   250,    91,
      92,    93,    94,    95,    96,   262,   263,   264,   265,   266,
     267,   268,   269,    99,   100,   415,   416,   417,   419,   425,
     176,     4,   408,     7,   353,   354,   355,     7,   367,   368,
     369,    86,   400,     8,   461,     3,     8,     8,   218,   221,
     223,   225,     4,     4,     4,     4,     4,   234,   236,     3,
       8,     8,   275,     6,     3,   314,     6,     3,   338,     6,
       3,   304,     6,     3,     3,     6,     3,     6,   251,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   418,
     420,     3,     8,     8,   146,   177,   178,   146,   356,     6,
       3,   370,     6,     3,   401,     8,     4,   459,     4,     4,
       4,     4,   147,   149,   147,   149,   147,     4,     4,   216,
     278,   274,   317,   313,   341,   337,   179,   190,   191,   192,
     195,   227,   270,   288,   292,   294,   305,   306,   333,   376,
     398,   303,   240,   292,   254,   250,   147,   147,   147,   147,
     147,   147,   263,     4,     4,   416,     6,     3,   359,   355,
     373,   369,     4,     5,    28,    29,    30,    31,   219,   146,
     146,   146,   146,   146,     8,     8,     8,     3,     8,     8,
     146,   146,   146,     8,     8,   146,     7,   462,   463,   306,
     464,     3,     6,   124,   126,   127,   179,   227,   465,   466,
     467,   468,   470,   463,   471,     4,   469,     3,     8,     4,
     147,     4,   466,     5,   146,     7,   472,   473,   474,     3,
       6,   125,   128,   129,   130,   475,   476,   477,   479,   480,
     481,   473,   478,     4,     4,     4,     3,     8,     4,   149,
     147,   147,   476,   146
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
     189,   189,   190,   191,   192,   193,   194,   195,   197,   196,
     198,   198,   199,   199,   199,   199,   201,   200,   203,   202,
     205,   204,   206,   206,   208,   207,   209,   209,   210,   212,
     211,   214,   213,   215,   215,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   218,   217,
     219,   219,   219,   219,   221,   220,   223,   222,   225,   224,
     226,   228,   227,   229,   230,   231,   232,   234,   233,   236,
     235,   238,   237,   239,   239,   240,   240,   240,   240,   240,
     241,   242,   243,   244,   245,   247,   246,   248,   248,   249,
     249,   251,   250,   253,   252,   254,   254,   254,   255,   255,
     257,   256,   259,   258,   261,   260,   262,   262,   263,   263,
     263,   263,   263,   263,   264,   265,   266,   267,   268,   269,
     271,   270,   272,   272,   273,   273,   275,   274,   277,   276,
     278,   278,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   281,   280,   283,   282,   285,   284,   287,
     286,   289,   288,   291,   290,   293,   292,   295,   294,   296,
     296,   296,   297,   298,   300,   299,   301,   301,   302,   302,
     304,   303,   305,   305,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   308,   307,   310,
     309,   311,   311,   312,   312,   314,   313,   316,   315,   317,
     317,   318,   318,   319,   319,   319,   319,   319,   319,   319,
     319,   320,   321,   322,   324,   323,   326,   325,   328,   327,
     329,   331,   330,   332,   334,   333,   335,   335,   336,   336,
     338,   337,   340,   339,   341,   341,   342,   342,   343,   343,
     343,   343,   343,   343,   343,   344,   346,   345,   347,   348,
     349,   350,   352,   351,   353,   353,   354,   354,   356,   355,
     358,   357,   359,   359,   360,   360,   360,   360,   362,   361,
     364,   363,   366,   365,   367,   367,   368,   368,   370,   369,
     372,   371,   373,   373,   374,   374,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   377,
     376,   379,   378,   381,   380,   383,   382,   385,   384,   387,
     386,   389,   388,   391,   390,   393,   392,   395,   394,   397,
     396,   399,   398,   401,   400,   403,   402,   404,   404,   405,
     292,   406,   406,   407,   407,   408,   408,   408,   408,   408,
     408,   408,   408,   409,   411,   410,   412,   414,   413,   415,
     415,   416,   416,   418,   417,   420,   419,   422,   421,   424,
     423,   425,   425,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   427,   429,
     428,   431,   430,   432,   434,   433,   435,   436,   438,   437,
     439,   439,   441,   440,   442,   443,   444,   446,   445,   447,
     447,   447,   447,   447,   449,   448,   451,   450,   453,   452,
     455,   454,   457,   456,   458,   458,   459,   461,   460,   462,
     462,   464,   463,   465,   465,   466,   466,   466,   466,   466,
     467,   469,   468,   471,   470,   472,   472,   474,   473,   475,
     475,   476,   476,   476,   476,   478,   477,   479,   480,   481
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
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
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
     432,   433,   436,   441,   446,   451,   456,   461,   467,   467,
     478,   479,   482,   483,   484,   485,   488,   488,   497,   497,
     507,   507,   514,   515,   518,   518,   525,   527,   531,   537,
     537,   549,   549,   561,   562,   565,   566,   567,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   580,   580,
     587,   588,   589,   590,   593,   593,   601,   601,   609,   609,
     617,   622,   622,   630,   635,   640,   645,   650,   650,   658,
     658,   667,   667,   677,   678,   681,   682,   683,   684,   685,
     688,   693,   698,   703,   708,   713,   713,   723,   724,   727,
     728,   731,   731,   741,   741,   751,   752,   753,   756,   757,
     760,   760,   768,   768,   776,   776,   787,   788,   791,   792,
     793,   794,   795,   796,   799,   804,   809,   814,   819,   824,
     832,   832,   845,   846,   849,   850,   857,   857,   883,   883,
     894,   895,   899,   900,   901,   902,   903,   904,   905,   906,
     907,   908,   909,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   922,   922,   930,   930,   938,   938,   946,
     946,   954,   954,   962,   962,   970,   970,   978,   978,   985,
     986,   987,   990,   995,  1002,  1002,  1013,  1014,  1018,  1019,
    1022,  1022,  1030,  1031,  1034,  1035,  1036,  1037,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1053,  1053,  1066,
    1066,  1075,  1076,  1079,  1080,  1085,  1085,  1100,  1100,  1114,
    1115,  1118,  1119,  1122,  1123,  1124,  1125,  1126,  1127,  1128,
    1129,  1132,  1134,  1139,  1141,  1141,  1149,  1149,  1157,  1157,
    1165,  1167,  1167,  1175,  1184,  1184,  1196,  1197,  1202,  1203,
    1208,  1208,  1220,  1220,  1232,  1233,  1238,  1239,  1244,  1245,
    1246,  1247,  1248,  1249,  1250,  1253,  1255,  1255,  1263,  1265,
    1267,  1272,  1280,  1280,  1292,  1293,  1296,  1297,  1300,  1300,
    1310,  1310,  1320,  1321,  1324,  1325,  1326,  1327,  1330,  1330,
    1338,  1338,  1348,  1348,  1358,  1359,  1362,  1363,  1366,  1366,
    1375,  1375,  1384,  1385,  1388,  1389,  1393,  1394,  1395,  1396,
    1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1408,
    1408,  1416,  1416,  1424,  1424,  1432,  1432,  1440,  1440,  1448,
    1448,  1456,  1456,  1464,  1464,  1472,  1472,  1480,  1480,  1488,
    1488,  1501,  1501,  1511,  1511,  1522,  1522,  1532,  1533,  1536,
    1536,  1546,  1547,  1550,  1551,  1554,  1555,  1556,  1557,  1558,
    1559,  1560,  1561,  1564,  1566,  1566,  1578,  1585,  1585,  1595,
    1596,  1599,  1600,  1603,  1603,  1611,  1611,  1621,  1621,  1633,
    1633,  1643,  1644,  1647,  1648,  1649,  1650,  1651,  1652,  1653,
    1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1664,  1669,
    1669,  1677,  1677,  1685,  1690,  1690,  1698,  1703,  1708,  1708,
    1716,  1717,  1720,  1720,  1728,  1733,  1738,  1743,  1743,  1751,
    1754,  1757,  1760,  1763,  1769,  1769,  1779,  1779,  1786,  1786,
    1793,  1793,  1805,  1805,  1818,  1819,  1823,  1827,  1827,  1839,
    1840,  1844,  1844,  1852,  1853,  1856,  1857,  1858,  1859,  1860,
    1863,  1868,  1868,  1876,  1876,  1886,  1887,  1890,  1890,  1898,
    1899,  1902,  1903,  1904,  1905,  1908,  1908,  1916,  1921,  1926
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
#line 4372 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1931 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
