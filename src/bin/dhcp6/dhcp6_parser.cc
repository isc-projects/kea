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
      case 167: // value
      case 171: // map_value
      case 215: // db_type
      case 291: // hr_mode
      case 412: // duid_type
      case 445: // ncr_protocol_value
      case 453: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 152: // "boolean"
        value.move< bool > (that.value);
        break;

      case 151: // "floating point"
        value.move< double > (that.value);
        break;

      case 150: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 149: // "constant string"
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
      case 167: // value
      case 171: // map_value
      case 215: // db_type
      case 291: // hr_mode
      case 412: // duid_type
      case 445: // ncr_protocol_value
      case 453: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 152: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 151: // "floating point"
        value.copy< double > (that.value);
        break;

      case 150: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 149: // "constant string"
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
            case 149: // "constant string"

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 150: // "integer"

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 151: // "floating point"

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 152: // "boolean"

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 167: // value

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 171: // map_value

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 215: // db_type

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 291: // hr_mode

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 412: // duid_type

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 445: // ncr_protocol_value

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 453: // replace_client_name_value

#line 225 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 167: // value
      case 171: // map_value
      case 215: // db_type
      case 291: // hr_mode
      case 412: // duid_type
      case 445: // ncr_protocol_value
      case 453: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 152: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 151: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 150: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 149: // "constant string"
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
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 818 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 285 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 289 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 329 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 333 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 379 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 386 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 464 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 582 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 718 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 839 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 858 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 907 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 930 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 940 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1029 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1133 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1176 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1210 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1212 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1225 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1244 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1291 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2287 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1368 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2361 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2371 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2447 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2593 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2751 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2778 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1687 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2905 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1728 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2929 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2998 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1777 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3026 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3046 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3055 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1816 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1882 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3156 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3183 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3187 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -507;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     118,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,    33,    19,    24,    34,    63,   106,   113,
     122,   128,   168,   191,   199,   203,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
      19,   -97,    17,    31,    76,    23,    -9,   105,    72,    62,
      -5,   -33,   233,  -507,   210,   242,   263,   228,   270,  -507,
    -507,  -507,  -507,  -507,   276,  -507,    71,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,   280,   281,   283,   284,
     286,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,   287,  -507,  -507,  -507,   103,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,   288,
     111,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
     292,   293,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,   124,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,   125,
    -507,  -507,  -507,  -507,   294,  -507,   298,   303,  -507,  -507,
    -507,   159,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,   300,   307,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,   309,
    -507,  -507,  -507,   310,  -507,  -507,   311,   308,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,   314,
     319,  -507,  -507,  -507,  -507,   316,   312,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,   170,  -507,  -507,
    -507,   321,  -507,  -507,   322,  -507,   323,   324,  -507,  -507,
     325,   326,   327,  -507,  -507,  -507,   171,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,    19,    19,  -507,   183,   329,   330,   331,
     347,   348,  -507,    17,  -507,   349,   350,   351,   207,   208,
     209,   211,   212,   352,   356,   359,   360,   361,   362,   363,
     364,   365,   366,   221,   368,   369,    31,  -507,   370,   225,
      76,  -507,    48,   371,   372,   374,   375,   376,   231,   234,
     379,   380,   381,   383,    23,  -507,   384,   385,    -9,  -507,
     386,   241,   388,   244,   245,   105,  -507,   389,   392,   393,
     394,   395,   396,   397,  -507,    72,   398,   399,   254,   401,
     402,   403,   256,  -507,    62,   405,   258,   259,  -507,    -5,
     408,   409,   169,  -507,   262,   411,   415,   271,   416,   272,
     273,   420,   421,   274,   275,   277,   424,   426,   233,  -507,
    -507,  -507,   427,   425,   428,    19,    19,    19,  -507,   429,
     430,   431,  -507,  -507,  -507,  -507,  -507,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,  -507,   446,   447,
    -507,   450,  -507,  -507,  -507,  -507,  -507,  -507,   448,   454,
    -507,  -507,  -507,   456,   457,   285,   315,   317,  -507,  -507,
     100,   318,   458,   452,  -507,   328,   461,  -507,   332,  -507,
     333,  -507,  -507,  -507,   450,   450,   450,   334,   335,   336,
     337,  -507,   338,   339,  -507,   340,   341,   342,  -507,  -507,
     343,  -507,  -507,  -507,   344,    19,  -507,  -507,   345,   346,
    -507,   353,  -507,  -507,    36,   313,  -507,  -507,  -507,   -31,
     354,  -507,    19,    31,   373,  -507,  -507,  -507,    76,   160,
     160,   463,   464,   465,   -32,    19,   116,    25,   466,   115,
      28,   177,   233,  -507,  -507,   470,  -507,    48,   468,   469,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,   472,   400,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,   204,  -507,   205,  -507,  -507,
     206,  -507,  -507,  -507,  -507,   493,   494,   496,   497,   500,
    -507,  -507,  -507,   214,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,   215,  -507,   499,
     503,  -507,  -507,   501,   505,  -507,  -507,   504,   506,  -507,
    -507,  -507,    45,  -507,  -507,  -507,   508,  -507,  -507,  -507,
     243,  -507,  -507,  -507,  -507,   247,  -507,   509,   513,  -507,
     507,   514,   515,   516,   517,   518,   216,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,   519,   520,   521,  -507,
    -507,   217,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
     223,  -507,  -507,  -507,   224,   377,   378,  -507,  -507,   511,
     525,  -507,  -507,   523,   527,  -507,  -507,   526,   528,  -507,
    -507,   529,  -507,   530,   373,  -507,  -507,   531,   532,   534,
     535,   390,   391,   404,   406,   407,   537,   538,   160,  -507,
    -507,    23,  -507,   463,    62,  -507,   464,    -5,  -507,   465,
     -32,  -507,  -507,   116,  -507,    25,  -507,   -33,  -507,   466,
     410,   412,   413,   414,   417,   418,   115,  -507,   540,   541,
     419,   422,   423,    28,  -507,   542,   543,   177,  -507,  -507,
    -507,   544,   545,  -507,    -9,  -507,   468,   105,  -507,   469,
      72,  -507,   472,   547,  -507,   548,  -507,   119,   432,   433,
     444,  -507,  -507,  -507,  -507,  -507,   445,   449,  -507,   226,
    -507,   551,  -507,   553,  -507,  -507,  -507,  -507,   230,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,   -34,   451,  -507,
    -507,  -507,  -507,   453,   455,  -507,  -507,   459,   232,  -507,
     236,  -507,   557,  -507,   460,   549,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,   265,  -507,    66,   549,  -507,  -507,   562,
    -507,  -507,  -507,   239,  -507,  -507,  -507,  -507,  -507,   566,
     462,   567,    66,  -507,   550,  -507,   467,  -507,   568,  -507,
    -507,   266,  -507,   -56,   568,  -507,  -507,   570,   572,   573,
     240,  -507,  -507,  -507,  -507,  -507,  -507,   574,   471,   474,
     475,   -56,  -507,   473,  -507,  -507,  -507,  -507,  -507
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,    99,     9,   212,    11,   319,    13,   339,    15,
     366,    17,   256,    19,   291,    21,   177,    23,   450,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   368,   258,
     293,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     503,   497,   499,   501,     0,    63,     0,    56,    58,    60,
      61,    62,    59,    97,   108,   110,     0,     0,     0,     0,
       0,   204,   248,   283,   150,   167,   158,   399,   169,   188,
     416,     0,   438,   448,    91,     0,    68,    70,    71,    72,
      73,    74,    76,    77,    78,    79,    81,    80,    85,    86,
      75,    83,    84,    82,    87,    88,    89,    90,   105,     0,
       0,   101,   103,   104,   403,   311,   331,   233,   235,   237,
       0,     0,   241,   239,   358,   395,   232,   216,   217,   218,
     219,     0,   214,   223,   224,   225,   228,   230,   226,   227,
     220,   221,   222,   229,   231,   327,   329,   326,   324,     0,
     321,   323,   325,   351,     0,   354,     0,     0,   350,   346,
     349,     0,   341,   343,   344,   347,   348,   345,   393,   381,
     383,   385,   387,   389,   391,   380,   379,     0,   369,   370,
     374,   375,   372,   376,   377,   378,   373,   273,   140,     0,
     277,   275,   280,     0,   269,   270,     0,   259,   260,   262,
     272,   263,   264,   265,   279,   266,   267,   268,   305,     0,
       0,   303,   304,   307,   308,     0,   294,   295,   297,   298,
     299,   300,   301,   302,   184,   186,   181,     0,   179,   182,
     183,     0,   470,   472,     0,   475,     0,     0,   479,   483,
       0,     0,     0,   488,   495,   468,     0,   452,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,    42,     0,     0,    35,     0,     0,     0,     0,
       0,     0,    53,     0,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    67,     0,     0,
       0,   100,   405,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   213,     0,     0,     0,   320,
       0,     0,     0,     0,     0,     0,   340,     0,     0,     0,
       0,     0,     0,     0,   367,     0,     0,     0,     0,     0,
       0,     0,     0,   257,     0,     0,     0,     0,   292,     0,
       0,     0,     0,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   451,
      46,    39,     0,     0,     0,     0,     0,     0,    57,     0,
       0,     0,    92,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   437,     0,     0,
      69,     0,   107,   102,   414,   412,   413,   411,     0,   406,
     407,   409,   410,     0,     0,     0,     0,     0,   246,   247,
       0,     0,     0,     0,   215,     0,     0,   322,     0,   353,
       0,   356,   357,   342,     0,     0,     0,     0,     0,     0,
       0,   371,     0,     0,   271,     0,     0,     0,   282,   261,
       0,   309,   310,   296,     0,     0,   180,   469,     0,     0,
     474,     0,   477,   478,     0,     0,   485,   486,   487,     0,
       0,   453,     0,     0,     0,   498,   500,   502,     0,     0,
       0,   206,   250,   285,     0,    43,     0,     0,   171,     0,
       0,     0,     0,    47,   106,     0,   404,     0,   313,   333,
     234,   236,   238,   243,   244,   245,   242,   240,   360,     0,
     328,    36,   330,   352,   355,   394,   382,   384,   386,   388,
     390,   392,   274,   141,   278,   276,   281,   306,   185,   187,
     471,   473,   476,   481,   482,   480,   484,   490,   491,   492,
     493,   494,   489,   496,    40,     0,   508,     0,   505,   507,
       0,   127,   133,   135,   137,     0,     0,     0,     0,     0,
     146,   148,   126,     0,   112,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,   210,     0,
     207,   208,   254,     0,   251,   252,   289,     0,   286,   287,
     156,   157,     0,   152,   154,   155,     0,   165,   166,   162,
       0,   160,   163,   164,   401,     0,   175,     0,   172,   173,
       0,     0,     0,     0,     0,     0,     0,   190,   192,   193,
     194,   195,   196,   197,   427,   433,     0,     0,     0,   426,
     425,     0,   418,   420,   423,   421,   422,   424,   444,   446,
       0,   440,   442,   443,     0,    49,     0,   408,   317,     0,
     314,   315,   337,     0,   334,   335,   364,     0,   361,   362,
     397,     0,    65,     0,     0,   504,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   109,
     111,     0,   205,     0,   258,   249,     0,   293,   284,     0,
       0,   151,   168,     0,   159,     0,   400,     0,   170,     0,
       0,     0,     0,     0,     0,     0,     0,   189,     0,     0,
       0,     0,     0,     0,   417,     0,     0,     0,   439,   449,
      51,     0,    50,   415,     0,   312,     0,     0,   332,     0,
     368,   359,     0,     0,   396,     0,   506,     0,     0,     0,
       0,   139,   142,   143,   144,   145,     0,     0,   113,     0,
     209,     0,   253,     0,   288,   153,   161,   402,     0,   174,
     198,   199,   200,   201,   202,   203,   191,     0,     0,   432,
     435,   436,   419,     0,     0,   441,    48,     0,     0,   316,
       0,   336,     0,   363,     0,     0,   129,   130,   131,   132,
     128,   134,   136,   138,   147,   149,   211,   255,   290,   176,
     429,   430,   431,   428,   434,   445,   447,    52,   318,   338,
     365,   398,   512,     0,   510,     0,     0,   509,   524,     0,
     522,   520,   516,     0,   514,   518,   519,   517,   511,     0,
       0,     0,     0,   513,     0,   521,     0,   515,     0,   523,
     528,     0,   526,     0,     0,   525,   536,     0,     0,     0,
       0,   530,   532,   533,   534,   535,   527,     0,     0,     0,
       0,     0,   529,     0,   538,   539,   540,   531,   537
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,    11,  -507,    56,  -507,  -507,  -507,
    -507,  -507,  -507,    18,  -507,  -189,  -507,  -507,  -507,   -62,
    -507,  -507,  -507,   246,  -507,  -507,  -507,  -507,    49,   253,
     -63,   -50,   -44,   -43,  -507,  -507,  -507,  -507,  -507,    75,
     250,  -507,  -507,  -507,  -507,  -507,  -507,  -507,    74,  -123,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
     -58,  -507,  -506,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -134,  -493,  -507,  -507,  -507,  -507,  -136,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -141,  -507,
    -507,  -507,  -138,   213,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -146,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -122,  -507,  -507,  -507,  -119,   252,  -507,  -507,
    -507,  -507,  -507,  -507,  -497,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -117,  -507,  -507,  -507,  -113,
    -507,   229,  -507,   -59,  -507,  -507,  -507,  -507,  -507,   -57,
    -507,  -507,  -507,  -507,  -507,   -49,  -507,  -507,  -507,  -114,
    -507,  -507,  -507,  -120,  -507,   227,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -149,  -507,  -507,
    -507,  -144,   267,  -507,  -507,   -66,  -507,  -507,  -507,  -507,
    -507,  -148,  -507,  -507,  -507,  -143,   264,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -145,  -507,
    -507,  -507,  -147,  -507,   255,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,    91,
    -507,  -507,  -507,  -507,  -507,  -507,  -116,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -126,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,   104,   235,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,   -65,  -507,  -507,  -507,  -218,  -507,  -507,  -232,
    -507,  -507,  -507,  -507,  -507,  -507,  -243,  -507,  -507,  -259,
    -507,  -507,  -507,  -507,  -507
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   542,    77,
      78,    37,    60,    74,    75,   524,   675,   751,   752,   114,
      39,    62,    86,    87,    88,   297,    41,    63,   115,   116,
     117,   118,   119,   120,   121,   122,   305,    43,    64,   140,
     141,   142,   328,   143,   123,   306,   124,   307,   593,   594,
     595,   697,   820,   596,   698,   597,   699,   598,   700,   599,
     225,   367,   601,   602,   603,   604,   605,   706,   606,   707,
     125,   316,   622,   623,   624,   625,   126,   318,   630,   631,
     632,   633,   127,   317,   128,   320,   637,   638,   639,   727,
      57,    71,   257,   258,   259,   380,   260,   381,   129,   321,
     646,   647,   648,   649,   650,   651,   652,   653,   130,   313,
     609,   610,   611,   711,    45,    65,   161,   162,   163,   335,
     164,   336,   165,   337,   166,   341,   167,   340,   536,   168,
     169,   131,   314,   613,   614,   615,   714,    53,    69,   226,
     227,   228,   229,   230,   231,   232,   366,   233,   370,   234,
     369,   235,   236,   371,   237,   132,   315,   617,   618,   619,
     717,    55,    70,   245,   246,   247,   248,   249,   375,   250,
     251,   252,   253,   171,   333,   679,   680,   681,   754,    47,
      66,   179,   180,   181,   346,   182,   347,   172,   334,   683,
     684,   685,   757,    49,    67,   191,   192,   193,   350,   194,
     195,   352,   196,   197,   173,   342,   687,   688,   689,   760,
      51,    68,   207,   208,   209,   210,   358,   211,   359,   212,
     360,   213,   361,   214,   362,   215,   363,   216,   357,   174,
     343,   691,   763,   133,   319,   635,   332,   438,   439,   440,
     441,   442,   525,   134,   322,   661,   662,   663,   738,   833,
     664,   665,   739,   666,   667,   135,   136,   324,   670,   671,
     672,   745,   673,   746,   137,   325,    59,    72,   276,   277,
     278,   279,   385,   280,   386,   281,   282,   388,   283,   284,
     285,   391,   565,   286,   392,   287,   288,   289,   290,   396,
     572,   291,   397,    89,   299,    90,   300,    91,   301,    92,
     298,   577,   578,   579,   693,   843,   844,   845,   853,   854,
     855,   856,   861,   857,   859,   871,   872,   873,   880,   881,
     882,   887,   883,   884,   885
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      85,   190,   157,   156,   177,   188,   205,   224,   241,   256,
     275,   243,   242,   244,   660,   158,   170,   178,   189,   206,
     634,   159,   160,   629,    27,    34,    28,    79,    29,   103,
     144,    38,   144,    26,   218,   238,   219,   220,   239,   240,
     175,    40,    93,   620,   654,    94,    95,   176,   720,   254,
     255,   721,    76,   586,    96,    97,    98,    99,   830,   831,
     832,   103,    96,    97,    98,    99,   100,   101,   102,   103,
      42,   145,   876,   146,   303,   877,   878,   879,   217,   304,
     147,   148,   149,   150,   151,   152,   103,   218,   138,   139,
     567,   568,   569,   570,   153,   154,   153,   104,   105,   106,
     107,   218,   155,   219,   220,   218,   326,   221,   222,   223,
     103,   327,   108,    44,   330,   109,    84,   621,   434,   331,
      46,   571,   110,   655,   656,   657,   658,   344,   348,    48,
     111,   112,   345,   349,   113,    50,   816,   817,   818,   819,
      84,   198,    80,   103,    84,   199,   200,   201,   202,   203,
     204,    81,    82,    83,   563,   564,   183,   184,   185,   186,
     187,   176,   355,   533,   534,   535,    84,   356,    30,    31,
      32,    33,    84,   382,   398,    52,   581,    84,   383,   399,
      84,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   620,   627,   848,   628,   849,   850,    84,    54,   218,
     640,   641,   642,   643,   644,   645,    56,   326,   694,   330,
      58,    84,   692,   695,   696,    84,   292,   708,   708,   736,
     743,    84,   709,   710,   737,   744,   747,   398,   787,   344,
     629,   748,   749,   382,   826,   348,   295,   660,   829,   355,
     838,    85,   862,   891,   839,   293,   723,   863,   892,   724,
     725,   254,   255,   726,    84,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,   294,   846,   874,
     435,   847,   875,   296,   436,   545,   546,   547,   668,   669,
     302,   157,   156,   437,   308,   309,   177,   310,   311,   190,
     312,   323,   329,   188,   158,   170,   338,   339,   351,   178,
     159,   160,   353,   205,   400,   401,   189,   354,   364,    84,
     365,   374,   224,   368,   372,   379,   206,   241,   376,   373,
     243,   242,   244,   377,   378,   384,   387,   389,   390,   393,
     394,   395,   402,   403,   404,   405,   275,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   406,   407,   409,   410,   411,   417,   412,   413,   414,
     418,   415,   416,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   431,   443,   444,   432,   445,   446,
     447,   448,    84,   450,   451,   452,   449,   453,   455,   456,
     458,   459,   460,   464,   461,   462,   465,   466,   467,   468,
     469,   470,   472,   473,   474,   475,   476,   477,   478,   480,
     481,   482,   484,   485,   487,   488,   505,   506,   507,   489,
     491,   490,   492,   493,   494,   495,   496,   497,   499,   498,
     500,   502,   503,   566,   530,   504,   508,   509,   510,   511,
     512,   513,   514,   515,   516,   517,   518,   592,   592,   519,
     520,   600,   600,   521,   522,   523,   526,   527,   659,   539,
     275,   528,   529,   538,   531,   435,   532,   537,    28,   436,
     608,   612,   616,   636,   676,   678,   682,   540,   437,   686,
     690,   543,   544,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   560,   561,   559,   701,   702,   576,
     703,   704,   562,   573,   705,   712,   713,   715,   716,   719,
     718,   730,   541,   574,   722,   728,   729,   755,   731,   732,
     733,   734,   735,   740,   741,   742,   750,   753,   756,   758,
     759,   762,   761,   626,   765,   767,   768,   764,   769,   770,
     771,   776,   777,   772,   797,   798,   803,   804,   807,   408,
     806,   814,   575,   815,   773,   868,   842,   775,   774,   827,
     790,   828,   791,   792,   793,   840,   860,   794,   795,   799,
     864,   866,   800,   801,   888,   870,   889,   890,   893,   430,
     433,   821,   822,   580,   607,   778,   785,   786,   789,   788,
     796,   780,   779,   823,   824,   486,   454,   783,   825,   782,
     834,   781,   835,   479,   836,   784,   483,   809,   837,   841,
     808,   811,   865,   812,   810,   457,   869,   813,   677,   463,
     471,   805,   898,   894,   895,   896,   674,   802,   858,   766,
     867,   886,   897,   501,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   592,     0,   157,   156,
     600,     0,   224,     0,     0,   241,     0,     0,   243,   242,
     244,   158,   170,     0,     0,   256,     0,   159,   160,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   659,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   190,   177,     0,     0,   188,     0,     0,   205,     0,
       0,     0,     0,     0,     0,   178,     0,     0,   189,     0,
       0,   206,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   851,     0,     0,     0,   852,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     851,     0,     0,     0,   852
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   520,    65,    65,    66,    67,    68,
     517,    65,    65,   516,     5,    14,     7,    10,     9,    38,
       7,     7,     7,     0,    39,    40,    41,    42,    43,    44,
      49,     7,    11,    75,    16,    14,    15,    56,     3,    82,
      83,     6,   149,    25,    31,    32,    33,    34,    92,    93,
      94,    38,    31,    32,    33,    34,    35,    36,    37,    38,
       7,    48,   128,    50,     3,   131,   132,   133,    16,     8,
      57,    58,    59,    60,    61,    62,    38,    39,    12,    13,
     121,   122,   123,   124,    71,    72,    71,    66,    67,    68,
      69,    39,    79,    41,    42,    39,     3,    45,    46,    47,
      38,     8,    81,     7,     3,    84,   149,   149,    70,     8,
       7,   152,    91,    95,    96,    97,    98,     3,     3,     7,
      99,   100,     8,     8,   103,     7,    17,    18,    19,    20,
     149,    69,   125,    38,   149,    73,    74,    75,    76,    77,
      78,   134,   135,   136,   118,   119,    51,    52,    53,    54,
      55,    56,     3,    63,    64,    65,   149,     8,   149,   150,
     151,   152,   149,     3,     3,     7,    16,   149,     8,     8,
     149,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    75,    76,   127,    78,   129,   130,   149,     7,    39,
      85,    86,    87,    88,    89,    90,     7,     3,     3,     3,
       7,   149,     8,     8,     8,   149,     6,     3,     3,     3,
       3,   149,     8,     8,     8,     8,     3,     3,   725,     3,
     723,     8,     8,     3,     8,     3,     8,   743,     8,     3,
       8,   303,     3,     3,     8,     3,     3,     8,     8,     6,
       3,    82,    83,     6,   149,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     4,     3,     3,
     332,     6,     6,     3,   332,   464,   465,   466,   101,   102,
       4,   344,   344,   332,     4,     4,   348,     4,     4,   355,
       4,     4,     4,   355,   344,   344,     4,     4,     4,   348,
     344,   344,     4,   365,   293,   294,   355,     4,     8,   149,
       3,     3,   374,     4,     4,     3,   365,   379,     4,     8,
     379,   379,   379,     4,     8,     4,     4,     4,     4,     4,
       4,     4,   149,     4,     4,     4,   398,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,     4,     4,     4,     4,     4,     4,   150,   150,   150,
       4,   150,   150,     4,     4,     4,     4,     4,     4,     4,
       4,   150,     4,     4,     4,     4,     4,   152,     4,     4,
       4,   150,   149,     4,     4,     4,   152,     4,     4,     4,
       4,   150,     4,     4,   150,   150,     4,     4,     4,     4,
       4,     4,     4,     4,   150,     4,     4,     4,   152,     4,
     152,   152,     4,     4,   152,     4,   405,   406,   407,     4,
       4,   150,   150,   150,     4,     4,   152,   152,     4,   152,
       4,     4,     7,   120,   149,     7,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,   509,   510,     7,
       7,   509,   510,     7,     7,     5,     8,     3,   520,     7,
     522,     5,     5,     5,   149,   527,   149,   149,     7,   527,
       7,     7,     7,     7,     4,     7,     7,   149,   527,     7,
      80,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   485,     4,     4,   126,
       4,     4,   149,   149,     4,     6,     3,     6,     3,     3,
       6,     4,   456,   502,     6,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     4,   149,   149,     3,     6,
       3,     3,     6,   515,     4,     4,     4,     8,     4,     4,
     150,     4,     4,   152,     4,     4,     4,     4,     3,   303,
       6,     4,   503,     5,   150,     5,     7,   150,   152,     8,
     150,     8,   150,   150,   150,     8,     4,   150,   150,   150,
       4,     4,   150,   150,     4,     7,     4,     4,     4,   326,
     330,   149,   149,   508,   510,   708,   720,   723,   729,   727,
     736,   713,   711,   149,   149,   382,   344,   717,   149,   716,
     149,   714,   149,   374,   149,   719,   379,   756,   149,   149,
     754,   759,   150,   760,   757,   348,   149,   762,   527,   355,
     365,   747,   149,   152,   150,   150,   522,   743,   846,   694,
     862,   874,   891,   398,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   708,    -1,   711,   711,
     708,    -1,   714,    -1,    -1,   717,    -1,    -1,   717,   717,
     717,   711,   711,    -1,    -1,   727,    -1,   711,   711,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   743,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   757,   754,    -1,    -1,   757,    -1,    -1,   760,    -1,
      -1,    -1,    -1,    -1,    -1,   754,    -1,    -1,   757,    -1,
      -1,   760,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   845,    -1,    -1,    -1,   845,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     862,    -1,    -1,    -1,   862
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,     0,     5,     7,     9,
     149,   150,   151,   152,   167,   168,   169,   174,     7,   183,
       7,   189,     7,   200,     7,   277,     7,   342,     7,   356,
       7,   373,     7,   300,     7,   324,     7,   253,     7,   429,
     175,   170,   184,   190,   201,   278,   343,   357,   374,   301,
     325,   254,   430,   167,   176,   177,   149,   172,   173,    10,
     125,   134,   135,   136,   149,   182,   185,   186,   187,   456,
     458,   460,   462,    11,    14,    15,    31,    32,    33,    34,
      35,    36,    37,    38,    66,    67,    68,    69,    81,    84,
      91,    99,   100,   103,   182,   191,   192,   193,   194,   195,
     196,   197,   198,   207,   209,   233,   239,   245,   247,   261,
     271,   294,   318,   396,   406,   418,   419,   427,    12,    13,
     202,   203,   204,   206,     7,    48,    50,    57,    58,    59,
      60,    61,    62,    71,    72,    79,   182,   193,   194,   195,
     196,   279,   280,   281,   283,   285,   287,   289,   292,   293,
     318,   336,   350,   367,   392,    49,    56,   182,   318,   344,
     345,   346,   348,    51,    52,    53,    54,    55,   182,   318,
     348,   358,   359,   360,   362,   363,   365,   366,    69,    73,
      74,    75,    76,    77,    78,   182,   318,   375,   376,   377,
     378,   380,   382,   384,   386,   388,   390,    16,    39,    41,
      42,    45,    46,    47,   182,   223,   302,   303,   304,   305,
     306,   307,   308,   310,   312,   314,   315,   317,    40,    43,
      44,   182,   223,   306,   312,   326,   327,   328,   329,   330,
     332,   333,   334,   335,    82,    83,   182,   255,   256,   257,
     259,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   182,   431,   432,   433,   434,
     436,   438,   439,   441,   442,   443,   446,   448,   449,   450,
     451,   454,     6,     3,     4,     8,     3,   188,   463,   457,
     459,   461,     4,     3,     8,   199,   208,   210,     4,     4,
       4,     4,     4,   272,   295,   319,   234,   246,   240,   397,
     248,   262,   407,     4,   420,   428,     3,     8,   205,     4,
       3,     8,   399,   337,   351,   282,   284,   286,     4,     4,
     290,   288,   368,   393,     3,     8,   347,   349,     3,     8,
     361,     4,   364,     4,     4,     3,     8,   391,   379,   381,
     383,   385,   387,   389,     8,     3,   309,   224,     4,   313,
     311,   316,     4,     8,     3,   331,     4,     4,     8,     3,
     258,   260,     3,     8,     4,   435,   437,     4,   440,     4,
       4,   444,   447,     4,     4,     4,   452,   455,     3,     8,
     167,   167,   149,     4,     4,     4,     4,     4,   186,     4,
       4,     4,   150,   150,   150,   150,   150,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   150,     4,     4,
     192,     4,   152,   203,    70,   182,   223,   318,   400,   401,
     402,   403,   404,     4,     4,     4,     4,     4,   150,   152,
       4,     4,     4,     4,   280,     4,     4,   345,     4,   150,
       4,   150,   150,   359,     4,     4,     4,     4,     4,     4,
       4,   377,     4,     4,   150,     4,     4,     4,   152,   304,
       4,   152,   152,   328,     4,     4,   256,   152,     4,     4,
     150,     4,   150,   150,     4,     4,   152,   152,   152,     4,
       4,   432,     4,     7,     7,   167,   167,   167,     7,     7,
       7,     5,     5,     5,     5,     5,     5,     5,     5,     7,
       7,     7,     7,     5,   178,   405,     8,     3,     5,     5,
     149,   149,   149,    63,    64,    65,   291,   149,     5,     7,
     149,   169,   171,   149,   149,   178,   178,   178,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   167,
     149,   149,   149,   118,   119,   445,   120,   121,   122,   123,
     124,   152,   453,   149,   167,   191,   126,   464,   465,   466,
     202,    16,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,   182,   211,   212,   213,   216,   218,   220,   222,
     223,   225,   226,   227,   228,   229,   231,   211,     7,   273,
     274,   275,     7,   296,   297,   298,     7,   320,   321,   322,
      75,   149,   235,   236,   237,   238,   176,    76,    78,   237,
     241,   242,   243,   244,   287,   398,     7,   249,   250,   251,
      85,    86,    87,    88,    89,    90,   263,   264,   265,   266,
     267,   268,   269,   270,    16,    95,    96,    97,    98,   182,
     225,   408,   409,   410,   413,   414,   416,   417,   101,   102,
     421,   422,   423,   425,   431,   179,     4,   402,     7,   338,
     339,   340,     7,   352,   353,   354,     7,   369,   370,   371,
      80,   394,     8,   467,     3,     8,     8,   214,   217,   219,
     221,     4,     4,     4,     4,     4,   230,   232,     3,     8,
       8,   276,     6,     3,   299,     6,     3,   323,     6,     3,
       3,     6,     6,     3,     6,     3,     6,   252,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   411,   415,
       4,     4,     4,     3,     8,   424,   426,     3,     8,     8,
     149,   180,   181,   149,   341,     6,     3,   355,     6,     3,
     372,     6,     3,   395,     8,     4,   465,     4,     4,     4,
       4,   150,   152,   150,   152,   150,     4,     4,   212,   279,
     275,   302,   298,   326,   322,   236,   242,   287,   255,   251,
     150,   150,   150,   150,   150,   150,   264,     4,     4,   150,
     150,   150,   409,     4,     4,   422,     6,     3,   344,   340,
     358,   354,   375,   371,     4,     5,    17,    18,    19,    20,
     215,   149,   149,   149,   149,   149,     8,     8,     8,     8,
      92,    93,    94,   412,   149,   149,   149,   149,     8,     8,
       8,   149,     7,   468,   469,   470,     3,     6,   127,   129,
     130,   182,   223,   471,   472,   473,   474,   476,   469,   477,
       4,   475,     3,     8,     4,   150,     4,   472,     5,   149,
       7,   478,   479,   480,     3,     6,   128,   131,   132,   133,
     481,   482,   483,   485,   486,   487,   479,   484,     4,     4,
       4,     3,     8,     4,   152,   150,   150,   482,   149
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   153,   155,   154,   156,   154,   157,   154,   158,   154,
     159,   154,   160,   154,   161,   154,   162,   154,   163,   154,
     164,   154,   165,   154,   166,   154,   167,   167,   167,   167,
     167,   167,   167,   168,   170,   169,   171,   172,   172,   173,
     173,   175,   174,   176,   176,   177,   177,   179,   178,   180,
     180,   181,   181,   182,   184,   183,   185,   185,   186,   186,
     186,   186,   186,   186,   188,   187,   190,   189,   191,   191,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   193,   194,   195,   196,   197,   199,   198,   201,
     200,   202,   202,   203,   203,   205,   204,   206,   208,   207,
     210,   209,   211,   211,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   214,   213,   215,
     215,   215,   215,   217,   216,   219,   218,   221,   220,   222,
     224,   223,   225,   226,   227,   228,   230,   229,   232,   231,
     234,   233,   235,   235,   236,   236,   237,   238,   240,   239,
     241,   241,   242,   242,   242,   243,   244,   246,   245,   248,
     247,   249,   249,   250,   250,   252,   251,   254,   253,   255,
     255,   255,   256,   256,   258,   257,   260,   259,   262,   261,
     263,   263,   264,   264,   264,   264,   264,   264,   265,   266,
     267,   268,   269,   270,   272,   271,   273,   273,   274,   274,
     276,   275,   278,   277,   279,   279,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   282,   281,   284,   283,   286,   285,   288,
     287,   290,   289,   291,   291,   291,   292,   293,   295,   294,
     296,   296,   297,   297,   299,   298,   301,   300,   302,   302,
     303,   303,   304,   304,   304,   304,   304,   304,   304,   304,
     305,   306,   307,   309,   308,   311,   310,   313,   312,   314,
     316,   315,   317,   319,   318,   320,   320,   321,   321,   323,
     322,   325,   324,   326,   326,   327,   327,   328,   328,   328,
     328,   328,   328,   328,   329,   331,   330,   332,   333,   334,
     335,   337,   336,   338,   338,   339,   339,   341,   340,   343,
     342,   344,   344,   345,   345,   345,   345,   347,   346,   349,
     348,   351,   350,   352,   352,   353,   353,   355,   354,   357,
     356,   358,   358,   359,   359,   359,   359,   359,   359,   359,
     359,   361,   360,   362,   364,   363,   365,   366,   368,   367,
     369,   369,   370,   370,   372,   371,   374,   373,   375,   375,
     376,   376,   377,   377,   377,   377,   377,   377,   377,   377,
     377,   379,   378,   381,   380,   383,   382,   385,   384,   387,
     386,   389,   388,   391,   390,   393,   392,   395,   394,   397,
     396,   398,   398,   399,   287,   400,   400,   401,   401,   402,
     402,   402,   402,   403,   405,   404,   407,   406,   408,   408,
     409,   409,   409,   409,   409,   409,   409,   411,   410,   412,
     412,   412,   413,   415,   414,   416,   417,   418,   420,   419,
     421,   421,   422,   422,   424,   423,   426,   425,   428,   427,
     430,   429,   431,   431,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   433,
     435,   434,   437,   436,   438,   440,   439,   441,   442,   444,
     443,   445,   445,   447,   446,   448,   449,   450,   452,   451,
     453,   453,   453,   453,   453,   455,   454,   457,   456,   459,
     458,   461,   460,   463,   462,   464,   464,   465,   467,   466,
     468,   468,   470,   469,   471,   471,   472,   472,   472,   472,
     472,   473,   475,   474,   477,   476,   478,   478,   480,   479,
     481,   481,   482,   482,   482,   482,   484,   483,   485,   486,
     487
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
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
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
       0,   234,   234,   234,   235,   235,   236,   236,   237,   237,
     238,   238,   239,   239,   240,   240,   241,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   253,   254,   255,   256,
     257,   258,   259,   262,   267,   267,   278,   281,   282,   285,
     289,   296,   296,   303,   304,   307,   311,   318,   318,   325,
     326,   329,   333,   344,   354,   354,   366,   367,   371,   372,
     373,   374,   375,   376,   379,   379,   396,   396,   404,   405,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   434,   439,   444,   449,   454,   459,   459,   469,
     469,   477,   478,   481,   482,   485,   485,   495,   501,   501,
     511,   511,   521,   522,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   540,   540,   547,
     548,   549,   550,   553,   553,   561,   561,   569,   569,   577,
     582,   582,   590,   595,   600,   605,   610,   610,   618,   618,
     627,   627,   637,   638,   641,   642,   645,   650,   655,   655,
     665,   666,   669,   670,   671,   674,   679,   686,   686,   696,
     696,   706,   707,   710,   711,   714,   714,   722,   722,   730,
     731,   732,   735,   736,   739,   739,   747,   747,   755,   755,
     765,   766,   769,   770,   771,   772,   773,   774,   777,   782,
     787,   792,   797,   802,   810,   810,   823,   824,   827,   828,
     835,   835,   858,   858,   867,   868,   872,   873,   874,   875,
     876,   877,   878,   879,   880,   881,   882,   883,   884,   885,
     886,   887,   888,   891,   891,   899,   899,   907,   907,   915,
     915,   923,   923,   930,   931,   932,   935,   940,   949,   949,
     961,   962,   965,   966,   971,   971,   982,   982,   992,   993,
     996,   997,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1010,  1012,  1017,  1019,  1019,  1027,  1027,  1035,  1035,  1043,
    1045,  1045,  1053,  1062,  1062,  1074,  1075,  1080,  1081,  1086,
    1086,  1097,  1097,  1108,  1109,  1114,  1115,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1129,  1131,  1131,  1139,  1141,  1143,
    1148,  1156,  1156,  1168,  1169,  1172,  1173,  1176,  1176,  1184,
    1184,  1192,  1193,  1196,  1197,  1198,  1199,  1202,  1202,  1210,
    1210,  1220,  1220,  1232,  1233,  1236,  1237,  1240,  1240,  1248,
    1248,  1256,  1257,  1260,  1261,  1262,  1263,  1264,  1265,  1266,
    1267,  1270,  1270,  1278,  1283,  1283,  1291,  1296,  1304,  1304,
    1314,  1315,  1318,  1319,  1322,  1322,  1330,  1330,  1338,  1339,
    1342,  1343,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1358,  1358,  1368,  1368,  1378,  1378,  1386,  1386,  1394,
    1394,  1402,  1402,  1410,  1410,  1423,  1423,  1433,  1433,  1444,
    1444,  1454,  1455,  1458,  1458,  1466,  1467,  1470,  1471,  1474,
    1475,  1476,  1477,  1480,  1482,  1482,  1493,  1493,  1503,  1504,
    1507,  1508,  1509,  1510,  1511,  1512,  1513,  1516,  1516,  1523,
    1524,  1525,  1528,  1533,  1533,  1541,  1546,  1553,  1560,  1560,
    1570,  1571,  1574,  1575,  1578,  1578,  1586,  1586,  1596,  1596,
    1606,  1606,  1614,  1615,  1618,  1619,  1620,  1621,  1622,  1623,
    1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,  1635,
    1640,  1640,  1648,  1648,  1656,  1661,  1661,  1669,  1674,  1679,
    1679,  1687,  1688,  1691,  1691,  1699,  1704,  1709,  1714,  1714,
    1722,  1725,  1728,  1731,  1734,  1740,  1740,  1750,  1750,  1757,
    1757,  1764,  1764,  1777,  1777,  1790,  1791,  1795,  1799,  1799,
    1811,  1812,  1816,  1816,  1824,  1825,  1828,  1829,  1830,  1831,
    1832,  1835,  1840,  1840,  1848,  1848,  1858,  1859,  1862,  1862,
    1870,  1871,  1874,  1875,  1876,  1877,  1880,  1880,  1888,  1893,
    1898
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
#line 4325 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1903 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
