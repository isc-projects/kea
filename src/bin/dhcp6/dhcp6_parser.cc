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
      case 162: // value
      case 166: // map_value
      case 210: // db_type
      case 405: // duid_type
      case 438: // ncr_protocol_value
      case 446: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 147: // "boolean"
        value.move< bool > (that.value);
        break;

      case 146: // "floating point"
        value.move< double > (that.value);
        break;

      case 145: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 144: // "constant string"
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
      case 162: // value
      case 166: // map_value
      case 210: // db_type
      case 405: // duid_type
      case 438: // ncr_protocol_value
      case 446: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 147: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 146: // "floating point"
        value.copy< double > (that.value);
        break;

      case 145: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 144: // "constant string"
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
            case 144: // "constant string"

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 145: // "integer"

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 146: // "floating point"

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 147: // "boolean"

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 162: // value

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 166: // map_value

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 210: // db_type

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 405: // duid_type

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 438: // ncr_protocol_value

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 446: // replace_client_name_value

#line 219 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 425 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 162: // value
      case 166: // map_value
      case 210: // db_type
      case 405: // duid_type
      case 438: // ncr_protocol_value
      case 446: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 147: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 146: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 145: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 144: // "constant string"
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
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 314 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 327 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 372 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 389 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 504 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1147 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 540 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 541 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 753 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 785 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 790 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 892 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 900 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 902 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1812 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1010 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1187 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1266 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1398 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1418 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1499 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1506 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1507 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2557 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1711 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2982 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1841 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3130 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3134 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -498;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     185,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,    39,    20,    36,    64,    77,    95,   120,
     154,   175,   181,   189,   190,   224,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
      20,    94,    18,    27,   100,    19,    -1,    45,    81,    28,
     117,   -33,    99,  -498,   250,   248,   258,   262,   272,  -498,
    -498,  -498,  -498,   274,  -498,    98,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,   276,   278,   279,   288,   289,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   290,
    -498,  -498,  -498,   102,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   293,   137,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   297,   299,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   166,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   167,  -498,  -498,
    -498,  -498,   300,  -498,   301,   302,  -498,  -498,  -498,   170,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,   305,   306,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   304,  -498,  -498,
    -498,   325,  -498,  -498,   323,   307,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   328,  -498,  -498,
    -498,  -498,   326,   330,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,   173,  -498,  -498,  -498,   331,  -498,  -498,
     332,  -498,   333,   334,  -498,  -498,   335,   336,   337,  -498,
    -498,  -498,   211,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    20,
      20,  -498,   198,   339,   340,   341,   342,  -498,    18,  -498,
     343,   344,   345,   205,   206,   207,   208,   209,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   220,   362,
     363,    27,  -498,   364,   222,   100,  -498,    43,   366,   367,
     368,   369,   370,   230,   231,   372,   373,   375,   376,    19,
    -498,   377,   378,    -1,  -498,   379,   241,   380,   242,   243,
      45,  -498,   381,   385,   386,   387,   388,   389,   390,  -498,
      81,   391,   392,   252,   394,   395,   396,   254,  -498,    28,
     398,   256,  -498,   117,   400,   401,   -46,  -498,   259,   403,
     404,   266,   408,   268,   269,   411,   412,   270,   271,   273,
     415,   417,    99,  -498,  -498,  -498,   418,   416,   419,    20,
      20,  -498,   420,   421,   422,  -498,  -498,  -498,  -498,  -498,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
    -498,   437,   438,  -498,   441,  -498,  -498,  -498,  -498,  -498,
    -498,   439,   445,  -498,  -498,  -498,   447,   448,   280,   281,
     310,  -498,  -498,   311,   313,   453,   443,  -498,   315,   454,
    -498,   318,  -498,   319,  -498,  -498,  -498,   441,   441,   441,
     320,   321,   322,   324,  -498,   327,   329,  -498,   338,   346,
     347,  -498,  -498,   348,  -498,  -498,   349,    20,  -498,  -498,
     350,   361,  -498,   365,  -498,  -498,     6,   382,  -498,  -498,
    -498,    66,   371,  -498,    20,    27,   374,  -498,  -498,   100,
     108,   108,   460,   462,   465,   -41,    20,    70,    41,   467,
     109,    24,   -42,    99,  -498,  -498,   471,  -498,    43,   469,
     470,  -498,  -498,  -498,  -498,  -498,   472,   402,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,   212,  -498,   213,  -498,  -498,   214,  -498,
    -498,  -498,  -498,   476,   477,   479,   480,   481,  -498,  -498,
    -498,   215,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,   221,  -498,   482,   483,  -498,
    -498,   489,   486,  -498,  -498,   491,   496,  -498,  -498,  -498,
      82,  -498,  -498,  -498,   494,  -498,  -498,  -498,   122,  -498,
    -498,  -498,  -498,   260,  -498,   495,   499,  -498,   502,   503,
     504,   506,   507,   508,   225,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,   509,   510,   512,  -498,  -498,   227,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   229,  -498,
    -498,  -498,   236,   383,   384,  -498,  -498,   497,   514,  -498,
    -498,   513,   515,  -498,  -498,   516,   517,  -498,  -498,   518,
    -498,   519,   374,  -498,  -498,   520,   521,   525,   526,   393,
     397,   405,   399,   406,   527,   528,   108,  -498,  -498,    19,
    -498,   460,    28,  -498,   462,   117,  -498,   465,   -41,  -498,
    -498,    70,  -498,    41,  -498,   -33,  -498,   467,   407,   409,
     410,   413,   414,   423,   109,  -498,   529,   530,   424,   435,
     436,    24,  -498,   531,   532,   -42,  -498,  -498,  -498,   533,
     534,  -498,    -1,  -498,   469,    45,  -498,   470,    81,  -498,
     472,   536,  -498,   537,  -498,   240,   440,   442,   444,  -498,
    -498,  -498,  -498,  -498,   446,   449,  -498,   237,  -498,   535,
    -498,   539,  -498,  -498,  -498,  -498,   238,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,   184,   450,  -498,  -498,  -498,
    -498,   451,   452,  -498,  -498,   455,   239,  -498,   245,  -498,
     540,  -498,   456,   538,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,   261,  -498,    54,   538,  -498,  -498,   545,  -498,  -498,
    -498,   246,  -498,  -498,  -498,  -498,  -498,   549,   457,   552,
      54,  -498,   555,  -498,   459,  -498,   550,  -498,  -498,   265,
    -498,   -93,   550,  -498,  -498,   557,   558,   559,   247,  -498,
    -498,  -498,  -498,  -498,  -498,   560,   458,   461,   463,   -93,
    -498,   466,  -498,  -498,  -498,  -498,  -498
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   211,    11,   313,    13,   333,    15,
     360,    17,   252,    19,   287,    21,   176,    23,   444,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   362,   254,
     289,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     495,   491,   493,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   107,   109,     0,     0,     0,     0,     0,   203,
     244,   279,   149,   166,   157,   393,   168,   187,   410,     0,
     432,   442,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   104,     0,     0,   100,
     102,   103,   397,   305,   325,   232,   234,   236,     0,     0,
     240,   238,   352,   389,   231,   215,   216,   217,   218,     0,
     213,   222,   223,   224,   227,   229,   225,   226,   219,   220,
     221,   228,   230,   321,   323,   320,   318,     0,   315,   317,
     319,   345,     0,   348,     0,     0,   344,   340,   343,     0,
     335,   337,   338,   341,   342,   339,   387,   375,   377,   379,
     381,   383,   385,   374,   373,     0,   363,   364,   368,   369,
     366,   370,   371,   372,   367,   269,   139,     0,   273,   271,
     276,     0,   265,   266,     0,   255,   256,   258,   268,   259,
     260,   261,   275,   262,   263,   264,   300,     0,   298,   299,
     302,   303,     0,   290,   291,   293,   294,   295,   296,   297,
     183,   185,   180,     0,   178,   181,   182,     0,   464,   466,
       0,   469,     0,     0,   473,   477,     0,     0,     0,   482,
     489,   462,     0,   446,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,    42,     0,
       0,    35,     0,     0,     0,     0,     0,    53,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,    99,   399,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     212,     0,     0,     0,   314,     0,     0,     0,     0,     0,
       0,   334,     0,     0,     0,     0,     0,     0,     0,   361,
       0,     0,     0,     0,     0,     0,     0,     0,   253,     0,
       0,     0,   288,     0,     0,     0,     0,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   445,    46,    39,     0,     0,     0,     0,
       0,    57,     0,     0,     0,    91,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     431,     0,     0,    68,     0,   106,   101,   408,   406,   407,
     405,     0,   400,   401,   403,   404,     0,     0,     0,     0,
       0,   242,   243,     0,     0,     0,     0,   214,     0,     0,
     316,     0,   347,     0,   350,   351,   336,     0,     0,     0,
       0,     0,     0,     0,   365,     0,     0,   267,     0,     0,
       0,   278,   257,     0,   304,   292,     0,     0,   179,   463,
       0,     0,   468,     0,   471,   472,     0,     0,   479,   480,
     481,     0,     0,   447,     0,     0,     0,   492,   494,     0,
       0,     0,   205,   246,   281,     0,    43,     0,     0,   170,
       0,     0,     0,     0,    47,   105,     0,   398,     0,   307,
     327,   233,   235,   237,   241,   239,   354,     0,   322,    36,
     324,   346,   349,   388,   376,   378,   380,   382,   384,   386,
     270,   140,   274,   272,   277,   301,   184,   186,   465,   467,
     470,   475,   476,   474,   478,   484,   485,   486,   487,   488,
     483,   490,    40,     0,   500,     0,   497,   499,     0,   126,
     132,   134,   136,     0,     0,     0,     0,     0,   145,   147,
     125,     0,   111,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,     0,   209,     0,   206,   207,
     250,     0,   247,   248,   285,     0,   282,   283,   155,   156,
       0,   151,   153,   154,     0,   164,   165,   161,     0,   159,
     162,   163,   395,     0,   174,     0,   171,   172,     0,     0,
       0,     0,     0,     0,     0,   189,   191,   192,   193,   194,
     195,   196,   421,   427,     0,     0,     0,   420,   419,     0,
     412,   414,   417,   415,   416,   418,   438,   440,     0,   434,
     436,   437,     0,    49,     0,   402,   311,     0,   308,   309,
     331,     0,   328,   329,   358,     0,   355,   356,   391,     0,
      64,     0,     0,   496,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   110,     0,
     204,     0,   254,   245,     0,   289,   280,     0,     0,   150,
     167,     0,   158,     0,   394,     0,   169,     0,     0,     0,
       0,     0,     0,     0,     0,   188,     0,     0,     0,     0,
       0,     0,   411,     0,     0,     0,   433,   443,    51,     0,
      50,   409,     0,   306,     0,     0,   326,     0,   362,   353,
       0,     0,   390,     0,   498,     0,     0,     0,     0,   138,
     141,   142,   143,   144,     0,     0,   112,     0,   208,     0,
     249,     0,   284,   152,   160,   396,     0,   173,   197,   198,
     199,   200,   201,   202,   190,     0,     0,   426,   429,   430,
     413,     0,     0,   435,    48,     0,     0,   310,     0,   330,
       0,   357,     0,     0,   128,   129,   130,   131,   127,   133,
     135,   137,   146,   148,   210,   251,   286,   175,   423,   424,
     425,   422,   428,   439,   441,    52,   312,   332,   359,   392,
     504,     0,   502,     0,     0,   501,   516,     0,   514,   512,
     508,     0,   506,   510,   511,   509,   503,     0,     0,     0,
       0,   505,     0,   513,     0,   507,     0,   515,   520,     0,
     518,     0,     0,   517,   528,     0,     0,     0,     0,   522,
     524,   525,   526,   527,   519,     0,     0,     0,     0,     0,
     521,     0,   530,   531,   532,   523,   529
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,    10,  -498,    72,  -498,  -498,  -498,
    -498,  -498,  -498,    35,  -498,  -172,  -498,  -498,  -498,   -62,
    -498,  -498,  -498,   267,  -498,  -498,  -498,  -498,    71,   249,
     -63,   -50,   -49,   -43,  -498,  -498,  -498,  -498,  -498,    68,
     251,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    73,  -125,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
     -58,  -498,  -497,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -136,  -484,  -498,  -498,  -498,  -498,  -138,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -142,  -498,
    -498,  -498,  -137,   201,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -145,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -119,  -498,  -498,  -498,  -116,   253,  -498,  -498,
    -498,  -498,  -498,  -498,  -487,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -117,  -498,  -498,  -498,  -113,  -498,
     216,  -498,   -59,  -498,  -498,  -498,  -498,  -498,   -57,  -498,
    -498,  -498,  -498,  -498,   -48,  -498,  -498,  -498,  -110,  -498,
    -498,  -498,  -114,  -498,   228,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -146,  -498,  -498,  -498,  -135,
     275,  -498,  -498,   -66,  -498,  -498,  -498,  -498,  -498,  -143,
    -498,  -498,  -498,  -134,   263,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -141,  -498,  -498,  -498,
    -133,  -498,   257,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,    96,  -498,  -498,
    -498,  -498,  -498,  -498,  -115,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -123,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,   106,   232,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   -61,  -498,
    -498,  -498,  -214,  -498,  -498,  -228,  -498,  -498,  -498,  -498,
    -498,  -498,  -239,  -498,  -498,  -254,  -498,  -498,  -498,  -498,
    -498
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   530,    77,
      78,    37,    60,    74,    75,   515,   663,   739,   740,   112,
      39,    62,    85,    86,    87,   293,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   300,    43,    64,   138,
     139,   140,   323,   141,   121,   301,   122,   302,   581,   582,
     583,   685,   808,   584,   686,   585,   687,   586,   688,   587,
     223,   362,   589,   590,   591,   592,   593,   694,   594,   695,
     123,   311,   610,   611,   612,   613,   124,   313,   618,   619,
     620,   621,   125,   312,   126,   315,   625,   626,   627,   715,
      57,    71,   253,   254,   255,   374,   256,   375,   127,   316,
     634,   635,   636,   637,   638,   639,   640,   641,   128,   308,
     597,   598,   599,   699,    45,    65,   159,   160,   161,   330,
     162,   331,   163,   332,   164,   336,   165,   335,   166,   167,
     129,   309,   601,   602,   603,   702,    53,    69,   224,   225,
     226,   227,   228,   229,   230,   361,   231,   365,   232,   364,
     233,   234,   366,   235,   130,   310,   605,   606,   607,   705,
      55,    70,   242,   243,   244,   245,   246,   370,   247,   248,
     249,   169,   328,   667,   668,   669,   742,    47,    66,   177,
     178,   179,   341,   180,   342,   170,   329,   671,   672,   673,
     745,    49,    67,   189,   190,   191,   345,   192,   193,   347,
     194,   195,   171,   337,   675,   676,   677,   748,    51,    68,
     205,   206,   207,   208,   353,   209,   354,   210,   355,   211,
     356,   212,   357,   213,   358,   214,   352,   172,   338,   679,
     751,   131,   314,   623,   327,   431,   432,   433,   434,   435,
     516,   132,   317,   649,   650,   651,   726,   821,   652,   653,
     727,   654,   655,   133,   134,   319,   658,   659,   660,   733,
     661,   734,   135,   320,    59,    72,   272,   273,   274,   275,
     379,   276,   380,   277,   278,   382,   279,   280,   281,   385,
     553,   282,   386,   283,   284,   285,   286,   390,   560,   287,
     391,    88,   295,    89,   296,    90,   294,   565,   566,   567,
     681,   831,   832,   833,   841,   842,   843,   844,   849,   845,
     847,   859,   860,   861,   868,   869,   870,   875,   871,   872,
     873
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   188,   155,   154,   175,   186,   203,   222,   238,   252,
     271,   240,   239,   241,   648,   156,   157,   168,   176,   187,
     204,   622,   158,   617,    34,    27,   142,    28,    79,    29,
     608,   864,   250,   251,   865,   866,   867,   101,    91,    26,
     642,    92,    93,    38,   215,   250,   251,   173,   142,   574,
      94,    95,    96,    97,   174,   656,   657,   101,    94,    95,
      96,    97,    98,    99,   100,   101,   143,   216,   144,   217,
     218,    40,   219,   220,   221,   145,   146,   147,   148,   149,
     150,   101,   216,   101,    42,   708,   151,   152,   709,   102,
     103,   104,   105,   216,   153,   181,   182,   183,   184,   185,
     174,   298,    44,   609,   106,   321,   299,   107,   151,   427,
     322,    83,   136,   137,   108,   643,   644,   645,   646,   101,
     551,   552,   109,   110,   569,   711,   111,    46,   712,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,    80,
     325,   608,   615,    83,   616,   326,   196,   216,    81,    82,
     197,   198,   199,   200,   201,   202,   216,   236,   217,   218,
     237,    48,    83,    83,    30,    31,    32,    33,    83,   339,
     343,    83,    83,   350,   340,   344,   376,   836,   351,   837,
     838,   377,    50,   555,   556,   557,   558,    83,    52,    83,
     628,   629,   630,   631,   632,   633,    54,    56,    83,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   559,   392,   321,   682,   325,   696,   393,
     680,   683,   684,   697,   696,    83,   775,   617,   724,   698,
     731,    58,   735,   725,   648,   732,    84,   736,    76,   392,
     339,   376,   343,    83,   737,   814,   817,   826,   350,   850,
     879,   289,    83,   827,   851,   880,   288,   804,   805,   806,
     807,    83,   290,   713,   834,   428,   714,   835,   862,   429,
     291,   863,   818,   819,   820,   292,   155,   154,   297,   430,
     303,   175,   304,   305,   188,   533,   534,   535,   186,   156,
     157,   168,   306,   307,   318,   176,   158,   324,   203,   394,
     395,   333,   187,   334,   346,   348,   349,   222,   363,   360,
     369,   238,   204,   359,   240,   239,   241,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,   367,
     271,   368,   371,   373,   372,   378,   381,   383,   384,   387,
     388,   389,   396,   397,   398,   399,   400,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   424,   425,
     436,   437,   438,   439,   440,   441,   443,   444,   442,   445,
     446,   448,   449,   451,   453,   457,   452,   454,   455,   458,
     459,   460,   461,   462,   463,   465,   466,   467,   468,   469,
     470,   471,   473,   474,   476,   477,   479,   480,   481,   497,
     498,   482,   483,   484,   485,   486,   487,   488,   489,   491,
     490,   492,   494,   495,   521,   522,   496,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   580,   580,
     510,   511,   588,   588,   512,   513,   514,   517,   518,   647,
     527,   271,   519,   520,   523,   524,   428,   525,   526,   528,
     429,    28,   531,   532,   536,   537,   538,   596,   539,   600,
     430,   540,   604,   541,   624,   664,   666,   670,   678,   674,
     689,   690,   542,   691,   692,   693,   701,   547,   700,   704,
     543,   544,   545,   546,   548,   703,   564,   706,   554,   707,
     710,   716,   717,   743,   562,   549,   718,   719,   720,   550,
     721,   722,   723,   728,   729,   561,   730,   744,   747,   746,
     750,   529,   749,   753,   755,   756,   752,   738,   741,   757,
     758,   764,   765,   785,   786,   791,   792,   795,   759,   794,
     802,   614,   803,   815,   760,   830,   762,   816,   828,   848,
     761,   763,   778,   852,   779,   780,   854,   858,   781,   782,
     856,   876,   877,   878,   881,   401,   563,   568,   783,   787,
     423,   766,   773,   774,   595,   777,   426,   478,   776,   784,
     788,   789,   768,   767,   809,   472,   810,   770,   811,   769,
     812,   771,   447,   813,   822,   823,   824,   772,   797,   825,
     829,   475,   853,   857,   799,   882,   883,   796,   884,   801,
     886,   798,   793,   456,   665,   800,   790,   464,   450,   662,
     846,   754,   855,   874,   493,   885,     0,     0,     0,     0,
       0,     0,     0,     0,   580,     0,   155,   154,   588,     0,
     222,     0,     0,   238,     0,     0,   240,   239,   241,   156,
     157,   168,     0,   252,     0,     0,   158,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   647,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
     175,     0,     0,   186,     0,     0,   203,     0,     0,     0,
       0,     0,     0,     0,   176,     0,     0,   187,     0,     0,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   839,     0,     0,     0,   840,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   839,     0,
       0,     0,   840
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   511,    65,    65,    65,    66,    67,
      68,   508,    65,   507,    14,     5,     7,     7,    10,     9,
      71,   124,    78,    79,   127,   128,   129,    38,    11,     0,
      16,    14,    15,     7,    16,    78,    79,    48,     7,    25,
      31,    32,    33,    34,    55,    97,    98,    38,    31,    32,
      33,    34,    35,    36,    37,    38,    47,    39,    49,    41,
      42,     7,    44,    45,    46,    56,    57,    58,    59,    60,
      61,    38,    39,    38,     7,     3,    67,    68,     6,    62,
      63,    64,    65,    39,    75,    50,    51,    52,    53,    54,
      55,     3,     7,   144,    77,     3,     8,    80,    67,    66,
       8,   144,    12,    13,    87,    91,    92,    93,    94,    38,
     114,   115,    95,    96,    16,     3,    99,     7,     6,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,   121,
       3,    71,    72,   144,    74,     8,    65,    39,   130,   131,
      69,    70,    71,    72,    73,    74,    39,    40,    41,    42,
      43,     7,   144,   144,   144,   145,   146,   147,   144,     3,
       3,   144,   144,     3,     8,     8,     3,   123,     8,   125,
     126,     8,     7,   117,   118,   119,   120,   144,     7,   144,
      81,    82,    83,    84,    85,    86,     7,     7,   144,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   147,     3,     3,     3,     3,     3,     8,
       8,     8,     8,     8,     3,   144,   713,   711,     3,     8,
       3,     7,     3,     8,   731,     8,   298,     8,   144,     3,
       3,     3,     3,   144,     8,     8,     8,     8,     3,     3,
       3,     3,   144,     8,     8,     8,     6,    17,    18,    19,
      20,   144,     4,     3,     3,   327,     6,     6,     3,   327,
       8,     6,    88,    89,    90,     3,   339,   339,     4,   327,
       4,   343,     4,     4,   350,   457,   458,   459,   350,   339,
     339,   339,     4,     4,     4,   343,   339,     4,   360,   289,
     290,     4,   350,     4,     4,     4,     4,   369,     4,     3,
       3,   373,   360,     8,   373,   373,   373,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,     4,
     392,     8,     4,     3,     8,     4,     4,     4,     4,     4,
       4,     4,   144,     4,     4,     4,     4,     4,     4,     4,
     145,   145,   145,   145,   145,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   145,     4,     4,     4,   147,
       4,     4,     4,     4,     4,   145,     4,     4,   147,     4,
       4,     4,     4,     4,     4,     4,   145,   145,   145,     4,
       4,     4,     4,     4,     4,     4,     4,   145,     4,     4,
       4,   147,     4,   147,     4,     4,   147,     4,     4,   399,
     400,   145,     4,   145,   145,     4,     4,   147,   147,     4,
     147,     4,     4,     7,   144,   144,     7,     7,     7,     7,
       5,     5,     5,     5,     5,     5,     5,     5,   500,   501,
       7,     7,   500,   501,     7,     7,     5,     8,     3,   511,
       7,   513,     5,     5,   144,   144,   518,   144,     5,   144,
     518,     7,   144,   144,   144,   144,   144,     7,   144,     7,
     518,   144,     7,   144,     7,     4,     7,     7,    76,     7,
       4,     4,   144,     4,     4,     4,     3,   477,     6,     3,
     144,   144,   144,   144,   144,     6,   122,     6,   116,     3,
       6,     6,     3,     6,   494,   144,     4,     4,     4,   144,
       4,     4,     4,     4,     4,   144,     4,     3,     3,     6,
       3,   449,     6,     4,     4,     4,     8,   144,   144,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   145,     6,
       4,   506,     5,     8,   147,     7,   147,     8,     8,     4,
     145,   145,   145,     4,   145,   145,     4,     7,   145,   145,
       5,     4,     4,     4,     4,   298,   495,   499,   145,   145,
     321,   696,   708,   711,   501,   717,   325,   376,   715,   724,
     145,   145,   701,   699,   144,   369,   144,   704,   144,   702,
     144,   705,   339,   144,   144,   144,   144,   707,   744,   144,
     144,   373,   145,   144,   747,   147,   145,   742,   145,   750,
     144,   745,   735,   350,   518,   748,   731,   360,   343,   513,
     834,   682,   850,   862,   392,   879,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   696,    -1,   699,   699,   696,    -1,
     702,    -1,    -1,   705,    -1,    -1,   705,   705,   705,   699,
     699,   699,    -1,   715,    -1,    -1,   699,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   731,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   745,
     742,    -1,    -1,   745,    -1,    -1,   748,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   742,    -1,    -1,   745,    -1,    -1,
     748,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   833,    -1,    -1,    -1,   833,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   850,    -1,
      -1,    -1,   850
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,     0,     5,     7,     9,
     144,   145,   146,   147,   162,   163,   164,   169,     7,   178,
       7,   184,     7,   195,     7,   272,     7,   335,     7,   349,
       7,   366,     7,   294,     7,   318,     7,   248,     7,   422,
     170,   165,   179,   185,   196,   273,   336,   350,   367,   295,
     319,   249,   423,   162,   171,   172,   144,   167,   168,    10,
     121,   130,   131,   144,   177,   180,   181,   182,   449,   451,
     453,    11,    14,    15,    31,    32,    33,    34,    35,    36,
      37,    38,    62,    63,    64,    65,    77,    80,    87,    95,
      96,    99,   177,   186,   187,   188,   189,   190,   191,   192,
     193,   202,   204,   228,   234,   240,   242,   256,   266,   288,
     312,   389,   399,   411,   412,   420,    12,    13,   197,   198,
     199,   201,     7,    47,    49,    56,    57,    58,    59,    60,
      61,    67,    68,    75,   177,   188,   189,   190,   191,   274,
     275,   276,   278,   280,   282,   284,   286,   287,   312,   329,
     343,   360,   385,    48,    55,   177,   312,   337,   338,   339,
     341,    50,    51,    52,    53,    54,   177,   312,   341,   351,
     352,   353,   355,   356,   358,   359,    65,    69,    70,    71,
      72,    73,    74,   177,   312,   368,   369,   370,   371,   373,
     375,   377,   379,   381,   383,    16,    39,    41,    42,    44,
      45,    46,   177,   218,   296,   297,   298,   299,   300,   301,
     302,   304,   306,   308,   309,   311,    40,    43,   177,   218,
     300,   306,   320,   321,   322,   323,   324,   326,   327,   328,
      78,    79,   177,   250,   251,   252,   254,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   177,   424,   425,   426,   427,   429,   431,   432,   434,
     435,   436,   439,   441,   442,   443,   444,   447,     6,     3,
       4,     8,     3,   183,   454,   450,   452,     4,     3,     8,
     194,   203,   205,     4,     4,     4,     4,     4,   267,   289,
     313,   229,   241,   235,   390,   243,   257,   400,     4,   413,
     421,     3,     8,   200,     4,     3,     8,   392,   330,   344,
     277,   279,   281,     4,     4,   285,   283,   361,   386,     3,
       8,   340,   342,     3,     8,   354,     4,   357,     4,     4,
       3,     8,   384,   372,   374,   376,   378,   380,   382,     8,
       3,   303,   219,     4,   307,   305,   310,     4,     8,     3,
     325,     4,     8,     3,   253,   255,     3,     8,     4,   428,
     430,     4,   433,     4,     4,   437,   440,     4,     4,     4,
     445,   448,     3,     8,   162,   162,   144,     4,     4,     4,
       4,   181,     4,     4,     4,   145,   145,   145,   145,   145,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     145,     4,     4,   187,     4,   147,   198,    66,   177,   218,
     312,   393,   394,   395,   396,   397,     4,     4,     4,     4,
       4,   145,   147,     4,     4,     4,     4,   275,     4,     4,
     338,     4,   145,     4,   145,   145,   352,     4,     4,     4,
       4,     4,     4,     4,   370,     4,     4,   145,     4,     4,
       4,   147,   298,     4,   147,   322,     4,     4,   251,   147,
       4,     4,   145,     4,   145,   145,     4,     4,   147,   147,
     147,     4,     4,   425,     4,     7,     7,   162,   162,     7,
       7,     7,     5,     5,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   173,   398,     8,     3,     5,
       5,   144,   144,   144,   144,   144,     5,     7,   144,   164,
     166,   144,   144,   173,   173,   173,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   162,   144,   144,
     144,   114,   115,   438,   116,   117,   118,   119,   120,   147,
     446,   144,   162,   186,   122,   455,   456,   457,   197,    16,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
     177,   206,   207,   208,   211,   213,   215,   217,   218,   220,
     221,   222,   223,   224,   226,   206,     7,   268,   269,   270,
       7,   290,   291,   292,     7,   314,   315,   316,    71,   144,
     230,   231,   232,   233,   171,    72,    74,   232,   236,   237,
     238,   239,   282,   391,     7,   244,   245,   246,    81,    82,
      83,    84,    85,    86,   258,   259,   260,   261,   262,   263,
     264,   265,    16,    91,    92,    93,    94,   177,   220,   401,
     402,   403,   406,   407,   409,   410,    97,    98,   414,   415,
     416,   418,   424,   174,     4,   395,     7,   331,   332,   333,
       7,   345,   346,   347,     7,   362,   363,   364,    76,   387,
       8,   458,     3,     8,     8,   209,   212,   214,   216,     4,
       4,     4,     4,     4,   225,   227,     3,     8,     8,   271,
       6,     3,   293,     6,     3,   317,     6,     3,     3,     6,
       6,     3,     6,     3,     6,   247,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   404,   408,     4,     4,
       4,     3,     8,   417,   419,     3,     8,     8,   144,   175,
     176,   144,   334,     6,     3,   348,     6,     3,   365,     6,
       3,   388,     8,     4,   456,     4,     4,     4,     4,   145,
     147,   145,   147,   145,     4,     4,   207,   274,   270,   296,
     292,   320,   316,   231,   237,   282,   250,   246,   145,   145,
     145,   145,   145,   145,   259,     4,     4,   145,   145,   145,
     402,     4,     4,   415,     6,     3,   337,   333,   351,   347,
     368,   364,     4,     5,    17,    18,    19,    20,   210,   144,
     144,   144,   144,   144,     8,     8,     8,     8,    88,    89,
      90,   405,   144,   144,   144,   144,     8,     8,     8,   144,
       7,   459,   460,   461,     3,     6,   123,   125,   126,   177,
     218,   462,   463,   464,   465,   467,   460,   468,     4,   466,
       3,     8,     4,   145,     4,   463,     5,   144,     7,   469,
     470,   471,     3,     6,   124,   127,   128,   129,   472,   473,
     474,   476,   477,   478,   470,   475,     4,     4,     4,     3,
       8,     4,   147,   145,   145,   473,   144
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   148,   150,   149,   151,   149,   152,   149,   153,   149,
     154,   149,   155,   149,   156,   149,   157,   149,   158,   149,
     159,   149,   160,   149,   161,   149,   162,   162,   162,   162,
     162,   162,   162,   163,   165,   164,   166,   167,   167,   168,
     168,   170,   169,   171,   171,   172,   172,   174,   173,   175,
     175,   176,   176,   177,   179,   178,   180,   180,   181,   181,
     181,   181,   181,   183,   182,   185,   184,   186,   186,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   188,   189,   190,   191,   192,   194,   193,   196,   195,
     197,   197,   198,   198,   200,   199,   201,   203,   202,   205,
     204,   206,   206,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   209,   208,   210,   210,
     210,   210,   212,   211,   214,   213,   216,   215,   217,   219,
     218,   220,   221,   222,   223,   225,   224,   227,   226,   229,
     228,   230,   230,   231,   231,   232,   233,   235,   234,   236,
     236,   237,   237,   237,   238,   239,   241,   240,   243,   242,
     244,   244,   245,   245,   247,   246,   249,   248,   250,   250,
     250,   251,   251,   253,   252,   255,   254,   257,   256,   258,
     258,   259,   259,   259,   259,   259,   259,   260,   261,   262,
     263,   264,   265,   267,   266,   268,   268,   269,   269,   271,
     270,   273,   272,   274,   274,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   275,   277,   276,   279,   278,   281,   280,   283,   282,
     285,   284,   286,   287,   289,   288,   290,   290,   291,   291,
     293,   292,   295,   294,   296,   296,   297,   297,   298,   298,
     298,   298,   298,   298,   298,   298,   299,   300,   301,   303,
     302,   305,   304,   307,   306,   308,   310,   309,   311,   313,
     312,   314,   314,   315,   315,   317,   316,   319,   318,   320,
     320,   321,   321,   322,   322,   322,   322,   322,   322,   323,
     325,   324,   326,   327,   328,   330,   329,   331,   331,   332,
     332,   334,   333,   336,   335,   337,   337,   338,   338,   338,
     338,   340,   339,   342,   341,   344,   343,   345,   345,   346,
     346,   348,   347,   350,   349,   351,   351,   352,   352,   352,
     352,   352,   352,   352,   352,   354,   353,   355,   357,   356,
     358,   359,   361,   360,   362,   362,   363,   363,   365,   364,
     367,   366,   368,   368,   369,   369,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   372,   371,   374,   373,   376,
     375,   378,   377,   380,   379,   382,   381,   384,   383,   386,
     385,   388,   387,   390,   389,   391,   391,   392,   282,   393,
     393,   394,   394,   395,   395,   395,   395,   396,   398,   397,
     400,   399,   401,   401,   402,   402,   402,   402,   402,   402,
     402,   404,   403,   405,   405,   405,   406,   408,   407,   409,
     410,   411,   413,   412,   414,   414,   415,   415,   417,   416,
     419,   418,   421,   420,   423,   422,   424,   424,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   426,   428,   427,   430,   429,   431,   433,
     432,   434,   435,   437,   436,   438,   438,   440,   439,   441,
     442,   443,   445,   444,   446,   446,   446,   446,   446,   448,
     447,   450,   449,   452,   451,   454,   453,   455,   455,   456,
     458,   457,   459,   459,   461,   460,   462,   462,   463,   463,
     463,   463,   463,   464,   466,   465,   468,   467,   469,   469,
     471,   470,   472,   472,   473,   473,   473,   473,   475,   474,
     476,   477,   478
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
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       3,     3,     3
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
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"mac-sources\"",
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
  "$@46", "reservation_mode", "$@47", "id", "rapid_commit",
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
       0,   228,   228,   228,   229,   229,   230,   230,   231,   231,
     232,   232,   233,   233,   234,   234,   235,   235,   236,   236,
     237,   237,   238,   238,   239,   239,   247,   248,   249,   250,
     251,   252,   253,   256,   261,   261,   272,   275,   276,   279,
     283,   290,   290,   297,   298,   301,   305,   312,   312,   319,
     320,   323,   327,   338,   348,   348,   360,   361,   365,   366,
     367,   368,   369,   372,   372,   389,   389,   397,   398,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   427,   432,   437,   442,   447,   452,   452,   462,   462,
     470,   471,   474,   475,   478,   478,   488,   494,   494,   504,
     504,   514,   515,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   533,   533,   540,   541,
     542,   543,   546,   546,   554,   554,   562,   562,   570,   575,
     575,   583,   588,   593,   598,   603,   603,   611,   611,   620,
     620,   630,   631,   634,   635,   638,   643,   648,   648,   658,
     659,   662,   663,   664,   667,   672,   679,   679,   689,   689,
     699,   700,   703,   704,   707,   707,   715,   715,   723,   724,
     725,   728,   729,   732,   732,   740,   740,   748,   748,   758,
     759,   762,   763,   764,   765,   766,   767,   770,   775,   780,
     785,   790,   795,   803,   803,   816,   817,   820,   821,   828,
     828,   851,   851,   860,   861,   865,   866,   867,   868,   869,
     870,   871,   872,   873,   874,   875,   876,   877,   878,   879,
     880,   881,   884,   884,   892,   892,   900,   900,   908,   908,
     916,   916,   924,   929,   938,   938,   950,   951,   954,   955,
     960,   960,   971,   971,   981,   982,   985,   986,   989,   990,
     991,   992,   993,   994,   995,   996,   999,  1001,  1006,  1008,
    1008,  1016,  1016,  1024,  1024,  1032,  1034,  1034,  1042,  1051,
    1051,  1063,  1064,  1069,  1070,  1075,  1075,  1086,  1086,  1097,
    1098,  1103,  1104,  1109,  1110,  1111,  1112,  1113,  1114,  1117,
    1119,  1119,  1127,  1129,  1131,  1139,  1139,  1151,  1152,  1155,
    1156,  1159,  1159,  1167,  1167,  1175,  1176,  1179,  1180,  1181,
    1182,  1185,  1185,  1193,  1193,  1203,  1203,  1215,  1216,  1219,
    1220,  1223,  1223,  1231,  1231,  1239,  1240,  1243,  1244,  1245,
    1246,  1247,  1248,  1249,  1250,  1253,  1253,  1261,  1266,  1266,
    1274,  1279,  1287,  1287,  1297,  1298,  1301,  1302,  1305,  1305,
    1313,  1313,  1321,  1322,  1325,  1326,  1330,  1331,  1332,  1333,
    1334,  1335,  1336,  1337,  1338,  1341,  1341,  1351,  1351,  1361,
    1361,  1369,  1369,  1377,  1377,  1385,  1385,  1393,  1393,  1406,
    1406,  1416,  1416,  1427,  1427,  1437,  1438,  1441,  1441,  1449,
    1450,  1453,  1454,  1457,  1458,  1459,  1460,  1463,  1465,  1465,
    1476,  1476,  1486,  1487,  1490,  1491,  1492,  1493,  1494,  1495,
    1496,  1499,  1499,  1506,  1507,  1508,  1511,  1516,  1516,  1524,
    1529,  1536,  1543,  1543,  1553,  1554,  1557,  1558,  1561,  1561,
    1569,  1569,  1579,  1579,  1589,  1589,  1597,  1598,  1601,  1602,
    1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,
    1613,  1614,  1615,  1618,  1623,  1623,  1631,  1631,  1639,  1644,
    1644,  1652,  1657,  1662,  1662,  1670,  1671,  1674,  1674,  1682,
    1687,  1692,  1697,  1697,  1705,  1708,  1711,  1714,  1717,  1723,
    1723,  1733,  1733,  1740,  1740,  1752,  1752,  1765,  1766,  1770,
    1774,  1774,  1786,  1787,  1791,  1791,  1799,  1800,  1803,  1804,
    1805,  1806,  1807,  1810,  1815,  1815,  1823,  1823,  1833,  1834,
    1837,  1837,  1845,  1846,  1849,  1850,  1851,  1852,  1855,  1855,
    1863,  1868,  1873
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
#line 4263 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1878 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
