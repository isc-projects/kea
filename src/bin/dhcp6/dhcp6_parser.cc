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
      case 410: // duid_type
      case 443: // ncr_protocol_value
      case 451: // replace_client_name_value
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
      case 410: // duid_type
      case 443: // ncr_protocol_value
      case 451: // replace_client_name_value
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

      case 410: // duid_type

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 443: // ncr_protocol_value

#line 224 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 451: // replace_client_name_value

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

    // FIXME: This should be completely indented.  It is not yet to
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
      case 410: // duid_type
      case 443: // ncr_protocol_value
      case 451: // replace_client_name_value
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

  case 64:
#line 378 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 65:
#line 385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 399 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 443 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 834 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 838 "dhcp6_parser.yy" // lalr1.cc:859
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

  case 212:
#line 857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1052 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1181 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1205 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1213 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1233 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1245 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2278 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1491 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2649 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2677 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3046 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3174 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3178 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -503;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
      60,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,    29,    19,    30,    34,    79,    98,   100,
     102,   108,   121,   128,   146,   157,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
      19,    18,    17,    31,   162,    23,    47,    37,    70,    32,
      -8,   -42,   137,  -503,   202,   181,   210,   217,   231,  -503,
    -503,  -503,  -503,  -503,   286,  -503,    35,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,   300,   305,   312,   318,
     319,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,   320,  -503,  -503,  -503,   123,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,   321,
     124,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
     322,   323,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,   170,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,   174,
    -503,  -503,  -503,  -503,   324,  -503,   325,   326,  -503,  -503,
    -503,   178,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,   228,   264,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,   327,
    -503,  -503,  -503,   328,  -503,  -503,   329,   331,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,   332,
    -503,  -503,  -503,  -503,   330,   336,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,   180,  -503,  -503,  -503,   337,
    -503,  -503,   338,  -503,   339,   340,  -503,  -503,   341,   342,
     343,  -503,  -503,  -503,   207,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,    19,    19,  -503,   187,   344,   345,   346,   347,   348,
    -503,    17,  -503,   349,   350,   351,   191,   211,   212,   213,
     214,   352,   353,   354,   355,   360,   361,   362,   363,   364,
     365,   221,   367,   368,    31,  -503,   369,   226,   162,  -503,
      65,   370,   371,   372,   374,   375,   233,   229,   377,   379,
     380,   381,    23,  -503,   382,   383,    47,  -503,   384,   240,
     386,   242,   243,    37,  -503,   389,   390,   391,   392,   393,
     394,   395,  -503,    70,   396,   397,   256,   398,   399,   400,
     258,  -503,    32,   402,   259,  -503,    -8,   403,   404,   111,
    -503,   260,   408,   412,   268,   414,   271,   272,   415,   418,
     273,   274,   275,   419,   423,   137,  -503,  -503,  -503,   424,
     422,   425,    19,    19,    19,  -503,   426,   427,   428,  -503,
    -503,  -503,  -503,  -503,   431,   432,   433,   434,   435,   436,
     437,   440,   439,   442,  -503,   443,   444,  -503,   447,  -503,
    -503,  -503,  -503,  -503,  -503,   445,   452,  -503,  -503,  -503,
     453,   454,   282,   309,   314,  -503,  -503,    -4,   315,   455,
     457,  -503,   333,   459,  -503,   334,  -503,   335,  -503,  -503,
    -503,   447,   447,   447,   356,   357,   358,   359,  -503,   366,
     373,  -503,   376,   378,   385,  -503,  -503,   387,  -503,  -503,
     388,    19,  -503,  -503,   401,   405,  -503,   406,  -503,  -503,
     203,   409,  -503,  -503,  -503,    -3,   407,  -503,    19,    31,
     306,  -503,  -503,  -503,   162,   133,   133,   460,   461,   462,
     -38,    19,    62,    42,   463,   135,    28,   195,   137,  -503,
    -503,   467,  -503,    65,   465,   466,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,   469,   410,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,   208,  -503,   209,  -503,  -503,   223,  -503,  -503,  -503,
    -503,   470,   473,   474,   475,   476,  -503,  -503,  -503,   224,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,   225,  -503,   478,   482,  -503,  -503,   480,
     484,  -503,  -503,   485,   487,  -503,  -503,  -503,   110,  -503,
    -503,  -503,   488,  -503,  -503,  -503,   188,  -503,  -503,  -503,
    -503,   232,  -503,   489,   490,  -503,   492,   493,   494,   495,
     496,   497,   251,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,   498,   499,   504,  -503,  -503,   252,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,   253,  -503,  -503,  -503,
     254,   411,   413,  -503,  -503,   505,   507,  -503,  -503,   506,
     510,  -503,  -503,   509,   513,  -503,  -503,   511,  -503,   514,
     306,  -503,  -503,   516,   518,   519,   521,   416,   417,   420,
     421,   429,   523,   525,   133,  -503,  -503,    23,  -503,   460,
      32,  -503,   461,    -8,  -503,   462,   -38,  -503,  -503,    62,
    -503,    42,  -503,   -42,  -503,   463,   430,   438,   441,   446,
     448,   449,   135,  -503,   526,   527,   450,   451,   456,    28,
    -503,   528,   530,   195,  -503,  -503,  -503,   531,   535,  -503,
      47,  -503,   465,    37,  -503,   466,    70,  -503,   469,   536,
    -503,   483,  -503,   257,   458,   464,   468,  -503,  -503,  -503,
    -503,  -503,   471,   472,  -503,   255,  -503,   533,  -503,   534,
    -503,  -503,  -503,  -503,   261,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,   215,   477,  -503,  -503,  -503,  -503,   479,
     481,  -503,  -503,   486,   262,  -503,   263,  -503,   537,  -503,
     491,   532,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,   283,
    -503,    61,   532,  -503,  -503,   539,  -503,  -503,  -503,   270,
    -503,  -503,  -503,  -503,  -503,   540,   500,   542,    61,  -503,
     512,  -503,   502,  -503,   541,  -503,  -503,   294,  -503,   -80,
     541,  -503,  -503,   543,   546,   547,   280,  -503,  -503,  -503,
    -503,  -503,  -503,   548,   501,   517,   520,   -80,  -503,   515,
    -503,  -503,  -503,  -503,  -503
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,    99,     9,   212,    11,   317,    13,   337,    15,
     364,    17,   256,    19,   291,    21,   177,    23,   448,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   366,   258,
     293,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     501,   495,   497,   499,     0,    63,     0,    56,    58,    60,
      61,    62,    59,    97,   108,   110,     0,     0,     0,     0,
       0,   204,   248,   283,   150,   167,   158,   397,   169,   188,
     414,     0,   436,   446,    91,     0,    68,    70,    71,    72,
      73,    74,    76,    77,    78,    79,    81,    80,    85,    86,
      75,    83,    84,    82,    87,    88,    89,    90,   105,     0,
       0,   101,   103,   104,   401,   309,   329,   233,   235,   237,
       0,     0,   241,   239,   356,   393,   232,   216,   217,   218,
     219,     0,   214,   223,   224,   225,   228,   230,   226,   227,
     220,   221,   222,   229,   231,   325,   327,   324,   322,     0,
     319,   321,   323,   349,     0,   352,     0,     0,   348,   344,
     347,     0,   339,   341,   342,   345,   346,   343,   391,   379,
     381,   383,   385,   387,   389,   378,   377,     0,   367,   368,
     372,   373,   370,   374,   375,   376,   371,   273,   140,     0,
     277,   275,   280,     0,   269,   270,     0,   259,   260,   262,
     272,   263,   264,   265,   279,   266,   267,   268,   304,     0,
     302,   303,   306,   307,     0,   294,   295,   297,   298,   299,
     300,   301,   184,   186,   181,     0,   179,   182,   183,     0,
     468,   470,     0,   473,     0,     0,   477,   481,     0,     0,
       0,   486,   493,   466,     0,   450,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
      42,     0,     0,    35,     0,     0,     0,     0,     0,     0,
      53,     0,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,     0,   100,
     403,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   213,     0,     0,     0,   318,     0,     0,
       0,     0,     0,     0,   338,     0,     0,     0,     0,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
       0,   257,     0,     0,     0,   292,     0,     0,     0,     0,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   449,    46,    39,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    92,
      93,    94,    95,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   435,     0,     0,    69,     0,   107,
     102,   412,   410,   411,   409,     0,   404,   405,   407,   408,
       0,     0,     0,     0,     0,   246,   247,     0,     0,     0,
       0,   215,     0,     0,   320,     0,   351,     0,   354,   355,
     340,     0,     0,     0,     0,     0,     0,     0,   369,     0,
       0,   271,     0,     0,     0,   282,   261,     0,   308,   296,
       0,     0,   180,   467,     0,     0,   472,     0,   475,   476,
       0,     0,   483,   484,   485,     0,     0,   451,     0,     0,
       0,   496,   498,   500,     0,     0,     0,   206,   250,   285,
       0,    43,     0,     0,   171,     0,     0,     0,     0,    47,
     106,     0,   402,     0,   311,   331,   234,   236,   238,   243,
     244,   245,   242,   240,   358,     0,   326,    36,   328,   350,
     353,   392,   380,   382,   384,   386,   388,   390,   274,   141,
     278,   276,   281,   305,   185,   187,   469,   471,   474,   479,
     480,   478,   482,   488,   489,   490,   491,   492,   487,   494,
      40,     0,   506,     0,   503,   505,     0,   127,   133,   135,
     137,     0,     0,     0,     0,     0,   146,   148,   126,     0,
     112,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,   210,     0,   207,   208,   254,     0,
     251,   252,   289,     0,   286,   287,   156,   157,     0,   152,
     154,   155,     0,   165,   166,   162,     0,   160,   163,   164,
     399,     0,   175,     0,   172,   173,     0,     0,     0,     0,
       0,     0,     0,   190,   192,   193,   194,   195,   196,   197,
     425,   431,     0,     0,     0,   424,   423,     0,   416,   418,
     421,   419,   420,   422,   442,   444,     0,   438,   440,   441,
       0,    49,     0,   406,   315,     0,   312,   313,   335,     0,
     332,   333,   362,     0,   359,   360,   395,     0,    65,     0,
       0,   502,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   109,   111,     0,   205,     0,
     258,   249,     0,   293,   284,     0,     0,   151,   168,     0,
     159,     0,   398,     0,   170,     0,     0,     0,     0,     0,
       0,     0,     0,   189,     0,     0,     0,     0,     0,     0,
     415,     0,     0,     0,   437,   447,    51,     0,    50,   413,
       0,   310,     0,     0,   330,     0,   366,   357,     0,     0,
     394,     0,   504,     0,     0,     0,     0,   139,   142,   143,
     144,   145,     0,     0,   113,     0,   209,     0,   253,     0,
     288,   153,   161,   400,     0,   174,   198,   199,   200,   201,
     202,   203,   191,     0,     0,   430,   433,   434,   417,     0,
       0,   439,    48,     0,     0,   314,     0,   334,     0,   361,
       0,     0,   129,   130,   131,   132,   128,   134,   136,   138,
     147,   149,   211,   255,   290,   176,   427,   428,   429,   426,
     432,   443,   445,    52,   316,   336,   363,   396,   510,     0,
     508,     0,     0,   507,   522,     0,   520,   518,   514,     0,
     512,   516,   517,   515,   509,     0,     0,     0,     0,   511,
       0,   519,     0,   513,     0,   521,   526,     0,   524,     0,
       0,   523,   534,     0,     0,     0,     0,   528,   530,   531,
     532,   533,   525,     0,     0,     0,     0,     0,   527,     0,
     536,   537,   538,   529,   535
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,    11,  -503,   103,  -503,  -503,  -503,
    -503,  -503,  -503,    46,  -503,  -150,  -503,  -503,  -503,   -62,
    -503,  -503,  -503,   265,  -503,  -503,  -503,  -503,    59,   236,
     -63,   -50,   -49,   -43,  -503,  -503,  -503,  -503,  -503,    58,
     235,  -503,  -503,  -503,  -503,  -503,  -503,  -503,    64,  -140,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
     -58,  -503,  -502,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -149,  -489,  -503,  -503,  -503,  -503,  -148,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -152,  -503,
    -503,  -503,  -147,   196,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -158,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -132,  -503,  -503,  -503,  -127,   239,  -503,  -503,
    -503,  -503,  -503,  -503,  -492,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -130,  -503,  -503,  -503,  -126,
    -503,   216,  -503,   -59,  -503,  -503,  -503,  -503,  -503,   -57,
    -503,  -503,  -503,  -503,  -503,   -48,  -503,  -503,  -503,  -129,
    -503,  -503,  -503,  -128,  -503,   218,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -169,  -503,  -503,  -503,
    -161,   245,  -503,  -503,   -66,  -503,  -503,  -503,  -503,  -503,
    -163,  -503,  -503,  -503,  -160,   248,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -162,  -503,  -503,
    -503,  -154,  -503,   241,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,    80,  -503,
    -503,  -503,  -503,  -503,  -503,  -131,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -136,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,    91,   219,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,  -503,
    -503,   -79,  -503,  -503,  -503,  -232,  -503,  -503,  -245,  -503,
    -503,  -503,  -503,  -503,  -503,  -255,  -503,  -503,  -270,  -503,
    -503,  -503,  -503,  -503
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   538,    77,
      78,    37,    60,    74,    75,   520,   671,   747,   748,   114,
      39,    62,    86,    87,    88,   295,    41,    63,   115,   116,
     117,   118,   119,   120,   121,   122,   303,    43,    64,   140,
     141,   142,   326,   143,   123,   304,   124,   305,   589,   590,
     591,   693,   816,   592,   694,   593,   695,   594,   696,   595,
     225,   365,   597,   598,   599,   600,   601,   702,   602,   703,
     125,   314,   618,   619,   620,   621,   126,   316,   626,   627,
     628,   629,   127,   315,   128,   318,   633,   634,   635,   723,
      57,    71,   255,   256,   257,   377,   258,   378,   129,   319,
     642,   643,   644,   645,   646,   647,   648,   649,   130,   311,
     605,   606,   607,   707,    45,    65,   161,   162,   163,   333,
     164,   334,   165,   335,   166,   339,   167,   338,   532,   168,
     169,   131,   312,   609,   610,   611,   710,    53,    69,   226,
     227,   228,   229,   230,   231,   232,   364,   233,   368,   234,
     367,   235,   236,   369,   237,   132,   313,   613,   614,   615,
     713,    55,    70,   244,   245,   246,   247,   248,   373,   249,
     250,   251,   171,   331,   675,   676,   677,   750,    47,    66,
     179,   180,   181,   344,   182,   345,   172,   332,   679,   680,
     681,   753,    49,    67,   191,   192,   193,   348,   194,   195,
     350,   196,   197,   173,   340,   683,   684,   685,   756,    51,
      68,   207,   208,   209,   210,   356,   211,   357,   212,   358,
     213,   359,   214,   360,   215,   361,   216,   355,   174,   341,
     687,   759,   133,   317,   631,   330,   435,   436,   437,   438,
     439,   521,   134,   320,   657,   658,   659,   734,   829,   660,
     661,   735,   662,   663,   135,   136,   322,   666,   667,   668,
     741,   669,   742,   137,   323,    59,    72,   274,   275,   276,
     277,   382,   278,   383,   279,   280,   385,   281,   282,   283,
     388,   561,   284,   389,   285,   286,   287,   288,   393,   568,
     289,   394,    89,   297,    90,   298,    91,   299,    92,   296,
     573,   574,   575,   689,   839,   840,   841,   849,   850,   851,
     852,   857,   853,   855,   867,   868,   869,   876,   877,   878,
     883,   879,   880,   881
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      85,   190,   157,   156,   177,   188,   205,   224,   240,   254,
     273,   242,   241,   243,   656,   158,   159,   170,   178,   189,
     206,   630,   160,   625,    27,    34,    28,    79,    29,    26,
     144,   218,   238,   219,   220,   239,   616,    38,   301,   252,
     253,    40,    93,   302,   650,    94,    95,   872,   217,   144,
     873,   874,   875,   582,    96,    97,    98,    99,   529,   530,
     531,   103,    96,    97,    98,    99,   100,   101,   102,   103,
     145,   218,   146,   219,   220,   103,   221,   222,   223,   147,
     148,   149,   150,   151,   152,   103,    42,   183,   184,   185,
     186,   187,   176,   153,   154,   175,   104,   105,   106,   107,
     218,   155,   176,   103,   218,    44,    84,    46,   103,    48,
     617,   108,   153,   716,   109,    50,   717,   563,   564,   565,
     566,   110,   651,   652,   653,   654,   324,   328,    52,   111,
     112,   325,   329,   113,   431,    54,   616,   623,   198,   624,
      84,    80,   199,   200,   201,   202,   203,   204,   567,   577,
      81,    82,    83,    56,   578,   579,   580,   581,   582,   583,
     584,   585,   586,   587,    58,    84,    76,    30,    31,    32,
      33,    84,   218,   342,   138,   139,    84,   346,   343,    84,
      84,   353,   347,   379,   291,    84,   354,   844,   380,   845,
     846,   719,   252,   253,   720,    84,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,   290,    84,
     395,   324,   690,    84,   292,   396,   688,   691,    84,   636,
     637,   638,   639,   640,   641,   293,   328,   704,   704,   783,
     625,   692,   705,   706,   294,   721,   362,   656,   722,    85,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   732,   739,   743,   395,   342,   733,
     740,   744,   745,   822,   379,   346,   353,   363,   432,   825,
     834,   835,   433,   858,   812,   813,   814,   815,   859,   157,
     156,    84,   434,   887,   177,    84,   842,   190,   888,   843,
     300,   188,   158,   159,   170,   664,   665,   870,   178,   160,
     871,   205,   397,   398,   306,   189,   826,   827,   828,   307,
     224,   541,   542,   543,   240,   206,   308,   242,   241,   243,
     559,   560,   309,   310,   321,   327,   336,   337,   349,   351,
     352,   366,   370,   273,   372,   399,   374,   371,   375,   376,
     409,   381,   384,   386,   387,   390,   391,   392,   400,   401,
     402,   403,   404,   406,   407,   408,   414,   415,   416,   417,
     410,   411,   412,   413,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   428,   440,   441,   442,   429,   443,   444,
     446,   447,   445,   448,   449,   450,   452,   453,   455,   456,
     457,   458,   459,   461,   462,   463,   464,   465,   466,   467,
     469,   470,   472,   473,   474,   471,   477,   480,   481,   475,
     478,   483,   484,   501,   502,   503,   485,   486,   487,   490,
     488,   489,   491,   495,   492,   493,   494,   496,   498,   499,
     526,   572,   500,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   588,   588,   514,   515,   596,   596,   516,
     517,   518,   519,   522,   655,   523,   273,   527,   524,   525,
     534,   432,   528,   533,   535,   433,    28,   604,   608,   612,
     632,   672,   674,   678,   697,   434,   682,   698,   699,   700,
     701,   536,   539,   540,   708,   709,   711,   712,   811,   686,
     715,   714,   555,   725,   718,   724,   726,   727,   728,   729,
     730,   731,   736,   737,   544,   545,   546,   547,   738,   570,
     752,   751,   754,   755,   548,   757,   758,   864,   761,   760,
     763,   549,   764,   765,   550,   766,   551,   772,   562,   773,
     793,   794,   799,   552,   800,   553,   554,   802,   803,   838,
     810,   823,   824,   856,   860,   836,   862,   884,   866,   556,
     885,   886,   889,   557,   558,   569,   537,   622,   571,   746,
     427,   749,   576,   430,   774,   767,   405,   781,   768,   769,
     603,   782,   770,   785,   792,   482,   784,   776,   771,   786,
     775,   451,   778,   805,   777,   779,   780,   787,   476,   804,
     788,   454,   807,   806,   479,   789,   809,   790,   791,   795,
     796,   460,   808,   673,   468,   797,   817,   801,   798,   670,
     854,   762,   818,   863,   497,   882,   819,   893,     0,   820,
     821,     0,     0,     0,     0,   830,     0,   831,     0,   832,
       0,     0,     0,     0,   833,     0,     0,     0,     0,   837,
       0,     0,   588,     0,   157,   156,   596,     0,   224,   861,
     865,   240,   890,     0,   242,   241,   243,   158,   159,   170,
       0,   254,     0,   894,   160,     0,   891,     0,     0,   892,
       0,     0,     0,     0,     0,     0,     0,   655,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   190,   177,     0,
       0,   188,     0,     0,   205,     0,     0,     0,     0,     0,
       0,     0,   178,     0,     0,   189,     0,     0,   206,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   847,
       0,     0,     0,   848,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   847,     0,     0,     0,
     848
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   516,    65,    65,    65,    66,    67,
      68,   513,    65,   512,     5,    14,     7,    10,     9,     0,
       7,    39,    40,    41,    42,    43,    74,     7,     3,    81,
      82,     7,    11,     8,    16,    14,    15,   127,    16,     7,
     130,   131,   132,    25,    31,    32,    33,    34,    62,    63,
      64,    38,    31,    32,    33,    34,    35,    36,    37,    38,
      47,    39,    49,    41,    42,    38,    44,    45,    46,    56,
      57,    58,    59,    60,    61,    38,     7,    50,    51,    52,
      53,    54,    55,    70,    71,    48,    65,    66,    67,    68,
      39,    78,    55,    38,    39,     7,   148,     7,    38,     7,
     148,    80,    70,     3,    83,     7,     6,   120,   121,   122,
     123,    90,    94,    95,    96,    97,     3,     3,     7,    98,
      99,     8,     8,   102,    69,     7,    74,    75,    68,    77,
     148,   124,    72,    73,    74,    75,    76,    77,   151,    16,
     133,   134,   135,     7,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     7,   148,   148,   148,   149,   150,
     151,   148,    39,     3,    12,    13,   148,     3,     8,   148,
     148,     3,     8,     3,     3,   148,     8,   126,     8,   128,
     129,     3,    81,    82,     6,   148,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,     6,   148,
       3,     3,     3,   148,     4,     8,     8,     8,   148,    84,
      85,    86,    87,    88,    89,     8,     3,     3,     3,   721,
     719,     8,     8,     8,     3,     3,     8,   739,     6,   301,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     3,     3,     3,     3,     3,     8,
       8,     8,     8,     8,     3,     3,     3,     3,   330,     8,
       8,     8,   330,     3,    17,    18,    19,    20,     8,   342,
     342,   148,   330,     3,   346,   148,     3,   353,     8,     6,
       4,   353,   342,   342,   342,   100,   101,     3,   346,   342,
       6,   363,   291,   292,     4,   353,    91,    92,    93,     4,
     372,   461,   462,   463,   376,   363,     4,   376,   376,   376,
     117,   118,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   395,     3,   148,     4,     8,     8,     3,
     149,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     149,   149,   149,   149,     4,     4,     4,     4,     4,     4,
     149,     4,     4,     4,     4,     4,     4,   151,     4,     4,
     151,     4,   149,     4,     4,     4,     4,     4,     4,   149,
       4,   149,   149,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   149,     4,     4,     4,   151,
     151,   151,     4,   402,   403,   404,     4,   149,     4,     4,
     149,   149,     4,     4,   151,   151,   151,     4,     4,     7,
     148,   125,     7,     7,     7,     7,     5,     5,     5,     5,
       5,     5,     5,   505,   506,     5,     7,   505,   506,     7,
       7,     7,     5,     8,   516,     3,   518,   148,     5,     5,
       5,   523,   148,   148,     7,   523,     7,     7,     7,     7,
       7,     4,     7,     7,     4,   523,     7,     4,     4,     4,
       4,   148,   148,   148,     6,     3,     6,     3,     5,    79,
       3,     6,   481,     3,     6,     6,     4,     4,     4,     4,
       4,     4,     4,     4,   148,   148,   148,   148,     4,   498,
       3,     6,     6,     3,   148,     6,     3,     5,     4,     8,
       4,   148,     4,     4,   148,     4,   148,     4,   119,     4,
       4,     4,     4,   148,     4,   148,   148,     6,     3,     7,
       4,     8,     8,     4,     4,     8,     4,     4,     7,   148,
       4,     4,     4,   148,   148,   148,   453,   511,   499,   148,
     324,   148,   504,   328,   704,   149,   301,   716,   151,   149,
     506,   719,   151,   725,   732,   379,   723,   709,   149,   149,
     707,   342,   712,   752,   710,   713,   715,   149,   372,   750,
     149,   346,   755,   753,   376,   149,   758,   149,   149,   149,
     149,   353,   756,   523,   363,   149,   148,   743,   739,   518,
     842,   690,   148,   858,   395,   870,   148,   887,    -1,   148,
     148,    -1,    -1,    -1,    -1,   148,    -1,   148,    -1,   148,
      -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,   148,
      -1,    -1,   704,    -1,   707,   707,   704,    -1,   710,   149,
     148,   713,   151,    -1,   713,   713,   713,   707,   707,   707,
      -1,   723,    -1,   148,   707,    -1,   149,    -1,    -1,   149,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   739,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   753,   750,    -1,
      -1,   753,    -1,    -1,   756,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   750,    -1,    -1,   753,    -1,    -1,   756,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   841,
      -1,    -1,    -1,   841,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   858,    -1,    -1,    -1,
     858
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     0,     5,     7,     9,
     148,   149,   150,   151,   166,   167,   168,   173,     7,   182,
       7,   188,     7,   199,     7,   276,     7,   340,     7,   354,
       7,   371,     7,   299,     7,   323,     7,   252,     7,   427,
     174,   169,   183,   189,   200,   277,   341,   355,   372,   300,
     324,   253,   428,   166,   175,   176,   148,   171,   172,    10,
     124,   133,   134,   135,   148,   181,   184,   185,   186,   454,
     456,   458,   460,    11,    14,    15,    31,    32,    33,    34,
      35,    36,    37,    38,    65,    66,    67,    68,    80,    83,
      90,    98,    99,   102,   181,   190,   191,   192,   193,   194,
     195,   196,   197,   206,   208,   232,   238,   244,   246,   260,
     270,   293,   317,   394,   404,   416,   417,   425,    12,    13,
     201,   202,   203,   205,     7,    47,    49,    56,    57,    58,
      59,    60,    61,    70,    71,    78,   181,   192,   193,   194,
     195,   278,   279,   280,   282,   284,   286,   288,   291,   292,
     317,   334,   348,   365,   390,    48,    55,   181,   317,   342,
     343,   344,   346,    50,    51,    52,    53,    54,   181,   317,
     346,   356,   357,   358,   360,   361,   363,   364,    68,    72,
      73,    74,    75,    76,    77,   181,   317,   373,   374,   375,
     376,   378,   380,   382,   384,   386,   388,    16,    39,    41,
      42,    44,    45,    46,   181,   222,   301,   302,   303,   304,
     305,   306,   307,   309,   311,   313,   314,   316,    40,    43,
     181,   222,   305,   311,   325,   326,   327,   328,   329,   331,
     332,   333,    81,    82,   181,   254,   255,   256,   258,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   181,   429,   430,   431,   432,   434,   436,
     437,   439,   440,   441,   444,   446,   447,   448,   449,   452,
       6,     3,     4,     8,     3,   187,   461,   455,   457,   459,
       4,     3,     8,   198,   207,   209,     4,     4,     4,     4,
       4,   271,   294,   318,   233,   245,   239,   395,   247,   261,
     405,     4,   418,   426,     3,     8,   204,     4,     3,     8,
     397,   335,   349,   281,   283,   285,     4,     4,   289,   287,
     366,   391,     3,     8,   345,   347,     3,     8,   359,     4,
     362,     4,     4,     3,     8,   389,   377,   379,   381,   383,
     385,   387,     8,     3,   308,   223,     4,   312,   310,   315,
       4,     8,     3,   330,     4,     8,     3,   257,   259,     3,
       8,     4,   433,   435,     4,   438,     4,     4,   442,   445,
       4,     4,     4,   450,   453,     3,     8,   166,   166,   148,
       4,     4,     4,     4,     4,   185,     4,     4,     4,   149,
     149,   149,   149,   149,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   149,     4,     4,   191,     4,   151,
     202,    69,   181,   222,   317,   398,   399,   400,   401,   402,
       4,     4,     4,     4,     4,   149,   151,     4,     4,     4,
       4,   279,     4,     4,   343,     4,   149,     4,   149,   149,
     357,     4,     4,     4,     4,     4,     4,     4,   375,     4,
       4,   149,     4,     4,     4,   151,   303,     4,   151,   327,
       4,     4,   255,   151,     4,     4,   149,     4,   149,   149,
       4,     4,   151,   151,   151,     4,     4,   430,     4,     7,
       7,   166,   166,   166,     7,     7,     7,     5,     5,     5,
       5,     5,     5,     5,     5,     7,     7,     7,     7,     5,
     177,   403,     8,     3,     5,     5,   148,   148,   148,    62,
      63,    64,   290,   148,     5,     7,   148,   168,   170,   148,
     148,   177,   177,   177,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   166,   148,   148,   148,   117,
     118,   443,   119,   120,   121,   122,   123,   151,   451,   148,
     166,   190,   125,   462,   463,   464,   201,    16,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,   181,   210,
     211,   212,   215,   217,   219,   221,   222,   224,   225,   226,
     227,   228,   230,   210,     7,   272,   273,   274,     7,   295,
     296,   297,     7,   319,   320,   321,    74,   148,   234,   235,
     236,   237,   175,    75,    77,   236,   240,   241,   242,   243,
     286,   396,     7,   248,   249,   250,    84,    85,    86,    87,
      88,    89,   262,   263,   264,   265,   266,   267,   268,   269,
      16,    94,    95,    96,    97,   181,   224,   406,   407,   408,
     411,   412,   414,   415,   100,   101,   419,   420,   421,   423,
     429,   178,     4,   400,     7,   336,   337,   338,     7,   350,
     351,   352,     7,   367,   368,   369,    79,   392,     8,   465,
       3,     8,     8,   213,   216,   218,   220,     4,     4,     4,
       4,     4,   229,   231,     3,     8,     8,   275,     6,     3,
     298,     6,     3,   322,     6,     3,     3,     6,     6,     3,
       6,     3,     6,   251,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   409,   413,     4,     4,     4,     3,
       8,   422,   424,     3,     8,     8,   148,   179,   180,   148,
     339,     6,     3,   353,     6,     3,   370,     6,     3,   393,
       8,     4,   463,     4,     4,     4,     4,   149,   151,   149,
     151,   149,     4,     4,   211,   278,   274,   301,   297,   325,
     321,   235,   241,   286,   254,   250,   149,   149,   149,   149,
     149,   149,   263,     4,     4,   149,   149,   149,   407,     4,
       4,   420,     6,     3,   342,   338,   356,   352,   373,   369,
       4,     5,    17,    18,    19,    20,   214,   148,   148,   148,
     148,   148,     8,     8,     8,     8,    91,    92,    93,   410,
     148,   148,   148,   148,     8,     8,     8,   148,     7,   466,
     467,   468,     3,     6,   126,   128,   129,   181,   222,   469,
     470,   471,   472,   474,   467,   475,     4,   473,     3,     8,
       4,   149,     4,   470,     5,   148,     7,   476,   477,   478,
       3,     6,   127,   130,   131,   132,   479,   480,   481,   483,
     484,   485,   477,   482,     4,     4,     4,     3,     8,     4,
     151,   149,   149,   480,   148
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
     185,   185,   185,   185,   187,   186,   189,   188,   190,   190,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   192,   193,   194,   195,   196,   198,   197,   200,
     199,   201,   201,   202,   202,   204,   203,   205,   207,   206,
     209,   208,   210,   210,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   213,   212,   214,
     214,   214,   214,   216,   215,   218,   217,   220,   219,   221,
     223,   222,   224,   225,   226,   227,   229,   228,   231,   230,
     233,   232,   234,   234,   235,   235,   236,   237,   239,   238,
     240,   240,   241,   241,   241,   242,   243,   245,   244,   247,
     246,   248,   248,   249,   249,   251,   250,   253,   252,   254,
     254,   254,   255,   255,   257,   256,   259,   258,   261,   260,
     262,   262,   263,   263,   263,   263,   263,   263,   264,   265,
     266,   267,   268,   269,   271,   270,   272,   272,   273,   273,
     275,   274,   277,   276,   278,   278,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   281,   280,   283,   282,   285,   284,   287,
     286,   289,   288,   290,   290,   290,   291,   292,   294,   293,
     295,   295,   296,   296,   298,   297,   300,   299,   301,   301,
     302,   302,   303,   303,   303,   303,   303,   303,   303,   303,
     304,   305,   306,   308,   307,   310,   309,   312,   311,   313,
     315,   314,   316,   318,   317,   319,   319,   320,   320,   322,
     321,   324,   323,   325,   325,   326,   326,   327,   327,   327,
     327,   327,   327,   328,   330,   329,   331,   332,   333,   335,
     334,   336,   336,   337,   337,   339,   338,   341,   340,   342,
     342,   343,   343,   343,   343,   345,   344,   347,   346,   349,
     348,   350,   350,   351,   351,   353,   352,   355,   354,   356,
     356,   357,   357,   357,   357,   357,   357,   357,   357,   359,
     358,   360,   362,   361,   363,   364,   366,   365,   367,   367,
     368,   368,   370,   369,   372,   371,   373,   373,   374,   374,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   377,
     376,   379,   378,   381,   380,   383,   382,   385,   384,   387,
     386,   389,   388,   391,   390,   393,   392,   395,   394,   396,
     396,   397,   286,   398,   398,   399,   399,   400,   400,   400,
     400,   401,   403,   402,   405,   404,   406,   406,   407,   407,
     407,   407,   407,   407,   407,   409,   408,   410,   410,   410,
     411,   413,   412,   414,   415,   416,   418,   417,   419,   419,
     420,   420,   422,   421,   424,   423,   426,   425,   428,   427,
     429,   429,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   431,   433,   432,
     435,   434,   436,   438,   437,   439,   440,   442,   441,   443,
     443,   445,   444,   446,   447,   448,   450,   449,   451,   451,
     451,   451,   451,   453,   452,   455,   454,   457,   456,   459,
     458,   461,   460,   462,   462,   463,   465,   464,   466,   466,
     468,   467,   469,   469,   470,   470,   470,   470,   470,   471,
     473,   472,   475,   474,   476,   476,   478,   477,   479,   479,
     480,   480,   480,   480,   482,   481,   483,   484,   485
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
       1,     1,     1,     1,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
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
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "value", "sub_json", "map2", "$@13", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@14", "list_content",
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
  "pools_list", "$@59", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@60", "sub_pool6", "$@61", "pool_params",
  "pool_param", "pool_entry", "$@62", "user_context", "$@63",
  "pd_pools_list", "$@64", "pd_pools_list_content",
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
  "dhcpddns_json_object", "$@100", "control_agent_json_object", "$@101",
  "logging_object", "$@102", "logging_params", "logging_param", "loggers",
  "$@103", "loggers_entries", "logger_entry", "$@104", "logger_params",
  "logger_param", "debuglevel", "severity", "$@105", "output_options_list",
  "$@106", "output_options_list_content", "output_entry", "$@107",
  "output_params_list", "output_params", "output", "$@108", "flush",
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
     372,   373,   374,   375,   378,   378,   395,   395,   403,   404,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   433,   438,   443,   448,   453,   458,   458,   468,
     468,   476,   477,   480,   481,   484,   484,   494,   500,   500,
     510,   510,   520,   521,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   539,   539,   546,
     547,   548,   549,   552,   552,   560,   560,   568,   568,   576,
     581,   581,   589,   594,   599,   604,   609,   609,   617,   617,
     626,   626,   636,   637,   640,   641,   644,   649,   654,   654,
     664,   665,   668,   669,   670,   673,   678,   685,   685,   695,
     695,   705,   706,   709,   710,   713,   713,   721,   721,   729,
     730,   731,   734,   735,   738,   738,   746,   746,   754,   754,
     764,   765,   768,   769,   770,   771,   772,   773,   776,   781,
     786,   791,   796,   801,   809,   809,   822,   823,   826,   827,
     834,   834,   857,   857,   866,   867,   871,   872,   873,   874,
     875,   876,   877,   878,   879,   880,   881,   882,   883,   884,
     885,   886,   887,   890,   890,   898,   898,   906,   906,   914,
     914,   922,   922,   929,   930,   931,   934,   939,   948,   948,
     960,   961,   964,   965,   970,   970,   981,   981,   991,   992,
     995,   996,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,
    1009,  1011,  1016,  1018,  1018,  1026,  1026,  1034,  1034,  1042,
    1044,  1044,  1052,  1061,  1061,  1073,  1074,  1079,  1080,  1085,
    1085,  1096,  1096,  1107,  1108,  1113,  1114,  1119,  1120,  1121,
    1122,  1123,  1124,  1127,  1129,  1129,  1137,  1139,  1141,  1149,
    1149,  1161,  1162,  1165,  1166,  1169,  1169,  1177,  1177,  1185,
    1186,  1189,  1190,  1191,  1192,  1195,  1195,  1203,  1203,  1213,
    1213,  1225,  1226,  1229,  1230,  1233,  1233,  1241,  1241,  1249,
    1250,  1253,  1254,  1255,  1256,  1257,  1258,  1259,  1260,  1263,
    1263,  1271,  1276,  1276,  1284,  1289,  1297,  1297,  1307,  1308,
    1311,  1312,  1315,  1315,  1323,  1323,  1331,  1332,  1335,  1336,
    1340,  1341,  1342,  1343,  1344,  1345,  1346,  1347,  1348,  1351,
    1351,  1361,  1361,  1371,  1371,  1379,  1379,  1387,  1387,  1395,
    1395,  1403,  1403,  1416,  1416,  1426,  1426,  1437,  1437,  1447,
    1448,  1451,  1451,  1459,  1460,  1463,  1464,  1467,  1468,  1469,
    1470,  1473,  1475,  1475,  1486,  1486,  1496,  1497,  1500,  1501,
    1502,  1503,  1504,  1505,  1506,  1509,  1509,  1516,  1517,  1518,
    1521,  1526,  1526,  1534,  1539,  1546,  1553,  1553,  1563,  1564,
    1567,  1568,  1571,  1571,  1579,  1579,  1589,  1589,  1599,  1599,
    1607,  1608,  1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,
    1619,  1620,  1621,  1622,  1623,  1624,  1625,  1628,  1633,  1633,
    1641,  1641,  1649,  1654,  1654,  1662,  1667,  1672,  1672,  1680,
    1681,  1684,  1684,  1692,  1697,  1702,  1707,  1707,  1715,  1718,
    1721,  1724,  1727,  1733,  1733,  1743,  1743,  1750,  1750,  1757,
    1757,  1770,  1770,  1783,  1784,  1788,  1792,  1792,  1804,  1805,
    1809,  1809,  1817,  1818,  1821,  1822,  1823,  1824,  1825,  1828,
    1833,  1833,  1841,  1841,  1851,  1852,  1855,  1855,  1863,  1864,
    1867,  1868,  1869,  1870,  1873,  1873,  1881,  1886,  1891
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
#line 4313 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1896 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
