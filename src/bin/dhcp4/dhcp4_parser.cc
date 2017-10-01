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

  case 94:
#line 434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 571 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 572 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 574 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 577 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 579 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1271 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1391 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1418 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1427 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1531 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1635 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 845 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 215:
#line 867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1717 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 976 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1122 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1129 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1131 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1139 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1177 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2118 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2193 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2279 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2517 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2575 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2642 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1704 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1748 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2942 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -701;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     248,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,    40,    32,    35,    45,    49,    65,    67,
      71,    74,    76,    91,   114,   148,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
      32,     4,     3,   141,   208,    25,     7,   186,   109,     2,
      59,   -24,   266,  -701,   160,   176,   183,   202,   220,  -701,
    -701,  -701,  -701,  -701,   247,  -701,    77,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,   268,   271,  -701,  -701,  -701,  -701,
    -701,   272,   273,   279,   281,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,   282,  -701,  -701,  -701,    94,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,   283,   117,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,   284,
     285,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
     136,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,   140,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,   245,   267,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,   286,  -701,  -701,   287,  -701,  -701,  -701,   288,  -701,
    -701,   289,   296,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,   297,   298,  -701,  -701,  -701,  -701,
     292,   303,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,   162,  -701,  -701,  -701,   305,  -701,  -701,   310,
    -701,   312,   319,  -701,  -701,   324,   326,   327,  -701,  -701,
    -701,   164,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,    32,    32,
    -701,   190,   330,   331,   332,   333,   336,  -701,     3,  -701,
     338,   197,   209,   350,   352,   353,   354,   355,   216,   250,
     255,   256,   387,   388,   389,   391,   392,   393,   394,   397,
     258,   399,   400,   141,  -701,   401,   402,   261,   208,  -701,
      28,   404,   406,   407,   408,   409,   410,   411,   412,   274,
     275,   413,   415,   416,   418,    25,  -701,   419,     7,  -701,
     420,   421,   422,   423,   424,   425,   426,   427,  -701,   186,
    -701,   428,   429,   290,   431,   432,   433,   293,  -701,     2,
     434,   294,   295,  -701,    59,   438,   439,   -52,  -701,   300,
     440,   443,   304,   445,   306,   307,   450,   451,   311,   317,
     318,   452,   457,   266,  -701,  -701,  -701,   461,   459,   460,
      32,    32,    32,  -701,   462,  -701,  -701,   325,   329,   334,
     466,   468,  -701,  -701,  -701,  -701,   471,   474,   475,   476,
     477,   478,   479,   480,  -701,   481,   482,  -701,   486,   126,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
     484,   483,  -701,  -701,  -701,   342,   351,   356,   488,   489,
     357,   358,   359,  -701,  -701,    60,   361,   492,   498,  -701,
     363,  -701,   486,   364,   365,   366,   367,   368,   369,   370,
    -701,   371,   372,  -701,   373,   374,   375,  -701,  -701,   376,
    -701,  -701,  -701,   377,    32,  -701,  -701,   378,   379,  -701,
     380,  -701,  -701,    23,   414,  -701,  -701,  -701,   -12,   381,
    -701,    32,   141,   405,  -701,  -701,  -701,   208,  -701,  -701,
    -701,   315,   315,   519,   520,   522,   523,   138,    43,   524,
     102,    89,   266,  -701,  -701,  -701,  -701,  -701,   528,  -701,
      28,  -701,  -701,  -701,   526,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,   527,   453,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,   166,
    -701,   193,  -701,  -701,   195,  -701,  -701,  -701,  -701,   531,
     533,   534,   535,   536,  -701,  -701,  -701,   219,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,   229,  -701,   537,   538,  -701,  -701,   539,   541,  -701,
    -701,   540,   544,  -701,  -701,   542,   546,  -701,  -701,  -701,
    -701,  -701,  -701,    57,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,   194,  -701,   545,   547,  -701,   548,   549,   550,   551,
     552,   553,   230,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,   237,  -701,  -701,  -701,   239,   417,   430,  -701,
    -701,   555,   556,  -701,  -701,   557,   559,  -701,  -701,   558,
    -701,   554,   405,  -701,  -701,   560,   561,   563,   564,   398,
     435,   436,   437,   441,   565,   566,   315,  -701,  -701,    25,
    -701,   519,     2,  -701,   520,    59,  -701,   522,    75,  -701,
     523,   138,  -701,    43,  -701,   -24,  -701,   524,   442,   444,
     446,   447,   448,   449,   102,  -701,   567,   568,    89,  -701,
    -701,  -701,   569,   571,  -701,     7,  -701,   526,   186,  -701,
     527,   572,  -701,   573,  -701,   254,   454,   455,   456,  -701,
    -701,  -701,  -701,  -701,   458,   463,  -701,   240,  -701,   574,
    -701,   576,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,   249,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,   251,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,   464,   465,  -701,  -701,   467,   252,  -701,   579,
    -701,   469,   570,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,    75,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,   205,  -701,  -701,    30,
     570,  -701,  -701,   575,  -701,  -701,  -701,   253,  -701,  -701,
    -701,  -701,  -701,   585,   470,   590,    30,  -701,   591,  -701,
     472,  -701,   588,  -701,  -701,   238,  -701,   104,   588,  -701,
    -701,   596,   598,   599,   265,  -701,  -701,  -701,  -701,  -701,
    -701,   600,   473,   485,   487,   104,  -701,   490,  -701,  -701,
    -701,  -701,  -701
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   107,     9,   215,    11,   361,    13,   381,    15,
     290,    17,   298,    19,   333,    21,   180,    23,   460,    25,
      43,    37,     0,     0,     0,     0,     0,   383,     0,   300,
     335,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     513,   507,   509,   511,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   100,     0,     0,   400,   402,   404,   116,
     118,     0,     0,     0,     0,   207,   288,   325,   263,   158,
     426,   172,   191,     0,   448,   458,    93,     0,    68,    70,
      71,    72,    73,    88,    89,    76,    77,    78,    79,    83,
      84,    74,    75,    81,    82,    90,    91,    92,    80,    85,
      86,    87,   109,   111,     0,     0,   102,   104,   105,   106,
     430,   244,   246,   248,   353,   371,   242,   250,   252,     0,
       0,   256,   254,   373,   422,   241,   219,   220,   221,   233,
       0,   217,   224,   237,   238,   239,   225,   226,   229,   231,
     227,   228,   222,   223,   240,   230,   234,   235,   236,   232,
     369,   368,   366,     0,   363,   365,   367,   420,   408,   410,
     414,   412,   418,   416,   406,   399,   395,     0,   384,   385,
     396,   397,   398,   392,   387,   393,   389,   390,   391,   394,
     388,     0,   315,   148,     0,   319,   317,   322,     0,   311,
     312,     0,   301,   302,   304,   314,   305,   306,   307,   321,
     308,   309,   310,   347,     0,     0,   345,   346,   349,   350,
       0,   336,   337,   339,   340,   341,   342,   343,   344,   187,
     189,   184,     0,   182,   185,   186,     0,   480,   482,     0,
     485,     0,     0,   489,   493,     0,     0,     0,   498,   505,
     478,     0,   462,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,    42,     0,     0,
      35,     0,     0,     0,     0,     0,     0,    53,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,   108,
     432,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   216,     0,     0,   362,
       0,     0,     0,     0,     0,     0,     0,     0,   382,     0,
     291,     0,     0,     0,     0,     0,     0,     0,   299,     0,
       0,     0,     0,   334,     0,     0,     0,     0,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   461,    46,    39,     0,     0,     0,
       0,     0,     0,    57,     0,    98,    99,     0,     0,     0,
       0,     0,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,   447,     0,     0,    69,     0,     0,
     115,   103,   445,   443,   444,   438,   439,   440,   441,   442,
       0,   433,   434,   436,   437,     0,     0,     0,     0,     0,
       0,     0,     0,   261,   262,     0,     0,     0,     0,   218,
       0,   364,     0,     0,     0,     0,     0,     0,     0,     0,
     386,     0,     0,   313,     0,     0,     0,   324,   303,     0,
     351,   352,   338,     0,     0,   183,   479,     0,     0,   484,
       0,   487,   488,     0,     0,   495,   496,   497,     0,     0,
     463,     0,     0,     0,   508,   510,   512,     0,   401,   403,
     405,     0,     0,   209,   292,   327,   265,     0,     0,   174,
       0,     0,     0,    47,   110,   113,   114,   112,     0,   431,
       0,   245,   247,   249,   355,    36,   372,   243,   251,   253,
     258,   259,   260,   257,   255,   375,     0,   370,   421,   409,
     411,   415,   413,   419,   417,   407,   316,   149,   320,   318,
     323,   348,   188,   190,   481,   483,   486,   491,   492,   490,
     494,   500,   501,   502,   503,   504,   499,   506,    40,     0,
     518,     0,   515,   517,     0,   135,   141,   143,   145,     0,
       0,     0,     0,     0,   154,   156,   134,     0,   120,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   213,     0,   210,   211,   296,     0,   293,   294,
     331,     0,   328,   329,   269,     0,   266,   267,   167,   168,
     169,   170,   171,     0,   160,   162,   163,   164,   165,   166,
     428,     0,   178,     0,   175,   176,     0,     0,     0,     0,
       0,     0,     0,   193,   195,   196,   197,   198,   199,   200,
     454,   456,     0,   450,   452,   453,     0,    49,     0,   435,
     359,     0,   356,   357,   379,     0,   376,   377,   424,     0,
      65,     0,     0,   514,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   119,     0,
     208,     0,   300,   289,     0,   335,   326,     0,     0,   264,
       0,     0,   159,     0,   427,     0,   173,     0,     0,     0,
       0,     0,     0,     0,     0,   192,     0,     0,     0,   449,
     459,    51,     0,    50,   446,     0,   354,     0,   383,   374,
       0,     0,   423,     0,   516,     0,     0,     0,     0,   147,
     150,   151,   152,   153,     0,     0,   121,     0,   212,     0,
     295,     0,   330,   287,   286,   276,   277,   279,   273,   274,
     275,   285,   284,     0,   271,   278,   280,   281,   282,   283,
     268,   161,   429,     0,   177,   201,   202,   203,   204,   205,
     206,   194,     0,     0,   451,    48,     0,     0,   358,     0,
     378,     0,     0,   137,   138,   139,   140,   136,   142,   144,
     146,   155,   157,   214,   297,   332,     0,   270,   179,   455,
     457,    52,   360,   380,   425,   522,     0,   520,   272,     0,
       0,   519,   534,     0,   532,   530,   526,     0,   524,   528,
     529,   527,   521,     0,     0,     0,     0,   523,     0,   531,
       0,   525,     0,   533,   538,     0,   536,     0,     0,   535,
     546,     0,     0,     0,     0,   540,   542,   543,   544,   545,
     537,     0,     0,     0,     0,     0,   539,     0,   548,   549,
     550,   541,   547
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,   -49,  -701,   146,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,   137,  -701,  -701,  -701,   -62,
    -701,  -701,  -701,   308,  -701,  -701,  -701,  -701,    99,   280,
     -44,   -34,   -30,  -701,  -701,   -29,  -701,  -701,   100,   301,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,    96,   -86,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,   -69,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -100,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -105,  -701,  -701,
    -701,  -102,   241,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -110,  -701,  -701,  -701,  -701,  -701,  -701,  -700,  -701,  -701,
    -701,   -85,  -701,  -701,  -701,   -84,   277,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -699,  -701,  -701,  -701,  -514,
    -701,  -691,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
     -93,  -701,  -701,  -196,   -66,  -701,  -701,  -701,  -701,  -701,
     -80,  -701,  -701,  -701,   -77,  -701,   257,  -701,   -64,  -701,
    -701,  -701,  -701,  -701,   -46,  -701,  -701,  -701,  -701,  -701,
     -50,  -701,  -701,  -701,   -79,  -701,  -701,  -701,   -75,  -701,
     259,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -106,  -701,  -701,  -701,  -103,   299,  -701,  -701,
     -54,  -701,  -701,  -701,  -701,  -701,   -98,  -701,  -701,  -701,
     -94,  -701,   276,   -45,  -701,   -42,  -701,   -37,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -689,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,   108,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,   -83,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,   128,   263,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,  -701,
    -701,  -701,  -701,  -701,  -701,  -701,   -31,  -701,  -701,  -701,
    -182,  -701,  -701,  -194,  -701,  -701,  -701,  -701,  -701,  -701,
    -198,  -701,  -701,  -214,  -701,  -701,  -701,  -701,  -701
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   546,    77,
      78,    37,    60,    74,    75,   534,   677,   742,   743,   116,
      39,    62,    86,    87,    88,   302,    41,    63,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   310,   145,   146,
      43,    64,   147,   335,   148,   336,   537,   149,   126,   316,
     127,   317,   607,   608,   609,   695,   817,   610,   696,   611,
     697,   612,   698,   613,   230,   372,   615,   616,   617,   618,
     619,   704,   620,   705,   128,   326,   643,   644,   645,   646,
     647,   648,   649,   129,   328,   653,   654,   655,   725,    57,
      71,   262,   263,   264,   385,   265,   386,   130,   329,   662,
     663,   664,   665,   666,   667,   668,   669,   131,   322,   623,
     624,   625,   709,    45,    65,   170,   171,   172,   346,   173,
     341,   174,   342,   175,   343,   176,   347,   177,   348,   178,
     352,   179,   351,   553,   180,   181,   132,   325,   635,   636,
     637,   718,   783,   784,   133,   323,    51,    68,   627,   628,
     629,   712,    53,    69,   231,   232,   233,   234,   235,   236,
     237,   371,   238,   375,   239,   374,   240,   241,   376,   242,
     134,   324,   631,   632,   633,   715,    55,    70,   250,   251,
     252,   253,   254,   380,   255,   256,   257,   258,   183,   344,
     681,   682,   683,   745,    47,    66,   193,   194,   195,   357,
     184,   345,   185,   353,   685,   686,   687,   748,    49,    67,
     207,   208,   209,   135,   313,   136,   314,   137,   315,   213,
     367,   214,   361,   215,   362,   216,   364,   217,   363,   218,
     366,   219,   365,   220,   360,   189,   354,   689,   751,   138,
     327,   651,   340,   450,   451,   452,   453,   454,   538,   139,
     140,   331,   672,   673,   674,   736,   675,   737,   141,   332,
      59,    72,   281,   282,   283,   284,   390,   285,   391,   286,
     287,   393,   288,   289,   290,   396,   579,   291,   397,   292,
     293,   294,   295,   401,   586,   296,   402,    89,   304,    90,
     305,    91,   306,    92,   303,   591,   592,   593,   691,   836,
     837,   839,   847,   848,   849,   850,   855,   851,   853,   865,
     866,   867,   874,   875,   876,   881,   877,   878,   879
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   247,   221,   165,   191,   205,   248,   229,   246,   261,
     280,    73,   196,    79,   650,   182,   192,   206,   779,   780,
     186,   166,   210,   187,   249,   211,   222,   782,   188,   789,
     212,   167,   150,   259,   260,   168,   169,    27,   577,    28,
      26,    29,    38,    95,    96,    97,    98,    96,    97,    98,
     150,   223,    40,   224,   225,   107,    42,   226,   227,   228,
     721,   259,   260,   722,   101,   102,   103,   190,   155,   151,
     152,   153,    44,   107,    46,   106,   107,   223,    48,   223,
     308,    50,   150,    52,   154,   309,   155,   156,   157,   158,
     159,   160,   161,    95,    96,    97,    98,   333,    54,   162,
     163,   442,   334,   581,   582,   583,   584,   164,   223,   243,
     224,   225,   244,   245,   101,   102,   103,   162,   105,    84,
     338,    56,    80,   107,   223,   339,   779,   780,   550,   551,
     552,    81,    82,    83,   585,   782,   578,   789,   157,   355,
     535,   536,   161,   358,   356,    84,    84,    76,   359,   162,
      84,   842,    93,   843,   844,    58,   106,   164,    94,    95,
      96,    97,    98,    99,   100,   387,   297,   403,    84,   333,
     388,    84,   404,    84,   690,    30,    31,    32,    33,   298,
     101,   102,   103,   104,   105,   670,   671,   299,   106,   107,
     656,   657,   658,   659,   660,   661,   692,   723,   338,   108,
     724,   693,    84,   694,   781,    96,    97,    98,   840,   792,
     300,   841,   109,   110,   638,   639,   640,   641,    84,   642,
     142,   143,   706,   301,   144,   111,   870,   707,   112,   871,
     872,   873,   706,   734,   107,   113,   114,   708,   735,   115,
     738,   868,   403,   355,   869,   739,    85,   740,   823,   405,
     406,   307,   826,   368,   387,   358,   856,   827,   197,   828,
     832,   857,   198,   199,   200,   201,   202,   203,   885,   204,
     369,   444,   311,   886,   445,   312,   318,   319,   443,   813,
     814,   815,   816,   320,    84,   321,   330,   337,   349,   350,
     446,   373,   377,   165,   370,   447,   191,   378,   448,   379,
     383,   381,   382,   449,   196,   182,   384,   205,   192,   389,
     186,   166,   781,   187,   392,   247,   394,   229,   188,   206,
     248,   167,   246,   395,   210,   168,   169,   211,   398,    84,
     399,   400,   212,   407,   408,   409,   410,   411,   249,   595,
     412,   280,   414,   415,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   417,   416,   418,   419,   420,   421,
     422,   514,   515,   516,   223,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,   426,   427,   428,   423,   429,   430,   431,   432,   424,
     425,   433,   434,   435,   436,   438,   439,   440,   455,    84,
     456,   457,   458,   459,   460,   461,   462,   465,   463,   466,
     467,   464,   468,   470,   472,   473,   474,   475,   476,   477,
     478,   479,   481,   482,   483,   484,   485,   486,   489,   487,
     490,   491,   493,   494,   497,   573,   496,   498,   499,   500,
     501,   502,   614,   614,   503,   504,   508,   505,    84,   606,
     606,   509,   588,   506,   507,   511,   512,   513,   518,   517,
     280,   444,   519,   521,   445,   522,   523,   520,   443,   524,
     525,   526,   527,   528,   529,   541,   540,   530,   531,   532,
     446,   533,   539,   544,   542,   447,    28,   555,   448,   543,
     547,   548,   549,   449,   554,   556,   557,   559,   560,   561,
     562,   563,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   574,   575,   576,   587,   590,   622,   626,   580,   630,
     634,   652,   678,   680,   684,   699,   688,   700,   701,   702,
     703,   711,   759,   710,   714,   713,   716,   717,   719,   720,
     727,   726,   728,   729,   730,   731,   732,   733,   753,   747,
     741,   746,   750,   749,   755,   756,   752,   757,   758,   764,
     765,   802,   803,   744,   806,   805,   811,   835,   812,   854,
     761,   760,   824,   762,   825,   763,   795,   833,   796,   858,
     797,   798,   799,   800,   860,   864,   862,   818,   819,   820,
     882,   821,   883,   884,   887,   545,   822,   829,   830,   558,
     831,   589,   834,   437,   859,   863,   413,   594,   621,   888,
     766,   791,   794,   793,   801,   767,   768,   790,   495,   889,
     838,   890,   469,   892,   770,   769,   488,   614,   772,   441,
     771,   808,   807,   492,   606,   480,   247,   165,   679,   778,
     229,   248,   810,   246,   809,   804,   773,   471,   852,   182,
     676,   754,   861,   261,   186,   166,   510,   187,   785,   249,
     880,   891,   188,   786,   774,   167,   787,     0,     0,   168,
     169,   788,     0,   191,   775,     0,   205,     0,   776,   777,
       0,   196,     0,     0,     0,   192,     0,     0,   206,     0,
       0,     0,     0,   210,     0,     0,   211,     0,     0,     0,
       0,   212,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   778,     0,     0,
       0,     0,     0,     0,   773,     0,     0,     0,     0,     0,
     846,     0,     0,     0,     0,     0,   785,   845,     0,     0,
       0,   786,   774,     0,   787,     0,     0,   846,     0,   788,
       0,     0,   775,     0,   845,     0,   776,   777
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    68,    65,    66,    67,    70,    69,    70,    71,
      72,    60,    66,    10,   528,    65,    66,    67,   718,   718,
      65,    65,    67,    65,    70,    67,    24,   718,    65,   718,
      67,    65,     7,    85,    86,    65,    65,     5,    15,     7,
       0,     9,     7,    18,    19,    20,    21,    19,    20,    21,
       7,    49,     7,    51,    52,    48,     7,    55,    56,    57,
       3,    85,    86,     6,    39,    40,    41,    60,    61,    44,
      45,    46,     7,    48,     7,    47,    48,    49,     7,    49,
       3,     7,     7,     7,    59,     8,    61,    62,    63,    64,
      65,    66,    67,    18,    19,    20,    21,     3,     7,    74,
      75,    73,     8,   115,   116,   117,   118,    82,    49,    50,
      51,    52,    53,    54,    39,    40,    41,    74,    43,   143,
       3,     7,   119,    48,    49,     8,   826,   826,    68,    69,
      70,   128,   129,   130,   146,   826,   113,   826,    63,     3,
      14,    15,    67,     3,     8,   143,   143,   143,     8,    74,
     143,   121,    11,   123,   124,     7,    47,    82,    17,    18,
      19,    20,    21,    22,    23,     3,     6,     3,   143,     3,
       8,   143,     8,   143,     8,   143,   144,   145,   146,     3,
      39,    40,    41,    42,    43,    96,    97,     4,    47,    48,
      88,    89,    90,    91,    92,    93,     3,     3,     3,    58,
       6,     8,   143,     8,   718,    19,    20,    21,     3,   723,
       8,     6,    71,    72,    76,    77,    78,    79,   143,    81,
      12,    13,     3,     3,    16,    84,   122,     8,    87,   125,
     126,   127,     3,     3,    48,    94,    95,     8,     8,    98,
       3,     3,     3,     3,     6,     8,   308,     8,     8,   298,
     299,     4,     3,     8,     3,     3,     3,     8,    72,     8,
       8,     8,    76,    77,    78,    79,    80,    81,     3,    83,
       3,   340,     4,     8,   340,     4,     4,     4,   340,    25,
      26,    27,    28,     4,   143,     4,     4,     4,     4,     4,
     340,     4,     4,   355,     8,   340,   358,     8,   340,     3,
       8,     4,     4,   340,   358,   355,     3,   369,   358,     4,
     355,   355,   826,   355,     4,   384,     4,   379,   355,   369,
     384,   355,   384,     4,   369,   355,   355,   369,     4,   143,
       4,     4,   369,   143,     4,     4,     4,     4,   384,    24,
       4,   403,     4,   146,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,     4,   146,     4,     4,     4,     4,
     144,   410,   411,   412,    49,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,     4,     4,     4,   144,     4,     4,     4,     4,   144,
     144,     4,   144,     4,     4,     4,     4,   146,     4,   143,
       4,     4,     4,     4,     4,     4,     4,     4,   144,     4,
       4,   146,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   144,     4,     4,     4,     4,   146,
     146,   146,     4,     4,     4,   494,   146,     4,   144,     4,
     144,   144,   521,   522,     4,     4,     4,   146,   143,   521,
     522,     4,   511,   146,   146,     4,     7,     7,   143,     7,
     532,   540,   143,     7,   540,     7,     5,   143,   540,     5,
       5,     5,     5,     5,     5,   143,     3,     7,     7,     7,
     540,     5,     8,     5,   143,   540,     7,     5,   540,   143,
     143,   143,   143,   540,   143,     7,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   120,     7,     7,   114,     7,
       7,     7,     4,     7,     7,     4,    83,     4,     4,     4,
       4,     3,   144,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     3,
     143,     6,     3,     6,     4,     4,     8,     4,     4,     4,
       4,     4,     4,   143,     3,     6,     4,     7,     5,     4,
     144,   146,     8,   146,     8,   144,   144,     8,   144,     4,
     144,   144,   144,   144,     4,     7,     5,   143,   143,   143,
       4,   143,     4,     4,     4,   459,   143,   143,   143,   472,
     143,   512,   143,   333,   144,   143,   308,   517,   522,   146,
     706,   721,   727,   725,   734,   709,   711,   720,   387,   144,
     826,   144,   355,   143,   714,   712,   379,   706,   717,   338,
     715,   747,   745,   384,   706,   369,   715,   709,   540,   718,
     712,   715,   750,   715,   748,   738,   718,   358,   840,   709,
     532,   692,   856,   725,   709,   709,   403,   709,   718,   715,
     868,   885,   709,   718,   718,   709,   718,    -1,    -1,   709,
     709,   718,    -1,   745,   718,    -1,   748,    -1,   718,   718,
      -1,   745,    -1,    -1,    -1,   745,    -1,    -1,   748,    -1,
      -1,    -1,    -1,   748,    -1,    -1,   748,    -1,    -1,    -1,
      -1,   748,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   826,    -1,    -1,
      -1,    -1,    -1,    -1,   826,    -1,    -1,    -1,    -1,    -1,
     839,    -1,    -1,    -1,    -1,    -1,   826,   839,    -1,    -1,
      -1,   826,   826,    -1,   826,    -1,    -1,   856,    -1,   826,
      -1,    -1,   826,    -1,   856,    -1,   826,   826
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
     446,   448,   450,    11,    17,    18,    19,    20,    21,    22,
      23,    39,    40,    41,    42,    43,    47,    48,    58,    71,
      72,    84,    87,    94,    95,    98,   176,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   205,   207,   231,   240,
     254,   264,   293,   301,   327,   370,   372,   374,   396,   406,
     407,   415,    12,    13,    16,   195,   196,   199,   201,   204,
       7,    44,    45,    46,    59,    61,    62,    63,    64,    65,
      66,    67,    74,    75,    82,   176,   187,   188,   189,   192,
     272,   273,   274,   276,   278,   280,   282,   284,   286,   288,
     291,   292,   327,   345,   357,   359,   370,   372,   374,   392,
      60,   176,   327,   353,   354,   355,   357,    72,    76,    77,
      78,    79,    80,    81,    83,   176,   327,   367,   368,   369,
     370,   372,   374,   376,   378,   380,   382,   384,   386,   388,
     390,   301,    24,    49,    51,    52,    55,    56,    57,   176,
     221,   311,   312,   313,   314,   315,   316,   317,   319,   321,
     323,   324,   326,    50,    53,    54,   176,   221,   315,   321,
     335,   336,   337,   338,   339,   341,   342,   343,   344,    85,
      86,   176,   248,   249,   250,   252,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     176,   419,   420,   421,   422,   424,   426,   427,   429,   430,
     431,   434,   436,   437,   438,   439,   442,     6,     3,     4,
       8,     3,   182,   451,   445,   447,   449,     4,     3,     8,
     194,     4,     4,   371,   373,   375,   206,   208,     4,     4,
       4,     4,   265,   302,   328,   294,   232,   397,   241,   255,
       4,   408,   416,     3,     8,   200,   202,     4,     3,     8,
     399,   277,   279,   281,   346,   358,   275,   283,   285,     4,
       4,   289,   287,   360,   393,     3,     8,   356,     3,     8,
     391,   379,   381,   385,   383,   389,   387,   377,     8,     3,
       8,   318,   222,     4,   322,   320,   325,     4,     8,     3,
     340,     4,     4,     8,     3,   251,   253,     3,     8,     4,
     423,   425,     4,   428,     4,     4,   432,   435,     4,     4,
       4,   440,   443,     3,     8,   161,   161,   143,     4,     4,
       4,     4,     4,   180,     4,   146,   146,     4,     4,     4,
       4,     4,   144,   144,   144,   144,     4,     4,     4,     4,
       4,     4,     4,     4,   144,     4,     4,   186,     4,     4,
     146,   196,    73,   176,   221,   301,   327,   370,   372,   374,
     400,   401,   402,   403,   404,     4,     4,     4,     4,     4,
       4,     4,     4,   144,   146,     4,     4,     4,     4,   273,
       4,   354,     4,     4,     4,     4,     4,     4,     4,     4,
     369,     4,     4,   144,     4,     4,     4,   146,   313,     4,
     146,   146,   337,     4,     4,   249,   146,     4,     4,   144,
       4,   144,   144,     4,     4,   146,   146,   146,     4,     4,
     420,     4,     7,     7,   161,   161,   161,     7,   143,   143,
     143,     7,     7,     5,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     5,   172,    14,    15,   203,   405,     8,
       3,   143,   143,   143,     5,   163,   165,   143,   143,   143,
      68,    69,    70,   290,   143,     5,     7,   143,   172,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   161,   143,   143,   143,    15,   113,   433,
     114,   115,   116,   117,   118,   146,   441,   143,   161,   185,
     120,   452,   453,   454,   195,    24,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   176,   209,   210,   211,
     214,   216,   218,   220,   221,   223,   224,   225,   226,   227,
     229,   209,     7,   266,   267,   268,     7,   305,   306,   307,
       7,   329,   330,   331,     7,   295,   296,   297,    76,    77,
      78,    79,    81,   233,   234,   235,   236,   237,   238,   239,
     286,   398,     7,   242,   243,   244,    88,    89,    90,    91,
      92,    93,   256,   257,   258,   259,   260,   261,   262,   263,
      96,    97,   409,   410,   411,   413,   419,   173,     4,   402,
       7,   347,   348,   349,     7,   361,   362,   363,    83,   394,
       8,   455,     3,     8,     8,   212,   215,   217,   219,     4,
       4,     4,     4,     4,   228,   230,     3,     8,     8,   269,
       6,     3,   308,     6,     3,   332,     6,     3,   298,     6,
       3,     3,     6,     3,     6,   245,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   412,   414,     3,     8,
       8,   143,   174,   175,   143,   350,     6,     3,   364,     6,
       3,   395,     8,     4,   453,     4,     4,     4,     4,   144,
     146,   144,   146,   144,     4,     4,   210,   272,   268,   311,
     307,   335,   331,   176,   187,   188,   189,   192,   221,   264,
     282,   286,   288,   299,   300,   327,   370,   372,   374,   392,
     297,   234,   286,   248,   244,   144,   144,   144,   144,   144,
     144,   257,     4,     4,   410,     6,     3,   353,   349,   367,
     363,     4,     5,    25,    26,    27,    28,   213,   143,   143,
     143,   143,   143,     8,     8,     8,     3,     8,     8,   143,
     143,   143,     8,     8,   143,     7,   456,   457,   300,   458,
       3,     6,   121,   123,   124,   176,   221,   459,   460,   461,
     462,   464,   457,   465,     4,   463,     3,     8,     4,   144,
       4,   460,     5,   143,     7,   466,   467,   468,     3,     6,
     122,   125,   126,   127,   469,   470,   471,   473,   474,   475,
     467,   472,     4,     4,     4,     3,     8,     4,   146,   144,
     144,   470,   143
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
     186,   186,   186,   186,   187,   188,   189,   190,   191,   192,
     194,   193,   195,   195,   196,   196,   196,   198,   197,   200,
     199,   202,   201,   203,   203,   204,   206,   205,   208,   207,
     209,   209,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   212,   211,   213,   213,   213,
     213,   215,   214,   217,   216,   219,   218,   220,   222,   221,
     223,   224,   225,   226,   228,   227,   230,   229,   232,   231,
     233,   233,   234,   234,   234,   234,   234,   235,   236,   237,
     238,   239,   241,   240,   242,   242,   243,   243,   245,   244,
     247,   246,   248,   248,   248,   249,   249,   251,   250,   253,
     252,   255,   254,   256,   256,   257,   257,   257,   257,   257,
     257,   258,   259,   260,   261,   262,   263,   265,   264,   266,
     266,   267,   267,   269,   268,   271,   270,   272,   272,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   275,   274,   277,   276,   279,   278,   281,   280,
     283,   282,   285,   284,   287,   286,   289,   288,   290,   290,
     290,   291,   292,   294,   293,   295,   295,   296,   296,   298,
     297,   299,   299,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   302,   301,
     304,   303,   305,   305,   306,   306,   308,   307,   310,   309,
     311,   311,   312,   312,   313,   313,   313,   313,   313,   313,
     313,   313,   314,   315,   316,   318,   317,   320,   319,   322,
     321,   323,   325,   324,   326,   328,   327,   329,   329,   330,
     330,   332,   331,   334,   333,   335,   335,   336,   336,   337,
     337,   337,   337,   337,   337,   337,   338,   340,   339,   341,
     342,   343,   344,   346,   345,   347,   347,   348,   348,   350,
     349,   352,   351,   353,   353,   354,   354,   354,   354,   356,
     355,   358,   357,   360,   359,   361,   361,   362,   362,   364,
     363,   366,   365,   367,   367,   368,   368,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     371,   370,   373,   372,   375,   374,   377,   376,   379,   378,
     381,   380,   383,   382,   385,   384,   387,   386,   389,   388,
     391,   390,   393,   392,   395,   394,   397,   396,   398,   398,
     399,   286,   400,   400,   401,   401,   402,   402,   402,   402,
     402,   402,   402,   402,   403,   405,   404,   406,   408,   407,
     409,   409,   410,   410,   412,   411,   414,   413,   416,   415,
     418,   417,   419,   419,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   421,
     423,   422,   425,   424,   426,   428,   427,   429,   430,   432,
     431,   433,   433,   435,   434,   436,   437,   438,   440,   439,
     441,   441,   441,   441,   441,   443,   442,   445,   444,   447,
     446,   449,   448,   451,   450,   452,   452,   453,   455,   454,
     456,   456,   458,   457,   459,   459,   460,   460,   460,   460,
     460,   461,   463,   462,   465,   464,   466,   466,   468,   467,
     469,   469,   470,   470,   470,   470,   472,   471,   473,   474,
     475
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     3,     0,     6,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
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
     428,   429,   430,   431,   434,   439,   444,   449,   454,   459,
     465,   465,   476,   477,   480,   481,   482,   485,   485,   494,
     494,   504,   504,   511,   512,   515,   521,   521,   533,   533,
     545,   546,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   564,   564,   571,   572,   573,
     574,   577,   577,   585,   585,   593,   593,   601,   606,   606,
     614,   619,   624,   629,   634,   634,   642,   642,   651,   651,
     661,   662,   665,   666,   667,   668,   669,   672,   677,   682,
     687,   692,   697,   697,   707,   708,   711,   712,   715,   715,
     725,   725,   735,   736,   737,   740,   741,   744,   744,   752,
     752,   760,   760,   771,   772,   775,   776,   777,   778,   779,
     780,   783,   788,   793,   798,   803,   808,   816,   816,   829,
     830,   833,   834,   841,   841,   867,   867,   878,   879,   883,
     884,   885,   886,   887,   888,   889,   890,   891,   892,   893,
     894,   895,   896,   897,   898,   899,   900,   901,   902,   903,
     904,   905,   908,   908,   916,   916,   924,   924,   932,   932,
     940,   940,   948,   948,   956,   956,   964,   964,   971,   972,
     973,   976,   981,   988,   988,   999,  1000,  1004,  1005,  1008,
    1008,  1016,  1017,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1041,  1041,
    1054,  1054,  1063,  1064,  1067,  1068,  1073,  1073,  1088,  1088,
    1102,  1103,  1106,  1107,  1110,  1111,  1112,  1113,  1114,  1115,
    1116,  1117,  1120,  1122,  1127,  1129,  1129,  1137,  1137,  1145,
    1145,  1153,  1155,  1155,  1163,  1172,  1172,  1184,  1185,  1190,
    1191,  1196,  1196,  1208,  1208,  1220,  1221,  1226,  1227,  1232,
    1233,  1234,  1235,  1236,  1237,  1238,  1241,  1243,  1243,  1251,
    1253,  1255,  1260,  1268,  1268,  1280,  1281,  1284,  1285,  1288,
    1288,  1298,  1298,  1308,  1309,  1312,  1313,  1314,  1315,  1318,
    1318,  1326,  1326,  1336,  1336,  1346,  1347,  1350,  1351,  1354,
    1354,  1363,  1363,  1372,  1373,  1376,  1377,  1381,  1382,  1383,
    1384,  1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,
    1396,  1396,  1404,  1404,  1412,  1412,  1420,  1420,  1428,  1428,
    1436,  1436,  1444,  1444,  1452,  1452,  1460,  1460,  1468,  1468,
    1476,  1476,  1489,  1489,  1499,  1499,  1510,  1510,  1520,  1521,
    1524,  1524,  1534,  1535,  1538,  1539,  1542,  1543,  1544,  1545,
    1546,  1547,  1548,  1549,  1552,  1554,  1554,  1566,  1573,  1573,
    1583,  1584,  1587,  1588,  1591,  1591,  1599,  1599,  1609,  1609,
    1621,  1621,  1631,  1632,  1635,  1636,  1637,  1638,  1639,  1640,
    1641,  1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1652,
    1657,  1657,  1665,  1665,  1673,  1678,  1678,  1686,  1691,  1696,
    1696,  1704,  1705,  1708,  1708,  1716,  1721,  1726,  1731,  1731,
    1739,  1742,  1745,  1748,  1751,  1757,  1757,  1767,  1767,  1774,
    1774,  1781,  1781,  1793,  1793,  1806,  1807,  1811,  1815,  1815,
    1827,  1828,  1832,  1832,  1840,  1841,  1844,  1845,  1846,  1847,
    1848,  1851,  1856,  1856,  1864,  1864,  1874,  1875,  1878,  1878,
    1886,  1887,  1890,  1891,  1892,  1893,  1896,  1896,  1904,  1909,
    1914
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
#line 4328 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1919 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
