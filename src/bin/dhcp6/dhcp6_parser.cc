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
      case 161: // value
      case 165: // map_value
      case 206: // db_type
      case 401: // duid_type
      case 434: // ncr_protocol_value
      case 442: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 146: // "boolean"
        value.move< bool > (that.value);
        break;

      case 145: // "floating point"
        value.move< double > (that.value);
        break;

      case 144: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 143: // "constant string"
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
      case 161: // value
      case 165: // map_value
      case 206: // db_type
      case 401: // duid_type
      case 434: // ncr_protocol_value
      case 442: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 146: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 145: // "floating point"
        value.copy< double > (that.value);
        break;

      case 144: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 143: // "constant string"
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
            case 143: // "constant string"

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 362 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 144: // "integer"

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 369 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 145: // "floating point"

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 376 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 146: // "boolean"

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 383 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 161: // value

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 390 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 165: // map_value

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 397 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 206: // db_type

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 401: // duid_type

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 411 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 434: // ncr_protocol_value

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 418 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 442: // replace_client_name_value

#line 218 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 161: // value
      case 165: // map_value
      case 206: // db_type
      case 401: // duid_type
      case 434: // ncr_protocol_value
      case 442: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 146: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 145: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 144: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 143: // "constant string"
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
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 682 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 694 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 700 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 712 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 718 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 271 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 850 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 300 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 304 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 326 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 371 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 378 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1034 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 494 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 525 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1233 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 717 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 770 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 788 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1709 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1727 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 956 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1838 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1003 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1071 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1212 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1246 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1372 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1391 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1417 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1491 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1492 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1496 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2623 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2652 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1608 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2927 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3028 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3125 "dhcp6_parser.cc" // lalr1.cc:859
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
     180,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,    47,    20,    63,    80,    95,   102,   113,
     153,   174,   188,   189,   216,   220,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
      20,   -32,    18,    27,   175,    19,    -1,    45,    81,    28,
     117,   -33,    99,  -490,   223,   234,   241,   249,   263,  -490,
    -490,  -490,  -490,   264,  -490,    29,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   265,   268,   270,   272,   273,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   287,
    -490,  -490,  -490,    97,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   285,  -490,  -490,
    -490,  -490,  -490,  -490,   293,   294,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   104,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   116,  -490,  -490,  -490,  -490,   295,  -490,
     296,   298,  -490,  -490,  -490,   136,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   299,   300,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   319,  -490,  -490,  -490,   321,  -490,  -490,
     318,   301,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   323,  -490,  -490,  -490,  -490,   320,   326,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   165,
    -490,  -490,  -490,   327,  -490,  -490,   328,  -490,   329,   330,
    -490,  -490,   331,   332,   333,  -490,  -490,  -490,   166,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    20,    20,  -490,   187,   334,
     335,   336,   337,  -490,    18,  -490,   338,   339,   340,   201,
     202,   203,   204,   205,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   217,   356,   358,    27,  -490,   359,
    -490,    43,   360,   361,   362,   363,   364,   225,   224,   367,
     368,   369,   370,    19,  -490,   371,   372,    -1,  -490,   373,
     235,   374,   239,   242,    45,  -490,   376,   377,   378,   380,
     381,   383,   384,  -490,    81,   385,   386,   247,   388,   389,
     390,   250,  -490,    28,   391,   251,  -490,   117,   394,   395,
     -23,  -490,   254,   397,   400,   262,   401,   266,   267,   403,
     404,   269,   271,   274,   405,   408,    99,  -490,  -490,  -490,
     409,   407,   411,    20,    20,  -490,   412,   414,   415,  -490,
    -490,  -490,  -490,  -490,   418,   419,   420,   421,   422,   423,
     424,   427,   426,   429,  -490,   430,   431,  -490,   434,  -490,
    -490,  -490,  -490,   432,   413,  -490,  -490,  -490,   437,   439,
     302,   303,   304,  -490,  -490,   306,   307,   446,   447,  -490,
     310,   448,  -490,   313,  -490,   314,  -490,  -490,  -490,   434,
     434,   434,   315,   316,   317,   322,  -490,   324,   325,  -490,
     341,   342,   343,  -490,  -490,   344,  -490,  -490,   345,    20,
    -490,  -490,   357,   365,  -490,   366,  -490,  -490,   -30,   375,
    -490,  -490,  -490,    66,   379,  -490,    20,    27,   382,  -490,
    -490,   175,   108,   108,   454,   456,   457,   -39,    20,    70,
      35,   459,   109,    24,    30,    99,  -490,  -490,   465,  -490,
      43,   463,   464,  -490,  -490,  -490,  -490,  -490,   466,   399,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   169,  -490,   172,  -490,  -490,
     467,  -490,  -490,  -490,  -490,   468,   472,   473,   475,   476,
    -490,  -490,  -490,   210,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   211,  -490,   477,
     478,  -490,  -490,   483,   479,  -490,  -490,   485,   489,  -490,
    -490,  -490,   244,  -490,  -490,  -490,   487,  -490,  -490,  -490,
     246,  -490,  -490,  -490,  -490,   255,  -490,   488,   493,  -490,
     494,   495,   497,   498,   500,   501,   212,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   502,   503,   506,  -490,
    -490,   213,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     214,  -490,  -490,  -490,   222,   387,   392,  -490,  -490,   491,
     508,  -490,  -490,   507,   509,  -490,  -490,   510,   511,  -490,
    -490,   512,  -490,   513,   382,  -490,  -490,   514,   515,   517,
     519,   393,   396,   402,   398,   406,   520,   521,   108,  -490,
    -490,    19,  -490,   454,    28,  -490,   456,   117,  -490,   457,
     -39,  -490,  -490,    70,  -490,    35,  -490,   -33,  -490,   459,
     410,   416,   417,   425,   428,   433,   109,  -490,   522,   523,
     435,   436,   438,    24,  -490,   524,   525,    30,  -490,  -490,
    -490,   526,   528,  -490,    -1,  -490,   463,    45,  -490,   464,
      81,  -490,   466,   529,  -490,   531,  -490,   237,   440,   441,
     442,  -490,  -490,  -490,  -490,  -490,   443,   444,  -490,   228,
    -490,   530,  -490,   532,  -490,  -490,  -490,  -490,   230,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   192,   445,  -490,
    -490,  -490,  -490,   449,   450,  -490,  -490,   451,   232,  -490,
     236,  -490,   533,  -490,   452,   527,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   259,  -490,    54,   527,  -490,  -490,   535,
    -490,  -490,  -490,   238,  -490,  -490,  -490,  -490,  -490,   539,
     453,   541,    54,  -490,   542,  -490,   455,  -490,   544,  -490,
    -490,   261,  -490,   -93,   544,  -490,  -490,   545,   548,   549,
     240,  -490,  -490,  -490,  -490,  -490,  -490,   551,   458,   461,
     462,   -93,  -490,   460,  -490,  -490,  -490,  -490,  -490
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   206,    11,   308,    13,   328,    15,
     355,    17,   247,    19,   282,    21,   171,    23,   439,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   357,   249,
     284,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     490,   486,   488,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   102,   104,     0,     0,     0,     0,     0,   198,
     239,   274,   144,   161,   152,   388,   163,   182,   405,     0,
     427,   437,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   100,     0,   392,   300,
     320,   227,   229,   231,     0,     0,   235,   233,   347,   384,
     226,   210,   211,   212,   213,     0,   208,   217,   218,   219,
     222,   224,   220,   221,   214,   215,   216,   223,   225,   316,
     318,   315,   313,     0,   310,   312,   314,   340,     0,   343,
       0,     0,   339,   335,   338,     0,   330,   332,   333,   336,
     337,   334,   382,   370,   372,   374,   376,   378,   380,   369,
     368,     0,   358,   359,   363,   364,   361,   365,   366,   367,
     362,   264,   134,     0,   268,   266,   271,     0,   260,   261,
       0,   250,   251,   253,   263,   254,   255,   256,   270,   257,
     258,   259,   295,     0,   293,   294,   297,   298,     0,   285,
     286,   288,   289,   290,   291,   292,   178,   180,   175,     0,
     173,   176,   177,     0,   459,   461,     0,   464,     0,     0,
     468,   472,     0,     0,     0,   477,   484,   457,     0,   441,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,    42,     0,     0,    35,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      99,   394,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   207,     0,     0,     0,   309,     0,
       0,     0,     0,     0,     0,   329,     0,     0,     0,     0,
       0,     0,     0,   356,     0,     0,     0,     0,     0,     0,
       0,     0,   248,     0,     0,     0,   283,     0,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   440,    46,    39,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    91,
      92,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   426,     0,     0,    68,     0,   403,
     401,   402,   400,     0,   395,   396,   398,   399,     0,     0,
       0,     0,     0,   237,   238,     0,     0,     0,     0,   209,
       0,     0,   311,     0,   342,     0,   345,   346,   331,     0,
       0,     0,     0,     0,     0,     0,   360,     0,     0,   262,
       0,     0,     0,   273,   252,     0,   299,   287,     0,     0,
     174,   458,     0,     0,   463,     0,   466,   467,     0,     0,
     474,   475,   476,     0,     0,   442,     0,     0,     0,   487,
     489,     0,     0,     0,   200,   241,   276,     0,    43,     0,
       0,   165,     0,     0,     0,     0,    47,   101,     0,   393,
       0,   302,   322,   228,   230,   232,   236,   234,   349,     0,
     317,    36,   319,   341,   344,   383,   371,   373,   375,   377,
     379,   381,   265,   135,   269,   267,   272,   296,   179,   181,
     460,   462,   465,   470,   471,   469,   473,   479,   480,   481,
     482,   483,   478,   485,    40,     0,   495,     0,   492,   494,
       0,   121,   127,   129,   131,     0,     0,     0,     0,     0,
     140,   142,   120,     0,   106,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,     0,   204,     0,
     201,   202,   245,     0,   242,   243,   280,     0,   277,   278,
     150,   151,     0,   146,   148,   149,     0,   159,   160,   156,
       0,   154,   157,   158,   390,     0,   169,     0,   166,   167,
       0,     0,     0,     0,     0,     0,     0,   184,   186,   187,
     188,   189,   190,   191,   416,   422,     0,     0,     0,   415,
     414,     0,   407,   409,   412,   410,   411,   413,   433,   435,
       0,   429,   431,   432,     0,    49,     0,   397,   306,     0,
     303,   304,   326,     0,   323,   324,   353,     0,   350,   351,
     386,     0,    64,     0,     0,   491,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     105,     0,   199,     0,   249,   240,     0,   284,   275,     0,
       0,   145,   162,     0,   153,     0,   389,     0,   164,     0,
       0,     0,     0,     0,     0,     0,     0,   183,     0,     0,
       0,     0,     0,     0,   406,     0,     0,     0,   428,   438,
      51,     0,    50,   404,     0,   301,     0,     0,   321,     0,
     357,   348,     0,     0,   385,     0,   493,     0,     0,     0,
       0,   133,   136,   137,   138,   139,     0,     0,   107,     0,
     203,     0,   244,     0,   279,   147,   155,   391,     0,   168,
     192,   193,   194,   195,   196,   197,   185,     0,     0,   421,
     424,   425,   408,     0,     0,   430,    48,     0,     0,   305,
       0,   325,     0,   352,     0,     0,   123,   124,   125,   126,
     122,   128,   130,   132,   141,   143,   205,   246,   281,   170,
     418,   419,   420,   417,   423,   434,   436,    52,   307,   327,
     354,   387,   499,     0,   497,     0,     0,   496,   511,     0,
     509,   507,   503,     0,   501,   505,   506,   504,   498,     0,
       0,     0,     0,   500,     0,   508,     0,   502,     0,   510,
     515,     0,   513,     0,     0,   512,   523,     0,     0,     0,
       0,   517,   519,   520,   521,   522,   514,     0,     0,     0,
       0,     0,   516,     0,   525,   526,   527,   518,   524
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,     9,  -490,    74,  -490,  -490,  -490,
    -490,  -490,  -490,    50,  -490,  -163,  -490,  -490,  -490,   -62,
    -490,  -490,  -490,   276,  -490,  -490,  -490,  -490,    69,   245,
     -63,   -50,   -49,   -43,  -490,  -490,  -490,  -490,  -490,    67,
    -490,  -490,  -490,  -490,  -490,    64,  -129,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   -58,  -490,  -489,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -137,  -475,  -490,  -490,  -490,  -490,  -139,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -144,  -490,  -490,  -490,  -141,
     197,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -148,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -122,
    -490,  -490,  -490,  -118,   243,  -490,  -490,  -490,  -490,  -490,
    -490,  -479,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -121,  -490,  -490,  -490,  -120,  -490,   215,  -490,   -59,
    -490,  -490,  -490,  -490,  -490,   -57,  -490,  -490,  -490,  -490,
    -490,   -48,  -490,  -490,  -490,  -110,  -490,  -490,  -490,  -116,
    -490,   229,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -146,  -490,  -490,  -490,  -143,   275,  -490,  -490,
     -66,  -490,  -490,  -490,  -490,  -490,  -140,  -490,  -490,  -490,
    -136,   256,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -135,  -490,  -490,  -490,  -138,  -490,   257,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,    98,  -490,  -490,  -490,  -490,  -490,
    -490,  -114,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -117,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   110,   227,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   -60,  -490,  -490,  -490,  -210,
    -490,  -490,  -225,  -490,  -490,  -490,  -490,  -490,  -490,  -236,
    -490,  -490,  -252,  -490,  -490,  -490,  -490,  -490
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   522,    77,
      78,    37,    60,    74,    75,   507,   655,   731,   732,   112,
      39,    62,    85,    86,    87,   289,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   296,    43,    64,   137,
     319,   121,   297,   122,   298,   573,   574,   575,   677,   800,
     576,   678,   577,   679,   578,   680,   579,   219,   356,   581,
     582,   583,   584,   585,   686,   586,   687,   123,   307,   602,
     603,   604,   605,   124,   309,   610,   611,   612,   613,   125,
     308,   126,   311,   617,   618,   619,   707,    57,    71,   249,
     250,   251,   368,   252,   369,   127,   312,   626,   627,   628,
     629,   630,   631,   632,   633,   128,   304,   589,   590,   591,
     691,    45,    65,   155,   156,   157,   324,   158,   325,   159,
     326,   160,   330,   161,   329,   162,   163,   129,   305,   593,
     594,   595,   694,    53,    69,   220,   221,   222,   223,   224,
     225,   226,   355,   227,   359,   228,   358,   229,   230,   360,
     231,   130,   306,   597,   598,   599,   697,    55,    70,   238,
     239,   240,   241,   242,   364,   243,   244,   245,   165,   322,
     659,   660,   661,   734,    47,    66,   173,   174,   175,   335,
     176,   336,   166,   323,   663,   664,   665,   737,    49,    67,
     185,   186,   187,   339,   188,   189,   341,   190,   191,   167,
     331,   667,   668,   669,   740,    51,    68,   201,   202,   203,
     204,   347,   205,   348,   206,   349,   207,   350,   208,   351,
     209,   352,   210,   346,   168,   332,   671,   743,   131,   310,
     615,   321,   423,   424,   425,   426,   427,   508,   132,   313,
     641,   642,   643,   718,   813,   644,   645,   719,   646,   647,
     133,   134,   315,   650,   651,   652,   725,   653,   726,   135,
     316,    59,    72,   268,   269,   270,   271,   373,   272,   374,
     273,   274,   376,   275,   276,   277,   379,   545,   278,   380,
     279,   280,   281,   282,   384,   552,   283,   385,    88,   291,
      89,   292,    90,   290,   557,   558,   559,   673,   823,   824,
     825,   833,   834,   835,   836,   841,   837,   839,   851,   852,
     853,   860,   861,   862,   867,   863,   864,   865
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   184,   151,   150,   171,   182,   199,   218,   234,   248,
     267,   236,   235,   237,   640,   152,   153,   164,   172,   183,
     200,   614,   154,    34,   609,    27,   138,    28,    79,    29,
     856,   600,   294,   857,   858,   859,   101,   295,    91,   634,
      92,    93,   138,   211,   246,   247,   169,    26,   566,    94,
      95,    96,    97,   170,   246,   247,   101,    94,    95,    96,
      97,    98,    99,   100,   101,   139,   212,   140,   213,   214,
      38,   215,   216,   217,   141,   142,   143,   144,   145,   146,
     101,   212,   101,   543,   544,   147,   148,    40,   102,   103,
     104,   105,   212,   149,   177,   178,   179,   180,   181,   170,
     317,   147,    42,   106,   601,   318,   107,   333,   419,    44,
      83,    76,   334,   108,   635,   636,   637,   638,   101,   337,
      46,   109,   110,   561,   338,   111,   648,   649,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,    80,   344,
     600,   607,    83,   608,   345,   192,   212,    81,    82,   193,
     194,   195,   196,   197,   198,   212,   232,   213,   214,   233,
      48,    83,    83,    30,    31,    32,    33,    83,   370,   386,
      83,    83,   317,   371,   387,   674,   828,   672,   829,   830,
     675,    50,   547,   548,   549,   550,    83,   136,    83,   620,
     621,   622,   623,   624,   625,    52,    54,    83,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   551,   688,   688,   716,   723,   727,   689,   690,
     717,   724,   728,    56,    83,   386,   767,    58,   609,   284,
     729,   333,    84,   370,   640,   337,   806,   285,   809,   344,
     818,   842,    83,   871,   819,   286,   843,   700,   872,   703,
     701,    83,   704,   796,   797,   798,   799,   287,   705,   420,
      83,   706,   826,   421,   854,   827,   288,   855,   293,   299,
     151,   150,   300,   422,   301,   171,   302,   303,   184,   810,
     811,   812,   182,   152,   153,   164,   525,   526,   527,   172,
     154,   314,   199,   320,   388,   389,   183,   327,   328,   340,
     342,   218,   343,   354,   363,   234,   200,   353,   236,   235,
     237,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   357,   267,   361,   362,   365,   366,   367,
     390,   372,   375,   377,   378,   381,   382,   383,   391,   392,
     393,   394,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     415,   414,   416,   418,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   440,   441,   443,   445,   444,
     449,   450,   451,   446,   452,   453,   447,   454,   455,   457,
     458,   459,   460,   461,   462,   465,   463,   466,   468,   469,
     471,   472,   489,   490,   473,   475,   474,   478,   479,   483,
     476,   477,   484,   486,   487,   480,   510,   481,   488,   491,
     482,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     572,   572,   501,   502,   580,   580,   503,   504,   505,   506,
     509,   639,   511,   267,   512,   513,   514,   515,   420,   516,
     517,   518,   421,   520,   519,    28,   523,   524,   528,   529,
     530,   588,   422,   592,   596,   531,   616,   532,   533,   656,
     658,   662,   681,   666,   670,   676,   682,   683,   539,   684,
     685,   693,   696,   692,   534,   535,   536,   537,   538,   695,
     546,   698,   699,   702,   708,   554,   709,   735,   710,   711,
     540,   712,   713,   556,   714,   715,   720,   721,   541,   542,
     722,   736,   739,   738,   742,   521,   741,   745,   747,   748,
     744,   749,   553,   750,   756,   757,   777,   778,   783,   784,
     730,   787,   786,   794,   822,   733,   795,   751,   807,   840,
     808,   820,   752,   844,   754,   846,   753,   848,   606,   868,
     755,   850,   869,   870,   770,   873,   555,   587,   560,   758,
     771,   772,   417,   765,   766,   769,   768,   470,   776,   773,
     395,   760,   774,   759,   761,   762,   439,   775,   464,   779,
     780,   763,   781,   801,   802,   803,   804,   805,   814,   764,
     789,   788,   815,   816,   817,   821,   467,   845,   849,   791,
     448,   790,   792,   878,   874,   875,   876,   793,   657,   782,
     785,   456,   442,   485,   746,   654,   838,   847,   866,   877,
       0,     0,     0,     0,     0,     0,   572,     0,   151,   150,
     580,     0,   218,     0,     0,   234,     0,     0,   236,   235,
     237,   152,   153,   164,     0,   248,     0,     0,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   639,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   184,   171,     0,     0,   182,     0,     0,   199,     0,
       0,     0,     0,     0,     0,     0,   172,     0,     0,   183,
       0,     0,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   831,     0,     0,     0,   832,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     831,     0,     0,     0,   832
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   503,    65,    65,    65,    66,    67,
      68,   500,    65,    14,   499,     5,     7,     7,    10,     9,
     123,    70,     3,   126,   127,   128,    37,     8,    11,    15,
      13,    14,     7,    15,    77,    78,    47,     0,    24,    30,
      31,    32,    33,    54,    77,    78,    37,    30,    31,    32,
      33,    34,    35,    36,    37,    46,    38,    48,    40,    41,
       7,    43,    44,    45,    55,    56,    57,    58,    59,    60,
      37,    38,    37,   113,   114,    66,    67,     7,    61,    62,
      63,    64,    38,    74,    49,    50,    51,    52,    53,    54,
       3,    66,     7,    76,   143,     8,    79,     3,    65,     7,
     143,   143,     8,    86,    90,    91,    92,    93,    37,     3,
       7,    94,    95,    15,     8,    98,    96,    97,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,   120,     3,
      70,    71,   143,    73,     8,    64,    38,   129,   130,    68,
      69,    70,    71,    72,    73,    38,    39,    40,    41,    42,
       7,   143,   143,   143,   144,   145,   146,   143,     3,     3,
     143,   143,     3,     8,     8,     3,   122,     8,   124,   125,
       8,     7,   116,   117,   118,   119,   143,    12,   143,    80,
      81,    82,    83,    84,    85,     7,     7,   143,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   146,     3,     3,     3,     3,     3,     8,     8,
       8,     8,     8,     7,   143,     3,   705,     7,   703,     6,
       8,     3,   294,     3,   723,     3,     8,     3,     8,     3,
       8,     3,   143,     3,     8,     4,     8,     3,     8,     3,
       6,   143,     6,    16,    17,    18,    19,     8,     3,   321,
     143,     6,     3,   321,     3,     6,     3,     6,     4,     4,
     333,   333,     4,   321,     4,   337,     4,     4,   344,    87,
      88,    89,   344,   333,   333,   333,   449,   450,   451,   337,
     333,     4,   354,     8,   285,   286,   344,     4,     4,     4,
       4,   363,     4,     3,     3,   367,   354,     8,   367,   367,
     367,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,     4,   386,     4,     8,     4,     8,     3,
     143,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   144,   144,   144,   144,   144,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   144,     4,     4,     4,     4,     4,     4,     4,   144,
     146,     4,     4,     4,     4,     4,     4,     4,     4,   144,
       4,     4,     4,   144,     4,     4,   144,     4,     4,     4,
       4,   144,     4,     4,     4,     4,   146,   146,     4,     4,
     146,     4,   393,   394,     4,     4,   144,     4,     4,     4,
     144,   144,     4,     4,     7,   146,     3,   146,     7,     7,
     146,     7,     7,     5,     5,     5,     5,     5,     5,     5,
     492,   493,     5,     7,   492,   493,     7,     7,     7,     5,
       8,   503,     5,   505,     5,   143,   143,   143,   510,   143,
     143,     5,   510,   143,     7,     7,   143,   143,   143,   143,
     143,     7,   510,     7,     7,   143,     7,   143,   143,     4,
       7,     7,     4,     7,    75,     8,     4,     4,   469,     4,
       4,     3,     3,     6,   143,   143,   143,   143,   143,     6,
     115,     6,     3,     6,     6,   486,     3,     6,     4,     4,
     143,     4,     4,   121,     4,     4,     4,     4,   143,   143,
       4,     3,     3,     6,     3,   441,     6,     4,     4,     4,
       8,     4,   143,     4,     4,     4,     4,     4,     4,     4,
     143,     3,     6,     4,     7,   143,     5,   144,     8,     4,
       8,     8,   146,     4,   146,     4,   144,     5,   498,     4,
     144,     7,     4,     4,   144,     4,   487,   493,   491,   688,
     144,   144,   317,   700,   703,   709,   707,   370,   716,   144,
     294,   693,   144,   691,   694,   696,   333,   144,   363,   144,
     144,   697,   144,   143,   143,   143,   143,   143,   143,   699,
     736,   734,   143,   143,   143,   143,   367,   144,   143,   739,
     344,   737,   740,   143,   146,   144,   144,   742,   510,   723,
     727,   354,   337,   386,   674,   505,   826,   842,   854,   871,
      -1,    -1,    -1,    -1,    -1,    -1,   688,    -1,   691,   691,
     688,    -1,   694,    -1,    -1,   697,    -1,    -1,   697,   697,
     697,   691,   691,   691,    -1,   707,    -1,    -1,   691,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   723,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   737,   734,    -1,    -1,   737,    -1,    -1,   740,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   734,    -1,    -1,   737,
      -1,    -1,   740,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   825,    -1,    -1,    -1,   825,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     842,    -1,    -1,    -1,   842
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,     0,     5,     7,     9,
     143,   144,   145,   146,   161,   162,   163,   168,     7,   177,
       7,   183,     7,   194,     7,   268,     7,   331,     7,   345,
       7,   362,     7,   290,     7,   314,     7,   244,     7,   418,
     169,   164,   178,   184,   195,   269,   332,   346,   363,   291,
     315,   245,   419,   161,   170,   171,   143,   166,   167,    10,
     120,   129,   130,   143,   176,   179,   180,   181,   445,   447,
     449,    11,    13,    14,    30,    31,    32,    33,    34,    35,
      36,    37,    61,    62,    63,    64,    76,    79,    86,    94,
      95,    98,   176,   185,   186,   187,   188,   189,   190,   191,
     192,   198,   200,   224,   230,   236,   238,   252,   262,   284,
     308,   385,   395,   407,   408,   416,    12,   196,     7,    46,
      48,    55,    56,    57,    58,    59,    60,    66,    67,    74,
     176,   187,   188,   189,   190,   270,   271,   272,   274,   276,
     278,   280,   282,   283,   308,   325,   339,   356,   381,    47,
      54,   176,   308,   333,   334,   335,   337,    49,    50,    51,
      52,    53,   176,   308,   337,   347,   348,   349,   351,   352,
     354,   355,    64,    68,    69,    70,    71,    72,    73,   176,
     308,   364,   365,   366,   367,   369,   371,   373,   375,   377,
     379,    15,    38,    40,    41,    43,    44,    45,   176,   214,
     292,   293,   294,   295,   296,   297,   298,   300,   302,   304,
     305,   307,    39,    42,   176,   214,   296,   302,   316,   317,
     318,   319,   320,   322,   323,   324,    77,    78,   176,   246,
     247,   248,   250,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   176,   420,   421,
     422,   423,   425,   427,   428,   430,   431,   432,   435,   437,
     438,   439,   440,   443,     6,     3,     4,     8,     3,   182,
     450,   446,   448,     4,     3,     8,   193,   199,   201,     4,
       4,     4,     4,     4,   263,   285,   309,   225,   237,   231,
     386,   239,   253,   396,     4,   409,   417,     3,     8,   197,
       8,   388,   326,   340,   273,   275,   277,     4,     4,   281,
     279,   357,   382,     3,     8,   336,   338,     3,     8,   350,
       4,   353,     4,     4,     3,     8,   380,   368,   370,   372,
     374,   376,   378,     8,     3,   299,   215,     4,   303,   301,
     306,     4,     8,     3,   321,     4,     8,     3,   249,   251,
       3,     8,     4,   424,   426,     4,   429,     4,     4,   433,
     436,     4,     4,     4,   441,   444,     3,     8,   161,   161,
     143,     4,     4,     4,     4,   180,     4,     4,     4,   144,
     144,   144,   144,   144,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   144,     4,     4,   186,     4,    65,
     176,   214,   308,   389,   390,   391,   392,   393,     4,     4,
       4,     4,     4,   144,   146,     4,     4,     4,     4,   271,
       4,     4,   334,     4,   144,     4,   144,   144,   348,     4,
       4,     4,     4,     4,     4,     4,   366,     4,     4,   144,
       4,     4,     4,   146,   294,     4,   146,   318,     4,     4,
     247,   146,     4,     4,   144,     4,   144,   144,     4,     4,
     146,   146,   146,     4,     4,   421,     4,     7,     7,   161,
     161,     7,     7,     7,     5,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   172,   394,     8,
       3,     5,     5,   143,   143,   143,   143,   143,     5,     7,
     143,   163,   165,   143,   143,   172,   172,   172,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   161,
     143,   143,   143,   113,   114,   434,   115,   116,   117,   118,
     119,   146,   442,   143,   161,   185,   121,   451,   452,   453,
     196,    15,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   176,   202,   203,   204,   207,   209,   211,   213,
     214,   216,   217,   218,   219,   220,   222,   202,     7,   264,
     265,   266,     7,   286,   287,   288,     7,   310,   311,   312,
      70,   143,   226,   227,   228,   229,   170,    71,    73,   228,
     232,   233,   234,   235,   278,   387,     7,   240,   241,   242,
      80,    81,    82,    83,    84,    85,   254,   255,   256,   257,
     258,   259,   260,   261,    15,    90,    91,    92,    93,   176,
     216,   397,   398,   399,   402,   403,   405,   406,    96,    97,
     410,   411,   412,   414,   420,   173,     4,   391,     7,   327,
     328,   329,     7,   341,   342,   343,     7,   358,   359,   360,
      75,   383,     8,   454,     3,     8,     8,   205,   208,   210,
     212,     4,     4,     4,     4,     4,   221,   223,     3,     8,
       8,   267,     6,     3,   289,     6,     3,   313,     6,     3,
       3,     6,     6,     3,     6,     3,     6,   243,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   400,   404,
       4,     4,     4,     3,     8,   413,   415,     3,     8,     8,
     143,   174,   175,   143,   330,     6,     3,   344,     6,     3,
     361,     6,     3,   384,     8,     4,   452,     4,     4,     4,
       4,   144,   146,   144,   146,   144,     4,     4,   203,   270,
     266,   292,   288,   316,   312,   227,   233,   278,   246,   242,
     144,   144,   144,   144,   144,   144,   255,     4,     4,   144,
     144,   144,   398,     4,     4,   411,     6,     3,   333,   329,
     347,   343,   364,   360,     4,     5,    16,    17,    18,    19,
     206,   143,   143,   143,   143,   143,     8,     8,     8,     8,
      87,    88,    89,   401,   143,   143,   143,   143,     8,     8,
       8,   143,     7,   455,   456,   457,     3,     6,   122,   124,
     125,   176,   214,   458,   459,   460,   461,   463,   456,   464,
       4,   462,     3,     8,     4,   144,     4,   459,     5,   143,
       7,   465,   466,   467,     3,     6,   123,   126,   127,   128,
     468,   469,   470,   472,   473,   474,   466,   471,     4,     4,
       4,     3,     8,     4,   146,   144,   144,   469,   143
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   147,   149,   148,   150,   148,   151,   148,   152,   148,
     153,   148,   154,   148,   155,   148,   156,   148,   157,   148,
     158,   148,   159,   148,   160,   148,   161,   161,   161,   161,
     161,   161,   161,   162,   164,   163,   165,   166,   166,   167,
     167,   169,   168,   170,   170,   171,   171,   173,   172,   174,
     174,   175,   175,   176,   178,   177,   179,   179,   180,   180,
     180,   180,   180,   182,   181,   184,   183,   185,   185,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   187,   188,   189,   190,   191,   193,   192,   195,   194,
     197,   196,   199,   198,   201,   200,   202,   202,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   205,   204,   206,   206,   206,   206,   208,   207,   210,
     209,   212,   211,   213,   215,   214,   216,   217,   218,   219,
     221,   220,   223,   222,   225,   224,   226,   226,   227,   227,
     228,   229,   231,   230,   232,   232,   233,   233,   233,   234,
     235,   237,   236,   239,   238,   240,   240,   241,   241,   243,
     242,   245,   244,   246,   246,   246,   247,   247,   249,   248,
     251,   250,   253,   252,   254,   254,   255,   255,   255,   255,
     255,   255,   256,   257,   258,   259,   260,   261,   263,   262,
     264,   264,   265,   265,   267,   266,   269,   268,   270,   270,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   273,   272,   275,
     274,   277,   276,   279,   278,   281,   280,   282,   283,   285,
     284,   286,   286,   287,   287,   289,   288,   291,   290,   292,
     292,   293,   293,   294,   294,   294,   294,   294,   294,   294,
     294,   295,   296,   297,   299,   298,   301,   300,   303,   302,
     304,   306,   305,   307,   309,   308,   310,   310,   311,   311,
     313,   312,   315,   314,   316,   316,   317,   317,   318,   318,
     318,   318,   318,   318,   319,   321,   320,   322,   323,   324,
     326,   325,   327,   327,   328,   328,   330,   329,   332,   331,
     333,   333,   334,   334,   334,   334,   336,   335,   338,   337,
     340,   339,   341,   341,   342,   342,   344,   343,   346,   345,
     347,   347,   348,   348,   348,   348,   348,   348,   348,   348,
     350,   349,   351,   353,   352,   354,   355,   357,   356,   358,
     358,   359,   359,   361,   360,   363,   362,   364,   364,   365,
     365,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     368,   367,   370,   369,   372,   371,   374,   373,   376,   375,
     378,   377,   380,   379,   382,   381,   384,   383,   386,   385,
     387,   387,   388,   278,   389,   389,   390,   390,   391,   391,
     391,   391,   392,   394,   393,   396,   395,   397,   397,   398,
     398,   398,   398,   398,   398,   398,   400,   399,   401,   401,
     401,   402,   404,   403,   405,   406,   407,   409,   408,   410,
     410,   411,   411,   413,   412,   415,   414,   417,   416,   419,
     418,   420,   420,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   422,   424,
     423,   426,   425,   427,   429,   428,   430,   431,   433,   432,
     434,   434,   436,   435,   437,   438,   439,   441,   440,   442,
     442,   442,   442,   442,   444,   443,   446,   445,   448,   447,
     450,   449,   451,   451,   452,   454,   453,   455,   455,   457,
     456,   458,   458,   459,   459,   459,   459,   459,   460,   462,
     461,   464,   463,   465,   465,   467,   466,   468,   468,   469,
     469,   469,   469,   471,   470,   472,   473,   474
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
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
  "\"interfaces-config\"", "\"interfaces\"", "\"lease-database\"",
  "\"hosts-database\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
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
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "value", "sub_json",
  "map2", "$@13", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@14", "list_content", "not_empty_list", "list_strings",
  "$@15", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@16", "global_objects",
  "global_object", "dhcp6_object", "$@17", "sub_dhcp6", "$@18",
  "global_params", "global_param", "preferred_lifetime", "valid_lifetime",
  "renew_timer", "rebind_timer", "decline_probation_period",
  "interfaces_config", "$@19", "sub_interfaces6", "$@20",
  "interface_config_map", "$@21", "lease_database", "$@22",
  "hosts_database", "$@23", "database_map_params", "database_map_param",
  "database_type", "$@24", "db_type", "user", "$@25", "password", "$@26",
  "host", "$@27", "port", "name", "$@28", "persist", "lfc_interval",
  "readonly", "connect_timeout", "contact_points", "$@29", "keyspace",
  "$@30", "mac_sources", "$@31", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@32",
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
       0,   227,   227,   227,   228,   228,   229,   229,   230,   230,
     231,   231,   232,   232,   233,   233,   234,   234,   235,   235,
     236,   236,   237,   237,   238,   238,   246,   247,   248,   249,
     250,   251,   252,   255,   260,   260,   271,   274,   275,   278,
     282,   289,   289,   296,   297,   300,   304,   311,   311,   318,
     319,   322,   326,   337,   347,   347,   359,   360,   364,   365,
     366,   367,   368,   371,   371,   388,   388,   396,   397,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   426,   431,   436,   441,   446,   451,   451,   461,   461,
     469,   469,   479,   479,   489,   489,   499,   500,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   518,   518,   525,   526,   527,   528,   531,   531,   539,
     539,   547,   547,   555,   560,   560,   568,   573,   578,   583,
     588,   588,   596,   596,   605,   605,   615,   616,   619,   620,
     623,   628,   633,   633,   643,   644,   647,   648,   649,   652,
     657,   664,   664,   674,   674,   684,   685,   688,   689,   692,
     692,   700,   700,   708,   709,   710,   713,   714,   717,   717,
     725,   725,   733,   733,   743,   744,   747,   748,   749,   750,
     751,   752,   755,   760,   765,   770,   775,   780,   788,   788,
     801,   802,   805,   806,   813,   813,   836,   836,   845,   846,
     850,   851,   852,   853,   854,   855,   856,   857,   858,   859,
     860,   861,   862,   863,   864,   865,   866,   869,   869,   877,
     877,   885,   885,   893,   893,   901,   901,   909,   914,   923,
     923,   935,   936,   939,   940,   945,   945,   956,   956,   966,
     967,   970,   971,   974,   975,   976,   977,   978,   979,   980,
     981,   984,   986,   991,   993,   993,  1001,  1001,  1009,  1009,
    1017,  1019,  1019,  1027,  1036,  1036,  1048,  1049,  1054,  1055,
    1060,  1060,  1071,  1071,  1082,  1083,  1088,  1089,  1094,  1095,
    1096,  1097,  1098,  1099,  1102,  1104,  1104,  1112,  1114,  1116,
    1124,  1124,  1136,  1137,  1140,  1141,  1144,  1144,  1152,  1152,
    1160,  1161,  1164,  1165,  1166,  1167,  1170,  1170,  1178,  1178,
    1188,  1188,  1200,  1201,  1204,  1205,  1208,  1208,  1216,  1216,
    1224,  1225,  1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,
    1238,  1238,  1246,  1251,  1251,  1259,  1264,  1272,  1272,  1282,
    1283,  1286,  1287,  1290,  1290,  1298,  1298,  1306,  1307,  1310,
    1311,  1315,  1316,  1317,  1318,  1319,  1320,  1321,  1322,  1323,
    1326,  1326,  1336,  1336,  1346,  1346,  1354,  1354,  1362,  1362,
    1370,  1370,  1378,  1378,  1391,  1391,  1401,  1401,  1412,  1412,
    1422,  1423,  1426,  1426,  1434,  1435,  1438,  1439,  1442,  1443,
    1444,  1445,  1448,  1450,  1450,  1461,  1461,  1471,  1472,  1475,
    1476,  1477,  1478,  1479,  1480,  1481,  1484,  1484,  1491,  1492,
    1493,  1496,  1501,  1501,  1509,  1514,  1521,  1528,  1528,  1538,
    1539,  1542,  1543,  1546,  1546,  1554,  1554,  1564,  1564,  1574,
    1574,  1582,  1583,  1586,  1587,  1588,  1589,  1590,  1591,  1592,
    1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,  1603,  1608,
    1608,  1616,  1616,  1624,  1629,  1629,  1637,  1642,  1647,  1647,
    1655,  1656,  1659,  1659,  1667,  1672,  1677,  1682,  1682,  1690,
    1693,  1696,  1699,  1702,  1708,  1708,  1718,  1718,  1725,  1725,
    1737,  1737,  1750,  1751,  1755,  1759,  1759,  1771,  1772,  1776,
    1776,  1784,  1785,  1788,  1789,  1790,  1791,  1792,  1795,  1800,
    1800,  1808,  1808,  1818,  1819,  1822,  1822,  1830,  1831,  1834,
    1835,  1836,  1837,  1840,  1840,  1848,  1853,  1858
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
#line 4242 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1863 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
