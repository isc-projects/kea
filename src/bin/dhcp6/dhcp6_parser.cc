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
      case 165: // value
      case 169: // map_value
      case 213: // db_type
      case 289: // hr_mode
      case 409: // duid_type
      case 442: // ncr_protocol_value
      case 450: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 150: // "boolean"
        value.move< bool > (that.value);
        break;

      case 149: // "floating point"
        value.move< double > (that.value);
        break;

      case 148: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 147: // "constant string"
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
      case 165: // value
      case 169: // map_value
      case 213: // db_type
      case 289: // hr_mode
      case 409: // duid_type
      case 442: // ncr_protocol_value
      case 450: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 150: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 149: // "floating point"
        value.copy< double > (that.value);
        break;

      case 148: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 147: // "constant string"
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
            case 147: // "constant string"

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 148: // "integer"

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 149: // "floating point"

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 150: // "boolean"

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 165: // value

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 169: // map_value

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 213: // db_type

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 289: // hr_mode

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 409: // duid_type

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 442: // ncr_protocol_value

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 450: // replace_client_name_value

#line 223 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 165: // value
      case 169: // map_value
      case 213: // db_type
      case 289: // hr_mode
      case 409: // duid_type
      case 442: // ncr_protocol_value
      case 450: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 150: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 149: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 148: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 147: // "constant string"
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
#line 232 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 233 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 234 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 818 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 276 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 287 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 294 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 309 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 316 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 318 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 327 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 352 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 376 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 383 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 545 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 546 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 547 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 574 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 609 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 617 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 624 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 642 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 683 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 719 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 723 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 836 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 859 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 896 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 898 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 914 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 928 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 929 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 983 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1009 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1026 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1094 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2076 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2122 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1231 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2185 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1313 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2278 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2286 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2398 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1406 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1424 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1473 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2502 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1507 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1509 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1514 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2567 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2649 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2667 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2677 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2715 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2760 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2769 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2787 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2822 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2887 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1719 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2937 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2972 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1787 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1823 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3085 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1845 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3130 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3139 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3157 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3161 "dhcp6_parser.cc" // lalr1.cc:859
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
      56,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,    39,    20,    41,    84,   115,   117,   123,
     138,   196,   198,   224,   246,   257,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
      20,   119,    18,    27,   151,    19,    -1,    33,    85,    28,
      59,   -36,   104,  -498,   264,   277,   282,   279,   289,  -498,
    -498,  -498,  -498,   299,  -498,   101,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,   301,   302,   309,   316,   317,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   318,
    -498,  -498,  -498,   169,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   319,   170,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   320,   321,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   173,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   176,  -498,  -498,
    -498,  -498,   322,  -498,   323,   324,  -498,  -498,  -498,   179,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,   285,   326,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   327,  -498,  -498,
    -498,   328,  -498,  -498,   325,   331,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   332,  -498,  -498,
    -498,  -498,   329,   335,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,   218,  -498,  -498,  -498,   336,  -498,  -498,
     337,  -498,   338,   339,  -498,  -498,   340,   341,   342,  -498,
    -498,  -498,   219,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    20,
      20,  -498,   188,   343,   344,   345,   346,  -498,    18,  -498,
     347,   348,   349,   191,   206,   207,   209,   210,   352,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   221,   364,
     366,    27,  -498,   367,   222,   151,  -498,    43,   369,   370,
     371,   372,   373,   233,   228,   375,   376,   378,   379,    19,
    -498,   380,   381,    -1,  -498,   382,   243,   383,   244,   245,
      33,  -498,   384,   385,   386,   390,   391,   392,   393,  -498,
      85,   394,   395,   255,   396,   397,   398,   256,  -498,    28,
     400,   258,  -498,    59,   401,   403,   -26,  -498,   261,   408,
     409,   266,   411,   268,   269,   414,   415,   270,   271,   273,
     418,   420,   104,  -498,  -498,  -498,   421,   419,   422,    20,
      20,  -498,   423,   424,   425,  -498,  -498,  -498,  -498,  -498,
     428,   429,   430,   431,   432,   435,   436,   439,   438,   440,
    -498,   441,   443,  -498,   447,  -498,  -498,  -498,  -498,  -498,
    -498,   445,   451,  -498,  -498,  -498,   450,   452,   280,   281,
     311,  -498,  -498,    92,   312,   456,   455,  -498,   330,   457,
    -498,   333,  -498,   334,  -498,  -498,  -498,   447,   447,   447,
     350,   351,   353,   354,  -498,   365,   368,  -498,   374,   377,
     387,  -498,  -498,   388,  -498,  -498,   389,    20,  -498,  -498,
     399,   402,  -498,   404,  -498,  -498,    71,   406,  -498,  -498,
    -498,    -7,   405,  -498,    20,    27,   407,  -498,  -498,   151,
     111,   111,   458,   459,   460,   -44,    20,   208,    36,   461,
     -53,    24,   124,   104,  -498,  -498,   442,  -498,    43,   462,
     464,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   465,
     410,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,   220,  -498,   230,  -498,
    -498,   231,  -498,  -498,  -498,  -498,   469,   470,   471,   472,
     474,  -498,  -498,  -498,   232,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   238,  -498,
     473,   479,  -498,  -498,   477,   481,  -498,  -498,   480,   482,
    -498,  -498,  -498,   102,  -498,  -498,  -498,   484,  -498,  -498,
    -498,   125,  -498,  -498,  -498,  -498,   272,  -498,   485,   489,
    -498,   490,   491,   492,   495,   498,   499,   239,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,   501,   502,   503,
    -498,  -498,   240,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,   241,  -498,  -498,  -498,   242,   412,   413,  -498,  -498,
     487,   505,  -498,  -498,   504,   506,  -498,  -498,   507,   508,
    -498,  -498,   509,  -498,   510,   407,  -498,  -498,   512,   514,
     515,   516,   315,   416,   417,   426,   427,   518,   519,   111,
    -498,  -498,    19,  -498,   458,    28,  -498,   459,    59,  -498,
     460,   -44,  -498,  -498,   208,  -498,    36,  -498,   -36,  -498,
     461,   433,   434,   437,   444,   446,   448,   -53,  -498,   522,
     523,   449,   453,   454,    24,  -498,   524,   525,   124,  -498,
    -498,  -498,   527,   528,  -498,    -1,  -498,   462,    33,  -498,
     464,    85,  -498,   465,   526,  -498,   483,  -498,   254,   463,
     466,   467,  -498,  -498,  -498,  -498,  -498,   468,   475,  -498,
     249,  -498,   529,  -498,   530,  -498,  -498,  -498,  -498,   251,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   217,   476,
    -498,  -498,  -498,  -498,   478,   486,  -498,  -498,   488,   252,
    -498,   253,  -498,   531,  -498,   497,   533,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,   291,  -498,    57,   533,  -498,  -498,
     537,  -498,  -498,  -498,   259,  -498,  -498,  -498,  -498,  -498,
     538,   494,   539,    57,  -498,   540,  -498,   500,  -498,   541,
    -498,  -498,   298,  -498,    17,   541,  -498,  -498,   543,   546,
     549,   260,  -498,  -498,  -498,  -498,  -498,  -498,   550,   511,
     517,   520,    17,  -498,   513,  -498,  -498,  -498,  -498,  -498
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      65,     7,    98,     9,   211,    11,   316,    13,   336,    15,
     363,    17,   255,    19,   290,    21,   176,    23,   447,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   365,   257,
     292,     0,     0,    45,     0,    44,     0,     0,    38,    63,
     498,   494,   496,     0,    62,     0,    56,    58,    60,    61,
      59,    96,   107,   109,     0,     0,     0,     0,     0,   203,
     247,   282,   149,   166,   157,   396,   168,   187,   413,     0,
     435,   445,    90,     0,    67,    69,    70,    71,    72,    73,
      75,    76,    77,    78,    80,    79,    84,    85,    74,    82,
      83,    81,    86,    87,    88,    89,   104,     0,     0,   100,
     102,   103,   400,   308,   328,   232,   234,   236,     0,     0,
     240,   238,   355,   392,   231,   215,   216,   217,   218,     0,
     213,   222,   223,   224,   227,   229,   225,   226,   219,   220,
     221,   228,   230,   324,   326,   323,   321,     0,   318,   320,
     322,   348,     0,   351,     0,     0,   347,   343,   346,     0,
     338,   340,   341,   344,   345,   342,   390,   378,   380,   382,
     384,   386,   388,   377,   376,     0,   366,   367,   371,   372,
     369,   373,   374,   375,   370,   272,   139,     0,   276,   274,
     279,     0,   268,   269,     0,   258,   259,   261,   271,   262,
     263,   264,   278,   265,   266,   267,   303,     0,   301,   302,
     305,   306,     0,   293,   294,   296,   297,   298,   299,   300,
     183,   185,   180,     0,   178,   181,   182,     0,   467,   469,
       0,   472,     0,     0,   476,   480,     0,     0,     0,   485,
     492,   465,     0,   449,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,    42,     0,
       0,    35,     0,     0,     0,     0,     0,    53,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,    99,   402,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     212,     0,     0,     0,   317,     0,     0,     0,     0,     0,
       0,   337,     0,     0,     0,     0,     0,     0,     0,   364,
       0,     0,     0,     0,     0,     0,     0,     0,   256,     0,
       0,     0,   291,     0,     0,     0,     0,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   448,    46,    39,     0,     0,     0,     0,
       0,    57,     0,     0,     0,    91,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     434,     0,     0,    68,     0,   106,   101,   411,   409,   410,
     408,     0,   403,   404,   406,   407,     0,     0,     0,     0,
       0,   245,   246,     0,     0,     0,     0,   214,     0,     0,
     319,     0,   350,     0,   353,   354,   339,     0,     0,     0,
       0,     0,     0,     0,   368,     0,     0,   270,     0,     0,
       0,   281,   260,     0,   307,   295,     0,     0,   179,   466,
       0,     0,   471,     0,   474,   475,     0,     0,   482,   483,
     484,     0,     0,   450,     0,     0,     0,   495,   497,     0,
       0,     0,   205,   249,   284,     0,    43,     0,     0,   170,
       0,     0,     0,     0,    47,   105,     0,   401,     0,   310,
     330,   233,   235,   237,   242,   243,   244,   241,   239,   357,
       0,   325,    36,   327,   349,   352,   391,   379,   381,   383,
     385,   387,   389,   273,   140,   277,   275,   280,   304,   184,
     186,   468,   470,   473,   478,   479,   477,   481,   487,   488,
     489,   490,   491,   486,   493,    40,     0,   503,     0,   500,
     502,     0,   126,   132,   134,   136,     0,     0,     0,     0,
       0,   145,   147,   125,     0,   111,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,   209,
       0,   206,   207,   253,     0,   250,   251,   288,     0,   285,
     286,   155,   156,     0,   151,   153,   154,     0,   164,   165,
     161,     0,   159,   162,   163,   398,     0,   174,     0,   171,
     172,     0,     0,     0,     0,     0,     0,     0,   189,   191,
     192,   193,   194,   195,   196,   424,   430,     0,     0,     0,
     423,   422,     0,   415,   417,   420,   418,   419,   421,   441,
     443,     0,   437,   439,   440,     0,    49,     0,   405,   314,
       0,   311,   312,   334,     0,   331,   332,   361,     0,   358,
     359,   394,     0,    64,     0,     0,   499,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   110,     0,   204,     0,   257,   248,     0,   292,   283,
       0,     0,   150,   167,     0,   158,     0,   397,     0,   169,
       0,     0,     0,     0,     0,     0,     0,     0,   188,     0,
       0,     0,     0,     0,     0,   414,     0,     0,     0,   436,
     446,    51,     0,    50,   412,     0,   309,     0,     0,   329,
       0,   365,   356,     0,     0,   393,     0,   501,     0,     0,
       0,     0,   138,   141,   142,   143,   144,     0,     0,   112,
       0,   208,     0,   252,     0,   287,   152,   160,   399,     0,
     173,   197,   198,   199,   200,   201,   202,   190,     0,     0,
     429,   432,   433,   416,     0,     0,   438,    48,     0,     0,
     313,     0,   333,     0,   360,     0,     0,   128,   129,   130,
     131,   127,   133,   135,   137,   146,   148,   210,   254,   289,
     175,   426,   427,   428,   425,   431,   442,   444,    52,   315,
     335,   362,   395,   507,     0,   505,     0,     0,   504,   519,
       0,   517,   515,   511,     0,   509,   513,   514,   512,   506,
       0,     0,     0,     0,   508,     0,   516,     0,   510,     0,
     518,   523,     0,   521,     0,     0,   520,   531,     0,     0,
       0,     0,   525,   527,   528,   529,   530,   522,     0,     0,
       0,     0,     0,   524,     0,   533,   534,   535,   526,   532
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,    10,  -498,    95,  -498,  -498,  -498,
    -498,  -498,  -498,    49,  -498,  -140,  -498,  -498,  -498,   -62,
    -498,  -498,  -498,   263,  -498,  -498,  -498,  -498,    61,   236,
     -63,   -50,   -49,   -43,  -498,  -498,  -498,  -498,  -498,    63,
     247,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    62,  -141,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
     -58,  -498,  -497,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -147,  -484,  -498,  -498,  -498,  -498,  -146,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -153,  -498,
    -498,  -498,  -149,   194,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -156,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -131,  -498,  -498,  -498,  -128,   248,  -498,  -498,
    -498,  -498,  -498,  -498,  -487,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -130,  -498,  -498,  -498,  -127,
    -498,   211,  -498,   -59,  -498,  -498,  -498,  -498,  -498,   -57,
    -498,  -498,  -498,  -498,  -498,   -48,  -498,  -498,  -498,  -126,
    -498,  -498,  -498,  -129,  -498,   213,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -164,  -498,  -498,  -498,
    -157,   250,  -498,  -498,   -66,  -498,  -498,  -498,  -498,  -498,
    -161,  -498,  -498,  -498,  -158,   262,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -162,  -498,  -498,
    -498,  -152,  -498,   235,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,    80,  -498,
    -498,  -498,  -498,  -498,  -498,  -134,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -135,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,    91,   214,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,
    -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,  -498,   -80,
    -498,  -498,  -498,  -230,  -498,  -498,  -245,  -498,  -498,  -498,
    -498,  -498,  -498,  -256,  -498,  -498,  -271,  -498,  -498,  -498,
    -498,  -498
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   533,    77,
      78,    37,    60,    74,    75,   515,   666,   742,   743,   112,
      39,    62,    85,    86,    87,   293,    41,    63,   113,   114,
     115,   116,   117,   118,   119,   120,   300,    43,    64,   138,
     139,   140,   323,   141,   121,   301,   122,   302,   584,   585,
     586,   688,   811,   587,   689,   588,   690,   589,   691,   590,
     223,   362,   592,   593,   594,   595,   596,   697,   597,   698,
     123,   311,   613,   614,   615,   616,   124,   313,   621,   622,
     623,   624,   125,   312,   126,   315,   628,   629,   630,   718,
      57,    71,   253,   254,   255,   374,   256,   375,   127,   316,
     637,   638,   639,   640,   641,   642,   643,   644,   128,   308,
     600,   601,   602,   702,    45,    65,   159,   160,   161,   330,
     162,   331,   163,   332,   164,   336,   165,   335,   527,   166,
     167,   129,   309,   604,   605,   606,   705,    53,    69,   224,
     225,   226,   227,   228,   229,   230,   361,   231,   365,   232,
     364,   233,   234,   366,   235,   130,   310,   608,   609,   610,
     708,    55,    70,   242,   243,   244,   245,   246,   370,   247,
     248,   249,   169,   328,   670,   671,   672,   745,    47,    66,
     177,   178,   179,   341,   180,   342,   170,   329,   674,   675,
     676,   748,    49,    67,   189,   190,   191,   345,   192,   193,
     347,   194,   195,   171,   337,   678,   679,   680,   751,    51,
      68,   205,   206,   207,   208,   353,   209,   354,   210,   355,
     211,   356,   212,   357,   213,   358,   214,   352,   172,   338,
     682,   754,   131,   314,   626,   327,   431,   432,   433,   434,
     435,   516,   132,   317,   652,   653,   654,   729,   824,   655,
     656,   730,   657,   658,   133,   134,   319,   661,   662,   663,
     736,   664,   737,   135,   320,    59,    72,   272,   273,   274,
     275,   379,   276,   380,   277,   278,   382,   279,   280,   281,
     385,   556,   282,   386,   283,   284,   285,   286,   390,   563,
     287,   391,    88,   295,    89,   296,    90,   294,   568,   569,
     570,   684,   834,   835,   836,   844,   845,   846,   847,   852,
     848,   850,   862,   863,   864,   871,   872,   873,   878,   874,
     875,   876
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      84,   188,   155,   154,   175,   186,   203,   222,   238,   252,
     271,   240,   239,   241,   651,   156,   157,   168,   176,   187,
     204,   625,   158,   620,    34,    27,   142,    28,    79,    29,
     611,   631,   632,   633,   634,   635,   636,   101,    91,    26,
     645,    92,    93,   142,   215,   250,   251,   173,    38,   577,
      94,    95,    96,    97,   174,   250,   251,   101,    94,    95,
      96,    97,    98,    99,   100,   101,   143,   216,   144,   217,
     218,   101,   219,   220,   221,   145,   146,   147,   148,   149,
     150,   101,   216,   181,   182,   183,   184,   185,   174,   151,
     152,    40,   102,   103,   104,   105,   216,   153,   216,   236,
     217,   218,   237,   612,   298,   711,   151,   106,   712,   299,
     107,    83,   427,   558,   559,   560,   561,   108,   646,   647,
     648,   649,    42,   101,    44,   109,   110,   572,   714,   111,
      46,   715,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,    80,   562,   867,    48,    83,   868,   869,   870,
     216,    81,    82,   196,   524,   525,   526,   197,   198,   199,
     200,   201,   202,   136,   137,    83,    83,    30,    31,    32,
      33,    83,   321,   325,    83,    83,   339,   322,   326,   343,
      83,   340,   350,   839,   344,   840,   841,   351,   554,   555,
      83,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    50,    83,    52,    83,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   376,   392,   321,   659,   660,   377,   393,   683,   778,
     620,    54,    83,   685,   325,   699,    84,   651,   686,   687,
     700,   699,   727,   734,   738,   392,   701,   728,   735,   739,
     740,    83,   339,    56,   376,   343,   350,   817,    83,   820,
     829,   830,   853,   882,    58,   428,    76,   854,   883,   429,
     288,   807,   808,   809,   810,   716,   155,   154,   717,   430,
     289,   175,   611,   618,   188,   619,   290,   291,   186,   156,
     157,   168,   292,   359,   837,   176,   158,   838,   203,   394,
     395,   865,   187,   297,   866,   303,   304,   222,   821,   822,
     823,   238,   204,   305,   240,   239,   241,   536,   537,   538,
     306,   307,   318,   324,   333,   334,   346,   348,   349,   360,
     271,   363,   367,   368,   369,   396,   371,   372,   373,   405,
     378,   381,   383,   384,   387,   388,   389,   397,   398,   399,
     400,   402,   403,   404,   406,   407,   410,   408,   409,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   421,   420,
     422,   424,   425,   436,   437,   438,   439,   440,   442,   443,
     444,   441,   445,   446,   448,   449,   451,   453,   457,   458,
     459,   452,   454,   455,   460,   461,   462,   463,   465,   466,
     468,   469,   470,   467,   473,   476,   471,   477,   474,   497,
     498,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   491,   490,   492,   494,   495,   521,   522,   496,
     499,   500,   501,   502,   503,   504,   505,   506,   583,   583,
     507,   508,   591,   591,   509,   510,   667,   511,   512,   650,
     513,   271,   514,   517,   518,   519,   428,   520,   523,   528,
     429,   529,   530,   762,    28,   599,   603,   607,   627,   669,
     430,   673,   677,   692,   693,   694,   695,   531,   696,   703,
     534,   535,   704,   706,   707,   710,   709,   550,   806,   681,
     713,   719,   720,   746,   721,   722,   723,   539,   540,   724,
     541,   542,   725,   726,   565,   731,   732,   733,   747,   750,
     749,   753,   543,   752,   756,   544,   758,   755,   759,   760,
     761,   545,   767,   768,   546,   557,   788,   789,   794,   795,
     805,   798,   567,   797,   547,   548,   549,   818,   819,   831,
     833,   851,   855,   857,   532,   859,   551,   879,   861,   552,
     880,   553,   564,   881,   884,   617,   566,   423,   769,   741,
     744,   401,   571,   598,   776,   764,   763,   780,   777,   779,
     478,   787,   426,   771,   770,   766,   765,   773,   772,   774,
     472,   781,   782,   800,   775,   783,   475,   447,   799,   802,
     801,   804,   784,   450,   785,   464,   786,   790,   668,   803,
     793,   791,   792,   796,   665,   757,   493,   849,   858,   877,
     812,   888,   456,   813,   814,   815,     0,     0,     0,     0,
       0,     0,   816,   825,     0,   826,     0,     0,     0,     0,
       0,     0,     0,   827,     0,   828,     0,   583,     0,   155,
     154,   591,   856,   222,   832,     0,   238,   860,     0,   240,
     239,   241,   156,   157,   168,     0,   252,     0,     0,   158,
     889,   885,     0,     0,     0,   886,     0,     0,   887,     0,
       0,     0,   650,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   175,     0,     0,   186,     0,     0,   203,
       0,     0,     0,     0,     0,     0,     0,   176,     0,     0,
     187,     0,     0,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   842,     0,     0,     0,   843,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   842,     0,     0,     0,   843
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    67,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    70,    70,    70,   511,    65,    65,    65,    66,    67,
      68,   508,    65,   507,    14,     5,     7,     7,    10,     9,
      74,    84,    85,    86,    87,    88,    89,    38,    11,     0,
      16,    14,    15,     7,    16,    81,    82,    48,     7,    25,
      31,    32,    33,    34,    55,    81,    82,    38,    31,    32,
      33,    34,    35,    36,    37,    38,    47,    39,    49,    41,
      42,    38,    44,    45,    46,    56,    57,    58,    59,    60,
      61,    38,    39,    50,    51,    52,    53,    54,    55,    70,
      71,     7,    65,    66,    67,    68,    39,    78,    39,    40,
      41,    42,    43,   147,     3,     3,    70,    80,     6,     8,
      83,   147,    69,   120,   121,   122,   123,    90,    94,    95,
      96,    97,     7,    38,     7,    98,    99,    16,     3,   102,
       7,     6,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,   124,   150,   127,     7,   147,   130,   131,   132,
      39,   133,   134,    68,    62,    63,    64,    72,    73,    74,
      75,    76,    77,    12,    13,   147,   147,   147,   148,   149,
     150,   147,     3,     3,   147,   147,     3,     8,     8,     3,
     147,     8,     3,   126,     8,   128,   129,     8,   117,   118,
     147,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     7,   147,     7,   147,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     3,     3,     3,   100,   101,     8,     8,     8,   716,
     714,     7,   147,     3,     3,     3,   298,   734,     8,     8,
       8,     3,     3,     3,     3,     3,     8,     8,     8,     8,
       8,   147,     3,     7,     3,     3,     3,     8,   147,     8,
       8,     8,     3,     3,     7,   327,   147,     8,     8,   327,
       6,    17,    18,    19,    20,     3,   339,   339,     6,   327,
       3,   343,    74,    75,   350,    77,     4,     8,   350,   339,
     339,   339,     3,     8,     3,   343,   339,     6,   360,   289,
     290,     3,   350,     4,     6,     4,     4,   369,    91,    92,
      93,   373,   360,     4,   373,   373,   373,   457,   458,   459,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     392,     4,     4,     8,     3,   147,     4,     8,     3,   148,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   148,   148,     4,   148,   148,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   148,
       4,     4,   150,     4,     4,     4,     4,     4,   150,     4,
       4,   148,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   148,   148,   148,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   148,     4,     4,   150,     4,   150,   399,
     400,   150,     4,     4,   148,     4,   148,   148,     4,     4,
     150,   150,     4,   150,     4,     4,     7,   147,   147,     7,
       7,     7,     7,     5,     5,     5,     5,     5,   500,   501,
       5,     5,   500,   501,     5,     7,     4,     7,     7,   511,
       7,   513,     5,     8,     3,     5,   518,     5,   147,   147,
     518,     5,     7,   148,     7,     7,     7,     7,     7,     7,
     518,     7,     7,     4,     4,     4,     4,   147,     4,     6,
     147,   147,     3,     6,     3,     3,     6,   477,     5,    79,
       6,     6,     3,     6,     4,     4,     4,   147,   147,     4,
     147,   147,     4,     4,   494,     4,     4,     4,     3,     3,
       6,     3,   147,     6,     4,   147,     4,     8,     4,     4,
       4,   147,     4,     4,   147,   119,     4,     4,     4,     4,
       4,     3,   125,     6,   147,   147,   147,     8,     8,     8,
       7,     4,     4,     4,   449,     5,   147,     4,     7,   147,
       4,   147,   147,     4,     4,   506,   495,   321,   699,   147,
     147,   298,   499,   501,   711,   148,   150,   720,   714,   718,
     376,   727,   325,   704,   702,   148,   150,   707,   705,   708,
     369,   148,   148,   747,   710,   148,   373,   339,   745,   750,
     748,   753,   148,   343,   148,   360,   148,   148,   518,   751,
     734,   148,   148,   738,   513,   685,   392,   837,   853,   865,
     147,   882,   350,   147,   147,   147,    -1,    -1,    -1,    -1,
      -1,    -1,   147,   147,    -1,   147,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   147,    -1,   147,    -1,   699,    -1,   702,
     702,   699,   148,   705,   147,    -1,   708,   147,    -1,   708,
     708,   708,   702,   702,   702,    -1,   718,    -1,    -1,   702,
     147,   150,    -1,    -1,    -1,   148,    -1,    -1,   148,    -1,
      -1,    -1,   734,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   748,   745,    -1,    -1,   748,    -1,    -1,   751,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   745,    -1,    -1,
     748,    -1,    -1,   751,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   836,    -1,    -1,    -1,   836,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   853,    -1,    -1,    -1,   853
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     0,     5,     7,     9,
     147,   148,   149,   150,   165,   166,   167,   172,     7,   181,
       7,   187,     7,   198,     7,   275,     7,   339,     7,   353,
       7,   370,     7,   298,     7,   322,     7,   251,     7,   426,
     173,   168,   182,   188,   199,   276,   340,   354,   371,   299,
     323,   252,   427,   165,   174,   175,   147,   170,   171,    10,
     124,   133,   134,   147,   180,   183,   184,   185,   453,   455,
     457,    11,    14,    15,    31,    32,    33,    34,    35,    36,
      37,    38,    65,    66,    67,    68,    80,    83,    90,    98,
      99,   102,   180,   189,   190,   191,   192,   193,   194,   195,
     196,   205,   207,   231,   237,   243,   245,   259,   269,   292,
     316,   393,   403,   415,   416,   424,    12,    13,   200,   201,
     202,   204,     7,    47,    49,    56,    57,    58,    59,    60,
      61,    70,    71,    78,   180,   191,   192,   193,   194,   277,
     278,   279,   281,   283,   285,   287,   290,   291,   316,   333,
     347,   364,   389,    48,    55,   180,   316,   341,   342,   343,
     345,    50,    51,    52,    53,    54,   180,   316,   345,   355,
     356,   357,   359,   360,   362,   363,    68,    72,    73,    74,
      75,    76,    77,   180,   316,   372,   373,   374,   375,   377,
     379,   381,   383,   385,   387,    16,    39,    41,    42,    44,
      45,    46,   180,   221,   300,   301,   302,   303,   304,   305,
     306,   308,   310,   312,   313,   315,    40,    43,   180,   221,
     304,   310,   324,   325,   326,   327,   328,   330,   331,   332,
      81,    82,   180,   253,   254,   255,   257,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   180,   428,   429,   430,   431,   433,   435,   436,   438,
     439,   440,   443,   445,   446,   447,   448,   451,     6,     3,
       4,     8,     3,   186,   458,   454,   456,     4,     3,     8,
     197,   206,   208,     4,     4,     4,     4,     4,   270,   293,
     317,   232,   244,   238,   394,   246,   260,   404,     4,   417,
     425,     3,     8,   203,     4,     3,     8,   396,   334,   348,
     280,   282,   284,     4,     4,   288,   286,   365,   390,     3,
       8,   344,   346,     3,     8,   358,     4,   361,     4,     4,
       3,     8,   388,   376,   378,   380,   382,   384,   386,     8,
       3,   307,   222,     4,   311,   309,   314,     4,     8,     3,
     329,     4,     8,     3,   256,   258,     3,     8,     4,   432,
     434,     4,   437,     4,     4,   441,   444,     4,     4,     4,
     449,   452,     3,     8,   165,   165,   147,     4,     4,     4,
       4,   184,     4,     4,     4,   148,   148,   148,   148,   148,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     148,     4,     4,   190,     4,   150,   201,    69,   180,   221,
     316,   397,   398,   399,   400,   401,     4,     4,     4,     4,
       4,   148,   150,     4,     4,     4,     4,   278,     4,     4,
     342,     4,   148,     4,   148,   148,   356,     4,     4,     4,
       4,     4,     4,     4,   374,     4,     4,   148,     4,     4,
       4,   150,   302,     4,   150,   326,     4,     4,   254,   150,
       4,     4,   148,     4,   148,   148,     4,     4,   150,   150,
     150,     4,     4,   429,     4,     7,     7,   165,   165,     7,
       7,     7,     5,     5,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   176,   402,     8,     3,     5,
       5,   147,   147,   147,    62,    63,    64,   289,   147,     5,
       7,   147,   167,   169,   147,   147,   176,   176,   176,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     165,   147,   147,   147,   117,   118,   442,   119,   120,   121,
     122,   123,   150,   450,   147,   165,   189,   125,   459,   460,
     461,   200,    16,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   180,   209,   210,   211,   214,   216,   218,
     220,   221,   223,   224,   225,   226,   227,   229,   209,     7,
     271,   272,   273,     7,   294,   295,   296,     7,   318,   319,
     320,    74,   147,   233,   234,   235,   236,   174,    75,    77,
     235,   239,   240,   241,   242,   285,   395,     7,   247,   248,
     249,    84,    85,    86,    87,    88,    89,   261,   262,   263,
     264,   265,   266,   267,   268,    16,    94,    95,    96,    97,
     180,   223,   405,   406,   407,   410,   411,   413,   414,   100,
     101,   418,   419,   420,   422,   428,   177,     4,   399,     7,
     335,   336,   337,     7,   349,   350,   351,     7,   366,   367,
     368,    79,   391,     8,   462,     3,     8,     8,   212,   215,
     217,   219,     4,     4,     4,     4,     4,   228,   230,     3,
       8,     8,   274,     6,     3,   297,     6,     3,   321,     6,
       3,     3,     6,     6,     3,     6,     3,     6,   250,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   408,
     412,     4,     4,     4,     3,     8,   421,   423,     3,     8,
       8,   147,   178,   179,   147,   338,     6,     3,   352,     6,
       3,   369,     6,     3,   392,     8,     4,   460,     4,     4,
       4,     4,   148,   150,   148,   150,   148,     4,     4,   210,
     277,   273,   300,   296,   324,   320,   234,   240,   285,   253,
     249,   148,   148,   148,   148,   148,   148,   262,     4,     4,
     148,   148,   148,   406,     4,     4,   419,     6,     3,   341,
     337,   355,   351,   372,   368,     4,     5,    17,    18,    19,
      20,   213,   147,   147,   147,   147,   147,     8,     8,     8,
       8,    91,    92,    93,   409,   147,   147,   147,   147,     8,
       8,     8,   147,     7,   463,   464,   465,     3,     6,   126,
     128,   129,   180,   221,   466,   467,   468,   469,   471,   464,
     472,     4,   470,     3,     8,     4,   148,     4,   467,     5,
     147,     7,   473,   474,   475,     3,     6,   127,   130,   131,
     132,   476,   477,   478,   480,   481,   482,   474,   479,     4,
       4,     4,     3,     8,     4,   150,   148,   148,   477,   147
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   151,   153,   152,   154,   152,   155,   152,   156,   152,
     157,   152,   158,   152,   159,   152,   160,   152,   161,   152,
     162,   152,   163,   152,   164,   152,   165,   165,   165,   165,
     165,   165,   165,   166,   168,   167,   169,   170,   170,   171,
     171,   173,   172,   174,   174,   175,   175,   177,   176,   178,
     178,   179,   179,   180,   182,   181,   183,   183,   184,   184,
     184,   184,   184,   186,   185,   188,   187,   189,   189,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   191,   192,   193,   194,   195,   197,   196,   199,   198,
     200,   200,   201,   201,   203,   202,   204,   206,   205,   208,
     207,   209,   209,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   212,   211,   213,   213,
     213,   213,   215,   214,   217,   216,   219,   218,   220,   222,
     221,   223,   224,   225,   226,   228,   227,   230,   229,   232,
     231,   233,   233,   234,   234,   235,   236,   238,   237,   239,
     239,   240,   240,   240,   241,   242,   244,   243,   246,   245,
     247,   247,   248,   248,   250,   249,   252,   251,   253,   253,
     253,   254,   254,   256,   255,   258,   257,   260,   259,   261,
     261,   262,   262,   262,   262,   262,   262,   263,   264,   265,
     266,   267,   268,   270,   269,   271,   271,   272,   272,   274,
     273,   276,   275,   277,   277,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   280,   279,   282,   281,   284,   283,   286,   285,
     288,   287,   289,   289,   289,   290,   291,   293,   292,   294,
     294,   295,   295,   297,   296,   299,   298,   300,   300,   301,
     301,   302,   302,   302,   302,   302,   302,   302,   302,   303,
     304,   305,   307,   306,   309,   308,   311,   310,   312,   314,
     313,   315,   317,   316,   318,   318,   319,   319,   321,   320,
     323,   322,   324,   324,   325,   325,   326,   326,   326,   326,
     326,   326,   327,   329,   328,   330,   331,   332,   334,   333,
     335,   335,   336,   336,   338,   337,   340,   339,   341,   341,
     342,   342,   342,   342,   344,   343,   346,   345,   348,   347,
     349,   349,   350,   350,   352,   351,   354,   353,   355,   355,
     356,   356,   356,   356,   356,   356,   356,   356,   358,   357,
     359,   361,   360,   362,   363,   365,   364,   366,   366,   367,
     367,   369,   368,   371,   370,   372,   372,   373,   373,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   376,   375,
     378,   377,   380,   379,   382,   381,   384,   383,   386,   385,
     388,   387,   390,   389,   392,   391,   394,   393,   395,   395,
     396,   285,   397,   397,   398,   398,   399,   399,   399,   399,
     400,   402,   401,   404,   403,   405,   405,   406,   406,   406,
     406,   406,   406,   406,   408,   407,   409,   409,   409,   410,
     412,   411,   413,   414,   415,   417,   416,   418,   418,   419,
     419,   421,   420,   423,   422,   425,   424,   427,   426,   428,
     428,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   430,   432,   431,   434,
     433,   435,   437,   436,   438,   439,   441,   440,   442,   442,
     444,   443,   445,   446,   447,   449,   448,   450,   450,   450,
     450,   450,   452,   451,   454,   453,   456,   455,   458,   457,
     459,   459,   460,   462,   461,   463,   463,   465,   464,   466,
     466,   467,   467,   467,   467,   467,   468,   470,   469,   472,
     471,   473,   473,   475,   474,   476,   476,   477,   477,   477,
     477,   479,   478,   480,   481,   482
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
       1,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
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
       0,   232,   232,   232,   233,   233,   234,   234,   235,   235,
     236,   236,   237,   237,   238,   238,   239,   239,   240,   240,
     241,   241,   242,   242,   243,   243,   251,   252,   253,   254,
     255,   256,   257,   260,   265,   265,   276,   279,   280,   283,
     287,   294,   294,   301,   302,   305,   309,   316,   316,   323,
     324,   327,   331,   342,   352,   352,   364,   365,   369,   370,
     371,   372,   373,   376,   376,   393,   393,   401,   402,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   431,   436,   441,   446,   451,   456,   456,   466,   466,
     474,   475,   478,   479,   482,   482,   492,   498,   498,   508,
     508,   518,   519,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   537,   537,   544,   545,
     546,   547,   550,   550,   558,   558,   566,   566,   574,   579,
     579,   587,   592,   597,   602,   607,   607,   615,   615,   624,
     624,   634,   635,   638,   639,   642,   647,   652,   652,   662,
     663,   666,   667,   668,   671,   676,   683,   683,   693,   693,
     703,   704,   707,   708,   711,   711,   719,   719,   727,   728,
     729,   732,   733,   736,   736,   744,   744,   752,   752,   762,
     763,   766,   767,   768,   769,   770,   771,   774,   779,   784,
     789,   794,   799,   807,   807,   820,   821,   824,   825,   832,
     832,   855,   855,   864,   865,   869,   870,   871,   872,   873,
     874,   875,   876,   877,   878,   879,   880,   881,   882,   883,
     884,   885,   888,   888,   896,   896,   904,   904,   912,   912,
     920,   920,   927,   928,   929,   932,   937,   946,   946,   958,
     959,   962,   963,   968,   968,   979,   979,   989,   990,   993,
     994,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,  1007,
    1009,  1014,  1016,  1016,  1024,  1024,  1032,  1032,  1040,  1042,
    1042,  1050,  1059,  1059,  1071,  1072,  1077,  1078,  1083,  1083,
    1094,  1094,  1105,  1106,  1111,  1112,  1117,  1118,  1119,  1120,
    1121,  1122,  1125,  1127,  1127,  1135,  1137,  1139,  1147,  1147,
    1159,  1160,  1163,  1164,  1167,  1167,  1175,  1175,  1183,  1184,
    1187,  1188,  1189,  1190,  1193,  1193,  1201,  1201,  1211,  1211,
    1223,  1224,  1227,  1228,  1231,  1231,  1239,  1239,  1247,  1248,
    1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,  1261,  1261,
    1269,  1274,  1274,  1282,  1287,  1295,  1295,  1305,  1306,  1309,
    1310,  1313,  1313,  1321,  1321,  1329,  1330,  1333,  1334,  1338,
    1339,  1340,  1341,  1342,  1343,  1344,  1345,  1346,  1349,  1349,
    1359,  1359,  1369,  1369,  1377,  1377,  1385,  1385,  1393,  1393,
    1401,  1401,  1414,  1414,  1424,  1424,  1435,  1435,  1445,  1446,
    1449,  1449,  1457,  1458,  1461,  1462,  1465,  1466,  1467,  1468,
    1471,  1473,  1473,  1484,  1484,  1494,  1495,  1498,  1499,  1500,
    1501,  1502,  1503,  1504,  1507,  1507,  1514,  1515,  1516,  1519,
    1524,  1524,  1532,  1537,  1544,  1551,  1551,  1561,  1562,  1565,
    1566,  1569,  1569,  1577,  1577,  1587,  1587,  1597,  1597,  1605,
    1606,  1609,  1610,  1611,  1612,  1613,  1614,  1615,  1616,  1617,
    1618,  1619,  1620,  1621,  1622,  1623,  1626,  1631,  1631,  1639,
    1639,  1647,  1652,  1652,  1660,  1665,  1670,  1670,  1678,  1679,
    1682,  1682,  1690,  1695,  1700,  1705,  1705,  1713,  1716,  1719,
    1722,  1725,  1731,  1731,  1741,  1741,  1748,  1748,  1760,  1760,
    1773,  1774,  1778,  1782,  1782,  1794,  1795,  1799,  1799,  1807,
    1808,  1811,  1812,  1813,  1814,  1815,  1818,  1823,  1823,  1831,
    1831,  1841,  1842,  1845,  1845,  1853,  1854,  1857,  1858,  1859,
    1860,  1863,  1863,  1871,  1876,  1881
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
#line 4291 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1886 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
