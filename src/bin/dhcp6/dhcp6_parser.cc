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
      case 177: // value
      case 181: // map_value
      case 225: // db_type
      case 305: // hr_mode
      case 439: // duid_type
      case 472: // ncr_protocol_value
      case 480: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 160: // "boolean"
        value.move< bool > (that.value);
        break;

      case 159: // "floating point"
        value.move< double > (that.value);
        break;

      case 158: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 157: // "constant string"
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
      case 177: // value
      case 181: // map_value
      case 225: // db_type
      case 305: // hr_mode
      case 439: // duid_type
      case 472: // ncr_protocol_value
      case 480: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 160: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 159: // "floating point"
        value.copy< double > (that.value);
        break;

      case 158: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 157: // "constant string"
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
            case 157: // "constant string"

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 158: // "integer"

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 159: // "floating point"

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 160: // "boolean"

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 177: // value

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 181: // map_value

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 225: // db_type

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 305: // hr_mode

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 439: // duid_type

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 472: // ncr_protocol_value

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 480: // replace_client_name_value

#line 233 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 177: // value
      case 181: // map_value
      case 225: // db_type
      case 305: // hr_mode
      case 439: // duid_type
      case 472: // ncr_protocol_value
      case 480: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 160: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 159: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 158: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 157: // "constant string"
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
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 299 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 317 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 321 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 339 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 343 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 369 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 392 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1264 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1497 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1572 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1804 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1812 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1827 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 991 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1906 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1145 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1160 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1168 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2142 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2210 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2339 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2351 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2844 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2871 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1824 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1905 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1940 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1949 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2063 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2076 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2108 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3408 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3412 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -762;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     402,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,    43,    27,    42,    50,    92,
     119,   146,   150,   158,   166,   167,   174,   190,   214,   215,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,    27,    26,
      36,    49,    32,   189,    41,   228,   198,   163,    82,   247,
     -38,   347,   102,  -762,   251,   265,   296,   308,   314,  -762,
    -762,  -762,  -762,  -762,   316,  -762,    34,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,   319,   324,   329,   341,
     344,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,   346,  -762,  -762,  -762,    71,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,   349,  -762,    72,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   352,   359,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,    74,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   100,
    -762,  -762,  -762,  -762,  -762,   364,  -762,   366,   367,  -762,
    -762,  -762,  -762,  -762,   126,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,   317,   370,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,   369,  -762,  -762,   371,  -762,  -762,  -762,   374,
    -762,  -762,   372,   378,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,   379,   380,  -762,
    -762,  -762,  -762,   381,   384,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,   127,  -762,  -762,
    -762,   386,  -762,  -762,   387,  -762,   389,   390,  -762,  -762,
     391,   398,   405,  -762,  -762,  -762,  -762,  -762,   161,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,   187,  -762,  -762,  -762,    27,
      27,  -762,   210,   407,   408,   409,   410,   411,  -762,    36,
    -762,   413,   414,   415,   216,   262,   263,   264,   267,   424,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   437,
     438,   439,   286,   441,   442,    49,  -762,   443,   289,    32,
    -762,   446,   447,   451,   452,   467,   315,   312,   473,   474,
     475,   476,   189,  -762,   477,    41,  -762,   478,   325,   480,
     327,   328,   228,  -762,   483,   484,   485,   489,   490,   491,
     493,  -762,   198,  -762,   494,   495,   342,   497,   498,   499,
     345,  -762,    82,   502,   348,   350,  -762,   247,   503,   505,
     -50,  -762,   351,   511,   512,   360,   513,   361,   365,   517,
     518,   368,   373,   375,   522,   523,   347,  -762,   525,   102,
    -762,  -762,  -762,   526,   524,   527,    27,    27,    27,  -762,
     529,   530,   536,  -762,  -762,  -762,  -762,  -762,   554,   555,
     556,   557,   406,   560,   561,   562,   563,   564,   565,   566,
     567,  -762,   568,   569,  -762,   572,  -762,  -762,   573,   574,
     423,   425,   426,  -762,  -762,   176,   436,   576,   577,  -762,
     440,  -762,   444,  -762,   445,  -762,  -762,  -762,   572,   572,
     572,   448,   449,   450,   453,  -762,   454,   455,  -762,   456,
     457,   458,  -762,  -762,   459,  -762,  -762,  -762,   460,    27,
    -762,  -762,   461,   462,  -762,   463,  -762,  -762,    -8,   464,
    -762,  -762,  -762,   -15,   465,  -762,   580,  -762,    27,    49,
     102,  -762,  -762,  -762,    32,   186,   186,   579,   581,   582,
    -762,  -762,  -762,   584,   -46,    27,    56,   585,   587,   169,
      46,    44,   347,  -762,  -762,   588,   589,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,   591,   486,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   592,
    -762,   188,   191,   197,  -762,  -762,  -762,  -762,   528,   558,
     583,   596,   599,  -762,  -762,   600,   604,   605,   617,  -762,
     220,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   227,  -762,
     618,   620,  -762,  -762,   619,   623,  -762,  -762,   621,   625,
    -762,  -762,   624,   626,  -762,  -762,  -762,    70,  -762,  -762,
    -762,   627,  -762,  -762,  -762,    94,  -762,  -762,  -762,  -762,
     138,  -762,  -762,   628,   629,  -762,   631,   632,   633,   634,
     635,   636,   229,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,   637,   638,   639,  -762,  -762,  -762,  -762,   230,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,   239,  -762,  -762,  -762,   268,   487,  -762,   640,   642,
    -762,  -762,   641,   645,  -762,  -762,   643,   647,  -762,  -762,
     644,  -762,   160,  -762,  -762,  -762,  -762,   649,   650,   651,
     652,   500,   471,   501,   504,   507,   653,   656,   508,   509,
     510,   514,   186,  -762,  -762,   189,  -762,   579,    82,  -762,
     581,   247,  -762,   582,   363,  -762,   584,   -46,  -762,  -762,
      56,  -762,     5,   585,  -762,   -38,  -762,   587,   515,   519,
     520,   521,   531,   532,   169,  -762,   657,   658,   533,   538,
     539,    46,  -762,   659,   665,    44,  -762,  -762,  -762,   664,
     648,    41,  -762,   588,   228,  -762,   589,   198,  -762,   591,
     667,  -762,    35,   592,  -762,   321,   537,   542,   543,  -762,
    -762,  -762,  -762,  -762,   546,   548,  -762,  -762,  -762,  -762,
    -762,   293,  -762,   668,  -762,   672,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   294,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,   673,   669,  -762,  -762,  -762,  -762,
     295,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   231,
     551,  -762,  -762,  -762,  -762,   570,   571,  -762,  -762,   575,
     301,  -762,   303,  -762,   674,  -762,   586,  -762,   671,  -762,
    -762,  -762,  -762,  -762,   310,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,   363,  -762,   679,  -762,     5,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,   680,   578,   681,    35,  -762,  -762,   593,  -762,   682,
    -762,   601,  -762,  -762,   706,  -762,  -762,   269,  -762,    22,
     706,  -762,  -762,   684,   710,   717,   311,  -762,  -762,  -762,
    -762,  -762,  -762,   718,   610,   598,   602,    22,  -762,   608,
    -762,  -762,  -762,  -762,  -762
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   106,     9,   230,    11,
     371,    13,   395,    15,   424,    17,   296,    19,   304,    21,
     341,    23,   195,    25,   517,    27,   574,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   426,     0,   306,   343,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     572,   566,   568,   570,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   104,   118,   120,     0,     0,     0,     0,
       0,   222,   294,   333,   383,   385,   268,   168,   185,   176,
     459,   187,   206,   478,     0,   502,   515,    98,     0,    72,
      74,    75,    76,    77,    78,    81,    82,    83,    84,    86,
      85,    90,    91,    79,    80,    88,    89,    96,    97,    87,
      92,    93,    94,    95,   115,     0,   114,     0,   108,   110,
     111,   112,   113,   363,   387,   253,   255,   257,     0,     0,
     261,   259,   416,   455,   252,   234,   235,   236,   237,     0,
     232,   241,   242,   243,   246,   248,   244,   245,   238,   239,
     250,   251,   240,   247,   249,   381,   380,   377,   376,     0,
     373,   375,   378,   379,   409,     0,   412,     0,     0,   408,
     403,   402,   406,   407,     0,   397,   399,   400,   404,   405,
     401,   453,   441,   443,   445,   447,   449,   451,   440,   437,
     438,   439,     0,   427,   428,   432,   433,   430,   434,   435,
     436,   431,     0,   323,   154,     0,   327,   325,   330,     0,
     319,   320,     0,   307,   308,   310,   322,   311,   312,   313,
     329,   314,   315,   316,   317,   318,   357,     0,     0,   355,
     356,   359,   360,     0,   344,   345,   347,   348,   349,   350,
     351,   352,   353,   354,   202,   204,   199,     0,   197,   200,
     201,     0,   539,   541,     0,   544,     0,     0,   548,   552,
       0,     0,     0,   557,   564,   537,   535,   536,     0,   519,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   579,     0,   576,   578,    46,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   231,     0,     0,   372,     0,     0,     0,
       0,     0,     0,   396,     0,     0,     0,     0,     0,     0,
       0,   425,     0,   297,     0,     0,     0,     0,     0,     0,
       0,   305,     0,     0,     0,     0,   342,     0,     0,     0,
       0,   196,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   518,     0,     0,
     575,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   501,     0,     0,    73,     0,   117,   109,     0,     0,
       0,     0,     0,   266,   267,     0,     0,     0,     0,   233,
       0,   374,     0,   411,     0,   414,   415,   398,     0,     0,
       0,     0,     0,     0,     0,   429,     0,     0,   321,     0,
       0,     0,   332,   309,     0,   361,   362,   346,     0,     0,
     198,   538,     0,     0,   543,     0,   546,   547,     0,     0,
     554,   555,   556,     0,     0,   520,     0,   577,     0,     0,
       0,   567,   569,   571,     0,     0,     0,   224,   298,   335,
      40,   384,   386,   270,     0,    47,     0,     0,   189,     0,
       0,     0,     0,    51,   116,   365,   389,   254,   256,   258,
     263,   264,   265,   262,   260,   418,     0,   382,   410,   413,
     454,   442,   444,   446,   448,   450,   452,   324,   155,   328,
     326,   331,   358,   203,   205,   540,   542,   545,   550,   551,
     549,   553,   559,   560,   561,   562,   563,   558,   565,     0,
      44,     0,     0,     0,   141,   147,   149,   151,     0,     0,
       0,     0,     0,   164,   166,     0,     0,     0,     0,   140,
       0,   122,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   135,   136,   137,   138,   134,   139,     0,   228,
       0,   225,   226,   302,     0,   299,   300,   339,     0,   336,
     337,   274,     0,   271,   272,   174,   175,     0,   170,   172,
     173,     0,   183,   184,   180,     0,   178,   181,   182,   463,
       0,   461,   193,     0,   190,   191,     0,     0,     0,     0,
       0,     0,     0,   208,   210,   211,   212,   213,   214,   215,
     491,   497,     0,     0,     0,   490,   487,   488,   489,     0,
     480,   482,   485,   483,   484,   486,   511,   513,   510,   508,
     509,     0,   504,   506,   507,     0,    53,   369,     0,   366,
     367,   393,     0,   390,   391,   422,     0,   419,   420,   457,
       0,   583,     0,   581,    69,   573,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   121,     0,   223,     0,   306,   295,
       0,   343,   334,     0,     0,   269,     0,     0,   169,   186,
       0,   177,   465,     0,   460,     0,   188,     0,     0,     0,
       0,     0,     0,     0,     0,   207,     0,     0,     0,     0,
       0,     0,   479,     0,     0,     0,   503,   516,    55,     0,
      54,     0,   364,     0,     0,   388,     0,   426,   417,     0,
       0,   456,     0,     0,   580,     0,     0,     0,     0,   153,
     156,   157,   158,   159,     0,     0,   160,   161,   162,   163,
     123,     0,   227,     0,   301,     0,   338,   293,   288,   290,
     282,   283,   278,   279,   280,   281,   287,   286,   289,     0,
     276,   284,   291,   292,   285,   273,   171,   179,   476,   474,
     475,   471,   472,   473,     0,   466,   467,   469,   470,   462,
       0,   192,   216,   217,   218,   219,   220,   221,   209,     0,
       0,   496,   499,   500,   481,     0,     0,   505,    52,     0,
       0,   368,     0,   392,     0,   421,     0,   597,     0,   595,
     593,   587,   591,   592,     0,   585,   589,   590,   588,   582,
     143,   144,   145,   146,   142,   148,   150,   152,   165,   167,
     229,   303,   340,     0,   275,     0,   464,     0,   194,   493,
     494,   495,   492,   498,   512,   514,    56,   370,   394,   423,
     458,     0,     0,     0,     0,   584,   277,     0,   468,     0,
     594,     0,   586,   477,     0,   596,   601,     0,   599,     0,
       0,   598,   609,     0,     0,     0,     0,   603,   605,   606,
     607,   608,   600,     0,     0,     0,     0,     0,   602,     0,
     611,   612,   613,   604,   610
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,     6,  -762,   110,  -762,
    -762,  -762,  -762,  -762,  -762,   131,  -762,  -139,  -762,  -762,
    -762,   -70,  -762,  -762,  -762,   385,  -762,  -762,  -762,  -762,
     194,   377,   -72,   -58,   -56,   -55,  -762,  -762,  -762,  -762,
    -762,   181,   392,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
     183,   -32,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,    -7,  -762,  -553,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   -40,
    -544,  -762,  -762,  -762,  -762,   -42,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,   -41,  -762,  -762,  -762,   -36,   353,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,   -23,  -762,  -762,
    -762,  -762,  -762,  -762,  -761,  -762,  -762,  -762,   -28,  -762,
    -762,  -762,     7,   396,  -762,  -762,  -758,  -762,  -754,  -762,
     -34,  -762,  -753,  -762,  -762,  -762,  -751,  -762,  -762,  -762,
    -762,     3,  -762,  -762,  -151,   707,  -762,  -762,  -762,  -762,
    -762,    13,  -762,  -762,  -762,    18,  -762,   376,  -762,   -65,
    -762,  -762,  -762,  -762,  -762,   -60,  -762,  -762,  -762,  -762,
    -762,    -6,  -762,  -762,  -762,    14,  -762,  -762,  -762,    19,
    -762,   382,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,   -24,  -762,  -762,  -762,   -19,   416,  -762,
    -762,   -48,  -762,   -20,  -762,  -762,  -762,  -762,  -762,   -21,
    -762,  -762,  -762,   -18,   401,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,   -16,  -762,  -762,  -762,
     -17,  -762,   404,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -745,  -762,  -762,
    -762,  -762,  -762,  -762,    15,  -762,  -762,  -762,  -133,  -762,
    -762,  -762,  -762,  -762,  -762,     8,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,     2,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,   248,   383,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,   272,   388,  -762,  -762,  -762,   -10,  -762,  -762,
    -140,  -762,  -762,  -762,  -762,  -762,  -762,  -154,  -762,  -762,
    -170,  -762,  -762,  -762,  -762,  -762
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     551,    87,    88,    41,    68,    84,    85,   564,   726,   809,
     810,   127,    43,    70,    96,    97,    98,   333,    45,    71,
     128,   129,   130,   131,   132,   133,   134,   135,   341,    47,
      72,   157,   158,   159,   367,   160,   136,   342,   137,   343,
     630,   631,   632,   747,   924,   633,   748,   634,   749,   635,
     750,   636,   251,   405,   638,   639,   640,   641,   642,   643,
     644,   645,   646,   756,   647,   757,   138,   355,   667,   668,
     669,   670,   139,   357,   675,   676,   677,   678,   140,   356,
     141,   359,   683,   684,   685,   785,    63,    80,   287,   288,
     289,   418,   290,   419,   142,   360,   692,   693,   694,   695,
     696,   697,   698,   699,   143,   349,   650,   651,   652,   765,
      49,    73,   179,   180,   181,   373,   182,   374,   183,   375,
     184,   379,   185,   378,   573,   186,   187,   144,   354,   662,
     663,   664,   774,   859,   860,   145,   350,    57,    77,   654,
     655,   656,   768,    59,    78,   252,   253,   254,   255,   256,
     257,   258,   404,   259,   408,   260,   407,   261,   262,   409,
     263,   146,   351,   658,   659,   660,   771,    61,    79,   273,
     274,   275,   276,   277,   413,   278,   279,   280,   281,   189,
     371,   728,   729,   730,   811,    51,    74,   199,   200,   201,
     384,   147,   352,   148,   353,   192,   372,   732,   733,   734,
     814,    53,    75,   214,   215,   216,   387,   217,   218,   389,
     219,   220,   193,   380,   736,   737,   738,   817,    55,    76,
     232,   233,   234,   235,   395,   236,   396,   237,   397,   238,
     398,   239,   399,   240,   400,   241,   394,   194,   381,   740,
     820,   149,   358,   680,   681,   782,   874,   875,   876,   877,
     878,   935,   150,   361,   709,   710,   711,   796,   942,   712,
     713,   797,   714,   715,   151,   152,   363,   721,   722,   723,
     803,   724,   804,   153,   364,    65,    81,   308,   309,   310,
     311,   423,   312,   424,   313,   314,   426,   315,   316,   317,
     429,   600,   318,   430,   319,   320,   321,   322,   434,   607,
     323,   435,    99,   335,   100,   336,   101,   337,   102,   334,
      67,    82,   325,   326,   327,   438,   742,   743,   822,   914,
     915,   916,   917,   953,   918,   951,   967,   968,   969,   976,
     977,   978,   983,   979,   980,   981
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   175,   156,   174,   196,   209,   228,   706,   250,   269,
     286,   305,   674,   853,   271,   176,   854,   177,   178,   272,
     855,   857,    38,   858,   161,   190,   202,   212,   230,   864,
     264,   282,    31,   306,    32,   665,    33,   339,   284,   285,
     197,   210,   340,    30,   154,   155,    89,   113,   244,    42,
     284,   285,   162,   191,   203,   213,   231,    44,   265,   283,
     103,   307,   700,   104,   105,   114,   115,   188,   198,   211,
     229,   619,   270,   777,   365,   369,   778,   382,   244,   366,
     370,   868,   383,   113,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   195,   114,   115,   780,   243,    46,
     781,   114,   115,   385,   114,   115,   114,   115,   386,   114,
     115,   666,   602,   603,   604,   605,   598,   599,   171,    94,
     116,   117,   118,   119,   120,   244,    48,   245,   246,   392,
     420,   247,   248,   249,   393,   421,   121,   665,   672,   122,
     673,   783,   114,   115,   784,   606,   123,   701,   702,   703,
     704,   716,   717,    50,   124,   125,   972,    52,   126,   973,
     974,   975,    94,   823,   436,    54,   824,    90,   907,   437,
     908,   909,   853,    56,    58,   854,    91,    92,    93,   855,
     857,    60,   858,    86,    34,    35,    36,    37,   864,    94,
     439,   365,    94,    94,   439,   440,   744,    62,    94,   745,
     369,    94,   614,    94,   112,   746,    94,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   627,
     628,    64,    66,   762,   106,   107,   108,   109,   763,   244,
     762,   113,   794,   801,   324,   764,   674,   795,   802,    94,
     113,   163,   805,   164,   570,   571,   572,   806,   706,   114,
     115,   165,   166,   167,   168,   169,   170,   328,   114,   115,
     686,   687,   688,   689,   690,   691,   171,   172,   329,    95,
     113,   436,   970,   221,   173,   971,   807,   222,   223,   224,
     225,   226,   227,   204,   205,   206,   207,   208,   114,   115,
     244,   266,   245,   246,   267,   268,   382,   933,   420,   156,
     330,   930,   934,   938,   385,   171,   392,   114,   115,   947,
     175,   948,   174,   954,   987,   196,   331,   332,   955,   988,
     338,   161,   209,   344,   176,   401,   177,   178,   345,   939,
     940,   941,   228,   346,   190,   441,   442,   202,   920,   921,
     922,   923,   250,    94,   212,   347,    94,   269,   348,   162,
     362,   197,   271,   368,   230,    94,   376,   272,   210,   580,
     581,   582,   191,   377,   264,   203,   305,   443,   388,   282,
     390,   391,   213,   402,   453,   406,   188,   403,   410,   198,
     411,   412,   231,   414,   415,    94,   211,   417,   306,   416,
     422,   425,   265,   427,   428,   431,   229,   283,   106,   107,
     108,   109,   432,   111,    94,   113,   244,   114,   115,   433,
     270,   444,   445,   446,   447,   448,   307,   450,   451,   452,
     454,   455,   456,   114,   115,   457,   166,   167,   458,   169,
     170,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     171,   468,   469,   470,   471,   472,   473,   475,   173,   476,
     478,   479,   541,   542,   543,   480,   481,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   482,   484,   483,   156,   629,   629,   485,   486,   487,
     488,   490,   492,   493,   494,   495,   496,   498,   499,   500,
     705,   718,   305,   501,   502,   503,   161,   504,   506,   507,
     508,   509,   510,   511,    94,   512,   514,   518,   515,   519,
     516,   521,   707,   719,   306,   522,   523,   525,   524,   526,
      94,   528,   529,   527,   162,   594,   533,   534,   530,   536,
     538,   539,   751,   531,   540,   532,   544,   545,   637,   637,
     708,   720,   307,   546,   610,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   547,
     548,   549,   752,   552,    32,   553,   554,   555,   556,   557,
     558,   550,   739,   559,   560,   561,   562,   563,   565,   566,
     567,   575,   568,   569,   576,   609,   649,   753,   653,   657,
     601,   661,   679,   574,   682,   727,   731,   577,   735,   741,
     754,   578,   579,   755,   758,   583,   584,   585,   759,   760,
     586,   587,   588,   589,   590,   591,   592,   593,   595,   596,
     597,   761,   608,   767,   766,   769,   770,   772,   773,   776,
     775,   830,   787,   779,   786,   788,   789,   790,   791,   792,
     793,   798,   799,   800,   808,   813,   812,   815,   816,   818,
     819,   899,   821,   825,   826,   827,   828,   834,   829,   831,
     835,   889,   890,   895,   832,   833,   836,   837,   838,   896,
     898,   906,   937,   882,   839,   952,   931,   883,   884,   885,
     932,   936,   949,   957,   959,   961,   671,   964,   984,   886,
     887,   891,   629,   175,   925,   174,   892,   893,   250,   926,
     927,   269,   848,   928,   847,   929,   271,   176,   943,   177,
     178,   272,   869,   966,   985,   286,   849,   190,   850,   851,
     264,   986,   989,   282,   449,   613,   862,   944,   945,   648,
     840,   705,   946,   611,   872,   718,   960,   866,   867,   842,
     856,   196,   474,   950,   209,   191,   881,   228,   265,   880,
     963,   283,   910,   707,   863,   637,   991,   719,   965,   188,
     992,   477,   873,   202,   270,   994,   212,   852,   861,   230,
     990,   888,   841,   520,   912,   870,   871,   197,   489,   865,
     210,   708,   956,   844,   242,   720,   843,   846,   513,   901,
     845,   203,   900,   497,   213,   903,   902,   231,   879,   517,
     904,   491,   913,   905,   958,   198,   505,   897,   211,   894,
     725,   229,   612,   919,   962,   911,   982,   993,     0,   535,
       0,     0,     0,     0,     0,     0,     0,   537,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   848,     0,   847,     0,     0,     0,   869,     0,     0,
       0,     0,     0,     0,     0,   849,     0,   850,   851,     0,
       0,     0,     0,     0,   910,   862,     0,     0,     0,   872,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   856,
       0,     0,     0,     0,     0,     0,   912,     0,     0,     0,
       0,     0,     0,   863,     0,     0,     0,   873,     0,     0,
       0,     0,     0,     0,     0,     0,   852,   861,     0,     0,
     870,   871,     0,     0,   913,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   911
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    73,    72,    73,    74,    75,    76,   560,    78,    79,
      80,    81,   556,   774,    79,    73,   774,    73,    73,    79,
     774,   774,    16,   774,    72,    73,    74,    75,    76,   774,
      78,    79,     5,    81,     7,    81,     9,     3,    88,    89,
      74,    75,     8,     0,    12,    13,    10,    42,    43,     7,
      88,    89,    72,    73,    74,    75,    76,     7,    78,    79,
      11,    81,    16,    14,    15,    60,    61,    73,    74,    75,
      76,    25,    79,     3,     3,     3,     6,     3,    43,     8,
       8,    76,     8,    42,    35,    36,    37,    38,    39,    40,
      41,    42,    60,    61,    53,    60,    61,     3,    16,     7,
       6,    60,    61,     3,    60,    61,    60,    61,     8,    60,
      61,   157,   127,   128,   129,   130,   124,   125,    77,   157,
      71,    72,    73,    74,    75,    43,     7,    45,    46,     3,
       3,    49,    50,    51,     8,     8,    87,    81,    82,    90,
      84,     3,    60,    61,     6,   160,    97,   101,   102,   103,
     104,   107,   108,     7,   105,   106,   134,     7,   109,   137,
     138,   139,   157,     3,     3,     7,     6,   131,   133,     8,
     135,   136,   933,     7,     7,   933,   140,   141,   142,   933,
     933,     7,   933,   157,   157,   158,   159,   160,   933,   157,
       3,     3,   157,   157,     3,     8,     8,     7,   157,     8,
       3,   157,    16,   157,    41,     8,   157,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     7,     7,     3,    35,    36,    37,    38,     8,    43,
       3,    42,     3,     3,   132,     8,   780,     8,     8,   157,
      42,    52,     3,    54,    68,    69,    70,     8,   801,    60,
      61,    62,    63,    64,    65,    66,    67,     6,    60,    61,
      91,    92,    93,    94,    95,    96,    77,    78,     3,   339,
      42,     3,     3,    75,    85,     6,     8,    79,    80,    81,
      82,    83,    84,    55,    56,    57,    58,    59,    60,    61,
      43,    44,    45,    46,    47,    48,     3,     3,     3,   369,
       4,     8,     8,     8,     3,    77,     3,    60,    61,     8,
     382,     8,   382,     3,     3,   385,     8,     3,     8,     8,
       4,   369,   392,     4,   382,     8,   382,   382,     4,    98,
      99,   100,   402,     4,   382,   329,   330,   385,    17,    18,
      19,    20,   412,   157,   392,     4,   157,   417,     4,   369,
       4,   385,   417,     4,   402,   157,     4,   417,   392,   498,
     499,   500,   382,     4,   412,   385,   436,   157,     4,   417,
       4,     4,   392,     3,   158,     4,   382,     8,     4,   385,
       8,     3,   402,     4,     4,   157,   392,     3,   436,     8,
       4,     4,   412,     4,     4,     4,   402,   417,    35,    36,
      37,    38,     4,    40,   157,    42,    43,    60,    61,     4,
     417,     4,     4,     4,     4,     4,   436,     4,     4,     4,
     158,   158,   158,    60,    61,   158,    63,    64,     4,    66,
      67,     4,     4,     4,     4,     4,     4,     4,     4,     4,
      77,     4,     4,     4,   158,     4,     4,     4,    85,   160,
       4,     4,   446,   447,   448,     4,     4,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,     4,   160,   158,   544,   545,   546,     4,     4,     4,
       4,     4,     4,   158,     4,   158,   158,     4,     4,     4,
     560,   561,   562,     4,     4,     4,   544,     4,     4,     4,
     158,     4,     4,     4,   157,   160,     4,     4,   160,     4,
     160,   160,   560,   561,   562,     4,     4,     4,   158,   158,
     157,     4,     4,   158,   544,   519,     4,     4,   160,     4,
       4,     7,     4,   160,     7,   160,     7,     7,   545,   546,
     560,   561,   562,     7,   538,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     5,
       5,     5,     4,   157,     7,     5,     5,     5,     5,     5,
       5,   461,    86,     7,     7,     7,     7,     5,     5,     5,
     157,     5,   157,   157,     7,     5,     7,     4,     7,     7,
     126,     7,     7,   157,     7,     7,     7,   157,     7,     7,
       4,   157,   157,     4,     4,   157,   157,   157,     4,     4,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,     4,   157,     3,     6,     6,     3,     6,     3,     3,
       6,   160,     3,     6,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   157,     3,     6,     6,     3,     6,
       3,     3,     8,     4,     4,     4,     4,     4,   158,   158,
       4,     4,     4,     4,   160,   158,   158,   158,   158,     4,
       6,     4,     3,   158,   160,     4,     8,   158,   158,   158,
       8,     8,     8,     4,     4,     4,   555,     5,     4,   158,
     158,   158,   762,   765,   157,   765,   158,   158,   768,   157,
     157,   771,   774,   157,   774,   157,   771,   765,   157,   765,
     765,   771,   782,     7,     4,   785,   774,   765,   774,   774,
     768,     4,     4,   771,   339,   544,   774,   157,   157,   546,
     762,   801,   157,   539,   782,   805,   158,   777,   780,   767,
     774,   811,   365,   157,   814,   765,   787,   817,   768,   785,
     157,   771,   822,   801,   774,   762,   158,   805,   157,   765,
     158,   369,   782,   811,   771,   157,   814,   774,   774,   817,
     160,   794,   765,   420,   822,   782,   782,   811,   382,   776,
     814,   801,   933,   770,    77,   805,   768,   773,   412,   813,
     771,   811,   811,   392,   814,   816,   814,   817,   783,   417,
     817,   385,   822,   819,   937,   811,   402,   805,   814,   801,
     562,   817,   540,   823,   954,   822,   970,   987,    -1,   436,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   933,    -1,   933,    -1,    -1,    -1,   937,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   933,    -1,   933,   933,    -1,
      -1,    -1,    -1,    -1,   954,   933,    -1,    -1,    -1,   937,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   933,
      -1,    -1,    -1,    -1,    -1,    -1,   954,    -1,    -1,    -1,
      -1,    -1,    -1,   933,    -1,    -1,    -1,   937,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   933,   933,    -1,    -1,
     937,   937,    -1,    -1,   954,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   954
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
       0,     5,     7,     9,   157,   158,   159,   160,   177,   178,
     179,   184,     7,   193,     7,   199,     7,   210,     7,   291,
       7,   366,     7,   382,     7,   399,     7,   318,     7,   324,
       7,   348,     7,   267,     7,   456,     7,   491,   185,   180,
     194,   200,   211,   292,   367,   383,   400,   319,   325,   349,
     268,   457,   492,   177,   186,   187,   157,   182,   183,    10,
     131,   140,   141,   142,   157,   192,   195,   196,   197,   483,
     485,   487,   489,    11,    14,    15,    35,    36,    37,    38,
      39,    40,    41,    42,    60,    61,    71,    72,    73,    74,
      75,    87,    90,    97,   105,   106,   109,   192,   201,   202,
     203,   204,   205,   206,   207,   208,   217,   219,   247,   253,
     259,   261,   275,   285,   308,   316,   342,   372,   374,   422,
     433,   445,   446,   454,    12,    13,   192,   212,   213,   214,
     216,   372,   374,    52,    54,    62,    63,    64,    65,    66,
      67,    77,    78,    85,   192,   203,   204,   205,   206,   293,
     294,   295,   297,   299,   301,   303,   306,   307,   342,   360,
     372,   374,   376,   393,   418,    53,   192,   301,   342,   368,
     369,   370,   372,   374,    55,    56,    57,    58,    59,   192,
     301,   342,   372,   374,   384,   385,   386,   388,   389,   391,
     392,    75,    79,    80,    81,    82,    83,    84,   192,   342,
     372,   374,   401,   402,   403,   404,   406,   408,   410,   412,
     414,   416,   316,    16,    43,    45,    46,    49,    50,    51,
     192,   233,   326,   327,   328,   329,   330,   331,   332,   334,
     336,   338,   339,   341,   372,   374,    44,    47,    48,   192,
     233,   330,   336,   350,   351,   352,   353,   354,   356,   357,
     358,   359,   372,   374,    88,    89,   192,   269,   270,   271,
     273,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   192,   372,   374,   458,   459,
     460,   461,   463,   465,   466,   468,   469,   470,   473,   475,
     476,   477,   478,   481,   132,   493,   494,   495,     6,     3,
       4,     8,     3,   198,   490,   484,   486,   488,     4,     3,
       8,   209,   218,   220,     4,     4,     4,     4,     4,   286,
     317,   343,   373,   375,   309,   248,   260,   254,   423,   262,
     276,   434,     4,   447,   455,     3,     8,   215,     4,     3,
       8,   361,   377,   296,   298,   300,     4,     4,   304,   302,
     394,   419,     3,     8,   371,     3,     8,   387,     4,   390,
       4,     4,     3,     8,   417,   405,   407,   409,   411,   413,
     415,     8,     3,     8,   333,   234,     4,   337,   335,   340,
       4,     8,     3,   355,     4,     4,     8,     3,   272,   274,
       3,     8,     4,   462,   464,     4,   467,     4,     4,   471,
     474,     4,     4,     4,   479,   482,     3,     8,   496,     3,
       8,   177,   177,   157,     4,     4,     4,     4,     4,   196,
       4,     4,     4,   158,   158,   158,   158,   158,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   158,     4,     4,   202,     4,   160,   213,     4,     4,
       4,     4,     4,   158,   160,     4,     4,     4,     4,   294,
       4,   369,     4,   158,     4,   158,   158,   385,     4,     4,
       4,     4,     4,     4,     4,   403,     4,     4,   158,     4,
       4,     4,   160,   328,     4,   160,   160,   352,     4,     4,
     270,   160,     4,     4,   158,     4,   158,   158,     4,     4,
     160,   160,   160,     4,     4,   459,     4,   494,     4,     7,
       7,   177,   177,   177,     7,     7,     7,     5,     5,     5,
     179,   181,   157,     5,     5,     5,     5,     5,     5,     7,
       7,     7,     7,     5,   188,     5,     5,   157,   157,   157,
      68,    69,    70,   305,   157,     5,     7,   157,   157,   157,
     188,   188,   188,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   177,   157,   157,   157,   124,   125,
     472,   126,   127,   128,   129,   130,   160,   480,   157,     5,
     177,   201,   493,   212,    16,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,   192,
     221,   222,   223,   226,   228,   230,   232,   233,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   245,   221,     7,
     287,   288,   289,     7,   320,   321,   322,     7,   344,   345,
     346,     7,   310,   311,   312,    81,   157,   249,   250,   251,
     252,   186,    82,    84,   251,   255,   256,   257,   258,     7,
     424,   425,     7,   263,   264,   265,    91,    92,    93,    94,
      95,    96,   277,   278,   279,   280,   281,   282,   283,   284,
      16,   101,   102,   103,   104,   192,   235,   372,   374,   435,
     436,   437,   440,   441,   443,   444,   107,   108,   192,   372,
     374,   448,   449,   450,   452,   458,   189,     7,   362,   363,
     364,     7,   378,   379,   380,     7,   395,   396,   397,    86,
     420,     7,   497,   498,     8,     8,     8,   224,   227,   229,
     231,     4,     4,     4,     4,     4,   244,   246,     4,     4,
       4,     4,     3,     8,     8,   290,     6,     3,   323,     6,
       3,   347,     6,     3,   313,     6,     3,     3,     6,     6,
       3,     6,   426,     3,     6,   266,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   438,   442,     4,     4,
       4,     3,     8,   451,   453,     3,     8,     8,   157,   190,
     191,   365,     6,     3,   381,     6,     3,   398,     6,     3,
     421,     8,   499,     3,     6,     4,     4,     4,     4,   158,
     160,   158,   160,   158,     4,     4,   158,   158,   158,   160,
     222,   293,   289,   326,   322,   350,   346,   192,   203,   204,
     205,   206,   233,   285,   297,   299,   301,   303,   307,   314,
     315,   342,   372,   374,   418,   312,   250,   256,    76,   192,
     233,   342,   372,   374,   427,   428,   429,   430,   431,   425,
     269,   265,   158,   158,   158,   158,   158,   158,   278,     4,
       4,   158,   158,   158,   436,     4,     4,   449,     6,     3,
     368,   364,   384,   380,   401,   397,     4,   133,   135,   136,
     192,   233,   372,   374,   500,   501,   502,   503,   505,   498,
      17,    18,    19,    20,   225,   157,   157,   157,   157,   157,
       8,     8,     8,     3,     8,   432,     8,     3,     8,    98,
      99,   100,   439,   157,   157,   157,   157,     8,     8,     8,
     157,   506,     4,   504,     3,     8,   315,     4,   429,     4,
     158,     4,   501,   157,     5,   157,     7,   507,   508,   509,
       3,     6,   134,   137,   138,   139,   510,   511,   512,   514,
     515,   516,   508,   513,     4,     4,     4,     3,     8,     4,
     160,   158,   158,   511,   157
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   161,   163,   162,   164,   162,   165,   162,   166,   162,
     167,   162,   168,   162,   169,   162,   170,   162,   171,   162,
     172,   162,   173,   162,   174,   162,   175,   162,   176,   162,
     177,   177,   177,   177,   177,   177,   177,   178,   180,   179,
     181,   182,   182,   183,   183,   185,   184,   186,   186,   187,
     187,   189,   188,   190,   190,   191,   191,   192,   194,   193,
     195,   195,   196,   196,   196,   196,   196,   196,   198,   197,
     200,   199,   201,   201,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   203,
     204,   205,   206,   207,   209,   208,   211,   210,   212,   212,
     213,   213,   213,   213,   213,   215,   214,   216,   218,   217,
     220,   219,   221,   221,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   224,   223,   225,   225,   225,   225,   227,   226,   229,
     228,   231,   230,   232,   234,   233,   235,   236,   237,   238,
     239,   240,   241,   242,   244,   243,   246,   245,   248,   247,
     249,   249,   250,   250,   251,   252,   254,   253,   255,   255,
     256,   256,   256,   257,   258,   260,   259,   262,   261,   263,
     263,   264,   264,   266,   265,   268,   267,   269,   269,   269,
     270,   270,   272,   271,   274,   273,   276,   275,   277,   277,
     278,   278,   278,   278,   278,   278,   279,   280,   281,   282,
     283,   284,   286,   285,   287,   287,   288,   288,   290,   289,
     292,   291,   293,   293,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   296,   295,   298,   297,   300,   299,   302,
     301,   304,   303,   305,   305,   305,   306,   307,   309,   308,
     310,   310,   311,   311,   313,   312,   314,   314,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   317,   316,   319,   318,   320,   320,
     321,   321,   323,   322,   325,   324,   326,   326,   327,   327,
     328,   328,   328,   328,   328,   328,   328,   328,   328,   328,
     329,   330,   331,   333,   332,   335,   334,   337,   336,   338,
     340,   339,   341,   343,   342,   344,   344,   345,   345,   347,
     346,   349,   348,   350,   350,   351,   351,   352,   352,   352,
     352,   352,   352,   352,   352,   352,   353,   355,   354,   356,
     357,   358,   359,   361,   360,   362,   362,   363,   363,   365,
     364,   367,   366,   368,   368,   369,   369,   369,   369,   369,
     369,   371,   370,   373,   372,   375,   374,   377,   376,   378,
     378,   379,   379,   381,   380,   383,   382,   384,   384,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   387,
     386,   388,   390,   389,   391,   392,   394,   393,   395,   395,
     396,   396,   398,   397,   400,   399,   401,   401,   402,   402,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   405,   404,   407,   406,   409,   408,   411,   410,   413,
     412,   415,   414,   417,   416,   419,   418,   421,   420,   423,
     422,   424,   424,   426,   425,   427,   427,   428,   428,   429,
     429,   429,   429,   429,   429,   430,   432,   431,   434,   433,
     435,   435,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   438,   437,   439,   439,   439,   440,   442,   441,   443,
     444,   445,   447,   446,   448,   448,   449,   449,   449,   449,
     449,   451,   450,   453,   452,   455,   454,   457,   456,   458,
     458,   459,   459,   459,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   459,   459,   460,   462,
     461,   464,   463,   465,   467,   466,   468,   469,   471,   470,
     472,   472,   474,   473,   475,   476,   477,   479,   478,   480,
     480,   480,   480,   480,   482,   481,   484,   483,   486,   485,
     488,   487,   490,   489,   492,   491,   493,   493,   494,   496,
     495,   497,   497,   499,   498,   500,   500,   501,   501,   501,
     501,   501,   501,   501,   502,   504,   503,   506,   505,   507,
     507,   509,   508,   510,   510,   511,   511,   511,   511,   513,
     512,   514,   515,   516
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
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
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     3,     3,     3
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
  "\"keyspace\"", "\"reconnect-wait-time\"", "\"request-timeout\"",
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
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@31", "keyspace", "$@32", "mac_sources", "$@33",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
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
       0,   242,   242,   242,   243,   243,   244,   244,   245,   245,
     246,   246,   247,   247,   248,   248,   249,   249,   250,   250,
     251,   251,   252,   252,   253,   253,   254,   254,   255,   255,
     263,   264,   265,   266,   267,   268,   269,   272,   277,   277,
     288,   291,   292,   295,   299,   306,   306,   313,   314,   317,
     321,   328,   328,   335,   336,   339,   343,   354,   364,   364,
     379,   380,   384,   385,   386,   387,   388,   389,   392,   392,
     407,   407,   416,   417,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   449,
     454,   459,   464,   469,   474,   474,   485,   485,   494,   495,
     498,   499,   500,   501,   502,   505,   505,   515,   521,   521,
     533,   533,   545,   546,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   568,   568,   575,   576,   577,   578,   581,   581,   589,
     589,   597,   597,   605,   610,   610,   618,   623,   628,   633,
     638,   643,   648,   653,   658,   658,   666,   666,   675,   675,
     685,   686,   689,   690,   693,   698,   703,   703,   713,   714,
     717,   718,   719,   722,   727,   734,   734,   744,   744,   754,
     755,   758,   759,   762,   762,   772,   772,   782,   783,   784,
     787,   788,   791,   791,   799,   799,   807,   807,   818,   819,
     822,   823,   824,   825,   826,   827,   830,   835,   840,   845,
     850,   855,   863,   863,   876,   877,   880,   881,   888,   888,
     914,   914,   925,   926,   930,   931,   932,   933,   934,   935,
     936,   937,   938,   939,   940,   941,   942,   943,   944,   945,
     946,   947,   948,   951,   951,   959,   959,   967,   967,   975,
     975,   983,   983,   990,   991,   992,   995,  1000,  1008,  1008,
    1019,  1020,  1024,  1025,  1028,  1028,  1036,  1037,  1040,  1041,
    1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,
    1052,  1053,  1054,  1055,  1062,  1062,  1075,  1075,  1084,  1085,
    1088,  1089,  1094,  1094,  1109,  1109,  1123,  1124,  1127,  1128,
    1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,
    1143,  1145,  1150,  1152,  1152,  1160,  1160,  1168,  1168,  1176,
    1178,  1178,  1186,  1195,  1195,  1207,  1208,  1213,  1214,  1219,
    1219,  1231,  1231,  1243,  1244,  1249,  1250,  1255,  1256,  1257,
    1258,  1259,  1260,  1261,  1262,  1263,  1266,  1268,  1268,  1276,
    1278,  1280,  1285,  1293,  1293,  1305,  1306,  1309,  1310,  1313,
    1313,  1323,  1323,  1332,  1333,  1336,  1337,  1338,  1339,  1340,
    1341,  1344,  1344,  1352,  1352,  1377,  1377,  1407,  1407,  1419,
    1420,  1423,  1424,  1427,  1427,  1439,  1439,  1451,  1452,  1455,
    1456,  1457,  1458,  1459,  1460,  1461,  1462,  1463,  1464,  1467,
    1467,  1475,  1480,  1480,  1488,  1493,  1501,  1501,  1511,  1512,
    1515,  1516,  1519,  1519,  1528,  1528,  1537,  1538,  1541,  1542,
    1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,
    1556,  1559,  1559,  1569,  1569,  1579,  1579,  1587,  1587,  1595,
    1595,  1603,  1603,  1611,  1611,  1624,  1624,  1634,  1634,  1645,
    1645,  1655,  1656,  1659,  1659,  1669,  1670,  1673,  1674,  1677,
    1678,  1679,  1680,  1681,  1682,  1685,  1687,  1687,  1698,  1698,
    1710,  1711,  1714,  1715,  1716,  1717,  1718,  1719,  1720,  1721,
    1722,  1725,  1725,  1732,  1733,  1734,  1737,  1742,  1742,  1750,
    1755,  1762,  1769,  1769,  1779,  1780,  1783,  1784,  1785,  1786,
    1787,  1790,  1790,  1798,  1798,  1808,  1808,  1820,  1820,  1830,
    1831,  1834,  1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,
    1843,  1844,  1845,  1846,  1847,  1848,  1849,  1850,  1853,  1858,
    1858,  1866,  1866,  1874,  1879,  1879,  1887,  1892,  1897,  1897,
    1905,  1906,  1909,  1909,  1917,  1922,  1927,  1932,  1932,  1940,
    1943,  1946,  1949,  1952,  1958,  1958,  1968,  1968,  1975,  1975,
    1982,  1982,  1995,  1995,  2005,  2005,  2016,  2017,  2021,  2025,
    2025,  2037,  2038,  2042,  2042,  2050,  2051,  2054,  2055,  2056,
    2057,  2058,  2059,  2060,  2063,  2068,  2068,  2076,  2076,  2086,
    2087,  2090,  2090,  2098,  2099,  2102,  2103,  2104,  2105,  2108,
    2108,  2116,  2121,  2126
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
#line 4642 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2131 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
