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
      case 190: // value
      case 194: // map_value
      case 246: // db_type
      case 335: // hr_mode
      case 471: // duid_type
      case 504: // ncr_protocol_value
      case 512: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 172: // "boolean"
        value.move< bool > (that.value);
        break;

      case 171: // "floating point"
        value.move< double > (that.value);
        break;

      case 170: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 169: // "constant string"
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
      case 190: // value
      case 194: // map_value
      case 246: // db_type
      case 335: // hr_mode
      case 471: // duid_type
      case 504: // ncr_protocol_value
      case 512: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 172: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 171: // "floating point"
        value.copy< double > (that.value);
        break;

      case 170: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 169: // "constant string"
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
            case 169: // "constant string"

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 170: // "integer"

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 171: // "floating point"

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 172: // "boolean"

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 190: // value

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 194: // map_value

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 246: // db_type

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 335: // hr_mode

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 471: // duid_type

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 504: // ncr_protocol_value

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 512: // replace_client_name_value

#line 246 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 190: // value
      case 194: // map_value
      case 246: // db_type
      case 335: // hr_mode
      case 471: // duid_type
      case 504: // ncr_protocol_value
      case 512: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 172: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 171: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 170: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 169: // "constant string"
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
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 302 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 313 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 335 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 353 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 357 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1463 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1618 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1685 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1063 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1071 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1998 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2028 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1199 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2117 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1418 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2341 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2351 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1460 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2492 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1850 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1907 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2024 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2025 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2059 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3278 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2065 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2068 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2071 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2093 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2103 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3426 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 619:
#line 2150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3497 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 627:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2194 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3562 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3571 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 650:
#line 2255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 655:
#line 2275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 656:
#line 2279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 663:
#line 2293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 664:
#line 2295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 665:
#line 2301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 666:
#line 2306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 667:
#line 2311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3672 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3676 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -821;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     414,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,    64,    46,    76,    95,
      99,   119,   126,   130,   143,   145,   157,   174,   178,   191,
     204,   218,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,    46,    66,    44,    45,    63,   230,   190,   244,
      65,   187,    53,   194,   -27,   362,   108,    57,  -821,   258,
     262,   263,   270,   285,  -821,  -821,  -821,  -821,  -821,   286,
    -821,    97,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   288,   290,   299,   308,   310,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,   322,  -821,  -821,  -821,   112,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   333,  -821,   131,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   336,   363,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,   132,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,   199,  -821,  -821,
    -821,  -821,  -821,   375,  -821,   376,   389,  -821,  -821,  -821,
    -821,  -821,  -821,   201,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   374,   368,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   387,  -821,  -821,   402,  -821,  -821,  -821,   408,  -821,
    -821,   407,   430,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,   437,   438,  -821,  -821,
    -821,  -821,   440,   442,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,   216,  -821,  -821,  -821,
     447,  -821,  -821,   448,  -821,   449,   450,  -821,  -821,   451,
     452,   453,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   228,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   246,  -821,
    -821,  -821,  -821,   250,  -821,  -821,  -821,    46,    46,  -821,
     170,   454,   455,   456,   458,   459,  -821,    44,  -821,    57,
     461,   462,   463,   464,   465,   300,   301,   303,   304,   305,
     472,   473,   474,   475,   476,   491,   492,   493,   494,   495,
     496,   497,   500,   501,   502,   503,   338,   505,   506,    45,
    -821,   507,   340,    63,  -821,   509,   511,   512,   513,   520,
     355,   354,   523,   524,   525,   526,   230,  -821,   528,   190,
    -821,   530,   366,   531,   369,   370,   244,  -821,   533,   534,
     540,   542,   544,   545,   546,  -821,    65,  -821,   547,   548,
     386,   553,   554,   555,   388,  -821,    53,   557,   390,   391,
    -821,   194,   560,   579,    16,  -821,   412,   581,   582,   417,
     584,   419,   420,   587,   588,   421,   422,   423,   592,   594,
     595,   596,   362,  -821,   597,   108,  -821,   598,    57,  -821,
    -821,  -821,   599,   600,   601,    46,    46,    46,  -821,   254,
     602,   603,   604,   605,   608,  -821,  -821,  -821,  -821,  -821,
     435,   609,   610,   611,   612,   436,   613,   616,   617,   618,
     619,   620,   622,   623,   624,   625,  -821,   626,   627,  -821,
     630,  -821,  -821,   631,   632,   460,   469,   470,  -821,  -821,
     274,   630,   471,   634,  -821,   477,  -821,   478,  -821,   479,
    -821,  -821,  -821,   630,   630,   630,   480,   481,   482,   483,
    -821,   484,   485,  -821,   486,   487,   488,  -821,  -821,   489,
    -821,  -821,  -821,   490,    46,  -821,  -821,   498,   499,  -821,
     504,  -821,  -821,   105,   508,  -821,  -821,  -821,   146,   510,
     514,   515,  -821,   637,  -821,   639,  -821,    46,    45,   108,
    -821,  -821,  -821,  -821,    57,    63,   142,   142,   638,  -821,
     653,   654,   655,  -821,  -821,  -821,   656,   -31,    46,   -17,
     536,   657,   658,   659,   231,   117,    83,   362,  -821,  -821,
     662,   663,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   -13,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,   664,   638,  -821,   260,
     271,   272,   312,  -821,  -821,  -821,  -821,   668,   670,   671,
     672,   673,  -821,   674,   676,  -821,   677,   678,   681,  -821,
     320,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   335,
    -821,   680,   621,  -821,  -821,   682,   684,  -821,  -821,   683,
     687,  -821,  -821,   685,   689,  -821,  -821,   688,   690,  -821,
    -821,  -821,    54,  -821,  -821,  -821,   691,  -821,  -821,  -821,
      93,  -821,  -821,  -821,  -821,   347,  -821,  -821,  -821,   140,
    -821,  -821,   692,   693,  -821,  -821,   694,   696,  -821,   697,
     698,   699,   700,   701,   702,   348,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,   703,   704,   705,  -821,  -821,
    -821,  -821,   357,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   365,  -821,  -821,  -821,   367,   541,
    -821,   706,   708,  -821,  -821,   707,   711,  -821,  -821,  -821,
     709,  -821,  -821,   159,  -821,   710,  -821,  -821,  -821,  -821,
     714,   715,   716,   717,   552,   434,   556,   543,   558,   719,
     559,   561,   720,   562,   563,   564,   142,  -821,  -821,   142,
    -821,   638,   230,  -821,   653,    53,  -821,   654,   194,  -821,
     655,   378,  -821,   656,   -31,  -821,  -821,   -17,  -821,   721,
     536,  -821,    32,   657,  -821,    65,  -821,   658,   -27,  -821,
     659,   565,   567,   568,   569,   570,   571,   231,  -821,   723,
     726,   572,   573,   574,   117,  -821,   730,   741,    83,  -821,
    -821,  -821,   740,   744,   190,  -821,   662,   244,  -821,   663,
     745,  -821,   175,   664,  -821,  -821,   171,   583,   585,   586,
    -821,  -821,  -821,  -821,  -821,   589,  -821,  -821,   590,  -821,
    -821,  -821,  -821,   380,  -821,   394,  -821,   742,  -821,   743,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   400,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   591,  -821,  -821,   749,  -821,  -821,  -821,
    -821,  -821,   748,   754,  -821,  -821,  -821,  -821,  -821,   753,
    -821,   413,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
     331,   606,  -821,  -821,  -821,  -821,   607,   628,  -821,  -821,
     640,   426,  -821,   427,  -821,   642,  -821,   759,  -821,  -821,
    -821,  -821,  -821,   428,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   378,  -821,  -821,   760,   576,  -821,    32,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   762,   615,   763,   175,  -821,  -821,   649,
    -821,  -821,   764,  -821,   652,  -821,  -821,   766,  -821,  -821,
     202,  -821,    39,   766,  -821,  -821,   774,   775,   778,   429,
    -821,  -821,  -821,  -821,  -821,  -821,   786,   661,   666,   667,
      39,  -821,   660,  -821,  -821,  -821,  -821,  -821
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   115,     9,
     256,    11,   401,    13,   426,    15,   456,    17,   326,    19,
     334,    21,   371,    23,   221,    25,   553,    27,   628,    29,
     618,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     458,     0,   336,   373,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   626,   608,   610,   612,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   614,   616,
     113,   127,   129,   131,     0,     0,     0,     0,     0,   111,
     248,   324,   363,   414,   416,   297,   194,   211,   202,   187,
     493,   448,   213,   232,   514,     0,   538,   551,   105,     0,
      74,    76,    77,    78,    79,    80,   104,    83,    84,    85,
      86,   101,    87,    89,    88,    93,    94,    81,    82,    91,
      92,    99,   100,   102,    90,    95,    96,    97,    98,   103,
     124,     0,   123,     0,   117,   119,   120,   121,   122,   393,
     418,   280,   282,   284,     0,     0,   290,   288,   286,   487,
     279,   260,   261,   262,   263,     0,   258,   267,   268,   269,
     272,   273,   275,   270,   271,   264,   265,   277,   278,   266,
     274,   276,   412,   411,   407,   408,   406,     0,   403,   405,
     409,   410,   441,     0,   444,     0,     0,   440,   434,   435,
     433,   438,   439,     0,   428,   430,   431,   436,   437,   432,
     485,   473,   475,   477,   479,   481,   483,   472,   469,   470,
     471,     0,   459,   460,   464,   465,   462,   466,   467,   468,
     463,     0,   353,   172,     0,   357,   355,   360,     0,   349,
     350,     0,   337,   338,   340,   352,   341,   342,   343,   359,
     344,   345,   346,   347,   348,   387,     0,     0,   385,   386,
     389,   390,     0,   374,   375,   377,   378,   379,   380,   381,
     382,   383,   384,   228,   230,   225,     0,   223,   226,   227,
       0,   577,   579,     0,   582,     0,     0,   586,   590,     0,
       0,     0,   595,   602,   604,   606,   575,   573,   574,     0,
     555,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,   633,     0,   630,
     632,   624,   623,     0,   620,   622,    48,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    59,     0,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   257,     0,     0,
     402,     0,     0,     0,     0,     0,     0,   427,     0,     0,
       0,     0,     0,     0,     0,   457,     0,   327,     0,     0,
       0,     0,     0,     0,     0,   335,     0,     0,     0,     0,
     372,     0,     0,     0,     0,   222,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   554,     0,     0,   629,     0,     0,   619,
      52,    45,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,     0,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   537,     0,     0,    75,
       0,   126,   118,     0,     0,     0,     0,     0,   295,   296,
       0,     0,     0,     0,   259,     0,   404,     0,   443,     0,
     446,   447,   429,     0,     0,     0,     0,     0,     0,     0,
     461,     0,     0,   351,     0,     0,     0,   362,   339,     0,
     391,   392,   376,     0,     0,   224,   576,     0,     0,   581,
       0,   584,   585,     0,     0,   592,   593,   594,     0,     0,
       0,     0,   556,     0,   631,     0,   621,     0,     0,     0,
     609,   611,   613,   615,     0,     0,     0,     0,   133,   112,
     250,   328,   365,    42,   415,   417,   299,     0,    49,     0,
       0,     0,   450,   215,     0,     0,     0,     0,    53,   125,
     395,   420,   281,   283,   285,   292,   293,   294,   291,   289,
     287,     0,   413,   442,   445,   486,   474,   476,   478,   480,
     482,   484,   354,   173,   358,   356,   361,   388,   229,   231,
     578,   580,   583,   588,   589,   587,   591,   597,   598,   599,
     600,   601,   596,   603,   605,   607,     0,   133,    46,     0,
       0,     0,     0,   159,   165,   167,   169,     0,     0,     0,
       0,     0,   182,     0,     0,   185,     0,     0,     0,   158,
       0,   139,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   153,   154,   155,   156,   151,   152,   157,     0,
     137,     0,   134,   135,   254,     0,   251,   252,   332,     0,
     329,   330,   369,     0,   366,   367,   303,     0,   300,   301,
     200,   201,     0,   196,   198,   199,     0,   209,   210,   206,
       0,   204,   207,   208,   192,     0,   189,   191,   497,     0,
     495,   454,     0,   451,   452,   219,     0,   216,   217,     0,
       0,     0,     0,     0,     0,     0,   234,   236,   237,   238,
     239,   240,   241,   527,   533,     0,     0,     0,   526,   523,
     524,   525,     0,   516,   518,   521,   519,   520,   522,   547,
     549,   546,   544,   545,     0,   540,   542,   543,     0,    55,
     399,     0,   396,   397,   424,     0,   421,   422,   491,   490,
       0,   489,   637,     0,   635,     0,    71,   627,   617,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   130,     0,
     132,     0,     0,   249,     0,   336,   325,     0,   373,   364,
       0,     0,   298,     0,     0,   195,   212,     0,   203,     0,
       0,   188,   499,     0,   494,   458,   449,     0,     0,   214,
       0,     0,     0,     0,     0,     0,     0,     0,   233,     0,
       0,     0,     0,     0,     0,   515,     0,     0,     0,   539,
     552,    57,     0,    56,     0,   394,     0,     0,   419,     0,
       0,   488,     0,     0,   634,   625,     0,     0,     0,     0,
     171,   174,   175,   176,   177,     0,   184,   178,     0,   179,
     180,   181,   140,     0,   136,     0,   253,     0,   331,     0,
     368,   323,   318,   320,   311,   312,   307,   308,   309,   310,
     316,   317,   315,   319,     0,   305,   313,   321,   322,   314,
     302,   197,   205,     0,   190,   511,     0,   509,   510,   506,
     507,   508,     0,   500,   501,   503,   504,   505,   496,     0,
     453,     0,   218,   242,   243,   244,   245,   246,   247,   235,
       0,     0,   532,   535,   536,   517,     0,     0,   541,    54,
       0,     0,   398,     0,   423,     0,   651,     0,   649,   647,
     641,   645,   646,     0,   639,   643,   644,   642,   636,   161,
     162,   163,   164,   160,   166,   168,   170,   183,   186,   138,
     255,   333,   370,     0,   304,   193,     0,     0,   498,     0,
     455,   220,   529,   530,   531,   528,   534,   548,   550,    58,
     400,   425,   492,     0,     0,     0,     0,   638,   306,     0,
     513,   502,     0,   648,     0,   640,   512,     0,   650,   655,
       0,   653,     0,     0,   652,   663,     0,     0,     0,     0,
     657,   659,   660,   661,   662,   654,     0,     0,     0,     0,
       0,   656,     0,   665,   666,   667,   658,   664
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,    33,  -821,   266,
    -821,  -821,  -821,  -821,  -821,  -821,    22,  -821,  -450,  -821,
    -821,  -821,   -74,  -821,  -821,  -821,   328,  -821,  -821,  -821,
    -821,   236,   432,   -70,   -58,   -55,   -38,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   232,   439,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,   158,  -821,     0,  -821,  -573,
       7,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   -46,  -821,  -603,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   -15,
    -821,  -821,  -821,  -821,  -821,    -8,  -596,  -821,  -821,  -821,
    -821,    -9,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
     -21,  -821,  -821,  -821,   -14,   397,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   -22,  -821,  -821,  -821,  -821,  -821,  -821,
    -820,  -821,  -821,  -821,    13,  -821,  -821,  -821,    17,   445,
    -821,  -821,  -817,  -821,  -813,  -821,   -34,  -821,   -32,  -821,
    -811,  -821,  -821,  -821,  -803,  -821,  -821,  -821,  -821,     5,
    -821,  -821,  -159,   785,  -821,  -821,  -821,  -821,  -821,    20,
    -821,  -821,  -821,    23,  -821,   424,  -821,   -42,  -821,  -821,
    -821,  -821,  -821,   -40,  -821,  -821,  -821,  -821,  -821,   -12,
    -821,  -821,  -821,    19,  -821,  -821,  -821,    24,  -821,   425,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   -25,  -821,  -821,  -821,   -20,   467,  -821,  -821,   -62,
    -821,   -50,  -821,  -821,  -821,  -821,  -821,   -26,  -821,  -821,
    -821,   -19,   457,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
     -35,  -821,  -821,  -821,     8,  -821,  -821,  -821,    12,  -821,
     443,   249,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -802,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,    18,  -821,  -821,  -821,  -145,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,     3,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,     1,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,   273,   416,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -344,   415,  -821,
    -821,  -821,  -821,  -821,  -821,   302,   431,  -821,  -821,  -821,
     -11,  -821,  -821,  -152,  -821,  -821,  -821,  -821,  -821,  -821,
    -168,  -821,  -821,  -184,  -821,  -821,  -821,  -821,  -821
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   604,    92,    93,    43,    72,    89,    90,   619,   799,
     892,   893,   352,    45,    74,   101,   102,   103,   361,    47,
      75,   139,   140,   141,   142,   143,   144,   145,   146,   380,
     147,   371,    49,    76,   173,   174,   175,   401,   176,   148,
     372,   149,   373,   150,   374,   711,   712,   713,   839,   690,
     691,   692,   820,  1013,   693,   821,   694,   822,   695,   823,
     696,   697,   439,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   829,   707,   708,   832,   151,   390,   745,   746,
     747,   859,   152,   387,   732,   733,   734,   735,   153,   389,
     740,   741,   742,   743,   154,   388,   155,   393,   756,   757,
     758,   868,    65,    84,   306,   307,   308,   452,   309,   453,
     156,   394,   765,   766,   767,   768,   769,   770,   771,   772,
     157,   381,   715,   716,   717,   842,    51,    77,   195,   196,
     197,   407,   198,   408,   199,   409,   200,   414,   201,   413,
     202,   412,   628,   203,   204,   158,   386,   727,   728,   729,
     851,   944,   945,   159,   382,    59,    81,   719,   720,   721,
     845,    61,    82,   271,   272,   273,   274,   275,   276,   277,
     438,   278,   442,   279,   441,   280,   281,   443,   282,   160,
     383,   723,   724,   725,   848,    63,    83,   292,   293,   294,
     295,   296,   447,   297,   298,   299,   300,   206,   405,   801,
     802,   803,   894,    53,    78,   217,   218,   219,   418,   161,
     384,   162,   385,   209,   406,   805,   806,   807,   897,    55,
      79,   233,   234,   235,   421,   236,   237,   423,   238,   239,
     163,   392,   752,   753,   754,   865,    57,    80,   251,   252,
     253,   254,   429,   255,   430,   256,   431,   257,   432,   258,
     433,   259,   434,   260,   428,   211,   415,   810,   811,   900,
     164,   391,   749,   750,   862,   962,   963,   964,   965,   966,
    1026,   967,   165,   395,   782,   783,   784,   879,  1035,   785,
     786,   880,   787,   788,   166,   167,   397,   794,   795,   796,
     886,   797,   887,   168,   398,    67,    85,   329,   330,   331,
     332,   457,   333,   458,   334,   335,   460,   336,   337,   338,
     463,   655,   339,   464,   340,   341,   342,   343,   468,   662,
     344,   469,   345,   470,   346,   471,   104,   363,   105,   364,
     106,   365,   169,   369,   370,    71,    87,   353,   354,   355,
     477,   107,   362,    69,    86,   348,   349,   350,   474,   813,
     814,   902,  1003,  1004,  1005,  1006,  1045,  1007,  1043,  1060,
    1061,  1062,  1069,  1070,  1071,  1076,  1072,  1073,  1074
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
     100,   138,   172,   190,   213,   227,   247,   191,   269,   288,
     305,   326,   779,   739,   177,   207,   220,   231,   249,   192,
     283,   301,   193,   327,   709,   489,   178,   208,   221,   232,
     250,   937,   284,   302,   938,   328,   270,   289,   939,   194,
     942,   290,   210,   291,   214,   228,   215,   229,   943,   949,
      40,    33,   108,    34,    94,    35,   109,   854,   110,   730,
     855,   111,   112,   113,    32,   205,   216,   230,   248,   351,
     303,   304,   262,   730,   737,   241,   738,   170,   171,   122,
     263,   629,   808,    44,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   635,   636,   637,   857,   123,   124,   858,
     367,   263,    46,   264,   265,   368,    48,   266,   267,   268,
     123,   124,   122,   303,   304,   399,   955,   956,   123,   124,
     400,   125,   126,   127,   128,   129,    50,   130,   123,   124,
     123,   124,   131,    52,   403,   416,   773,    54,   731,   404,
     417,   132,    99,   863,   133,   678,   864,   240,   123,   124,
      56,   134,    58,   241,   242,   243,   244,   245,   246,   135,
     136,   673,   903,   137,    60,   904,   674,   675,   676,   677,
     678,   679,   680,   681,   682,   683,   684,   685,   686,   687,
     688,    62,   123,   124,  1065,    64,    95,  1066,  1067,  1068,
     263,  1009,  1010,  1011,  1012,    96,    97,    98,    66,   789,
     790,    99,   419,   937,   426,  1063,   938,   420,  1064,   427,
     939,    68,   942,    99,    99,    36,    37,    38,    39,   454,
     943,   949,    99,   263,   455,    70,    99,   774,   775,   776,
     777,   472,    99,   121,    99,    91,   473,   122,   653,   654,
     123,   124,   263,   285,   264,   265,   286,   287,   212,   475,
     671,   347,    99,   478,   476,   123,   124,   478,   479,   123,
     124,   739,   593,   399,   356,   357,   923,   358,   816,   114,
     115,   116,   117,   187,   475,   478,   188,   122,   359,   817,
     818,   779,   657,   658,   659,   660,    99,   179,   360,   180,
     366,   122,   375,   100,   376,   123,   124,   181,   182,   183,
     184,   185,   186,   377,   222,   223,   224,   225,   226,   123,
     124,    99,   378,   187,   379,   403,   188,   131,   661,   996,
     819,   997,   998,   836,   189,   138,   396,   187,   837,   172,
     188,   759,   760,   761,   762,   763,   764,   402,   836,   482,
     410,   177,   190,   838,    99,   213,   191,   625,   626,   627,
     860,   877,   227,   178,   207,   861,   878,   220,   192,    99,
     884,   193,   247,    99,   231,   885,   208,   411,   888,   221,
     472,   436,   269,   889,   249,   890,   232,   288,   194,   422,
     424,   210,   435,   836,   283,   214,   250,   215,  1019,   301,
     480,   481,   228,   425,   229,   437,   284,   416,   326,    99,
     270,   302,  1020,  1023,   205,   289,   440,   216,  1024,   290,
     327,   291,   444,    99,   230,   445,   454,   114,   115,   116,
     117,  1031,   328,   120,   248,   122,   263,   123,   124,   419,
     426,  1046,  1080,   446,  1040,  1041,  1047,  1081,  1032,  1033,
    1034,   448,   449,   123,   124,   451,   182,   183,   450,   185,
     186,   456,   459,   461,   462,   465,   466,   467,   483,   484,
     485,   187,   486,   487,   188,   490,   491,   492,   493,   494,
     495,   496,   189,   497,   498,   499,   500,   501,   502,   503,
     504,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   505,   506,   507,   508,   509,
     510,   511,   324,   325,   512,   513,   514,   515,   516,   517,
     518,   520,   521,   523,   138,   524,   525,   526,   590,   591,
     592,   172,   689,   689,   527,   528,   529,   530,   531,   532,
     533,    99,   535,   177,   537,   539,   538,   543,   544,   540,
     541,   778,   791,   326,   545,   178,   546,    99,   547,   548,
     549,   551,   552,   780,   792,   327,   553,   554,   555,   556,
     557,   559,   560,   561,   563,   781,   793,   328,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   564,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   649,   579,   580,
     581,   583,   585,   587,   599,   605,   911,   588,   589,   594,
     595,   596,   597,   598,   600,   601,   602,   744,   606,    34,
     668,   607,   608,   609,   841,   611,   610,   612,   613,   622,
     736,   614,   615,   616,   617,   618,   620,   621,   623,   624,
     630,   631,   666,   656,   667,   710,   632,   633,   634,   638,
     639,   640,   641,   642,   643,   644,   645,   646,   647,   648,
     714,   718,   722,   726,   748,   751,   755,   650,   651,   800,
     804,   812,   824,   652,   825,   826,   827,   828,   830,   663,
     831,   833,   834,   664,   665,   835,   840,   844,   843,   846,
     847,   849,   850,   853,   852,   488,   867,   856,   866,   870,
     869,   871,   872,   873,   874,   875,   876,   881,   882,   883,
     891,   896,   895,   898,   899,   913,   905,   901,   906,   907,
     908,   909,   910,   915,   918,   953,   912,   980,   914,   916,
     981,   917,   919,   920,   986,   973,   921,   974,   975,   976,
     977,   978,   982,   983,   984,   987,   989,   990,  1050,   995,
    1021,  1022,  1014,  1027,  1015,  1016,  1028,  1029,  1017,  1018,
    1025,  1030,   689,  1044,  1049,   689,  1052,  1054,   190,  1057,
     603,   269,   191,  1059,   288,  1036,  1037,   931,  1077,  1078,
     207,   932,  1079,   283,   192,  1053,   301,   193,   957,   947,
    1082,   247,   208,   933,   305,   284,   934,  1038,   302,   270,
     960,   948,   289,   249,   194,   936,   290,   210,   291,  1039,
     778,  1042,   961,   935,   791,   250,   958,   940,  1056,   941,
     213,  1058,   780,   227,   669,   815,   792,   672,   999,  1087,
     205,   519,   220,  1083,   781,   231,  1084,  1085,   793,   946,
    1001,   924,   522,   922,   221,   954,   951,   232,   952,   972,
     959,   565,  1002,   248,   971,   979,  1000,   926,   950,   925,
     214,   534,   215,   228,  1048,   229,   261,   928,   927,   930,
     558,   992,   929,   994,   991,   970,   562,   969,   993,   550,
     809,   968,   216,   542,  1051,   230,   536,   985,   582,   988,
     798,   670,  1008,   586,  1055,  1075,  1086,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   584,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   931,
       0,     0,     0,   932,     0,   957,     0,     0,     0,     0,
       0,   947,     0,     0,     0,   933,     0,   960,   934,     0,
       0,     0,   999,   948,     0,     0,     0,   936,     0,   961,
       0,     0,     0,   958,  1001,   935,     0,     0,     0,   940,
       0,   941,     0,     0,     0,     0,  1002,     0,     0,     0,
    1000,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   946,     0,     0,     0,     0,     0,   959
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,   615,   609,    76,    77,    78,    79,    80,    77,
      82,    83,    77,    85,   597,   369,    76,    77,    78,    79,
      80,   851,    82,    83,   851,    85,    82,    83,   851,    77,
     851,    83,    77,    83,    78,    79,    78,    79,   851,   851,
      17,     5,     7,     7,    10,     9,    11,     3,    13,    90,
       6,    16,    17,    18,     0,    77,    78,    79,    80,    12,
      97,    98,    19,    90,    91,    88,    93,    14,    15,    47,
      48,   531,    95,     7,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   543,   544,   545,     3,    65,    66,     6,
       3,    48,     7,    50,    51,     8,     7,    54,    55,    56,
      65,    66,    47,    97,    98,     3,    84,    85,    65,    66,
       8,    76,    77,    78,    79,    80,     7,    82,    65,    66,
      65,    66,    87,     7,     3,     3,    19,     7,   169,     8,
       8,    96,   169,     3,    99,    28,     6,    82,    65,    66,
       7,   106,     7,    88,    89,    90,    91,    92,    93,   114,
     115,    19,     3,   118,     7,     6,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,     7,    65,    66,   145,     7,   142,   148,   149,   150,
      48,    20,    21,    22,    23,   151,   152,   153,     7,   116,
     117,   169,     3,  1023,     3,     3,  1023,     8,     6,     8,
    1023,     7,  1023,   169,   169,   169,   170,   171,   172,     3,
    1023,  1023,   169,    48,     8,     7,   169,   110,   111,   112,
     113,     3,   169,    46,   169,   169,     8,    47,   133,   134,
      65,    66,    48,    49,    50,    51,    52,    53,    58,     3,
     594,   143,   169,     3,     8,    65,    66,     3,     8,    65,
      66,   857,     8,     3,     6,     3,   839,     4,     8,    39,
      40,    41,    42,    83,     3,     3,    86,    47,     8,     8,
       8,   884,   136,   137,   138,   139,   169,    57,     3,    59,
       4,    47,     4,   367,     4,    65,    66,    67,    68,    69,
      70,    71,    72,     4,    60,    61,    62,    63,    64,    65,
      66,   169,     4,    83,     4,     3,    86,    87,   172,   144,
       8,   146,   147,     3,    94,   399,     4,    83,     8,   403,
      86,   100,   101,   102,   103,   104,   105,     4,     3,   169,
       4,   403,   416,     8,   169,   419,   416,    73,    74,    75,
       3,     3,   426,   403,   416,     8,     8,   419,   416,   169,
       3,   416,   436,   169,   426,     8,   416,     4,     3,   419,
       3,     3,   446,     8,   436,     8,   426,   451,   416,     4,
       4,   416,     8,     3,   446,   419,   436,   419,     8,   451,
     357,   358,   426,     4,   426,     8,   446,     3,   472,   169,
     446,   451,     8,     3,   416,   451,     4,   419,     8,   451,
     472,   451,     4,   169,   426,     8,     3,    39,    40,    41,
      42,     8,   472,    45,   436,    47,    48,    65,    66,     3,
       3,     3,     3,     3,     8,     8,     8,     8,   107,   108,
     109,     4,     4,    65,    66,     3,    68,    69,     8,    71,
      72,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,    83,     4,     4,    86,     4,     4,     4,     4,     4,
     170,   170,    94,   170,   170,   170,     4,     4,     4,     4,
       4,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,     4,     4,     4,     4,     4,
       4,     4,   140,   141,     4,     4,     4,     4,   170,     4,
       4,     4,   172,     4,   588,     4,     4,     4,   485,   486,
     487,   595,   596,   597,     4,   170,   172,     4,     4,     4,
       4,   169,     4,   595,     4,     4,   170,     4,     4,   170,
     170,   615,   616,   617,     4,   595,     4,   169,     4,     4,
       4,     4,     4,   615,   616,   617,   170,     4,     4,     4,
     172,     4,   172,   172,     4,   615,   616,   617,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,     4,   172,     4,     4,   170,     4,   170,
     170,     4,     4,   172,   172,   172,     4,   564,     4,     4,
       4,     4,     4,     4,   169,   169,   172,     7,     7,     7,
       7,     7,     7,     5,     5,     5,     5,    81,     5,     7,
     587,     5,     5,     5,     3,     5,     7,     5,     5,   169,
     608,     7,     7,     7,     7,     5,     5,     5,   169,   169,
     169,     7,     5,   135,     5,     7,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
       7,     7,     7,     7,     7,     7,     7,   169,   169,     7,
       7,     7,     4,   169,     4,     4,     4,     4,     4,   169,
       4,     4,     4,   169,   169,     4,     6,     3,     6,     6,
       3,     6,     3,     3,     6,   367,     3,     6,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     169,     3,     6,     6,     3,   172,     6,     8,     4,     4,
       4,     4,   170,     4,     4,     4,   170,     4,   170,   170,
       4,   170,   170,   170,     4,   170,   172,   170,   170,   170,
     170,   170,   170,   170,   170,     4,     6,     3,   172,     4,
       8,     8,   169,     4,   169,   169,     8,     3,   169,   169,
     169,     8,   836,     4,     4,   839,     4,     4,   842,     5,
     504,   845,   842,     7,   848,   169,   169,   851,     4,     4,
     842,   851,     4,   845,   842,   170,   848,   842,   862,   851,
       4,   865,   842,   851,   868,   845,   851,   169,   848,   845,
     862,   851,   848,   865,   842,   851,   848,   842,   848,   169,
     884,   169,   862,   851,   888,   865,   862,   851,   169,   851,
     894,   169,   884,   897,   588,   667,   888,   595,   902,   169,
     842,   399,   894,   172,   884,   897,   170,   170,   888,   851,
     902,   841,   403,   836,   894,   860,   854,   897,   857,   870,
     862,   454,   902,   865,   868,   877,   902,   844,   853,   842,
     894,   416,   894,   897,  1023,   897,    81,   847,   845,   850,
     446,   896,   848,   899,   894,   867,   451,   865,   897,   436,
     631,   863,   894,   426,  1029,   897,   419,   884,   472,   888,
     617,   589,   903,   478,  1046,  1063,  1080,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   475,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1023,
      -1,    -1,    -1,  1023,    -1,  1029,    -1,    -1,    -1,    -1,
      -1,  1023,    -1,    -1,    -1,  1023,    -1,  1029,  1023,    -1,
      -1,    -1,  1046,  1023,    -1,    -1,    -1,  1023,    -1,  1029,
      -1,    -1,    -1,  1029,  1046,  1023,    -1,    -1,    -1,  1023,
      -1,  1023,    -1,    -1,    -1,    -1,  1046,    -1,    -1,    -1,
    1046,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1023,    -1,    -1,    -1,    -1,    -1,  1029
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,     0,     5,     7,     9,   169,   170,   171,   172,
     190,   191,   192,   197,     7,   206,     7,   212,     7,   225,
       7,   319,     7,   396,     7,   412,     7,   429,     7,   348,
       7,   354,     7,   378,     7,   295,     7,   488,     7,   536,
       7,   528,   198,   193,   207,   213,   226,   320,   397,   413,
     430,   349,   355,   379,   296,   489,   537,   529,   190,   199,
     200,   169,   195,   196,    10,   142,   151,   152,   153,   169,
     205,   208,   209,   210,   519,   521,   523,   534,     7,    11,
      13,    16,    17,    18,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    66,    76,    77,    78,    79,    80,
      82,    87,    96,    99,   106,   114,   115,   118,   205,   214,
     215,   216,   217,   218,   219,   220,   221,   223,   232,   234,
     236,   269,   275,   281,   287,   289,   303,   313,   338,   346,
     372,   402,   404,   423,   453,   465,   477,   478,   486,   525,
      14,    15,   205,   227,   228,   229,   231,   402,   404,    57,
      59,    67,    68,    69,    70,    71,    72,    83,    86,    94,
     205,   216,   217,   218,   219,   321,   322,   323,   325,   327,
     329,   331,   333,   336,   337,   372,   390,   402,   404,   406,
     423,   448,    58,   205,   329,   331,   372,   398,   399,   400,
     402,   404,    60,    61,    62,    63,    64,   205,   329,   331,
     372,   402,   404,   414,   415,   416,   418,   419,   421,   422,
      82,    88,    89,    90,    91,    92,    93,   205,   372,   402,
     404,   431,   432,   433,   434,   436,   438,   440,   442,   444,
     446,   346,    19,    48,    50,    51,    54,    55,    56,   205,
     254,   356,   357,   358,   359,   360,   361,   362,   364,   366,
     368,   369,   371,   402,   404,    49,    52,    53,   205,   254,
     360,   366,   380,   381,   382,   383,   384,   386,   387,   388,
     389,   402,   404,    97,    98,   205,   297,   298,   299,   301,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   140,   141,   205,   402,   404,   490,
     491,   492,   493,   495,   497,   498,   500,   501,   502,   505,
     507,   508,   509,   510,   513,   515,   517,   143,   538,   539,
     540,    12,   205,   530,   531,   532,     6,     3,     4,     8,
       3,   211,   535,   520,   522,   524,     4,     3,     8,   526,
     527,   224,   233,   235,   237,     4,     4,     4,     4,     4,
     222,   314,   347,   373,   403,   405,   339,   276,   288,   282,
     270,   454,   424,   290,   304,   466,     4,   479,   487,     3,
       8,   230,     4,     3,     8,   391,   407,   324,   326,   328,
       4,     4,   334,   332,   330,   449,     3,     8,   401,     3,
       8,   417,     4,   420,     4,     4,     3,     8,   447,   435,
     437,   439,   441,   443,   445,     8,     3,     8,   363,   255,
       4,   367,   365,   370,     4,     8,     3,   385,     4,     4,
       8,     3,   300,   302,     3,     8,     4,   494,   496,     4,
     499,     4,     4,   503,   506,     4,     4,     4,   511,   514,
     516,   518,     3,     8,   541,     3,     8,   533,     3,     8,
     190,   190,   169,     4,     4,     4,     4,     4,   209,   530,
       4,     4,     4,     4,     4,   170,   170,   170,   170,   170,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   170,     4,     4,   215,
       4,   172,   228,     4,     4,     4,     4,     4,   170,   172,
       4,     4,     4,     4,   322,     4,   399,     4,   170,     4,
     170,   170,   415,     4,     4,     4,     4,     4,     4,     4,
     433,     4,     4,   170,     4,     4,     4,   172,   358,     4,
     172,   172,   382,     4,     4,   298,   172,     4,     4,   170,
       4,   170,   170,     4,     4,   172,   172,   172,     4,     4,
       4,     4,   491,     4,   539,     4,   531,     4,     7,     7,
     190,   190,   190,     8,     7,     7,     7,     7,     5,   169,
       5,     5,     5,   192,   194,   169,     5,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     5,   201,
       5,     5,   169,   169,   169,    73,    74,    75,   335,   201,
     169,     7,   169,   169,   169,   201,   201,   201,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   190,
     169,   169,   169,   133,   134,   504,   135,   136,   137,   138,
     139,   172,   512,   169,   169,   169,     5,     5,   190,   214,
     538,   530,   227,    19,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   205,
     242,   243,   244,   247,   249,   251,   253,   254,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   266,   267,   242,
       7,   238,   239,   240,     7,   315,   316,   317,     7,   350,
     351,   352,     7,   374,   375,   376,     7,   340,   341,   342,
      90,   169,   277,   278,   279,   280,   199,    91,    93,   279,
     283,   284,   285,   286,    81,   271,   272,   273,     7,   455,
     456,     7,   425,   426,   427,     7,   291,   292,   293,   100,
     101,   102,   103,   104,   105,   305,   306,   307,   308,   309,
     310,   311,   312,    19,   110,   111,   112,   113,   205,   256,
     402,   404,   467,   468,   469,   472,   473,   475,   476,   116,
     117,   205,   402,   404,   480,   481,   482,   484,   490,   202,
       7,   392,   393,   394,     7,   408,   409,   410,    95,   434,
     450,   451,     7,   542,   543,   238,     8,     8,     8,     8,
     245,   248,   250,   252,     4,     4,     4,     4,     4,   265,
       4,     4,   268,     4,     4,     4,     3,     8,     8,   241,
       6,     3,   318,     6,     3,   353,     6,     3,   377,     6,
       3,   343,     6,     3,     3,     6,     6,     3,     6,   274,
       3,     8,   457,     3,     6,   428,     6,     3,   294,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   470,
     474,     4,     4,     4,     3,     8,   483,   485,     3,     8,
       8,   169,   203,   204,   395,     6,     3,   411,     6,     3,
     452,     8,   544,     3,     6,     6,     4,     4,     4,     4,
     170,   172,   170,   172,   170,     4,   170,   170,     4,   170,
     170,   172,   243,   242,   240,   321,   317,   356,   352,   380,
     376,   205,   216,   217,   218,   219,   254,   313,   325,   327,
     329,   331,   333,   337,   344,   345,   372,   402,   404,   448,
     342,   278,   284,     4,   272,    84,    85,   205,   254,   372,
     402,   404,   458,   459,   460,   461,   462,   464,   456,   431,
     427,   297,   293,   170,   170,   170,   170,   170,   170,   306,
       4,     4,   170,   170,   170,   468,     4,     4,   481,     6,
       3,   398,   394,   414,   410,     4,   144,   146,   147,   205,
     254,   402,   404,   545,   546,   547,   548,   550,   543,    20,
      21,    22,    23,   246,   169,   169,   169,   169,   169,     8,
       8,     8,     8,     3,     8,   169,   463,     4,     8,     3,
       8,     8,   107,   108,   109,   471,   169,   169,   169,   169,
       8,     8,   169,   551,     4,   549,     3,     8,   345,     4,
     172,   460,     4,   170,     4,   546,   169,     5,   169,     7,
     552,   553,   554,     3,     6,   145,   148,   149,   150,   555,
     556,   557,   559,   560,   561,   553,   558,     4,     4,     4,
       3,     8,     4,   172,   170,   170,   556,   169
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   173,   175,   174,   176,   174,   177,   174,   178,   174,
     179,   174,   180,   174,   181,   174,   182,   174,   183,   174,
     184,   174,   185,   174,   186,   174,   187,   174,   188,   174,
     189,   174,   190,   190,   190,   190,   190,   190,   190,   191,
     193,   192,   194,   195,   195,   196,   196,   198,   197,   199,
     199,   200,   200,   202,   201,   203,   203,   204,   204,   205,
     207,   206,   208,   208,   209,   209,   209,   209,   209,   209,
     211,   210,   213,   212,   214,   214,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   216,   217,   218,   219,
     220,   222,   221,   224,   223,   226,   225,   227,   227,   228,
     228,   228,   228,   228,   230,   229,   231,   233,   232,   235,
     234,   237,   236,   238,   238,   239,   239,   241,   240,   242,
     242,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   245,
     244,   246,   246,   246,   246,   248,   247,   250,   249,   252,
     251,   253,   255,   254,   256,   257,   258,   259,   260,   261,
     262,   263,   265,   264,   266,   268,   267,   270,   269,   271,
     271,   272,   274,   273,   276,   275,   277,   277,   278,   278,
     279,   280,   282,   281,   283,   283,   284,   284,   284,   285,
     286,   288,   287,   290,   289,   291,   291,   292,   292,   294,
     293,   296,   295,   297,   297,   297,   298,   298,   300,   299,
     302,   301,   304,   303,   305,   305,   306,   306,   306,   306,
     306,   306,   307,   308,   309,   310,   311,   312,   314,   313,
     315,   315,   316,   316,   318,   317,   320,   319,   321,   321,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     324,   323,   326,   325,   328,   327,   330,   329,   332,   331,
     334,   333,   335,   335,   335,   336,   337,   339,   338,   340,
     340,   341,   341,   343,   342,   344,   344,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   347,   346,   349,   348,   350,   350,
     351,   351,   353,   352,   355,   354,   356,   356,   357,   357,
     358,   358,   358,   358,   358,   358,   358,   358,   358,   358,
     359,   360,   361,   363,   362,   365,   364,   367,   366,   368,
     370,   369,   371,   373,   372,   374,   374,   375,   375,   377,
     376,   379,   378,   380,   380,   381,   381,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   383,   385,   384,   386,
     387,   388,   389,   391,   390,   392,   392,   393,   393,   395,
     394,   397,   396,   398,   398,   399,   399,   399,   399,   399,
     399,   399,   401,   400,   403,   402,   405,   404,   407,   406,
     408,   408,   409,   409,   411,   410,   413,   412,   414,   414,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   417,   416,   418,   420,   419,   421,   422,   424,   423,
     425,   425,   426,   426,   428,   427,   430,   429,   431,   431,
     432,   432,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   435,   434,   437,   436,   439,   438,   441,
     440,   443,   442,   445,   444,   447,   446,   449,   448,   450,
     450,   452,   451,   454,   453,   455,   455,   457,   456,   458,
     458,   459,   459,   460,   460,   460,   460,   460,   460,   460,
     461,   463,   462,   464,   466,   465,   467,   467,   468,   468,
     468,   468,   468,   468,   468,   468,   468,   470,   469,   471,
     471,   471,   472,   474,   473,   475,   476,   477,   479,   478,
     480,   480,   481,   481,   481,   481,   481,   483,   482,   485,
     484,   487,   486,   489,   488,   490,   490,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   492,   494,   493,   496,
     495,   497,   499,   498,   500,   501,   503,   502,   504,   504,
     506,   505,   507,   508,   509,   511,   510,   512,   512,   512,
     512,   512,   514,   513,   516,   515,   518,   517,   520,   519,
     522,   521,   524,   523,   526,   525,   527,   525,   529,   528,
     530,   530,   531,   531,   533,   532,   535,   534,   537,   536,
     538,   538,   539,   541,   540,   542,   542,   544,   543,   545,
     545,   546,   546,   546,   546,   546,   546,   546,   547,   549,
     548,   551,   550,   552,   552,   554,   553,   555,   555,   556,
     556,   556,   556,   558,   557,   559,   560,   561
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     0,     4,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       1,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     0,     6,     0,     4,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"config-control\"",
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"preferred-lifetime\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "$@15", "value", "sub_json", "map2", "$@16", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@17", "list_content",
  "not_empty_list", "list_strings", "$@18", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@19",
  "global_objects", "global_object", "dhcp6_object", "$@20", "sub_dhcp6",
  "$@21", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "server_tag", "$@22", "interfaces_config",
  "$@23", "sub_interfaces6", "$@24", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@25", "re_detect",
  "lease_database", "$@26", "hosts_database", "$@27", "hosts_databases",
  "$@28", "database_list", "not_empty_database_list", "database", "$@29",
  "database_map_params", "database_map_param", "database_type", "$@30",
  "db_type", "user", "$@31", "password", "$@32", "host", "$@33", "port",
  "name", "$@34", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@35", "max_reconnect_tries", "keyspace", "$@36",
  "sanity_checks", "$@37", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@38", "mac_sources", "$@39", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@40",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@41",
  "hooks_libraries", "$@42", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@43",
  "sub_hooks_library", "$@44", "hooks_params", "hooks_param", "library",
  "$@45", "parameters", "$@46", "expired_leases_processing", "$@47",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@48",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@49",
  "sub_subnet6", "$@50", "subnet6_params", "subnet6_param", "subnet",
  "$@51", "interface", "$@52", "interface_id", "$@53", "client_class",
  "$@54", "require_client_classes", "$@55", "reservation_mode", "$@56",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@57",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@58", "shared_network_params", "shared_network_param",
  "option_def_list", "$@59", "sub_option_def_list", "$@60",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@61", "sub_option_def", "$@62",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@63",
  "option_def_record_types", "$@64", "space", "$@65", "option_def_space",
  "option_def_encapsulate", "$@66", "option_def_array", "option_data_list",
  "$@67", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@68", "sub_option_data", "$@69",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@70",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@71", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@72", "sub_pool6", "$@73",
  "pool_params", "pool_param", "pool_entry", "$@74", "user_context",
  "$@75", "comment", "$@76", "pd_pools_list", "$@77",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@78", "sub_pd_pool", "$@79", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@80", "pd_prefix_len", "excluded_prefix", "$@81",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@82",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@83", "sub_reservation", "$@84", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@85", "prefixes", "$@86", "duid", "$@87", "hw_address", "$@88",
  "hostname", "$@89", "flex_id_value", "$@90",
  "reservation_client_classes", "$@91", "relay", "$@92", "relay_map",
  "ip_address", "$@93", "client_classes", "$@94", "client_classes_list",
  "client_class_entry", "$@95", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@96", "only_if_required",
  "server_id", "$@97", "server_id_params", "server_id_param",
  "server_id_type", "$@98", "duid_type", "htype", "identifier", "$@99",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@100",
  "control_socket_params", "control_socket_param", "socket_type", "$@101",
  "socket_name", "$@102", "dhcp_ddns", "$@103", "sub_dhcp_ddns", "$@104",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@105", "server_ip", "$@106", "server_port",
  "sender_ip", "$@107", "sender_port", "max_queue_size", "ncr_protocol",
  "$@108", "ncr_protocol_value", "ncr_format", "$@109",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@110", "replace_client_name_value",
  "generated_prefix", "$@111", "hostname_char_set", "$@112",
  "hostname_char_replacement", "$@113", "dhcp4_json_object", "$@114",
  "dhcpddns_json_object", "$@115", "control_agent_json_object", "$@116",
  "config_control", "$@117", "$@118", "sub_config_control", "$@119",
  "config_control_params", "config_control_param", "config_databases",
  "$@120", "logging_object", "$@121", "sub_logging", "$@122",
  "logging_params", "logging_param", "loggers", "$@123", "loggers_entries",
  "logger_entry", "$@124", "logger_params", "logger_param", "debuglevel",
  "severity", "$@125", "output_options_list", "$@126",
  "output_options_list_content", "output_entry", "$@127",
  "output_params_list", "output_params", "output", "$@128", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   255,   255,   255,   256,   256,   257,   257,   258,   258,
     259,   259,   260,   260,   261,   261,   262,   262,   263,   263,
     264,   264,   265,   265,   266,   266,   267,   267,   268,   268,
     269,   269,   277,   278,   279,   280,   281,   282,   283,   286,
     291,   291,   302,   305,   306,   309,   313,   320,   320,   327,
     328,   331,   335,   342,   342,   349,   350,   353,   357,   368,
     378,   378,   393,   394,   398,   399,   400,   401,   402,   403,
     406,   406,   421,   421,   430,   431,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   468,   473,   478,   483,
     488,   493,   493,   501,   501,   512,   512,   521,   522,   525,
     526,   527,   528,   529,   532,   532,   542,   548,   548,   560,
     560,   572,   572,   582,   583,   586,   587,   590,   590,   600,
     601,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     613,   614,   615,   616,   617,   618,   619,   620,   621,   624,
     624,   631,   632,   633,   634,   637,   637,   645,   645,   653,
     653,   661,   666,   666,   674,   679,   684,   689,   694,   699,
     704,   709,   714,   714,   722,   727,   727,   735,   735,   745,
     746,   748,   750,   750,   768,   768,   778,   779,   782,   783,
     786,   791,   796,   796,   806,   807,   810,   811,   812,   815,
     820,   827,   827,   837,   837,   847,   848,   851,   852,   855,
     855,   865,   865,   875,   876,   877,   880,   881,   884,   884,
     892,   892,   900,   900,   911,   912,   915,   916,   917,   918,
     919,   920,   923,   928,   933,   938,   943,   948,   956,   956,
     969,   970,   973,   974,   981,   981,  1007,  1007,  1018,  1019,
    1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,
    1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,
    1045,  1045,  1053,  1053,  1061,  1061,  1069,  1069,  1077,  1077,
    1087,  1087,  1094,  1095,  1096,  1099,  1104,  1112,  1112,  1123,
    1124,  1128,  1129,  1132,  1132,  1140,  1141,  1144,  1145,  1146,
    1147,  1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,
    1157,  1158,  1159,  1160,  1167,  1167,  1180,  1180,  1189,  1190,
    1193,  1194,  1199,  1199,  1214,  1214,  1228,  1229,  1232,  1233,
    1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,
    1248,  1250,  1255,  1257,  1257,  1265,  1265,  1273,  1273,  1281,
    1283,  1283,  1291,  1300,  1300,  1312,  1313,  1318,  1319,  1324,
    1324,  1336,  1336,  1348,  1349,  1354,  1355,  1360,  1361,  1362,
    1363,  1364,  1365,  1366,  1367,  1368,  1371,  1373,  1373,  1381,
    1383,  1385,  1390,  1398,  1398,  1410,  1411,  1414,  1415,  1418,
    1418,  1428,  1428,  1437,  1438,  1441,  1442,  1443,  1444,  1445,
    1446,  1447,  1450,  1450,  1458,  1458,  1483,  1483,  1513,  1513,
    1525,  1526,  1529,  1530,  1533,  1533,  1545,  1545,  1557,  1558,
    1561,  1562,  1563,  1564,  1565,  1566,  1567,  1568,  1569,  1570,
    1571,  1574,  1574,  1582,  1587,  1587,  1595,  1600,  1608,  1608,
    1618,  1619,  1622,  1623,  1626,  1626,  1635,  1635,  1644,  1645,
    1648,  1649,  1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,
    1661,  1662,  1663,  1666,  1666,  1676,  1676,  1686,  1686,  1694,
    1694,  1702,  1702,  1710,  1710,  1718,  1718,  1731,  1731,  1741,
    1742,  1745,  1745,  1756,  1756,  1766,  1767,  1770,  1770,  1780,
    1781,  1784,  1785,  1788,  1789,  1790,  1791,  1792,  1793,  1794,
    1797,  1799,  1799,  1807,  1815,  1815,  1827,  1828,  1831,  1832,
    1833,  1834,  1835,  1836,  1837,  1838,  1839,  1842,  1842,  1849,
    1850,  1851,  1854,  1859,  1859,  1867,  1872,  1879,  1886,  1886,
    1896,  1897,  1900,  1901,  1902,  1903,  1904,  1907,  1907,  1915,
    1915,  1925,  1925,  1937,  1937,  1947,  1948,  1951,  1952,  1953,
    1954,  1955,  1956,  1957,  1958,  1959,  1960,  1961,  1962,  1963,
    1964,  1965,  1966,  1967,  1968,  1969,  1972,  1977,  1977,  1985,
    1985,  1993,  1998,  1998,  2006,  2011,  2016,  2016,  2024,  2025,
    2028,  2028,  2036,  2041,  2046,  2051,  2051,  2059,  2062,  2065,
    2068,  2071,  2077,  2077,  2085,  2085,  2093,  2093,  2103,  2103,
    2110,  2110,  2117,  2117,  2126,  2126,  2135,  2135,  2146,  2146,
    2156,  2157,  2161,  2162,  2165,  2165,  2180,  2180,  2190,  2190,
    2201,  2202,  2206,  2210,  2210,  2222,  2223,  2227,  2227,  2235,
    2236,  2239,  2240,  2241,  2242,  2243,  2244,  2245,  2248,  2253,
    2253,  2261,  2261,  2271,  2272,  2275,  2275,  2283,  2284,  2287,
    2288,  2289,  2290,  2293,  2293,  2301,  2306,  2311
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
#line 4978 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2316 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
