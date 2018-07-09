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
      case 183: // value
      case 187: // map_value
      case 237: // db_type
      case 320: // hr_mode
      case 456: // duid_type
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 166: // "boolean"
        value.move< bool > (that.value);
        break;

      case 165: // "floating point"
        value.move< double > (that.value);
        break;

      case 164: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 163: // "constant string"
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
      case 183: // value
      case 187: // map_value
      case 237: // db_type
      case 320: // hr_mode
      case 456: // duid_type
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 166: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 165: // "floating point"
        value.copy< double > (that.value);
        break;

      case 164: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 163: // "constant string"
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
            case 163: // "constant string"

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 164: // "integer"

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 165: // "floating point"

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 166: // "boolean"

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 183: // value

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 187: // map_value

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 237: // db_type

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 320: // hr_mode

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 456: // duid_type

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 489: // ncr_protocol_value

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 497: // replace_client_name_value

#line 239 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 183: // value
      case 187: // map_value
      case 237: // db_type
      case 320: // hr_mode
      case 456: // duid_type
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 166: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 165: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 164: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 163: // "constant string"
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
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 275 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 327 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 345 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 349 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 375 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 398 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 405 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 613 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1497 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1575 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 834 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1725 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1003 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1044 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1052 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1166 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1198 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1233 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2220 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2240 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1834 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1973 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3173 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2007 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2010 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3302 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2058 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3310 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3356 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2108 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2199 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2204 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3522 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3526 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -789;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     344,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,    35,    33,    34,    54,    82,
      95,   102,   140,   142,   148,   161,   168,   170,   181,   194,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,    33,    32,
      19,    41,    37,   220,   188,    63,    75,   160,    43,   268,
      -6,   355,    99,  -789,   239,   243,   250,   267,   275,  -789,
    -789,  -789,  -789,  -789,   277,  -789,    40,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,   315,   325,   331,
     339,   345,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,   346,  -789,  -789,  -789,    89,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,   349,  -789,    90,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
     352,   356,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,   145,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,   166,  -789,  -789,  -789,  -789,  -789,
     357,  -789,   362,   369,  -789,  -789,  -789,  -789,  -789,  -789,
     173,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,   303,   319,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,   363,  -789,
    -789,   370,  -789,  -789,  -789,   380,  -789,  -789,   378,   330,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,   388,   394,  -789,  -789,  -789,  -789,   391,
     416,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,   175,  -789,  -789,  -789,   417,  -789,  -789,
     418,  -789,   419,   420,  -789,  -789,   422,   423,   424,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,   184,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,   225,  -789,  -789,  -789,    33,
      33,  -789,   271,   433,   434,   435,   436,   437,  -789,    19,
    -789,   438,   439,   440,   443,   285,   286,   287,   288,   289,
     450,   451,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   479,   480,   321,   482,   484,    41,  -789,   485,   341,
      37,  -789,   504,   508,   509,   510,   511,   353,   350,   515,
     517,   518,   519,   520,   220,  -789,   521,   188,  -789,   522,
     364,   523,   365,   368,    63,  -789,   527,   529,   530,   531,
     532,   536,   538,  -789,    75,  -789,   539,   540,   381,   542,
     543,   544,   383,  -789,    43,   546,   385,   386,  -789,   268,
     549,   550,    47,  -789,   389,   552,   553,   396,   555,   397,
     399,   560,   561,   400,   401,   402,   565,   566,   567,   568,
     355,  -789,   569,    99,  -789,  -789,  -789,   570,   571,   572,
      33,    33,    33,  -789,   573,   574,   575,   578,  -789,  -789,
    -789,  -789,  -789,   579,   580,   581,   582,   425,   585,   586,
     587,   588,   589,   590,   591,   592,  -789,   593,   594,  -789,
     597,  -789,  -789,   598,   599,   442,   444,   445,  -789,  -789,
     307,   597,   446,   601,   603,  -789,   448,  -789,   449,  -789,
     452,  -789,  -789,  -789,   597,   597,   597,   462,   463,   464,
     465,  -789,   466,   467,  -789,   468,   469,   470,  -789,  -789,
     471,  -789,  -789,  -789,   472,    33,  -789,  -789,   473,   474,
    -789,   475,  -789,  -789,    56,   483,  -789,  -789,  -789,    39,
     476,   477,   478,  -789,   609,  -789,    33,    41,    99,  -789,
    -789,  -789,    37,   185,   185,   610,   611,   612,   613,  -789,
    -789,  -789,   614,   -32,    33,   309,   615,   616,   197,   117,
       1,   355,  -789,  -789,   617,   635,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,   636,    18,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,   637,  -789,   236,   244,   245,  -789,  -789,  -789,  -789,
     583,   641,   642,   643,   644,  -789,   645,   646,  -789,   647,
     648,   649,  -789,   253,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,   259,  -789,   650,   651,  -789,  -789,   652,   654,
    -789,  -789,   653,   657,  -789,  -789,   655,   659,  -789,  -789,
     658,   660,  -789,  -789,  -789,    48,  -789,  -789,  -789,   661,
    -789,  -789,  -789,    59,  -789,  -789,  -789,  -789,    70,  -789,
    -789,   662,   663,  -789,   665,   666,   667,   668,   669,   670,
     260,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
     671,   672,   673,  -789,  -789,  -789,  -789,   262,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,   269,
    -789,  -789,  -789,   296,   492,  -789,   674,   675,  -789,  -789,
     676,   678,  -789,  -789,   677,   681,  -789,  -789,  -789,   608,
    -789,  -789,   124,  -789,  -789,  -789,  -789,   682,   683,   684,
     685,   432,   431,   501,   513,   526,   687,   528,   533,   689,
     534,   535,   537,   185,  -789,  -789,   185,  -789,   610,   220,
    -789,   611,    43,  -789,   612,   268,  -789,   613,   367,  -789,
     614,   -32,  -789,  -789,   309,  -789,    66,   615,  -789,    -6,
    -789,   616,   541,   545,   547,   548,   551,   554,   197,  -789,
     690,   691,   556,   557,   558,   117,  -789,   692,   696,     1,
    -789,  -789,  -789,   679,   698,   188,  -789,   617,    63,  -789,
     635,    75,  -789,   636,   700,  -789,   228,   637,  -789,   395,
     562,   563,   564,  -789,  -789,  -789,  -789,  -789,   595,  -789,
    -789,   596,  -789,  -789,  -789,  -789,   297,  -789,   300,  -789,
     694,  -789,   699,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,   304,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,   702,  -789,  -789,
    -789,  -789,  -789,   705,   707,  -789,  -789,  -789,  -789,  -789,
     317,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,   299,
     604,  -789,  -789,  -789,  -789,   605,   619,  -789,  -789,   620,
     318,  -789,   320,  -789,   706,  -789,   621,  -789,   704,  -789,
    -789,  -789,  -789,  -789,   329,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,   367,  -789,   712,   577,  -789,    66,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,   713,   559,   715,   228,  -789,  -789,   622,
    -789,  -789,   719,  -789,   625,  -789,  -789,   721,  -789,  -789,
     130,  -789,    91,   721,  -789,  -789,   726,   727,   730,   333,
    -789,  -789,  -789,  -789,  -789,  -789,   733,   606,   584,   600,
      91,  -789,   626,  -789,  -789,  -789,  -789,  -789
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
     356,    23,   206,    25,   538,    27,   601,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   443,     0,   321,   358,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     599,   593,   595,   597,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   105,   119,   121,   123,     0,     0,     0,
       0,     0,   233,   309,   348,   399,   401,   282,   179,   196,
     187,   478,   198,   217,   499,     0,   523,   536,    99,     0,
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
     213,   215,   210,     0,   208,   211,   212,     0,   562,   564,
       0,   567,     0,     0,   571,   575,     0,     0,     0,   580,
     587,   589,   591,   560,   558,   559,     0,   540,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   606,     0,   603,   605,    46,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,     0,     0,
       0,   108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   242,     0,     0,   387,     0,
       0,     0,     0,     0,     0,   412,     0,     0,     0,     0,
       0,     0,     0,   442,     0,   312,     0,     0,     0,     0,
       0,     0,     0,   320,     0,     0,     0,     0,   357,     0,
       0,     0,     0,   207,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   539,     0,     0,   602,    50,    43,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,     0,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   522,     0,     0,    73,
       0,   118,   110,     0,     0,     0,     0,     0,   280,   281,
       0,     0,     0,     0,     0,   244,     0,   389,     0,   428,
       0,   431,   432,   414,     0,     0,     0,     0,     0,     0,
       0,   446,     0,     0,   336,     0,     0,     0,   347,   324,
       0,   376,   377,   361,     0,     0,   209,   561,     0,     0,
     566,     0,   569,   570,     0,     0,   577,   578,   579,     0,
       0,     0,     0,   541,     0,   604,     0,     0,     0,   594,
     596,   598,     0,     0,     0,   125,   235,   313,   350,    40,
     400,   402,   284,     0,    47,     0,     0,   200,     0,     0,
       0,     0,    51,   117,   380,   405,   266,   268,   270,   277,
     278,   279,   276,   274,   272,   435,     0,   398,   427,   430,
     471,   459,   461,   463,   465,   467,   469,   339,   165,   343,
     341,   346,   373,   214,   216,   563,   565,   568,   573,   574,
     572,   576,   582,   583,   584,   585,   586,   581,   588,   590,
     592,     0,    44,     0,     0,     0,   151,   157,   159,   161,
       0,     0,     0,     0,     0,   174,     0,     0,   177,     0,
       0,     0,   150,     0,   131,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   145,   146,   147,   148,   143,
     144,   149,     0,   129,     0,   126,   127,   239,     0,   236,
     237,   317,     0,   314,   315,   354,     0,   351,   352,   288,
       0,   285,   286,   185,   186,     0,   181,   183,   184,     0,
     194,   195,   191,     0,   189,   192,   193,   482,     0,   480,
     204,     0,   201,   202,     0,     0,     0,     0,     0,     0,
       0,   219,   221,   222,   223,   224,   225,   226,   512,   518,
       0,     0,     0,   511,   508,   509,   510,     0,   501,   503,
     506,   504,   505,   507,   532,   534,   531,   529,   530,     0,
     525,   527,   528,     0,    53,   384,     0,   381,   382,   409,
       0,   406,   407,   439,     0,   436,   437,   476,   475,     0,
     474,   610,     0,   608,    69,   600,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,   122,     0,   124,     0,     0,
     234,     0,   321,   310,     0,   358,   349,     0,     0,   283,
       0,     0,   180,   197,     0,   188,   484,     0,   479,     0,
     199,     0,     0,     0,     0,     0,     0,     0,     0,   218,
       0,     0,     0,     0,     0,     0,   500,     0,     0,     0,
     524,   537,    55,     0,    54,     0,   379,     0,     0,   404,
       0,   443,   434,     0,     0,   473,     0,     0,   607,     0,
       0,     0,     0,   163,   166,   167,   168,   169,     0,   176,
     170,     0,   171,   172,   173,   132,     0,   128,     0,   238,
       0,   316,     0,   353,   308,   303,   305,   296,   297,   292,
     293,   294,   295,   301,   302,   300,   304,     0,   290,   298,
     306,   307,   299,   287,   182,   190,   496,     0,   494,   495,
     491,   492,   493,     0,   485,   486,   488,   489,   490,   481,
       0,   203,   227,   228,   229,   230,   231,   232,   220,     0,
       0,   517,   520,   521,   502,     0,     0,   526,    52,     0,
       0,   383,     0,   408,     0,   438,     0,   624,     0,   622,
     620,   614,   618,   619,     0,   612,   616,   617,   615,   609,
     153,   154,   155,   156,   152,   158,   160,   162,   175,   178,
     130,   240,   318,   355,     0,   289,     0,     0,   483,     0,
     205,   514,   515,   516,   513,   519,   533,   535,    56,   385,
     410,   440,   477,     0,     0,     0,     0,   611,   291,     0,
     498,   487,     0,   621,     0,   613,   497,     0,   623,   628,
       0,   626,     0,     0,   625,   636,     0,     0,     0,     0,
     630,   632,   633,   634,   635,   627,     0,     0,     0,     0,
       0,   629,     0,   638,   639,   640,   631,   637
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,     6,  -789,   265,  -789,
    -789,  -789,  -789,  -789,  -789,   177,  -789,  -274,  -789,  -789,
    -789,   -70,  -789,  -789,  -789,   406,  -789,  -789,  -789,  -789,
     205,   404,   -55,   -54,   -52,   -47,  -789,  -789,  -789,  -789,
    -789,   209,   393,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,   -22,  -789,  -547,    -2,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,   -66,  -789,
    -564,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,   -34,  -559,  -789,  -789,
    -789,  -789,   -20,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,   -25,  -789,  -789,  -789,   -17,   373,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,   -21,  -789,  -789,  -789,  -789,  -789,
    -789,  -788,  -789,  -789,  -789,     7,  -789,  -789,  -789,     0,
     421,  -789,  -789,  -785,  -789,  -784,  -789,   -16,  -789,    -8,
    -789,  -783,  -789,  -789,  -789,  -781,  -789,  -789,  -789,  -789,
       3,  -789,  -789,  -164,   734,  -789,  -789,  -789,  -789,  -789,
      13,  -789,  -789,  -789,    16,  -789,   403,  -789,   -72,  -789,
    -789,  -789,  -789,  -789,   -65,  -789,  -789,  -789,  -789,  -789,
     -29,  -789,  -789,  -789,    14,  -789,  -789,  -789,    15,  -789,
     405,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,   -24,  -789,  -789,  -789,   -19,   427,  -789,  -789,
     -42,  -789,    -4,  -789,  -789,  -789,  -789,  -789,   -14,  -789,
    -789,  -789,   -23,   426,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,   -15,  -789,  -789,  -789,   -18,
    -789,   414,   246,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -780,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,    22,  -789,  -789,  -789,  -136,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,    10,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,     9,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,   270,   407,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,  -789,
    -789,  -789,  -789,  -789,  -789,  -789,  -789,   291,   408,  -789,
    -789,  -789,   -11,  -789,  -789,  -146,  -789,  -789,  -789,  -789,
    -789,  -789,  -160,  -789,  -789,  -176,  -789,  -789,  -789,  -789,
    -789
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     570,    87,    88,    41,    68,    84,    85,   583,   754,   843,
     844,   652,    43,    70,    96,    97,    98,   343,    45,    71,
     129,   130,   131,   132,   133,   134,   135,   136,   351,    47,
      72,   159,   160,   161,   378,   162,   137,   352,   138,   353,
     139,   354,   674,   675,   676,   796,   653,   654,   655,   777,
     964,   656,   778,   657,   779,   658,   780,   659,   660,   417,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   786,
     670,   671,   789,   140,   366,   695,   696,   697,   698,   141,
     368,   703,   704,   705,   706,   142,   367,   143,   370,   711,
     712,   713,   819,    63,    80,   293,   294,   295,   430,   296,
     431,   144,   371,   720,   721,   722,   723,   724,   725,   726,
     727,   145,   360,   678,   679,   680,   799,    49,    73,   182,
     183,   184,   384,   185,   385,   186,   386,   187,   391,   188,
     390,   189,   389,   592,   190,   191,   146,   365,   690,   691,
     692,   808,   897,   898,   147,   361,    57,    77,   682,   683,
     684,   802,    59,    78,   258,   259,   260,   261,   262,   263,
     264,   416,   265,   420,   266,   419,   267,   268,   421,   269,
     148,   362,   686,   687,   688,   805,    61,    79,   279,   280,
     281,   282,   283,   425,   284,   285,   286,   287,   193,   382,
     756,   757,   758,   845,    51,    74,   204,   205,   206,   396,
     149,   363,   150,   364,   196,   383,   760,   761,   762,   848,
      53,    75,   220,   221,   222,   399,   223,   224,   401,   225,
     226,   197,   392,   764,   765,   766,   851,    55,    76,   238,
     239,   240,   241,   407,   242,   408,   243,   409,   244,   410,
     245,   411,   246,   412,   247,   406,   198,   393,   769,   770,
     854,   151,   369,   708,   709,   816,   913,   914,   915,   916,
     917,   976,   918,   152,   372,   737,   738,   739,   830,   984,
     740,   741,   831,   742,   743,   153,   154,   374,   749,   750,
     751,   837,   752,   838,   155,   375,    65,    81,   316,   317,
     318,   319,   435,   320,   436,   321,   322,   438,   323,   324,
     325,   441,   620,   326,   442,   327,   328,   329,   330,   446,
     627,   331,   447,   332,   448,   333,   449,    99,   345,   100,
     346,   101,   347,   102,   344,    67,    82,   335,   336,   337,
     452,   772,   773,   856,   954,   955,   956,   957,   995,   958,
     993,  1010,  1011,  1012,  1019,  1020,  1021,  1026,  1022,  1023,
    1024
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   128,   158,   177,   200,   214,   234,   277,   256,   275,
     292,   313,   257,   276,   278,   734,   702,   672,   178,   179,
     890,   180,    38,   891,   892,   895,   181,   896,   902,    89,
     163,   194,   207,   218,   236,    30,   270,   288,    31,   314,
      32,    42,    33,   349,   192,   203,   217,   235,   350,   156,
     157,   811,   103,   693,   812,   104,   105,   106,   201,   215,
     249,    44,   814,   115,   116,   815,   202,   216,   164,   195,
     208,   219,   237,   817,   271,   289,   818,   315,   107,   108,
     109,   110,   111,   112,   113,   114,   290,   291,   250,    46,
     251,   252,   376,   380,   253,   254,   255,   377,   381,   115,
     116,   228,    48,   115,   116,   115,   116,   114,   767,    50,
     114,   250,   744,   745,   117,   118,   119,   120,   121,   114,
     209,   210,   211,   212,   213,   115,   116,   857,   115,   116,
     858,   694,   122,  1013,   728,   123,  1014,   115,   116,   290,
     291,   173,   124,   641,   174,   906,   907,    52,   394,    54,
     125,   126,   227,   395,   127,    56,    90,    94,   228,   229,
     230,   231,   232,   233,    94,    91,    92,    93,    58,   397,
     622,   623,   624,   625,   398,    60,   404,    62,   432,   115,
     116,   405,    94,   433,   618,   619,   890,   450,    64,   891,
     892,   895,   451,   896,   902,    86,    34,    35,    36,    37,
      94,    66,   636,   113,    94,   626,    94,   637,   638,   639,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   649,
     650,   651,   729,   730,   731,   732,    94,   593,   453,    94,
     250,  1015,   114,   454,  1016,  1017,  1018,   334,    94,   376,
     600,   601,   602,   199,   774,   338,   339,   453,   380,   876,
     115,   116,   775,   776,   340,   702,   793,   107,   108,   109,
     110,   794,   793,   828,   114,   835,   173,   795,   829,   174,
     836,   734,   839,   250,   165,   341,   166,   840,   342,    95,
      94,   348,   115,   116,   167,   168,   169,   170,   171,   172,
     115,   116,   714,   715,   716,   717,   718,   719,   173,   450,
     793,   174,   175,   394,   841,   970,   128,   974,   971,   176,
     158,   413,   975,   250,   272,   251,   252,   273,   274,   355,
     432,   397,   414,   404,   177,   980,   989,   200,   990,   356,
     115,   116,   996,   424,   214,   357,  1030,   997,   163,   178,
     179,  1031,   180,   358,   234,   455,   456,   181,    94,   359,
     373,    94,   194,   379,   256,   207,   387,   277,   257,   275,
     388,   400,   218,   276,   278,   192,   402,   947,   203,   948,
     949,   415,   236,   403,   418,   217,   164,   589,   590,   591,
     313,   201,   270,    94,   422,   235,   423,   288,   215,   202,
     195,    94,   426,   208,   693,   700,   216,   701,   427,   428,
     219,   981,   982,   983,   107,   108,   109,   110,   314,   112,
     237,   114,   250,   960,   961,   962,   963,   115,   116,   429,
     271,   434,   437,   439,   440,   289,   443,   444,   445,   115,
     116,    94,   168,   169,   457,   171,   172,   458,   459,   460,
     461,   462,   464,   465,   466,   173,   315,   467,   174,   468,
     469,   470,   471,   472,   473,   474,   176,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   559,   560,   561,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   484,   485,   486,   487,   128,   488,   490,
     311,   312,   158,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   491,   493,   733,
     746,   313,   494,   495,   496,   497,   499,   498,    94,   500,
     163,   501,   502,   503,   504,   506,   508,   510,   509,   511,
      94,   514,   512,   515,   516,   517,   518,   735,   747,   314,
     519,   614,   520,   522,   523,   524,   525,   526,   527,   528,
     530,   531,   532,   534,   535,   537,   538,   539,   164,   541,
     540,   542,   632,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   554,   556,   736,   748,   315,   557,   558,
     562,   563,   564,   565,   566,   567,   568,   781,   571,    32,
     572,   573,   574,   575,   576,   577,   863,   864,   578,   579,
     580,   581,   582,   584,   585,   586,   595,   587,   588,   594,
     596,   597,   598,   621,   631,   599,   855,   673,   677,   681,
     685,   689,   707,   710,   755,   603,   604,   605,   606,   607,
     608,   609,   610,   611,   612,   613,   615,   616,   617,   628,
     629,   630,   759,   763,   771,   782,   783,   784,   785,   787,
     788,   790,   791,   792,   798,   842,   797,   801,   800,   803,
     804,   806,   807,   810,   809,   865,   821,   813,   820,   822,
     823,   824,   825,   826,   827,   832,   833,   834,   847,   866,
     846,   850,   849,   852,   853,   938,   859,   860,   861,   862,
     867,   868,   869,   871,   929,   930,   935,   870,   872,   873,
     936,   939,   972,   874,   946,   922,   977,   973,   994,   923,
     979,   924,   925,   978,   991,   926,   999,  1002,   927,  1004,
     931,   932,   933,  1003,  1007,   965,   966,   967,  1009,   177,
    1027,  1028,   256,   277,  1029,   275,   257,  1032,   884,   276,
     278,   569,   889,  1000,   178,   179,   908,   180,  1034,   292,
     909,   699,   181,   885,   886,   463,   887,   194,   968,   969,
     270,   888,   633,   288,  1035,   733,   900,   985,   986,   746,
     192,   635,  1033,   492,   911,   200,   877,   904,   214,   899,
     489,   234,   987,   988,   992,  1006,   950,   910,  1008,  1037,
     951,   875,   893,   735,   905,   195,   921,   747,   271,   878,
     894,   289,   920,   207,   901,   536,   218,   928,   879,   236,
     998,   248,   912,   903,   952,   505,   203,   881,   880,   217,
     882,   883,   235,   941,   507,   942,   940,   529,   521,   201,
     513,   736,   215,   944,   533,   748,   943,   202,   945,   919,
     216,   208,   768,  1001,   219,   934,   959,   237,   937,   634,
    1005,   753,   953,  1025,  1036,     0,     0,   553,     0,     0,
       0,   555,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   884,     0,     0,     0,   889,   908,
       0,     0,     0,   909,     0,     0,     0,     0,     0,   885,
     886,     0,   887,     0,     0,     0,   950,   888,     0,     0,
     951,     0,   900,     0,     0,     0,     0,   911,     0,     0,
       0,     0,     0,     0,     0,   899,     0,     0,     0,     0,
     910,     0,     0,     0,   952,     0,     0,     0,   893,     0,
       0,     0,     0,     0,     0,     0,   894,     0,     0,     0,
     901,     0,     0,     0,     0,   912,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   953
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    79,    78,    79,
      80,    81,    78,    79,    79,   579,   575,   564,    73,    73,
     808,    73,    16,   808,   808,   808,    73,   808,   808,    10,
      72,    73,    74,    75,    76,     0,    78,    79,     5,    81,
       7,     7,     9,     3,    73,    74,    75,    76,     8,    12,
      13,     3,    11,    85,     6,    14,    15,    16,    74,    75,
      17,     7,     3,    62,    63,     6,    74,    75,    72,    73,
      74,    75,    76,     3,    78,    79,     6,    81,    37,    38,
      39,    40,    41,    42,    43,    44,    92,    93,    45,     7,
      47,    48,     3,     3,    51,    52,    53,     8,     8,    62,
      63,    83,     7,    62,    63,    62,    63,    44,    90,     7,
      44,    45,   111,   112,    73,    74,    75,    76,    77,    44,
      57,    58,    59,    60,    61,    62,    63,     3,    62,    63,
       6,   163,    91,     3,    17,    94,     6,    62,    63,    92,
      93,    78,   101,    26,    81,    79,    80,     7,     3,     7,
     109,   110,    77,     8,   113,     7,   137,   163,    83,    84,
      85,    86,    87,    88,   163,   146,   147,   148,     7,     3,
     131,   132,   133,   134,     8,     7,     3,     7,     3,    62,
      63,     8,   163,     8,   128,   129,   974,     3,     7,   974,
     974,   974,     8,   974,   974,   163,   163,   164,   165,   166,
     163,     7,    17,    43,   163,   166,   163,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   105,   106,   107,   108,   163,   501,     3,   163,
      45,   140,    44,     8,   143,   144,   145,   138,   163,     3,
     514,   515,   516,    55,     8,     6,     3,     3,     3,   796,
      62,    63,     8,     8,     4,   814,     3,    37,    38,    39,
      40,     8,     3,     3,    44,     3,    78,     8,     8,    81,
       8,   835,     3,    45,    54,     8,    56,     8,     3,   349,
     163,     4,    62,    63,    64,    65,    66,    67,    68,    69,
      62,    63,    95,    96,    97,    98,    99,   100,    78,     3,
       3,    81,    82,     3,     8,     8,   376,     3,     8,    89,
     380,     8,     8,    45,    46,    47,    48,    49,    50,     4,
       3,     3,     3,     3,   394,     8,     8,   397,     8,     4,
      62,    63,     3,     3,   404,     4,     3,     8,   380,   394,
     394,     8,   394,     4,   414,   339,   340,   394,   163,     4,
       4,   163,   394,     4,   424,   397,     4,   429,   424,   429,
       4,     4,   404,   429,   429,   394,     4,   139,   397,   141,
     142,     8,   414,     4,     4,   404,   380,    70,    71,    72,
     450,   397,   424,   163,     4,   414,     8,   429,   404,   397,
     394,   163,     4,   397,    85,    86,   404,    88,     4,     8,
     404,   102,   103,   104,    37,    38,    39,    40,   450,    42,
     414,    44,    45,    18,    19,    20,    21,    62,    63,     3,
     424,     4,     4,     4,     4,   429,     4,     4,     4,    62,
      63,   163,    65,    66,   163,    68,    69,     4,     4,     4,
       4,     4,     4,     4,     4,    78,   450,     4,    81,   164,
     164,   164,   164,   164,     4,     4,    89,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   460,   461,   462,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     4,     4,   164,     4,   557,     4,     4,
     135,   136,   562,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   166,     4,   579,
     580,   581,     4,     4,     4,     4,   166,   164,   163,     4,
     562,     4,     4,     4,     4,     4,     4,     4,   164,   164,
     163,     4,   164,     4,     4,     4,     4,   579,   580,   581,
       4,   535,     4,     4,     4,   164,     4,     4,     4,   166,
       4,   166,   166,     4,     4,   166,     4,     4,   562,     4,
     164,   164,   556,   164,     4,     4,   166,   166,   166,     4,
       4,     4,     4,     4,     4,   579,   580,   581,     7,     7,
       7,     7,     7,     5,     5,     5,     5,     4,   163,     7,
       5,     5,     5,     5,     5,     5,   164,   166,     7,     7,
       7,     7,     5,     5,     5,   163,     5,   163,   163,   163,
       7,   163,   163,   130,     5,   163,     8,     7,     7,     7,
       7,     7,     7,     7,     7,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,     7,     7,     7,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   163,     6,     3,     6,     6,
       3,     6,     3,     3,     6,   164,     3,     6,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   166,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
     164,     4,   164,     4,     4,     4,     4,   164,   164,   164,
       4,     3,     8,   166,     4,   164,     4,     8,     4,   164,
       3,   164,   164,     8,     8,   164,     4,     4,   164,     4,
     164,   164,   164,   164,     5,   163,   163,   163,     7,   799,
       4,     4,   802,   805,     4,   805,   802,     4,   808,   805,
     805,   476,   808,   166,   799,   799,   816,   799,   164,   819,
     816,   574,   799,   808,   808,   349,   808,   799,   163,   163,
     802,   808,   557,   805,   164,   835,   808,   163,   163,   839,
     799,   562,   166,   380,   816,   845,   798,   811,   848,   808,
     376,   851,   163,   163,   163,   163,   856,   816,   163,   163,
     856,   793,   808,   835,   814,   799,   821,   839,   802,   799,
     808,   805,   819,   845,   808,   432,   848,   828,   801,   851,
     974,    77,   816,   810,   856,   394,   845,   804,   802,   848,
     805,   807,   851,   847,   397,   848,   845,   424,   414,   845,
     404,   835,   848,   851,   429,   839,   850,   845,   853,   817,
     848,   845,   596,   979,   848,   835,   857,   851,   839,   558,
     996,   581,   856,  1013,  1030,    -1,    -1,   450,    -1,    -1,
      -1,   453,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   974,    -1,    -1,    -1,   974,   979,
      -1,    -1,    -1,   979,    -1,    -1,    -1,    -1,    -1,   974,
     974,    -1,   974,    -1,    -1,    -1,   996,   974,    -1,    -1,
     996,    -1,   974,    -1,    -1,    -1,    -1,   979,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   974,    -1,    -1,    -1,    -1,
     979,    -1,    -1,    -1,   996,    -1,    -1,    -1,   974,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   974,    -1,    -1,    -1,
     974,    -1,    -1,    -1,    -1,   979,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   996
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
       0,     5,     7,     9,   163,   164,   165,   166,   183,   184,
     185,   190,     7,   199,     7,   205,     7,   216,     7,   304,
       7,   381,     7,   397,     7,   414,     7,   333,     7,   339,
       7,   363,     7,   280,     7,   473,     7,   512,   191,   186,
     200,   206,   217,   305,   382,   398,   415,   334,   340,   364,
     281,   474,   513,   183,   192,   193,   163,   188,   189,    10,
     137,   146,   147,   148,   163,   198,   201,   202,   203,   504,
     506,   508,   510,    11,    14,    15,    16,    37,    38,    39,
      40,    41,    42,    43,    44,    62,    63,    73,    74,    75,
      76,    77,    91,    94,   101,   109,   110,   113,   198,   207,
     208,   209,   210,   211,   212,   213,   214,   223,   225,   227,
     260,   266,   272,   274,   288,   298,   323,   331,   357,   387,
     389,   438,   450,   462,   463,   471,    12,    13,   198,   218,
     219,   220,   222,   387,   389,    54,    56,    64,    65,    66,
      67,    68,    69,    78,    81,    82,    89,   198,   209,   210,
     211,   212,   306,   307,   308,   310,   312,   314,   316,   318,
     321,   322,   357,   375,   387,   389,   391,   408,   433,    55,
     198,   314,   316,   357,   383,   384,   385,   387,   389,    57,
      58,    59,    60,    61,   198,   314,   316,   357,   387,   389,
     399,   400,   401,   403,   404,   406,   407,    77,    83,    84,
      85,    86,    87,    88,   198,   357,   387,   389,   416,   417,
     418,   419,   421,   423,   425,   427,   429,   431,   331,    17,
      45,    47,    48,    51,    52,    53,   198,   245,   341,   342,
     343,   344,   345,   346,   347,   349,   351,   353,   354,   356,
     387,   389,    46,    49,    50,   198,   245,   345,   351,   365,
     366,   367,   368,   369,   371,   372,   373,   374,   387,   389,
      92,    93,   198,   282,   283,   284,   286,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   135,   136,   198,   387,   389,   475,   476,   477,   478,
     480,   482,   483,   485,   486,   487,   490,   492,   493,   494,
     495,   498,   500,   502,   138,   514,   515,   516,     6,     3,
       4,     8,     3,   204,   511,   505,   507,   509,     4,     3,
       8,   215,   224,   226,   228,     4,     4,     4,     4,     4,
     299,   332,   358,   388,   390,   324,   261,   273,   267,   439,
     275,   289,   451,     4,   464,   472,     3,     8,   221,     4,
       3,     8,   376,   392,   309,   311,   313,     4,     4,   319,
     317,   315,   409,   434,     3,     8,   386,     3,     8,   402,
       4,   405,     4,     4,     3,     8,   432,   420,   422,   424,
     426,   428,   430,     8,     3,     8,   348,   246,     4,   352,
     350,   355,     4,     8,     3,   370,     4,     4,     8,     3,
     285,   287,     3,     8,     4,   479,   481,     4,   484,     4,
       4,   488,   491,     4,     4,     4,   496,   499,   501,   503,
       3,     8,   517,     3,     8,   183,   183,   163,     4,     4,
       4,     4,     4,   202,     4,     4,     4,     4,   164,   164,
     164,   164,   164,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   164,     4,     4,   208,
       4,   166,   219,     4,     4,     4,     4,     4,   164,   166,
       4,     4,     4,     4,     4,   307,     4,   384,     4,   164,
       4,   164,   164,   400,     4,     4,     4,     4,     4,     4,
       4,   418,     4,     4,   164,     4,     4,     4,   166,   343,
       4,   166,   166,   367,     4,     4,   283,   166,     4,     4,
     164,     4,   164,   164,     4,     4,   166,   166,   166,     4,
       4,     4,     4,   476,     4,   515,     4,     7,     7,   183,
     183,   183,     7,     7,     7,     5,     5,     5,     5,   185,
     187,   163,     5,     5,     5,     5,     5,     5,     7,     7,
       7,     7,     5,   194,     5,     5,   163,   163,   163,    70,
      71,    72,   320,   194,   163,     5,     7,   163,   163,   163,
     194,   194,   194,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   183,   163,   163,   163,   128,   129,
     489,   130,   131,   132,   133,   134,   166,   497,   163,   163,
     163,     5,   183,   207,   514,   218,    17,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   198,   233,   234,   235,   238,   240,   242,   244,
     245,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     257,   258,   233,     7,   229,   230,   231,     7,   300,   301,
     302,     7,   335,   336,   337,     7,   359,   360,   361,     7,
     325,   326,   327,    85,   163,   262,   263,   264,   265,   192,
      86,    88,   264,   268,   269,   270,   271,     7,   440,   441,
       7,   276,   277,   278,    95,    96,    97,    98,    99,   100,
     290,   291,   292,   293,   294,   295,   296,   297,    17,   105,
     106,   107,   108,   198,   247,   387,   389,   452,   453,   454,
     457,   458,   460,   461,   111,   112,   198,   387,   389,   465,
     466,   467,   469,   475,   195,     7,   377,   378,   379,     7,
     393,   394,   395,     7,   410,   411,   412,    90,   419,   435,
     436,     7,   518,   519,     8,     8,     8,   236,   239,   241,
     243,     4,     4,     4,     4,     4,   256,     4,     4,   259,
       4,     4,     4,     3,     8,     8,   232,     6,     3,   303,
       6,     3,   338,     6,     3,   362,     6,     3,   328,     6,
       3,     3,     6,     6,     3,     6,   442,     3,     6,   279,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     455,   459,     4,     4,     4,     3,     8,   468,   470,     3,
       8,     8,   163,   196,   197,   380,     6,     3,   396,     6,
       3,   413,     6,     3,   437,     8,   520,     3,     6,     4,
       4,     4,     4,   164,   166,   164,   166,   164,     4,   164,
     164,     4,   164,   164,   166,   234,   233,   231,   306,   302,
     341,   337,   365,   361,   198,   209,   210,   211,   212,   245,
     298,   310,   312,   314,   316,   318,   322,   329,   330,   357,
     387,   389,   433,   327,   263,   269,    79,    80,   198,   245,
     357,   387,   389,   443,   444,   445,   446,   447,   449,   441,
     282,   278,   164,   164,   164,   164,   164,   164,   291,     4,
       4,   164,   164,   164,   453,     4,     4,   466,     6,     3,
     383,   379,   399,   395,   416,   412,     4,   139,   141,   142,
     198,   245,   387,   389,   521,   522,   523,   524,   526,   519,
      18,    19,    20,    21,   237,   163,   163,   163,   163,   163,
       8,     8,     8,     8,     3,     8,   448,     4,     8,     3,
       8,   102,   103,   104,   456,   163,   163,   163,   163,     8,
       8,     8,   163,   527,     4,   525,     3,     8,   330,     4,
     166,   445,     4,   164,     4,   522,   163,     5,   163,     7,
     528,   529,   530,     3,     6,   140,   143,   144,   145,   531,
     532,   533,   535,   536,   537,   529,   534,     4,     4,     4,
       3,     8,     4,   166,   164,   164,   532,   163
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   167,   169,   168,   170,   168,   171,   168,   172,   168,
     173,   168,   174,   168,   175,   168,   176,   168,   177,   168,
     178,   168,   179,   168,   180,   168,   181,   168,   182,   168,
     183,   183,   183,   183,   183,   183,   183,   184,   186,   185,
     187,   188,   188,   189,   189,   191,   190,   192,   192,   193,
     193,   195,   194,   196,   196,   197,   197,   198,   200,   199,
     201,   201,   202,   202,   202,   202,   202,   202,   204,   203,
     206,   205,   207,   207,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     209,   210,   211,   212,   213,   215,   214,   217,   216,   218,
     218,   219,   219,   219,   219,   219,   221,   220,   222,   224,
     223,   226,   225,   228,   227,   229,   229,   230,   230,   232,
     231,   233,   233,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   236,   235,   237,   237,   237,   237,   239,   238,   241,
     240,   243,   242,   244,   246,   245,   247,   248,   249,   250,
     251,   252,   253,   254,   256,   255,   257,   259,   258,   261,
     260,   262,   262,   263,   263,   264,   265,   267,   266,   268,
     268,   269,   269,   269,   270,   271,   273,   272,   275,   274,
     276,   276,   277,   277,   279,   278,   281,   280,   282,   282,
     282,   283,   283,   285,   284,   287,   286,   289,   288,   290,
     290,   291,   291,   291,   291,   291,   291,   292,   293,   294,
     295,   296,   297,   299,   298,   300,   300,   301,   301,   303,
     302,   305,   304,   306,   306,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   309,   308,   311,   310,   313,
     312,   315,   314,   317,   316,   319,   318,   320,   320,   320,
     321,   322,   324,   323,   325,   325,   326,   326,   328,   327,
     329,   329,   330,   330,   330,   330,   330,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   330,   330,   332,
     331,   334,   333,   335,   335,   336,   336,   338,   337,   340,
     339,   341,   341,   342,   342,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   344,   345,   346,   348,   347,
     350,   349,   352,   351,   353,   355,   354,   356,   358,   357,
     359,   359,   360,   360,   362,   361,   364,   363,   365,   365,
     366,   366,   367,   367,   367,   367,   367,   367,   367,   367,
     367,   368,   370,   369,   371,   372,   373,   374,   376,   375,
     377,   377,   378,   378,   380,   379,   382,   381,   383,   383,
     384,   384,   384,   384,   384,   384,   384,   386,   385,   388,
     387,   390,   389,   392,   391,   393,   393,   394,   394,   396,
     395,   398,   397,   399,   399,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   402,   401,   403,   405,
     404,   406,   407,   409,   408,   410,   410,   411,   411,   413,
     412,   415,   414,   416,   416,   417,   417,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   420,   419,
     422,   421,   424,   423,   426,   425,   428,   427,   430,   429,
     432,   431,   434,   433,   435,   435,   437,   436,   439,   438,
     440,   440,   442,   441,   443,   443,   444,   444,   445,   445,
     445,   445,   445,   445,   445,   446,   448,   447,   449,   451,
     450,   452,   452,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   455,   454,   456,   456,   456,   457,   459,   458,
     460,   461,   462,   464,   463,   465,   465,   466,   466,   466,
     466,   466,   468,   467,   470,   469,   472,   471,   474,   473,
     475,   475,   476,   476,   476,   476,   476,   476,   476,   476,
     476,   476,   476,   476,   476,   476,   476,   476,   476,   476,
     476,   477,   479,   478,   481,   480,   482,   484,   483,   485,
     486,   488,   487,   489,   489,   491,   490,   492,   493,   494,
     496,   495,   497,   497,   497,   497,   497,   499,   498,   501,
     500,   503,   502,   505,   504,   507,   506,   509,   508,   511,
     510,   513,   512,   514,   514,   515,   517,   516,   518,   518,
     520,   519,   521,   521,   522,   522,   522,   522,   522,   522,
     522,   523,   525,   524,   527,   526,   528,   528,   530,   529,
     531,   531,   532,   532,   532,   532,   534,   533,   535,   536,
     537
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
  "generated_prefix", "$@107", "hostname_char_set", "$@108",
  "hostname_char_replacement", "$@109", "dhcp4_json_object", "$@110",
  "dhcpddns_json_object", "$@111", "control_agent_json_object", "$@112",
  "logging_object", "$@113", "sub_logging", "$@114", "logging_params",
  "logging_param", "loggers", "$@115", "loggers_entries", "logger_entry",
  "$@116", "logger_params", "logger_param", "debuglevel", "severity",
  "$@117", "output_options_list", "$@118", "output_options_list_content",
  "output_entry", "$@119", "output_params_list", "output_params", "output",
  "$@120", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   248,   248,   248,   249,   249,   250,   250,   251,   251,
     252,   252,   253,   253,   254,   254,   255,   255,   256,   256,
     257,   257,   258,   258,   259,   259,   260,   260,   261,   261,
     269,   270,   271,   272,   273,   274,   275,   278,   283,   283,
     294,   297,   298,   301,   305,   312,   312,   319,   320,   323,
     327,   334,   334,   341,   342,   345,   349,   360,   370,   370,
     385,   386,   390,   391,   392,   393,   394,   395,   398,   398,
     413,   413,   422,   423,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     456,   461,   466,   471,   476,   481,   481,   492,   492,   501,
     502,   505,   506,   507,   508,   509,   512,   512,   522,   528,
     528,   540,   540,   552,   552,   562,   563,   566,   567,   570,
     570,   580,   581,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   604,   604,   611,   612,   613,   614,   617,   617,   625,
     625,   633,   633,   641,   646,   646,   654,   659,   664,   669,
     674,   679,   684,   689,   694,   694,   702,   707,   707,   716,
     716,   726,   727,   730,   731,   734,   739,   744,   744,   754,
     755,   758,   759,   760,   763,   768,   775,   775,   785,   785,
     795,   796,   799,   800,   803,   803,   813,   813,   823,   824,
     825,   828,   829,   832,   832,   840,   840,   848,   848,   859,
     860,   863,   864,   865,   866,   867,   868,   871,   876,   881,
     886,   891,   896,   904,   904,   917,   918,   921,   922,   929,
     929,   955,   955,   966,   967,   971,   972,   973,   974,   975,
     976,   977,   978,   979,   980,   981,   982,   983,   984,   985,
     986,   987,   988,   989,   990,   993,   993,  1001,  1001,  1009,
    1009,  1017,  1017,  1025,  1025,  1035,  1035,  1042,  1043,  1044,
    1047,  1052,  1060,  1060,  1071,  1072,  1076,  1077,  1080,  1080,
    1088,  1089,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,
    1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,  1108,  1115,
    1115,  1128,  1128,  1137,  1138,  1141,  1142,  1147,  1147,  1162,
    1162,  1176,  1177,  1180,  1181,  1184,  1185,  1186,  1187,  1188,
    1189,  1190,  1191,  1192,  1193,  1196,  1198,  1203,  1205,  1205,
    1213,  1213,  1221,  1221,  1229,  1231,  1231,  1239,  1248,  1248,
    1260,  1261,  1266,  1267,  1272,  1272,  1284,  1284,  1296,  1297,
    1302,  1303,  1308,  1309,  1310,  1311,  1312,  1313,  1314,  1315,
    1316,  1319,  1321,  1321,  1329,  1331,  1333,  1338,  1346,  1346,
    1358,  1359,  1362,  1363,  1366,  1366,  1376,  1376,  1385,  1386,
    1389,  1390,  1391,  1392,  1393,  1394,  1395,  1398,  1398,  1406,
    1406,  1431,  1431,  1461,  1461,  1473,  1474,  1477,  1478,  1481,
    1481,  1493,  1493,  1505,  1506,  1509,  1510,  1511,  1512,  1513,
    1514,  1515,  1516,  1517,  1518,  1519,  1522,  1522,  1530,  1535,
    1535,  1543,  1548,  1556,  1556,  1566,  1567,  1570,  1571,  1574,
    1574,  1583,  1583,  1592,  1593,  1596,  1597,  1601,  1602,  1603,
    1604,  1605,  1606,  1607,  1608,  1609,  1610,  1611,  1614,  1614,
    1624,  1624,  1634,  1634,  1642,  1642,  1650,  1650,  1658,  1658,
    1666,  1666,  1679,  1679,  1689,  1690,  1693,  1693,  1704,  1704,
    1714,  1715,  1718,  1718,  1728,  1729,  1732,  1733,  1736,  1737,
    1738,  1739,  1740,  1741,  1742,  1745,  1747,  1747,  1755,  1763,
    1763,  1775,  1776,  1779,  1780,  1781,  1782,  1783,  1784,  1785,
    1786,  1787,  1790,  1790,  1797,  1798,  1799,  1802,  1807,  1807,
    1815,  1820,  1827,  1834,  1834,  1844,  1845,  1848,  1849,  1850,
    1851,  1852,  1855,  1855,  1863,  1863,  1873,  1873,  1885,  1885,
    1895,  1896,  1899,  1900,  1901,  1902,  1903,  1904,  1905,  1906,
    1907,  1908,  1909,  1910,  1911,  1912,  1913,  1914,  1915,  1916,
    1917,  1920,  1925,  1925,  1933,  1933,  1941,  1946,  1946,  1954,
    1959,  1964,  1964,  1972,  1973,  1976,  1976,  1984,  1989,  1994,
    1999,  1999,  2007,  2010,  2013,  2016,  2019,  2025,  2025,  2033,
    2033,  2041,  2041,  2051,  2051,  2058,  2058,  2065,  2065,  2078,
    2078,  2088,  2088,  2099,  2100,  2104,  2108,  2108,  2120,  2121,
    2125,  2125,  2133,  2134,  2137,  2138,  2139,  2140,  2141,  2142,
    2143,  2146,  2151,  2151,  2159,  2159,  2169,  2170,  2173,  2173,
    2181,  2182,  2185,  2186,  2187,  2188,  2191,  2191,  2199,  2204,
    2209
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
#line 4796 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2214 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
