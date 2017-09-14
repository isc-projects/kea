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
#define yylex   parser4_lex

// First part of user declarations.

#line 39 "dhcp4_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp4_parser.h"

// User implementation prologue.

#line 53 "dhcp4_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:413

#include <dhcp4/parser_context.h>

#line 59 "dhcp4_parser.cc" // lalr1.cc:413


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
    :
#if PARSER4_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp4Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp4Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp4Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp4Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 161: // value
      case 165: // map_value
      case 203: // socket_type
      case 213: // db_type
      case 290: // hr_mode
      case 433: // ncr_protocol_value
      case 441: // replace_client_name_value
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 161: // value
      case 165: // map_value
      case 203: // socket_type
      case 213: // db_type
      case 290: // hr_mode
      case 433: // ncr_protocol_value
      case 441: // replace_client_name_value
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo,
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

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 144: // "integer"

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 145: // "floating point"

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 146: // "boolean"

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 161: // value

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 165: // map_value

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 203: // socket_type

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 213: // db_type

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 290: // hr_mode

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 433: // ncr_protocol_value

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 441: // replace_client_name_value

#line 220 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp4_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp4Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp4Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  inline Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::parse ()
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
      case 203: // socket_type
      case 213: // db_type
      case 290: // hr_mode
      case 433: // ncr_protocol_value
      case 441: // replace_client_name_value
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
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 797 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 886 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 437 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 487 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 570 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 763 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 801 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1635 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1671 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 928 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 967 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1048 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 310:
#line 1125 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1133 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1141 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2118 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1254 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2193 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1424 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2517 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1738 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3188 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3192 "dhcp4_parser.cc" // lalr1.cc:859
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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp4Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp4Parser::yypact_ninf_ = -688;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     211,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,    39,    18,    38,    58,    71,    73,    75,
     120,   146,   179,   185,   193,   203,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
      18,   -72,     9,    83,   196,    22,   -14,    31,    51,    91,
      23,   -27,   222,  -688,   214,   226,   227,   239,   257,  -688,
    -688,  -688,  -688,  -688,   275,  -688,    34,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,   277,   278,  -688,  -688,  -688,   280,
     281,   282,   287,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,   288,  -688,  -688,  -688,    45,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
     290,    46,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,   291,   292,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,    52,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,    61,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,   298,   296,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,   299,  -688,  -688,
     305,  -688,  -688,  -688,   306,  -688,  -688,   304,   297,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
     311,   312,  -688,  -688,  -688,  -688,   309,   316,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,    87,  -688,
    -688,  -688,   331,  -688,  -688,   332,  -688,   334,   335,  -688,
    -688,   350,   351,   352,  -688,  -688,  -688,   148,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,    18,    18,  -688,   217,   357,   359,
     360,   362,   363,  -688,     9,  -688,   364,   223,   228,   366,
     367,   368,   229,   231,   232,   233,   374,   375,   376,   377,
     378,   379,   380,   381,   242,   383,   384,    83,  -688,   385,
     386,   245,   196,  -688,    72,   388,   389,   390,   391,   392,
     393,   394,   395,   260,   254,   397,   398,   399,   401,    22,
    -688,   402,   -14,  -688,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,  -688,    31,  -688,   413,   414,   276,
     415,   417,   418,   279,  -688,    91,   419,   283,   284,  -688,
      23,   420,   422,   -29,  -688,   285,   423,   424,   289,   428,
     293,   294,   430,   431,   295,   301,   302,   432,   435,   222,
    -688,  -688,  -688,   438,   436,   437,    18,    18,    18,  -688,
     442,  -688,  -688,   307,   444,   447,  -688,  -688,  -688,  -688,
     450,   451,   453,   454,   455,   456,   457,   458,  -688,   459,
     460,  -688,   463,   121,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,   461,   467,  -688,  -688,  -688,   329,   330,
     333,   469,   468,   336,   337,   338,  -688,  -688,    49,   340,
     472,   471,  -688,   341,  -688,   342,   343,   463,   344,   346,
     347,   348,   349,   353,   354,  -688,   355,   356,  -688,   358,
     361,   365,  -688,  -688,   369,  -688,  -688,  -688,   370,    18,
    -688,  -688,   371,   372,  -688,   373,  -688,  -688,    20,   396,
    -688,  -688,  -688,    79,   382,  -688,    18,    83,   387,  -688,
    -688,  -688,   196,  -688,   219,   219,   486,   487,   488,   493,
     125,    25,   495,   147,    76,   222,  -688,  -688,  -688,  -688,
    -688,   499,  -688,    72,  -688,  -688,  -688,   498,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,   502,   434,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,   168,  -688,   172,  -688,  -688,   213,
    -688,  -688,  -688,  -688,   507,   514,   515,   516,   517,  -688,
    -688,  -688,   215,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,   216,  -688,   500,   519,
    -688,  -688,   518,   520,  -688,  -688,   521,   523,  -688,  -688,
     522,   526,  -688,  -688,  -688,  -688,  -688,  -688,    30,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,   224,  -688,   524,   528,
    -688,   529,   530,   531,   532,   533,   534,   225,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,   255,  -688,  -688,
    -688,   256,   400,   416,  -688,  -688,   535,   536,  -688,  -688,
     538,   537,  -688,  -688,   539,  -688,   541,   387,  -688,  -688,
     542,   544,   545,   546,   421,   425,   426,   427,   433,   547,
     548,   219,  -688,  -688,    22,  -688,   486,    91,  -688,   487,
      23,  -688,   488,   150,  -688,   493,   125,  -688,    25,  -688,
     -27,  -688,   495,   439,   440,   441,   443,   445,   446,   147,
    -688,   549,   550,    76,  -688,  -688,  -688,   551,   552,  -688,
     -14,  -688,   498,    31,  -688,   502,   554,  -688,   527,  -688,
     132,   429,   448,   449,  -688,  -688,  -688,  -688,  -688,   452,
     462,  -688,   258,  -688,   553,  -688,   555,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,   259,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,   266,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,   464,   465,  -688,  -688,   466,
     267,  -688,   556,  -688,   470,   559,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,   150,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,   238,
    -688,  -688,    64,   559,  -688,  -688,   558,  -688,  -688,  -688,
     268,  -688,  -688,  -688,  -688,  -688,   563,   473,   564,    64,
    -688,   569,  -688,   475,  -688,   562,  -688,  -688,   274,  -688,
      57,   562,  -688,  -688,   571,   572,   574,   270,  -688,  -688,
    -688,  -688,  -688,  -688,   575,   474,   477,   478,    57,  -688,
     476,  -688,  -688,  -688,  -688,  -688
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   105,     9,   213,    11,   355,    13,   375,    15,
     284,    17,   292,    19,   327,    21,   178,    23,   453,    25,
      43,    37,     0,     0,     0,     0,     0,   377,     0,   294,
     329,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     506,   500,   502,   504,     0,    63,     0,    56,    58,    60,
      61,    62,    59,    98,     0,     0,   394,   114,   116,     0,
       0,     0,     0,   205,   282,   319,   259,   156,   420,   170,
     189,     0,   441,   451,    91,     0,    68,    70,    71,    72,
      73,    88,    89,    76,    77,    78,    79,    83,    84,    74,
      75,    81,    82,    90,    80,    85,    86,    87,   107,   109,
       0,     0,   100,   102,   103,   104,   424,   240,   242,   244,
     347,   365,   238,   246,   248,     0,     0,   252,   250,   367,
     416,   237,   217,   218,   219,   231,     0,   215,   222,   233,
     234,   235,   223,   224,   227,   229,   225,   226,   220,   221,
     236,   228,   232,   230,   363,   362,   360,     0,   357,   359,
     361,   396,   398,   414,   402,   404,   408,   406,   412,   410,
     400,   393,   389,     0,   378,   379,   390,   391,   392,   386,
     381,   387,   383,   384,   385,   388,   382,     0,   309,   146,
       0,   313,   311,   316,     0,   305,   306,     0,   295,   296,
     298,   308,   299,   300,   301,   315,   302,   303,   304,   341,
       0,     0,   339,   340,   343,   344,     0,   330,   331,   333,
     334,   335,   336,   337,   338,   185,   187,   182,     0,   180,
     183,   184,     0,   473,   475,     0,   478,     0,     0,   482,
     486,     0,     0,     0,   491,   498,   471,     0,   455,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,    42,     0,     0,    35,     0,     0,     0,
       0,     0,     0,    53,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,   106,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     214,     0,     0,   356,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   376,     0,   285,     0,     0,     0,
       0,     0,     0,     0,   293,     0,     0,     0,     0,   328,
       0,     0,     0,     0,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     454,    46,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    96,    97,     0,     0,     0,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,   440,     0,
       0,    69,     0,     0,   113,   101,   438,   436,   437,   432,
     433,   434,   435,     0,   427,   428,   430,   431,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,     0,     0,
       0,     0,   216,     0,   358,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   380,     0,     0,   307,     0,
       0,     0,   318,   297,     0,   345,   346,   332,     0,     0,
     181,   472,     0,     0,   477,     0,   480,   481,     0,     0,
     488,   489,   490,     0,     0,   456,     0,     0,     0,   501,
     503,   505,     0,   395,     0,     0,   207,   286,   321,   261,
       0,     0,   172,     0,     0,     0,    47,   108,   111,   112,
     110,     0,   425,     0,   241,   243,   245,   349,    36,   366,
     239,   247,   249,   254,   255,   256,   253,   251,   369,     0,
     364,   397,   399,   415,   403,   405,   409,   407,   413,   411,
     401,   310,   147,   314,   312,   317,   342,   186,   188,   474,
     476,   479,   484,   485,   483,   487,   493,   494,   495,   496,
     497,   492,   499,    40,     0,   511,     0,   508,   510,     0,
     133,   139,   141,   143,     0,     0,     0,     0,     0,   152,
     154,   132,     0,   118,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,     0,   211,     0,   208,
     209,   290,     0,   287,   288,   325,     0,   322,   323,   265,
       0,   262,   263,   165,   166,   167,   168,   169,     0,   158,
     160,   161,   162,   163,   164,   422,     0,   176,     0,   173,
     174,     0,     0,     0,     0,     0,     0,     0,   191,   193,
     194,   195,   196,   197,   198,   447,   449,     0,   443,   445,
     446,     0,    49,     0,   429,   353,     0,   350,   351,   373,
       0,   370,   371,   418,     0,    65,     0,     0,   507,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   115,   117,     0,   206,     0,   294,   283,     0,
     329,   320,     0,     0,   260,     0,     0,   157,     0,   421,
       0,   171,     0,     0,     0,     0,     0,     0,     0,     0,
     190,     0,     0,     0,   442,   452,    51,     0,    50,   439,
       0,   348,     0,   377,   368,     0,     0,   417,     0,   509,
       0,     0,     0,     0,   145,   148,   149,   150,   151,     0,
       0,   119,     0,   210,     0,   289,     0,   324,   281,   280,
     272,   273,   275,   269,   270,   271,   278,     0,   267,   274,
     276,   277,   279,   264,   159,   423,     0,   175,   199,   200,
     201,   202,   203,   204,   192,     0,     0,   444,    48,     0,
       0,   352,     0,   372,     0,     0,   135,   136,   137,   138,
     134,   140,   142,   144,   153,   155,   212,   291,   326,     0,
     266,   177,   448,   450,    52,   354,   374,   419,   515,     0,
     513,   268,     0,     0,   512,   527,     0,   525,   523,   519,
       0,   517,   521,   522,   520,   514,     0,     0,     0,     0,
     516,     0,   524,     0,   518,     0,   526,   531,     0,   529,
       0,     0,   528,   539,     0,     0,     0,     0,   533,   535,
     536,   537,   538,   530,     0,     0,     0,     0,     0,   532,
       0,   541,   542,   543,   534,   540
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,   -49,  -688,    90,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,    89,  -688,  -688,  -688,   -62,
    -688,  -688,  -688,   300,  -688,  -688,  -688,  -688,    53,   253,
     -52,   -47,   -44,  -688,  -688,   -41,  -688,  -688,    69,   250,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,    78,  -115,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,   -69,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -128,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -126,  -688,  -688,
    -688,  -123,   218,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -135,  -688,  -688,  -688,  -688,  -688,  -688,  -687,  -688,  -688,
    -688,  -108,  -688,  -688,  -688,  -105,   251,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -685,  -688,  -688,  -688,  -504,
    -688,  -675,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -113,  -688,  -688,  -216,   543,  -688,  -688,  -688,  -688,  -688,
    -103,  -688,  -688,  -688,   -97,  -688,   237,  -688,   -40,  -688,
    -688,  -688,  -688,  -688,   -39,  -688,  -688,  -688,  -688,  -688,
     -51,  -688,  -688,  -688,   -98,  -688,  -688,  -688,   -95,  -688,
     236,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -119,  -688,  -688,  -688,  -116,   273,  -688,  -688,
     -64,  -688,  -688,  -688,  -688,  -688,  -118,  -688,  -688,  -688,
    -117,  -688,   263,   -45,  -688,  -328,  -688,  -322,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -670,  -688,  -688,  -688,  -669,
    -688,  -688,  -688,  -688,  -688,    96,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -102,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,   105,   234,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,  -688,
    -688,  -688,  -688,  -688,  -688,  -688,   -53,  -688,  -688,  -688,
    -198,  -688,  -688,  -213,  -688,  -688,  -688,  -688,  -688,  -688,
    -224,  -688,  -688,  -240,  -688,  -688,  -688,  -688,  -688
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   539,    77,
      78,    37,    60,    74,    75,   527,   672,   737,   738,   114,
      39,    62,    86,    87,    88,   298,    41,    63,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   306,   141,   142,
      43,    64,   143,   329,   144,   330,   530,   145,   124,   310,
     125,   311,   602,   603,   604,   690,   810,   605,   691,   606,
     692,   607,   693,   608,   226,   368,   610,   611,   612,   613,
     614,   699,   615,   700,   126,   320,   638,   639,   640,   641,
     642,   643,   644,   127,   322,   648,   649,   650,   720,    57,
      71,   258,   259,   260,   381,   261,   382,   128,   323,   657,
     658,   659,   660,   661,   662,   663,   664,   129,   316,   618,
     619,   620,   704,    45,    65,   166,   167,   168,   340,   169,
     335,   170,   336,   171,   337,   172,   341,   173,   342,   174,
     346,   175,   345,   546,   176,   177,   130,   319,   630,   631,
     632,   713,   777,   778,   131,   317,    51,    68,   622,   623,
     624,   707,    53,    69,   227,   228,   229,   230,   231,   232,
     233,   367,   234,   371,   235,   370,   236,   237,   372,   238,
     132,   318,   626,   627,   628,   710,    55,    70,   246,   247,
     248,   249,   250,   376,   251,   252,   253,   254,   179,   338,
     676,   677,   678,   740,    47,    66,   187,   188,   189,   351,
     180,   339,   181,   347,   680,   681,   682,   743,    49,    67,
     203,   204,   205,   133,   309,   207,   354,   208,   355,   209,
     363,   210,   357,   211,   358,   212,   360,   213,   359,   214,
     362,   215,   361,   216,   356,   183,   348,   684,   746,   134,
     321,   646,   334,   443,   444,   445,   446,   447,   531,   135,
     136,   325,   667,   668,   669,   731,   670,   732,   137,   326,
      59,    72,   277,   278,   279,   280,   386,   281,   387,   282,
     283,   389,   284,   285,   286,   392,   574,   287,   393,   288,
     289,   290,   291,   397,   581,   292,   398,    89,   300,    90,
     301,    91,   302,    92,   299,   586,   587,   588,   686,   829,
     830,   832,   840,   841,   842,   843,   848,   844,   846,   858,
     859,   860,   867,   868,   869,   874,   870,   871,   872
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   243,   190,   161,   185,   201,   441,   225,   242,   257,
     276,    73,   442,   162,   178,   186,   202,   645,   163,    79,
     182,   164,   206,    27,   165,    28,   774,    29,   775,   146,
     244,   245,   146,   716,   105,   572,   717,   304,   776,    26,
      95,    96,   305,   781,   782,    38,   184,   151,   327,   332,
      96,   191,   192,   328,   333,   349,   255,   256,   255,   256,
     350,    99,   100,   101,   352,    40,   147,   148,   149,   353,
     105,    76,   219,   239,   220,   221,   240,   241,    42,   105,
      44,   150,    46,   151,   152,   153,   154,   155,   156,   157,
     383,    96,   191,   192,    93,   384,   158,   159,   104,   158,
      94,    95,    96,   193,   160,    97,    98,   194,   195,   196,
     197,   198,   199,   219,   200,   218,    84,   543,   544,   545,
     105,   219,    99,   100,   101,   102,   103,    48,    80,    84,
     104,   105,   774,   573,   775,   528,   529,    81,    82,    83,
     219,   106,   220,   221,   776,   436,   222,   223,   224,   781,
     782,   399,    84,    50,   107,   108,   400,   806,   807,   808,
     809,    30,    31,    32,    33,    84,    84,   109,    95,    96,
     110,   327,   665,   666,    84,   687,   685,   111,   112,   863,
     688,   113,   864,   865,   866,   835,    52,   836,   837,    99,
     100,   101,    54,   103,   576,   577,   578,   579,   105,   219,
      56,   633,   634,   635,   636,   441,   637,    84,   138,   139,
      58,   442,   140,   153,   785,    84,   332,   157,   701,   701,
     293,   689,   108,   702,   703,   580,    84,   718,   729,   294,
     719,   295,   160,   730,    84,   651,   652,   653,   654,   655,
     656,   833,    85,   590,   834,   401,   402,   296,   591,   592,
     593,   594,   595,   596,   597,   598,   599,   600,   733,   399,
     297,   349,   819,   734,   735,   438,   816,   820,   219,   383,
     352,   849,   437,   878,   821,   825,   850,   861,   879,   303,
     862,   307,   308,   439,   312,   313,   314,   161,   190,   440,
     185,   315,   324,    84,   331,   343,   344,   162,   178,   365,
     375,   186,   163,   201,   182,   164,   364,   366,   165,   369,
     373,   243,   374,   225,   202,   377,   378,   379,   242,   380,
     206,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   385,   388,   276,   390,   391,
     244,   245,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,   394,   395,   396,   509,   510,   511,
     403,   404,    84,   405,   406,    84,   407,   408,   410,   411,
     413,   414,   415,   416,   412,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   432,
     433,   434,   448,   449,   450,   451,   452,   453,   454,   455,
     457,   458,   459,   460,   456,   461,   463,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   476,   477,   479,
     478,   480,   481,   484,   488,   482,   489,   492,   493,   485,
     486,   491,   495,   494,   498,   499,   503,   496,   497,   504,
     568,   500,   506,   507,   508,   609,   609,   501,   502,   512,
     513,   514,   601,   601,   515,   516,   517,   583,   518,   519,
     520,   521,   522,   276,   438,   523,   524,   525,   526,   532,
     533,   437,   534,   535,   537,    28,   536,   548,   549,   540,
     541,   542,   439,   547,   550,   551,   552,   554,   440,   555,
     556,   557,   558,   617,   621,   625,   559,   560,   561,   562,
     629,   563,   647,   673,   564,   675,   705,   585,   565,   679,
     575,   694,   566,   567,   569,   570,   571,   683,   695,   696,
     697,   698,   706,   709,   708,   582,   712,   711,   714,   715,
     721,   722,   805,   723,   724,   725,   726,   727,   728,   742,
     745,   741,   538,   736,   744,   748,   750,   747,   751,   752,
     753,   759,   760,   795,   796,   799,   553,   798,   804,   739,
     584,   817,   847,   818,   826,   754,   828,   851,   853,   857,
     756,   755,   811,   757,   855,   875,   876,   758,   877,   880,
     431,   589,   435,   788,   789,   790,   761,   791,   784,   792,
     793,   812,   813,   616,   794,   814,   787,   786,   763,   762,
     462,   490,   783,   831,   409,   815,   765,   822,   823,   824,
     764,   217,   483,   827,   767,   766,   487,   852,   856,   885,
     881,   882,   883,   801,   800,   464,   802,   803,   475,   674,
     671,   797,   609,   505,   749,   845,   854,   873,   884,   601,
       0,   243,   161,     0,   773,   225,     0,     0,   242,     0,
       0,   768,   162,   178,     0,     0,     0,   163,   257,   182,
     164,   769,   779,   165,     0,     0,   770,     0,   780,   771,
     244,   245,   772,     0,     0,     0,   190,     0,   185,     0,
       0,   201,     0,     0,     0,     0,     0,     0,     0,   186,
       0,     0,   202,     0,     0,     0,     0,     0,   206,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     773,     0,     0,     0,     0,     0,     0,   768,     0,     0,
       0,     0,     0,   839,     0,     0,     0,   769,   779,     0,
     838,     0,   770,     0,   780,   771,     0,     0,   772,     0,
     839,     0,     0,     0,     0,     0,     0,   838
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    66,    65,    66,    67,   334,    69,    70,    71,
      72,    60,   334,    65,    65,    66,    67,   521,    65,    10,
      65,    65,    67,     5,    65,     7,   713,     9,   713,     7,
      70,    70,     7,     3,    48,    15,     6,     3,   713,     0,
      18,    19,     8,   713,   713,     7,    60,    61,     3,     3,
      19,    20,    21,     8,     8,     3,    85,    86,    85,    86,
       8,    39,    40,    41,     3,     7,    44,    45,    46,     8,
      48,   143,    49,    50,    51,    52,    53,    54,     7,    48,
       7,    59,     7,    61,    62,    63,    64,    65,    66,    67,
       3,    19,    20,    21,    11,     8,    74,    75,    47,    74,
      17,    18,    19,    72,    82,    22,    23,    76,    77,    78,
      79,    80,    81,    49,    83,    24,   143,    68,    69,    70,
      48,    49,    39,    40,    41,    42,    43,     7,   119,   143,
      47,    48,   819,   113,   819,    14,    15,   128,   129,   130,
      49,    58,    51,    52,   819,    73,    55,    56,    57,   819,
     819,     3,   143,     7,    71,    72,     8,    25,    26,    27,
      28,   143,   144,   145,   146,   143,   143,    84,    18,    19,
      87,     3,    96,    97,   143,     3,     8,    94,    95,   122,
       8,    98,   125,   126,   127,   121,     7,   123,   124,    39,
      40,    41,     7,    43,   115,   116,   117,   118,    48,    49,
       7,    76,    77,    78,    79,   533,    81,   143,    12,    13,
       7,   533,    16,    63,   718,   143,     3,    67,     3,     3,
       6,     8,    72,     8,     8,   146,   143,     3,     3,     3,
       6,     4,    82,     8,   143,    88,    89,    90,    91,    92,
      93,     3,   304,    24,     6,   294,   295,     8,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,     3,     3,
       3,     3,     3,     8,     8,   334,     8,     8,    49,     3,
       3,     3,   334,     3,     8,     8,     8,     3,     8,     4,
       6,     4,     4,   334,     4,     4,     4,   349,   352,   334,
     352,     4,     4,   143,     4,     4,     4,   349,   349,     3,
       3,   352,   349,   365,   349,   349,     8,     8,   349,     4,
       4,   380,     8,   375,   365,     4,     4,     8,   380,     3,
     365,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,     4,     4,   399,     4,     4,
     380,   380,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,     4,     4,     4,   406,   407,   408,
     143,     4,   143,     4,     4,   143,     4,     4,     4,   146,
       4,     4,     4,   144,   146,   144,   144,   144,     4,     4,
       4,     4,     4,     4,     4,     4,   144,     4,     4,     4,
       4,   146,     4,     4,     4,     4,     4,     4,     4,     4,
     146,     4,     4,     4,   144,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     144,     4,     4,     4,     4,   146,     4,     4,     4,   146,
     146,   146,     4,   144,     4,     4,     4,   144,   144,     4,
     489,   146,     4,     7,     7,   514,   515,   146,   146,     7,
     143,     7,   514,   515,     7,     5,     5,   506,     5,     5,
       5,     5,     5,   525,   533,     7,     7,     7,     5,     8,
       3,   533,   143,   143,     5,     7,   143,     5,     7,   143,
     143,   143,   533,   143,   143,   143,   143,   143,   533,   143,
     143,   143,   143,     7,     7,     7,   143,   143,   143,   143,
       7,   143,     7,     4,   143,     7,     6,   120,   143,     7,
     114,     4,   143,   143,   143,   143,   143,    83,     4,     4,
       4,     4,     3,     3,     6,   143,     3,     6,     6,     3,
       6,     3,     5,     4,     4,     4,     4,     4,     4,     3,
       3,     6,   452,   143,     6,     4,     4,     8,     4,     4,
       4,     4,     4,     4,     4,     3,   467,     6,     4,   143,
     507,     8,     4,     8,     8,   144,     7,     4,     4,     7,
     144,   146,   143,   146,     5,     4,     4,   144,     4,     4,
     327,   512,   332,   144,   144,   144,   701,   144,   716,   144,
     144,   143,   143,   515,   729,   143,   722,   720,   706,   704,
     349,   383,   715,   819,   304,   143,   709,   143,   143,   143,
     707,    68,   375,   143,   712,   710,   380,   144,   143,   143,
     146,   144,   144,   742,   740,   352,   743,   745,   365,   533,
     525,   733,   701,   399,   687,   833,   849,   861,   878,   701,
      -1,   710,   704,    -1,   713,   707,    -1,    -1,   710,    -1,
      -1,   713,   704,   704,    -1,    -1,    -1,   704,   720,   704,
     704,   713,   713,   704,    -1,    -1,   713,    -1,   713,   713,
     710,   710,   713,    -1,    -1,    -1,   740,    -1,   740,    -1,
      -1,   743,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   740,
      -1,    -1,   743,    -1,    -1,    -1,    -1,    -1,   743,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     819,    -1,    -1,    -1,    -1,    -1,    -1,   819,    -1,    -1,
      -1,    -1,    -1,   832,    -1,    -1,    -1,   819,   819,    -1,
     832,    -1,   819,    -1,   819,   819,    -1,    -1,   819,    -1,
     849,    -1,    -1,    -1,    -1,    -1,    -1,   849
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,     0,     5,     7,     9,
     143,   144,   145,   146,   161,   162,   163,   168,     7,   177,
       7,   183,     7,   197,     7,   270,     7,   351,     7,   365,
       7,   303,     7,   309,     7,   333,     7,   246,     7,   417,
     169,   164,   178,   184,   198,   271,   352,   366,   304,   310,
     334,   247,   418,   161,   170,   171,   143,   166,   167,    10,
     119,   128,   129,   130,   143,   176,   179,   180,   181,   444,
     446,   448,   450,    11,    17,    18,    19,    22,    23,    39,
      40,    41,    42,    43,    47,    48,    58,    71,    72,    84,
      87,    94,    95,    98,   176,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   205,   207,   231,   240,   254,   264,
     293,   301,   327,   370,   396,   406,   407,   415,    12,    13,
      16,   195,   196,   199,   201,   204,     7,    44,    45,    46,
      59,    61,    62,    63,    64,    65,    66,    67,    74,    75,
      82,   176,   187,   188,   189,   192,   272,   273,   274,   276,
     278,   280,   282,   284,   286,   288,   291,   292,   327,   345,
     357,   359,   370,   392,    60,   176,   327,   353,   354,   355,
     357,    20,    21,    72,    76,    77,    78,    79,    80,    81,
      83,   176,   327,   367,   368,   369,   370,   372,   374,   376,
     378,   380,   382,   384,   386,   388,   390,   301,    24,    49,
      51,    52,    55,    56,    57,   176,   221,   311,   312,   313,
     314,   315,   316,   317,   319,   321,   323,   324,   326,    50,
      53,    54,   176,   221,   315,   321,   335,   336,   337,   338,
     339,   341,   342,   343,   344,    85,    86,   176,   248,   249,
     250,   252,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   176,   419,   420,   421,
     422,   424,   426,   427,   429,   430,   431,   434,   436,   437,
     438,   439,   442,     6,     3,     4,     8,     3,   182,   451,
     445,   447,   449,     4,     3,     8,   194,     4,     4,   371,
     206,   208,     4,     4,     4,     4,   265,   302,   328,   294,
     232,   397,   241,   255,     4,   408,   416,     3,     8,   200,
     202,     4,     3,     8,   399,   277,   279,   281,   346,   358,
     275,   283,   285,     4,     4,   289,   287,   360,   393,     3,
       8,   356,     3,     8,   373,   375,   391,   379,   381,   385,
     383,   389,   387,   377,     8,     3,     8,   318,   222,     4,
     322,   320,   325,     4,     8,     3,   340,     4,     4,     8,
       3,   251,   253,     3,     8,     4,   423,   425,     4,   428,
       4,     4,   432,   435,     4,     4,     4,   440,   443,     3,
       8,   161,   161,   143,     4,     4,     4,     4,     4,   180,
       4,   146,   146,     4,     4,     4,   144,   144,   144,   144,
       4,     4,     4,     4,     4,     4,     4,     4,   144,     4,
       4,   186,     4,     4,   146,   196,    73,   176,   221,   327,
     370,   372,   374,   400,   401,   402,   403,   404,     4,     4,
       4,     4,     4,     4,     4,     4,   144,   146,     4,     4,
       4,     4,   273,     4,   354,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   369,     4,     4,   144,     4,
       4,     4,   146,   313,     4,   146,   146,   337,     4,     4,
     249,   146,     4,     4,   144,     4,   144,   144,     4,     4,
     146,   146,   146,     4,     4,   420,     4,     7,     7,   161,
     161,   161,     7,   143,     7,     7,     5,     5,     5,     5,
       5,     5,     5,     7,     7,     7,     5,   172,    14,    15,
     203,   405,     8,     3,   143,   143,   143,     5,   163,   165,
     143,   143,   143,    68,    69,    70,   290,   143,     5,     7,
     143,   143,   143,   172,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   161,   143,
     143,   143,    15,   113,   433,   114,   115,   116,   117,   118,
     146,   441,   143,   161,   185,   120,   452,   453,   454,   195,
      24,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,   176,   209,   210,   211,   214,   216,   218,   220,   221,
     223,   224,   225,   226,   227,   229,   209,     7,   266,   267,
     268,     7,   305,   306,   307,     7,   329,   330,   331,     7,
     295,   296,   297,    76,    77,    78,    79,    81,   233,   234,
     235,   236,   237,   238,   239,   286,   398,     7,   242,   243,
     244,    88,    89,    90,    91,    92,    93,   256,   257,   258,
     259,   260,   261,   262,   263,    96,    97,   409,   410,   411,
     413,   419,   173,     4,   402,     7,   347,   348,   349,     7,
     361,   362,   363,    83,   394,     8,   455,     3,     8,     8,
     212,   215,   217,   219,     4,     4,     4,     4,     4,   228,
     230,     3,     8,     8,   269,     6,     3,   308,     6,     3,
     332,     6,     3,   298,     6,     3,     3,     6,     3,     6,
     245,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   412,   414,     3,     8,     8,   143,   174,   175,   143,
     350,     6,     3,   364,     6,     3,   395,     8,     4,   453,
       4,     4,     4,     4,   144,   146,   144,   146,   144,     4,
       4,   210,   272,   268,   311,   307,   335,   331,   176,   187,
     188,   189,   192,   221,   264,   282,   288,   299,   300,   327,
     370,   392,   396,   297,   234,   286,   248,   244,   144,   144,
     144,   144,   144,   144,   257,     4,     4,   410,     6,     3,
     353,   349,   367,   363,     4,     5,    25,    26,    27,    28,
     213,   143,   143,   143,   143,   143,     8,     8,     8,     3,
       8,     8,   143,   143,   143,     8,     8,   143,     7,   456,
     457,   300,   458,     3,     6,   121,   123,   124,   176,   221,
     459,   460,   461,   462,   464,   457,   465,     4,   463,     3,
       8,     4,   144,     4,   460,     5,   143,     7,   466,   467,
     468,     3,     6,   122,   125,   126,   127,   469,   470,   471,
     473,   474,   475,   467,   472,     4,     4,     4,     3,     8,
       4,   146,   144,   144,   470,   143
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   147,   149,   148,   150,   148,   151,   148,   152,   148,
     153,   148,   154,   148,   155,   148,   156,   148,   157,   148,
     158,   148,   159,   148,   160,   148,   161,   161,   161,   161,
     161,   161,   161,   162,   164,   163,   165,   166,   166,   167,
     167,   169,   168,   170,   170,   171,   171,   173,   172,   174,
     174,   175,   175,   176,   178,   177,   179,   179,   180,   180,
     180,   180,   180,   180,   182,   181,   184,   183,   185,   185,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   187,   188,   189,   190,   191,   192,   194,   193,
     195,   195,   196,   196,   196,   198,   197,   200,   199,   202,
     201,   203,   203,   204,   206,   205,   208,   207,   209,   209,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   212,   211,   213,   213,   213,   213,   215,
     214,   217,   216,   219,   218,   220,   222,   221,   223,   224,
     225,   226,   228,   227,   230,   229,   232,   231,   233,   233,
     234,   234,   234,   234,   234,   235,   236,   237,   238,   239,
     241,   240,   242,   242,   243,   243,   245,   244,   247,   246,
     248,   248,   248,   249,   249,   251,   250,   253,   252,   255,
     254,   256,   256,   257,   257,   257,   257,   257,   257,   258,
     259,   260,   261,   262,   263,   265,   264,   266,   266,   267,
     267,   269,   268,   271,   270,   272,   272,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   275,   274,
     277,   276,   279,   278,   281,   280,   283,   282,   285,   284,
     287,   286,   289,   288,   290,   290,   290,   291,   292,   294,
     293,   295,   295,   296,   296,   298,   297,   299,   299,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   302,   301,   304,   303,   305,   305,   306,   306,
     308,   307,   310,   309,   311,   311,   312,   312,   313,   313,
     313,   313,   313,   313,   313,   313,   314,   315,   316,   318,
     317,   320,   319,   322,   321,   323,   325,   324,   326,   328,
     327,   329,   329,   330,   330,   332,   331,   334,   333,   335,
     335,   336,   336,   337,   337,   337,   337,   337,   337,   337,
     338,   340,   339,   341,   342,   343,   344,   346,   345,   347,
     347,   348,   348,   350,   349,   352,   351,   353,   353,   354,
     354,   354,   354,   356,   355,   358,   357,   360,   359,   361,
     361,   362,   362,   364,   363,   366,   365,   367,   367,   368,
     368,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   371,   370,   373,   372,   375,   374,
     377,   376,   379,   378,   381,   380,   383,   382,   385,   384,
     387,   386,   389,   388,   391,   390,   393,   392,   395,   394,
     397,   396,   398,   398,   399,   286,   400,   400,   401,   401,
     402,   402,   402,   402,   402,   402,   402,   403,   405,   404,
     406,   408,   407,   409,   409,   410,   410,   412,   411,   414,
     413,   416,   415,   418,   417,   419,   419,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   420,   421,   423,   422,   425,   424,   426,   428,   427,
     429,   430,   432,   431,   433,   433,   435,   434,   436,   437,
     438,   440,   439,   441,   441,   441,   441,   441,   443,   442,
     445,   444,   447,   446,   449,   448,   451,   450,   452,   452,
     453,   455,   454,   456,   456,   458,   457,   459,   459,   460,
     460,   460,   460,   460,   461,   463,   462,   465,   464,   466,
     466,   468,   467,   469,   469,   470,   470,   470,   470,   472,
     471,   473,   474,   475
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
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
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     3,     0,     6,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"re-detect\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"subnet\"", "\"interface\"", "\"interface-id\"", "\"id\"",
  "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"duid\"", "\"hw-address\"", "\"circuit-id\"", "\"client-id\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "value", "sub_json",
  "map2", "$@13", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@14", "list_content", "not_empty_list", "list_strings",
  "$@15", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@16", "global_objects",
  "global_object", "dhcp4_object", "$@17", "sub_dhcp4", "$@18",
  "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@19",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@20", "interfaces_list", "$@21", "dhcp_socket_type", "$@22",
  "socket_type", "re_detect", "lease_database", "$@23", "hosts_database",
  "$@24", "database_map_params", "database_map_param", "database_type",
  "$@25", "db_type", "user", "$@26", "password", "$@27", "host", "$@28",
  "port", "name", "$@29", "persist", "lfc_interval", "readonly",
  "connect_timeout", "contact_points", "$@30", "keyspace", "$@31",
  "host_reservation_identifiers", "$@32",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@33", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@34",
  "sub_hooks_library", "$@35", "hooks_params", "hooks_param", "library",
  "$@36", "parameters", "$@37", "expired_leases_processing", "$@38",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@39",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@40",
  "sub_subnet4", "$@41", "subnet4_params", "subnet4_param", "subnet",
  "$@42", "subnet_4o6_interface", "$@43", "subnet_4o6_interface_id",
  "$@44", "subnet_4o6_subnet", "$@45", "interface", "$@46", "interface_id",
  "$@47", "client_class", "$@48", "reservation_mode", "$@49", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@50",
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
  "not_empty_pools_list", "pool_list_entry", "$@65", "sub_pool4", "$@66",
  "pool_params", "pool_param", "pool_entry", "$@67", "user_context",
  "$@68", "reservations", "$@69", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@70", "sub_reservation",
  "$@71", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@72", "server_hostname", "$@73",
  "boot_file_name", "$@74", "ip_address", "$@75", "duid", "$@76",
  "hw_address", "$@77", "client_id_value", "$@78", "circuit_id_value",
  "$@79", "flex_id_value", "$@80", "hostname", "$@81",
  "reservation_client_classes", "$@82", "relay", "$@83", "relay_map",
  "$@84", "client_classes", "$@85", "client_classes_list", "$@86",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@87",
  "dhcp4o6_port", "control_socket", "$@88", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@89",
  "control_socket_name", "$@90", "dhcp_ddns", "$@91", "sub_dhcp_ddns",
  "$@92", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@93", "server_ip", "$@94", "server_port",
  "sender_ip", "$@95", "sender_port", "max_queue_size", "ncr_protocol",
  "$@96", "ncr_protocol_value", "ncr_format", "$@97",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@98", "replace_client_name_value",
  "generated_prefix", "$@99", "dhcp6_json_object", "$@100",
  "dhcpddns_json_object", "$@101", "control_agent_json_object", "$@102",
  "logging_object", "$@103", "logging_params", "logging_param", "loggers",
  "$@104", "loggers_entries", "logger_entry", "$@105", "logger_params",
  "logger_param", "debuglevel", "severity", "$@106", "output_options_list",
  "$@107", "output_options_list_content", "output_entry", "$@108",
  "output_params_list", "output_params", "output", "$@109", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   229,   229,   229,   230,   230,   231,   231,   232,   232,
     233,   233,   234,   234,   235,   235,   236,   236,   237,   237,
     238,   238,   239,   239,   240,   240,   248,   249,   250,   251,
     252,   253,   254,   257,   262,   262,   273,   276,   277,   280,
     284,   291,   291,   298,   299,   302,   306,   313,   313,   320,
     321,   324,   328,   339,   349,   349,   365,   366,   370,   371,
     372,   373,   374,   375,   378,   378,   393,   393,   402,   403,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   432,   437,   442,   447,   452,   457,   463,   463,
     474,   475,   478,   479,   480,   483,   483,   492,   492,   502,
     502,   509,   510,   513,   519,   519,   531,   531,   543,   544,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   562,   562,   569,   570,   571,   572,   575,
     575,   583,   583,   591,   591,   599,   604,   604,   612,   617,
     622,   627,   632,   632,   640,   640,   649,   649,   659,   660,
     663,   664,   665,   666,   667,   670,   675,   680,   685,   690,
     695,   695,   705,   706,   709,   710,   713,   713,   723,   723,
     733,   734,   735,   738,   739,   742,   742,   750,   750,   758,
     758,   769,   770,   773,   774,   775,   776,   777,   778,   781,
     786,   791,   796,   801,   806,   814,   814,   827,   828,   831,
     832,   839,   839,   865,   865,   876,   877,   881,   882,   883,
     884,   885,   886,   887,   888,   889,   890,   891,   892,   893,
     894,   895,   896,   897,   898,   899,   900,   901,   904,   904,
     912,   912,   920,   920,   928,   928,   936,   936,   944,   944,
     952,   952,   960,   960,   967,   968,   969,   972,   977,   984,
     984,   995,   996,  1000,  1001,  1004,  1004,  1012,  1013,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1035,  1035,  1048,  1048,  1057,  1058,  1061,  1062,
    1067,  1067,  1082,  1082,  1096,  1097,  1100,  1101,  1104,  1105,
    1106,  1107,  1108,  1109,  1110,  1111,  1114,  1116,  1121,  1123,
    1123,  1131,  1131,  1139,  1139,  1147,  1149,  1149,  1157,  1166,
    1166,  1178,  1179,  1184,  1185,  1190,  1190,  1202,  1202,  1214,
    1215,  1220,  1221,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1235,  1237,  1237,  1245,  1247,  1249,  1254,  1262,  1262,  1274,
    1275,  1278,  1279,  1282,  1282,  1292,  1292,  1302,  1303,  1306,
    1307,  1308,  1309,  1312,  1312,  1320,  1320,  1330,  1330,  1340,
    1341,  1344,  1345,  1348,  1348,  1357,  1357,  1366,  1367,  1370,
    1371,  1375,  1376,  1377,  1378,  1379,  1380,  1381,  1382,  1383,
    1384,  1385,  1386,  1387,  1390,  1390,  1398,  1398,  1406,  1406,
    1414,  1414,  1422,  1422,  1430,  1430,  1438,  1438,  1446,  1446,
    1454,  1454,  1462,  1462,  1470,  1470,  1483,  1483,  1493,  1493,
    1504,  1504,  1514,  1515,  1518,  1518,  1528,  1529,  1532,  1533,
    1536,  1537,  1538,  1539,  1540,  1541,  1542,  1545,  1547,  1547,
    1559,  1566,  1566,  1576,  1577,  1580,  1581,  1584,  1584,  1592,
    1592,  1602,  1602,  1614,  1614,  1624,  1625,  1628,  1629,  1630,
    1631,  1632,  1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,
    1641,  1642,  1645,  1650,  1650,  1658,  1658,  1666,  1671,  1671,
    1679,  1684,  1689,  1689,  1697,  1698,  1701,  1701,  1709,  1714,
    1719,  1724,  1724,  1732,  1735,  1738,  1741,  1744,  1750,  1750,
    1760,  1760,  1767,  1767,  1774,  1774,  1786,  1786,  1799,  1800,
    1804,  1808,  1808,  1820,  1821,  1825,  1825,  1833,  1834,  1837,
    1838,  1839,  1840,  1841,  1844,  1849,  1849,  1857,  1857,  1867,
    1868,  1871,  1871,  1879,  1880,  1883,  1884,  1885,  1886,  1889,
    1889,  1897,  1902,  1907
  };

  // Print the state stack on the debug stream.
  void
  Dhcp4Parser::yystack_print_ ()
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4320 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1912 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
