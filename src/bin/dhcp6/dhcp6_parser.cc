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
      case 174: // value
      case 178: // map_value
      case 228: // db_type
      case 304: // hr_mode
      case 438: // duid_type
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 157: // "boolean"
        value.move< bool > (that.value);
        break;

      case 156: // "floating point"
        value.move< double > (that.value);
        break;

      case 155: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 154: // "constant string"
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
      case 174: // value
      case 178: // map_value
      case 228: // db_type
      case 304: // hr_mode
      case 438: // duid_type
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 157: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 156: // "floating point"
        value.copy< double > (that.value);
        break;

      case 155: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 154: // "constant string"
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
            case 154: // "constant string"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 155: // "integer"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 156: // "floating point"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 157: // "boolean"

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 174: // value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 178: // map_value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 228: // db_type

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 304: // hr_mode

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 438: // duid_type

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 471: // ncr_protocol_value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 479: // replace_client_name_value

#line 230 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 174: // value
      case 178: // map_value
      case 228: // db_type
      case 304: // hr_mode
      case 438: // duid_type
      case 471: // ncr_protocol_value
      case 479: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 157: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 156: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 155: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 154: // "constant string"
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
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 252 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 266 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 269 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 274 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 285 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 292 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 296 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 303 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 306 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 314 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 318 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 327 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 336 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 340 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 351 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 361 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 366 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 389 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 404 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 408 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 452 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 467 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 472 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 483 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 519 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 524 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 536 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 543 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1171 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 548 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1180 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 590 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 598 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1229 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 599 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 600 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 603 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 619 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 627 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1304 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1322 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 645 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1358 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 660 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1376 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 668 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 682 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1443 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 710 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1452 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 736 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1481 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1501 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1520 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 768 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 774 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1540 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 778 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1576 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1585 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 814 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 832 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1624 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1633 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 847 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1642 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1660 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1671 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 894 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 1716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 916 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1736 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 953 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 969 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1780 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 971 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1798 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 987 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 992 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1831 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 993 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 994 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1010 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1030 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1891 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1910 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1919 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1968 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1156 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2043 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1180 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2051 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2061 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2070 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1197 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1221 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1225 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1233 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2119 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2136 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2204 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2231 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1348 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1356 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2276 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1381 "dhcp6_parser.yy" // lalr1.cc:859
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
#line 2313 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2343 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2395 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2404 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1482 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2451 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2479 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2489 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2509 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1566 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2529 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2538 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2546 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2556 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2708 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2737 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1705 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2748 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2756 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1729 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2765 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2777 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2783 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2792 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2810 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2819 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2828 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1764 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2837 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2865 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2883 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1815 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2944 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1868 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3007 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3016 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3025 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1899 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3042 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1907 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1908 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3054 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3062 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3072 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1942 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1945 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3132 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1951 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3165 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1962 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3192 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1979 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1984 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1997 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 2007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3256 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3264 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3294 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2048 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3302 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3329 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3340 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2083 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3349 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3359 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2096 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3367 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2112 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2118 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 613:
#line 2123 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 614:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3412 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3416 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -759;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     312,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,    41,    40,    27,    37,    39,
      55,   102,   116,   139,   143,   162,   169,   216,   230,   266,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,    40,    36,
      19,    49,    38,   217,   185,    18,    87,   231,    82,   176,
     -46,   441,   153,  -759,   294,   290,   327,   321,   331,  -759,
    -759,  -759,  -759,  -759,   334,  -759,    86,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,   337,   338,   342,
     347,   349,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,   354,  -759,  -759,  -759,    90,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,   357,  -759,   108,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
     358,   360,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,   124,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,   145,  -759,  -759,  -759,  -759,  -759,   362,  -759,   366,
     370,  -759,  -759,  -759,  -759,  -759,   146,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,   365,   374,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,   371,  -759,  -759,   376,  -759,  -759,
    -759,   382,  -759,  -759,   379,   386,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,   388,
     389,  -759,  -759,  -759,  -759,   391,   387,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,   167,
    -759,  -759,  -759,   390,  -759,  -759,   392,  -759,   393,   401,
    -759,  -759,   403,   406,   407,  -759,  -759,  -759,  -759,  -759,
     183,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,   190,  -759,  -759,
    -759,    40,    40,  -759,   258,   409,   410,   411,   412,   413,
    -759,    19,  -759,   414,   416,   417,   418,   268,   269,   270,
     273,   276,   430,   431,   432,   433,   434,   435,   440,   442,
     443,   444,   445,   446,   462,   313,   463,   465,    49,  -759,
     466,   288,    38,  -759,   467,   468,   470,   471,   472,   322,
     323,   475,   477,   478,   479,   217,  -759,   480,   185,  -759,
     481,   332,   482,   333,   335,    18,  -759,   485,   487,   488,
     489,   490,   497,   498,  -759,    87,  -759,   499,   500,   350,
     502,   503,   504,   352,  -759,    82,   506,   355,   356,  -759,
     176,   507,   511,   129,  -759,   359,   516,   517,   367,   520,
     372,   375,   521,   522,   377,   378,   380,   525,   527,   441,
    -759,   528,   153,  -759,  -759,  -759,   532,   531,   533,    40,
      40,    40,  -759,   534,   535,   536,   539,  -759,  -759,  -759,
    -759,  -759,   557,   558,   559,   560,   385,   561,   563,   564,
     565,   566,   567,   568,   569,  -759,   570,   571,  -759,   574,
    -759,  -759,   575,   576,   419,   420,   428,  -759,  -759,    95,
     429,   579,   578,  -759,   436,  -759,   437,  -759,   438,  -759,
    -759,  -759,   574,   574,   574,   439,   447,   448,   449,  -759,
     450,   451,  -759,   452,   453,   454,  -759,  -759,   455,  -759,
    -759,  -759,   456,    40,  -759,  -759,   457,   458,  -759,   459,
    -759,  -759,   198,   464,  -759,  -759,  -759,   -22,   460,  -759,
     581,  -759,    40,    49,   153,  -759,  -759,  -759,    38,   182,
     182,   582,   587,   589,   590,  -759,  -759,  -759,   591,   -40,
      40,    34,   592,   593,   215,    84,    33,   441,  -759,  -759,
     608,   609,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
     610,   505,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,   611,  -759,   222,   223,   236,  -759,
    -759,  -759,  -759,   615,   616,   617,   618,   619,  -759,  -759,
    -759,   237,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,   250,  -759,   620,   562,  -759,
    -759,   621,   622,  -759,  -759,   623,   625,  -759,  -759,   624,
     628,  -759,  -759,   626,   630,  -759,  -759,  -759,    94,  -759,
    -759,  -759,   629,  -759,  -759,  -759,   128,  -759,  -759,  -759,
    -759,   251,  -759,  -759,   631,   633,  -759,   634,   635,   636,
     637,   638,   639,   252,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,   640,   641,   642,  -759,  -759,  -759,  -759,
     262,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,   264,  -759,  -759,  -759,   281,   493,  -759,   643,
     645,  -759,  -759,   644,   648,  -759,  -759,   646,   650,  -759,
    -759,   647,  -759,   291,  -759,  -759,  -759,  -759,   652,   653,
     654,   655,   469,   508,   509,   510,   513,   656,   657,   182,
    -759,  -759,   182,  -759,   582,   217,  -759,   587,    82,  -759,
     589,   176,  -759,   590,   369,  -759,   591,   -40,  -759,  -759,
      34,  -759,   189,   592,  -759,   -46,  -759,   593,   514,   515,
     518,   519,   523,   524,   215,  -759,   658,   659,   526,   529,
     530,    84,  -759,   662,   667,    33,  -759,  -759,  -759,   666,
     651,   185,  -759,   608,    18,  -759,   609,    87,  -759,   610,
     671,  -759,   131,   611,  -759,    59,   537,   538,   540,  -759,
    -759,  -759,  -759,  -759,   542,   543,  -759,   287,  -759,   293,
    -759,   668,  -759,   669,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,   306,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,   672,   679,  -759,  -759,  -759,  -759,   308,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,   105,   545,  -759,
    -759,  -759,  -759,   546,   548,  -759,  -759,   549,   309,  -759,
     318,  -759,   675,  -759,   551,  -759,   682,  -759,  -759,  -759,
    -759,  -759,   324,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,   369,  -759,   683,  -759,   189,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
     684,   553,   685,   131,  -759,  -759,   555,  -759,   688,  -759,
     585,  -759,  -759,   627,  -759,  -759,   307,  -759,   152,   627,
    -759,  -759,   686,   707,   710,   325,  -759,  -759,  -759,  -759,
    -759,  -759,   712,   573,   577,   588,   152,  -759,   596,  -759,
    -759,  -759,  -759,  -759
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   107,     9,   231,    11,
     372,    13,   396,    15,   425,    17,   297,    19,   305,    21,
     342,    23,   196,    25,   518,    27,   575,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   427,     0,   307,   344,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     573,   567,   569,   571,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   105,   119,   121,   123,     0,     0,     0,
       0,     0,   223,   295,   334,   384,   386,   269,   169,   186,
     177,   460,   188,   207,   479,     0,   503,   516,    99,     0,
      72,    74,    75,    76,    77,    78,    81,    82,    83,    84,
      85,    87,    86,    91,    92,    79,    80,    89,    90,    97,
      98,    88,    93,    94,    95,    96,   116,     0,   115,     0,
     109,   111,   112,   113,   114,   364,   388,   254,   256,   258,
       0,     0,   262,   260,   417,   456,   253,   235,   236,   237,
     238,     0,   233,   242,   243,   244,   247,   249,   245,   246,
     239,   240,   251,   252,   241,   248,   250,   382,   381,   378,
     377,     0,   374,   376,   379,   380,   410,     0,   413,     0,
       0,   409,   404,   403,   407,   408,     0,   398,   400,   401,
     405,   406,   402,   454,   442,   444,   446,   448,   450,   452,
     441,   438,   439,   440,     0,   428,   429,   433,   434,   431,
     435,   436,   437,   432,     0,   324,   159,     0,   328,   326,
     331,     0,   320,   321,     0,   308,   309,   311,   323,   312,
     313,   314,   330,   315,   316,   317,   318,   319,   358,     0,
       0,   356,   357,   360,   361,     0,   345,   346,   348,   349,
     350,   351,   352,   353,   354,   355,   203,   205,   200,     0,
     198,   201,   202,     0,   540,   542,     0,   545,     0,     0,
     549,   553,     0,     0,     0,   558,   565,   538,   536,   537,
       0,   520,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   580,     0,   577,   579,
      46,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      57,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    71,
       0,     0,     0,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   232,     0,     0,   373,
       0,     0,     0,     0,     0,     0,   397,     0,     0,     0,
       0,     0,     0,     0,   426,     0,   298,     0,     0,     0,
       0,     0,     0,     0,   306,     0,     0,     0,     0,   343,
       0,     0,     0,     0,   197,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     519,     0,     0,   576,    50,    43,     0,     0,     0,     0,
       0,     0,    61,     0,     0,     0,     0,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   502,     0,     0,    73,     0,
     118,   110,     0,     0,     0,     0,     0,   267,   268,     0,
       0,     0,     0,   234,     0,   375,     0,   412,     0,   415,
     416,   399,     0,     0,     0,     0,     0,     0,     0,   430,
       0,     0,   322,     0,     0,     0,   333,   310,     0,   362,
     363,   347,     0,     0,   199,   539,     0,     0,   544,     0,
     547,   548,     0,     0,   555,   556,   557,     0,     0,   521,
       0,   578,     0,     0,     0,   568,   570,   572,     0,     0,
       0,   125,   225,   299,   336,    40,   385,   387,   271,     0,
      47,     0,     0,   190,     0,     0,     0,     0,    51,   117,
     366,   390,   255,   257,   259,   264,   265,   266,   263,   261,
     419,     0,   383,   411,   414,   455,   443,   445,   447,   449,
     451,   453,   325,   160,   329,   327,   332,   359,   204,   206,
     541,   543,   546,   551,   552,   550,   554,   560,   561,   562,
     563,   564,   559,   566,     0,    44,     0,     0,     0,   146,
     152,   154,   156,     0,     0,     0,     0,     0,   165,   167,
     145,     0,   131,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,   129,     0,   126,   127,
     229,     0,   226,   227,   303,     0,   300,   301,   340,     0,
     337,   338,   275,     0,   272,   273,   175,   176,     0,   171,
     173,   174,     0,   184,   185,   181,     0,   179,   182,   183,
     464,     0,   462,   194,     0,   191,   192,     0,     0,     0,
       0,     0,     0,     0,   209,   211,   212,   213,   214,   215,
     216,   492,   498,     0,     0,     0,   491,   488,   489,   490,
       0,   481,   483,   486,   484,   485,   487,   512,   514,   511,
     509,   510,     0,   505,   507,   508,     0,    53,   370,     0,
     367,   368,   394,     0,   391,   392,   423,     0,   420,   421,
     458,     0,   584,     0,   582,    69,   574,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,   122,     0,   124,     0,     0,   224,     0,   307,   296,
       0,   344,   335,     0,     0,   270,     0,     0,   170,   187,
       0,   178,   466,     0,   461,     0,   189,     0,     0,     0,
       0,     0,     0,     0,     0,   208,     0,     0,     0,     0,
       0,     0,   480,     0,     0,     0,   504,   517,    55,     0,
      54,     0,   365,     0,     0,   389,     0,   427,   418,     0,
       0,   457,     0,     0,   581,     0,     0,     0,     0,   158,
     161,   162,   163,   164,     0,     0,   132,     0,   128,     0,
     228,     0,   302,     0,   339,   294,   289,   291,   283,   284,
     279,   280,   281,   282,   288,   287,   290,     0,   277,   285,
     292,   293,   286,   274,   172,   180,   477,   475,   476,   472,
     473,   474,     0,   467,   468,   470,   471,   463,     0,   193,
     217,   218,   219,   220,   221,   222,   210,     0,     0,   497,
     500,   501,   482,     0,     0,   506,    52,     0,     0,   369,
       0,   393,     0,   422,     0,   598,     0,   596,   594,   588,
     592,   593,     0,   586,   590,   591,   589,   583,   148,   149,
     150,   151,   147,   153,   155,   157,   166,   168,   130,   230,
     304,   341,     0,   276,     0,   465,     0,   195,   494,   495,
     496,   493,   499,   513,   515,    56,   371,   395,   424,   459,
       0,     0,     0,     0,   585,   278,     0,   469,     0,   595,
       0,   587,   478,     0,   597,   602,     0,   600,     0,     0,
     599,   610,     0,     0,     0,     0,   604,   606,   607,   608,
     609,   601,     0,     0,     0,     0,     0,   603,     0,   612,
     613,   614,   605,   611
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,    -9,  -759,   253,  -759,
    -759,  -759,  -759,  -759,  -759,   159,  -759,  -120,  -759,  -759,
    -759,   -70,  -759,  -759,  -759,   381,  -759,  -759,  -759,  -759,
     193,   396,   -41,   -37,   -36,   -25,  -759,  -759,  -759,  -759,
    -759,   177,   383,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,   -18,  -759,  -535,    -3,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,   -61,  -759,
    -553,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,   -17,  -548,  -759,  -759,  -759,  -759,   -21,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,   -19,  -759,  -759,  -759,
     -15,   348,  -759,  -759,  -759,  -759,  -759,  -759,  -759,   -29,
    -759,  -759,  -759,  -759,  -759,  -759,  -758,  -759,  -759,  -759,
       5,  -759,  -759,  -759,     8,   395,  -759,  -759,  -755,  -759,
    -754,  -759,   -32,  -759,  -753,  -759,  -759,  -759,  -752,  -759,
    -759,  -759,  -759,     0,  -759,  -759,  -155,   701,  -759,  -759,
    -759,  -759,  -759,    13,  -759,  -759,  -759,    16,  -759,   373,
    -759,   -65,  -759,  -759,  -759,  -759,  -759,   -44,  -759,  -759,
    -759,  -759,  -759,    -7,  -759,  -759,  -759,    14,  -759,  -759,
    -759,    15,  -759,   394,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,   -24,  -759,  -759,  -759,   -16,
     402,  -759,  -759,   -48,  -759,   -20,  -759,  -759,  -759,  -759,
    -759,   -23,  -759,  -759,  -759,   -14,   397,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,   -13,  -759,
    -759,  -759,   -12,  -759,   398,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -751,
    -759,  -759,  -759,  -759,  -759,  -759,    25,  -759,  -759,  -759,
    -140,  -759,  -759,  -759,  -759,  -759,  -759,    -2,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
      -4,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,   242,
     384,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,  -759,
    -759,  -759,  -759,  -759,   254,   399,  -759,  -759,  -759,   -11,
    -759,  -759,  -142,  -759,  -759,  -759,  -759,  -759,  -759,  -156,
    -759,  -759,  -171,  -759,  -759,  -759,  -759,  -759
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     556,    87,    88,    41,    68,    84,    85,   569,   727,   809,
     810,   630,    43,    70,    96,    97,    98,   335,    45,    71,
     129,   130,   131,   132,   133,   134,   135,   136,   343,    47,
      72,   159,   160,   161,   370,   162,   137,   344,   138,   345,
     139,   346,   647,   648,   649,   762,   631,   632,   633,   748,
     922,   634,   749,   635,   750,   636,   751,   637,   638,   408,
     639,   640,   641,   642,   643,   757,   644,   758,   140,   358,
     668,   669,   670,   671,   141,   360,   676,   677,   678,   679,
     142,   359,   143,   362,   684,   685,   686,   785,    63,    80,
     289,   290,   291,   421,   292,   422,   144,   363,   693,   694,
     695,   696,   697,   698,   699,   700,   145,   352,   651,   652,
     653,   765,    49,    73,   181,   182,   183,   376,   184,   377,
     185,   378,   186,   382,   187,   381,   578,   188,   189,   146,
     357,   663,   664,   665,   774,   857,   858,   147,   353,    57,
      77,   655,   656,   657,   768,    59,    78,   254,   255,   256,
     257,   258,   259,   260,   407,   261,   411,   262,   410,   263,
     264,   412,   265,   148,   354,   659,   660,   661,   771,    61,
      79,   275,   276,   277,   278,   279,   416,   280,   281,   282,
     283,   191,   374,   729,   730,   731,   811,    51,    74,   201,
     202,   203,   387,   149,   355,   150,   356,   194,   375,   733,
     734,   735,   814,    53,    75,   216,   217,   218,   390,   219,
     220,   392,   221,   222,   195,   383,   737,   738,   739,   817,
      55,    76,   234,   235,   236,   237,   398,   238,   399,   239,
     400,   240,   401,   241,   402,   242,   403,   243,   397,   196,
     384,   741,   820,   151,   361,   681,   682,   782,   872,   873,
     874,   875,   876,   934,   152,   364,   710,   711,   712,   796,
     941,   713,   714,   797,   715,   716,   153,   154,   366,   722,
     723,   724,   803,   725,   804,   155,   367,    65,    81,   310,
     311,   312,   313,   426,   314,   427,   315,   316,   429,   317,
     318,   319,   432,   605,   320,   433,   321,   322,   323,   324,
     437,   612,   325,   438,    99,   337,   100,   338,   101,   339,
     102,   336,    67,    82,   327,   328,   329,   441,   743,   744,
     822,   912,   913,   914,   915,   952,   916,   950,   966,   967,
     968,   975,   976,   977,   982,   978,   979,   980
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   128,   158,   176,   198,   211,   230,    38,   252,   271,
     288,   307,   707,   675,   273,   645,   851,   253,   272,   852,
     853,   855,   856,   862,   163,   192,   204,   214,   232,    89,
     266,   284,   177,   308,    42,   274,   178,   179,   666,   286,
     287,    30,   199,   212,    44,    31,    46,    32,   180,    33,
     156,   157,   164,   193,   205,   215,   233,   114,   267,   285,
     103,   309,    48,   104,   105,   106,   190,   200,   213,   231,
     206,   207,   208,   209,   210,   115,   116,   918,   919,   920,
     921,   107,   108,   109,   110,   111,   112,   113,   114,   341,
     115,   116,   173,   368,   342,   115,   116,   777,   369,   245,
     778,   701,   607,   608,   609,   610,   115,   116,    94,    50,
     624,   372,   666,   673,   667,   674,   373,   117,   118,   119,
     120,   121,   246,    52,   247,   248,   114,   385,   249,   250,
     251,   780,   386,   122,   781,   611,   123,   717,   718,   115,
     116,   115,   116,   124,   115,   116,    54,    90,   388,   395,
      56,   125,   126,   389,   396,   127,    91,    92,    93,   223,
     575,   576,   577,   224,   225,   226,   227,   228,   229,    58,
     423,   246,    94,    94,   851,   424,    60,   852,   853,   855,
     856,   862,   702,   703,   704,   705,   439,    94,   115,   116,
      86,   440,    94,   442,    34,    35,    36,    37,   443,   619,
     938,   939,   940,    94,   620,   621,   622,   623,   624,   625,
     626,   627,   628,   629,   286,   287,   246,   268,   247,   248,
     269,   270,   246,    62,   114,   368,   442,   837,   114,   246,
     745,   746,   675,   115,   116,   197,    94,    64,    94,   372,
     759,    94,   115,   116,   747,   760,   115,   116,   707,   107,
     108,   109,   110,   759,   783,   794,   114,   784,   761,   173,
     795,   905,   866,   906,   907,   801,   165,   805,   166,   113,
     802,    95,   806,    66,   115,   116,   167,   168,   169,   170,
     171,   172,   326,   971,   439,    94,   972,   973,   974,   807,
     759,   173,   174,   331,   823,   928,   385,   824,   128,   175,
     330,   929,   158,   687,   688,   689,   690,   691,   692,   932,
     969,   423,   388,   970,   933,   176,   937,   946,   198,   603,
     604,   395,   444,   445,   163,   211,   947,   953,   986,   333,
      94,   332,   954,   987,   334,   230,    94,   192,   340,    94,
     204,   347,   348,    94,   177,   252,   349,   214,   178,   179,
     271,   350,   164,   351,   253,   273,   199,   232,   365,   272,
     180,   371,   379,   212,   380,   193,   391,   266,   205,   307,
     393,    94,   284,   404,   394,   215,   274,   405,   190,   406,
     409,   200,   585,   586,   587,   233,   413,   414,   213,   415,
     420,   308,   417,   418,   425,   267,   428,   430,   231,   419,
     285,   107,   108,   109,   110,   431,   112,   434,   114,   246,
     435,   436,   446,   447,   448,   449,   450,   451,   453,   309,
     454,   455,   456,   457,   458,   459,   115,   116,   460,   168,
     169,   461,   171,   172,   462,   463,   464,   465,   466,   467,
     545,   546,   547,   173,   468,   480,   469,   470,   471,   472,
     473,   175,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   474,   476,   475,   477,
     479,   482,   483,   128,   484,   485,   486,   487,   158,   489,
     488,   490,   491,   492,   494,   496,   498,   497,   499,   502,
     500,   503,   504,   505,   506,   706,   719,   307,   115,   116,
     163,   507,   508,   510,   511,   512,   513,   514,   515,   516,
     518,   522,   519,   520,   599,   523,   525,   708,   720,   308,
     526,   527,   528,    94,   529,   532,   533,   530,   164,   537,
     531,   538,   540,   615,   534,   535,   542,   536,   543,   557,
     544,   548,   549,   550,   551,   709,   721,   309,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   552,   553,   554,   764,   558,    32,   559,   560,
     561,   562,   563,   572,   573,   564,   565,   566,   567,   568,
     570,   571,   574,   579,   580,   581,   614,   606,   740,   646,
     582,   583,   584,   588,   650,    94,   654,   658,   662,   680,
     683,   589,   590,   591,   592,   593,   594,   595,   596,   597,
     598,   600,   601,   602,   613,   728,   732,   736,   742,   752,
     753,   754,   755,   756,   829,   767,   763,   766,   770,   769,
     772,   773,   775,   776,   965,   779,   787,   786,   788,   789,
     790,   791,   792,   793,   798,   799,   800,   808,   813,   812,
     815,   816,   818,   819,   897,   821,   825,   826,   827,   828,
     834,   835,   887,   888,   831,   830,   893,   832,   833,   880,
     881,   894,   896,   882,   883,   904,   930,   931,   884,   885,
     935,   889,   936,   948,   890,   891,   951,   956,   958,   960,
     983,   923,   924,   963,   925,   176,   926,   927,   252,   942,
     943,   271,   944,   945,   845,   949,   273,   253,   959,   962,
     272,   984,   867,   850,   985,   288,   988,   192,   555,   672,
     266,   868,   452,   284,   177,   618,   860,   274,   178,   179,
     989,   706,   990,   846,   870,   719,   616,   847,   848,   964,
     180,   198,   854,   991,   211,   193,   838,   230,   267,   849,
     993,   285,   908,   708,   861,   481,   836,   720,   190,   865,
     864,   909,   871,   204,   478,   886,   214,   859,   879,   232,
     878,   524,   840,   839,   910,   869,   863,   955,   244,   199,
     493,   709,   212,   842,   841,   721,   843,   844,   517,   899,
     495,   205,   501,   901,   215,   898,   957,   233,   617,   892,
     900,   895,   911,   509,   200,   902,   903,   213,   877,   726,
     231,   961,   917,   981,   521,   992,     0,     0,     0,     0,
       0,     0,     0,   539,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   541,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   845,     0,     0,     0,   867,     0,     0,     0,
       0,   850,     0,     0,     0,   868,     0,     0,     0,     0,
       0,     0,     0,   908,   860,     0,     0,     0,   870,     0,
       0,   846,   909,     0,     0,   847,   848,     0,     0,     0,
     854,     0,     0,     0,     0,   910,     0,   849,     0,     0,
       0,     0,   861,     0,     0,     0,   871,     0,     0,     0,
       0,     0,     0,     0,     0,   859,     0,     0,     0,   869,
       0,     0,     0,   911
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    16,    78,    79,
      80,    81,   565,   561,    79,   550,   774,    78,    79,   774,
     774,   774,   774,   774,    72,    73,    74,    75,    76,    10,
      78,    79,    73,    81,     7,    79,    73,    73,    78,    85,
      86,     0,    74,    75,     7,     5,     7,     7,    73,     9,
      12,    13,    72,    73,    74,    75,    76,    39,    78,    79,
      11,    81,     7,    14,    15,    16,    73,    74,    75,    76,
      52,    53,    54,    55,    56,    57,    58,    18,    19,    20,
      21,    32,    33,    34,    35,    36,    37,    38,    39,     3,
      57,    58,    74,     3,     8,    57,    58,     3,     8,    17,
       6,    17,   124,   125,   126,   127,    57,    58,   154,     7,
      26,     3,    78,    79,   154,    81,     8,    68,    69,    70,
      71,    72,    40,     7,    42,    43,    39,     3,    46,    47,
      48,     3,     8,    84,     6,   157,    87,   104,   105,    57,
      58,    57,    58,    94,    57,    58,     7,   128,     3,     3,
       7,   102,   103,     8,     8,   106,   137,   138,   139,    72,
      65,    66,    67,    76,    77,    78,    79,    80,    81,     7,
       3,    40,   154,   154,   932,     8,     7,   932,   932,   932,
     932,   932,    98,    99,   100,   101,     3,   154,    57,    58,
     154,     8,   154,     3,   154,   155,   156,   157,     8,    17,
      95,    96,    97,   154,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    85,    86,    40,    41,    42,    43,
      44,    45,    40,     7,    39,     3,     3,   762,    39,    40,
       8,     8,   780,    57,    58,    50,   154,     7,   154,     3,
       3,   154,    57,    58,     8,     8,    57,    58,   801,    32,
      33,    34,    35,     3,     3,     3,    39,     6,     8,    74,
       8,   130,    73,   132,   133,     3,    49,     3,    51,    38,
       8,   341,     8,     7,    57,    58,    59,    60,    61,    62,
      63,    64,   129,   131,     3,   154,   134,   135,   136,     8,
       3,    74,    75,     3,     3,     8,     3,     6,   368,    82,
       6,     8,   372,    88,    89,    90,    91,    92,    93,     3,
       3,     3,     3,     6,     8,   385,     8,     8,   388,   121,
     122,     3,   331,   332,   372,   395,     8,     3,     3,     8,
     154,     4,     8,     8,     3,   405,   154,   385,     4,   154,
     388,     4,     4,   154,   385,   415,     4,   395,   385,   385,
     420,     4,   372,     4,   415,   420,   388,   405,     4,   420,
     385,     4,     4,   395,     4,   385,     4,   415,   388,   439,
       4,   154,   420,     8,     4,   395,   420,     3,   385,     8,
       4,   388,   502,   503,   504,   405,     4,     8,   395,     3,
       3,   439,     4,     4,     4,   415,     4,     4,   405,     8,
     420,    32,    33,    34,    35,     4,    37,     4,    39,    40,
       4,     4,   154,     4,     4,     4,     4,     4,     4,   439,
       4,     4,     4,   155,   155,   155,    57,    58,   155,    60,
      61,   155,    63,    64,     4,     4,     4,     4,     4,     4,
     449,   450,   451,    74,     4,   157,     4,     4,     4,     4,
       4,    82,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,     4,     4,   155,     4,
       4,     4,     4,   543,     4,     4,     4,   155,   548,     4,
     157,     4,     4,     4,     4,     4,     4,   155,   155,     4,
     155,     4,     4,     4,     4,   565,   566,   567,    57,    58,
     548,     4,     4,     4,     4,   155,     4,     4,     4,   157,
       4,     4,   157,   157,   523,     4,   157,   565,   566,   567,
       4,     4,   155,   154,     4,     4,     4,   155,   548,     4,
     155,     4,     4,   542,   157,   157,     4,   157,     7,   154,
       7,     7,     7,     7,     5,   565,   566,   567,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,     5,     5,     5,     3,     5,     7,     5,     5,
       5,     5,     5,   154,   154,     7,     7,     7,     7,     5,
       5,     5,   154,   154,     5,     7,     5,   123,    83,     7,
     154,   154,   154,   154,     7,   154,     7,     7,     7,     7,
       7,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,     7,     7,     7,     7,     4,
       4,     4,     4,     4,   155,     3,     6,     6,     3,     6,
       6,     3,     6,     3,     7,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   154,     3,     6,
       6,     3,     6,     3,     3,     8,     4,     4,     4,     4,
       4,     4,     4,     4,   155,   157,     4,   157,   155,   155,
     155,     4,     6,   155,   155,     4,     8,     8,   155,   155,
       8,   155,     3,     8,   155,   155,     4,     4,     4,     4,
       4,   154,   154,     5,   154,   765,   154,   154,   768,   154,
     154,   771,   154,   154,   774,   154,   771,   768,   155,   154,
     771,     4,   782,   774,     4,   785,     4,   765,   465,   560,
     768,   782,   341,   771,   765,   548,   774,   771,   765,   765,
     157,   801,   155,   774,   782,   805,   543,   774,   774,   154,
     765,   811,   774,   155,   814,   765,   764,   817,   768,   774,
     154,   771,   822,   801,   774,   372,   759,   805,   765,   780,
     777,   822,   782,   811,   368,   794,   814,   774,   787,   817,
     785,   423,   767,   765,   822,   782,   776,   932,    77,   811,
     385,   801,   814,   770,   768,   805,   771,   773,   415,   813,
     388,   811,   395,   816,   814,   811,   936,   817,   544,   801,
     814,   805,   822,   405,   811,   817,   819,   814,   783,   567,
     817,   953,   823,   969,   420,   986,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   439,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   932,    -1,    -1,    -1,   936,    -1,    -1,    -1,
      -1,   932,    -1,    -1,    -1,   936,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   953,   932,    -1,    -1,    -1,   936,    -1,
      -1,   932,   953,    -1,    -1,   932,   932,    -1,    -1,    -1,
     932,    -1,    -1,    -1,    -1,   953,    -1,   932,    -1,    -1,
      -1,    -1,   932,    -1,    -1,    -1,   936,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   932,    -1,    -1,    -1,   936,
      -1,    -1,    -1,   953
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
       0,     5,     7,     9,   154,   155,   156,   157,   174,   175,
     176,   181,     7,   190,     7,   196,     7,   207,     7,   290,
       7,   365,     7,   381,     7,   398,     7,   317,     7,   323,
       7,   347,     7,   266,     7,   455,     7,   490,   182,   177,
     191,   197,   208,   291,   366,   382,   399,   318,   324,   348,
     267,   456,   491,   174,   183,   184,   154,   179,   180,    10,
     128,   137,   138,   139,   154,   189,   192,   193,   194,   482,
     484,   486,   488,    11,    14,    15,    16,    32,    33,    34,
      35,    36,    37,    38,    39,    57,    58,    68,    69,    70,
      71,    72,    84,    87,    94,   102,   103,   106,   189,   198,
     199,   200,   201,   202,   203,   204,   205,   214,   216,   218,
     246,   252,   258,   260,   274,   284,   307,   315,   341,   371,
     373,   421,   432,   444,   445,   453,    12,    13,   189,   209,
     210,   211,   213,   371,   373,    49,    51,    59,    60,    61,
      62,    63,    64,    74,    75,    82,   189,   200,   201,   202,
     203,   292,   293,   294,   296,   298,   300,   302,   305,   306,
     341,   359,   371,   373,   375,   392,   417,    50,   189,   300,
     341,   367,   368,   369,   371,   373,    52,    53,    54,    55,
      56,   189,   300,   341,   371,   373,   383,   384,   385,   387,
     388,   390,   391,    72,    76,    77,    78,    79,    80,    81,
     189,   341,   371,   373,   400,   401,   402,   403,   405,   407,
     409,   411,   413,   415,   315,    17,    40,    42,    43,    46,
      47,    48,   189,   236,   325,   326,   327,   328,   329,   330,
     331,   333,   335,   337,   338,   340,   371,   373,    41,    44,
      45,   189,   236,   329,   335,   349,   350,   351,   352,   353,
     355,   356,   357,   358,   371,   373,    85,    86,   189,   268,
     269,   270,   272,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   189,   371,   373,
     457,   458,   459,   460,   462,   464,   465,   467,   468,   469,
     472,   474,   475,   476,   477,   480,   129,   492,   493,   494,
       6,     3,     4,     8,     3,   195,   489,   483,   485,   487,
       4,     3,     8,   206,   215,   217,   219,     4,     4,     4,
       4,     4,   285,   316,   342,   372,   374,   308,   247,   259,
     253,   422,   261,   275,   433,     4,   446,   454,     3,     8,
     212,     4,     3,     8,   360,   376,   295,   297,   299,     4,
       4,   303,   301,   393,   418,     3,     8,   370,     3,     8,
     386,     4,   389,     4,     4,     3,     8,   416,   404,   406,
     408,   410,   412,   414,     8,     3,     8,   332,   237,     4,
     336,   334,   339,     4,     8,     3,   354,     4,     4,     8,
       3,   271,   273,     3,     8,     4,   461,   463,     4,   466,
       4,     4,   470,   473,     4,     4,     4,   478,   481,     3,
       8,   495,     3,     8,   174,   174,   154,     4,     4,     4,
       4,     4,   193,     4,     4,     4,     4,   155,   155,   155,
     155,   155,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   155,     4,     4,   199,     4,
     157,   210,     4,     4,     4,     4,     4,   155,   157,     4,
       4,     4,     4,   293,     4,   368,     4,   155,     4,   155,
     155,   384,     4,     4,     4,     4,     4,     4,     4,   402,
       4,     4,   155,     4,     4,     4,   157,   327,     4,   157,
     157,   351,     4,     4,   269,   157,     4,     4,   155,     4,
     155,   155,     4,     4,   157,   157,   157,     4,     4,   458,
       4,   493,     4,     7,     7,   174,   174,   174,     7,     7,
       7,     5,     5,     5,     5,   176,   178,   154,     5,     5,
       5,     5,     5,     5,     7,     7,     7,     7,     5,   185,
       5,     5,   154,   154,   154,    65,    66,    67,   304,   154,
       5,     7,   154,   154,   154,   185,   185,   185,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   174,
     154,   154,   154,   121,   122,   471,   123,   124,   125,   126,
     127,   157,   479,   154,     5,   174,   198,   492,   209,    17,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
     189,   224,   225,   226,   229,   231,   233,   235,   236,   238,
     239,   240,   241,   242,   244,   224,     7,   220,   221,   222,
       7,   286,   287,   288,     7,   319,   320,   321,     7,   343,
     344,   345,     7,   309,   310,   311,    78,   154,   248,   249,
     250,   251,   183,    79,    81,   250,   254,   255,   256,   257,
       7,   423,   424,     7,   262,   263,   264,    88,    89,    90,
      91,    92,    93,   276,   277,   278,   279,   280,   281,   282,
     283,    17,    98,    99,   100,   101,   189,   238,   371,   373,
     434,   435,   436,   439,   440,   442,   443,   104,   105,   189,
     371,   373,   447,   448,   449,   451,   457,   186,     7,   361,
     362,   363,     7,   377,   378,   379,     7,   394,   395,   396,
      83,   419,     7,   496,   497,     8,     8,     8,   227,   230,
     232,   234,     4,     4,     4,     4,     4,   243,   245,     3,
       8,     8,   223,     6,     3,   289,     6,     3,   322,     6,
       3,   346,     6,     3,   312,     6,     3,     3,     6,     6,
       3,     6,   425,     3,     6,   265,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   437,   441,     4,     4,
       4,     3,     8,   450,   452,     3,     8,     8,   154,   187,
     188,   364,     6,     3,   380,     6,     3,   397,     6,     3,
     420,     8,   498,     3,     6,     4,     4,     4,     4,   155,
     157,   155,   157,   155,     4,     4,   225,   224,   222,   292,
     288,   325,   321,   349,   345,   189,   200,   201,   202,   203,
     236,   284,   296,   298,   300,   302,   306,   313,   314,   341,
     371,   373,   417,   311,   249,   255,    73,   189,   236,   341,
     371,   373,   426,   427,   428,   429,   430,   424,   268,   264,
     155,   155,   155,   155,   155,   155,   277,     4,     4,   155,
     155,   155,   435,     4,     4,   448,     6,     3,   367,   363,
     383,   379,   400,   396,     4,   130,   132,   133,   189,   236,
     371,   373,   499,   500,   501,   502,   504,   497,    18,    19,
      20,    21,   228,   154,   154,   154,   154,   154,     8,     8,
       8,     8,     3,     8,   431,     8,     3,     8,    95,    96,
      97,   438,   154,   154,   154,   154,     8,     8,     8,   154,
     505,     4,   503,     3,     8,   314,     4,   428,     4,   155,
       4,   500,   154,     5,   154,     7,   506,   507,   508,     3,
       6,   131,   134,   135,   136,   509,   510,   511,   513,   514,
     515,   507,   512,     4,     4,     4,     3,     8,     4,   157,
     155,   155,   510,   154
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   158,   160,   159,   161,   159,   162,   159,   163,   159,
     164,   159,   165,   159,   166,   159,   167,   159,   168,   159,
     169,   159,   170,   159,   171,   159,   172,   159,   173,   159,
     174,   174,   174,   174,   174,   174,   174,   175,   177,   176,
     178,   179,   179,   180,   180,   182,   181,   183,   183,   184,
     184,   186,   185,   187,   187,   188,   188,   189,   191,   190,
     192,   192,   193,   193,   193,   193,   193,   193,   195,   194,
     197,   196,   198,   198,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     200,   201,   202,   203,   204,   206,   205,   208,   207,   209,
     209,   210,   210,   210,   210,   210,   212,   211,   213,   215,
     214,   217,   216,   219,   218,   220,   220,   221,   221,   223,
     222,   224,   224,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   227,   226,   228,   228,
     228,   228,   230,   229,   232,   231,   234,   233,   235,   237,
     236,   238,   239,   240,   241,   243,   242,   245,   244,   247,
     246,   248,   248,   249,   249,   250,   251,   253,   252,   254,
     254,   255,   255,   255,   256,   257,   259,   258,   261,   260,
     262,   262,   263,   263,   265,   264,   267,   266,   268,   268,
     268,   269,   269,   271,   270,   273,   272,   275,   274,   276,
     276,   277,   277,   277,   277,   277,   277,   278,   279,   280,
     281,   282,   283,   285,   284,   286,   286,   287,   287,   289,
     288,   291,   290,   292,   292,   293,   293,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,   293,   293,   293,
     293,   293,   293,   293,   295,   294,   297,   296,   299,   298,
     301,   300,   303,   302,   304,   304,   304,   305,   306,   308,
     307,   309,   309,   310,   310,   312,   311,   313,   313,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   316,   315,   318,   317,   319,
     319,   320,   320,   322,   321,   324,   323,   325,   325,   326,
     326,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   328,   329,   330,   332,   331,   334,   333,   336,   335,
     337,   339,   338,   340,   342,   341,   343,   343,   344,   344,
     346,   345,   348,   347,   349,   349,   350,   350,   351,   351,
     351,   351,   351,   351,   351,   351,   351,   352,   354,   353,
     355,   356,   357,   358,   360,   359,   361,   361,   362,   362,
     364,   363,   366,   365,   367,   367,   368,   368,   368,   368,
     368,   368,   370,   369,   372,   371,   374,   373,   376,   375,
     377,   377,   378,   378,   380,   379,   382,   381,   383,   383,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     386,   385,   387,   389,   388,   390,   391,   393,   392,   394,
     394,   395,   395,   397,   396,   399,   398,   400,   400,   401,
     401,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   404,   403,   406,   405,   408,   407,   410,   409,
     412,   411,   414,   413,   416,   415,   418,   417,   420,   419,
     422,   421,   423,   423,   425,   424,   426,   426,   427,   427,
     428,   428,   428,   428,   428,   428,   429,   431,   430,   433,
     432,   434,   434,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   437,   436,   438,   438,   438,   439,   441,   440,
     442,   443,   444,   446,   445,   447,   447,   448,   448,   448,
     448,   448,   450,   449,   452,   451,   454,   453,   456,   455,
     457,   457,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   459,
     461,   460,   463,   462,   464,   466,   465,   467,   468,   470,
     469,   471,   471,   473,   472,   474,   475,   476,   478,   477,
     479,   479,   479,   479,   479,   481,   480,   483,   482,   485,
     484,   487,   486,   489,   488,   491,   490,   492,   492,   493,
     495,   494,   496,   496,   498,   497,   499,   499,   500,   500,
     500,   500,   500,   500,   500,   501,   503,   502,   505,   504,
     506,   506,   508,   507,   509,   509,   510,   510,   510,   510,
     512,   511,   513,   514,   515
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"preferred-lifetime\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "lease_database", "$@24", "hosts_database", "$@25", "hosts_databases",
  "$@26", "database_list", "not_empty_database_list", "database", "$@27",
  "database_map_params", "database_map_param", "database_type", "$@28",
  "db_type", "user", "$@29", "password", "$@30", "host", "$@31", "port",
  "name", "$@32", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@33", "keyspace", "$@34", "mac_sources", "$@35",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@37",
  "hooks_libraries", "$@38", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@39",
  "sub_hooks_library", "$@40", "hooks_params", "hooks_param", "library",
  "$@41", "parameters", "$@42", "expired_leases_processing", "$@43",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@44",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@45",
  "sub_subnet6", "$@46", "subnet6_params", "subnet6_param", "subnet",
  "$@47", "interface", "$@48", "interface_id", "$@49", "client_class",
  "$@50", "reservation_mode", "$@51", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@52", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@53",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@54", "sub_option_def_list", "$@55", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@56",
  "sub_option_def", "$@57", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@58",
  "option_def_record_types", "$@59", "space", "$@60", "option_def_space",
  "option_def_encapsulate", "$@61", "option_def_array", "option_data_list",
  "$@62", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@63", "sub_option_data", "$@64",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@65",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@66", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@67", "sub_pool6", "$@68",
  "pool_params", "pool_param", "pool_entry", "$@69", "user_context",
  "$@70", "comment", "$@71", "pd_pools_list", "$@72",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@73", "sub_pd_pool", "$@74", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@75", "pd_prefix_len", "excluded_prefix", "$@76",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@77",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@78", "sub_reservation", "$@79", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@80", "prefixes", "$@81", "duid", "$@82", "hw_address", "$@83",
  "hostname", "$@84", "flex_id_value", "$@85",
  "reservation_client_classes", "$@86", "relay", "$@87", "relay_map",
  "$@88", "client_classes", "$@89", "client_classes_list",
  "client_class_entry", "$@90", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@91", "server_id", "$@92",
  "server_id_params", "server_id_param", "server_id_type", "$@93",
  "duid_type", "htype", "identifier", "$@94", "time", "enterprise_id",
  "dhcp4o6_port", "control_socket", "$@95", "control_socket_params",
  "control_socket_param", "socket_type", "$@96", "socket_name", "$@97",
  "dhcp_ddns", "$@98", "sub_dhcp_ddns", "$@99", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@100",
  "server_ip", "$@101", "server_port", "sender_ip", "$@102", "sender_port",
  "max_queue_size", "ncr_protocol", "$@103", "ncr_protocol_value",
  "ncr_format", "$@104", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@105",
  "replace_client_name_value", "generated_prefix", "$@106",
  "dhcp4_json_object", "$@107", "dhcpddns_json_object", "$@108",
  "control_agent_json_object", "$@109", "logging_object", "$@110",
  "sub_logging", "$@111", "logging_params", "logging_param", "loggers",
  "$@112", "loggers_entries", "logger_entry", "$@113", "logger_params",
  "logger_param", "debuglevel", "severity", "$@114", "output_options_list",
  "$@115", "output_options_list_content", "output_entry", "$@116",
  "output_params_list", "output_params", "output", "$@117", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   239,   239,   239,   240,   240,   241,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   246,   246,   247,   247,
     248,   248,   249,   249,   250,   250,   251,   251,   252,   252,
     260,   261,   262,   263,   264,   265,   266,   269,   274,   274,
     285,   288,   289,   292,   296,   303,   303,   310,   311,   314,
     318,   325,   325,   332,   333,   336,   340,   351,   361,   361,
     376,   377,   381,   382,   383,   384,   385,   386,   389,   389,
     404,   404,   413,   414,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     447,   452,   457,   462,   467,   472,   472,   483,   483,   492,
     493,   496,   497,   498,   499,   500,   503,   503,   513,   519,
     519,   531,   531,   543,   543,   553,   554,   557,   558,   561,
     561,   571,   572,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   590,   590,   597,   598,
     599,   600,   603,   603,   611,   611,   619,   619,   627,   632,
     632,   640,   645,   650,   655,   660,   660,   668,   668,   677,
     677,   687,   688,   691,   692,   695,   700,   705,   705,   715,
     716,   719,   720,   721,   724,   729,   736,   736,   746,   746,
     756,   757,   760,   761,   764,   764,   774,   774,   784,   785,
     786,   789,   790,   793,   793,   801,   801,   809,   809,   820,
     821,   824,   825,   826,   827,   828,   829,   832,   837,   842,
     847,   852,   857,   865,   865,   878,   879,   882,   883,   890,
     890,   916,   916,   927,   928,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   946,
     947,   948,   949,   950,   953,   953,   961,   961,   969,   969,
     977,   977,   985,   985,   992,   993,   994,   997,  1002,  1010,
    1010,  1021,  1022,  1026,  1027,  1030,  1030,  1038,  1039,  1042,
    1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,
    1053,  1054,  1055,  1056,  1057,  1064,  1064,  1077,  1077,  1086,
    1087,  1090,  1091,  1096,  1096,  1111,  1111,  1125,  1126,  1129,
    1130,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,
    1142,  1145,  1147,  1152,  1154,  1154,  1162,  1162,  1170,  1170,
    1178,  1180,  1180,  1188,  1197,  1197,  1209,  1210,  1215,  1216,
    1221,  1221,  1233,  1233,  1245,  1246,  1251,  1252,  1257,  1258,
    1259,  1260,  1261,  1262,  1263,  1264,  1265,  1268,  1270,  1270,
    1278,  1280,  1282,  1287,  1295,  1295,  1307,  1308,  1311,  1312,
    1315,  1315,  1325,  1325,  1334,  1335,  1338,  1339,  1340,  1341,
    1342,  1343,  1346,  1346,  1354,  1354,  1379,  1379,  1409,  1409,
    1421,  1422,  1425,  1426,  1429,  1429,  1441,  1441,  1453,  1454,
    1457,  1458,  1459,  1460,  1461,  1462,  1463,  1464,  1465,  1466,
    1469,  1469,  1477,  1482,  1482,  1490,  1495,  1503,  1503,  1513,
    1514,  1517,  1518,  1521,  1521,  1530,  1530,  1539,  1540,  1543,
    1544,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,  1556,
    1557,  1558,  1561,  1561,  1571,  1571,  1581,  1581,  1589,  1589,
    1597,  1597,  1605,  1605,  1613,  1613,  1626,  1626,  1636,  1636,
    1647,  1647,  1657,  1658,  1661,  1661,  1671,  1672,  1675,  1676,
    1679,  1680,  1681,  1682,  1683,  1684,  1687,  1689,  1689,  1700,
    1700,  1712,  1713,  1716,  1717,  1718,  1719,  1720,  1721,  1722,
    1723,  1724,  1727,  1727,  1734,  1735,  1736,  1739,  1744,  1744,
    1752,  1757,  1764,  1771,  1771,  1781,  1782,  1785,  1786,  1787,
    1788,  1789,  1792,  1792,  1800,  1800,  1810,  1810,  1822,  1822,
    1832,  1833,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,
    1844,  1845,  1846,  1847,  1848,  1849,  1850,  1851,  1852,  1855,
    1860,  1860,  1868,  1868,  1876,  1881,  1881,  1889,  1894,  1899,
    1899,  1907,  1908,  1911,  1911,  1919,  1924,  1929,  1934,  1934,
    1942,  1945,  1948,  1951,  1954,  1960,  1960,  1970,  1970,  1977,
    1977,  1984,  1984,  1997,  1997,  2007,  2007,  2018,  2019,  2023,
    2027,  2027,  2039,  2040,  2044,  2044,  2052,  2053,  2056,  2057,
    2058,  2059,  2060,  2061,  2062,  2065,  2070,  2070,  2078,  2078,
    2088,  2089,  2092,  2092,  2100,  2101,  2104,  2105,  2106,  2107,
    2110,  2110,  2118,  2123,  2128
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
#line 4643 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2133 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
