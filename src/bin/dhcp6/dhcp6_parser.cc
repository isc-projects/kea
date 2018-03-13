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
      case 175: // value
      case 179: // map_value
      case 223: // db_type
      case 301: // hr_mode
      case 435: // duid_type
      case 468: // ncr_protocol_value
      case 476: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 158: // "boolean"
        value.move< bool > (that.value);
        break;

      case 157: // "floating point"
        value.move< double > (that.value);
        break;

      case 156: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 155: // "constant string"
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
      case 175: // value
      case 179: // map_value
      case 223: // db_type
      case 301: // hr_mode
      case 435: // duid_type
      case 468: // ncr_protocol_value
      case 476: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 158: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 157: // "floating point"
        value.copy< double > (that.value);
        break;

      case 156: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 155: // "constant string"
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
            case 155: // "constant string"

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 156: // "integer"

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 157: // "floating point"

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 158: // "boolean"

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 175: // value

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 179: // map_value

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 223: // db_type

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 301: // hr_mode

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 435: // duid_type

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 468: // ncr_protocol_value

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 476: // replace_client_name_value

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 175: // value
      case 179: // map_value
      case 223: // db_type
      case 301: // hr_mode
      case 435: // duid_type
      case 468: // ncr_protocol_value
      case 476: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 158: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 157: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 156: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 155: // "constant string"
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
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 337 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 367 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 390 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 571 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1264 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1479 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 798 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 816 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1593 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1649 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 878 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 977 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 978 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1906 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1138 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1166 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1181 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2097 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2106 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2133 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2142 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2302 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2599 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2749 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1719 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1926 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1935 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2056 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2102 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3390 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3394 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -756;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     404,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,    39,    27,    44,    50,    88,
     117,   128,   144,   153,   172,   174,   181,   222,   238,   247,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,    27,   -13,
      36,    49,    32,   188,    41,   232,   201,   110,    82,   259,
     -49,   349,    65,  -756,   237,   252,   263,   250,   313,  -756,
    -756,  -756,  -756,  -756,   280,  -756,    70,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,   315,   325,   326,   327,
     342,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,   344,  -756,  -756,  -756,   107,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   346,  -756,   124,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   351,   355,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   125,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   135,
    -756,  -756,  -756,  -756,  -756,   363,  -756,   364,   366,  -756,
    -756,  -756,  -756,  -756,   147,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,   258,   338,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,   345,  -756,  -756,   367,  -756,  -756,  -756,   369,
    -756,  -756,   370,   371,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,   373,   376,  -756,
    -756,  -756,  -756,   375,   372,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,   158,  -756,  -756,
    -756,   377,  -756,  -756,   380,  -756,   381,   385,  -756,  -756,
     386,   387,   389,  -756,  -756,  -756,  -756,  -756,   160,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   186,  -756,  -756,  -756,    27,
      27,  -756,   239,   391,   398,   400,   405,   407,  -756,    36,
    -756,   408,   409,   411,   261,   264,   266,   269,   272,   414,
     415,   417,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   437,   286,   439,   440,    49,  -756,   441,   288,    32,
    -756,   443,   445,   446,   447,   451,   300,   314,   467,   469,
     473,   474,   188,  -756,   475,    41,  -756,   476,   328,   477,
     329,   331,   232,  -756,   478,   479,   482,   484,   485,   489,
     490,  -756,   201,  -756,   491,   493,   343,   494,   496,   497,
     347,  -756,    82,   498,   348,   350,  -756,   259,   499,   503,
     140,  -756,   352,   505,   507,   359,   512,   361,   362,   515,
     517,   368,   374,   378,   518,   519,   349,  -756,   523,    65,
    -756,  -756,  -756,   524,   522,   526,    27,    27,    27,  -756,
     527,   528,   530,  -756,  -756,  -756,  -756,  -756,   525,   538,
     554,   553,   406,   557,   558,   559,   560,   561,   562,   563,
     564,  -756,   565,   566,  -756,   569,  -756,  -756,   570,   571,
     413,   422,   423,  -756,  -756,   209,   424,   575,   574,  -756,
     436,  -756,   438,  -756,   442,  -756,  -756,  -756,   569,   569,
     569,   444,   448,   449,   450,  -756,   452,   453,  -756,   454,
     455,   456,  -756,  -756,   457,  -756,  -756,  -756,   458,    27,
    -756,  -756,   459,   460,  -756,   461,  -756,  -756,   -80,   462,
    -756,  -756,  -756,   -78,   463,  -756,   577,  -756,    27,    49,
      65,  -756,  -756,  -756,    32,   184,   184,   576,   578,   580,
    -756,  -756,  -756,   581,   -44,    27,   281,   582,   583,   142,
      46,     7,   349,  -756,  -756,   585,   587,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   588,   500,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   589,
    -756,   189,   195,   236,  -756,  -756,  -756,  -756,   594,   596,
     597,   598,   602,  -756,   613,   615,  -756,  -756,   253,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,   254,  -756,   614,   618,  -756,  -756,
     616,   620,  -756,  -756,   619,   621,  -756,  -756,   622,   623,
    -756,  -756,  -756,    71,  -756,  -756,  -756,   624,  -756,  -756,
    -756,   111,  -756,  -756,  -756,  -756,   133,  -756,  -756,   625,
     626,  -756,   628,   629,   630,   631,   632,   633,   262,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,   634,   635,
     636,  -756,  -756,  -756,  -756,   265,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,   289,  -756,  -756,
    -756,   290,   472,  -756,   637,   638,  -756,  -756,   639,   641,
    -756,  -756,   640,   644,  -756,  -756,   642,  -756,   161,  -756,
    -756,  -756,  -756,   645,   647,   648,   649,   486,   501,   492,
     502,   506,   650,   508,   509,   651,   184,  -756,  -756,   188,
    -756,   576,    82,  -756,   578,   259,  -756,   580,   365,  -756,
     581,   -44,  -756,  -756,   281,  -756,    35,   582,  -756,   -49,
    -756,   583,   510,   511,   513,   514,   516,   520,   142,  -756,
     652,   653,   521,   529,   532,    46,  -756,   654,   657,     7,
    -756,  -756,  -756,   662,   660,    41,  -756,   585,   232,  -756,
     587,   201,  -756,   588,   667,  -756,    38,   589,  -756,   200,
     535,   536,   539,  -756,  -756,  -756,  -756,  -756,   542,  -756,
    -756,   544,  -756,   303,  -756,   665,  -756,   666,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,   305,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,   670,   672,  -756,  -756,
    -756,  -756,   306,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,     5,   547,  -756,  -756,  -756,  -756,   552,   567,  -756,
    -756,   568,   317,  -756,   320,  -756,   671,  -756,   572,  -756,
     676,  -756,  -756,  -756,  -756,  -756,   330,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   365,  -756,   677,  -756,    35,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,   678,   537,   679,    38,  -756,  -756,   595,
    -756,   703,  -756,   599,  -756,  -756,   708,  -756,  -756,   196,
    -756,    22,   708,  -756,  -756,   680,   712,   714,   337,  -756,
    -756,  -756,  -756,  -756,  -756,   715,   573,   584,   603,    22,
    -756,   600,  -756,  -756,  -756,  -756,  -756
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   106,     9,   226,    11,
     367,    13,   391,    15,   420,    17,   292,    19,   300,    21,
     337,    23,   191,    25,   513,    27,   570,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   422,     0,   302,   339,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     568,   562,   564,   566,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   104,   118,   120,     0,     0,     0,     0,
       0,   218,   290,   329,   379,   381,   264,   164,   181,   172,
     455,   183,   202,   474,     0,   498,   511,    98,     0,    72,
      74,    75,    76,    77,    78,    81,    82,    83,    84,    86,
      85,    90,    91,    79,    80,    88,    89,    96,    97,    87,
      92,    93,    94,    95,   115,     0,   114,     0,   108,   110,
     111,   112,   113,   359,   383,   249,   251,   253,     0,     0,
     257,   255,   412,   451,   248,   230,   231,   232,   233,     0,
     228,   237,   238,   239,   242,   244,   240,   241,   234,   235,
     246,   247,   236,   243,   245,   377,   376,   373,   372,     0,
     369,   371,   374,   375,   405,     0,   408,     0,     0,   404,
     399,   398,   402,   403,     0,   393,   395,   396,   400,   401,
     397,   449,   437,   439,   441,   443,   445,   447,   436,   433,
     434,   435,     0,   423,   424,   428,   429,   426,   430,   431,
     432,   427,     0,   319,   152,     0,   323,   321,   326,     0,
     315,   316,     0,   303,   304,   306,   318,   307,   308,   309,
     325,   310,   311,   312,   313,   314,   353,     0,     0,   351,
     352,   355,   356,     0,   340,   341,   343,   344,   345,   346,
     347,   348,   349,   350,   198,   200,   195,     0,   193,   196,
     197,     0,   535,   537,     0,   540,     0,     0,   544,   548,
       0,     0,     0,   553,   560,   533,   531,   532,     0,   515,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   575,     0,   572,   574,    46,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   227,     0,     0,   368,     0,     0,     0,
       0,     0,     0,   392,     0,     0,     0,     0,     0,     0,
       0,   421,     0,   293,     0,     0,     0,     0,     0,     0,
       0,   301,     0,     0,     0,     0,   338,     0,     0,     0,
       0,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   514,     0,     0,
     571,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   497,     0,     0,    73,     0,   117,   109,     0,     0,
       0,     0,     0,   262,   263,     0,     0,     0,     0,   229,
       0,   370,     0,   407,     0,   410,   411,   394,     0,     0,
       0,     0,     0,     0,     0,   425,     0,     0,   317,     0,
       0,     0,   328,   305,     0,   357,   358,   342,     0,     0,
     194,   534,     0,     0,   539,     0,   542,   543,     0,     0,
     550,   551,   552,     0,     0,   516,     0,   573,     0,     0,
       0,   563,   565,   567,     0,     0,     0,   220,   294,   331,
      40,   380,   382,   266,     0,    47,     0,     0,   185,     0,
       0,     0,     0,    51,   116,   361,   385,   250,   252,   254,
     259,   260,   261,   258,   256,   414,     0,   378,   406,   409,
     450,   438,   440,   442,   444,   446,   448,   320,   153,   324,
     322,   327,   354,   199,   201,   536,   538,   541,   546,   547,
     545,   549,   555,   556,   557,   558,   559,   554,   561,     0,
      44,     0,     0,     0,   139,   145,   147,   149,     0,     0,
       0,     0,     0,   158,     0,     0,   162,   138,     0,   122,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,     0,   224,     0,   221,   222,   298,
       0,   295,   296,   335,     0,   332,   333,   270,     0,   267,
     268,   170,   171,     0,   166,   168,   169,     0,   179,   180,
     176,     0,   174,   177,   178,   459,     0,   457,   189,     0,
     186,   187,     0,     0,     0,     0,     0,     0,     0,   204,
     206,   207,   208,   209,   210,   211,   487,   493,     0,     0,
       0,   486,   483,   484,   485,     0,   476,   478,   481,   479,
     480,   482,   507,   509,   506,   504,   505,     0,   500,   502,
     503,     0,    53,   365,     0,   362,   363,   389,     0,   386,
     387,   418,     0,   415,   416,   453,     0,   579,     0,   577,
      69,   569,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   119,   121,     0,
     219,     0,   302,   291,     0,   339,   330,     0,     0,   265,
       0,     0,   165,   182,     0,   173,   461,     0,   456,     0,
     184,     0,     0,     0,     0,     0,     0,     0,     0,   203,
       0,     0,     0,     0,     0,     0,   475,     0,     0,     0,
     499,   512,    55,     0,    54,     0,   360,     0,     0,   384,
       0,   422,   413,     0,     0,   452,     0,     0,   576,     0,
       0,     0,     0,   151,   154,   155,   156,   157,     0,   160,
     161,     0,   123,     0,   223,     0,   297,     0,   334,   289,
     284,   286,   278,   279,   274,   275,   276,   277,   283,   282,
     285,     0,   272,   280,   287,   288,   281,   269,   167,   175,
     472,   470,   471,   467,   468,   469,     0,   462,   463,   465,
     466,   458,     0,   188,   212,   213,   214,   215,   216,   217,
     205,     0,     0,   492,   495,   496,   477,     0,     0,   501,
      52,     0,     0,   364,     0,   388,     0,   417,     0,   593,
       0,   591,   589,   583,   587,   588,     0,   581,   585,   586,
     584,   578,   141,   142,   143,   144,   140,   146,   148,   150,
     159,   163,   225,   299,   336,     0,   271,     0,   460,     0,
     190,   489,   490,   491,   488,   494,   508,   510,    56,   366,
     390,   419,   454,     0,     0,     0,     0,   580,   273,     0,
     464,     0,   590,     0,   582,   473,     0,   592,   597,     0,
     595,     0,     0,   594,   605,     0,     0,     0,     0,   599,
     601,   602,   603,   604,   596,     0,     0,     0,     0,     0,
     598,     0,   607,   608,   609,   600,   606
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,     6,  -756,   108,  -756,
    -756,  -756,  -756,  -756,  -756,   -24,  -756,  -204,  -756,  -756,
    -756,   -70,  -756,  -756,  -756,   382,  -756,  -756,  -756,  -756,
     185,   379,   -72,   -58,   -56,   -55,  -756,  -756,  -756,  -756,
    -756,   182,   383,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
     187,   -26,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,    -7,  -756,  -553,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,   -39,  -544,  -756,
    -756,  -756,  -756,   -38,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,   -17,  -756,  -756,  -756,   -42,   323,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   -23,  -756,  -756,  -756,  -756,
    -756,  -756,  -755,  -756,  -756,  -756,    11,  -756,  -756,  -756,
       8,   384,  -756,  -756,  -752,  -756,  -748,  -756,   -34,  -756,
    -747,  -756,  -756,  -756,  -745,  -756,  -756,  -756,  -756,     3,
    -756,  -756,  -149,   700,  -756,  -756,  -756,  -756,  -756,    14,
    -756,  -756,  -756,    18,  -756,   388,  -756,   -65,  -756,  -756,
    -756,  -756,  -756,   -60,  -756,  -756,  -756,  -756,  -756,    -6,
    -756,  -756,  -756,    15,  -756,  -756,  -756,    16,  -756,   390,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,   -21,  -756,  -756,  -756,   -22,   399,  -756,  -756,   -48,
    -756,   -20,  -756,  -756,  -756,  -756,  -756,   -18,  -756,  -756,
    -756,   -19,   395,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,   -16,  -756,  -756,  -756,   -10,  -756,
     392,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -739,  -756,  -756,  -756,  -756,
    -756,  -756,    13,  -756,  -756,  -756,  -136,  -756,  -756,  -756,
    -756,  -756,  -756,     0,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,    -1,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,   241,   393,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
    -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,  -756,
     268,   394,  -756,  -756,  -756,   -11,  -756,  -756,  -142,  -756,
    -756,  -756,  -756,  -756,  -756,  -152,  -756,  -756,  -168,  -756,
    -756,  -756,  -756,  -756
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     551,    87,    88,    41,    68,    84,    85,   564,   722,   803,
     804,   127,    43,    70,    96,    97,    98,   333,    45,    71,
     128,   129,   130,   131,   132,   133,   134,   135,   341,    47,
      72,   157,   158,   159,   367,   160,   136,   342,   137,   343,
     628,   629,   630,   743,   916,   631,   744,   632,   745,   633,
     746,   634,   251,   405,   636,   637,   638,   639,   640,   752,
     641,   642,   643,   755,   138,   355,   663,   664,   665,   666,
     139,   357,   671,   672,   673,   674,   140,   356,   141,   359,
     679,   680,   681,   779,    63,    80,   287,   288,   289,   418,
     290,   419,   142,   360,   688,   689,   690,   691,   692,   693,
     694,   695,   143,   349,   646,   647,   648,   759,    49,    73,
     179,   180,   181,   373,   182,   374,   183,   375,   184,   379,
     185,   378,   573,   186,   187,   144,   354,   658,   659,   660,
     768,   851,   852,   145,   350,    57,    77,   650,   651,   652,
     762,    59,    78,   252,   253,   254,   255,   256,   257,   258,
     404,   259,   408,   260,   407,   261,   262,   409,   263,   146,
     351,   654,   655,   656,   765,    61,    79,   273,   274,   275,
     276,   277,   413,   278,   279,   280,   281,   189,   371,   724,
     725,   726,   805,    51,    74,   199,   200,   201,   384,   147,
     352,   148,   353,   192,   372,   728,   729,   730,   808,    53,
      75,   214,   215,   216,   387,   217,   218,   389,   219,   220,
     193,   380,   732,   733,   734,   811,    55,    76,   232,   233,
     234,   235,   395,   236,   396,   237,   397,   238,   398,   239,
     399,   240,   400,   241,   394,   194,   381,   736,   814,   149,
     358,   676,   677,   776,   866,   867,   868,   869,   870,   927,
     150,   361,   705,   706,   707,   790,   934,   708,   709,   791,
     710,   711,   151,   152,   363,   717,   718,   719,   797,   720,
     798,   153,   364,    65,    81,   308,   309,   310,   311,   423,
     312,   424,   313,   314,   426,   315,   316,   317,   429,   600,
     318,   430,   319,   320,   321,   322,   434,   607,   323,   435,
      99,   335,   100,   336,   101,   337,   102,   334,    67,    82,
     325,   326,   327,   438,   738,   739,   816,   906,   907,   908,
     909,   945,   910,   943,   959,   960,   961,   968,   969,   970,
     975,   971,   972,   973
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   175,   156,   174,   196,   209,   228,   702,   250,   269,
     286,   305,   670,   845,   271,   176,   846,   177,   178,   272,
     847,   849,    38,   850,   161,   190,   202,   212,   230,   856,
     264,   282,    31,   306,    32,   661,    33,   284,   285,    30,
     197,   210,   598,   599,   154,   155,    89,   602,   603,   604,
     605,    42,   162,   191,   203,   213,   231,    44,   265,   283,
     103,   307,   696,   104,   105,   114,   115,   188,   198,   211,
     229,   619,   270,   339,   771,   113,   244,   772,   340,   244,
     606,   113,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   195,   114,   115,    46,   114,   115,   243,   114,
     115,   931,   932,   933,   114,   115,    94,   114,   115,   860,
     365,   662,   712,   713,   774,   366,   171,   775,   116,   117,
     118,   119,   120,   244,    48,   245,   246,   369,   382,   247,
     248,   249,   370,   383,   121,    50,   777,   122,   385,   778,
     114,   115,    86,   386,   123,   697,   698,   699,   700,   112,
     392,    52,   124,   125,   964,   393,   126,   965,   966,   967,
      54,   420,    94,   436,   817,    90,   421,   818,   437,   899,
     845,   900,   901,   846,    91,    92,    93,   847,   849,    56,
     850,    58,    34,    35,    36,    37,   856,    94,    60,   439,
      94,    94,   365,    94,   440,   324,    94,   740,   439,   962,
     614,    94,   963,   741,    94,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   624,   625,   626,   912,   913,   914,
     915,   106,   107,   108,   109,   244,   284,   285,   113,    62,
     670,   682,   683,   684,   685,   686,   687,    94,   163,   369,
     164,   113,   702,   328,   742,    64,   114,   115,   165,   166,
     167,   168,   169,   170,    66,   329,   756,   756,   331,   114,
     115,   757,   758,   171,   172,   788,   401,   330,   795,    95,
     789,   173,   113,   796,   221,   570,   571,   572,   222,   223,
     224,   225,   226,   227,   338,   204,   205,   206,   207,   208,
     114,   115,   799,   436,   580,   581,   582,   800,   801,   156,
     244,   266,   245,   246,   267,   268,   382,   171,   925,   420,
     175,   922,   174,   926,   930,   196,   332,   114,   115,   344,
     385,   161,   209,   392,   176,   939,   177,   178,   940,   345,
     346,   347,   228,   946,   190,   441,   442,   202,   947,    94,
     979,   402,   250,    94,   212,   980,   348,   269,   362,   162,
     368,   197,   271,   403,   230,   376,    94,   272,   210,   377,
     661,   668,   191,   669,   264,   203,   305,   388,   390,   282,
     391,   406,   213,   410,   412,   417,   188,   414,   411,   198,
     415,   422,   231,   416,   425,   427,   211,    94,   306,   428,
     431,   432,   265,   433,   443,   444,   229,   283,   106,   107,
     108,   109,   445,   111,   446,   113,   244,   114,   115,   447,
     270,   448,   450,   451,    94,   452,   307,   453,   458,   459,
     454,   460,   455,   114,   115,   456,   166,   167,   457,   169,
     170,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     171,   470,   471,   472,   473,   475,   476,   478,   173,   479,
     480,   481,   541,   542,   543,   482,   483,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   485,   484,   486,   156,   627,   627,   487,   488,   490,
     492,   494,   498,   499,   493,   495,   500,   496,   501,   502,
     701,   714,   305,   503,   504,   506,   161,   507,   509,   508,
     510,   511,   514,   518,    94,   512,   515,   519,   516,   522,
     521,   523,   703,   715,   306,   524,   525,   526,   527,   528,
      94,   529,   533,   534,   162,   594,   530,   536,   538,   539,
     547,   667,   531,   540,   544,   545,   532,   546,   635,   635,
     704,   716,   307,   548,   610,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   549,
      32,   552,   553,   554,   555,   556,   557,   558,   567,   550,
     559,   560,   561,   562,   563,   565,   566,   568,   569,   574,
     575,   576,   609,   645,   735,   649,   601,   653,   657,   675,
     678,   577,   723,   578,   727,   731,   737,   579,   747,   583,
     748,   749,   750,   584,   585,   586,   751,   587,   588,   589,
     590,   591,   592,   593,   595,   596,   597,   753,   608,   754,
     760,   761,   763,   764,   767,   766,   770,   802,   769,   781,
     773,   780,   782,   783,   784,   785,   786,   787,   792,   793,
     794,   807,   823,   806,   810,   809,   812,   813,   825,   819,
     815,   820,   821,   822,   828,   831,   881,   882,   887,   824,
     826,   888,   827,   891,   829,   830,   874,   875,   890,   876,
     877,   898,   878,   923,   924,   929,   879,   883,   928,   941,
     944,   949,   951,   953,   976,   884,   627,   175,   885,   174,
     917,   918,   250,   952,   919,   269,   840,   920,   839,   921,
     271,   176,   935,   177,   178,   272,   861,   936,   956,   286,
     841,   190,   842,   843,   264,   958,   977,   282,   978,   981,
     854,   449,   937,   938,   611,   701,   613,   942,   864,   714,
     832,   982,   858,   644,   848,   196,   859,   872,   209,   191,
     983,   228,   265,   520,   474,   283,   902,   703,   855,   635,
     955,   715,   477,   188,   957,   986,   865,   202,   270,   984,
     212,   844,   853,   230,   873,   880,   489,   833,   904,   862,
     863,   197,   834,   857,   210,   704,   948,   242,   836,   716,
     835,   837,   838,   892,   491,   203,   893,   497,   213,   894,
     871,   231,   895,   950,   505,   886,   905,   897,   889,   198,
     513,   896,   211,   721,   954,   229,   911,   517,   612,   903,
     974,   985,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   535,
       0,     0,     0,   537,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   840,     0,   839,     0,     0,     0,   861,
       0,     0,     0,     0,     0,     0,     0,   841,     0,   842,
     843,     0,     0,     0,     0,     0,   902,   854,     0,     0,
       0,   864,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   848,     0,     0,     0,     0,     0,     0,   904,     0,
       0,     0,     0,     0,     0,   855,     0,     0,     0,   865,
       0,     0,     0,     0,     0,     0,     0,     0,   844,   853,
       0,     0,   862,   863,     0,     0,   905,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   903
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    73,    72,    73,    74,    75,    76,   560,    78,    79,
      80,    81,   556,   768,    79,    73,   768,    73,    73,    79,
     768,   768,    16,   768,    72,    73,    74,    75,    76,   768,
      78,    79,     5,    81,     7,    79,     9,    86,    87,     0,
      74,    75,   122,   123,    12,    13,    10,   125,   126,   127,
     128,     7,    72,    73,    74,    75,    76,     7,    78,    79,
      11,    81,    16,    14,    15,    58,    59,    73,    74,    75,
      76,    25,    79,     3,     3,    40,    41,     6,     8,    41,
     158,    40,    33,    34,    35,    36,    37,    38,    39,    40,
      58,    59,    51,    58,    59,     7,    58,    59,    16,    58,
      59,    96,    97,    98,    58,    59,   155,    58,    59,    74,
       3,   155,   105,   106,     3,     8,    75,     6,    69,    70,
      71,    72,    73,    41,     7,    43,    44,     3,     3,    47,
      48,    49,     8,     8,    85,     7,     3,    88,     3,     6,
      58,    59,   155,     8,    95,    99,   100,   101,   102,    39,
       3,     7,   103,   104,   132,     8,   107,   135,   136,   137,
       7,     3,   155,     3,     3,   129,     8,     6,     8,   131,
     925,   133,   134,   925,   138,   139,   140,   925,   925,     7,
     925,     7,   155,   156,   157,   158,   925,   155,     7,     3,
     155,   155,     3,   155,     8,   130,   155,     8,     3,     3,
      16,   155,     6,     8,   155,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    17,    18,    19,
      20,    33,    34,    35,    36,    41,    86,    87,    40,     7,
     774,    89,    90,    91,    92,    93,    94,   155,    50,     3,
      52,    40,   795,     6,     8,     7,    58,    59,    60,    61,
      62,    63,    64,    65,     7,     3,     3,     3,     8,    58,
      59,     8,     8,    75,    76,     3,     8,     4,     3,   339,
       8,    83,    40,     8,    73,    66,    67,    68,    77,    78,
      79,    80,    81,    82,     4,    53,    54,    55,    56,    57,
      58,    59,     3,     3,   498,   499,   500,     8,     8,   369,
      41,    42,    43,    44,    45,    46,     3,    75,     3,     3,
     382,     8,   382,     8,     8,   385,     3,    58,    59,     4,
       3,   369,   392,     3,   382,     8,   382,   382,     8,     4,
       4,     4,   402,     3,   382,   329,   330,   385,     8,   155,
       3,     3,   412,   155,   392,     8,     4,   417,     4,   369,
       4,   385,   417,     8,   402,     4,   155,   417,   392,     4,
      79,    80,   382,    82,   412,   385,   436,     4,     4,   417,
       4,     4,   392,     4,     3,     3,   382,     4,     8,   385,
       4,     4,   402,     8,     4,     4,   392,   155,   436,     4,
       4,     4,   412,     4,   155,     4,   402,   417,    33,    34,
      35,    36,     4,    38,     4,    40,    41,    58,    59,     4,
     417,     4,     4,     4,   155,     4,   436,   156,     4,     4,
     156,     4,   156,    58,    59,   156,    61,    62,   156,    64,
      65,     4,     4,     4,     4,     4,     4,     4,     4,     4,
      75,     4,   156,     4,     4,     4,   158,     4,    83,     4,
       4,     4,   446,   447,   448,     4,   156,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     4,   158,     4,   544,   545,   546,     4,     4,     4,
       4,     4,     4,     4,   156,   156,     4,   156,     4,     4,
     560,   561,   562,     4,     4,     4,   544,     4,     4,   156,
       4,     4,     4,     4,   155,   158,   158,     4,   158,     4,
     158,     4,   560,   561,   562,   156,     4,   156,   156,     4,
     155,     4,     4,     4,   544,   519,   158,     4,     4,     7,
       5,   555,   158,     7,     7,     7,   158,     7,   545,   546,
     560,   561,   562,     5,   538,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,     5,
       7,   155,     5,     5,     5,     5,     5,     5,   155,   461,
       7,     7,     7,     7,     5,     5,     5,   155,   155,   155,
       5,     7,     5,     7,    84,     7,   124,     7,     7,     7,
       7,   155,     7,   155,     7,     7,     7,   155,     4,   155,
       4,     4,     4,   155,   155,   155,     4,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,     4,   155,     4,
       6,     3,     6,     3,     3,     6,     3,   155,     6,     3,
       6,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   156,     6,     3,     6,     6,     3,   156,     4,
       8,     4,     4,     4,     4,     4,     4,     4,     4,   158,
     158,     4,   156,     3,   156,   156,   156,   156,     6,   156,
     156,     4,   156,     8,     8,     3,   156,   156,     8,     8,
       4,     4,     4,     4,     4,   156,   756,   759,   156,   759,
     155,   155,   762,   156,   155,   765,   768,   155,   768,   155,
     765,   759,   155,   759,   759,   765,   776,   155,     5,   779,
     768,   759,   768,   768,   762,     7,     4,   765,     4,     4,
     768,   339,   155,   155,   539,   795,   544,   155,   776,   799,
     756,   158,   771,   546,   768,   805,   774,   779,   808,   759,
     156,   811,   762,   420,   365,   765,   816,   795,   768,   756,
     155,   799,   369,   759,   155,   155,   776,   805,   765,   156,
     808,   768,   768,   811,   781,   788,   382,   759,   816,   776,
     776,   805,   761,   770,   808,   795,   925,    77,   764,   799,
     762,   765,   767,   805,   385,   805,   807,   392,   808,   808,
     777,   811,   810,   929,   402,   795,   816,   813,   799,   805,
     412,   811,   808,   562,   946,   811,   817,   417,   540,   816,
     962,   979,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   436,
      -1,    -1,    -1,   439,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   925,    -1,   925,    -1,    -1,    -1,   929,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   925,    -1,   925,
     925,    -1,    -1,    -1,    -1,    -1,   946,   925,    -1,    -1,
      -1,   929,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   925,    -1,    -1,    -1,    -1,    -1,    -1,   946,    -1,
      -1,    -1,    -1,    -1,    -1,   925,    -1,    -1,    -1,   929,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   925,   925,
      -1,    -1,   929,   929,    -1,    -1,   946,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   946
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     5,     7,     9,   155,   156,   157,   158,   175,   176,
     177,   182,     7,   191,     7,   197,     7,   208,     7,   287,
       7,   362,     7,   378,     7,   395,     7,   314,     7,   320,
       7,   344,     7,   263,     7,   452,     7,   487,   183,   178,
     192,   198,   209,   288,   363,   379,   396,   315,   321,   345,
     264,   453,   488,   175,   184,   185,   155,   180,   181,    10,
     129,   138,   139,   140,   155,   190,   193,   194,   195,   479,
     481,   483,   485,    11,    14,    15,    33,    34,    35,    36,
      37,    38,    39,    40,    58,    59,    69,    70,    71,    72,
      73,    85,    88,    95,   103,   104,   107,   190,   199,   200,
     201,   202,   203,   204,   205,   206,   215,   217,   243,   249,
     255,   257,   271,   281,   304,   312,   338,   368,   370,   418,
     429,   441,   442,   450,    12,    13,   190,   210,   211,   212,
     214,   368,   370,    50,    52,    60,    61,    62,    63,    64,
      65,    75,    76,    83,   190,   201,   202,   203,   204,   289,
     290,   291,   293,   295,   297,   299,   302,   303,   338,   356,
     368,   370,   372,   389,   414,    51,   190,   297,   338,   364,
     365,   366,   368,   370,    53,    54,    55,    56,    57,   190,
     297,   338,   368,   370,   380,   381,   382,   384,   385,   387,
     388,    73,    77,    78,    79,    80,    81,    82,   190,   338,
     368,   370,   397,   398,   399,   400,   402,   404,   406,   408,
     410,   412,   312,    16,    41,    43,    44,    47,    48,    49,
     190,   231,   322,   323,   324,   325,   326,   327,   328,   330,
     332,   334,   335,   337,   368,   370,    42,    45,    46,   190,
     231,   326,   332,   346,   347,   348,   349,   350,   352,   353,
     354,   355,   368,   370,    86,    87,   190,   265,   266,   267,
     269,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   190,   368,   370,   454,   455,
     456,   457,   459,   461,   462,   464,   465,   466,   469,   471,
     472,   473,   474,   477,   130,   489,   490,   491,     6,     3,
       4,     8,     3,   196,   486,   480,   482,   484,     4,     3,
       8,   207,   216,   218,     4,     4,     4,     4,     4,   282,
     313,   339,   369,   371,   305,   244,   256,   250,   419,   258,
     272,   430,     4,   443,   451,     3,     8,   213,     4,     3,
       8,   357,   373,   292,   294,   296,     4,     4,   300,   298,
     390,   415,     3,     8,   367,     3,     8,   383,     4,   386,
       4,     4,     3,     8,   413,   401,   403,   405,   407,   409,
     411,     8,     3,     8,   329,   232,     4,   333,   331,   336,
       4,     8,     3,   351,     4,     4,     8,     3,   268,   270,
       3,     8,     4,   458,   460,     4,   463,     4,     4,   467,
     470,     4,     4,     4,   475,   478,     3,     8,   492,     3,
       8,   175,   175,   155,     4,     4,     4,     4,     4,   194,
       4,     4,     4,   156,   156,   156,   156,   156,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   156,     4,     4,   200,     4,   158,   211,     4,     4,
       4,     4,     4,   156,   158,     4,     4,     4,     4,   290,
       4,   365,     4,   156,     4,   156,   156,   381,     4,     4,
       4,     4,     4,     4,     4,   399,     4,     4,   156,     4,
       4,     4,   158,   324,     4,   158,   158,   348,     4,     4,
     266,   158,     4,     4,   156,     4,   156,   156,     4,     4,
     158,   158,   158,     4,     4,   455,     4,   490,     4,     7,
       7,   175,   175,   175,     7,     7,     7,     5,     5,     5,
     177,   179,   155,     5,     5,     5,     5,     5,     5,     7,
       7,     7,     7,     5,   186,     5,     5,   155,   155,   155,
      66,    67,    68,   301,   155,     5,     7,   155,   155,   155,
     186,   186,   186,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   175,   155,   155,   155,   122,   123,
     468,   124,   125,   126,   127,   128,   158,   476,   155,     5,
     175,   199,   489,   210,    16,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   190,   219,   220,
     221,   224,   226,   228,   230,   231,   233,   234,   235,   236,
     237,   239,   240,   241,   219,     7,   283,   284,   285,     7,
     316,   317,   318,     7,   340,   341,   342,     7,   306,   307,
     308,    79,   155,   245,   246,   247,   248,   184,    80,    82,
     247,   251,   252,   253,   254,     7,   420,   421,     7,   259,
     260,   261,    89,    90,    91,    92,    93,    94,   273,   274,
     275,   276,   277,   278,   279,   280,    16,    99,   100,   101,
     102,   190,   233,   368,   370,   431,   432,   433,   436,   437,
     439,   440,   105,   106,   190,   368,   370,   444,   445,   446,
     448,   454,   187,     7,   358,   359,   360,     7,   374,   375,
     376,     7,   391,   392,   393,    84,   416,     7,   493,   494,
       8,     8,     8,   222,   225,   227,   229,     4,     4,     4,
       4,     4,   238,     4,     4,   242,     3,     8,     8,   286,
       6,     3,   319,     6,     3,   343,     6,     3,   309,     6,
       3,     3,     6,     6,     3,     6,   422,     3,     6,   262,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     434,   438,     4,     4,     4,     3,     8,   447,   449,     3,
       8,     8,   155,   188,   189,   361,     6,     3,   377,     6,
       3,   394,     6,     3,   417,     8,   495,     3,     6,     4,
       4,     4,     4,   156,   158,   156,   158,   156,     4,   156,
     156,     4,   220,   289,   285,   322,   318,   346,   342,   190,
     201,   202,   203,   204,   231,   281,   293,   295,   297,   299,
     303,   310,   311,   338,   368,   370,   414,   308,   246,   252,
      74,   190,   231,   338,   368,   370,   423,   424,   425,   426,
     427,   421,   265,   261,   156,   156,   156,   156,   156,   156,
     274,     4,     4,   156,   156,   156,   432,     4,     4,   445,
       6,     3,   364,   360,   380,   376,   397,   393,     4,   131,
     133,   134,   190,   231,   368,   370,   496,   497,   498,   499,
     501,   494,    17,    18,    19,    20,   223,   155,   155,   155,
     155,   155,     8,     8,     8,     3,     8,   428,     8,     3,
       8,    96,    97,    98,   435,   155,   155,   155,   155,     8,
       8,     8,   155,   502,     4,   500,     3,     8,   311,     4,
     425,     4,   156,     4,   497,   155,     5,   155,     7,   503,
     504,   505,     3,     6,   132,   135,   136,   137,   506,   507,
     508,   510,   511,   512,   504,   509,     4,     4,     4,     3,
       8,     4,   158,   156,   156,   507,   155
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   159,   161,   160,   162,   160,   163,   160,   164,   160,
     165,   160,   166,   160,   167,   160,   168,   160,   169,   160,
     170,   160,   171,   160,   172,   160,   173,   160,   174,   160,
     175,   175,   175,   175,   175,   175,   175,   176,   178,   177,
     179,   180,   180,   181,   181,   183,   182,   184,   184,   185,
     185,   187,   186,   188,   188,   189,   189,   190,   192,   191,
     193,   193,   194,   194,   194,   194,   194,   194,   196,   195,
     198,   197,   199,   199,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   201,
     202,   203,   204,   205,   207,   206,   209,   208,   210,   210,
     211,   211,   211,   211,   211,   213,   212,   214,   216,   215,
     218,   217,   219,   219,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   222,
     221,   223,   223,   223,   223,   225,   224,   227,   226,   229,
     228,   230,   232,   231,   233,   234,   235,   236,   238,   237,
     239,   240,   242,   241,   244,   243,   245,   245,   246,   246,
     247,   248,   250,   249,   251,   251,   252,   252,   252,   253,
     254,   256,   255,   258,   257,   259,   259,   260,   260,   262,
     261,   264,   263,   265,   265,   265,   266,   266,   268,   267,
     270,   269,   272,   271,   273,   273,   274,   274,   274,   274,
     274,   274,   275,   276,   277,   278,   279,   280,   282,   281,
     283,   283,   284,   284,   286,   285,   288,   287,   289,   289,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   292,
     291,   294,   293,   296,   295,   298,   297,   300,   299,   301,
     301,   301,   302,   303,   305,   304,   306,   306,   307,   307,
     309,   308,   310,   310,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     313,   312,   315,   314,   316,   316,   317,   317,   319,   318,
     321,   320,   322,   322,   323,   323,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   325,   326,   327,   329,
     328,   331,   330,   333,   332,   334,   336,   335,   337,   339,
     338,   340,   340,   341,   341,   343,   342,   345,   344,   346,
     346,   347,   347,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   349,   351,   350,   352,   353,   354,   355,   357,
     356,   358,   358,   359,   359,   361,   360,   363,   362,   364,
     364,   365,   365,   365,   365,   365,   365,   367,   366,   369,
     368,   371,   370,   373,   372,   374,   374,   375,   375,   377,
     376,   379,   378,   380,   380,   381,   381,   381,   381,   381,
     381,   381,   381,   381,   381,   383,   382,   384,   386,   385,
     387,   388,   390,   389,   391,   391,   392,   392,   394,   393,
     396,   395,   397,   397,   398,   398,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   399,   399,   401,   400,   403,
     402,   405,   404,   407,   406,   409,   408,   411,   410,   413,
     412,   415,   414,   417,   416,   419,   418,   420,   420,   422,
     421,   423,   423,   424,   424,   425,   425,   425,   425,   425,
     425,   426,   428,   427,   430,   429,   431,   431,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   434,   433,   435,
     435,   435,   436,   438,   437,   439,   440,   441,   443,   442,
     444,   444,   445,   445,   445,   445,   445,   447,   446,   449,
     448,   451,   450,   453,   452,   454,   454,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   456,   458,   457,   460,   459,   461,
     463,   462,   464,   465,   467,   466,   468,   468,   470,   469,
     471,   472,   473,   475,   474,   476,   476,   476,   476,   476,
     478,   477,   480,   479,   482,   481,   484,   483,   486,   485,
     488,   487,   489,   489,   490,   492,   491,   493,   493,   495,
     494,   496,   496,   497,   497,   497,   497,   497,   497,   497,
     498,   500,   499,   502,   501,   503,   503,   505,   504,   506,
     506,   507,   507,   507,   507,   509,   508,   510,   511,   512
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     0,     4,
       3,     3,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"keyspace\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
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
  "lease_database", "$@24", "hosts_database", "$@25",
  "database_map_params", "database_map_param", "database_type", "$@26",
  "db_type", "user", "$@27", "password", "$@28", "host", "$@29", "port",
  "name", "$@30", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@31", "max_reconnect_tries", "reconnect_wait_time",
  "keyspace", "$@32", "mac_sources", "$@33", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@34",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@35",
  "hooks_libraries", "$@36", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@37",
  "sub_hooks_library", "$@38", "hooks_params", "hooks_param", "library",
  "$@39", "parameters", "$@40", "expired_leases_processing", "$@41",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@42",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@43",
  "sub_subnet6", "$@44", "subnet6_params", "subnet6_param", "subnet",
  "$@45", "interface", "$@46", "interface_id", "$@47", "client_class",
  "$@48", "reservation_mode", "$@49", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@50", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@51",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@52", "sub_option_def_list", "$@53", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@54",
  "sub_option_def", "$@55", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@56",
  "option_def_record_types", "$@57", "space", "$@58", "option_def_space",
  "option_def_encapsulate", "$@59", "option_def_array", "option_data_list",
  "$@60", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@61", "sub_option_data", "$@62",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@63",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@64", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@65", "sub_pool6", "$@66",
  "pool_params", "pool_param", "pool_entry", "$@67", "user_context",
  "$@68", "comment", "$@69", "pd_pools_list", "$@70",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@71", "sub_pd_pool", "$@72", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@73", "pd_prefix_len", "excluded_prefix", "$@74",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@75",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@76", "sub_reservation", "$@77", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@78", "prefixes", "$@79", "duid", "$@80", "hw_address", "$@81",
  "hostname", "$@82", "flex_id_value", "$@83",
  "reservation_client_classes", "$@84", "relay", "$@85", "relay_map",
  "$@86", "client_classes", "$@87", "client_classes_list",
  "client_class_entry", "$@88", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@89", "server_id", "$@90",
  "server_id_params", "server_id_param", "server_id_type", "$@91",
  "duid_type", "htype", "identifier", "$@92", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@93", "control_socket_params",
  "control_socket_param", "socket_type", "$@94", "socket_name", "$@95",
  "dhcp_ddns", "$@96", "sub_dhcp_ddns", "$@97", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@98",
  "server_ip", "$@99", "server_port", "sender_ip", "$@100", "sender_port",
  "max_queue_size", "ncr_protocol", "$@101", "ncr_protocol_value",
  "ncr_format", "$@102", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@103",
  "replace_client_name_value", "generated_prefix", "$@104",
  "dhcp4_json_object", "$@105", "dhcpddns_json_object", "$@106",
  "control_agent_json_object", "$@107", "logging_object", "$@108",
  "sub_logging", "$@109", "logging_params", "logging_param", "loggers",
  "$@110", "loggers_entries", "logger_entry", "$@111", "logger_params",
  "logger_param", "debuglevel", "severity", "$@112", "output_options_list",
  "$@113", "output_options_list_content", "output_entry", "$@114",
  "output_params_list", "output_params", "output", "$@115", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   240,   240,   240,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   245,   246,   246,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   251,   252,   252,   253,   253,
     261,   262,   263,   264,   265,   266,   267,   270,   275,   275,
     286,   289,   290,   293,   297,   304,   304,   311,   312,   315,
     319,   326,   326,   333,   334,   337,   341,   352,   362,   362,
     377,   378,   382,   383,   384,   385,   386,   387,   390,   390,
     405,   405,   414,   415,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   447,
     452,   457,   462,   467,   472,   472,   483,   483,   492,   493,
     496,   497,   498,   499,   500,   503,   503,   513,   519,   519,
     531,   531,   543,   544,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   564,
     564,   571,   572,   573,   574,   577,   577,   585,   585,   593,
     593,   601,   606,   606,   614,   619,   624,   629,   634,   634,
     642,   647,   652,   652,   661,   661,   671,   672,   675,   676,
     679,   684,   689,   689,   699,   700,   703,   704,   705,   708,
     713,   720,   720,   730,   730,   740,   741,   744,   745,   748,
     748,   758,   758,   768,   769,   770,   773,   774,   777,   777,
     785,   785,   793,   793,   804,   805,   808,   809,   810,   811,
     812,   813,   816,   821,   826,   831,   836,   841,   849,   849,
     862,   863,   866,   867,   874,   874,   900,   900,   911,   912,
     916,   917,   918,   919,   920,   921,   922,   923,   924,   925,
     926,   927,   928,   929,   930,   931,   932,   933,   934,   937,
     937,   945,   945,   953,   953,   961,   961,   969,   969,   976,
     977,   978,   981,   986,   994,   994,  1005,  1006,  1010,  1011,
    1014,  1014,  1022,  1023,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,
    1048,  1048,  1061,  1061,  1070,  1071,  1074,  1075,  1080,  1080,
    1095,  1095,  1109,  1110,  1113,  1114,  1117,  1118,  1119,  1120,
    1121,  1122,  1123,  1124,  1125,  1126,  1129,  1131,  1136,  1138,
    1138,  1146,  1146,  1154,  1154,  1162,  1164,  1164,  1172,  1181,
    1181,  1193,  1194,  1199,  1200,  1205,  1205,  1217,  1217,  1229,
    1230,  1235,  1236,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1252,  1254,  1254,  1262,  1264,  1266,  1271,  1279,
    1279,  1291,  1292,  1295,  1296,  1299,  1299,  1309,  1309,  1318,
    1319,  1322,  1323,  1324,  1325,  1326,  1327,  1330,  1330,  1338,
    1338,  1363,  1363,  1393,  1393,  1405,  1406,  1409,  1410,  1413,
    1413,  1425,  1425,  1437,  1438,  1441,  1442,  1443,  1444,  1445,
    1446,  1447,  1448,  1449,  1450,  1453,  1453,  1461,  1466,  1466,
    1474,  1479,  1487,  1487,  1497,  1498,  1501,  1502,  1505,  1505,
    1514,  1514,  1523,  1524,  1527,  1528,  1532,  1533,  1534,  1535,
    1536,  1537,  1538,  1539,  1540,  1541,  1542,  1545,  1545,  1555,
    1555,  1565,  1565,  1573,  1573,  1581,  1581,  1589,  1589,  1597,
    1597,  1610,  1610,  1620,  1620,  1631,  1631,  1641,  1642,  1645,
    1645,  1655,  1656,  1659,  1660,  1663,  1664,  1665,  1666,  1667,
    1668,  1671,  1673,  1673,  1684,  1684,  1696,  1697,  1700,  1701,
    1702,  1703,  1704,  1705,  1706,  1707,  1708,  1711,  1711,  1718,
    1719,  1720,  1723,  1728,  1728,  1736,  1741,  1748,  1755,  1755,
    1765,  1766,  1769,  1770,  1771,  1772,  1773,  1776,  1776,  1784,
    1784,  1794,  1794,  1806,  1806,  1816,  1817,  1820,  1821,  1822,
    1823,  1824,  1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,
    1833,  1834,  1835,  1836,  1839,  1844,  1844,  1852,  1852,  1860,
    1865,  1865,  1873,  1878,  1883,  1883,  1891,  1892,  1895,  1895,
    1903,  1908,  1913,  1918,  1918,  1926,  1929,  1932,  1935,  1938,
    1944,  1944,  1954,  1954,  1961,  1961,  1968,  1968,  1981,  1981,
    1991,  1991,  2002,  2003,  2007,  2011,  2011,  2023,  2024,  2028,
    2028,  2036,  2037,  2040,  2041,  2042,  2043,  2044,  2045,  2046,
    2049,  2054,  2054,  2062,  2062,  2072,  2073,  2076,  2076,  2084,
    2085,  2088,  2089,  2090,  2091,  2094,  2094,  2102,  2107,  2112
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
#line 4615 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2117 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
