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
      case 172: // value
      case 176: // map_value
      case 220: // db_type
      case 298: // hr_mode
      case 431: // duid_type
      case 464: // ncr_protocol_value
      case 472: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 156: // "boolean"
        value.move< bool > (that.value);
        break;

      case 155: // "floating point"
        value.move< double > (that.value);
        break;

      case 154: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 153: // "constant string"
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
      case 172: // value
      case 176: // map_value
      case 220: // db_type
      case 298: // hr_mode
      case 431: // duid_type
      case 464: // ncr_protocol_value
      case 472: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 156: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 155: // "floating point"
        value.copy< double > (that.value);
        break;

      case 154: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 153: // "constant string"
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
            case 153: // "constant string"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 154: // "integer"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 155: // "floating point"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 156: // "boolean"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 172: // value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 176: // map_value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 220: // db_type

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 298: // hr_mode

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 431: // duid_type

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 464: // ncr_protocol_value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 472: // replace_client_name_value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 172: // value
      case 176: // map_value
      case 220: // db_type
      case 298: // hr_mode
      case 431: // duid_type
      case 464: // ncr_protocol_value
      case 472: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 156: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 155: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 154: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 153: // "constant string"
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
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 814 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 858 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 304 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 316 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 901 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 338 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 394 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 402 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 442 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 478 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1092 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1101 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1143 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 554 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 564 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1213 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1258 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1303 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1368 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 664 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 669 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 674 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1406 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1424 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1444 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1455 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 759 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 816 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 821 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 829 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 834 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 858 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1670 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 954 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 966 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 967 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 968 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1826 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 989 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1884 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1932 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1942 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1954 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1125 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1981 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1133 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2017 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1153 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1168 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2055 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2083 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1256 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2274 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2284 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2323 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2341 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2379 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1505 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2483 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2598 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2617 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2627 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2645 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2654 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2699 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2705 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2711 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2832 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2863 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2953 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2961 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2976 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2982 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2990 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3035 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3052 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1905 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1981 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 2005 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3322 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3326 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -707;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     223,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,    70,    29,    61,    65,    73,   111,
     138,   146,   166,   168,   170,   174,   181,   198,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,    29,   -44,     3,     9,    78,   160,
      87,    33,    43,   162,    53,   128,   -19,   242,  -707,   201,
     206,   207,   229,   268,  -707,  -707,  -707,  -707,  -707,   282,
    -707,    94,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,   291,   297,   299,   303,   307,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,   323,  -707,  -707,
    -707,    98,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,   327,   127,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,   329,   335,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   129,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     130,  -707,  -707,  -707,  -707,   339,  -707,   340,   341,  -707,
    -707,  -707,  -707,  -707,   136,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     231,   281,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     338,  -707,  -707,   372,  -707,  -707,  -707,   373,  -707,  -707,
     370,   376,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,   377,   378,  -707,  -707,  -707,  -707,   375,
     381,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,   143,  -707,  -707,  -707,   382,  -707,  -707,   383,  -707,
     384,   385,  -707,  -707,   386,   387,   388,  -707,  -707,  -707,
     149,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,    29,    29,  -707,
     227,   389,   390,   392,   393,   394,  -707,     3,  -707,   395,
     396,   397,   248,   249,   251,   252,   253,   400,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   264,   415,
     416,     9,  -707,   417,   266,    78,  -707,   419,   420,   421,
     422,   423,   424,   275,   274,   427,   428,   432,   433,   434,
     160,  -707,   435,    87,  -707,   436,   287,   438,   289,   293,
      33,  -707,   440,   444,   445,   446,   447,   450,   451,  -707,
      43,  -707,   452,   453,   304,   455,   456,   457,   306,  -707,
      53,   459,   309,   311,  -707,   128,   464,   465,   250,  -707,
     314,   467,   468,   319,   470,   321,   322,   473,   474,   324,
     325,   326,   475,   479,   242,  -707,  -707,  -707,   480,   478,
     481,    29,    29,    29,  -707,   482,   483,   484,  -707,  -707,
    -707,  -707,  -707,   380,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,  -707,   497,   498,  -707,   502,  -707,
    -707,   503,   504,   505,   333,   334,   347,  -707,  -707,   -11,
     502,   348,   506,   507,  -707,   357,  -707,   360,  -707,   362,
    -707,  -707,  -707,   502,   502,   502,   363,   364,   365,   366,
    -707,   367,   368,  -707,   369,   371,   374,  -707,  -707,   379,
    -707,  -707,  -707,   391,    29,  -707,  -707,   398,   399,  -707,
     401,  -707,  -707,   216,   402,  -707,  -707,  -707,    88,   403,
    -707,    29,     9,   414,  -707,  -707,  -707,    78,    34,    34,
     519,   521,   522,   523,   -27,    29,   221,   524,   526,   157,
      49,   236,   242,  -707,  -707,   527,   528,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   529,   454,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,   151,  -707,   152,  -707,  -707,   171,  -707,
    -707,  -707,  -707,   534,   535,   536,   537,   538,  -707,  -707,
    -707,   192,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,   233,  -707,   539,   543,  -707,
    -707,   541,   545,  -707,  -707,   544,   546,  -707,  -707,   547,
     552,  -707,  -707,  -707,   102,  -707,  -707,  -707,   551,  -707,
    -707,  -707,   257,  -707,  -707,  -707,  -707,   290,  -707,  -707,
     553,   555,  -707,   556,   557,   558,   559,   560,   561,   235,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   562,
     563,   564,  -707,  -707,   258,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,   259,  -707,  -707,  -707,   261,   418,  -707,
     566,   567,  -707,  -707,   568,   570,  -707,  -707,   569,   573,
    -707,  -707,   571,  -707,   565,   414,  -707,  -707,   574,   576,
     577,   578,   429,   430,   431,   437,   441,   580,   583,    34,
    -707,  -707,   160,  -707,   519,    53,  -707,   521,   128,  -707,
     522,   194,  -707,   523,   -27,  -707,  -707,   221,  -707,    44,
     524,  -707,   -19,  -707,   526,   442,   443,   448,   449,   458,
     460,   157,  -707,   584,   585,   461,   462,   463,    49,  -707,
     586,   587,   236,  -707,  -707,  -707,   588,   589,    87,  -707,
     527,    33,  -707,   528,    43,  -707,   529,   594,  -707,   572,
    -707,   272,   466,   469,   471,  -707,  -707,  -707,  -707,  -707,
     472,   476,  -707,   267,  -707,   591,  -707,   592,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,   269,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     597,  -707,  -707,  -707,   596,   602,  -707,  -707,  -707,  -707,
    -707,   270,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
      68,   477,  -707,  -707,  -707,  -707,   485,   486,  -707,  -707,
     499,   271,  -707,   277,  -707,   598,  -707,   501,   600,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,   194,  -707,   604,   508,  -707,    44,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,   302,  -707,  -707,   510,  -707,  -707,    71,   600,
    -707,  -707,  -707,   605,  -707,  -707,  -707,   279,  -707,  -707,
    -707,  -707,  -707,   606,   516,   607,    71,  -707,   608,  -707,
     518,  -707,   611,  -707,  -707,   312,  -707,   123,   611,  -707,
    -707,   616,   617,   619,   280,  -707,  -707,  -707,  -707,  -707,
    -707,   622,   530,   533,   540,   123,  -707,   525,  -707,  -707,
    -707,  -707,  -707
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   102,     9,   215,    11,   353,    13,
     375,    15,   404,    17,   282,    19,   290,    21,   325,    23,
     180,    25,   490,    27,    45,    39,     0,     0,     0,     0,
       0,     0,   406,     0,   292,   327,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   543,   537,   539,   541,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   100,   111,
     113,     0,     0,     0,     0,     0,   207,   280,   317,   255,
     153,   170,   161,   437,   172,   191,   456,     0,   478,   488,
      94,     0,    70,    72,    73,    74,    75,    76,    79,    80,
      81,    82,    84,    83,    88,    89,    77,    78,    86,    87,
      85,    90,    91,    92,    93,   108,     0,     0,   104,   106,
     107,   345,   367,   365,   238,   240,   242,     0,     0,   248,
     246,   244,   396,   433,   237,   219,   220,   221,   222,     0,
     217,   226,   227,   228,   231,   232,   234,   229,   230,   223,
     224,   236,   225,   233,   235,   363,   362,   359,   360,   358,
       0,   355,   357,   361,   389,     0,   392,     0,     0,   388,
     383,   384,   382,   387,     0,   377,   379,   380,   385,   386,
     381,   431,   419,   421,   423,   425,   427,   429,   418,   417,
       0,   407,   408,   412,   413,   410,   414,   415,   416,   411,
       0,   307,   143,     0,   311,   309,   314,     0,   303,   304,
       0,   293,   294,   296,   306,   297,   298,   299,   313,   300,
     301,   302,   339,     0,     0,   337,   338,   341,   342,     0,
     328,   329,   331,   332,   333,   334,   335,   336,   187,   189,
     184,     0,   182,   185,   186,     0,   510,   512,     0,   515,
       0,     0,   519,   523,     0,     0,     0,   528,   535,   508,
       0,   492,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,    44,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    55,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   216,     0,     0,   354,     0,     0,     0,     0,     0,
       0,   376,     0,     0,     0,     0,     0,     0,     0,   405,
       0,   283,     0,     0,     0,     0,     0,     0,     0,   291,
       0,     0,     0,     0,   326,     0,     0,     0,     0,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   491,    48,    41,     0,     0,
       0,     0,     0,     0,    59,     0,     0,     0,    95,    96,
      97,    98,    99,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   477,     0,     0,    71,     0,   110,
     105,     0,     0,     0,     0,     0,     0,   253,   254,     0,
       0,     0,     0,     0,   218,     0,   356,     0,   391,     0,
     394,   395,   378,     0,     0,     0,     0,     0,     0,     0,
     409,     0,     0,   305,     0,     0,     0,   316,   295,     0,
     343,   344,   330,     0,     0,   183,   509,     0,     0,   514,
       0,   517,   518,     0,     0,   525,   526,   527,     0,     0,
     493,     0,     0,     0,   538,   540,   542,     0,     0,     0,
     209,   284,   319,   257,     0,    45,     0,     0,   174,     0,
       0,     0,     0,    49,   109,   347,   369,    38,   366,   239,
     241,   243,   250,   251,   252,   249,   247,   245,   398,     0,
     364,   390,   393,   432,   420,   422,   424,   426,   428,   430,
     308,   144,   312,   310,   315,   340,   188,   190,   511,   513,
     516,   521,   522,   520,   524,   530,   531,   532,   533,   534,
     529,   536,    42,     0,   548,     0,   545,   547,     0,   130,
     136,   138,   140,     0,     0,     0,     0,     0,   149,   151,
     129,     0,   115,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,   213,     0,   210,   211,
     288,     0,   285,   286,   323,     0,   320,   321,   261,     0,
     258,   259,   159,   160,     0,   155,   157,   158,     0,   168,
     169,   165,     0,   163,   166,   167,   441,     0,   439,   178,
       0,   175,   176,     0,     0,     0,     0,     0,     0,     0,
     193,   195,   196,   197,   198,   199,   200,   467,   473,     0,
       0,     0,   466,   465,     0,   458,   460,   463,   461,   462,
     464,   484,   486,     0,   480,   482,   483,     0,    51,   351,
       0,   348,   349,   373,     0,   370,   371,   402,     0,   399,
     400,   435,     0,    67,     0,     0,   544,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,   114,     0,   208,     0,   292,   281,     0,   327,   318,
       0,     0,   256,     0,     0,   154,   171,     0,   162,   443,
       0,   438,     0,   173,     0,     0,     0,     0,     0,     0,
       0,     0,   192,     0,     0,     0,     0,     0,     0,   457,
       0,     0,     0,   479,   489,    53,     0,    52,     0,   346,
       0,     0,   368,     0,   406,   397,     0,     0,   434,     0,
     546,     0,     0,     0,     0,   142,   145,   146,   147,   148,
       0,     0,   116,     0,   212,     0,   287,     0,   322,   279,
     276,   278,   269,   270,   265,   266,   267,   268,   274,   275,
     273,   277,     0,   263,   271,   272,   260,   156,   164,   453,
       0,   451,   452,   450,     0,   444,   445,   447,   448,   449,
     440,     0,   177,   201,   202,   203,   204,   205,   206,   194,
       0,     0,   472,   475,   476,   459,     0,     0,   481,    50,
       0,     0,   350,     0,   372,     0,   401,     0,     0,   132,
     133,   134,   135,   131,   137,   139,   141,   150,   152,   214,
     289,   324,     0,   262,     0,     0,   442,     0,   179,   469,
     470,   471,   468,   474,   485,   487,    54,   352,   374,   403,
     436,   552,     0,   550,   264,     0,   455,   446,     0,     0,
     549,   454,   564,     0,   562,   560,   556,     0,   554,   558,
     559,   557,   551,     0,     0,     0,     0,   553,     0,   561,
       0,   555,     0,   563,   568,     0,   566,     0,     0,   565,
     576,     0,     0,     0,     0,   570,   572,   573,   574,   575,
     567,     0,     0,     0,     0,     0,   569,     0,   578,   579,
     580,   571,   577
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,    12,  -707,   175,  -707,  -707,
    -707,  -707,  -707,  -707,   106,  -707,  -346,  -707,  -707,  -707,
     -66,  -707,  -707,  -707,   310,  -707,  -707,  -707,  -707,   120,
     292,   -62,   -50,   -48,   -43,  -707,  -707,  -707,  -707,  -707,
     117,   295,  -707,  -707,  -707,  -707,  -707,  -707,  -707,   116,
     -83,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,   -73,  -707,  -529,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,   -97,  -514,  -707,  -707,  -707,  -707,
     -96,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -102,
    -707,  -707,  -707,   -99,   246,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -106,  -707,  -707,  -707,  -707,  -707,  -707,  -706,
    -707,  -707,  -707,   -77,  -707,  -707,  -707,   -74,   301,  -707,
    -707,  -696,  -707,  -694,  -707,   -42,  -707,   -38,  -707,  -692,
    -707,  -707,  -707,  -683,  -707,  -707,  -707,  -707,   -84,  -707,
    -707,  -222,   609,  -707,  -707,  -707,  -707,  -707,   -76,  -707,
    -707,  -707,   -68,  -707,   294,  -707,   -61,  -707,  -707,  -707,
    -707,  -707,   -53,  -707,  -707,  -707,  -707,  -707,   -54,  -707,
    -707,  -707,   -39,  -707,  -707,  -707,   -33,  -707,   285,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
     -80,  -707,  -707,  -707,   -72,   336,  -707,  -707,   -40,  -707,
    -707,  -707,  -707,  -707,   -75,  -707,  -707,  -707,   -71,   331,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,   -79,  -707,  -707,  -707,   -70,  -707,   330,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -682,  -707,  -707,  -707,  -707,  -707,  -707,   -37,
    -707,  -707,  -707,  -171,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,   -51,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,   -49,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,   177,   298,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,  -707,
    -707,  -707,  -707,  -707,  -707,  -707,  -707,     6,  -707,  -707,
    -707,  -184,  -707,  -707,  -200,  -707,  -707,  -707,  -707,  -707,
    -707,  -210,  -707,  -707,  -226,  -707,  -707,  -707,  -707,  -707
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    78,    37,    38,    65,   538,
      82,    83,    39,    64,    79,    80,   534,   688,   766,   767,
     120,    41,    66,    91,    92,    93,   311,    43,    67,   121,
     122,   123,   124,   125,   126,   127,   128,   319,    45,    68,
     147,   148,   149,   343,   150,   129,   320,   130,   321,   601,
     602,   603,   708,   863,   604,   709,   605,   710,   606,   711,
     607,   239,   383,   609,   610,   611,   612,   613,   717,   614,
     718,   131,   331,   634,   635,   636,   637,   132,   333,   642,
     643,   644,   645,   133,   332,   134,   335,   650,   651,   652,
     742,    61,    76,   271,   272,   273,   396,   274,   397,   135,
     336,   659,   660,   661,   662,   663,   664,   665,   666,   136,
     327,   617,   618,   619,   722,    47,    69,   169,   170,   171,
     350,   172,   351,   173,   352,   174,   357,   175,   356,   176,
     355,   545,   177,   178,   137,   330,   629,   630,   631,   731,
     812,   813,   138,   328,    55,    73,   621,   622,   623,   725,
      57,    74,   240,   241,   242,   243,   244,   245,   246,   382,
     247,   386,   248,   385,   249,   250,   387,   251,   139,   329,
     625,   626,   627,   728,    59,    75,   259,   260,   261,   262,
     263,   391,   264,   265,   266,   267,   180,   347,   690,   691,
     692,   768,    49,    70,   190,   191,   192,   362,   181,   349,
     182,   348,   694,   695,   696,   771,    51,    71,   204,   205,
     206,   365,   207,   208,   367,   209,   210,   183,   358,   698,
     699,   700,   774,    53,    72,   220,   221,   222,   223,   373,
     224,   374,   225,   375,   226,   376,   227,   377,   228,   378,
     229,   372,   184,   359,   702,   777,   140,   334,   647,   648,
     739,   824,   825,   826,   827,   828,   874,   829,   141,   337,
     674,   675,   676,   753,   882,   677,   678,   754,   679,   680,
     142,   143,   339,   683,   684,   685,   760,   686,   761,   144,
     340,    63,    77,   290,   291,   292,   293,   401,   294,   402,
     295,   296,   404,   297,   298,   299,   407,   573,   300,   408,
     301,   302,   303,   304,   412,   580,   305,   413,    94,   313,
      95,   314,    96,   315,    97,   312,   585,   586,   587,   704,
     892,   893,   898,   907,   908,   909,   910,   915,   911,   913,
     925,   926,   927,   934,   935,   936,   941,   937,   938,   939
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      90,   673,   256,   164,   186,   199,   218,   165,   238,   255,
     270,   289,   641,    84,   257,   179,   189,   202,   219,   166,
      98,   167,   258,    99,   100,   805,   168,    36,   187,   200,
     193,   203,   188,   201,    29,   806,    30,   807,    31,   810,
     101,   102,   103,   104,   105,   106,   107,   108,   811,   815,
     589,   632,   542,   543,   544,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   667,   268,   269,    40,   231,
      28,   108,    42,   232,   594,   109,   110,   111,   112,   113,
      44,   108,   108,   232,   194,   195,   196,   197,   198,   153,
     145,   146,   232,   114,   233,   234,   115,   317,   235,   236,
     237,   341,   318,   116,   160,   734,   342,   161,   735,    81,
     232,   117,   118,   211,   546,   119,   819,   820,    46,   212,
     213,   214,   215,   216,   217,   108,   633,   553,   554,   555,
     345,    85,   360,   363,    89,   346,   185,   361,   364,   370,
      86,    87,    88,   153,   371,    48,   398,   668,   669,   670,
     671,   399,   414,    50,   341,   705,    89,   415,   160,   703,
     706,   161,    89,   879,   880,   881,   805,   232,   252,   233,
     234,   253,   254,    52,   345,    54,   806,    56,   807,   707,
     810,    58,    32,    33,    34,    35,    89,    89,    60,   811,
     815,   101,   102,   103,   104,   719,    89,    89,   108,   107,
     720,   902,    89,   903,   904,    62,    89,   306,   151,   307,
     152,   308,   575,   576,   577,   578,   153,   154,   155,   156,
     157,   158,   159,   641,    89,   101,   102,   103,   104,   673,
     106,   160,   108,   232,   161,   162,   719,   309,   751,   379,
      89,   721,   163,   752,   579,   653,   654,   655,   656,   657,
     658,    90,   155,   156,   930,   158,   159,   931,   932,   933,
     737,   758,   762,   738,   414,   160,   759,   763,   161,   764,
     360,   310,   872,   398,   363,   869,   163,   873,   878,   887,
     370,    89,   916,   945,   380,   888,   316,   917,   946,   859,
     860,   861,   862,   740,   164,   322,   741,   186,   165,   632,
     639,   323,   640,   324,   199,   899,   179,   325,   900,   189,
     166,   326,   167,    89,   218,   928,   202,   168,   929,   416,
     417,   187,   256,   193,   238,   188,   219,   338,   200,   255,
     203,   344,   201,   353,   257,   268,   269,   571,   572,   354,
     681,   682,   258,   366,   368,   369,   381,    89,   289,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   384,   388,   389,   390,
     418,   392,   393,   394,   395,   520,   400,   403,   405,   406,
     409,   410,   411,   419,   420,    89,   421,   422,   423,   425,
     426,   427,   428,   429,   433,   430,   431,   432,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   448,   449,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   514,   515,   516,   461,   462,   463,   465,
     467,   468,   469,   470,   473,   608,   608,   471,   474,   475,
     476,   477,   600,   600,   478,   479,   481,   482,   483,   484,
     485,   486,   487,   489,   672,   490,   289,   491,   493,   494,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   508,
     505,   506,   507,   509,   511,   512,   539,   540,   513,   517,
     518,   519,   521,   522,   523,   524,   525,   526,   527,   528,
     541,   547,   529,   530,   531,   532,   567,   533,   535,   536,
     550,   548,    30,   551,   549,   552,   556,   557,   558,   559,
     560,   561,   562,   582,   563,   574,   616,   564,   620,   624,
     628,   646,   565,   649,   689,   693,   697,   701,   712,   713,
     714,   715,   716,   584,   566,   723,   724,   726,   727,   730,
     729,   568,   569,   732,   570,   733,   581,   736,   744,   743,
     745,   746,   747,   748,   749,   750,   755,   756,   757,   779,
     770,   765,   769,   773,   772,   775,   776,   858,   781,   778,
     782,   783,   784,   785,   790,   787,   786,   791,   840,   841,
     846,   847,   850,   788,   849,   789,   833,   834,   857,   870,
     871,   875,   835,   836,   876,   877,   889,   891,   895,   914,
     918,   920,   837,   922,   838,   842,   843,   844,   924,   864,
     942,   943,   865,   944,   866,   867,   947,   424,   537,   868,
     883,   638,   583,   447,   588,   615,   792,   817,   884,   885,
     450,   818,   832,   831,   495,   839,   608,   794,   793,   816,
     894,   796,   886,   600,   890,   256,   164,   795,   804,   238,
     165,   464,   255,   901,   896,   799,   822,   257,   179,   800,
     919,   923,   166,   821,   167,   258,   270,   814,   952,   168,
     492,   801,   230,   802,   488,   823,   948,   949,   803,   808,
     852,   798,   672,   809,   950,   797,   851,   856,   854,   466,
     853,   472,   186,   830,   855,   199,   897,   845,   218,   687,
     480,   780,   510,   848,   189,   912,   921,   202,   940,   951,
     219,     0,     0,     0,     0,     0,   187,     0,   193,   200,
     188,   203,     0,   201,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   804,
       0,     0,     0,     0,   822,     0,   799,     0,     0,     0,
     800,   821,     0,     0,     0,     0,     0,     0,   814,     0,
       0,     0,   801,   823,   802,   906,     0,     0,     0,   803,
     808,     0,   905,     0,   809,     0,     0,     0,     0,     0,
       0,     0,     0,   906,     0,     0,     0,     0,     0,     0,
     905
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      66,   530,    75,    69,    70,    71,    72,    69,    74,    75,
      76,    77,   526,    10,    75,    69,    70,    71,    72,    69,
      11,    69,    75,    14,    15,   731,    69,    15,    70,    71,
      70,    71,    70,    71,     5,   731,     7,   731,     9,   731,
      31,    32,    33,    34,    35,    36,    37,    38,   731,   731,
      16,    78,    63,    64,    65,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    16,    85,    86,     7,    16,
       0,    38,     7,    39,    25,    66,    67,    68,    69,    70,
       7,    38,    38,    39,    51,    52,    53,    54,    55,    56,
      12,    13,    39,    84,    41,    42,    87,     3,    45,    46,
      47,     3,     8,    94,    71,     3,     8,    74,     6,   153,
      39,   102,   103,    70,   460,   106,    72,    73,     7,    76,
      77,    78,    79,    80,    81,    38,   153,   473,   474,   475,
       3,   128,     3,     3,   153,     8,    49,     8,     8,     3,
     137,   138,   139,    56,     8,     7,     3,    98,    99,   100,
     101,     8,     3,     7,     3,     3,   153,     8,    71,     8,
       8,    74,   153,    95,    96,    97,   872,    39,    40,    41,
      42,    43,    44,     7,     3,     7,   872,     7,   872,     8,
     872,     7,   153,   154,   155,   156,   153,   153,     7,   872,
     872,    31,    32,    33,    34,     3,   153,   153,    38,    37,
       8,   130,   153,   132,   133,     7,   153,     6,    48,     3,
      50,     4,   124,   125,   126,   127,    56,    57,    58,    59,
      60,    61,    62,   737,   153,    31,    32,    33,    34,   758,
      36,    71,    38,    39,    74,    75,     3,     8,     3,     8,
     153,     8,    82,     8,   156,    88,    89,    90,    91,    92,
      93,   317,    58,    59,   131,    61,    62,   134,   135,   136,
       3,     3,     3,     6,     3,    71,     8,     8,    74,     8,
       3,     3,     3,     3,     3,     8,    82,     8,     8,     8,
       3,   153,     3,     3,     3,     8,     4,     8,     8,    17,
      18,    19,    20,     3,   360,     4,     6,   363,   360,    78,
      79,     4,    81,     4,   370,     3,   360,     4,     6,   363,
     360,     4,   360,   153,   380,     3,   370,   360,     6,   307,
     308,   363,   395,   363,   390,   363,   380,     4,   370,   395,
     370,     4,   370,     4,   395,    85,    86,   121,   122,     4,
     104,   105,   395,     4,     4,     4,     8,   153,   414,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,     4,     4,     8,     3,
     153,     4,     4,     8,     3,     5,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   153,     4,     4,     4,     4,
       4,     4,   154,   154,     4,   154,   154,   154,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   154,     4,
       4,     4,   156,     4,     4,     4,     4,     4,     4,   154,
     156,     4,     4,   421,   422,   423,     4,     4,     4,     4,
       4,   154,     4,   154,     4,   518,   519,   154,     4,     4,
       4,     4,   518,   519,     4,     4,     4,     4,   154,     4,
       4,     4,   156,     4,   530,   156,   532,   156,     4,     4,
     156,     4,     4,   154,     4,   154,   154,     4,     4,     4,
     156,   156,   156,     4,     4,     7,   153,   153,     7,     7,
       7,     7,     5,     5,     5,     5,     5,     5,     5,     5,
     153,   153,     7,     7,     7,     7,   494,     5,     5,     5,
     153,     5,     7,   153,     7,   153,   153,   153,   153,   153,
     153,   153,   153,   511,   153,   123,     7,   153,     7,     7,
       7,     7,   153,     7,     7,     7,     7,    83,     4,     4,
       4,     4,     4,   129,   153,     6,     3,     6,     3,     3,
       6,   153,   153,     6,   153,     3,   153,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   153,     6,     3,     6,     6,     3,     5,     4,     8,
       4,     4,     4,   154,     4,   154,   156,     4,     4,     4,
       4,     4,     3,   156,     6,   154,   154,   154,     4,     8,
       8,     4,   154,   154,     8,     3,     8,     7,     4,     4,
       4,     4,   154,     5,   154,   154,   154,   154,     7,   153,
       4,     4,   153,     4,   153,   153,     4,   317,   453,   153,
     153,   525,   512,   341,   517,   519,   719,   734,   153,   153,
     345,   737,   744,   742,   398,   751,   719,   724,   722,   733,
     872,   727,   153,   719,   153,   728,   722,   725,   731,   725,
     722,   360,   728,   153,   156,   731,   739,   728,   722,   731,
     154,   153,   722,   739,   722,   728,   742,   731,   153,   722,
     395,   731,    73,   731,   390,   739,   156,   154,   731,   731,
     770,   730,   758,   731,   154,   728,   768,   776,   773,   363,
     771,   370,   768,   740,   774,   771,   877,   758,   774,   532,
     380,   705,   414,   762,   768,   899,   916,   771,   928,   945,
     774,    -1,    -1,    -1,    -1,    -1,   768,    -1,   768,   771,
     768,   771,    -1,   771,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   872,
      -1,    -1,    -1,    -1,   877,    -1,   872,    -1,    -1,    -1,
     872,   877,    -1,    -1,    -1,    -1,    -1,    -1,   872,    -1,
      -1,    -1,   872,   877,   872,   898,    -1,    -1,    -1,   872,
     872,    -1,   898,    -1,   872,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   916,    -1,    -1,    -1,    -1,    -1,    -1,
     916
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,     0,     5,
       7,     9,   153,   154,   155,   156,   172,   173,   174,   179,
       7,   188,     7,   194,     7,   205,     7,   282,     7,   359,
       7,   373,     7,   390,     7,   311,     7,   317,     7,   341,
       7,   258,     7,   448,   180,   175,   189,   195,   206,   283,
     360,   374,   391,   312,   318,   342,   259,   449,   172,   181,
     182,   153,   177,   178,    10,   128,   137,   138,   139,   153,
     187,   190,   191,   192,   475,   477,   479,   481,    11,    14,
      15,    31,    32,    33,    34,    35,    36,    37,    38,    66,
      67,    68,    69,    70,    84,    87,    94,   102,   103,   106,
     187,   196,   197,   198,   199,   200,   201,   202,   203,   212,
     214,   238,   244,   250,   252,   266,   276,   301,   309,   335,
     413,   425,   437,   438,   446,    12,    13,   207,   208,   209,
     211,    48,    50,    56,    57,    58,    59,    60,    61,    62,
      71,    74,    75,    82,   187,   198,   199,   200,   201,   284,
     285,   286,   288,   290,   292,   294,   296,   299,   300,   335,
     353,   365,   367,   384,   409,    49,   187,   292,   294,   335,
     361,   362,   363,   365,    51,    52,    53,    54,    55,   187,
     292,   294,   335,   365,   375,   376,   377,   379,   380,   382,
     383,    70,    76,    77,    78,    79,    80,    81,   187,   335,
     392,   393,   394,   395,   397,   399,   401,   403,   405,   407,
     309,    16,    39,    41,    42,    45,    46,    47,   187,   228,
     319,   320,   321,   322,   323,   324,   325,   327,   329,   331,
     332,   334,    40,    43,    44,   187,   228,   323,   329,   343,
     344,   345,   346,   347,   349,   350,   351,   352,    85,    86,
     187,   260,   261,   262,   264,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   187,
     450,   451,   452,   453,   455,   457,   458,   460,   461,   462,
     465,   467,   468,   469,   470,   473,     6,     3,     4,     8,
       3,   193,   482,   476,   478,   480,     4,     3,     8,   204,
     213,   215,     4,     4,     4,     4,     4,   277,   310,   336,
     302,   239,   251,   245,   414,   253,   267,   426,     4,   439,
     447,     3,     8,   210,     4,     3,     8,   354,   368,   366,
     287,   289,   291,     4,     4,   297,   295,   293,   385,   410,
       3,     8,   364,     3,     8,   378,     4,   381,     4,     4,
       3,     8,   408,   396,   398,   400,   402,   404,   406,     8,
       3,     8,   326,   229,     4,   330,   328,   333,     4,     8,
       3,   348,     4,     4,     8,     3,   263,   265,     3,     8,
       4,   454,   456,     4,   459,     4,     4,   463,   466,     4,
       4,     4,   471,   474,     3,     8,   172,   172,   153,     4,
       4,     4,     4,     4,   191,     4,     4,     4,   154,   154,
     154,   154,   154,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   154,     4,     4,   197,     4,   156,
     208,     4,     4,     4,     4,     4,     4,   154,   156,     4,
       4,     4,     4,     4,   285,     4,   362,     4,   154,     4,
     154,   154,   376,     4,     4,     4,     4,     4,     4,     4,
     394,     4,     4,   154,     4,     4,     4,   156,   321,     4,
     156,   156,   345,     4,     4,   261,   156,     4,     4,   154,
       4,   154,   154,     4,     4,   156,   156,   156,     4,     4,
     451,     4,     7,     7,   172,   172,   172,     7,     7,     7,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     7,
       7,     7,     7,     5,   183,     5,     5,   174,   176,   153,
     153,   153,    63,    64,    65,   298,   183,   153,     5,     7,
     153,   153,   153,   183,   183,   183,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   172,   153,   153,
     153,   121,   122,   464,   123,   124,   125,   126,   127,   156,
     472,   153,   172,   196,   129,   483,   484,   485,   207,    16,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
     187,   216,   217,   218,   221,   223,   225,   227,   228,   230,
     231,   232,   233,   234,   236,   216,     7,   278,   279,   280,
       7,   313,   314,   315,     7,   337,   338,   339,     7,   303,
     304,   305,    78,   153,   240,   241,   242,   243,   181,    79,
      81,   242,   246,   247,   248,   249,     7,   415,   416,     7,
     254,   255,   256,    88,    89,    90,    91,    92,    93,   268,
     269,   270,   271,   272,   273,   274,   275,    16,    98,    99,
     100,   101,   187,   230,   427,   428,   429,   432,   433,   435,
     436,   104,   105,   440,   441,   442,   444,   450,   184,     7,
     355,   356,   357,     7,   369,   370,   371,     7,   386,   387,
     388,    83,   411,     8,   486,     3,     8,     8,   219,   222,
     224,   226,     4,     4,     4,     4,     4,   235,   237,     3,
       8,     8,   281,     6,     3,   316,     6,     3,   340,     6,
       3,   306,     6,     3,     3,     6,     6,     3,     6,   417,
       3,     6,   257,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   430,   434,     4,     4,     4,     3,     8,
     443,   445,     3,     8,     8,   153,   185,   186,   358,     6,
       3,   372,     6,     3,   389,     6,     3,   412,     8,     4,
     484,     4,     4,     4,     4,   154,   156,   154,   156,   154,
       4,     4,   217,   284,   280,   319,   315,   343,   339,   187,
     198,   199,   200,   201,   228,   276,   288,   290,   292,   294,
     296,   300,   307,   308,   335,   409,   305,   241,   247,    72,
      73,   187,   228,   335,   418,   419,   420,   421,   422,   424,
     416,   260,   256,   154,   154,   154,   154,   154,   154,   269,
       4,     4,   154,   154,   154,   428,     4,     4,   441,     6,
       3,   361,   357,   375,   371,   392,   388,     4,     5,    17,
      18,    19,    20,   220,   153,   153,   153,   153,   153,     8,
       8,     8,     3,     8,   423,     4,     8,     3,     8,    95,
      96,    97,   431,   153,   153,   153,   153,     8,     8,     8,
     153,     7,   487,   488,   308,     4,   156,   420,   489,     3,
       6,   153,   130,   132,   133,   187,   228,   490,   491,   492,
     493,   495,   488,   496,     4,   494,     3,     8,     4,   154,
       4,   491,     5,   153,     7,   497,   498,   499,     3,     6,
     131,   134,   135,   136,   500,   501,   502,   504,   505,   506,
     498,   503,     4,     4,     4,     3,     8,     4,   156,   154,
     154,   501,   153
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   157,   159,   158,   160,   158,   161,   158,   162,   158,
     163,   158,   164,   158,   165,   158,   166,   158,   167,   158,
     168,   158,   169,   158,   170,   158,   171,   158,   172,   172,
     172,   172,   172,   172,   172,   173,   175,   174,   176,   177,
     177,   178,   178,   180,   179,   181,   181,   182,   182,   184,
     183,   185,   185,   186,   186,   187,   189,   188,   190,   190,
     191,   191,   191,   191,   191,   191,   193,   192,   195,   194,
     196,   196,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   198,   199,   200,   201,   202,
     204,   203,   206,   205,   207,   207,   208,   208,   210,   209,
     211,   213,   212,   215,   214,   216,   216,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     219,   218,   220,   220,   220,   220,   222,   221,   224,   223,
     226,   225,   227,   229,   228,   230,   231,   232,   233,   235,
     234,   237,   236,   239,   238,   240,   240,   241,   241,   242,
     243,   245,   244,   246,   246,   247,   247,   247,   248,   249,
     251,   250,   253,   252,   254,   254,   255,   255,   257,   256,
     259,   258,   260,   260,   260,   261,   261,   263,   262,   265,
     264,   267,   266,   268,   268,   269,   269,   269,   269,   269,
     269,   270,   271,   272,   273,   274,   275,   277,   276,   278,
     278,   279,   279,   281,   280,   283,   282,   284,   284,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   287,   286,
     289,   288,   291,   290,   293,   292,   295,   294,   297,   296,
     298,   298,   298,   299,   300,   302,   301,   303,   303,   304,
     304,   306,   305,   307,   307,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     310,   309,   312,   311,   313,   313,   314,   314,   316,   315,
     318,   317,   319,   319,   320,   320,   321,   321,   321,   321,
     321,   321,   321,   321,   322,   323,   324,   326,   325,   328,
     327,   330,   329,   331,   333,   332,   334,   336,   335,   337,
     337,   338,   338,   340,   339,   342,   341,   343,   343,   344,
     344,   345,   345,   345,   345,   345,   345,   345,   346,   348,
     347,   349,   350,   351,   352,   354,   353,   355,   355,   356,
     356,   358,   357,   360,   359,   361,   361,   362,   362,   362,
     362,   362,   362,   364,   363,   366,   365,   368,   367,   369,
     369,   370,   370,   372,   371,   374,   373,   375,   375,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   378,
     377,   379,   381,   380,   382,   383,   385,   384,   386,   386,
     387,   387,   389,   388,   391,   390,   392,   392,   393,   393,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   396,
     395,   398,   397,   400,   399,   402,   401,   404,   403,   406,
     405,   408,   407,   410,   409,   412,   411,   414,   413,   415,
     415,   417,   416,   418,   418,   419,   419,   420,   420,   420,
     420,   420,   421,   423,   422,   424,   426,   425,   427,   427,
     428,   428,   428,   428,   428,   428,   428,   430,   429,   431,
     431,   431,   432,   434,   433,   435,   436,   437,   439,   438,
     440,   440,   441,   441,   443,   442,   445,   444,   447,   446,
     449,   448,   450,   450,   451,   451,   451,   451,   451,   451,
     451,   451,   451,   451,   451,   451,   451,   451,   451,   452,
     454,   453,   456,   455,   457,   459,   458,   460,   461,   463,
     462,   464,   464,   466,   465,   467,   468,   469,   471,   470,
     472,   472,   472,   472,   472,   474,   473,   476,   475,   478,
     477,   480,   479,   482,   481,   483,   483,   484,   486,   485,
     487,   487,   489,   488,   490,   490,   491,   491,   491,   491,
     491,   492,   494,   493,   496,   495,   497,   497,   499,   498,
     500,   500,   501,   501,   501,   501,   503,   502,   504,   505,
     506
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     6,     1,     3,
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
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "value",
  "sub_json", "map2", "$@14", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@15", "list_content", "not_empty_list", "list_strings",
  "$@16", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@17", "global_objects",
  "global_object", "dhcp6_object", "$@18", "sub_dhcp6", "$@19",
  "global_params", "global_param", "preferred_lifetime", "valid_lifetime",
  "renew_timer", "rebind_timer", "decline_probation_period",
  "interfaces_config", "$@20", "sub_interfaces6", "$@21",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@22", "re_detect", "lease_database", "$@23", "hosts_database", "$@24",
  "database_map_params", "database_map_param", "database_type", "$@25",
  "db_type", "user", "$@26", "password", "$@27", "host", "$@28", "port",
  "name", "$@29", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@30", "keyspace", "$@31", "mac_sources", "$@32",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@33",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@34",
  "hooks_libraries", "$@35", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@36",
  "sub_hooks_library", "$@37", "hooks_params", "hooks_param", "library",
  "$@38", "parameters", "$@39", "expired_leases_processing", "$@40",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@41",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@42",
  "sub_subnet6", "$@43", "subnet6_params", "subnet6_param", "subnet",
  "$@44", "interface", "$@45", "interface_id", "$@46", "client_class",
  "$@47", "require_client_classes", "$@48", "reservation_mode", "$@49",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@50",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@51", "shared_network_params", "shared_network_param",
  "option_def_list", "$@52", "sub_option_def_list", "$@53",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@54", "sub_option_def", "$@55",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@56",
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
  "$@68", "pd_pools_list", "$@69", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@70", "sub_pd_pool",
  "$@71", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@72",
  "pd_prefix_len", "excluded_prefix", "$@73", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@74", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@75", "sub_reservation",
  "$@76", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@77", "prefixes", "$@78", "duid",
  "$@79", "hw_address", "$@80", "hostname", "$@81", "flex_id_value",
  "$@82", "reservation_client_classes", "$@83", "relay", "$@84",
  "relay_map", "$@85", "client_classes", "$@86", "client_classes_list",
  "client_class_entry", "$@87", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@88", "only_if_required",
  "server_id", "$@89", "server_id_params", "server_id_param",
  "server_id_type", "$@90", "duid_type", "htype", "identifier", "$@91",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@92",
  "control_socket_params", "control_socket_param", "socket_type", "$@93",
  "socket_name", "$@94", "dhcp_ddns", "$@95", "sub_dhcp_ddns", "$@96",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@97", "server_ip", "$@98", "server_port",
  "sender_ip", "$@99", "sender_port", "max_queue_size", "ncr_protocol",
  "$@100", "ncr_protocol_value", "ncr_format", "$@101",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@102", "replace_client_name_value",
  "generated_prefix", "$@103", "dhcp4_json_object", "$@104",
  "dhcpddns_json_object", "$@105", "control_agent_json_object", "$@106",
  "logging_object", "$@107", "logging_params", "logging_param", "loggers",
  "$@108", "loggers_entries", "logger_entry", "$@109", "logger_params",
  "logger_param", "debuglevel", "severity", "$@110", "output_options_list",
  "$@111", "output_options_list_content", "output_entry", "$@112",
  "output_params_list", "output_params", "output", "$@113", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   238,   238,   238,   239,   239,   240,   240,   241,   241,
     242,   242,   243,   243,   244,   244,   245,   245,   246,   246,
     247,   247,   248,   248,   249,   249,   250,   250,   258,   259,
     260,   261,   262,   263,   264,   267,   272,   272,   283,   286,
     287,   290,   294,   301,   301,   308,   309,   312,   316,   323,
     323,   330,   331,   334,   338,   349,   359,   359,   374,   375,
     379,   380,   381,   382,   383,   384,   387,   387,   402,   402,
     411,   412,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   442,   447,   452,   457,   462,
     467,   467,   478,   478,   487,   488,   491,   492,   495,   495,
     505,   511,   511,   523,   523,   535,   536,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     554,   554,   561,   562,   563,   564,   567,   567,   575,   575,
     583,   583,   591,   596,   596,   604,   609,   614,   619,   624,
     624,   632,   632,   641,   641,   651,   652,   655,   656,   659,
     664,   669,   669,   679,   680,   683,   684,   685,   688,   693,
     700,   700,   710,   710,   720,   721,   724,   725,   728,   728,
     738,   738,   748,   749,   750,   753,   754,   757,   757,   765,
     765,   773,   773,   784,   785,   788,   789,   790,   791,   792,
     793,   796,   801,   806,   811,   816,   821,   829,   829,   842,
     843,   846,   847,   854,   854,   880,   880,   891,   892,   896,
     897,   898,   899,   900,   901,   902,   903,   904,   905,   906,
     907,   908,   909,   910,   911,   912,   913,   914,   917,   917,
     925,   925,   933,   933,   941,   941,   949,   949,   959,   959,
     966,   967,   968,   971,   976,   984,   984,   995,   996,  1000,
    1001,  1004,  1004,  1012,  1013,  1016,  1017,  1018,  1019,  1020,
    1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,
    1037,  1037,  1050,  1050,  1059,  1060,  1063,  1064,  1069,  1069,
    1084,  1084,  1098,  1099,  1102,  1103,  1106,  1107,  1108,  1109,
    1110,  1111,  1112,  1113,  1116,  1118,  1123,  1125,  1125,  1133,
    1133,  1141,  1141,  1149,  1151,  1151,  1159,  1168,  1168,  1180,
    1181,  1186,  1187,  1192,  1192,  1204,  1204,  1216,  1217,  1222,
    1223,  1228,  1229,  1230,  1231,  1232,  1233,  1234,  1237,  1239,
    1239,  1247,  1249,  1251,  1256,  1264,  1264,  1276,  1277,  1280,
    1281,  1284,  1284,  1294,  1294,  1303,  1304,  1307,  1308,  1309,
    1310,  1311,  1312,  1315,  1315,  1323,  1323,  1333,  1333,  1345,
    1346,  1349,  1350,  1353,  1353,  1365,  1365,  1377,  1378,  1381,
    1382,  1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1393,
    1393,  1401,  1406,  1406,  1414,  1419,  1427,  1427,  1437,  1438,
    1441,  1442,  1445,  1445,  1454,  1454,  1463,  1464,  1467,  1468,
    1472,  1473,  1474,  1475,  1476,  1477,  1478,  1479,  1480,  1483,
    1483,  1493,  1493,  1503,  1503,  1511,  1511,  1519,  1519,  1527,
    1527,  1535,  1535,  1548,  1548,  1558,  1558,  1569,  1569,  1579,
    1580,  1583,  1583,  1593,  1594,  1597,  1598,  1601,  1602,  1603,
    1604,  1605,  1608,  1610,  1610,  1618,  1626,  1626,  1638,  1639,
    1642,  1643,  1644,  1645,  1646,  1647,  1648,  1651,  1651,  1658,
    1659,  1660,  1663,  1668,  1668,  1676,  1681,  1688,  1695,  1695,
    1705,  1706,  1709,  1710,  1713,  1713,  1721,  1721,  1731,  1731,
    1743,  1743,  1753,  1754,  1757,  1758,  1759,  1760,  1761,  1762,
    1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,  1771,  1774,
    1779,  1779,  1787,  1787,  1795,  1800,  1800,  1808,  1813,  1818,
    1818,  1826,  1827,  1830,  1830,  1838,  1843,  1848,  1853,  1853,
    1861,  1864,  1867,  1870,  1873,  1879,  1879,  1889,  1889,  1896,
    1896,  1903,  1903,  1916,  1916,  1929,  1930,  1934,  1938,  1938,
    1950,  1951,  1955,  1955,  1963,  1964,  1967,  1968,  1969,  1970,
    1971,  1974,  1979,  1979,  1987,  1987,  1997,  1998,  2001,  2001,
    2009,  2010,  2013,  2014,  2015,  2016,  2019,  2019,  2027,  2032,
    2037
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
#line 4511 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2042 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
