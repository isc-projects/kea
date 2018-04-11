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
#define yylex   parser6_lex

// First part of user declarations.

#line 39 "dhcp6_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp6_parser.h"

// User implementation prologue.

#line 53 "dhcp6_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:413

#include <dhcp6/parser_context.h>

#line 59 "dhcp6_parser.cc" // lalr1.cc:413


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp6_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 181: // value
      case 185: // map_value
      case 235: // db_type
      case 318: // hr_mode
      case 453: // duid_type
      case 486: // ncr_protocol_value
      case 494: // replace_client_name_value
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

  inline
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 181: // value
      case 185: // map_value
      case 235: // db_type
      case 318: // hr_mode
      case 453: // duid_type
      case 486: // ncr_protocol_value
      case 494: // replace_client_name_value
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
  inline
  void
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
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

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 162: // "integer"

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 163: // "floating point"

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 164: // "boolean"

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 181: // value

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 185: // map_value

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 235: // db_type

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 318: // hr_mode

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 453: // duid_type

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 486: // ncr_protocol_value

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 494: // replace_client_name_value

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp6Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  inline Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::parse ()
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
      case 235: // db_type
      case 318: // hr_mode
      case 453: // duid_type
      case 486: // ncr_protocol_value
      case 494: // replace_client_name_value
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
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 299 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 303 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 321 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 325 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 343 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 347 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1497 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 788 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1575 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 907 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1725 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1040 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1063 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2341 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1793 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1965 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1999 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2005 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3486 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3490 "dhcp6_parser.cc" // lalr1.cc:859
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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp6Parser::yypact_ninf_ = -781;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     435,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,    38,    41,    40,    42,    85,
      92,   101,   107,   108,   116,   124,   128,   146,   158,   174,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,    41,    -2,
      17,    63,    27,   214,    67,   227,   403,   140,    65,   266,
     -41,   454,    64,  -781,   215,   220,   221,   239,   256,  -781,
    -781,  -781,  -781,  -781,   259,  -781,    33,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,   265,   269,   270,
     287,   297,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,   303,  -781,  -781,  -781,    68,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,   306,  -781,   138,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
     315,   321,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,   139,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,   148,  -781,  -781,  -781,  -781,  -781,
     323,  -781,   327,   333,  -781,  -781,  -781,  -781,  -781,  -781,
     152,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,   290,   348,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,   310,  -781,
    -781,   359,  -781,  -781,  -781,   367,  -781,  -781,   357,   370,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,   373,   374,  -781,  -781,  -781,  -781,   372,
     379,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,   172,  -781,  -781,  -781,   381,  -781,  -781,
     385,  -781,   388,   389,  -781,  -781,   394,   395,   397,  -781,
    -781,  -781,  -781,  -781,   219,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,   233,  -781,  -781,  -781,    41,    41,  -781,   222,   399,
     402,   404,   405,   406,  -781,    17,  -781,   407,   409,   411,
     412,   228,   245,   255,   258,   267,   414,   417,   428,   429,
     430,   431,   432,   433,   436,   437,   438,   439,   440,   277,
     441,   442,    63,  -781,   446,   289,    27,  -781,   452,   453,
     455,   459,   464,   296,   305,   466,   467,   468,   469,   470,
     214,  -781,   472,    67,  -781,   473,   316,   477,   320,   331,
     227,  -781,   479,   481,   488,   490,   491,   492,   493,  -781,
     403,  -781,   494,   495,   338,   500,   501,   502,   343,  -781,
      65,   504,   345,   347,  -781,   266,   508,   509,   -28,  -781,
     355,   510,   511,   356,   516,   360,   362,   517,   519,   366,
     368,   369,   521,   522,   454,  -781,   527,    64,  -781,  -781,
    -781,   530,   529,   531,    41,    41,    41,  -781,   532,   533,
     534,   537,  -781,  -781,  -781,  -781,  -781,   538,   539,   540,
     542,   376,   541,   545,   546,   547,   548,   550,   549,   551,
    -781,   552,   553,  -781,   556,  -781,  -781,   557,   558,   396,
     443,   444,  -781,  -781,   -15,   556,   445,   591,   590,  -781,
     447,  -781,   448,  -781,   449,  -781,  -781,  -781,   556,   556,
     556,   450,   451,   456,   457,  -781,   458,   460,  -781,   461,
     462,   463,  -781,  -781,   465,  -781,  -781,  -781,   471,    41,
    -781,  -781,   474,   475,  -781,   476,  -781,  -781,   -45,   483,
    -781,  -781,  -781,   -73,   478,  -781,   593,  -781,    41,    63,
      64,  -781,  -781,  -781,    27,   184,   184,   592,   594,   595,
     596,  -781,  -781,  -781,   600,   -52,    41,    99,   607,   609,
     135,   132,    32,   454,  -781,  -781,   613,   618,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,   620,   543,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,   621,  -781,   247,   253,   254,  -781,  -781,  -781,  -781,
     625,   626,   627,   630,   634,  -781,   636,   637,  -781,   638,
     639,   640,  -781,   257,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,   264,  -781,   641,   597,  -781,  -781,   642,   643,
    -781,  -781,   644,   646,  -781,  -781,   645,   649,  -781,  -781,
     647,   651,  -781,  -781,  -781,    90,  -781,  -781,  -781,   650,
    -781,  -781,  -781,   118,  -781,  -781,  -781,  -781,   171,  -781,
    -781,   652,   654,  -781,   655,   656,   657,   658,   659,   660,
     291,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
     661,   662,   663,  -781,  -781,  -781,  -781,   301,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,   314,
    -781,  -781,  -781,   318,   484,  -781,   664,   665,  -781,  -781,
     666,   668,  -781,  -781,   667,   671,  -781,  -781,   669,  -781,
     243,  -781,  -781,  -781,  -781,   672,   674,   675,   676,   507,
     518,   513,   520,   523,   677,   524,   525,   679,   526,   528,
     535,   184,  -781,  -781,   184,  -781,   592,   214,  -781,   594,
      65,  -781,   595,   266,  -781,   596,   386,  -781,   600,   -52,
    -781,  -781,    99,  -781,    18,   607,  -781,   -41,  -781,   609,
     536,   544,   554,   560,   562,   563,   135,  -781,   685,   687,
     565,   567,   574,   132,  -781,   688,   689,    32,  -781,  -781,
    -781,   690,   691,    67,  -781,   613,   227,  -781,   618,   403,
    -781,   620,   693,  -781,   105,   621,  -781,   178,   577,   578,
     583,  -781,  -781,  -781,  -781,  -781,   584,  -781,  -781,   586,
    -781,  -781,  -781,  -781,   330,  -781,   336,  -781,   692,  -781,
     694,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,   340,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,   697,  -781,  -781,  -781,  -781,
    -781,   695,   701,  -781,  -781,  -781,  -781,  -781,   344,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,   293,   587,  -781,
    -781,  -781,  -781,   589,   604,  -781,  -781,   606,   350,  -781,
     351,  -781,   699,  -781,   610,  -781,   704,  -781,  -781,  -781,
    -781,  -781,   354,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,   386,  -781,   705,   555,  -781,    18,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,   706,   599,   707,   105,  -781,  -781,   611,  -781,  -781,
     700,  -781,   612,  -781,  -781,   648,  -781,  -781,   294,  -781,
      28,   648,  -781,  -781,   708,   709,   710,   361,  -781,  -781,
    -781,  -781,  -781,  -781,   711,   614,   615,   623,    28,  -781,
     619,  -781,  -781,  -781,  -781,  -781
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   107,     9,   241,    11,
     386,    13,   411,    15,   441,    17,   311,    19,   319,    21,
     356,    23,   206,    25,   536,    27,   593,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   443,     0,   321,   358,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     591,   585,   587,   589,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   105,   119,   121,   123,     0,     0,     0,
       0,     0,   233,   309,   348,   399,   401,   282,   179,   196,
     187,   476,   198,   217,   497,     0,   521,   534,    99,     0,
      72,    74,    75,    76,    77,    78,    81,    82,    83,    84,
      85,    87,    86,    91,    92,    79,    80,    89,    90,    97,
      98,    88,    93,    94,    95,    96,   116,     0,   115,     0,
     109,   111,   112,   113,   114,   378,   403,   265,   267,   269,
       0,     0,   275,   273,   271,   433,   472,   264,   245,   246,
     247,   248,     0,   243,   252,   253,   254,   257,   258,   260,
     255,   256,   249,   250,   262,   263,   251,   259,   261,   397,
     396,   392,   393,   391,     0,   388,   390,   394,   395,   426,
       0,   429,     0,     0,   425,   419,   420,   418,   423,   424,
       0,   413,   415,   416,   421,   422,   417,   470,   458,   460,
     462,   464,   466,   468,   457,   454,   455,   456,     0,   444,
     445,   449,   450,   447,   451,   452,   453,   448,     0,   338,
     164,     0,   342,   340,   345,     0,   334,   335,     0,   322,
     323,   325,   337,   326,   327,   328,   344,   329,   330,   331,
     332,   333,   372,     0,     0,   370,   371,   374,   375,     0,
     359,   360,   362,   363,   364,   365,   366,   367,   368,   369,
     213,   215,   210,     0,   208,   211,   212,     0,   558,   560,
       0,   563,     0,     0,   567,   571,     0,     0,     0,   576,
     583,   556,   554,   555,     0,   538,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     598,     0,   595,   597,    46,     0,     0,    39,     0,     0,
       0,     0,     0,     0,    57,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,     0,     0,     0,   108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   242,     0,     0,   387,     0,     0,     0,     0,     0,
       0,   412,     0,     0,     0,     0,     0,     0,     0,   442,
       0,   312,     0,     0,     0,     0,     0,     0,     0,   320,
       0,     0,     0,     0,   357,     0,     0,     0,     0,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   537,     0,     0,   594,    50,
      43,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,   100,   101,   102,   103,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     520,     0,     0,    73,     0,   118,   110,     0,     0,     0,
       0,     0,   280,   281,     0,     0,     0,     0,     0,   244,
       0,   389,     0,   428,     0,   431,   432,   414,     0,     0,
       0,     0,     0,     0,     0,   446,     0,     0,   336,     0,
       0,     0,   347,   324,     0,   376,   377,   361,     0,     0,
     209,   557,     0,     0,   562,     0,   565,   566,     0,     0,
     573,   574,   575,     0,     0,   539,     0,   596,     0,     0,
       0,   586,   588,   590,     0,     0,     0,   125,   235,   313,
     350,    40,   400,   402,   284,     0,    47,     0,     0,   200,
       0,     0,     0,     0,    51,   117,   380,   405,   266,   268,
     270,   277,   278,   279,   276,   274,   272,   435,     0,   398,
     427,   430,   471,   459,   461,   463,   465,   467,   469,   339,
     165,   343,   341,   346,   373,   214,   216,   559,   561,   564,
     569,   570,   568,   572,   578,   579,   580,   581,   582,   577,
     584,     0,    44,     0,     0,     0,   151,   157,   159,   161,
       0,     0,     0,     0,     0,   174,     0,     0,   177,     0,
       0,     0,   150,     0,   131,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   145,   146,   147,   148,   143,
     144,   149,     0,   129,     0,   126,   127,   239,     0,   236,
     237,   317,     0,   314,   315,   354,     0,   351,   352,   288,
       0,   285,   286,   185,   186,     0,   181,   183,   184,     0,
     194,   195,   191,     0,   189,   192,   193,   480,     0,   478,
     204,     0,   201,   202,     0,     0,     0,     0,     0,     0,
       0,   219,   221,   222,   223,   224,   225,   226,   510,   516,
       0,     0,     0,   509,   506,   507,   508,     0,   499,   501,
     504,   502,   503,   505,   530,   532,   529,   527,   528,     0,
     523,   525,   526,     0,    53,   384,     0,   381,   382,   409,
       0,   406,   407,   439,     0,   436,   437,   474,     0,   602,
       0,   600,    69,   592,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,   122,     0,   124,     0,     0,   234,     0,
     321,   310,     0,   358,   349,     0,     0,   283,     0,     0,
     180,   197,     0,   188,   482,     0,   477,     0,   199,     0,
       0,     0,     0,     0,     0,     0,     0,   218,     0,     0,
       0,     0,     0,     0,   498,     0,     0,     0,   522,   535,
      55,     0,    54,     0,   379,     0,     0,   404,     0,   443,
     434,     0,     0,   473,     0,     0,   599,     0,     0,     0,
       0,   163,   166,   167,   168,   169,     0,   176,   170,     0,
     171,   172,   173,   132,     0,   128,     0,   238,     0,   316,
       0,   353,   308,   303,   305,   296,   297,   292,   293,   294,
     295,   301,   302,   300,   304,     0,   290,   298,   306,   307,
     299,   287,   182,   190,   494,     0,   492,   493,   489,   490,
     491,     0,   483,   484,   486,   487,   488,   479,     0,   203,
     227,   228,   229,   230,   231,   232,   220,     0,     0,   515,
     518,   519,   500,     0,     0,   524,    52,     0,     0,   383,
       0,   408,     0,   438,     0,   616,     0,   614,   612,   606,
     610,   611,     0,   604,   608,   609,   607,   601,   153,   154,
     155,   156,   152,   158,   160,   162,   175,   178,   130,   240,
     318,   355,     0,   289,     0,     0,   481,     0,   205,   512,
     513,   514,   511,   517,   531,   533,    56,   385,   410,   440,
     475,     0,     0,     0,     0,   603,   291,     0,   496,   485,
       0,   613,     0,   605,   495,     0,   615,   620,     0,   618,
       0,     0,   617,   628,     0,     0,     0,     0,   622,   624,
     625,   626,   627,   619,     0,     0,     0,     0,     0,   621,
       0,   630,   631,   632,   623,   629
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,     6,  -781,   225,  -781,
    -781,  -781,  -781,  -781,  -781,   185,  -781,  -376,  -781,  -781,
    -781,   -70,  -781,  -781,  -781,   410,  -781,  -781,  -781,  -781,
     169,   382,   -66,   -56,   -55,   -54,  -781,  -781,  -781,  -781,
    -781,   204,   392,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,   -10,  -781,  -541,     1,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,   -34,  -781,
    -559,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,   -13,  -554,  -781,  -781,
    -781,  -781,   -14,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,   -18,  -781,  -781,  -781,   -11,   365,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,   -22,  -781,  -781,  -781,  -781,  -781,
    -781,  -780,  -781,  -781,  -781,     8,  -781,  -781,  -781,    15,
     413,  -781,  -781,  -776,  -781,  -773,  -781,   -32,  -781,   -21,
    -781,  -772,  -781,  -781,  -781,  -771,  -781,  -781,  -781,  -781,
       7,  -781,  -781,  -156,   730,  -781,  -781,  -781,  -781,  -781,
      19,  -781,  -781,  -781,    23,  -781,   398,  -781,   -65,  -781,
    -781,  -781,  -781,  -781,   -58,  -781,  -781,  -781,  -781,  -781,
      12,  -781,  -781,  -781,    14,  -781,  -781,  -781,    21,  -781,
     400,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,   -16,  -781,  -781,  -781,    -9,   427,  -781,  -781,
     -44,  -781,    -6,  -781,  -781,  -781,  -781,  -781,   -12,  -781,
    -781,  -781,    -8,   422,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,    -7,  -781,  -781,  -781,    -4,
    -781,   419,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -770,  -781,  -781,  -781,
    -781,  -781,  -781,    26,  -781,  -781,  -781,  -144,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,     9,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,    10,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,   263,   408,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,  -781,
    -781,  -781,   292,   393,  -781,  -781,  -781,    -1,  -781,  -781,
    -145,  -781,  -781,  -781,  -781,  -781,  -781,  -160,  -781,  -781,
    -175,  -781,  -781,  -781,  -781,  -781
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     562,    87,    88,    41,    68,    84,    85,   575,   744,   831,
     832,   642,    43,    70,    96,    97,    98,   339,    45,    71,
     129,   130,   131,   132,   133,   134,   135,   136,   347,    47,
      72,   159,   160,   161,   374,   162,   137,   348,   138,   349,
     139,   350,   664,   665,   666,   784,   643,   644,   645,   765,
     952,   646,   766,   647,   767,   648,   768,   649,   650,   413,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   774,
     660,   661,   777,   140,   362,   685,   686,   687,   688,   141,
     364,   693,   694,   695,   696,   142,   363,   143,   366,   701,
     702,   703,   807,    63,    80,   293,   294,   295,   426,   296,
     427,   144,   367,   710,   711,   712,   713,   714,   715,   716,
     717,   145,   356,   668,   669,   670,   787,    49,    73,   182,
     183,   184,   380,   185,   381,   186,   382,   187,   387,   188,
     386,   189,   385,   584,   190,   191,   146,   361,   680,   681,
     682,   796,   885,   886,   147,   357,    57,    77,   672,   673,
     674,   790,    59,    78,   258,   259,   260,   261,   262,   263,
     264,   412,   265,   416,   266,   415,   267,   268,   417,   269,
     148,   358,   676,   677,   678,   793,    61,    79,   279,   280,
     281,   282,   283,   421,   284,   285,   286,   287,   193,   378,
     746,   747,   748,   833,    51,    74,   204,   205,   206,   392,
     149,   359,   150,   360,   196,   379,   750,   751,   752,   836,
      53,    75,   220,   221,   222,   395,   223,   224,   397,   225,
     226,   197,   388,   754,   755,   756,   839,    55,    76,   238,
     239,   240,   241,   403,   242,   404,   243,   405,   244,   406,
     245,   407,   246,   408,   247,   402,   198,   389,   758,   842,
     151,   365,   698,   699,   804,   901,   902,   903,   904,   905,
     964,   906,   152,   368,   727,   728,   729,   818,   972,   730,
     731,   819,   732,   733,   153,   154,   370,   739,   740,   741,
     825,   742,   826,   155,   371,    65,    81,   314,   315,   316,
     317,   431,   318,   432,   319,   320,   434,   321,   322,   323,
     437,   612,   324,   438,   325,   326,   327,   328,   442,   619,
     329,   443,    99,   341,   100,   342,   101,   343,   102,   340,
      67,    82,   331,   332,   333,   446,   760,   761,   844,   942,
     943,   944,   945,   983,   946,   981,   998,   999,  1000,  1007,
    1008,  1009,  1014,  1010,  1011,  1012
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   128,   158,   177,   200,   214,   234,   178,   256,   275,
     292,   311,   724,   692,   277,   662,   878,   179,   180,   181,
     879,   278,    38,   880,   883,   884,   890,    89,   163,   194,
     207,   218,   236,   683,   270,   288,   345,   312,    30,   156,
     157,   346,   201,   215,   257,   276,    31,    42,    32,    44,
      33,   290,   291,   202,   216,   581,   582,   583,   614,   615,
     616,   617,   114,   250,   290,   291,   164,   195,   208,   219,
     237,   372,   271,   289,   103,   313,   373,   104,   105,   106,
     115,   116,   249,   610,   611,   192,   203,   217,   235,   115,
     116,   618,    46,   799,   115,   116,   800,   894,   895,    48,
     107,   108,   109,   110,   111,   112,   113,   114,    50,   684,
     250,   114,   251,   252,    52,    54,   253,   254,   255,   585,
      94,   802,   199,    56,   803,   115,   116,   115,   116,   115,
     116,    58,   592,   593,   594,    60,   117,   118,   119,   120,
     121,   376,   390,   734,   735,   173,   377,   391,   174,   718,
     250,   393,    90,    62,   122,   400,   394,   123,   631,    86,
     401,    91,    92,    93,   124,    64,  1003,   115,   116,  1004,
    1005,  1006,   125,   126,   805,   428,   127,   806,    94,    94,
     429,    66,   878,   113,   683,   690,   879,   691,    94,   880,
     883,   884,   890,    94,   115,   116,   948,   949,   950,   951,
     330,   626,    34,    35,    36,    37,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   334,   444,   335,    94,   336,    94,   445,    94,   250,
     704,   705,   706,   707,   708,   709,   447,   719,   720,   721,
     722,   448,   935,   864,   936,   937,   845,   337,   692,   846,
     372,   107,   108,   109,   110,   762,   447,   376,   114,   338,
     781,   763,   764,   344,   724,   782,    94,   781,   165,   351,
     166,   114,   783,   352,   353,    95,   115,   116,   167,   168,
     169,   170,   171,   172,   209,   210,   211,   212,   213,   115,
     116,   354,   173,    94,   816,   174,   175,  1001,   409,   817,
    1002,   355,   128,   176,   823,   173,   158,   369,   174,   824,
     375,   250,   272,   251,   252,   273,   274,   827,   411,   383,
     177,   444,   828,   200,   178,   384,   829,   396,   115,   116,
     214,   398,   163,   781,   179,   180,   181,   399,   958,   390,
     234,   449,   450,   962,   959,    94,   194,   428,   963,   207,
     256,   410,   968,   393,   400,   275,   218,   984,   977,   978,
     277,   201,   985,   414,  1018,   419,   236,   278,   215,  1019,
     164,   418,   202,   420,   311,    94,   270,   422,   423,   216,
     424,   288,   425,   451,   195,   430,   257,   208,    94,   433,
     462,   276,   435,   436,   219,   969,   970,   971,   439,   440,
     312,   441,   192,   452,   237,   203,   453,   463,   454,   455,
     456,   458,   217,   459,   271,   460,   461,   464,   467,   289,
     465,   468,   235,   107,   108,   109,   110,    94,   112,   466,
     114,   250,   469,   470,   471,   472,   473,   474,   313,   480,
     475,   476,   477,   478,   479,   481,   482,   114,   115,   116,
     484,   168,   169,   485,   171,   172,   487,   488,   492,   489,
     551,   552,   553,   490,   173,   115,   116,   174,   491,   493,
     494,   495,   496,   497,   498,   176,   500,   502,   503,   128,
     227,   504,   505,   508,   158,   509,   228,   229,   230,   231,
     232,   233,   510,   506,   511,   512,   513,   514,   516,   517,
     518,   723,   736,   311,   519,   520,   521,   522,   524,   525,
     163,   526,   528,   529,   532,   533,   115,   116,   534,   531,
     535,   538,   536,   539,   537,   543,   544,   725,   737,   312,
     540,   546,   541,   542,   548,   606,   549,   563,   550,   554,
     555,   556,   557,   558,   559,   560,   564,    94,   164,    32,
     565,   566,   567,   568,   622,   569,   570,   578,   571,   572,
     573,   574,   576,   577,    94,   726,   738,   313,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   587,   588,   621,   663,
     786,   667,   671,   675,   579,   580,   586,   679,   589,   590,
     591,   595,   596,   613,   697,    94,   700,   597,   598,   599,
     745,   600,   601,   602,   603,   749,   604,   753,   759,   769,
     770,   771,   605,   757,   772,   607,   608,   609,   773,   620,
     775,   776,   778,   779,   780,   830,   789,   785,   788,   792,
     791,   794,   795,   797,   798,   997,   801,   809,   808,   810,
     811,   812,   813,   814,   815,   820,   821,   822,   835,   851,
     834,   838,   837,   840,   841,   853,   847,   843,   848,   849,
     850,   856,   852,   859,   854,   855,   857,   858,   860,   917,
     861,   918,   923,   924,   927,   561,   926,   934,   910,   862,
     960,   965,   961,   966,   967,   995,   911,   979,   982,   987,
     990,   992,  1015,  1016,  1017,  1020,   912,   177,   623,   988,
     256,   178,   913,   275,   914,   915,   872,   919,   277,   920,
     873,   179,   180,   181,   896,   278,   921,   292,   953,   954,
     874,   875,   876,   194,   955,   956,   270,   957,   973,   288,
     974,   689,   888,   723,   483,   457,   257,   736,   625,   276,
     899,   991,   877,   200,   881,   975,   214,   976,   486,   234,
     897,   980,   994,   996,   938,   882,   865,  1022,  1021,   725,
    1025,   195,   863,   737,   271,  1023,   892,   289,   893,   207,
     889,   909,   218,   530,   916,   236,   908,   867,   900,   192,
     940,   201,   866,   499,   215,   891,   986,   248,   887,   871,
     939,   869,   202,   868,   870,   216,   898,   726,   523,   929,
     501,   738,   507,   989,   928,   527,   931,   208,   930,   515,
     219,   907,   922,   237,   933,   932,   743,   925,   941,   993,
     547,  1013,   624,  1024,   947,   203,     0,     0,   217,     0,
       0,   235,   545,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   872,     0,     0,     0,   873,   896,     0,     0,
       0,     0,     0,     0,     0,     0,   874,   875,   876,     0,
       0,     0,     0,     0,   938,     0,     0,     0,   888,     0,
       0,     0,     0,   899,     0,     0,     0,     0,   877,     0,
     881,     0,     0,   897,     0,     0,     0,     0,     0,     0,
     940,   882,     0,     0,     0,     0,     0,     0,     0,     0,
     939,     0,     0,     0,     0,     0,   889,     0,     0,     0,
       0,   900,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   887,     0,     0,     0,   941,   898
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    73,    78,    79,
      80,    81,   571,   567,    79,   556,   796,    73,    73,    73,
     796,    79,    16,   796,   796,   796,   796,    10,    72,    73,
      74,    75,    76,    85,    78,    79,     3,    81,     0,    12,
      13,     8,    74,    75,    78,    79,     5,     7,     7,     7,
       9,    92,    93,    74,    75,    70,    71,    72,   131,   132,
     133,   134,    44,    45,    92,    93,    72,    73,    74,    75,
      76,     3,    78,    79,    11,    81,     8,    14,    15,    16,
      62,    63,    17,   128,   129,    73,    74,    75,    76,    62,
      63,   164,     7,     3,    62,    63,     6,    79,    80,     7,
      37,    38,    39,    40,    41,    42,    43,    44,     7,   161,
      45,    44,    47,    48,     7,     7,    51,    52,    53,   495,
     161,     3,    55,     7,     6,    62,    63,    62,    63,    62,
      63,     7,   508,   509,   510,     7,    73,    74,    75,    76,
      77,     3,     3,   111,   112,    78,     8,     8,    81,    17,
      45,     3,   135,     7,    91,     3,     8,    94,    26,   161,
       8,   144,   145,   146,   101,     7,   138,    62,    63,   141,
     142,   143,   109,   110,     3,     3,   113,     6,   161,   161,
       8,     7,   962,    43,    85,    86,   962,    88,   161,   962,
     962,   962,   962,   161,    62,    63,    18,    19,    20,    21,
     136,    17,   161,   162,   163,   164,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,     6,     3,     3,   161,     4,   161,     8,   161,    45,
      95,    96,    97,    98,    99,   100,     3,   105,   106,   107,
     108,     8,   137,   784,   139,   140,     3,     8,   802,     6,
       3,    37,    38,    39,    40,     8,     3,     3,    44,     3,
       3,     8,     8,     4,   823,     8,   161,     3,    54,     4,
      56,    44,     8,     4,     4,   345,    62,    63,    64,    65,
      66,    67,    68,    69,    57,    58,    59,    60,    61,    62,
      63,     4,    78,   161,     3,    81,    82,     3,     8,     8,
       6,     4,   372,    89,     3,    78,   376,     4,    81,     8,
       4,    45,    46,    47,    48,    49,    50,     3,     8,     4,
     390,     3,     8,   393,   390,     4,     8,     4,    62,    63,
     400,     4,   376,     3,   390,   390,   390,     4,     8,     3,
     410,   335,   336,     3,     8,   161,   390,     3,     8,   393,
     420,     3,     8,     3,     3,   425,   400,     3,     8,     8,
     425,   393,     8,     4,     3,     8,   410,   425,   400,     8,
     376,     4,   393,     3,   444,   161,   420,     4,     4,   400,
       8,   425,     3,   161,   390,     4,   420,   393,   161,     4,
     162,   425,     4,     4,   400,   102,   103,   104,     4,     4,
     444,     4,   390,     4,   410,   393,     4,   162,     4,     4,
       4,     4,   400,     4,   420,     4,     4,   162,     4,   425,
     162,     4,   410,    37,    38,    39,    40,   161,    42,   162,
      44,    45,     4,     4,     4,     4,     4,     4,   444,   162,
       4,     4,     4,     4,     4,     4,     4,    44,    62,    63,
       4,    65,    66,   164,    68,    69,     4,     4,   162,     4,
     454,   455,   456,     4,    78,    62,    63,    81,     4,   164,
       4,     4,     4,     4,     4,    89,     4,     4,   162,   549,
      77,     4,   162,     4,   554,     4,    83,    84,    85,    86,
      87,    88,     4,   162,     4,     4,     4,     4,     4,     4,
     162,   571,   572,   573,     4,     4,     4,   164,     4,   164,
     554,   164,     4,     4,     4,     4,    62,    63,   162,   164,
       4,     4,   162,     4,   162,     4,     4,   571,   572,   573,
     164,     4,   164,   164,     4,   529,     7,   161,     7,     7,
       7,     7,     5,     5,     5,     5,     5,   161,   554,     7,
       5,     5,     5,     5,   548,     5,     7,   161,     7,     7,
       7,     5,     5,     5,   161,   571,   572,   573,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,     5,     7,     5,     7,
       3,     7,     7,     7,   161,   161,   161,     7,   161,   161,
     161,   161,   161,   130,     7,   161,     7,   161,   161,   161,
       7,   161,   161,   161,   161,     7,   161,     7,     7,     4,
       4,     4,   161,    90,     4,   161,   161,   161,     4,   161,
       4,     4,     4,     4,     4,   161,     3,     6,     6,     3,
       6,     6,     3,     6,     3,     7,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   162,
       6,     3,     6,     6,     3,   162,     4,     8,     4,     4,
       4,     4,   164,     4,   164,   162,   162,   162,   162,     4,
     162,     4,     4,     4,     3,   470,     6,     4,   162,   164,
       8,     4,     8,     8,     3,     5,   162,     8,     4,     4,
       4,     4,     4,     4,     4,     4,   162,   787,   549,   164,
     790,   787,   162,   793,   162,   162,   796,   162,   793,   162,
     796,   787,   787,   787,   804,   793,   162,   807,   161,   161,
     796,   796,   796,   787,   161,   161,   790,   161,   161,   793,
     161,   566,   796,   823,   372,   345,   790,   827,   554,   793,
     804,   162,   796,   833,   796,   161,   836,   161,   376,   839,
     804,   161,   161,   161,   844,   796,   786,   162,   164,   823,
     161,   787,   781,   827,   790,   162,   799,   793,   802,   833,
     796,   809,   836,   428,   816,   839,   807,   789,   804,   787,
     844,   833,   787,   390,   836,   798,   962,    77,   796,   795,
     844,   792,   833,   790,   793,   836,   804,   823,   420,   835,
     393,   827,   400,   967,   833,   425,   838,   833,   836,   410,
     836,   805,   823,   839,   841,   839,   573,   827,   844,   984,
     447,  1001,   550,  1018,   845,   833,    -1,    -1,   836,    -1,
      -1,   839,   444,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   962,    -1,    -1,    -1,   962,   967,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   962,   962,   962,    -1,
      -1,    -1,    -1,    -1,   984,    -1,    -1,    -1,   962,    -1,
      -1,    -1,    -1,   967,    -1,    -1,    -1,    -1,   962,    -1,
     962,    -1,    -1,   967,    -1,    -1,    -1,    -1,    -1,    -1,
     984,   962,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     984,    -1,    -1,    -1,    -1,    -1,   962,    -1,    -1,    -1,
      -1,   967,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   962,    -1,    -1,    -1,   984,   967
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
       0,     5,     7,     9,   161,   162,   163,   164,   181,   182,
     183,   188,     7,   197,     7,   203,     7,   214,     7,   302,
       7,   379,     7,   395,     7,   412,     7,   331,     7,   337,
       7,   361,     7,   278,     7,   470,     7,   505,   189,   184,
     198,   204,   215,   303,   380,   396,   413,   332,   338,   362,
     279,   471,   506,   181,   190,   191,   161,   186,   187,    10,
     135,   144,   145,   146,   161,   196,   199,   200,   201,   497,
     499,   501,   503,    11,    14,    15,    16,    37,    38,    39,
      40,    41,    42,    43,    44,    62,    63,    73,    74,    75,
      76,    77,    91,    94,   101,   109,   110,   113,   196,   205,
     206,   207,   208,   209,   210,   211,   212,   221,   223,   225,
     258,   264,   270,   272,   286,   296,   321,   329,   355,   385,
     387,   435,   447,   459,   460,   468,    12,    13,   196,   216,
     217,   218,   220,   385,   387,    54,    56,    64,    65,    66,
      67,    68,    69,    78,    81,    82,    89,   196,   207,   208,
     209,   210,   304,   305,   306,   308,   310,   312,   314,   316,
     319,   320,   355,   373,   385,   387,   389,   406,   431,    55,
     196,   312,   314,   355,   381,   382,   383,   385,   387,    57,
      58,    59,    60,    61,   196,   312,   314,   355,   385,   387,
     397,   398,   399,   401,   402,   404,   405,    77,    83,    84,
      85,    86,    87,    88,   196,   355,   385,   387,   414,   415,
     416,   417,   419,   421,   423,   425,   427,   429,   329,    17,
      45,    47,    48,    51,    52,    53,   196,   243,   339,   340,
     341,   342,   343,   344,   345,   347,   349,   351,   352,   354,
     385,   387,    46,    49,    50,   196,   243,   343,   349,   363,
     364,   365,   366,   367,   369,   370,   371,   372,   385,   387,
      92,    93,   196,   280,   281,   282,   284,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   196,   385,   387,   472,   473,   474,   475,   477,   479,
     480,   482,   483,   484,   487,   489,   490,   491,   492,   495,
     136,   507,   508,   509,     6,     3,     4,     8,     3,   202,
     504,   498,   500,   502,     4,     3,     8,   213,   222,   224,
     226,     4,     4,     4,     4,     4,   297,   330,   356,   386,
     388,   322,   259,   271,   265,   436,   273,   287,   448,     4,
     461,   469,     3,     8,   219,     4,     3,     8,   374,   390,
     307,   309,   311,     4,     4,   317,   315,   313,   407,   432,
       3,     8,   384,     3,     8,   400,     4,   403,     4,     4,
       3,     8,   430,   418,   420,   422,   424,   426,   428,     8,
       3,     8,   346,   244,     4,   350,   348,   353,     4,     8,
       3,   368,     4,     4,     8,     3,   283,   285,     3,     8,
       4,   476,   478,     4,   481,     4,     4,   485,   488,     4,
       4,     4,   493,   496,     3,     8,   510,     3,     8,   181,
     181,   161,     4,     4,     4,     4,     4,   200,     4,     4,
       4,     4,   162,   162,   162,   162,   162,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     162,     4,     4,   206,     4,   164,   217,     4,     4,     4,
       4,     4,   162,   164,     4,     4,     4,     4,     4,   305,
       4,   382,     4,   162,     4,   162,   162,   398,     4,     4,
       4,     4,     4,     4,     4,   416,     4,     4,   162,     4,
       4,     4,   164,   341,     4,   164,   164,   365,     4,     4,
     281,   164,     4,     4,   162,     4,   162,   162,     4,     4,
     164,   164,   164,     4,     4,   473,     4,   508,     4,     7,
       7,   181,   181,   181,     7,     7,     7,     5,     5,     5,
       5,   183,   185,   161,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   192,     5,     5,   161,   161,
     161,    70,    71,    72,   318,   192,   161,     5,     7,   161,
     161,   161,   192,   192,   192,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   181,   161,   161,   161,
     128,   129,   486,   130,   131,   132,   133,   134,   164,   494,
     161,     5,   181,   205,   507,   216,    17,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   196,   231,   232,   233,   236,   238,   240,   242,
     243,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     255,   256,   231,     7,   227,   228,   229,     7,   298,   299,
     300,     7,   333,   334,   335,     7,   357,   358,   359,     7,
     323,   324,   325,    85,   161,   260,   261,   262,   263,   190,
      86,    88,   262,   266,   267,   268,   269,     7,   437,   438,
       7,   274,   275,   276,    95,    96,    97,    98,    99,   100,
     288,   289,   290,   291,   292,   293,   294,   295,    17,   105,
     106,   107,   108,   196,   245,   385,   387,   449,   450,   451,
     454,   455,   457,   458,   111,   112,   196,   385,   387,   462,
     463,   464,   466,   472,   193,     7,   375,   376,   377,     7,
     391,   392,   393,     7,   408,   409,   410,    90,   433,     7,
     511,   512,     8,     8,     8,   234,   237,   239,   241,     4,
       4,     4,     4,     4,   254,     4,     4,   257,     4,     4,
       4,     3,     8,     8,   230,     6,     3,   301,     6,     3,
     336,     6,     3,   360,     6,     3,   326,     6,     3,     3,
       6,     6,     3,     6,   439,     3,     6,   277,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   452,   456,
       4,     4,     4,     3,     8,   465,   467,     3,     8,     8,
     161,   194,   195,   378,     6,     3,   394,     6,     3,   411,
       6,     3,   434,     8,   513,     3,     6,     4,     4,     4,
       4,   162,   164,   162,   164,   162,     4,   162,   162,     4,
     162,   162,   164,   232,   231,   229,   304,   300,   339,   335,
     363,   359,   196,   207,   208,   209,   210,   243,   296,   308,
     310,   312,   314,   316,   320,   327,   328,   355,   385,   387,
     431,   325,   261,   267,    79,    80,   196,   243,   355,   385,
     387,   440,   441,   442,   443,   444,   446,   438,   280,   276,
     162,   162,   162,   162,   162,   162,   289,     4,     4,   162,
     162,   162,   450,     4,     4,   463,     6,     3,   381,   377,
     397,   393,   414,   410,     4,   137,   139,   140,   196,   243,
     385,   387,   514,   515,   516,   517,   519,   512,    18,    19,
      20,    21,   235,   161,   161,   161,   161,   161,     8,     8,
       8,     8,     3,     8,   445,     4,     8,     3,     8,   102,
     103,   104,   453,   161,   161,   161,   161,     8,     8,     8,
     161,   520,     4,   518,     3,     8,   328,     4,   164,   442,
       4,   162,     4,   515,   161,     5,   161,     7,   521,   522,
     523,     3,     6,   138,   141,   142,   143,   524,   525,   526,
     528,   529,   530,   522,   527,     4,     4,     4,     3,     8,
       4,   164,   162,   162,   525,   161
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   165,   167,   166,   168,   166,   169,   166,   170,   166,
     171,   166,   172,   166,   173,   166,   174,   166,   175,   166,
     176,   166,   177,   166,   178,   166,   179,   166,   180,   166,
     181,   181,   181,   181,   181,   181,   181,   182,   184,   183,
     185,   186,   186,   187,   187,   189,   188,   190,   190,   191,
     191,   193,   192,   194,   194,   195,   195,   196,   198,   197,
     199,   199,   200,   200,   200,   200,   200,   200,   202,   201,
     204,   203,   205,   205,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     207,   208,   209,   210,   211,   213,   212,   215,   214,   216,
     216,   217,   217,   217,   217,   217,   219,   218,   220,   222,
     221,   224,   223,   226,   225,   227,   227,   228,   228,   230,
     229,   231,   231,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   234,   233,   235,   235,   235,   235,   237,   236,   239,
     238,   241,   240,   242,   244,   243,   245,   246,   247,   248,
     249,   250,   251,   252,   254,   253,   255,   257,   256,   259,
     258,   260,   260,   261,   261,   262,   263,   265,   264,   266,
     266,   267,   267,   267,   268,   269,   271,   270,   273,   272,
     274,   274,   275,   275,   277,   276,   279,   278,   280,   280,
     280,   281,   281,   283,   282,   285,   284,   287,   286,   288,
     288,   289,   289,   289,   289,   289,   289,   290,   291,   292,
     293,   294,   295,   297,   296,   298,   298,   299,   299,   301,
     300,   303,   302,   304,   304,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   307,   306,   309,   308,   311,
     310,   313,   312,   315,   314,   317,   316,   318,   318,   318,
     319,   320,   322,   321,   323,   323,   324,   324,   326,   325,
     327,   327,   328,   328,   328,   328,   328,   328,   328,   328,
     328,   328,   328,   328,   328,   328,   328,   328,   328,   330,
     329,   332,   331,   333,   333,   334,   334,   336,   335,   338,
     337,   339,   339,   340,   340,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   342,   343,   344,   346,   345,
     348,   347,   350,   349,   351,   353,   352,   354,   356,   355,
     357,   357,   358,   358,   360,   359,   362,   361,   363,   363,
     364,   364,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   366,   368,   367,   369,   370,   371,   372,   374,   373,
     375,   375,   376,   376,   378,   377,   380,   379,   381,   381,
     382,   382,   382,   382,   382,   382,   382,   384,   383,   386,
     385,   388,   387,   390,   389,   391,   391,   392,   392,   394,
     393,   396,   395,   397,   397,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   400,   399,   401,   403,
     402,   404,   405,   407,   406,   408,   408,   409,   409,   411,
     410,   413,   412,   414,   414,   415,   415,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   418,   417,
     420,   419,   422,   421,   424,   423,   426,   425,   428,   427,
     430,   429,   432,   431,   434,   433,   436,   435,   437,   437,
     439,   438,   440,   440,   441,   441,   442,   442,   442,   442,
     442,   442,   442,   443,   445,   444,   446,   448,   447,   449,
     449,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     452,   451,   453,   453,   453,   454,   456,   455,   457,   458,
     459,   461,   460,   462,   462,   463,   463,   463,   463,   463,
     465,   464,   467,   466,   469,   468,   471,   470,   472,   472,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   474,   476,   475,
     478,   477,   479,   481,   480,   482,   483,   485,   484,   486,
     486,   488,   487,   489,   490,   491,   493,   492,   494,   494,
     494,   494,   494,   496,   495,   498,   497,   500,   499,   502,
     501,   504,   503,   506,   505,   507,   507,   508,   510,   509,
     511,   511,   513,   512,   514,   514,   515,   515,   515,   515,
     515,   515,   515,   516,   518,   517,   520,   519,   521,   521,
     523,   522,   524,   524,   525,   525,   525,   525,   527,   526,
     528,   529,   530
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
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
       3,     3,     3,     3,     3,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"preferred-lifetime\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"only-if-required\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp6_object", "$@19", "sub_dhcp6",
  "$@20", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@21",
  "sub_interfaces6", "$@22", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@23", "re_detect",
  "lease_database", "$@24", "hosts_database", "$@25", "hosts_databases",
  "$@26", "database_list", "not_empty_database_list", "database", "$@27",
  "database_map_params", "database_map_param", "database_type", "$@28",
  "db_type", "user", "$@29", "password", "$@30", "host", "$@31", "port",
  "name", "$@32", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@33", "max_reconnect_tries", "keyspace", "$@34",
  "mac_sources", "$@35", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@37",
  "hooks_libraries", "$@38", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@39",
  "sub_hooks_library", "$@40", "hooks_params", "hooks_param", "library",
  "$@41", "parameters", "$@42", "expired_leases_processing", "$@43",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@44",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@45",
  "sub_subnet6", "$@46", "subnet6_params", "subnet6_param", "subnet",
  "$@47", "interface", "$@48", "interface_id", "$@49", "client_class",
  "$@50", "require_client_classes", "$@51", "reservation_mode", "$@52",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@53",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@54", "shared_network_params", "shared_network_param",
  "option_def_list", "$@55", "sub_option_def_list", "$@56",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@57", "sub_option_def", "$@58",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@59",
  "option_def_record_types", "$@60", "space", "$@61", "option_def_space",
  "option_def_encapsulate", "$@62", "option_def_array", "option_data_list",
  "$@63", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@64", "sub_option_data", "$@65",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@66",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@67", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@68", "sub_pool6", "$@69",
  "pool_params", "pool_param", "pool_entry", "$@70", "user_context",
  "$@71", "comment", "$@72", "pd_pools_list", "$@73",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@74", "sub_pd_pool", "$@75", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@76", "pd_prefix_len", "excluded_prefix", "$@77",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@78",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@79", "sub_reservation", "$@80", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@81", "prefixes", "$@82", "duid", "$@83", "hw_address", "$@84",
  "hostname", "$@85", "flex_id_value", "$@86",
  "reservation_client_classes", "$@87", "relay", "$@88", "relay_map",
  "$@89", "client_classes", "$@90", "client_classes_list",
  "client_class_entry", "$@91", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@92", "only_if_required",
  "server_id", "$@93", "server_id_params", "server_id_param",
  "server_id_type", "$@94", "duid_type", "htype", "identifier", "$@95",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@96",
  "control_socket_params", "control_socket_param", "socket_type", "$@97",
  "socket_name", "$@98", "dhcp_ddns", "$@99", "sub_dhcp_ddns", "$@100",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@101", "server_ip", "$@102", "server_port",
  "sender_ip", "$@103", "sender_port", "max_queue_size", "ncr_protocol",
  "$@104", "ncr_protocol_value", "ncr_format", "$@105",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@106", "replace_client_name_value",
  "generated_prefix", "$@107", "dhcp4_json_object", "$@108",
  "dhcpddns_json_object", "$@109", "control_agent_json_object", "$@110",
  "logging_object", "$@111", "sub_logging", "$@112", "logging_params",
  "logging_param", "loggers", "$@113", "loggers_entries", "logger_entry",
  "$@114", "logger_params", "logger_param", "debuglevel", "severity",
  "$@115", "output_options_list", "$@116", "output_options_list_content",
  "output_entry", "$@117", "output_params_list", "output_params", "output",
  "$@118", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   246,   246,   246,   247,   247,   248,   248,   249,   249,
     250,   250,   251,   251,   252,   252,   253,   253,   254,   254,
     255,   255,   256,   256,   257,   257,   258,   258,   259,   259,
     267,   268,   269,   270,   271,   272,   273,   276,   281,   281,
     292,   295,   296,   299,   303,   310,   310,   317,   318,   321,
     325,   332,   332,   339,   340,   343,   347,   358,   368,   368,
     383,   384,   388,   389,   390,   391,   392,   393,   396,   396,
     411,   411,   420,   421,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     454,   459,   464,   469,   474,   479,   479,   490,   490,   499,
     500,   503,   504,   505,   506,   507,   510,   510,   520,   526,
     526,   538,   538,   550,   550,   560,   561,   564,   565,   568,
     568,   578,   579,   582,   583,   584,   585,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   602,   602,   609,   610,   611,   612,   615,   615,   623,
     623,   631,   631,   639,   644,   644,   652,   657,   662,   667,
     672,   677,   682,   687,   692,   692,   700,   705,   705,   714,
     714,   724,   725,   728,   729,   732,   737,   742,   742,   752,
     753,   756,   757,   758,   761,   766,   773,   773,   783,   783,
     793,   794,   797,   798,   801,   801,   811,   811,   821,   822,
     823,   826,   827,   830,   830,   838,   838,   846,   846,   857,
     858,   861,   862,   863,   864,   865,   866,   869,   874,   879,
     884,   889,   894,   902,   902,   915,   916,   919,   920,   927,
     927,   953,   953,   964,   965,   969,   970,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   980,   981,   982,   983,
     984,   985,   986,   987,   988,   991,   991,   999,   999,  1007,
    1007,  1015,  1015,  1023,  1023,  1033,  1033,  1040,  1041,  1042,
    1045,  1050,  1058,  1058,  1069,  1070,  1074,  1075,  1078,  1078,
    1086,  1087,  1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,
    1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1113,
    1113,  1126,  1126,  1135,  1136,  1139,  1140,  1145,  1145,  1160,
    1160,  1174,  1175,  1178,  1179,  1182,  1183,  1184,  1185,  1186,
    1187,  1188,  1189,  1190,  1191,  1194,  1196,  1201,  1203,  1203,
    1211,  1211,  1219,  1219,  1227,  1229,  1229,  1237,  1246,  1246,
    1258,  1259,  1264,  1265,  1270,  1270,  1282,  1282,  1294,  1295,
    1300,  1301,  1306,  1307,  1308,  1309,  1310,  1311,  1312,  1313,
    1314,  1317,  1319,  1319,  1327,  1329,  1331,  1336,  1344,  1344,
    1356,  1357,  1360,  1361,  1364,  1364,  1374,  1374,  1383,  1384,
    1387,  1388,  1389,  1390,  1391,  1392,  1393,  1396,  1396,  1404,
    1404,  1429,  1429,  1459,  1459,  1471,  1472,  1475,  1476,  1479,
    1479,  1491,  1491,  1503,  1504,  1507,  1508,  1509,  1510,  1511,
    1512,  1513,  1514,  1515,  1516,  1517,  1520,  1520,  1528,  1533,
    1533,  1541,  1546,  1554,  1554,  1564,  1565,  1568,  1569,  1572,
    1572,  1581,  1581,  1590,  1591,  1594,  1595,  1599,  1600,  1601,
    1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,  1612,  1612,
    1622,  1622,  1632,  1632,  1640,  1640,  1648,  1648,  1656,  1656,
    1664,  1664,  1677,  1677,  1687,  1687,  1698,  1698,  1708,  1709,
    1712,  1712,  1722,  1723,  1726,  1727,  1730,  1731,  1732,  1733,
    1734,  1735,  1736,  1739,  1741,  1741,  1749,  1757,  1757,  1769,
    1770,  1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,
    1784,  1784,  1791,  1792,  1793,  1796,  1801,  1801,  1809,  1814,
    1821,  1828,  1828,  1838,  1839,  1842,  1843,  1844,  1845,  1846,
    1849,  1849,  1857,  1857,  1867,  1867,  1879,  1879,  1889,  1890,
    1893,  1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,
    1903,  1904,  1905,  1906,  1907,  1908,  1909,  1912,  1917,  1917,
    1925,  1925,  1933,  1938,  1938,  1946,  1951,  1956,  1956,  1964,
    1965,  1968,  1968,  1976,  1981,  1986,  1991,  1991,  1999,  2002,
    2005,  2008,  2011,  2017,  2017,  2027,  2027,  2034,  2034,  2041,
    2041,  2054,  2054,  2064,  2064,  2075,  2076,  2080,  2084,  2084,
    2096,  2097,  2101,  2101,  2109,  2110,  2113,  2114,  2115,  2116,
    2117,  2118,  2119,  2122,  2127,  2127,  2135,  2135,  2145,  2146,
    2149,  2149,  2157,  2158,  2161,  2162,  2163,  2164,  2167,  2167,
    2175,  2180,  2185
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4746 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2190 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
