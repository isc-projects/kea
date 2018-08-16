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
      case 241: // db_type
      case 330: // hr_mode
      case 466: // duid_type
      case 499: // ncr_protocol_value
      case 507: // replace_client_name_value
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
      case 241: // db_type
      case 330: // hr_mode
      case 466: // duid_type
      case 499: // ncr_protocol_value
      case 507: // replace_client_name_value
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

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 167: // "integer"

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 168: // "floating point"

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 169: // "boolean"

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 186: // value

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 190: // map_value

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 241: // db_type

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 330: // hr_mode

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 466: // duid_type

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 499: // ncr_protocol_value

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 507: // replace_client_name_value

#line 244 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 241: // db_type
      case 330: // hr_mode
      case 466: // duid_type
      case 499: // ncr_protocol_value
      case 507: // replace_client_name_value
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
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 299 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 306 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 328 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 339 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 350 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 354 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 380 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 404 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-reconfiguration", b);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 626 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 730 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 747 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1572 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1717 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1818 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 1006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1040 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1194 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2499 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2553 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2562 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2573 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2601 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2810 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1845 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2923 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2979 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3046 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1988 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2020 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2057 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3263 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2063 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2066 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3332 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3342 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2114 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 617:
#line 2155 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 618:
#line 2160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3451 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2176 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 632:
#line 2193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 633:
#line 2198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 634:
#line 2200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 635:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2224 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 647:
#line 2238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 648:
#line 2240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 649:
#line 2246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 650:
#line 2251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 651:
#line 2256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3579 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3583 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -798;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     310,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,    54,    46,    70,    80,    84,
      98,   110,   121,   129,   131,   139,   151,   164,   165,   177,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,    46,   -82,
      40,    58,    44,   225,   257,   105,   236,   155,    41,   381,
     -19,   444,    67,  -798,   260,   249,   270,   248,   273,  -798,
    -798,  -798,  -798,  -798,   282,  -798,    82,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,   299,   306,   309,
     313,   332,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,   341,  -798,  -798,
     344,  -798,   106,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,   352,  -798,   142,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,   358,   364,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,   145,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   149,
    -798,  -798,  -798,  -798,  -798,   375,  -798,   376,   378,  -798,
    -798,  -798,  -798,  -798,  -798,   184,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,   288,   326,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,   330,  -798,  -798,   380,  -798,  -798,  -798,
     382,  -798,  -798,   384,   385,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   391,   393,
    -798,  -798,  -798,  -798,   411,   398,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   196,  -798,
    -798,  -798,   416,  -798,  -798,   417,  -798,   418,   420,  -798,
    -798,   421,   430,   433,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,   213,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
     240,  -798,  -798,  -798,    46,    46,  -798,   274,   437,   438,
     441,   442,   443,  -798,    40,  -798,   445,   447,   448,   450,
     281,   289,   290,   291,   293,   451,   455,   472,   473,   474,
     475,   476,   477,   481,   482,   483,   484,   485,   486,   487,
     327,   488,   489,   328,    58,  -798,   491,   329,    44,  -798,
     495,   496,   498,   499,   500,   338,   339,   505,   506,   507,
     508,   225,  -798,   510,   257,  -798,   511,   350,   512,   351,
     356,   105,  -798,   515,   520,   522,   523,   524,   525,   526,
    -798,   236,  -798,   527,   531,   371,   533,   535,   536,   372,
    -798,    41,   538,   374,   379,  -798,   381,   545,   546,   -24,
    -798,   383,   547,   549,   387,   551,   389,   390,   554,   570,
     406,   407,   408,   574,   575,   579,   580,   444,  -798,   581,
      67,  -798,  -798,  -798,   582,   583,   584,    46,    46,    46,
    -798,   585,   586,   587,   590,  -798,  -798,  -798,  -798,  -798,
     591,   592,   593,   594,   422,   595,   597,   598,   599,   600,
     601,   603,   604,   605,   606,  -798,   607,   608,  -798,  -798,
     611,  -798,  -798,   612,   613,   423,   439,   453,  -798,  -798,
     334,   611,   454,   614,  -798,   456,  -798,   457,  -798,   458,
    -798,  -798,  -798,   611,   611,   611,   459,   460,   461,   462,
    -798,   463,   464,  -798,   465,   466,   467,  -798,  -798,   468,
    -798,  -798,  -798,   469,    46,  -798,  -798,   470,   471,  -798,
     478,  -798,  -798,    87,   479,  -798,  -798,  -798,   -53,   480,
     490,   492,  -798,   633,  -798,    46,    58,    67,  -798,  -798,
    -798,    44,   205,   205,   632,   634,   635,   636,  -798,  -798,
    -798,   638,   -27,    46,    37,   509,   640,   641,   642,    77,
      93,    16,   444,  -798,  -798,   643,   644,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,   -33,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,   645,  -798,   243,   246,   250,  -798,  -798,  -798,  -798,
     649,   650,   651,   653,   655,  -798,   656,   657,  -798,   658,
     659,   660,  -798,   252,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,   264,  -798,   661,   596,  -798,  -798,   662,   637,
    -798,  -798,   663,   667,  -798,  -798,   665,   669,  -798,  -798,
     668,   670,  -798,  -798,  -798,   112,  -798,  -798,  -798,   671,
    -798,  -798,  -798,   180,  -798,  -798,  -798,  -798,   265,  -798,
    -798,  -798,   239,  -798,  -798,   672,   673,  -798,  -798,   674,
     676,  -798,   677,   678,   679,   680,   681,   682,   267,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   683,   684,
     685,  -798,  -798,  -798,  -798,   275,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,   292,  -798,  -798,
    -798,   294,   528,  -798,   686,   687,  -798,  -798,   689,   688,
    -798,  -798,  -798,   690,  -798,  -798,   279,  -798,  -798,  -798,
    -798,   692,   693,   695,   696,   534,   497,   537,   539,   540,
     698,   542,   543,   699,   544,   548,   550,   205,  -798,  -798,
     205,  -798,   632,   225,  -798,   634,    41,  -798,   635,   381,
    -798,   636,   370,  -798,   638,   -27,  -798,  -798,    37,  -798,
     701,   509,  -798,    78,   640,  -798,   236,  -798,   641,   -19,
    -798,   642,   553,   555,   556,   557,   558,   559,    77,  -798,
     702,   708,   560,   561,   562,    93,  -798,   709,   710,    16,
    -798,  -798,  -798,   711,   713,   257,  -798,   643,   105,  -798,
     644,   714,  -798,    81,   645,  -798,    43,   564,   565,   566,
    -798,  -798,  -798,  -798,  -798,   567,  -798,  -798,   568,  -798,
    -798,  -798,  -798,   303,  -798,   324,  -798,   727,  -798,   728,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,   325,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,   571,  -798,  -798,   717,  -798,  -798,  -798,
    -798,  -798,   730,   736,  -798,  -798,  -798,  -798,  -798,   732,
    -798,   336,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
     312,   576,  -798,  -798,  -798,  -798,   578,   588,  -798,  -798,
     618,   346,  -798,   349,  -798,   620,  -798,   737,  -798,  -798,
    -798,  -798,  -798,   361,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,   370,  -798,  -798,   741,   624,  -798,    78,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,   744,   629,   746,    81,  -798,  -798,   646,
    -798,  -798,   748,  -798,   652,  -798,  -798,   750,  -798,  -798,
     301,  -798,   -35,   750,  -798,  -798,   747,   756,   761,   369,
    -798,  -798,  -798,  -798,  -798,  -798,   768,   630,   639,   654,
     -35,  -798,   664,  -798,  -798,  -798,  -798,  -798
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   111,     9,   252,    11,
     397,    13,   422,    15,   452,    17,   322,    19,   330,    21,
     367,    23,   217,    25,   549,    27,   612,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   454,     0,   332,   369,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     610,   604,   606,   608,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   109,   123,   125,   127,     0,     0,     0,
       0,     0,   244,   320,   359,   410,   412,   293,   190,   207,
     198,   183,   489,   444,   209,   228,   510,     0,   534,   547,
       0,   102,     0,    72,    79,    74,    75,    76,    77,    78,
      82,    83,    84,    85,   100,    86,    88,    87,    92,    93,
      80,    81,    90,    91,    98,    99,   101,    89,    94,    95,
      96,    97,   120,     0,   119,     0,   113,   115,   116,   117,
     118,   389,   414,   276,   278,   280,     0,     0,   286,   284,
     282,   483,   275,   256,   257,   258,   259,     0,   254,   263,
     264,   265,   268,   269,   271,   266,   267,   260,   261,   273,
     274,   262,   270,   272,   408,   407,   403,   404,   402,     0,
     399,   401,   405,   406,   437,     0,   440,     0,     0,   436,
     430,   431,   429,   434,   435,     0,   424,   426,   427,   432,
     433,   428,   481,   469,   471,   473,   475,   477,   479,   468,
     465,   466,   467,     0,   455,   456,   460,   461,   458,   462,
     463,   464,   459,     0,   349,   168,     0,   353,   351,   356,
       0,   345,   346,     0,   333,   334,   336,   348,   337,   338,
     339,   355,   340,   341,   342,   343,   344,   383,     0,     0,
     381,   382,   385,   386,     0,   370,   371,   373,   374,   375,
     376,   377,   378,   379,   380,   224,   226,   221,     0,   219,
     222,   223,     0,   573,   575,     0,   578,     0,     0,   582,
     586,     0,     0,     0,   591,   598,   600,   602,   571,   569,
     570,     0,   551,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   566,   567,   568,   617,
       0,   614,   616,    46,     0,     0,    39,     0,     0,     0,
       0,     0,     0,    57,     0,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,     0,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   253,     0,     0,   398,     0,     0,     0,     0,
       0,     0,   423,     0,     0,     0,     0,     0,     0,     0,
     453,     0,   323,     0,     0,     0,     0,     0,     0,     0,
     331,     0,     0,     0,     0,   368,     0,     0,     0,     0,
     218,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   550,     0,
       0,   613,    50,    43,     0,     0,     0,     0,     0,     0,
      61,     0,     0,     0,     0,   104,   105,   106,   107,   108,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   533,     0,     0,   103,    73,
       0,   122,   114,     0,     0,     0,     0,     0,   291,   292,
       0,     0,     0,     0,   255,     0,   400,     0,   439,     0,
     442,   443,   425,     0,     0,     0,     0,     0,     0,     0,
     457,     0,     0,   347,     0,     0,     0,   358,   335,     0,
     387,   388,   372,     0,     0,   220,   572,     0,     0,   577,
       0,   580,   581,     0,     0,   588,   589,   590,     0,     0,
       0,     0,   552,     0,   615,     0,     0,     0,   605,   607,
     609,     0,     0,     0,   129,   246,   324,   361,    40,   411,
     413,   295,     0,    47,     0,     0,     0,   446,   211,     0,
       0,     0,     0,    51,   121,   391,   416,   277,   279,   281,
     288,   289,   290,   287,   285,   283,     0,   409,   438,   441,
     482,   470,   472,   474,   476,   478,   480,   350,   169,   354,
     352,   357,   384,   225,   227,   574,   576,   579,   584,   585,
     583,   587,   593,   594,   595,   596,   597,   592,   599,   601,
     603,     0,    44,     0,     0,     0,   155,   161,   163,   165,
       0,     0,     0,     0,     0,   178,     0,     0,   181,     0,
       0,     0,   154,     0,   135,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   149,   150,   151,   152,   147,
     148,   153,     0,   133,     0,   130,   131,   250,     0,   247,
     248,   328,     0,   325,   326,   365,     0,   362,   363,   299,
       0,   296,   297,   196,   197,     0,   192,   194,   195,     0,
     205,   206,   202,     0,   200,   203,   204,   188,     0,   185,
     187,   493,     0,   491,   450,     0,   447,   448,   215,     0,
     212,   213,     0,     0,     0,     0,     0,     0,     0,   230,
     232,   233,   234,   235,   236,   237,   523,   529,     0,     0,
       0,   522,   519,   520,   521,     0,   512,   514,   517,   515,
     516,   518,   543,   545,   542,   540,   541,     0,   536,   538,
     539,     0,    53,   395,     0,   392,   393,   420,     0,   417,
     418,   487,   486,     0,   485,   621,     0,   619,    69,   611,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   124,   126,
       0,   128,     0,     0,   245,     0,   332,   321,     0,   369,
     360,     0,     0,   294,     0,     0,   191,   208,     0,   199,
       0,     0,   184,   495,     0,   490,   454,   445,     0,     0,
     210,     0,     0,     0,     0,     0,     0,     0,     0,   229,
       0,     0,     0,     0,     0,     0,   511,     0,     0,     0,
     535,   548,    55,     0,    54,     0,   390,     0,     0,   415,
       0,     0,   484,     0,     0,   618,     0,     0,     0,     0,
     167,   170,   171,   172,   173,     0,   180,   174,     0,   175,
     176,   177,   136,     0,   132,     0,   249,     0,   327,     0,
     364,   319,   314,   316,   307,   308,   303,   304,   305,   306,
     312,   313,   311,   315,     0,   301,   309,   317,   318,   310,
     298,   193,   201,     0,   186,   507,     0,   505,   506,   502,
     503,   504,     0,   496,   497,   499,   500,   501,   492,     0,
     449,     0,   214,   238,   239,   240,   241,   242,   243,   231,
       0,     0,   528,   531,   532,   513,     0,     0,   537,    52,
       0,     0,   394,     0,   419,     0,   635,     0,   633,   631,
     625,   629,   630,     0,   623,   627,   628,   626,   620,   157,
     158,   159,   160,   156,   162,   164,   166,   179,   182,   134,
     251,   329,   366,     0,   300,   189,     0,     0,   494,     0,
     451,   216,   525,   526,   527,   524,   530,   544,   546,    56,
     396,   421,   488,     0,     0,     0,     0,   622,   302,     0,
     509,   498,     0,   632,     0,   624,   508,     0,   634,   639,
       0,   637,     0,     0,   636,   647,     0,     0,     0,     0,
     641,   643,   644,   645,   646,   638,     0,     0,     0,     0,
       0,   640,     0,   649,   650,   651,   642,   648
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,    15,  -798,   182,  -798,
    -798,  -798,  -798,  -798,  -798,    92,  -798,  -330,  -798,  -798,
    -798,   -70,  -798,  -798,  -798,   446,  -798,  -798,  -798,  -798,
     127,   424,  -798,   -66,   -54,   -51,   -34,  -798,  -798,  -798,
    -798,  -798,   231,   428,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,    -1,  -798,  -549,    -3,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   -42,
    -798,  -578,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,   -14,  -798,  -798,
    -798,  -798,  -798,    -5,  -571,  -798,  -798,  -798,  -798,    -4,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   -18,  -798,
    -798,  -798,   -13,   394,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,   -16,  -798,  -798,  -798,  -798,  -798,  -798,  -797,  -798,
    -798,  -798,    14,  -798,  -798,  -798,    21,   435,  -798,  -798,
    -788,  -798,  -784,  -798,   -30,  -798,   -28,  -798,  -782,  -798,
    -798,  -798,  -774,  -798,  -798,  -798,  -798,    17,  -798,  -798,
    -154,   765,  -798,  -798,  -798,  -798,  -798,    25,  -798,  -798,
    -798,    28,  -798,   414,  -798,   -38,  -798,  -798,  -798,  -798,
    -798,   -36,  -798,  -798,  -798,  -798,  -798,    -8,  -798,  -798,
    -798,    26,  -798,  -798,  -798,    27,  -798,   412,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   -17,
    -798,  -798,  -798,   -12,   452,  -798,  -798,   -58,  -798,   -46,
    -798,  -798,  -798,  -798,  -798,   -21,  -798,  -798,  -798,   -10,
     440,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   -31,  -798,
    -798,  -798,    23,  -798,  -798,  -798,    18,  -798,   431,   253,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -773,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,    29,  -798,  -798,  -798,  -144,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,     7,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,     5,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,   276,   409,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,   298,   410,  -798,  -798,  -798,    -7,
    -798,  -798,  -147,  -798,  -798,  -798,  -798,  -798,  -798,  -162,
    -798,  -798,  -178,  -798,  -798,  -798,  -798,  -798
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     579,    87,    88,    41,    68,    84,    85,   594,   772,   863,
     864,   662,    43,    70,    96,    97,    98,   348,    45,    71,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   356,
      47,    72,   165,   166,   167,   386,   168,   141,   357,   142,
     358,   143,   359,   684,   685,   686,   810,   663,   664,   665,
     791,   983,   666,   792,   667,   793,   668,   794,   669,   670,
     424,   671,   672,   673,   674,   675,   676,   677,   678,   679,
     800,   680,   681,   803,   144,   374,   718,   719,   720,   830,
     145,   371,   705,   706,   707,   708,   146,   373,   713,   714,
     715,   716,   147,   372,   148,   377,   729,   730,   731,   839,
      63,    80,   298,   299,   300,   437,   301,   438,   149,   378,
     738,   739,   740,   741,   742,   743,   744,   745,   150,   365,
     688,   689,   690,   813,    49,    73,   187,   188,   189,   392,
     190,   393,   191,   394,   192,   399,   193,   398,   194,   397,
     603,   195,   196,   151,   370,   700,   701,   702,   822,   914,
     915,   152,   366,    57,    77,   692,   693,   694,   816,    59,
      78,   263,   264,   265,   266,   267,   268,   269,   423,   270,
     427,   271,   426,   272,   273,   428,   274,   153,   367,   696,
     697,   698,   819,    61,    79,   284,   285,   286,   287,   288,
     432,   289,   290,   291,   292,   198,   390,   774,   775,   776,
     865,    51,    74,   209,   210,   211,   403,   154,   368,   155,
     369,   201,   391,   778,   779,   780,   868,    53,    75,   225,
     226,   227,   406,   228,   229,   408,   230,   231,   156,   376,
     725,   726,   727,   836,    55,    76,   243,   244,   245,   246,
     414,   247,   415,   248,   416,   249,   417,   250,   418,   251,
     419,   252,   413,   203,   400,   783,   784,   871,   157,   375,
     722,   723,   833,   932,   933,   934,   935,   936,   996,   937,
     158,   379,   755,   756,   757,   850,  1005,   758,   759,   851,
     760,   761,   159,   160,   381,   767,   768,   769,   857,   770,
     858,   161,   382,    65,    81,   321,   322,   323,   324,   442,
     325,   443,   326,   327,   445,   328,   329,   330,   448,   630,
     331,   449,   332,   333,   334,   335,   453,   637,   336,   454,
     337,   455,   338,   456,    99,   350,   100,   351,   101,   352,
     102,   349,    67,    82,   340,   341,   342,   459,   786,   787,
     873,   973,   974,   975,   976,  1015,   977,  1013,  1030,  1031,
    1032,  1039,  1040,  1041,  1046,  1042,  1043,  1044
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   131,   164,   182,   205,   219,   239,   183,   261,   280,
     297,   318,   752,   712,   169,   199,   212,   223,   241,   184,
     275,   293,   185,   319,   682,   907,   170,   200,   213,   224,
     242,    38,   276,   294,   908,   320,   262,   281,   909,   186,
     912,   282,   202,   283,   206,   220,   207,   221,   913,   919,
      89,    31,   233,    32,    30,    33,   162,   163,   254,   781,
     703,   979,   980,   981,   982,   197,   208,   222,   240,   103,
     295,   296,   104,   105,   106,   295,   296,    42,   115,   116,
     632,   633,   634,   635,    86,   354,   255,    44,   256,   257,
     355,    46,   258,   259,   260,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,    48,   115,   116,  1035,   384,
     746,  1036,  1037,  1038,   385,   825,   636,    50,   826,   651,
     115,   116,   114,   255,   703,   710,   255,   711,    52,   762,
     763,   117,   118,   119,   120,   121,    54,   122,    56,   704,
     115,   116,   123,   115,   116,   388,    58,    94,   401,   114,
     389,   124,   404,   402,   125,   115,   116,   405,    60,   925,
     926,   126,   214,   215,   216,   217,   218,   115,   116,   127,
     128,    62,    64,   129,   732,   733,   734,   735,   736,   737,
      90,   604,    94,   828,    66,   179,   829,   411,   180,    91,
      92,    93,   412,   610,   611,   612,   907,   130,   113,   439,
     747,   748,   749,   750,   440,   908,    94,    94,   339,   909,
      94,   912,    34,    35,    36,    37,   457,   628,   629,   913,
     919,   458,   646,   966,    94,   967,   968,   647,   648,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   659,
     660,   661,   834,   460,    94,   835,   384,    94,   461,   460,
     255,   788,   344,   388,   789,   807,   346,   712,   790,    94,
     808,   893,   107,   108,   109,   110,   343,   807,   831,   114,
     848,    94,   809,   832,   345,   849,   347,   752,   855,   171,
     114,   172,   874,   856,    95,   875,   353,   115,   116,   173,
     174,   175,   176,   177,   178,   859,   420,   457,   115,   116,
     860,   114,   861,   360,  1033,   179,   807,  1034,   180,   123,
     361,   989,   204,   362,   131,   232,   181,   363,   164,   115,
     116,   233,   234,   235,   236,   237,   238,   401,   993,   421,
     169,   182,   990,   994,   205,   183,   364,   179,   422,   439,
     180,   219,   170,   199,  1001,   380,   212,   184,   383,   404,
     185,   239,   411,   223,  1010,   200,   387,  1011,   213,   462,
     463,   261,   395,   241,  1016,   224,   280,   186,   396,  1017,
     202,    94,  1050,   275,   206,   242,   207,  1051,   293,   407,
     409,   220,   410,   221,   425,   276,   429,   318,   431,   262,
     294,    94,   430,   197,   281,   433,   208,   434,   282,   319,
     283,   436,    94,   222,   600,   601,   602,   107,   108,   109,
     110,   320,   112,   240,   114,   255,  1002,  1003,  1004,   435,
     441,   444,   446,    94,   447,   450,   255,   277,   256,   257,
     278,   279,   115,   116,   451,   174,   175,   452,   177,   178,
     464,   465,   466,   115,   116,   467,   468,   469,   475,   471,
     179,   472,   473,   180,   474,   480,   476,   477,   478,   481,
     479,   181,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   482,   483,   484,   485,
     486,   487,   568,   569,   570,   488,   489,   490,   491,   492,
     493,   494,   496,   497,   495,   500,   131,   498,   501,   503,
     504,   164,   505,   506,   507,   508,   115,   116,   509,   510,
     511,   512,   513,   169,   515,   517,   519,   518,   520,   523,
     751,   764,   318,   521,   524,   170,   525,   526,   527,   528,
     529,   531,   753,   765,   319,   532,    94,   534,   533,   535,
     536,   537,   539,   540,   754,   766,   320,    94,   541,   543,
     544,   547,   546,   548,   549,   550,   551,   552,   553,   624,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   554,   555,   556,   557,   558,   559,
     642,   316,   317,   560,   561,   563,   565,   717,   580,   597,
     566,   567,   571,   572,   573,   574,   575,   576,   577,   812,
     581,    32,   582,   583,   584,   598,   586,   585,   587,   588,
      94,   631,   589,   590,   591,   592,   593,   595,   596,   599,
     605,   606,   607,   608,   609,   613,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   625,   626,   641,   683,
     815,   687,   691,   695,   627,   699,   638,   721,   724,   728,
     773,   777,   785,   795,   796,   797,   639,   798,   640,   799,
     801,   802,   804,   805,   806,   578,   881,   811,   814,   817,
     818,   820,   821,   824,   823,   709,   838,   827,   837,   841,
     840,   842,   843,   844,   845,   846,   847,   852,   853,   854,
     867,   870,   866,   643,   862,   869,   876,   877,   872,   878,
     879,   880,   885,   888,   882,   923,   950,   884,   883,   886,
     887,   889,   951,   956,   957,   890,   960,   959,   965,   891,
     943,   997,   944,   945,   946,   947,   948,   952,   953,   954,
     984,   985,   986,   987,   988,   991,   992,   995,   998,   999,
    1000,  1014,  1006,   182,  1007,  1019,   261,   183,  1022,   280,
    1024,  1047,   901,  1027,  1008,   199,   902,  1029,   275,   184,
    1048,   293,   185,   927,   917,  1049,   239,   200,   903,   297,
     276,   904,  1052,   294,   262,   930,   918,   281,   241,   186,
     906,   282,   202,   283,  1009,   751,  1012,   931,   905,   764,
     242,   928,   910,  1020,   911,   205,  1023,   753,   219,  1053,
     470,   765,   645,   969,   892,   197,  1054,   212,   499,   754,
     223,   894,  1026,   766,   916,   971,   502,   924,  1028,   213,
     921,  1055,   224,   942,   922,   929,   941,   972,   240,   896,
    1057,   970,   949,   545,   895,   206,   514,   207,   220,  1018,
     221,   920,   253,   898,   897,   538,   899,   900,   542,   964,
     962,   522,   530,   961,   939,  1021,   516,   208,   963,   782,
     222,   940,   955,   938,   958,   644,   562,   978,   771,  1025,
     564,  1045,  1056,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   901,     0,     0,     0,   902,     0,   927,
       0,     0,     0,     0,     0,   917,     0,     0,     0,   903,
       0,   930,   904,     0,     0,     0,   969,   918,     0,     0,
       0,   906,     0,   931,     0,     0,     0,   928,   971,   905,
       0,     0,     0,   910,     0,   911,     0,     0,     0,     0,
     972,     0,     0,     0,   970,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   916,     0,     0,     0,     0,
       0,   929
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    73,    78,    79,
      80,    81,   590,   584,    72,    73,    74,    75,    76,    73,
      78,    79,    73,    81,   573,   822,    72,    73,    74,    75,
      76,    16,    78,    79,   822,    81,    78,    79,   822,    73,
     822,    79,    73,    79,    74,    75,    74,    75,   822,   822,
      10,     5,    85,     7,     0,     9,    12,    13,    17,    92,
      87,    18,    19,    20,    21,    73,    74,    75,    76,    11,
      94,    95,    14,    15,    16,    94,    95,     7,    62,    63,
     133,   134,   135,   136,   166,     3,    45,     7,    47,    48,
       8,     7,    51,    52,    53,    37,    38,    39,    40,    41,
      42,    43,    44,    62,    63,     7,    62,    63,   143,     3,
      17,   146,   147,   148,     8,     3,   169,     7,     6,    26,
      62,    63,    44,    45,    87,    88,    45,    90,     7,   113,
     114,    73,    74,    75,    76,    77,     7,    79,     7,   166,
      62,    63,    84,    62,    63,     3,     7,   166,     3,    44,
       8,    93,     3,     8,    96,    62,    63,     8,     7,    81,
      82,   103,    57,    58,    59,    60,    61,    62,    63,   111,
     112,     7,     7,   115,    97,    98,    99,   100,   101,   102,
     140,   511,   166,     3,     7,    80,     6,     3,    83,   149,
     150,   151,     8,   523,   524,   525,   993,   139,    43,     3,
     107,   108,   109,   110,     8,   993,   166,   166,   141,   993,
     166,   993,   166,   167,   168,   169,     3,   130,   131,   993,
     993,     8,    17,   142,   166,   144,   145,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,     3,     3,   166,     6,     3,   166,     8,     3,
      45,     8,     3,     3,     8,     3,     8,   828,     8,   166,
       8,   810,    37,    38,    39,    40,     6,     3,     3,    44,
       3,   166,     8,     8,     4,     8,     3,   855,     3,    54,
      44,    56,     3,     8,   354,     6,     4,    62,    63,    64,
      65,    66,    67,    68,    69,     3,     8,     3,    62,    63,
       8,    44,     8,     4,     3,    80,     3,     6,    83,    84,
       4,     8,    55,     4,   384,    79,    91,     4,   388,    62,
      63,    85,    86,    87,    88,    89,    90,     3,     3,     3,
     388,   401,     8,     8,   404,   401,     4,    80,     8,     3,
      83,   411,   388,   401,     8,     4,   404,   401,     4,     3,
     401,   421,     3,   411,     8,   401,     4,     8,   404,   344,
     345,   431,     4,   421,     3,   411,   436,   401,     4,     8,
     401,   166,     3,   431,   404,   421,   404,     8,   436,     4,
       4,   411,     4,   411,     4,   431,     4,   457,     3,   431,
     436,   166,     8,   401,   436,     4,   404,     4,   436,   457,
     436,     3,   166,   411,    70,    71,    72,    37,    38,    39,
      40,   457,    42,   421,    44,    45,   104,   105,   106,     8,
       4,     4,     4,   166,     4,     4,    45,    46,    47,    48,
      49,    50,    62,    63,     4,    65,    66,     4,    68,    69,
     166,     4,     4,    62,    63,     4,     4,     4,   167,     4,
      80,     4,     4,    83,     4,     4,   167,   167,   167,     4,
     167,    91,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     4,     4,     4,     4,
       4,     4,   467,   468,   469,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   167,     4,   566,   169,   169,     4,
       4,   571,     4,     4,     4,   167,    62,    63,   169,     4,
       4,     4,     4,   571,     4,     4,     4,   167,   167,     4,
     590,   591,   592,   167,     4,   571,     4,     4,     4,     4,
       4,     4,   590,   591,   592,     4,   166,     4,   167,     4,
       4,   169,     4,   169,   590,   591,   592,   166,   169,     4,
       4,     4,   169,     4,   167,     4,   167,   167,     4,   544,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,     4,   169,   169,   169,     4,     4,
     565,   137,   138,     4,     4,     4,     4,    78,   166,   166,
       7,     7,     7,     7,     7,     5,     5,     5,     5,     3,
       5,     7,     5,     5,     5,   166,     5,     7,     5,     5,
     166,   132,     7,     7,     7,     7,     5,     5,     5,   166,
     166,     7,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,     5,     7,
       3,     7,     7,     7,   166,     7,   166,     7,     7,     7,
       7,     7,     7,     4,     4,     4,   166,     4,   166,     4,
       4,     4,     4,     4,     4,   483,   169,     6,     6,     6,
       3,     6,     3,     3,     6,   583,     3,     6,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     3,     6,   566,   166,     6,     4,     4,     8,     4,
       4,   167,     4,     4,   167,     4,     4,   167,   169,   167,
     167,   167,     4,     4,     4,   167,     3,     6,     4,   169,
     167,     4,   167,   167,   167,   167,   167,   167,   167,   167,
     166,   166,   166,   166,   166,     8,     8,   166,     8,     3,
       8,     4,   166,   813,   166,     4,   816,   813,     4,   819,
       4,     4,   822,     5,   166,   813,   822,     7,   816,   813,
       4,   819,   813,   833,   822,     4,   836,   813,   822,   839,
     816,   822,     4,   819,   816,   833,   822,   819,   836,   813,
     822,   819,   813,   819,   166,   855,   166,   833,   822,   859,
     836,   833,   822,   169,   822,   865,   167,   855,   868,   169,
     354,   859,   571,   873,   807,   813,   167,   865,   384,   855,
     868,   812,   166,   859,   822,   873,   388,   831,   166,   865,
     825,   167,   868,   841,   828,   833,   839,   873,   836,   815,
     166,   873,   848,   439,   813,   865,   401,   865,   868,   993,
     868,   824,    77,   818,   816,   431,   819,   821,   436,   870,
     867,   411,   421,   865,   836,   999,   404,   865,   868,   606,
     868,   838,   855,   834,   859,   567,   457,   874,   592,  1016,
     460,  1033,  1050,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   993,    -1,    -1,    -1,   993,    -1,   999,
      -1,    -1,    -1,    -1,    -1,   993,    -1,    -1,    -1,   993,
      -1,   999,   993,    -1,    -1,    -1,  1016,   993,    -1,    -1,
      -1,   993,    -1,   999,    -1,    -1,    -1,   999,  1016,   993,
      -1,    -1,    -1,   993,    -1,   993,    -1,    -1,    -1,    -1,
    1016,    -1,    -1,    -1,  1016,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   993,    -1,    -1,    -1,    -1,
      -1,   999
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     5,     7,     9,   166,   167,   168,   169,   186,   187,
     188,   193,     7,   202,     7,   208,     7,   220,     7,   314,
       7,   391,     7,   407,     7,   424,     7,   343,     7,   349,
       7,   373,     7,   290,     7,   483,     7,   522,   194,   189,
     203,   209,   221,   315,   392,   408,   425,   344,   350,   374,
     291,   484,   523,   186,   195,   196,   166,   191,   192,    10,
     140,   149,   150,   151,   166,   201,   204,   205,   206,   514,
     516,   518,   520,    11,    14,    15,    16,    37,    38,    39,
      40,    41,    42,    43,    44,    62,    63,    73,    74,    75,
      76,    77,    79,    84,    93,    96,   103,   111,   112,   115,
     139,   201,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   227,   229,   231,   264,   270,   276,   282,   284,   298,
     308,   333,   341,   367,   397,   399,   418,   448,   460,   472,
     473,   481,    12,    13,   201,   222,   223,   224,   226,   397,
     399,    54,    56,    64,    65,    66,    67,    68,    69,    80,
      83,    91,   201,   213,   214,   215,   216,   316,   317,   318,
     320,   322,   324,   326,   328,   331,   332,   367,   385,   397,
     399,   401,   418,   443,    55,   201,   324,   326,   367,   393,
     394,   395,   397,   399,    57,    58,    59,    60,    61,   201,
     324,   326,   367,   397,   399,   409,   410,   411,   413,   414,
     416,   417,    79,    85,    86,    87,    88,    89,    90,   201,
     367,   397,   399,   426,   427,   428,   429,   431,   433,   435,
     437,   439,   441,   341,    17,    45,    47,    48,    51,    52,
      53,   201,   249,   351,   352,   353,   354,   355,   356,   357,
     359,   361,   363,   364,   366,   397,   399,    46,    49,    50,
     201,   249,   355,   361,   375,   376,   377,   378,   379,   381,
     382,   383,   384,   397,   399,    94,    95,   201,   292,   293,
     294,   296,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   137,   138,   201,   397,
     399,   485,   486,   487,   488,   490,   492,   493,   495,   496,
     497,   500,   502,   503,   504,   505,   508,   510,   512,   141,
     524,   525,   526,     6,     3,     4,     8,     3,   207,   521,
     515,   517,   519,     4,     3,     8,   219,   228,   230,   232,
       4,     4,     4,     4,     4,   309,   342,   368,   398,   400,
     334,   271,   283,   277,   265,   449,   419,   285,   299,   461,
       4,   474,   482,     4,     3,     8,   225,     4,     3,     8,
     386,   402,   319,   321,   323,     4,     4,   329,   327,   325,
     444,     3,     8,   396,     3,     8,   412,     4,   415,     4,
       4,     3,     8,   442,   430,   432,   434,   436,   438,   440,
       8,     3,     8,   358,   250,     4,   362,   360,   365,     4,
       8,     3,   380,     4,     4,     8,     3,   295,   297,     3,
       8,     4,   489,   491,     4,   494,     4,     4,   498,   501,
       4,     4,     4,   506,   509,   511,   513,     3,     8,   527,
       3,     8,   186,   186,   166,     4,     4,     4,     4,     4,
     205,     4,     4,     4,     4,   167,   167,   167,   167,   167,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   167,     4,     4,   169,   211,
       4,   169,   223,     4,     4,     4,     4,     4,   167,   169,
       4,     4,     4,     4,   317,     4,   394,     4,   167,     4,
     167,   167,   410,     4,     4,     4,     4,     4,     4,     4,
     428,     4,     4,   167,     4,     4,     4,   169,   353,     4,
     169,   169,   377,     4,     4,   293,   169,     4,     4,   167,
       4,   167,   167,     4,     4,   169,   169,   169,     4,     4,
       4,     4,   486,     4,   525,     4,     7,     7,   186,   186,
     186,     7,     7,     7,     5,     5,     5,     5,   188,   190,
     166,     5,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     5,   197,     5,     5,   166,   166,   166,
      70,    71,    72,   330,   197,   166,     7,   166,   166,   166,
     197,   197,   197,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   186,   166,   166,   166,   130,   131,
     499,   132,   133,   134,   135,   136,   169,   507,   166,   166,
     166,     5,   186,   210,   524,   222,    17,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   201,   237,   238,   239,   242,   244,   246,   248,
     249,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     261,   262,   237,     7,   233,   234,   235,     7,   310,   311,
     312,     7,   345,   346,   347,     7,   369,   370,   371,     7,
     335,   336,   337,    87,   166,   272,   273,   274,   275,   195,
      88,    90,   274,   278,   279,   280,   281,    78,   266,   267,
     268,     7,   450,   451,     7,   420,   421,   422,     7,   286,
     287,   288,    97,    98,    99,   100,   101,   102,   300,   301,
     302,   303,   304,   305,   306,   307,    17,   107,   108,   109,
     110,   201,   251,   397,   399,   462,   463,   464,   467,   468,
     470,   471,   113,   114,   201,   397,   399,   475,   476,   477,
     479,   485,   198,     7,   387,   388,   389,     7,   403,   404,
     405,    92,   429,   445,   446,     7,   528,   529,     8,     8,
       8,   240,   243,   245,   247,     4,     4,     4,     4,     4,
     260,     4,     4,   263,     4,     4,     4,     3,     8,     8,
     236,     6,     3,   313,     6,     3,   348,     6,     3,   372,
       6,     3,   338,     6,     3,     3,     6,     6,     3,     6,
     269,     3,     8,   452,     3,     6,   423,     6,     3,   289,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     465,   469,     4,     4,     4,     3,     8,   478,   480,     3,
       8,     8,   166,   199,   200,   390,     6,     3,   406,     6,
       3,   447,     8,   530,     3,     6,     4,     4,     4,     4,
     167,   169,   167,   169,   167,     4,   167,   167,     4,   167,
     167,   169,   238,   237,   235,   316,   312,   351,   347,   375,
     371,   201,   213,   214,   215,   216,   249,   308,   320,   322,
     324,   326,   328,   332,   339,   340,   367,   397,   399,   443,
     337,   273,   279,     4,   267,    81,    82,   201,   249,   367,
     397,   399,   453,   454,   455,   456,   457,   459,   451,   426,
     422,   292,   288,   167,   167,   167,   167,   167,   167,   301,
       4,     4,   167,   167,   167,   463,     4,     4,   476,     6,
       3,   393,   389,   409,   405,     4,   142,   144,   145,   201,
     249,   397,   399,   531,   532,   533,   534,   536,   529,    18,
      19,    20,    21,   241,   166,   166,   166,   166,   166,     8,
       8,     8,     8,     3,     8,   166,   458,     4,     8,     3,
       8,     8,   104,   105,   106,   466,   166,   166,   166,   166,
       8,     8,   166,   537,     4,   535,     3,     8,   340,     4,
     169,   455,     4,   167,     4,   532,   166,     5,   166,     7,
     538,   539,   540,     3,     6,   143,   146,   147,   148,   541,
     542,   543,   545,   546,   547,   539,   544,     4,     4,     4,
       3,     8,     4,   169,   167,   167,   542,   166
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
     211,   211,   211,   212,   213,   214,   215,   216,   217,   219,
     218,   221,   220,   222,   222,   223,   223,   223,   223,   223,
     225,   224,   226,   228,   227,   230,   229,   232,   231,   233,
     233,   234,   234,   236,   235,   237,   237,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   240,   239,   241,   241,   241,
     241,   243,   242,   245,   244,   247,   246,   248,   250,   249,
     251,   252,   253,   254,   255,   256,   257,   258,   260,   259,
     261,   263,   262,   265,   264,   266,   266,   267,   269,   268,
     271,   270,   272,   272,   273,   273,   274,   275,   277,   276,
     278,   278,   279,   279,   279,   280,   281,   283,   282,   285,
     284,   286,   286,   287,   287,   289,   288,   291,   290,   292,
     292,   292,   293,   293,   295,   294,   297,   296,   299,   298,
     300,   300,   301,   301,   301,   301,   301,   301,   302,   303,
     304,   305,   306,   307,   309,   308,   310,   310,   311,   311,
     313,   312,   315,   314,   316,   316,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   319,   318,   321,   320,
     323,   322,   325,   324,   327,   326,   329,   328,   330,   330,
     330,   331,   332,   334,   333,   335,   335,   336,   336,   338,
     337,   339,   339,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     342,   341,   344,   343,   345,   345,   346,   346,   348,   347,
     350,   349,   351,   351,   352,   352,   353,   353,   353,   353,
     353,   353,   353,   353,   353,   353,   354,   355,   356,   358,
     357,   360,   359,   362,   361,   363,   365,   364,   366,   368,
     367,   369,   369,   370,   370,   372,   371,   374,   373,   375,
     375,   376,   376,   377,   377,   377,   377,   377,   377,   377,
     377,   377,   378,   380,   379,   381,   382,   383,   384,   386,
     385,   387,   387,   388,   388,   390,   389,   392,   391,   393,
     393,   394,   394,   394,   394,   394,   394,   394,   396,   395,
     398,   397,   400,   399,   402,   401,   403,   403,   404,   404,
     406,   405,   408,   407,   409,   409,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   412,   411,   413,
     415,   414,   416,   417,   419,   418,   420,   420,   421,   421,
     423,   422,   425,   424,   426,   426,   427,   427,   428,   428,
     428,   428,   428,   428,   428,   428,   428,   428,   428,   430,
     429,   432,   431,   434,   433,   436,   435,   438,   437,   440,
     439,   442,   441,   444,   443,   445,   445,   447,   446,   449,
     448,   450,   450,   452,   451,   453,   453,   454,   454,   455,
     455,   455,   455,   455,   455,   455,   456,   458,   457,   459,
     461,   460,   462,   462,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   465,   464,   466,   466,   466,   467,   469,
     468,   470,   471,   472,   474,   473,   475,   475,   476,   476,
     476,   476,   476,   478,   477,   480,   479,   482,   481,   484,
     483,   485,   485,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   487,   489,   488,   491,   490,   492,   494,   493,
     495,   496,   498,   497,   499,   499,   501,   500,   502,   503,
     504,   506,   505,   507,   507,   507,   507,   507,   509,   508,
     511,   510,   513,   512,   515,   514,   517,   516,   519,   518,
     521,   520,   523,   522,   524,   524,   525,   527,   526,   528,
     528,   530,   529,   531,   531,   532,   532,   532,   532,   532,
     532,   532,   533,   535,   534,   537,   536,   538,   538,   540,
     539,   541,   541,   542,   542,   542,   542,   544,   543,   545,
     546,   547
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
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     0,     4,     0,     6,     1,     3,     1,     0,     4,
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
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
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
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"enable-reconfiguration\"", "\"Logging\"", "\"loggers\"",
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
  "$@20", "global_params", "global_param", "enable_reconfiguration",
  "preferred_lifetime", "valid_lifetime", "renew_timer", "rebind_timer",
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
       0,   253,   253,   253,   254,   254,   255,   255,   256,   256,
     257,   257,   258,   258,   259,   259,   260,   260,   261,   261,
     262,   262,   263,   263,   264,   264,   265,   265,   266,   266,
     274,   275,   276,   277,   278,   279,   280,   283,   288,   288,
     299,   302,   303,   306,   310,   317,   317,   324,   325,   328,
     332,   339,   339,   346,   347,   350,   354,   365,   375,   375,
     390,   391,   395,   396,   397,   398,   399,   400,   404,   404,
     419,   419,   429,   430,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   466,   471,   476,   481,   486,   491,   496,
     496,   507,   507,   516,   517,   520,   521,   522,   523,   524,
     527,   527,   537,   543,   543,   555,   555,   567,   567,   577,
     578,   581,   582,   585,   585,   595,   596,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   619,   619,   626,   627,   628,
     629,   632,   632,   640,   640,   648,   648,   656,   661,   661,
     669,   674,   679,   684,   689,   694,   699,   704,   709,   709,
     717,   722,   722,   730,   730,   740,   741,   743,   745,   745,
     763,   763,   773,   774,   777,   778,   781,   786,   791,   791,
     801,   802,   805,   806,   807,   810,   815,   822,   822,   832,
     832,   842,   843,   846,   847,   850,   850,   860,   860,   870,
     871,   872,   875,   876,   879,   879,   887,   887,   895,   895,
     906,   907,   910,   911,   912,   913,   914,   915,   918,   923,
     928,   933,   938,   943,   951,   951,   964,   965,   968,   969,
     976,   976,  1002,  1002,  1013,  1014,  1018,  1019,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1034,  1035,  1036,  1037,  1040,  1040,  1048,  1048,
    1056,  1056,  1064,  1064,  1072,  1072,  1082,  1082,  1089,  1090,
    1091,  1094,  1099,  1107,  1107,  1118,  1119,  1123,  1124,  1127,
    1127,  1135,  1136,  1139,  1140,  1141,  1142,  1143,  1144,  1145,
    1146,  1147,  1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,
    1162,  1162,  1175,  1175,  1184,  1185,  1188,  1189,  1194,  1194,
    1209,  1209,  1223,  1224,  1227,  1228,  1231,  1232,  1233,  1234,
    1235,  1236,  1237,  1238,  1239,  1240,  1243,  1245,  1250,  1252,
    1252,  1260,  1260,  1268,  1268,  1276,  1278,  1278,  1286,  1295,
    1295,  1307,  1308,  1313,  1314,  1319,  1319,  1331,  1331,  1343,
    1344,  1349,  1350,  1355,  1356,  1357,  1358,  1359,  1360,  1361,
    1362,  1363,  1366,  1368,  1368,  1376,  1378,  1380,  1385,  1393,
    1393,  1405,  1406,  1409,  1410,  1413,  1413,  1423,  1423,  1432,
    1433,  1436,  1437,  1438,  1439,  1440,  1441,  1442,  1445,  1445,
    1453,  1453,  1478,  1478,  1508,  1508,  1520,  1521,  1524,  1525,
    1528,  1528,  1540,  1540,  1552,  1553,  1556,  1557,  1558,  1559,
    1560,  1561,  1562,  1563,  1564,  1565,  1566,  1569,  1569,  1577,
    1582,  1582,  1590,  1595,  1603,  1603,  1613,  1614,  1617,  1618,
    1621,  1621,  1630,  1630,  1639,  1640,  1643,  1644,  1648,  1649,
    1650,  1651,  1652,  1653,  1654,  1655,  1656,  1657,  1658,  1661,
    1661,  1671,  1671,  1681,  1681,  1689,  1689,  1697,  1697,  1705,
    1705,  1713,  1713,  1726,  1726,  1736,  1737,  1740,  1740,  1751,
    1751,  1761,  1762,  1765,  1765,  1775,  1776,  1779,  1780,  1783,
    1784,  1785,  1786,  1787,  1788,  1789,  1792,  1794,  1794,  1802,
    1810,  1810,  1822,  1823,  1826,  1827,  1828,  1829,  1830,  1831,
    1832,  1833,  1834,  1837,  1837,  1844,  1845,  1846,  1849,  1854,
    1854,  1862,  1867,  1874,  1881,  1881,  1891,  1892,  1895,  1896,
    1897,  1898,  1899,  1902,  1902,  1910,  1910,  1920,  1920,  1932,
    1932,  1942,  1943,  1946,  1947,  1948,  1949,  1950,  1951,  1952,
    1953,  1954,  1955,  1956,  1957,  1958,  1959,  1960,  1961,  1962,
    1963,  1964,  1967,  1972,  1972,  1980,  1980,  1988,  1993,  1993,
    2001,  2006,  2011,  2011,  2019,  2020,  2023,  2023,  2031,  2036,
    2041,  2046,  2046,  2054,  2057,  2060,  2063,  2066,  2072,  2072,
    2080,  2080,  2088,  2088,  2098,  2098,  2105,  2105,  2112,  2112,
    2125,  2125,  2135,  2135,  2146,  2147,  2151,  2155,  2155,  2167,
    2168,  2172,  2172,  2180,  2181,  2184,  2185,  2186,  2187,  2188,
    2189,  2190,  2193,  2198,  2198,  2206,  2206,  2216,  2217,  2220,
    2220,  2228,  2229,  2232,  2233,  2234,  2235,  2238,  2238,  2246,
    2251,  2256
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
#line 4865 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2261 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
