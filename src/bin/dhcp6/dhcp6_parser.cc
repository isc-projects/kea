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
      case 454: // duid_type
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
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
      case 454: // duid_type
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
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

      case 454: // duid_type

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 487: // ncr_protocol_value

#line 237 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 495: // replace_client_name_value

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
      case 454: // duid_type
      case 487: // ncr_protocol_value
      case 495: // replace_client_name_value
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

  case 101:
#line 455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 613 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1497 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1575 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 816 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1725 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 242:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1010 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1212 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1232 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 402:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 404:
#line 1460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1973 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2004 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2007 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2010 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2022 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2174 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -774;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     313,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,    45,    35,    42,    74,    81,
     105,   124,   128,   165,   182,   184,   186,   188,   198,   232,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,    35,   -82,
      29,    52,    59,   225,   193,   238,   123,   127,    85,   381,
     -45,   444,    51,  -774,   245,   242,   249,   269,   299,  -774,
    -774,  -774,  -774,  -774,   305,  -774,    54,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,   307,   311,   322,
     324,   328,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,   340,  -774,  -774,  -774,
      72,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   342,
    -774,   110,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   351,   353,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   136,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,   142,  -774,  -774,  -774,  -774,
    -774,   357,  -774,   360,   361,  -774,  -774,  -774,  -774,  -774,
    -774,   148,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   354,
     347,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   362,
    -774,  -774,   369,  -774,  -774,  -774,   376,  -774,  -774,   374,
     382,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   380,   386,  -774,  -774,  -774,  -774,
     384,   391,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   160,  -774,  -774,  -774,   393,  -774,
    -774,   394,  -774,   400,   401,  -774,  -774,   407,   409,   418,
    -774,  -774,  -774,  -774,  -774,   163,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   176,  -774,  -774,  -774,    35,    35,  -774,   234,
     419,   420,   430,   433,   436,  -774,    29,  -774,   437,   438,
     441,   442,   285,   287,   288,   290,   291,   450,   451,   452,
     453,   454,   470,   471,   472,   473,   474,   475,   477,   478,
     479,   325,   480,   482,    52,  -774,   484,   329,    59,  -774,
     485,   486,   487,   488,   490,   333,   332,   494,   495,   496,
     497,   225,  -774,   498,   193,  -774,   504,   348,   505,   349,
     350,   238,  -774,   509,   510,   514,   515,   516,   520,   521,
    -774,   123,  -774,   522,   523,   366,   525,   526,   528,   372,
    -774,    85,   529,   373,   375,  -774,   381,   530,   534,    27,
    -774,   377,   536,   539,   383,   540,   385,   387,   542,   544,
     388,   392,   408,   546,   547,   444,  -774,   553,    51,  -774,
    -774,  -774,   569,   567,   568,    35,    35,    35,  -774,   570,
     571,   572,   575,  -774,  -774,  -774,  -774,  -774,   576,   577,
     578,   579,   415,   580,   582,   583,   584,   585,   586,   587,
     588,   590,  -774,   591,   592,  -774,   589,  -774,  -774,   595,
     596,   423,   432,   443,  -774,  -774,   346,   589,   445,   600,
    -774,   447,  -774,   448,  -774,   449,  -774,  -774,  -774,   589,
     589,   589,   455,   456,   457,   458,  -774,   459,   460,  -774,
     461,   462,   463,  -774,  -774,   464,  -774,  -774,  -774,   465,
      35,  -774,  -774,   466,   467,  -774,   468,  -774,  -774,    90,
     481,  -774,  -774,  -774,   -47,   469,  -774,   597,  -774,    35,
      52,    51,  -774,  -774,  -774,    59,   199,   199,   605,   606,
     607,   624,  -774,  -774,  -774,   625,   -21,    35,   252,   626,
     627,   628,     8,   152,   -12,   444,  -774,  -774,   629,   630,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,    -7,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   631,  -774,   180,   209,   233,  -774,  -774,  -774,
    -774,   599,   635,   636,   637,   638,  -774,   639,   640,  -774,
     641,   642,   643,  -774,   235,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   239,  -774,   644,   645,  -774,  -774,   646,
     648,  -774,  -774,   647,   651,  -774,  -774,   649,   653,  -774,
    -774,   652,   654,  -774,  -774,  -774,    40,  -774,  -774,  -774,
     655,  -774,  -774,  -774,    95,  -774,  -774,  -774,  -774,   154,
    -774,  -774,   656,   657,  -774,  -774,   658,   660,  -774,   661,
     662,   663,   664,   665,   666,   246,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,   667,   668,   669,  -774,  -774,
    -774,  -774,   258,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   264,  -774,  -774,  -774,   267,   513,
    -774,   670,   672,  -774,  -774,   671,   675,  -774,  -774,  -774,
     673,  -774,  -774,   280,  -774,  -774,  -774,  -774,   676,   678,
     679,   680,   517,   524,   527,   531,   532,   681,   535,   537,
     682,   538,   541,   543,   199,  -774,  -774,   199,  -774,   605,
     225,  -774,   606,    85,  -774,   607,   381,  -774,   624,   370,
    -774,   625,   -21,  -774,  -774,   252,  -774,    79,   626,  -774,
     123,  -774,   627,   -45,  -774,   628,   548,   549,   550,   551,
     552,   554,     8,  -774,   683,   686,   555,   556,   557,   152,
    -774,   687,   688,   -12,  -774,  -774,  -774,   690,   695,   193,
    -774,   629,   238,  -774,   630,   689,  -774,    15,   631,  -774,
     358,   545,   560,   561,  -774,  -774,  -774,  -774,  -774,   564,
    -774,  -774,   566,  -774,  -774,  -774,  -774,   270,  -774,   277,
    -774,   693,  -774,   694,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   302,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   700,  -774,
    -774,  -774,  -774,  -774,   697,   705,  -774,  -774,  -774,  -774,
    -774,   701,  -774,   309,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   317,   573,  -774,  -774,  -774,  -774,   593,   601,
    -774,  -774,   603,   315,  -774,   319,  -774,   613,  -774,   711,
    -774,  -774,  -774,  -774,  -774,   326,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,   370,  -774,   724,   602,  -774,
      79,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,   726,   598,   727,    15,  -774,  -774,
     617,  -774,  -774,   745,  -774,   619,  -774,  -774,   744,  -774,
    -774,   336,  -774,    39,   744,  -774,  -774,   757,   763,   779,
     327,  -774,  -774,  -774,  -774,  -774,  -774,   781,   622,   633,
     634,    39,  -774,   650,  -774,  -774,  -774,  -774,  -774
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   108,     9,   242,    11,
     387,    13,   412,    15,   442,    17,   312,    19,   320,    21,
     357,    23,   207,    25,   539,    27,   596,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   444,     0,   322,   359,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     594,   588,   590,   592,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   106,   120,   122,   124,     0,     0,     0,
       0,     0,   234,   310,   349,   400,   402,   283,   180,   197,
     188,   479,   434,   199,   218,   500,     0,   524,   537,   100,
       0,    72,    74,    75,    76,    77,    78,    81,    82,    83,
      84,    85,    87,    86,    91,    92,    79,    80,    89,    90,
      97,    98,    99,    88,    93,    94,    95,    96,   117,     0,
     116,     0,   110,   112,   113,   114,   115,   379,   404,   266,
     268,   270,     0,     0,   276,   274,   272,   473,   265,   246,
     247,   248,   249,     0,   244,   253,   254,   255,   258,   259,
     261,   256,   257,   250,   251,   263,   264,   252,   260,   262,
     398,   397,   393,   394,   392,     0,   389,   391,   395,   396,
     427,     0,   430,     0,     0,   426,   420,   421,   419,   424,
     425,     0,   414,   416,   417,   422,   423,   418,   471,   459,
     461,   463,   465,   467,   469,   458,   455,   456,   457,     0,
     445,   446,   450,   451,   448,   452,   453,   454,   449,     0,
     339,   165,     0,   343,   341,   346,     0,   335,   336,     0,
     323,   324,   326,   338,   327,   328,   329,   345,   330,   331,
     332,   333,   334,   373,     0,     0,   371,   372,   375,   376,
       0,   360,   361,   363,   364,   365,   366,   367,   368,   369,
     370,   214,   216,   211,     0,   209,   212,   213,     0,   561,
     563,     0,   566,     0,     0,   570,   574,     0,     0,     0,
     579,   586,   559,   557,   558,     0,   541,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   601,     0,   598,   600,    46,     0,     0,    39,     0,
       0,     0,     0,     0,     0,    57,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,     0,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   243,     0,     0,   388,     0,     0,     0,     0,
       0,     0,   413,     0,     0,     0,     0,     0,     0,     0,
     443,     0,   313,     0,     0,     0,     0,     0,     0,     0,
     321,     0,     0,     0,     0,   358,     0,     0,     0,     0,
     208,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   540,     0,     0,   597,
      50,    43,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,     0,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   523,     0,     0,    73,     0,   119,   111,     0,
       0,     0,     0,     0,   281,   282,     0,     0,     0,     0,
     245,     0,   390,     0,   429,     0,   432,   433,   415,     0,
       0,     0,     0,     0,     0,     0,   447,     0,     0,   337,
       0,     0,     0,   348,   325,     0,   377,   378,   362,     0,
       0,   210,   560,     0,     0,   565,     0,   568,   569,     0,
       0,   576,   577,   578,     0,     0,   542,     0,   599,     0,
       0,     0,   589,   591,   593,     0,     0,     0,   126,   236,
     314,   351,    40,   401,   403,   285,     0,    47,     0,     0,
     436,   201,     0,     0,     0,     0,    51,   118,   381,   406,
     267,   269,   271,   278,   279,   280,   277,   275,   273,     0,
     399,   428,   431,   472,   460,   462,   464,   466,   468,   470,
     340,   166,   344,   342,   347,   374,   215,   217,   562,   564,
     567,   572,   573,   571,   575,   581,   582,   583,   584,   585,
     580,   587,     0,    44,     0,     0,     0,   152,   158,   160,
     162,     0,     0,     0,     0,     0,   175,     0,     0,   178,
       0,     0,     0,   151,     0,   132,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   146,   147,   148,   149,
     144,   145,   150,     0,   130,     0,   127,   128,   240,     0,
     237,   238,   318,     0,   315,   316,   355,     0,   352,   353,
     289,     0,   286,   287,   186,   187,     0,   182,   184,   185,
       0,   195,   196,   192,     0,   190,   193,   194,   483,     0,
     481,   440,     0,   437,   438,   205,     0,   202,   203,     0,
       0,     0,     0,     0,     0,     0,   220,   222,   223,   224,
     225,   226,   227,   513,   519,     0,     0,     0,   512,   509,
     510,   511,     0,   502,   504,   507,   505,   506,   508,   533,
     535,   532,   530,   531,     0,   526,   528,   529,     0,    53,
     385,     0,   382,   383,   410,     0,   407,   408,   477,   476,
       0,   475,   605,     0,   603,    69,   595,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   121,   123,     0,   125,     0,
       0,   235,     0,   322,   311,     0,   359,   350,     0,     0,
     284,     0,     0,   181,   198,     0,   189,   485,     0,   480,
     444,   435,     0,     0,   200,     0,     0,     0,     0,     0,
       0,     0,     0,   219,     0,     0,     0,     0,     0,     0,
     501,     0,     0,     0,   525,   538,    55,     0,    54,     0,
     380,     0,     0,   405,     0,     0,   474,     0,     0,   602,
       0,     0,     0,     0,   164,   167,   168,   169,   170,     0,
     177,   171,     0,   172,   173,   174,   133,     0,   129,     0,
     239,     0,   317,     0,   354,   309,   304,   306,   297,   298,
     293,   294,   295,   296,   302,   303,   301,   305,     0,   291,
     299,   307,   308,   300,   288,   183,   191,   497,     0,   495,
     496,   492,   493,   494,     0,   486,   487,   489,   490,   491,
     482,     0,   439,     0,   204,   228,   229,   230,   231,   232,
     233,   221,     0,     0,   518,   521,   522,   503,     0,     0,
     527,    52,     0,     0,   384,     0,   409,     0,   619,     0,
     617,   615,   609,   613,   614,     0,   607,   611,   612,   610,
     604,   154,   155,   156,   157,   153,   159,   161,   163,   176,
     179,   131,   241,   319,   356,     0,   290,     0,     0,   484,
       0,   441,   206,   515,   516,   517,   514,   520,   534,   536,
      56,   386,   411,   478,     0,     0,     0,     0,   606,   292,
       0,   499,   488,     0,   616,     0,   608,   498,     0,   618,
     623,     0,   621,     0,     0,   620,   631,     0,     0,     0,
       0,   625,   627,   628,   629,   630,   622,     0,     0,     0,
       0,     0,   624,     0,   633,   634,   635,   626,   632
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,    66,  -774,   178,  -774,
    -774,  -774,  -774,  -774,  -774,    92,  -774,  -400,  -774,  -774,
    -774,   -70,  -774,  -774,  -774,   446,  -774,  -774,  -774,  -774,
     251,   414,   -66,   -44,   -43,    -8,  -774,  -774,  -774,  -774,
    -774,   244,   424,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,    14,  -774,  -535,    20,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   -54,  -774,
    -561,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,     3,  -555,  -774,  -774,
    -774,  -774,     1,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,    -3,  -774,  -774,  -774,    -6,   379,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,    -4,  -774,  -774,  -774,  -774,  -774,
    -774,  -773,  -774,  -774,  -774,    18,  -774,  -774,  -774,    24,
     425,  -774,  -774,  -771,  -774,  -764,  -774,    -5,  -774,    -1,
    -774,  -763,  -774,  -774,  -774,  -762,  -774,  -774,  -774,  -774,
      16,  -774,  -774,  -150,   743,  -774,  -774,  -774,  -774,  -774,
      26,  -774,  -774,  -774,    30,  -774,   403,  -774,   -60,  -774,
    -774,  -774,  -774,  -774,   -38,  -774,  -774,  -774,  -774,  -774,
     -42,  -774,  -774,  -774,    28,  -774,  -774,  -774,    32,  -774,
     399,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,   -11,  -774,  -774,  -774,   -10,   439,  -774,  -774,
     -58,  -774,   -20,  -774,  -774,  -774,  -774,  -774,   -13,  -774,
    -774,  -774,    -2,   431,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,   -46,  -774,  -774,  -774,    23,  -774,  -774,  -774,    33,
    -774,   428,   247,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -761,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,    34,  -774,  -774,  -774,  -126,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,    17,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,    12,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,   272,   404,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,  -774,
    -774,  -774,  -774,   297,   402,  -774,  -774,  -774,     4,  -774,
    -774,  -136,  -774,  -774,  -774,  -774,  -774,  -774,  -151,  -774,
    -774,  -167,  -774,  -774,  -774,  -774,  -774
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     563,    87,    88,    41,    68,    84,    85,   577,   749,   837,
     838,   643,    43,    70,    96,    97,    98,   340,    45,    71,
     130,   131,   132,   133,   134,   135,   136,   137,   348,    47,
      72,   161,   162,   163,   376,   164,   138,   349,   139,   350,
     140,   351,   665,   666,   667,   787,   644,   645,   646,   768,
     955,   647,   769,   648,   770,   649,   771,   650,   651,   414,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   777,
     661,   662,   780,   141,   363,   686,   687,   688,   689,   142,
     365,   694,   695,   696,   697,   143,   364,   144,   368,   706,
     707,   708,   813,    63,    80,   294,   295,   296,   427,   297,
     428,   145,   369,   715,   716,   717,   718,   719,   720,   721,
     722,   146,   357,   669,   670,   671,   790,    49,    73,   183,
     184,   185,   382,   186,   383,   187,   384,   188,   389,   189,
     388,   190,   387,   586,   191,   192,   147,   362,   681,   682,
     683,   799,   888,   889,   148,   358,    57,    77,   673,   674,
     675,   793,    59,    78,   259,   260,   261,   262,   263,   264,
     265,   413,   266,   417,   267,   416,   268,   269,   418,   270,
     149,   359,   677,   678,   679,   796,    61,    79,   280,   281,
     282,   283,   284,   422,   285,   286,   287,   288,   194,   380,
     751,   752,   753,   839,    51,    74,   205,   206,   207,   393,
     150,   360,   151,   361,   197,   381,   755,   756,   757,   842,
      53,    75,   221,   222,   223,   396,   224,   225,   398,   226,
     227,   152,   367,   702,   703,   704,   810,    55,    76,   239,
     240,   241,   242,   404,   243,   405,   244,   406,   245,   407,
     246,   408,   247,   409,   248,   403,   199,   390,   760,   761,
     845,   153,   366,   699,   700,   807,   904,   905,   906,   907,
     908,   967,   909,   154,   370,   732,   733,   734,   824,   976,
     735,   736,   825,   737,   738,   155,   156,   372,   744,   745,
     746,   831,   747,   832,   157,   373,    65,    81,   315,   316,
     317,   318,   432,   319,   433,   320,   321,   435,   322,   323,
     324,   438,   613,   325,   439,   326,   327,   328,   329,   443,
     620,   330,   444,    99,   342,   100,   343,   101,   344,   102,
     341,    67,    82,   332,   333,   334,   447,   763,   764,   847,
     945,   946,   947,   948,   986,   949,   984,  1001,  1002,  1003,
    1010,  1011,  1012,  1017,  1013,  1014,  1015
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   129,   160,   178,   201,   215,   235,   179,   257,   276,
     293,   312,   729,   693,   165,   195,   208,   219,   237,   278,
     271,   289,   663,   313,   258,   277,   881,   198,   882,   180,
     181,   193,   204,   218,   236,   883,   886,   887,   893,    89,
      31,   279,    32,   802,    33,    30,   803,   291,   292,    42,
     115,   116,   166,   196,   209,   220,   238,   346,   272,   290,
     251,   314,   347,   103,   684,   182,   104,   105,   106,   202,
     216,   158,   159,   203,   217,   374,   229,   115,   116,    86,
     375,    44,    38,   758,   615,   616,   617,   618,    46,   107,
     108,   109,   110,   111,   112,   113,   114,   587,   805,   739,
     740,   806,   250,   709,   710,   711,   712,   713,   714,   593,
     594,   595,    48,   378,   115,   116,    94,   619,   379,   291,
     292,   115,   116,   114,   251,   117,   118,   119,   120,   121,
     251,    50,   252,   253,   122,    52,   254,   255,   256,   391,
     685,   115,   116,   123,   392,   394,   124,   115,   116,    94,
     395,   401,   938,   125,   939,   940,   402,   808,   897,   898,
     809,   126,   127,   429,    90,   128,   445,   114,   430,   723,
     113,   446,    54,    91,    92,    93,    94,  1006,   632,   448,
    1007,  1008,  1009,   374,   449,   115,   116,   331,   765,    56,
      94,    58,   881,    60,   882,    62,    34,    35,    36,    37,
     228,   883,   886,   887,   893,    64,   229,   230,   231,   232,
     233,   234,   448,    94,   115,   116,   627,   766,   611,   612,
      94,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,   639,   640,   641,   642,   378,   114,   784,    66,
      94,   767,   784,   785,   251,   336,    94,   786,   200,   822,
     693,   335,   867,   337,   823,   115,   116,   724,   725,   726,
     727,   829,   107,   108,   109,   110,   830,   833,   729,   114,
     445,   175,   834,   784,   176,   835,    95,   338,   961,   167,
     391,   168,   114,   848,    94,   962,   849,   115,   116,   169,
     170,   171,   172,   173,   174,   210,   211,   212,   213,   214,
     115,   116,   339,   175,   129,   965,   176,   122,   160,   345,
     966,   352,   429,    94,   177,   353,   175,   972,   394,   176,
     165,   178,   401,   981,   201,   179,   354,   982,   355,   987,
    1021,   215,   356,   195,   988,  1022,   208,   684,   691,  1004,
     692,   235,  1005,   219,   371,   198,   377,   180,   181,   193,
     411,   257,   204,   237,    94,   385,   276,   386,   166,   218,
      94,   397,   410,   271,   399,   400,   278,   258,   289,   236,
     412,   196,   277,   415,   209,   312,   951,   952,   953,   954,
     419,   220,   420,   182,   423,   421,    94,   313,   279,   202,
     424,   238,   425,   203,   426,   452,   216,   431,   434,    94,
     217,   272,   450,   451,   436,   437,   290,   107,   108,   109,
     110,   440,   112,   441,   114,   251,   583,   584,   585,   973,
     974,   975,   442,   453,   454,   314,   251,   273,   252,   253,
     274,   275,   115,   116,   455,   170,   171,   456,   173,   174,
     457,   459,   460,   115,   116,   461,   462,   463,   175,   464,
     465,   176,   466,   467,   468,   469,   470,   471,   472,   177,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   473,   474,   475,   476,   477,   478,
     129,   479,   480,   481,   483,   160,   484,   482,   486,   489,
     490,   491,   492,   487,   493,   494,   495,   165,   496,   497,
     498,   499,   501,   728,   741,   312,   115,   116,   503,   505,
     504,   506,   507,   509,   510,   730,   742,   313,   511,   512,
     513,   552,   553,   554,   514,   515,   517,   518,   519,   520,
     521,    94,   522,   525,   529,   166,   523,   526,   530,   527,
     533,   532,    94,   534,   536,   535,   539,   537,   540,   538,
     544,   545,   541,   731,   743,   314,   542,   547,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   543,   549,   550,   551,   564,   555,   556,   557,
     558,   559,   560,   561,   580,   565,    32,   566,   567,   568,
     569,   570,   571,   581,   576,   572,   607,   573,   574,   575,
     578,   579,   622,   772,   582,    94,   588,   589,   590,   591,
     592,   614,   664,   668,   672,   623,   596,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   608,   609,   610,
     621,   676,   680,   698,   701,   705,   750,   754,   762,   773,
     774,   775,   776,   778,   779,   781,   782,   783,   789,   562,
     788,   792,   791,   794,   795,   797,   798,   801,   800,   690,
     812,   804,   811,   815,   814,   816,   817,   818,   819,   820,
     821,   826,   827,   828,   836,   841,   840,   843,   844,   854,
     850,   846,   851,   852,   853,   859,   862,   922,   855,   856,
     923,   928,   929,   937,   858,   857,   931,   860,   932,   861,
     863,   963,   964,   864,   968,   969,   956,   865,   970,   971,
     915,   916,   917,   918,   919,   985,   920,   924,   925,   926,
     178,   957,   958,   257,   179,   959,   276,   960,   990,   875,
     993,   995,   195,   876,   977,   271,   278,   899,   289,   258,
     235,   891,   277,   293,   198,   880,   180,   181,   193,   902,
     998,  1000,   237,   900,   978,   877,   878,   890,   279,   728,
     994,  1018,   979,   741,   980,   901,   991,  1019,   236,   201,
     196,   730,   215,   272,   983,   742,   290,   941,   997,   892,
     999,   208,   182,  1020,   219,  1023,  1024,   903,   485,   943,
     238,   879,   458,   942,   884,  1025,  1026,   204,   885,   626,
     218,   624,   488,   868,   866,   895,   896,   913,   531,   731,
     870,  1028,   914,   743,   869,   989,   500,   894,   921,   209,
     249,   872,   220,   871,   524,   528,   874,   944,   873,   933,
     934,   936,   508,   502,   202,   912,   759,   216,   203,   516,
     935,   217,   910,   911,   992,   930,   927,   748,   625,   546,
     548,   996,   950,  1016,  1027,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   875,     0,     0,     0,   876,
     899,     0,     0,     0,     0,     0,     0,   891,     0,     0,
       0,   880,   902,     0,     0,     0,   900,   941,     0,     0,
       0,   877,   878,   890,     0,     0,     0,     0,   901,   943,
       0,     0,     0,   942,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   892,     0,     0,     0,     0,
     903,     0,     0,     0,     0,     0,     0,   879,     0,     0,
     884,     0,     0,     0,   885,     0,     0,   944
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    73,    78,    79,
      80,    81,   573,   568,    72,    73,    74,    75,    76,    79,
      78,    79,   557,    81,    78,    79,   799,    73,   799,    73,
      73,    73,    74,    75,    76,   799,   799,   799,   799,    10,
       5,    79,     7,     3,     9,     0,     6,    92,    93,     7,
      62,    63,    72,    73,    74,    75,    76,     3,    78,    79,
      45,    81,     8,    11,    85,    73,    14,    15,    16,    74,
      75,    12,    13,    74,    75,     3,    83,    62,    63,   161,
       8,     7,    16,    90,   131,   132,   133,   134,     7,    37,
      38,    39,    40,    41,    42,    43,    44,   497,     3,   111,
     112,     6,    17,    95,    96,    97,    98,    99,   100,   509,
     510,   511,     7,     3,    62,    63,   161,   164,     8,    92,
      93,    62,    63,    44,    45,    73,    74,    75,    76,    77,
      45,     7,    47,    48,    82,     7,    51,    52,    53,     3,
     161,    62,    63,    91,     8,     3,    94,    62,    63,   161,
       8,     3,   137,   101,   139,   140,     8,     3,    79,    80,
       6,   109,   110,     3,   135,   113,     3,    44,     8,    17,
      43,     8,     7,   144,   145,   146,   161,   138,    26,     3,
     141,   142,   143,     3,     8,    62,    63,   136,     8,     7,
     161,     7,   965,     7,   965,     7,   161,   162,   163,   164,
      77,   965,   965,   965,   965,     7,    83,    84,    85,    86,
      87,    88,     3,   161,    62,    63,    17,     8,   128,   129,
     161,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,     3,    44,     3,     7,
     161,     8,     3,     8,    45,     3,   161,     8,    55,     3,
     805,     6,   787,     4,     8,    62,    63,   105,   106,   107,
     108,     3,    37,    38,    39,    40,     8,     3,   829,    44,
       3,    78,     8,     3,    81,     8,   346,     8,     8,    54,
       3,    56,    44,     3,   161,     8,     6,    62,    63,    64,
      65,    66,    67,    68,    69,    57,    58,    59,    60,    61,
      62,    63,     3,    78,   374,     3,    81,    82,   378,     4,
       8,     4,     3,   161,    89,     4,    78,     8,     3,    81,
     378,   391,     3,     8,   394,   391,     4,     8,     4,     3,
       3,   401,     4,   391,     8,     8,   394,    85,    86,     3,
      88,   411,     6,   401,     4,   391,     4,   391,   391,   391,
       3,   421,   394,   411,   161,     4,   426,     4,   378,   401,
     161,     4,     8,   421,     4,     4,   426,   421,   426,   411,
       8,   391,   426,     4,   394,   445,    18,    19,    20,    21,
       4,   401,     8,   391,     4,     3,   161,   445,   426,   394,
       4,   411,     8,   394,     3,   161,   401,     4,     4,   161,
     401,   421,   336,   337,     4,     4,   426,    37,    38,    39,
      40,     4,    42,     4,    44,    45,    70,    71,    72,   102,
     103,   104,     4,     4,     4,   445,    45,    46,    47,    48,
      49,    50,    62,    63,     4,    65,    66,     4,    68,    69,
       4,     4,     4,    62,    63,     4,     4,   162,    78,   162,
     162,    81,   162,   162,     4,     4,     4,     4,     4,    89,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,     4,     4,     4,     4,     4,     4,
     550,     4,     4,     4,     4,   555,     4,   162,     4,     4,
       4,     4,     4,   164,     4,   162,   164,   555,     4,     4,
       4,     4,     4,   573,   574,   575,    62,    63,     4,     4,
     162,   162,   162,     4,     4,   573,   574,   575,     4,     4,
       4,   455,   456,   457,     4,     4,     4,     4,   162,     4,
       4,   161,     4,     4,     4,   555,   164,   164,     4,   164,
       4,   164,   161,     4,     4,   162,     4,   162,     4,   162,
       4,     4,   164,   573,   574,   575,   164,     4,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   164,     4,     7,     7,   161,     7,     7,     7,
       5,     5,     5,     5,   161,     5,     7,     5,     5,     5,
       5,     5,     5,   161,     5,     7,   530,     7,     7,     7,
       5,     5,     5,     4,   161,   161,   161,     7,   161,   161,
     161,   130,     7,     7,     7,   549,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,     7,     7,     7,     7,     7,     7,     7,     7,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   471,
       6,     3,     6,     6,     3,     6,     3,     3,     6,   567,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   161,     3,     6,     6,     3,   162,
       4,     8,     4,     4,     4,     4,     4,     4,   164,   162,
       4,     4,     4,     4,   162,   164,     6,   162,     3,   162,
     162,     8,     8,   162,     4,     8,   161,   164,     3,     8,
     162,   162,   162,   162,   162,     4,   162,   162,   162,   162,
     790,   161,   161,   793,   790,   161,   796,   161,     4,   799,
       4,     4,   790,   799,   161,   793,   796,   807,   796,   793,
     810,   799,   796,   813,   790,   799,   790,   790,   790,   807,
       5,     7,   810,   807,   161,   799,   799,   799,   796,   829,
     162,     4,   161,   833,   161,   807,   164,     4,   810,   839,
     790,   829,   842,   793,   161,   833,   796,   847,   161,   799,
     161,   839,   790,     4,   842,     4,   164,   807,   374,   847,
     810,   799,   346,   847,   799,   162,   162,   839,   799,   555,
     842,   550,   378,   789,   784,   802,   805,   813,   429,   829,
     792,   161,   815,   833,   790,   965,   391,   801,   822,   839,
      77,   795,   842,   793,   421,   426,   798,   847,   796,   839,
     841,   844,   401,   394,   839,   812,   589,   842,   839,   411,
     842,   842,   808,   810,   970,   833,   829,   575,   551,   445,
     448,   987,   848,  1004,  1021,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   965,    -1,    -1,    -1,   965,
     970,    -1,    -1,    -1,    -1,    -1,    -1,   965,    -1,    -1,
      -1,   965,   970,    -1,    -1,    -1,   970,   987,    -1,    -1,
      -1,   965,   965,   965,    -1,    -1,    -1,    -1,   970,   987,
      -1,    -1,    -1,   987,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   965,    -1,    -1,    -1,    -1,
     970,    -1,    -1,    -1,    -1,    -1,    -1,   965,    -1,    -1,
     965,    -1,    -1,    -1,   965,    -1,    -1,   987
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
       7,   361,     7,   278,     7,   471,     7,   506,   189,   184,
     198,   204,   215,   303,   380,   396,   413,   332,   338,   362,
     279,   472,   507,   181,   190,   191,   161,   186,   187,    10,
     135,   144,   145,   146,   161,   196,   199,   200,   201,   498,
     500,   502,   504,    11,    14,    15,    16,    37,    38,    39,
      40,    41,    42,    43,    44,    62,    63,    73,    74,    75,
      76,    77,    82,    91,    94,   101,   109,   110,   113,   196,
     205,   206,   207,   208,   209,   210,   211,   212,   221,   223,
     225,   258,   264,   270,   272,   286,   296,   321,   329,   355,
     385,   387,   406,   436,   448,   460,   461,   469,    12,    13,
     196,   216,   217,   218,   220,   385,   387,    54,    56,    64,
      65,    66,    67,    68,    69,    78,    81,    89,   196,   207,
     208,   209,   210,   304,   305,   306,   308,   310,   312,   314,
     316,   319,   320,   355,   373,   385,   387,   389,   406,   431,
      55,   196,   312,   314,   355,   381,   382,   383,   385,   387,
      57,    58,    59,    60,    61,   196,   312,   314,   355,   385,
     387,   397,   398,   399,   401,   402,   404,   405,    77,    83,
      84,    85,    86,    87,    88,   196,   355,   385,   387,   414,
     415,   416,   417,   419,   421,   423,   425,   427,   429,   329,
      17,    45,    47,    48,    51,    52,    53,   196,   243,   339,
     340,   341,   342,   343,   344,   345,   347,   349,   351,   352,
     354,   385,   387,    46,    49,    50,   196,   243,   343,   349,
     363,   364,   365,   366,   367,   369,   370,   371,   372,   385,
     387,    92,    93,   196,   280,   281,   282,   284,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   196,   385,   387,   473,   474,   475,   476,   478,
     480,   481,   483,   484,   485,   488,   490,   491,   492,   493,
     496,   136,   508,   509,   510,     6,     3,     4,     8,     3,
     202,   505,   499,   501,   503,     4,     3,     8,   213,   222,
     224,   226,     4,     4,     4,     4,     4,   297,   330,   356,
     386,   388,   322,   259,   271,   265,   437,   407,   273,   287,
     449,     4,   462,   470,     3,     8,   219,     4,     3,     8,
     374,   390,   307,   309,   311,     4,     4,   317,   315,   313,
     432,     3,     8,   384,     3,     8,   400,     4,   403,     4,
       4,     3,     8,   430,   418,   420,   422,   424,   426,   428,
       8,     3,     8,   346,   244,     4,   350,   348,   353,     4,
       8,     3,   368,     4,     4,     8,     3,   283,   285,     3,
       8,     4,   477,   479,     4,   482,     4,     4,   486,   489,
       4,     4,     4,   494,   497,     3,     8,   511,     3,     8,
     181,   181,   161,     4,     4,     4,     4,     4,   200,     4,
       4,     4,     4,   162,   162,   162,   162,   162,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   162,     4,     4,   206,     4,   164,   217,     4,
       4,     4,     4,     4,   162,   164,     4,     4,     4,     4,
     305,     4,   382,     4,   162,     4,   162,   162,   398,     4,
       4,     4,     4,     4,     4,     4,   416,     4,     4,   162,
       4,     4,     4,   164,   341,     4,   164,   164,   365,     4,
       4,   281,   164,     4,     4,   162,     4,   162,   162,     4,
       4,   164,   164,   164,     4,     4,   474,     4,   509,     4,
       7,     7,   181,   181,   181,     7,     7,     7,     5,     5,
       5,     5,   183,   185,   161,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   192,     5,     5,
     161,   161,   161,    70,    71,    72,   318,   192,   161,     7,
     161,   161,   161,   192,   192,   192,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   181,   161,   161,
     161,   128,   129,   487,   130,   131,   132,   133,   134,   164,
     495,   161,     5,   181,   205,   508,   216,    17,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,   196,   231,   232,   233,   236,   238,   240,
     242,   243,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   255,   256,   231,     7,   227,   228,   229,     7,   298,
     299,   300,     7,   333,   334,   335,     7,   357,   358,   359,
       7,   323,   324,   325,    85,   161,   260,   261,   262,   263,
     190,    86,    88,   262,   266,   267,   268,   269,     7,   438,
     439,     7,   408,   409,   410,     7,   274,   275,   276,    95,
      96,    97,    98,    99,   100,   288,   289,   290,   291,   292,
     293,   294,   295,    17,   105,   106,   107,   108,   196,   245,
     385,   387,   450,   451,   452,   455,   456,   458,   459,   111,
     112,   196,   385,   387,   463,   464,   465,   467,   473,   193,
       7,   375,   376,   377,     7,   391,   392,   393,    90,   417,
     433,   434,     7,   512,   513,     8,     8,     8,   234,   237,
     239,   241,     4,     4,     4,     4,     4,   254,     4,     4,
     257,     4,     4,     4,     3,     8,     8,   230,     6,     3,
     301,     6,     3,   336,     6,     3,   360,     6,     3,   326,
       6,     3,     3,     6,     6,     3,     6,   440,     3,     6,
     411,     6,     3,   277,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   453,   457,     4,     4,     4,     3,
       8,   466,   468,     3,     8,     8,   161,   194,   195,   378,
       6,     3,   394,     6,     3,   435,     8,   514,     3,     6,
       4,     4,     4,     4,   162,   164,   162,   164,   162,     4,
     162,   162,     4,   162,   162,   164,   232,   231,   229,   304,
     300,   339,   335,   363,   359,   196,   207,   208,   209,   210,
     243,   296,   308,   310,   312,   314,   316,   320,   327,   328,
     355,   385,   387,   431,   325,   261,   267,    79,    80,   196,
     243,   355,   385,   387,   441,   442,   443,   444,   445,   447,
     439,   414,   410,   280,   276,   162,   162,   162,   162,   162,
     162,   289,     4,     4,   162,   162,   162,   451,     4,     4,
     464,     6,     3,   381,   377,   397,   393,     4,   137,   139,
     140,   196,   243,   385,   387,   515,   516,   517,   518,   520,
     513,    18,    19,    20,    21,   235,   161,   161,   161,   161,
     161,     8,     8,     8,     8,     3,     8,   446,     4,     8,
       3,     8,     8,   102,   103,   104,   454,   161,   161,   161,
     161,     8,     8,   161,   521,     4,   519,     3,     8,   328,
       4,   164,   443,     4,   162,     4,   516,   161,     5,   161,
       7,   522,   523,   524,     3,     6,   138,   141,   142,   143,
     525,   526,   527,   529,   530,   531,   523,   528,     4,     4,
       4,     3,     8,     4,   164,   162,   162,   526,   161
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
     206,   207,   208,   209,   210,   211,   213,   212,   215,   214,
     216,   216,   217,   217,   217,   217,   217,   219,   218,   220,
     222,   221,   224,   223,   226,   225,   227,   227,   228,   228,
     230,   229,   231,   231,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   234,   233,   235,   235,   235,   235,   237,   236,
     239,   238,   241,   240,   242,   244,   243,   245,   246,   247,
     248,   249,   250,   251,   252,   254,   253,   255,   257,   256,
     259,   258,   260,   260,   261,   261,   262,   263,   265,   264,
     266,   266,   267,   267,   267,   268,   269,   271,   270,   273,
     272,   274,   274,   275,   275,   277,   276,   279,   278,   280,
     280,   280,   281,   281,   283,   282,   285,   284,   287,   286,
     288,   288,   289,   289,   289,   289,   289,   289,   290,   291,
     292,   293,   294,   295,   297,   296,   298,   298,   299,   299,
     301,   300,   303,   302,   304,   304,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   307,   306,   309,   308,
     311,   310,   313,   312,   315,   314,   317,   316,   318,   318,
     318,   319,   320,   322,   321,   323,   323,   324,   324,   326,
     325,   327,   327,   328,   328,   328,   328,   328,   328,   328,
     328,   328,   328,   328,   328,   328,   328,   328,   328,   328,
     330,   329,   332,   331,   333,   333,   334,   334,   336,   335,
     338,   337,   339,   339,   340,   340,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   342,   343,   344,   346,
     345,   348,   347,   350,   349,   351,   353,   352,   354,   356,
     355,   357,   357,   358,   358,   360,   359,   362,   361,   363,
     363,   364,   364,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   366,   368,   367,   369,   370,   371,   372,   374,
     373,   375,   375,   376,   376,   378,   377,   380,   379,   381,
     381,   382,   382,   382,   382,   382,   382,   382,   384,   383,
     386,   385,   388,   387,   390,   389,   391,   391,   392,   392,
     394,   393,   396,   395,   397,   397,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   398,   400,   399,   401,
     403,   402,   404,   405,   407,   406,   408,   408,   409,   409,
     411,   410,   413,   412,   414,   414,   415,   415,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   418,
     417,   420,   419,   422,   421,   424,   423,   426,   425,   428,
     427,   430,   429,   432,   431,   433,   433,   435,   434,   437,
     436,   438,   438,   440,   439,   441,   441,   442,   442,   443,
     443,   443,   443,   443,   443,   443,   444,   446,   445,   447,
     449,   448,   450,   450,   451,   451,   451,   451,   451,   451,
     451,   451,   451,   453,   452,   454,   454,   454,   455,   457,
     456,   458,   459,   460,   462,   461,   463,   463,   464,   464,
     464,   464,   464,   466,   465,   468,   467,   470,   469,   472,
     471,   473,   473,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     475,   477,   476,   479,   478,   480,   482,   481,   483,   484,
     486,   485,   487,   487,   489,   488,   490,   491,   492,   494,
     493,   495,   495,   495,   495,   495,   497,   496,   499,   498,
     501,   500,   503,   502,   505,   504,   507,   506,   508,   508,
     509,   511,   510,   512,   512,   514,   513,   515,   515,   516,
     516,   516,   516,   516,   516,   516,   517,   519,   518,   521,
     520,   522,   522,   524,   523,   525,   525,   526,   526,   526,
     526,   528,   527,   529,   530,   531
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
       1,     3,     3,     3,     3,     3,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
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
  "ip_address", "$@89", "client_classes", "$@90", "client_classes_list",
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
     452,   455,   460,   465,   470,   475,   480,   480,   491,   491,
     500,   501,   504,   505,   506,   507,   508,   511,   511,   521,
     527,   527,   539,   539,   551,   551,   561,   562,   565,   566,
     569,   569,   579,   580,   583,   584,   585,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   603,   603,   610,   611,   612,   613,   616,   616,
     624,   624,   632,   632,   640,   645,   645,   653,   658,   663,
     668,   673,   678,   683,   688,   693,   693,   701,   706,   706,
     715,   715,   725,   726,   729,   730,   733,   738,   743,   743,
     753,   754,   757,   758,   759,   762,   767,   774,   774,   784,
     784,   794,   795,   798,   799,   802,   802,   812,   812,   822,
     823,   824,   827,   828,   831,   831,   839,   839,   847,   847,
     858,   859,   862,   863,   864,   865,   866,   867,   870,   875,
     880,   885,   890,   895,   903,   903,   916,   917,   920,   921,
     928,   928,   954,   954,   965,   966,   970,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   980,   981,   982,   983,
     984,   985,   986,   987,   988,   989,   992,   992,  1000,  1000,
    1008,  1008,  1016,  1016,  1024,  1024,  1034,  1034,  1041,  1042,
    1043,  1046,  1051,  1059,  1059,  1070,  1071,  1075,  1076,  1079,
    1079,  1087,  1088,  1091,  1092,  1093,  1094,  1095,  1096,  1097,
    1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,
    1114,  1114,  1127,  1127,  1136,  1137,  1140,  1141,  1146,  1146,
    1161,  1161,  1175,  1176,  1179,  1180,  1183,  1184,  1185,  1186,
    1187,  1188,  1189,  1190,  1191,  1192,  1195,  1197,  1202,  1204,
    1204,  1212,  1212,  1220,  1220,  1228,  1230,  1230,  1238,  1247,
    1247,  1259,  1260,  1265,  1266,  1271,  1271,  1283,  1283,  1295,
    1296,  1301,  1302,  1307,  1308,  1309,  1310,  1311,  1312,  1313,
    1314,  1315,  1318,  1320,  1320,  1328,  1330,  1332,  1337,  1345,
    1345,  1357,  1358,  1361,  1362,  1365,  1365,  1375,  1375,  1384,
    1385,  1388,  1389,  1390,  1391,  1392,  1393,  1394,  1397,  1397,
    1405,  1405,  1430,  1430,  1460,  1460,  1472,  1473,  1476,  1477,
    1480,  1480,  1492,  1492,  1504,  1505,  1508,  1509,  1510,  1511,
    1512,  1513,  1514,  1515,  1516,  1517,  1518,  1521,  1521,  1529,
    1534,  1534,  1542,  1547,  1555,  1555,  1565,  1566,  1569,  1570,
    1573,  1573,  1582,  1582,  1591,  1592,  1595,  1596,  1600,  1601,
    1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,  1613,
    1613,  1623,  1623,  1633,  1633,  1641,  1641,  1649,  1649,  1657,
    1657,  1665,  1665,  1678,  1678,  1688,  1689,  1692,  1692,  1703,
    1703,  1713,  1714,  1717,  1717,  1727,  1728,  1731,  1732,  1735,
    1736,  1737,  1738,  1739,  1740,  1741,  1744,  1746,  1746,  1754,
    1762,  1762,  1774,  1775,  1778,  1779,  1780,  1781,  1782,  1783,
    1784,  1785,  1786,  1789,  1789,  1796,  1797,  1798,  1801,  1806,
    1806,  1814,  1819,  1826,  1833,  1833,  1843,  1844,  1847,  1848,
    1849,  1850,  1851,  1854,  1854,  1862,  1862,  1872,  1872,  1884,
    1884,  1894,  1895,  1898,  1899,  1900,  1901,  1902,  1903,  1904,
    1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,  1914,
    1917,  1922,  1922,  1930,  1930,  1938,  1943,  1943,  1951,  1956,
    1961,  1961,  1969,  1970,  1973,  1973,  1981,  1986,  1991,  1996,
    1996,  2004,  2007,  2010,  2013,  2016,  2022,  2022,  2032,  2032,
    2039,  2039,  2046,  2046,  2059,  2059,  2069,  2069,  2080,  2081,
    2085,  2089,  2089,  2101,  2102,  2106,  2106,  2114,  2115,  2118,
    2119,  2120,  2121,  2122,  2123,  2124,  2127,  2132,  2132,  2140,
    2140,  2150,  2151,  2154,  2154,  2162,  2163,  2166,  2167,  2168,
    2169,  2172,  2172,  2180,  2185,  2190
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
#line 4744 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2195 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
