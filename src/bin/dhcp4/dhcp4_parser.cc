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
      case 175: // value
      case 179: // map_value
      case 217: // socket_type
      case 220: // outbound_interface_value
      case 236: // db_type
      case 320: // hr_mode
      case 467: // ncr_protocol_value
      case 475: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 159: // "boolean"
        value.move< bool > (that.value);
        break;

      case 158: // "floating point"
        value.move< double > (that.value);
        break;

      case 157: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 156: // "constant string"
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
      case 175: // value
      case 179: // map_value
      case 217: // socket_type
      case 220: // outbound_interface_value
      case 236: // db_type
      case 320: // hr_mode
      case 467: // ncr_protocol_value
      case 475: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 159: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 158: // "floating point"
        value.copy< double > (that.value);
        break;

      case 157: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 156: // "constant string"
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
            case 156: // "constant string"

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 157: // "integer"

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 158: // "floating point"

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 159: // "boolean"

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 175: // value

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 179: // map_value

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 217: // socket_type

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 220: // outbound_interface_value

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 236: // db_type

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 320: // hr_mode

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 467: // ncr_protocol_value

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 475: // replace_client_name_value

#line 234 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 175: // value
      case 179: // map_value
      case 217: // socket_type
      case 220: // outbound_interface_value
      case 236: // db_type
      case 320: // hr_mode
      case 467: // ncr_protocol_value
      case 475: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 159: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 158: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 157: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 156: // "constant string"
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
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 295 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 317 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 321 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 343 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 669 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 807 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1665 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 908 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1805 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1815 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1825 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1861 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1034 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1050 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1052 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1058 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1068 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1979 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1080 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2035 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1199 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1246 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1254 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1256 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1317 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2291 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2299 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2477 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2535 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2543 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2561 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2571 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2625 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2643 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2697 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2705 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2715 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2916 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1878 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1879 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3084 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1919 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1925 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 2002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3371 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 608:
#line 2080 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 609:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 612:
#line 2098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3424 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3428 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -763;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     391,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,    30,    22,    54,    62,    66,    70,
     170,   213,   214,   221,   223,   231,   240,   250,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,    22,   -81,    43,    59,    75,   169,
     210,    32,    48,    73,   271,   -50,   349,     4,  -763,   157,
     255,   261,   268,   281,  -763,  -763,  -763,  -763,  -763,   282,
    -763,    41,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   293,
     299,  -763,  -763,  -763,  -763,  -763,  -763,   300,   311,   315,
     322,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,   324,  -763,  -763,  -763,    68,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,   331,  -763,    87,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,   333,   339,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,    97,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,   144,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   280,
     298,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,   310,  -763,  -763,   341,  -763,  -763,  -763,
     342,  -763,  -763,   344,   304,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   343,   345,
    -763,  -763,  -763,  -763,   346,   352,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   145,  -763,
    -763,  -763,   358,  -763,  -763,   365,  -763,   367,   371,  -763,
    -763,   373,   378,   379,  -763,  -763,  -763,  -763,  -763,   146,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,   153,  -763,  -763,  -763,
      22,    22,  -763,   220,   385,   387,   394,   396,   398,  -763,
      43,  -763,   399,   227,   246,   402,   411,   412,   413,   414,
     417,   266,   267,   274,   275,   418,   421,   422,   429,   430,
     431,   433,   436,   437,   440,   288,   442,   443,    59,  -763,
     444,   445,   446,   292,    75,  -763,   448,   449,   450,   451,
     454,   470,   471,   319,   320,   474,   476,   477,   480,   481,
     169,  -763,   482,   210,  -763,   483,   484,   485,   486,   487,
     488,   489,   491,  -763,    32,  -763,   492,   493,   347,   494,
     495,   499,   348,  -763,    73,   502,   350,   351,  -763,   271,
     504,   507,    89,  -763,   356,   512,   513,   361,   515,   363,
     364,   518,   519,   366,   368,   370,   520,   522,   349,  -763,
     526,     4,  -763,  -763,  -763,   527,   540,   541,    22,    22,
      22,  -763,   542,  -763,  -763,   395,   397,   400,   543,   545,
     549,  -763,  -763,  -763,  -763,   550,   552,   553,   554,   555,
     404,   556,   558,   559,   560,  -763,   561,   562,  -763,   565,
      78,   179,  -763,  -763,   409,   410,   415,   567,   419,   420,
     423,  -763,  -763,    39,   565,   424,   568,   570,  -763,   425,
    -763,   565,   426,   427,   428,   432,   434,   435,   438,  -763,
     439,   441,  -763,   447,   452,   453,  -763,  -763,   455,  -763,
    -763,  -763,   456,    22,  -763,  -763,   457,   458,  -763,   459,
    -763,  -763,    17,   460,  -763,  -763,  -763,   -31,   461,  -763,
     569,  -763,    22,    59,     4,  -763,  -763,  -763,    75,  -763,
    -763,  -763,   167,   167,   571,   578,   580,   582,   585,  -763,
    -763,  -763,   160,   586,   589,   209,    42,   349,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   591,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   592,
     505,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,   594,  -763,   156,   164,   165,  -763,  -763,  -763,
    -763,   598,   600,   601,   602,   603,  -763,  -763,   606,   612,
     614,   615,   616,  -763,   168,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,   186,  -763,   617,   618,  -763,  -763,   619,
     621,  -763,  -763,   620,   624,  -763,  -763,   622,   626,  -763,
    -763,   625,   627,  -763,  -763,  -763,  -763,  -763,  -763,    35,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,   129,  -763,  -763,
     628,   629,  -763,   631,   632,   633,   634,   635,   636,   224,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,   251,  -763,  -763,  -763,   263,   466,  -763,   637,
     630,  -763,  -763,   638,   639,  -763,  -763,   640,  -763,   154,
    -763,  -763,  -763,  -763,   641,   642,   643,   645,   496,   497,
     498,   500,   501,   646,   647,   503,   506,   508,   509,   510,
     167,  -763,  -763,   167,  -763,   571,   169,  -763,   578,    73,
    -763,   580,   271,  -763,   582,   212,  -763,   585,   160,  -763,
     372,   586,  -763,   -50,  -763,   589,   511,   514,   516,   517,
     521,   523,   209,  -763,   648,   650,    42,  -763,  -763,  -763,
     651,   658,   210,  -763,   591,    32,  -763,   592,   660,  -763,
     303,   594,  -763,   382,   525,   528,   529,  -763,  -763,  -763,
    -763,  -763,   530,   531,  -763,  -763,  -763,  -763,  -763,  -763,
     265,  -763,   269,  -763,   654,  -763,   659,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   284,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,   666,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,   664,   672,  -763,  -763,  -763,  -763,  -763,   291,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,   532,   533,  -763,
    -763,   534,   297,  -763,   668,  -763,   535,  -763,   673,  -763,
    -763,  -763,  -763,  -763,   313,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,   212,  -763,   675,   524,  -763,   372,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,   678,   536,   688,
     303,  -763,  -763,   538,  -763,  -763,   690,  -763,   546,  -763,
    -763,   689,  -763,  -763,   272,  -763,   -75,   689,  -763,  -763,
     693,   694,   695,   314,  -763,  -763,  -763,  -763,  -763,  -763,
     697,   548,   547,   551,   -75,  -763,   557,  -763,  -763,  -763,
    -763,  -763
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   116,     9,   246,    11,   403,    13,
     428,    15,   328,    17,   336,    19,   373,    21,   211,    23,
     516,    25,   573,    27,    45,    39,     0,     0,     0,     0,
       0,   430,     0,   338,   375,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   571,   565,   567,   569,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   105,     0,
       0,   449,   451,   453,   129,   131,   133,     0,     0,     0,
       0,   238,   326,   365,   298,   416,   418,   189,   475,   203,
     222,     0,   501,   514,    98,     0,    70,    72,    73,    74,
      75,    91,    92,    78,    79,    80,    81,    82,    86,    87,
      76,    77,    84,    85,    96,    97,    93,    94,    95,    83,
      88,    89,    90,   118,   120,   124,     0,   115,     0,   107,
     109,   110,   111,   112,   113,   114,   277,   279,   281,   395,
     275,   283,   285,     0,     0,   291,   289,   287,   420,   471,
     274,   250,   251,   252,   265,     0,   248,   255,   269,   270,
     271,   256,   257,   260,   261,   263,   258,   259,   253,   254,
     272,   273,   262,   266,   267,   268,   264,   414,   413,   409,
     410,   408,     0,   405,   407,   411,   412,   469,   457,   459,
     463,   461,   467,   465,   455,   448,   442,   446,   447,     0,
     431,   432,   443,   444,   445,   439,   434,   440,   436,   437,
     438,   441,   435,     0,   355,   174,     0,   359,   357,   362,
       0,   351,   352,     0,   339,   340,   342,   354,   343,   344,
     345,   361,   346,   347,   348,   349,   350,   389,     0,     0,
     387,   388,   391,   392,     0,   376,   377,   379,   380,   381,
     382,   383,   384,   385,   386,   218,   220,   215,     0,   213,
     216,   217,     0,   538,   540,     0,   543,     0,     0,   547,
     551,     0,     0,     0,   556,   563,   536,   534,   535,     0,
     518,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   578,     0,   575,   577,    44,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    55,
       0,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   247,     0,     0,   404,     0,     0,     0,     0,     0,
       0,     0,     0,   429,     0,   329,     0,     0,     0,     0,
       0,     0,     0,   337,     0,     0,     0,     0,   374,     0,
       0,     0,     0,   212,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   517,
       0,     0,   574,    48,    41,     0,     0,     0,     0,     0,
       0,    59,     0,   103,   104,     0,     0,     0,     0,     0,
       0,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   500,     0,     0,    71,     0,
       0,     0,   128,   108,     0,     0,     0,     0,     0,     0,
       0,   296,   297,     0,     0,     0,     0,     0,   249,     0,
     406,     0,     0,     0,     0,     0,     0,     0,     0,   433,
       0,     0,   353,     0,     0,     0,   364,   341,     0,   393,
     394,   378,     0,     0,   214,   537,     0,     0,   542,     0,
     545,   546,     0,     0,   553,   554,   555,     0,     0,   519,
       0,   576,     0,     0,     0,   566,   568,   570,     0,   450,
     452,   454,     0,     0,   135,   240,   330,   367,   300,    38,
     417,   419,     0,     0,   205,     0,     0,     0,    49,   119,
     122,   123,   121,   126,   127,   125,   278,   280,   282,   397,
     276,   284,   286,   293,   294,   295,   292,   290,   288,   422,
       0,   415,   470,   458,   460,   464,   462,   468,   466,   456,
     356,   175,   360,   358,   363,   390,   219,   221,   539,   541,
     544,   549,   550,   548,   552,   558,   559,   560,   561,   562,
     557,   564,     0,    42,     0,     0,     0,   161,   167,   169,
     171,     0,     0,     0,     0,     0,   183,   185,     0,     0,
       0,     0,     0,   160,     0,   141,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   156,   157,   158,   153,
     159,   154,   155,     0,   139,     0,   136,   137,   244,     0,
     241,   242,   334,     0,   331,   332,   371,     0,   368,   369,
     304,     0,   301,   302,   198,   199,   200,   201,   202,     0,
     191,   193,   194,   195,   196,   197,   479,     0,   477,   209,
       0,   206,   207,     0,     0,     0,     0,     0,     0,     0,
     224,   226,   227,   228,   229,   230,   231,   510,   512,   509,
     507,   508,     0,   503,   505,   506,     0,    51,   401,     0,
     398,   399,   426,     0,   423,   424,   473,     0,   582,     0,
     580,    67,   572,   106,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,   132,     0,   134,     0,     0,   239,     0,   338,
     327,     0,   375,   366,     0,     0,   299,     0,     0,   190,
     481,     0,   476,     0,   204,     0,     0,     0,     0,     0,
       0,     0,     0,   223,     0,     0,     0,   502,   515,    53,
       0,    52,     0,   396,     0,   430,   421,     0,     0,   472,
       0,     0,   579,     0,     0,     0,     0,   173,   176,   177,
     178,   179,     0,     0,   187,   188,   180,   181,   182,   142,
       0,   138,     0,   243,     0,   333,     0,   370,   325,   322,
     311,   312,   314,   308,   309,   310,   320,   321,   319,     0,
     306,   313,   323,   324,   315,   316,   317,   318,   303,   192,
     497,     0,   495,   496,   488,   489,   493,   494,   490,   491,
     492,     0,   482,   483,   485,   486,   487,   478,     0,   208,
     232,   233,   234,   235,   236,   237,   225,     0,     0,   504,
      50,     0,     0,   400,     0,   425,     0,   596,     0,   594,
     592,   586,   590,   591,     0,   584,   588,   589,   587,   581,
     163,   164,   165,   166,   162,   168,   170,   172,   184,   186,
     140,   245,   335,   372,     0,   305,     0,     0,   480,     0,
     210,   511,   513,    54,   402,   427,   474,     0,     0,     0,
       0,   583,   307,     0,   499,   484,     0,   593,     0,   585,
     498,     0,   595,   600,     0,   598,     0,     0,   597,   608,
       0,     0,     0,     0,   602,   604,   605,   606,   607,   599,
       0,     0,     0,     0,     0,   601,     0,   610,   611,   612,
     603,   609
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,   -40,  -763,   172,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -444,  -763,  -763,  -763,
     -66,  -763,  -763,  -763,   383,  -763,  -763,  -763,  -763,   162,
     354,   -23,   -11,    -9,  -763,  -763,     9,  -763,  -763,   163,
     353,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
     -41,  -763,  -547,   -35,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,   -22,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,   -47,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,   -57,  -763,  -763,  -763,   -38,   359,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,   -55,  -763,  -763,  -763,  -763,
    -763,  -763,  -762,  -763,  -763,  -763,    -7,  -763,  -763,  -763,
      -1,   377,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -754,  -763,  -763,  -763,   -42,  -763,    -5,  -763,  -749,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,    -4,  -763,  -763,
    -150,   -61,  -763,  -763,  -763,  -763,  -763,    11,  -763,  -763,
    -763,    16,  -763,   375,  -763,   -62,  -763,  -763,  -763,  -763,
    -763,   -56,  -763,  -763,  -763,  -763,  -763,    -3,  -763,  -763,
    -763,     6,  -763,  -763,  -763,    14,  -763,   374,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   -17,
    -763,  -763,  -763,   -12,   401,  -763,  -763,   -54,  -763,   -34,
    -763,  -763,  -763,  -763,  -763,   -16,  -763,  -763,  -763,   -13,
    -763,   392,   -46,  -763,   -26,  -763,     3,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -742,  -763,  -763,  -763,  -763,  -763,
    -763,    19,  -763,  -763,  -763,  -134,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,     2,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,   234,   369,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,
    -763,  -763,  -763,  -763,  -763,  -763,  -763,  -763,   259,   376,
    -763,  -763,  -763,    -6,  -763,  -763,  -136,  -763,  -763,  -763,
    -763,  -763,  -763,  -151,  -763,  -763,  -165,  -763,  -763,  -763,
    -763,  -763
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   560,
      82,    83,    39,    64,    79,    80,   569,   727,   800,   801,
     643,    41,    66,    91,    92,    93,   334,    43,    67,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   342,   158,
     159,    45,    68,   160,   370,   161,   371,   572,   162,   372,
     575,   163,   134,   348,   135,   349,   136,   350,   665,   666,
     667,   763,   644,   645,   646,   744,   914,   647,   745,   648,
     746,   649,   747,   650,   651,   407,   652,   653,   654,   655,
     656,   657,   658,   659,   753,   660,   754,   661,   662,   137,
     361,   689,   690,   691,   692,   693,   694,   695,   138,   363,
     700,   701,   702,   783,    59,    75,   288,   289,   290,   420,
     291,   421,   139,   364,   709,   710,   711,   712,   713,   714,
     715,   716,   140,   355,   669,   670,   671,   766,    47,    69,
     185,   186,   187,   380,   188,   376,   189,   377,   190,   378,
     191,   381,   192,   382,   193,   387,   194,   386,   195,   385,
     586,   196,   197,   141,   358,   681,   682,   683,   775,   849,
     850,   142,   356,    53,    72,   673,   674,   675,   769,    55,
      73,   253,   254,   255,   256,   257,   258,   259,   406,   260,
     410,   261,   409,   262,   263,   411,   264,   143,   357,   677,
     678,   679,   772,    57,    74,   274,   275,   276,   277,   278,
     415,   279,   280,   281,   282,   199,   379,   729,   730,   731,
     802,    49,    70,   212,   213,   214,   392,   144,   359,   145,
     360,   202,   388,   733,   734,   735,   805,    51,    71,   229,
     230,   231,   146,   345,   147,   346,   148,   347,   235,   402,
     236,   396,   237,   397,   238,   399,   239,   398,   240,   401,
     241,   400,   242,   395,   206,   389,   737,   808,   149,   362,
     697,   698,   780,   871,   872,   873,   874,   875,   926,   876,
     150,   151,   366,   722,   723,   724,   794,   725,   795,   152,
     367,    61,    76,   309,   310,   311,   312,   425,   313,   426,
     314,   315,   428,   316,   317,   318,   431,   613,   319,   432,
     320,   321,   322,   323,   436,   620,   324,   437,    94,   336,
      95,   337,    96,   338,    97,   335,    63,    77,   326,   327,
     328,   440,   739,   740,   810,   904,   905,   906,   907,   939,
     908,   937,   954,   955,   956,   963,   964,   965,   970,   966,
     967,   968
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   124,   157,   180,   208,   225,   663,   251,   270,   287,
     306,   243,   272,   844,   164,   200,   215,   227,   273,   265,
     283,   845,   307,   203,    78,   232,   848,    29,   209,    30,
      28,    31,   611,   857,   165,   201,   216,   228,   778,   266,
     284,   779,   308,   204,   340,   233,   181,   285,   286,   341,
     587,   252,   271,    84,   101,   102,   103,   592,   182,   959,
     183,    40,   960,   961,   962,   210,   198,   211,   226,    42,
      98,   368,   205,    44,   234,    81,   369,    46,   184,    99,
     100,   101,   102,   103,   104,   105,   106,   153,   154,   113,
     374,   155,   570,   571,   156,   375,   615,   616,   617,   618,
     390,   244,   115,   116,   112,   391,    89,   107,   108,   109,
     110,   111,   115,   116,   217,   112,   113,   583,   584,   585,
     218,   219,   220,   221,   222,   223,   114,   224,   619,   115,
     116,   245,   781,   246,   247,   782,   325,   248,   249,   250,
     117,   118,   612,   115,   116,   115,   116,   393,   422,   438,
     717,   718,   394,   423,   439,   119,   441,   811,   120,   368,
     812,   442,   844,   329,   741,   121,   122,   441,   374,   123,
     845,   760,   742,   743,    85,   848,   761,    48,    32,    33,
      34,    35,   857,    86,    87,    88,   285,   286,    89,   760,
     100,   101,   102,   103,   762,   627,   573,   574,    89,    89,
     628,   629,   630,   631,   632,   633,   634,   635,   636,   637,
     638,   639,   640,   641,   642,    89,   830,   107,   108,   109,
      50,    52,   166,   167,   168,   245,   113,   792,    54,    89,
      56,    89,   793,   100,   101,   102,   103,   169,    58,   115,
     116,   170,   171,   172,   173,   174,   175,    60,   684,   685,
     686,   687,   176,   688,   796,   177,   178,    62,   330,   797,
     107,   108,   109,   179,   111,   331,   438,   113,   760,   113,
     245,   798,   390,   920,    90,   957,   332,   921,   958,   207,
     115,   116,   115,   116,   333,   171,   339,   924,   403,   175,
     443,   444,   925,   176,   422,   176,   177,   343,   177,   930,
     393,   404,   124,   344,   351,   934,   179,   414,   157,   703,
     704,   705,   706,   707,   708,   352,   940,   974,   405,   353,
     164,   941,   975,    89,   180,    89,   354,   208,   365,   245,
     267,   246,   247,   268,   269,   373,   200,   383,   225,   215,
     165,   115,   116,   384,   203,   408,   412,   416,   251,   417,
     227,   209,   413,   270,   418,   419,   201,   272,   232,   216,
     265,   245,   424,   273,   204,   283,    89,   181,    89,   427,
     228,   429,   306,   115,   116,   430,   445,   433,   233,   182,
     266,   183,   434,   435,   307,   284,   453,   198,   210,   446,
     211,   447,   252,   205,   101,   102,   103,   271,   448,   184,
     449,   226,   450,   452,   308,   454,   455,   234,   545,   546,
     547,   910,   911,   912,   913,   456,   457,   458,   459,   115,
     116,   460,   465,   461,   462,   466,   467,    89,   112,   113,
     245,   463,   464,   468,   469,   470,   897,   471,   898,   899,
     472,   473,   115,   116,   474,   475,   476,   477,   479,   480,
     481,   482,   484,   485,   486,   487,   860,   861,   488,    89,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   489,   490,   491,   124,   493,   492,
     494,   495,   157,   607,   496,   497,   499,   501,   502,   503,
     504,   505,   506,   507,   164,   508,   510,   511,   513,   514,
     719,   306,   623,   515,   512,    89,   518,   516,   522,   519,
     520,   523,   720,   307,   165,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   537,   534,   538,   535,    89,   536,
     540,   542,   721,   308,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   543,   544,   548,
     552,   549,   553,   550,   554,   555,   551,   556,   557,   558,
     561,   562,    30,   563,   564,   576,   577,   565,   566,   567,
     568,   578,   579,   589,   622,   580,   581,   590,   664,   582,
     588,   591,   593,   594,   595,   668,   614,   672,   596,   676,
     597,   598,   680,   696,   599,   600,   699,   601,   728,   732,
     736,   738,   748,   602,   749,   750,   751,   752,   603,   604,
     755,   605,   606,   608,   609,   610,   756,   621,   757,   758,
     759,   765,   799,   764,   768,   767,   770,   771,   773,   774,
     777,   776,   785,   804,   784,   786,   787,   788,   789,   790,
     791,   559,   807,   803,   806,   813,   814,   815,   809,   816,
     822,   823,   887,   817,   888,   819,   818,   890,   821,   820,
     824,   891,   922,   825,   896,   826,   827,   923,   880,   828,
     927,   881,   928,   882,   883,   929,   935,   938,   884,   943,
     885,   915,   946,   944,   916,   917,   918,   919,   931,   932,
     933,   936,   948,   947,   950,   951,   953,   971,   972,   973,
     180,   976,   952,   251,   978,   624,   270,   977,   979,   838,
     272,   626,   200,   981,   862,   265,   273,   287,   283,   864,
     203,   852,   478,   451,   831,   829,   866,   483,   879,   854,
     719,   859,   201,   846,   868,   266,   208,   886,   284,   225,
     204,   853,   720,   181,   900,   878,   867,   252,   215,   855,
     271,   227,   839,   843,   869,   182,   902,   183,   863,   232,
     209,   833,   721,   198,   840,   832,   841,   498,   216,   205,
     847,   228,   851,   858,   942,   184,   903,   865,   856,   233,
     837,   524,   835,   870,   842,   834,   836,   893,   901,   517,
     892,   895,   894,   521,   500,   945,   509,   210,   889,   211,
     877,   726,   226,   625,   949,   909,   969,   539,   234,   980,
       0,     0,     0,     0,     0,     0,     0,   541,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   838,     0,
       0,     0,     0,   862,     0,     0,     0,     0,   864,     0,
     852,     0,     0,     0,   900,   866,     0,     0,   854,     0,
       0,     0,   846,   868,     0,     0,   902,     0,     0,     0,
     853,     0,     0,     0,     0,   867,     0,     0,   855,     0,
       0,   839,   843,   869,     0,     0,   903,   863,     0,     0,
       0,     0,     0,   840,     0,   841,     0,     0,   901,   847,
       0,   851,     0,     0,     0,     0,   865,   856,     0,     0,
       0,     0,   870,   842
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,   553,    73,    74,    75,
      76,    72,    74,   775,    68,    69,    70,    71,    74,    73,
      74,   775,    76,    69,    64,    71,   775,     5,    70,     7,
       0,     9,    15,   775,    68,    69,    70,    71,     3,    73,
      74,     6,    76,    69,     3,    71,    69,    97,    98,     8,
     494,    73,    74,    10,    22,    23,    24,   501,    69,   134,
      69,     7,   137,   138,   139,    70,    69,    70,    71,     7,
      11,     3,    69,     7,    71,   156,     8,     7,    69,    20,
      21,    22,    23,    24,    25,    26,    27,    12,    13,    57,
       3,    16,    14,    15,    19,     8,   127,   128,   129,   130,
       3,    28,    70,    71,    56,     8,   156,    48,    49,    50,
      51,    52,    70,    71,    82,    56,    57,    78,    79,    80,
      88,    89,    90,    91,    92,    93,    67,    95,   159,    70,
      71,    58,     3,    60,    61,     6,   132,    64,    65,    66,
      81,    82,   125,    70,    71,    70,    71,     3,     3,     3,
     108,   109,     8,     8,     8,    96,     3,     3,    99,     3,
       6,     8,   924,     6,     8,   106,   107,     3,     3,   110,
     924,     3,     8,     8,   131,   924,     8,     7,   156,   157,
     158,   159,   924,   140,   141,   142,    97,    98,   156,     3,
      21,    22,    23,    24,     8,    28,    17,    18,   156,   156,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,   156,   763,    48,    49,    50,
       7,     7,    53,    54,    55,    58,    57,     3,     7,   156,
       7,   156,     8,    21,    22,    23,    24,    68,     7,    70,
      71,    72,    73,    74,    75,    76,    77,     7,    88,    89,
      90,    91,    83,    93,     3,    86,    87,     7,     3,     8,
      48,    49,    50,    94,    52,     4,     3,    57,     3,    57,
      58,     8,     3,     8,   340,     3,     8,     8,     6,    69,
      70,    71,    70,    71,     3,    73,     4,     3,     8,    77,
     330,   331,     8,    83,     3,    83,    86,     4,    86,     8,
       3,     3,   368,     4,     4,     8,    94,     3,   374,   100,
     101,   102,   103,   104,   105,     4,     3,     3,     8,     4,
     374,     8,     8,   156,   390,   156,     4,   393,     4,    58,
      59,    60,    61,    62,    63,     4,   390,     4,   404,   393,
     374,    70,    71,     4,   390,     4,     4,     4,   414,     4,
     404,   393,     8,   419,     8,     3,   390,   419,   404,   393,
     414,    58,     4,   419,   390,   419,   156,   390,   156,     4,
     404,     4,   438,    70,    71,     4,   156,     4,   404,   390,
     414,   390,     4,     4,   438,   419,   159,   390,   393,     4,
     393,     4,   414,   390,    22,    23,    24,   419,     4,   390,
       4,   404,     4,     4,   438,   159,     4,   404,   448,   449,
     450,    29,    30,    31,    32,     4,     4,     4,     4,    70,
      71,     4,     4,   157,   157,     4,     4,   156,    56,    57,
      58,   157,   157,     4,     4,     4,   133,     4,   135,   136,
       4,     4,    70,    71,     4,   157,     4,     4,     4,     4,
       4,   159,     4,     4,     4,     4,    84,    85,     4,   156,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     4,     4,   157,   543,     4,   159,
       4,     4,   548,   523,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   548,     4,     4,     4,     4,     4,
     566,   567,   542,     4,   157,   156,     4,   159,     4,   159,
     159,     4,   566,   567,   548,   159,     4,     4,   157,     4,
     157,   157,     4,     4,     4,   159,     4,   159,   156,   159,
       4,     4,   566,   567,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,     7,     7,     7,
       7,   156,     7,   156,     5,     5,   156,     5,     5,     5,
     156,     5,     7,     5,     5,   156,   156,     7,     7,     7,
       5,   156,     5,     5,     5,   156,   156,     7,     7,   156,
     156,   156,   156,   156,   156,     7,   126,     7,   156,     7,
     156,   156,     7,     7,   156,   156,     7,   156,     7,     7,
      95,     7,     4,   156,     4,     4,     4,     4,   156,   156,
       4,   156,   156,   156,   156,   156,     4,   156,     4,     4,
       4,     3,   156,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,   469,     3,     6,     6,     4,     4,     4,     8,     4,
       4,     4,     4,   157,     4,   157,   159,     6,   157,   159,
     157,     3,     8,   157,     4,   157,   157,     8,   157,   159,
       4,   157,     8,   157,   157,     3,     8,     4,   157,     4,
     157,   156,     4,   159,   156,   156,   156,   156,   156,   156,
     156,   156,     4,   157,   156,     5,     7,     4,     4,     4,
     766,     4,   156,   769,   157,   543,   772,   159,   157,   775,
     772,   548,   766,   156,   780,   769,   772,   783,   772,   780,
     766,   775,   368,   340,   765,   760,   780,   374,   785,   775,
     796,   778,   766,   775,   780,   769,   802,   792,   772,   805,
     766,   775,   796,   766,   810,   783,   780,   769,   802,   775,
     772,   805,   775,   775,   780,   766,   810,   766,   780,   805,
     802,   768,   796,   766,   775,   766,   775,   390,   802,   766,
     775,   805,   775,   777,   924,   766,   810,   780,   775,   805,
     774,   422,   771,   780,   775,   769,   772,   804,   810,   414,
     802,   807,   805,   419,   393,   929,   404,   802,   796,   802,
     781,   567,   805,   544,   940,   811,   957,   438,   805,   974,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   441,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   924,    -1,
      -1,    -1,    -1,   929,    -1,    -1,    -1,    -1,   929,    -1,
     924,    -1,    -1,    -1,   940,   929,    -1,    -1,   924,    -1,
      -1,    -1,   924,   929,    -1,    -1,   940,    -1,    -1,    -1,
     924,    -1,    -1,    -1,    -1,   929,    -1,    -1,   924,    -1,
      -1,   924,   924,   929,    -1,    -1,   940,   929,    -1,    -1,
      -1,    -1,    -1,   924,    -1,   924,    -1,    -1,   940,   924,
      -1,   924,    -1,    -1,    -1,    -1,   929,   924,    -1,    -1,
      -1,    -1,   929,   924
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     5,
       7,     9,   156,   157,   158,   159,   175,   176,   177,   182,
       7,   191,     7,   197,     7,   211,     7,   298,     7,   381,
       7,   397,     7,   333,     7,   339,     7,   363,     7,   274,
       7,   451,     7,   486,   183,   178,   192,   198,   212,   299,
     382,   398,   334,   340,   364,   275,   452,   487,   175,   184,
     185,   156,   180,   181,    10,   131,   140,   141,   142,   156,
     190,   193,   194,   195,   478,   480,   482,   484,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    48,    49,    50,
      51,    52,    56,    57,    67,    70,    71,    81,    82,    96,
      99,   106,   107,   110,   190,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   222,   224,   226,   259,   268,   282,
     292,   323,   331,   357,   387,   389,   402,   404,   406,   428,
     440,   441,   449,    12,    13,    16,    19,   190,   209,   210,
     213,   215,   218,   221,   387,   389,    53,    54,    55,    68,
      72,    73,    74,    75,    76,    77,    83,    86,    87,    94,
     190,   201,   202,   203,   206,   300,   301,   302,   304,   306,
     308,   310,   312,   314,   316,   318,   321,   322,   357,   375,
     387,   389,   391,   402,   404,   406,   424,    69,   190,   314,
     316,   357,   383,   384,   385,   387,   389,    82,    88,    89,
      90,    91,    92,    93,    95,   190,   357,   387,   389,   399,
     400,   401,   402,   404,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   331,    28,    58,    60,    61,    64,    65,
      66,   190,   244,   341,   342,   343,   344,   345,   346,   347,
     349,   351,   353,   354,   356,   387,   389,    59,    62,    63,
     190,   244,   345,   351,   365,   366,   367,   368,   369,   371,
     372,   373,   374,   387,   389,    97,    98,   190,   276,   277,
     278,   280,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   190,   387,   389,   453,
     454,   455,   456,   458,   460,   461,   463,   464,   465,   468,
     470,   471,   472,   473,   476,   132,   488,   489,   490,     6,
       3,     4,     8,     3,   196,   485,   479,   481,   483,     4,
       3,     8,   208,     4,     4,   403,   405,   407,   223,   225,
     227,     4,     4,     4,     4,   293,   332,   358,   324,   388,
     390,   260,   429,   269,   283,     4,   442,   450,     3,     8,
     214,   216,   219,     4,     3,     8,   305,   307,   309,   376,
     303,   311,   313,     4,     4,   319,   317,   315,   392,   425,
       3,     8,   386,     3,     8,   423,   411,   413,   417,   415,
     421,   419,   409,     8,     3,     8,   348,   245,     4,   352,
     350,   355,     4,     8,     3,   370,     4,     4,     8,     3,
     279,   281,     3,     8,     4,   457,   459,     4,   462,     4,
       4,   466,   469,     4,     4,     4,   474,   477,     3,     8,
     491,     3,     8,   175,   175,   156,     4,     4,     4,     4,
       4,   194,     4,   159,   159,     4,     4,     4,     4,     4,
       4,   157,   157,   157,   157,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   157,     4,     4,   200,     4,
       4,     4,   159,   210,     4,     4,     4,     4,     4,     4,
       4,   157,   159,     4,     4,     4,     4,     4,   301,     4,
     384,     4,     4,     4,     4,     4,     4,     4,     4,   401,
       4,     4,   157,     4,     4,     4,   159,   343,     4,   159,
     159,   367,     4,     4,   277,   159,     4,     4,   157,     4,
     157,   157,     4,     4,   159,   159,   159,     4,     4,   454,
       4,   489,     4,     7,     7,   175,   175,   175,     7,   156,
     156,   156,     7,     7,     5,     5,     5,     5,     5,   177,
     179,   156,     5,     5,     5,     7,     7,     7,     5,   186,
      14,    15,   217,    17,    18,   220,   156,   156,   156,     5,
     156,   156,   156,    78,    79,    80,   320,   186,   156,     5,
       7,   156,   186,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   175,   156,   156,
     156,    15,   125,   467,   126,   127,   128,   129,   130,   159,
     475,   156,     5,   175,   199,   488,   209,    28,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   190,   232,   233,   234,   237,   239,   241,
     243,   244,   246,   247,   248,   249,   250,   251,   252,   253,
     255,   257,   258,   232,     7,   228,   229,   230,     7,   294,
     295,   296,     7,   335,   336,   337,     7,   359,   360,   361,
       7,   325,   326,   327,    88,    89,    90,    91,    93,   261,
     262,   263,   264,   265,   266,   267,     7,   430,   431,     7,
     270,   271,   272,   100,   101,   102,   103,   104,   105,   284,
     285,   286,   287,   288,   289,   290,   291,   108,   109,   190,
     387,   389,   443,   444,   445,   447,   453,   187,     7,   377,
     378,   379,     7,   393,   394,   395,    95,   426,     7,   492,
     493,     8,     8,     8,   235,   238,   240,   242,     4,     4,
       4,     4,     4,   254,   256,     4,     4,     4,     4,     4,
       3,     8,     8,   231,     6,     3,   297,     6,     3,   338,
       6,     3,   362,     6,     3,   328,     6,     3,     3,     6,
     432,     3,     6,   273,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   446,   448,     3,     8,     8,   156,
     188,   189,   380,     6,     3,   396,     6,     3,   427,     8,
     494,     3,     6,     4,     4,     4,     4,   157,   159,   157,
     159,   157,     4,     4,   157,   157,   157,   157,   159,   233,
     232,   230,   300,   296,   341,   337,   365,   361,   190,   201,
     202,   203,   206,   244,   292,   310,   314,   316,   318,   329,
     330,   357,   387,   389,   402,   404,   406,   424,   327,   262,
      84,    85,   190,   244,   331,   357,   387,   389,   402,   404,
     406,   433,   434,   435,   436,   437,   439,   431,   276,   272,
     157,   157,   157,   157,   157,   157,   285,     4,     4,   444,
       6,     3,   383,   379,   399,   395,     4,   133,   135,   136,
     190,   244,   387,   389,   495,   496,   497,   498,   500,   493,
      29,    30,    31,    32,   236,   156,   156,   156,   156,   156,
       8,     8,     8,     8,     3,     8,   438,     4,     8,     3,
       8,   156,   156,   156,     8,     8,   156,   501,     4,   499,
       3,     8,   330,     4,   159,   435,     4,   157,     4,   496,
     156,     5,   156,     7,   502,   503,   504,     3,     6,   134,
     137,   138,   139,   505,   506,   507,   509,   510,   511,   503,
     508,     4,     4,     4,     3,     8,     4,   159,   157,   157,
     506,   156
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   160,   162,   161,   163,   161,   164,   161,   165,   161,
     166,   161,   167,   161,   168,   161,   169,   161,   170,   161,
     171,   161,   172,   161,   173,   161,   174,   161,   175,   175,
     175,   175,   175,   175,   175,   176,   178,   177,   179,   180,
     180,   181,   181,   183,   182,   184,   184,   185,   185,   187,
     186,   188,   188,   189,   189,   190,   192,   191,   193,   193,
     194,   194,   194,   194,   194,   194,   196,   195,   198,   197,
     199,   199,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   201,
     202,   203,   204,   205,   206,   208,   207,   209,   209,   210,
     210,   210,   210,   210,   210,   210,   212,   211,   214,   213,
     216,   215,   217,   217,   219,   218,   220,   220,   221,   223,
     222,   225,   224,   227,   226,   228,   228,   229,   229,   231,
     230,   232,   232,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   235,   234,   236,   236,   236,   236,   238,   237,   240,
     239,   242,   241,   243,   245,   244,   246,   247,   248,   249,
     250,   251,   252,   254,   253,   256,   255,   257,   258,   260,
     259,   261,   261,   262,   262,   262,   262,   262,   263,   264,
     265,   266,   267,   269,   268,   270,   270,   271,   271,   273,
     272,   275,   274,   276,   276,   276,   277,   277,   279,   278,
     281,   280,   283,   282,   284,   284,   285,   285,   285,   285,
     285,   285,   286,   287,   288,   289,   290,   291,   293,   292,
     294,   294,   295,   295,   297,   296,   299,   298,   300,   300,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   303,   302,   305,   304,   307,
     306,   309,   308,   311,   310,   313,   312,   315,   314,   317,
     316,   319,   318,   320,   320,   320,   321,   322,   324,   323,
     325,   325,   326,   326,   328,   327,   329,   329,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   332,   331,   334,   333,
     335,   335,   336,   336,   338,   337,   340,   339,   341,   341,
     342,   342,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   344,   345,   346,   348,   347,   350,   349,   352,
     351,   353,   355,   354,   356,   358,   357,   359,   359,   360,
     360,   362,   361,   364,   363,   365,   365,   366,   366,   367,
     367,   367,   367,   367,   367,   367,   367,   367,   368,   370,
     369,   371,   372,   373,   374,   376,   375,   377,   377,   378,
     378,   380,   379,   382,   381,   383,   383,   384,   384,   384,
     384,   384,   384,   384,   386,   385,   388,   387,   390,   389,
     392,   391,   393,   393,   394,   394,   396,   395,   398,   397,
     399,   399,   400,   400,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   403,
     402,   405,   404,   407,   406,   409,   408,   411,   410,   413,
     412,   415,   414,   417,   416,   419,   418,   421,   420,   423,
     422,   425,   424,   427,   426,   429,   428,   430,   430,   432,
     431,   433,   433,   434,   434,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   436,   438,   437,   439,
     440,   442,   441,   443,   443,   444,   444,   444,   444,   444,
     446,   445,   448,   447,   450,   449,   452,   451,   453,   453,
     454,   454,   454,   454,   454,   454,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   455,   457,   456,
     459,   458,   460,   462,   461,   463,   464,   466,   465,   467,
     467,   469,   468,   470,   471,   472,   474,   473,   475,   475,
     475,   475,   475,   477,   476,   479,   478,   481,   480,   483,
     482,   485,   484,   487,   486,   488,   488,   489,   491,   490,
     492,   492,   494,   493,   495,   495,   496,   496,   496,   496,
     496,   496,   496,   497,   499,   498,   501,   500,   502,   502,
     504,   503,   505,   505,   506,   506,   506,   506,   508,   507,
     509,   510,   511
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     4,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_LOGGING", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp4_object", "$@18", "sub_dhcp4",
  "$@19", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@20",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@21", "interfaces_list", "$@22", "dhcp_socket_type", "$@23",
  "socket_type", "outbound_interface", "$@24", "outbound_interface_value",
  "re_detect", "lease_database", "$@25", "hosts_database", "$@26",
  "hosts_databases", "$@27", "database_list", "not_empty_database_list",
  "database", "$@28", "database_map_params", "database_map_param",
  "database_type", "$@29", "db_type", "user", "$@30", "password", "$@31",
  "host", "$@32", "port", "name", "$@33", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@34", "keyspace", "$@35",
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@37", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@38",
  "sub_hooks_library", "$@39", "hooks_params", "hooks_param", "library",
  "$@40", "parameters", "$@41", "expired_leases_processing", "$@42",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@43",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@44",
  "sub_subnet4", "$@45", "subnet4_params", "subnet4_param", "subnet",
  "$@46", "subnet_4o6_interface", "$@47", "subnet_4o6_interface_id",
  "$@48", "subnet_4o6_subnet", "$@49", "interface", "$@50", "interface_id",
  "$@51", "client_class", "$@52", "require_client_classes", "$@53",
  "reservation_mode", "$@54", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@55", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@56",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@57", "sub_option_def_list", "$@58", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@59",
  "sub_option_def", "$@60", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@61",
  "option_def_record_types", "$@62", "space", "$@63", "option_def_space",
  "option_def_encapsulate", "$@64", "option_def_array", "option_data_list",
  "$@65", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@66", "sub_option_data", "$@67",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@68",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@69", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@70", "sub_pool4", "$@71",
  "pool_params", "pool_param", "pool_entry", "$@72", "user_context",
  "$@73", "comment", "$@74", "reservations", "$@75", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@76", "sub_reservation",
  "$@77", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@78", "server_hostname", "$@79",
  "boot_file_name", "$@80", "ip_address", "$@81", "duid", "$@82",
  "hw_address", "$@83", "client_id_value", "$@84", "circuit_id_value",
  "$@85", "flex_id_value", "$@86", "hostname", "$@87",
  "reservation_client_classes", "$@88", "relay", "$@89", "relay_map",
  "$@90", "client_classes", "$@91", "client_classes_list",
  "client_class_entry", "$@92", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@93", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@94", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@95",
  "control_socket_name", "$@96", "dhcp_ddns", "$@97", "sub_dhcp_ddns",
  "$@98", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@99", "server_ip", "$@100", "server_port",
  "sender_ip", "$@101", "sender_port", "max_queue_size", "ncr_protocol",
  "$@102", "ncr_protocol_value", "ncr_format", "$@103",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@104", "replace_client_name_value",
  "generated_prefix", "$@105", "dhcp6_json_object", "$@106",
  "dhcpddns_json_object", "$@107", "control_agent_json_object", "$@108",
  "logging_object", "$@109", "sub_logging", "$@110", "logging_params",
  "logging_param", "loggers", "$@111", "loggers_entries", "logger_entry",
  "$@112", "logger_params", "logger_param", "debuglevel", "severity",
  "$@113", "output_options_list", "$@114", "output_options_list_content",
  "output_entry", "$@115", "output_params_list", "output_params", "output",
  "$@116", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   243,   243,   243,   244,   244,   245,   245,   246,   246,
     247,   247,   248,   248,   249,   249,   250,   250,   251,   251,
     252,   252,   253,   253,   254,   254,   255,   255,   263,   264,
     265,   266,   267,   268,   269,   272,   277,   277,   288,   291,
     292,   295,   299,   306,   306,   313,   314,   317,   321,   328,
     328,   335,   336,   339,   343,   354,   364,   364,   380,   381,
     385,   386,   387,   388,   389,   390,   393,   393,   408,   408,
     417,   418,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   452,
     457,   462,   467,   472,   477,   483,   483,   494,   495,   498,
     499,   500,   501,   502,   503,   504,   507,   507,   516,   516,
     526,   526,   533,   534,   537,   537,   544,   546,   550,   556,
     556,   568,   568,   580,   580,   590,   591,   594,   595,   598,
     598,   608,   609,   612,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   622,   623,   624,   625,   626,   627,   628,
     629,   632,   632,   639,   640,   641,   642,   645,   645,   653,
     653,   661,   661,   669,   674,   674,   682,   687,   692,   697,
     702,   707,   712,   717,   717,   725,   725,   733,   738,   743,
     743,   753,   754,   757,   758,   759,   760,   761,   764,   769,
     774,   779,   784,   789,   789,   799,   800,   803,   804,   807,
     807,   817,   817,   827,   828,   829,   832,   833,   836,   836,
     844,   844,   852,   852,   863,   864,   867,   868,   869,   870,
     871,   872,   875,   880,   885,   890,   895,   900,   908,   908,
     921,   922,   925,   926,   933,   933,   959,   959,   970,   971,
     975,   976,   977,   978,   979,   980,   981,   982,   983,   984,
     985,   986,   987,   988,   989,   990,   991,   992,   993,   994,
     995,   996,   997,   998,   999,  1002,  1002,  1010,  1010,  1018,
    1018,  1026,  1026,  1034,  1034,  1042,  1042,  1050,  1050,  1058,
    1058,  1068,  1068,  1075,  1076,  1077,  1080,  1085,  1092,  1092,
    1103,  1104,  1108,  1109,  1112,  1112,  1120,  1121,  1124,  1125,
    1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,
    1136,  1137,  1138,  1139,  1140,  1141,  1148,  1148,  1161,  1161,
    1170,  1171,  1174,  1175,  1180,  1180,  1195,  1195,  1209,  1210,
    1213,  1214,  1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,  1226,  1229,  1231,  1236,  1238,  1238,  1246,  1246,  1254,
    1254,  1262,  1264,  1264,  1272,  1281,  1281,  1293,  1294,  1299,
    1300,  1305,  1305,  1317,  1317,  1329,  1330,  1335,  1336,  1341,
    1342,  1343,  1344,  1345,  1346,  1347,  1348,  1349,  1352,  1354,
    1354,  1362,  1364,  1366,  1371,  1379,  1379,  1391,  1392,  1395,
    1396,  1399,  1399,  1409,  1409,  1419,  1420,  1423,  1424,  1425,
    1426,  1427,  1428,  1429,  1432,  1432,  1440,  1440,  1465,  1465,
    1495,  1495,  1505,  1506,  1509,  1510,  1513,  1513,  1522,  1522,
    1531,  1532,  1535,  1536,  1540,  1541,  1542,  1543,  1544,  1545,
    1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1557,
    1557,  1565,  1565,  1573,  1573,  1581,  1581,  1589,  1589,  1597,
    1597,  1605,  1605,  1613,  1613,  1621,  1621,  1629,  1629,  1637,
    1637,  1650,  1650,  1660,  1660,  1671,  1671,  1681,  1682,  1685,
    1685,  1695,  1696,  1699,  1700,  1703,  1704,  1705,  1706,  1707,
    1708,  1709,  1710,  1711,  1712,  1713,  1716,  1718,  1718,  1726,
    1735,  1742,  1742,  1752,  1753,  1756,  1757,  1758,  1759,  1760,
    1763,  1763,  1771,  1771,  1781,  1781,  1793,  1793,  1803,  1804,
    1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,
    1817,  1818,  1819,  1820,  1821,  1822,  1823,  1826,  1831,  1831,
    1839,  1839,  1847,  1852,  1852,  1860,  1865,  1870,  1870,  1878,
    1879,  1882,  1882,  1890,  1895,  1900,  1905,  1905,  1913,  1916,
    1919,  1922,  1925,  1931,  1931,  1941,  1941,  1948,  1948,  1955,
    1955,  1967,  1967,  1977,  1977,  1988,  1989,  1993,  1997,  1997,
    2009,  2010,  2014,  2014,  2022,  2023,  2026,  2027,  2028,  2029,
    2030,  2031,  2032,  2035,  2040,  2040,  2048,  2048,  2058,  2059,
    2062,  2062,  2070,  2071,  2074,  2075,  2076,  2077,  2080,  2080,
    2088,  2093,  2098
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
#line 4653 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2103 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
