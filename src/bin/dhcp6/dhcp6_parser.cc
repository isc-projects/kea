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
      case 186: // value
      case 190: // map_value
      case 240: // db_type
      case 329: // hr_mode
      case 465: // duid_type
      case 498: // ncr_protocol_value
      case 506: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 169: // "boolean"
        value.move< bool > (that.value);
        break;

      case 168: // "floating point"
        value.move< double > (that.value);
        break;

      case 167: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 166: // "constant string"
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
      case 186: // value
      case 190: // map_value
      case 240: // db_type
      case 329: // hr_mode
      case 465: // duid_type
      case 498: // ncr_protocol_value
      case 506: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 169: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 168: // "floating point"
        value.copy< double > (that.value);
        break;

      case 167: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 166: // "constant string"
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
            case 166: // "constant string"

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 167: // "integer"

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 168: // "floating point"

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 169: // "boolean"

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 186: // value

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 190: // map_value

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 240: // db_type

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 329: // hr_mode

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 465: // duid_type

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 498: // ncr_protocol_value

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 506: // replace_client_name_value

#line 243 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 186: // value
      case 190: // map_value
      case 240: // db_type
      case 329: // hr_mode
      case 465: // duid_type
      case 498: // ncr_protocol_value
      case 506: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 169: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 168: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 167: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 166: // "constant string"
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
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 298 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 327 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 340 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 349 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 353 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 379 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 402 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1623 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1055 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1063 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1991 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1123 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2055 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2152 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1372 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2274 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 411:
#line 1470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1472 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 413:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2749 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2827 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1788 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2854 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3117 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2003 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2012 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2040 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2052 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2058 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3356 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2122 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 616:
#line 2147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 620:
#line 2164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2168 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 631:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2192 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2212 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 646:
#line 2230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2232 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 650:
#line 2248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3576 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3580 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -795;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     277,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,    49,    46,    47,    68,    84,
     121,   130,   139,   150,   152,   166,   168,   172,   176,   183,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,    46,    51,
      42,    58,    44,   237,   339,   208,    98,   210,    41,    14,
     -25,   336,   113,  -795,   257,   254,   255,   264,   270,  -795,
    -795,  -795,  -795,  -795,   275,  -795,   107,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   276,   286,   304,
     305,   306,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   322,  -795,  -795,
    -795,   108,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,   341,  -795,   123,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   349,   355,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   136,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   137,  -795,  -795,
    -795,  -795,  -795,   375,  -795,   377,   381,  -795,  -795,  -795,
    -795,  -795,  -795,   160,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,   358,   354,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,   380,  -795,  -795,   385,  -795,  -795,  -795,   388,  -795,
    -795,   397,   409,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,   411,   421,  -795,  -795,
    -795,  -795,   414,   424,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,   164,  -795,  -795,  -795,
     447,  -795,  -795,   448,  -795,   463,   467,  -795,  -795,   468,
     469,   472,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   173,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   195,  -795,
    -795,  -795,    46,    46,  -795,   311,   474,   475,   476,   477,
     478,  -795,    42,  -795,   479,   480,   481,   482,   320,   321,
     323,   324,   326,   485,   490,   491,   492,   497,   499,   500,
     502,   503,   504,   506,   507,   508,   509,   510,   348,   515,
     516,    58,  -795,   518,   356,    44,  -795,   519,   520,   522,
     523,   527,   365,   364,   530,   531,   532,   533,   237,  -795,
     534,   339,  -795,   535,   376,   540,   378,   379,   208,  -795,
     543,   544,   545,   546,   547,   548,   549,  -795,    98,  -795,
     550,   551,   389,   553,   554,   555,   391,  -795,    41,   557,
     393,   394,  -795,    14,   560,   561,    13,  -795,   398,   562,
     564,   402,   566,   404,   405,   569,   571,   407,   412,   413,
     573,   574,   575,   576,   336,  -795,   579,   113,  -795,  -795,
    -795,   580,   578,   581,    46,    46,    46,  -795,   582,   583,
     584,   587,  -795,  -795,  -795,  -795,  -795,   588,   589,   591,
     590,   420,   593,   594,   595,   596,   597,   598,   600,   601,
     602,   603,  -795,   604,   605,  -795,   608,  -795,  -795,   609,
     610,   436,   441,   442,  -795,  -795,   373,   608,   450,   611,
    -795,   451,  -795,   453,  -795,   454,  -795,  -795,  -795,   608,
     608,   608,   455,   456,   457,   458,  -795,   459,   460,  -795,
     461,   462,   464,  -795,  -795,   465,  -795,  -795,  -795,   466,
      46,  -795,  -795,   470,   471,  -795,   473,  -795,  -795,   115,
     496,  -795,  -795,  -795,   -55,   483,   484,   486,  -795,   628,
    -795,    46,    58,   113,  -795,  -795,  -795,    44,   203,   203,
     627,   631,   633,   634,  -795,  -795,  -795,   635,   -10,    46,
      -4,   556,   636,   637,   638,   185,   132,    50,   336,  -795,
    -795,   639,   640,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,    -3,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   641,  -795,
     196,   198,   241,  -795,  -795,  -795,  -795,   647,   649,   650,
     651,   652,  -795,   653,   654,  -795,   655,   656,   657,  -795,
     242,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   252,
    -795,   658,   659,  -795,  -795,   660,   662,  -795,  -795,   661,
     665,  -795,  -795,   663,   667,  -795,  -795,   666,   668,  -795,
    -795,  -795,   194,  -795,  -795,  -795,   669,  -795,  -795,  -795,
     291,  -795,  -795,  -795,  -795,   253,  -795,  -795,  -795,   313,
    -795,  -795,   670,   671,  -795,  -795,   672,   674,  -795,   675,
     676,   677,   678,   679,   680,   309,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,   681,   682,   683,  -795,  -795,
    -795,  -795,   327,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   333,  -795,  -795,  -795,   334,   524,
    -795,   685,   686,  -795,  -795,   687,   689,  -795,  -795,  -795,
     688,  -795,  -795,   317,  -795,  -795,  -795,  -795,   684,   690,
     691,   693,   536,   494,   537,   529,   538,   695,   539,   541,
     696,   542,   552,   558,   203,  -795,  -795,   203,  -795,   627,
     237,  -795,   631,    41,  -795,   633,    14,  -795,   634,    85,
    -795,   635,   -10,  -795,  -795,    -4,  -795,   697,   556,  -795,
     251,   636,  -795,    98,  -795,   637,   -25,  -795,   638,   559,
     563,   565,   567,   568,   570,   185,  -795,   698,   703,   572,
     614,   616,   132,  -795,   706,   707,    50,  -795,  -795,  -795,
     708,   709,   339,  -795,   639,   208,  -795,   640,   711,  -795,
     262,   641,  -795,   429,   585,   624,   630,  -795,  -795,  -795,
    -795,  -795,   642,  -795,  -795,   643,  -795,  -795,  -795,  -795,
     343,  -795,   346,  -795,   705,  -795,   710,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,   353,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
     648,  -795,  -795,   712,  -795,  -795,  -795,  -795,  -795,   713,
     714,  -795,  -795,  -795,  -795,  -795,   715,  -795,   406,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   363,   664,  -795,
    -795,  -795,  -795,   673,   692,  -795,  -795,   694,   408,  -795,
     410,  -795,   699,  -795,   716,  -795,  -795,  -795,  -795,  -795,
     416,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
      85,  -795,  -795,   718,   632,  -795,   251,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
     720,   626,   721,   262,  -795,  -795,   700,  -795,  -795,   723,
    -795,   701,  -795,  -795,   722,  -795,  -795,   362,  -795,    75,
     722,  -795,  -795,   727,   729,   732,   418,  -795,  -795,  -795,
    -795,  -795,  -795,   734,   644,   702,   704,    75,  -795,   717,
    -795,  -795,  -795,  -795,  -795
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   109,     9,   250,    11,
     396,    13,   421,    15,   451,    17,   321,    19,   329,    21,
     366,    23,   215,    25,   548,    27,   611,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   453,     0,   331,   368,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     609,   603,   605,   607,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   107,   121,   123,   125,     0,     0,     0,
       0,     0,   242,   319,   358,   409,   411,   292,   188,   205,
     196,   181,   488,   443,   207,   226,   509,     0,   533,   546,
     101,     0,    72,    74,    75,    76,    77,    78,    81,    82,
      83,    84,    99,    85,    87,    86,    91,    92,    79,    80,
      89,    90,    97,    98,   100,    88,    93,    94,    95,    96,
     118,     0,   117,     0,   111,   113,   114,   115,   116,   388,
     413,   274,   276,   278,     0,     0,   284,   282,   280,   482,
     273,   254,   255,   256,   257,     0,   252,   261,   262,   263,
     266,   267,   269,   264,   265,   258,   259,   271,   272,   260,
     268,   270,   407,   406,   402,   403,   401,     0,   398,   400,
     404,   405,   436,     0,   439,     0,     0,   435,   429,   430,
     428,   433,   434,     0,   423,   425,   426,   431,   432,   427,
     480,   468,   470,   472,   474,   476,   478,   467,   464,   465,
     466,     0,   454,   455,   459,   460,   457,   461,   462,   463,
     458,     0,   348,   166,     0,   352,   350,   355,     0,   344,
     345,     0,   332,   333,   335,   347,   336,   337,   338,   354,
     339,   340,   341,   342,   343,   382,     0,     0,   380,   381,
     384,   385,     0,   369,   370,   372,   373,   374,   375,   376,
     377,   378,   379,   222,   224,   219,     0,   217,   220,   221,
       0,   572,   574,     0,   577,     0,     0,   581,   585,     0,
       0,     0,   590,   597,   599,   601,   570,   568,   569,     0,
     550,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   616,     0,   613,
     615,    46,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    57,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   251,
       0,     0,   397,     0,     0,     0,     0,     0,     0,   422,
       0,     0,     0,     0,     0,     0,     0,   452,     0,   322,
       0,     0,     0,     0,     0,     0,     0,   330,     0,     0,
       0,     0,   367,     0,     0,     0,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   549,     0,     0,   612,    50,
      43,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,   102,   103,   104,   105,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   532,     0,     0,    73,     0,   120,   112,     0,
       0,     0,     0,     0,   290,   291,     0,     0,     0,     0,
     253,     0,   399,     0,   438,     0,   441,   442,   424,     0,
       0,     0,     0,     0,     0,     0,   456,     0,     0,   346,
       0,     0,     0,   357,   334,     0,   386,   387,   371,     0,
       0,   218,   571,     0,     0,   576,     0,   579,   580,     0,
       0,   587,   588,   589,     0,     0,     0,     0,   551,     0,
     614,     0,     0,     0,   604,   606,   608,     0,     0,     0,
     127,   244,   323,   360,    40,   410,   412,   294,     0,    47,
       0,     0,     0,   445,   209,     0,     0,     0,     0,    51,
     119,   390,   415,   275,   277,   279,   286,   287,   288,   289,
     285,   283,   281,     0,   408,   437,   440,   481,   469,   471,
     473,   475,   477,   479,   349,   167,   353,   351,   356,   383,
     223,   225,   573,   575,   578,   583,   584,   582,   586,   592,
     593,   594,   595,   596,   591,   598,   600,   602,     0,    44,
       0,     0,     0,   153,   159,   161,   163,     0,     0,     0,
       0,     0,   176,     0,     0,   179,     0,     0,     0,   152,
       0,   133,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   147,   148,   149,   150,   145,   146,   151,     0,
     131,     0,   128,   129,   248,     0,   245,   246,   327,     0,
     324,   325,   364,     0,   361,   362,   298,     0,   295,   296,
     194,   195,     0,   190,   192,   193,     0,   203,   204,   200,
       0,   198,   201,   202,   186,     0,   183,   185,   492,     0,
     490,   449,     0,   446,   447,   213,     0,   210,   211,     0,
       0,     0,     0,     0,     0,     0,   228,   230,   231,   232,
     233,   234,   235,   522,   528,     0,     0,     0,   521,   518,
     519,   520,     0,   511,   513,   516,   514,   515,   517,   542,
     544,   541,   539,   540,     0,   535,   537,   538,     0,    53,
     394,     0,   391,   392,   419,     0,   416,   417,   486,   485,
       0,   484,   620,     0,   618,    69,   610,   108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   122,   124,     0,   126,     0,
       0,   243,     0,   331,   320,     0,   368,   359,     0,     0,
     293,     0,     0,   189,   206,     0,   197,     0,     0,   182,
     494,     0,   489,   453,   444,     0,     0,   208,     0,     0,
       0,     0,     0,     0,     0,     0,   227,     0,     0,     0,
       0,     0,     0,   510,     0,     0,     0,   534,   547,    55,
       0,    54,     0,   389,     0,     0,   414,     0,     0,   483,
       0,     0,   617,     0,     0,     0,     0,   165,   168,   169,
     170,   171,     0,   178,   172,     0,   173,   174,   175,   134,
       0,   130,     0,   247,     0,   326,     0,   363,   318,   313,
     315,   306,   307,   302,   303,   304,   305,   311,   312,   310,
     314,     0,   300,   308,   316,   317,   309,   297,   191,   199,
       0,   184,   506,     0,   504,   505,   501,   502,   503,     0,
     495,   496,   498,   499,   500,   491,     0,   448,     0,   212,
     236,   237,   238,   239,   240,   241,   229,     0,     0,   527,
     530,   531,   512,     0,     0,   536,    52,     0,     0,   393,
       0,   418,     0,   634,     0,   632,   630,   624,   628,   629,
       0,   622,   626,   627,   625,   619,   155,   156,   157,   158,
     154,   160,   162,   164,   177,   180,   132,   249,   328,   365,
       0,   299,   187,     0,     0,   493,     0,   450,   214,   524,
     525,   526,   523,   529,   543,   545,    56,   395,   420,   487,
       0,     0,     0,     0,   621,   301,     0,   508,   497,     0,
     631,     0,   623,   507,     0,   633,   638,     0,   636,     0,
       0,   635,   646,     0,     0,     0,     0,   640,   642,   643,
     644,   645,   637,     0,     0,     0,     0,     0,   639,     0,
     648,   649,   650,   641,   647
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,    34,  -795,   193,  -795,
    -795,  -795,  -795,  -795,  -795,     8,  -795,  -402,  -795,  -795,
    -795,   -70,  -795,  -795,  -795,   390,  -795,  -795,  -795,  -795,
     179,   366,   -66,   -54,   -51,   -34,  -795,  -795,  -795,  -795,
    -795,   178,   369,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   -61,  -795,  -545,   -47,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   -42,  -795,
    -574,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,   -78,  -795,  -795,  -795,
    -795,  -795,   -60,  -567,  -795,  -795,  -795,  -795,   -56,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   -41,  -795,  -795,
    -795,   -37,   367,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
     -40,  -795,  -795,  -795,  -795,  -795,  -795,  -794,  -795,  -795,
    -795,     3,  -795,  -795,  -795,     7,   422,  -795,  -795,  -788,
    -795,  -785,  -795,   -30,  -795,   -28,  -795,  -781,  -795,  -795,
    -795,  -779,  -795,  -795,  -795,  -795,     0,  -795,  -795,  -172,
     746,  -795,  -795,  -795,  -795,  -795,    11,  -795,  -795,  -795,
      16,  -795,   399,  -795,   -38,  -795,  -795,  -795,  -795,  -795,
     -36,  -795,  -795,  -795,  -795,  -795,    -8,  -795,  -795,  -795,
      15,  -795,  -795,  -795,    20,  -795,   415,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,   -33,  -795,
    -795,  -795,   -24,   439,  -795,  -795,   -58,  -795,   -46,  -795,
    -795,  -795,  -795,  -795,   -26,  -795,  -795,  -795,   -23,   435,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,   -31,  -795,  -795,
    -795,     9,  -795,  -795,  -795,    12,  -795,   428,   244,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -771,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
      18,  -795,  -795,  -795,  -146,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,    -1,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,     5,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,   265,   401,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,  -795,
    -795,  -795,  -795,   289,   417,  -795,  -795,  -795,   -15,  -795,
    -795,  -154,  -795,  -795,  -795,  -795,  -795,  -795,  -168,  -795,
    -795,  -184,  -795,  -795,  -795,  -795,  -795
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     575,    87,    88,    41,    68,    84,    85,   590,   769,   860,
     861,   659,    43,    70,    96,    97,    98,   346,    45,    71,
     131,   132,   133,   134,   135,   136,   137,   138,   354,    47,
      72,   163,   164,   165,   383,   166,   139,   355,   140,   356,
     141,   357,   681,   682,   683,   807,   660,   661,   662,   788,
     980,   663,   789,   664,   790,   665,   791,   666,   667,   421,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   797,
     677,   678,   800,   142,   372,   715,   716,   717,   827,   143,
     369,   702,   703,   704,   705,   144,   371,   710,   711,   712,
     713,   145,   370,   146,   375,   726,   727,   728,   836,    63,
      80,   296,   297,   298,   434,   299,   435,   147,   376,   735,
     736,   737,   738,   739,   740,   741,   742,   148,   363,   685,
     686,   687,   810,    49,    73,   185,   186,   187,   389,   188,
     390,   189,   391,   190,   396,   191,   395,   192,   394,   600,
     193,   194,   149,   368,   697,   698,   699,   819,   911,   912,
     150,   364,    57,    77,   689,   690,   691,   813,    59,    78,
     261,   262,   263,   264,   265,   266,   267,   420,   268,   424,
     269,   423,   270,   271,   425,   272,   151,   365,   693,   694,
     695,   816,    61,    79,   282,   283,   284,   285,   286,   429,
     287,   288,   289,   290,   196,   387,   771,   772,   773,   862,
      51,    74,   207,   208,   209,   400,   152,   366,   153,   367,
     199,   388,   775,   776,   777,   865,    53,    75,   223,   224,
     225,   403,   226,   227,   405,   228,   229,   154,   374,   722,
     723,   724,   833,    55,    76,   241,   242,   243,   244,   411,
     245,   412,   246,   413,   247,   414,   248,   415,   249,   416,
     250,   410,   201,   397,   780,   781,   868,   155,   373,   719,
     720,   830,   929,   930,   931,   932,   933,   993,   934,   156,
     377,   752,   753,   754,   847,  1002,   755,   756,   848,   757,
     758,   157,   158,   379,   764,   765,   766,   854,   767,   855,
     159,   380,    65,    81,   319,   320,   321,   322,   439,   323,
     440,   324,   325,   442,   326,   327,   328,   445,   627,   329,
     446,   330,   331,   332,   333,   450,   634,   334,   451,   335,
     452,   336,   453,    99,   348,   100,   349,   101,   350,   102,
     347,    67,    82,   338,   339,   340,   456,   783,   784,   870,
     970,   971,   972,   973,  1012,   974,  1010,  1027,  1028,  1029,
    1036,  1037,  1038,  1043,  1039,  1040,  1041
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   130,   162,   180,   203,   217,   237,   181,   259,   278,
     295,   316,   749,   709,   167,   197,   210,   221,   239,   182,
     273,   291,   183,   317,   679,   904,   168,   198,   211,   222,
     240,   905,   274,   292,   906,   318,   260,   279,   909,   184,
     910,   280,   200,   281,   204,   218,   205,   219,   916,    30,
      38,    31,    89,    32,    42,    33,   160,   161,   252,   253,
     275,   254,   255,   276,   277,   195,   206,   220,   238,   103,
     293,   294,   104,   105,   106,    44,   115,   116,   700,   629,
     630,   631,   632,   231,   700,   707,   253,   708,   254,   255,
     778,    46,   256,   257,   258,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   601,   115,   116,   293,   294,
     352,   381,   115,   116,   633,   353,   382,   607,   608,   609,
     115,   116,   107,   108,   109,   110,   385,   112,    48,   114,
     253,   386,   117,   118,   119,   120,   121,    50,   122,   398,
     401,    94,   114,   123,   399,   402,    52,   115,   116,   743,
     172,   173,   124,   175,   176,   125,   701,    54,   648,    56,
     115,   116,   126,   408,   759,   760,   177,   436,   409,   178,
     127,   128,   437,    58,   129,    60,   454,   179,   230,    62,
      94,   455,    90,    64,   231,   232,   233,   234,   235,   236,
      66,    91,    92,    93,   115,   116,   904,   822,   457,   381,
     823,   457,   905,   458,   785,   906,   786,    94,    94,   909,
      94,   910,    34,    35,    36,    37,    94,    86,  1032,   916,
     643,  1033,  1034,  1035,    94,   644,   645,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     744,   745,   746,   747,   385,   804,   625,   626,   253,   787,
     805,    94,   114,   113,   337,   804,   828,   342,   709,   343,
     806,   829,   890,   341,    94,   212,   213,   214,   215,   216,
     115,   116,   344,   345,   107,   108,   109,   110,   749,   351,
     358,   114,    95,   729,   730,   731,   732,   733,   734,   177,
     359,   169,   178,   170,   825,   114,   253,   826,    94,   115,
     116,   171,   172,   173,   174,   175,   176,   253,   360,   361,
     362,   130,   845,   115,   116,   162,   831,   846,   177,   832,
     871,   178,   123,   872,   115,   116,   378,   167,   180,   179,
     852,   203,   181,   922,   923,   853,   856,   454,   217,   168,
     197,   857,   858,   210,   182,   384,   804,   183,   237,   398,
     221,   986,   198,   392,   987,   211,   990,   418,   259,   393,
     239,   991,   222,   278,   184,  1030,   417,   200,  1031,    94,
     273,   204,   240,   205,    94,   291,   459,   460,   218,   404,
     219,   406,   274,   114,   316,   407,   260,   292,   419,   422,
     195,   279,   426,   206,   202,   280,   317,   281,   115,   116,
     220,   115,   116,    94,   963,   427,   964,   965,   318,   436,
     238,   401,   428,   408,   998,   430,  1007,    94,  1008,  1013,
     177,  1047,   432,   178,  1014,   431,  1048,   433,    94,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   596,   597,   598,   599,   976,   977,   978,
     979,   438,   441,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   443,   999,  1000,
    1001,   444,   447,   448,   314,   315,   449,   461,   462,   463,
     464,   465,   466,   468,   469,   470,   471,   472,   473,   477,
     474,   475,   130,   476,   478,   479,   480,   162,   564,   565,
     566,   481,    94,   482,   483,    94,   484,   485,   486,   167,
     487,   488,   489,   490,   491,   492,   748,   761,   316,   493,
     494,   168,   496,   499,   500,   497,   501,   502,   750,   762,
     317,   503,   504,   505,   506,   507,   508,   509,   511,   513,
     751,   763,   318,   514,   515,   516,   517,   519,   520,   521,
     522,   523,   524,   525,   527,   528,   529,   530,   531,   532,
     533,   535,   536,   537,   539,   540,   543,   542,   544,   545,
     546,   547,   548,   549,   621,   550,   551,   554,   555,   556,
     557,   552,   553,   559,   561,   562,   576,   706,   563,   567,
     568,   569,   570,   571,   572,   639,   573,    32,   577,   578,
     579,   580,   593,   582,   581,   583,   584,   594,   595,   585,
     586,   587,   588,   589,   591,   592,   602,   604,   603,   605,
     606,   610,   611,   612,   613,   614,   615,   616,   617,   628,
     618,   619,   620,   638,   680,   714,   622,   623,   684,   624,
     688,   692,   696,   718,   721,   725,   770,   774,   782,   635,
     636,   792,   637,   793,   794,   795,   796,   798,   799,   801,
     802,   803,   809,   878,   808,   812,   811,   814,   815,   817,
     818,   821,   820,   574,   835,   824,   834,   838,   837,   839,
     840,   841,   842,   843,   844,   849,   850,   851,   873,   864,
     859,   863,   867,   866,   874,   875,   869,   876,   880,   882,
     885,   920,   947,   877,   879,   881,   883,   948,   884,   886,
     953,   954,   957,   988,   956,   962,   994,   996,   989,   887,
    1011,   995,  1016,   997,  1019,  1021,   940,   888,  1024,  1026,
     941,  1044,   942,  1045,   943,   944,  1046,   945,  1049,   949,
     180,   640,   467,   259,   181,   642,   278,   495,   891,   898,
     921,   981,   197,   899,   498,   273,   182,   889,   291,   183,
     924,   914,   918,   237,   198,   900,   295,   274,   901,   919,
     292,   260,   927,   915,   279,   239,   184,   903,   280,   200,
     281,   950,   748,   951,   928,   902,   761,   240,   925,   907,
     982,   908,   203,  1020,   750,   217,   983,   939,   762,   938,
     966,  1017,   195,   541,   210,   946,   751,   221,   984,   985,
     763,   913,   968,  1050,   992,   893,   211,   892,  1015,   222,
     510,   917,   926,   251,   969,   238,   895,   534,   967,   894,
    1003,   959,   204,   897,   205,   218,   896,   219,   958,  1004,
     512,   961,   960,   518,   937,   936,   526,   779,   538,   935,
    1018,   952,   641,   768,   206,   558,   975,   220,  1005,  1022,
    1006,   955,  1042,  1053,     0,  1009,  1023,  1025,     0,  1051,
       0,  1052,     0,     0,   560,     0,     0,     0,     0,     0,
       0,     0,     0,  1054,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     898,     0,     0,     0,   899,     0,   924,     0,     0,     0,
       0,     0,   914,     0,     0,     0,   900,     0,   927,   901,
       0,     0,     0,   966,   915,     0,     0,     0,   903,     0,
     928,     0,     0,     0,   925,   968,   902,     0,     0,     0,
     907,     0,   908,     0,     0,     0,     0,   969,     0,     0,
       0,   967,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   913,     0,     0,     0,     0,     0,   926
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    73,    78,    79,
      80,    81,   586,   580,    72,    73,    74,    75,    76,    73,
      78,    79,    73,    81,   569,   819,    72,    73,    74,    75,
      76,   819,    78,    79,   819,    81,    78,    79,   819,    73,
     819,    79,    73,    79,    74,    75,    74,    75,   819,     0,
      16,     5,    10,     7,     7,     9,    12,    13,    17,    45,
      46,    47,    48,    49,    50,    73,    74,    75,    76,    11,
      95,    96,    14,    15,    16,     7,    62,    63,    88,   134,
     135,   136,   137,    86,    88,    89,    45,    91,    47,    48,
      93,     7,    51,    52,    53,    37,    38,    39,    40,    41,
      42,    43,    44,    62,    63,   507,    62,    63,    95,    96,
       3,     3,    62,    63,   169,     8,     8,   519,   520,   521,
      62,    63,    37,    38,    39,    40,     3,    42,     7,    44,
      45,     8,    74,    75,    76,    77,    78,     7,    80,     3,
       3,   166,    44,    85,     8,     8,     7,    62,    63,    17,
      65,    66,    94,    68,    69,    97,   166,     7,    26,     7,
      62,    63,   104,     3,   114,   115,    81,     3,     8,    84,
     112,   113,     8,     7,   116,     7,     3,    92,    80,     7,
     166,     8,   140,     7,    86,    87,    88,    89,    90,    91,
       7,   149,   150,   151,    62,    63,   990,     3,     3,     3,
       6,     3,   990,     8,     8,   990,     8,   166,   166,   990,
     166,   990,   166,   167,   168,   169,   166,   166,   143,   990,
      17,   146,   147,   148,   166,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
     108,   109,   110,   111,     3,     3,   131,   132,    45,     8,
       8,   166,    44,    43,   141,     3,     3,     3,   825,     4,
       8,     8,   807,     6,   166,    57,    58,    59,    60,    61,
      62,    63,     8,     3,    37,    38,    39,    40,   852,     4,
       4,    44,   352,    98,    99,   100,   101,   102,   103,    81,
       4,    54,    84,    56,     3,    44,    45,     6,   166,    62,
      63,    64,    65,    66,    67,    68,    69,    45,     4,     4,
       4,   381,     3,    62,    63,   385,     3,     8,    81,     6,
       3,    84,    85,     6,    62,    63,     4,   385,   398,    92,
       3,   401,   398,    82,    83,     8,     3,     3,   408,   385,
     398,     8,     8,   401,   398,     4,     3,   398,   418,     3,
     408,     8,   398,     4,     8,   401,     3,     3,   428,     4,
     418,     8,   408,   433,   398,     3,     8,   398,     6,   166,
     428,   401,   418,   401,   166,   433,   342,   343,   408,     4,
     408,     4,   428,    44,   454,     4,   428,   433,     8,     4,
     398,   433,     4,   401,    55,   433,   454,   433,    62,    63,
     408,    62,    63,   166,   142,     8,   144,   145,   454,     3,
     418,     3,     3,     3,     8,     4,     8,   166,     8,     3,
      81,     3,     8,    84,     8,     4,     8,     3,   166,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    70,    71,    72,    73,    18,    19,    20,
      21,     4,     4,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     4,   105,   106,
     107,     4,     4,     4,   138,   139,     4,   166,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   167,   167,     4,
     167,   167,   562,   167,     4,     4,     4,   567,   464,   465,
     466,     4,   166,     4,     4,   166,     4,     4,     4,   567,
       4,     4,     4,     4,     4,   167,   586,   587,   588,     4,
       4,   567,     4,     4,     4,   169,     4,     4,   586,   587,
     588,     4,   167,   169,     4,     4,     4,     4,     4,     4,
     586,   587,   588,   167,     4,   167,   167,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   167,     4,     4,     4,
     169,     4,   169,   169,     4,     4,     4,   169,     4,   167,
       4,   167,   167,     4,   540,     4,   169,     4,     4,     4,
       4,   169,   169,     4,     4,     7,   166,   579,     7,     7,
       7,     7,     5,     5,     5,   561,     5,     7,     5,     5,
       5,     5,   166,     5,     7,     5,     5,   166,   166,     7,
       7,     7,     7,     5,     5,     5,   166,   166,     7,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   133,
     166,   166,   166,     5,     7,    79,   166,   166,     7,   166,
       7,     7,     7,     7,     7,     7,     7,     7,     7,   166,
     166,     4,   166,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   169,     6,     3,     6,     6,     3,     6,
       3,     3,     6,   480,     3,     6,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     166,     6,     3,     6,     4,     4,     8,     4,   169,     4,
       4,     4,     4,   167,   167,   167,   167,     4,   167,   167,
       4,     4,     3,     8,     6,     4,     4,     3,     8,   167,
       4,     8,     4,     8,     4,     4,   167,   169,     5,     7,
     167,     4,   167,     4,   167,   167,     4,   167,     4,   167,
     810,   562,   352,   813,   810,   567,   816,   381,   809,   819,
     828,   166,   810,   819,   385,   813,   810,   804,   816,   810,
     830,   819,   822,   833,   810,   819,   836,   813,   819,   825,
     816,   813,   830,   819,   816,   833,   810,   819,   816,   810,
     816,   167,   852,   167,   830,   819,   856,   833,   830,   819,
     166,   819,   862,   167,   852,   865,   166,   838,   856,   836,
     870,   169,   810,   436,   862,   845,   852,   865,   166,   166,
     856,   819,   870,   169,   166,   812,   862,   810,   990,   865,
     398,   821,   830,    77,   870,   833,   815,   428,   870,   813,
     166,   864,   862,   818,   862,   865,   816,   865,   862,   166,
     401,   867,   865,   408,   835,   833,   418,   603,   433,   831,
     996,   852,   563,   588,   862,   454,   871,   865,   166,  1013,
     166,   856,  1030,  1047,    -1,   166,   166,   166,    -1,   167,
      -1,   167,    -1,    -1,   457,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     990,    -1,    -1,    -1,   990,    -1,   996,    -1,    -1,    -1,
      -1,    -1,   990,    -1,    -1,    -1,   990,    -1,   996,   990,
      -1,    -1,    -1,  1013,   990,    -1,    -1,    -1,   990,    -1,
     996,    -1,    -1,    -1,   996,  1013,   990,    -1,    -1,    -1,
     990,    -1,   990,    -1,    -1,    -1,    -1,  1013,    -1,    -1,
      -1,  1013,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   990,    -1,    -1,    -1,    -1,    -1,   996
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     5,     7,     9,   166,   167,   168,   169,   186,   187,
     188,   193,     7,   202,     7,   208,     7,   219,     7,   313,
       7,   390,     7,   406,     7,   423,     7,   342,     7,   348,
       7,   372,     7,   289,     7,   482,     7,   521,   194,   189,
     203,   209,   220,   314,   391,   407,   424,   343,   349,   373,
     290,   483,   522,   186,   195,   196,   166,   191,   192,    10,
     140,   149,   150,   151,   166,   201,   204,   205,   206,   513,
     515,   517,   519,    11,    14,    15,    16,    37,    38,    39,
      40,    41,    42,    43,    44,    62,    63,    74,    75,    76,
      77,    78,    80,    85,    94,    97,   104,   112,   113,   116,
     201,   210,   211,   212,   213,   214,   215,   216,   217,   226,
     228,   230,   263,   269,   275,   281,   283,   297,   307,   332,
     340,   366,   396,   398,   417,   447,   459,   471,   472,   480,
      12,    13,   201,   221,   222,   223,   225,   396,   398,    54,
      56,    64,    65,    66,    67,    68,    69,    81,    84,    92,
     201,   212,   213,   214,   215,   315,   316,   317,   319,   321,
     323,   325,   327,   330,   331,   366,   384,   396,   398,   400,
     417,   442,    55,   201,   323,   325,   366,   392,   393,   394,
     396,   398,    57,    58,    59,    60,    61,   201,   323,   325,
     366,   396,   398,   408,   409,   410,   412,   413,   415,   416,
      80,    86,    87,    88,    89,    90,    91,   201,   366,   396,
     398,   425,   426,   427,   428,   430,   432,   434,   436,   438,
     440,   340,    17,    45,    47,    48,    51,    52,    53,   201,
     248,   350,   351,   352,   353,   354,   355,   356,   358,   360,
     362,   363,   365,   396,   398,    46,    49,    50,   201,   248,
     354,   360,   374,   375,   376,   377,   378,   380,   381,   382,
     383,   396,   398,    95,    96,   201,   291,   292,   293,   295,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   138,   139,   201,   396,   398,   484,
     485,   486,   487,   489,   491,   492,   494,   495,   496,   499,
     501,   502,   503,   504,   507,   509,   511,   141,   523,   524,
     525,     6,     3,     4,     8,     3,   207,   520,   514,   516,
     518,     4,     3,     8,   218,   227,   229,   231,     4,     4,
       4,     4,     4,   308,   341,   367,   397,   399,   333,   270,
     282,   276,   264,   448,   418,   284,   298,   460,     4,   473,
     481,     3,     8,   224,     4,     3,     8,   385,   401,   318,
     320,   322,     4,     4,   328,   326,   324,   443,     3,     8,
     395,     3,     8,   411,     4,   414,     4,     4,     3,     8,
     441,   429,   431,   433,   435,   437,   439,     8,     3,     8,
     357,   249,     4,   361,   359,   364,     4,     8,     3,   379,
       4,     4,     8,     3,   294,   296,     3,     8,     4,   488,
     490,     4,   493,     4,     4,   497,   500,     4,     4,     4,
     505,   508,   510,   512,     3,     8,   526,     3,     8,   186,
     186,   166,     4,     4,     4,     4,     4,   205,     4,     4,
       4,     4,   167,   167,   167,   167,   167,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   167,     4,     4,   211,     4,   169,   222,     4,
       4,     4,     4,     4,   167,   169,     4,     4,     4,     4,
     316,     4,   393,     4,   167,     4,   167,   167,   409,     4,
       4,     4,     4,     4,     4,     4,   427,     4,     4,   167,
       4,     4,     4,   169,   352,     4,   169,   169,   376,     4,
       4,   292,   169,     4,     4,   167,     4,   167,   167,     4,
       4,   169,   169,   169,     4,     4,     4,     4,   485,     4,
     524,     4,     7,     7,   186,   186,   186,     7,     7,     7,
       5,     5,     5,     5,   188,   190,   166,     5,     5,     5,
       5,     7,     5,     5,     5,     7,     7,     7,     7,     5,
     197,     5,     5,   166,   166,   166,    70,    71,    72,    73,
     329,   197,   166,     7,   166,   166,   166,   197,   197,   197,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   186,   166,   166,   166,   131,   132,   498,   133,   134,
     135,   136,   137,   169,   506,   166,   166,   166,     5,   186,
     210,   523,   221,    17,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,   201,
     236,   237,   238,   241,   243,   245,   247,   248,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   260,   261,   236,
       7,   232,   233,   234,     7,   309,   310,   311,     7,   344,
     345,   346,     7,   368,   369,   370,     7,   334,   335,   336,
      88,   166,   271,   272,   273,   274,   195,    89,    91,   273,
     277,   278,   279,   280,    79,   265,   266,   267,     7,   449,
     450,     7,   419,   420,   421,     7,   285,   286,   287,    98,
      99,   100,   101,   102,   103,   299,   300,   301,   302,   303,
     304,   305,   306,    17,   108,   109,   110,   111,   201,   250,
     396,   398,   461,   462,   463,   466,   467,   469,   470,   114,
     115,   201,   396,   398,   474,   475,   476,   478,   484,   198,
       7,   386,   387,   388,     7,   402,   403,   404,    93,   428,
     444,   445,     7,   527,   528,     8,     8,     8,   239,   242,
     244,   246,     4,     4,     4,     4,     4,   259,     4,     4,
     262,     4,     4,     4,     3,     8,     8,   235,     6,     3,
     312,     6,     3,   347,     6,     3,   371,     6,     3,   337,
       6,     3,     3,     6,     6,     3,     6,   268,     3,     8,
     451,     3,     6,   422,     6,     3,   288,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   464,   468,     4,
       4,     4,     3,     8,   477,   479,     3,     8,     8,   166,
     199,   200,   389,     6,     3,   405,     6,     3,   446,     8,
     529,     3,     6,     4,     4,     4,     4,   167,   169,   167,
     169,   167,     4,   167,   167,     4,   167,   167,   169,   237,
     236,   234,   315,   311,   350,   346,   374,   370,   201,   212,
     213,   214,   215,   248,   307,   319,   321,   323,   325,   327,
     331,   338,   339,   366,   396,   398,   442,   336,   272,   278,
       4,   266,    82,    83,   201,   248,   366,   396,   398,   452,
     453,   454,   455,   456,   458,   450,   425,   421,   291,   287,
     167,   167,   167,   167,   167,   167,   300,     4,     4,   167,
     167,   167,   462,     4,     4,   475,     6,     3,   392,   388,
     408,   404,     4,   142,   144,   145,   201,   248,   396,   398,
     530,   531,   532,   533,   535,   528,    18,    19,    20,    21,
     240,   166,   166,   166,   166,   166,     8,     8,     8,     8,
       3,     8,   166,   457,     4,     8,     3,     8,     8,   105,
     106,   107,   465,   166,   166,   166,   166,     8,     8,   166,
     536,     4,   534,     3,     8,   339,     4,   169,   454,     4,
     167,     4,   531,   166,     5,   166,     7,   537,   538,   539,
       3,     6,   143,   146,   147,   148,   540,   541,   542,   544,
     545,   546,   538,   543,     4,     4,     4,     3,     8,     4,
     169,   167,   167,   541,   166
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   170,   172,   171,   173,   171,   174,   171,   175,   171,
     176,   171,   177,   171,   178,   171,   179,   171,   180,   171,
     181,   171,   182,   171,   183,   171,   184,   171,   185,   171,
     186,   186,   186,   186,   186,   186,   186,   187,   189,   188,
     190,   191,   191,   192,   192,   194,   193,   195,   195,   196,
     196,   198,   197,   199,   199,   200,   200,   201,   203,   202,
     204,   204,   205,   205,   205,   205,   205,   205,   207,   206,
     209,   208,   210,   210,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   212,   213,   214,   215,   216,   218,   217,   220,
     219,   221,   221,   222,   222,   222,   222,   222,   224,   223,
     225,   227,   226,   229,   228,   231,   230,   232,   232,   233,
     233,   235,   234,   236,   236,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   239,   238,   240,   240,   240,   240,   242,
     241,   244,   243,   246,   245,   247,   249,   248,   250,   251,
     252,   253,   254,   255,   256,   257,   259,   258,   260,   262,
     261,   264,   263,   265,   265,   266,   268,   267,   270,   269,
     271,   271,   272,   272,   273,   274,   276,   275,   277,   277,
     278,   278,   278,   279,   280,   282,   281,   284,   283,   285,
     285,   286,   286,   288,   287,   290,   289,   291,   291,   291,
     292,   292,   294,   293,   296,   295,   298,   297,   299,   299,
     300,   300,   300,   300,   300,   300,   301,   302,   303,   304,
     305,   306,   308,   307,   309,   309,   310,   310,   312,   311,
     314,   313,   315,   315,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   318,   317,   320,   319,   322,   321,
     324,   323,   326,   325,   328,   327,   329,   329,   329,   329,
     330,   331,   333,   332,   334,   334,   335,   335,   337,   336,
     338,   338,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   341,
     340,   343,   342,   344,   344,   345,   345,   347,   346,   349,
     348,   350,   350,   351,   351,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   353,   354,   355,   357,   356,
     359,   358,   361,   360,   362,   364,   363,   365,   367,   366,
     368,   368,   369,   369,   371,   370,   373,   372,   374,   374,
     375,   375,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   377,   379,   378,   380,   381,   382,   383,   385,   384,
     386,   386,   387,   387,   389,   388,   391,   390,   392,   392,
     393,   393,   393,   393,   393,   393,   393,   395,   394,   397,
     396,   399,   398,   401,   400,   402,   402,   403,   403,   405,
     404,   407,   406,   408,   408,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   411,   410,   412,   414,
     413,   415,   416,   418,   417,   419,   419,   420,   420,   422,
     421,   424,   423,   425,   425,   426,   426,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   429,   428,
     431,   430,   433,   432,   435,   434,   437,   436,   439,   438,
     441,   440,   443,   442,   444,   444,   446,   445,   448,   447,
     449,   449,   451,   450,   452,   452,   453,   453,   454,   454,
     454,   454,   454,   454,   454,   455,   457,   456,   458,   460,
     459,   461,   461,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   464,   463,   465,   465,   465,   466,   468,   467,
     469,   470,   471,   473,   472,   474,   474,   475,   475,   475,
     475,   475,   477,   476,   479,   478,   481,   480,   483,   482,
     484,   484,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   486,   488,   487,   490,   489,   491,   493,   492,   494,
     495,   497,   496,   498,   498,   500,   499,   501,   502,   503,
     505,   504,   506,   506,   506,   506,   506,   508,   507,   510,
     509,   512,   511,   514,   513,   516,   515,   518,   517,   520,
     519,   522,   521,   523,   523,   524,   526,   525,   527,   527,
     529,   528,   530,   530,   531,   531,   531,   531,   531,   531,
     531,   532,   534,   533,   536,   535,   537,   537,   539,   538,
     540,   540,   541,   541,   541,   541,   543,   542,   544,   545,
     546
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
       1,     1,     3,     3,     3,     3,     3,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     1,
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
       0,     4,     0,     6,     1,     1,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
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
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"shared-networks\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"client-classes\"", "\"require-client-classes\"",
  "\"test\"", "\"only-if-required\"", "\"client-class\"",
  "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"", "\"duid\"",
  "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
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
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"Logging\"", "\"loggers\"",
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
  "sanity_checks", "$@35", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@36", "mac_sources", "$@37", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@38",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@39",
  "hooks_libraries", "$@40", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@41",
  "sub_hooks_library", "$@42", "hooks_params", "hooks_param", "library",
  "$@43", "parameters", "$@44", "expired_leases_processing", "$@45",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@46",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@47",
  "sub_subnet6", "$@48", "subnet6_params", "subnet6_param", "subnet",
  "$@49", "interface", "$@50", "interface_id", "$@51", "client_class",
  "$@52", "require_client_classes", "$@53", "reservation_mode", "$@54",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@55",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@56", "shared_network_params", "shared_network_param",
  "option_def_list", "$@57", "sub_option_def_list", "$@58",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@59", "sub_option_def", "$@60",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@61",
  "option_def_record_types", "$@62", "space", "$@63", "option_def_space",
  "option_def_encapsulate", "$@64", "option_def_array", "option_data_list",
  "$@65", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@66", "sub_option_data", "$@67",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@68",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@69", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@70", "sub_pool6", "$@71",
  "pool_params", "pool_param", "pool_entry", "$@72", "user_context",
  "$@73", "comment", "$@74", "pd_pools_list", "$@75",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@76", "sub_pd_pool", "$@77", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@78", "pd_prefix_len", "excluded_prefix", "$@79",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@80",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@81", "sub_reservation", "$@82", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@83", "prefixes", "$@84", "duid", "$@85", "hw_address", "$@86",
  "hostname", "$@87", "flex_id_value", "$@88",
  "reservation_client_classes", "$@89", "relay", "$@90", "relay_map",
  "ip_address", "$@91", "client_classes", "$@92", "client_classes_list",
  "client_class_entry", "$@93", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@94", "only_if_required",
  "server_id", "$@95", "server_id_params", "server_id_param",
  "server_id_type", "$@96", "duid_type", "htype", "identifier", "$@97",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@98",
  "control_socket_params", "control_socket_param", "socket_type", "$@99",
  "socket_name", "$@100", "dhcp_ddns", "$@101", "sub_dhcp_ddns", "$@102",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@103", "server_ip", "$@104", "server_port",
  "sender_ip", "$@105", "sender_port", "max_queue_size", "ncr_protocol",
  "$@106", "ncr_protocol_value", "ncr_format", "$@107",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@108", "replace_client_name_value",
  "generated_prefix", "$@109", "hostname_char_set", "$@110",
  "hostname_char_replacement", "$@111", "dhcp4_json_object", "$@112",
  "dhcpddns_json_object", "$@113", "control_agent_json_object", "$@114",
  "logging_object", "$@115", "sub_logging", "$@116", "logging_params",
  "logging_param", "loggers", "$@117", "loggers_entries", "logger_entry",
  "$@118", "logger_params", "logger_param", "debuglevel", "severity",
  "$@119", "output_options_list", "$@120", "output_options_list_content",
  "output_entry", "$@121", "output_params_list", "output_params", "output",
  "$@122", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   252,   252,   252,   253,   253,   254,   254,   255,   255,
     256,   256,   257,   257,   258,   258,   259,   259,   260,   260,
     261,   261,   262,   262,   263,   263,   264,   264,   265,   265,
     273,   274,   275,   276,   277,   278,   279,   282,   287,   287,
     298,   301,   302,   305,   309,   316,   316,   323,   324,   327,
     331,   338,   338,   345,   346,   349,   353,   364,   374,   374,
     389,   390,   394,   395,   396,   397,   398,   399,   402,   402,
     417,   417,   426,   427,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   462,   467,   472,   477,   482,   487,   487,   498,
     498,   507,   508,   511,   512,   513,   514,   515,   518,   518,
     528,   534,   534,   546,   546,   558,   558,   568,   569,   572,
     573,   576,   576,   586,   587,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   610,   610,   617,   618,   619,   620,   623,
     623,   631,   631,   639,   639,   647,   652,   652,   660,   665,
     670,   675,   680,   685,   690,   695,   700,   700,   708,   713,
     713,   721,   721,   731,   732,   734,   736,   736,   754,   754,
     764,   765,   768,   769,   772,   777,   782,   782,   792,   793,
     796,   797,   798,   801,   806,   813,   813,   823,   823,   833,
     834,   837,   838,   841,   841,   851,   851,   861,   862,   863,
     866,   867,   870,   870,   878,   878,   886,   886,   897,   898,
     901,   902,   903,   904,   905,   906,   909,   914,   919,   924,
     929,   934,   942,   942,   955,   956,   959,   960,   967,   967,
     993,   993,  1004,  1005,  1009,  1010,  1011,  1012,  1013,  1014,
    1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,
    1025,  1026,  1027,  1028,  1031,  1031,  1039,  1039,  1047,  1047,
    1055,  1055,  1063,  1063,  1073,  1073,  1080,  1081,  1082,  1083,
    1086,  1091,  1099,  1099,  1110,  1111,  1115,  1116,  1119,  1119,
    1127,  1128,  1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,
    1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1154,
    1154,  1167,  1167,  1176,  1177,  1180,  1181,  1186,  1186,  1201,
    1201,  1215,  1216,  1219,  1220,  1223,  1224,  1225,  1226,  1227,
    1228,  1229,  1230,  1231,  1232,  1235,  1237,  1242,  1244,  1244,
    1252,  1252,  1260,  1260,  1268,  1270,  1270,  1278,  1287,  1287,
    1299,  1300,  1305,  1306,  1311,  1311,  1323,  1323,  1335,  1336,
    1341,  1342,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1358,  1360,  1360,  1368,  1370,  1372,  1377,  1385,  1385,
    1397,  1398,  1401,  1402,  1405,  1405,  1415,  1415,  1424,  1425,
    1428,  1429,  1430,  1431,  1432,  1433,  1434,  1437,  1437,  1445,
    1445,  1470,  1470,  1500,  1500,  1512,  1513,  1516,  1517,  1520,
    1520,  1532,  1532,  1544,  1545,  1548,  1549,  1550,  1551,  1552,
    1553,  1554,  1555,  1556,  1557,  1558,  1561,  1561,  1569,  1574,
    1574,  1582,  1587,  1595,  1595,  1605,  1606,  1609,  1610,  1613,
    1613,  1622,  1622,  1631,  1632,  1635,  1636,  1640,  1641,  1642,
    1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1653,  1653,
    1663,  1663,  1673,  1673,  1681,  1681,  1689,  1689,  1697,  1697,
    1705,  1705,  1718,  1718,  1728,  1729,  1732,  1732,  1743,  1743,
    1753,  1754,  1757,  1757,  1767,  1768,  1771,  1772,  1775,  1776,
    1777,  1778,  1779,  1780,  1781,  1784,  1786,  1786,  1794,  1802,
    1802,  1814,  1815,  1818,  1819,  1820,  1821,  1822,  1823,  1824,
    1825,  1826,  1829,  1829,  1836,  1837,  1838,  1841,  1846,  1846,
    1854,  1859,  1866,  1873,  1873,  1883,  1884,  1887,  1888,  1889,
    1890,  1891,  1894,  1894,  1902,  1902,  1912,  1912,  1924,  1924,
    1934,  1935,  1938,  1939,  1940,  1941,  1942,  1943,  1944,  1945,
    1946,  1947,  1948,  1949,  1950,  1951,  1952,  1953,  1954,  1955,
    1956,  1959,  1964,  1964,  1972,  1972,  1980,  1985,  1985,  1993,
    1998,  2003,  2003,  2011,  2012,  2015,  2015,  2023,  2028,  2033,
    2038,  2038,  2046,  2049,  2052,  2055,  2058,  2064,  2064,  2072,
    2072,  2080,  2080,  2090,  2090,  2097,  2097,  2104,  2104,  2117,
    2117,  2127,  2127,  2138,  2139,  2143,  2147,  2147,  2159,  2160,
    2164,  2164,  2172,  2173,  2176,  2177,  2178,  2179,  2180,  2181,
    2182,  2185,  2190,  2190,  2198,  2198,  2208,  2209,  2212,  2212,
    2220,  2221,  2224,  2225,  2226,  2227,  2230,  2230,  2238,  2243,
    2248
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
#line 4860 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2253 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
