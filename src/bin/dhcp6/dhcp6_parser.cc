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
      case 178: // value
      case 182: // map_value
      case 226: // db_type
      case 307: // hr_mode
      case 441: // duid_type
      case 474: // ncr_protocol_value
      case 482: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 161: // "boolean"
        value.move< bool > (that.value);
        break;

      case 160: // "floating point"
        value.move< double > (that.value);
        break;

      case 159: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 158: // "constant string"
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
      case 178: // value
      case 182: // map_value
      case 226: // db_type
      case 307: // hr_mode
      case 441: // duid_type
      case 474: // ncr_protocol_value
      case 482: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 161: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 160: // "floating point"
        value.copy< double > (that.value);
        break;

      case 159: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 158: // "constant string"
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
            case 158: // "constant string"

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 159: // "integer"

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 160: // "floating point"

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 161: // "boolean"

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 178: // value

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 182: // map_value

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 226: // db_type

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 307: // hr_mode

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 441: // duid_type

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 474: // ncr_protocol_value

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 482: // replace_client_name_value

#line 234 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 178: // value
      case 182: // map_value
      case 226: // db_type
      case 307: // hr_mode
      case 441: // duid_type
      case 474: // ncr_protocol_value
      case 482: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 161: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 160: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 159: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 158: // "constant string"
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
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 253 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 267 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 270 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 283 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 289 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 296 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 300 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 307 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 310 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 318 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 322 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 340 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 344 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 355 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 370 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 393 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 400 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 412 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 527 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 572 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 577 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 578 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 580 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 585 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 601 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1264 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 635 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1362 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 673 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 687 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1419 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1437 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1448 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 715 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1457 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1466 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1495 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1515 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1525 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1535 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 783 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1555 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 798 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1573 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 806 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 808 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1590 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1601 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1629 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1656 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1685 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 899 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1721 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 921 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1731 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 958 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1749 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1759 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 966 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 976 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1795 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1813 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 990 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 997 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 998 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 999 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1933 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1963 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1161 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2030 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1175 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1187 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2075 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2114 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2133 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1275 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1334 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2228 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1353 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
    ConstElementPtr old = parent->get("user-context");

    // Handle already existing user context
    if (old) {
        // Check if it was a comment or a duplicate
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the comment
        user_context->set("comment", old->get("comment"));
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1386 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    user_context->set("comment", comment);

    // Handle already existing user context
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        // Check for duplicate comment
        if (old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context/comment entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the user context in the comment
        merge(user_context, old);
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2338 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2348 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2360 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1474 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2400 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2436 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2484 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2543 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2551 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2561 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2569 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1596 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2605 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2626 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2635 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2646 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2655 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2663 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2673 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2703 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2731 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2815 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2842 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2862 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2880 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2994 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3012 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3030 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1904 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3059 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3086 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3095 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3104 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3112 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1947 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3129 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3137 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1953 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3145 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3153 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3162 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1965 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3170 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1975 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3242 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3251 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 2012 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3269 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3299 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2097 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3380 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3390 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2123 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3408 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 615:
#line 2133 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3417 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3421 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -765;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     401,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,    35,    27,    44,    64,    72,
      74,    76,   109,   121,   135,   155,   164,   175,   177,   185,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,    27,    46,
      36,    49,    32,   197,    96,    39,   162,   160,    68,   233,
     -51,   346,   104,  -765,   235,   246,   249,   247,   267,  -765,
    -765,  -765,  -765,  -765,   270,  -765,   101,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,   296,   303,   319,   329,
     337,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,   339,  -765,  -765,  -765,   123,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   342,  -765,   124,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   344,   352,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   133,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   145,
    -765,  -765,  -765,  -765,  -765,   359,  -765,   363,   364,  -765,
    -765,  -765,  -765,  -765,   146,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,   301,   347,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,   365,  -765,  -765,   366,  -765,  -765,  -765,   367,
    -765,  -765,   369,   371,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,   379,   380,  -765,
    -765,  -765,  -765,   377,   372,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,   158,  -765,  -765,
    -765,   383,  -765,  -765,   385,  -765,   386,   389,  -765,  -765,
     390,   391,   400,  -765,  -765,  -765,  -765,  -765,   167,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   188,  -765,  -765,  -765,    27,
      27,  -765,   251,   407,   408,   409,   410,   411,  -765,    36,
    -765,   413,   414,   415,   261,   262,   266,   269,   272,   418,
     428,   429,   430,   431,   432,   433,   434,   435,   437,   438,
     439,   440,   286,   442,   443,    49,  -765,   445,   289,    32,
    -765,   447,   451,   452,   467,   468,   314,   316,   474,   475,
     476,   477,   197,  -765,   478,    96,  -765,   479,   325,   481,
     327,   328,    39,  -765,   484,   485,   489,   490,   491,   493,
     494,  -765,   162,  -765,   495,   496,   343,   497,   499,   501,
     345,  -765,    68,   503,   348,   349,  -765,   233,   504,   507,
     -47,  -765,   354,   512,   513,   360,   514,   368,   370,   517,
     518,   373,   374,   375,   519,   522,   346,  -765,   524,   104,
    -765,  -765,  -765,   526,   525,   530,    27,    27,    27,  -765,
     536,   552,   553,  -765,  -765,  -765,  -765,  -765,   528,   556,
     557,   558,   405,   559,   561,   562,   563,   564,   565,   566,
     567,  -765,   568,   569,  -765,   572,  -765,  -765,   573,   574,
     422,   423,   424,  -765,  -765,   260,   425,   579,   578,  -765,
     436,  -765,   441,  -765,   444,  -765,  -765,  -765,   572,   572,
     572,   446,   448,   449,   450,  -765,   453,   454,  -765,   455,
     456,   457,  -765,  -765,   458,  -765,  -765,  -765,   459,    27,
    -765,  -765,   460,   461,  -765,   462,  -765,  -765,   103,   404,
    -765,  -765,  -765,   -81,   463,  -765,   581,  -765,    27,    49,
     104,  -765,  -765,  -765,    32,   187,   187,   580,   582,   583,
    -765,  -765,  -765,   584,   -45,    27,    23,   585,   586,   -19,
      41,   195,   346,  -765,  -765,   588,   589,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   590,   511,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   593,
    -765,   190,   192,   198,  -765,  -765,  -765,  -765,   597,   599,
     601,   605,   606,  -765,   618,   619,  -765,   620,   621,   622,
    -765,   222,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
     224,  -765,   623,   624,  -765,  -765,   625,   627,  -765,  -765,
     626,   630,  -765,  -765,   628,   632,  -765,  -765,  -765,    59,
    -765,  -765,  -765,   631,  -765,  -765,  -765,   132,  -765,  -765,
    -765,  -765,   166,  -765,  -765,   633,   635,  -765,   636,   637,
     638,   639,   640,   641,   263,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,   642,   643,   644,  -765,  -765,  -765,
    -765,   264,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   265,  -765,  -765,  -765,   281,   470,  -765,
     645,   646,  -765,  -765,   647,   649,  -765,  -765,   648,   652,
    -765,  -765,   650,  -765,   308,  -765,  -765,  -765,  -765,   653,
     655,   656,   657,   412,   427,   505,   502,   506,   658,   508,
     509,   662,   510,   515,   516,   187,  -765,  -765,   197,  -765,
     580,    68,  -765,   582,   233,  -765,   583,   362,  -765,   584,
     -45,  -765,  -765,    23,  -765,    90,   585,  -765,   -51,  -765,
     586,   520,   521,   523,   527,   529,   531,   -19,  -765,   666,
     667,   532,   533,   534,    41,  -765,   668,   669,   195,  -765,
    -765,  -765,   670,   672,    96,  -765,   588,    39,  -765,   589,
     162,  -765,   590,   674,  -765,   244,   593,  -765,   299,   492,
     498,   539,  -765,  -765,  -765,  -765,  -765,   541,  -765,  -765,
     542,  -765,  -765,  -765,  -765,   282,  -765,   673,  -765,   675,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   283,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   676,   682,
    -765,  -765,  -765,  -765,   284,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   239,   544,  -765,  -765,  -765,  -765,   545,
     548,  -765,  -765,   550,   290,  -765,   293,  -765,   679,  -765,
     570,  -765,   685,  -765,  -765,  -765,  -765,  -765,   294,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,   362,  -765,   690,
    -765,    90,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   707,   571,   712,   244,  -765,
    -765,   575,  -765,   719,  -765,   577,  -765,  -765,   629,  -765,
    -765,   322,  -765,    25,   629,  -765,  -765,   713,   721,   723,
     305,  -765,  -765,  -765,  -765,  -765,  -765,   727,   591,   587,
     594,    25,  -765,   603,  -765,  -765,  -765,  -765,  -765
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   106,     9,   232,    11,
     373,    13,   397,    15,   426,    17,   298,    19,   306,    21,
     343,    23,   197,    25,   519,    27,   576,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   428,     0,   308,   345,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     574,   568,   570,   572,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   104,   118,   120,     0,     0,     0,     0,
       0,   224,   296,   335,   385,   387,   270,   170,   187,   178,
     461,   189,   208,   480,     0,   504,   517,    98,     0,    72,
      74,    75,    76,    77,    78,    81,    82,    83,    84,    86,
      85,    90,    91,    79,    80,    88,    89,    96,    97,    87,
      92,    93,    94,    95,   115,     0,   114,     0,   108,   110,
     111,   112,   113,   365,   389,   255,   257,   259,     0,     0,
     263,   261,   418,   457,   254,   236,   237,   238,   239,     0,
     234,   243,   244,   245,   248,   250,   246,   247,   240,   241,
     252,   253,   242,   249,   251,   383,   382,   379,   378,     0,
     375,   377,   380,   381,   411,     0,   414,     0,     0,   410,
     405,   404,   408,   409,     0,   399,   401,   402,   406,   407,
     403,   455,   443,   445,   447,   449,   451,   453,   442,   439,
     440,   441,     0,   429,   430,   434,   435,   432,   436,   437,
     438,   433,     0,   325,   155,     0,   329,   327,   332,     0,
     321,   322,     0,   309,   310,   312,   324,   313,   314,   315,
     331,   316,   317,   318,   319,   320,   359,     0,     0,   357,
     358,   361,   362,     0,   346,   347,   349,   350,   351,   352,
     353,   354,   355,   356,   204,   206,   201,     0,   199,   202,
     203,     0,   541,   543,     0,   546,     0,     0,   550,   554,
       0,     0,     0,   559,   566,   539,   537,   538,     0,   521,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   581,     0,   578,   580,    46,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   233,     0,     0,   374,     0,     0,     0,
       0,     0,     0,   398,     0,     0,     0,     0,     0,     0,
       0,   427,     0,   299,     0,     0,     0,     0,     0,     0,
       0,   307,     0,     0,     0,     0,   344,     0,     0,     0,
       0,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   520,     0,     0,
     577,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   503,     0,     0,    73,     0,   117,   109,     0,     0,
       0,     0,     0,   268,   269,     0,     0,     0,     0,   235,
       0,   376,     0,   413,     0,   416,   417,   400,     0,     0,
       0,     0,     0,     0,     0,   431,     0,     0,   323,     0,
       0,     0,   334,   311,     0,   363,   364,   348,     0,     0,
     200,   540,     0,     0,   545,     0,   548,   549,     0,     0,
     556,   557,   558,     0,     0,   522,     0,   579,     0,     0,
       0,   569,   571,   573,     0,     0,     0,   226,   300,   337,
      40,   386,   388,   272,     0,    47,     0,     0,   191,     0,
       0,     0,     0,    51,   116,   367,   391,   256,   258,   260,
     265,   266,   267,   264,   262,   420,     0,   384,   412,   415,
     456,   444,   446,   448,   450,   452,   454,   326,   156,   330,
     328,   333,   360,   205,   207,   542,   544,   547,   552,   553,
     551,   555,   561,   562,   563,   564,   565,   560,   567,     0,
      44,     0,     0,     0,   142,   148,   150,   152,     0,     0,
       0,     0,     0,   165,     0,     0,   168,     0,     0,     0,
     141,     0,   122,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   136,   137,   138,   139,   134,   135,   140,
       0,   230,     0,   227,   228,   304,     0,   301,   302,   341,
       0,   338,   339,   276,     0,   273,   274,   176,   177,     0,
     172,   174,   175,     0,   185,   186,   182,     0,   180,   183,
     184,   465,     0,   463,   195,     0,   192,   193,     0,     0,
       0,     0,     0,     0,     0,   210,   212,   213,   214,   215,
     216,   217,   493,   499,     0,     0,     0,   492,   489,   490,
     491,     0,   482,   484,   487,   485,   486,   488,   513,   515,
     512,   510,   511,     0,   506,   508,   509,     0,    53,   371,
       0,   368,   369,   395,     0,   392,   393,   424,     0,   421,
     422,   459,     0,   585,     0,   583,    69,   575,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   121,     0,   225,
       0,   308,   297,     0,   345,   336,     0,     0,   271,     0,
       0,   171,   188,     0,   179,   467,     0,   462,     0,   190,
       0,     0,     0,     0,     0,     0,     0,     0,   209,     0,
       0,     0,     0,     0,     0,   481,     0,     0,     0,   505,
     518,    55,     0,    54,     0,   366,     0,     0,   390,     0,
     428,   419,     0,     0,   458,     0,     0,   582,     0,     0,
       0,     0,   154,   157,   158,   159,   160,     0,   167,   161,
       0,   162,   163,   164,   123,     0,   229,     0,   303,     0,
     340,   295,   290,   292,   284,   285,   280,   281,   282,   283,
     289,   288,   291,     0,   278,   286,   293,   294,   287,   275,
     173,   181,   478,   476,   477,   473,   474,   475,     0,   468,
     469,   471,   472,   464,     0,   194,   218,   219,   220,   221,
     222,   223,   211,     0,     0,   498,   501,   502,   483,     0,
       0,   507,    52,     0,     0,   370,     0,   394,     0,   423,
       0,   599,     0,   597,   595,   589,   593,   594,     0,   587,
     591,   592,   590,   584,   144,   145,   146,   147,   143,   149,
     151,   153,   166,   169,   231,   305,   342,     0,   277,     0,
     466,     0,   196,   495,   496,   497,   494,   500,   514,   516,
      56,   372,   396,   425,   460,     0,     0,     0,     0,   586,
     279,     0,   470,     0,   596,     0,   588,   479,     0,   598,
     603,     0,   601,     0,     0,   600,   611,     0,     0,     0,
       0,   605,   607,   608,   609,   610,   602,     0,     0,     0,
       0,     0,   604,     0,   613,   614,   615,   606,   612
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,     6,  -765,   111,  -765,
    -765,  -765,  -765,  -765,  -765,   181,  -765,  -139,  -765,  -765,
    -765,   -70,  -765,  -765,  -765,   393,  -765,  -765,  -765,  -765,
     200,   376,   -72,   -58,   -56,   -55,  -765,  -765,  -765,  -765,
    -765,   196,   394,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
     199,   -23,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,    -7,  -765,  -553,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
     -31,  -544,  -765,  -765,  -765,  -765,   -24,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,   -26,  -765,  -765,  -765,   -15,
     355,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   -29,  -765,
    -765,  -765,  -765,  -765,  -765,  -764,  -765,  -765,  -765,     4,
    -765,  -765,  -765,     8,   399,  -765,  -765,  -761,  -765,  -757,
    -765,   -34,  -765,  -756,  -765,  -765,  -765,  -754,  -765,  -765,
    -765,  -765,     3,  -765,  -765,  -152,   709,  -765,  -765,  -765,
    -765,  -765,    14,  -765,  -765,  -765,    18,  -765,   378,  -765,
     -65,  -765,  -765,  -765,  -765,  -765,   -60,  -765,  -765,  -765,
    -765,  -765,    -6,  -765,  -765,  -765,    15,  -765,  -765,  -765,
      19,  -765,   381,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,   -21,  -765,  -765,  -765,   -22,   416,
    -765,  -765,   -48,  -765,   -20,  -765,  -765,  -765,  -765,  -765,
     -17,  -765,  -765,  -765,   -18,   417,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,   -16,  -765,  -765,
    -765,   -13,  -765,   402,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -748,  -765,
    -765,  -765,  -765,  -765,  -765,    10,  -765,  -765,  -765,  -138,
    -765,  -765,  -765,  -765,  -765,  -765,     9,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,     2,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,   250,   384,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,  -765,
    -765,  -765,  -765,   275,   382,  -765,  -765,  -765,   -10,  -765,
    -765,  -141,  -765,  -765,  -765,  -765,  -765,  -765,  -155,  -765,
    -765,  -169,  -765,  -765,  -765,  -765,  -765
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     551,    87,    88,    41,    68,    84,    85,   564,   728,   812,
     813,   127,    43,    70,    96,    97,    98,   333,    45,    71,
     128,   129,   130,   131,   132,   133,   134,   135,   341,    47,
      72,   157,   158,   159,   367,   160,   136,   342,   137,   343,
     631,   632,   633,   749,   928,   634,   750,   635,   751,   636,
     752,   637,   251,   405,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   758,   648,   649,   761,   138,   355,   669,
     670,   671,   672,   139,   357,   677,   678,   679,   680,   140,
     356,   141,   359,   685,   686,   687,   788,    63,    80,   287,
     288,   289,   418,   290,   419,   142,   360,   694,   695,   696,
     697,   698,   699,   700,   701,   143,   349,   652,   653,   654,
     768,    49,    73,   179,   180,   181,   373,   182,   374,   183,
     375,   184,   379,   185,   378,   573,   186,   187,   144,   354,
     664,   665,   666,   777,   863,   864,   145,   350,    57,    77,
     656,   657,   658,   771,    59,    78,   252,   253,   254,   255,
     256,   257,   258,   404,   259,   408,   260,   407,   261,   262,
     409,   263,   146,   351,   660,   661,   662,   774,    61,    79,
     273,   274,   275,   276,   277,   413,   278,   279,   280,   281,
     189,   371,   730,   731,   732,   814,    51,    74,   199,   200,
     201,   384,   147,   352,   148,   353,   192,   372,   734,   735,
     736,   817,    53,    75,   214,   215,   216,   387,   217,   218,
     389,   219,   220,   193,   380,   738,   739,   740,   820,    55,
      76,   232,   233,   234,   235,   395,   236,   396,   237,   397,
     238,   398,   239,   399,   240,   400,   241,   394,   194,   381,
     742,   823,   149,   358,   682,   683,   785,   878,   879,   880,
     881,   882,   939,   150,   361,   711,   712,   713,   799,   946,
     714,   715,   800,   716,   717,   151,   152,   363,   723,   724,
     725,   806,   726,   807,   153,   364,    65,    81,   308,   309,
     310,   311,   423,   312,   424,   313,   314,   426,   315,   316,
     317,   429,   600,   318,   430,   319,   320,   321,   322,   434,
     607,   323,   435,    99,   335,   100,   336,   101,   337,   102,
     334,    67,    82,   325,   326,   327,   438,   744,   745,   825,
     918,   919,   920,   921,   957,   922,   955,   971,   972,   973,
     980,   981,   982,   987,   983,   984,   985
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   175,   156,   174,   196,   209,   228,   708,   250,   269,
     286,   305,   676,   857,   271,   176,   858,   177,   178,   272,
     859,   861,    38,   862,   161,   190,   202,   212,   230,   868,
     264,   282,    31,   306,    32,    30,    33,   667,   284,   285,
     197,   210,   284,   285,   154,   155,    89,   602,   603,   604,
     605,    42,   162,   191,   203,   213,   231,   702,   265,   283,
     103,   307,   780,   104,   105,   781,   619,   188,   198,   211,
     229,    44,   270,   688,   689,   690,   691,   692,   693,    46,
     606,    48,   113,    50,   243,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   204,   205,   206,   207,   208,
     114,   115,   114,   115,   339,   667,   674,    94,   675,   340,
     114,   115,   244,   668,   245,   246,    52,   171,   247,   248,
     249,   116,   117,   118,   119,   120,   365,   369,    54,   114,
     115,   366,   370,   113,   244,   783,   382,   121,   784,   113,
     122,   383,    56,   703,   704,   705,   706,   123,   385,   392,
     195,   114,   115,   386,   393,   124,   125,   114,   115,   126,
     976,   420,    58,   977,   978,   979,   421,   872,    90,   786,
     436,    60,   787,   857,   171,   437,   858,    91,    92,    93,
     859,   861,    62,   862,    64,    34,    35,    36,    37,   868,
      94,   439,    66,   365,    94,   439,   440,    94,   746,    94,
     747,   369,   112,   614,    86,   113,   748,    94,   615,   616,
     617,   618,   619,   620,   621,   622,   623,   624,   625,   626,
     627,   628,   629,   114,   115,   765,    94,   765,   598,   599,
     766,   244,   767,   106,   107,   108,   109,   324,   221,   676,
     113,   328,   222,   223,   224,   225,   226,   227,    94,   329,
     163,   708,   164,   330,    94,   331,   114,   115,   114,   115,
     165,   166,   167,   168,   169,   170,   797,   804,   808,    95,
     332,   798,   805,   809,   338,   171,   172,   244,   266,   245,
     246,   267,   268,   173,   436,   382,   937,   420,   244,   810,
     934,   938,   942,   385,   114,   115,   392,   958,   951,   156,
     344,   952,   959,   718,   719,   114,   115,   345,   991,   401,
     175,   826,   174,   992,   827,   196,   924,   925,   926,   927,
      94,   161,   209,   346,   176,   974,   177,   178,   975,   570,
     571,   572,   228,   347,   190,   441,   442,   202,   943,   944,
     945,   348,   250,   362,   212,    94,   368,   269,   376,   162,
     402,   197,   271,    94,   230,    94,   377,   272,   210,   580,
     581,   582,   191,   388,   264,   203,   305,   390,   391,   282,
     406,   410,   213,   403,   412,   417,   188,   411,   911,   198,
     912,   913,   231,   414,   415,   416,   211,   422,   306,   425,
     427,    94,   265,   428,   431,   432,   229,   283,   106,   107,
     108,   109,    94,   111,   433,   113,   244,   114,   115,   443,
     270,   444,   445,   446,   447,   448,   307,   450,   451,   452,
     453,   454,   458,   114,   115,   455,   166,   167,   456,   169,
     170,   457,   459,   460,   461,   462,   463,   464,   465,   466,
     171,   467,   468,   469,   470,   471,   472,   473,   173,   475,
     476,   478,   541,   542,   543,   479,   480,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   481,   482,   483,   156,   630,   630,   484,   485,   486,
     487,   488,   490,   492,   493,   494,   495,   496,   498,   499,
     707,   720,   305,   500,   501,   502,   161,   503,   504,   506,
     507,   509,   508,   510,    94,   511,   512,   514,   518,   515,
     516,   519,   709,   721,   306,   521,   522,   523,   525,   524,
      94,   528,   529,   533,   162,   594,   534,   526,   536,   527,
     538,   601,   539,   547,   530,   531,   532,   540,   638,   638,
     710,   722,   307,   544,   610,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   545,
     546,   548,   549,   552,   553,    32,   554,   555,   556,   557,
     558,   832,   550,   559,   560,   561,   562,   563,   565,   566,
     567,   568,   569,   574,   575,   576,   609,   651,   833,   655,
     659,   663,   681,   684,   577,   729,   733,   737,   741,   578,
     743,   753,   579,   754,   583,   755,   584,   585,   586,   756,
     757,   587,   588,   589,   590,   591,   592,   593,   595,   596,
     597,   608,   759,   760,   762,   763,   764,   770,   811,   769,
     773,   772,   775,   776,   778,   779,   970,   782,   790,   789,
     791,   792,   793,   794,   795,   796,   801,   802,   803,   816,
     929,   815,   819,   818,   821,   822,   930,   828,   824,   829,
     830,   831,   837,   835,   834,   836,   840,   838,   839,   841,
     893,   894,   899,   900,   842,   903,   902,   843,   910,   886,
     887,   935,   888,   936,   940,   941,   889,   953,   890,   956,
     891,   895,   896,   897,   961,   630,   175,   931,   174,   932,
     933,   250,   947,   948,   269,   852,   949,   851,   950,   271,
     176,   963,   177,   178,   272,   873,   965,   988,   286,   853,
     190,   854,   855,   264,   968,   989,   282,   990,   954,   866,
     964,   993,   449,   967,   707,   969,   673,   876,   720,   611,
     613,   474,   844,   860,   196,   650,   995,   209,   191,   870,
     228,   265,   994,   996,   283,   914,   709,   867,   638,   871,
     721,   998,   188,   477,   885,   877,   202,   270,   892,   212,
     856,   865,   230,   884,   846,   520,   845,   916,   874,   875,
     197,   489,   869,   210,   710,   960,   242,   848,   722,   847,
     513,   850,   904,   849,   203,   905,   883,   213,   517,   906,
     231,   491,   907,   962,   505,   917,   909,   908,   198,   497,
     901,   211,   727,   898,   229,   612,   923,   966,   915,   986,
     535,   537,   997,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   852,     0,   851,     0,     0,
       0,   873,     0,     0,     0,     0,     0,     0,     0,   853,
       0,   854,   855,     0,     0,     0,     0,     0,   914,   866,
       0,     0,     0,   876,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   860,     0,     0,     0,     0,     0,     0,
     916,     0,     0,     0,     0,     0,     0,   867,     0,     0,
       0,   877,     0,     0,     0,     0,     0,     0,     0,     0,
     856,   865,     0,     0,   874,   875,     0,     0,   917,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   915
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    73,    72,    73,    74,    75,    76,   560,    78,    79,
      80,    81,   556,   777,    79,    73,   777,    73,    73,    79,
     777,   777,    16,   777,    72,    73,    74,    75,    76,   777,
      78,    79,     5,    81,     7,     0,     9,    82,    89,    90,
      74,    75,    89,    90,    12,    13,    10,   128,   129,   130,
     131,     7,    72,    73,    74,    75,    76,    16,    78,    79,
      11,    81,     3,    14,    15,     6,    25,    73,    74,    75,
      76,     7,    79,    92,    93,    94,    95,    96,    97,     7,
     161,     7,    43,     7,    16,    36,    37,    38,    39,    40,
      41,    42,    43,    61,    62,    56,    57,    58,    59,    60,
      61,    62,    61,    62,     3,    82,    83,   158,    85,     8,
      61,    62,    44,   158,    46,    47,     7,    78,    50,    51,
      52,    72,    73,    74,    75,    76,     3,     3,     7,    61,
      62,     8,     8,    43,    44,     3,     3,    88,     6,    43,
      91,     8,     7,   102,   103,   104,   105,    98,     3,     3,
      54,    61,    62,     8,     8,   106,   107,    61,    62,   110,
     135,     3,     7,   138,   139,   140,     8,    77,   132,     3,
       3,     7,     6,   937,    78,     8,   937,   141,   142,   143,
     937,   937,     7,   937,     7,   158,   159,   160,   161,   937,
     158,     3,     7,     3,   158,     3,     8,   158,     8,   158,
       8,     3,    42,    16,   158,    43,     8,   158,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    61,    62,     3,   158,     3,   125,   126,
       8,    44,     8,    36,    37,    38,    39,   133,    76,   783,
      43,     6,    80,    81,    82,    83,    84,    85,   158,     3,
      53,   804,    55,     4,   158,     8,    61,    62,    61,    62,
      63,    64,    65,    66,    67,    68,     3,     3,     3,   339,
       3,     8,     8,     8,     4,    78,    79,    44,    45,    46,
      47,    48,    49,    86,     3,     3,     3,     3,    44,     8,
       8,     8,     8,     3,    61,    62,     3,     3,     8,   369,
       4,     8,     8,   108,   109,    61,    62,     4,     3,     8,
     382,     3,   382,     8,     6,   385,    17,    18,    19,    20,
     158,   369,   392,     4,   382,     3,   382,   382,     6,    69,
      70,    71,   402,     4,   382,   329,   330,   385,    99,   100,
     101,     4,   412,     4,   392,   158,     4,   417,     4,   369,
       3,   385,   417,   158,   402,   158,     4,   417,   392,   498,
     499,   500,   382,     4,   412,   385,   436,     4,     4,   417,
       4,     4,   392,     8,     3,     3,   382,     8,   134,   385,
     136,   137,   402,     4,     4,     8,   392,     4,   436,     4,
       4,   158,   412,     4,     4,     4,   402,   417,    36,    37,
      38,    39,   158,    41,     4,    43,    44,    61,    62,   158,
     417,     4,     4,     4,     4,     4,   436,     4,     4,     4,
     159,   159,     4,    61,    62,   159,    64,    65,   159,    67,
      68,   159,     4,     4,     4,     4,     4,     4,     4,     4,
      78,     4,     4,     4,     4,   159,     4,     4,    86,     4,
     161,     4,   446,   447,   448,     4,     4,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     4,     4,   159,   544,   545,   546,   161,     4,     4,
       4,     4,     4,     4,   159,     4,   159,   159,     4,     4,
     560,   561,   562,     4,     4,     4,   544,     4,     4,     4,
       4,     4,   159,     4,   158,     4,   161,     4,     4,   161,
     161,     4,   560,   561,   562,   161,     4,     4,     4,   159,
     158,     4,     4,     4,   544,   519,     4,   159,     4,   159,
       4,   127,     7,     5,   161,   161,   161,     7,   545,   546,
     560,   561,   562,     7,   538,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     7,
       7,     5,     5,   158,     5,     7,     5,     5,     5,     5,
       5,   159,   461,     7,     7,     7,     7,     5,     5,     5,
     158,   158,   158,   158,     5,     7,     5,     7,   161,     7,
       7,     7,     7,     7,   158,     7,     7,     7,    87,   158,
       7,     4,   158,     4,   158,     4,   158,   158,   158,     4,
       4,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,     4,     4,     4,     4,     4,     3,   158,     6,
       3,     6,     6,     3,     6,     3,     7,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     158,     6,     3,     6,     6,     3,   158,     4,     8,     4,
       4,     4,     4,   161,   159,   159,     4,   159,   159,   159,
       4,     4,     4,     4,   159,     3,     6,   161,     4,   159,
     159,     8,   159,     8,     8,     3,   159,     8,   159,     4,
     159,   159,   159,   159,     4,   765,   768,   158,   768,   158,
     158,   771,   158,   158,   774,   777,   158,   777,   158,   774,
     768,     4,   768,   768,   774,   785,     4,     4,   788,   777,
     768,   777,   777,   771,     5,     4,   774,     4,   158,   777,
     159,     4,   339,   158,   804,   158,   555,   785,   808,   539,
     544,   365,   765,   777,   814,   546,   159,   817,   768,   780,
     820,   771,   161,   159,   774,   825,   804,   777,   765,   783,
     808,   158,   768,   369,   790,   785,   814,   774,   797,   817,
     777,   777,   820,   788,   770,   420,   768,   825,   785,   785,
     814,   382,   779,   817,   804,   937,    77,   773,   808,   771,
     412,   776,   814,   774,   814,   816,   786,   817,   417,   817,
     820,   385,   819,   941,   402,   825,   822,   820,   814,   392,
     808,   817,   562,   804,   820,   540,   826,   958,   825,   974,
     436,   439,   991,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   937,    -1,   937,    -1,    -1,
      -1,   941,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   937,
      -1,   937,   937,    -1,    -1,    -1,    -1,    -1,   958,   937,
      -1,    -1,    -1,   941,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   937,    -1,    -1,    -1,    -1,    -1,    -1,
     958,    -1,    -1,    -1,    -1,    -1,    -1,   937,    -1,    -1,
      -1,   941,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     937,   937,    -1,    -1,   941,   941,    -1,    -1,   958,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   958
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
       0,     5,     7,     9,   158,   159,   160,   161,   178,   179,
     180,   185,     7,   194,     7,   200,     7,   211,     7,   293,
       7,   368,     7,   384,     7,   401,     7,   320,     7,   326,
       7,   350,     7,   269,     7,   458,     7,   493,   186,   181,
     195,   201,   212,   294,   369,   385,   402,   321,   327,   351,
     270,   459,   494,   178,   187,   188,   158,   183,   184,    10,
     132,   141,   142,   143,   158,   193,   196,   197,   198,   485,
     487,   489,   491,    11,    14,    15,    36,    37,    38,    39,
      40,    41,    42,    43,    61,    62,    72,    73,    74,    75,
      76,    88,    91,    98,   106,   107,   110,   193,   202,   203,
     204,   205,   206,   207,   208,   209,   218,   220,   249,   255,
     261,   263,   277,   287,   310,   318,   344,   374,   376,   424,
     435,   447,   448,   456,    12,    13,   193,   213,   214,   215,
     217,   374,   376,    53,    55,    63,    64,    65,    66,    67,
      68,    78,    79,    86,   193,   204,   205,   206,   207,   295,
     296,   297,   299,   301,   303,   305,   308,   309,   344,   362,
     374,   376,   378,   395,   420,    54,   193,   303,   344,   370,
     371,   372,   374,   376,    56,    57,    58,    59,    60,   193,
     303,   344,   374,   376,   386,   387,   388,   390,   391,   393,
     394,    76,    80,    81,    82,    83,    84,    85,   193,   344,
     374,   376,   403,   404,   405,   406,   408,   410,   412,   414,
     416,   418,   318,    16,    44,    46,    47,    50,    51,    52,
     193,   234,   328,   329,   330,   331,   332,   333,   334,   336,
     338,   340,   341,   343,   374,   376,    45,    48,    49,   193,
     234,   332,   338,   352,   353,   354,   355,   356,   358,   359,
     360,   361,   374,   376,    89,    90,   193,   271,   272,   273,
     275,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   193,   374,   376,   460,   461,
     462,   463,   465,   467,   468,   470,   471,   472,   475,   477,
     478,   479,   480,   483,   133,   495,   496,   497,     6,     3,
       4,     8,     3,   199,   492,   486,   488,   490,     4,     3,
       8,   210,   219,   221,     4,     4,     4,     4,     4,   288,
     319,   345,   375,   377,   311,   250,   262,   256,   425,   264,
     278,   436,     4,   449,   457,     3,     8,   216,     4,     3,
       8,   363,   379,   298,   300,   302,     4,     4,   306,   304,
     396,   421,     3,     8,   373,     3,     8,   389,     4,   392,
       4,     4,     3,     8,   419,   407,   409,   411,   413,   415,
     417,     8,     3,     8,   335,   235,     4,   339,   337,   342,
       4,     8,     3,   357,     4,     4,     8,     3,   274,   276,
       3,     8,     4,   464,   466,     4,   469,     4,     4,   473,
     476,     4,     4,     4,   481,   484,     3,     8,   498,     3,
       8,   178,   178,   158,     4,     4,     4,     4,     4,   197,
       4,     4,     4,   159,   159,   159,   159,   159,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   159,     4,     4,   203,     4,   161,   214,     4,     4,
       4,     4,     4,   159,   161,     4,     4,     4,     4,   296,
       4,   371,     4,   159,     4,   159,   159,   387,     4,     4,
       4,     4,     4,     4,     4,   405,     4,     4,   159,     4,
       4,     4,   161,   330,     4,   161,   161,   354,     4,     4,
     272,   161,     4,     4,   159,     4,   159,   159,     4,     4,
     161,   161,   161,     4,     4,   461,     4,   496,     4,     7,
       7,   178,   178,   178,     7,     7,     7,     5,     5,     5,
     180,   182,   158,     5,     5,     5,     5,     5,     5,     7,
       7,     7,     7,     5,   189,     5,     5,   158,   158,   158,
      69,    70,    71,   307,   158,     5,     7,   158,   158,   158,
     189,   189,   189,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   178,   158,   158,   158,   125,   126,
     474,   127,   128,   129,   130,   131,   161,   482,   158,     5,
     178,   202,   495,   213,    16,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     193,   222,   223,   224,   227,   229,   231,   233,   234,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   246,   247,
     222,     7,   289,   290,   291,     7,   322,   323,   324,     7,
     346,   347,   348,     7,   312,   313,   314,    82,   158,   251,
     252,   253,   254,   187,    83,    85,   253,   257,   258,   259,
     260,     7,   426,   427,     7,   265,   266,   267,    92,    93,
      94,    95,    96,    97,   279,   280,   281,   282,   283,   284,
     285,   286,    16,   102,   103,   104,   105,   193,   236,   374,
     376,   437,   438,   439,   442,   443,   445,   446,   108,   109,
     193,   374,   376,   450,   451,   452,   454,   460,   190,     7,
     364,   365,   366,     7,   380,   381,   382,     7,   397,   398,
     399,    87,   422,     7,   499,   500,     8,     8,     8,   225,
     228,   230,   232,     4,     4,     4,     4,     4,   245,     4,
       4,   248,     4,     4,     4,     3,     8,     8,   292,     6,
       3,   325,     6,     3,   349,     6,     3,   315,     6,     3,
       3,     6,     6,     3,     6,   428,     3,     6,   268,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   440,
     444,     4,     4,     4,     3,     8,   453,   455,     3,     8,
       8,   158,   191,   192,   367,     6,     3,   383,     6,     3,
     400,     6,     3,   423,     8,   501,     3,     6,     4,     4,
       4,     4,   159,   161,   159,   161,   159,     4,   159,   159,
       4,   159,   159,   161,   223,   295,   291,   328,   324,   352,
     348,   193,   204,   205,   206,   207,   234,   287,   299,   301,
     303,   305,   309,   316,   317,   344,   374,   376,   420,   314,
     252,   258,    77,   193,   234,   344,   374,   376,   429,   430,
     431,   432,   433,   427,   271,   267,   159,   159,   159,   159,
     159,   159,   280,     4,     4,   159,   159,   159,   438,     4,
       4,   451,     6,     3,   370,   366,   386,   382,   403,   399,
       4,   134,   136,   137,   193,   234,   374,   376,   502,   503,
     504,   505,   507,   500,    17,    18,    19,    20,   226,   158,
     158,   158,   158,   158,     8,     8,     8,     3,     8,   434,
       8,     3,     8,    99,   100,   101,   441,   158,   158,   158,
     158,     8,     8,     8,   158,   508,     4,   506,     3,     8,
     317,     4,   431,     4,   159,     4,   503,   158,     5,   158,
       7,   509,   510,   511,     3,     6,   135,   138,   139,   140,
     512,   513,   514,   516,   517,   518,   510,   515,     4,     4,
       4,     3,     8,     4,   161,   159,   159,   513,   158
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   162,   164,   163,   165,   163,   166,   163,   167,   163,
     168,   163,   169,   163,   170,   163,   171,   163,   172,   163,
     173,   163,   174,   163,   175,   163,   176,   163,   177,   163,
     178,   178,   178,   178,   178,   178,   178,   179,   181,   180,
     182,   183,   183,   184,   184,   186,   185,   187,   187,   188,
     188,   190,   189,   191,   191,   192,   192,   193,   195,   194,
     196,   196,   197,   197,   197,   197,   197,   197,   199,   198,
     201,   200,   202,   202,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   204,
     205,   206,   207,   208,   210,   209,   212,   211,   213,   213,
     214,   214,   214,   214,   214,   216,   215,   217,   219,   218,
     221,   220,   222,   222,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   225,   224,   226,   226,   226,   226,   228,   227,
     230,   229,   232,   231,   233,   235,   234,   236,   237,   238,
     239,   240,   241,   242,   243,   245,   244,   246,   248,   247,
     250,   249,   251,   251,   252,   252,   253,   254,   256,   255,
     257,   257,   258,   258,   258,   259,   260,   262,   261,   264,
     263,   265,   265,   266,   266,   268,   267,   270,   269,   271,
     271,   271,   272,   272,   274,   273,   276,   275,   278,   277,
     279,   279,   280,   280,   280,   280,   280,   280,   281,   282,
     283,   284,   285,   286,   288,   287,   289,   289,   290,   290,
     292,   291,   294,   293,   295,   295,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   298,   297,   300,   299,   302,
     301,   304,   303,   306,   305,   307,   307,   307,   308,   309,
     311,   310,   312,   312,   313,   313,   315,   314,   316,   316,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   319,   318,   321,   320,
     322,   322,   323,   323,   325,   324,   327,   326,   328,   328,
     329,   329,   330,   330,   330,   330,   330,   330,   330,   330,
     330,   330,   331,   332,   333,   335,   334,   337,   336,   339,
     338,   340,   342,   341,   343,   345,   344,   346,   346,   347,
     347,   349,   348,   351,   350,   352,   352,   353,   353,   354,
     354,   354,   354,   354,   354,   354,   354,   354,   355,   357,
     356,   358,   359,   360,   361,   363,   362,   364,   364,   365,
     365,   367,   366,   369,   368,   370,   370,   371,   371,   371,
     371,   371,   371,   373,   372,   375,   374,   377,   376,   379,
     378,   380,   380,   381,   381,   383,   382,   385,   384,   386,
     386,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   389,   388,   390,   392,   391,   393,   394,   396,   395,
     397,   397,   398,   398,   400,   399,   402,   401,   403,   403,
     404,   404,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   407,   406,   409,   408,   411,   410,   413,
     412,   415,   414,   417,   416,   419,   418,   421,   420,   423,
     422,   425,   424,   426,   426,   428,   427,   429,   429,   430,
     430,   431,   431,   431,   431,   431,   431,   432,   434,   433,
     436,   435,   437,   437,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   440,   439,   441,   441,   441,   442,   444,
     443,   445,   446,   447,   449,   448,   450,   450,   451,   451,
     451,   451,   451,   453,   452,   455,   454,   457,   456,   459,
     458,   460,   460,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     462,   464,   463,   466,   465,   467,   469,   468,   470,   471,
     473,   472,   474,   474,   476,   475,   477,   478,   479,   481,
     480,   482,   482,   482,   482,   482,   484,   483,   486,   485,
     488,   487,   490,   489,   492,   491,   494,   493,   495,   495,
     496,   498,   497,   499,   499,   501,   500,   502,   502,   503,
     503,   503,   503,   503,   503,   503,   504,   506,   505,   508,
     507,   509,   509,   511,   510,   512,   512,   513,   513,   513,
     513,   515,   514,   516,   517,   518
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
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
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"keyspace\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
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
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp6_object", "$@19", "sub_dhcp6",
  "$@20", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@21",
  "sub_interfaces6", "$@22", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@23", "re_detect",
  "lease_database", "$@24", "hosts_database", "$@25",
  "database_map_params", "database_map_param", "database_type", "$@26",
  "db_type", "user", "$@27", "password", "$@28", "host", "$@29", "port",
  "name", "$@30", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@31", "max_reconnect_tries", "keyspace", "$@32",
  "mac_sources", "$@33", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@34",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@35",
  "hooks_libraries", "$@36", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@37",
  "sub_hooks_library", "$@38", "hooks_params", "hooks_param", "library",
  "$@39", "parameters", "$@40", "expired_leases_processing", "$@41",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@42",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@43",
  "sub_subnet6", "$@44", "subnet6_params", "subnet6_param", "subnet",
  "$@45", "interface", "$@46", "interface_id", "$@47", "client_class",
  "$@48", "reservation_mode", "$@49", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@50", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@51",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@52", "sub_option_def_list", "$@53", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@54",
  "sub_option_def", "$@55", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@56",
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
  "$@68", "comment", "$@69", "pd_pools_list", "$@70",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@71", "sub_pd_pool", "$@72", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@73", "pd_prefix_len", "excluded_prefix", "$@74",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@75",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@76", "sub_reservation", "$@77", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@78", "prefixes", "$@79", "duid", "$@80", "hw_address", "$@81",
  "hostname", "$@82", "flex_id_value", "$@83",
  "reservation_client_classes", "$@84", "relay", "$@85", "relay_map",
  "$@86", "client_classes", "$@87", "client_classes_list",
  "client_class_entry", "$@88", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@89", "server_id", "$@90",
  "server_id_params", "server_id_param", "server_id_type", "$@91",
  "duid_type", "htype", "identifier", "$@92", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@93", "control_socket_params",
  "control_socket_param", "socket_type", "$@94", "socket_name", "$@95",
  "dhcp_ddns", "$@96", "sub_dhcp_ddns", "$@97", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@98",
  "server_ip", "$@99", "server_port", "sender_ip", "$@100", "sender_port",
  "max_queue_size", "ncr_protocol", "$@101", "ncr_protocol_value",
  "ncr_format", "$@102", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@103",
  "replace_client_name_value", "generated_prefix", "$@104",
  "dhcp4_json_object", "$@105", "dhcpddns_json_object", "$@106",
  "control_agent_json_object", "$@107", "logging_object", "$@108",
  "sub_logging", "$@109", "logging_params", "logging_param", "loggers",
  "$@110", "loggers_entries", "logger_entry", "$@111", "logger_params",
  "logger_param", "debuglevel", "severity", "$@112", "output_options_list",
  "$@113", "output_options_list_content", "output_entry", "$@114",
  "output_params_list", "output_params", "output", "$@115", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   243,   243,   243,   244,   244,   245,   245,   246,   246,
     247,   247,   248,   248,   249,   249,   250,   250,   251,   251,
     252,   252,   253,   253,   254,   254,   255,   255,   256,   256,
     264,   265,   266,   267,   268,   269,   270,   273,   278,   278,
     289,   292,   293,   296,   300,   307,   307,   314,   315,   318,
     322,   329,   329,   336,   337,   340,   344,   355,   365,   365,
     380,   381,   385,   386,   387,   388,   389,   390,   393,   393,
     408,   408,   417,   418,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   450,
     455,   460,   465,   470,   475,   475,   486,   486,   495,   496,
     499,   500,   501,   502,   503,   506,   506,   516,   522,   522,
     534,   534,   546,   547,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   570,   570,   577,   578,   579,   580,   583,   583,
     591,   591,   599,   599,   607,   612,   612,   620,   625,   630,
     635,   640,   645,   650,   655,   660,   660,   668,   673,   673,
     682,   682,   692,   693,   696,   697,   700,   705,   710,   710,
     720,   721,   724,   725,   726,   729,   734,   741,   741,   751,
     751,   761,   762,   765,   766,   769,   769,   779,   779,   789,
     790,   791,   794,   795,   798,   798,   806,   806,   814,   814,
     825,   826,   829,   830,   831,   832,   833,   834,   837,   842,
     847,   852,   857,   862,   870,   870,   883,   884,   887,   888,
     895,   895,   921,   921,   932,   933,   937,   938,   939,   940,
     941,   942,   943,   944,   945,   946,   947,   948,   949,   950,
     951,   952,   953,   954,   955,   958,   958,   966,   966,   974,
     974,   982,   982,   990,   990,   997,   998,   999,  1002,  1007,
    1015,  1015,  1026,  1027,  1031,  1032,  1035,  1035,  1043,  1044,
    1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,
    1057,  1058,  1059,  1060,  1061,  1062,  1069,  1069,  1082,  1082,
    1091,  1092,  1095,  1096,  1101,  1101,  1116,  1116,  1130,  1131,
    1134,  1135,  1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,
    1146,  1147,  1150,  1152,  1157,  1159,  1159,  1167,  1167,  1175,
    1175,  1183,  1185,  1185,  1193,  1202,  1202,  1214,  1215,  1220,
    1221,  1226,  1226,  1238,  1238,  1250,  1251,  1256,  1257,  1262,
    1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1273,  1275,
    1275,  1283,  1285,  1287,  1292,  1300,  1300,  1312,  1313,  1316,
    1317,  1320,  1320,  1330,  1330,  1339,  1340,  1343,  1344,  1345,
    1346,  1347,  1348,  1351,  1351,  1359,  1359,  1384,  1384,  1414,
    1414,  1426,  1427,  1430,  1431,  1434,  1434,  1446,  1446,  1458,
    1459,  1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,  1470,
    1471,  1474,  1474,  1482,  1487,  1487,  1495,  1500,  1508,  1508,
    1518,  1519,  1522,  1523,  1526,  1526,  1535,  1535,  1544,  1545,
    1548,  1549,  1553,  1554,  1555,  1556,  1557,  1558,  1559,  1560,
    1561,  1562,  1563,  1566,  1566,  1576,  1576,  1586,  1586,  1594,
    1594,  1602,  1602,  1610,  1610,  1618,  1618,  1631,  1631,  1641,
    1641,  1652,  1652,  1662,  1663,  1666,  1666,  1676,  1677,  1680,
    1681,  1684,  1685,  1686,  1687,  1688,  1689,  1692,  1694,  1694,
    1705,  1705,  1717,  1718,  1721,  1722,  1723,  1724,  1725,  1726,
    1727,  1728,  1729,  1732,  1732,  1739,  1740,  1741,  1744,  1749,
    1749,  1757,  1762,  1769,  1776,  1776,  1786,  1787,  1790,  1791,
    1792,  1793,  1794,  1797,  1797,  1805,  1805,  1815,  1815,  1827,
    1827,  1837,  1838,  1841,  1842,  1843,  1844,  1845,  1846,  1847,
    1848,  1849,  1850,  1851,  1852,  1853,  1854,  1855,  1856,  1857,
    1860,  1865,  1865,  1873,  1873,  1881,  1886,  1886,  1894,  1899,
    1904,  1904,  1912,  1913,  1916,  1916,  1924,  1929,  1934,  1939,
    1939,  1947,  1950,  1953,  1956,  1959,  1965,  1965,  1975,  1975,
    1982,  1982,  1989,  1989,  2002,  2002,  2012,  2012,  2023,  2024,
    2028,  2032,  2032,  2044,  2045,  2049,  2049,  2057,  2058,  2061,
    2062,  2063,  2064,  2065,  2066,  2067,  2070,  2075,  2075,  2083,
    2083,  2093,  2094,  2097,  2097,  2105,  2106,  2109,  2110,  2111,
    2112,  2115,  2115,  2123,  2128,  2133
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
#line 4653 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2138 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
