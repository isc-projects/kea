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
      case 434: // duid_type
      case 467: // ncr_protocol_value
      case 475: // replace_client_name_value
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
      case 434: // duid_type
      case 467: // ncr_protocol_value
      case 475: // replace_client_name_value
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

      case 434: // duid_type

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 467: // ncr_protocol_value

#line 231 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 475: // replace_client_name_value

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
      case 434: // duid_type
      case 467: // ncr_protocol_value
      case 475: // replace_client_name_value
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

  case 376:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1339 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 380:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 382:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2302 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2507 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2599 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2749 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1890 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1933 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3126 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1936 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1944 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 2009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 2026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 2030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2052 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -768;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     304,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,    60,    28,    62,    80,    84,
     119,   129,   153,   159,   168,   172,   181,   183,   185,   187,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,    28,     3,
      32,   162,    34,    38,    97,    -2,   182,   164,   165,   248,
     -28,   319,    95,  -768,   230,   268,   283,   280,   296,  -768,
    -768,  -768,  -768,  -768,   301,  -768,   103,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,   323,   327,   348,   350,
     360,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,   361,  -768,  -768,  -768,   131,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,   368,  -768,   151,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,   369,
     371,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
     161,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,   207,
    -768,  -768,  -768,  -768,  -768,   378,  -768,   385,   389,  -768,
    -768,  -768,  -768,   208,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,   322,   383,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,   386,  -768,  -768,   392,  -768,  -768,  -768,   393,  -768,
    -768,   390,   396,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,   400,   401,  -768,  -768,
    -768,  -768,   399,   397,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,   236,  -768,  -768,  -768,
     404,  -768,  -768,   406,  -768,   407,   415,  -768,  -768,   416,
     417,   418,  -768,  -768,  -768,  -768,  -768,   240,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,   243,  -768,  -768,  -768,    28,    28,
    -768,   269,   419,   422,   437,   455,   456,  -768,    32,  -768,
     457,   458,   459,   309,   311,   312,   313,   314,   460,   462,
     467,   468,   469,   471,   472,   473,   474,   475,   476,   477,
     478,   328,   479,   484,   162,  -768,   485,   334,    34,  -768,
      36,   489,   490,   491,   492,   493,   343,   340,   496,   500,
     501,   503,    38,  -768,   505,    97,  -768,   506,   357,   507,
     358,   362,    -2,  -768,   511,   512,   513,   515,   516,   517,
     521,  -768,   182,  -768,   523,   524,   374,   527,   528,   529,
     377,  -768,   165,   530,   379,   381,  -768,   248,   532,   534,
      -7,  -768,   384,   536,   537,   387,   542,   391,   394,   544,
     545,   395,   398,   405,   547,   548,   319,  -768,   550,    95,
    -768,  -768,  -768,   551,   552,   557,    28,    28,    28,  -768,
     558,   559,   561,  -768,  -768,  -768,  -768,  -768,   553,   564,
     565,   566,   402,   567,   569,   570,   571,   572,   573,   574,
     575,  -768,   576,   577,  -768,   580,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,   563,   583,  -768,  -768,  -768,   582,
     584,   424,   425,   435,  -768,  -768,   -27,   436,   587,   586,
    -768,   439,  -768,   440,  -768,   441,  -768,  -768,  -768,   580,
     580,   580,   442,   443,   444,   445,  -768,   446,   447,  -768,
     448,   449,   450,  -768,  -768,   451,  -768,  -768,  -768,   452,
      28,  -768,  -768,   453,   454,  -768,   461,  -768,  -768,     2,
     486,  -768,  -768,  -768,     5,   463,  -768,   606,  -768,    28,
     162,    95,  -768,  -768,  -768,    34,   254,   254,   605,   607,
     608,  -768,  -768,  -768,   610,   -36,    28,    25,    37,   612,
     324,    50,    23,   319,  -768,  -768,   609,  -768,    36,   613,
     614,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,   615,
     539,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,   617,  -768,   246,   250,   264,  -768,  -768,
    -768,  -768,   621,   622,   623,   624,   625,  -768,   626,   627,
    -768,  -768,   293,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,   294,  -768,
     628,   629,  -768,  -768,   630,   632,  -768,  -768,   631,   635,
    -768,  -768,   633,   637,  -768,  -768,  -768,   132,  -768,  -768,
    -768,   636,  -768,  -768,  -768,   139,  -768,  -768,  -768,  -768,
     201,  -768,   638,   640,  -768,   641,   642,   643,   644,   645,
     646,   300,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,   647,   648,   649,  -768,  -768,  -768,  -768,   306,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
     308,  -768,  -768,  -768,   310,   499,   502,  -768,  -768,   650,
     652,  -768,  -768,   653,   655,  -768,  -768,   654,   658,  -768,
    -768,   656,  -768,   338,  -768,  -768,  -768,  -768,   659,   661,
     662,   663,   514,   483,   518,   504,   519,   664,   520,   522,
     665,   254,  -768,  -768,    38,  -768,   605,   165,  -768,   607,
     248,  -768,   608,    82,  -768,   610,   -36,  -768,  -768,    25,
    -768,    37,  -768,   -28,  -768,   612,   525,   526,   531,   533,
     535,   538,   324,  -768,   667,   668,   540,   541,   543,    50,
    -768,   669,   673,    23,  -768,  -768,  -768,   674,   676,  -768,
      97,  -768,   613,    -2,  -768,   614,   182,  -768,   615,   679,
    -768,   215,   617,  -768,   209,   554,   578,   581,  -768,  -768,
    -768,  -768,  -768,   585,  -768,  -768,   589,  -768,   326,  -768,
     677,  -768,   678,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,   342,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,   352,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,   121,   590,  -768,  -768,  -768,
    -768,   591,   592,  -768,  -768,   593,   359,  -768,   376,  -768,
     680,  -768,   594,  -768,   686,  -768,  -768,  -768,  -768,  -768,
     380,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,    82,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,   688,   556,   689,   215,  -768,  -768,
     690,  -768,   596,  -768,   691,  -768,  -768,   355,  -768,   203,
     691,  -768,  -768,   696,   699,   702,   382,  -768,  -768,  -768,
    -768,  -768,  -768,   704,   568,   560,   579,   203,  -768,   597,
    -768,  -768,  -768,  -768,  -768
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   106,     9,   226,    11,
     367,    13,   390,    15,   418,    17,   292,    19,   300,    21,
     337,    23,   191,    25,   511,    27,   568,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   420,     0,   302,   339,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     566,   560,   562,   564,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   104,   118,   120,     0,     0,     0,     0,
       0,   218,   290,   329,   378,   380,   264,   164,   181,   172,
     453,   183,   202,   472,     0,   496,   509,    98,     0,    72,
      74,    75,    76,    77,    78,    81,    82,    83,    84,    86,
      85,    90,    91,    79,    80,    88,    89,    96,    97,    87,
      92,    93,    94,    95,   115,     0,   114,     0,   108,   110,
     111,   112,   113,   457,   359,   382,   249,   251,   253,     0,
       0,   257,   255,   410,   449,   248,   230,   231,   232,   233,
       0,   228,   237,   238,   239,   242,   244,   240,   241,   234,
     235,   246,   247,   236,   243,   245,   376,   375,   372,     0,
     369,   371,   373,   374,   403,     0,   406,     0,     0,   402,
     397,   400,   401,     0,   392,   394,   395,   398,   399,   396,
     447,   435,   437,   439,   441,   443,   445,   434,   431,   432,
     433,     0,   421,   422,   426,   427,   424,   428,   429,   430,
     425,     0,   319,   152,     0,   323,   321,   326,     0,   315,
     316,     0,   303,   304,   306,   318,   307,   308,   309,   325,
     310,   311,   312,   313,   314,   353,     0,     0,   351,   352,
     355,   356,     0,   340,   341,   343,   344,   345,   346,   347,
     348,   349,   350,   198,   200,   195,     0,   193,   196,   197,
       0,   533,   535,     0,   538,     0,     0,   542,   546,     0,
       0,     0,   551,   558,   531,   529,   530,     0,   513,   515,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   573,     0,   570,   572,    46,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    57,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,     0,   107,
     459,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   227,     0,     0,   368,     0,     0,     0,
       0,     0,     0,   391,     0,     0,     0,     0,     0,     0,
       0,   419,     0,   293,     0,     0,     0,     0,     0,     0,
       0,   301,     0,     0,     0,     0,   338,     0,     0,     0,
       0,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   512,     0,     0,
     569,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   495,     0,     0,    73,     0,   117,   109,   470,   468,
     469,   465,   466,   467,     0,   460,   461,   463,   464,     0,
       0,     0,     0,     0,   262,   263,     0,     0,     0,     0,
     229,     0,   370,     0,   405,     0,   408,   409,   393,     0,
       0,     0,     0,     0,     0,     0,   423,     0,     0,   317,
       0,     0,     0,   328,   305,     0,   357,   358,   342,     0,
       0,   194,   532,     0,     0,   537,     0,   540,   541,     0,
       0,   548,   549,   550,     0,     0,   514,     0,   571,     0,
       0,     0,   561,   563,   565,     0,     0,     0,   220,   294,
     331,    40,   379,   381,   266,     0,    47,     0,     0,   185,
       0,     0,     0,     0,    51,   116,     0,   458,     0,   361,
     384,   250,   252,   254,   259,   260,   261,   258,   256,   412,
       0,   377,   404,   407,   448,   436,   438,   440,   442,   444,
     446,   320,   153,   324,   322,   327,   354,   199,   201,   534,
     536,   539,   544,   545,   543,   547,   553,   554,   555,   556,
     557,   552,   559,     0,    44,     0,     0,     0,   139,   145,
     147,   149,     0,     0,     0,     0,     0,   158,     0,     0,
     162,   138,     0,   122,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,     0,   224,
       0,   221,   222,   298,     0,   295,   296,   335,     0,   332,
     333,   270,     0,   267,   268,   170,   171,     0,   166,   168,
     169,     0,   179,   180,   176,     0,   174,   177,   178,   455,
       0,   189,     0,   186,   187,     0,     0,     0,     0,     0,
       0,     0,   204,   206,   207,   208,   209,   210,   211,   485,
     491,     0,     0,     0,   484,   481,   482,   483,     0,   474,
     476,   479,   477,   478,   480,   505,   507,   504,   502,   503,
       0,   498,   500,   501,     0,    53,     0,   462,   365,     0,
     362,   363,   388,     0,   385,   386,   416,     0,   413,   414,
     451,     0,   577,     0,   575,    69,   567,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   119,   121,     0,   219,     0,   302,   291,     0,
     339,   330,     0,     0,   265,     0,     0,   165,   182,     0,
     173,     0,   454,     0,   184,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,     0,     0,     0,     0,     0,
     473,     0,     0,     0,   497,   510,    55,     0,    54,   471,
       0,   360,     0,     0,   383,     0,   420,   411,     0,     0,
     450,     0,     0,   574,     0,     0,     0,     0,   151,   154,
     155,   156,   157,     0,   160,   161,     0,   123,     0,   223,
       0,   297,     0,   334,   289,   284,   286,   278,   279,   274,
     275,   276,   277,   283,   282,   285,     0,   272,   280,   287,
     288,   281,   269,   167,   175,   456,     0,   188,   212,   213,
     214,   215,   216,   217,   205,     0,     0,   490,   493,   494,
     475,     0,     0,   499,    52,     0,     0,   364,     0,   387,
       0,   415,     0,   591,     0,   589,   587,   581,   585,   586,
       0,   579,   583,   584,   582,   576,   141,   142,   143,   144,
     140,   146,   148,   150,   159,   163,   225,   299,   336,     0,
     271,   190,   487,   488,   489,   486,   492,   506,   508,    56,
     366,   389,   417,   452,     0,     0,     0,     0,   578,   273,
       0,   588,     0,   580,     0,   590,   595,     0,   593,     0,
       0,   592,   603,     0,     0,     0,     0,   597,   599,   600,
     601,   602,   594,     0,     0,     0,     0,     0,   596,     0,
     605,   606,   607,   598,   604
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,    -4,  -768,   223,  -768,
    -768,  -768,  -768,  -768,  -768,    67,  -768,  -461,  -768,  -768,
    -768,   -70,  -768,  -768,  -768,   403,  -768,  -768,  -768,  -768,
     171,   366,   -72,   -59,   -56,   -54,  -768,  -768,  -768,  -768,
    -768,   167,   370,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
     180,   -29,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,   -66,  -768,  -564,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,   -32,  -547,  -768,
    -768,  -768,  -768,   -34,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,   -38,  -768,  -768,  -768,   -35,   339,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,   -40,  -768,  -768,  -768,  -768,
    -768,  -768,  -767,  -768,  -768,  -768,    -9,  -768,  -768,  -768,
      -6,   388,  -768,  -768,  -762,  -768,  -761,  -768,  -553,  -768,
    -755,  -768,  -768,  -768,  -749,  -768,  -768,  -768,  -768,   -12,
    -768,  -768,  -154,   701,  -768,  -768,  -768,  -768,  -768,    -3,
    -768,  -768,  -768,     4,  -768,   367,  -768,   -61,  -768,  -768,
    -768,  -768,  -768,   -48,  -768,  -768,  -768,  -768,  -768,    10,
    -768,  -768,  -768,     1,  -768,  -768,  -768,     0,  -768,   372,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,   -37,  -768,  -768,  -768,   -33,   409,  -768,  -768,   -49,
    -768,   -11,  -768,  -768,  -768,  -768,  -768,   -39,  -768,  -768,
    -768,   -31,   408,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,   -25,  -768,  -768,  -768,   -30,  -768,
     411,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -747,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,   210,  -768,  -768,  -768,  -768,
    -768,  -768,   -19,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,   -22,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,   222,   363,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,   253,
     375,  -768,  -768,  -768,   -26,  -768,  -768,  -150,  -768,  -768,
    -768,  -768,  -768,  -768,  -159,  -768,  -768,  -172,  -768,  -768,
    -768,  -768,  -768
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     562,    87,    88,    41,    68,    84,    85,   575,   735,   817,
     818,   127,    43,    70,    96,    97,    98,   332,    45,    71,
     128,   129,   130,   131,   132,   133,   134,   135,   340,    47,
      72,   157,   158,   159,   366,   160,   136,   341,   137,   342,
     642,   643,   644,   758,   920,   645,   759,   646,   760,   647,
     761,   648,   250,   405,   650,   651,   652,   653,   654,   767,
     655,   656,   657,   770,   138,   354,   677,   678,   679,   680,
     139,   356,   685,   686,   687,   688,   140,   355,   141,   358,
     692,   693,   694,   793,    63,    80,   286,   287,   288,   418,
     289,   419,   142,   359,   701,   702,   703,   704,   705,   706,
     707,   708,   143,   348,   660,   661,   662,   774,    49,    73,
     180,   181,   182,   373,   183,   374,   184,   375,   185,   379,
     186,   378,   587,   187,   188,   144,   353,   672,   673,   674,
     783,   866,   867,   145,   349,    57,    77,   664,   665,   666,
     777,    59,    78,   251,   252,   253,   254,   255,   256,   257,
     404,   258,   408,   259,   407,   260,   261,   409,   262,   146,
     350,   668,   669,   670,   780,    61,    79,   272,   273,   274,
     275,   276,   413,   277,   278,   279,   280,   190,   371,   739,
     740,   741,   820,    51,    74,   199,   200,   201,   384,   147,
     351,   148,   352,   193,   372,   743,   744,   745,   823,    53,
      75,   213,   214,   215,   387,   216,   217,   389,   218,   219,
     194,   380,   747,   748,   749,   826,    55,    76,   231,   232,
     233,   234,   395,   235,   396,   236,   397,   237,   398,   238,
     399,   239,   400,   240,   394,   195,   381,   751,   829,   149,
     357,   690,   370,   484,   485,   486,   487,   488,   576,   150,
     360,   718,   719,   720,   804,   935,   721,   722,   805,   723,
     724,   151,   152,   362,   730,   731,   732,   811,   733,   812,
     153,   363,    65,    81,   307,   308,   309,   310,   423,   311,
     424,   312,   313,   426,   314,   315,   316,   429,   614,   317,
     430,   318,   319,   320,   321,   434,   621,   322,   435,    99,
     334,   100,   335,   101,   336,   102,   333,    67,    82,   324,
     325,   326,   438,   753,   754,   831,   910,   911,   912,   913,
     946,   914,   944,   957,   958,   959,   966,   967,   968,   973,
     969,   970,   971
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   176,   156,   175,   197,   209,   227,   715,   249,   268,
     285,   304,    38,   269,   177,   689,   860,   178,   270,   179,
     684,   861,   862,   161,   191,   202,   211,   229,   864,   263,
     281,   271,   305,    31,   865,    32,   871,    33,   113,   584,
     585,   586,    89,   675,   163,   163,   154,   155,   594,   595,
     596,   204,   205,   206,   207,   208,   114,   115,   283,   284,
      30,   162,   192,   203,   212,   230,   709,   264,   282,    42,
     306,   106,   107,   108,   109,   633,   113,   243,   113,   283,
     284,   114,   115,   189,   198,   210,   228,    44,   164,   163,
     165,    46,   114,   115,   114,   115,   114,   115,   166,   167,
     168,   169,   170,   171,   675,   682,   338,   683,   114,   115,
     478,   339,   172,   172,   173,   106,   107,   108,   109,   676,
     111,   174,   113,   243,   612,   613,    48,    94,   725,   726,
     616,   617,   618,   619,   364,   786,    50,   113,   787,   365,
     114,   115,   789,   167,   168,   790,   170,   171,   196,   710,
     711,   712,   713,    94,   368,   114,   115,   172,    86,   369,
      52,    90,   860,   620,   382,   174,    54,   861,   862,   383,
      91,    92,    93,   103,   864,    56,   104,   105,    94,    58,
     865,   242,   871,    34,    35,    36,    37,    94,    60,    94,
      62,    94,    64,    94,    66,   106,   107,   108,   109,   110,
     111,   112,   113,   112,   791,    94,   243,   792,   244,   245,
     385,   392,   246,   247,   248,   386,   393,   932,   933,   934,
     114,   115,   113,   114,   115,   323,   916,   917,   918,   919,
     863,   116,   117,   118,   119,   120,   327,    94,   875,   420,
     114,   115,   684,   436,   421,   715,   439,   121,   437,   364,
     122,   440,    94,   439,   755,   220,   243,   123,   756,   221,
     222,   223,   224,   225,   226,   124,   125,   368,    95,   126,
     628,   328,   757,   114,   115,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   639,   640,   329,   330,   243,
     265,   244,   245,   266,   267,   243,   771,   771,   156,   331,
     479,   772,   773,   802,   480,   337,   114,   115,   803,   809,
     176,   813,   175,   436,   810,   197,   814,    94,   815,   161,
      94,   482,   209,   177,   441,   442,   178,   343,   179,   382,
     401,   344,   227,   191,   926,   962,   202,    94,   963,   964,
     965,   832,   249,   211,   833,   929,   903,   268,   904,   905,
     930,   269,   345,   229,   346,   420,   270,   162,   960,   483,
     931,   961,   385,   263,   347,   361,   304,   940,   281,   271,
      94,   192,   367,   376,   203,   377,   863,   114,   115,   392,
     481,   212,   388,   947,   941,   977,   402,   305,   948,   390,
     978,   230,   189,   391,   403,   198,   406,   410,   411,   412,
     417,   264,   210,    94,   414,   415,   282,   416,   422,    94,
     425,   427,   228,   695,   696,   697,   698,   699,   700,   428,
     431,   432,   433,   444,   443,   306,   445,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   446,   552,   553,   554,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   447,
     448,   450,   451,   452,   458,   453,   459,   454,   455,   456,
     457,   460,   461,   462,    94,   463,   464,   465,   466,   467,
     468,   469,   470,   472,   471,   156,   641,   641,   473,   475,
     649,   649,   476,   489,   490,   491,   492,   493,   495,   494,
     496,   714,   727,   304,   497,   498,   161,   499,   479,   501,
     503,   505,   480,   504,   506,   509,   510,   511,   507,   512,
     513,   514,   716,   728,   305,   515,   608,   517,   518,   482,
     519,   520,   521,   522,   525,   523,   529,   526,   530,   527,
     533,   534,   532,   535,   162,   624,   536,   537,   539,   540,
     538,   544,   545,   541,   547,   549,   542,   563,   558,   550,
     717,   729,   306,   543,   551,   555,   556,   483,   557,   559,
     560,   577,   564,    32,   565,   566,   567,   568,   569,   581,
     582,   570,   571,   572,   573,   574,   578,   579,   481,   580,
     583,   588,   589,   590,   591,   592,   593,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   609,   610,
     615,   623,   659,   736,   663,   667,   611,   671,   622,   691,
     738,   742,   746,   750,   752,   762,   763,   764,   765,   766,
     768,   769,   776,   681,   775,   779,   778,   781,   782,   784,
     785,   839,   788,   795,   794,   796,   797,   798,   799,   800,
     801,   806,   807,   808,   816,   822,   821,   819,   825,   824,
     827,   828,   841,   834,   830,   835,   836,   837,   843,   846,
     838,   885,   886,   891,   840,   842,   844,   892,   845,   895,
     894,   878,   879,   902,   561,   927,   928,   880,   942,   881,
     945,   882,   950,   952,   883,   954,   887,   888,   956,   889,
     974,   641,   176,   975,   175,   649,   976,   249,   979,   921,
     268,   855,   951,   854,   269,   177,   981,   859,   178,   270,
     179,   625,   627,   285,   856,   191,   980,   857,   263,   858,
     474,   281,   271,   922,   869,   982,   923,   658,   477,   714,
     924,   449,   847,   727,   925,   936,   937,   938,   939,   943,
     197,   955,   984,   209,   873,   874,   227,   877,   876,   531,
     716,   906,   884,   192,   728,   907,   264,   849,   848,   282,
     500,   202,   870,   872,   211,   949,   851,   229,   241,   524,
     852,   850,   908,   853,   189,   897,   899,   896,   737,   528,
     890,   893,   898,   868,   502,   734,   900,   953,   717,   546,
     508,   972,   729,   901,   626,   983,   915,     0,     0,   203,
       0,     0,   212,   516,   548,   230,     0,     0,     0,     0,
     909,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     198,     0,     0,   210,     0,     0,   228,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   855,     0,   854,
       0,     0,     0,   859,     0,     0,     0,     0,     0,     0,
     856,     0,     0,   857,     0,   858,     0,   906,     0,     0,
     869,   907,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   908,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   870,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   909,     0,     0,   868
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    73,    72,    73,    74,    75,    76,   571,    78,    79,
      80,    81,    16,    79,    73,   568,   783,    73,    79,    73,
     567,   783,   783,    72,    73,    74,    75,    76,   783,    78,
      79,    79,    81,     5,   783,     7,   783,     9,    40,    66,
      67,    68,    10,    79,     7,     7,    12,    13,   509,   510,
     511,    53,    54,    55,    56,    57,    58,    59,    86,    87,
       0,    72,    73,    74,    75,    76,    16,    78,    79,     7,
      81,    33,    34,    35,    36,    25,    40,    41,    40,    86,
      87,    58,    59,    73,    74,    75,    76,     7,    50,     7,
      52,     7,    58,    59,    58,    59,    58,    59,    60,    61,
      62,    63,    64,    65,    79,    80,     3,    82,    58,    59,
      74,     8,    75,    75,    76,    33,    34,    35,    36,   155,
      38,    83,    40,    41,   122,   123,     7,   155,   105,   106,
     125,   126,   127,   128,     3,     3,     7,    40,     6,     8,
      58,    59,     3,    61,    62,     6,    64,    65,    51,    99,
     100,   101,   102,   155,     3,    58,    59,    75,   155,     8,
       7,   129,   929,   158,     3,    83,     7,   929,   929,     8,
     138,   139,   140,    11,   929,     7,    14,    15,   155,     7,
     929,    16,   929,   155,   156,   157,   158,   155,     7,   155,
       7,   155,     7,   155,     7,    33,    34,    35,    36,    37,
      38,    39,    40,    39,     3,   155,    41,     6,    43,    44,
       3,     3,    47,    48,    49,     8,     8,    96,    97,    98,
      58,    59,    40,    58,    59,   130,    17,    18,    19,    20,
     783,    69,    70,    71,    72,    73,     6,   155,   791,     3,
      58,    59,   789,     3,     8,   809,     3,    85,     8,     3,
      88,     8,   155,     3,     8,    73,    41,    95,     8,    77,
      78,    79,    80,    81,    82,   103,   104,     3,   338,   107,
      16,     3,     8,    58,    59,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     4,     8,    41,
      42,    43,    44,    45,    46,    41,     3,     3,   368,     3,
     370,     8,     8,     3,   370,     4,    58,    59,     8,     3,
     382,     3,   382,     3,     8,   385,     8,   155,     8,   368,
     155,   370,   392,   382,   328,   329,   382,     4,   382,     3,
       8,     4,   402,   382,     8,   132,   385,   155,   135,   136,
     137,     3,   412,   392,     6,     3,   131,   417,   133,   134,
       8,   417,     4,   402,     4,     3,   417,   368,     3,   370,
       8,     6,     3,   412,     4,     4,   436,     8,   417,   417,
     155,   382,     4,     4,   385,     4,   929,    58,    59,     3,
     370,   392,     4,     3,     8,     3,     3,   436,     8,     4,
       8,   402,   382,     4,     8,   385,     4,     4,     8,     3,
       3,   412,   392,   155,     4,     4,   417,     8,     4,   155,
       4,     4,   402,    89,    90,    91,    92,    93,    94,     4,
       4,     4,     4,     4,   155,   436,     4,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     4,   446,   447,   448,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,     4,
       4,     4,     4,     4,     4,   156,     4,   156,   156,   156,
     156,     4,     4,     4,   155,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   156,   555,   556,   557,     4,     4,
     556,   557,   158,     4,     4,     4,     4,     4,   158,   156,
       4,   571,   572,   573,     4,     4,   555,     4,   578,     4,
       4,     4,   578,   156,   156,     4,     4,     4,   156,     4,
       4,     4,   571,   572,   573,     4,   530,     4,     4,   578,
     156,     4,     4,     4,     4,   158,     4,   158,     4,   158,
       4,     4,   158,   156,   555,   549,     4,   156,     4,     4,
     156,     4,     4,   158,     4,     4,   158,   155,     5,     7,
     571,   572,   573,   158,     7,     7,     7,   578,     7,     5,
       5,     8,     5,     7,     5,     5,     5,     5,     5,   155,
     155,     7,     7,     7,     7,     5,     3,     5,   578,     5,
     155,   155,     5,     7,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     124,     5,     7,     4,     7,     7,   155,     7,   155,     7,
       7,     7,     7,    84,     7,     4,     4,     4,     4,     4,
       4,     4,     3,   566,     6,     3,     6,     6,     3,     6,
       3,   158,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   155,     3,     6,   155,     3,     6,
       6,     3,   158,     4,     8,     4,     4,     4,     4,     4,
     156,     4,     4,     4,   156,   156,   156,     4,   156,     3,
       6,   156,   156,     4,   461,     8,     8,   156,     8,   156,
       4,   156,     4,     4,   156,     5,   156,   156,     7,   156,
       4,   771,   774,     4,   774,   771,     4,   777,     4,   155,
     780,   783,   156,   783,   780,   774,   156,   783,   774,   780,
     774,   550,   555,   793,   783,   774,   158,   783,   777,   783,
     364,   780,   780,   155,   783,   156,   155,   557,   368,   809,
     155,   338,   771,   813,   155,   155,   155,   155,   155,   155,
     820,   155,   155,   823,   786,   789,   826,   795,   793,   420,
     809,   831,   802,   774,   813,   831,   777,   776,   774,   780,
     382,   820,   783,   785,   823,   929,   779,   826,    77,   412,
     780,   777,   831,   782,   774,   822,   825,   820,   578,   417,
     809,   813,   823,   783,   385,   573,   826,   947,   809,   436,
     392,   960,   813,   828,   551,   977,   832,    -1,    -1,   820,
      -1,    -1,   823,   402,   439,   826,    -1,    -1,    -1,    -1,
     831,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     820,    -1,    -1,   823,    -1,    -1,   826,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   929,    -1,   929,
      -1,    -1,    -1,   929,    -1,    -1,    -1,    -1,    -1,    -1,
     929,    -1,    -1,   929,    -1,   929,    -1,   947,    -1,    -1,
     929,   947,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   947,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   929,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   947,    -1,    -1,   929
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
       7,   344,     7,   263,     7,   451,     7,   486,   183,   178,
     192,   198,   209,   288,   363,   379,   396,   315,   321,   345,
     264,   452,   487,   175,   184,   185,   155,   180,   181,    10,
     129,   138,   139,   140,   155,   190,   193,   194,   195,   478,
     480,   482,   484,    11,    14,    15,    33,    34,    35,    36,
      37,    38,    39,    40,    58,    59,    69,    70,    71,    72,
      73,    85,    88,    95,   103,   104,   107,   190,   199,   200,
     201,   202,   203,   204,   205,   206,   215,   217,   243,   249,
     255,   257,   271,   281,   304,   312,   338,   368,   370,   418,
     428,   440,   441,   449,    12,    13,   190,   210,   211,   212,
     214,   368,   370,     7,    50,    52,    60,    61,    62,    63,
      64,    65,    75,    76,    83,   190,   201,   202,   203,   204,
     289,   290,   291,   293,   295,   297,   299,   302,   303,   338,
     356,   368,   370,   372,   389,   414,    51,   190,   338,   364,
     365,   366,   368,   370,    53,    54,    55,    56,    57,   190,
     338,   368,   370,   380,   381,   382,   384,   385,   387,   388,
      73,    77,    78,    79,    80,    81,    82,   190,   338,   368,
     370,   397,   398,   399,   400,   402,   404,   406,   408,   410,
     412,   312,    16,    41,    43,    44,    47,    48,    49,   190,
     231,   322,   323,   324,   325,   326,   327,   328,   330,   332,
     334,   335,   337,   368,   370,    42,    45,    46,   190,   231,
     326,   332,   346,   347,   348,   349,   350,   352,   353,   354,
     355,   368,   370,    86,    87,   190,   265,   266,   267,   269,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   190,   368,   370,   453,   454,   455,
     456,   458,   460,   461,   463,   464,   465,   468,   470,   471,
     472,   473,   476,   130,   488,   489,   490,     6,     3,     4,
       8,     3,   196,   485,   479,   481,   483,     4,     3,     8,
     207,   216,   218,     4,     4,     4,     4,     4,   282,   313,
     339,   369,   371,   305,   244,   256,   250,   419,   258,   272,
     429,     4,   442,   450,     3,     8,   213,     4,     3,     8,
     421,   357,   373,   292,   294,   296,     4,     4,   300,   298,
     390,   415,     3,     8,   367,     3,     8,   383,     4,   386,
       4,     4,     3,     8,   413,   401,   403,   405,   407,   409,
     411,     8,     3,     8,   329,   232,     4,   333,   331,   336,
       4,     8,     3,   351,     4,     4,     8,     3,   268,   270,
       3,     8,     4,   457,   459,     4,   462,     4,     4,   466,
     469,     4,     4,     4,   474,   477,     3,     8,   491,     3,
       8,   175,   175,   155,     4,     4,     4,     4,     4,   194,
       4,     4,     4,   156,   156,   156,   156,   156,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   156,     4,     4,   200,     4,   158,   211,    74,   190,
     231,   338,   368,   370,   422,   423,   424,   425,   426,     4,
       4,     4,     4,     4,   156,   158,     4,     4,     4,     4,
     290,     4,   365,     4,   156,     4,   156,   156,   381,     4,
       4,     4,     4,     4,     4,     4,   399,     4,     4,   156,
       4,     4,     4,   158,   324,     4,   158,   158,   348,     4,
       4,   266,   158,     4,     4,   156,     4,   156,   156,     4,
       4,   158,   158,   158,     4,     4,   454,     4,   489,     4,
       7,     7,   175,   175,   175,     7,     7,     7,     5,     5,
       5,   177,   179,   155,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   186,   427,     8,     3,     5,
       5,   155,   155,   155,    66,    67,    68,   301,   155,     5,
       7,   155,   155,   155,   186,   186,   186,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   175,   155,
     155,   155,   122,   123,   467,   124,   125,   126,   127,   128,
     158,   475,   155,     5,   175,   199,   488,   210,    16,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,   190,   219,   220,   221,   224,   226,   228,   230,   231,
     233,   234,   235,   236,   237,   239,   240,   241,   219,     7,
     283,   284,   285,     7,   316,   317,   318,     7,   340,   341,
     342,     7,   306,   307,   308,    79,   155,   245,   246,   247,
     248,   184,    80,    82,   247,   251,   252,   253,   254,   297,
     420,     7,   259,   260,   261,    89,    90,    91,    92,    93,
      94,   273,   274,   275,   276,   277,   278,   279,   280,    16,
      99,   100,   101,   102,   190,   233,   368,   370,   430,   431,
     432,   435,   436,   438,   439,   105,   106,   190,   368,   370,
     443,   444,   445,   447,   453,   187,     4,   424,     7,   358,
     359,   360,     7,   374,   375,   376,     7,   391,   392,   393,
      84,   416,     7,   492,   493,     8,     8,     8,   222,   225,
     227,   229,     4,     4,     4,     4,     4,   238,     4,     4,
     242,     3,     8,     8,   286,     6,     3,   319,     6,     3,
     343,     6,     3,   309,     6,     3,     3,     6,     6,     3,
       6,     3,     6,   262,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   433,   437,     4,     4,     4,     3,
       8,   446,   448,     3,     8,     8,   155,   188,   189,   155,
     361,     6,     3,   377,     6,     3,   394,     6,     3,   417,
       8,   494,     3,     6,     4,     4,     4,     4,   156,   158,
     156,   158,   156,     4,   156,   156,     4,   220,   289,   285,
     322,   318,   346,   342,   190,   201,   202,   203,   204,   231,
     281,   293,   295,   297,   299,   303,   310,   311,   338,   368,
     370,   414,   308,   246,   252,   297,   265,   261,   156,   156,
     156,   156,   156,   156,   274,     4,     4,   156,   156,   156,
     431,     4,     4,   444,     6,     3,   364,   360,   380,   376,
     397,   393,     4,   131,   133,   134,   190,   231,   368,   370,
     495,   496,   497,   498,   500,   493,    17,    18,    19,    20,
     223,   155,   155,   155,   155,   155,     8,     8,     8,     3,
       8,     8,    96,    97,    98,   434,   155,   155,   155,   155,
       8,     8,     8,   155,   501,     4,   499,     3,     8,   311,
       4,   156,     4,   496,     5,   155,     7,   502,   503,   504,
       3,     6,   132,   135,   136,   137,   505,   506,   507,   509,
     510,   511,   503,   508,     4,     4,     4,     3,     8,     4,
     158,   156,   156,   506,   155
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
     364,   365,   365,   365,   365,   365,   367,   366,   369,   368,
     371,   370,   373,   372,   374,   374,   375,   375,   377,   376,
     379,   378,   380,   380,   381,   381,   381,   381,   381,   381,
     381,   381,   381,   383,   382,   384,   386,   385,   387,   388,
     390,   389,   391,   391,   392,   392,   394,   393,   396,   395,
     397,   397,   398,   398,   399,   399,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   401,   400,   403,   402,   405,
     404,   407,   406,   409,   408,   411,   410,   413,   412,   415,
     414,   417,   416,   419,   418,   420,   420,   421,   297,   422,
     422,   423,   423,   424,   424,   424,   424,   424,   424,   425,
     427,   426,   429,   428,   430,   430,   431,   431,   431,   431,
     431,   431,   431,   431,   431,   433,   432,   434,   434,   434,
     435,   437,   436,   438,   439,   440,   442,   441,   443,   443,
     444,   444,   444,   444,   444,   446,   445,   448,   447,   450,
     449,   452,   451,   453,   453,   454,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   454,   454,   454,
     454,   454,   455,   457,   456,   459,   458,   460,   462,   461,
     463,   464,   466,   465,   467,   467,   469,   468,   470,   471,
     472,   474,   473,   475,   475,   475,   475,   475,   477,   476,
     479,   478,   481,   480,   483,   482,   485,   484,   487,   486,
     488,   488,   489,   491,   490,   492,   492,   494,   493,   495,
     495,   496,   496,   496,   496,   496,   496,   496,   497,   499,
     498,   501,   500,   502,   502,   504,   503,   505,   505,   506,
     506,   506,   506,   508,   507,   509,   510,   511
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
       3,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
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
  "$@86", "client_classes", "$@87", "client_classes_list", "$@88",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@89",
  "server_id", "$@90", "server_id_params", "server_id_param",
  "server_id_type", "$@91", "duid_type", "htype", "identifier", "$@92",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@93",
  "control_socket_params", "control_socket_param", "socket_type", "$@94",
  "socket_name", "$@95", "dhcp_ddns", "$@96", "sub_dhcp_ddns", "$@97",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@98", "server_ip", "$@99", "server_port",
  "sender_ip", "$@100", "sender_port", "max_queue_size", "ncr_protocol",
  "$@101", "ncr_protocol_value", "ncr_format", "$@102",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@103", "replace_client_name_value",
  "generated_prefix", "$@104", "dhcp4_json_object", "$@105",
  "dhcpddns_json_object", "$@106", "control_agent_json_object", "$@107",
  "logging_object", "$@108", "sub_logging", "$@109", "logging_params",
  "logging_param", "loggers", "$@110", "loggers_entries", "logger_entry",
  "$@111", "logger_params", "logger_param", "debuglevel", "severity",
  "$@112", "output_options_list", "$@113", "output_options_list_content",
  "output_entry", "$@114", "output_params_list", "output_params", "output",
  "$@115", "flush", "maxsize", "maxver", YY_NULLPTR
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
    1319,  1322,  1323,  1324,  1325,  1326,  1329,  1329,  1337,  1337,
    1362,  1362,  1392,  1392,  1404,  1405,  1408,  1409,  1412,  1412,
    1424,  1424,  1436,  1437,  1440,  1441,  1442,  1443,  1444,  1445,
    1446,  1447,  1448,  1451,  1451,  1459,  1464,  1464,  1472,  1477,
    1485,  1485,  1495,  1496,  1499,  1500,  1503,  1503,  1512,  1512,
    1521,  1522,  1525,  1526,  1530,  1531,  1532,  1533,  1534,  1535,
    1536,  1537,  1538,  1539,  1540,  1543,  1543,  1553,  1553,  1563,
    1563,  1571,  1571,  1579,  1579,  1587,  1587,  1595,  1595,  1608,
    1608,  1618,  1618,  1629,  1629,  1639,  1640,  1643,  1643,  1653,
    1654,  1657,  1658,  1661,  1662,  1663,  1664,  1665,  1666,  1669,
    1671,  1671,  1682,  1682,  1694,  1695,  1698,  1699,  1700,  1701,
    1702,  1703,  1704,  1705,  1706,  1709,  1709,  1716,  1717,  1718,
    1721,  1726,  1726,  1734,  1739,  1746,  1753,  1753,  1763,  1764,
    1767,  1768,  1769,  1770,  1771,  1774,  1774,  1782,  1782,  1792,
    1792,  1804,  1804,  1814,  1815,  1818,  1819,  1820,  1821,  1822,
    1823,  1824,  1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,
    1833,  1834,  1837,  1842,  1842,  1850,  1850,  1858,  1863,  1863,
    1871,  1876,  1881,  1881,  1889,  1890,  1893,  1893,  1901,  1906,
    1911,  1916,  1916,  1924,  1927,  1930,  1933,  1936,  1942,  1942,
    1952,  1952,  1959,  1959,  1966,  1966,  1979,  1979,  1989,  1989,
    2000,  2001,  2005,  2009,  2009,  2021,  2022,  2026,  2026,  2034,
    2035,  2038,  2039,  2040,  2041,  2042,  2043,  2044,  2047,  2052,
    2052,  2060,  2060,  2070,  2071,  2074,  2074,  2082,  2083,  2086,
    2087,  2088,  2089,  2092,  2092,  2100,  2105,  2110
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
#line 4614 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2115 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
