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
      case 166: // value
      case 170: // map_value
      case 214: // db_type
      case 290: // hr_mode
      case 411: // duid_type
      case 444: // ncr_protocol_value
      case 452: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 151: // "boolean"
        value.move< bool > (that.value);
        break;

      case 150: // "floating point"
        value.move< double > (that.value);
        break;

      case 149: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 148: // "constant string"
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
      case 166: // value
      case 170: // map_value
      case 214: // db_type
      case 290: // hr_mode
      case 411: // duid_type
      case 444: // ncr_protocol_value
      case 452: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 151: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 150: // "floating point"
        value.copy< double > (that.value);
        break;

      case 149: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 148: // "constant string"
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
            case 148: // "constant string"

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 149: // "integer"

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 150: // "floating point"

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 151: // "boolean"

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 166: // value

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 170: // map_value

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 214: // db_type

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 290: // hr_mode

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 411: // duid_type

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 444: // ncr_protocol_value

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 452: // replace_client_name_value

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 166: // value
      case 170: // map_value
      case 214: // db_type
      case 290: // hr_mode
      case 411: // duid_type
      case 444: // ncr_protocol_value
      case 452: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 151: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 150: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 149: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 148: // "constant string"
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
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 818 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 288 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 306 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 328 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 332 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 343 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 658 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 758 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
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
    ctx.stack_.pop_back();
}
#line 1648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 897 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 907 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 973 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1010 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1025 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1146 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1174 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1200 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1281 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2593 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1685 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1729 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2998 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3166 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -502;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
      57,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,    75,    20,   118,   138,   169,   181,   198,
     218,   228,   248,   259,   274,   292,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
      20,  -109,    18,    27,    43,    19,    -2,    32,    85,    58,
      73,   -39,   136,  -502,    76,   269,   302,   300,   307,  -502,
    -502,  -502,  -502,   308,  -502,    29,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,   311,   312,   316,   317,   318,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,   319,
    -502,  -502,  -502,    99,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,   320,   121,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,   321,   322,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,   170,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,   171,  -502,  -502,
    -502,  -502,   323,  -502,   324,   325,  -502,  -502,  -502,   204,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,   303,   327,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,   328,  -502,  -502,
    -502,   330,  -502,  -502,   329,   332,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,   334,   335,  -502,
    -502,  -502,  -502,   333,   337,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,   205,  -502,  -502,  -502,   338,
    -502,  -502,   339,  -502,   340,   341,  -502,  -502,   342,   343,
     344,  -502,  -502,  -502,   206,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,    20,    20,  -502,   183,   345,   346,   347,   348,  -502,
      18,  -502,   349,   350,   351,   187,   207,   209,   210,   211,
     353,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     221,   367,   368,    27,  -502,   369,   225,    43,  -502,    -4,
     370,   371,   373,   374,   375,   231,   230,   378,   379,   380,
     381,    19,  -502,   382,   383,    -2,  -502,   384,   240,   386,
     242,   243,    32,  -502,   389,   390,   391,   392,   393,   394,
     395,  -502,    85,   396,   397,   256,   398,   399,   400,   258,
    -502,    58,   402,   260,   263,  -502,    73,   403,   404,   -52,
    -502,   264,   406,   412,   268,   414,   270,   271,   417,   418,
     272,   273,   275,   421,   423,   136,  -502,  -502,  -502,   424,
     422,   425,    20,    20,  -502,   426,   427,   428,  -502,  -502,
    -502,  -502,  -502,   431,   432,   433,   434,   435,   436,   439,
     440,   441,   442,  -502,   443,   444,  -502,   447,  -502,  -502,
    -502,  -502,  -502,  -502,   446,   453,  -502,  -502,  -502,   452,
     454,   282,   283,   310,  -502,  -502,    92,   313,   457,   456,
    -502,   326,   458,  -502,   331,  -502,   336,  -502,  -502,  -502,
     447,   447,   447,   352,   354,   355,   356,  -502,   366,   372,
    -502,   376,   377,   385,  -502,  -502,   387,  -502,  -502,  -502,
     388,    20,  -502,  -502,   401,   405,  -502,   407,  -502,  -502,
      13,   408,  -502,  -502,  -502,    26,   409,  -502,    20,    27,
     411,  -502,  -502,    43,   112,   112,   459,   460,   461,   -42,
      20,   229,    39,   462,    96,    24,    63,   136,  -502,  -502,
     466,  -502,    -4,   464,   465,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,   468,   410,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
     208,  -502,   212,  -502,  -502,   214,  -502,  -502,  -502,  -502,
     472,   473,   474,   476,   477,  -502,  -502,  -502,   215,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,   216,  -502,   479,   480,  -502,  -502,   481,   483,
    -502,  -502,   482,   486,  -502,  -502,  -502,    42,  -502,  -502,
    -502,   487,  -502,  -502,  -502,    86,  -502,  -502,  -502,  -502,
     184,  -502,   488,   489,  -502,   478,   491,   492,   493,   494,
     495,   223,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,   497,   501,   502,  -502,  -502,   224,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,   226,  -502,  -502,  -502,   251,
     413,   415,  -502,  -502,   503,   504,  -502,  -502,   505,   507,
    -502,  -502,   506,   510,  -502,  -502,   508,  -502,   511,   411,
    -502,  -502,   513,   514,   515,   517,   416,   419,   420,   429,
     430,   518,   519,   112,  -502,  -502,    19,  -502,   459,    58,
    -502,   460,    73,  -502,   461,   -42,  -502,  -502,   229,  -502,
      39,  -502,   -39,  -502,   462,   437,   438,   445,   448,   449,
     450,    96,  -502,   522,   523,   451,   455,   463,    24,  -502,
     525,   526,    63,  -502,  -502,  -502,   528,   529,  -502,    -2,
    -502,   464,    32,  -502,   465,    85,  -502,   468,   527,  -502,
     533,  -502,   257,   467,   469,   470,  -502,  -502,  -502,  -502,
    -502,   471,   475,  -502,   253,  -502,   531,  -502,   532,  -502,
    -502,  -502,  -502,   254,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,   195,   484,  -502,  -502,  -502,  -502,   485,   490,
    -502,  -502,   498,   255,  -502,   261,  -502,   534,  -502,   500,
     536,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,   233,  -502,
      62,   536,  -502,  -502,   537,  -502,  -502,  -502,   262,  -502,
    -502,  -502,  -502,  -502,   540,   509,   541,    62,  -502,   542,
    -502,   516,  -502,   539,  -502,  -502,   279,  -502,   -60,   539,
    -502,  -502,   544,   546,   547,   265,  -502,  -502,  -502,  -502,
    -502,  -502,   548,   520,   512,   521,   -60,  -502,   524,  -502,
    -502,  -502,  -502,  -502
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   211,    11,   318,    13,   338,    15,
     365,    17,   255,    19,   290,    21,   176,    23,   449,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   367,   257,
     292,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     500,   496,   498,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   107,   109,     0,     0,     0,     0,     0,   203,
     247,   282,   149,   166,   157,   398,   168,   187,   415,     0,
     437,   447,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   104,     0,     0,   100,
     102,   103,   402,   310,   330,   232,   234,   236,     0,     0,
     240,   238,   357,   394,   231,   215,   216,   217,   218,     0,
     213,   222,   223,   224,   227,   229,   225,   226,   219,   220,
     221,   228,   230,   326,   328,   325,   323,     0,   320,   322,
     324,   350,     0,   353,     0,     0,   349,   345,   348,     0,
     340,   342,   343,   346,   347,   344,   392,   380,   382,   384,
     386,   388,   390,   379,   378,     0,   368,   369,   373,   374,
     371,   375,   376,   377,   372,   272,   139,     0,   276,   274,
     279,     0,   268,   269,     0,   258,   259,   261,   271,   262,
     263,   264,   278,   265,   266,   267,   304,     0,     0,   302,
     303,   306,   307,     0,   293,   294,   296,   297,   298,   299,
     300,   301,   183,   185,   180,     0,   178,   181,   182,     0,
     469,   471,     0,   474,     0,     0,   478,   482,     0,     0,
       0,   487,   494,   467,     0,   451,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
      42,     0,     0,    35,     0,     0,     0,     0,     0,    53,
       0,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,     0,     0,     0,    99,   404,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   212,     0,     0,     0,   319,     0,     0,     0,
       0,     0,     0,   339,     0,     0,     0,     0,     0,     0,
       0,   366,     0,     0,     0,     0,     0,     0,     0,     0,
     256,     0,     0,     0,     0,   291,     0,     0,     0,     0,
     177,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   450,    46,    39,     0,
       0,     0,     0,     0,    57,     0,     0,     0,    91,    92,
      93,    94,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   436,     0,     0,    68,     0,   106,   101,
     413,   411,   412,   410,     0,   405,   406,   408,   409,     0,
       0,     0,     0,     0,   245,   246,     0,     0,     0,     0,
     214,     0,     0,   321,     0,   352,     0,   355,   356,   341,
       0,     0,     0,     0,     0,     0,     0,   370,     0,     0,
     270,     0,     0,     0,   281,   260,     0,   308,   309,   295,
       0,     0,   179,   468,     0,     0,   473,     0,   476,   477,
       0,     0,   484,   485,   486,     0,     0,   452,     0,     0,
       0,   497,   499,     0,     0,     0,   205,   249,   284,     0,
      43,     0,     0,   170,     0,     0,     0,     0,    47,   105,
       0,   403,     0,   312,   332,   233,   235,   237,   242,   243,
     244,   241,   239,   359,     0,   327,    36,   329,   351,   354,
     393,   381,   383,   385,   387,   389,   391,   273,   140,   277,
     275,   280,   305,   184,   186,   470,   472,   475,   480,   481,
     479,   483,   489,   490,   491,   492,   493,   488,   495,    40,
       0,   505,     0,   502,   504,     0,   126,   132,   134,   136,
       0,     0,     0,     0,     0,   145,   147,   125,     0,   111,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,     0,   209,     0,   206,   207,   253,     0,   250,
     251,   288,     0,   285,   286,   155,   156,     0,   151,   153,
     154,     0,   164,   165,   161,     0,   159,   162,   163,   400,
       0,   174,     0,   171,   172,     0,     0,     0,     0,     0,
       0,     0,   189,   191,   192,   193,   194,   195,   196,   426,
     432,     0,     0,     0,   425,   424,     0,   417,   419,   422,
     420,   421,   423,   443,   445,     0,   439,   441,   442,     0,
      49,     0,   407,   316,     0,   313,   314,   336,     0,   333,
     334,   363,     0,   360,   361,   396,     0,    64,     0,     0,
     501,    97,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   108,   110,     0,   204,     0,   257,
     248,     0,   292,   283,     0,     0,   150,   167,     0,   158,
       0,   399,     0,   169,     0,     0,     0,     0,     0,     0,
       0,     0,   188,     0,     0,     0,     0,     0,     0,   416,
       0,     0,     0,   438,   448,    51,     0,    50,   414,     0,
     311,     0,     0,   331,     0,   367,   358,     0,     0,   395,
       0,   503,     0,     0,     0,     0,   138,   141,   142,   143,
     144,     0,     0,   112,     0,   208,     0,   252,     0,   287,
     152,   160,   401,     0,   173,   197,   198,   199,   200,   201,
     202,   190,     0,     0,   431,   434,   435,   418,     0,     0,
     440,    48,     0,     0,   315,     0,   335,     0,   362,     0,
       0,   128,   129,   130,   131,   127,   133,   135,   137,   146,
     148,   210,   254,   289,   175,   428,   429,   430,   427,   433,
     444,   446,    52,   317,   337,   364,   397,   509,     0,   507,
       0,     0,   506,   521,     0,   519,   517,   513,     0,   511,
     515,   516,   514,   508,     0,     0,     0,     0,   510,     0,
     518,     0,   512,     0,   520,   525,     0,   523,     0,     0,
     522,   533,     0,     0,     0,     0,   527,   529,   530,   531,
     532,   524,     0,     0,     0,     0,     0,   526,     0,   535,
     536,   537,   528,   534
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,    10,  -502,   102,  -502,  -502,  -502,
    -502,  -502,  -502,    46,  -502,  -167,  -502,  -502,  -502,   -62,
    -502,  -502,  -502,   266,  -502,  -502,  -502,  -502,    59,   236,
     -63,   -50,   -44,   -43,  -502,  -502,  -502,  -502,  -502,    61,
     235,  -502,  -502,  -502,  -502,  -502,  -502,  -502,    55,  -136,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
     -58,  -502,  -501,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -147,  -488,  -502,  -502,  -502,  -502,  -146,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -153,  -502,
    -502,  -502,  -149,   196,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -157,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -132,  -502,  -502,  -502,  -129,   237,  -502,  -502,
    -502,  -502,  -502,  -502,  -492,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -130,  -502,  -502,  -502,  -127,
    -502,   213,  -502,   -59,  -502,  -502,  -502,  -502,  -502,   -57,
    -502,  -502,  -502,  -502,  -502,   -49,  -502,  -502,  -502,  -131,
    -502,  -502,  -502,  -124,  -502,   217,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -166,  -502,  -502,
    -502,  -160,   245,  -502,  -502,   -66,  -502,  -502,  -502,  -502,
    -502,  -163,  -502,  -502,  -502,  -156,   249,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -165,  -502,
    -502,  -502,  -152,  -502,   244,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,    80,
    -502,  -502,  -502,  -502,  -502,  -502,  -143,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -137,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,    90,   219,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
    -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,  -502,
     -81,  -502,  -502,  -502,  -232,  -502,  -502,  -247,  -502,  -502,
    -502,  -502,  -502,  -502,  -258,  -502,  -502,  -273,  -502,  -502,
    -502,  -502,  -502
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   537,    77,
      78,    37,    60,    74,    75,   519,   670,   746,   747,   112,
      39,    62,    85,    86,    87,   295,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   302,    43,    64,   138,
     139,   140,   325,   141,   121,   303,   122,   304,   588,   589,
     590,   692,   815,   591,   693,   592,   694,   593,   695,   594,
     223,   364,   596,   597,   598,   599,   600,   701,   601,   702,
     123,   313,   617,   618,   619,   620,   124,   315,   625,   626,
     627,   628,   125,   314,   126,   317,   632,   633,   634,   722,
      57,    71,   255,   256,   257,   377,   258,   378,   127,   318,
     641,   642,   643,   644,   645,   646,   647,   648,   128,   310,
     604,   605,   606,   706,    45,    65,   159,   160,   161,   332,
     162,   333,   163,   334,   164,   338,   165,   337,   531,   166,
     167,   129,   311,   608,   609,   610,   709,    53,    69,   224,
     225,   226,   227,   228,   229,   230,   363,   231,   367,   232,
     366,   233,   234,   368,   235,   130,   312,   612,   613,   614,
     712,    55,    70,   243,   244,   245,   246,   247,   372,   248,
     249,   250,   251,   169,   330,   674,   675,   676,   749,    47,
      66,   177,   178,   179,   343,   180,   344,   170,   331,   678,
     679,   680,   752,    49,    67,   189,   190,   191,   347,   192,
     193,   349,   194,   195,   171,   339,   682,   683,   684,   755,
      51,    68,   205,   206,   207,   208,   355,   209,   356,   210,
     357,   211,   358,   212,   359,   213,   360,   214,   354,   172,
     340,   686,   758,   131,   316,   630,   329,   434,   435,   436,
     437,   438,   520,   132,   319,   656,   657,   658,   733,   828,
     659,   660,   734,   661,   662,   133,   134,   321,   665,   666,
     667,   740,   668,   741,   135,   322,    59,    72,   274,   275,
     276,   277,   382,   278,   383,   279,   280,   385,   281,   282,
     283,   388,   560,   284,   389,   285,   286,   287,   288,   393,
     567,   289,   394,    88,   297,    89,   298,    90,   296,   572,
     573,   574,   688,   838,   839,   840,   848,   849,   850,   851,
     856,   852,   854,   866,   867,   868,   875,   876,   877,   882,
     878,   879,   880
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   188,   155,   154,   175,   186,   203,   222,   239,   254,
     273,   241,   240,   242,   655,   156,   168,   176,   187,   204,
     629,   157,   158,   624,    34,    27,   142,    28,    79,    29,
     252,   253,   300,   615,   101,   216,   101,   301,    91,    76,
     649,    92,    93,   252,   253,   715,   142,   173,   716,   581,
      94,    95,    96,    97,   174,   136,   137,   101,    94,    95,
      96,    97,    98,    99,   100,   101,   430,   143,   871,   144,
     101,   872,   873,   874,   215,    26,   145,   146,   147,   148,
     149,   150,   290,   181,   182,   183,   184,   185,   174,   718,
     151,   152,   719,   102,   103,   104,   105,   216,   153,   217,
     218,   216,   323,   219,   220,   221,   616,   324,   106,    83,
     151,   107,   216,   236,   217,   218,   237,   238,   108,   650,
     651,   652,   653,   101,   327,    38,   109,   110,   576,   328,
     111,   558,   559,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   586,    80,    83,    40,    83,   562,   563,   564,
     565,   216,    81,    82,   196,   528,   529,   530,   197,   198,
     199,   200,   201,   202,   663,   664,    83,    83,    30,    31,
      32,    33,    83,   341,   345,    83,    42,   566,   342,   346,
      83,   635,   636,   637,   638,   639,   640,   720,    44,   843,
     721,   844,   845,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    46,    83,   352,   379,   395,
      83,   323,   353,   380,   396,   689,   687,   327,   703,   703,
     690,    83,   691,   704,   705,    48,   731,   738,   782,   742,
     624,   732,   739,    83,   743,    50,   841,   655,    84,   842,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   395,    52,   341,   379,   345,   744,
      83,   821,   824,   833,   352,   857,    54,   431,   886,   834,
     858,   432,   291,   887,   811,   812,   813,   814,   155,   154,
     433,    56,   869,   175,    83,   870,   188,   825,   826,   827,
     186,   156,   168,   540,   541,   542,   176,   157,   158,    58,
     203,   397,   398,   187,   615,   622,   292,   623,   293,   222,
     294,   361,   299,   204,   239,   305,   306,   241,   240,   242,
     307,   308,   309,   320,   326,   335,   336,   348,   350,   351,
     362,   399,   365,   273,   369,   371,   408,   370,   373,   374,
     376,   375,   381,   384,   386,   387,   390,   391,   392,   400,
     401,   402,   403,   405,   406,   407,   409,   413,   410,   411,
     412,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   427,   439,   440,   428,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   451,   452,   454,   455,
     456,   457,   458,   460,   461,   462,   463,   464,   465,   466,
     468,   469,   471,   472,   473,   470,   476,   480,   481,   474,
     484,   477,   501,   502,   478,   483,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   495,   494,   496,   498,   499,
     525,   526,   500,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   587,   587,   512,   513,   595,   595,   514,   515,
     516,   517,   518,   654,   521,   273,   522,   523,   527,   524,
     431,   532,   533,   534,   432,    28,   603,   607,   611,   631,
     671,   673,   677,   433,   535,   681,   696,   697,   698,   538,
     699,   700,   725,   708,   539,   707,   711,   710,   713,   714,
     685,   554,   724,   717,   723,   726,   727,   728,   729,   730,
     543,   735,   544,   545,   546,   736,   737,   751,   569,   750,
     754,   753,   756,   757,   547,   760,   759,   762,   763,   764,
     548,   765,   771,   772,   549,   550,   792,   793,   561,   798,
     799,   809,   802,   551,   801,   552,   553,   571,   810,   822,
     823,   855,   835,   837,   859,   861,   865,   863,   883,   555,
     884,   885,   888,   556,   536,   557,   621,   568,   570,   426,
     602,   745,   429,   748,   575,   766,   404,   773,   780,   768,
     767,   784,   781,   783,   791,   482,   775,   774,   450,   770,
     769,   777,   776,   779,   475,   804,   785,   786,   778,   803,
     453,   806,   808,   479,   787,   797,   805,   788,   789,   790,
     794,   459,   672,   807,   795,   800,   467,   669,   761,   853,
     862,   881,   796,   892,   497,   816,     0,   817,   818,   819,
       0,     0,     0,   820,     0,     0,     0,     0,     0,     0,
       0,     0,   829,   830,     0,     0,     0,     0,   831,     0,
       0,   587,     0,   155,   154,   595,   832,   222,   836,     0,
     239,     0,     0,   241,   240,   242,   156,   168,   860,     0,
     254,   890,   157,   158,   864,     0,     0,     0,     0,     0,
     891,   889,   893,     0,     0,     0,   654,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   188,   175,     0,     0,
     186,     0,     0,   203,     0,     0,     0,     0,     0,     0,
     176,     0,     0,   187,     0,     0,   204,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   846,     0,
       0,     0,   847,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   846,     0,     0,     0,   847
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   515,    65,    65,    66,    67,    68,
     512,    65,    65,   511,    14,     5,     7,     7,    10,     9,
      82,    83,     3,    75,    38,    39,    38,     8,    11,   148,
      16,    14,    15,    82,    83,     3,     7,    49,     6,    25,
      31,    32,    33,    34,    56,    12,    13,    38,    31,    32,
      33,    34,    35,    36,    37,    38,    70,    48,   128,    50,
      38,   131,   132,   133,    16,     0,    57,    58,    59,    60,
      61,    62,     6,    51,    52,    53,    54,    55,    56,     3,
      71,    72,     6,    66,    67,    68,    69,    39,    79,    41,
      42,    39,     3,    45,    46,    47,   148,     8,    81,   148,
      71,    84,    39,    40,    41,    42,    43,    44,    91,    95,
      96,    97,    98,    38,     3,     7,    99,   100,    16,     8,
     103,   118,   119,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   125,   148,     7,   148,   121,   122,   123,
     124,    39,   134,   135,    69,    63,    64,    65,    73,    74,
      75,    76,    77,    78,   101,   102,   148,   148,   148,   149,
     150,   151,   148,     3,     3,   148,     7,   151,     8,     8,
     148,    85,    86,    87,    88,    89,    90,     3,     7,   127,
       6,   129,   130,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,     7,   148,     3,     3,     3,
     148,     3,     8,     8,     8,     3,     8,     3,     3,     3,
       8,   148,     8,     8,     8,     7,     3,     3,   720,     3,
     718,     8,     8,   148,     8,     7,     3,   738,   300,     6,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,     3,     7,     3,     3,     3,     8,
     148,     8,     8,     8,     3,     3,     7,   329,     3,     8,
       8,   329,     3,     8,    17,    18,    19,    20,   341,   341,
     329,     7,     3,   345,   148,     6,   352,    92,    93,    94,
     352,   341,   341,   460,   461,   462,   345,   341,   341,     7,
     362,   291,   292,   352,    75,    76,     4,    78,     8,   371,
       3,     8,     4,   362,   376,     4,     4,   376,   376,   376,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   148,     4,   395,     4,     3,   149,     8,     4,     4,
       3,     8,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   149,     4,   149,   149,
     149,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     149,     4,     4,     4,     4,     4,   151,     4,     4,     4,
     149,   151,     4,     4,     4,     4,     4,     4,     4,   149,
       4,   149,   149,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   149,     4,     4,     4,   151,
       4,   151,   402,   403,   151,   151,     4,   149,     4,   149,
     149,     4,     4,   151,   151,     4,   151,     4,     4,     7,
     148,   148,     7,     7,     7,     7,     5,     5,     5,     5,
       5,     5,   504,   505,     5,     5,   504,   505,     7,     7,
       7,     7,     5,   515,     8,   517,     3,     5,   148,     5,
     522,   148,     5,     7,   522,     7,     7,     7,     7,     7,
       4,     7,     7,   522,   148,     7,     4,     4,     4,   148,
       4,     4,     4,     3,   148,     6,     3,     6,     6,     3,
      80,   481,     3,     6,     6,     4,     4,     4,     4,     4,
     148,     4,   148,   148,   148,     4,     4,     3,   498,     6,
       3,     6,     6,     3,   148,     4,     8,     4,     4,     4,
     148,     4,     4,     4,   148,   148,     4,     4,   120,     4,
       4,     4,     3,   148,     6,   148,   148,   126,     5,     8,
       8,     4,     8,     7,     4,     4,     7,     5,     4,   148,
       4,     4,     4,   148,   452,   148,   510,   148,   499,   323,
     505,   148,   327,   148,   503,   149,   300,   703,   715,   149,
     151,   724,   718,   722,   731,   379,   708,   706,   341,   149,
     151,   711,   709,   714,   371,   751,   149,   149,   712,   749,
     345,   754,   757,   376,   149,   738,   752,   149,   149,   149,
     149,   352,   522,   755,   149,   742,   362,   517,   689,   841,
     857,   869,   149,   886,   395,   148,    -1,   148,   148,   148,
      -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   148,    -1,    -1,    -1,    -1,   148,    -1,
      -1,   703,    -1,   706,   706,   703,   148,   709,   148,    -1,
     712,    -1,    -1,   712,   712,   712,   706,   706,   149,    -1,
     722,   149,   706,   706,   148,    -1,    -1,    -1,    -1,    -1,
     149,   151,   148,    -1,    -1,    -1,   738,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   752,   749,    -1,    -1,
     752,    -1,    -1,   755,    -1,    -1,    -1,    -1,    -1,    -1,
     749,    -1,    -1,   752,    -1,    -1,   755,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   840,    -1,
      -1,    -1,   840,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   857,    -1,    -1,    -1,   857
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     0,     5,     7,     9,
     148,   149,   150,   151,   166,   167,   168,   173,     7,   182,
       7,   188,     7,   199,     7,   276,     7,   341,     7,   355,
       7,   372,     7,   299,     7,   323,     7,   252,     7,   428,
     174,   169,   183,   189,   200,   277,   342,   356,   373,   300,
     324,   253,   429,   166,   175,   176,   148,   171,   172,    10,
     125,   134,   135,   148,   181,   184,   185,   186,   455,   457,
     459,    11,    14,    15,    31,    32,    33,    34,    35,    36,
      37,    38,    66,    67,    68,    69,    81,    84,    91,    99,
     100,   103,   181,   190,   191,   192,   193,   194,   195,   196,
     197,   206,   208,   232,   238,   244,   246,   260,   270,   293,
     317,   395,   405,   417,   418,   426,    12,    13,   201,   202,
     203,   205,     7,    48,    50,    57,    58,    59,    60,    61,
      62,    71,    72,    79,   181,   192,   193,   194,   195,   278,
     279,   280,   282,   284,   286,   288,   291,   292,   317,   335,
     349,   366,   391,    49,    56,   181,   317,   343,   344,   345,
     347,    51,    52,    53,    54,    55,   181,   317,   347,   357,
     358,   359,   361,   362,   364,   365,    69,    73,    74,    75,
      76,    77,    78,   181,   317,   374,   375,   376,   377,   379,
     381,   383,   385,   387,   389,    16,    39,    41,    42,    45,
      46,    47,   181,   222,   301,   302,   303,   304,   305,   306,
     307,   309,   311,   313,   314,   316,    40,    43,    44,   181,
     222,   305,   311,   325,   326,   327,   328,   329,   331,   332,
     333,   334,    82,    83,   181,   254,   255,   256,   258,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   181,   430,   431,   432,   433,   435,   437,
     438,   440,   441,   442,   445,   447,   448,   449,   450,   453,
       6,     3,     4,     8,     3,   187,   460,   456,   458,     4,
       3,     8,   198,   207,   209,     4,     4,     4,     4,     4,
     271,   294,   318,   233,   245,   239,   396,   247,   261,   406,
       4,   419,   427,     3,     8,   204,     4,     3,     8,   398,
     336,   350,   281,   283,   285,     4,     4,   289,   287,   367,
     392,     3,     8,   346,   348,     3,     8,   360,     4,   363,
       4,     4,     3,     8,   390,   378,   380,   382,   384,   386,
     388,     8,     3,   308,   223,     4,   312,   310,   315,     4,
       8,     3,   330,     4,     4,     8,     3,   257,   259,     3,
       8,     4,   434,   436,     4,   439,     4,     4,   443,   446,
       4,     4,     4,   451,   454,     3,     8,   166,   166,   148,
       4,     4,     4,     4,   185,     4,     4,     4,   149,   149,
     149,   149,   149,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   149,     4,     4,   191,     4,   151,   202,
      70,   181,   222,   317,   399,   400,   401,   402,   403,     4,
       4,     4,     4,     4,   149,   151,     4,     4,     4,     4,
     279,     4,     4,   344,     4,   149,     4,   149,   149,   358,
       4,     4,     4,     4,     4,     4,     4,   376,     4,     4,
     149,     4,     4,     4,   151,   303,     4,   151,   151,   327,
       4,     4,   255,   151,     4,     4,   149,     4,   149,   149,
       4,     4,   151,   151,   151,     4,     4,   431,     4,     7,
       7,   166,   166,     7,     7,     7,     5,     5,     5,     5,
       5,     5,     5,     5,     7,     7,     7,     7,     5,   177,
     404,     8,     3,     5,     5,   148,   148,   148,    63,    64,
      65,   290,   148,     5,     7,   148,   168,   170,   148,   148,
     177,   177,   177,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   166,   148,   148,   148,   118,   119,
     444,   120,   121,   122,   123,   124,   151,   452,   148,   166,
     190,   126,   461,   462,   463,   201,    16,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,   181,   210,   211,
     212,   215,   217,   219,   221,   222,   224,   225,   226,   227,
     228,   230,   210,     7,   272,   273,   274,     7,   295,   296,
     297,     7,   319,   320,   321,    75,   148,   234,   235,   236,
     237,   175,    76,    78,   236,   240,   241,   242,   243,   286,
     397,     7,   248,   249,   250,    85,    86,    87,    88,    89,
      90,   262,   263,   264,   265,   266,   267,   268,   269,    16,
      95,    96,    97,    98,   181,   224,   407,   408,   409,   412,
     413,   415,   416,   101,   102,   420,   421,   422,   424,   430,
     178,     4,   401,     7,   337,   338,   339,     7,   351,   352,
     353,     7,   368,   369,   370,    80,   393,     8,   464,     3,
       8,     8,   213,   216,   218,   220,     4,     4,     4,     4,
       4,   229,   231,     3,     8,     8,   275,     6,     3,   298,
       6,     3,   322,     6,     3,     3,     6,     6,     3,     6,
       3,     6,   251,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   410,   414,     4,     4,     4,     3,     8,
     423,   425,     3,     8,     8,   148,   179,   180,   148,   340,
       6,     3,   354,     6,     3,   371,     6,     3,   394,     8,
       4,   462,     4,     4,     4,     4,   149,   151,   149,   151,
     149,     4,     4,   211,   278,   274,   301,   297,   325,   321,
     235,   241,   286,   254,   250,   149,   149,   149,   149,   149,
     149,   263,     4,     4,   149,   149,   149,   408,     4,     4,
     421,     6,     3,   343,   339,   357,   353,   374,   370,     4,
       5,    17,    18,    19,    20,   214,   148,   148,   148,   148,
     148,     8,     8,     8,     8,    92,    93,    94,   411,   148,
     148,   148,   148,     8,     8,     8,   148,     7,   465,   466,
     467,     3,     6,   127,   129,   130,   181,   222,   468,   469,
     470,   471,   473,   466,   474,     4,   472,     3,     8,     4,
     149,     4,   469,     5,   148,     7,   475,   476,   477,     3,
       6,   128,   131,   132,   133,   478,   479,   480,   482,   483,
     484,   476,   481,     4,     4,     4,     3,     8,     4,   151,
     149,   149,   479,   148
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   152,   154,   153,   155,   153,   156,   153,   157,   153,
     158,   153,   159,   153,   160,   153,   161,   153,   162,   153,
     163,   153,   164,   153,   165,   153,   166,   166,   166,   166,
     166,   166,   166,   167,   169,   168,   170,   171,   171,   172,
     172,   174,   173,   175,   175,   176,   176,   178,   177,   179,
     179,   180,   180,   181,   183,   182,   184,   184,   185,   185,
     185,   185,   185,   187,   186,   189,   188,   190,   190,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   192,   193,   194,   195,   196,   198,   197,   200,   199,
     201,   201,   202,   202,   204,   203,   205,   207,   206,   209,
     208,   210,   210,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   213,   212,   214,   214,
     214,   214,   216,   215,   218,   217,   220,   219,   221,   223,
     222,   224,   225,   226,   227,   229,   228,   231,   230,   233,
     232,   234,   234,   235,   235,   236,   237,   239,   238,   240,
     240,   241,   241,   241,   242,   243,   245,   244,   247,   246,
     248,   248,   249,   249,   251,   250,   253,   252,   254,   254,
     254,   255,   255,   257,   256,   259,   258,   261,   260,   262,
     262,   263,   263,   263,   263,   263,   263,   264,   265,   266,
     267,   268,   269,   271,   270,   272,   272,   273,   273,   275,
     274,   277,   276,   278,   278,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   281,   280,   283,   282,   285,   284,   287,   286,
     289,   288,   290,   290,   290,   291,   292,   294,   293,   295,
     295,   296,   296,   298,   297,   300,   299,   301,   301,   302,
     302,   303,   303,   303,   303,   303,   303,   303,   303,   304,
     305,   306,   308,   307,   310,   309,   312,   311,   313,   315,
     314,   316,   318,   317,   319,   319,   320,   320,   322,   321,
     324,   323,   325,   325,   326,   326,   327,   327,   327,   327,
     327,   327,   327,   328,   330,   329,   331,   332,   333,   334,
     336,   335,   337,   337,   338,   338,   340,   339,   342,   341,
     343,   343,   344,   344,   344,   344,   346,   345,   348,   347,
     350,   349,   351,   351,   352,   352,   354,   353,   356,   355,
     357,   357,   358,   358,   358,   358,   358,   358,   358,   358,
     360,   359,   361,   363,   362,   364,   365,   367,   366,   368,
     368,   369,   369,   371,   370,   373,   372,   374,   374,   375,
     375,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     378,   377,   380,   379,   382,   381,   384,   383,   386,   385,
     388,   387,   390,   389,   392,   391,   394,   393,   396,   395,
     397,   397,   398,   286,   399,   399,   400,   400,   401,   401,
     401,   401,   402,   404,   403,   406,   405,   407,   407,   408,
     408,   408,   408,   408,   408,   408,   410,   409,   411,   411,
     411,   412,   414,   413,   415,   416,   417,   419,   418,   420,
     420,   421,   421,   423,   422,   425,   424,   427,   426,   429,
     428,   430,   430,   431,   431,   431,   431,   431,   431,   431,
     431,   431,   431,   431,   431,   431,   431,   431,   432,   434,
     433,   436,   435,   437,   439,   438,   440,   441,   443,   442,
     444,   444,   446,   445,   447,   448,   449,   451,   450,   452,
     452,   452,   452,   452,   454,   453,   456,   455,   458,   457,
     460,   459,   461,   461,   462,   464,   463,   465,   465,   467,
     466,   468,   468,   469,   469,   469,   469,   469,   470,   472,
     471,   474,   473,   475,   475,   477,   476,   478,   478,   479,
     479,   479,   479,   481,   480,   482,   483,   484
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     0,     1,     3,
       5,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     4,     3,     0,     6,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     3,     0,
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
  "\"keyspace\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"mac-sources\"",
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
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "value", "sub_json", "map2", "$@13", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@14", "list_content",
  "not_empty_list", "list_strings", "$@15", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@16",
  "global_objects", "global_object", "dhcp6_object", "$@17", "sub_dhcp6",
  "$@18", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@19",
  "sub_interfaces6", "$@20", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@21", "re_detect",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "database_type", "$@24",
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "port",
  "name", "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@29", "keyspace", "$@30", "mac_sources", "$@31",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@32",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@33",
  "hooks_libraries", "$@34", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@35",
  "sub_hooks_library", "$@36", "hooks_params", "hooks_param", "library",
  "$@37", "parameters", "$@38", "expired_leases_processing", "$@39",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@40",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@41",
  "sub_subnet6", "$@42", "subnet6_params", "subnet6_param", "subnet",
  "$@43", "interface", "$@44", "interface_id", "$@45", "client_class",
  "$@46", "reservation_mode", "$@47", "hr_mode", "id", "rapid_commit",
  "option_def_list", "$@48", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@49",
  "sub_option_def", "$@50", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@51",
  "option_def_record_types", "$@52", "space", "$@53", "option_def_space",
  "option_def_encapsulate", "$@54", "option_def_array", "option_data_list",
  "$@55", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@56", "sub_option_data", "$@57",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@58",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@59", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@60", "sub_pool6", "$@61",
  "pool_params", "pool_param", "pool_entry", "$@62", "user_context",
  "$@63", "pd_pools_list", "$@64", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@65", "sub_pd_pool",
  "$@66", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@67",
  "pd_prefix_len", "excluded_prefix", "$@68", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@69", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@70", "sub_reservation",
  "$@71", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@72", "prefixes", "$@73", "duid",
  "$@74", "hw_address", "$@75", "hostname", "$@76", "flex_id_value",
  "$@77", "reservation_client_classes", "$@78", "relay", "$@79",
  "relay_map", "$@80", "client_classes", "$@81", "client_classes_list",
  "$@82", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@83",
  "server_id", "$@84", "server_id_params", "server_id_param",
  "server_id_type", "$@85", "duid_type", "htype", "identifier", "$@86",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@87",
  "control_socket_params", "control_socket_param", "socket_type", "$@88",
  "socket_name", "$@89", "dhcp_ddns", "$@90", "sub_dhcp_ddns", "$@91",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@92", "server_ip", "$@93", "server_port",
  "sender_ip", "$@94", "sender_port", "max_queue_size", "ncr_protocol",
  "$@95", "ncr_protocol_value", "ncr_format", "$@96",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@97", "replace_client_name_value",
  "generated_prefix", "$@98", "dhcp4_json_object", "$@99",
  "dhcpddns_json_object", "$@100", "logging_object", "$@101",
  "logging_params", "logging_param", "loggers", "$@102", "loggers_entries",
  "logger_entry", "$@103", "logger_params", "logger_param", "debuglevel",
  "severity", "$@104", "output_options_list", "$@105",
  "output_options_list_content", "output_entry", "$@106",
  "output_params_list", "output_params", "output", "$@107", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   233,   233,   233,   234,   234,   235,   235,   236,   236,
     237,   237,   238,   238,   239,   239,   240,   240,   241,   241,
     242,   242,   243,   243,   244,   244,   252,   253,   254,   255,
     256,   257,   258,   261,   266,   266,   277,   280,   281,   284,
     288,   295,   295,   302,   303,   306,   310,   317,   317,   324,
     325,   328,   332,   343,   353,   353,   365,   366,   370,   371,
     372,   373,   374,   377,   377,   394,   394,   402,   403,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   432,   437,   442,   447,   452,   457,   457,   467,   467,
     475,   476,   479,   480,   483,   483,   493,   499,   499,   509,
     509,   519,   520,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   538,   538,   545,   546,
     547,   548,   551,   551,   559,   559,   567,   567,   575,   580,
     580,   588,   593,   598,   603,   608,   608,   616,   616,   625,
     625,   635,   636,   639,   640,   643,   648,   653,   653,   663,
     664,   667,   668,   669,   672,   677,   684,   684,   694,   694,
     704,   705,   708,   709,   712,   712,   720,   720,   728,   729,
     730,   733,   734,   737,   737,   745,   745,   753,   753,   763,
     764,   767,   768,   769,   770,   771,   772,   775,   780,   785,
     790,   795,   800,   808,   808,   821,   822,   825,   826,   833,
     833,   856,   856,   865,   866,   870,   871,   872,   873,   874,
     875,   876,   877,   878,   879,   880,   881,   882,   883,   884,
     885,   886,   889,   889,   897,   897,   905,   905,   913,   913,
     921,   921,   928,   929,   930,   933,   938,   947,   947,   959,
     960,   963,   964,   969,   969,   980,   980,   990,   991,   994,
     995,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1008,
    1010,  1015,  1017,  1017,  1025,  1025,  1033,  1033,  1041,  1043,
    1043,  1051,  1060,  1060,  1072,  1073,  1078,  1079,  1084,  1084,
    1095,  1095,  1106,  1107,  1112,  1113,  1118,  1119,  1120,  1121,
    1122,  1123,  1124,  1127,  1129,  1129,  1137,  1139,  1141,  1146,
    1154,  1154,  1166,  1167,  1170,  1171,  1174,  1174,  1182,  1182,
    1190,  1191,  1194,  1195,  1196,  1197,  1200,  1200,  1208,  1208,
    1218,  1218,  1230,  1231,  1234,  1235,  1238,  1238,  1246,  1246,
    1254,  1255,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,
    1268,  1268,  1276,  1281,  1281,  1289,  1294,  1302,  1302,  1312,
    1313,  1316,  1317,  1320,  1320,  1328,  1328,  1336,  1337,  1340,
    1341,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,
    1356,  1356,  1366,  1366,  1376,  1376,  1384,  1384,  1392,  1392,
    1400,  1400,  1408,  1408,  1421,  1421,  1431,  1431,  1442,  1442,
    1452,  1453,  1456,  1456,  1464,  1465,  1468,  1469,  1472,  1473,
    1474,  1475,  1478,  1480,  1480,  1491,  1491,  1501,  1502,  1505,
    1506,  1507,  1508,  1509,  1510,  1511,  1514,  1514,  1521,  1522,
    1523,  1526,  1531,  1531,  1539,  1544,  1551,  1558,  1558,  1568,
    1569,  1572,  1573,  1576,  1576,  1584,  1584,  1594,  1594,  1604,
    1604,  1612,  1613,  1616,  1617,  1618,  1619,  1620,  1621,  1622,
    1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1633,  1638,
    1638,  1646,  1646,  1654,  1659,  1659,  1667,  1672,  1677,  1677,
    1685,  1686,  1689,  1689,  1697,  1702,  1707,  1712,  1712,  1720,
    1723,  1726,  1729,  1732,  1738,  1738,  1748,  1748,  1755,  1755,
    1767,  1767,  1780,  1781,  1785,  1789,  1789,  1801,  1802,  1806,
    1806,  1814,  1815,  1818,  1819,  1820,  1821,  1822,  1825,  1830,
    1830,  1838,  1838,  1848,  1849,  1852,  1852,  1860,  1861,  1864,
    1865,  1866,  1867,  1870,  1870,  1878,  1883,  1888
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
#line 4303 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1893 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
