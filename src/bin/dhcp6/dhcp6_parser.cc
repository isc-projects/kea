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
      case 158: // value
      case 162: // map_value
      case 203: // db_type
      case 273: // hr_mode
      case 391: // duid_type
      case 424: // ncr_protocol_value
      case 433: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 143: // "boolean"
        value.move< bool > (that.value);
        break;

      case 142: // "floating point"
        value.move< double > (that.value);
        break;

      case 141: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 140: // "constant string"
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
      case 158: // value
      case 162: // map_value
      case 203: // db_type
      case 273: // hr_mode
      case 391: // duid_type
      case 424: // ncr_protocol_value
      case 433: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 143: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 142: // "floating point"
        value.copy< double > (that.value);
        break;

      case 141: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 140: // "constant string"
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
            case 140: // "constant string"

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 141: // "integer"

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 142: // "floating point"

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 143: // "boolean"

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 158: // value

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 162: // map_value

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 203: // db_type

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 273: // hr_mode

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 391: // duid_type

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 424: // ncr_protocol_value

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 433: // replace_client_name_value

#line 216 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 158: // value
      case 162: // map_value
      case 203: // db_type
      case 273: // hr_mode
      case 391: // duid_type
      case 424: // ncr_protocol_value
      case 433: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 143: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 142: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 141: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 140: // "constant string"
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
#line 225 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 226 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 227 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 228 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 229 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 230 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 231 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 818 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 280 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 298 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 302 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 320 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 324 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 335 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 369 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 376 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 390 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 444 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 454 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 459 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 520 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 521 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1166 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 523 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1172 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 528 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1347 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1378 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 646 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1397 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 667 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1415 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 692 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1449 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1458 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1469 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1487 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1496 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1505 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 737 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 747 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 755 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1562 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 838 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 846 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1639 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1675 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1683 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 875 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 876 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 877 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 880 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 885 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1739 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1766 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1784 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 964 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1801 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1031 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1977 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1123 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1187 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1224 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1248 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2234 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2263 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1358 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2386 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2451 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2459 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1448 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2474 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2522 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2560 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1510 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2607 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2616 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2634 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2643 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2747 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1619 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-client-update",  b);
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1658 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2832 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2873 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 2984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1780 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3062 "dhcp6_parser.cc" // lalr1.cc:859
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
     105,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,    54,    19,   145,   169,   220,   251,   262,
     265,   267,   269,   270,   272,   273,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
      19,    34,    17,    31,   237,    23,    64,    37,    63,    32,
      65,   -21,    90,  -490,   275,   283,   284,   279,   291,  -490,
    -490,  -490,  -490,   293,  -490,    40,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   294,   295,   297,   298,   299,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   302,
    -490,  -490,  -490,   114,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   287,  -490,  -490,
    -490,  -490,  -490,  -490,   306,   307,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   137,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   147,  -490,  -490,  -490,  -490,   308,  -490,
     309,   310,  -490,  -490,  -490,   148,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     311,   312,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   313,  -490,  -490,  -490,   314,  -490,  -490,   315,   317,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   318,  -490,  -490,  -490,  -490,   319,   322,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   150,  -490,  -490,
    -490,   324,  -490,  -490,   325,  -490,   326,   327,  -490,  -490,
     328,   329,   330,   331,  -490,  -490,  -490,   161,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    19,    19,  -490,   176,   332,
     333,   334,   335,  -490,    17,  -490,   336,   337,   338,   180,
     185,   202,   208,   209,   340,   341,   342,   343,   344,   347,
     348,   349,   350,   351,   216,   352,   354,    31,  -490,   355,
    -490,    47,   356,   357,   358,   359,   360,   224,   223,   363,
     364,   365,   366,    23,  -490,   367,   368,    64,  -490,   369,
     233,   371,   235,   236,    37,  -490,   374,   375,   376,   377,
     378,   379,  -490,    63,   380,   381,   246,   382,   384,   385,
     247,  -490,    32,   387,   249,  -490,    65,   389,   390,   -44,
    -490,   252,   392,   393,   257,   395,   261,   263,   399,   401,
     264,   266,   268,   271,   402,   404,    90,  -490,  -490,  -490,
     406,   405,   408,    19,    19,  -490,   409,   410,   411,  -490,
    -490,  -490,  -490,  -490,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   425,  -490,   426,   429,  -490,   423,  -490,
    -490,  -490,  -490,   430,   424,  -490,  -490,  -490,   432,   434,
     300,   304,   305,  -490,  -490,   126,   316,   437,   439,  -490,
     320,   440,  -490,   321,  -490,   323,  -490,  -490,  -490,   423,
     423,   423,   339,   345,   346,  -490,   361,   362,  -490,   370,
     372,   373,  -490,  -490,   383,  -490,  -490,   386,    19,  -490,
    -490,   388,   391,  -490,   394,  -490,  -490,     0,   353,  -490,
    -490,  -490,  -490,    30,   396,  -490,    19,    31,   292,  -490,
    -490,   237,    14,    14,   442,   443,   444,   -29,    19,    59,
      39,   446,    99,    76,   172,    90,  -490,  -490,   450,  -490,
      47,   448,   451,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,   452,   397,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,   167,  -490,   203,
    -490,  -490,   449,  -490,  -490,  -490,  -490,   460,   461,   462,
     463,  -490,   204,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   205,  -490,   464,   466,  -490,  -490,   467,
     469,  -490,  -490,   468,   473,  -490,  -490,  -490,   104,  -490,
    -490,  -490,   471,  -490,  -490,   120,  -490,  -490,  -490,   135,
    -490,   472,   477,  -490,   478,   479,   480,   483,   484,   485,
     206,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     486,   487,   488,  -490,  -490,   207,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   214,  -490,  -490,  -490,   215,   398,
     400,  -490,  -490,   475,   491,  -490,  -490,   489,   493,  -490,
    -490,   492,   494,  -490,  -490,   495,  -490,   496,   292,  -490,
    -490,   500,   501,   502,   503,   403,   407,   412,   413,    14,
    -490,  -490,    23,  -490,   442,    32,  -490,   443,    65,  -490,
     444,   -29,  -490,  -490,    59,  -490,    39,  -490,   -21,  -490,
     446,   427,   428,   431,   433,   435,   436,    99,  -490,   504,
     505,   438,   441,   445,    76,  -490,   507,   510,   172,  -490,
    -490,  -490,   509,   513,  -490,    64,  -490,   448,    37,  -490,
     451,    63,  -490,   452,   514,  -490,   512,  -490,   238,   447,
     453,   454,  -490,  -490,  -490,  -490,  -490,   218,  -490,   511,
    -490,   516,  -490,  -490,  -490,  -490,   221,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,   174,   455,  -490,  -490,  -490,
    -490,   456,   457,  -490,  -490,   458,   242,  -490,   243,  -490,
     517,  -490,   459,   515,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   136,
    -490,    -4,   515,  -490,  -490,   523,  -490,  -490,  -490,   244,
    -490,  -490,  -490,  -490,  -490,   525,   465,   526,    -4,  -490,
     527,  -490,   470,  -490,   528,  -490,  -490,   225,  -490,   481,
     528,  -490,  -490,   245,  -490,  -490,   529,   481,  -490,   474,
    -490,  -490
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   196,    11,   301,    13,   321,    15,
     348,    17,   240,    19,   275,    21,   161,    23,   429,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   350,   242,
     277,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     482,   478,   480,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   102,   104,     0,     0,     0,     0,     0,   188,
     232,   267,   136,   151,   144,   378,   153,   172,   395,     0,
     417,   427,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   100,     0,   382,   293,
     313,   217,   219,   221,     0,     0,   225,   223,   340,   374,
     216,   200,   201,   202,   203,     0,   198,   207,   208,   209,
     212,   214,   210,   211,   204,   205,   206,   213,   215,   309,
     311,   308,   306,     0,   303,   305,   307,   333,     0,   336,
       0,     0,   332,   328,   331,     0,   323,   325,   326,   329,
     330,   327,   372,   362,   364,   366,   368,   370,   361,   360,
       0,   351,   352,   356,   357,   354,   358,   359,   355,   257,
     130,     0,   261,   259,   264,     0,   253,   254,     0,   243,
     244,   246,   256,   247,   248,   249,   263,   250,   251,   252,
     288,     0,   286,   287,   290,   291,     0,   278,   279,   281,
     282,   283,   284,   285,   168,   170,   165,     0,   163,   166,
     167,     0,   450,   452,     0,   455,     0,     0,   459,   463,
       0,     0,     0,     0,   469,   476,   448,     0,   431,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,    42,     0,     0,    35,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      99,   384,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   197,     0,     0,     0,   302,     0,
       0,     0,     0,     0,     0,   322,     0,     0,     0,     0,
       0,     0,   349,     0,     0,     0,     0,     0,     0,     0,
       0,   241,     0,     0,     0,   276,     0,     0,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   430,    46,    39,
       0,     0,     0,     0,     0,    57,     0,     0,     0,    91,
      92,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   416,     0,     0,    68,     0,   393,
     391,   392,   390,     0,   385,   386,   388,   389,     0,     0,
       0,     0,     0,   230,   231,     0,     0,     0,     0,   199,
       0,     0,   304,     0,   335,     0,   338,   339,   324,     0,
       0,     0,     0,     0,     0,   353,     0,     0,   255,     0,
       0,     0,   266,   245,     0,   292,   280,     0,     0,   164,
     449,     0,     0,   454,     0,   457,   458,     0,     0,   465,
     466,   467,   468,     0,     0,   432,     0,     0,     0,   479,
     481,     0,     0,     0,   190,   234,   269,     0,    43,     0,
       0,   155,     0,     0,     0,     0,    47,   101,     0,   383,
       0,   295,   315,   218,   220,   222,   227,   228,   229,   226,
     224,   342,     0,   310,    36,   312,   334,   337,   373,   363,
     365,   367,   369,   371,   258,   131,   262,   260,   265,   289,
     169,   171,   451,   453,   456,   461,   462,   460,   464,   471,
     472,   473,   474,   475,   470,   477,    40,     0,   487,     0,
     484,   486,     0,   118,   124,   126,   128,     0,     0,     0,
       0,   117,     0,   106,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,   194,     0,   191,   192,   238,     0,
     235,   236,   273,     0,   270,   271,   142,   143,     0,   138,
     140,   141,     0,   150,   148,     0,   146,   149,   380,     0,
     159,     0,   156,   157,     0,     0,     0,     0,     0,     0,
       0,   174,   176,   177,   178,   179,   180,   181,   406,   412,
       0,     0,     0,   405,   404,     0,   397,   399,   402,   400,
     401,   403,   423,   425,     0,   419,   421,   422,     0,    49,
       0,   387,   299,     0,   296,   297,   319,     0,   316,   317,
     346,     0,   343,   344,   376,     0,    64,     0,     0,   483,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     103,   105,     0,   189,     0,   242,   233,     0,   277,   268,
       0,     0,   137,   152,     0,   145,     0,   379,     0,   154,
       0,     0,     0,     0,     0,     0,     0,     0,   173,     0,
       0,     0,     0,     0,     0,   396,     0,     0,     0,   418,
     428,    51,     0,    50,   394,     0,   294,     0,     0,   314,
       0,   350,   341,     0,     0,   375,     0,   485,     0,     0,
       0,     0,   132,   133,   134,   135,   107,     0,   193,     0,
     237,     0,   272,   139,   147,   381,     0,   158,   182,   183,
     184,   185,   186,   187,   175,     0,     0,   411,   414,   415,
     398,     0,     0,   420,    48,     0,     0,   298,     0,   318,
       0,   345,     0,     0,   120,   121,   122,   123,   119,   125,
     127,   129,   195,   239,   274,   160,   408,   409,   410,   407,
     413,   424,   426,    52,   300,   320,   347,   377,   491,     0,
     489,     0,     0,   488,   503,     0,   501,   499,   495,     0,
     493,   497,   498,   496,   490,     0,     0,     0,     0,   492,
       0,   500,     0,   494,     0,   502,   507,     0,   505,     0,
       0,   504,   511,     0,   509,   506,     0,     0,   508,     0,
     510,   512
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,     7,  -490,    58,  -490,  -490,  -490,
    -490,  -490,  -490,    22,  -490,  -185,  -490,  -490,  -490,   -62,
    -490,  -490,  -490,   227,  -490,  -490,  -490,  -490,    50,   222,
     -63,   -50,   -49,   -43,  -490,  -490,  -490,  -490,  -490,    51,
    -490,  -490,  -490,  -490,  -490,    48,  -136,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   -58,  -490,  -489,  -490,
    -490,  -490,  -490,  -490,  -490,  -147,  -474,  -490,  -490,  -490,
    -490,  -149,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -153,
    -490,  -490,  -490,  -148,   182,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -158,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -132,  -490,  -490,  -490,  -129,   226,  -490,
    -490,  -490,  -490,  -490,  -490,  -477,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -131,  -490,  -490,  -490,
    -128,  -490,   196,  -490,   -59,  -490,  -490,  -490,  -490,  -490,
     -57,  -490,  -490,  -490,  -490,  -490,   -48,  -490,  -490,  -490,
    -130,  -490,  -490,  -490,  -127,  -490,   197,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -165,  -490,  -490,
    -490,  -161,   228,  -490,  -490,   -66,  -490,  -490,  -490,  -490,
    -490,  -164,  -490,  -490,  -490,  -157,   229,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -166,  -490,
    -490,  -490,  -156,  -490,   217,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,    68,  -490,  -490,
    -490,  -490,  -490,  -490,  -134,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -137,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,    78,   198,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   -83,
    -490,  -490,  -490,  -224,  -490,  -490,  -239,  -490,  -490,  -490,
    -490,  -490,  -490,  -250,  -490,  -490,  -256,  -490
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   525,    77,
      78,    37,    60,    74,    75,   507,   649,   722,   723,   112,
      39,    62,    85,    86,    87,   289,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   296,    43,    64,   137,
     319,   121,   297,   122,   298,   572,   573,   574,   671,   788,
     575,   672,   576,   673,   577,   674,   217,   355,   579,   580,
     581,   582,   123,   307,   598,   599,   600,   601,   124,   309,
     605,   606,   607,   125,   308,   126,   311,   611,   612,   613,
     698,    57,    71,   247,   248,   249,   367,   250,   368,   127,
     312,   620,   621,   622,   623,   624,   625,   626,   627,   128,
     304,   585,   586,   587,   682,    45,    65,   155,   156,   157,
     324,   158,   325,   159,   326,   160,   330,   161,   329,   519,
     162,   163,   129,   305,   589,   590,   591,   685,    53,    69,
     218,   219,   220,   221,   222,   223,   224,   354,   225,   358,
     226,   357,   227,   228,   359,   229,   130,   306,   593,   594,
     595,   688,    55,    70,   236,   237,   238,   239,   240,   363,
     241,   242,   243,   165,   322,   653,   654,   655,   725,    47,
      66,   173,   174,   175,   335,   176,   336,   166,   323,   657,
     658,   659,   728,    49,    67,   185,   186,   187,   339,   188,
     189,   341,   190,   191,   167,   331,   661,   662,   663,   731,
      51,    68,   200,   201,   202,   203,   347,   204,   348,   205,
     349,   206,   350,   207,   351,   208,   346,   168,   332,   665,
     734,   131,   310,   609,   321,   423,   424,   425,   426,   427,
     508,   132,   313,   635,   636,   637,   709,   799,   638,   639,
     710,   640,   641,   133,   134,   315,   644,   645,   646,   716,
     647,   717,   135,   316,    59,    72,   267,   268,   269,   270,
     372,   271,   373,   272,   273,   375,   274,   275,   276,   378,
     547,   277,   379,   278,   279,   280,   281,   282,   384,   554,
     283,   385,    88,   291,    89,   292,    90,   290,   559,   560,
     561,   667,   809,   810,   811,   819,   820,   821,   822,   827,
     823,   825,   837,   838,   839,   843,   844,   846
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   184,   151,   150,   171,   182,   198,   216,   232,   246,
     266,   234,   233,   235,   634,   152,   153,   164,   172,   183,
     199,    34,   154,   608,    27,   604,    28,    79,    29,   563,
     138,   210,   244,   245,   564,   565,   566,   567,   568,   569,
     570,   596,    91,   294,    92,    93,   138,   209,   295,   210,
      94,    95,    96,    97,    26,   244,   245,   101,    94,    95,
      96,    97,    98,    99,   100,   101,   139,   210,   140,   211,
     212,   101,   213,   214,   215,   141,   142,   143,   144,   145,
     146,   101,   210,   177,   178,   179,   180,   181,   170,   147,
     148,   628,   102,   103,   104,   105,   149,   101,   101,   567,
     210,   230,   211,   212,   231,   147,   106,   691,   169,   107,
     692,   597,   419,   545,   546,   170,   108,   317,   814,    83,
     815,   816,   318,   694,   109,   110,   695,   192,   111,   596,
     603,   193,   194,   195,   196,   197,    83,    80,   696,   812,
     333,   697,   813,    81,    82,   334,   549,   550,   551,   552,
     337,   344,    38,   369,    83,   338,   345,    83,   370,    30,
      31,    32,    33,    83,   386,   629,   630,   631,   632,   387,
     317,    83,    83,   553,    76,   666,    40,    83,   614,   615,
     616,   617,   618,   619,   516,   517,   518,    83,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,    83,    83,    83,   668,   679,   679,   707,
     714,   669,   680,   681,   708,   715,    83,   718,   386,   755,
     604,   333,   719,   720,   369,   634,   792,    42,   840,   795,
      83,   841,    84,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,   337,   344,   828,   847,   136,
     804,   805,   829,   848,   784,   785,   786,   787,    44,   420,
     796,   797,   798,   421,   528,   529,   530,   642,   643,    46,
     151,   150,    48,   422,    50,   171,    52,    54,   184,    56,
      58,   284,   182,   152,   153,   164,   285,   287,   286,   172,
     154,   198,   388,   389,   288,   320,   183,   293,   299,   300,
     216,   301,   302,   303,   232,   199,   314,   234,   233,   235,
     327,   328,   340,   342,   343,   353,   390,   356,   360,   352,
     362,   399,   364,   361,   266,   366,   400,   365,   371,   374,
     376,   377,   380,   381,   382,   383,   391,   392,   393,   394,
     396,   397,   398,   401,   404,   405,   406,   407,   408,   402,
     403,   409,   410,   411,   412,   413,   415,   414,   416,   418,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   440,   441,   443,   444,   445,   446,   447,   449,   450,
     451,   452,   453,   454,   456,   457,   459,   458,   460,   461,
     462,   464,   465,   467,   468,   470,   471,   472,   473,   474,
     489,   490,   475,   477,   476,   478,   483,   479,   484,   480,
     486,   481,   487,   558,   482,   488,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   510,   506,   502,
     571,   571,   503,   504,   578,   578,   505,   511,   509,   512,
     513,   633,   521,   266,   514,   515,   522,    28,   420,   584,
     588,   592,   421,   610,   650,   652,   520,   670,   656,   660,
     523,   526,   422,   527,   675,   676,   677,   678,   548,   684,
     683,   664,   687,   686,   689,   541,   690,   693,   699,   531,
     700,   726,   701,   702,   703,   532,   533,   704,   705,   706,
     711,   712,   713,   556,   727,   729,   730,   733,   732,   524,
     736,   534,   535,   735,   738,   739,   740,   741,   765,   766,
     536,   771,   537,   538,   772,   774,   775,   783,   782,   793,
     602,   395,   808,   539,   794,   806,   540,   826,   542,   830,
     832,   543,   834,   849,   544,   836,   555,   557,   721,   417,
     724,   583,   562,   746,   753,   754,   742,   757,   743,   764,
     756,   469,   748,   747,   745,   744,   750,   749,   463,   439,
     752,   751,   777,   466,   776,   442,   779,   781,   758,   759,
     455,   778,   760,   448,   761,   780,   762,   763,   651,   767,
     770,   773,   768,   648,   485,   737,   769,   789,   824,   833,
     845,   850,     0,   790,   791,   800,   801,   802,   803,   807,
       0,     0,     0,     0,   842,     0,   831,     0,     0,     0,
     835,     0,     0,     0,   851,     0,     0,   571,     0,   151,
     150,   578,     0,   216,     0,     0,   232,     0,     0,   234,
     233,   235,   152,   153,   164,     0,   246,     0,     0,   154,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   633,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   184,   171,     0,     0,   182,     0,     0,   198,
       0,     0,     0,     0,     0,     0,     0,   172,     0,     0,
     183,     0,     0,   199,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   817,
       0,     0,     0,   818,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   817,     0,     0,     0,
     818
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   503,    65,    65,    65,    66,    67,
      68,    14,    65,   500,     5,   499,     7,    10,     9,    15,
       7,    35,    76,    77,    20,    21,    22,    23,    24,    25,
      26,    70,    11,     3,    13,    14,     7,    15,     8,    35,
      27,    28,    29,    30,     0,    76,    77,    34,    27,    28,
      29,    30,    31,    32,    33,    34,    43,    35,    45,    37,
      38,    34,    40,    41,    42,    52,    53,    54,    55,    56,
      57,    34,    35,    46,    47,    48,    49,    50,    51,    66,
      67,    15,    61,    62,    63,    64,    73,    34,    34,    23,
      35,    36,    37,    38,    39,    66,    75,     3,    44,    78,
       6,   140,    65,   113,   114,    51,    85,     3,   122,   140,
     124,   125,     8,     3,    93,    94,     6,    64,    97,    70,
      71,    68,    69,    70,    71,    72,   140,   120,     3,     3,
       3,     6,     6,   126,   127,     8,   116,   117,   118,   119,
       3,     3,     7,     3,   140,     8,     8,   140,     8,   140,
     141,   142,   143,   140,     3,    89,    90,    91,    92,     8,
       3,   140,   140,   143,   140,     8,     7,   140,    79,    80,
      81,    82,    83,    84,    58,    59,    60,   140,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   140,   140,   140,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,   140,     3,     3,   696,
     694,     3,     8,     8,     3,   714,     8,     7,     3,     8,
     140,     6,   294,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,     3,     3,     3,     3,    12,
       8,     8,     8,     8,    16,    17,    18,    19,     7,   321,
      86,    87,    88,   321,   449,   450,   451,    95,    96,     7,
     333,   333,     7,   321,     7,   337,     7,     7,   344,     7,
       7,     6,   344,   333,   333,   333,     3,     8,     4,   337,
     333,   353,   285,   286,     3,     8,   344,     4,     4,     4,
     362,     4,     4,     4,   366,   353,     4,   366,   366,   366,
       4,     4,     4,     4,     4,     3,   140,     4,     4,     8,
       3,   141,     4,     8,   386,     3,   141,     8,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   141,     4,     4,     4,     4,     4,   141,
     141,     4,     4,     4,     4,     4,     4,   141,     4,     4,
       4,     4,     4,     4,     4,   141,   143,     4,     4,     4,
       4,     4,     4,     4,   141,     4,   141,   141,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   141,     4,     4,
     143,     4,   143,     4,     4,   143,     4,     4,   141,     4,
     393,   394,   141,     4,   141,     4,     4,   143,     4,   143,
       4,   143,     7,   121,   143,     7,     7,     7,     7,     5,
       5,     5,     5,     5,     5,     5,     5,     3,     5,     7,
     492,   493,     7,     7,   492,   493,     7,     5,     8,     5,
     140,   503,     5,   505,   140,   140,     7,     7,   510,     7,
       7,     7,   510,     7,     4,     7,   140,     8,     7,     7,
     140,   140,   510,   140,     4,     4,     4,     4,   115,     3,
       6,    74,     3,     6,     6,   468,     3,     6,     6,   140,
       3,     6,     4,     4,     4,   140,   140,     4,     4,     4,
       4,     4,     4,   486,     3,     6,     3,     3,     6,   441,
       4,   140,   140,     8,     4,     4,     4,     4,     4,     4,
     140,     4,   140,   140,     4,     6,     3,     5,     4,     8,
     498,   294,     7,   140,     8,     8,   140,     4,   140,     4,
       4,   140,     5,     4,   140,     7,   140,   487,   140,   317,
     140,   493,   491,   679,   691,   694,   143,   700,   141,   707,
     698,   369,   684,   682,   141,   143,   687,   685,   362,   333,
     690,   688,   727,   366,   725,   337,   730,   733,   141,   141,
     353,   728,   141,   344,   141,   731,   141,   141,   510,   141,
     714,   718,   141,   505,   386,   668,   141,   140,   812,   828,
     840,   847,    -1,   140,   140,   140,   140,   140,   140,   140,
      -1,    -1,    -1,    -1,   123,    -1,   141,    -1,    -1,    -1,
     140,    -1,    -1,    -1,   140,    -1,    -1,   679,    -1,   682,
     682,   679,    -1,   685,    -1,    -1,   688,    -1,    -1,   688,
     688,   688,   682,   682,   682,    -1,   698,    -1,    -1,   682,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   714,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   728,   725,    -1,    -1,   728,    -1,    -1,   731,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   725,    -1,    -1,
     728,    -1,    -1,   731,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   811,
      -1,    -1,    -1,   811,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   828,    -1,    -1,    -1,
     828
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     5,     7,     9,
     140,   141,   142,   143,   158,   159,   160,   165,     7,   174,
       7,   180,     7,   191,     7,   259,     7,   323,     7,   337,
       7,   354,     7,   282,     7,   306,     7,   235,     7,   408,
     166,   161,   175,   181,   192,   260,   324,   338,   355,   283,
     307,   236,   409,   158,   167,   168,   140,   163,   164,    10,
     120,   126,   127,   140,   173,   176,   177,   178,   436,   438,
     440,    11,    13,    14,    27,    28,    29,    30,    31,    32,
      33,    34,    61,    62,    63,    64,    75,    78,    85,    93,
      94,    97,   173,   182,   183,   184,   185,   186,   187,   188,
     189,   195,   197,   216,   222,   227,   229,   243,   253,   276,
     300,   375,   385,   397,   398,   406,    12,   193,     7,    43,
      45,    52,    53,    54,    55,    56,    57,    66,    67,    73,
     173,   184,   185,   186,   187,   261,   262,   263,   265,   267,
     269,   271,   274,   275,   300,   317,   331,   348,   371,    44,
      51,   173,   300,   325,   326,   327,   329,    46,    47,    48,
      49,    50,   173,   300,   329,   339,   340,   341,   343,   344,
     346,   347,    64,    68,    69,    70,    71,    72,   173,   300,
     356,   357,   358,   359,   361,   363,   365,   367,   369,    15,
      35,    37,    38,    40,    41,    42,   173,   210,   284,   285,
     286,   287,   288,   289,   290,   292,   294,   296,   297,   299,
      36,    39,   173,   210,   288,   294,   308,   309,   310,   311,
     312,   314,   315,   316,    76,    77,   173,   237,   238,   239,
     241,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   173,   410,   411,   412,
     413,   415,   417,   418,   420,   421,   422,   425,   427,   428,
     429,   430,   431,   434,     6,     3,     4,     8,     3,   179,
     441,   437,   439,     4,     3,     8,   190,   196,   198,     4,
       4,     4,     4,     4,   254,   277,   301,   217,   228,   223,
     376,   230,   244,   386,     4,   399,   407,     3,     8,   194,
       8,   378,   318,   332,   264,   266,   268,     4,     4,   272,
     270,   349,   372,     3,     8,   328,   330,     3,     8,   342,
       4,   345,     4,     4,     3,     8,   370,   360,   362,   364,
     366,   368,     8,     3,   291,   211,     4,   295,   293,   298,
       4,     8,     3,   313,     4,     8,     3,   240,   242,     3,
       8,     4,   414,   416,     4,   419,     4,     4,   423,   426,
       4,     4,     4,     4,   432,   435,     3,     8,   158,   158,
     140,     4,     4,     4,     4,   177,     4,     4,     4,   141,
     141,   141,   141,   141,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   141,     4,     4,   183,     4,    65,
     173,   210,   300,   379,   380,   381,   382,   383,     4,     4,
       4,     4,     4,   141,   143,     4,     4,     4,     4,   262,
       4,     4,   326,     4,   141,     4,   141,   141,   340,     4,
       4,     4,     4,     4,     4,   358,     4,     4,   141,     4,
       4,     4,   143,   286,     4,   143,   310,     4,     4,   238,
     143,     4,     4,   141,     4,   141,   141,     4,     4,   143,
     143,   143,   143,     4,     4,   411,     4,     7,     7,   158,
     158,     7,     7,     7,     5,     5,     5,     5,     5,     5,
       5,     5,     7,     7,     7,     7,     5,   169,   384,     8,
       3,     5,     5,   140,   140,   140,    58,    59,    60,   273,
     140,     5,     7,   140,   160,   162,   140,   140,   169,   169,
     169,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   158,   140,   140,   140,   113,   114,   424,   115,   116,
     117,   118,   119,   143,   433,   140,   158,   182,   121,   442,
     443,   444,   193,    15,    20,    21,    22,    23,    24,    25,
      26,   173,   199,   200,   201,   204,   206,   208,   210,   212,
     213,   214,   215,   199,     7,   255,   256,   257,     7,   278,
     279,   280,     7,   302,   303,   304,    70,   140,   218,   219,
     220,   221,   167,    71,   220,   224,   225,   226,   269,   377,
       7,   231,   232,   233,    79,    80,    81,    82,    83,    84,
     245,   246,   247,   248,   249,   250,   251,   252,    15,    89,
      90,    91,    92,   173,   212,   387,   388,   389,   392,   393,
     395,   396,    95,    96,   400,   401,   402,   404,   410,   170,
       4,   381,     7,   319,   320,   321,     7,   333,   334,   335,
       7,   350,   351,   352,    74,   373,     8,   445,     3,     8,
       8,   202,   205,   207,   209,     4,     4,     4,     4,     3,
       8,     8,   258,     6,     3,   281,     6,     3,   305,     6,
       3,     3,     6,     6,     3,     6,     3,     6,   234,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   390,
     394,     4,     4,     4,     3,     8,   403,   405,     3,     8,
       8,   140,   171,   172,   140,   322,     6,     3,   336,     6,
       3,   353,     6,     3,   374,     8,     4,   443,     4,     4,
       4,     4,   143,   141,   143,   141,   200,   261,   257,   284,
     280,   308,   304,   219,   225,   269,   237,   233,   141,   141,
     141,   141,   141,   141,   246,     4,     4,   141,   141,   141,
     388,     4,     4,   401,     6,     3,   325,   321,   339,   335,
     356,   352,     4,     5,    16,    17,    18,    19,   203,   140,
     140,   140,     8,     8,     8,     8,    86,    87,    88,   391,
     140,   140,   140,   140,     8,     8,     8,   140,     7,   446,
     447,   448,     3,     6,   122,   124,   125,   173,   210,   449,
     450,   451,   452,   454,   447,   455,     4,   453,     3,     8,
       4,   141,     4,   450,     5,   140,     7,   456,   457,   458,
       3,     6,   123,   459,   460,   457,   461,     3,     8,     4,
     460,   140
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   144,   146,   145,   147,   145,   148,   145,   149,   145,
     150,   145,   151,   145,   152,   145,   153,   145,   154,   145,
     155,   145,   156,   145,   157,   145,   158,   158,   158,   158,
     158,   158,   158,   159,   161,   160,   162,   163,   163,   164,
     164,   166,   165,   167,   167,   168,   168,   170,   169,   171,
     171,   172,   172,   173,   175,   174,   176,   176,   177,   177,
     177,   177,   177,   179,   178,   181,   180,   182,   182,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   184,   185,   186,   187,   188,   190,   189,   192,   191,
     194,   193,   196,   195,   198,   197,   199,   199,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   202,   201,
     203,   203,   203,   203,   205,   204,   207,   206,   209,   208,
     211,   210,   212,   213,   214,   215,   217,   216,   218,   218,
     219,   219,   220,   221,   223,   222,   224,   224,   225,   225,
     226,   228,   227,   230,   229,   231,   231,   232,   232,   234,
     233,   236,   235,   237,   237,   237,   238,   238,   240,   239,
     242,   241,   244,   243,   245,   245,   246,   246,   246,   246,
     246,   246,   247,   248,   249,   250,   251,   252,   254,   253,
     255,   255,   256,   256,   258,   257,   260,   259,   261,   261,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   264,   263,   266,
     265,   268,   267,   270,   269,   272,   271,   273,   273,   273,
     274,   275,   277,   276,   278,   278,   279,   279,   281,   280,
     283,   282,   284,   284,   285,   285,   286,   286,   286,   286,
     286,   286,   286,   286,   287,   288,   289,   291,   290,   293,
     292,   295,   294,   296,   298,   297,   299,   301,   300,   302,
     302,   303,   303,   305,   304,   307,   306,   308,   308,   309,
     309,   310,   310,   310,   310,   310,   310,   311,   313,   312,
     314,   315,   316,   318,   317,   319,   319,   320,   320,   322,
     321,   324,   323,   325,   325,   326,   326,   326,   326,   328,
     327,   330,   329,   332,   331,   333,   333,   334,   334,   336,
     335,   338,   337,   339,   339,   340,   340,   340,   340,   340,
     340,   340,   340,   342,   341,   343,   345,   344,   346,   347,
     349,   348,   350,   350,   351,   351,   353,   352,   355,   354,
     356,   356,   357,   357,   358,   358,   358,   358,   358,   358,
     358,   358,   360,   359,   362,   361,   364,   363,   366,   365,
     368,   367,   370,   369,   372,   371,   374,   373,   376,   375,
     377,   377,   378,   269,   379,   379,   380,   380,   381,   381,
     381,   381,   382,   384,   383,   386,   385,   387,   387,   388,
     388,   388,   388,   388,   388,   388,   390,   389,   391,   391,
     391,   392,   394,   393,   395,   396,   397,   399,   398,   400,
     400,   401,   401,   403,   402,   405,   404,   407,   406,   409,
     408,   410,   410,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   412,
     414,   413,   416,   415,   417,   419,   418,   420,   421,   423,
     422,   424,   424,   426,   425,   427,   428,   429,   430,   432,
     431,   433,   433,   433,   433,   433,   435,   434,   437,   436,
     439,   438,   441,   440,   442,   442,   443,   445,   444,   446,
     446,   448,   447,   449,   449,   450,   450,   450,   450,   450,
     451,   453,   452,   455,   454,   456,   456,   458,   457,   459,
     459,   461,   460
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
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     0,     4
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
  "\"disabled\"", "\"out-of-pool\"", "\"all\"", "\"mac-sources\"",
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
  "$@43", "client_class", "$@44", "reservation_mode", "$@45", "hr_mode",
  "id", "rapid_commit", "option_def_list", "$@46",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@47", "sub_option_def", "$@48",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@49",
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
       0,   225,   225,   225,   226,   226,   227,   227,   228,   228,
     229,   229,   230,   230,   231,   231,   232,   232,   233,   233,
     234,   234,   235,   235,   236,   236,   244,   245,   246,   247,
     248,   249,   250,   253,   258,   258,   269,   272,   273,   276,
     280,   287,   287,   294,   295,   298,   302,   309,   309,   316,
     317,   320,   324,   335,   345,   345,   357,   358,   362,   363,
     364,   365,   366,   369,   369,   386,   386,   394,   395,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   424,   429,   434,   439,   444,   449,   449,   459,   459,
     467,   467,   477,   477,   487,   487,   497,   498,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   513,   513,
     520,   521,   522,   523,   526,   526,   534,   534,   542,   542,
     550,   550,   558,   563,   568,   573,   578,   578,   588,   589,
     592,   593,   596,   601,   606,   606,   616,   617,   620,   621,
     624,   631,   631,   641,   641,   651,   652,   655,   656,   659,
     659,   667,   667,   675,   676,   677,   680,   681,   684,   684,
     692,   692,   700,   700,   710,   711,   714,   715,   716,   717,
     718,   719,   722,   727,   732,   737,   742,   747,   755,   755,
     768,   769,   772,   773,   780,   780,   803,   803,   812,   813,
     817,   818,   819,   820,   821,   822,   823,   824,   825,   826,
     827,   828,   829,   830,   831,   832,   833,   836,   836,   844,
     844,   852,   852,   860,   860,   868,   868,   875,   876,   877,
     880,   885,   894,   894,   906,   907,   910,   911,   916,   916,
     927,   927,   937,   938,   941,   942,   945,   946,   947,   948,
     949,   950,   951,   952,   955,   957,   962,   964,   964,   972,
     972,   980,   980,   988,   990,   990,   998,  1007,  1007,  1019,
    1020,  1025,  1026,  1031,  1031,  1042,  1042,  1053,  1054,  1059,
    1060,  1065,  1066,  1067,  1068,  1069,  1070,  1073,  1075,  1075,
    1083,  1085,  1087,  1095,  1095,  1107,  1108,  1111,  1112,  1115,
    1115,  1123,  1123,  1131,  1132,  1135,  1136,  1137,  1138,  1141,
    1141,  1149,  1149,  1159,  1159,  1171,  1172,  1175,  1176,  1179,
    1179,  1187,  1187,  1195,  1196,  1199,  1200,  1201,  1202,  1203,
    1204,  1205,  1206,  1209,  1209,  1217,  1222,  1222,  1230,  1235,
    1243,  1243,  1253,  1254,  1257,  1258,  1261,  1261,  1269,  1269,
    1277,  1278,  1281,  1282,  1286,  1287,  1288,  1289,  1290,  1291,
    1292,  1293,  1296,  1296,  1306,  1306,  1316,  1316,  1324,  1324,
    1332,  1332,  1340,  1340,  1353,  1353,  1363,  1363,  1374,  1374,
    1384,  1385,  1388,  1388,  1396,  1397,  1400,  1401,  1404,  1405,
    1406,  1407,  1410,  1412,  1412,  1423,  1423,  1433,  1434,  1437,
    1438,  1439,  1440,  1441,  1442,  1443,  1446,  1446,  1453,  1454,
    1455,  1458,  1463,  1463,  1471,  1476,  1483,  1490,  1490,  1500,
    1501,  1504,  1505,  1508,  1508,  1516,  1516,  1526,  1526,  1536,
    1536,  1544,  1545,  1548,  1549,  1550,  1551,  1552,  1553,  1554,
    1555,  1556,  1557,  1558,  1559,  1560,  1561,  1562,  1563,  1566,
    1571,  1571,  1579,  1579,  1587,  1592,  1592,  1600,  1605,  1610,
    1610,  1618,  1619,  1622,  1622,  1630,  1635,  1640,  1645,  1650,
    1650,  1658,  1661,  1664,  1667,  1670,  1676,  1676,  1686,  1686,
    1693,  1693,  1705,  1705,  1718,  1719,  1723,  1727,  1727,  1739,
    1740,  1744,  1744,  1752,  1753,  1756,  1757,  1758,  1759,  1760,
    1763,  1767,  1767,  1775,  1775,  1785,  1786,  1789,  1789,  1797,
    1798,  1801,  1801
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
#line 4162 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1809 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
