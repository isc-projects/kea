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
      case 154: // value
      case 198: // db_type
      case 383: // duid_type
      case 416: // ncr_protocol_value
      case 425: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 139: // "boolean"
        value.move< bool > (that.value);
        break;

      case 138: // "floating point"
        value.move< double > (that.value);
        break;

      case 137: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 136: // "constant string"
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
      case 154: // value
      case 198: // db_type
      case 383: // duid_type
      case 416: // ncr_protocol_value
      case 425: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 139: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 138: // "floating point"
        value.copy< double > (that.value);
        break;

      case 137: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 136: // "constant string"
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
            case 136: // "constant string"

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 360 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 137: // "integer"

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 367 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 138: // "floating point"

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 374 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 139: // "boolean"

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 381 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 154: // value

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 388 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 198: // db_type

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 395 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 383: // duid_type

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 402 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 416: // ncr_protocol_value

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 409 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 425: // replace_client_name_value

#line 210 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 416 "dhcp6_parser.cc" // lalr1.cc:636
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
      case 154: // value
      case 198: // db_type
      case 383: // duid_type
      case 416: // ncr_protocol_value
      case 425: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 139: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 138: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 137: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 136: // "constant string"
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
#line 219 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 220 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 221 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 222 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 678 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 223 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 224 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 316 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 382 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 998 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1037 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1045 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 479 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1113 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 512 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 514 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 520 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1182 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1265 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1274 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1283 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1292 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 616 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1321 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1332 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 628 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1341 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1352 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 697 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1479 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1497 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1517 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 776 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 828 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1649 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rm(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1685 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 887 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 908 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 945 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1804 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 978 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1812 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 995 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1063 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1914 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1103 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1978 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 1988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 1999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1144 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2008 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1163 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2079 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2257 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2305 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1367 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1391 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1425 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2420 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2426 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2508 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2547 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2556 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2566 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2601 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2619 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2628 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2664 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2681 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2687 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2897 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 2942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1754 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 2953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 2998 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3002 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -497;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     181,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,    30,    19,    25,    31,    43,    75,    85,
     111,   120,   137,   154,   164,   170,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
      19,    27,    17,    26,   183,    18,    -1,   100,    64,    53,
      40,   -31,   144,  -497,   206,   232,   233,   249,   258,  -497,
    -497,  -497,  -497,   259,  -497,    41,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,   260,   261,   262,   265,   266,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   268,
    -497,  -497,  -497,   114,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,   254,  -497,  -497,
    -497,  -497,  -497,  -497,   269,   270,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,   117,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,   118,  -497,  -497,  -497,   271,  -497,   272,   273,
    -497,  -497,   133,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,   276,   278,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   288,  -497,
    -497,  -497,   290,  -497,  -497,   287,   294,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   295,  -497,
    -497,  -497,  -497,   293,   299,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,   135,  -497,  -497,  -497,   313,  -497,
    -497,   314,  -497,   315,   317,  -497,  -497,   318,   319,   320,
     321,  -497,  -497,  -497,   156,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,    19,    19,  -497,   190,   323,   324,   325,   326,
    -497,    17,  -497,   327,   328,   329,   197,   200,   201,   202,
     203,   331,   332,   337,   338,   339,   340,   341,   342,   343,
     344,   212,   346,   347,    26,  -497,   348,  -497,     1,   349,
     350,   351,   352,   353,   221,   220,   356,   357,   358,   359,
      18,  -497,   360,    -1,  -497,   361,   229,   363,   231,   234,
     100,  -497,   365,   366,   368,   369,   370,   371,  -497,    64,
     372,   373,   241,   375,   376,   377,   243,  -497,    53,   379,
     245,  -497,    40,   381,   382,    29,  -497,   248,   384,   385,
     253,   387,   255,   256,   390,   391,   257,   263,   264,   267,
     395,   396,   144,  -497,  -497,  -497,   397,   398,   400,    19,
      19,  -497,   401,   402,   403,  -497,  -497,  -497,  -497,  -497,
     399,   406,   407,   408,   409,   410,   411,   412,   413,   414,
    -497,   415,   416,  -497,   419,  -497,  -497,  -497,  -497,   420,
     424,  -497,  -497,  -497,   426,   427,   282,   283,   297,  -497,
    -497,   298,   301,   430,   432,  -497,   304,  -497,   305,  -497,
     306,  -497,  -497,  -497,   419,   419,   419,   308,   309,   310,
    -497,   312,   316,  -497,   322,   330,   333,  -497,  -497,   334,
    -497,  -497,   336,    19,  -497,  -497,   345,   354,  -497,   355,
    -497,  -497,    42,   362,  -497,  -497,  -497,  -497,    66,   364,
    -497,    19,    26,   367,  -497,  -497,   183,    88,    88,   442,
     443,   444,   -37,    19,   192,    44,   446,   107,    81,   131,
     144,  -497,  -497,   451,  -497,     1,   449,   450,  -497,  -497,
    -497,  -497,  -497,   452,   392,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,   157,  -497,   185,
    -497,  -497,   453,  -497,  -497,  -497,  -497,   456,   459,   460,
     461,  -497,   188,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,   189,  -497,   462,   464,  -497,  -497,   468,
     472,  -497,  -497,   470,   474,  -497,  -497,  -497,    28,  -497,
    -497,  -497,   473,  -497,  -497,   139,  -497,  -497,  -497,   167,
    -497,   476,   475,  -497,   479,   481,   482,   483,   484,   488,
     191,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
     489,   490,   491,  -497,  -497,   195,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,   198,  -497,  -497,  -497,   199,   374,
     378,  -497,  -497,   492,   477,  -497,  -497,   493,   494,  -497,
    -497,   495,   499,  -497,  -497,   496,  -497,   501,   367,  -497,
    -497,   502,   503,   504,   505,   380,   383,   386,   389,    88,
    -497,  -497,    18,  -497,   442,    53,  -497,   443,    40,  -497,
     444,   -37,  -497,  -497,   192,  -497,    44,  -497,   -31,  -497,
     446,   393,   394,   404,   405,   417,   418,   107,  -497,   507,
     508,   421,   422,   423,    81,  -497,   509,   511,   131,  -497,
    -497,  -497,   497,   513,  -497,    -1,  -497,   449,   100,  -497,
     450,    64,  -497,   452,   514,  -497,   512,  -497,    48,   388,
     425,   428,  -497,  -497,  -497,  -497,  -497,   207,  -497,   515,
    -497,   519,  -497,  -497,  -497,  -497,   208,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,   150,   429,  -497,  -497,  -497,
    -497,   431,   433,  -497,  -497,   434,   210,  -497,   211,  -497,
     520,  -497,   435,   522,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,   224,
    -497,    54,   522,  -497,  -497,   517,  -497,  -497,  -497,   217,
    -497,  -497,  -497,  -497,  -497,   518,   436,   528,    54,  -497,
     529,  -497,   438,  -497,   526,  -497,  -497,   225,  -497,   437,
     526,  -497,  -497,   218,  -497,  -497,   531,   437,  -497,   439,
    -497,  -497
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    40,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    53,     5,
      64,     7,    97,     9,   195,    11,   297,    13,   314,    15,
     340,    17,   236,    19,   271,    21,   160,    23,   421,    25,
      42,    36,     0,     0,     0,     0,     0,     0,   342,   238,
     273,     0,     0,    44,     0,    43,     0,     0,    37,    62,
     474,   470,   472,     0,    61,     0,    55,    57,    59,    60,
      58,    95,   101,   103,     0,     0,     0,     0,     0,   187,
     228,   263,   135,   150,   143,   370,   152,   171,   387,     0,
     409,   419,    89,     0,    66,    68,    69,    70,    71,    72,
      74,    75,    76,    77,    79,    78,    83,    84,    73,    81,
      82,    80,    85,    86,    87,    88,    99,     0,   374,   289,
     306,   216,   218,   220,     0,     0,   224,   222,   332,   366,
     215,   199,   200,   201,   202,     0,   197,   206,   207,   208,
     211,   213,   209,   210,   203,   204,   205,   212,   214,   304,
     303,   302,     0,   299,   301,   325,     0,   328,     0,     0,
     324,   321,     0,   316,   318,   319,   322,   323,   320,   364,
     354,   356,   358,   360,   362,   353,   352,     0,   343,   344,
     348,   349,   346,   350,   351,   347,   253,   129,     0,   257,
     255,   260,     0,   249,   250,     0,   239,   240,   242,   252,
     243,   244,   245,   259,   246,   247,   248,   284,     0,   282,
     283,   286,   287,     0,   274,   275,   277,   278,   279,   280,
     281,   167,   169,   164,     0,   162,   165,   166,     0,   442,
     444,     0,   447,     0,     0,   451,   455,     0,     0,     0,
       0,   461,   468,   440,     0,   423,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,    41,     0,     0,    35,     0,     0,     0,     0,     0,
      52,     0,    54,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,     0,    98,   376,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   196,     0,     0,   298,     0,     0,     0,     0,     0,
       0,   315,     0,     0,     0,     0,     0,     0,   341,     0,
       0,     0,     0,     0,     0,     0,     0,   237,     0,     0,
       0,   272,     0,     0,     0,     0,   161,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   422,    45,    38,     0,     0,     0,     0,
       0,    56,     0,     0,     0,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     408,     0,     0,    67,     0,   385,   383,   384,   382,     0,
     377,   378,   380,   381,     0,     0,     0,     0,     0,   226,
     227,     0,     0,     0,     0,   198,     0,   300,     0,   327,
       0,   330,   331,   317,     0,     0,     0,     0,     0,     0,
     345,     0,     0,   251,     0,     0,     0,   262,   241,     0,
     288,   276,     0,     0,   163,   441,     0,     0,   446,     0,
     449,   450,     0,     0,   457,   458,   459,   460,     0,     0,
     424,     0,     0,     0,   471,   473,     0,     0,     0,   189,
     230,   265,     0,    42,     0,     0,   154,     0,     0,     0,
       0,    46,   100,     0,   375,     0,   291,   308,   217,   219,
     221,   225,   223,   334,     0,   305,   326,   329,   365,   355,
     357,   359,   361,   363,   254,   130,   258,   256,   261,   285,
     168,   170,   443,   445,   448,   453,   454,   452,   456,   463,
     464,   465,   466,   467,   462,   469,    39,     0,   479,     0,
     476,   478,     0,   117,   123,   125,   127,     0,     0,     0,
       0,   116,     0,   105,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     0,   193,     0,   190,   191,   234,     0,
     231,   232,   269,     0,   266,   267,   141,   142,     0,   137,
     139,   140,     0,   149,   147,     0,   145,   148,   372,     0,
     158,     0,   155,   156,     0,     0,     0,     0,     0,     0,
       0,   173,   175,   176,   177,   178,   179,   180,   398,   404,
       0,     0,     0,   397,   396,     0,   389,   391,   394,   392,
     393,   395,   415,   417,     0,   411,   413,   414,     0,    48,
       0,   379,   295,     0,   292,   293,   312,     0,   309,   310,
     338,     0,   335,   336,   368,     0,    63,     0,     0,   475,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     102,   104,     0,   188,     0,   238,   229,     0,   273,   264,
       0,     0,   136,   151,     0,   144,     0,   371,     0,   153,
       0,     0,     0,     0,     0,     0,     0,     0,   172,     0,
       0,     0,     0,     0,     0,   388,     0,     0,     0,   410,
     420,    50,     0,    49,   386,     0,   290,     0,     0,   307,
       0,   342,   333,     0,     0,   367,     0,   477,     0,     0,
       0,     0,   131,   132,   133,   134,   106,     0,   192,     0,
     233,     0,   268,   138,   146,   373,     0,   157,   181,   182,
     183,   184,   185,   186,   174,     0,     0,   403,   406,   407,
     390,     0,     0,   412,    47,     0,     0,   294,     0,   311,
       0,   337,     0,     0,   119,   120,   121,   122,   118,   124,
     126,   128,   194,   235,   270,   159,   400,   401,   402,   399,
     405,   416,   418,    51,   296,   313,   339,   369,   483,     0,
     481,     0,     0,   480,   495,     0,   493,   491,   487,     0,
     485,   489,   490,   488,   482,     0,     0,     0,     0,   484,
       0,   492,     0,   486,     0,   494,   499,     0,   497,     0,
       0,   496,   503,     0,   501,   498,     0,     0,   500,     0,
     502,   504
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,     8,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,     3,  -497,  -191,  -497,  -497,  -497,   -62,  -497,
    -497,  -497,   246,  -497,  -497,  -497,  -497,    56,   222,   -47,
     -45,   -44,   -42,  -497,  -497,  -497,  -497,  -497,    57,  -497,
    -497,  -497,  -497,  -497,    51,  -129,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,   -58,  -497,  -496,  -497,  -497,
    -497,  -497,  -497,  -497,  -137,  -475,  -497,  -497,  -497,  -497,
    -139,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -144,  -497,
    -497,  -497,  -141,   184,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -149,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -124,  -497,  -497,  -497,  -121,   223,  -497,  -497,
    -497,  -497,  -497,  -497,  -482,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -125,  -497,  -497,  -497,  -118,  -497,
     204,  -497,   -69,  -497,  -497,  -497,  -497,  -497,   -59,  -497,
    -497,  -497,  -497,  -497,   -51,  -497,  -497,  -497,  -117,  -497,
    -497,  -497,  -112,  -497,   214,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -145,  -497,  -497,  -497,  -147,
     244,  -497,  -497,  -497,  -497,  -497,  -497,  -142,  -497,  -497,
    -497,  -138,   239,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -140,  -497,  -497,  -497,  -136,  -497,
     235,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,    76,  -497,  -497,  -497,  -497,  -497,  -497,
    -122,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -120,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,    86,   205,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,  -497,
    -497,  -497,  -497,  -497,  -497,   -68,  -497,  -497,  -497,  -213,
    -497,  -497,  -227,  -497,  -497,  -497,  -497,  -497,  -497,  -238,
    -497,  -497,  -244,  -497
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,    77,    78,
      37,    60,    74,    75,   502,   639,   712,   713,   112,    39,
      62,    85,    86,    87,   286,    41,    63,   113,   114,   115,
     116,   117,   118,   119,   120,   293,    43,    64,   137,   316,
     121,   294,   122,   295,   562,   563,   564,   661,   778,   565,
     662,   566,   663,   567,   664,   214,   351,   569,   570,   571,
     572,   123,   304,   588,   589,   590,   591,   124,   306,   595,
     596,   597,   125,   305,   126,   308,   601,   602,   603,   688,
      57,    71,   244,   245,   246,   363,   247,   364,   127,   309,
     610,   611,   612,   613,   614,   615,   616,   617,   128,   301,
     575,   576,   577,   672,    45,    65,   155,   156,   157,   321,
     158,   322,   159,   323,   160,   327,   161,   326,   162,   163,
     129,   302,   579,   580,   581,   675,    53,    69,   215,   216,
     217,   218,   219,   220,   221,   350,   222,   354,   223,   353,
     224,   225,   355,   226,   130,   303,   583,   584,   585,   678,
      55,    70,   233,   234,   235,   236,   237,   359,   238,   239,
     240,   165,   319,   643,   644,   645,   715,    47,    66,   172,
     173,   174,   332,   166,   320,   647,   648,   649,   718,    49,
      67,   182,   183,   184,   335,   185,   186,   337,   187,   188,
     167,   328,   651,   652,   653,   721,    51,    68,   197,   198,
     199,   200,   343,   201,   344,   202,   345,   203,   346,   204,
     347,   205,   342,   168,   329,   655,   724,   131,   307,   599,
     318,   419,   420,   421,   422,   423,   503,   132,   310,   625,
     626,   627,   699,   789,   628,   629,   700,   630,   631,   133,
     134,   312,   634,   635,   636,   706,   637,   707,   135,   313,
      59,    72,   264,   265,   266,   267,   368,   268,   369,   269,
     270,   371,   271,   272,   273,   374,   537,   274,   375,   275,
     276,   277,   278,   279,   380,   544,   280,   381,    88,   288,
      89,   289,    90,   287,   549,   550,   551,   657,   799,   800,
     801,   809,   810,   811,   812,   817,   813,   815,   827,   828,
     829,   833,   834,   836
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   231,   624,   150,   170,   180,   195,   213,   229,   243,
     263,   232,   230,   598,   164,   171,   181,   196,   151,   594,
     152,   153,    34,   154,    27,   138,    28,    79,    29,   586,
      26,   681,    38,   101,   682,   101,   207,    91,    40,    92,
      93,   241,   242,   169,   291,    94,    95,    96,    97,   292,
      42,   138,   101,    94,    95,    96,    97,    98,    99,   100,
     101,   139,   415,   140,   774,   775,   776,   777,   206,   141,
     142,   143,   144,   145,   146,   207,   227,   208,   209,   228,
     147,   148,    44,   102,   103,   104,   105,   149,   207,   207,
     208,   209,    46,   210,   211,   212,   618,   106,   101,   587,
     107,   241,   242,   553,   557,    83,   147,   108,   554,   555,
     556,   557,   558,   559,   560,   109,   110,   314,    48,   111,
     330,   333,   315,   207,   189,   331,   334,    50,   190,   191,
     192,   193,   194,    80,   101,    83,   340,    83,   365,    81,
      82,   341,   684,   366,    52,   685,   175,   176,   177,   178,
     179,   535,   536,    83,    83,    30,    31,    32,    33,   382,
     314,    54,    83,    76,   383,   656,   619,   620,   621,   622,
     686,    56,   804,   687,   805,   806,    83,    58,   539,   540,
     541,   542,   604,   605,   606,   607,   608,   609,   658,    83,
      83,   669,   669,   659,   697,   136,   670,   671,   704,   698,
      83,   708,   382,   705,   745,   543,   709,   710,   624,   594,
     330,   365,   281,   333,   340,   782,   785,    83,   794,   795,
     818,   837,   632,   633,    83,   819,   838,   802,   830,    84,
     803,   831,   786,   787,   788,   282,    83,   283,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   518,   519,   520,   416,   284,   586,   593,
     417,   285,   317,   290,   296,   297,   298,   418,   150,   299,
     300,   170,   311,   324,   325,   336,   338,   339,   180,   164,
      83,   349,   171,   151,   348,   152,   153,   195,   154,   181,
     384,   385,   352,   231,   356,   357,   213,   358,   196,   360,
     229,   361,   362,   232,   230,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,   367,   370,   372,
     263,   373,   376,   377,   378,   379,   386,   387,   388,   389,
     390,   392,   393,   394,   395,   400,   401,   396,   397,   398,
     399,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   414,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   436,   438,   439,   440,   441,   444,
     445,   442,   446,   447,   448,   449,   451,   452,   453,   454,
     455,   456,   457,   459,   460,   462,   463,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   484,   485,   478,
     479,   481,   475,   476,   489,   482,   477,   483,   486,   487,
     488,   490,   491,   492,   493,   494,   495,   496,   508,   509,
     497,   498,   499,   500,   501,   561,   561,   505,   504,   568,
     568,   506,   507,   510,   511,   513,   623,   512,   263,   514,
     515,   516,   517,   416,   521,   522,   523,   417,   524,   574,
     578,   582,   525,   600,   418,   640,   642,   646,   526,   650,
     665,   660,   654,   666,   667,   668,   527,   674,   673,   528,
     529,   531,   530,   538,   676,   677,   679,   680,   690,   683,
     717,   532,   689,   691,   548,   692,   693,   694,   695,   546,
     533,   534,   696,   701,   702,   703,   592,   720,   716,   719,
     545,   722,   723,   764,   725,   726,   728,   729,   730,   731,
     711,   755,   756,   761,   714,   762,   765,   773,   772,   732,
     733,   816,   820,   783,   779,   734,   735,   784,   796,   798,
     748,   749,   822,   826,   824,   839,   413,   391,   547,   573,
     736,   750,   751,   552,   743,   744,   747,   746,   754,   464,
     738,   737,   740,   435,   752,   753,   832,   739,   757,   758,
     759,   780,   458,   742,   781,   790,   741,   791,   766,   792,
     793,   797,   767,   821,   825,   841,   461,   437,   769,   443,
     768,   641,   760,   771,   450,   770,   638,   480,   763,   814,
     727,   823,   835,   840,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   561,     0,   231,
     150,   568,     0,   213,     0,     0,   229,     0,     0,   232,
     230,   164,     0,     0,     0,   151,   243,   152,   153,     0,
     154,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   623,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   170,     0,     0,   180,     0,     0,   195,
       0,     0,     0,     0,   171,     0,     0,   181,     0,     0,
     196,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   807,
       0,     0,     0,   808,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   807,     0,     0,     0,
     808
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    70,   498,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,   495,    65,    66,    67,    68,    65,   494,
      65,    65,    14,    65,     5,     7,     7,    10,     9,    66,
       0,     3,     7,    34,     6,    34,    35,    11,     7,    13,
      14,    72,    73,    44,     3,    27,    28,    29,    30,     8,
       7,     7,    34,    27,    28,    29,    30,    31,    32,    33,
      34,    43,    61,    45,    16,    17,    18,    19,    15,    51,
      52,    53,    54,    55,    56,    35,    36,    37,    38,    39,
      62,    63,     7,    57,    58,    59,    60,    69,    35,    35,
      37,    38,     7,    40,    41,    42,    15,    71,    34,   136,
      74,    72,    73,    15,    23,   136,    62,    81,    20,    21,
      22,    23,    24,    25,    26,    89,    90,     3,     7,    93,
       3,     3,     8,    35,    60,     8,     8,     7,    64,    65,
      66,    67,    68,   116,    34,   136,     3,   136,     3,   122,
     123,     8,     3,     8,     7,     6,    46,    47,    48,    49,
      50,   109,   110,   136,   136,   136,   137,   138,   139,     3,
       3,     7,   136,   136,     8,     8,    85,    86,    87,    88,
       3,     7,   118,     6,   120,   121,   136,     7,   112,   113,
     114,   115,    75,    76,    77,    78,    79,    80,     3,   136,
     136,     3,     3,     8,     3,    12,     8,     8,     3,     8,
     136,     3,     3,     8,   686,   139,     8,     8,   704,   684,
       3,     3,     6,     3,     3,     8,     8,   136,     8,     8,
       3,     3,    91,    92,   136,     8,     8,     3,     3,   291,
       6,     6,    82,    83,    84,     3,   136,     4,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   444,   445,   446,   318,     8,    66,    67,
     318,     3,     8,     4,     4,     4,     4,   318,   330,     4,
       4,   333,     4,     4,     4,     4,     4,     4,   340,   330,
     136,     3,   333,   330,     8,   330,   330,   349,   330,   340,
     282,   283,     4,   362,     4,     8,   358,     3,   349,     4,
     362,     8,     3,   362,   362,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,     4,     4,     4,
     382,     4,     4,     4,     4,     4,   136,     4,     4,     4,
       4,     4,     4,     4,   137,     4,     4,   137,   137,   137,
     137,     4,     4,     4,     4,     4,     4,     4,     4,   137,
       4,     4,     4,     4,     4,     4,     4,     4,   137,   139,
       4,     4,     4,     4,     4,     4,   137,     4,   137,     4,
       4,   137,     4,     4,     4,     4,     4,     4,   137,     4,
       4,     4,   139,     4,   139,     4,     4,   139,     4,     4,
     137,     4,   137,   137,     4,     4,   139,   389,   390,     4,
       4,     4,   139,   139,     5,     7,   139,     7,     7,     7,
       7,     5,     5,     5,     5,     5,     5,     5,   136,   136,
       7,     7,     7,     7,     5,   487,   488,     3,     8,   487,
     488,     5,     5,   136,   136,     5,   498,   136,   500,     7,
     136,   136,   136,   505,   136,   136,   136,   505,   136,     7,
       7,     7,   136,     7,   505,     4,     7,     7,   136,     7,
       4,     8,    70,     4,     4,     4,   136,     3,     6,   136,
     136,   463,   136,   111,     6,     3,     6,     3,     3,     6,
       3,   136,     6,     4,   117,     4,     4,     4,     4,   481,
     136,   136,     4,     4,     4,     4,   493,     3,     6,     6,
     136,     6,     3,     6,     8,     4,     4,     4,     4,     4,
     136,     4,     4,     4,   136,     4,     3,     5,     4,   139,
     137,     4,     4,     8,   136,   139,   137,     8,     8,     7,
     137,   137,     4,     7,     5,     4,   314,   291,   482,   488,
     669,   137,   137,   486,   681,   684,   690,   688,   697,   365,
     674,   672,   677,   330,   137,   137,   119,   675,   137,   137,
     137,   136,   358,   680,   136,   136,   678,   136,   715,   136,
     136,   136,   717,   137,   136,   136,   362,   333,   720,   340,
     718,   505,   704,   723,   349,   721,   500,   382,   708,   802,
     658,   818,   830,   837,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   669,    -1,   678,
     672,   669,    -1,   675,    -1,    -1,   678,    -1,    -1,   678,
     678,   672,    -1,    -1,    -1,   672,   688,   672,   672,    -1,
     672,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   704,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   715,    -1,    -1,   718,    -1,    -1,   721,
      -1,    -1,    -1,    -1,   715,    -1,    -1,   718,    -1,    -1,
     721,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   801,
      -1,    -1,    -1,   801,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   818,    -1,    -1,    -1,
     818
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,     0,     5,     7,     9,
     136,   137,   138,   139,   154,   155,   156,   160,     7,   169,
       7,   175,     7,   186,     7,   254,     7,   317,     7,   329,
       7,   346,     7,   276,     7,   300,     7,   230,     7,   400,
     161,   157,   170,   176,   187,   255,   318,   330,   347,   277,
     301,   231,   401,   154,   162,   163,   136,   158,   159,    10,
     116,   122,   123,   136,   168,   171,   172,   173,   428,   430,
     432,    11,    13,    14,    27,    28,    29,    30,    31,    32,
      33,    34,    57,    58,    59,    60,    71,    74,    81,    89,
      90,    93,   168,   177,   178,   179,   180,   181,   182,   183,
     184,   190,   192,   211,   217,   222,   224,   238,   248,   270,
     294,   367,   377,   389,   390,   398,    12,   188,     7,    43,
      45,    51,    52,    53,    54,    55,    56,    62,    63,    69,
     168,   179,   180,   181,   182,   256,   257,   258,   260,   262,
     264,   266,   268,   269,   294,   311,   323,   340,   363,    44,
     168,   294,   319,   320,   321,    46,    47,    48,    49,    50,
     168,   294,   331,   332,   333,   335,   336,   338,   339,    60,
      64,    65,    66,    67,    68,   168,   294,   348,   349,   350,
     351,   353,   355,   357,   359,   361,    15,    35,    37,    38,
      40,    41,    42,   168,   205,   278,   279,   280,   281,   282,
     283,   284,   286,   288,   290,   291,   293,    36,    39,   168,
     205,   282,   288,   302,   303,   304,   305,   306,   308,   309,
     310,    72,    73,   168,   232,   233,   234,   236,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   168,   402,   403,   404,   405,   407,   409,
     410,   412,   413,   414,   417,   419,   420,   421,   422,   423,
     426,     6,     3,     4,     8,     3,   174,   433,   429,   431,
       4,     3,     8,   185,   191,   193,     4,     4,     4,     4,
       4,   249,   271,   295,   212,   223,   218,   368,   225,   239,
     378,     4,   391,   399,     3,     8,   189,     8,   370,   312,
     324,   259,   261,   263,     4,     4,   267,   265,   341,   364,
       3,     8,   322,     3,     8,   334,     4,   337,     4,     4,
       3,     8,   362,   352,   354,   356,   358,   360,     8,     3,
     285,   206,     4,   289,   287,   292,     4,     8,     3,   307,
       4,     8,     3,   235,   237,     3,     8,     4,   406,   408,
       4,   411,     4,     4,   415,   418,     4,     4,     4,     4,
     424,   427,     3,     8,   154,   154,   136,     4,     4,     4,
       4,   172,     4,     4,     4,   137,   137,   137,   137,   137,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     137,     4,     4,   178,     4,    61,   168,   205,   294,   371,
     372,   373,   374,   375,     4,     4,     4,     4,     4,   137,
     139,     4,     4,     4,     4,   257,     4,   320,     4,   137,
       4,   137,   137,   332,     4,     4,     4,     4,     4,     4,
     350,     4,     4,   137,     4,     4,     4,   139,   280,     4,
     139,   304,     4,     4,   233,   139,     4,     4,   137,     4,
     137,   137,     4,     4,   139,   139,   139,   139,     4,     4,
     403,     4,     7,     7,   154,   154,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,     7,     7,     7,
       7,     5,   164,   376,     8,     3,     5,     5,   136,   136,
     136,   136,   136,     5,     7,   136,   136,   136,   164,   164,
     164,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   154,   136,   136,   136,   109,   110,   416,   111,   112,
     113,   114,   115,   139,   425,   136,   154,   177,   117,   434,
     435,   436,   188,    15,    20,    21,    22,    23,    24,    25,
      26,   168,   194,   195,   196,   199,   201,   203,   205,   207,
     208,   209,   210,   194,     7,   250,   251,   252,     7,   272,
     273,   274,     7,   296,   297,   298,    66,   136,   213,   214,
     215,   216,   162,    67,   215,   219,   220,   221,   264,   369,
       7,   226,   227,   228,    75,    76,    77,    78,    79,    80,
     240,   241,   242,   243,   244,   245,   246,   247,    15,    85,
      86,    87,    88,   168,   207,   379,   380,   381,   384,   385,
     387,   388,    91,    92,   392,   393,   394,   396,   402,   165,
       4,   373,     7,   313,   314,   315,     7,   325,   326,   327,
       7,   342,   343,   344,    70,   365,     8,   437,     3,     8,
       8,   197,   200,   202,   204,     4,     4,     4,     4,     3,
       8,     8,   253,     6,     3,   275,     6,     3,   299,     6,
       3,     3,     6,     6,     3,     6,     3,     6,   229,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   382,
     386,     4,     4,     4,     3,     8,   395,   397,     3,     8,
       8,   136,   166,   167,   136,   316,     6,     3,   328,     6,
       3,   345,     6,     3,   366,     8,     4,   435,     4,     4,
       4,     4,   139,   137,   139,   137,   195,   256,   252,   278,
     274,   302,   298,   214,   220,   264,   232,   228,   137,   137,
     137,   137,   137,   137,   241,     4,     4,   137,   137,   137,
     380,     4,     4,   393,     6,     3,   319,   315,   331,   327,
     348,   344,     4,     5,    16,    17,    18,    19,   198,   136,
     136,   136,     8,     8,     8,     8,    82,    83,    84,   383,
     136,   136,   136,   136,     8,     8,     8,   136,     7,   438,
     439,   440,     3,     6,   118,   120,   121,   168,   205,   441,
     442,   443,   444,   446,   439,   447,     4,   445,     3,     8,
       4,   137,     4,   442,     5,   136,     7,   448,   449,   450,
       3,     6,   119,   451,   452,   449,   453,     3,     8,     4,
     452,   136
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   140,   142,   141,   143,   141,   144,   141,   145,   141,
     146,   141,   147,   141,   148,   141,   149,   141,   150,   141,
     151,   141,   152,   141,   153,   141,   154,   154,   154,   154,
     154,   154,   154,   155,   157,   156,   158,   158,   159,   159,
     161,   160,   162,   162,   163,   163,   165,   164,   166,   166,
     167,   167,   168,   170,   169,   171,   171,   172,   172,   172,
     172,   172,   174,   173,   176,   175,   177,   177,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     179,   180,   181,   182,   183,   185,   184,   187,   186,   189,
     188,   191,   190,   193,   192,   194,   194,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   197,   196,   198,
     198,   198,   198,   200,   199,   202,   201,   204,   203,   206,
     205,   207,   208,   209,   210,   212,   211,   213,   213,   214,
     214,   215,   216,   218,   217,   219,   219,   220,   220,   221,
     223,   222,   225,   224,   226,   226,   227,   227,   229,   228,
     231,   230,   232,   232,   232,   233,   233,   235,   234,   237,
     236,   239,   238,   240,   240,   241,   241,   241,   241,   241,
     241,   242,   243,   244,   245,   246,   247,   249,   248,   250,
     250,   251,   251,   253,   252,   255,   254,   256,   256,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   259,   258,   261,   260,
     263,   262,   265,   264,   267,   266,   268,   269,   271,   270,
     272,   272,   273,   273,   275,   274,   277,   276,   278,   278,
     279,   279,   280,   280,   280,   280,   280,   280,   280,   280,
     281,   282,   283,   285,   284,   287,   286,   289,   288,   290,
     292,   291,   293,   295,   294,   296,   296,   297,   297,   299,
     298,   301,   300,   302,   302,   303,   303,   304,   304,   304,
     304,   304,   304,   305,   307,   306,   308,   309,   310,   312,
     311,   313,   313,   314,   314,   316,   315,   318,   317,   319,
     319,   320,   320,   320,   322,   321,   324,   323,   325,   325,
     326,   326,   328,   327,   330,   329,   331,   331,   332,   332,
     332,   332,   332,   332,   332,   334,   333,   335,   337,   336,
     338,   339,   341,   340,   342,   342,   343,   343,   345,   344,
     347,   346,   348,   348,   349,   349,   350,   350,   350,   350,
     350,   350,   350,   350,   352,   351,   354,   353,   356,   355,
     358,   357,   360,   359,   362,   361,   364,   363,   366,   365,
     368,   367,   369,   369,   370,   264,   371,   371,   372,   372,
     373,   373,   373,   373,   374,   376,   375,   378,   377,   379,
     379,   380,   380,   380,   380,   380,   380,   380,   382,   381,
     383,   383,   383,   384,   386,   385,   387,   388,   389,   391,
     390,   392,   392,   393,   393,   395,   394,   397,   396,   399,
     398,   401,   400,   402,   402,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   404,   406,   405,   408,   407,   409,   411,   410,   412,
     413,   415,   414,   416,   416,   418,   417,   419,   420,   421,
     422,   424,   423,   425,   425,   425,   425,   425,   427,   426,
     429,   428,   431,   430,   433,   432,   434,   434,   435,   437,
     436,   438,   438,   440,   439,   441,   441,   442,   442,   442,
     442,   442,   443,   445,   444,   447,   446,   448,   448,   450,
     449,   451,   451,   453,   452
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     1,     3,     5,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     0,     6,     0,     4,     0,
       4,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     0,     4
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
  "\"delegated-len\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
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
  "$@11", "$@12", "value", "sub_json", "map2", "$@13", "map_content",
  "not_empty_map", "list_generic", "$@14", "list_content",
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
  "pool_param", "pool_entry", "$@60", "pd_pools_list", "$@61",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@62", "sub_pd_pool", "$@63", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@64", "pd_prefix_len", "excluded_prefix", "$@65",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@66",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@67", "sub_reservation", "$@68", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@69", "prefixes", "$@70", "duid", "$@71", "hw_address", "$@72",
  "hostname", "$@73", "reservation_client_classes", "$@74", "relay",
  "$@75", "relay_map", "$@76", "client_classes", "$@77",
  "client_classes_list", "$@78", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@79", "server_id", "$@80",
  "server_id_params", "server_id_param", "server_id_type", "$@81",
  "duid_type", "htype", "identifier", "$@82", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@83", "control_socket_params",
  "control_socket_param", "socket_type", "$@84", "socket_name", "$@85",
  "dhcp_ddns", "$@86", "sub_dhcp_ddns", "$@87", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@88",
  "server_ip", "$@89", "server_port", "sender_ip", "$@90", "sender_port",
  "max_queue_size", "ncr_protocol", "$@91", "ncr_protocol_value",
  "ncr_format", "$@92", "always_include_fqdn", "allow_client_update",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@93", "replace_client_name_value", "generated_prefix", "$@94",
  "dhcp4_json_object", "$@95", "dhcpddns_json_object", "$@96",
  "logging_object", "$@97", "logging_params", "logging_param", "loggers",
  "$@98", "loggers_entries", "logger_entry", "$@99", "logger_params",
  "logger_param", "debuglevel", "severity", "$@100", "output_options_list",
  "$@101", "output_options_list_content", "output_entry", "$@102",
  "output_params", "output_param", "$@103", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   219,   219,   219,   220,   220,   221,   221,   222,   222,
     223,   223,   224,   224,   225,   225,   226,   226,   227,   227,
     228,   228,   229,   229,   230,   230,   238,   239,   240,   241,
     242,   243,   244,   247,   252,   252,   264,   265,   268,   272,
     279,   279,   286,   287,   290,   294,   301,   301,   308,   309,
     312,   316,   327,   337,   337,   349,   350,   354,   355,   356,
     357,   358,   361,   361,   378,   378,   386,   387,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     416,   421,   426,   431,   436,   441,   441,   451,   451,   459,
     459,   469,   469,   479,   479,   489,   490,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   505,   505,   512,
     513,   514,   515,   518,   518,   526,   526,   534,   534,   542,
     542,   550,   555,   560,   565,   570,   570,   580,   581,   584,
     585,   588,   593,   598,   598,   608,   609,   612,   613,   616,
     623,   623,   633,   633,   643,   644,   647,   648,   651,   651,
     659,   659,   667,   668,   669,   672,   673,   676,   676,   684,
     684,   692,   692,   702,   703,   706,   707,   708,   709,   710,
     711,   714,   719,   724,   729,   734,   739,   747,   747,   760,
     761,   764,   765,   772,   772,   795,   795,   804,   805,   809,
     810,   811,   812,   813,   814,   815,   816,   817,   818,   819,
     820,   821,   822,   823,   824,   825,   828,   828,   836,   836,
     844,   844,   852,   852,   860,   860,   868,   873,   882,   882,
     894,   895,   898,   899,   904,   904,   915,   915,   925,   926,
     929,   930,   933,   934,   935,   936,   937,   938,   939,   940,
     943,   945,   950,   952,   952,   960,   960,   968,   968,   976,
     978,   978,   986,   995,   995,  1007,  1008,  1013,  1014,  1019,
    1019,  1030,  1030,  1041,  1042,  1047,  1048,  1053,  1054,  1055,
    1056,  1057,  1058,  1061,  1063,  1063,  1071,  1073,  1075,  1083,
    1083,  1095,  1096,  1099,  1100,  1103,  1103,  1111,  1111,  1119,
    1120,  1123,  1124,  1125,  1128,  1128,  1139,  1139,  1151,  1152,
    1155,  1156,  1159,  1159,  1167,  1167,  1175,  1176,  1179,  1180,
    1181,  1182,  1183,  1184,  1185,  1188,  1188,  1196,  1201,  1201,
    1209,  1214,  1222,  1222,  1232,  1233,  1236,  1237,  1240,  1240,
    1248,  1248,  1256,  1257,  1260,  1261,  1265,  1266,  1267,  1268,
    1269,  1270,  1271,  1272,  1275,  1275,  1285,  1285,  1295,  1295,
    1303,  1303,  1311,  1311,  1319,  1319,  1332,  1332,  1342,  1342,
    1353,  1353,  1363,  1364,  1367,  1367,  1375,  1376,  1379,  1380,
    1383,  1384,  1385,  1386,  1389,  1391,  1391,  1402,  1402,  1412,
    1413,  1416,  1417,  1418,  1419,  1420,  1421,  1422,  1425,  1425,
    1432,  1433,  1434,  1437,  1442,  1442,  1450,  1455,  1462,  1469,
    1469,  1479,  1480,  1483,  1484,  1487,  1487,  1495,  1495,  1505,
    1505,  1515,  1515,  1523,  1524,  1527,  1528,  1529,  1530,  1531,
    1532,  1533,  1534,  1535,  1536,  1537,  1538,  1539,  1540,  1541,
    1542,  1545,  1550,  1550,  1558,  1558,  1566,  1571,  1571,  1579,
    1584,  1589,  1589,  1597,  1598,  1601,  1601,  1609,  1614,  1619,
    1624,  1629,  1629,  1637,  1640,  1643,  1646,  1649,  1655,  1655,
    1665,  1665,  1672,  1672,  1684,  1684,  1697,  1698,  1702,  1706,
    1706,  1718,  1719,  1723,  1723,  1731,  1732,  1735,  1736,  1737,
    1738,  1739,  1742,  1746,  1746,  1754,  1754,  1764,  1765,  1768,
    1768,  1776,  1777,  1780,  1780
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
#line 4092 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1788 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
