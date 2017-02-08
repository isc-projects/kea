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
      case 155: // value
      case 159: // map_value
      case 200: // db_type
      case 387: // duid_type
      case 420: // ncr_protocol_value
      case 429: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 140: // "boolean"
        value.move< bool > (that.value);
        break;

      case 139: // "floating point"
        value.move< double > (that.value);
        break;

      case 138: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 137: // "constant string"
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
      case 155: // value
      case 159: // map_value
      case 200: // db_type
      case 387: // duid_type
      case 420: // ncr_protocol_value
      case 429: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 140: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 139: // "floating point"
        value.copy< double > (that.value);
        break;

      case 138: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 137: // "constant string"
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
            case 137: // "constant string"

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 138: // "integer"

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 139: // "floating point"

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 140: // "boolean"

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 155: // value

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 159: // map_value

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 200: // db_type

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 387: // duid_type

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 420: // ncr_protocol_value

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 429: // replace_client_name_value

#line 212 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 155: // value
      case 159: // map_value
      case 200: // db_type
      case 387: // duid_type
      case 420: // ncr_protocol_value
      case 429: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 140: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 139: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 138: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 137: // "constant string"
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
#line 221 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 298 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 316 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 365 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 372 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 382 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 538 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 559 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1575 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1593 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1601 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 834 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 850 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 856 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 872 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1721 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1731 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1739 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1749 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1757 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1774 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1810 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1867 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1038 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1950 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1133 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1308 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2310 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1355 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2580 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2599 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2624 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1685 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3031 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3035 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -490;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     185,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,    46,    19,    91,   113,   117,   119,   160,
     193,   227,   228,   249,   250,   251,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
      19,    16,    17,    31,   182,    23,    37,    68,    62,    32,
     100,    11,   143,  -490,   205,   257,   258,   253,   261,  -490,
    -490,  -490,  -490,   262,  -490,    40,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   263,   264,   265,   268,   270,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   272,
    -490,  -490,  -490,    92,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   269,  -490,  -490,
    -490,  -490,  -490,  -490,   275,   277,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   101,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   147,  -490,  -490,  -490,  -490,   282,  -490,
     283,   284,  -490,  -490,  -490,   158,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     286,   292,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   293,  -490,  -490,  -490,   294,  -490,  -490,   291,   298,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   299,  -490,  -490,  -490,  -490,   314,   303,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   174,  -490,  -490,
    -490,   319,  -490,  -490,   321,  -490,   322,   323,  -490,  -490,
     324,   325,   326,   327,  -490,  -490,  -490,   176,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    19,    19,  -490,   128,   328,
     329,   330,   331,  -490,    17,  -490,   332,   333,   334,   164,
     202,   203,   206,   208,   335,   338,   339,   341,   343,   344,
     345,   346,   347,   348,   215,   350,   351,    31,  -490,   352,
    -490,    48,   353,   354,   355,   356,   357,   224,   223,   360,
     361,   362,   363,    23,  -490,   364,   365,    37,  -490,   366,
     233,   368,   235,   236,    68,  -490,   371,   372,   373,   374,
     375,   376,  -490,    62,   377,   378,   245,   380,   381,   382,
     247,  -490,    32,   384,   252,  -490,   100,   385,   386,   -41,
    -490,   254,   387,   389,   259,   391,   260,   266,   392,   395,
     267,   271,   273,   274,   398,   399,   143,  -490,  -490,  -490,
     401,   402,   403,    19,    19,  -490,   405,   408,   409,  -490,
    -490,  -490,  -490,  -490,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,  -490,   422,   425,  -490,   428,  -490,
    -490,  -490,  -490,   400,   423,  -490,  -490,  -490,   431,   432,
     288,   301,   302,  -490,  -490,   305,   307,   435,   438,  -490,
     309,   440,  -490,   312,  -490,   313,  -490,  -490,  -490,   428,
     428,   428,   316,   317,   318,  -490,   320,   336,  -490,   337,
     340,   342,  -490,  -490,   349,  -490,  -490,   358,    19,  -490,
    -490,   359,   367,  -490,   369,  -490,  -490,     1,   370,  -490,
    -490,  -490,  -490,    49,   379,  -490,    19,    31,   383,  -490,
    -490,   182,    14,    14,   444,   449,   451,   -36,    19,    65,
      34,   452,    66,    84,    83,   143,  -490,  -490,   456,  -490,
      48,   454,   457,  -490,  -490,  -490,  -490,  -490,   458,   396,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   180,  -490,   183,  -490,  -490,   455,
    -490,  -490,  -490,  -490,   462,   464,   465,   466,  -490,   184,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     187,  -490,   470,   468,  -490,  -490,   472,   469,  -490,  -490,
     474,   478,  -490,  -490,  -490,   102,  -490,  -490,  -490,   477,
    -490,  -490,   146,  -490,  -490,  -490,   220,  -490,   479,   481,
    -490,   483,   484,   485,   486,   487,   488,   190,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   490,   493,   494,
    -490,  -490,   194,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   198,  -490,  -490,  -490,   200,   388,   390,  -490,  -490,
     496,   497,  -490,  -490,   499,   500,  -490,  -490,   501,   505,
    -490,  -490,   491,  -490,   506,   383,  -490,  -490,   507,   508,
     509,   510,   393,   394,   397,   404,    14,  -490,  -490,    23,
    -490,   444,    32,  -490,   449,   100,  -490,   451,   -36,  -490,
    -490,    65,  -490,    34,  -490,    11,  -490,   452,   406,   407,
     410,   411,   424,   426,    66,  -490,   511,   513,   427,   429,
     430,    84,  -490,   514,   515,    83,  -490,  -490,  -490,   503,
     517,  -490,    37,  -490,   454,    68,  -490,   457,    62,  -490,
     458,   518,  -490,   516,  -490,   212,   433,   434,   436,  -490,
    -490,  -490,  -490,  -490,   201,  -490,   520,  -490,   521,  -490,
    -490,  -490,  -490,   204,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,   -29,   437,  -490,  -490,  -490,  -490,   439,   441,
    -490,  -490,   442,   207,  -490,   210,  -490,   522,  -490,   443,
     519,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   221,  -490,    59,   519,
    -490,  -490,   527,  -490,  -490,  -490,   211,  -490,  -490,  -490,
    -490,  -490,   530,   445,   531,    59,  -490,   533,  -490,   447,
    -490,   529,  -490,  -490,   230,  -490,   446,   529,  -490,  -490,
     217,  -490,  -490,   535,   446,  -490,   448,  -490,  -490
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   196,    11,   298,    13,   318,    15,
     345,    17,   237,    19,   272,    21,   161,    23,   426,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   347,   239,
     274,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     479,   475,   477,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   102,   104,     0,     0,     0,     0,     0,   188,
     229,   264,   136,   151,   144,   375,   153,   172,   392,     0,
     414,   424,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   100,     0,   379,   290,
     310,   217,   219,   221,     0,     0,   225,   223,   337,   371,
     216,   200,   201,   202,   203,     0,   198,   207,   208,   209,
     212,   214,   210,   211,   204,   205,   206,   213,   215,   306,
     308,   305,   303,     0,   300,   302,   304,   330,     0,   333,
       0,     0,   329,   325,   328,     0,   320,   322,   323,   326,
     327,   324,   369,   359,   361,   363,   365,   367,   358,   357,
       0,   348,   349,   353,   354,   351,   355,   356,   352,   254,
     130,     0,   258,   256,   261,     0,   250,   251,     0,   240,
     241,   243,   253,   244,   245,   246,   260,   247,   248,   249,
     285,     0,   283,   284,   287,   288,     0,   275,   276,   278,
     279,   280,   281,   282,   168,   170,   165,     0,   163,   166,
     167,     0,   447,   449,     0,   452,     0,     0,   456,   460,
       0,     0,     0,     0,   466,   473,   445,     0,   428,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,    42,     0,     0,    35,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      99,   381,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   197,     0,     0,     0,   299,     0,
       0,     0,     0,     0,     0,   319,     0,     0,     0,     0,
       0,     0,   346,     0,     0,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,   273,     0,     0,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   427,    46,    39,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    91,
      92,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   413,     0,     0,    68,     0,   390,
     388,   389,   387,     0,   382,   383,   385,   386,     0,     0,
       0,     0,     0,   227,   228,     0,     0,     0,     0,   199,
       0,     0,   301,     0,   332,     0,   335,   336,   321,     0,
       0,     0,     0,     0,     0,   350,     0,     0,   252,     0,
       0,     0,   263,   242,     0,   289,   277,     0,     0,   164,
     446,     0,     0,   451,     0,   454,   455,     0,     0,   462,
     463,   464,   465,     0,     0,   429,     0,     0,     0,   476,
     478,     0,     0,     0,   190,   231,   266,     0,    43,     0,
       0,   155,     0,     0,     0,     0,    47,   101,     0,   380,
       0,   292,   312,   218,   220,   222,   226,   224,   339,     0,
     307,    36,   309,   331,   334,   370,   360,   362,   364,   366,
     368,   255,   131,   259,   257,   262,   286,   169,   171,   448,
     450,   453,   458,   459,   457,   461,   468,   469,   470,   471,
     472,   467,   474,    40,     0,   484,     0,   481,   483,     0,
     118,   124,   126,   128,     0,     0,     0,     0,   117,     0,
     106,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,   194,     0,   191,   192,   235,     0,   232,   233,   270,
       0,   267,   268,   142,   143,     0,   138,   140,   141,     0,
     150,   148,     0,   146,   149,   377,     0,   159,     0,   156,
     157,     0,     0,     0,     0,     0,     0,     0,   174,   176,
     177,   178,   179,   180,   181,   403,   409,     0,     0,     0,
     402,   401,     0,   394,   396,   399,   397,   398,   400,   420,
     422,     0,   416,   418,   419,     0,    49,     0,   384,   296,
       0,   293,   294,   316,     0,   313,   314,   343,     0,   340,
     341,   373,     0,    64,     0,     0,   480,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   105,     0,
     189,     0,   239,   230,     0,   274,   265,     0,     0,   137,
     152,     0,   145,     0,   376,     0,   154,     0,     0,     0,
       0,     0,     0,     0,     0,   173,     0,     0,     0,     0,
       0,     0,   393,     0,     0,     0,   415,   425,    51,     0,
      50,   391,     0,   291,     0,     0,   311,     0,   347,   338,
       0,     0,   372,     0,   482,     0,     0,     0,     0,   132,
     133,   134,   135,   107,     0,   193,     0,   234,     0,   269,
     139,   147,   378,     0,   158,   182,   183,   184,   185,   186,
     187,   175,     0,     0,   408,   411,   412,   395,     0,     0,
     417,    48,     0,     0,   295,     0,   315,     0,   342,     0,
       0,   120,   121,   122,   123,   119,   125,   127,   129,   195,
     236,   271,   160,   405,   406,   407,   404,   410,   421,   423,
      52,   297,   317,   344,   374,   488,     0,   486,     0,     0,
     485,   500,     0,   498,   496,   492,     0,   490,   494,   495,
     493,   487,     0,     0,     0,     0,   489,     0,   497,     0,
     491,     0,   499,   504,     0,   502,     0,     0,   501,   508,
       0,   506,   503,     0,     0,   505,     0,   507,   509
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,     7,  -490,   -35,  -490,  -490,  -490,
    -490,  -490,  -490,    25,  -490,  -196,  -490,  -490,  -490,   -62,
    -490,  -490,  -490,   246,  -490,  -490,  -490,  -490,    54,   226,
     -63,   -50,   -49,   -43,  -490,  -490,  -490,  -490,  -490,    33,
    -490,  -490,  -490,  -490,  -490,    53,  -129,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   -58,  -490,  -489,  -490,
    -490,  -490,  -490,  -490,  -490,  -138,  -474,  -490,  -490,  -490,
    -490,  -140,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -145,
    -490,  -490,  -490,  -142,   186,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -150,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -125,  -490,  -490,  -490,  -122,   225,  -490,
    -490,  -490,  -490,  -490,  -490,  -477,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -124,  -490,  -490,  -490,  -123,
    -490,   199,  -490,   -59,  -490,  -490,  -490,  -490,  -490,   -57,
    -490,  -490,  -490,  -490,  -490,   -48,  -490,  -490,  -490,  -118,
    -490,  -490,  -490,  -113,  -490,   197,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -149,  -490,  -490,  -490,
    -141,   240,  -490,  -490,   -66,  -490,  -490,  -490,  -490,  -490,
    -139,  -490,  -490,  -490,  -143,   242,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -137,  -490,  -490,
    -490,  -136,  -490,   234,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,    79,  -490,  -490,  -490,
    -490,  -490,  -490,  -121,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -120,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    86,   213,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   -71,  -490,
    -490,  -490,  -213,  -490,  -490,  -228,  -490,  -490,  -490,  -490,
    -490,  -490,  -239,  -490,  -490,  -244,  -490
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   522,    77,
      78,    37,    60,    74,    75,   507,   646,   719,   720,   112,
      39,    62,    85,    86,    87,   289,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   296,    43,    64,   137,
     319,   121,   297,   122,   298,   569,   570,   571,   668,   785,
     572,   669,   573,   670,   574,   671,   217,   355,   576,   577,
     578,   579,   123,   307,   595,   596,   597,   598,   124,   309,
     602,   603,   604,   125,   308,   126,   311,   608,   609,   610,
     695,    57,    71,   247,   248,   249,   367,   250,   368,   127,
     312,   617,   618,   619,   620,   621,   622,   623,   624,   128,
     304,   582,   583,   584,   679,    45,    65,   155,   156,   157,
     324,   158,   325,   159,   326,   160,   330,   161,   329,   162,
     163,   129,   305,   586,   587,   588,   682,    53,    69,   218,
     219,   220,   221,   222,   223,   224,   354,   225,   358,   226,
     357,   227,   228,   359,   229,   130,   306,   590,   591,   592,
     685,    55,    70,   236,   237,   238,   239,   240,   363,   241,
     242,   243,   165,   322,   650,   651,   652,   722,    47,    66,
     173,   174,   175,   335,   176,   336,   166,   323,   654,   655,
     656,   725,    49,    67,   185,   186,   187,   339,   188,   189,
     341,   190,   191,   167,   331,   658,   659,   660,   728,    51,
      68,   200,   201,   202,   203,   347,   204,   348,   205,   349,
     206,   350,   207,   351,   208,   346,   168,   332,   662,   731,
     131,   310,   606,   321,   423,   424,   425,   426,   427,   508,
     132,   313,   632,   633,   634,   706,   796,   635,   636,   707,
     637,   638,   133,   134,   315,   641,   642,   643,   713,   644,
     714,   135,   316,    59,    72,   267,   268,   269,   270,   372,
     271,   373,   272,   273,   375,   274,   275,   276,   378,   544,
     277,   379,   278,   279,   280,   281,   282,   384,   551,   283,
     385,    88,   291,    89,   292,    90,   290,   556,   557,   558,
     664,   806,   807,   808,   816,   817,   818,   819,   824,   820,
     822,   834,   835,   836,   840,   841,   843
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   184,   151,   150,   171,   182,   198,   216,   232,   246,
     266,   234,   233,   235,   631,   152,   153,   164,   172,   183,
     199,    34,   154,   605,    27,   601,    28,    79,    29,   560,
     138,   593,   244,   245,   561,   562,   563,   564,   565,   566,
     567,   138,    91,   294,    92,    93,    26,   209,   295,   210,
      94,    95,    96,    97,   793,   794,   795,   101,    94,    95,
      96,    97,    98,    99,   100,   101,   139,   210,   140,   211,
     212,   101,   213,   214,   215,   141,   142,   143,   144,   145,
     146,   169,   101,   210,   244,   245,   147,   148,   170,   102,
     103,   104,   105,   149,   210,   317,   101,   147,    38,   625,
     318,   594,   101,   106,   333,   688,   107,   564,   689,   334,
     419,   542,   543,   108,   177,   178,   179,   180,   181,   170,
      40,   109,   110,   192,    42,   111,    44,   193,   194,   195,
     196,   197,   593,   600,    80,   210,   230,   211,   212,   231,
      81,    82,   611,   612,   613,   614,   615,   616,    83,   691,
     337,    83,   692,    76,    83,   338,    30,    31,    32,    33,
      83,   344,   546,   547,   548,   549,   345,    46,    83,    83,
     626,   627,   628,   629,    83,   639,   640,   369,   811,   386,
     812,   813,   370,   317,   387,    83,   665,   676,   663,   550,
     676,   666,   677,   704,   136,   678,    83,   711,   705,    83,
      48,   715,   712,   386,   333,    83,   716,   369,   717,   789,
     337,   284,   792,   344,   825,   801,   752,   601,   802,   826,
     844,    83,   631,   693,   809,   845,   694,   810,   781,   782,
     783,   784,    84,   837,    50,    52,   838,    83,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   525,   526,   527,    54,    56,    58,   420,
     285,   287,   286,   421,   288,   390,   293,   299,   300,   301,
     151,   150,   302,   422,   303,   171,   314,   320,   184,   327,
      83,   328,   182,   152,   153,   164,   340,   342,   343,   172,
     154,   198,   388,   389,   352,   353,   183,   356,   360,   361,
     216,   362,   399,   364,   232,   199,   366,   234,   233,   235,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,   365,   371,   266,   374,   376,   377,   380,   381,
     382,   383,   391,   392,   393,   394,   396,   397,   398,   404,
     400,   401,   405,   406,   402,   407,   403,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   418,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   440,   441,
     443,   444,   445,   446,   447,   449,   450,   451,   452,   453,
     454,   456,   457,   458,   459,   460,   461,   462,   464,   467,
     468,   471,   465,   472,   470,   474,   477,   473,   475,   478,
     489,   490,   483,   484,   476,   486,   521,   479,   509,   487,
     488,   480,   491,   481,   482,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   513,   510,   502,   503,   504,
     568,   568,   505,   506,   575,   575,   511,   512,   514,   515,
     518,   630,   516,   266,   517,   519,   520,    28,   420,   523,
     524,   581,   421,   528,   529,   530,   585,   531,   589,   607,
     647,   649,   422,   667,   653,   657,   672,   661,   673,   674,
     675,   681,   684,   532,   533,   538,   680,   534,   683,   535,
     686,   687,   545,   690,   697,   696,   536,   698,   699,   700,
     701,   702,   703,   553,   708,   537,   539,   709,   710,   732,
     724,   555,   723,   727,   540,   726,   541,   729,   730,   771,
     733,   735,   736,   737,   738,   762,   552,   763,   768,   769,
     772,   780,   779,   599,   559,   718,   805,   721,   790,   791,
     803,   823,   740,   739,   827,   829,   833,   741,   831,   846,
     395,   554,   742,   417,   755,   756,   580,   743,   757,   758,
     750,   751,   754,   753,   761,   469,   745,   744,   439,   746,
     747,   463,   759,   466,   760,   764,   839,   765,   766,   749,
     786,   787,   748,   788,   797,   774,   798,   442,   799,   800,
     804,   773,   775,   828,   832,   848,   448,   455,   776,   648,
     767,   645,   777,   778,   734,   770,   821,   830,   842,   485,
     847,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   568,     0,   151,   150,   575,     0,
     216,     0,     0,   232,     0,     0,   234,   233,   235,   152,
     153,   164,     0,   246,     0,     0,   154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   630,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     171,     0,     0,   182,     0,     0,   198,     0,     0,     0,
       0,     0,     0,     0,   172,     0,     0,   183,     0,     0,
     199,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   814,     0,     0,     0,
     815,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   814,     0,     0,     0,   815
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   503,    65,    65,    65,    66,    67,
      68,    14,    65,   500,     5,   499,     7,    10,     9,    15,
       7,    67,    73,    74,    20,    21,    22,    23,    24,    25,
      26,     7,    11,     3,    13,    14,     0,    15,     8,    35,
      27,    28,    29,    30,    83,    84,    85,    34,    27,    28,
      29,    30,    31,    32,    33,    34,    43,    35,    45,    37,
      38,    34,    40,    41,    42,    52,    53,    54,    55,    56,
      57,    44,    34,    35,    73,    74,    63,    64,    51,    58,
      59,    60,    61,    70,    35,     3,    34,    63,     7,    15,
       8,   137,    34,    72,     3,     3,    75,    23,     6,     8,
      62,   110,   111,    82,    46,    47,    48,    49,    50,    51,
       7,    90,    91,    61,     7,    94,     7,    65,    66,    67,
      68,    69,    67,    68,   117,    35,    36,    37,    38,    39,
     123,   124,    76,    77,    78,    79,    80,    81,   137,     3,
       3,   137,     6,   137,   137,     8,   137,   138,   139,   140,
     137,     3,   113,   114,   115,   116,     8,     7,   137,   137,
      86,    87,    88,    89,   137,    92,    93,     3,   119,     3,
     121,   122,     8,     3,     8,   137,     3,     3,     8,   140,
       3,     8,     8,     3,    12,     8,   137,     3,     8,   137,
       7,     3,     8,     3,     3,   137,     8,     3,     8,     8,
       3,     6,     8,     3,     3,     8,   693,   691,     8,     8,
       3,   137,   711,     3,     3,     8,     6,     6,    16,    17,
      18,    19,   294,     3,     7,     7,     6,   137,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   449,   450,   451,     7,     7,     7,   321,
       3,     8,     4,   321,     3,   137,     4,     4,     4,     4,
     333,   333,     4,   321,     4,   337,     4,     8,   344,     4,
     137,     4,   344,   333,   333,   333,     4,     4,     4,   337,
     333,   353,   285,   286,     8,     3,   344,     4,     4,     8,
     362,     3,   138,     4,   366,   353,     3,   366,   366,   366,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,     8,     4,   386,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     138,   138,     4,     4,   138,     4,   138,     4,     4,     4,
       4,     4,     4,   138,     4,     4,     4,     4,     4,     4,
       4,     4,   138,   140,     4,     4,     4,     4,     4,     4,
       4,   138,     4,   138,   138,     4,     4,     4,     4,     4,
       4,     4,     4,   138,     4,     4,     4,   140,     4,     4,
       4,     4,   140,     4,   140,     4,     4,   138,   138,     4,
     393,   394,     4,     4,   138,     4,   441,   140,     8,     7,
       7,   140,     7,   140,   140,     7,     7,     5,     5,     5,
       5,     5,     5,     5,     5,   137,     3,     7,     7,     7,
     492,   493,     7,     5,   492,   493,     5,     5,   137,   137,
       5,   503,   137,   505,   137,     7,   137,     7,   510,   137,
     137,     7,   510,   137,   137,   137,     7,   137,     7,     7,
       4,     7,   510,     8,     7,     7,     4,    71,     4,     4,
       4,     3,     3,   137,   137,   468,     6,   137,     6,   137,
       6,     3,   112,     6,     3,     6,   137,     4,     4,     4,
       4,     4,     4,   486,     4,   137,   137,     4,     4,     8,
       3,   118,     6,     3,   137,     6,   137,     6,     3,     6,
       4,     4,     4,     4,     4,     4,   137,     4,     4,     4,
       3,     5,     4,   498,   491,   137,     7,   137,     8,     8,
       8,     4,   138,   140,     4,     4,     7,   140,     5,     4,
     294,   487,   138,   317,   138,   138,   493,   676,   138,   138,
     688,   691,   697,   695,   704,   369,   681,   679,   333,   682,
     684,   362,   138,   366,   138,   138,   120,   138,   138,   687,
     137,   137,   685,   137,   137,   724,   137,   337,   137,   137,
     137,   722,   725,   138,   137,   137,   344,   353,   727,   510,
     711,   505,   728,   730,   665,   715,   809,   825,   837,   386,
     844,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   676,    -1,   679,   679,   676,    -1,
     682,    -1,    -1,   685,    -1,    -1,   685,   685,   685,   679,
     679,   679,    -1,   695,    -1,    -1,   679,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   711,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   725,
     722,    -1,    -1,   725,    -1,    -1,   728,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   722,    -1,    -1,   725,    -1,    -1,
     728,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   808,    -1,    -1,    -1,
     808,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   825,    -1,    -1,    -1,   825
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,     0,     5,     7,     9,
     137,   138,   139,   140,   155,   156,   157,   162,     7,   171,
       7,   177,     7,   188,     7,   256,     7,   319,     7,   333,
       7,   350,     7,   278,     7,   302,     7,   232,     7,   404,
     163,   158,   172,   178,   189,   257,   320,   334,   351,   279,
     303,   233,   405,   155,   164,   165,   137,   160,   161,    10,
     117,   123,   124,   137,   170,   173,   174,   175,   432,   434,
     436,    11,    13,    14,    27,    28,    29,    30,    31,    32,
      33,    34,    58,    59,    60,    61,    72,    75,    82,    90,
      91,    94,   170,   179,   180,   181,   182,   183,   184,   185,
     186,   192,   194,   213,   219,   224,   226,   240,   250,   272,
     296,   371,   381,   393,   394,   402,    12,   190,     7,    43,
      45,    52,    53,    54,    55,    56,    57,    63,    64,    70,
     170,   181,   182,   183,   184,   258,   259,   260,   262,   264,
     266,   268,   270,   271,   296,   313,   327,   344,   367,    44,
      51,   170,   296,   321,   322,   323,   325,    46,    47,    48,
      49,    50,   170,   296,   325,   335,   336,   337,   339,   340,
     342,   343,    61,    65,    66,    67,    68,    69,   170,   296,
     352,   353,   354,   355,   357,   359,   361,   363,   365,    15,
      35,    37,    38,    40,    41,    42,   170,   207,   280,   281,
     282,   283,   284,   285,   286,   288,   290,   292,   293,   295,
      36,    39,   170,   207,   284,   290,   304,   305,   306,   307,
     308,   310,   311,   312,    73,    74,   170,   234,   235,   236,
     238,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   170,   406,   407,   408,
     409,   411,   413,   414,   416,   417,   418,   421,   423,   424,
     425,   426,   427,   430,     6,     3,     4,     8,     3,   176,
     437,   433,   435,     4,     3,     8,   187,   193,   195,     4,
       4,     4,     4,     4,   251,   273,   297,   214,   225,   220,
     372,   227,   241,   382,     4,   395,   403,     3,     8,   191,
       8,   374,   314,   328,   261,   263,   265,     4,     4,   269,
     267,   345,   368,     3,     8,   324,   326,     3,     8,   338,
       4,   341,     4,     4,     3,     8,   366,   356,   358,   360,
     362,   364,     8,     3,   287,   208,     4,   291,   289,   294,
       4,     8,     3,   309,     4,     8,     3,   237,   239,     3,
       8,     4,   410,   412,     4,   415,     4,     4,   419,   422,
       4,     4,     4,     4,   428,   431,     3,     8,   155,   155,
     137,     4,     4,     4,     4,   174,     4,     4,     4,   138,
     138,   138,   138,   138,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   138,     4,     4,   180,     4,    62,
     170,   207,   296,   375,   376,   377,   378,   379,     4,     4,
       4,     4,     4,   138,   140,     4,     4,     4,     4,   259,
       4,     4,   322,     4,   138,     4,   138,   138,   336,     4,
       4,     4,     4,     4,     4,   354,     4,     4,   138,     4,
       4,     4,   140,   282,     4,   140,   306,     4,     4,   235,
     140,     4,     4,   138,     4,   138,   138,     4,     4,   140,
     140,   140,   140,     4,     4,   407,     4,     7,     7,   155,
     155,     7,     7,     7,     5,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   166,   380,     8,
       3,     5,     5,   137,   137,   137,   137,   137,     5,     7,
     137,   157,   159,   137,   137,   166,   166,   166,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   155,   137,
     137,   137,   110,   111,   420,   112,   113,   114,   115,   116,
     140,   429,   137,   155,   179,   118,   438,   439,   440,   190,
      15,    20,    21,    22,    23,    24,    25,    26,   170,   196,
     197,   198,   201,   203,   205,   207,   209,   210,   211,   212,
     196,     7,   252,   253,   254,     7,   274,   275,   276,     7,
     298,   299,   300,    67,   137,   215,   216,   217,   218,   164,
      68,   217,   221,   222,   223,   266,   373,     7,   228,   229,
     230,    76,    77,    78,    79,    80,    81,   242,   243,   244,
     245,   246,   247,   248,   249,    15,    86,    87,    88,    89,
     170,   209,   383,   384,   385,   388,   389,   391,   392,    92,
      93,   396,   397,   398,   400,   406,   167,     4,   377,     7,
     315,   316,   317,     7,   329,   330,   331,     7,   346,   347,
     348,    71,   369,     8,   441,     3,     8,     8,   199,   202,
     204,   206,     4,     4,     4,     4,     3,     8,     8,   255,
       6,     3,   277,     6,     3,   301,     6,     3,     3,     6,
       6,     3,     6,     3,     6,   231,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   386,   390,     4,     4,
       4,     3,     8,   399,   401,     3,     8,     8,   137,   168,
     169,   137,   318,     6,     3,   332,     6,     3,   349,     6,
       3,   370,     8,     4,   439,     4,     4,     4,     4,   140,
     138,   140,   138,   197,   258,   254,   280,   276,   304,   300,
     216,   222,   266,   234,   230,   138,   138,   138,   138,   138,
     138,   243,     4,     4,   138,   138,   138,   384,     4,     4,
     397,     6,     3,   321,   317,   335,   331,   352,   348,     4,
       5,    16,    17,    18,    19,   200,   137,   137,   137,     8,
       8,     8,     8,    83,    84,    85,   387,   137,   137,   137,
     137,     8,     8,     8,   137,     7,   442,   443,   444,     3,
       6,   119,   121,   122,   170,   207,   445,   446,   447,   448,
     450,   443,   451,     4,   449,     3,     8,     4,   138,     4,
     446,     5,   137,     7,   452,   453,   454,     3,     6,   120,
     455,   456,   453,   457,     3,     8,     4,   456,   137
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   141,   143,   142,   144,   142,   145,   142,   146,   142,
     147,   142,   148,   142,   149,   142,   150,   142,   151,   142,
     152,   142,   153,   142,   154,   142,   155,   155,   155,   155,
     155,   155,   155,   156,   158,   157,   159,   160,   160,   161,
     161,   163,   162,   164,   164,   165,   165,   167,   166,   168,
     168,   169,   169,   170,   172,   171,   173,   173,   174,   174,
     174,   174,   174,   176,   175,   178,   177,   179,   179,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   181,   182,   183,   184,   185,   187,   186,   189,   188,
     191,   190,   193,   192,   195,   194,   196,   196,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   199,   198,
     200,   200,   200,   200,   202,   201,   204,   203,   206,   205,
     208,   207,   209,   210,   211,   212,   214,   213,   215,   215,
     216,   216,   217,   218,   220,   219,   221,   221,   222,   222,
     223,   225,   224,   227,   226,   228,   228,   229,   229,   231,
     230,   233,   232,   234,   234,   234,   235,   235,   237,   236,
     239,   238,   241,   240,   242,   242,   243,   243,   243,   243,
     243,   243,   244,   245,   246,   247,   248,   249,   251,   250,
     252,   252,   253,   253,   255,   254,   257,   256,   258,   258,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   261,   260,   263,
     262,   265,   264,   267,   266,   269,   268,   270,   271,   273,
     272,   274,   274,   275,   275,   277,   276,   279,   278,   280,
     280,   281,   281,   282,   282,   282,   282,   282,   282,   282,
     282,   283,   284,   285,   287,   286,   289,   288,   291,   290,
     292,   294,   293,   295,   297,   296,   298,   298,   299,   299,
     301,   300,   303,   302,   304,   304,   305,   305,   306,   306,
     306,   306,   306,   306,   307,   309,   308,   310,   311,   312,
     314,   313,   315,   315,   316,   316,   318,   317,   320,   319,
     321,   321,   322,   322,   322,   322,   324,   323,   326,   325,
     328,   327,   329,   329,   330,   330,   332,   331,   334,   333,
     335,   335,   336,   336,   336,   336,   336,   336,   336,   336,
     338,   337,   339,   341,   340,   342,   343,   345,   344,   346,
     346,   347,   347,   349,   348,   351,   350,   352,   352,   353,
     353,   354,   354,   354,   354,   354,   354,   354,   354,   356,
     355,   358,   357,   360,   359,   362,   361,   364,   363,   366,
     365,   368,   367,   370,   369,   372,   371,   373,   373,   374,
     266,   375,   375,   376,   376,   377,   377,   377,   377,   378,
     380,   379,   382,   381,   383,   383,   384,   384,   384,   384,
     384,   384,   384,   386,   385,   387,   387,   387,   388,   390,
     389,   391,   392,   393,   395,   394,   396,   396,   397,   397,
     399,   398,   401,   400,   403,   402,   405,   404,   406,   406,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   408,   410,   409,   412,
     411,   413,   415,   414,   416,   417,   419,   418,   420,   420,
     422,   421,   423,   424,   425,   426,   428,   427,   429,   429,
     429,   429,   429,   431,   430,   433,   432,   435,   434,   437,
     436,   438,   438,   439,   441,   440,   442,   442,   444,   443,
     445,   445,   446,   446,   446,   446,   446,   447,   449,   448,
     451,   450,   452,   452,   454,   453,   455,   455,   457,   456
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
       0,     4,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"record-types\"", "\"encapsulate\"",
  "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"", "\"prefix\"",
  "\"prefix-len\"", "\"excluded-prefix\"", "\"excluded-prefix-len\"",
  "\"delegated-len\"", "\"user-context\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"allow-client-update\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"Dhcp4\"", "\"DhcpDdns\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
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
  "sub_interfaces6", "$@20", "interface_config_map", "$@21",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "database_type", "$@24",
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "name",
  "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
  "mac_sources", "$@29", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@30",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "relay_supplied_options", "$@31", "hooks_libraries",
  "$@32", "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@33", "sub_hooks_library", "$@34", "hooks_params",
  "hooks_param", "library", "$@35", "parameters", "$@36",
  "expired_leases_processing", "$@37", "expired_leases_params",
  "expired_leases_param", "reclaim_timer_wait_time",
  "flush_reclaimed_timer_wait_time", "hold_reclaimed_time",
  "max_reclaim_leases", "max_reclaim_time", "unwarned_reclaim_cycles",
  "subnet6_list", "$@38", "subnet6_list_content", "not_empty_subnet6_list",
  "subnet6", "$@39", "sub_subnet6", "$@40", "subnet6_params",
  "subnet6_param", "subnet", "$@41", "interface", "$@42", "interface_id",
  "$@43", "client_class", "$@44", "reservation_mode", "$@45", "id",
  "rapid_commit", "option_def_list", "$@46", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@47",
  "sub_option_def", "$@48", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@49",
  "option_def_record_types", "$@50", "space", "$@51", "option_def_space",
  "option_def_encapsulate", "$@52", "option_def_array", "option_data_list",
  "$@53", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@54", "sub_option_data", "$@55",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@56",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "pools_list", "$@57", "pools_list_content", "not_empty_pools_list",
  "pool_list_entry", "$@58", "sub_pool6", "$@59", "pool_params",
  "pool_param", "pool_entry", "$@60", "user_context", "$@61",
  "pd_pools_list", "$@62", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@63", "sub_pd_pool",
  "$@64", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@65",
  "pd_prefix_len", "excluded_prefix", "$@66", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@67", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@68", "sub_reservation",
  "$@69", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@70", "prefixes", "$@71", "duid",
  "$@72", "hw_address", "$@73", "hostname", "$@74",
  "reservation_client_classes", "$@75", "relay", "$@76", "relay_map",
  "$@77", "client_classes", "$@78", "client_classes_list", "$@79",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@80",
  "server_id", "$@81", "server_id_params", "server_id_param",
  "server_id_type", "$@82", "duid_type", "htype", "identifier", "$@83",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@84",
  "control_socket_params", "control_socket_param", "socket_type", "$@85",
  "socket_name", "$@86", "dhcp_ddns", "$@87", "sub_dhcp_ddns", "$@88",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@89", "server_ip", "$@90", "server_port",
  "sender_ip", "$@91", "sender_port", "max_queue_size", "ncr_protocol",
  "$@92", "ncr_protocol_value", "ncr_format", "$@93",
  "always_include_fqdn", "allow_client_update", "override_no_update",
  "override_client_update", "replace_client_name", "$@94",
  "replace_client_name_value", "generated_prefix", "$@95",
  "dhcp4_json_object", "$@96", "dhcpddns_json_object", "$@97",
  "logging_object", "$@98", "logging_params", "logging_param", "loggers",
  "$@99", "loggers_entries", "logger_entry", "$@100", "logger_params",
  "logger_param", "debuglevel", "severity", "$@101", "output_options_list",
  "$@102", "output_options_list_content", "output_entry", "$@103",
  "output_params", "output_param", "$@104", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   221,   221,   221,   222,   222,   223,   223,   224,   224,
     225,   225,   226,   226,   227,   227,   228,   228,   229,   229,
     230,   230,   231,   231,   232,   232,   240,   241,   242,   243,
     244,   245,   246,   249,   254,   254,   265,   268,   269,   272,
     276,   283,   283,   290,   291,   294,   298,   305,   305,   312,
     313,   316,   320,   331,   341,   341,   353,   354,   358,   359,
     360,   361,   362,   365,   365,   382,   382,   390,   391,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   420,   425,   430,   435,   440,   445,   445,   455,   455,
     463,   463,   473,   473,   483,   483,   493,   494,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   509,   509,
     516,   517,   518,   519,   522,   522,   530,   530,   538,   538,
     546,   546,   554,   559,   564,   569,   574,   574,   584,   585,
     588,   589,   592,   597,   602,   602,   612,   613,   616,   617,
     620,   627,   627,   637,   637,   647,   648,   651,   652,   655,
     655,   663,   663,   671,   672,   673,   676,   677,   680,   680,
     688,   688,   696,   696,   706,   707,   710,   711,   712,   713,
     714,   715,   718,   723,   728,   733,   738,   743,   751,   751,
     764,   765,   768,   769,   776,   776,   799,   799,   808,   809,
     813,   814,   815,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   832,   832,   840,
     840,   848,   848,   856,   856,   864,   864,   872,   877,   886,
     886,   898,   899,   902,   903,   908,   908,   919,   919,   929,
     930,   933,   934,   937,   938,   939,   940,   941,   942,   943,
     944,   947,   949,   954,   956,   956,   964,   964,   972,   972,
     980,   982,   982,   990,   999,   999,  1011,  1012,  1017,  1018,
    1023,  1023,  1034,  1034,  1045,  1046,  1051,  1052,  1057,  1058,
    1059,  1060,  1061,  1062,  1065,  1067,  1067,  1075,  1077,  1079,
    1087,  1087,  1099,  1100,  1103,  1104,  1107,  1107,  1115,  1115,
    1123,  1124,  1127,  1128,  1129,  1130,  1133,  1133,  1141,  1141,
    1151,  1151,  1163,  1164,  1167,  1168,  1171,  1171,  1179,  1179,
    1187,  1188,  1191,  1192,  1193,  1194,  1195,  1196,  1197,  1198,
    1201,  1201,  1209,  1214,  1214,  1222,  1227,  1235,  1235,  1245,
    1246,  1249,  1250,  1253,  1253,  1261,  1261,  1269,  1270,  1273,
    1274,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1288,
    1288,  1298,  1298,  1308,  1308,  1316,  1316,  1324,  1324,  1332,
    1332,  1345,  1345,  1355,  1355,  1366,  1366,  1376,  1377,  1380,
    1380,  1388,  1389,  1392,  1393,  1396,  1397,  1398,  1399,  1402,
    1404,  1404,  1415,  1415,  1425,  1426,  1429,  1430,  1431,  1432,
    1433,  1434,  1435,  1438,  1438,  1445,  1446,  1447,  1450,  1455,
    1455,  1463,  1468,  1475,  1482,  1482,  1492,  1493,  1496,  1497,
    1500,  1500,  1508,  1508,  1518,  1518,  1528,  1528,  1536,  1537,
    1540,  1541,  1542,  1543,  1544,  1545,  1546,  1547,  1548,  1549,
    1550,  1551,  1552,  1553,  1554,  1555,  1558,  1563,  1563,  1571,
    1571,  1579,  1584,  1584,  1592,  1597,  1602,  1602,  1610,  1611,
    1614,  1614,  1622,  1627,  1632,  1637,  1642,  1642,  1650,  1653,
    1656,  1659,  1662,  1668,  1668,  1678,  1678,  1685,  1685,  1697,
    1697,  1710,  1711,  1715,  1719,  1719,  1731,  1732,  1736,  1736,
    1744,  1745,  1748,  1749,  1750,  1751,  1752,  1755,  1760,  1760,
    1768,  1768,  1778,  1779,  1782,  1782,  1790,  1791,  1794,  1794
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
#line 4127 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1802 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
