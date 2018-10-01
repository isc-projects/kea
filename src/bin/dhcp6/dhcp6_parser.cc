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
      case 189: // value
      case 193: // map_value
      case 243: // db_type
      case 332: // hr_mode
      case 468: // duid_type
      case 501: // ncr_protocol_value
      case 509: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 171: // "boolean"
        value.move< bool > (that.value);
        break;

      case 170: // "floating point"
        value.move< double > (that.value);
        break;

      case 169: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 168: // "constant string"
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
      case 189: // value
      case 193: // map_value
      case 243: // db_type
      case 332: // hr_mode
      case 468: // duid_type
      case 501: // ncr_protocol_value
      case 509: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 171: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 170: // "floating point"
        value.copy< double > (that.value);
        break;

      case 169: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 168: // "constant string"
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
            case 168: // "constant string"

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 169: // "integer"

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 170: // "floating point"

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 171: // "boolean"

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 189: // value

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 193: // map_value

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 243: // db_type

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 332: // hr_mode

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 468: // duid_type

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 501: // ncr_protocol_value

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 509: // replace_client_name_value

#line 245 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 189: // value
      case 193: // map_value
      case 243: // db_type
      case 332: // hr_mode
      case 468: // duid_type
      case 501: // ncr_protocol_value
      case 509: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 171: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 170: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 169: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 168: // "constant string"
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
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 281 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 308 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 330 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 356 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 382 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1133 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1186 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1273 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1310 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1473 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 742 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1580 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1649 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 975 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1927 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2055 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1189 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
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
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1314 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2274 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1418 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2749 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2827 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2854 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1834 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1840 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1841 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1907 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3117 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1988 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2015 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2052 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2058 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2061 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2093 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3356 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2109 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2136 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2155 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3479 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 626:
#line 2184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 630:
#line 2200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 645:
#line 2238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3571 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3582 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3591 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 652:
#line 2265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3601 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 653:
#line 2269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 660:
#line 2283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 661:
#line 2285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 662:
#line 2291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 663:
#line 2296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 664:
#line 2301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3654 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3658 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -816;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     317,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,    59,    46,   118,   142,
     156,   198,   216,   242,   256,   273,   299,   303,   313,   314,
     318,   326,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,    46,   -89,    50,    45,    63,   204,   220,   194,
      65,   166,    51,   265,   -23,   367,   -25,    42,  -816,   286,
     305,   337,   336,   353,  -816,  -816,  -816,  -816,  -816,   360,
    -816,    68,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,   363,   364,   366,   375,   381,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,   383,  -816,  -816,  -816,    72,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   386,
    -816,    91,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,   388,   390,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,   100,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,   104,  -816,  -816,  -816,  -816,
    -816,   392,  -816,   395,   396,  -816,  -816,  -816,  -816,  -816,
    -816,   110,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   349,
     377,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   397,
    -816,  -816,   399,  -816,  -816,  -816,   405,  -816,  -816,   402,
     422,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,   434,   435,  -816,  -816,  -816,  -816,
     437,   439,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,   111,  -816,  -816,  -816,   444,  -816,
    -816,   446,  -816,   447,   448,  -816,  -816,   449,   450,   451,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,   179,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,   201,  -816,  -816,  -816,
    -816,   221,  -816,  -816,  -816,    46,    46,  -816,   288,   453,
     455,   456,   458,   459,  -816,    50,  -816,    42,   460,   461,
     462,   463,   464,   330,   333,   339,   342,   343,   496,   497,
     505,   509,   510,   511,   512,   516,   517,   518,   519,   520,
     521,   522,   523,   359,   526,   527,    45,  -816,   528,   362,
      63,  -816,   530,   535,   536,   538,   539,   378,   374,   542,
     547,   548,   549,   204,  -816,   550,   220,  -816,   551,   387,
     553,   389,   394,   194,  -816,   555,   560,   561,   562,   563,
     564,   565,  -816,    65,  -816,   566,   567,   403,   569,   570,
     571,   406,  -816,    51,   572,   407,   408,  -816,   265,   576,
     578,    84,  -816,   412,   580,   581,   417,   583,   419,   420,
     586,   587,   421,   423,   424,   589,   592,   593,   594,   367,
    -816,   595,   -25,  -816,   596,    42,  -816,  -816,  -816,   597,
     598,   599,    46,    46,    46,  -816,   222,   600,   601,   602,
     603,   606,  -816,  -816,  -816,  -816,  -816,   607,   608,   609,
     610,   452,   611,   613,   614,   616,   615,   618,   619,   620,
     621,   622,  -816,   623,   624,  -816,   627,  -816,  -816,   628,
     629,   467,   468,   469,  -816,  -816,   340,   627,   470,   632,
    -816,   472,  -816,   473,  -816,   474,  -816,  -816,  -816,   627,
     627,   627,   475,   476,   477,   478,  -816,   479,   480,  -816,
     481,   482,   483,  -816,  -816,   484,  -816,  -816,  -816,   485,
      46,  -816,  -816,   486,   487,  -816,   488,  -816,  -816,    64,
     492,  -816,  -816,  -816,    57,   489,   490,   491,  -816,   655,
    -816,   656,  -816,    46,    45,   -25,  -816,  -816,  -816,  -816,
      42,    63,   141,   141,   657,   658,   659,   660,  -816,  -816,
    -816,   661,   -17,    46,    52,   582,   662,   663,   664,    33,
      74,    83,   367,  -816,  -816,   665,   666,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,   -30,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,   667,   657,  -816,   229,   231,   233,   244,  -816,  -816,
    -816,  -816,   671,   672,   673,   674,   675,  -816,   676,   677,
    -816,   678,   679,   680,  -816,   275,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,   279,  -816,   681,   612,  -816,  -816,
     682,   683,  -816,  -816,   684,   686,  -816,  -816,   685,   689,
    -816,  -816,   687,   691,  -816,  -816,  -816,   158,  -816,  -816,
    -816,   690,  -816,  -816,  -816,   232,  -816,  -816,  -816,  -816,
     285,  -816,  -816,  -816,   261,  -816,  -816,   692,   694,  -816,
    -816,   693,   697,  -816,   698,   699,   700,   701,   702,   703,
     291,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
     704,   705,   706,  -816,  -816,  -816,  -816,   292,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   293,
    -816,  -816,  -816,   295,   495,  -816,   695,   708,  -816,  -816,
     707,   709,  -816,  -816,  -816,   710,  -816,  -816,   301,  -816,
     711,  -816,  -816,  -816,  -816,   712,   715,   716,   717,   433,
     432,   545,   514,   546,   718,   554,   556,   720,   557,   558,
     524,   141,  -816,  -816,   141,  -816,   657,   204,  -816,   658,
      51,  -816,   659,   265,  -816,   660,   376,  -816,   661,   -17,
    -816,  -816,    52,  -816,   724,   582,  -816,   143,   662,  -816,
      65,  -816,   663,   -23,  -816,   664,   568,   573,   574,   575,
     577,   579,    33,  -816,   725,   726,   584,   585,   590,    74,
    -816,   727,   728,    83,  -816,  -816,  -816,   729,   730,   220,
    -816,   665,   194,  -816,   666,   732,  -816,   281,   667,  -816,
    -816,   414,   588,   605,   617,  -816,  -816,  -816,  -816,  -816,
     636,  -816,  -816,   638,  -816,  -816,  -816,  -816,   315,  -816,
     316,  -816,   731,  -816,   733,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   324,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   645,  -816,
    -816,   734,  -816,  -816,  -816,  -816,  -816,   737,   744,  -816,
    -816,  -816,  -816,  -816,   741,  -816,   328,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,   322,   648,  -816,  -816,  -816,
    -816,   651,   652,  -816,  -816,   654,   332,  -816,   344,  -816,
     668,  -816,   736,  -816,  -816,  -816,  -816,  -816,   345,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   376,  -816,
    -816,   746,   591,  -816,   143,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   747,   669,
     748,   281,  -816,  -816,   688,  -816,  -816,   750,  -816,   696,
    -816,  -816,   751,  -816,  -816,   331,  -816,   -52,   751,  -816,
    -816,   757,   760,   761,   357,  -816,  -816,  -816,  -816,  -816,
    -816,   764,   653,   713,   714,   -52,  -816,   719,  -816,  -816,
    -816,  -816,  -816
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   112,     9,
     253,    11,   398,    13,   423,    15,   453,    17,   323,    19,
     331,    21,   368,    23,   218,    25,   550,    27,   625,    29,
     615,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     455,     0,   333,   370,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   623,   605,   607,   609,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   611,   613,
     110,   124,   126,   128,     0,     0,     0,     0,     0,   245,
     321,   360,   411,   413,   294,   191,   208,   199,   184,   490,
     445,   210,   229,   511,     0,   535,   548,   104,     0,    74,
      76,    77,    78,    79,    80,    83,    84,    85,    86,   101,
      87,    89,    88,    93,    94,    81,    82,    91,    92,    99,
     100,   102,    90,    95,    96,    97,    98,   103,   121,     0,
     120,     0,   114,   116,   117,   118,   119,   390,   415,   277,
     279,   281,     0,     0,   287,   285,   283,   484,   276,   257,
     258,   259,   260,     0,   255,   264,   265,   266,   269,   270,
     272,   267,   268,   261,   262,   274,   275,   263,   271,   273,
     409,   408,   404,   405,   403,     0,   400,   402,   406,   407,
     438,     0,   441,     0,     0,   437,   431,   432,   430,   435,
     436,     0,   425,   427,   428,   433,   434,   429,   482,   470,
     472,   474,   476,   478,   480,   469,   466,   467,   468,     0,
     456,   457,   461,   462,   459,   463,   464,   465,   460,     0,
     350,   169,     0,   354,   352,   357,     0,   346,   347,     0,
     334,   335,   337,   349,   338,   339,   340,   356,   341,   342,
     343,   344,   345,   384,     0,     0,   382,   383,   386,   387,
       0,   371,   372,   374,   375,   376,   377,   378,   379,   380,
     381,   225,   227,   222,     0,   220,   223,   224,     0,   574,
     576,     0,   579,     0,     0,   583,   587,     0,     0,     0,
     592,   599,   601,   603,   572,   570,   571,     0,   552,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   630,     0,   627,   629,   621,
     620,     0,   617,   619,    48,     0,     0,    41,     0,     0,
       0,     0,     0,     0,    59,     0,    61,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   254,     0,     0,   399,     0,     0,
       0,     0,     0,     0,   424,     0,     0,     0,     0,     0,
       0,     0,   454,     0,   324,     0,     0,     0,     0,     0,
       0,     0,   332,     0,     0,     0,     0,   369,     0,     0,
       0,     0,   219,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     551,     0,     0,   626,     0,     0,   616,    52,    45,     0,
       0,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   534,     0,     0,    75,     0,   123,   115,     0,
       0,     0,     0,     0,   292,   293,     0,     0,     0,     0,
     256,     0,   401,     0,   440,     0,   443,   444,   426,     0,
       0,     0,     0,     0,     0,     0,   458,     0,     0,   348,
       0,     0,     0,   359,   336,     0,   388,   389,   373,     0,
       0,   221,   573,     0,     0,   578,     0,   581,   582,     0,
       0,   589,   590,   591,     0,     0,     0,     0,   553,     0,
     628,     0,   618,     0,     0,     0,   606,   608,   610,   612,
       0,     0,     0,     0,   130,   247,   325,   362,    42,   412,
     414,   296,     0,    49,     0,     0,     0,   447,   212,     0,
       0,     0,     0,    53,   122,   392,   417,   278,   280,   282,
     289,   290,   291,   288,   286,   284,     0,   410,   439,   442,
     483,   471,   473,   475,   477,   479,   481,   351,   170,   355,
     353,   358,   385,   226,   228,   575,   577,   580,   585,   586,
     584,   588,   594,   595,   596,   597,   598,   593,   600,   602,
     604,     0,   130,    46,     0,     0,     0,     0,   156,   162,
     164,   166,     0,     0,     0,     0,     0,   179,     0,     0,
     182,     0,     0,     0,   155,     0,   136,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   150,   151,   152,
     153,   148,   149,   154,     0,   134,     0,   131,   132,   251,
       0,   248,   249,   329,     0,   326,   327,   366,     0,   363,
     364,   300,     0,   297,   298,   197,   198,     0,   193,   195,
     196,     0,   206,   207,   203,     0,   201,   204,   205,   189,
       0,   186,   188,   494,     0,   492,   451,     0,   448,   449,
     216,     0,   213,   214,     0,     0,     0,     0,     0,     0,
       0,   231,   233,   234,   235,   236,   237,   238,   524,   530,
       0,     0,     0,   523,   520,   521,   522,     0,   513,   515,
     518,   516,   517,   519,   544,   546,   543,   541,   542,     0,
     537,   539,   540,     0,    55,   396,     0,   393,   394,   421,
       0,   418,   419,   488,   487,     0,   486,   634,     0,   632,
       0,    71,   624,   614,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   127,     0,   129,     0,     0,   246,     0,
     333,   322,     0,   370,   361,     0,     0,   295,     0,     0,
     192,   209,     0,   200,     0,     0,   185,   496,     0,   491,
     455,   446,     0,     0,   211,     0,     0,     0,     0,     0,
       0,     0,     0,   230,     0,     0,     0,     0,     0,     0,
     512,     0,     0,     0,   536,   549,    57,     0,    56,     0,
     391,     0,     0,   416,     0,     0,   485,     0,     0,   631,
     622,     0,     0,     0,     0,   168,   171,   172,   173,   174,
       0,   181,   175,     0,   176,   177,   178,   137,     0,   133,
       0,   250,     0,   328,     0,   365,   320,   315,   317,   308,
     309,   304,   305,   306,   307,   313,   314,   312,   316,     0,
     302,   310,   318,   319,   311,   299,   194,   202,     0,   187,
     508,     0,   506,   507,   503,   504,   505,     0,   497,   498,
     500,   501,   502,   493,     0,   450,     0,   215,   239,   240,
     241,   242,   243,   244,   232,     0,     0,   529,   532,   533,
     514,     0,     0,   538,    54,     0,     0,   395,     0,   420,
       0,   648,     0,   646,   644,   638,   642,   643,     0,   636,
     640,   641,   639,   633,   158,   159,   160,   161,   157,   163,
     165,   167,   180,   183,   135,   252,   330,   367,     0,   301,
     190,     0,     0,   495,     0,   452,   217,   526,   527,   528,
     525,   531,   545,   547,    58,   397,   422,   489,     0,     0,
       0,     0,   635,   303,     0,   510,   499,     0,   645,     0,
     637,   509,     0,   647,   652,     0,   650,     0,     0,   649,
     660,     0,     0,     0,     0,   654,   656,   657,   658,   659,
     651,     0,     0,     0,     0,     0,   653,     0,   662,   663,
     664,   655,   661
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,    21,  -816,   127,
    -816,  -816,  -816,  -816,  -816,  -816,   131,  -816,  -458,  -816,
    -816,  -816,   -74,  -816,  -816,  -816,   409,  -816,  -816,  -816,
    -816,   186,   384,   -70,   -58,   -55,   -38,  -816,  -816,  -816,
    -816,  -816,   180,   426,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,   115,  -816,   -44,  -816,  -569,    -3,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   -46,
    -816,  -598,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,   -24,  -816,  -816,
    -816,  -816,  -816,    -9,  -591,  -816,  -816,  -816,  -816,   -20,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   -28,  -816,
    -816,  -816,   -22,   393,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,   -29,  -816,  -816,  -816,  -816,  -816,  -816,  -815,  -816,
    -816,  -816,     7,  -816,  -816,  -816,    12,   440,  -816,  -816,
    -812,  -816,  -806,  -816,   -34,  -816,   -32,  -816,  -798,  -816,
    -816,  -816,  -797,  -816,  -816,  -816,  -816,     2,  -816,  -816,
    -166,   773,  -816,  -816,  -816,  -816,  -816,    17,  -816,  -816,
    -816,    22,  -816,   418,  -816,   -42,  -816,  -816,  -816,  -816,
    -816,   -40,  -816,  -816,  -816,  -816,  -816,   -12,  -816,  -816,
    -816,    18,  -816,  -816,  -816,    23,  -816,   425,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   -26,
    -816,  -816,  -816,   -21,   454,  -816,  -816,   -62,  -816,   -50,
    -816,  -816,  -816,  -816,  -816,   -27,  -816,  -816,  -816,   -18,
     465,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   -35,  -816,
    -816,  -816,     9,  -816,  -816,  -816,    15,  -816,   436,   246,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -796,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,    20,  -816,  -816,  -816,  -148,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,     0,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,    -2,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,   272,   416,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -342,   411,  -816,  -816,  -816,
    -816,  -816,  -816,   304,   427,  -816,  -816,  -816,    -8,  -816,
    -816,  -150,  -816,  -816,  -816,  -816,  -816,  -816,  -165,  -816,
    -816,  -183,  -816,  -816,  -816,  -816,  -816
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   599,    92,    93,    43,    72,    89,    90,   614,   794,
     887,   888,   350,    45,    74,   101,   102,   103,   359,    47,
      75,   138,   139,   140,   141,   142,   143,   144,   145,   369,
      49,    76,   171,   172,   173,   398,   174,   146,   370,   147,
     371,   148,   372,   706,   707,   708,   834,   685,   686,   687,
     815,  1008,   688,   816,   689,   817,   690,   818,   691,   692,
     436,   693,   694,   695,   696,   697,   698,   699,   700,   701,
     824,   702,   703,   827,   149,   387,   740,   741,   742,   854,
     150,   384,   727,   728,   729,   730,   151,   386,   735,   736,
     737,   738,   152,   385,   153,   390,   751,   752,   753,   863,
      65,    84,   304,   305,   306,   449,   307,   450,   154,   391,
     760,   761,   762,   763,   764,   765,   766,   767,   155,   378,
     710,   711,   712,   837,    51,    77,   193,   194,   195,   404,
     196,   405,   197,   406,   198,   411,   199,   410,   200,   409,
     623,   201,   202,   156,   383,   722,   723,   724,   846,   939,
     940,   157,   379,    59,    81,   714,   715,   716,   840,    61,
      82,   269,   270,   271,   272,   273,   274,   275,   435,   276,
     439,   277,   438,   278,   279,   440,   280,   158,   380,   718,
     719,   720,   843,    63,    83,   290,   291,   292,   293,   294,
     444,   295,   296,   297,   298,   204,   402,   796,   797,   798,
     889,    53,    78,   215,   216,   217,   415,   159,   381,   160,
     382,   207,   403,   800,   801,   802,   892,    55,    79,   231,
     232,   233,   418,   234,   235,   420,   236,   237,   161,   389,
     747,   748,   749,   860,    57,    80,   249,   250,   251,   252,
     426,   253,   427,   254,   428,   255,   429,   256,   430,   257,
     431,   258,   425,   209,   412,   805,   806,   895,   162,   388,
     744,   745,   857,   957,   958,   959,   960,   961,  1021,   962,
     163,   392,   777,   778,   779,   874,  1030,   780,   781,   875,
     782,   783,   164,   165,   394,   789,   790,   791,   881,   792,
     882,   166,   395,    67,    85,   327,   328,   329,   330,   454,
     331,   455,   332,   333,   457,   334,   335,   336,   460,   650,
     337,   461,   338,   339,   340,   341,   465,   657,   342,   466,
     343,   467,   344,   468,   104,   361,   105,   362,   106,   363,
     167,   367,   368,    71,    87,   351,   352,   353,   474,   107,
     360,    69,    86,   346,   347,   348,   471,   808,   809,   897,
     998,   999,  1000,  1001,  1040,  1002,  1038,  1055,  1056,  1057,
    1064,  1065,  1066,  1071,  1067,  1068,  1069
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
     100,   137,   170,   188,   211,   225,   245,   189,   267,   286,
     303,   324,   774,   734,   175,   205,   218,   229,   247,   190,
     281,   299,   191,   325,   704,   486,   176,   206,   219,   230,
     248,   932,   282,   300,   933,   326,   268,   287,    40,   192,
     934,   288,   208,   289,   212,   226,   213,   227,   937,   938,
     944,    33,   108,    34,   349,    35,   109,   239,   110,    32,
      94,   111,   112,   113,   803,   203,   214,   228,   246,   624,
     260,   365,   725,   301,   302,   396,   366,   168,   169,    91,
     397,   630,   631,   632,   114,   115,   116,   117,   118,   119,
     120,   121,  1060,   768,   400,  1061,  1062,  1063,   261,   401,
     262,   263,   673,   413,   264,   265,   266,   416,   414,   122,
     123,   121,   417,   423,   451,   122,   123,   345,   424,   452,
     124,   125,   126,   127,   128,    44,   129,   122,   123,   122,
     123,   130,   754,   755,   756,   757,   758,   759,   122,   123,
     131,   725,   732,   132,   733,    99,   238,   122,   123,    46,
     133,   726,   239,   240,   241,   242,   243,   244,   134,   135,
     668,   849,   136,    48,   850,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     301,   302,   469,   769,   770,   771,   772,   470,   261,   121,
     261,    95,   652,   653,   654,   655,   648,   649,   784,   785,
      96,    97,    98,   932,   472,    50,   933,   122,   123,   473,
      99,   120,   934,    99,    36,    37,    38,    39,    99,    99,
     937,   938,   944,    52,   475,   475,   950,   951,   656,   476,
     589,    99,   396,    99,   472,   852,   475,   811,   853,   812,
     121,   813,    99,   114,   115,   116,   117,   400,   666,    54,
     121,    99,   814,   220,   221,   222,   223,   224,   122,   123,
     177,   734,   178,    56,   858,   918,   121,   859,   122,   123,
     179,   180,   181,   182,   183,   184,   185,   210,   831,   186,
      58,   774,   831,   832,   122,   123,   185,   833,   855,   186,
     130,   100,   354,   856,   872,   879,   883,   187,   469,   873,
     880,   884,   185,   885,   898,   186,    60,   899,   355,    99,
      62,    99,   261,   283,   262,   263,   284,   285,   831,   413,
      64,    66,   137,  1014,  1015,    68,   170,  1018,   261,   122,
     123,   451,  1019,    70,  1058,   416,  1026,  1059,   175,   188,
    1035,   356,   211,   189,   357,   122,   123,   423,  1041,   225,
     176,   205,  1036,  1042,   218,   190,   358,   432,   191,   245,
    1075,   229,    99,   206,   364,  1076,   219,   373,   374,   267,
     375,   247,    99,   230,   286,   192,   477,   478,   208,   376,
     433,   281,   212,   248,   213,   377,   299,   393,    99,   226,
     399,   227,   407,   282,   408,   324,   419,   268,   300,   421,
     422,   203,   287,   437,   214,   434,   288,   325,   289,   441,
     442,   228,   620,   621,   622,   114,   115,   116,   117,   326,
     119,   246,   121,   261,   991,   443,   992,   993,  1027,  1028,
    1029,   122,   123,    99,  1004,  1005,  1006,  1007,   445,   446,
     122,   123,   448,   180,   181,   447,   183,   184,   453,    99,
     456,   458,   459,   462,   463,   464,   479,   480,   185,   481,
     482,   186,   483,   484,   487,   488,   489,   490,   491,   187,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   492,
     497,   498,   493,   586,   587,   588,   322,   323,   494,   499,
     137,   495,   496,   500,   501,   502,   503,   170,   684,   684,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   175,
     513,   514,   516,   517,   519,    99,   773,   786,   324,   520,
     521,   176,   522,   523,    99,   525,   526,   524,   775,   787,
     325,   527,   528,   529,   531,   533,   534,   535,   536,   539,
     776,   788,   326,   537,   540,   541,   542,   543,   544,   545,
     547,   548,   549,   550,   551,   552,   555,   553,   556,   557,
     559,   644,   560,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   574,   572,   573,   575,   576,   577,   579,
     581,   583,   905,   906,   663,   584,   585,   590,   591,   592,
     593,   594,   595,   596,   597,   836,   601,    34,   602,   603,
     600,   604,   605,   606,   607,   608,   651,   598,   609,   610,
     611,   612,   613,   615,   616,   617,   618,   619,   625,   626,
     627,   628,   629,   633,   634,   635,   636,   637,   638,   639,
     640,   641,   642,   643,   645,   646,   647,   658,   659,   660,
     661,   662,   739,   886,   705,   709,   713,   717,   721,   743,
     746,   750,   795,   799,   807,   819,   820,   821,   822,   823,
     825,   826,   828,   829,   830,   908,   839,   835,   838,   842,
     841,   844,   845,   847,   848,   916,   851,   862,   861,   864,
     865,   890,   866,   867,   868,   869,   870,   871,   876,   877,
     878,   891,   894,   893,   907,   909,   901,   900,   896,   902,
     903,   904,   910,   911,   913,   912,   914,   915,   948,   975,
     976,   981,   982,   985,   731,   984,   990,   968,  1022,  1016,
    1039,  1017,   969,   970,   971,  1023,   972,  1024,   973,  1025,
    1044,  1047,  1049,   977,   978,  1052,  1009,   684,  1054,   979,
     684,  1072,  1045,   188,  1073,  1074,   267,   189,  1077,   286,
     664,   667,   926,  1010,   485,   205,   927,   810,   281,   190,
     515,   299,   191,   952,   942,  1011,   245,   206,   928,   303,
     282,   929,   919,   300,   268,   955,   943,   287,   247,   192,
     931,   288,   208,   289,  1012,   773,  1013,   956,   930,   786,
     248,   953,   935,  1020,   936,   211,  1031,   775,   225,  1032,
    1033,   787,  1034,   994,  1078,   203,   518,   218,   917,   776,
     229,   949,   947,   788,   941,   996,  1037,   967,  1048,   219,
     946,   966,   230,   974,   561,   954,   921,   997,   246,   920,
     945,   995,  1043,   530,   259,   212,  1051,   213,   226,   923,
     227,   554,   922,   925,  1053,   987,   924,   989,   986,   546,
     532,   965,   804,   558,   988,   964,  1046,   214,   963,   980,
     228,   983,  1079,  1080,   793,   578,   582,  1082,   538,   665,
    1003,  1050,  1081,  1070,     0,     0,     0,     0,     0,   580,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   926,     0,     0,     0,   927,     0,
     952,     0,     0,     0,     0,     0,   942,     0,     0,     0,
     928,     0,   955,   929,     0,     0,     0,   994,   943,     0,
       0,     0,   931,     0,   956,     0,     0,     0,   953,   996,
     930,     0,     0,     0,   935,     0,   936,     0,     0,     0,
       0,   997,     0,     0,     0,   995,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   941,     0,     0,     0,
       0,     0,   954
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,   610,   604,    76,    77,    78,    79,    80,    77,
      82,    83,    77,    85,   593,   367,    76,    77,    78,    79,
      80,   846,    82,    83,   846,    85,    82,    83,    17,    77,
     846,    83,    77,    83,    78,    79,    78,    79,   846,   846,
     846,     5,     7,     7,    12,     9,    11,    87,    13,     0,
      10,    16,    17,    18,    94,    77,    78,    79,    80,   527,
      19,     3,    89,    96,    97,     3,     8,    14,    15,   168,
       8,   539,   540,   541,    39,    40,    41,    42,    43,    44,
      45,    46,   144,    19,     3,   147,   148,   149,    47,     8,
      49,    50,    28,     3,    53,    54,    55,     3,     8,    64,
      65,    46,     8,     3,     3,    64,    65,   142,     8,     8,
      75,    76,    77,    78,    79,     7,    81,    64,    65,    64,
      65,    86,    99,   100,   101,   102,   103,   104,    64,    65,
      95,    89,    90,    98,    92,   168,    81,    64,    65,     7,
     105,   168,    87,    88,    89,    90,    91,    92,   113,   114,
      19,     3,   117,     7,     6,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      96,    97,     3,   109,   110,   111,   112,     8,    47,    46,
      47,   141,   135,   136,   137,   138,   132,   133,   115,   116,
     150,   151,   152,  1018,     3,     7,  1018,    64,    65,     8,
     168,    45,  1018,   168,   168,   169,   170,   171,   168,   168,
    1018,  1018,  1018,     7,     3,     3,    83,    84,   171,     8,
       8,   168,     3,   168,     3,     3,     3,     8,     6,     8,
      46,     8,   168,    39,    40,    41,    42,     3,   590,     7,
      46,   168,     8,    59,    60,    61,    62,    63,    64,    65,
      56,   852,    58,     7,     3,   834,    46,     6,    64,    65,
      66,    67,    68,    69,    70,    71,    82,    57,     3,    85,
       7,   879,     3,     8,    64,    65,    82,     8,     3,    85,
      86,   365,     6,     8,     3,     3,     3,    93,     3,     8,
       8,     8,    82,     8,     3,    85,     7,     6,     3,   168,
       7,   168,    47,    48,    49,    50,    51,    52,     3,     3,
       7,     7,   396,     8,     8,     7,   400,     3,    47,    64,
      65,     3,     8,     7,     3,     3,     8,     6,   400,   413,
       8,     4,   416,   413,     8,    64,    65,     3,     3,   423,
     400,   413,     8,     8,   416,   413,     3,     8,   413,   433,
       3,   423,   168,   413,     4,     8,   416,     4,     4,   443,
       4,   433,   168,   423,   448,   413,   355,   356,   413,     4,
       3,   443,   416,   433,   416,     4,   448,     4,   168,   423,
       4,   423,     4,   443,     4,   469,     4,   443,   448,     4,
       4,   413,   448,     4,   416,     8,   448,   469,   448,     4,
       8,   423,    72,    73,    74,    39,    40,    41,    42,   469,
      44,   433,    46,    47,   143,     3,   145,   146,   106,   107,
     108,    64,    65,   168,    20,    21,    22,    23,     4,     4,
      64,    65,     3,    67,    68,     8,    70,    71,     4,   168,
       4,     4,     4,     4,     4,     4,   168,     4,    82,     4,
       4,    85,     4,     4,     4,     4,     4,     4,     4,    93,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   169,
       4,     4,   169,   482,   483,   484,   139,   140,   169,     4,
     584,   169,   169,     4,     4,     4,     4,   591,   592,   593,
       4,     4,     4,     4,     4,     4,     4,     4,   169,   591,
       4,     4,     4,   171,     4,   168,   610,   611,   612,     4,
       4,   591,     4,     4,   168,   171,     4,   169,   610,   611,
     612,     4,     4,     4,     4,     4,   169,     4,   169,     4,
     610,   611,   612,   169,     4,     4,     4,     4,     4,     4,
       4,     4,   169,     4,     4,     4,     4,   171,   171,   171,
       4,   560,     4,   171,     4,     4,   169,     4,   169,   169,
       4,     4,   171,     4,   171,   171,     4,     4,     4,     4,
       4,     4,   169,   171,   583,     7,     7,     7,     7,     7,
       7,     5,     5,     5,     5,     3,     5,     7,     5,     5,
     168,     5,     7,     5,     5,     5,   134,   500,     7,     7,
       7,     7,     5,     5,     5,   168,   168,   168,   168,     7,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
       5,     5,    80,   168,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   171,     3,     6,     6,     3,
       6,     6,     3,     6,     3,   171,     6,     3,     6,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,     3,     6,   169,   169,     4,     6,     8,     4,
       4,     4,     4,   169,     4,   169,   169,   169,     4,     4,
       4,     4,     4,     3,   603,     6,     4,   169,     4,     8,
       4,     8,   169,   169,   169,     8,   169,     3,   169,     8,
       4,     4,     4,   169,   169,     5,   168,   831,     7,   169,
     834,     4,   171,   837,     4,     4,   840,   837,     4,   843,
     584,   591,   846,   168,   365,   837,   846,   662,   840,   837,
     396,   843,   837,   857,   846,   168,   860,   837,   846,   863,
     840,   846,   836,   843,   840,   857,   846,   843,   860,   837,
     846,   843,   837,   843,   168,   879,   168,   857,   846,   883,
     860,   857,   846,   168,   846,   889,   168,   879,   892,   168,
     168,   883,   168,   897,   171,   837,   400,   889,   831,   879,
     892,   855,   852,   883,   846,   897,   168,   865,   169,   889,
     849,   863,   892,   872,   451,   857,   839,   897,   860,   837,
     848,   897,  1018,   413,    81,   889,   168,   889,   892,   842,
     892,   443,   840,   845,   168,   891,   843,   894,   889,   433,
     416,   862,   626,   448,   892,   860,  1024,   889,   858,   879,
     892,   883,   169,   169,   612,   469,   475,   168,   423,   585,
     898,  1041,  1075,  1058,    -1,    -1,    -1,    -1,    -1,   472,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1018,    -1,    -1,    -1,  1018,    -1,
    1024,    -1,    -1,    -1,    -1,    -1,  1018,    -1,    -1,    -1,
    1018,    -1,  1024,  1018,    -1,    -1,    -1,  1041,  1018,    -1,
      -1,    -1,  1018,    -1,  1024,    -1,    -1,    -1,  1024,  1041,
    1018,    -1,    -1,    -1,  1018,    -1,  1018,    -1,    -1,    -1,
      -1,  1041,    -1,    -1,    -1,  1041,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1018,    -1,    -1,    -1,
      -1,    -1,  1024
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,     0,     5,     7,     9,   168,   169,   170,   171,
     189,   190,   191,   196,     7,   205,     7,   211,     7,   222,
       7,   316,     7,   393,     7,   409,     7,   426,     7,   345,
       7,   351,     7,   375,     7,   292,     7,   485,     7,   533,
       7,   525,   197,   192,   206,   212,   223,   317,   394,   410,
     427,   346,   352,   376,   293,   486,   534,   526,   189,   198,
     199,   168,   194,   195,    10,   141,   150,   151,   152,   168,
     204,   207,   208,   209,   516,   518,   520,   531,     7,    11,
      13,    16,    17,    18,    39,    40,    41,    42,    43,    44,
      45,    46,    64,    65,    75,    76,    77,    78,    79,    81,
      86,    95,    98,   105,   113,   114,   117,   204,   213,   214,
     215,   216,   217,   218,   219,   220,   229,   231,   233,   266,
     272,   278,   284,   286,   300,   310,   335,   343,   369,   399,
     401,   420,   450,   462,   474,   475,   483,   522,    14,    15,
     204,   224,   225,   226,   228,   399,   401,    56,    58,    66,
      67,    68,    69,    70,    71,    82,    85,    93,   204,   215,
     216,   217,   218,   318,   319,   320,   322,   324,   326,   328,
     330,   333,   334,   369,   387,   399,   401,   403,   420,   445,
      57,   204,   326,   328,   369,   395,   396,   397,   399,   401,
      59,    60,    61,    62,    63,   204,   326,   328,   369,   399,
     401,   411,   412,   413,   415,   416,   418,   419,    81,    87,
      88,    89,    90,    91,    92,   204,   369,   399,   401,   428,
     429,   430,   431,   433,   435,   437,   439,   441,   443,   343,
      19,    47,    49,    50,    53,    54,    55,   204,   251,   353,
     354,   355,   356,   357,   358,   359,   361,   363,   365,   366,
     368,   399,   401,    48,    51,    52,   204,   251,   357,   363,
     377,   378,   379,   380,   381,   383,   384,   385,   386,   399,
     401,    96,    97,   204,   294,   295,   296,   298,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   139,   140,   204,   399,   401,   487,   488,   489,
     490,   492,   494,   495,   497,   498,   499,   502,   504,   505,
     506,   507,   510,   512,   514,   142,   535,   536,   537,    12,
     204,   527,   528,   529,     6,     3,     4,     8,     3,   210,
     532,   517,   519,   521,     4,     3,     8,   523,   524,   221,
     230,   232,   234,     4,     4,     4,     4,     4,   311,   344,
     370,   400,   402,   336,   273,   285,   279,   267,   451,   421,
     287,   301,   463,     4,   476,   484,     3,     8,   227,     4,
       3,     8,   388,   404,   321,   323,   325,     4,     4,   331,
     329,   327,   446,     3,     8,   398,     3,     8,   414,     4,
     417,     4,     4,     3,     8,   444,   432,   434,   436,   438,
     440,   442,     8,     3,     8,   360,   252,     4,   364,   362,
     367,     4,     8,     3,   382,     4,     4,     8,     3,   297,
     299,     3,     8,     4,   491,   493,     4,   496,     4,     4,
     500,   503,     4,     4,     4,   508,   511,   513,   515,     3,
       8,   538,     3,     8,   530,     3,     8,   189,   189,   168,
       4,     4,     4,     4,     4,   208,   527,     4,     4,     4,
       4,     4,   169,   169,   169,   169,   169,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   169,     4,     4,   214,     4,   171,   225,     4,
       4,     4,     4,     4,   169,   171,     4,     4,     4,     4,
     319,     4,   396,     4,   169,     4,   169,   169,   412,     4,
       4,     4,     4,     4,     4,     4,   430,     4,     4,   169,
       4,     4,     4,   171,   355,     4,   171,   171,   379,     4,
       4,   295,   171,     4,     4,   169,     4,   169,   169,     4,
       4,   171,   171,   171,     4,     4,     4,     4,   488,     4,
     536,     4,   528,     4,     7,     7,   189,   189,   189,     8,
       7,     7,     7,     7,     5,     5,     5,     5,   191,   193,
     168,     5,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     5,   200,     5,     5,   168,   168,   168,
      72,    73,    74,   332,   200,   168,     7,   168,   168,   168,
     200,   200,   200,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   189,   168,   168,   168,   132,   133,
     501,   134,   135,   136,   137,   138,   171,   509,   168,   168,
     168,     5,     5,   189,   213,   535,   527,   224,    19,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   204,   239,   240,   241,   244,   246,
     248,   250,   251,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   263,   264,   239,     7,   235,   236,   237,     7,
     312,   313,   314,     7,   347,   348,   349,     7,   371,   372,
     373,     7,   337,   338,   339,    89,   168,   274,   275,   276,
     277,   198,    90,    92,   276,   280,   281,   282,   283,    80,
     268,   269,   270,     7,   452,   453,     7,   422,   423,   424,
       7,   288,   289,   290,    99,   100,   101,   102,   103,   104,
     302,   303,   304,   305,   306,   307,   308,   309,    19,   109,
     110,   111,   112,   204,   253,   399,   401,   464,   465,   466,
     469,   470,   472,   473,   115,   116,   204,   399,   401,   477,
     478,   479,   481,   487,   201,     7,   389,   390,   391,     7,
     405,   406,   407,    94,   431,   447,   448,     7,   539,   540,
     235,     8,     8,     8,     8,   242,   245,   247,   249,     4,
       4,     4,     4,     4,   262,     4,     4,   265,     4,     4,
       4,     3,     8,     8,   238,     6,     3,   315,     6,     3,
     350,     6,     3,   374,     6,     3,   340,     6,     3,     3,
       6,     6,     3,     6,   271,     3,     8,   454,     3,     6,
     425,     6,     3,   291,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   467,   471,     4,     4,     4,     3,
       8,   480,   482,     3,     8,     8,   168,   202,   203,   392,
       6,     3,   408,     6,     3,   449,     8,   541,     3,     6,
       6,     4,     4,     4,     4,   169,   171,   169,   171,   169,
       4,   169,   169,     4,   169,   169,   171,   240,   239,   237,
     318,   314,   353,   349,   377,   373,   204,   215,   216,   217,
     218,   251,   310,   322,   324,   326,   328,   330,   334,   341,
     342,   369,   399,   401,   445,   339,   275,   281,     4,   269,
      83,    84,   204,   251,   369,   399,   401,   455,   456,   457,
     458,   459,   461,   453,   428,   424,   294,   290,   169,   169,
     169,   169,   169,   169,   303,     4,     4,   169,   169,   169,
     465,     4,     4,   478,     6,     3,   395,   391,   411,   407,
       4,   143,   145,   146,   204,   251,   399,   401,   542,   543,
     544,   545,   547,   540,    20,    21,    22,    23,   243,   168,
     168,   168,   168,   168,     8,     8,     8,     8,     3,     8,
     168,   460,     4,     8,     3,     8,     8,   106,   107,   108,
     468,   168,   168,   168,   168,     8,     8,   168,   548,     4,
     546,     3,     8,   342,     4,   171,   457,     4,   169,     4,
     543,   168,     5,   168,     7,   549,   550,   551,     3,     6,
     144,   147,   148,   149,   552,   553,   554,   556,   557,   558,
     550,   555,     4,     4,     4,     3,     8,     4,   171,   169,
     169,   553,   168
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   172,   174,   173,   175,   173,   176,   173,   177,   173,
     178,   173,   179,   173,   180,   173,   181,   173,   182,   173,
     183,   173,   184,   173,   185,   173,   186,   173,   187,   173,
     188,   173,   189,   189,   189,   189,   189,   189,   189,   190,
     192,   191,   193,   194,   194,   195,   195,   197,   196,   198,
     198,   199,   199,   201,   200,   202,   202,   203,   203,   204,
     206,   205,   207,   207,   208,   208,   208,   208,   208,   208,
     210,   209,   212,   211,   213,   213,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   215,   216,   217,   218,   219,
     221,   220,   223,   222,   224,   224,   225,   225,   225,   225,
     225,   227,   226,   228,   230,   229,   232,   231,   234,   233,
     235,   235,   236,   236,   238,   237,   239,   239,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   242,   241,   243,   243,
     243,   243,   245,   244,   247,   246,   249,   248,   250,   252,
     251,   253,   254,   255,   256,   257,   258,   259,   260,   262,
     261,   263,   265,   264,   267,   266,   268,   268,   269,   271,
     270,   273,   272,   274,   274,   275,   275,   276,   277,   279,
     278,   280,   280,   281,   281,   281,   282,   283,   285,   284,
     287,   286,   288,   288,   289,   289,   291,   290,   293,   292,
     294,   294,   294,   295,   295,   297,   296,   299,   298,   301,
     300,   302,   302,   303,   303,   303,   303,   303,   303,   304,
     305,   306,   307,   308,   309,   311,   310,   312,   312,   313,
     313,   315,   314,   317,   316,   318,   318,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   321,   320,   323,
     322,   325,   324,   327,   326,   329,   328,   331,   330,   332,
     332,   332,   333,   334,   336,   335,   337,   337,   338,   338,
     340,   339,   341,   341,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   344,   343,   346,   345,   347,   347,   348,   348,   350,
     349,   352,   351,   353,   353,   354,   354,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   356,   357,   358,
     360,   359,   362,   361,   364,   363,   365,   367,   366,   368,
     370,   369,   371,   371,   372,   372,   374,   373,   376,   375,
     377,   377,   378,   378,   379,   379,   379,   379,   379,   379,
     379,   379,   379,   380,   382,   381,   383,   384,   385,   386,
     388,   387,   389,   389,   390,   390,   392,   391,   394,   393,
     395,   395,   396,   396,   396,   396,   396,   396,   396,   398,
     397,   400,   399,   402,   401,   404,   403,   405,   405,   406,
     406,   408,   407,   410,   409,   411,   411,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   414,   413,
     415,   417,   416,   418,   419,   421,   420,   422,   422,   423,
     423,   425,   424,   427,   426,   428,   428,   429,   429,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     432,   431,   434,   433,   436,   435,   438,   437,   440,   439,
     442,   441,   444,   443,   446,   445,   447,   447,   449,   448,
     451,   450,   452,   452,   454,   453,   455,   455,   456,   456,
     457,   457,   457,   457,   457,   457,   457,   458,   460,   459,
     461,   463,   462,   464,   464,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   467,   466,   468,   468,   468,   469,
     471,   470,   472,   473,   474,   476,   475,   477,   477,   478,
     478,   478,   478,   478,   480,   479,   482,   481,   484,   483,
     486,   485,   487,   487,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   489,   491,   490,   493,   492,   494,   496,
     495,   497,   498,   500,   499,   501,   501,   503,   502,   504,
     505,   506,   508,   507,   509,   509,   509,   509,   509,   511,
     510,   513,   512,   515,   514,   517,   516,   519,   518,   521,
     520,   523,   522,   524,   522,   526,   525,   527,   527,   528,
     528,   530,   529,   532,   531,   534,   533,   535,   535,   536,
     538,   537,   539,   539,   541,   540,   542,   542,   543,   543,
     543,   543,   543,   543,   543,   544,   546,   545,   548,   547,
     549,   549,   551,   550,   552,   552,   553,   553,   553,   553,
     555,   554,   556,   557,   558
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     0,     4,     0,     6,     1,     3,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
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
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     0,     6,     0,     6,     0,     4,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     3
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
  "decline_probation_period", "interfaces_config", "$@22",
  "sub_interfaces6", "$@23", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@24", "re_detect",
  "lease_database", "$@25", "hosts_database", "$@26", "hosts_databases",
  "$@27", "database_list", "not_empty_database_list", "database", "$@28",
  "database_map_params", "database_map_param", "database_type", "$@29",
  "db_type", "user", "$@30", "password", "$@31", "host", "$@32", "port",
  "name", "$@33", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@34", "max_reconnect_tries", "keyspace", "$@35",
  "sanity_checks", "$@36", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@37", "mac_sources", "$@38", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@39",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@40",
  "hooks_libraries", "$@41", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@42",
  "sub_hooks_library", "$@43", "hooks_params", "hooks_param", "library",
  "$@44", "parameters", "$@45", "expired_leases_processing", "$@46",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@47",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@48",
  "sub_subnet6", "$@49", "subnet6_params", "subnet6_param", "subnet",
  "$@50", "interface", "$@51", "interface_id", "$@52", "client_class",
  "$@53", "require_client_classes", "$@54", "reservation_mode", "$@55",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@56",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@57", "shared_network_params", "shared_network_param",
  "option_def_list", "$@58", "sub_option_def_list", "$@59",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@60", "sub_option_def", "$@61",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@62",
  "option_def_record_types", "$@63", "space", "$@64", "option_def_space",
  "option_def_encapsulate", "$@65", "option_def_array", "option_data_list",
  "$@66", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@67", "sub_option_data", "$@68",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@69",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@70", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@71", "sub_pool6", "$@72",
  "pool_params", "pool_param", "pool_entry", "$@73", "user_context",
  "$@74", "comment", "$@75", "pd_pools_list", "$@76",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@77", "sub_pd_pool", "$@78", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@79", "pd_prefix_len", "excluded_prefix", "$@80",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@81",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@82", "sub_reservation", "$@83", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@84", "prefixes", "$@85", "duid", "$@86", "hw_address", "$@87",
  "hostname", "$@88", "flex_id_value", "$@89",
  "reservation_client_classes", "$@90", "relay", "$@91", "relay_map",
  "ip_address", "$@92", "client_classes", "$@93", "client_classes_list",
  "client_class_entry", "$@94", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@95", "only_if_required",
  "server_id", "$@96", "server_id_params", "server_id_param",
  "server_id_type", "$@97", "duid_type", "htype", "identifier", "$@98",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@99",
  "control_socket_params", "control_socket_param", "socket_type", "$@100",
  "socket_name", "$@101", "dhcp_ddns", "$@102", "sub_dhcp_ddns", "$@103",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@104", "server_ip", "$@105", "server_port",
  "sender_ip", "$@106", "sender_port", "max_queue_size", "ncr_protocol",
  "$@107", "ncr_protocol_value", "ncr_format", "$@108",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@109", "replace_client_name_value",
  "generated_prefix", "$@110", "hostname_char_set", "$@111",
  "hostname_char_replacement", "$@112", "dhcp4_json_object", "$@113",
  "dhcpddns_json_object", "$@114", "control_agent_json_object", "$@115",
  "config_control", "$@116", "$@117", "sub_config_control", "$@118",
  "config_control_params", "config_control_param", "config_databases",
  "$@119", "logging_object", "$@120", "sub_logging", "$@121",
  "logging_params", "logging_param", "loggers", "$@122", "loggers_entries",
  "logger_entry", "$@123", "logger_params", "logger_param", "debuglevel",
  "severity", "$@124", "output_options_list", "$@125",
  "output_options_list_content", "output_entry", "$@126",
  "output_params_list", "output_params", "output", "$@127", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   254,   254,   254,   255,   255,   256,   256,   257,   257,
     258,   258,   259,   259,   260,   260,   261,   261,   262,   262,
     263,   263,   264,   264,   265,   265,   266,   266,   267,   267,
     268,   268,   276,   277,   278,   279,   280,   281,   282,   285,
     290,   290,   301,   304,   305,   308,   312,   319,   319,   326,
     327,   330,   334,   341,   341,   348,   349,   352,   356,   367,
     377,   377,   392,   393,   397,   398,   399,   400,   401,   402,
     405,   405,   420,   420,   429,   430,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   466,   471,   476,   481,   486,
     491,   491,   502,   502,   511,   512,   515,   516,   517,   518,
     519,   522,   522,   532,   538,   538,   550,   550,   562,   562,
     572,   573,   576,   577,   580,   580,   590,   591,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   614,   614,   621,   622,
     623,   624,   627,   627,   635,   635,   643,   643,   651,   656,
     656,   664,   669,   674,   679,   684,   689,   694,   699,   704,
     704,   712,   717,   717,   725,   725,   735,   736,   738,   740,
     740,   758,   758,   768,   769,   772,   773,   776,   781,   786,
     786,   796,   797,   800,   801,   802,   805,   810,   817,   817,
     827,   827,   837,   838,   841,   842,   845,   845,   855,   855,
     865,   866,   867,   870,   871,   874,   874,   882,   882,   890,
     890,   901,   902,   905,   906,   907,   908,   909,   910,   913,
     918,   923,   928,   933,   938,   946,   946,   959,   960,   963,
     964,   971,   971,   997,   997,  1008,  1009,  1013,  1014,  1015,
    1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1035,  1035,  1043,
    1043,  1051,  1051,  1059,  1059,  1067,  1067,  1077,  1077,  1084,
    1085,  1086,  1089,  1094,  1102,  1102,  1113,  1114,  1118,  1119,
    1122,  1122,  1130,  1131,  1134,  1135,  1136,  1137,  1138,  1139,
    1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,  1149,
    1150,  1157,  1157,  1170,  1170,  1179,  1180,  1183,  1184,  1189,
    1189,  1204,  1204,  1218,  1219,  1222,  1223,  1226,  1227,  1228,
    1229,  1230,  1231,  1232,  1233,  1234,  1235,  1238,  1240,  1245,
    1247,  1247,  1255,  1255,  1263,  1263,  1271,  1273,  1273,  1281,
    1290,  1290,  1302,  1303,  1308,  1309,  1314,  1314,  1326,  1326,
    1338,  1339,  1344,  1345,  1350,  1351,  1352,  1353,  1354,  1355,
    1356,  1357,  1358,  1361,  1363,  1363,  1371,  1373,  1375,  1380,
    1388,  1388,  1400,  1401,  1404,  1405,  1408,  1408,  1418,  1418,
    1427,  1428,  1431,  1432,  1433,  1434,  1435,  1436,  1437,  1440,
    1440,  1448,  1448,  1473,  1473,  1503,  1503,  1515,  1516,  1519,
    1520,  1523,  1523,  1535,  1535,  1547,  1548,  1551,  1552,  1553,
    1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,  1564,  1564,
    1572,  1577,  1577,  1585,  1590,  1598,  1598,  1608,  1609,  1612,
    1613,  1616,  1616,  1625,  1625,  1634,  1635,  1638,  1639,  1643,
    1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,  1653,
    1656,  1656,  1666,  1666,  1676,  1676,  1684,  1684,  1692,  1692,
    1700,  1700,  1708,  1708,  1721,  1721,  1731,  1732,  1735,  1735,
    1746,  1746,  1756,  1757,  1760,  1760,  1770,  1771,  1774,  1775,
    1778,  1779,  1780,  1781,  1782,  1783,  1784,  1787,  1789,  1789,
    1797,  1805,  1805,  1817,  1818,  1821,  1822,  1823,  1824,  1825,
    1826,  1827,  1828,  1829,  1832,  1832,  1839,  1840,  1841,  1844,
    1849,  1849,  1857,  1862,  1869,  1876,  1876,  1886,  1887,  1890,
    1891,  1892,  1893,  1894,  1897,  1897,  1905,  1905,  1915,  1915,
    1927,  1927,  1937,  1938,  1941,  1942,  1943,  1944,  1945,  1946,
    1947,  1948,  1949,  1950,  1951,  1952,  1953,  1954,  1955,  1956,
    1957,  1958,  1959,  1962,  1967,  1967,  1975,  1975,  1983,  1988,
    1988,  1996,  2001,  2006,  2006,  2014,  2015,  2018,  2018,  2026,
    2031,  2036,  2041,  2041,  2049,  2052,  2055,  2058,  2061,  2067,
    2067,  2075,  2075,  2083,  2083,  2093,  2093,  2100,  2100,  2107,
    2107,  2116,  2116,  2125,  2125,  2136,  2136,  2146,  2147,  2151,
    2152,  2155,  2155,  2170,  2170,  2180,  2180,  2191,  2192,  2196,
    2200,  2200,  2212,  2213,  2217,  2217,  2225,  2226,  2229,  2230,
    2231,  2232,  2233,  2234,  2235,  2238,  2243,  2243,  2251,  2251,
    2261,  2262,  2265,  2265,  2273,  2274,  2277,  2278,  2279,  2280,
    2283,  2283,  2291,  2296,  2301
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
#line 4960 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2306 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
